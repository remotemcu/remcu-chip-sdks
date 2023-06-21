/**
 * \file
 *
 * \brief USBC host driver
 * Compliance with common driver UHD
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include <stdlib.h>

/* Get USB host configuration */
#include "conf_usb_host.h"
#include "sysclk.h"
#include "uhd.h"
#include "usbc_otg.h"
#include "usbc_host.h"

#if !(SAM4L)
# error The current USBC Host Driver supports only SAM4L.
#endif

//#define dbg_print printf
#define dbg_print(...)

//#define dbgp_ctrl printf
#define dbgp_ctrl(...)

//#define dbgp_ep printf
#define dbgp_ep(...)

#ifndef UHD_USB_INT_FUN
# define UHD_USB_INT_FUN USBC_Handler
#endif

#ifndef UHD_USB_INT_LEVEL
# define UHD_USB_INT_LEVEL 5 // By default USB interrupt have low priority
#endif

#ifdef UDD_ENABLE
// Dual (device/host) mode enabled
extern void udd_interrupt(void);
extern void udc_stop(void);
extern void udc_start(void);
#else
// Host mode only = Device mode disabled
# define udd_interrupt() Assert(false) // System error
# define udc_start()
# define udc_stop()
#endif

#ifdef UHD_START_MODE_MANUAL
// Automatic start mode is disabled
# define uhc_start()
# define udc_start()
#endif

#ifndef UHD_BULK_INTERVAL_MIN
// Minimal bulk interval value
#  define UHD_BULK_INTERVAL_MIN 1
#endif

// Optional UHC callbacks
#ifndef UHC_MODE_CHANGE
# define UHC_MODE_CHANGE(arg)
#endif
#ifndef UHC_SOF_EVENT
# define UHC_SOF_EVENT()
#endif
#ifndef UHC_VBUS_CHANGE
# define UHC_VBUS_CHANGE(b_present)
#endif
#ifndef UHC_VBUS_ERROR
# define UHC_VBUS_ERROR()
#endif

/**
 * \ingroup uhd_group
 * \defgroup uhd_usbb_group USBC Host Driver
 *
 * \section USB_CONF USB dual role configuration
 * The defines UHD_ENABLE and UDD_ENABLE must be added in project to allow
 * the USB low level (UHD) to manage or not the dual role (device and host).
 *
 * \section USBC_CONF USBC Custom configuration
 * The following USBC driver configuration must be defined in conf_usb_host.h
 * file of the application.
 *
 * UHD_USB_INT_LEVEL<br>
 * Option to change the interrupt priority (0 to 15) by default 5 (recommended).
 *
 * UHD_USB_INT_FUN<br>
 * Option to fit interrupt function to what defined in exception table.
 *
 * UHD_BULK_INTERVAL_MIN<br>
 * Feature to reduce or increase bulk token rate when it's NAKed (0, 1 ...).
 * To adjust bandwidth usage.
 * Default value 1.
 *
 * UHD_NO_SLEEP_MGR<br>
 * Feature to work without sleep manager module.
 * Default not defined.
 * Note that with this feature defined sleep manager must not be used in
 * application.
 *
 * \section Callbacks management
 * The USB driver is fully managed by interrupt and does not request periodic
 * task. Thereby, the USB events use callbacks to transfer the information.
 * The callbacks can be declared in static during compilation
 * or dynamically during code execution.
 *
 * \section Power mode management
 * The driver uses the sleepmgr service to manage the different sleep modes.
 * The sleep mode depends on USB driver state (uhd_usbc_state_enum).
 * @{
 */

// Check USB host configuration
#ifdef USB_HOST_HS_SUPPORT
#  error The High speed mode is not supported on this part, please remove USB_HOST_HS_SUPPORT in conf_usb_host.h
#endif


/**
 * \name Power management
 */
//@{
#ifndef UHD_NO_SLEEP_MGR

#include "sleepmgr.h"
//! States of USBC interface
enum uhd_usbc_state_enum {
	UHD_STATE_OFF = 0,
	UHD_STATE_WAIT_ID_HOST = 1,
	UHD_STATE_NO_VBUS = 2,
	UHD_STATE_DISCONNECT = 3,
	UHD_STATE_SUSPEND = 4,
	UHD_STATE_IDLE = 5,
};


/*! \brief Manages the sleep mode following the USBC state
 *
 * \param new_state  New USBC state
 */
static void uhd_sleep_mode(enum uhd_usbc_state_enum new_state)
{
	enum sleepmgr_mode sleep_mode[] = {
		SLEEPMGR_BACKUP,  // UHD_STATE_OFF (not used)
#if OTG_ID_IO || OTG_VBUS_IO || UHD_VBERR_IO
		SLEEPMGR_SLEEP_1, // UHD_STATE_WAIT_ID_HOST
		SLEEPMGR_SLEEP_1, // UHD_STATE_NO_VBUS
		SLEEPMGR_SLEEP_1, // UHD_STATE_DISCONNECT
#else
		SLEEPMGR_RET,     // UHD_STATE_WAIT_ID_HOST
		SLEEPMGR_RET,     // UHD_STATE_NO_VBUS
		SLEEPMGR_RET,     // UHD_STATE_DISCONNECT
#endif
		/* In suspend state, the SLEEPMGR_RET level is authorized
		 * even if ID Pin, Vbus... pins are managed through IO.
		 * When a ID disconnection or Vbus low event occurs,
		 * the asynchrone USB wakeup occurs.
		 */
		SLEEPMGR_RET,     // UHD_STATE_SUSPEND
		SLEEPMGR_SLEEP_0, // UHD_STATE_IDLE
	};
	static enum uhd_usbc_state_enum uhd_state = UHD_STATE_OFF;

	if (uhd_state == new_state) {
		return; // No change
	}
	if (new_state != UHD_STATE_OFF) {
		// Lock new limit
		sleepmgr_lock_mode(sleep_mode[new_state]);
	}
	if (uhd_state != UHD_STATE_OFF) {
		// Unlock old limit
		sleepmgr_unlock_mode(sleep_mode[uhd_state]);
	}
	uhd_state = new_state;
}

#else
#  define uhd_sleep_mode(arg)
#endif // UHD_NO_SLEEP_MGR
//@}

/**
 * \name USB IO PADs handlers
 */
//@{

#if OTG_ID_IO || OTG_ID_EIC
/**
 * USB ID pin change handler
 */
static void otg_id_handler(void)
{
	pad_ack_id_interrupt();
	if (Is_pad_id_device()) {
		uhc_stop(false);
		UHC_MODE_CHANGE(false);
		otg_enable_device_mode();
		udc_start();
	} else {
		udc_stop();
		UHC_MODE_CHANGE(true);
		otg_enable_host_mode();
		uhc_start();
	}
}
#endif

#if OTG_VBUS_IO || OTG_VBUS_EIC
/**
 * USB VBus pin change handler
 */
static void uhd_vbus_handler(void)
{
	pad_ack_vbus_interrupt();
	while (!Is_otg_clock_usable());
	if (Is_pad_vbus_high()) {
		otg_unfreeze_clock();
		uhd_vbus_is_on();
		/* Freeze USB clock to use wakeup interrupt
		 * to detect connection.
		 * After detection of wakeup interrupt,
		 * the clock is unfreeze to have the true
		 * connection interrupt.
		 */
		uhd_enable_wakeup_interrupt();
		otg_freeze_clock();
		uhd_sleep_mode(UHD_STATE_DISCONNECT);
		UHC_VBUS_CHANGE(true);
	} else {
		otg_unfreeze_clock();
		uhd_vbus_is_off();
		otg_freeze_clock();
		uhd_sleep_mode(UHD_STATE_NO_VBUS);
		UHC_VBUS_CHANGE(false);
	}
}
#endif

#if UHD_VBERR_IO || UHD_VBERR_EIC
/**
 * USB VBus error pin change handler
 */
static void uhd_vberr_handler(void)
{
	pad_ack_vbus_error_interrupt();
	if (Is_pad_vbus_error()) {
		UHC_VBUS_ERROR();
	} else {
		// End of error
	}
}
#endif
//@}

