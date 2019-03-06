/***************************************************************************//**
 * @file dmadrv.c
 * @brief DMADRV API implementation.
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

#include <stdbool.h>
#include <stddef.h>

#include "em_device.h"
#include "em_cmu.h"
#include "em_core.h"

#include "dmadrv.h"

#if defined( EMDRV_DMADRV_UDMA )
#include "dmactrl.h"
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#if !defined( EMDRV_DMADRV_DMA_CH_COUNT ) \
    || ( EMDRV_DMADRV_DMA_CH_COUNT > DMA_CHAN_COUNT )
#define EMDRV_DMADRV_DMA_CH_COUNT DMA_CHAN_COUNT
#endif

typedef enum
{
  dmaDirectionMemToPeripheral,
  dmaDirectionPeripheralToMem
} DmaDirection_t;

typedef enum
{
  dmaModeBasic,
  dmaModePingPong
} DmaMode_t;

#if defined( EMDRV_DMADRV_USE_NATIVE_API ) && defined( EMDRV_DMADRV_UDMA )
typedef struct
{
  bool              allocated;
} ChTable_t;

#elif defined( EMDRV_DMADRV_USE_NATIVE_API ) && defined( EMDRV_DMADRV_LDMA )
typedef struct
{
  DMADRV_Callback_t callback;
  void              *userParam;
  unsigned int      callbackCount;
  bool              allocated;
} ChTable_t;

#else
typedef struct
{
  DMADRV_Callback_t callback;
  void              *userParam;
  unsigned int      callbackCount;
#if defined( EMDRV_DMADRV_UDMA )
  int               length;
#endif
  bool              allocated;
#if defined( EMDRV_DMADRV_LDMA )
  DmaMode_t         mode;
#endif
} ChTable_t;
#endif

static bool initialized = false;
static ChTable_t chTable[ EMDRV_DMADRV_DMA_CH_COUNT ];

#if defined( EMDRV_DMADRV_UDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
static DMA_CB_TypeDef dmaCallBack[ EMDRV_DMADRV_DMA_CH_COUNT ];
#endif

#if defined( EMDRV_DMADRV_LDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
const LDMA_TransferCfg_t xferCfg = LDMA_TRANSFER_CFG_PERIPHERAL( 0 );
const LDMA_Descriptor_t m2p = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE( NULL, NULL, 1UL );
const LDMA_Descriptor_t p2m = LDMA_DESCRIPTOR_SINGLE_P2M_BYTE( NULL, NULL, 1UL );

typedef struct
{
  LDMA_Descriptor_t desc[2];
} DmaXfer_t;

static DmaXfer_t dmaXfer[ EMDRV_DMADRV_DMA_CH_COUNT ];
#endif

#if !defined( EMDRV_DMADRV_USE_NATIVE_API )
static Ecode_t StartTransfer( DmaMode_t             mode,
                              DmaDirection_t        direction,
                              unsigned int          channelId,
                              DMADRV_PeripheralSignal_t
                                                    peripheralSignal,
                              void                  *buf0,
                              void                  *buf1,
                              void                  *buf2,
                              bool                  bufInc,
                              int                   len,
                              DMADRV_DataSize_t     size,
                              DMADRV_Callback_t     callback,
                              void                  *cbUserParam );
#endif

/// @endcond

/***************************************************************************//**
 * @brief
 *  Allocate (reserve) a DMA channel.
 *
 * @param[out] channelId
 *  The channel Id assigned by DMADRV.
 *
 * @param[in] capabilities
 *  Not used.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_AllocateChannel( unsigned int *channelId, void *capabilities )
{
  int i;
  (void)capabilities;
  CORE_DECLARE_IRQ_STATE;

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId == NULL )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  CORE_ENTER_ATOMIC();
  for ( i=0; i < EMDRV_DMADRV_DMA_CH_COUNT; i++ )
  {
    if ( !chTable[ i ].allocated )
    {
      *channelId             = i;
      chTable[ i ].allocated = true;
#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( EMDRV_DMADRV_LDMA )
      chTable[ i ].callback  = NULL;
#endif
      CORE_EXIT_ATOMIC();
      return ECODE_EMDRV_DMADRV_OK;
    }
  }
  CORE_EXIT_ATOMIC();
  return ECODE_EMDRV_DMADRV_CHANNELS_EXHAUSTED;
}

/***************************************************************************//**
 * @brief
 *  Deinitialize DMADRV.
 *
 * @details
 *  If no DMA channels are currently allocated, it will disable DMA hardware
 *  and mask associated interrupts.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_DeInit( void )
{
  int i;
  bool inUse;
  CORE_DECLARE_IRQ_STATE;

  inUse = false;

  CORE_ENTER_ATOMIC();
  for ( i=0; i < EMDRV_DMADRV_DMA_CH_COUNT; i++ )
  {
    if ( chTable[ i ].allocated )
    {
      inUse = true;
      break;
    }
  }

  if ( !inUse )
  {
#if defined( EMDRV_DMADRV_UDMA )
    NVIC_DisableIRQ( DMA_IRQn );
    DMA->IEN    = _DMA_IEN_RESETVALUE;
    DMA->CONFIG = _DMA_CONFIG_RESETVALUE;
    CMU_ClockEnable( cmuClock_DMA, false );
#elif defined( EMDRV_DMADRV_LDMA )
    LDMA_DeInit();
#endif
    initialized = false;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_DMADRV_OK;
  }
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_DMADRV_IN_USE;
}

/***************************************************************************//**
 * @brief
 *  Free an allocate (reserved) DMA channel.
 *
 * @param[in] channelId
 *  The channel Id to free.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_FreeChannel( unsigned int channelId )
{
  CORE_DECLARE_IRQ_STATE;

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  CORE_ENTER_ATOMIC();
  if ( chTable[ channelId ].allocated )
  {
    chTable[ channelId ].allocated = false;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_DMADRV_OK;
  }
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_DMADRV_ALREADY_FREED;
}

/***************************************************************************//**
 * @brief
 *  Initialize DMADRV.
 *
 * @details
 *  The DMA hw is initialized.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_Init( void )
{
  int i;
  CORE_DECLARE_IRQ_STATE;
#if defined( EMDRV_DMADRV_UDMA )
  DMA_Init_TypeDef dmaInit;
#elif defined( EMDRV_DMADRV_LDMA )
  LDMA_Init_t dmaInit = LDMA_INIT_DEFAULT;
  dmaInit.ldmaInitCtrlNumFixed = EMDRV_DMADRV_DMA_CH_PRIORITY;
#endif

  CORE_ENTER_ATOMIC();
  if ( initialized )
  {
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_DMADRV_ALREADY_INITIALIZED;
  }
  initialized = true;
  CORE_EXIT_ATOMIC();

  if ( EMDRV_DMADRV_DMA_IRQ_PRIORITY > 7 )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  for ( i=0; i < EMDRV_DMADRV_DMA_CH_COUNT; i++ )
  {
    chTable[ i ].allocated = false;
  }

#if defined( EMDRV_DMADRV_UDMA )
  NVIC_SetPriority( DMA_IRQn, EMDRV_DMADRV_DMA_IRQ_PRIORITY );
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;
  DMA_Init( &dmaInit );
#elif defined( EMDRV_DMADRV_LDMA )
  dmaInit.ldmaInitIrqPriority = EMDRV_DMADRV_DMA_IRQ_PRIORITY;
  LDMA_Init( &dmaInit );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

#if defined( EMDRV_DMADRV_LDMA ) && defined( EMDRV_DMADRV_USE_NATIVE_API )
/***************************************************************************//**
 * @brief
 *  Start a LDMA transfer.
 *
 * @details
 *  This function can only be used on LDMA when @ref EMDRV_DMADRV_USE_NATIVE_API
 *  is defined. It is a wrapper around similar emlib ldma function.
 *
 * @param[in] channelId
 *  The channel Id to use.
 *
 * @param[in] transfer
 *  DMA transfer configuration data structure.
 *
 * @param[in] descriptor
 *  DMA transfer descriptor, can be an array of descriptors linked together.
 *
 * @param[in] callback
 *  Optional callback function for signalling completion. May be NULL if not
 *  needed.
 *
 * @param[in] cbUserParam
 *  Optional user parameter to feed to the callback function. May be NULL if
 *  not needed.
 *
 * @return
 *   @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *   DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_LdmaStartTransfer( int                channelId,
                                  LDMA_TransferCfg_t *transfer,
                                  LDMA_Descriptor_t  *descriptor,
                                  DMADRV_Callback_t  callback,
                                  void               *cbUserParam )
{
  ChTable_t *ch;

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  ch = &chTable[ channelId ];
  if ( ch->allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

  ch->callback      = callback;
  ch->userParam     = cbUserParam;
  ch->callbackCount = 0;
  LDMA_StartTransfer( channelId, transfer, descriptor );

  return ECODE_EMDRV_DMADRV_OK;
}
#endif

#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( DOXY_DOC_ONLY )
/***************************************************************************//**
 * @brief
 *  Start a memory to peripheral DMA transfer.
 *
 * @param[in] channelId
 *  Not used
 *
 * @param[in] peripheralSignal
 *  Selects which peripheral/peripheralsignal to use.
 *
 * @param[in] dst
 *  Destination (peripheral register) memory address.
 *
 * @param[in] src
 *  Source memory address.
 *
 * @param[in] srcInc
 *  Set to true to enable source address increment (increment is according to
 *  @a size parameter).
 *
 * @param[in] len
 *  Number if items (of @a size size) to transfer.
 *
 * @param[in] size
 *  Item size, byte, halfword or word.
 *
 * @param[in] callback
 *  Function to call on dma completion, use NULL if not needed.
 *
 * @param[in] cbUserParam
 *  Optional user parameter to feed to the callback function. Use NULL if
 *  not needed.
 *
 * @return
 *   @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *   DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_MemoryPeripheral( unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst,
                                 void                  *src,
                                 bool                  srcInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam )
{
  return StartTransfer( dmaModeBasic,
                        dmaDirectionMemToPeripheral,
                        channelId,
                        peripheralSignal,
                        dst,
                        src,
                        NULL,
                        srcInc,
                        len,
                        size,
                        callback,
                        cbUserParam );
}
#endif

#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( DOXY_DOC_ONLY )
/***************************************************************************//**
 * @brief
 *  Start a memory to peripheral ping-pong DMA transfer.
 *
 * @param[in] channelId
 *  Not used
 *
 * @param[in] peripheralSignal
 *  Selects which peripheral/peripheralsignal to use.
 *
 * @param[in] dst
 *  Destination (peripheral register) memory address.
 *
 * @param[in] src0
 *  Source memory address of first (ping) buffer.
 *
 * @param[in] src1
 *  Source memory address of second (pong) buffer.
 *
 * @param[in] srcInc
 *  Set to true to enable source address increment (increment is according to
 *  @a size parameter).
 *
 * @param[in] len
 *  Number if items (of @a size size) to transfer.
 *
 * @param[in] size
 *  Item size, byte, halfword or word.
 *
 * @param[in] callback
 *  Function to call on dma completion, use NULL if not needed.
 *
 * @param[in] cbUserParam
 *  Optional user parameter to feed to the callback function. Use NULL if
 *  not needed.
 *
 * @return
 *   @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *   DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
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
                                 void                  *cbUserParam )
{
  return StartTransfer( dmaModePingPong,
                        dmaDirectionMemToPeripheral,
                        channelId,
                        peripheralSignal,
                        dst,
                        src0,
                        src1,
                        srcInc,
                        len,
                        size,
                        callback,
                        cbUserParam );
}
#endif

#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( DOXY_DOC_ONLY )
/***************************************************************************//**
 * @brief
 *  Start a peripheral to memory DMA transfer.
 *
 * @param[in] channelId
 *  Not used
 *
 * @param[in] peripheralSignal
 *  Selects which peripheral/peripheralsignal to use.
 *
 * @param[in] dst
 *  Destination memory address.
 *
 * @param[in] src
 *  Source memory (peripheral register) address.
 *
 * @param[in] dstInc
 *  Set to true to enable destination address increment (increment is according
 *  to @a size parameter).
 *
 * @param[in] len
 *  Number if items (of @a size size) to transfer.
 *
 * @param[in] size
 *  Item size, byte, halfword or word.
 *
 * @param[in] callback
 *  Function to call on dma completion, use NULL if not needed.
 *
 * @param[in] cbUserParam
 *  Optional user parameter to feed to the callback function. Use NULL if
 *  not needed.
 *
 * @return
 *   @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *   DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_PeripheralMemory( unsigned int          channelId,
                                 DMADRV_PeripheralSignal_t
                                                       peripheralSignal,
                                 void                  *dst,
                                 void                  *src,
                                 bool                  dstInc,
                                 int                   len,
                                 DMADRV_DataSize_t     size,
                                 DMADRV_Callback_t     callback,
                                 void                  *cbUserParam )
{
  return StartTransfer( dmaModeBasic,
                        dmaDirectionPeripheralToMem,
                        channelId,
                        peripheralSignal,
                        dst,
                        src,
                        NULL,
                        dstInc,
                        len,
                        size,
                        callback,
                        cbUserParam );
}
#endif

#if !defined( EMDRV_DMADRV_USE_NATIVE_API ) || defined( DOXY_DOC_ONLY )
/***************************************************************************//**
 * @brief
 *  Start a peripheral to memory ping-pong DMA transfer.
 *
 * @param[in] channelId
 *  Not used
 *
 * @param[in] peripheralSignal
 *  Selects which peripheral/peripheralsignal to use.
 *
 * @param[in] dst0
 *  Destination memory address of first (ping) buffer.
 *
 * @param[in] dst1
 *  Destination memory address of second (pong) buffer.
 *
 * @param[in] src
 *  Source memory (peripheral register) address.
 *
 * @param[in] dstInc
 *  Set to true to enable destination address increment (increment is according
 *  to @a size parameter).
 *
 * @param[in] len
 *  Number if items (of @a size size) to transfer.
 *
 * @param[in] size
 *  Item size, byte, halfword or word.
 *
 * @param[in] callback
 *  Function to call on dma completion, use NULL if not needed.
 *
 * @param[in] cbUserParam
 *  Optional user parameter to feed to the callback function. Use NULL if
 *  not needed.
 *
 * @return
 *   @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *   DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
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
                                 void                  *cbUserParam )
{
  return StartTransfer( dmaModePingPong,
                        dmaDirectionPeripheralToMem,
                        channelId,
                        peripheralSignal,
                        dst0,
                        dst1,
                        src,
                        dstInc,
                        len,
                        size,
                        callback,
                        cbUserParam );
}
#endif /* !defined( EMDRV_DMADRV_USE_NATIVE_API ) */

