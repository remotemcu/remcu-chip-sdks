/**
 * \file
 *
 * \brief USB host driver
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

#include "conf_usb_host.h"
#include "sysclk.h"
#include "uhd.h"
#include "uhdp_otg.h"
#include "uhdp_host.h"
#include <string.h>
#include <stdlib.h>


#if !(SAM4C32)
# error The current UHDP Device Driver supports only SAM4C32E.
#endif

#ifndef UHD_USB_INT_FUN
# define UHD_USB_INT_FUN UOTGHS_Handler
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

// for debug text
//#define dbg_print printf
#define dbg_print(...)

/**
 * \ingroup usb_host_group
 * \defgroup uhd_group USB Host Driver (UHD)
 *
 * \section USB_CONF USB dual role configuration
 * The defines UHD_ENABLE and UDD_ENABLE must be added in project to allow
 * the USB low level (UHD) to manage or not the dual role (device and host).
 *
 * \section uhdp_conf UHDP Custom configuration
 * The following UHDP driver configuration must be defined in conf_usb_host.h
 * file of the application.
 *
 * USB_INT_LEVEL<br>
 * Option to change the interrupt priority (0 to 15) by default 5 (recommended).
 *
 * UHD_USB_INT_FUN<br>
 * Option to fit interrupt function to what defined in exception table.
 *
 * UHD_ISOCHRONOUS_NB_BANK<br>
 * Feature to reduce or increase isochronous endpoints buffering (1 to 2).
 * Default value 2.
 *
 * UHD_BULK_NB_BANK<br>
 * Feature to reduce or increase bulk endpoints buffering (1 to 2).
 * Default value 2.
 *
 * UHD_INTERRUPT_NB_BANK<br>
 * Feature to reduce or increase interrupt endpoints buffering (1 to 2).
 * Default value 1.
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
 * The sleep mode depends on USB driver state (uhd_uhdp_state_enum).
 * @{
 */

// Check USB host configuration
#ifdef USB_HOST_HS_SUPPORT
#  error The High speed mode is not supported on this part, please remove USB_HOST_HS_SUPPORT in conf_usb_host.h
#endif

#ifndef UHD_ISOCHRONOUS_NB_BANK
#  define UHD_ISOCHRONOUS_NB_BANK 2
#else
#  if (UHD_ISOCHRONOUS_NB_BANK < 1) || (UHD_ISOCHRONOUS_NB_BANK > 2)
#    error UHD_ISOCHRONOUS_NB_BANK must be define with 1 or 2.
#  endif
#endif

#ifndef UHD_BULK_NB_BANK
#  define UHD_BULK_NB_BANK        2
#else
#  if (UHD_BULK_NB_BANK < 1) || (UHD_BULK_NB_BANK > 2)
#    error UHD_BULK_NB_BANK must be define with 1 or 2.
#  endif
#endif

#ifndef UHD_INTERRUPT_NB_BANK
#  define UHD_INTERRUPT_NB_BANK   1
#else
#  if (UHD_INTERRUPT_NB_BANK < 1) || (UHD_INTERRUPT_NB_BANK > 2)
#    error UHD_INTERRUPT_NB_BANK must be define with 1 or 2.
#  endif
#endif

#ifndef UHD_BULK_INTERVAL_MIN
/** Minimal bulk interval value */
#  define UHD_BULK_INTERVAL_MIN 1
#endif


/**
 * \name Power management
 */
//@{
#ifndef UHD_NO_SLEEP_MGR

#include "sleepmgr.h"
//! States of UHDP interface
enum uhd_uhdp_state_enum {
	UHD_STATE_OFF = 0,
	UHD_STATE_WAIT_ID_HOST = 1,
	UHD_STATE_NO_VBUS = 2,
	UHD_STATE_DISCONNECT = 3,
	UHD_STATE_SUSPEND = 4,
	UHD_STATE_IDLE = 5,
};

/*! \brief Manages the sleep mode following the UHDP state
 *
 * \param new_state  New UHDP state
 */
static void uhd_sleep_mode(enum uhd_uhdp_state_enum new_state)
{
	enum sleepmgr_mode sleep_mode[] = {
		SLEEPMGR_BACKUP,    // UHD_STATE_OFF (not used)
		SLEEPMGR_WAIT_FAST, // UHD_STATE_WAIT_ID_HOST
		SLEEPMGR_SLEEP_WFI, // UHD_STATE_NO_VBUS
		SLEEPMGR_SLEEP_WFI, // UHD_STATE_DISCONNECT
		SLEEPMGR_WAIT_FAST, // UHD_STATE_SUSPEND
		SLEEPMGR_SLEEP_WFI, // UHD_STATE_IDLE
	};

	static enum uhd_uhdp_state_enum uhd_state = UHD_STATE_OFF;

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

#if OTG_ID_IO
/**
 * USB ID pin change handler
 */
static void otg_id_handler(uint32_t id, uint32_t mask)
{
	if (USB_ID_PIO_ID != id || USB_ID_PIO_MASK != mask) {
		return;
	}

	if (Is_otg_id_device()) {
		uhc_stop(false);
		UHC_MODE_CHANGE(false);
		otg_force_device_mode();
		udc_start();
		dbg_print("\r\nudc_start ");
	} else {
		udc_stop();
		UHC_MODE_CHANGE(true);
		otg_force_host_mode();
		uhc_start();
		dbg_print("\r\nuhc_start ");
	}
}
#endif

#if OTG_VBUS_IO
/**
 * USB VBus pin change handler
 */
static void uhd_vbus_handler(uint32_t id, uint32_t mask)
{
	if (USB_VBUS_PIO_ID != id || USB_VBUS_PIO_MASK != mask) {
		return;
	}

	if (Is_otg_vbus_high()) {
		otg_unfreeze_clock();
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
		otg_freeze_clock();
		uhd_sleep_mode(UHD_STATE_NO_VBUS);
		UHC_VBUS_CHANGE(false);
	}
}
#endif

//! State of UHDP OTG initialization
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
 * \brief Structure to store the high level setup request
 */

struct uhd_ctrl_request_t {
	//! Next setup request to process
	struct uhd_ctrl_request_t *next_request;

	//! Callback called when buffer is empty or full
	uhd_callback_setup_run_t callback_run;
	//! Callback called when request is completed
	uhd_callback_setup_end_t callback_end;

	//! Buffer to store the setup DATA phase
	uint8_t *payload;

	//! USB address of control endpoint
	usb_add_t add;

	//! Setup request definition
	usb_setup_req_t req;

	//! Size of buffer used in DATA phase
	uint16_t payload_size;
};

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
	//! Callback to call at the end of transfer
	uhd_callback_trans_t call_end;

	//! Buffer located in internal RAM to send or fill during job
	uint8_t *buf;
	//! Size of buffer to send or fill
	iram_size_t buf_size;
	//! Total number of transfered data on endpoint
	iram_size_t nb_trans;

	//! timeout on this request (ms)
	uint16_t timeout;
	//! A job is registered on this pipe
	uint16_t busy:1;
	//! A short packet is requested for this job on endpoint IN
	uint16_t b_shortpacket:1;
	//! Periodic packet start for this job
	uint16_t b_periodic_start:1;
} uhd_pipe_job_t;

