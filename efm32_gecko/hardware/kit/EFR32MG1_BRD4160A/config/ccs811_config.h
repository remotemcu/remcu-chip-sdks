/***************************************************************************//**
 * @file ccs811_config.h
 * @brief Cambridge CMOS Sensors CCS811 gas sensor configuration file
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

#ifndef __CCS811_CONFIG_H_
#define __CCS811_CONFIG_H_

#define CCS811_CONFIG_I2C_BUS_TIMEOUT ( 1000 )
#define CCS811_CONFIG_DEVICE          ( I2C0 )
#define CCS811_CONFIG_BUS_ADDRESS     ( 0xB4 )
#define CCS811_CONFIG_FIRMWARE_UPDATE ( 0 )

#endif /* __CCS811_CONFIG_H_ */