/***************************************************************************//**
 * @brief
 *  Pause an ongoing DMA transfer.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to pause.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_PauseTransfer( unsigned int channelId )
{
  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  DMA_ChannelRequestEnable( channelId, false );
#elif defined( EMDRV_DMADRV_LDMA )
  LDMA_EnableChannelRequest( channelId, false );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Resume an ongoing DMA transfer.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to resume.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_ResumeTransfer( unsigned int channelId )
{
  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  DMA_ChannelRequestEnable( channelId, true );
#elif defined( EMDRV_DMADRV_LDMA )
  LDMA_EnableChannelRequest( channelId, true );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Stop an ongoing DMA transfer.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to stop.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_StopTransfer( unsigned int channelId )
{
  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  DMA_ChannelEnable( channelId, false );
#elif defined( EMDRV_DMADRV_LDMA )
  LDMA_StopTransfer( channelId );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Check if a transfer is running.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to check.
 *
 * @param[out] active
 *  True if transfer is running, false otherwise.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_TransferActive( unsigned int channelId, bool *active )
{
  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( active == NULL ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  if ( DMA_ChannelEnabled( channelId ) )
#elif defined( EMDRV_DMADRV_LDMA )
  if ( LDMA->CHEN & ( 1 << channelId ) )
#endif
  {
    *active = true;
  }
  else
  {
    *active = false;
  }

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Check if a transfer complete is pending.
 *
 * @details
 *  Will check channel interrupt flag. This assumes that the DMA is configured
 *  to giva a completion interrupt.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to check.
 *
 * @param[out] pending
 *  True if a transfer complete is pending, false otherwise.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_TransferCompletePending( unsigned int channelId, bool *pending )
{
  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( pending == NULL ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  if ( DMA->IF & ( 1 << channelId ) )
#elif defined( EMDRV_DMADRV_LDMA )
  if ( LDMA->IF & ( 1 << channelId ) )
#endif
  {
    *pending = true;
  }
  else
  {
    *pending = false;
  }

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Check if a transfer has completed.
 *
 * @note
 *  This function is meant to be used in a polled environment.
 *  Will only work reliable for transfers NOT using completion interrupt.
 *  On UDMA it will only work on basic transfers on primary channel.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to check.
 *
 * @param[out] done
 *  True if a transfer has completed, false otherwise.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_TransferDone( unsigned int channelId, bool *done )
{
#if defined( EMDRV_DMADRV_UDMA )
  uint32_t remaining, iflag;
#endif

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( done == NULL ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  CORE_ATOMIC_SECTION(
    /* This works for primary channel only ! */
    remaining = ( dmaControlBlock[ channelId ].CTRL
                  & _DMA_CTRL_N_MINUS_1_MASK )
                >> _DMA_CTRL_N_MINUS_1_SHIFT;
    iflag = DMA->IF;
  )

  if ( ( remaining == 0 ) && ( iflag & ( 1 << channelId ) ) )
  {
    *done = true;
  }
  else
  {
    *done = false;
  }