//! Array to register a job on bulk/interrupt/isochronous endpoint
static uhd_pipe_job_t uhd_pipe_job[UHDP_EPT_NUM - 1];

//! Variables to manage the suspend/resume sequence
static uint8_t uhd_suspend_start;
static uint8_t uhd_resume_start;
static uint16_t uhd_pipes_unfreeze;

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
static void uhd_pipe_interrupt_dma(uint8_t pipe);
static void uhd_pipe_interrupt(uint8_t pipe);
static void uhd_ep_abort_pipe(uint8_t pipe, uhd_trans_status_t status);
static void uhd_pipe_finish_job(uint8_t pipe, uhd_trans_status_t status);


//--------------------------------------------------------
//--- INTERNAL ROUTINES TO MANAGED GLOBAL EVENTS

/**
 * \internal
 * \brief Function called by UHDP interrupt handler to manage USB interrupts
 *
 * It manages the interrupt redirection between host or device interrupt.
 * It answers to OTG events (ID pin change).
 *
 * Note:
 * Here, the global interrupt mask is not cleared when an USB interrupt
 * is enabled because this one can not occurred during the USB ISR
 * (=during INTX is masked).
 */
ISR(UHD_USB_INT_FUN)
{
#ifndef UHD_NO_SLEEP_MGR
	/*
	 * For fast wakeup clocks restore
	 * In WAIT mode, clocks are switched to FASTRC.
	 * After wakeup clocks should be restored, before that ISR should not
	 * be served.
	 */
	if (!pmc_is_wakeup_clocks_restored() && !Is_otg_a_suspend()) {
		cpu_irq_disable();
		return;
	}
#endif
	// Redirection to host or device interrupt
	if (Is_otg_device_mode_forced()) {
		udd_interrupt();
	} else {
		uhd_interrupt();
	}
}

