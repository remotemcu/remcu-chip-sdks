/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_rtc.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_SetRtcClockSource(void);
/*!
 * @brief Set the alarm which will be trigerred x secs later. The alarm trigger
 *        will print a notification on the console.
 *
 * @param offsetSec  Offset seconds is set for alarm.
 */
static void CommandAlarm(uint8_t offsetSec);

/*!
 * @brief Run the digital clock in 20s and show the digital clock on console.
 *
 */
static void CommandSeconds(void);

/*!
 * @brief Get the current date time.
 *
 */
static void CommandGetDatetime(void);

/*!
 * @brief Receive the console input and echo.
 *
 * @param buf  Pointer of buffer.
 * @param size Size of buffer.
 */
static void ReceiveFromConsole(char *buf, uint32_t size);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint8_t g_AlarmPending = 0U;
volatile bool g_SecsFlag = false;

static char g_StrMenu[] =
    "\r\n"
    "Please choose the sub demo to run:\r\n"
    "1) Get current date time.\r\n"
    "2) Set current date time.\r\n"
    "3) Alarm trigger show.\r\n"
    "4) Second interrupt show (demo for 20s).\r\n";

static char g_StrNewline[] = "\r\n";
static char g_StrInvalid[] = "Invalid input format\r\n";

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Override the RTC IRQ handler.
 */
void RTC_IRQHandler(void)
{
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag)
    {
        g_AlarmPending = 1U;

        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC, kRTC_AlarmInterruptEnable);
    }
}

/*!
 * @brief Override the RTC Second IRQ handler.
 */
void RTC_Seconds_IRQHandler(void)
{
    g_SecsFlag = true;
}

void BOARD_SetRtcClockSource(void)
{
    /* Enable the RTC 32KHz oscillator */
    RTC->CR |= RTC_CR_OSCE_MASK;
}

static void CommandAlarm(uint8_t offsetSec)
{
    rtc_datetime_t date;

    RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);
    if ((offsetSec < 1U) || (offsetSec > 9U))
    {
        PRINTF("Invalid input format\r\n");
        return;
    }
    /* Get date time and add offset*/
    RTC_GetDatetime(RTC, &date);
    date.second += offsetSec;
    if (date.second > 59U)
    {
        date.second -= 60U;
        date.minute += 1U;
        if (date.minute > 59U)
        {
            date.minute -= 60U;
            date.hour += 1U;
            if (date.hour > 23U)
            {
                date.hour -= 24U;
                date.day += 1U;
            }
        }
    }

    /* Set the datetime for alarm */
    if (RTC_SetAlarm(RTC, &date) == kStatus_Success)
    {
        /* Alarm was successfully set, wait for alarm interrupt */
        while (g_AlarmPending == 0U)
        {
        }
    }
    else
    {
        PRINTF("Failed to set alarm. Alarm time is not in the future\r\n");
        return;
    }
    /* Interrupt done */
    RTC_GetDatetime(RTC, &date);
    PRINTF("Triggered Alarm: %02d:%02d:%02d\r\n", date.hour, date.minute, date.second);

    g_AlarmPending = 0U;
    RTC_DisableInterrupts(RTC, kRTC_AlarmInterruptEnable);
}

static void CommandGetDatetime(void)
{
    rtc_datetime_t date;

    RTC_GetDatetime(RTC, &date);
    PRINTF("Current datetime: %04d-%02d-%02d %02d:%02d:%02d\r\n", date.year, date.month, date.day, date.hour,
           date.minute, date.second);
}