/**
 * @brief USB SRAM data containing pipe descriptor table
 * The content of the USB SRAM can be :
 * - modified by USB hardware interface to update pipe status.
 *   Thereby, it is read by software.
 * - modified by USB software to control pipe.
 *   Thereby, it is read by hardware.
 * This data section is volatile.
 *
 * @{
 */
COMPILER_ALIGNED(32)
static volatile uhd_desc_table_t uhd_g_pipe_table[UHD_PEP_NB];

//! State of USBC OTG initialization
static bool otg_initialized = false;

//! Store the callback to be call at the end of reset signal
static uhd_callback_reset_t uhd_reset_callback = NULL;

/**
 * \name Control endpoint low level management routine.
 *
 * This function performs control endpoint management.
 * It handles the SETUP/DATA/HANDSHAKE phases of a control transaction.
 */
//@{

/**
 * \brief Buffer to store the sent/received data on control endpoint
 *
 * Used to avoid a RAM buffer overflow when the payload buffer
 * is smaller than control endpoint size.
 * Also used when payload buffer is not word aligned.
 */
uint32_t uhd_ctrl_buffer[64/4];

/**
 * \brief Structure to store the high level setup request
 */

struct uhd_ctrl_request_t{

	//! Buffer to store the setup DATA phase
	uint8_t *payload;
	//! Callback called when buffer is empty or full
	uhd_callback_setup_run_t callback_run;
	//! Callback called when request is completed
	uhd_callback_setup_end_t callback_end;
	//! Next setup request to process
	struct uhd_ctrl_request_t *next_request;
	//! Setup request definition
	usb_setup_req_t req;
	//! Size of buffer used in DATA phase
	uint16_t payload_size;
	//! USB address of control endpoint
	usb_add_t add;
};

//! Flag to delay a ZLP OUT on control endpoint
static bool uhd_b_zlp_out_delayed = false;

//! Entry points of setup request list
struct uhd_ctrl_request_t *uhd_ctrl_request_first;
struct uhd_ctrl_request_t *uhd_ctrl_request_last;

//! Remaining time for on-going setup request (No request on-going if equal 0)
volatile uint16_t uhd_ctrl_request_timeout;

//! Number of transfered byte on DATA phase of current setup request
uint16_t uhd_ctrl_nb_trans;

//! Flag to delay a suspend request after all on-going setup request
static bool uhd_b_suspend_requested;

//! Bit definitions to store setup request state machine
typedef enum {

	//! Wait a SETUP packet
	UHD_CTRL_REQ_PHASE_SETUP = 0,
	//! Wait a OUT data packet
	UHD_CTRL_REQ_PHASE_DATA_OUT = 1,
	//! Wait a IN data packet
	UHD_CTRL_REQ_PHASE_DATA_IN = 2,
	//! Wait a IN ZLP packet
	UHD_CTRL_REQ_PHASE_ZLP_IN = 3,
	//! Wait a OUT ZLP packet
	UHD_CTRL_REQ_PHASE_ZLP_OUT = 4,
} uhd_ctrl_request_phase_t;
uhd_ctrl_request_phase_t uhd_ctrl_request_phase;

//@}


/**
 * \name Management of bulk/interrupt/isochronous endpoints
 *
 * The UHD manages the data transfer on endpoints:
 * - Start data transfer on endpoint with USB DMA
 * - Send a ZLP packet if requested
 * - Call registered callback to signal end of transfer
 * The transfer abort and stall feature are supported.
 */
//@{

//! Structure definition to store registered jobs on a pipe
typedef struct {

	//! Buffer located in internal RAM to send or fill during job
	uint8_t *buf;
	//! Internal buffer allocated in internal RAM to receive data in case of small user buffer
	uint8_t *buf_internal;
	//! Size of buffer to send or fill
	iram_size_t buf_size;
	//! Total number of transfered data on endpoint
	iram_size_t nb_trans;
	//! Callback to call at the end of transfer
	uhd_callback_trans_t call_end;

	//! timeout on this request (ms)
	uint16_t timeout;

	//! A job is registered on this pipe
	uint8_t busy:1;
	//! A short packet is requested for this job on endpoint IN
	uint8_t b_shortpacket:1;
} uhd_pipe_job_t;

//! Array to register a job on bulk/interrupt/isochronous endpoint
static uhd_pipe_job_t uhd_pipe_job[UHD_PEP_NB - 1];

//! Variables to manage the suspend/resume sequence
static uint8_t uhd_suspend_start;
static uint8_t uhd_resume_start;
static uint8_t uhd_pipes_unfreeze;

//! Variable to manage error on pipes
static uint8_t uhd_pipes_error;

//@}

static void uhd_interrupt(void);
static void uhd_sof_interrupt(void);
static void uhd_ctrl_interrupt(void);
static void uhd_ctrl_phase_setup(void);
static void uhd_ctrl_phase_data_in_start(void);
static void uhd_ctrl_phase_data_in(void);
static void uhd_ctrl_phase_zlp_in(void);
static void uhd_ctrl_phase_data_out(void);
static void uhd_ctrl_phase_zlp_out(void);
static void uhd_ctrl_request_end(uhd_trans_status_t status);

static uhd_trans_status_t uhd_pipe_get_error(uint8_t pipe);
static uint8_t uhd_get_pipe(usb_add_t add, usb_ep_t endp);
static void uhd_pipe_trans_complet(uint8_t pipe);
static void uhd_pipe_interrupt(uint8_t pipe);
static void uhd_ep_abort_pipe(uint8_t pipe, uhd_trans_status_t status);
static void uhd_pipe_finish_job(uint8_t pipe, uhd_trans_status_t status);


/**
 * \internal
 * \brief Function called by USBC interrupt handler to manage USB interrupts
 *
 * It manages the interrupt redirection between host or device interrupt.
 * It answers to OTG events (ID pin change).
 *
 * Note:
 * Here, the global interrupt mask is not cleared when an USB interrupt
 * is enabled because this one can not occurred during the USB ISR
 * (=during INTX is masked).
 * See Technical reference $3.8.3 Masking interrupt requests
 * in peripheral modules.
 */
ISR(UHD_USB_INT_FUN)
{
	// Redirection to host or device interrupt
	if (Is_otg_device_mode_enabled()) {
		udd_interrupt();
	} else {
		uhd_interrupt();
	}
	otg_data_memory_barrier();
}

bool otg_dual_enable(void)
{
	if (otg_initialized) {
		return false; // Dual role already initialized
	}
	otg_initialized = true;

	//* Enable USB hardware clock
	sysclk_enable_usb();

	//* Link USB interrupt on OTG interrupt in dual role
	NVIC_ClearPendingIRQ(USBC_IRQn);
	NVIC_SetPriority(USBC_IRQn, UHD_USB_INT_LEVEL);
	NVIC_EnableIRQ(USBC_IRQn);

	// Always authorize asynchronous USB interrupts to exit of sleep mode
	usbc_async_wake_up_enable();

#if OTG_ID_EIC || OTG_VBUS_EIC || UHD_VBERR_EIC
	eic_enable(EIC);
#endif

#if OTG_ID_IO || OTG_ID_EIC
	pad_id_init();
	if (Is_pad_id_device()) {
		otg_enable_device_mode();
		uhd_sleep_mode(UHD_STATE_WAIT_ID_HOST);
		UHC_MODE_CHANGE(false);
		udc_start();
	} else {
		otg_enable_host_mode();
		UHC_MODE_CHANGE(true);
		uhc_start();
	}

	// End of host or device startup,
	// the current mode selected is already started now
	return true; // ID pin management has been enabled
#else
	uhd_sleep_mode(UHD_STATE_OFF);
	return false; // ID pin management has not been enabled
#endif
}


void otg_dual_disable(void)
{
	if (!otg_initialized) {
		return; // Dual role not initialized
	}
	otg_initialized = false;

	// Do not authorize asynchronous USB interrupts
	usbc_async_wake_up_disable();
	otg_unfreeze_clock();
#if OTG_ID_IO || OTG_ID_EIC
	pad_id_interrupt_disable();
#endif
#if OTG_ID_EIC || OTG_VBUS_EIC || UHD_VBERR_EIC
	eic_disable(EIC);
#endif
	otg_disable();
	sysclk_disable_usb();
	NVIC_ClearPendingIRQ(USBC_IRQn);
	NVIC_DisableIRQ(USBC_IRQn);
	uhd_sleep_mode(UHD_STATE_OFF);
}


