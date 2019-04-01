/***************************************************************************//**
 * @file i2cspmconfig.h
 * @brief I2C SPM driver configuration parameters
 * @version 5.1.1
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

#ifndef __SILICON_LABS_I2CSPM_CONFIG_H__
#define __SILICON_LABS_I2CSPM_CONFIG_H__

/* I2C SPM driver config. This default override only works if one I2C interface
   is in use. If multiple interfaces are in use, define the peripheral setup
   inside the application in a I2CSPM_Init_TypeDef and then pass the initialization
   struct to I2CSPM_Init(). */

#define I2CSPM_INIT_DEFAULT                                                    \
  { I2C0,                      /* Use I2C instance 0 */                        \
    gpioPortC,                 /* SCL port */                                  \
    11,                        /* SCL pin */                                   \
    gpioPortC,                 /* SDA port */                                  \
    10,                        /* SDA pin */                                   \
    15,                        /* Port location of SCL signal */               \
    15,                        /* Port location of SDA signal */               \
    0,                         /* Use currently configured reference clock */  \
    I2C_FREQ_STANDARD_MAX,     /* Set to standard rate  */                     \
    i2cClockHLRStandard,       /* Set to use 4:4 low/high duty cycle */        \
  }

#define I2CSPM_TRANSFER_TIMEOUT 300000

#endif /* __SILICON_LABS_I2CSPM_CONFIG_H__ */