static void CommandSeconds(void)
{
    uint32_t count = 0U;
    rtc_datetime_t date;
    char sourceBuff[] = "\r10:10:00";

    g_SecsFlag = false;
    while (count < 20U)
    {
        /* If seconds interrupt ocurred, print new time */
        if (g_SecsFlag)
        {
            /* Build up the word */
            g_SecsFlag = false;
            count++;
            RTC_GetDatetime(RTC, &date);

            sourceBuff[1] = ((date.hour / 10) + 0x30);
            sourceBuff[2] = ((date.hour % 10) + 0x30);
            sourceBuff[3] = ':';
            sourceBuff[4] = ((date.minute / 10) + 0x30);
            sourceBuff[5] = ((date.minute % 10) + 0x30);
            sourceBuff[6] = ':';
            sourceBuff[7] = ((date.second / 10) + 0x30);
            sourceBuff[8] = ((date.second % 10) + 0x30);
            /* Print the time */
            PRINTF(sourceBuff);
        }
    }
    /* Disable Sec interrupt */
    RTC_DisableInterrupts(RTC, kRTC_SecondsInterruptEnable);
    PRINTF(g_StrNewline);
}

static void ReceiveFromConsole(char *buf, uint32_t size)
{
    uint32_t i;

    for (i = 0U; i < size; i++)
    {
        buf[i] = GETCHAR();
        PUTCHAR(buf[i]);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t index;
    uint8_t secs;
    char recvBuf[20];
    uint32_t result;
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    rtc_config_t rtcConfig;
    rtc_datetime_t date;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init RTC */
    /*
     * rtcConfig.wakeupSelect = false;
     * rtcConfig.updateMode = false;
     * rtcConfig.supervisorAccess = false;
     * rtcConfig.compensationInterval = 0;
     * rtcConfig.compensationTime = 0;
     */
    RTC_GetDefaultConfig(&rtcConfig);
    RTC_Init(RTC, &rtcConfig);
    /* Select RTC clock source */
    BOARD_SetRtcClockSource();

    /* Set a start date time and start RTC */
    date.year = 2015U;
    date.month = 11U;
    date.day = 11U;
    date.hour = 11U;
    date.minute = 11U;
    date.second = 11U;

    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
    RTC_StopTimer(RTC);

    RTC_SetDatetime(RTC, &date);

    /* Enable at the NVIC */
    EnableIRQ(RTC_IRQn);
    EnableIRQ(RTC_Seconds_IRQn);

    /* Start the RTC time counter */
    RTC_StartTimer(RTC);

    PRINTF("\r\nRTC Demo running...\r\n");

    /* Start loop */
    while (1)
    {
        /* Print the user information */
        PRINTF(g_StrMenu);
        PRINTF("\r\nSelect:");
        /* Get user input */
        index = GETCHAR();
        PUTCHAR(index);
        PRINTF(g_StrNewline);

        switch (index)
        {
            case '1':
                CommandGetDatetime();
                break;
            case '2':
                PRINTF("Input date time like: \"2010-10-10 10:10:10\"\r\n");
                ReceiveFromConsole(recvBuf, 19U);
                result = sscanf(recvBuf, "%04hd-%02hd-%02hd %02hd:%02hd:%02hd", &year, &month, &day, &hour, &minute,
                                &second);
                PRINTF("%s", g_StrNewline);
                /* Error message will appear when user enters the invalid date time */
                if (result != 6U)
                {
                    PRINTF(g_StrInvalid);
                    break;
                }
                date.year = (uint16_t)year;
                date.month = (uint8_t)month;
                date.day = (uint8_t)day;
                date.hour = (uint8_t)hour;
                date.minute = (uint8_t)minute;
                date.second = (uint8_t)second;

                /* RTC time counter has to be stopped before setting the date & time in the TSR register */
                RTC_StopTimer(RTC);

                if (kStatus_Success != RTC_SetDatetime(RTC, &date))
                {
                    PRINTF(g_StrInvalid);
                }
                RTC_StartTimer(RTC);

                CommandGetDatetime();
                break;
            case '3':
                PRINTF("Input the alarm seconds from now on (1s~9s):");
                secs = GETCHAR();
                PUTCHAR(secs);
                PRINTF(g_StrNewline);
                secs -= '0';
                CommandAlarm(secs);
                break;
            case '4':
                /* Enable seconds interrupt */
                RTC_EnableInterrupts(RTC, kRTC_SecondsInterruptEnable);
                CommandSeconds();
                break;
            default:
                break;
        }
    }
}