void uhd_enable(void)
{
	irqflags_t flags;

	// To avoid USB interrupt before end of initialization
	flags = cpu_irq_save();

	if (otg_dual_enable()) {
		// The current mode has been started by otg_dual_enable()
		cpu_irq_restore(flags);
		return;
	}

#if OTG_ID_EIC || OTG_ID_IO
	// Check that the host mode is selected by ID pin
	if (Is_pad_id_device()) {
		cpu_irq_restore(flags);
		return; // Host is not the current mode
	}
#else
	// ID pin not used then enable host mode
	otg_enable_host_mode();
#endif

	otg_enable();
	otg_unfreeze_clock();

	memset((uint8_t *) uhd_g_pipe_table, 0, sizeof(uhd_g_pipe_table));
	otg_register_desc_tab(uhd_g_pipe_table);

	uhd_ctrl_request_first = NULL;
	uhd_ctrl_request_last = NULL;
	uhd_ctrl_request_timeout = 0;
	uhd_suspend_start = 0;
	uhd_resume_start = 0;
	uhd_b_suspend_requested = false;

	// Clear all interrupts that may have been set by a previous host mode
	uhd_ack_all_interrupts();

	// Need on more cycle in the case that the CPIU/PBx frequency is 48 MHz.
	// Otherwise, there is a race between the previous clear in UHINT and
	// the set of the HWUPI interrupt.
	__DMB();
	__NOP();

	uhd_sleep_mode(UHD_STATE_NO_VBUS);

	/* Enable VBus error monitoring */
#if UHD_VBERR_EIC || UHD_VBERR_IO
	pad_vbus_error_init();
#endif

	/* Enable VBus monitoring */
# if OTG_VBUS_EIC || OTG_VBUS_IO
	pad_vbus_init(UHD_USB_INT_LEVEL);
	/* Force Vbus interrupt when Vbus is always high
	 * This is possible due to a short timing between a Host mode stop/start.
	 */
	if (Is_pad_vbus_high()) {
		uhd_vbus_handler();
		otg_unfreeze_clock();
	}
# else
	// No VBus detect, assume always high
	uhd_vbus_is_on();
	/* Freeze USB clock to use wakeup interrupt
	 * to detect connection.
	 * After detection of wakeup interrupt,
	 * the clock is unfreeze to have the true
	 * connection interrupt.
	 */
	uhd_enable_wakeup_interrupt();
	uhd_sleep_mode(UHD_STATE_DISCONNECT);
	UHC_VBUS_CHANGE(true); /* Changed to HIGH */
# endif

	/* enable VBus */
	pad_vbus_enable();

	// Enable main control interrupt
	// Connection, SOF and reset
	uhd_enable_sof_interrupt();
	uhd_enable_reset_sent_interrupt();
	uhd_enable_connection_int();
	otg_freeze_clock();

	cpu_irq_restore(flags);
}


void uhd_disable(bool b_id_stop)
{
	irqflags_t flags;
	UNUSED(b_id_stop);
	// Check USB clock ready after a potential sleep mode < IDLE
	while (!Is_otg_clock_usable());

	otg_unfreeze_clock();

	// Disable Vbus change and error interrupts
#if OTG_VBUS_IO || OTG_VBUS_EIC
	pad_vbus_interrupt_disable();
#endif
#if UHD_VBERR_IO || UHD_VBERR_EIC
	pad_vbus_error_interrupt_disable();
#endif

	// Disable main control interrupt
	// (Connection, disconnection, SOF and reset)
	uhd_disable_all_interrupts();
	uhd_disable_sof();
	pad_vbus_disable();
	uhc_notify_connection(false);
	otg_freeze_clock();

#if OTG_ID_EIC || OTG_ID_IO
	uhd_sleep_mode(UHD_STATE_WAIT_ID_HOST);
	if (!b_id_stop) {
		return; // No need to disable host, it is done automatically by hardware
	}
#endif

	flags = cpu_irq_save();
	otg_dual_disable();
	cpu_irq_restore(flags);
}

uhd_speed_t uhd_get_speed(void)
{
	switch( uhd_get_speed_mode() ) {
	case USBC_USBSTA_SPEED_FULL:
		return UHD_SPEED_FULL;

	case USBC_USBSTA_SPEED_LOW:
		return UHD_SPEED_LOW;

	default:
		Assert(false);
		return UHD_SPEED_LOW;
	}
}

uint16_t uhd_get_frame_number(void)
{
	return uhd_get_sof_number();
}

uint16_t uhd_get_microframe_number(void)
{
	return uhd_get_microsof_number();
}

void uhd_send_reset(uhd_callback_reset_t callback)
{
	uhd_reset_callback = callback;
	uhd_start_reset();
}

void uhd_suspend(void)
{
	if (uhd_ctrl_request_timeout) {
		// Delay suspend after setup requests
		uhd_b_suspend_requested = true;
		return;
	}
	// Save pipe freeze states and freeze pipes
	uhd_pipes_unfreeze = 0;
	for (uint8_t pipe = 1; pipe < UHD_PEP_NB; pipe++) {
		uhd_pipes_unfreeze |= (!Is_uhd_pipe_frozen(pipe)) << pipe;
		uhd_freeze_pipe(pipe);
	}
	// Wait three SOFs before entering in suspend state
	uhd_suspend_start = 3;
}

bool uhd_is_suspend(void)
{
	return !Is_uhd_sof_enabled();
}

void uhd_resume(void)
{
	if (Is_uhd_sof_enabled()) {
		// Currently in IDLE mode (!=Suspend)
		if (uhd_suspend_start) {
			// Suspend mode on going
			// then stop it and start resume event
			uhd_suspend_start = 0;
			uhd_resume_start = 1;
		}
		return;
	}
	// Check USB clock ready after a potential sleep mode < IDLE
	while (!Is_otg_clock_usable());
	otg_unfreeze_clock();
	uhd_enable_sof();
	uhd_send_resume();
	uhd_sleep_mode(UHD_STATE_IDLE);
}

bool uhd_ep0_alloc(
		usb_add_t add,
		uint8_t ep_size)
{
	if (ep_size < 8) {
		return false;
	}
#ifdef USB_HOST_HUB_SUPPORT
	if (Is_uhd_pipe_enabled(0)) {
		// Already allocated
#error TODO Add USB address in a list
		return true;
	}
#endif

	// Clear pipe control
	memset((uint8_t *)&uhd_g_pipe_table[0], 0, sizeof(uhd_g_pipe_table[0]));

	// Enable pipe
	uhd_enable_pipe(0);
	uhd_configure_pipe(0, // Pipe 0
			0, // No frequency
			0, // endpoint 0
			USBC_UECFG0_EPTYPE_CONTROL >> USBC_UECFG0_EPTYPE_Pos,
			USBC_UPCFG0_PTOKEN_SETUP >> USBC_UPCFG0_PTOKEN_Pos,
#ifdef USB_HOST_HUB_SUPPORT
			64, // Max size for control endpoint
#else
			ep_size,
#endif
			USBC_UECFG0_EPBK_SINGLE >> USBC_UPCFG0_PBK_Pos);

	uhd_udesc_set_uhaddr(0, add);
	uhd_udesc_set_buf0_addr(0, (uint8_t*)uhd_ctrl_buffer);

	// Always enable stall and error interrupts of control endpoint
	uhd_enable_stall_interrupt(0);
	uhd_enable_pipe_error_interrupt(0);
	uhd_enable_pipe_interrupt(0);
	return true;
}

