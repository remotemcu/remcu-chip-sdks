/***************************************************************************//**
 * @file bsp_stk_ioexp.c
 * @brief Board support package API implementation STK's.
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

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "bsp_stk_ioexp.h"
#include "i2cspm.h"

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *    Puts the IO Expander in sleep mode.
 *
 * @return
 *    None
 ******************************************************************************/
static inline void ioexpSleep(void)
{
  GPIO_PinOutSet(BSP_IOEXP_WAKE_PORT, BSP_IOEXP_WAKE_PIN);
  return;
}

/***************************************************************************//**
 * @brief
 *    Wakes up the IO expander
 *
 * @return
 *    None
 ******************************************************************************/
static inline void ioexpWake(void)
{
  GPIO_PinOutClear(BSP_IOEXP_WAKE_PORT, BSP_IOEXP_WAKE_PIN);
  return;
}

/***************************************************************************//**
 * @brief
 *    Performs register read through the I2C bus from the IO expander
 *
 * @param[in] addr
 *    The register address to read
 *
 * @param[out] result
 *    The data read from the device
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
static int i2cReadReg(uint8_t addr, uint8_t *value)
{
  I2C_TransferSeq_TypeDef seq;
  I2C_TransferReturn_TypeDef ret;
  int status;

  seq.addr        = 0x90;
  seq.flags       = I2C_FLAG_WRITE_READ;
  seq.buf[0].len  = 1;
  seq.buf[0].data = &addr;
  seq.buf[1].len  = 1;
  seq.buf[1].data = value;

  ret = I2CSPM_Transfer(BSP_IOEXP_I2C_DEVICE, &seq);

  if (ret == i2cTransferDone)
  {
    status = BSP_STATUS_OK;
  }
  else
  {
    status = BSP_STATUS_IOEXP_FAILURE;
  }

  return status;
}

/***************************************************************************//**
 * @brief
 *    Performs register write through the I2C bus to the IO expander
 *
 * @param[in] addr
 *    The register address to write
 *
 * @param[in] value
 *    The data to write to the register
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
static int i2cWriteReg(uint8_t addr, uint8_t value)
{
  I2C_TransferSeq_TypeDef seq;
  I2C_TransferReturn_TypeDef ret;
  int status;

  seq.addr        = 0x90;
  seq.flags       = I2C_FLAG_WRITE_WRITE;
  seq.buf[0].len  = 1;
  seq.buf[0].data = &addr;
  seq.buf[1].len  = 1;
  seq.buf[1].data = &value;

  ret = I2CSPM_Transfer(BSP_IOEXP_I2C_DEVICE, &seq);

  if (ret == i2cTransferDone)
  {
    status = BSP_STATUS_OK;
  }
  else
  {
    status = BSP_STATUS_IOEXP_FAILURE;
  }

  return status;
}

/***************************************************************************//**
 * @brief
 *    Reads the device ID of the IO expander
 *
 * @return
 *    Returns the device ID read from the device
 ******************************************************************************/
uint32_t ioexpGetDeviceId(void)
{
  uint32_t result;
  uint8_t *pU8;

  pU8 = (uint8_t*)&result;

  ioexpReadReg(BSP_IOEXP_REG_DEVICE_ID0, pU8++);
  ioexpReadReg(BSP_IOEXP_REG_DEVICE_ID1, pU8++);
  ioexpReadReg(BSP_IOEXP_REG_DEVICE_ID2, pU8++);
  ioexpReadReg(BSP_IOEXP_REG_DEVICE_ID3, pU8++);

  return result;
}

/***************************************************************************//**
 * @brief
 *    Reads a register in the IO expander
 *
 * @param[in] reg
 *    The register address to read
 *
 * @param[out] result
 *    The data read from the device
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
int ioexpReadReg(uint8_t reg, uint8_t *result)
{
  uint32_t status;

  ioexpWake();
  status = i2cReadReg(reg, result);
  ioexpSleep();

  return status;
}
/***************************************************************************//**
 * @brief
 *    Sets the given bit(s) in a register in the IO expander
 *
 * @param[in] addr
 *    The address of the register
 *
 * @param[in] set
 *    Specifies whether the bits selected by the mask should be set or cleared
 *
 * @param[in] bitMask
 *    The mask specifies which bits should be changed
 *
 * @return
 *    None
 ******************************************************************************/
int ioexpRegBitsSet(uint8_t addr, bool set, uint8_t bitMask)
{
  uint32_t status;
  uint8_t  value;

  ioexpWake();

  status = i2cReadReg(addr, &value);
  if (status != BSP_STATUS_OK)
  {
    goto cleanup;
  }

  if (set)
  {
    value |= bitMask;
  }
  else
  {
    value &= ~bitMask;
  }

  status = i2cWriteReg(addr, value);

cleanup:
  ioexpSleep();
  return status;
}

/***************************************************************************//**
 * @brief
 *    Writes a register in the IO expander
 *
 * @param[in] reg
 *    The register address to write
 *
 * @param[in] value
 *    The data to write to the register
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
int ioexpWriteReg(uint8_t reg, uint8_t value)
{
  uint32_t status;

  ioexpWake();
  status = i2cWriteReg(reg, value);
  ioexpSleep();

  return status;
}

/***************************************************************************//**
 * @brief
 *    Disable I/O expander, set registers to their default values.
 ******************************************************************************/
void ioexpDisable(void)
{
  /* Reset IO-expander registers */
  ioexpWake();
  i2cWriteReg(BSP_IOEXP_REG_VCOM_CTRL,   1);
  i2cWriteReg(BSP_IOEXP_REG_DISP_CTRL,   0);
  i2cWriteReg(BSP_IOEXP_REG_SENSOR_CTRL, 0);
  i2cWriteReg(BSP_IOEXP_REG_LED_CTRL,    0);
  ioexpSleep();
}

/***************************************************************************//**
 * @brief
 *    Enable I/O expander.
 ******************************************************************************/
int ioexpEnable(void)
{
  I2CSPM_Init_TypeDef i2cInit = I2CSPM_INIT_DEFAULT;

  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Setup GPIO pin used for waking up the io-expander */
  GPIO_PinModeSet(BSP_IOEXP_WAKE_PORT, BSP_IOEXP_WAKE_PIN,
                  gpioModeWiredAnd, 1);

  /* Initialize the I2C Simple Polled Mode driver */
  I2CSPM_Init(&i2cInit);

  /* Check that the device is responding */
  if (ioexpGetDeviceId() != BSP_IOEXP_DEVICE_ID)
  {
    return BSP_STATUS_IOEXP_FAILURE;
  }

  /* Set IOEXP default register content */
  ioexpWake();
  i2cWriteReg(BSP_IOEXP_REG_VCOM_CTRL,   1);
  i2cWriteReg(BSP_IOEXP_REG_DISP_CTRL,   0);
  i2cWriteReg(BSP_IOEXP_REG_SENSOR_CTRL, 0);
  i2cWriteReg(BSP_IOEXP_REG_LED_CTRL,    0);
  ioexpSleep();

  return BSP_STATUS_OK;
}

/** @endcond */
