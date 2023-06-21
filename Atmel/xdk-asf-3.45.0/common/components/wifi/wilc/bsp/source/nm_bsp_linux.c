/**
 *
 * \file
 *
 * \brief This module contains Linux WILC BSP APIs implementation.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#include "bsp/include/nm_bsp.h"
#include "common/include/nm_common.h"
#include <linux/kernel.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include "NMI_WFI_NetDevice.h"
#include "linux_wlan_common.h"
#include "nm_bus_wrapper.h"
#include "m2m_wifi.h"
extern linux_wlan_t* g_linux_wlan;

extern void linux_wlan_free(void* vp);
extern void* linux_wlan_malloc(uint32_t sz);

static tpfNmBspIsr gpfIsr;
#define NM_BUS_MAX_TRX_SZ	512U
tstrNmBusCapabilities egstrNmBusCapabilities = 
{
	NM_BUS_MAX_TRX_SZ	
};


extern struct semaphore m2m_wait;
void linux_wlan_unlock(void* vp);


irqreturn_t isr_uh_routine(int irq, void* user_data)
{

	if (gpfIsr) 
	{
		gpfIsr();
	}
	//kthread_run(m2m_wifi_handle_events,(void*)g_linux_wlan,"K_RXQ_BH");
	//schedule_work(&g_linux_wlan->rx_work_queue);
	//printk("*** isr\n");
	linux_wlan_unlock(&m2m_wait);
	return IRQ_HANDLED;

}
void nm_bsp_reset(void)
{
}

static void init_chip_pins(void)
{
}

/*
*	@fn		nm_bsp_init
*	@brief	Initialize BSP
*	@return	0 in case of success and -1 in case of failure
*	@author	M.S.M
*	@date	11 July 2012
*	@version	1.0
*/
sint8 nm_bsp_init(void)
{
	gpfIsr = NULL;

	
	return 0;
}
/*
*	@fn		nm_bsp_sleep
*	@brief	Sleep in units of mSec
*	@param[IN]	u32TimeMsec
*				Time in milliseconds
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_sleep(uint32 u32TimeMsec)
{
	msleep(u32TimeMsec);
}

/*
*	@fn		nm_bsp_register_isr
*	@brief	Register interrupt service routine
*	@param[IN]	pfIsr
*				Pointer to ISR handler
*	@author	M.S.M
*	@date	28 OCT 2013
*	@sa		tpfNmBspIsr
*	@version	1.0
*/
int init_irq(linux_wlan_t* p_nic);
int isr_bh_routine(void *vp);

void nm_bsp_register_isr(tpfNmBspIsr pfIsr)
{
	gpfIsr = pfIsr;
	init_irq(g_linux_wlan);
	kthread_run(isr_bh_routine,NULL,"M2M_RXQ_BH");
	
}
/*
*	@fn		nm_bsp_interrupt_ctrl
*	@brief	Enable/Disable interrupts
*	@param[IN]	u8Enable
*				'0' disable interrupts. '1' enable interrupts
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_interrupt_ctrl(uint8 u8Enable)
{
	static int Localstatus = 1;

	if(Localstatus == u8Enable)
		return;
	Localstatus = u8Enable;

	if (u8Enable) 
	{
		linux_wlan_enable_irq();		
	}
	else 
	{
		linux_wlan_disable_irq(0);		
	}
}

/*
*	@fn		nm_bsp_malloc
*	@brief	Allocate memory
*	@param [in]   u32Size
*               Size of the requested memory 
*	@return       Pointer to the allocated buffer, or NULL otherwise
*/
void* nm_bsp_malloc(uint32 u32Size)
{
	return linux_wlan_malloc(u32Size);
}

/*
*	@fn		nm_bsp_free
*	@brief	Free memory
*	@param [in]   pvMemBuffer
*               Pointer to the buffer to be freed 
*/
void nm_bsp_free(void* pvMemBuffer)
{
	linux_wlan_free(pvMemBuffer);
}