bool uhd_ep_alloc(
		usb_add_t add,
		usb_ep_desc_t *ep_desc,
		uhd_speed_t speed)
{
	uint8_t ep_addr;
	uint8_t ep_type;
	uint8_t ep_dir;
	uint8_t ep_interval;
	(void)speed; // No high speed currently

	for (uint8_t pipe = 1; pipe < UHD_PEP_NB; pipe++) {
		if (Is_uhd_pipe_enabled(pipe)) {
			continue;
		}
		// Clear pipe control
		memset((uint8_t *) &uhd_g_pipe_table[pipe], 0, sizeof(uhd_g_pipe_table[0]));

		// Enable pipe
		uhd_enable_pipe(pipe);
		ep_addr = ep_desc->bEndpointAddress & USB_EP_ADDR_MASK;
		ep_dir = (ep_desc->bEndpointAddress & USB_EP_DIR_IN)?
				USBC_UPCFG0_PTOKEN_IN >> USBC_UPCFG0_PTOKEN_Pos:
				USBC_UPCFG0_PTOKEN_OUT >> USBC_UPCFG0_PTOKEN_Pos;
		ep_type = ep_desc->bmAttributes & USB_EP_TYPE_MASK;
#if UHD_BULK_INTERVAL_MIN
		if (ep_type == USB_EP_TYPE_BULK) {
			if (ep_desc->bInterval > UHD_BULK_INTERVAL_MIN) {
				ep_interval = ep_desc->bInterval;
			} else {
				ep_interval = UHD_BULK_INTERVAL_MIN;
			}
		} else {
			ep_interval = ep_desc->bInterval;
		}
#else
		ep_interval = ep_desc->bInterval;
#endif
		uhd_configure_pipe(pipe, ep_interval, ep_addr, ep_type, ep_dir,
				le16_to_cpu(ep_desc->wMaxPacketSize),
				0);
		uhd_udesc_set_uhaddr(pipe,add);
		uhd_enable_pipe(pipe);
		uhd_ack_out_ready(pipe);

		// Enable endpoint interrupts
		uhd_enable_stall_interrupt(pipe);
		uhd_enable_pipe_error_interrupt(pipe);
		uhd_enable_pipe_interrupt(pipe);
		return true;
	}
	return false;
}


void uhd_ep_free(usb_add_t add, usb_ep_t endp)
{
	// Search endpoint(s) in all pipes
	for (uint8_t pipe = 0; pipe < UHD_PEP_NB; pipe++) {
		if (add != uhd_udesc_get_uhaddr(pipe)) {
			continue;
		}
		if (endp != 0xFF) {
			// Disable specific endpoint number
				if (!((endp == 0) && (0 == uhd_udesc_get_epnum(pipe)))) {
					// It is not the control endpoint
					if (endp != uhd_get_pipe_endpoint_address(pipe)) {
						continue; // Mismatch
					}
				}
		}

		if (pipe == 0) {
			// Disable and stop transfer on control endpoint
#ifdef USB_HOST_HUB_SUPPORT
#error TODO the list address must be updated
			if (uhd_ctrl_request_timeout
				&& (uhd_ctrl_request_first->add == add)) {
				uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
			}
#else
			uhd_disable_pipe(pipe);
			if (uhd_ctrl_request_timeout ||
				(uhd_pipes_error & 1)) {
				uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
			}
#endif
			continue;
		}

		// Endpoint interrupt, bulk or isochronous
		// Disable and stop transfer on this pipe
		uhd_disable_pipe(pipe);
		uhd_pipe_finish_job(pipe, UHD_TRANS_DISCONNECT);
	}
}

bool uhd_setup_request(
		usb_add_t add,
		usb_setup_req_t *req,
		uint8_t *payload,
		uint16_t payload_size,
		uhd_callback_setup_run_t callback_run,
		uhd_callback_setup_end_t callback_end)
{
	irqflags_t flags;
	struct uhd_ctrl_request_t *request;
	bool b_start_request = false;

	request = malloc(sizeof(struct uhd_ctrl_request_t));
	if (request == NULL) {
		Assert(false);
		return false;
	}

	// Fill structure
	request->add = (uint8_t) add;
	memcpy(&request->req, req, sizeof(usb_setup_req_t));
	request->payload = payload;
	request->payload_size = payload_size;
	request->callback_run = callback_run;
	request->callback_end = callback_end;
	request->next_request = NULL;

	// Add this request in the queue
	flags = cpu_irq_save();
	if (uhd_ctrl_request_first == NULL) {
		uhd_ctrl_request_first = request;
		b_start_request = true;
	} else {
		uhd_ctrl_request_last->next_request = request;
	}
	uhd_ctrl_request_last = request;
	cpu_irq_restore(flags);

	if (b_start_request) {
		// Start immediately request
		uhd_ctrl_phase_setup();
	}
	return true;
}

bool uhd_ep_run(
		usb_add_t add,
		usb_ep_t endp,
		bool b_shortpacket,
		uint8_t *buf,
		iram_size_t buf_size,
		uint16_t timeout,
		uhd_callback_trans_t callback)
{
	irqflags_t flags;
	uint8_t pipe;
	uhd_pipe_job_t *ptr_job;

	pipe = uhd_get_pipe(add, endp);
	if (pipe == UHD_PEP_NB) {
		return false; // pipe not found
	}
	// Get job about pipe
	ptr_job = &uhd_pipe_job[pipe - 1];
	flags = cpu_irq_save();
	if (ptr_job->busy == true) {
		cpu_irq_restore(flags);
		return false; // Job already on going
	}
	ptr_job->busy = true;

	// No job running. Let's setup a new one.
	ptr_job->buf = buf;
	ptr_job->buf_size = buf_size;
	ptr_job->nb_trans = 0;
	ptr_job->timeout = timeout;
	ptr_job->b_shortpacket = b_shortpacket;
	ptr_job->call_end = callback;
	uhd_udesc_rst_buf0_ctn(pipe);
	uhd_udesc_rst_buf0_size(pipe);
	cpu_irq_restore(flags);

	// Request first transfer
	uhd_pipe_trans_complet(pipe);
	return true;
}

void uhd_ep_abort(usb_add_t add, usb_ep_t endp)
{
	uint8_t pipe;

	pipe = uhd_get_pipe(add, endp);
	if (pipe == UHD_PEP_NB) {
		return; // pipe not found
	}
	uhd_ep_abort_pipe(pipe, UHD_TRANS_ABORTED);
}

/**
 * \internal
 * \brief Function called by USBC interrupt to manage USB host interrupts
 *
 * USB host interrupt events are split into four sections:
 * - USB line events
 *   (VBus error, device dis/connection, SOF, reset, suspend, resume, wakeup)
 * - control endpoint events
 *   (setup reception, end of data transfer, underflow, overflow, stall, error)
 * - bulk/interrupt/isochronous endpoints events
 *   (end of data transfer, stall, error)
 */