bool otg_dual_enable(void)
{
	if (otg_initialized) {
		return false; // Dual role already initialized
	}
	otg_initialized = true;

	// Enable USB hardware clock
	sysclk_enable_usb();
	pmc_enable_periph_clk(ID_UOTGHS);

	// Reset USB hardware
	otg_reset();

	// Always authorize asynchronous USB interrupts to exit of sleep mode
	// For SAM3 USB wake up device except BACKUP mode
	NVIC_SetPriority((IRQn_Type) ID_UOTGHS, USB_INT_LEVEL);
	NVIC_EnableIRQ((IRQn_Type) ID_UOTGHS);
	pmc_set_fast_startup_input(PMC_FSMR_USBAL);

#if OTG_ID_IO
	otg_id_init(otg_id_handler);
	if (Is_otg_id_device()) {
		otg_force_device_mode();
		uhd_sleep_mode(UHD_STATE_WAIT_ID_HOST);
		UHC_MODE_CHANGE(false);
		udc_start();
	} else {
		otg_force_host_mode();
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
	pmc_clr_fast_startup_input(PMC_FSMR_USBAL);

	otg_unfreeze_clock();
# if OTG_ID_IO
	otg_id_interrupt_disable();
# endif
	otg_freeze_clock();
	otg_disable();
	sysclk_disable_usb();
	pmc_disable_periph_clk(ID_UOTGHS);
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

#if OTG_ID_IO
	// Check that the host mode is selected by ID pin
	if (Is_otg_id_device()) {
		cpu_irq_restore(flags);
		return; // Host is not the current mode
	}
#else
	// ID pin not used then force host mode
	otg_force_host_mode();
#endif

	otg_enable();

	uhd_ctrl_request_first = NULL;
	uhd_ctrl_request_last = NULL;
	uhd_ctrl_request_timeout = 0;
	uhd_suspend_start = 0;
	uhd_resume_start = 0;
	uhd_b_suspend_requested = false;

	otg_unfreeze_clock();

	// Disable VBUS hardware control
	uhd_disable_vbus_hw_control();

	// Clear all interrupts that may have been set by a previous host mode
	UOTGHS->UOTGHS_HSTICR = UOTGHS_HSTICR_DCONNIC | UOTGHS_HSTICR_DDISCIC
			| UOTGHS_HSTICR_HSOFIC  | UOTGHS_HSTICR_HWUPIC
			| UOTGHS_HSTICR_RSMEDIC | UOTGHS_HSTICR_RSTIC
			| UOTGHS_HSTICR_RXRSMIC;

	/* Enable VBus monitoring */
# if OTG_VBUS_IO
	otg_vbus_init(uhd_vbus_handler);
	/* Force VBus interrupt when VBus is always high
	 * This is possible due to a short timing between a Host mode stop/start.
	 */
	if (Is_otg_vbus_high()) {
		uhd_vbus_handler(USB_VBUS_PIO_ID, USB_VBUS_PIO_MASK);
		otg_unfreeze_clock();
	}
# else
	/* No VBus detect, assume always high */

	/* Freeze USB clock to use wakeup interrupt to detect connection.
	 *
	 * After detection of wakeup interrupt, the clock is unfreeze to have
	 * the true connection interrupt.
	 */
	uhd_enable_wakeup_interrupt();
	uhd_sleep_mode(UHD_STATE_DISCONNECT);
	UHC_VBUS_CHANGE(true); /* Changed to HIGH */
# endif

	/* Enable VBus */
	pad_vbus_enable();

	// Enable main control interrupt
	// Connection, SOF and reset
	UOTGHS->UOTGHS_HSTIER = UOTGHS_HSTICR_DCONNIC | UOTGHS_HSTICR_HSOFIC
				| UOTGHS_HSTICR_RSTIC;

	cpu_irq_restore(flags);
}


void uhd_disable(bool b_id_stop)
{
	irqflags_t flags;

	otg_unfreeze_clock();

	// Disable VBus change and error interrupts
	Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_VBUSTE | UOTGHS_CTRL_VBERRE);

	// Disable main control interrupt
	// (Connection, disconnection, SOF and reset)
	UOTGHS->UOTGHS_HSTIDR = UOTGHS_HSTIDR_DCONNIEC | UOTGHS_HSTIDR_DDISCIEC
			| UOTGHS_HSTIDR_RSTIEC   | UOTGHS_HSTIDR_RSMEDIEC
			| UOTGHS_HSTIDR_RXRSMIEC | UOTGHS_HSTIDR_HSOFIEC
			| UOTGHS_HSTIDR_HWUPIEC;

	uhd_disable_sof();
	pad_vbus_disable();
	uhc_notify_connection(false);
	otg_freeze_clock();

#if OTG_ID_IO
	if (!b_id_stop) {
		// Freeze clock to switch mode
		otg_freeze_clock();
		otg_disable();
		otg_initialized = false; // Need re-initialize
		uhd_sleep_mode(UHD_STATE_WAIT_ID_HOST);
		return; // No need to disable host, it is done automatically by hardware
	}
#endif

	flags = cpu_irq_save();
	otg_dual_disable();
	cpu_irq_restore(flags);
}

