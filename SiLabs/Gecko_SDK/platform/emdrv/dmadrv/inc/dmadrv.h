/***************************************************************************//**
 * @file dmadrv.h
 * @brief DMADRV API definition.
 * @version 5.1.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __SILICON_LABS_DMADRV_H__
#define __SILICON_LABS_DMADRV_H__

#include "em_device.h"
#include "ecode.h"

#if defined( DMA_PRESENT ) && ( DMA_COUNT == 1 )
#define EMDRV_DMADRV_UDMA
#define EMDRV_DMADRV_DMA_PRESENT
#include "em_dma.h"
#elif defined( LDMA_PRESENT ) && ( LDMA_COUNT == 1 )
#define EMDRV_DMADRV_LDMA
#define EMDRV_DMADRV_DMA_PRESENT
#include "em_ldma.h"
#else
#error "No valid DMA engine defined."
#endif

#include "dmadrv_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup DMADRV
 * @{
 ******************************************************************************/

#define ECODE_EMDRV_DMADRV_OK                  ( ECODE_OK )                             ///< Success return value.
#define ECODE_EMDRV_DMADRV_PARAM_ERROR         ( ECODE_EMDRV_DMADRV_BASE | 0x00000001 ) ///< Illegal input parameter.
#define ECODE_EMDRV_DMADRV_NOT_INITIALIZED     ( ECODE_EMDRV_DMADRV_BASE | 0x00000002 ) ///< DMA is not initialized.
#define ECODE_EMDRV_DMADRV_ALREADY_INITIALIZED ( ECODE_EMDRV_DMADRV_BASE | 0x00000003 ) ///< DMA has already been initialized.
#define ECODE_EMDRV_DMADRV_CHANNELS_EXHAUSTED  ( ECODE_EMDRV_DMADRV_BASE | 0x00000004 ) ///< No DMA channels available.
#define ECODE_EMDRV_DMADRV_IN_USE              ( ECODE_EMDRV_DMADRV_BASE | 0x00000005 ) ///< DMA is in use.
#define ECODE_EMDRV_DMADRV_ALREADY_FREED       ( ECODE_EMDRV_DMADRV_BASE | 0x00000006 ) ///< DMA channel was free.
#define ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED    ( ECODE_EMDRV_DMADRV_BASE | 0x00000007 ) ///< The channel is not reserved.

/***************************************************************************//**
 * @brief
 *  DMADRV transfer completion callback function.
 *
 * @details
 *  The callback function is called when a transfer has completed.
 *
 * @param[in] channel
 *  The DMA channel number.
 *
 * @param[in] sequenceNo
 *  The number of times the callback had been called. Useful on long chains of
 *  linked transfers or on endless ping-pong type transfers.
 *
 * @param[in] userParam
 *  Optional user parameter supplied on DMA invocation.
 *
 * @return
 *   When doing ping-pong transfers, return true to continue or false to
 *   stop transfers.
 ******************************************************************************/
typedef bool (*DMADRV_Callback_t)( unsigned int channel,
                                   unsigned int sequenceNo,
                                   void *userParam );

#if defined( DMA_PRESENT ) && ( DMA_COUNT == 1 )

/// Maximum length of one DMA transfer.
#define DMADRV_MAX_XFER_COUNT ((int)((_DMA_CTRL_N_MINUS_1_MASK >> _DMA_CTRL_N_MINUS_1_SHIFT) + 1))