static void uhd_interrupt(void)
{
	uint8_t pipe_int;

	// Manage SOF interrupt
	if (Is_uhd_sof()) {
		uhd_ack_sof();
		uhd_sof_interrupt();
		goto uhd_interrupt_exit_sof;
	}

	dbg_print("%c ", Is_uhd_low_speed_mode() ? 'L' :
			(Is_uhd_high_speed_mode() ? 'H' : 'F'));

	// Manage pipe interrupts
	pipe_int = uhd_get_interrupt_pipe_number();
	if (pipe_int == 0) {
		dbg_print("0: ");
		// Interrupt acked by control endpoint managed
		uhd_ctrl_interrupt();
		goto uhd_interrupt_exit;
	}
	if (pipe_int != UHD_PEP_NB) {
		dbg_print("%x: ", pipe_int);
		// Interrupt acked by bulk/interrupt/isochronous endpoint
		uhd_pipe_interrupt(pipe_int);
		goto uhd_interrupt_exit;
	}
	// USB bus reset detection
	if (Is_uhd_reset_sent()) {
		uhd_ack_reset_sent();
		dbg_print("RST ");
		if (uhd_reset_callback != NULL) {
			uhd_reset_callback();
		}
		goto uhd_interrupt_exit;
	}

	// Check USB clock ready after asynchronous interrupt
	while (!Is_otg_clock_usable());
	otg_unfreeze_clock();

	// Manage dis/connection event
	if (Is_uhd_disconnection() && Is_uhd_disconnection_int_enabled()) {
		// This should be the normal way to handle this event.
		uhd_ack_disconnection();
		uhd_disable_disconnection_int();
		dbg_print("disc ");
		// Stop reset signal, in case of disconnection during reset
		uhd_stop_reset();
		// Disable wakeup/resumes interrupts,
		// in case of disconnection during suspend mode
		uhd_disable_wakeup_interrupts();
		/* Enable connection detection through asynchrone
		 * wakeup interrupt
		 */
		uhd_ack_connection();
		uhd_enable_connection_int();
		uhd_ack_wakeup();
		uhd_enable_wakeup_interrupt();
		otg_freeze_clock();
		uhd_suspend_start = 0;
		uhd_resume_start = 0;
		uhd_sleep_mode(UHD_STATE_DISCONNECT);
		uhc_notify_connection(false);
		goto uhd_interrupt_exit;
	}
	if (Is_uhd_connection() && Is_uhd_connection_int_enabled()) {
		uhd_ack_connection();
		uhd_disable_connection_int();
		dbg_print("conn ");
		uhd_ack_disconnection();
		uhd_enable_disconnection_int();
		uhd_enable_sof();
		uhd_sleep_mode(UHD_STATE_IDLE);
		uhd_suspend_start = 0;
		uhd_resume_start = 0;
		uhc_notify_connection(true);
		goto uhd_interrupt_exit;
	}

	if (Is_uhd_wakeup_interrupt_enabled() && (Is_uhd_wakeup() &&
			Is_uhd_connection_int_enabled())) {
		/* Here the wakeup interrupt has been used to detect connection
		 * with an asynchrone interrupt
		 */
		uhd_disable_wakeup_interrupt();
		goto uhd_interrupt_exit;
	}

	if (Is_uhd_wakeup_interrupt_enabled() && (Is_uhd_wakeup() ||
			Is_uhd_downstream_resume() || Is_uhd_upstream_resume())) {
		dbg_print("Wkup ");
		// Disable wakeup/resumes interrupts
		USBC->USBC_UHINTECLR = USBC_UHINTECLR_HWUPIEC
				| USBC_UHINTECLR_RSMEDIEC
				| USBC_UHINTECLR_RXRSMIEC;
		uhd_enable_sof();
		if ((!Is_uhd_downstream_resume())
				&& (!Is_uhd_disconnection())) {
			// It is a upstream resume
			// Note: When the CPU exits from a deep sleep mode, the event
			// Is_uhd_upstream_resume() can be not detected
			// because the USB clock are not available.

			// In High speed mode a downstream resume must be sent
			// after a upstream to avoid a disconnection.
			if (Is_uhd_high_speed_mode()) {
				uhd_send_resume();
			}
		}
		// Wait 50ms before restarting transfer
		uhd_resume_start = 50;
		uhd_sleep_mode(UHD_STATE_IDLE);
		goto uhd_interrupt_exit;
	}

	Assert(false); // Interrupt event no managed
uhd_interrupt_exit:
	dbg_print("\n\r");
uhd_interrupt_exit_sof:
	return;
}


/**
 * \internal
 * \brief Manages timeouts and actions based on SOF events
 * - Suspend delay
 * - Resume delay
 * - Setup packet delay
 * - Timeout on endpoint control transfer
 * - Timeouts on bulk/interrupt/isochronous endpoint transfers
 * - UHC user notification
 * - SOF user notification
 */
static void uhd_sof_interrupt(void)
{
	uint8_t pipe;
	// Manage a delay to enter in suspend
	if (uhd_suspend_start) {
		if (--uhd_suspend_start == 0) {
			uint8_t pos;
			// In case of high CPU frequency,
			// the current Keep-Alive/SOF can be always on-going
			// then wait end of SOF generation
			// to be sure that disable SOF has been accepted
			pos = Is_uhd_low_speed_mode() ? 21 : 185;
			while (pos<uhd_get_frame_position()) {
				if (Is_uhd_disconnection()) {
					break;
				}
			}
			// Disable SOF
			uhd_disable_sof();

			// Check that the hardware state machine has left the IDLE mode
			// before freeze USB clock
			while (3==otg_get_fsm_drd_state()) {
				if (Is_uhd_sof_enabled()) {
					uhd_disable_sof();
				}
			}

			// Ack previous wakeup and resumes interrupts
			USBC->USBC_UHINTCLR = USBC_UHINTCLR_HWUPIC
					| USBC_UHINTCLR_RSMEDIC
					| USBC_UHINTCLR_RXRSMIC;

			// Enable wakeup/resumes interrupts
			USBC->USBC_UHINTESET = USBC_UHINTESET_HWUPIES
					| USBC_UHINTESET_RSMEDIES
					| USBC_UHINTESET_RXRSMIES;

			// Freeze USB clock
			otg_freeze_clock();
			uhd_sleep_mode(UHD_STATE_SUSPEND);
		}
		return; // Abort SOF events
	}
	// Manage a delay to exit of suspend
	if (uhd_resume_start) {
		if (--uhd_resume_start == 0) {
			// Restore pipes unfreezed
			for (pipe = 1; pipe < UHD_PEP_NB; pipe++) {
				if ((uhd_pipes_unfreeze >> pipe) & 0x01) {
					uhd_unfreeze_pipe(pipe);
				}
			}
			uhc_notify_resume();
		}
		return; // Abort SOF events
	}
	// Manage the timeout on endpoint control transfer
	if (uhd_ctrl_request_timeout) {
		// Setup request on-going
		if (--uhd_ctrl_request_timeout == 0) {
			dbgp_ctrl(" TO0 ");
			// Stop request
			uhd_freeze_pipe(0);
			uhd_ctrl_request_end(UHD_TRANS_TIMEOUT);
		}
	}
	// Manage the timeouts on endpoint transfer
	uhd_pipe_job_t *ptr_job;
	for (pipe = 1; pipe < USBC_EPT_NBR; pipe++) {
		ptr_job = &uhd_pipe_job[pipe - 1];
		if (ptr_job->busy == true) {
			if (ptr_job->timeout) {
				// Timeout enabled on this job
				if (--ptr_job->timeout == 0) {
					dbgp_ep(" TO%d ", pipe);
					// Abort job
					uhd_ep_abort_pipe(pipe,UHD_TRANS_TIMEOUT);
				}
			}
		}
	}
	// Manage a delayed control endpoint action
	if (uhd_b_zlp_out_delayed) {
		uhd_b_zlp_out_delayed = false;
		uhd_unfreeze_pipe(0);
		uhd_enable_out_ready_interrupt(0);
	}
	// Manage error on pipe
	if (uhd_pipes_error != 0) {
		pipe = ctz(uhd_pipes_error);
		dbg_print("rERRp%d ", pipe);
		// Force error pipe event
		uhd_raise_pipe_error(pipe);
	}

	// Notify the UHC
	uhc_notify_sof(false);

	// Notify the user application
	UHC_SOF_EVENT();
}

/**
 * \internal
 * \brief Manages the events related to control endpoint
 */