uhd_speed_t uhd_get_speed(void)
{
	switch (uhd_get_speed_mode()) {

	case UOTGHS_SR_SPEED_FULL_SPEED:
		return UHD_SPEED_FULL;

	case UOTGHS_SR_SPEED_LOW_SPEED:
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
	return 0; // Not supported
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
	for (uint8_t pipe = 1; pipe < UHDP_EPT_NUM; pipe++) {
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
	otg_unfreeze_clock();
	uhd_enable_sof();
	uhd_send_resume();
	uhd_sleep_mode(UHD_STATE_IDLE);
}

bool uhd_ep0_alloc(usb_add_t add, uint8_t ep_size)
{
	if (ep_size < 8) {
		return false;
	}

	uhd_enable_pipe(0);
	uhd_configure_pipe(0, // Pipe 0
			0, // No frequency
			0, // endpoint 0
			UOTGHS_HSTPIPCFG_PTYPE_CTRL,
			UOTGHS_HSTPIPCFG_PTOKEN_SETUP,
			ep_size,
			UOTGHS_HSTPIPCFG_PBK_1_BANK, 0);

	uhd_allocate_memory(0);
	if (!Is_uhd_pipe_configured(0)) {
		uhd_disable_pipe(0);
		return false;
	}
	uhd_configure_address(0, add);

	// Always enable stall and error interrupts of control endpoint
	uhd_enable_stall_interrupt(0);
	uhd_enable_pipe_error_interrupt(0);
	uhd_enable_pipe_interrupt(0);
	return true;
}

bool uhd_ep_alloc(usb_add_t add, usb_ep_desc_t * ep_desc, uhd_speed_t speed)
{
	uint8_t ep_addr;
	uint8_t ep_type;
	uint8_t ep_dir;
	uint8_t ep_interval;
	uint8_t bank;
	(void)speed; // No high speed

	for (uint8_t pipe = 1; pipe < UHDP_EPT_NUM; pipe++) {
		if (Is_uhd_pipe_enabled(pipe)) {
			continue;
		}
		uhd_enable_pipe(pipe);
		ep_addr = ep_desc->bEndpointAddress & USB_EP_ADDR_MASK;
		ep_dir = (ep_desc->bEndpointAddress & USB_EP_DIR_IN)?
			(UOTGHS_HSTPIPCFG_PTOKEN_IN >> UOTGHS_HSTPIPCFG_PTOKEN_Pos):
			(UOTGHS_HSTPIPCFG_PTOKEN_OUT >> UOTGHS_HSTPIPCFG_PTOKEN_Pos),
		ep_type = ep_desc->bmAttributes&USB_EP_TYPE_MASK;
		// Bank choice
		switch(ep_type) {
		case USB_EP_TYPE_ISOCHRONOUS:
			bank = UHD_ISOCHRONOUS_NB_BANK;
			ep_interval = ep_desc->bInterval;
			break;
		case USB_EP_TYPE_INTERRUPT:
			bank = UHD_INTERRUPT_NB_BANK;
			ep_interval = ep_desc->bInterval;
			break;
		case USB_EP_TYPE_BULK:
			bank = UHD_BULK_NB_BANK;
			ep_interval = 0; // Value has no effect for a non-interrupt EP
			break;
		default:
			Assert(false);
			return false;
		}
		switch(bank) {
		case 1:
			bank = UOTGHS_HSTPIPCFG_PBK_1_BANK;
			break;
		case 2:
			bank = UOTGHS_HSTPIPCFG_PBK_2_BANK;
			break;
		case 3:
			bank = UOTGHS_HSTPIPCFG_PBK_3_BANK;
			break;
		default:
			Assert(false);
			return false;
		}

		uhd_configure_pipe(pipe, ep_interval, ep_addr, ep_type, ep_dir,
				le16_to_cpu(ep_desc->wMaxPacketSize),
				bank, UOTGHS_HSTPIPCFG_AUTOSW);

		uhd_allocate_memory(pipe);
		if (!Is_uhd_pipe_configured(pipe)) {
			uhd_disable_pipe(pipe);
			return false;
		}
		uhd_configure_address(pipe, add);
		uhd_enable_pipe(pipe);

		// Enable endpoint interrupts
		uhd_enable_pipe_dma_interrupt(pipe);
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
	for (uint8_t pipe = 0; pipe < UHDP_EPT_NUM; pipe++) {
		if (!Is_uhd_pipe_enabled(pipe)) {
			continue;
		}
		if (add != uhd_get_configured_address(pipe)) {
			continue;
		}
		if (endp != 0xFF) {
			// Disable specific endpoint number
			if (endp != uhd_get_pipe_endpoint_address(pipe)) {
				continue; // Mismatch
			}
		}

		// Stop transfer on this pipe
		if (pipe == 0) {
			// Endpoint control
			if (uhd_ctrl_request_timeout) {
				uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
			}
			continue;
		}

		// Endpoint interrupt, bulk or isochronous
		uhd_ep_abort_pipe(pipe, UHD_TRANS_DISCONNECT);
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

bool uhd_ep_run(usb_add_t add,
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

	pipe = uhd_get_pipe(add,endp);
	if (pipe == UHDP_EPT_NUM) {
		return false; // pipe not found
	}

	// Get job about pipe
	ptr_job = &uhd_pipe_job[pipe-1];
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
	if ((Is_uhd_pipe_int(pipe) || Is_uhd_pipe_iso(pipe))
			&& (Is_uhd_pipe_out(pipe))) {
		ptr_job->b_periodic_start = true;
	}
	cpu_irq_restore(flags);

#if UHD_BULK_INTERVAL_MIN
	// Enable NAK for bandwidth control
	if (Is_uhd_pipe_bulk(pipe)) {
		uhd_ack_nak_received(pipe);
		uhd_enable_nak_received_interrupt(pipe);
	}
#endif
	// Request first transfer
	uhd_pipe_trans_complet(pipe);
	return true;
}

void uhd_ep_abort(usb_add_t add, usb_ep_t endp)
{
	uint8_t pipe;

	pipe = uhd_get_pipe(add,endp);
	if (pipe == UHDP_EPT_NUM) {
		return; // pipe not found
	}
	uhd_ep_abort_pipe(pipe,UHD_TRANS_ABORTED);
}

/**
 * \internal
 * \brief Function called by UHDP interrupt to manage USB host interrupts
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
		uhd_sof_interrupt();
		goto uhd_interrupt_exit_sof;
	}

	// Manage pipe interrupts
	pipe_int = uhd_get_interrupt_pipe_number();
	if (pipe_int == 0) {
		dbg_print("0: ");
		// Interrupt acked by control endpoint managed
		uhd_ctrl_interrupt();
		goto uhd_interrupt_exit;
	}
	if (pipe_int != UHDP_EPT_NUM) {
		dbg_print("p%d: ", (int)pipe_int);
		// Interrupt acked by bulk/interrupt/isochronous endpoint
		uhd_pipe_interrupt(pipe_int);
		goto uhd_interrupt_exit;
	}
	pipe_int = uhd_get_pipe_dma_interrupt_number();
	if (pipe_int != UHDP_EPT_NUM) {
		dbg_print("dma%d: ", (int)pipe_int);
		// Interrupt DMA acked by bulk/interrupt/isochronous endpoint
		uhd_pipe_interrupt_dma(pipe_int);
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

	// Manage dis/connection event
	if (Is_uhd_disconnection() && Is_uhd_disconnection_int_enabled()) {
		uhd_ack_disconnection();
		uhd_disable_disconnection_int();
		dbg_print("DISC ");
		// Stop reset signal, in case of disconnection during reset
		uhd_stop_reset();
		// Disable wakeup/resumes interrupts,
		// in case of disconnection during suspend mode
		UOTGHS->UOTGHS_HSTIDR = UOTGHS_HSTIDR_HWUPIEC
				| UOTGHS_HSTIDR_RSMEDIEC
				| UOTGHS_HSTIDR_RXRSMIEC;
		uhd_sleep_mode(UHD_STATE_DISCONNECT);
		uhd_ack_connection();
		uhd_enable_connection_int();
		uhd_suspend_start = 0;
		uhd_resume_start = 0;
		uhc_notify_connection(false);
		goto uhd_interrupt_exit;
	}
	if (Is_uhd_connection() && Is_uhd_connection_int_enabled()) {
		uhd_ack_connection();
		uhd_disable_connection_int();
		uhd_ack_disconnection();
		dbg_print("CONN ");
		uhd_enable_disconnection_int();
		uhd_enable_sof();
		uhd_sleep_mode(UHD_STATE_IDLE);
		uhd_suspend_start = 0;
		uhd_resume_start = 0;
		uhc_notify_connection(true);
		goto uhd_interrupt_exit;
	}

	// Enable USB clock after asynchronous interrupt
	otg_unfreeze_clock();


	if (Is_uhd_wakeup_interrupt_enabled() && (Is_uhd_wakeup() ||
			Is_uhd_downstream_resume() || Is_uhd_upstream_resume())) {
		dbg_print("WKUP ");
		//uhd_ack_wakeup();
		// Disable wakeup/resumes interrupts
		UOTGHS->UOTGHS_HSTIDR = UOTGHS_HSTIDR_HWUPIEC
				| UOTGHS_HSTIDR_RSMEDIEC
				| UOTGHS_HSTIDR_RXRSMIEC;
		uhd_enable_sof();

		// Wait 50 ms before restarting transfer
		uhd_resume_start = 50;
		uhd_sleep_mode(UHD_STATE_IDLE);
		goto uhd_interrupt_exit;
	}

	// Other errors
	if (Is_uhd_errors_interrupt_enabled() && Is_uhd_errors_interrupt()) {
		uhd_ack_errors_interrupt();
		dbg_print("OtherErr ");
		goto uhd_interrupt_exit;
	}

	dbg_print("Interrupt event not managed! ");
	Assert(false);

uhd_interrupt_exit:
	dbg_print("\n\r");
uhd_interrupt_exit_sof:
	return;
}

static void uhd_delayed_suspend(void)
{
	if (--uhd_suspend_start == 0) {
		// In case of high CPU frequency,
		// the current Keep-Alive/SOF can be always on-going
		// then wait end of SOF generation
		// to be sure that disable SOF has been accepted
		uint8_t pos = 114;

		while (pos < uhd_get_frame_position()) {
			if (Is_uhd_disconnection()) {
				break;
			}
		}
		uhd_disable_sof();

		// When SOF is disabled, the current transmitted packet may
		// cause a resume.
		// Wait for a while to check this resume status and clear it.
		for (pos = 0; pos < 15; pos ++) {
			barrier();
			if (UOTGHS->UOTGHS_HSTISR & (UOTGHS_HSTICR_HWUPIC
					| UOTGHS_HSTICR_RSMEDIC
					| UOTGHS_HSTICR_RXRSMIC)) {
				break;
			}
		}

		// Ack previous wakeup and resumes interrupts
		UOTGHS->UOTGHS_HSTICR = UOTGHS_HSTICR_HWUPIC
				|UOTGHS_HSTICR_RSMEDIC
				|UOTGHS_HSTICR_RXRSMIC;
		// Enable wakeup/resumes interrupts
		UOTGHS->UOTGHS_HSTIER = UOTGHS_HSTIER_HWUPIES
				|UOTGHS_HSTIER_RSMEDIES
				|UOTGHS_HSTIER_RXRSMIES;

		otg_freeze_clock();
		uhd_sleep_mode(UHD_STATE_SUSPEND);
	}
}
static void uhd_delayed_resume(void)
{
	if (--uhd_resume_start == 0) {
		// Restore pipes unfreezed
		for (uint8_t pipe = 1; pipe < UHDP_EPT_NUM; pipe++) {
			if ((uhd_pipes_unfreeze >> pipe) & 0x01) {
				uhd_unfreeze_pipe(pipe);
			}
		}
		uhc_notify_resume();
	}
}
static void uhd_ctrl_timeout(void)
{
	if (uhd_ctrl_request_timeout) {
		// Setup request on-going
		if (--uhd_ctrl_request_timeout == 0) {
			// Stop request
			uhd_freeze_pipe(0);
			uhd_ctrl_request_end(UHD_TRANS_TIMEOUT);
		}
	}
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
	uhd_pipe_job_t *ptr_job;
	uint8_t pipe;

	uhd_ack_sof();

#if UHD_BULK_INTERVAL_MIN
	// Start any busy frozen Bulk
	for (pipe = 1; pipe < UHDP_EPT_NUM; pipe ++) {
		ptr_job = &uhd_pipe_job[pipe-1];
		if (!ptr_job->busy) {
			continue;
		}
		if (!Is_uhd_pipe_bulk(pipe)) {
			continue;
		}
		if (!Is_uhd_pipe_frozen(pipe)) {
			continue;
		}
		uhd_unfreeze_pipe(pipe);
	}
#endif

	// Manage a delay to enter in suspend
	if (uhd_suspend_start) {
		uhd_delayed_suspend();
		return; // Abort SOF events
	}
	// Manage a delay to exit of suspend
	if (uhd_resume_start) {
		uhd_delayed_resume();
		return; // Abort SOF events
	}
	// Manage the timeout on endpoint control transfer
	uhd_ctrl_timeout();

	// Manage the timeouts on endpoint transfer
	for (pipe = 1; pipe < UHDP_EPT_NUM; pipe++) {
		ptr_job = &uhd_pipe_job[pipe-1];
		if (ptr_job->busy == true) {
			if (ptr_job->timeout) {
				// Timeout enabled on this job
				if (--ptr_job->timeout == 0) {
					// Abort job
					uhd_ep_abort_pipe(pipe,UHD_TRANS_TIMEOUT);
				}
			}
			if (ptr_job->b_periodic_start) {
				ptr_job->b_periodic_start = false;
				uhd_unfreeze_pipe(pipe);
			}
		}
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
	Assert(uhd_ctrl_request_timeout!=0);

	// Disable setup, IN and OUT interrupts of control endpoint
	UOTGHS->UOTGHS_HSTPIPIDR[0] = UOTGHS_HSTPIPIDR_TXSTPEC
			| UOTGHS_HSTPIPIDR_RXINEC
			| UOTGHS_HSTPIPIDR_TXOUTEC;

	// Search event on control endpoint
	if (Is_uhd_setup_ready(0)) {
		// SETUP packet sent
		uhd_freeze_pipe(0);
		uhd_ack_setup_ready(0);
		Assert(uhd_ctrl_request_phase == UHD_CTRL_REQ_PHASE_SETUP);

		// Start DATA phase
		if ((uhd_ctrl_request_first->req.bmRequestType & USB_REQ_DIR_MASK)
				== USB_REQ_DIR_IN) {
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
		uhd_ctrl_request_end(UHD_TRANS_STALL);
		return;
	}
	if (Is_uhd_pipe_error(0)) {
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
	union{
		volatile uint64_t value64;
		usb_setup_req_t req;
	} setup;
	volatile uint64_t *ptr_ep_data;

	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_SETUP;
	memcpy(&setup.req, &uhd_ctrl_request_first->req, sizeof(usb_setup_req_t));

	// Manage LSB/MSB to fit with CPU usage
	setup.req.wValue = cpu_to_le16(setup.req.wValue);
	setup.req.wIndex = cpu_to_le16(setup.req.wIndex);
	setup.req.wLength = cpu_to_le16(setup.req.wLength);
	uhd_ctrl_nb_trans = 0;

	// Check pipe
	if (!Is_uhd_pipe_enabled(0) ||
			(uhd_ctrl_request_first->add != uhd_get_configured_address(0))) {
		uhd_ctrl_request_end(UHD_TRANS_DISCONNECT);
		return; // Endpoint not valid
	}

	// Fill pipe
	uhd_configure_pipe_token(0, UOTGHS_HSTPIPCFG_PTOKEN_SETUP);
	uhd_ack_setup_ready(0);
	Assert(sizeof(setup) == sizeof(uint64_t));

	ptr_ep_data = (volatile uint64_t *)&uhd_get_pipe_fifo_access(0, 64);
	*ptr_ep_data = setup.value64;

	uhd_ctrl_request_timeout = 5000;
	uhd_enable_setup_ready_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
}

/**
 * \internal
 * \brief Starts the DATA IN phase on control endpoint
 */
static void uhd_ctrl_phase_data_in_start(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_DATA_IN;
	uhd_configure_pipe_token(0, UOTGHS_HSTPIPCFG_PTOKEN_IN);
	uhd_ack_in_received(0);
	uhd_ack_short_packet(0);
	uhd_enable_in_received_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
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
	nb_byte_received = uhd_byte_count(0);
	b_short_packet = Is_uhd_short_packet(0);

	ptr_ep_data = (uint8_t *) & uhd_get_pipe_fifo_access(0, 8);
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
				uhd_get_configured_address(0),
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

	// Send a new IN packet request
	uhd_enable_in_received_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
}

/**
 * \internal
 * \brief Starts the ZLP IN phase on control endpoint
 */
static void uhd_ctrl_phase_zlp_in(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_ZLP_IN;
	uhd_configure_pipe_token(0, UOTGHS_HSTPIPCFG_PTOKEN_IN);
	uhd_ack_in_received(0);
	uhd_ack_short_packet(0);
	uhd_enable_in_received_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
}

/**
 * \internal
 * \brief Manages the DATA OUT phase on control endpoint
 */
static void uhd_ctrl_phase_data_out(void)
{
	uint8_t *ptr_ep_data;
	uint8_t ep_ctrl_size;

	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_DATA_OUT;

	if (uhd_ctrl_nb_trans == uhd_ctrl_request_first->req.wLength) {
		// End of DATA phase
		uhd_ctrl_phase_zlp_in();
		return;
	}

	if (!uhd_ctrl_request_first->payload_size) {
		// Buffer empty, then request a new buffer
		if (uhd_ctrl_request_first->callback_run==NULL
				|| !uhd_ctrl_request_first->callback_run(
				uhd_get_configured_address(0),
				&uhd_ctrl_request_first->payload,
				&uhd_ctrl_request_first->payload_size)) {
			// DATA phase aborted by host
			uhd_ctrl_phase_zlp_in();
			return;
		}
	}

	ep_ctrl_size = uhd_get_pipe_size(0);

	// Fill pipe
	uhd_configure_pipe_token(0, UOTGHS_HSTPIPCFG_PTOKEN_OUT);
	uhd_ack_out_ready(0);
	ptr_ep_data = (uint8_t *) & uhd_get_pipe_fifo_access(0, 8);
	while ((uhd_ctrl_nb_trans < uhd_ctrl_request_first->req.wLength)
			&& ep_ctrl_size && uhd_ctrl_request_first->payload_size) {
		*ptr_ep_data++ = *uhd_ctrl_request_first->payload++;
		uhd_ctrl_nb_trans++;
		ep_ctrl_size--;
		uhd_ctrl_request_first->payload_size--;
	}
	uhd_enable_out_ready_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
}

/**
 * \internal
 * \brief Starts the ZLP OUT phase on control endpoint
 */
static void uhd_ctrl_phase_zlp_out(void)
{
	uhd_ctrl_request_phase = UHD_CTRL_REQ_PHASE_ZLP_OUT;
	uhd_configure_pipe_token(0, UOTGHS_HSTPIPCFG_PTOKEN_OUT);
	uhd_ack_out_ready(0);
	uhd_enable_out_ready_interrupt(0);
	uhd_ack_fifocon(0);
	uhd_unfreeze_pipe(0);
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
		callback_end(uhd_get_configured_address(0), status, uhd_ctrl_nb_trans);
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
 * \brief Translates the UHDP pipe error to UHD error
 *
 * \param pipe  Pipe number to use
 *
 * \return UHD transfer error
 */
static uhd_trans_status_t uhd_pipe_get_error(uint8_t pipe)
{
	uint32_t error = uhd_error_status(pipe) &
			(UOTGHS_HSTPIPERR_DATATGL |
			UOTGHS_HSTPIPERR_TIMEOUT |
			UOTGHS_HSTPIPERR_PID |
			UOTGHS_HSTPIPERR_DATAPID);
	uhd_ack_all_errors(pipe);
	switch(error) {
	case UOTGHS_HSTPIPERR_DATATGL:
		return UHD_TRANS_DT_MISMATCH;
	case UOTGHS_HSTPIPERR_TIMEOUT:
		return UHD_TRANS_NOTRESPONDING;
	case UOTGHS_HSTPIPERR_DATAPID:
	case UOTGHS_HSTPIPERR_PID:
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
	for (pipe = 0; pipe < UHDP_EPT_NUM; pipe++) {

		if (!Is_uhd_pipe_enabled(pipe)) {
			continue;
		}
		if (add != uhd_get_configured_address(pipe)) {
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
	uint32_t uhd_dma_ctrl = 0;
	uhd_pipe_job_t *ptr_job;
	iram_size_t max_trans;
	iram_size_t next_trans;
	irqflags_t flags;

	// Get job corresponding at endpoint
	ptr_job = &uhd_pipe_job[pipe - 1];

	if (!ptr_job->busy) {
		return; // No job is running, then ignore it (system error)
	}

	if (ptr_job->nb_trans != ptr_job->buf_size) {
		// Need to send or receive other data
		next_trans = ptr_job->buf_size - ptr_job->nb_trans;
		max_trans = UHD_PIPE_MAX_TRANS;
		if (Is_uhd_pipe_in(pipe)) {
			// 256 is the maximum of IN requests via UPINRQ
			if ((256L*uhd_get_pipe_size(pipe))<UHD_PIPE_MAX_TRANS) {
				max_trans = 256L * uhd_get_pipe_size(pipe);
			}
		}
		if (max_trans < next_trans) {
			// The USB hardware supports a maximum
			// transfer size of UHD_PIPE_MAX_TRANS Bytes
			next_trans = max_trans;
		}

		if (next_trans == UHD_PIPE_MAX_TRANS) {
			// Set 0 to transfer the maximum
			uhd_dma_ctrl = UOTGHS_HSTDMACONTROL_BUFF_LENGTH(0);
		} else {
			uhd_dma_ctrl = UOTGHS_HSTDMACONTROL_BUFF_LENGTH(next_trans);
		}

		if (uhd_is_pipe_out(pipe)) {
			if (0 != (next_trans % uhd_get_pipe_size(pipe))) {
				// Enable short packet option
				// else the DMA transfer is accepted
				// and interrupt DMA valid but nothing is sent.
				uhd_dma_ctrl |= UOTGHS_HSTDMACONTROL_END_B_EN;
				// No need to request another ZLP
				ptr_job->b_shortpacket = false;
			}
		} else {
			if ((USB_EP_TYPE_ISOCHRONOUS != uhd_get_pipe_type(pipe))
					|| ((int)next_trans <= uhd_get_pipe_size(pipe))) {
				// Enable short packet reception
				uhd_dma_ctrl |= UOTGHS_HSTDMACONTROL_END_TR_IT
						| UOTGHS_HSTDMACONTROL_END_TR_EN;
			}
		}

		// Start USB DMA to fill or read fifo of the selected endpoint
		uhd_pipe_dma_set_addr(pipe, (U32) &ptr_job->buf[ptr_job->nb_trans]);
		uhd_dma_ctrl |= UOTGHS_HSTDMACONTROL_END_BUFFIT |
				UOTGHS_HSTDMACONTROL_CHANN_ENB;

		// Disable IRQs to have a short sequence
		// between read of EOT_STA and DMA enable
		flags = cpu_irq_save();
		if (!(uhd_pipe_dma_get_status(pipe)
				& UOTGHS_HSTDMASTATUS_END_TR_ST)) {
			if (Is_uhd_pipe_in(pipe)) {
				uint32_t pipe_size = uhd_get_pipe_size(pipe);
				uhd_in_request_number(pipe,
					(next_trans + pipe_size-1) / pipe_size);
			}
			if (!ptr_job->b_periodic_start) {
				uhd_disable_bank_interrupt(pipe);
				uhd_unfreeze_pipe(pipe);
			} else {
				// Last bank not sent, just start
				if (Is_uhd_bank_interrupt_enabled(pipe)) {
					uhd_disable_bank_interrupt(pipe);
					uhd_unfreeze_pipe(pipe);
				} else {
					// Wait SOF to start
				}
			}
			uhd_pipe_dma_set_control(pipe, uhd_dma_ctrl);
			ptr_job->nb_trans += next_trans;
			cpu_irq_restore(flags);
			return;
		}
		cpu_irq_restore(flags);
		// Here a ZLP has been received
		// and the DMA transfer must be not started.
		// It is the end of transfer
		ptr_job->buf_size = ptr_job->nb_trans;
	}
	if (uhd_is_pipe_out(pipe)) {
		if (ptr_job->b_shortpacket) {
			// Need to send a ZLP (No possible with USB DMA)
			// enable interrupt to wait a free bank to sent ZLP
			uhd_ack_out_ready(pipe);
			if (Is_uhd_write_enabled(pipe)) {
				// Force interrupt in case of pipe already free
				uhd_raise_out_ready(pipe);
			}
			uhd_enable_out_ready_interrupt(pipe);
			return;
		}
	}
	uhd_disable_nak_received_interrupt(pipe);

	// Call callback to signal end of transfer
	uhd_pipe_finish_job(pipe, UHD_TRANS_NOERROR);
}

/**
 * \internal
 * \brief Manages the pipe DMA interrupt
 *
 * \param pipe  Pipe number
 */
static void uhd_pipe_interrupt_dma(uint8_t pipe)
{
	uhd_pipe_job_t *ptr_job;
	uint32_t nb_remaining;

	if (uhd_pipe_dma_get_status(pipe)
			& UOTGHS_HSTDMASTATUS_CHANN_ENB) {
		return; // Ignore EOT_STA interrupt
	}
	// Save number of data no transfered
	nb_remaining = (uhd_pipe_dma_get_status(pipe) &
			UOTGHS_HSTDMASTATUS_BUFF_COUNT_Msk)
			>> UOTGHS_HSTDMASTATUS_BUFF_COUNT_Pos;
	if (nb_remaining) {
		// Get job corresponding at endpoint
		ptr_job = &uhd_pipe_job[pipe - 1];

		// Transfer no complete (short packet or ZLP) then:
		// Update number of transfered data
		ptr_job->nb_trans -= nb_remaining;

		// Set transfer complete to stop the transfer
		ptr_job->buf_size = ptr_job->nb_trans;
	}

	if (uhd_is_pipe_out(pipe)) {
		// Wait that all banks are free to freeze clock of OUT endpoint
		// and call callback
		uhd_enable_bank_interrupt(pipe);

		// For ISO out, start another DMA transfer since no ACK needed
		if (Is_uhd_pipe_iso(pipe)) {
			uhd_pipe_finish_job(pipe, UHD_TRANS_NOERROR);
		}
	} else {
		if (!Is_uhd_pipe_frozen(pipe)) {
			// Pipe is not freeze in case of :
			// - incomplete transfer when the request number INRQ is not complete.
			// - low USB speed and with a high CPU frequency,
			// a ACK from host can be always running on USB line.

			if (nb_remaining) {
				// Freeze pipe in case of incomplete transfer
				uhd_freeze_pipe(pipe);
			} else {
				// Wait freeze in case of ASK on going
				while (!Is_uhd_pipe_frozen(pipe)) {
				}
			}
		}

		uhd_pipe_trans_complet(pipe);
	}
}

/**
 * \internal
 * \brief Manages the following pipe interrupts:
 * - Real end of USB transfers (bank empty)
 * - One bank is free to send a OUT ZLP
 * - Stall received
 * - Error during transfer
 *
 * \param pipe  Pipe number
 */
static void uhd_pipe_interrupt(uint8_t pipe)
{
#if UHD_BULK_INTERVAL_MIN
	// for any bulk NAK endpoints, freeze to free bandwidth
	if (Is_uhd_pipe_bulk(pipe)
		&& Is_uhd_nak_received_interrupt_enabled(pipe)
		&& Is_uhd_nak_received(pipe)) {
		// Freeze until next frame start
		uhd_freeze_pipe(pipe);
		uhd_ack_nak_received(pipe);
		return;
	}
#endif

	// for DMA endpoints
	if (Is_uhd_bank_interrupt_enabled(pipe) && (0==uhd_nb_busy_bank(pipe))) {
		uhd_freeze_pipe(pipe);
		uhd_disable_bank_interrupt(pipe);
		// For ISO, no ACK, finished when DMA done
		if (!Is_uhd_pipe_iso(pipe)) {
			uhd_pipe_finish_job(pipe, UHD_TRANS_NOERROR);
		}
		return;
	}
	if (Is_uhd_out_ready_interrupt_enabled(pipe) && Is_uhd_out_ready(pipe)) {
		uhd_disable_out_ready_interrupt(pipe);
		// One bank is free then send a ZLP
		uhd_ack_out_ready(pipe);
		uhd_ack_fifocon(pipe);
		uhd_unfreeze_pipe(pipe);
		uhd_enable_bank_interrupt(pipe);
		return;
	}
	if (Is_uhd_stall(pipe)) {
		uhd_ack_stall(pipe);
		uhd_reset_data_toggle(pipe);
		uhd_ep_abort_pipe(pipe, UHD_TRANS_STALL);
		return;
	}
	if (Is_uhd_pipe_error(pipe)) {
		// Get and ack error
		uhd_ep_abort_pipe(pipe, uhd_pipe_get_error(pipe));
		return;
	}
	Assert(false); // Error system
}

/**
 * \internal
 * \brief Aborts the on going transfer on a pipe
 *
 * \param pipe   Pipe number
 * \param status Reason of abort
 */
static void uhd_ep_abort_pipe(uint8_t pipe, uhd_trans_status_t status)
{
	// Stop transfer
	if (Is_uhd_pipe_dma_supported(pipe)) {
		uhd_pipe_job_t *ptr_job = &uhd_pipe_job[pipe - 1];
		uhd_freeze_pipe(pipe);
		ptr_job->nb_trans =
				uhd_pipe_dma_get_addr(pipe) - (uint32_t)ptr_job->buf;
		uhd_pipe_dma_set_control(pipe, 0);
	}
	uhd_reset_pipe(pipe);

	// Auto switch bank and interrupts has been reseted, then re-enable it
	uhd_enable_pipe_bank_autoswitch(pipe);
	uhd_enable_stall_interrupt(pipe);
	uhd_enable_pipe_error_interrupt(pipe);
	uhd_disable_out_ready_interrupt(pipe);
	uhd_disable_nak_received_interrupt(pipe);

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
	uint32_t dev_addr = uhd_get_configured_address(pipe);
	uint32_t dev_ep = uhd_get_pipe_endpoint_address(pipe);

	if (status == UHD_TRANS_DISCONNECT) {
		// Unalloc pipe
		uhd_disable_pipe(pipe);
		uhd_unallocate_memory(pipe);
	}

	// Get job corresponding at endpoint
	ptr_job = &uhd_pipe_job[pipe - 1];
	if (ptr_job->busy == false) {
		return; // No job running
	}
	ptr_job->busy = false;
	if (NULL == ptr_job->call_end) {
		return; // No callback linked to job
	}
	ptr_job->call_end(dev_addr, dev_ep, status, ptr_job->nb_trans);
}

//@}
