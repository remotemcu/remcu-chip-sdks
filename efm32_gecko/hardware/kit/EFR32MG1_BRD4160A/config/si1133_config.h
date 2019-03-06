/***************************************************************************//**
 * @file si1133_config.h
 * @brief Si1133 Ambient Light and UV sensor configuration file
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

#ifndef __SI1133_CONFIG_H_
#define __SI1133_CONFIG_H_

#define SI1133_CONFIG_I2C_BUS_TIMEOUT ( 1000 )
#define SI1133_CONFIG_DEVICE          ( I2C0 )
#define SI1133_CONFIG_BUS_ADDRESS     ( 0xAA )

#endif /* __SI1133_CONFIG_H_ */