#elif defined( EMDRV_DMADRV_LDMA )
  *done = LDMA_TransferDone( channelId );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

/***************************************************************************//**
 * @brief
 *  Get number of items remaining in a transfer.
 *
 * @note
 *  This function is does not take into account that a DMA transfers with
 *  a chain of linked transfers might be ongoing. It will only check the
 *  count for the current transfer.
 *  On UDMA it will only work on the primary channel.
 *
 * @param[in] channelId
 *  The channel Id of the transfer to check.
 *
 * @param[out] remaining
 *  Number of items remaining in the transfer.
 *
 * @return
 *  @ref ECODE_EMDRV_DMADRV_OK on success. On failure an appropriate
 *  DMADRV @ref Ecode_t is returned.
 ******************************************************************************/
Ecode_t DMADRV_TransferRemainingCount( unsigned int channelId,
                                  int *remaining )
{
#if defined( EMDRV_DMADRV_UDMA )
  uint32_t remain, iflag;
#endif

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( remaining == NULL ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  if ( chTable[ channelId ].allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

#if defined( EMDRV_DMADRV_UDMA )
  CORE_ATOMIC_SECTION(
    /* This works for primary channel only ! */
    remain = ( dmaControlBlock[ channelId ].CTRL
               & _DMA_CTRL_N_MINUS_1_MASK )
             >> _DMA_CTRL_N_MINUS_1_SHIFT;
    iflag = DMA->IF;
  )

  if ( ( remain == 0 ) && ( iflag & ( 1 << channelId ) ) )
  {
    *remaining = 0;
  }
  else
  {
    *remaining = 1 + remain;
  }
#elif defined( EMDRV_DMADRV_LDMA )
  *remaining = LDMA_TransferRemainingCount( channelId );
#endif

  return ECODE_EMDRV_DMADRV_OK;
}

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#if defined( EMDRV_DMADRV_LDMA )
/***************************************************************************//**
 * @brief
 *  Interrupt handler for LDMA.
 ******************************************************************************/
void LDMA_IRQHandler( void )
{
#if !defined( EMDRV_DMADRV_USE_NATIVE_API )
  bool stop;
#endif
  ChTable_t *ch;
  uint32_t pending, chnum, chmask;

  /* Get all pending and enabled interrupts */
  pending  = LDMA->IF;
  pending &= LDMA->IEN;

  /* Check for LDMA error */
  if ( pending & LDMA_IF_ERROR )
  {
    /* Loop here to enable the debugger to see what has happened */
    while (1)
    {
      /* Wait forever. */
    }
  }

  /* Iterate over all LDMA channels. */
  for ( chnum = 0,                          chmask = 1;
        chnum < EMDRV_DMADRV_DMA_CH_COUNT;
        chnum++,                            chmask <<= 1 )
  {
    if ( pending & chmask )
    {
      /* Clear interrupt flag. */
      LDMA->IFC = chmask;

      ch = &chTable[ chnum ];
      if ( ch->callback != NULL )
      {
        ch->callbackCount++;
#if defined( EMDRV_DMADRV_USE_NATIVE_API )
        ch->callback( chnum, ch->callbackCount, ch->userParam );
#else
        stop = !ch->callback( chnum, ch->callbackCount, ch->userParam );

        if ( ( ch->mode == dmaModePingPong ) && stop )
        {
          dmaXfer[ chnum ].desc[0].xfer.link = 0;
          dmaXfer[ chnum ].desc[1].xfer.link = 0;
        }
#endif
      }
    }
  }
}
#endif /* defined( EMDRV_DMADRV_LDMA ) */

#if defined( EMDRV_DMADRV_UDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
/***************************************************************************//**
 * @brief
 *  Callback function for UDMA basic transfers.
 ******************************************************************************/
static void DmaBasicCallback( unsigned int channel, bool primary, void *user )
{
  ChTable_t *ch = &chTable[ channel ];
  (void)user;
  (void)primary;

  if ( ch->callback != NULL )
  {
    ch->callbackCount++;
    ch->callback( channel, ch->callbackCount, ch->userParam );
  }
}
#endif

#if defined( EMDRV_DMADRV_UDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
/***************************************************************************//**
 * @brief
 *  Callback function for UDMA ping-pong transfers.
 ******************************************************************************/
static void DmaPingPongCallback( unsigned int channel, bool primary, void *user )
{
  bool stop = true;
  ChTable_t *ch = &chTable[ channel ];

  (void)user;

  if ( ch->callback != NULL )
  {
    ch->callbackCount++;
    stop = !ch->callback( channel, ch->callbackCount, ch->userParam );
  }

  DMA_RefreshPingPong(  0,
                        primary,
                        false,
                        NULL,
                        NULL,
                        ch->length - 1,
                        stop );
}
#endif

#if defined( EMDRV_DMADRV_UDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
/***************************************************************************//**
 * @brief
 *  Start a UDMA transfer.
 ******************************************************************************/
static Ecode_t StartTransfer( DmaMode_t             mode,
                              DmaDirection_t        direction,
                              unsigned int          channelId,
                              DMADRV_PeripheralSignal_t
                                                    peripheralSignal,
                              void                  *buf0,
                              void                  *buf1,
                              void                  *buf2,
                              bool                  bufInc,
                              int                   len,
                              DMADRV_DataSize_t     size,
                              DMADRV_Callback_t     callback,
                              void                  *cbUserParam )
{
  ChTable_t *ch;
  DMA_CfgChannel_TypeDef chCfg;
  DMA_CfgDescr_TypeDef   descrCfg;

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( buf0 == NULL )
       || ( buf1 == NULL )
       || ( len > DMADRV_MAX_XFER_COUNT )
       || ( ( mode == dmaModePingPong ) && ( buf2 == NULL ) ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  ch = &chTable[ channelId ];
  if ( ch->allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

  /* Setup the interrupt callback routine. */
  if ( mode == dmaModeBasic )
  {
    dmaCallBack[ channelId ].cbFunc  = DmaBasicCallback;
  }
  else
  {
    dmaCallBack[ channelId ].cbFunc  = DmaPingPongCallback;
  }
  dmaCallBack[ channelId ].userPtr = NULL;

  /* Setup the channel */
  chCfg.highPri = false;              /* Can't use hi pri with peripherals. */

  /* Interrupt needed ? */
  if ( ( callback != NULL ) || ( mode == dmaModePingPong ) )
  {
    chCfg.enableInt = true;
  }
  else
  {
    chCfg.enableInt = false;
  }
  chCfg.select = peripheralSignal;
  chCfg.cb     = &dmaCallBack[ channelId ];
  DMA_CfgChannel( channelId, &chCfg );

  /* Setup channel descriptor. */
  if ( direction == dmaDirectionMemToPeripheral )
  {
    if ( bufInc )
    {
      if ( size == dmadrvDataSize1 )
      {
        descrCfg.srcInc = dmaDataInc1;
      }
      else if ( size == dmadrvDataSize2 )
      {
        descrCfg.srcInc = dmaDataInc2;
      }
      else /* dmadrvDataSize4 */
      {
        descrCfg.srcInc = dmaDataInc4;
      }
    }
    else
    {
      descrCfg.srcInc = dmaDataIncNone;
    }
    descrCfg.dstInc = dmaDataIncNone;
  }
  else
  {
    if ( bufInc )
    {
      if ( size == dmadrvDataSize1 )
      {
        descrCfg.dstInc = dmaDataInc1;
      }
      else if ( size == dmadrvDataSize2 )
      {
        descrCfg.dstInc = dmaDataInc2;
      }
      else /* dmadrvDataSize4 */
      {
        descrCfg.dstInc = dmaDataInc4;
      }
    }
    else
    {
      descrCfg.dstInc = dmaDataIncNone;
    }
    descrCfg.srcInc = dmaDataIncNone;
  }
  descrCfg.size    = (DMA_DataSize_TypeDef)size;
  descrCfg.arbRate = dmaArbitrate1;
  descrCfg.hprot   = 0;
  DMA_CfgDescr( channelId, true, &descrCfg );
  if ( mode == dmaModePingPong )
  {
    DMA_CfgDescr( channelId, false, &descrCfg );
  }

  ch->callback      = callback;
  ch->userParam     = cbUserParam;
  ch->callbackCount = 0;
  ch->length        = len;

  DMA->IFC = 1 << channelId;

  /* Start DMA cycle. */
  if ( mode == dmaModeBasic )
  {
    DMA_ActivateBasic( channelId, true, false, buf0, buf1, len - 1 );
  }
  else
  {
    if ( direction == dmaDirectionMemToPeripheral )
    {
      DMA_ActivatePingPong( channelId,
                            false,
                            buf0,                             /* dest */
                            buf1,                             /* src  */
                            len - 1,
                            buf0,                             /* dest */
                            buf2,                             /* src  */
                            len - 1);
    }
    else
    {
      DMA_ActivatePingPong( channelId,
                            false,
                            buf0,                             /* dest */
                            buf2,                             /* src  */
                            len - 1,
                            buf1,                             /* dest */
                            buf2,                             /* src  */
                            len - 1);
    }
  }

  return ECODE_EMDRV_DMADRV_OK;
}
#endif /* defined( EMDRV_DMADRV_UDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API ) */

#if defined( EMDRV_DMADRV_LDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API )
/***************************************************************************//**
 * @brief
 *  Start a LDMA transfer.
 ******************************************************************************/
static Ecode_t StartTransfer( DmaMode_t             mode,
                              DmaDirection_t        direction,
                              unsigned int          channelId,
                              DMADRV_PeripheralSignal_t
                                                    peripheralSignal,
                              void                  *buf0,
                              void                  *buf1,
                              void                  *buf2,
                              bool                  bufInc,
                              int                   len,
                              DMADRV_DataSize_t     size,
                              DMADRV_Callback_t     callback,
                              void                  *cbUserParam )
{
  ChTable_t *ch;
  LDMA_TransferCfg_t xfer;
  LDMA_Descriptor_t *desc;

  if ( !initialized )
  {
    return ECODE_EMDRV_DMADRV_NOT_INITIALIZED;
  }

  if ( ( channelId >= EMDRV_DMADRV_DMA_CH_COUNT )
       || ( buf0 == NULL )
       || ( buf1 == NULL )
       || ( len > DMADRV_MAX_XFER_COUNT )
       || ( ( mode == dmaModePingPong ) && ( buf2 == NULL ) ) )
  {
    return ECODE_EMDRV_DMADRV_PARAM_ERROR;
  }

  ch = &chTable[ channelId ];
  if ( ch->allocated == false )
  {
    return ECODE_EMDRV_DMADRV_CH_NOT_ALLOCATED;
  }

  xfer = xferCfg;
  desc = &dmaXfer[ channelId ].desc[0];

  if ( direction == dmaDirectionMemToPeripheral )
  {
    *desc = m2p;
    if ( !bufInc )
    {
      desc->xfer.srcInc = ldmaCtrlSrcIncNone;
    }
  }
  else
  {
    *desc = p2m;
    if ( !bufInc )
    {
      desc->xfer.dstInc = ldmaCtrlDstIncNone;
    }
  }
  xfer.ldmaReqSel    = peripheralSignal;
  desc->xfer.xferCnt = len - 1;
  desc->xfer.dstAddr = (uint32_t)buf0;
  desc->xfer.srcAddr = (uint32_t)buf1;
  desc->xfer.size    = size;

  if ( mode == dmaModePingPong )
  {
    desc->xfer.linkMode = ldmaLinkModeRel;
    desc->xfer.link     = 1;
    desc->xfer.linkAddr = 4;      /* Refer to "pong" descriptor. */

    /* Set the "pong" descriptor equal to the "ping" descriptor. */
    dmaXfer[ channelId ].desc[1] = *desc;
    /* Refer to "ping" descriptor. */
    dmaXfer[ channelId ].desc[1].xfer.linkAddr = -4;
    dmaXfer[ channelId ].desc[1].xfer.srcAddr = (uint32_t)buf2;

    if ( direction == dmaDirectionPeripheralToMem )
    {
      dmaXfer[ channelId ].desc[1].xfer.dstAddr = (uint32_t)buf1;
      desc->xfer.srcAddr = (uint32_t)buf2;
    }
  }

  /* Interrupt needed ? */
  if ( ( callback == NULL ) && ( mode == dmaModeBasic ) )
  {
    desc->xfer.doneIfs = 0;
  }

  ch->callback      = callback;
  ch->userParam     = cbUserParam;
  ch->callbackCount = 0;
  ch->mode          = mode;

  LDMA_StartTransfer( channelId, &xfer, desc );

  return ECODE_EMDRV_DMADRV_OK;
}
#endif /* defined( EMDRV_DMADRV_LDMA ) && !defined( EMDRV_DMADRV_USE_NATIVE_API ) */

/// @endcond


/******** THE REST OF THE FILE IS DOCUMENTATION ONLY !**********************//**
 * @addtogroup emdrv
 * @{
 * @addtogroup DMADRV
 * @brief DMADRV Direct Memory Access Driver
 * @{

@details

  @li @ref dmadrv_intro
  @li @ref dmadrv_conf
  @li @ref dmadrv_api
  @li @ref dmadrv_example

@n @section dmadrv_intro Introduction

  The DMADRV driver makes it possible to write code using DMA which will work
  regardless of the type of DMA controller on the underlying microcontroller.
  It will also make it possible to use DMA in several modules, without the
  modules knowing of each others existence.
  The driver does not preclude use of the native emlib API of the underlying
  DMA controller, on the contrary, this will often result in more efficient
  code and is a necessity when doing complex DMA operations. The housekeeping
  functions of this driver will be valuable even in this use-case.

  The source files for the DMA driver library resides in the
  emdrv/dmadrv folder, and are named dmadrv.c and dmadrv.h.

  @note DMA transfer completion callback functions are called from within the
  DMA interrupt handler.

@n @section dmadrv_conf Configuration Options

  Some properties of the DMADRV driver are compile-time configurable. These
  properties are stored in a file named @ref dmadrv_config.h. A template for this
  file, containing default values, resides in the emdrv/config folder.
  Currently the configuration options are:
  @li The interrupt priority of the DMA peripheral.
  @li Number of DMA channels to support.
  @li Use the native emlib API belonging to the underlying DMA hardware in
      combination with the DMADRV API.

  Both configuration options will help reduce the drivers ram memory footprint.

  To configure DMADRV, provide your own configuration file. Here is a
  sample @ref dmadrv_config.h file:
  @verbatim
#ifndef __SILICON_LABS_DMADRV_CONFIG_H__
#define __SILICON_LABS_DMADRV_CONFIG_H__

// DMADRV DMA interrupt priority configuration option.
// Set DMA interrupt priority. Range is 0..7, 0 is highest priority.
#define EMDRV_DMADRV_DMA_IRQ_PRIORITY 4

// DMADRV channel count configuration option.
// Number of DMA channels to support. A lower DMA channel count will reduce
// ram memory footprint.
#define EMDRV_DMADRV_DMA_CH_COUNT 4

// DMADRV native API configuration option.
// Use the native emlib api of the DMA controller, but still use DMADRV
// housekeeping functions as AllocateChannel/FreeChannel etc.
#define EMDRV_DMADRV_USE_NATIVE_API

#endif
  @endverbatim

@n @section dmadrv_api The API

  This section contain brief descriptions of the functions in the API. You will
  find detailed information on input and output parameters and return values by
  clicking on the hyperlinked function names. Most functions return an error
  code, @ref ECODE_EMDRV_DMADRV_OK is returned on success,
  see @ref ecode.h and @ref dmadrv.h for other error codes.

  Your application code must include one header file: @em dmadrv.h.

  @ref DMADRV_Init(), @ref DMADRV_DeInit() @n
    These functions initializes or deinitializes the DMADRV driver. Typically
    @htmlonly DMADRV_Init() @endhtmlonly is called once in your startup code.

  @ref DMADRV_AllocateChannel(), @ref DMADRV_FreeChannel() @n
    DMA channel reserve and release functions. It is recommended that
    application code check that @htmlonly DMADRV_AllocateChannel() @endhtmlonly
    returns @htmlonly ECODE_EMDRV_DMADRV_OK @endhtmlonly before starting a DMA
    transfer.

  @ref DMADRV_MemoryPeripheral() @n
    Start a DMA transfer from memory to a peripheral.

  @ref DMADRV_PeripheralMemory() @n
    Start a DMA transfer from a peripheral to memory.

  @ref DMADRV_MemoryPeripheralPingPong() @n
    Start a DMA ping-pong transfer from memory to a peripheral.

  @ref DMADRV_PeripheralMemoryPingPong() @n
    Start a DMA ping-pong transfer from a peripheral to memory.

  @ref DMADRV_LdmaStartTransfer() @n
    Start a DMA transfer on a LDMA controller. This function can only be used
    when configuration option @ref EMDRV_DMADRV_USE_NATIVE_API is defined.
    It is a wrapper around similar emlib ldma function, but adds support for
    completion callback and user defined callback function parameter.

  @ref DMADRV_StopTransfer() @n
    Stop an ongoing DMA transfer.

  @ref DMADRV_TransferActive() @n
    Check if a transfer is ongoing.

  @ref DMADRV_TransferCompletePending() @n
    Check if a transfer completion is pending.

  @ref DMADRV_TransferDone() @n
    Check if a transfer has completed.

  @ref DMADRV_TransferRemainingCount() @n
    Get number of items remaining in a transfer.

@n @section dmadrv_example Example
  Transfer a text string to USART1.
  @verbatim
#include "dmadrv.h"

char str[] = "Hello DMA !";
unsigned int channel;

int main( void )
{
  // Initialize DMA.
  DMADRV_Init();

  // Request a DMA channel.
  DMADRV_AllocateChannel( &channel, NULL );

  // Start the DMA transfer.
  DMADRV_MemoryPeripheral( channel,
                           dmadrvPeripheralSignal_USART1_TXBL,
                           (void*)&(USART1->TXDATA),
                           str,
                           true,
                           sizeof( str ),
                           dmadrvDataSize1,
                           NULL,
                           NULL );

  return 0;
}
  @endverbatim

 * @} end group DMADRV ********************************************************
 * @} end group emdrv ****************************************************/