/// Peripherals that can trigger UDMA transfers.
typedef enum
{
  dmadrvPeripheralSignal_NONE = 0,                                        ///< No peripheral selected for DMA triggering.
  #if defined( DMAREQ_ADC0_SCAN )
  dmadrvPeripheralSignal_ADC0_SCAN = DMAREQ_ADC0_SCAN,                    ///< Trig on ADC0_SCAN.
  #endif
  #if defined( DMAREQ_ADC0_SINGLE )
  dmadrvPeripheralSignal_ADC0_SINGLE = DMAREQ_ADC0_SINGLE,                ///< Trig on ADC0_SINGLE.
  #endif
  #if defined( DMAREQ_AES_DATARD )
  dmadrvPeripheralSignal_AES_DATARD = DMAREQ_AES_DATARD,                  ///< Trig on AES_DATARD.
  #endif
  #if defined( DMAREQ_AES_DATAWR )
  dmadrvPeripheralSignal_AES_DATAWR = DMAREQ_AES_DATAWR,                  ///< Trig on AES_DATAWR.
  #endif
  #if defined( DMAREQ_AES_KEYWR )
  dmadrvPeripheralSignal_AES_KEYWR = DMAREQ_AES_KEYWR,                    ///< Trig on AES_KEYWR.
  #endif
  #if defined( DMAREQ_AES_XORDATAWR )
  dmadrvPeripheralSignal_AES_XORDATAWR = DMAREQ_AES_XORDATAWR,            ///< Trig on AES_XORDATAWR.
  #endif
  #if defined( DMAREQ_DAC0_CH0 )
  dmadrvPeripheralSignal_DAC0_CH0 = DMAREQ_DAC0_CH0,                      ///< Trig on DAC0_CH0.
  #endif
  #if defined( DMAREQ_DAC0_CH1 )
  dmadrvPeripheralSignal_DAC0_CH1 = DMAREQ_DAC0_CH1,                      ///< Trig on DAC0_CH1.
  #endif
  #if defined( DMAREQ_EBI_DDEMPTY )
  dmadrvPeripheralSignal_EBI_DDEMPTY = DMAREQ_EBI_DDEMPTY,                ///< Trig on EBI_DDEMPTY.
  #endif
  #if defined( DMAREQ_EBI_PXL0EMPTY )
  dmadrvPeripheralSignal_EBI_PXL0EMPTY = DMAREQ_EBI_PXL0EMPTY,            ///< Trig on EBI_PXL0EMPTY.
  #endif
  #if defined( DMAREQ_EBI_PXL1EMPTY )
  dmadrvPeripheralSignal_EBI_PXL1EMPTY = DMAREQ_EBI_PXL1EMPTY,            ///< Trig on EBI_PXL1EMPTY.
  #endif
  #if defined( DMAREQ_EBI_PXLFULL )
  dmadrvPeripheralSignal_EBI_PXLFULL = DMAREQ_EBI_PXLFULL,                ///< Trig on EBI_PXLFULL.
  #endif
  #if defined( DMAREQ_I2C0_RXDATAV )
  dmadrvPeripheralSignal_I2C0_RXDATAV = DMAREQ_I2C0_RXDATAV,              ///< Trig on I2C0_RXDATAV.
  #endif
  #if defined( DMAREQ_I2C0_TXBL )
  dmadrvPeripheralSignal_I2C0_TXBL = DMAREQ_I2C0_TXBL,                    ///< Trig on I2C0_TXBL.
  #endif
  #if defined( DMAREQ_I2C1_RXDATAV )
  dmadrvPeripheralSignal_I2C1_RXDATAV = DMAREQ_I2C1_RXDATAV,              ///< Trig on I2C1_RXDATAV.
  #endif
  #if defined( DMAREQ_I2C1_TXBL )
  dmadrvPeripheralSignal_I2C1_TXBL = DMAREQ_I2C1_TXBL,                    ///< Trig on I2C1_TXBL.
  #endif
  #if defined( DMAREQ_LESENSE_BUFDATAV )
  dmadrvPeripheralSignal_LESENSE_BUFDATAV = DMAREQ_LESENSE_BUFDATAV,      ///< Trig on LESENSE_BUFDATAV.
  #endif
  #if defined( DMAREQ_LEUART0_RXDATAV )
  dmadrvPeripheralSignal_LEUART0_RXDATAV = DMAREQ_LEUART0_RXDATAV,        ///< Trig on LEUART0_RXDATAV.
  #endif
  #if defined( DMAREQ_LEUART0_TXBL )
  dmadrvPeripheralSignal_LEUART0_TXBL = DMAREQ_LEUART0_TXBL,              ///< Trig on LEUART0_TXBL.
  #endif
  #if defined( DMAREQ_LEUART0_TXEMPTY )
  dmadrvPeripheralSignal_LEUART0_TXEMPTY = DMAREQ_LEUART0_TXEMPTY,        ///< Trig on LEUART0_TXEMPTY.
  #endif
  #if defined( DMAREQ_LEUART1_RXDATAV )
  dmadrvPeripheralSignal_LEUART1_RXDATAV = DMAREQ_LEUART1_RXDATAV,        ///< Trig on LEUART1_RXDATAV.
  #endif
  #if defined( DMAREQ_LEUART1_TXBL )
  dmadrvPeripheralSignal_LEUART1_TXBL = DMAREQ_LEUART1_TXBL,              ///< Trig on LEUART1_TXBL.
  #endif
  #if defined( DMAREQ_LEUART1_TXEMPTY )
  dmadrvPeripheralSignal_LEUART1_TXEMPTY = DMAREQ_LEUART1_TXEMPTY,        ///< Trig on LEUART1_TXEMPTY.
  #endif
  #if defined( DMAREQ_MSC_WDATA )
  dmadrvPeripheralSignal_MSC_WDATA = DMAREQ_MSC_WDATA,                    ///< Trig on MSC_WDATA.
  #endif
  #if defined( DMAREQ_TIMER0_CC0 )
  dmadrvPeripheralSignal_TIMER0_CC0 = DMAREQ_TIMER0_CC0,                  ///< Trig on TIMER0_CC0.
  #endif
  #if defined( DMAREQ_TIMER0_CC1 )
  dmadrvPeripheralSignal_TIMER0_CC1 = DMAREQ_TIMER0_CC1,                  ///< Trig on TIMER0_CC1.
  #endif
  #if defined( DMAREQ_TIMER0_CC2 )
  dmadrvPeripheralSignal_TIMER0_CC2 = DMAREQ_TIMER0_CC2,                  ///< Trig on TIMER0_CC2.
  #endif
  #if defined( DMAREQ_TIMER0_UFOF )
  dmadrvPeripheralSignal_TIMER0_UFOF = DMAREQ_TIMER0_UFOF,                ///< Trig on TIMER0_UFOF.
  #endif
  #if defined( DMAREQ_TIMER1_CC0 )
  dmadrvPeripheralSignal_TIMER1_CC0 = DMAREQ_TIMER1_CC0,                  ///< Trig on TIMER1_CC0.
  #endif
  #if defined( DMAREQ_TIMER1_CC1 )
  dmadrvPeripheralSignal_TIMER1_CC1 = DMAREQ_TIMER1_CC1,                  ///< Trig on TIMER1_CC1.
  #endif
  #if defined( DMAREQ_TIMER1_CC2 )
  dmadrvPeripheralSignal_TIMER1_CC2 = DMAREQ_TIMER1_CC2,                  ///< Trig on TIMER1_CC2.
  #endif
  #if defined( DMAREQ_TIMER1_UFOF )
  dmadrvPeripheralSignal_TIMER1_UFOF = DMAREQ_TIMER1_UFOF,                ///< Trig on TIMER1_UFOF.
  #endif
  #if defined( DMAREQ_TIMER2_CC0 )
  dmadrvPeripheralSignal_TIMER2_CC0 = DMAREQ_TIMER2_CC0,                  ///< Trig on TIMER2_CC0.
  #endif
  #if defined( DMAREQ_TIMER2_CC1 )
  dmadrvPeripheralSignal_TIMER2_CC1 = DMAREQ_TIMER2_CC1,                  ///< Trig on TIMER2_CC1.
  #endif
  #if defined( DMAREQ_TIMER2_CC2 )
  dmadrvPeripheralSignal_TIMER2_CC2 = DMAREQ_TIMER2_CC2,                  ///< Trig on TIMER2_CC2.
  #endif
  #if defined( DMAREQ_TIMER2_UFOF )
  dmadrvPeripheralSignal_TIMER2_UFOF = DMAREQ_TIMER2_UFOF,                ///< Trig on TIMER2_UFOF.
  #endif
  #if defined( DMAREQ_TIMER3_CC0 )
  dmadrvPeripheralSignal_TIMER3_CC0 = DMAREQ_TIMER3_CC0,                  ///< Trig on TIMER3_CC0.
  #endif
  #if defined( DMAREQ_TIMER3_CC1 )
  dmadrvPeripheralSignal_TIMER3_CC1 = DMAREQ_TIMER3_CC1,                  ///< Trig on TIMER3_CC1.
  #endif
  #if defined( DMAREQ_TIMER3_CC2 )
  dmadrvPeripheralSignal_TIMER3_CC2 = DMAREQ_TIMER3_CC2,                  ///< Trig on TIMER3_CC2.
  #endif
  #if defined( DMAREQ_TIMER3_UFOF )
  dmadrvPeripheralSignal_TIMER3_UFOF = DMAREQ_TIMER3_UFOF,                ///< Trig on TIMER3_UFOF.
  #endif
  #if defined( DMAREQ_UART0_RXDATAV )
  dmadrvPeripheralSignal_UART0_RXDATAV = DMAREQ_UART0_RXDATAV,            ///< Trig on UART0_RXDATAV.
  #endif
  #if defined( DMAREQ_UART0_TXBL )
  dmadrvPeripheralSignal_UART0_TXBL = DMAREQ_UART0_TXBL,                  ///< Trig on UART0_TXBL.
  #endif
  #if defined( DMAREQ_UART0_TXEMPTY )
  dmadrvPeripheralSignal_UART0_TXEMPTY = DMAREQ_UART0_TXEMPTY,            ///< Trig on UART0_TXEMPTY.
  #endif
  #if defined( DMAREQ_UART1_RXDATAV )
  dmadrvPeripheralSignal_UART1_RXDATAV = DMAREQ_UART1_RXDATAV,            ///< Trig on UART1_RXDATAV.
  #endif
  #if defined( DMAREQ_UART1_TXBL )
  dmadrvPeripheralSignal_UART1_TXBL = DMAREQ_UART1_TXBL,                  ///< Trig on UART1_TXBL.
  #endif
  #if defined( DMAREQ_UART1_TXEMPTY )
  dmadrvPeripheralSignal_UART1_TXEMPTY = DMAREQ_UART1_TXEMPTY,            ///< Trig on UART1_TXEMPTY.
  #endif
  #if defined( DMAREQ_USART0_RXDATAV )
  dmadrvPeripheralSignal_USART0_RXDATAV = DMAREQ_USART0_RXDATAV,          ///< Trig on USART0_RXDATAV.
  #endif
  #if defined( DMAREQ_USART0_TXBL )
  dmadrvPeripheralSignal_USART0_TXBL = DMAREQ_USART0_TXBL,                ///< Trig on USART0_TXBL.
  #endif
  #if defined( DMAREQ_USART0_TXEMPTY )
  dmadrvPeripheralSignal_USART0_TXEMPTY = DMAREQ_USART0_TXEMPTY,          ///< Trig on USART0_TXEMPTY.
  #endif
  #if defined( DMAREQ_USARTRF0_RXDATAV )
  dmadrvPeripheralSignal_USARTRF0_RXDATAV = DMAREQ_USARTRF0_RXDATAV,            ///< Trig on USARTRF0_RXDATAV.
  #endif
  #if defined( DMAREQ_USARTRF0_TXBL )
  dmadrvPeripheralSignal_USARTRF0_TXBL = DMAREQ_USARTRF0_TXBL,                  ///< Trig on USARTRF0_TXBL.
  #endif
  #if defined( DMAREQ_USARTRF0_TXEMPTY )
  dmadrvPeripheralSignal_USARTRF0_TXEMPTY = DMAREQ_USARTRF0_TXEMPTY,            ///< Trig on USARTRF0_TXEMPTY.
  #endif
  #if defined( DMAREQ_USARTRF1_RXDATAV )
  dmadrvPeripheralSignal_USARTRF1_RXDATAV = DMAREQ_USARTRF1_RXDATAV,            ///< Trig on USARTRF1_RXDATAV.
  #endif
  #if defined( DMAREQ_USARTRF1_TXBL )
  dmadrvPeripheralSignal_USARTRF1_TXBL = DMAREQ_USARTRF1_TXBL,                  ///< Trig on USARTRF1_TXBL.
  #endif
  #if defined( DMAREQ_USARTRF1_TXEMPTY )
  dmadrvPeripheralSignal_USARTRF1_TXEMPTY = DMAREQ_USARTRF1_TXEMPTY,            ///< Trig on USARTRF1_TXEMPTY.
  #endif
  #if defined( DMAREQ_USART1_RXDATAV )
  dmadrvPeripheralSignal_USART1_RXDATAV = DMAREQ_USART1_RXDATAV,          ///< Trig on USART1_RXDATAV.
  #endif
  #if defined( DMAREQ_USART1_RXDATAVRIGHT )
  dmadrvPeripheralSignal_USART1_RXDATAVRIGHT = DMAREQ_USART1_RXDATAVRIGHT,///< Trig on USART1_RXDATAVRIGHT.
  #endif
  #if defined( DMAREQ_USART1_TXBL )
  dmadrvPeripheralSignal_USART1_TXBL = DMAREQ_USART1_TXBL,                ///< Trig on USART1_TXBL.
  #endif
  #if defined( DMAREQ_USART1_TXBLRIGHT )
  dmadrvPeripheralSignal_USART1_TXBLRIGHT = DMAREQ_USART1_TXBLRIGHT,      ///< Trig on USART1_TXBLRIGHT.
  #endif
  #if defined( DMAREQ_USART1_TXEMPTY )
  dmadrvPeripheralSignal_USART1_TXEMPTY = DMAREQ_USART1_TXEMPTY,          ///< Trig on USART1_TXEMPTY.
  #endif
  #if defined( DMAREQ_USART2_RXDATAV )
  dmadrvPeripheralSignal_USART2_RXDATAV = DMAREQ_USART2_RXDATAV,          ///< Trig on USART2_RXDATAV.
  #endif
  #if defined( DMAREQ_USART2_RXDATAVRIGHT )
  dmadrvPeripheralSignal_USART2_RXDATAVRIGHT = DMAREQ_USART2_RXDATAVRIGHT,///< Trig on USART2_RXDATAVRIGHT.
  #endif
  #if defined( DMAREQ_USART2_TXBL )
  dmadrvPeripheralSignal_USART2_TXBL = DMAREQ_USART2_TXBL,                ///< Trig on USART2_TXBL.
  #endif
  #if defined( DMAREQ_USART2_TXBLRIGHT )
  dmadrvPeripheralSignal_USART2_TXBLRIGHT = DMAREQ_USART2_TXBLRIGHT,      ///< Trig on USART2_TXBLRIGHT.
  #endif
  #if defined( DMAREQ_USART2_TXEMPTY )
  dmadrvPeripheralSignal_USART2_TXEMPTY = DMAREQ_USART2_TXEMPTY,          ///< Trig on USART2_TXEMPTY.
  #endif
#ifdef DOXY_DOC_ONLY
} DMADRV_Peripheralsignal_t;
#else
} DMADRV_PeripheralSignal_t;
#endif