static void uhd_ctrl_interrupt(void)
{
	// A setup request is on-going
	Assert(uhd_ctrl_request_timeout != 0);

	// After pipe error, the pipe is frozen by software
	if (Is_uhd_pipe_error(0)) {
		dbgp_ctrl("err ");
		if (!Is_uhd_pipe_frozen(0)) {
			// Stop the NEW transfer
			uhd_freeze_pipe(0);
			uhd_ack_pipe_error(0);
			// Here a OLD transfer can be always on_going
			// A new error pipe, or other pipe events, or SOF events must be waited
			uhd_pipes_error |= 1 << 0;
			return;
		}
	}

	// Disable setup, IN and OUT interrupts of control endpoint
	USBC->USBC_UPCON0CLR = USBC_UPCON0CLR_TXSTPEC
			| USBC_UPCON0CLR_RXINEC
			| USBC_UPCON0CLR_TXOUTEC;
	uhd_pipes_error &= ~(1<<0);

	// Search event on control endpoint
	if (Is_uhd_setup_ready(0)) {
		// SETUP packet sent
		uhd_freeze_pipe(0);
		uhd_ack_setup_ready(0);
		Assert(uhd_ctrl_request_phase == UHD_CTRL_REQ_PHASE_SETUP);
		dbgp_ctrl("stup ");

		// Start DATA phase
		if ((uhd_ctrl_request_first->req.bmRequestType & USB_REQ_DIR_MASK)
				== USB_REQ_DIR_IN ) {
			uhd_ctrl_phase_data_in_start();
		} else {
			if (uhd_ctrl_request_first->req.wLength) {
				uhd_ctrl_phase_data_out();
			} else {
				// No DATA phase
				uhd_ctrl_phase_zlp_in();
			}
		}
		return;
	}
	if (Is_uhd_in_received(0)) {
		// In case of low USB speed and with a high CPU frequency,
		// a ACK from host can be always running on USB line
		// then wait end of ACK on IN pipe.
		while (!Is_uhd_pipe_frozen(0));
		// IN packet received
		uhd_ack_in_received(0);
		dbgp_ctrl("in ");
		switch(uhd_ctrl_request_phase) {
		case UHD_CTRL_REQ_PHASE_DATA_IN:
			uhd_ctrl_phase_data_in();
			break;
		case UHD_CTRL_REQ_PHASE_ZLP_IN:
			uhd_ctrl_request_end(UHD_TRANS_NOERROR);
			break;
		default:
			Assert(false);
			break;
		}
		return;
	}
	if (Is_uhd_out_ready(0)) {
		// OUT packet sent
		uhd_freeze_pipe(0);
		uhd_ack_out_ready(0);
		dbgp_ctrl("out ");
		switch(uhd_ctrl_request_phase) {
		case UHD_CTRL_REQ_PHASE_DATA_OUT:
			uhd_ctrl_phase_data_out();
			break;
		case UHD_CTRL_REQ_PHASE_ZLP_OUT:
			uhd_ctrl_request_end(UHD_TRANS_NOERROR);
			break;
		default:
			Assert(false);
			break;
		}
		return;
	}
	if (Is_uhd_stall(0)) {
		// Stall Handshake received
		uhd_ack_stall(0);
		dbgp_ctrl("st ");
		uhd_ctrl_request_end(UHD_TRANS_STALL);
		return;
	}
	if (Is_uhd_pipe_error(0)) {
		dbgp_ctrl("pe ");
		// Get and ack error
		uhd_ctrl_request_end(uhd_pipe_get_error(0));
		return;
	}
	Assert(false); // Error system
}

/**
 * \internal
 * \brief Sends a USB setup packet to start a control request sequence
 */
static void uhd_ctrl_phase_setup(void)
{
	usb_setup_req_t setup_req;

	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_SETUP;
	memcpy( &setup_req, &uhd_ctrl_request_first->req, sizeof(usb_setup_req_t));
	// Manage LSB/MSB to fit with CPU usage
	setup_req.wValue = cpu_to_le16(setup_req.wValue);
	setup_req.wIndex = cpu_to_le16(setup_req.wIndex);
	setup_req.wLength = cpu_to_le16(setup_req.wLength);
	uhd_ctrl_nb_trans = 0;

  	// Check pipe
#ifdef USB_HOST_HUB_SUPPORT
	if (!Is_uhd_pipe_enabled(0)) {
		uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
		return; // Endpoint not valid
	}
#error TODO check address in list
	// Reconfigure USB address of pipe 0 used for all control endpoints
	uhd_udesc_set_uhaddr(0, uhd_ctrl_request_first->add);
#else
	if (!Is_uhd_pipe_enabled(0) ||
			(uhd_ctrl_request_first->add != uhd_udesc_get_uhaddr(0))) {
		uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
		return; // Endpoint not valid
	}
#endif

	// Fill pipe
	uhd_configure_pipe_token(0, (USBC_UPCFG0_PTOKEN_SETUP >> USBC_UPCFG0_PTOKEN_Pos));
	uhd_ack_setup_ready(0);
	memcpy(uhd_ctrl_buffer, &setup_req, sizeof(setup_req));
	uhd_udesc_set_buf0_ctn(0, sizeof(setup_req));
	uhd_udesc_rst_buf0_size(0);

	// Start transfer
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);

	uhd_ctrl_request_timeout = 5000;
	uhd_enable_setup_ready_interrupt(0);
}

/**
 * \internal
 * \brief Starts the DATA IN phase on control endpoint
 */
static void uhd_ctrl_phase_data_in_start(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_DATA_IN;
	uhd_configure_pipe_token(0, (USBC_UPCFG0_PTOKEN_IN >> USBC_UPCFG0_PTOKEN_Pos));
	uhd_ack_in_received(0);

	uhd_udesc_rst_buf0_ctn(0);
	uhd_udesc_set_buf0_size(0, uhd_get_pipe_size(0));

	// Start transfer
	uhd_in_request_number(0, 1);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
	uhd_enable_in_received_interrupt(0);
}

/**
 * \internal
 * \brief Manages the DATA IN phase on control endpoint
 */
static void uhd_ctrl_phase_data_in(void)
{
	bool b_short_packet;
	uint8_t *ptr_ep_data;
	uint8_t nb_byte_received;

	// Get information to read data
	nb_byte_received = uhd_udesc_get_buf0_ctn(0);

	//! In HUB mode, the control pipe is always configured to 64B
	//! thus the short packet flag must be computed
	b_short_packet = (nb_byte_received != uhd_get_pipe_size(0));

	ptr_ep_data = (uint8_t*)uhd_ctrl_buffer;
uhd_ctrl_receiv_in_read_data:
	// Copy data from pipe to payload buffer
	while (uhd_ctrl_request_first->payload_size && nb_byte_received) {
		*uhd_ctrl_request_first->payload++ = *ptr_ep_data++;
		uhd_ctrl_nb_trans++;
		uhd_ctrl_request_first->payload_size--;
		nb_byte_received--;
	}

	if (!uhd_ctrl_request_first->payload_size && nb_byte_received) {
		// payload buffer is full to store data remaining
		if (uhd_ctrl_request_first->callback_run == NULL
				|| !uhd_ctrl_request_first->callback_run(
				uhd_udesc_get_uhaddr(0),
				&uhd_ctrl_request_first->payload,
				&uhd_ctrl_request_first->payload_size)) {
			// DATA phase aborted by host
			goto uhd_ctrl_phase_data_in_end;
		}
		// The payload buffer has been updated by the callback
		// thus the data load can restart.
		goto uhd_ctrl_receiv_in_read_data;
	}

	// Test short packet
	if ((uhd_ctrl_nb_trans == uhd_ctrl_request_first->req.wLength)
			|| b_short_packet) {
		// End of DATA phase or DATA phase abort from device
uhd_ctrl_phase_data_in_end:
		uhd_ctrl_phase_zlp_out();
		return;
	}

	uhd_udesc_rst_buf0_ctn(0);
	uhd_udesc_set_buf0_size(0, uhd_get_pipe_size(0));

	// Start transfer
	uhd_in_request_number(0, 1);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
	uhd_enable_in_received_interrupt(0);
}

/**
 * \internal
 * \brief Starts the ZLP IN phase on control endpoint
 */
static void uhd_ctrl_phase_zlp_in(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_ZLP_IN;
	uhd_configure_pipe_token(0, (USBC_UPCFG0_PTOKEN_IN >> USBC_UPCFG0_PTOKEN_Pos));
	uhd_ack_in_received(0);

	uhd_udesc_rst_buf0_ctn(0);
	uhd_udesc_set_buf0_size(0, 0);

	// Start transfer
	uhd_in_request_number(0, 1);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
	uhd_enable_in_received_interrupt(0);
}

/**
 * \internal
 * \brief Manages the DATA OUT phase on control endpoint
 */
