/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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

#include "board.h"
#include "erpc_client_setup.h"
#include "erpc_error_handler.h"
#include "erpc_matrix_multiply.h"
#include "fsl_debug_console.h"
#include <stdlib.h>

#if BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_UART
#include "fsl_uart_cmsis.h"
#elif BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_LPUART
#include "fsl_lpuart_cmsis.h"
#elif BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_LPSCI
#include "fsl_lpsci_cmsis.h"
#endif

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BUTTON_INIT() GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &button_config)
#define IS_BUTTON_PRESSED() !GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN)
#define ERPC_DEMO_UART Driver_USART0
#define MATRIX_ITEM_MAX_VALUE 50

/*******************************************************************************
 * Variables
 ******************************************************************************/

extern bool g_erpc_error_occurred;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t UART0_GetFreq(void)
{
    return CLOCK_GetFreq(UART0_CLK_SRC);
}

/*!
 * @brief Fill matrices by random values
 */
static void fill_matrices(Matrix *matrix1_ptr, Matrix *matrix2_ptr)
{
    int32_t a, b;

    /* Fill both matrices by random values */
    for (a = 0; a < matrix_size; ++a)
    {
        for (b = 0; b < matrix_size; ++b)
        {
            (*matrix1_ptr)[a][b] = rand() % MATRIX_ITEM_MAX_VALUE;
            (*matrix2_ptr)[a][b] = rand() % MATRIX_ITEM_MAX_VALUE;
        }
    }
}

/*!
 * @brief Printing a matrix to the console
 */
static void print_matrix(Matrix *matrix_ptr)
{
    int32_t a, b;

    for (a = 0; a < matrix_size; ++a)
    {
        for (b = 0; b < matrix_size; ++b)
        {
            PRINTF("%4i ", (int)((*matrix_ptr)[a][b]));
        }
        PRINTF("\r\n");
    }
}

/*!
 * @brief Main function
 */
int main()
{
    Matrix matrix1, matrix2, result_matrix = {{0}};

    BOARD_InitPins();
    BOARD_BootClockRUN();

#if defined(BOARD_SW1_GPIO) || defined(BOARD_SW2_GPIO) || defined(BOARD_SW3_GPIO)
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t button_config = {
        kGPIO_DigitalInput, 0,
    };
    /* Configure BUTTON */
    BUTTON_INIT();
#endif

    /* UART transport layer initialization */
    erpc_transport_t transport;

    transport = erpc_transport_cmsis_uart_init((void *)&ERPC_DEMO_UART);

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
    message_buffer_factory = erpc_mbf_dynamic_init();

    /* eRPC client side initialization */
    erpc_client_init(transport, message_buffer_factory);

    /* Set default error handler */
    erpc_client_set_error_handler(erpc_error_handler);

    /* Fill both matrices by random values */
    fill_matrices(&matrix1, &matrix2);

    /* Print both matrices on the console */
    PRINTF("\r\nMatrix #1");
    PRINTF("\r\n=========\r\n");
    print_matrix(&matrix1);

    PRINTF("\r\nMatrix #2");
    PRINTF("\r\n=========\r\n");
    print_matrix(&matrix2);

    while (1)
    {
        PRINTF("\r\neRPC request is sent to the server\r\n");

        erpcMatrixMultiply((const Matrix *)&matrix1, (const Matrix *)&matrix2, &result_matrix);

        /* Check if some error occured in eRPC */
        if (g_erpc_error_occurred)
        {
            /* Exit program loop */
            break;
        }

        PRINTF("\r\nResult matrix");
        PRINTF("\r\n=============\r\n");
        print_matrix(&result_matrix);

#if defined(BOARD_SW1_GPIO) || defined(BOARD_SW2_GPIO) || defined(BOARD_SW3_GPIO)
        PRINTF("\r\nPress the button to initiate the next matrix multiplication\r\n");
        /* Check for button push. Pin is grounded when button is pushed. */
        while (1 != IS_BUTTON_PRESSED())
        {
        }

        /* Wait for a moment to eliminate the button glitch */
        int32_t i;
        for (i = 0; i < 2500000; ++i)
        {
            __NOP();
        }

        /* Fill both matrices by random values */
        fill_matrices(&matrix1, &matrix2);

        /* Print both matrices on the console */
        PRINTF("\r\nMatrix #1");
        PRINTF("\r\n=========\r\n");
        print_matrix(&matrix1);

        PRINTF("\r\nMatrix #2");
        PRINTF("\r\n=========\r\n");
        print_matrix(&matrix2);
#else
        PRINTF("\r\nEnd of example.\r\n");
        while (1)
        {
        }
#endif
    }
    while (1)
    {
    }
}