/// Data size of one UDMA transfer item.
typedef enum
{
  dmadrvDataSize1 = dmaDataSize1,     ///< Byte
  dmadrvDataSize2 = dmaDataSize2,     ///< Halfword
  dmadrvDataSize4 = dmaDataSize4      ///< Word
#ifdef DOXY_DOC_ONLY
} DMADRV_Datasize_t;
#else
} DMADRV_DataSize_t;
#endif

#endif // defined( DMA_PRESENT ) && ( DMA_COUNT == 1 )

#if defined( LDMA_PRESENT ) && ( LDMA_COUNT == 1 )

/// Maximum length of one DMA transfer.
#define DMADRV_MAX_XFER_COUNT ((int)((_LDMA_CH_CTRL_XFERCNT_MASK >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1))

/// Peripherals that can trigger LDMA transfers.
typedef enum
{
  dmadrvPeripheralSignal_NONE = LDMA_CH_REQSEL_SOURCESEL_NONE,                                                              ///< No peripheral selected for DMA triggering.
  #if defined( LDMA_CH_REQSEL_SIGSEL_ADC0SCAN )
  dmadrvPeripheralSignal_ADC0_SCAN = LDMA_CH_REQSEL_SIGSEL_ADC0SCAN | LDMA_CH_REQSEL_SOURCESEL_ADC0,                        ///< Trig on ADC0_SCAN.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_ADC0SINGLE )
  dmadrvPeripheralSignal_ADC0_SINGLE = LDMA_CH_REQSEL_SIGSEL_ADC0SINGLE | LDMA_CH_REQSEL_SOURCESEL_ADC0,                    ///< Trig on ADC0_SINGLE.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_AGCRSSI )
  dmadrvPeripheralSignal_AGC_RSSI = LDMA_CH_REQSEL_SIGSEL_AGCRSSI | LDMA_CH_REQSEL_SOURCESEL_AGC,                           ///< Trig on AGC_RSSI.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0RD )
  dmadrvPeripheralSignal_CRYPTO_DATA0RD = LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO,            ///< Trig on CRYPTO_DATA0RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0WR )
  dmadrvPeripheralSignal_CRYPTO_DATA0WR = LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO,            ///< Trig on CRYPTO_DATA0WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0XWR )
  dmadrvPeripheralSignal_CRYPTO_DATA0XWR = LDMA_CH_REQSEL_SIGSEL_CRYPTODATA0XWR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO,          ///< Trig on CRYPTO_DATA0XWR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTODATA1RD )
  dmadrvPeripheralSignal_CRYPTO_DATA1RD = LDMA_CH_REQSEL_SIGSEL_CRYPTODATA1RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO,            ///< Trig on CRYPTO_DATA1RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTODATA1WR )
  dmadrvPeripheralSignal_CRYPTO_DATA1WR = LDMA_CH_REQSEL_SIGSEL_CRYPTODATA1WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO,            ///< Trig on CRYPTO_DATA1WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0RD )
  dmadrvPeripheralSignal_CRYPTO0_DATA0RD = LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO0,            ///< Trig on CRYPTO0_DATA0RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0WR )
  dmadrvPeripheralSignal_CRYPTO0_DATA0WR = LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO0,            ///< Trig on CRYPTO0_DATA0WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0XWR )
  dmadrvPeripheralSignal_CRYPTO0_DATA0XWR = LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA0XWR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO0,          ///< Trig on CRYPTO0_DATA0XWR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA1RD )
  dmadrvPeripheralSignal_CRYPTO0_DATA1RD = LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA1RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO0,            ///< Trig on CRYPTO0_DATA1RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA1WR )
  dmadrvPeripheralSignal_CRYPTO0_DATA1WR = LDMA_CH_REQSEL_SIGSEL_CRYPTO0DATA1WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO0,            ///< Trig on CRYPTO0_DATA1WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0RD )
  dmadrvPeripheralSignal_CRYPTO1_DATA0RD = LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO1,            ///< Trig on CRYPTO1_DATA0RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0WR )
  dmadrvPeripheralSignal_CRYPTO1_DATA0WR = LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO1,            ///< Trig on CRYPTO1_DATA0WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0XWR )
  dmadrvPeripheralSignal_CRYPTO1_DATA0XWR = LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA0XWR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO1,          ///< Trig on CRYPTO1_DATA0XWR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA1RD )
  dmadrvPeripheralSignal_CRYPTO1_DATA1RD = LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA1RD | LDMA_CH_REQSEL_SOURCESEL_CRYPTO1,            ///< Trig on CRYPTO1_DATA1RD.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA1WR )
  dmadrvPeripheralSignal_CRYPTO1_DATA1WR = LDMA_CH_REQSEL_SIGSEL_CRYPTO1DATA1WR | LDMA_CH_REQSEL_SOURCESEL_CRYPTO1,            ///< Trig on CRYPTO1_DATA1WR.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_I2C0RXDATAV )
  dmadrvPeripheralSignal_I2C0_RXDATAV = LDMA_CH_REQSEL_SIGSEL_I2C0RXDATAV | LDMA_CH_REQSEL_SOURCESEL_I2C0,                  ///< Trig on I2C0_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_I2C0TXBL )
  dmadrvPeripheralSignal_I2C0_TXBL = LDMA_CH_REQSEL_SIGSEL_I2C0TXBL | LDMA_CH_REQSEL_SOURCESEL_I2C0,                        ///< Trig on I2C0_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_LEUART0RXDATAV )
  dmadrvPeripheralSignal_LEUART0_RXDATAV = LDMA_CH_REQSEL_SIGSEL_LEUART0RXDATAV | LDMA_CH_REQSEL_SOURCESEL_LEUART0,         ///< Trig on LEUART0_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_LEUART0TXBL )
  dmadrvPeripheralSignal_LEUART0_TXBL = LDMA_CH_REQSEL_SIGSEL_LEUART0TXBL | LDMA_CH_REQSEL_SOURCESEL_LEUART0,               ///< Trig on LEUART0_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_LEUART0TXEMPTY )
  dmadrvPeripheralSignal_LEUART0_TXEMPTY = LDMA_CH_REQSEL_SIGSEL_LEUART0TXEMPTY | LDMA_CH_REQSEL_SOURCESEL_LEUART0,         ///< Trig on LEUART0_TXEMPTY.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_MODEMDEBUG )
  dmadrvPeripheralSignal_MODEM_DEBUG = LDMA_CH_REQSEL_SIGSEL_MODEMDEBUG | LDMA_CH_REQSEL_SOURCESEL_MODEM,                   ///< Trig on MODEM_DEBUG.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_MSCWDATA )
  dmadrvPeripheralSignal_MSC_WDATA = LDMA_CH_REQSEL_SIGSEL_MSCWDATA | LDMA_CH_REQSEL_SOURCESEL_MSC,                         ///< Trig on MSC_WDATA.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERBOF )
  dmadrvPeripheralSignal_PROTIMER_BOF = LDMA_CH_REQSEL_SIGSEL_PROTIMERBOF | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_BOF.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERCC0 )
  dmadrvPeripheralSignal_PROTIMER_CC0 = LDMA_CH_REQSEL_SIGSEL_PROTIMERCC0 | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_CC0.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERCC1 )
  dmadrvPeripheralSignal_PROTIMER_CC1 = LDMA_CH_REQSEL_SIGSEL_PROTIMERCC1 | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_CC1.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERCC2 )
  dmadrvPeripheralSignal_PROTIMER_CC2 = LDMA_CH_REQSEL_SIGSEL_PROTIMERCC2 | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_CC2.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERCC3 )
  dmadrvPeripheralSignal_PROTIMER_CC3 = LDMA_CH_REQSEL_SIGSEL_PROTIMERCC3 | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_CC3.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERCC4 )
  dmadrvPeripheralSignal_PROTIMER_CC4 = LDMA_CH_REQSEL_SIGSEL_PROTIMERCC4 | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_CC4.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERPOF )
  dmadrvPeripheralSignal_PROTIMER_POF = LDMA_CH_REQSEL_SIGSEL_PROTIMERPOF | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_POF.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PROTIMERWOF )
  dmadrvPeripheralSignal_PROTIMER_WOF = LDMA_CH_REQSEL_SIGSEL_PROTIMERWOF | LDMA_CH_REQSEL_SOURCESEL_PROTIMER,              ///< Trig on PROTIMER_WOF.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PRSREQ0 )
  dmadrvPeripheralSignal_PRS_REQ0 = LDMA_CH_REQSEL_SIGSEL_PRSREQ0 | LDMA_CH_REQSEL_SOURCESEL_PRS,                           ///< Trig on PRS_REQ0.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_PRSREQ1 )
  dmadrvPeripheralSignal_PRS_REQ1 = LDMA_CH_REQSEL_SIGSEL_PRSREQ1 | LDMA_CH_REQSEL_SOURCESEL_PRS,                           ///< Trig on PRS_REQ1.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER0CC0 )
  dmadrvPeripheralSignal_TIMER0_CC0 = LDMA_CH_REQSEL_SIGSEL_TIMER0CC0 | LDMA_CH_REQSEL_SOURCESEL_TIMER0,                    ///< Trig on TIMER0_CC0.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER0CC1 )
  dmadrvPeripheralSignal_TIMER0_CC1 = LDMA_CH_REQSEL_SIGSEL_TIMER0CC1 | LDMA_CH_REQSEL_SOURCESEL_TIMER0,                    ///< Trig on TIMER0_CC1.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER0CC2 )
  dmadrvPeripheralSignal_TIMER0_CC2 = LDMA_CH_REQSEL_SIGSEL_TIMER0CC2 | LDMA_CH_REQSEL_SOURCESEL_TIMER0,                    ///< Trig on TIMER0_CC2.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER0UFOF )
  dmadrvPeripheralSignal_TIMER0_UFOF = LDMA_CH_REQSEL_SIGSEL_TIMER0UFOF | LDMA_CH_REQSEL_SOURCESEL_TIMER0,                  ///< Trig on TIMER0_UFOF.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER1CC0 )
  dmadrvPeripheralSignal_TIMER1_CC0 = LDMA_CH_REQSEL_SIGSEL_TIMER1CC0 | LDMA_CH_REQSEL_SOURCESEL_TIMER1,                    ///< Trig on TIMER1_CC0.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER1CC1 )
  dmadrvPeripheralSignal_TIMER1_CC1 = LDMA_CH_REQSEL_SIGSEL_TIMER1CC1 | LDMA_CH_REQSEL_SOURCESEL_TIMER1,                    ///< Trig on TIMER1_CC1.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER1CC2 )
  dmadrvPeripheralSignal_TIMER1_CC2 = LDMA_CH_REQSEL_SIGSEL_TIMER1CC2 | LDMA_CH_REQSEL_SOURCESEL_TIMER1,                    ///< Trig on TIMER1_CC2.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER1CC3 )
  dmadrvPeripheralSignal_TIMER1_CC3 = LDMA_CH_REQSEL_SIGSEL_TIMER1CC3 | LDMA_CH_REQSEL_SOURCESEL_TIMER1,                    ///< Trig on TIMER1_CC3.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_TIMER1UFOF )
  dmadrvPeripheralSignal_TIMER1_UFOF = LDMA_CH_REQSEL_SIGSEL_TIMER1UFOF | LDMA_CH_REQSEL_SOURCESEL_TIMER1,                  ///< Trig on TIMER1_UFOF.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART0RXDATAV )
  dmadrvPeripheralSignal_USART0_RXDATAV = LDMA_CH_REQSEL_SIGSEL_USART0RXDATAV | LDMA_CH_REQSEL_SOURCESEL_USART0,            ///< Trig on USART0_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART0TXBL )
  dmadrvPeripheralSignal_USART0_TXBL = LDMA_CH_REQSEL_SIGSEL_USART0TXBL | LDMA_CH_REQSEL_SOURCESEL_USART0,                  ///< Trig on USART0_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART0TXEMPTY )
  dmadrvPeripheralSignal_USART0_TXEMPTY = LDMA_CH_REQSEL_SIGSEL_USART0TXEMPTY | LDMA_CH_REQSEL_SOURCESEL_USART0,            ///< Trig on USART0_TXEMPTY.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART1RXDATAV )
  dmadrvPeripheralSignal_USART1_RXDATAV = LDMA_CH_REQSEL_SIGSEL_USART1RXDATAV | LDMA_CH_REQSEL_SOURCESEL_USART1,            ///< Trig on USART1_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART1RXDATAVRIGHT )
  dmadrvPeripheralSignal_USART1_RXDATAVRIGHT = LDMA_CH_REQSEL_SIGSEL_USART1RXDATAVRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART1,  ///< Trig on USART1_RXDATAVRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART1TXBL )
  dmadrvPeripheralSignal_USART1_TXBL = LDMA_CH_REQSEL_SIGSEL_USART1TXBL | LDMA_CH_REQSEL_SOURCESEL_USART1,                  ///< Trig on USART1_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART1TXBLRIGHT )
  dmadrvPeripheralSignal_USART1_TXBLRIGHT = LDMA_CH_REQSEL_SIGSEL_USART1TXBLRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART1,        ///< Trig on USART1_TXBLRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART1TXEMPTY )
  dmadrvPeripheralSignal_USART1_TXEMPTY = LDMA_CH_REQSEL_SIGSEL_USART1TXEMPTY | LDMA_CH_REQSEL_SOURCESEL_USART1,            ///< Trig on USART1_TXEMPTY.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART2RXDATAV )
  dmadrvPeripheralSignal_USART2_RXDATAV = LDMA_CH_REQSEL_SIGSEL_USART2RXDATAV | LDMA_CH_REQSEL_SOURCESEL_USART2,            ///< Trig on USART2_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART2RXDATAVRIGHT )
  dmadrvPeripheralSignal_USART2_RXDATAVRIGHT = LDMA_CH_REQSEL_SIGSEL_USART2RXDATAVRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART2,  ///< Trig on USART2_RXDATAVRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART2TXBL )
  dmadrvPeripheralSignal_USART2_TXBL = LDMA_CH_REQSEL_SIGSEL_USART2TXBL | LDMA_CH_REQSEL_SOURCESEL_USART2,                  ///< Trig on USART2_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART2TXBLRIGHT )
  dmadrvPeripheralSignal_USART2_TXBLRIGHT = LDMA_CH_REQSEL_SIGSEL_USART2TXBLRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART2,        ///< Trig on USART2_TXBLRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART2TXEMPTY )
  dmadrvPeripheralSignal_USART2_TXEMPTY = LDMA_CH_REQSEL_SIGSEL_USART2TXEMPTY | LDMA_CH_REQSEL_SOURCESEL_USART2,            ///< Trig on USART2_TXEMPTY.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART3RXDATAV )
  dmadrvPeripheralSignal_USART3_RXDATAV = LDMA_CH_REQSEL_SIGSEL_USART3RXDATAV | LDMA_CH_REQSEL_SOURCESEL_USART3,            ///< Trig on USART3_RXDATAV.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART3RXDATAVRIGHT )
  dmadrvPeripheralSignal_USART3_RXDATAVRIGHT = LDMA_CH_REQSEL_SIGSEL_USART3RXDATAVRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART3,  ///< Trig on USART3_RXDATAVRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART3TXBL )
  dmadrvPeripheralSignal_USART3_TXBL = LDMA_CH_REQSEL_SIGSEL_USART3TXBL | LDMA_CH_REQSEL_SOURCESEL_USART3,                  ///< Trig on USART3_TXBL.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART3TXBLRIGHT )
  dmadrvPeripheralSignal_USART3_TXBLRIGHT = LDMA_CH_REQSEL_SIGSEL_USART3TXBLRIGHT | LDMA_CH_REQSEL_SOURCESEL_USART3,        ///< Trig on USART3_TXBLRIGHT.
  #endif
  #if defined( LDMA_CH_REQSEL_SIGSEL_USART3TXEMPTY )
  dmadrvPeripheralSignal_USART3_TXEMPTY = LDMA_CH_REQSEL_SIGSEL_USART3TXEMPTY | LDMA_CH_REQSEL_SOURCESEL_USART3             ///< Trig on USART3_TXEMPTY.
  #endif


} DMADRV_PeripheralSignal_t;

