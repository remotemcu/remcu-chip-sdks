/***************************************************************************//**
 * @file token_config.h
 * @brief  * @brief Token configuration parameters
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

#ifndef TOKEN_CONFIG_H_INCLUDED__
#define TOKEN_CONFIG_H_INCLUDED__

#define TOKEN_DEVINFO_BASE_ADDRESS    0x0FE08000
#define TOKEN_LOCKBITS_BASE_ADDRESS   0x0FE04000
#define TOKEN_MAINFLASH_BASE_ADDRESS  0x00000000
#define TOKEN_USERDATA_BASE_ADDRESS   0x0FE00000

#define TOKEN_COUNT 8

#define SB_RADIO_CTUNE_OFFSET          0x0100
#define SB_RADIO_CTUNE_ADDR            (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_CTUNE_OFFSET)
#define SB_RADIO_CTUNE_SIZE            2

#define SB_RADIO_OUTPUT_POWER_OFFSET   0x0702
#define SB_RADIO_OUTPUT_POWER_ADDR     (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_OUTPUT_POWER_OFFSET)
#define SB_RADIO_OUTPUT_POWER_SIZE     2

#define SB_RADIO_CHANNEL_OFFSET        0x0704
#define SB_RADIO_CHANNEL_ADDR          (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_CHANNEL_OFFSET)
#define SB_RADIO_CHANNEL_SIZE          2

#define SB_RADIO_NODE_ID_OFFSET        0x0706
#define SB_RADIO_NODE_ID_ADDR          (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_NODE_ID_OFFSET)
#define SB_RADIO_NODE_ID_SIZE          1

#define SB_RADIO_NODE_ROLE_OFFSET      0x0707
#define SB_RADIO_NODE_ROLE_ADDR        (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_NODE_ROLE_OFFSET)
#define SB_RADIO_NODE_ROLE_SIZE        1

#define SB_RADIO_BEACON_PERIOD_OFFSET  0x0708
#define SB_RADIO_BEACON_PERIOD_ADDR    (TOKEN_USERDATA_BASE_ADDRESS + SB_RADIO_BEACON_PERIOD_OFFSET)
#define SB_RADIO_BEACON_PERIOD_SIZE    2

#define SB_NODE_COLOUR_OFFSET          0x0710
#define SB_NODE_COLOUR_ADDR            (TOKEN_USERDATA_BASE_ADDRESS + SB_NODE_COLOUR_OFFSET)
#define SB_NODE_COLOUR_SIZE            4

#define SB_NODE_COUNT_OFFSET           0x0714
#define SB_NODE_COUNT_ADDR             (TOKEN_USERDATA_BASE_ADDRESS + SB_NODE_COUNT_OFFSET)
#define SB_NODE_COUNT_SIZE             1


#endif /* TOKEN_CONFIG_H_INCLUDED__ */