static void uhd_ctrl_phase_data_out(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_DATA_OUT;
	uint16_t nb_trans;

	if (uhd_ctrl_nb_trans == uhd_ctrl_request_first->req.wLength) {
		// End of DATA phase
		uhd_ctrl_phase_zlp_in();
		return;
	}

	if (!uhd_ctrl_request_first->payload_size) {
		// Buffer empty, then request a new buffer
		if (uhd_ctrl_request_first->callback_run==NULL
				|| !uhd_ctrl_request_first->callback_run(
				uhd_udesc_get_uhaddr(0),
				&uhd_ctrl_request_first->payload,
				&uhd_ctrl_request_first->payload_size)) {
			// DATA phase aborted by host
			uhd_ctrl_phase_zlp_in();
			return;
		}
	}

	nb_trans = uhd_ctrl_request_first->payload_size;
	if (nb_trans > uhd_get_pipe_size(0)) {
		nb_trans = uhd_get_pipe_size(0);
	}
	// Fill pipe
	uhd_configure_pipe_token(0, (USBC_UPCFG0_PTOKEN_OUT >> USBC_UPCFG0_PTOKEN_Pos));
	uhd_ack_out_ready(0);
	uhd_udesc_set_buf0_ctn(0, nb_trans);
	uhd_udesc_rst_buf0_size(0);

	// Link the user buffer directly on USB hardware DMA
	memcpy(uhd_ctrl_buffer, uhd_ctrl_request_first->payload, nb_trans);

	// Update counters
	uhd_ctrl_request_first->payload += nb_trans;
	uhd_ctrl_nb_trans += nb_trans;
	uhd_ctrl_request_first->payload_size -= nb_trans;

	// Start transfer
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
	uhd_enable_out_ready_interrupt(0);

}

/**
 * \internal
 * \brief Starts the ZLP OUT phase on control endpoint
 */
static void uhd_ctrl_phase_zlp_out(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_ZLP_OUT;
	uhd_configure_pipe_token(0, (USBC_UPCFG0_PTOKEN_OUT >> USBC_UPCFG0_PTOKEN_Pos));
	uhd_ack_out_ready(0);
	uhd_udesc_set_buf0_ctn(0, 0);
	uhd_udesc_rst_buf0_size(0);

	// No need to link a user buffer directly on USB hardware DMA
	// Start transfer
	uhd_ack_fifocon(0);

	// Wait next SOF to start ZLP OUT
	uhd_b_zlp_out_delayed = true;
}

/**
 * \internal
 * \brief Call the callback linked to control request
 * and start the next request from the queue.
 */
static void uhd_ctrl_request_end(uhd_trans_status_t status)
{
	irqflags_t flags;
	uhd_callback_setup_end_t callback_end;
	struct uhd_ctrl_request_t *request_to_free;
	bool b_new_request;

	Assert (uhd_ctrl_request_first != NULL);

	dbgp_ctrl("reqE%d", status);
	dbgp_ctrl("\r\n");

	uhd_pipes_error &= ~(1 << 0);
	uhd_ctrl_request_timeout = 0;

	// Remove request from the control request list
	callback_end = uhd_ctrl_request_first->callback_end;
	request_to_free = uhd_ctrl_request_first;
	flags = cpu_irq_save();
	uhd_ctrl_request_first = uhd_ctrl_request_first->next_request;
	b_new_request = (uhd_ctrl_request_first != NULL);
	cpu_irq_restore(flags);
	free(request_to_free);

	// Call callback
	if (callback_end != NULL) {
		callback_end(uhd_udesc_get_uhaddr(0), status, uhd_ctrl_nb_trans);
	}

	// If a setup request is pending and no started by previous callback
	if (b_new_request) {
		uhd_ctrl_phase_setup();
	}
	if (uhd_b_suspend_requested) {
		// A suspend request has been delay after all setup request
		uhd_b_suspend_requested = false;
		uhd_suspend();
	}
}

/**
 * \internal
 * \brief Translates the USBC pipe error to UHD error
 *
 * \param pipe  Pipe number to use
 *
 * \return UHD transfer error
 */
static uhd_trans_status_t uhd_pipe_get_error(uint8_t pipe)
{
	uint32_t error = uhd_udesc_get_error_status(pipe) &
			(USBC_UPERR_UPERR0_DATATGL_MASK |
			USBC_UPERR_UPERR0_DATAPID_MASK  |
			USBC_UPERR_UPERR0_PID_MASK      |
			USBC_UPERR_UPERR0_TIMEOUT_MASK);
	uhd_udesc_ack_error_status(pipe);
	uhd_ack_pipe_error(pipe);
	switch(error) {
	case USBC_UPERR_UPERR0_DATATGL_MASK:
		return UHD_TRANS_DT_MISMATCH;
	case USBC_UPERR_UPERR0_TIMEOUT_MASK:
		return UHD_TRANS_NOTRESPONDING;
	case USBC_UPERR_UPERR0_CRC16_MASK:
		return UHD_TRANS_CRC;
	case USBC_UPERR_UPERR0_DATAPID_MASK:
	case USBC_UPERR_UPERR0_PID_MASK:
	default:
		return UHD_TRANS_PIDFAILURE;
	}
}

/**
 * \internal
 * \brief Returns the pipe number matching a USB endpoint
 *
 * \param add   USB address
 * \param endp  Endpoint number
 *
 * \return Pipe number
 */
static uint8_t uhd_get_pipe(usb_add_t add, usb_ep_t endp)
{
	uint8_t pipe;

	// Search pipe
	for (pipe = 0; pipe < USBC_EPT_NBR; pipe++) {
		if (!Is_uhd_pipe_enabled(pipe)) {
			continue;
		}
		if (add != uhd_udesc_get_uhaddr(pipe)) {
			continue;
		}
		if (endp != uhd_get_pipe_endpoint_address(pipe)) {
			continue;
		}
		break;
	}
	return pipe;
}

/**
 * \internal
 * \brief Computes and starts the next transfer on a pipe
 *
 * \param pipe  Pipe number
 */
