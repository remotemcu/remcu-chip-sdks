/***************************************************************************//**
 * @file bsp_stk_ioexp.h
 * @brief Board support package API implementation for STK's.
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef BSP_STK_IOEXP_H
#define BSP_STK_IOEXP_H

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

// These defines are internal to the BSP and should not be used by user code.

#define BSP_IOEXP_REG_DISP_CTRL                 0x00
#define BSP_IOEXP_REG_VCOM_CTRL                 0x01
#define BSP_IOEXP_REG_SENSOR_CTRL               0x02
#define BSP_IOEXP_REG_LED_CTRL                  0x03

#define BSP_IOEXP_NUM_APP_REGS                  4

#define BSP_IOEXP_REG_SYS_CMD                   0xF0
#define BSP_IOEXP_REG_VERSION_MAJOR             0xF1
#define BSP_IOEXP_REG_VERSION_MINOR             0xF2
#define BSP_IOEXP_REG_VERSION_PATCH             0xF3

#define BSP_IOEXP_REG_SCRATCH0                  0xF4
#define BSP_IOEXP_REG_SCRATCH1                  0xF5
#define BSP_IOEXP_REG_SCRATCH2                  0xF6
#define BSP_IOEXP_REG_SCRATCH3                  0xF7

#define BSP_IOEXP_REG_DEVICE_ID0                0xF8
#define BSP_IOEXP_REG_DEVICE_ID1                0xF9
#define BSP_IOEXP_REG_DEVICE_ID2                0xFA
#define BSP_IOEXP_REG_DEVICE_ID3                0xFB

#define BSP_IOEXP_SYS_REG_START                 0xF0
#define BSP_IOEXP_NUM_SYS_REGS                  12

#define BSP_IOEXP_REG_DISP_CTRL_ENABLE          0x01
#define BSP_IOEXP_REG_DISP_CTRL_EXTCOMIN        0x02
#define BSP_IOEXP_REG_DISP_CTRL_AUTO_EXTCOMIN   0x04
#define BSP_IOEXP_REG_VCOM_CTRL_ENABLE          0x01
#define BSP_IOEXP_REG_SENSOR_CTRL_ENABLE        0x01
#define BSP_IOEXP_REG_LED_CTRL_LED0             0x01
#define BSP_IOEXP_REG_LED_CTRL_LED1             0x02
#define BSP_IOEXP_REG_LED_CTRL_LED_MASK         0x03
#define BSP_IOEXP_REG_LED_CTRL_DIRECT           0x80

#define BSP_IOEXP_REG_SYS_CMD_BOOTMODE          0xA5

#define BSP_IOEXP_DEVICE_ID                     0x50584F49

// These functions are internal to the BSP and should not be used by user code.

void     ioexpDisable(void);
int      ioexpEnable(void);
uint32_t ioexpGetDeviceId(void);
int      ioexpReadReg(uint8_t reg, uint8_t *result);
int      ioexpRegBitsSet(uint8_t addr, bool set, uint8_t bitMask);
int      ioexpWriteReg(uint8_t reg, uint8_t value);

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif  /* BSP_STK_IOEXP_H */
