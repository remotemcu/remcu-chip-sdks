/**
 * \file
 *
 * \brief Unit test configuration.
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

#ifndef CONF_TEST_H
#define CONF_TEST_H

/* I2S instance */
#define CONF_I2SC I2SC0

/* Use DMA for test, comment to use no DMA/PDC */
#define CONF_TEST_DMA      1

#define CONF_DMA           XDMAC
#define CONF_DMA_ID        ID_XDMAC
#define CONF_DMA_IRQn      XDMAC_IRQn

#define CONF_DMA_CH_OUT_L  0
#define CONF_DMA_CH_IN_L   1
#define CONF_DMA_CH_OUT_R  2
#define CONF_DMA_CH_IN_R   3

#define CONF_DMA_PERID_TX_L 44
#define CONF_DMA_PERID_RX_L 45
#define CONF_DMA_PERID_TX_R 48
#define CONF_DMA_PERID_RX_R 49

#endif /* CONF_TEST_H_INCLUDED */