static void uhd_pipe_trans_complet(uint8_t pipe)
{
	uhd_pipe_job_t *ptr_job;
	uint16_t pipe_size, nb_trans;
	uint16_t max_trans;
	iram_size_t next_trans;
	irqflags_t flags;
	bool b_is_iso = (uhd_get_pipe_type(pipe) ==
			(USBC_UPCFG0_PTYPE_ISOCHRONOUS >> USBC_UPCFG0_PTYPE_Pos));

	pipe_size = uhd_get_pipe_size(pipe);

	// Get job corresponding at endpoint
	ptr_job = &uhd_pipe_job[pipe - 1];

	if (!ptr_job->busy) {
		return; // No job is running, then ignore it (system error)
	}

	if (uhd_is_pipe_out(pipe)) {
		// Transfer complete on OUT
		nb_trans = uhd_udesc_get_buf0_size(pipe);
		uhd_udesc_rst_buf0_size(pipe);

		if (0 == nb_trans) {
			nb_trans = uhd_udesc_get_buf0_ctn(pipe);
		}
		// Update number of transfered data
		ptr_job->nb_trans += nb_trans;

		// Need to send other data
		if ((ptr_job->nb_trans != ptr_job->buf_size)
				|| ptr_job->b_shortpacket) {
			next_trans = ptr_job->buf_size - ptr_job->nb_trans;
			if (UHD_ENDPOINT_MAX_TRANS < next_trans) {
				// The USB hardware supports a maximum
				// transfer size of UHD_ENDPOINT_MAX_TRANS Bytes
				next_trans = UHD_ENDPOINT_MAX_TRANS -
					(UHD_ENDPOINT_MAX_TRANS % pipe_size);
				uhd_udesc_set_buf0_autozlp(pipe, false);
			} else {
				// Need ZLP, if requested and last packet is not a short packet
				uhd_udesc_set_buf0_autozlp(pipe, ptr_job->b_shortpacket);
				ptr_job->b_shortpacket = false; // No need to request another ZLP
			}

			uhd_udesc_set_buf0_ctn(pipe, next_trans);
			uhd_udesc_rst_buf0_size(pipe);
			// Link the user buffer directly on USB hardware DMA
			uhd_udesc_set_buf0_addr(pipe, &ptr_job->buf[ptr_job->nb_trans]);
			// Start transfer
			uhd_ack_fifocon(pipe);
			uhd_unfreeze_pipe(pipe);
			// Enable interrupt
			flags = cpu_irq_save();
			uhd_enable_out_ready_interrupt(pipe);
			uhd_enable_pipe_interrupt(pipe);
			cpu_irq_restore(flags);
			return;
		}
	} else {
		// Transfer complete on IN
		nb_trans = uhd_udesc_get_buf0_ctn(pipe);
		uhd_udesc_rst_buf0_ctn(pipe);

		// May be required to copy received data from cache buffer to user buffer
		if (ptr_job->buf_internal != NULL) {
			memcpy(&ptr_job->buf[ptr_job->nb_trans],
					ptr_job->buf_internal,
					ptr_job->buf_size % pipe_size);
			free(ptr_job->buf_internal);
			ptr_job->buf_internal = NULL;
		}

		// Update number of transfered data
		ptr_job->nb_trans += nb_trans;
		if (ptr_job->nb_trans > ptr_job->buf_size) {
			ptr_job->nb_trans = ptr_job->buf_size;
		}

		// If all previous requested data have been received and user buffer not full
		// then need to receive other data
		if ((nb_trans == uhd_udesc_get_buf0_size(pipe))
			&& (ptr_job->nb_trans != ptr_job->buf_size)) {
			next_trans = ptr_job->buf_size - ptr_job->nb_trans;
			max_trans = UHD_ENDPOINT_MAX_TRANS;
			// 256 is the maximum of IN requests via UPINRQ
			if ((256L * pipe_size) < UHD_ENDPOINT_MAX_TRANS) {
				max_trans = 256L * pipe_size;
			}
			if (max_trans < next_trans) {
				// The USB hardware support a maximum transfer size
				// of UHD_ENDPOINT_MAX_TRANS Bytes
				next_trans = max_trans;
			}

			// In case of USB low speed and high CPU frequency,
			// be sure to wait end of ACK on IN pipe.
			while (!Is_uhd_pipe_frozen(pipe));

			if (next_trans < pipe_size) {
				uhd_disable_continuous_in_mode(pipe);
				// Use the cache buffer for Bulk or Interrupt size endpoint
				uhd_in_request_number(pipe, 1);
				ptr_job->buf_internal = malloc(pipe_size);
				if (ptr_job->buf_internal == NULL) {
					Assert(ptr_job->buf_internal != NULL);
					goto uhd_pipe_trans_complet_end;
				}
				uhd_udesc_set_buf0_addr(pipe, ptr_job->buf_internal);
				uhd_udesc_set_buf0_size(pipe, pipe_size);
			} else {
				next_trans -= next_trans % pipe_size;
				// Link the user buffer directly on USB hardware DMA
				if (b_is_iso) {
					uhd_enable_continuous_in_mode(pipe);
				} else {
					uhd_in_request_number(pipe, (next_trans+pipe_size-1)/pipe_size);
				}
				uhd_udesc_set_buf0_addr(pipe, &ptr_job->buf[ptr_job->nb_trans]);
				uhd_udesc_set_buf0_size(pipe, next_trans);
			}
			// Start transfer
			uhd_ack_fifocon(pipe);
			uhd_unfreeze_pipe(pipe);
			// Enable interrupt
			flags = cpu_irq_save();
			uhd_enable_in_received_interrupt(pipe);
			uhd_enable_pipe_interrupt(pipe);
			cpu_irq_restore(flags);
			return;
		}
		// Pipe is not freeze automatically in case of incomplete transfer
		if (0 != uhd_get_in_request_number(pipe)) {
			uhd_freeze_pipe(pipe);
		}
	}

uhd_pipe_trans_complet_end:
	// Call callback to signal end of transfer
	uhd_pipe_finish_job(pipe, UHD_TRANS_NOERROR);
	return;
}

/**
 * \internal
 * \brief Manages the following pipe interrupts:
 * - OUT sent
 * - IN received
 * - Stall received
 * - Error during transfer
 *
 * \param pipe  Pipe number
 */
static void uhd_pipe_interrupt(uint8_t pipe)
{
	// After pipe error, the pipe is frozen by software
	if (Is_uhd_pipe_error(pipe)) {
		dbgp_ep("ERR ");
		if (!Is_uhd_pipe_frozen(pipe)) {
			// Stop the NEW transfer
			uhd_freeze_pipe(pipe);
			uhd_ack_pipe_error(pipe);
			// Here a OLD transfer can be always on_going
			// A new error pipe, or other pipe events, or SOF events must be waited
			uhd_pipes_error |= 1 << pipe;
			return;
		}
	}

	// Disable interrupt of endpoint
	uhd_disable_pipe_interrupt(pipe);
	uhd_pipes_error &= ~(1<<pipe);

	if (Is_uhd_in_received(pipe)) {
		// IN packet received
		uhd_ack_in_received(pipe);
		dbgp_ep("IN ");
		uhd_pipe_trans_complet(pipe);
		return;
	}
	if (Is_uhd_out_ready(pipe)) {
		uhd_freeze_pipe(pipe);
		uhd_ack_out_ready(pipe);
		dbgp_ep("OUT ");
		uhd_pipe_trans_complet(pipe);
		return;
	}
	if (Is_uhd_stall(pipe)) {
		uhd_ack_stall(pipe);
		uhd_reset_data_toggle(pipe);
		dbgp_ep("STALL ");
		uhd_ep_abort_pipe(pipe, UHD_TRANS_STALL);
		return;
	}
	if (Is_uhd_pipe_error(pipe)) {
		dbgp_ep("ERRP ");
		// Get and ack error
		uhd_ep_abort_pipe(pipe, uhd_pipe_get_error(pipe));
		return;
	}
	Assert(false); // Error system
}

/**
 * \internal
 * \brief Aborts the on-going transfer on a pipe
 *
 * \param pipe   Pipe number
 * \param status Reason of abort
 */
static void uhd_ep_abort_pipe(uint8_t pipe, uhd_trans_status_t status)
{
	bool old_toggle = uhd_data_toggle(pipe);
	uint32_t config;
	uhd_pipe_job_t *ptr_job = &uhd_pipe_job[pipe - 1];

	// Freeze pipe and update nb_trans
	uhd_freeze_pipe(pipe);
	ptr_job->nb_trans += (uhd_is_pipe_out(pipe)) ?
			uhd_udesc_get_buf0_size(pipe) : uhd_udesc_get_buf0_ctn(pipe);

	// Reset pipe but keep configuration
	config = USBC_ARRAY(USBC_UPCFG0,pipe);
	uhd_disable_pipe(pipe);
	uhd_enable_pipe(pipe);
	USBC_ARRAY(USBC_UPCFG0,pipe) = config;
	// Setup the data toggle
	switch(status) {
	// Restore data toggle
	case UHD_TRANS_TIMEOUT:
		if (old_toggle) {
			uhd_set_data_toggle(pipe);
		}
		break;
	// Reverse data toggle
	}

	// Interrupts has been reseted, then renable it
	uhd_enable_stall_interrupt(pipe);
	uhd_enable_pipe_error_interrupt(pipe);

	uhd_pipe_finish_job(pipe, status);
}

/**
 * \internal
 * \brief Call the callback linked to the end of pipe transfer
 *
 * \param pipe   Pipe number
 * \param status Status of the transfer
 */
static void uhd_pipe_finish_job(uint8_t pipe, uhd_trans_status_t status)
{
	uhd_pipe_job_t *ptr_job;

	// Get job corresponding at endpoint
	ptr_job = &uhd_pipe_job[pipe - 1];
	if (ptr_job->busy == false) {
		return; // No job running
	}
	dbgp_ep("jobE%d ", pipe);
	// Clear pipe error
	uhd_pipes_error &= ~(1 << pipe);
	// In case of abort, free the internal buffer
	if (ptr_job->buf_internal != NULL) {
		free(ptr_job->buf_internal);
		ptr_job->buf_internal = NULL;
	}
	ptr_job->busy = false;
	if (NULL == ptr_job->call_end) {
		return; // No callback linked to job
	}
	ptr_job->call_end(uhd_udesc_get_uhaddr(pipe),
			uhd_get_pipe_endpoint_address(pipe),
			status, ptr_job->nb_trans);
}

//@}
//@}
