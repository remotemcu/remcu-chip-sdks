/***************************************************************************//**
 * @file i2cspmconfig.h
 * @brief I2CSPM driver configuration file
 * @version 5.1.0
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef I2CSPM_CONFIG_H
#define I2CSPM_CONFIG_H

/***************************************************************************//**
 * @addtogroup Drivers
 * @{
 ******************************************************************************/

 /***************************************************************************//**
 * @addtogroup I2CSPM
 * @{
 ******************************************************************************/

/* I2C SPM driver config. This default override only works if one I2C interface
   is in use. If multiple interfaces are in use, define the peripheral setup
   inside the application in a I2CSPM_Init_TypeDef and then pass the initialization
   struct to I2CSPM_Init(). */
#define I2CSPM_INIT_DEFAULT                                                    \
  { I2C0,                      /* Use I2C instance 0 */                        \
    gpioPortC,                 /* SCL port */                                  \
    10,                        /* SCL pin */                                   \
    gpioPortC,                 /* SDA port */                                  \
    11,                        /* SDA pin */                                   \
    14,                        /* Location of SCL */                           \
    16,                        /* Location of SDA */                           \
    0,                         /* Use currently configured reference clock */  \
    I2C_FREQ_STANDARD_MAX,     /* Set to standard rate  */                     \
    i2cClockHLRStandard,       /* Set to use 4:4 low/high duty cycle */        \
  }

#define I2CSPM_TRANSFER_TIMEOUT 300000

/** @} (end addtogroup I2CSPM) */
/** @} (end addtogroup Drivers) */

#endif /* I2CSPM_CONFIG_H */

