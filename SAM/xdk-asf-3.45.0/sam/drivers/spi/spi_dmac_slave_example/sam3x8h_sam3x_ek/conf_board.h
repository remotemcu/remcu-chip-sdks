/**
 * \file
 *
 * \brief Board configuration.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

#define CONF_BOARD_UART_CONSOLE

/** SPI0 MACRO definition */
#define CONF_BOARD_SPI0

/** SPI0 slave select0 MACRO definition */
#define CONF_BOARD_SPI0_NPCS0

/** Board SPI0 chip select0 pin definition */
#define BOARD_SPI0_NPCS0_GPIO         SPI0_NPCS0_GPIO
#define BOARD_SPI0_NPCS0_GPIO_FLAGS   SPI0_NPCS0_GPIO_FLAGS

/** Board SPI0 chip select1 pin definition. As there are several pins which 
 *  can be used as SPI chip select1, this needs to be modified according 
 *  to actual board.
 */
//#define BOARD_SPI0_NPCS1_GPIO         SPI0_NPCS1_GPIO_PA29
//#define BOARD_SPI0_NPCS1_GPIO_FLAGS   SPI0_NPCS1_GPIO_PA29_FLAGS

/** Board SPI0 chip select2 pin definition. As there are several pins which 
 *  can be used as SPI chip select2, this needs to be modified according 
 *  to actual board.
 */
//#define BOARD_SPI0_NPCS2_GPIO         SPI0_NPCS2_GPIO_PA30
//#define BOARD_SPI0_NPCS2_GPIO_FLAGS   SPI0_NPCS2_GPIO_PA30_FLAGS

/** Board SPI0 chip select3 pin definition. As there are several pins which 
 *  can be used as SPI chip select3, this needs to be modified according 
 *  to actual board.
 */
//#define BOARD_SPI0_NPCS3_GPIO         SPI0_NPCS3_GPIO_PA31
//#define BOARD_SPI0_NPCS3_GPIO_FLAGS   SPI0_NPCS3_GPIO_PA31_FLAGS

/** Board SPI1 chip select0 pin definition */
//#define BOARD_SPI1_NPCS0_GPIO         SPI1_NPCS0_GPIO
//#define BOARD_SPI1_NPCS0_GPIO_FLAGS   SPI1_NPCS0_GPIO_FLAGS

/** Board SPI1 chip select1 pin definition */
//#define BOARD_SPI1_NPCS1_GPIO         SPI1_NPCS1_GPIO
//#define BOARD_SPI1_NPCS1_GPIO_FLAGS   SPI1_NPCS1_GPIO_FLAGS

/** Board SPI1 chip select2 pin definition */
//#define BOARD_SPI1_NPCS2_GPIO         SPI1_NPCS2_GPIO
//#define BOARD_SPI1_NPCS2_GPIO_FLAGS   SPI1_NPCS2_GPIO_FLAGS

/** Board SPI1 chip select3 pin definition */
//#define BOARD_SPI1_NPCS3_GPIO         SPI1_NPCS3_GPIO
//#define BOARD_SPI1_NPCS3_GPIO_FLAGS   SPI1_NPCS3_GPIO_FLAGS

#endif /* CONF_BOARD_H_INCLUDED */