/// Data size of one LDMA transfer item.
typedef enum
{
  dmadrvDataSize1 = ldmaCtrlSizeByte, ///< Byte
  dmadrvDataSize2 = ldmaCtrlSizeHalf, ///< Halfword
  dmadrvDataSize4 = ldmaCtrlSizeWord  ///< Word
} DMADRV_DataSize_t;

#endif /* defined( LDMA_PRESENT ) && ( LDMA_COUNT == 1 ) */

Ecode_t DMADRV_AllocateChannel( unsigned int *channelId, void *capabilities );
Ecode_t DMADRV_DeInit( void );
Ecode_t DMADRV_FreeChannel( unsigned int channelId );
Ecode_t DMADRV_Init( void );

#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( DOXY_DOC_ONLY )
Ecode_t DMADRV_MemoryPeripheral( unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst,
                                 void                  *src,
                                 bool                  srcInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam );
Ecode_t DMADRV_PeripheralMemory( unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst,
                                 void                  *src,
                                 bool                  dstInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam );
Ecode_t DMADRV_MemoryPeripheralPingPong(
                                 unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst,
                                 void                  *src0,
                                 void                  *src1,
                                 bool                  srcInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam );
Ecode_t DMADRV_PeripheralMemoryPingPong(
                                 unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst0,
                                 void                  *dst1,
                                 void                  *src,
                                 bool                  dstInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam );
#endif

#if defined( EMDRV_DMADRV_LDMA ) && defined( EMDRV_DMADRV_USE_NATIVE_API )

Ecode_t DMADRV_LdmaStartTransfer(
                                 int                channelId,
                                 LDMA_TransferCfg_t *transfer,
                                 LDMA_Descriptor_t  *descriptor,
                                 DMADRV_Callback_t  callback,
                                 void               *cbUserParam );

#endif /* !defined( EMDRV_DMADRV_USE_NATIVE_API ) */

Ecode_t DMADRV_PauseTransfer( unsigned int channelId );
Ecode_t DMADRV_ResumeTransfer( unsigned int channelId );
Ecode_t DMADRV_StopTransfer( unsigned int channelId );
Ecode_t DMADRV_TransferActive( unsigned int channelId, bool *active );
Ecode_t DMADRV_TransferCompletePending( unsigned int channelId, bool *pending );
Ecode_t DMADRV_TransferDone( unsigned int channelId, bool *done );
Ecode_t DMADRV_TransferRemainingCount( unsigned int channelId,
                                       int *remaining );

/** @} (end addtogroup DMADRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* __SILICON_LABS_DMADRV_H__ */
