/**
 * \file
 *
 * \brief USB OTG Driver for UHDP.
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

#ifndef UHDP_OTG_H_INCLUDED
#define UHDP_OTG_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Get USB VBus/ID pin configuration in board configuration */
#include "conf_board.h"
#include "board.h"
#include "ioport.h"
#include "pio.h"
#include "pio_handler.h"

__always_inline static void otg_io_pin_init(uint32_t pin, uint32_t flags,
    IRQn_Type port_irqn, uint8_t irq_level,
    void (*handler)(uint32_t,uint32_t), uint32_t wkup)
{
	// IOPORT must be initialized before by ioport_init(), \see ioport_group.
	pio_handler_set_pin(pin, flags, handler);
	ioport_set_pin_sense_mode(pin, IOPORT_SENSE_BOTHEDGES);
	NVIC_SetPriority(port_irqn, irq_level);
	NVIC_EnableIRQ(port_irqn);
	pio_enable_pin_interrupt(pin);
	if (wkup) {
		pmc_set_fast_startup_input(wkup);
	}
}

//! \ingroup usb_group
//! \defgroup otg_group UHDP OTG Driver
//! UHDP low-level driver for OTG features
//!
//! @{

/**
 * \brief USB interrupt level
 * By default USB interrupt have low priority.
 */
#ifndef USB_INT_LEVEL
# define USB_INT_LEVEL 5
#endif

/**
 * \brief Initialize the dual role
 * This function is implemented in uhdp_host.c file.
 *
 * \return \c true if the ID pin management has been started, otherwise \c false.
 */
bool otg_dual_enable(void);

/**
 * \brief Uninitialize the dual role
 * This function is implemented in uhdp_host.c file.
 */
void otg_dual_disable(void);


//! @name UHDP OTG ID pin management
//! The ID pin come from the USB OTG connector (A and B receptacle) and
//! allows to select the USB mode host or device.
//!
//! The ID pin can be managed through PIO pin.
//! This feature is optional, and it is enabled if USB_ID_PIN
//! is defined in board.h and CONF_BOARD_USB_ID_DETECT defined in
//! conf_board.h.
//! @{
#define OTG_ID_DETECT       (defined(CONF_BOARD_USB_PORT) && \
    defined(CONF_BOARD_USB_ID_DETECT))
#define OTG_ID_IO           (defined(USB_ID_PIN) && OTG_ID_DETECT)

#if OTG_ID_IO
#define otg_id_init(handler)         otg_io_pin_init(USB_ID_PIN, USB_ID_FLAGS, \
			USB_ID_PIN_IRQn, USB_INT_LEVEL, handler, false)
# define otg_id_interrupt_enable()   pio_enable_pin_interrupt(USB_ID_PIN)
# define otg_id_interrupt_disable()  pio_disable_pin_interrupt(USB_ID_PIN)
# define Is_otg_id_device()          ioport_get_pin_level(USB_ID_PIN)
# define Is_otg_id_host()            (!Is_otg_id_device())
#endif

   //! Force device mode
#define otg_force_device_mode()             (Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIMOD), \
			Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIDE))
   //! Test if device mode is forced
#define Is_otg_device_mode_forced()         (Tst_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIMOD))
   //! Force host mode
#define otg_force_host_mode()               (Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIMOD), \
			Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIDE))
   //! Test if host mode is forced
#define Is_otg_host_mode_forced()           (!Tst_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UIMOD))

//! @}


//! @name UHDP OTG VBUS pin management
//! UHDP peripheral does not support VBUS management and it's monitored by a PIO
//! pin.
//! This feature is optional, and it is enabled if USB_VBUS_PIN is defined in
//! board.h and CONF_BOARD_USB_VBUS_DETECT defined in conf_board.h.
//!
//! @note ioport_init() must be invoked before using VBus pin functions since
//!       they use IOPORT API, \see ioport_group.
//!
//! @{
#define OTG_VBUS_DETECT (defined(CONF_BOARD_USB_PORT) && \
    defined(CONF_BOARD_USB_VBUS_DETECT))
#define OTG_VBUS_IO     (defined(USB_VBUS_PIN) && OTG_VBUS_DETECT)
#ifndef USB_VBUS_WKUP
#  define USB_VBUS_WKUP 0
#endif

#define otg_vbus_init(handler)       otg_io_pin_init(USB_VBUS_PIN, USB_VBUS_FLAGS, \
  USB_VBUS_PIN_IRQn, USB_INT_LEVEL, handler, USB_VBUS_WKUP)
#define Is_otg_vbus_high()           ioport_get_pin_level(USB_VBUS_PIN)
#define Is_otg_vbus_low()            (!Is_otg_vbus_high())
#define otg_enable_vbus_interrupt()  pio_enable_pin_interrupt(USB_VBUS_PIN)
#define otg_disable_vbus_interrupt() pio_disable_pin_interrupt(USB_VBUS_PIN)

//! Disables VBUS hardware control (Must be disabled as no VBUS pin controlled by UHDP)
#define uhd_disable_vbus_hw_control()         (Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_VBUSHWC))
//! @}


//! @name UHDP OTG main management
//! These macros allows to enable/disable pad and UHDP hardware
//! @{
  //! Reset USB macro
#define otg_reset()                         \
	do {                                    \
		UOTGHS->UOTGHS_CTRL = UOTGHS_CTRL_FRZCLK; \
		UOTGHS->UOTGHS_SCR = 0xFFFFFFFF;    \
	} while (0)

  //! Enable USB macro
#define otg_enable()                                        \
	do {                                                    \
		Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_OTGPADE); \
    	Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_USBE);    \
	} while (0)
  //! Disable USB macro
#define otg_disable()                                        \
	do {                                                     \
		Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_OTGPADE);  \
		Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_USBE);     \
	} while (0)
#define Is_otg_enabled()                    (Tst_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_USBE))

  //! Stop (freeze) internal USB clock
#define otg_freeze_clock()                  (Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_FRZCLK))
#define otg_unfreeze_clock()                (Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_FRZCLK))
#define Is_otg_clock_frozen()               (Tst_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_FRZCLK))

  //! Configure time-out of specified OTG timer
#define otg_configure_timeout(timer, timeout) (Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UNLOCK),\
		Wr_bitfield(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_TIMPAGE_Msk, timer),\
		Wr_bitfield(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_TIMVALUE_Msk, timeout),\
		Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UNLOCK))
  //! Get configured time-out of specified OTG timer
#define otg_get_timeout(timer)              (Set_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UNLOCK),\
		Wr_bitfield(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_TIMPAGE_Msk, timer),\
		Clr_bits(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_UNLOCK),\
		Rd_bitfield(UOTGHS->UOTGHS_CTRL, UOTGHS_CTRL_TIMVALUE_Msk))


  //! Get the dual-role device state of the internal USB finite state machine of the UHDP controller
#define otg_get_fsm_drd_state()             (Rd_bitfield(UOTGHS->UOTGHS_FSM, UOTGHS_FSM_DRDSTATE_Msk))
#define Is_otg_a_suspend()                  (4==otg_get_fsm_drd_state())
#define Is_otg_a_wait_vrise()               (1==otg_get_fsm_drd_state())
//! @}

//! @}

#ifdef __cplusplus
}
#endif

#endif /* UHDP_OTG_H_INCLUDED */

