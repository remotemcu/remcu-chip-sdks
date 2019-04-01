/***************************************************************************//**
 * @file util_sleep.c
 * @brief Utility Functions for the Thunderboard Sense
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
 
#include "thunderboard/util.h"
#include "rtcdriver.h"
#include "em_emu.h"

/***************************************************************************//**
 * @defgroup Util Utility Functions
 * @{
 * @brief Utility functions
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup Util_Locals Utility Functions Local Variables
 * @{
 * @brief Local variables used in the utility functions
 ******************************************************************************/
/* Local variables */
static volatile bool    rtcComplete;/**< Flag to show if the RTC has expired  */
static RTCDRV_TimerID_t rtcId;      /**< The ID of the currently used RTC     */

/** @} */

/***************************************************************************//**
 * @defgroup Util_Functions Utility Functions
 * @{
 * @brief Utility functions
 ******************************************************************************/
static void rtcCb( RTCDRV_TimerID_t id, void *user );
void SysTick_Handler( void );


/***************************************************************************//**
 * @brief
 *    Sets up the RTC timer used for sleep functions.
  *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t UTIL_sleepInit( void )
{
   uint32_t stat;

   /* Allocate RTC timer and start driver */
   stat = RTCDRV_Init();
   if( stat != ECODE_EMDRV_RTCDRV_OK ){
      return stat;
   }

   stat = RTCDRV_AllocateTimer(&rtcId);

   return stat;
}

/***************************************************************************//**
 * @brief
 *    Delays number of milliseconds in sleep mode (EM2) using the RTC
 *
 * @param ms
 *    Number of milliseconds to sleep
 *
 * @return
 *    None
 ******************************************************************************/
void UTIL_sleep( uint32_t ms )
{
   rtcComplete = false;
   RTCDRV_StartTimer( rtcId, rtcdrvTimerTypeOneshot, ms, rtcCb, 0 );

   while( !rtcComplete )
      EMU_EnterEM2(true);

   return;
}

/***************************************************************************//**
 * @brief
 *    Delays number of milliseconds in sleep mode (EM2) using the RTC but
 *    but returns if an event wakes up the MCU
 *
 * @param timeout
 *    Timeout, the maximum number of milliseconds to sleep
 *
 * @return
 *    The number of milliseconds remained from the timeout
 ******************************************************************************/
uint32_t UTIL_waitForEvent( uint32_t timeout )
{
   uint32_t remaining;

   rtcComplete = false;
   RTCDRV_StartTimer( rtcId, rtcdrvTimerTypeOneshot, timeout, rtcCb, 0 );

   EMU_EnterEM2( true );

   if( rtcComplete ){
      remaining = 0;
   }
   else {
      RTCDRV_TimeRemaining( rtcId, &remaining );
   }

   return remaining;
}

/***************************************************************************//**
 * @brief
 *    RTC callback function, called when the timer expired
 *
 * @param[in] id
 *    The id of the timer
 *
 * @param[in] user
 *    Extra parameter for user application (not used)
 *
 * @return
 *    None
 ******************************************************************************/
static void rtcCb( RTCDRV_TimerID_t id, void *user )
{
   rtcComplete = true;
}

/** @} */

/***************************************************************************//**
 * @}                                                                          *
 ******************************************************************************/
