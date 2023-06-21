/**
 * \file
 *
 * \brief SAM USART RS485 Quick Start
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_sam0_sercom_usart_rs485_use_case Quick Start Guide for SERCOM USART RS485
 *
 * The supported board list:
 *    - SAMC21 Xplained Pro
 *
 * The RS-485 Xplained Pro Board must be connected to extension
 * header 1 on the SAM C21 Xplained Pro.
 
 * This quick start demonstrate how to configure RS485 mode, according to your
 * configuration \c CONF_RS485_MODE.
 * For RS485 master, it can send message to slave.
 * For RS485 salve, it can receive message from slave.
 *
 * To use the example:
 * 1. Install jumper between pins 2 and 3 on J101. This enables the TE pin to manage 
 * both DE and RE for Half-Duplex operation.
 * 2. Install jumper between pins 3 and 4 on J102. This removes the Profibus Termination for A/B.
 * 3. Install jumper between pins 1 and 2 on J103. This removes the Profibus Termination for Z/Y.
 * 4. Install jumpers on J106 and J107. This connects A/Y and B/Z to form half-duplex A/B differential pair.
 * Alternatively, this can be done by jumpering RXP to TXP and RXN to TXN, or pins 2 and 5 and
 * pins 3 and 4 on the screw terminal block.
 *
 * Refer to: http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42468-RS-485-Communications-using-the-SAM-C21-Xplained-Pro-and-RS-485-Xplained-Pro_ApplicationNote_AT8547.pdf
 * for more information
 */
