# -*- coding: utf-8 -*-
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with
# remotemcu.com (remcu@remotemcu.com)
#
# It is python header file for using REMCU library
#
#
# word size : 32 bit
#
#


import ctypes



__version__ = "V1.5.0-af642d23"
__RUN = 0
__HALT = 1
__ERROR = 0
__WARNING = 1
__INFO = 2
__DEBUG = 3
__ALL_LOG = 4
DEFAULT_OPENOCD_PORT = 6666
DEFAULT_GDB_PORT = 3333
# file stm32f0xx_exti.h : 

# Enum EXTIMode_TypeDef
EXTI_Mode_Interrupt = 0x0
EXTI_Mode_Event = 0x4
# Enum EXTITrigger_TypeDef
EXTI_Trigger_Rising = 0x8
EXTI_Trigger_Falling = 0xC
EXTI_Trigger_Rising_Falling = 0x10
# empty define __STM32F0XX_EXTI_H
EXTI_Line0 = 0x1
EXTI_Line1 = 0x2
EXTI_Line2 = 0x4
EXTI_Line3 = 0x8
EXTI_Line4 = 0x10
EXTI_Line5 = 0x20
EXTI_Line6 = 0x40
EXTI_Line7 = 0x80
EXTI_Line8 = 0x100
EXTI_Line9 = 0x200
EXTI_Line10 = 0x400
EXTI_Line11 = 0x800
EXTI_Line12 = 0x1000
EXTI_Line13 = 0x2000
EXTI_Line14 = 0x4000
EXTI_Line15 = 0x8000
EXTI_Line16 = 0x10000
EXTI_Line17 = 0x20000
EXTI_Line18 = 0x40000
EXTI_Line19 = 0x80000
EXTI_Line20 = 0x100000
EXTI_Line21 = 0x200000
EXTI_Line22 = 0x400000
EXTI_Line23 = 0x800000
EXTI_Line25 = 0x2000000
EXTI_Line26 = 0x4000000
EXTI_Line27 = 0x8000000
EXTI_Line31 = 0x80000000
# struct EXTI_InitTypeDef

class EXTI_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('EXTI_Line',	ctypes.c_uint32),
		('EXTI_Mode',	ctypes.c_uint32),
		('EXTI_Trigger',	ctypes.c_uint32),
		('EXTI_LineCmd',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_adc.h : 

# empty define __STM32F0XX_ADC_H
ADC_JitterOff_PCLKDiv2 = 0x40000000
ADC_JitterOff_PCLKDiv4 = 0x80000000
ADC_ClockMode_AsynClk = 0x0
ADC_ClockMode_SynClkDiv2 = 0x40000000
ADC_ClockMode_SynClkDiv4 = 0x80000000
ADC_Resolution_12b = 0x0
ADC_Resolution_10b = 0x8
ADC_Resolution_8b = 0x10
ADC_Resolution_6b = 0x18
ADC_ExternalTrigConvEdge_None = 0x0
ADC_ExternalTrigConvEdge_Rising = 0x400
ADC_ExternalTrigConvEdge_Falling = 0x800
ADC_ExternalTrigConvEdge_RisingFalling = 0xC00
ADC_ExternalTrigConv_T1_TRGO = 0x0
ADC_ExternalTrigConv_T1_CC4 = 0x40
ADC_ExternalTrigConv_T2_TRGO = 0x80
ADC_ExternalTrigConv_T3_TRGO = 0xC0
ADC_ExternalTrigConv_T15_TRGO = 0x100
ADC_DataAlign_Right = 0x0
ADC_DataAlign_Left = 0x20
ADC_ScanDirection_Upward = 0x0
ADC_ScanDirection_Backward = 0x4
ADC_DMAMode_OneShot = 0x0
ADC_DMAMode_Circular = 0x2
ADC_AnalogWatchdog_Channel_0 = 0x0
ADC_AnalogWatchdog_Channel_1 = 0x4000000
ADC_AnalogWatchdog_Channel_2 = 0x8000000
ADC_AnalogWatchdog_Channel_3 = 0xC000000
ADC_AnalogWatchdog_Channel_4 = 0x10000000
ADC_AnalogWatchdog_Channel_5 = 0x14000000
ADC_AnalogWatchdog_Channel_6 = 0x18000000
ADC_AnalogWatchdog_Channel_7 = 0x1C000000
ADC_AnalogWatchdog_Channel_8 = 0x20000000
ADC_AnalogWatchdog_Channel_9 = 0x24000000
ADC_AnalogWatchdog_Channel_10 = 0x28000000
ADC_AnalogWatchdog_Channel_11 = 0x2C000000
ADC_AnalogWatchdog_Channel_12 = 0x30000000
ADC_AnalogWatchdog_Channel_13 = 0x34000000
ADC_AnalogWatchdog_Channel_14 = 0x38000000
ADC_AnalogWatchdog_Channel_15 = 0x3C000000
ADC_AnalogWatchdog_Channel_16 = 0x40000000
ADC_AnalogWatchdog_Channel_17 = 0x44000000
ADC_AnalogWatchdog_Channel_18 = 0x48000000
ADC_SampleTime_1_5Cycles = 0x0
ADC_SampleTime_7_5Cycles = 0x1
ADC_SampleTime_13_5Cycles = 0x2
ADC_SampleTime_28_5Cycles = 0x3
ADC_SampleTime_41_5Cycles = 0x4
ADC_SampleTime_55_5Cycles = 0x5
ADC_SampleTime_71_5Cycles = 0x6
ADC_SampleTime_239_5Cycles = 0x7
ADC_Channel_0 = 0x1
ADC_Channel_1 = 0x2
ADC_Channel_2 = 0x4
ADC_Channel_3 = 0x8
ADC_Channel_4 = 0x10
ADC_Channel_5 = 0x20
ADC_Channel_6 = 0x40
ADC_Channel_7 = 0x80
ADC_Channel_8 = 0x100
ADC_Channel_9 = 0x200
ADC_Channel_10 = 0x400
ADC_Channel_11 = 0x800
ADC_Channel_12 = 0x1000
ADC_Channel_13 = 0x2000
ADC_Channel_14 = 0x4000
ADC_Channel_15 = 0x8000
ADC_Channel_16 = 0x10000
ADC_Channel_17 = 0x20000
ADC_Channel_18 = 0x40000
ADC_Channel_TempSensor = 0x10000
ADC_Channel_Vrefint = 0x20000
ADC_Channel_Vbat = 0x40000
ADC_IT_ADRDY = 0x1
ADC_IT_EOSMP = 0x2
ADC_IT_EOC = 0x4
ADC_IT_EOSEQ = 0x8
ADC_IT_OVR = 0x10
ADC_IT_AWD = 0x80
ADC_FLAG_ADRDY = 0x1
ADC_FLAG_EOSMP = 0x2
ADC_FLAG_EOC = 0x4
ADC_FLAG_EOSEQ = 0x8
ADC_FLAG_OVR = 0x10
ADC_FLAG_AWD = 0x80
ADC_FLAG_ADEN = 0x1000001
ADC_FLAG_ADDIS = 0x1000002
ADC_FLAG_ADSTART = 0x1000004
ADC_FLAG_ADSTP = 0x1000010
ADC_FLAG_ADCAL = 0x81000000
# struct ADC_InitTypeDef

class ADC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_Resolution',	ctypes.c_uint32),
		('ADC_ContinuousConvMode',	ctypes.c_uint32),
		('ADC_ExternalTrigConvEdge',	ctypes.c_uint32),
		('ADC_ExternalTrigConv',	ctypes.c_uint32),
		('ADC_DataAlign',	ctypes.c_uint32),
		('ADC_ScanDirection',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_spi.h : 

# empty define __STM32F0XX_SPI_H
SPI_Direction_2Lines_FullDuplex = 0x0
SPI_Direction_2Lines_RxOnly = 0x400
SPI_Direction_1Line_Rx = 0x8000
SPI_Direction_1Line_Tx = 0xC000
SPI_Mode_Master = 0x104
SPI_Mode_Slave = 0x0
SPI_DataSize_4b = 0x300
SPI_DataSize_5b = 0x400
SPI_DataSize_6b = 0x500
SPI_DataSize_7b = 0x600
SPI_DataSize_8b = 0x700
SPI_DataSize_9b = 0x800
SPI_DataSize_10b = 0x900
SPI_DataSize_11b = 0xA00
SPI_DataSize_12b = 0xB00
SPI_DataSize_13b = 0xC00
SPI_DataSize_14b = 0xD00
SPI_DataSize_15b = 0xE00
SPI_DataSize_16b = 0xF00
SPI_CRCLength_8b = 0x0
SPI_CRCLength_16b = 0x800
SPI_CPOL_Low = 0x0
SPI_CPOL_High = 0x2
SPI_CPHA_1Edge = 0x0
SPI_CPHA_2Edge = 0x1
SPI_NSS_Soft = 0x200
SPI_NSS_Hard = 0x0
SPI_BaudRatePrescaler_2 = 0x0
SPI_BaudRatePrescaler_4 = 0x8
SPI_BaudRatePrescaler_8 = 0x10
SPI_BaudRatePrescaler_16 = 0x18
SPI_BaudRatePrescaler_32 = 0x20
SPI_BaudRatePrescaler_64 = 0x28
SPI_BaudRatePrescaler_128 = 0x30
SPI_BaudRatePrescaler_256 = 0x38
SPI_FirstBit_MSB = 0x0
SPI_FirstBit_LSB = 0x80
I2S_Mode_SlaveTx = 0x0
I2S_Mode_SlaveRx = 0x100
I2S_Mode_MasterTx = 0x200
I2S_Mode_MasterRx = 0x300
I2S_Standard_Phillips = 0x0
I2S_Standard_MSB = 0x10
I2S_Standard_LSB = 0x20
I2S_Standard_PCMShort = 0x30
I2S_Standard_PCMLong = 0xB0
I2S_DataFormat_16b = 0x0
I2S_DataFormat_16bextended = 0x1
I2S_DataFormat_24b = 0x3
I2S_DataFormat_32b = 0x5
I2S_MCLKOutput_Enable = 0x200
I2S_MCLKOutput_Disable = 0x0
I2S_AudioFreq_192k = 0x2EE00
I2S_AudioFreq_96k = 0x17700
I2S_AudioFreq_48k = 0xBB80
I2S_AudioFreq_44k = 0xAC44
I2S_AudioFreq_32k = 0x7D00
I2S_AudioFreq_22k = 0x5622
I2S_AudioFreq_16k = 0x3E80
I2S_AudioFreq_11k = 0x2B11
I2S_AudioFreq_8k = 0x1F40
I2S_AudioFreq_Default = 0x2
I2S_CPOL_Low = 0x0
I2S_CPOL_High = 0x8
SPI_RxFIFOThreshold_HF = 0x0
SPI_RxFIFOThreshold_QF = 0x1000
SPI_I2S_DMAReq_Tx = 0x2
SPI_I2S_DMAReq_Rx = 0x1
SPI_LastDMATransfer_TxEvenRxEven = 0x0
SPI_LastDMATransfer_TxOddRxEven = 0x4000
SPI_LastDMATransfer_TxEvenRxOdd = 0x2000
SPI_LastDMATransfer_TxOddRxOdd = 0x6000
SPI_NSSInternalSoft_Set = 0x100
SPI_NSSInternalSoft_Reset = 0xFEFF
SPI_CRC_Tx = 0x0
SPI_CRC_Rx = 0x1
SPI_Direction_Rx = 0xBFFF
SPI_Direction_Tx = 0x4000
SPI_I2S_IT_TXE = 0x71
SPI_I2S_IT_RXNE = 0x60
SPI_I2S_IT_ERR = 0x50
I2S_IT_UDR = 0x53
SPI_IT_MODF = 0x55
SPI_I2S_IT_OVR = 0x56
SPI_I2S_IT_FRE = 0x58
SPI_TransmissionFIFOStatus_Empty = 0x0
SPI_TransmissionFIFOStatus_1QuarterFull = 0x800
SPI_TransmissionFIFOStatus_HalfFull = 0x1000
SPI_TransmissionFIFOStatus_Full = 0x1800
SPI_ReceptionFIFOStatus_Empty = 0x0
SPI_ReceptionFIFOStatus_1QuarterFull = 0x200
SPI_ReceptionFIFOStatus_HalfFull = 0x400
SPI_ReceptionFIFOStatus_Full = 0x600
SPI_I2S_FLAG_RXNE = 0x1
SPI_I2S_FLAG_TXE = 0x2
I2S_FLAG_CHSIDE = 0x4
I2S_FLAG_UDR = 0x8
SPI_FLAG_CRCERR = 0x10
SPI_FLAG_MODF = 0x20
SPI_I2S_FLAG_OVR = 0x40
SPI_I2S_FLAG_BSY = 0x80
SPI_I2S_FLAG_FRE = 0x100
# struct SPI_InitTypeDef

class SPI_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SPI_Direction',	ctypes.c_uint16),
		('SPI_Mode',	ctypes.c_uint16),
		('SPI_DataSize',	ctypes.c_uint16),
		('SPI_CPOL',	ctypes.c_uint16),
		('SPI_CPHA',	ctypes.c_uint16),
		('SPI_NSS',	ctypes.c_uint16),
		('SPI_BaudRatePrescaler',	ctypes.c_uint16),
		('SPI_FirstBit',	ctypes.c_uint16),
		('SPI_CRCPolynomial',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct I2S_InitTypeDef

class I2S_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('I2S_Mode',	ctypes.c_uint16),
		('I2S_Standard',	ctypes.c_uint16),
		('I2S_DataFormat',	ctypes.c_uint16),
		('I2S_MCLKOutput',	ctypes.c_uint16),
		('I2S_AudioFreq',	ctypes.c_uint32),
		('I2S_CPOL',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_iwdg.h : 

# empty define __STM32F0XX_IWDG_H
IWDG_WriteAccess_Enable = 0x5555
IWDG_WriteAccess_Disable = 0x0
IWDG_Prescaler_4 = 0x0
IWDG_Prescaler_8 = 0x1
IWDG_Prescaler_16 = 0x2
IWDG_Prescaler_32 = 0x3
IWDG_Prescaler_64 = 0x4
IWDG_Prescaler_128 = 0x5
IWDG_Prescaler_256 = 0x6
IWDG_FLAG_PVU = 0x1
IWDG_FLAG_RVU = 0x2
IWDG_FLAG_WVU = 0x4
# ----------------------------------------

# file stm32f0xx_crc.h : 

# empty define __STM32F0XX_CRC_H
CRC_ReverseInputData_No = 0x0
CRC_ReverseInputData_8bits = 0x20
CRC_ReverseInputData_16bits = 0x40
CRC_ReverseInputData_32bits = 0x60
CRC_PolSize_7 = 0x18
CRC_PolSize_8 = 0x10
CRC_PolSize_16 = 0x8
CRC_PolSize_32 = 0x0
# ----------------------------------------

# file stm32f0xx_tim.h : 

# empty define __STM32F0XX_TIM_H
TIM_OCMode_Timing = 0x0
TIM_OCMode_Active = 0x10
TIM_OCMode_Inactive = 0x20
TIM_OCMode_Toggle = 0x30
TIM_OCMode_PWM1 = 0x60
TIM_OCMode_PWM2 = 0x70
TIM_OPMode_Single = 0x8
TIM_OPMode_Repetitive = 0x0
TIM_Channel_1 = 0x0
TIM_Channel_2 = 0x4
TIM_Channel_3 = 0x8
TIM_Channel_4 = 0xC
TIM_CKD_DIV1 = 0x0
TIM_CKD_DIV2 = 0x100
TIM_CKD_DIV4 = 0x200
TIM_CounterMode_Up = 0x0
TIM_CounterMode_Down = 0x10
TIM_CounterMode_CenterAligned1 = 0x20
TIM_CounterMode_CenterAligned2 = 0x40
TIM_CounterMode_CenterAligned3 = 0x60
TIM_OCPolarity_High = 0x0
TIM_OCPolarity_Low = 0x2
TIM_OCNPolarity_High = 0x0
TIM_OCNPolarity_Low = 0x8
TIM_OutputState_Disable = 0x0
TIM_OutputState_Enable = 0x1
TIM_OutputNState_Disable = 0x0
TIM_OutputNState_Enable = 0x4
TIM_CCx_Enable = 0x1
TIM_CCx_Disable = 0x0
TIM_CCxN_Enable = 0x4
TIM_CCxN_Disable = 0x0
TIM_Break_Enable = 0x1000
TIM_Break_Disable = 0x0
TIM_BreakPolarity_Low = 0x0
TIM_BreakPolarity_High = 0x2000
TIM_AutomaticOutput_Enable = 0x4000
TIM_AutomaticOutput_Disable = 0x0
TIM_LOCKLevel_OFF = 0x0
TIM_LOCKLevel_1 = 0x100
TIM_LOCKLevel_2 = 0x200
TIM_LOCKLevel_3 = 0x300
TIM_OSSIState_Enable = 0x400
TIM_OSSIState_Disable = 0x0
TIM_OSSRState_Enable = 0x800
TIM_OSSRState_Disable = 0x0
TIM_OCIdleState_Set = 0x100
TIM_OCIdleState_Reset = 0x0
TIM_OCNIdleState_Set = 0x200
TIM_OCNIdleState_Reset = 0x0
TIM_ICPolarity_Rising = 0x0
TIM_ICPolarity_Falling = 0x2
TIM_ICPolarity_BothEdge = 0xA
TIM_ICSelection_DirectTI = 0x1
TIM_ICSelection_IndirectTI = 0x2
TIM_ICSelection_TRC = 0x3
TIM_ICPSC_DIV1 = 0x0
TIM_ICPSC_DIV2 = 0x4
TIM_ICPSC_DIV4 = 0x8
TIM_ICPSC_DIV8 = 0xC
TIM_IT_Update = 0x1
TIM_IT_CC1 = 0x2
TIM_IT_CC2 = 0x4
TIM_IT_CC3 = 0x8
TIM_IT_CC4 = 0x10
TIM_IT_COM = 0x20
TIM_IT_Trigger = 0x40
TIM_IT_Break = 0x80
TIM_DMABase_CR1 = 0x0
TIM_DMABase_CR2 = 0x1
TIM_DMABase_SMCR = 0x2
TIM_DMABase_DIER = 0x3
TIM_DMABase_SR = 0x4
TIM_DMABase_EGR = 0x5
TIM_DMABase_CCMR1 = 0x6
TIM_DMABase_CCMR2 = 0x7
TIM_DMABase_CCER = 0x8
TIM_DMABase_CNT = 0x9
TIM_DMABase_PSC = 0xA
TIM_DMABase_ARR = 0xB
TIM_DMABase_RCR = 0xC
TIM_DMABase_CCR1 = 0xD
TIM_DMABase_CCR2 = 0xE
TIM_DMABase_CCR3 = 0xF
TIM_DMABase_CCR4 = 0x10
TIM_DMABase_BDTR = 0x11
TIM_DMABase_DCR = 0x12
TIM_DMABase_OR = 0x13
TIM_DMABurstLength_1Transfer = 0x0
TIM_DMABurstLength_2Transfers = 0x100
TIM_DMABurstLength_3Transfers = 0x200
TIM_DMABurstLength_4Transfers = 0x300
TIM_DMABurstLength_5Transfers = 0x400
TIM_DMABurstLength_6Transfers = 0x500
TIM_DMABurstLength_7Transfers = 0x600
TIM_DMABurstLength_8Transfers = 0x700
TIM_DMABurstLength_9Transfers = 0x800
TIM_DMABurstLength_10Transfers = 0x900
TIM_DMABurstLength_11Transfers = 0xA00
TIM_DMABurstLength_12Transfers = 0xB00
TIM_DMABurstLength_13Transfers = 0xC00
TIM_DMABurstLength_14Transfers = 0xD00
TIM_DMABurstLength_15Transfers = 0xE00
TIM_DMABurstLength_16Transfers = 0xF00
TIM_DMABurstLength_17Transfers = 0x1000
TIM_DMABurstLength_18Transfers = 0x1100
TIM_DMA_Update = 0x100
TIM_DMA_CC1 = 0x200
TIM_DMA_CC2 = 0x400
TIM_DMA_CC3 = 0x800
TIM_DMA_CC4 = 0x1000
TIM_DMA_COM = 0x2000
TIM_DMA_Trigger = 0x4000
TIM_ExtTRGPSC_OFF = 0x0
TIM_ExtTRGPSC_DIV2 = 0x1000
TIM_ExtTRGPSC_DIV4 = 0x2000
TIM_ExtTRGPSC_DIV8 = 0x3000
TIM_TS_ITR0 = 0x0
TIM_TS_ITR1 = 0x10
TIM_TS_ITR2 = 0x20
TIM_TS_ITR3 = 0x30
TIM_TS_TI1F_ED = 0x40
TIM_TS_TI1FP1 = 0x50
TIM_TS_TI2FP2 = 0x60
TIM_TS_ETRF = 0x70
TIM_TIxExternalCLK1Source_TI1 = 0x50
TIM_TIxExternalCLK1Source_TI2 = 0x60
TIM_TIxExternalCLK1Source_TI1ED = 0x40
TIM_ExtTRGPolarity_Inverted = 0x8000
TIM_ExtTRGPolarity_NonInverted = 0x0
TIM_PSCReloadMode_Update = 0x0
TIM_PSCReloadMode_Immediate = 0x1
TIM_ForcedAction_Active = 0x50
TIM_ForcedAction_InActive = 0x40
TIM_EncoderMode_TI1 = 0x1
TIM_EncoderMode_TI2 = 0x2
TIM_EncoderMode_TI12 = 0x3
TIM_EventSource_Update = 0x1
TIM_EventSource_CC1 = 0x2
TIM_EventSource_CC2 = 0x4
TIM_EventSource_CC3 = 0x8
TIM_EventSource_CC4 = 0x10
TIM_EventSource_COM = 0x20
TIM_EventSource_Trigger = 0x40
TIM_EventSource_Break = 0x80
TIM_UpdateSource_Global = 0x0
TIM_UpdateSource_Regular = 0x1
TIM_OCPreload_Enable = 0x8
TIM_OCPreload_Disable = 0x0
TIM_OCFast_Enable = 0x4
TIM_OCFast_Disable = 0x0
TIM_OCClear_Enable = 0x80
TIM_OCClear_Disable = 0x0
TIM_TRGOSource_Reset = 0x0
TIM_TRGOSource_Enable = 0x10
TIM_TRGOSource_Update = 0x20
TIM_TRGOSource_OC1 = 0x30
TIM_TRGOSource_OC1Ref = 0x40
TIM_TRGOSource_OC2Ref = 0x50
TIM_TRGOSource_OC3Ref = 0x60
TIM_TRGOSource_OC4Ref = 0x70
TIM_SlaveMode_Reset = 0x4
TIM_SlaveMode_Gated = 0x5
TIM_SlaveMode_Trigger = 0x6
TIM_SlaveMode_External1 = 0x7
TIM_MasterSlaveMode_Enable = 0x80
TIM_MasterSlaveMode_Disable = 0x0
TIM_FLAG_Update = 0x1
TIM_FLAG_CC1 = 0x2
TIM_FLAG_CC2 = 0x4
TIM_FLAG_CC3 = 0x8
TIM_FLAG_CC4 = 0x10
TIM_FLAG_COM = 0x20
TIM_FLAG_Trigger = 0x40
TIM_FLAG_Break = 0x80
TIM_FLAG_CC1OF = 0x200
TIM_FLAG_CC2OF = 0x400
TIM_FLAG_CC3OF = 0x800
TIM_FLAG_CC4OF = 0x1000
TIM_OCReferenceClear_ETRF = 0x8
TIM_OCReferenceClear_OCREFCLR = 0x0
TIM14_GPIO = 0x0
TIM14_RTC_CLK = 0x1
TIM14_HSEDiv32 = 0x2
TIM14_MCO = 0x3
TIM_DMABurstLength_1Byte = 0x0
TIM_DMABurstLength_2Bytes = 0x100
TIM_DMABurstLength_3Bytes = 0x200
TIM_DMABurstLength_4Bytes = 0x300
TIM_DMABurstLength_5Bytes = 0x400
TIM_DMABurstLength_6Bytes = 0x500
TIM_DMABurstLength_7Bytes = 0x600
TIM_DMABurstLength_8Bytes = 0x700
TIM_DMABurstLength_9Bytes = 0x800
TIM_DMABurstLength_10Bytes = 0x900
TIM_DMABurstLength_11Bytes = 0xA00
TIM_DMABurstLength_12Bytes = 0xB00
TIM_DMABurstLength_13Bytes = 0xC00
TIM_DMABurstLength_14Bytes = 0xD00
TIM_DMABurstLength_15Bytes = 0xE00
TIM_DMABurstLength_16Bytes = 0xF00
TIM_DMABurstLength_17Bytes = 0x1000
TIM_DMABurstLength_18Bytes = 0x1100
# struct TIM_TimeBaseInitTypeDef

class TIM_TimeBaseInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TIM_Prescaler',	ctypes.c_uint16),
		('TIM_CounterMode',	ctypes.c_uint16),
		('TIM_Period',	ctypes.c_uint32),
		('TIM_ClockDivision',	ctypes.c_uint16),
		('TIM_RepetitionCounter',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct TIM_OCInitTypeDef

class TIM_OCInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TIM_OCMode',	ctypes.c_uint16),
		('TIM_OutputState',	ctypes.c_uint16),
		('TIM_OutputNState',	ctypes.c_uint16),
		('TIM_Pulse',	ctypes.c_uint32),
		('TIM_OCPolarity',	ctypes.c_uint16),
		('TIM_OCNPolarity',	ctypes.c_uint16),
		('TIM_OCIdleState',	ctypes.c_uint16),
		('TIM_OCNIdleState',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct TIM_ICInitTypeDef

class TIM_ICInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TIM_Channel',	ctypes.c_uint16),
		('TIM_ICPolarity',	ctypes.c_uint16),
		('TIM_ICSelection',	ctypes.c_uint16),
		('TIM_ICPrescaler',	ctypes.c_uint16),
		('TIM_ICFilter',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct TIM_BDTRInitTypeDef

class TIM_BDTRInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TIM_OSSRState',	ctypes.c_uint16),
		('TIM_OSSIState',	ctypes.c_uint16),
		('TIM_LOCKLevel',	ctypes.c_uint16),
		('TIM_DeadTime',	ctypes.c_uint16),
		('TIM_Break',	ctypes.c_uint16),
		('TIM_BreakPolarity',	ctypes.c_uint16),
		('TIM_AutomaticOutput',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_crs.h : 

# empty define __STM32F0XX_CRS_H
CRS_IT_SYNCOK = 0x1
CRS_IT_SYNCWARN = 0x2
CRS_IT_ERR = 0x4
CRS_IT_ESYNC = 0x8
CRS_IT_TRIMOVF = 0x400
CRS_IT_SYNCERR = 0x100
CRS_IT_SYNCMISS = 0x200
CRS_FLAG_SYNCOK = 0x1
CRS_FLAG_SYNCWARN = 0x2
CRS_FLAG_ERR = 0x4
CRS_FLAG_ESYNC = 0x8
CRS_FLAG_TRIMOVF = 0x400
CRS_FLAG_SYNCERR = 0x100
CRS_FLAG_SYNCMISS = 0x200
CRS_SYNCSource_GPIO = 0x0
CRS_SYNCSource_LSE = 0x10000000
CRS_SYNCSource_USB = 0x20000000
CRS_SYNC_Div1 = 0x0
CRS_SYNC_Div2 = 0x1000000
CRS_SYNC_Div4 = 0x2000000
CRS_SYNC_Div8 = 0x3000000
CRS_SYNC_Div16 = 0x4000000
CRS_SYNC_Div32 = 0x5000000
CRS_SYNC_Div64 = 0x6000000
CRS_SYNC_Div128 = 0x7000000
CRS_SYNCPolarity_Rising = 0x0
CRS_SYNCPolarity_Falling = 0x80000000
# ----------------------------------------

# file stm32f0xx_gpio.h : 

# Enum GPIOMode_TypeDef
GPIO_Mode_IN = 0x0
GPIO_Mode_OUT = 0x1
GPIO_Mode_AF = 0x2
GPIO_Mode_AN = 0x3
# Enum GPIOOType_TypeDef
GPIO_OType_PP = 0x0
GPIO_OType_OD = 0x1
# Enum GPIOSpeed_TypeDef
GPIO_Speed_Level_1 = 0x0
GPIO_Speed_Level_2 = 0x1
GPIO_Speed_Level_3 = 0x3
# Enum GPIOPuPd_TypeDef
GPIO_PuPd_NOPULL = 0x0
GPIO_PuPd_UP = 0x1
GPIO_PuPd_DOWN = 0x2
# Enum BitAction
Bit_RESET = 0x0
Bit_SET = 0x1
# empty define __STM32F0XX_GPIO_H
GPIO_Pin_0 = 0x1
GPIO_Pin_1 = 0x2
GPIO_Pin_2 = 0x4
GPIO_Pin_3 = 0x8
GPIO_Pin_4 = 0x10
GPIO_Pin_5 = 0x20
GPIO_Pin_6 = 0x40
GPIO_Pin_7 = 0x80
GPIO_Pin_8 = 0x100
GPIO_Pin_9 = 0x200
GPIO_Pin_10 = 0x400
GPIO_Pin_11 = 0x800
GPIO_Pin_12 = 0x1000
GPIO_Pin_13 = 0x2000
GPIO_Pin_14 = 0x4000
GPIO_Pin_15 = 0x8000
GPIO_Pin_All = 0xFFFF
GPIO_PinSource0 = 0x0
GPIO_PinSource1 = 0x1
GPIO_PinSource2 = 0x2
GPIO_PinSource3 = 0x3
GPIO_PinSource4 = 0x4
GPIO_PinSource5 = 0x5
GPIO_PinSource6 = 0x6
GPIO_PinSource7 = 0x7
GPIO_PinSource8 = 0x8
GPIO_PinSource9 = 0x9
GPIO_PinSource10 = 0xA
GPIO_PinSource11 = 0xB
GPIO_PinSource12 = 0xC
GPIO_PinSource13 = 0xD
GPIO_PinSource14 = 0xE
GPIO_PinSource15 = 0xF
GPIO_AF_0 = 0x0
GPIO_AF_1 = 0x1
GPIO_AF_2 = 0x2
GPIO_AF_3 = 0x3
GPIO_AF_4 = 0x4
GPIO_AF_5 = 0x5
GPIO_AF_6 = 0x6
GPIO_AF_7 = 0x7
GPIO_Speed_2MHz = 0x0
GPIO_Speed_10MHz = 0x1
GPIO_Speed_50MHz = 0x3
# struct GPIO_InitTypeDef

class GPIO_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('GPIO_Pin',	ctypes.c_uint32),
		('GPIO_Mode',	ctypes.c_uint32),
		('GPIO_Speed',	ctypes.c_uint32),
		('GPIO_OType',	ctypes.c_uint32),
		('GPIO_PuPd',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_i2c.h : 

# empty define __STM32F0XX_I2C_H
I2C_AnalogFilter_Enable = 0x0
I2C_AnalogFilter_Disable = 0x1000
I2C_Mode_I2C = 0x0
I2C_Mode_SMBusDevice = 0x200000
I2C_Mode_SMBusHost = 0x100000
I2C_Ack_Enable = 0x0
I2C_Ack_Disable = 0x8000
I2C_AcknowledgedAddress_7bit = 0x0
I2C_AcknowledgedAddress_10bit = 0x400
I2C_Direction_Transmitter = 0x0
I2C_Direction_Receiver = 0x400
I2C_DMAReq_Tx = 0x4000
I2C_DMAReq_Rx = 0x8000
I2C_OA2_NoMask = 0x0
I2C_OA2_Mask01 = 0x1
I2C_OA2_Mask02 = 0x2
I2C_OA2_Mask03 = 0x3
I2C_OA2_Mask04 = 0x4
I2C_OA2_Mask05 = 0x5
I2C_OA2_Mask06 = 0x6
I2C_OA2_Mask07 = 0x7
I2C_Register_CR1 = 0x0
I2C_Register_CR2 = 0x4
I2C_Register_OAR1 = 0x8
I2C_Register_OAR2 = 0xC
I2C_Register_TIMINGR = 0x10
I2C_Register_TIMEOUTR = 0x14
I2C_Register_ISR = 0x18
I2C_Register_ICR = 0x1C
I2C_Register_PECR = 0x20
I2C_Register_RXDR = 0x24
I2C_Register_TXDR = 0x28
I2C_IT_ERRI = 0x80
I2C_IT_TCI = 0x40
I2C_IT_STOPI = 0x20
I2C_IT_NACKI = 0x10
I2C_IT_ADDRI = 0x8
I2C_IT_RXI = 0x4
I2C_IT_TXI = 0x2
I2C_FLAG_TXE = 0x1
I2C_FLAG_TXIS = 0x2
I2C_FLAG_RXNE = 0x4
I2C_FLAG_ADDR = 0x8
I2C_FLAG_NACKF = 0x10
I2C_FLAG_STOPF = 0x20
I2C_FLAG_TC = 0x40
I2C_FLAG_TCR = 0x80
I2C_FLAG_BERR = 0x100
I2C_FLAG_ARLO = 0x200
I2C_FLAG_OVR = 0x400
I2C_FLAG_PECERR = 0x800
I2C_FLAG_TIMEOUT = 0x1000
I2C_FLAG_ALERT = 0x2000
I2C_FLAG_BUSY = 0x8000
I2C_IT_TXIS = 0x2
I2C_IT_RXNE = 0x4
I2C_IT_ADDR = 0x8
I2C_IT_NACKF = 0x10
I2C_IT_STOPF = 0x20
I2C_IT_TC = 0x40
I2C_IT_TCR = 0x80
I2C_IT_BERR = 0x100
I2C_IT_ARLO = 0x200
I2C_IT_OVR = 0x400
I2C_IT_PECERR = 0x800
I2C_IT_TIMEOUT = 0x1000
I2C_IT_ALERT = 0x2000
I2C_Reload_Mode = 0x1000000
I2C_AutoEnd_Mode = 0x2000000
I2C_SoftEnd_Mode = 0x0
I2C_No_StartStop = 0x0
I2C_Generate_Stop = 0x4000
I2C_Generate_Start_Read = 0x2400
I2C_Generate_Start_Write = 0x2000
# struct I2C_InitTypeDef

class I2C_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('I2C_Timing',	ctypes.c_uint32),
		('I2C_AnalogFilter',	ctypes.c_uint32),
		('I2C_DigitalFilter',	ctypes.c_uint32),
		('I2C_Mode',	ctypes.c_uint32),
		('I2C_OwnAddress1',	ctypes.c_uint32),
		('I2C_Ack',	ctypes.c_uint32),
		('I2C_AcknowledgedAddress',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_syscfg.h : 

# empty define __STM32F0XX_SYSCFG_H
EXTI_PortSourceGPIOA = 0x0
EXTI_PortSourceGPIOB = 0x1
EXTI_PortSourceGPIOC = 0x2
EXTI_PortSourceGPIOD = 0x3
EXTI_PortSourceGPIOE = 0x4
EXTI_PortSourceGPIOF = 0x5
EXTI_PinSource0 = 0x0
EXTI_PinSource1 = 0x1
EXTI_PinSource2 = 0x2
EXTI_PinSource3 = 0x3
EXTI_PinSource4 = 0x4
EXTI_PinSource5 = 0x5
EXTI_PinSource6 = 0x6
EXTI_PinSource7 = 0x7
EXTI_PinSource8 = 0x8
EXTI_PinSource9 = 0x9
EXTI_PinSource10 = 0xA
EXTI_PinSource11 = 0xB
EXTI_PinSource12 = 0xC
EXTI_PinSource13 = 0xD
EXTI_PinSource14 = 0xE
EXTI_PinSource15 = 0xF
SYSCFG_MemoryRemap_Flash = 0x0
SYSCFG_MemoryRemap_SystemMemory = 0x1
SYSCFG_MemoryRemap_SRAM = 0x3
SYSCFG_DMARemap_TIM3 = 0x40000000
SYSCFG_DMARemap_TIM2 = 0x20000000
SYSCFG_DMARemap_TIM1 = 0x10000000
SYSCFG_DMARemap_I2C1 = 0x8000000
SYSCFG_DMARemap_USART3 = 0x4000000
SYSCFG_DMARemap_USART2 = 0x2000000
SYSCFG_DMARemap_SPI2 = 0x1000000
SYSCFG_DMARemap_TIM17_2 = 0x4000
SYSCFG_DMARemap_TIM16_2 = 0x2000
SYSCFG_DMARemap_TIM17 = 0x1000
SYSCFG_DMARemap_TIM16 = 0x800
SYSCFG_DMARemap_USART1Rx = 0x400
SYSCFG_DMARemap_USART1Tx = 0x200
SYSCFG_DMARemap_ADC1 = 0x100
SYSCFG_I2CFastModePlus_PB6 = 0x10000
SYSCFG_I2CFastModePlus_PB7 = 0x20000
SYSCFG_I2CFastModePlus_PB8 = 0x40000
SYSCFG_I2CFastModePlus_PB9 = 0x80000
SYSCFG_I2CFastModePlus_I2C1 = 0x100000
SYSCFG_I2CFastModePlus_I2C2 = 0x200000
SYSCFG_I2CFastModePlus_PA9 = 0x400000
SYSCFG_I2CFastModePlus_PA10 = 0x800000
SYSCFG_Break_PVD = 0x4
SYSCFG_Break_SRAMParity = 0x2
SYSCFG_Break_Lockup = 0x1
SYSCFG_FLAG_PE = 0x100
SYSCFG_ITLINE0 = 0x0
SYSCFG_ITLINE1 = 0x1
SYSCFG_ITLINE2 = 0x2
SYSCFG_ITLINE3 = 0x3
SYSCFG_ITLINE4 = 0x4
SYSCFG_ITLINE5 = 0x5
SYSCFG_ITLINE6 = 0x6
SYSCFG_ITLINE7 = 0x7
SYSCFG_ITLINE8 = 0x8
SYSCFG_ITLINE9 = 0x9
SYSCFG_ITLINE10 = 0xA
SYSCFG_ITLINE11 = 0xB
SYSCFG_ITLINE12 = 0xC
SYSCFG_ITLINE13 = 0xD
SYSCFG_ITLINE14 = 0xE
SYSCFG_ITLINE15 = 0xF
SYSCFG_ITLINE16 = 0x10
SYSCFG_ITLINE17 = 0x11
SYSCFG_ITLINE18 = 0x12
SYSCFG_ITLINE19 = 0x13
SYSCFG_ITLINE20 = 0x14
SYSCFG_ITLINE21 = 0x15
SYSCFG_ITLINE22 = 0x16
SYSCFG_ITLINE23 = 0x17
SYSCFG_ITLINE24 = 0x18
SYSCFG_ITLINE25 = 0x19
SYSCFG_ITLINE26 = 0x1A
SYSCFG_ITLINE27 = 0x1B
SYSCFG_ITLINE28 = 0x1C
SYSCFG_ITLINE29 = 0x1D
SYSCFG_ITLINE30 = 0x1E
SYSCFG_ITLINE31 = 0x1F
ITLINE_EWDG = 0x1
ITLINE_PVDOUT = 0x1000001
ITLINE_VDDIO2 = 0x1000002
ITLINE_RTC_WAKEUP = 0x2000001
ITLINE_RTC_TSTAMP = 0x2000002
ITLINE_RTC_ALRA = 0x2000003
ITLINE_FLASH_ITF = 0x3000001
ITLINE_CRS = 0x4000001
ITLINE_CLK_CTRL = 0x4000002
ITLINE_EXTI0 = 0x5000001
ITLINE_EXTI1 = 0x5000002
ITLINE_EXTI2 = 0x6000001
ITLINE_EXTI3 = 0x6000002
ITLINE_EXTI4 = 0x7000001
ITLINE_EXTI5 = 0x7000002
ITLINE_EXTI6 = 0x7000004
ITLINE_EXTI7 = 0x7000008
ITLINE_EXTI8 = 0x7000010
ITLINE_EXTI9 = 0x7000020
ITLINE_EXTI10 = 0x7000040
ITLINE_EXTI11 = 0x7000080
ITLINE_EXTI12 = 0x7000100
ITLINE_EXTI13 = 0x7000200
ITLINE_EXTI14 = 0x7000400
ITLINE_EXTI15 = 0x7000800
ITLINE_TSC_EOA = 0x8000001
ITLINE_TSC_MCE = 0x8000002
ITLINE_DMA1_CH1 = 0x9000001
ITLINE_DMA1_CH2 = 0xA000001
ITLINE_DMA1_CH3 = 0xA000002
ITLINE_DMA2_CH1 = 0xA000004
ITLINE_DMA2_CH2 = 0xA000008
ITLINE_DMA1_CH4 = 0xB000001
ITLINE_DMA1_CH5 = 0xB000002
ITLINE_DMA1_CH6 = 0xB000004
ITLINE_DMA1_CH7 = 0xB000008
ITLINE_DMA2_CH3 = 0xB000010
ITLINE_DMA2_CH4 = 0xB000020
ITLINE_DMA2_CH5 = 0xB000040
ITLINE_ADC = 0xC000001
ITLINE_COMP1 = 0xC000002
ITLINE_COMP2 = 0xC000004
ITLINE_TIM1_BRK = 0xD000001
ITLINE_TIM1_UPD = 0xD000002
ITLINE_TIM1_TRG = 0xD000004
ITLINE_TIM1_CCU = 0xD000008
ITLINE_TIM1_CC = 0xE000001
ITLINE_TIM2 = 0xF000001
ITLINE_TIM3 = 0x10000001
ITLINE_DAC = 0x11000001
ITLINE_TIM6 = 0x11000002
ITLINE_TIM7 = 0x12000001
ITLINE_TIM14 = 0x13000001
ITLINE_TIM15 = 0x14000001
ITLINE_TIM16 = 0x15000001
ITLINE_TIM17 = 0x16000001
ITLINE_I2C1 = 0x17000001
ITLINE_I2C2 = 0x18000001
ITLINE_SPI1 = 0x19000001
ITLINE_SPI2 = 0x1A000001
ITLINE_USART1 = 0x1B000001
ITLINE_USART2 = 0x1C000001
ITLINE_USART3 = 0x1D000001
ITLINE_USART4 = 0x1D000002
ITLINE_USART5 = 0x1D000004
ITLINE_USART6 = 0x1D000008
ITLINE_USART7 = 0x1D000010
ITLINE_USART8 = 0x1D000020
ITLINE_CAN = 0x1E000001
ITLINE_CEC = 0x1E000002
SYSCFG_IRDA_ENV_SEL_TIM16 = 0x0
SYSCFG_IRDA_ENV_SEL_USART1 = 0x40
SYSCFG_IRDA_ENV_SEL_USART4 = 0x80
# ----------------------------------------

# file stm32f0xx_rtc.h : 

# empty define __STM32F0XX_RTC_H
RTC_HourFormat_24 = 0x0
RTC_HourFormat_12 = 0x40
RTC_H12_AM = 0x0
RTC_H12_PM = 0x40
RTC_Month_January = 0x1
RTC_Month_February = 0x2
RTC_Month_March = 0x3
RTC_Month_April = 0x4
RTC_Month_May = 0x5
RTC_Month_June = 0x6
RTC_Month_July = 0x7
RTC_Month_August = 0x8
RTC_Month_September = 0x9
RTC_Month_October = 0x10
RTC_Month_November = 0x11
RTC_Month_December = 0x12
RTC_Weekday_Monday = 0x1
RTC_Weekday_Tuesday = 0x2
RTC_Weekday_Wednesday = 0x3
RTC_Weekday_Thursday = 0x4
RTC_Weekday_Friday = 0x5
RTC_Weekday_Saturday = 0x6
RTC_Weekday_Sunday = 0x7
RTC_AlarmDateWeekDaySel_Date = 0x0
RTC_AlarmDateWeekDaySel_WeekDay = 0x40000000
RTC_AlarmMask_None = 0x0
RTC_AlarmMask_DateWeekDay = 0x80000000
RTC_AlarmMask_Hours = 0x800000
RTC_AlarmMask_Minutes = 0x8000
RTC_AlarmMask_Seconds = 0x80
RTC_AlarmMask_All = 0x80808080
RTC_Alarm_A = 0x100
RTC_AlarmSubSecondMask_All = 0x0
RTC_AlarmSubSecondMask_SS14_1 = 0x1
RTC_AlarmSubSecondMask_SS14_2 = 0x2
RTC_AlarmSubSecondMask_SS14_3 = 0x3
RTC_AlarmSubSecondMask_SS14_4 = 0x4
RTC_AlarmSubSecondMask_SS14_5 = 0x5
RTC_AlarmSubSecondMask_SS14_6 = 0x6
RTC_AlarmSubSecondMask_SS14_7 = 0x7
RTC_AlarmSubSecondMask_SS14_8 = 0x8
RTC_AlarmSubSecondMask_SS14_9 = 0x9
RTC_AlarmSubSecondMask_SS14_10 = 0xA
RTC_AlarmSubSecondMask_SS14_11 = 0xB
RTC_AlarmSubSecondMask_SS14_12 = 0xC
RTC_AlarmSubSecondMask_SS14_13 = 0xD
RTC_AlarmSubSecondMask_SS14 = 0xE
RTC_AlarmSubSecondMask_None = 0xF
RTC_WakeUpClock_RTCCLK_Div16 = 0x0
RTC_WakeUpClock_RTCCLK_Div8 = 0x1
RTC_WakeUpClock_RTCCLK_Div4 = 0x2
RTC_WakeUpClock_RTCCLK_Div2 = 0x3
RTC_WakeUpClock_CK_SPRE_16bits = 0x4
RTC_WakeUpClock_CK_SPRE_17bits = 0x6
RTC_TimeStampEdge_Rising = 0x0
RTC_TimeStampEdge_Falling = 0x8
RTC_Output_Disable = 0x0
RTC_Output_AlarmA = 0x200000
RTC_Output_WakeUp = 0x600000
RTC_OutputPolarity_High = 0x0
RTC_OutputPolarity_Low = 0x100000
RTC_CalibOutput_512Hz = 0x0
RTC_CalibOutput_1Hz = 0x80000
RTC_SmoothCalibPeriod_32sec = 0x0
RTC_SmoothCalibPeriod_16sec = 0x2000
RTC_SmoothCalibPeriod_8sec = 0x4000
RTC_SmoothCalibPlusPulses_Set = 0x8000
RTC_SmoothCalibPlusPulses_Reset = 0x0
RTC_DayLightSaving_SUB1H = 0x20000
RTC_DayLightSaving_ADD1H = 0x10000
RTC_StoreOperation_Reset = 0x0
RTC_StoreOperation_Set = 0x40000
RTC_TamperTrigger_RisingEdge = 0x0
RTC_TamperTrigger_FallingEdge = 0x1
RTC_TamperTrigger_LowLevel = 0x0
RTC_TamperTrigger_HighLevel = 0x1
RTC_TamperFilter_Disable = 0x0
RTC_TamperFilter_2Sample = 0x800
RTC_TamperFilter_4Sample = 0x1000
RTC_TamperFilter_8Sample = 0x1800
RTC_TamperSamplingFreq_RTCCLK_Div32768 = 0x0
RTC_TamperSamplingFreq_RTCCLK_Div16384 = 0x100
RTC_TamperSamplingFreq_RTCCLK_Div8192 = 0x200
RTC_TamperSamplingFreq_RTCCLK_Div4096 = 0x300
RTC_TamperSamplingFreq_RTCCLK_Div2048 = 0x400
RTC_TamperSamplingFreq_RTCCLK_Div1024 = 0x500
RTC_TamperSamplingFreq_RTCCLK_Div512 = 0x600
RTC_TamperSamplingFreq_RTCCLK_Div256 = 0x700
RTC_TamperPrechargeDuration_1RTCCLK = 0x0
RTC_TamperPrechargeDuration_2RTCCLK = 0x2000
RTC_TamperPrechargeDuration_4RTCCLK = 0x4000
RTC_TamperPrechargeDuration_8RTCCLK = 0x6000
RTC_Tamper_1 = 0x1
RTC_Tamper_2 = 0x8
RTC_Tamper_3 = 0x20
RTC_OutputType_OpenDrain = 0x0
RTC_OutputType_PushPull = 0x40000
RTC_ShiftAdd1S_Reset = 0x0
RTC_ShiftAdd1S_Set = 0x80000000
RTC_BKP_DR0 = 0x0
RTC_BKP_DR1 = 0x1
RTC_BKP_DR2 = 0x2
RTC_BKP_DR3 = 0x3
RTC_BKP_DR4 = 0x4
RTC_Format_BIN = 0x0
RTC_Format_BCD = 0x1
RTC_FLAG_RECALPF = 0x10000
RTC_FLAG_TAMP3F = 0x8000
RTC_FLAG_TAMP2F = 0x4000
RTC_FLAG_TAMP1F = 0x2000
RTC_FLAG_TSOVF = 0x1000
RTC_FLAG_TSF = 0x800
RTC_FLAG_WUTF = 0x400
RTC_FLAG_ALRAF = 0x100
RTC_FLAG_INITF = 0x40
RTC_FLAG_RSF = 0x20
RTC_FLAG_INITS = 0x10
RTC_FLAG_SHPF = 0x8
RTC_FLAG_WUTWF = 0x4
RTC_FLAG_ALRAWF = 0x1
RTC_IT_TS = 0x8000
RTC_IT_WUT = 0x4000
RTC_IT_ALRA = 0x1000
RTC_IT_TAMP = 0x4
RTC_IT_TAMP1 = 0x20000
RTC_IT_TAMP2 = 0x40000
RTC_IT_TAMP3 = 0x80000
# struct RTC_InitTypeDef

class RTC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RTC_HourFormat',	ctypes.c_uint32),
		('RTC_AsynchPrediv',	ctypes.c_uint32),
		('RTC_SynchPrediv',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct RTC_TimeTypeDef

class RTC_TimeTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RTC_Hours',	ctypes.c_uint8),
		('RTC_Minutes',	ctypes.c_uint8),
		('RTC_Seconds',	ctypes.c_uint8),
		('RTC_H12',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct RTC_DateTypeDef

class RTC_DateTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RTC_WeekDay',	ctypes.c_uint8),
		('RTC_Month',	ctypes.c_uint8),
		('RTC_Date',	ctypes.c_uint8),
		('RTC_Year',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct RTC_AlarmTypeDef
# struct RTC_AlarmTypeDef : field is class : RTC_AlarmTime
# ----------------------------------------

# file stm32f0xx_misc.h : 

# empty define __STM32F0XX_MISC_H
NVIC_LP_SEVONPEND = 0x10
NVIC_LP_SLEEPDEEP = 0x4
NVIC_LP_SLEEPONEXIT = 0x2
SysTick_CLKSource_HCLK_Div8 = 0xFFFFFFFB
SysTick_CLKSource_HCLK = 0x4
# struct NVIC_InitTypeDef

class NVIC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('NVIC_IRQChannel',	ctypes.c_uint8),
		('NVIC_IRQChannelPriority',	ctypes.c_uint8),
		('NVIC_IRQChannelCmd',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_comp.h : 

# empty define __STM32F0XX_COMP_H
COMP_Selection_COMP1 = 0x0
COMP_Selection_COMP2 = 0x10
COMP_InvertingInput_1_4VREFINT = 0x0
COMP_InvertingInput_1_2VREFINT = 0x10
COMP_InvertingInput_3_4VREFINT = 0x20
COMP_InvertingInput_VREFINT = 0x30
COMP_InvertingInput_DAC1 = 0x40
COMP_InvertingInput_DAC2 = 0x50
COMP_InvertingInput_IO = 0x60
COMP_Output_None = 0x0
COMP_Output_TIM1BKIN = 0x100
COMP_Output_TIM1IC1 = 0x200
COMP_Output_TIM1OCREFCLR = 0x300
COMP_Output_TIM2IC4 = 0x400
COMP_Output_TIM2OCREFCLR = 0x500
COMP_Output_TIM3IC1 = 0x600
COMP_Output_TIM3OCREFCLR = 0x700
COMP_OutputPol_NonInverted = 0x0
COMP_OutputPol_Inverted = 0x800
COMP_Hysteresis_No = 0x0
COMP_Hysteresis_Low = 0x1000
COMP_Hysteresis_Medium = 0x2000
COMP_Hysteresis_High = 0x3000
COMP_Mode_HighSpeed = 0x0
COMP_Mode_MediumSpeed = 0x4
COMP_Mode_LowPower = 0x8
COMP_Mode_UltraLowPower = 0xC
COMP_OutputLevel_High = 0x4000
COMP_OutputLevel_Low = 0x0
# struct COMP_InitTypeDef

class COMP_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('COMP_InvertingInput',	ctypes.c_uint32),
		('COMP_Output',	ctypes.c_uint32),
		('COMP_OutputPol',	ctypes.c_uint32),
		('COMP_Hysteresis',	ctypes.c_uint32),
		('COMP_Mode',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_rcc.h : 

# empty define __STM32F0XX_RCC_H
RCC_HSE_OFF = 0x0
RCC_HSE_ON = 0x1
RCC_HSE_Bypass = 0x5
RCC_PLLSource_HSI_Div2 = 0x0
RCC_PLLSource_PREDIV1 = 0x10000
RCC_PLLSource_HSE = 0x10000
RCC_PLLSource_HSI48 = 0x18000
RCC_PLLSource_HSI = 0x8000
RCC_PLLMul_2 = 0x0
RCC_PLLMul_3 = 0x40000
RCC_PLLMul_4 = 0x80000
RCC_PLLMul_5 = 0xC0000
RCC_PLLMul_6 = 0x100000
RCC_PLLMul_7 = 0x140000
RCC_PLLMul_8 = 0x180000
RCC_PLLMul_9 = 0x1C0000
RCC_PLLMul_10 = 0x200000
RCC_PLLMul_11 = 0x240000
RCC_PLLMul_12 = 0x280000
RCC_PLLMul_13 = 0x2C0000
RCC_PLLMul_14 = 0x300000
RCC_PLLMul_15 = 0x340000
RCC_PLLMul_16 = 0x380000
RCC_PREDIV1_Div1 = 0x0
RCC_PREDIV1_Div2 = 0x1
RCC_PREDIV1_Div3 = 0x2
RCC_PREDIV1_Div4 = 0x3
RCC_PREDIV1_Div5 = 0x4
RCC_PREDIV1_Div6 = 0x5
RCC_PREDIV1_Div7 = 0x6
RCC_PREDIV1_Div8 = 0x7
RCC_PREDIV1_Div9 = 0x8
RCC_PREDIV1_Div10 = 0x9
RCC_PREDIV1_Div11 = 0xA
RCC_PREDIV1_Div12 = 0xB
RCC_PREDIV1_Div13 = 0xC
RCC_PREDIV1_Div14 = 0xD
RCC_PREDIV1_Div15 = 0xE
RCC_PREDIV1_Div16 = 0xF
RCC_SYSCLKSource_HSI = 0x0
RCC_SYSCLKSource_HSE = 0x1
RCC_SYSCLKSource_PLLCLK = 0x2
RCC_SYSCLKSource_HSI48 = 0x3
RCC_SYSCLK_Div1 = 0x0
RCC_SYSCLK_Div2 = 0x80
RCC_SYSCLK_Div4 = 0x90
RCC_SYSCLK_Div8 = 0xA0
RCC_SYSCLK_Div16 = 0xB0
RCC_SYSCLK_Div64 = 0xC0
RCC_SYSCLK_Div128 = 0xD0
RCC_SYSCLK_Div256 = 0xE0
RCC_SYSCLK_Div512 = 0xF0
RCC_HCLK_Div1 = 0x0
RCC_HCLK_Div2 = 0x400
RCC_HCLK_Div4 = 0x500
RCC_HCLK_Div8 = 0x600
RCC_HCLK_Div16 = 0x700
RCC_ADCCLK_HSI14 = 0x0
RCC_ADCCLK_PCLK_Div2 = 0x1000000
RCC_ADCCLK_PCLK_Div4 = 0x1004000
RCC_CECCLK_HSI_Div244 = 0x0
RCC_CECCLK_LSE = 0x40
RCC_I2C1CLK_HSI = 0x0
RCC_I2C1CLK_SYSCLK = 0x10
RCC_USBCLK_HSI48 = 0x0
RCC_USBCLK_PLLCLK = 0x80
RCC_USART1CLK_PCLK = 0x10000000
RCC_USART1CLK_SYSCLK = 0x10000001
RCC_USART1CLK_LSE = 0x10000002
RCC_USART1CLK_HSI = 0x10000003
RCC_USART2CLK_PCLK = 0x20000000
RCC_USART2CLK_SYSCLK = 0x20010000
RCC_USART2CLK_LSE = 0x20020000
RCC_USART2CLK_HSI = 0x20030000
RCC_USART3CLK_PCLK = 0x30000000
RCC_USART3CLK_SYSCLK = 0x30040000
RCC_USART3CLK_LSE = 0x30080000
RCC_USART3CLK_HSI = 0x300C0000
RCC_IT_LSIRDY = 0x1
RCC_IT_LSERDY = 0x2
RCC_IT_HSIRDY = 0x4
RCC_IT_HSERDY = 0x8
RCC_IT_PLLRDY = 0x10
RCC_IT_HSI14RDY = 0x20
RCC_IT_HSI48RDY = 0x40
RCC_IT_CSS = 0x80
RCC_LSE_OFF = 0x0
RCC_LSE_ON = 0x1
RCC_LSE_Bypass = 0x5
RCC_RTCCLKSource_LSE = 0x100
RCC_RTCCLKSource_LSI = 0x200
RCC_RTCCLKSource_HSE_Div32 = 0x300
RCC_LSEDrive_Low = 0x0
RCC_LSEDrive_MediumLow = 0x8
RCC_LSEDrive_MediumHigh = 0x10
RCC_LSEDrive_High = 0x18
RCC_AHBPeriph_GPIOA = 0x20000
RCC_AHBPeriph_GPIOB = 0x40000
RCC_AHBPeriph_GPIOC = 0x80000
RCC_AHBPeriph_GPIOD = 0x100000
RCC_AHBPeriph_GPIOE = 0x200000
RCC_AHBPeriph_GPIOF = 0x400000
RCC_AHBPeriph_TS = 0x1000000
RCC_AHBPeriph_CRC = 0x40
RCC_AHBPeriph_FLITF = 0x10
RCC_AHBPeriph_SRAM = 0x4
RCC_AHBPeriph_DMA1 = 0x1
RCC_AHBPeriph_DMA2 = 0x2
RCC_APB2Periph_SYSCFG = 0x1
RCC_APB2Periph_USART6 = 0x20
RCC_APB2Periph_USART7 = 0x40
RCC_APB2Periph_USART8 = 0x80
RCC_APB2Periph_ADC1 = 0x200
RCC_APB2Periph_TIM1 = 0x800
RCC_APB2Periph_SPI1 = 0x1000
RCC_APB2Periph_USART1 = 0x4000
RCC_APB2Periph_TIM15 = 0x10000
RCC_APB2Periph_TIM16 = 0x20000
RCC_APB2Periph_TIM17 = 0x40000
RCC_APB2Periph_DBGMCU = 0x400000
RCC_APB1Periph_TIM2 = 0x1
RCC_APB1Periph_TIM3 = 0x2
RCC_APB1Periph_TIM6 = 0x10
RCC_APB1Periph_TIM7 = 0x20
RCC_APB1Periph_TIM14 = 0x100
RCC_APB1Periph_WWDG = 0x800
RCC_APB1Periph_SPI2 = 0x4000
RCC_APB1Periph_USART2 = 0x20000
RCC_APB1Periph_USART3 = 0x40000
RCC_APB1Periph_USART4 = 0x80000
RCC_APB1Periph_USART5 = 0x100000
RCC_APB1Periph_I2C1 = 0x200000
RCC_APB1Periph_I2C2 = 0x400000
RCC_APB1Periph_USB = 0x800000
RCC_APB1Periph_CAN = 0x2000000
RCC_APB1Periph_CRS = 0x8000000
RCC_APB1Periph_PWR = 0x10000000
RCC_APB1Periph_DAC = 0x20000000
RCC_APB1Periph_CEC = 0x40000000
RCC_MCOSource_NoClock = 0x0
RCC_MCOSource_HSI14 = 0x1
RCC_MCOSource_LSI = 0x2
RCC_MCOSource_LSE = 0x3
RCC_MCOSource_SYSCLK = 0x4
RCC_MCOSource_HSI = 0x5
RCC_MCOSource_HSE = 0x6
RCC_MCOSource_PLLCLK_Div2 = 0x7
RCC_MCOSource_HSI48 = 0x8
RCC_MCOSource_PLLCLK = 0x87
RCC_MCOPrescaler_1 = 0x0
RCC_MCOPrescaler_2 = 0x10000000
RCC_MCOPrescaler_4 = 0x20000000
RCC_MCOPrescaler_8 = 0x30000000
RCC_MCOPrescaler_16 = 0x40000000
RCC_MCOPrescaler_32 = 0x50000000
RCC_MCOPrescaler_64 = 0x60000000
RCC_MCOPrescaler_128 = 0x70000000
RCC_FLAG_HSIRDY = 0x1
RCC_FLAG_HSERDY = 0x11
RCC_FLAG_PLLRDY = 0x19
RCC_FLAG_LSERDY = 0x21
RCC_FLAG_LSIRDY = 0x41
RCC_FLAG_V18PWRRSTF = 0x57
RCC_FLAG_OBLRST = 0x59
RCC_FLAG_PINRST = 0x5A
RCC_FLAG_PORRST = 0x5B
RCC_FLAG_SFTRST = 0x5C
RCC_FLAG_IWDGRST = 0x5D
RCC_FLAG_WWDGRST = 0x5E
RCC_FLAG_LPWRRST = 0x5F
RCC_FLAG_HSI14RDY = 0x61
RCC_FLAG_HSI48RDY = 0x71
# struct RCC_ClocksTypeDef

class RCC_ClocksTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SYSCLK_Frequency',	ctypes.c_uint32),
		('HCLK_Frequency',	ctypes.c_uint32),
		('PCLK_Frequency',	ctypes.c_uint32),
		('ADCCLK_Frequency',	ctypes.c_uint32),
		('CECCLK_Frequency',	ctypes.c_uint32),
		('I2C1CLK_Frequency',	ctypes.c_uint32),
		('USART1CLK_Frequency',	ctypes.c_uint32),
		('USART2CLK_Frequency',	ctypes.c_uint32),
		('USART3CLK_Frequency',	ctypes.c_uint32),
		('USBCLK_Frequency',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_flash.h : 

# Enum FLASH_Status
FLASH_BUSY = 0x1
FLASH_ERROR_WRP = 0x2
FLASH_ERROR_PROGRAM = 0x3
FLASH_COMPLETE = 0x4
FLASH_TIMEOUT = 0x5
# empty define __STM32F0XX_FLASH_H
FLASH_Latency_0 = 0x0
FLASH_Latency_1 = 0x1
FLASH_IT_EOP = 0x1000
FLASH_IT_ERR = 0x400
# Skip OB_WRP_Pages0to3 : no need parse
# Skip OB_WRP_Pages4to7 : no need parse
# Skip OB_WRP_Pages8to11 : no need parse
# Skip OB_WRP_Pages12to15 : no need parse
# Skip OB_WRP_Pages16to19 : no need parse
# Skip OB_WRP_Pages20to23 : no need parse
# Skip OB_WRP_Pages24to27 : no need parse
# Skip OB_WRP_Pages28to31 : no need parse
# Skip OB_WRP_Pages32to35 : no need parse
# Skip OB_WRP_Pages36to39 : no need parse
# Skip OB_WRP_Pages40to43 : no need parse
# Skip OB_WRP_Pages44to47 : no need parse
# Skip OB_WRP_Pages48to51 : no need parse
# Skip OB_WRP_Pages52to55 : no need parse
# Skip OB_WRP_Pages56to59 : no need parse
# Skip OB_WRP_Pages60to63 : no need parse
OB_WRP_AllPages = 0xFFFFFFFF
OB_WRP_Pages0to1 = 0x1
OB_WRP_Pages2to3 = 0x2
OB_WRP_Pages4to5 = 0x4
OB_WRP_Pages6to7 = 0x8
OB_WRP_Pages8to9 = 0x10
OB_WRP_Pages10to11 = 0x20
OB_WRP_Pages12to13 = 0x40
OB_WRP_Pages14to15 = 0x80
OB_WRP_Pages16to17 = 0x100
OB_WRP_Pages18to19 = 0x200
OB_WRP_Pages20to21 = 0x400
OB_WRP_Pages22to23 = 0x800
OB_WRP_Pages24to25 = 0x1000
OB_WRP_Pages26to27 = 0x2000
OB_WRP_Pages28to29 = 0x4000
OB_WRP_Pages30to31 = 0x8000
OB_WRP_Pages32to33 = 0x10000
OB_WRP_Pages34to35 = 0x20000
OB_WRP_Pages36to37 = 0x40000
OB_WRP_Pages38to39 = 0x80000
OB_WRP_Pages40to41 = 0x100000
OB_WRP_Pages42to43 = 0x200000
OB_WRP_Pages44to45 = 0x400000
OB_WRP_Pages46to47 = 0x800000
OB_WRP_Pages48to49 = 0x1000000
OB_WRP_Pages50to51 = 0x2000000
OB_WRP_Pages52to53 = 0x4000000
OB_WRP_Pages54to55 = 0x8000000
OB_WRP_Pages56to57 = 0x10000000
OB_WRP_Pages58to59 = 0x20000000
OB_WRP_Pages60to61 = 0x40000000
OB_WRP_Pages62to127 = 0x80000000
# Skip OB_WRP_Pages62to63 : no need parse
OB_WRP_AllPages = 0xFFFFFFFF
OB_RDP_Level_0 = 0xAA
OB_RDP_Level_1 = 0xBB
OB_IWDG_SW = 0x1
OB_IWDG_HW = 0x0
OB_STOP_NoRST = 0x2
OB_STOP_RST = 0x0
OB_STDBY_NoRST = 0x4
OB_STDBY_RST = 0x0
OB_BOOT1_RESET = 0x0
OB_BOOT1_SET = 0x10
OB_BOOT0_RESET = 0x0
OB_BOOT0_SET = 0x8
OB_BOOT0_SW = 0x0
OB_BOOT0_HW = 0x80
OB_VDDA_ANALOG_ON = 0x20
OB_VDDA_ANALOG_OFF = 0x0
OB_SRAM_PARITY_SET = 0x0
OB_SRAM_PARITY_RESET = 0x40
FLASH_FLAG_BSY = 0x1
FLASH_FLAG_PGERR = 0x4
FLASH_FLAG_WRPERR = 0x10
FLASH_FLAG_EOP = 0x20
FLASH_ER_PRG_TIMEOUT = 0xB0000
# Skip FLASH_WRProt_Pages0to3	 : no need parse
# Skip FLASH_WRProt_Pages4to7	 : no need parse
# Skip FLASH_WRProt_Pages8to11	 : no need parse
# Skip FLASH_WRProt_Pages12to15	 : no need parse
# Skip FLASH_WRProt_Pages16to19	 : no need parse
# Skip FLASH_WRProt_Pages20to23	 : no need parse
# Skip FLASH_WRProt_Pages24to27	 : no need parse
# Skip FLASH_WRProt_Pages28to31	 : no need parse
# Skip FLASH_WRProt_Pages32to35	 : no need parse
# Skip FLASH_WRProt_Pages36to39	 : no need parse
# Skip FLASH_WRProt_Pages40to43	 : no need parse
# Skip FLASH_WRProt_Pages44to47	 : no need parse
# Skip FLASH_WRProt_Pages48to51	 : no need parse
# Skip FLASH_WRProt_Pages52to55	 : no need parse
# Skip FLASH_WRProt_Pages56to59	 : no need parse
# Skip FLASH_WRProt_Pages60to63	 : no need parse
FLASH_WRProt_AllPages = 0xFFFFFFFF
# Skip FLASH_EraseOptionBytes : no need parse
# Skip FLASH_EnableWriteProtection	 : no need parse
# Skip FLASH_UserOptionByteConfig	 : no need parse
# Skip FLASH_ProgramOptionByteData : no need parse
# Skip FLASH_GetUserOptionByte	 : no need parse
# Skip FLASH_GetWriteProtectionOptionByte : no need parse
# ----------------------------------------

# file stm32f0xx_dma.h : 

# empty define __STM32F0XX_DMA_H
DMA_DIR_PeripheralSRC = 0x0
DMA_DIR_PeripheralDST = 0x10
DMA_PeripheralInc_Disable = 0x0
DMA_PeripheralInc_Enable = 0x40
DMA_MemoryInc_Disable = 0x0
DMA_MemoryInc_Enable = 0x80
DMA_PeripheralDataSize_Byte = 0x0
DMA_PeripheralDataSize_HalfWord = 0x100
DMA_PeripheralDataSize_Word = 0x200
DMA_MemoryDataSize_Byte = 0x0
DMA_MemoryDataSize_HalfWord = 0x400
DMA_MemoryDataSize_Word = 0x800
DMA_Mode_Normal = 0x0
DMA_Mode_Circular = 0x20
DMA_Priority_VeryHigh = 0x3000
DMA_Priority_High = 0x2000
DMA_Priority_Medium = 0x1000
DMA_Priority_Low = 0x0
DMA_M2M_Disable = 0x0
DMA_M2M_Enable = 0x4000
DMAx_CHANNEL1_RMP = 0x0
DMAx_CHANNEL2_RMP = 0x10000000
DMAx_CHANNEL3_RMP = 0x20000000
DMAx_CHANNEL4_RMP = 0x30000000
DMAx_CHANNEL5_RMP = 0x40000000
DMAx_CHANNEL6_RMP = 0x50000000
DMAx_CHANNEL7_RMP = 0x60000000
DMA1_CH1_DEFAULT = 0x0
DMA1_CH1_ADC = 0x1
DMA1_CH1_TIM17_CH1 = 0x7
DMA1_CH1_TIM17_UP = 0x7
DMA1_CH1_USART1_RX = 0x8
DMA1_CH1_USART2_RX = 0x9
DMA1_CH1_USART3_RX = 0xA
DMA1_CH1_USART4_RX = 0xB
DMA1_CH1_USART5_RX = 0xC
DMA1_CH1_USART6_RX = 0xD
DMA1_CH1_USART7_RX = 0xE
DMA1_CH1_USART8_RX = 0xF
DMA1_CH2_DEFAULT = 0x10000000
DMA1_CH2_ADC = 0x10000010
DMA1_CH2_I2C1_TX = 0x10000020
DMA1_CH2_SPI1_RX = 0x10000030
DMA1_CH2_TIM1_CH1 = 0x10000040
DMA1_CH2_TIM17_CH1 = 0x10000070
DMA1_CH2_TIM17_UP = 0x10000070
DMA1_CH2_USART1_TX = 0x10000080
DMA1_CH2_USART2_TX = 0x10000090
DMA1_CH2_USART3_TX = 0x100000A0
DMA1_CH2_USART4_TX = 0x100000B0
DMA1_CH2_USART5_TX = 0x100000C0
DMA1_CH2_USART6_TX = 0x100000D0
DMA1_CH2_USART7_TX = 0x100000E0
DMA1_CH2_USART8_TX = 0x100000F0
DMA1_CH3_DEFAULT = 0x20000000
DMA1_CH3_TIM6_UP = 0x20000100
DMA1_CH3_DAC_CH1 = 0x20000100
DMA1_CH3_I2C1_RX = 0x20000200
DMA1_CH3_SPI1_TX = 0x20000300
DMA1_CH3_TIM1_CH2 = 0x20000400
DMA1_CH3_TIM2_CH2 = 0x20000500
DMA1_CH3_TIM16_CH1 = 0x20000700
DMA1_CH3_TIM16_UP = 0x20000700
DMA1_CH3_USART1_RX = 0x20000800
DMA1_CH3_USART2_RX = 0x20000900
DMA1_CH3_USART3_RX = 0x20000A00
DMA1_CH3_USART4_RX = 0x20000B00
DMA1_CH3_USART5_RX = 0x20000C00
DMA1_CH3_USART6_RX = 0x20000D00
DMA1_CH3_USART7_RX = 0x20000E00
DMA1_CH3_USART8_RX = 0x20000F00
DMA1_CH4_DEFAULT = 0x30000000
DMA1_CH4_TIM7_UP = 0x30001000
DMA1_CH4_DAC_CH2 = 0x30001000
DMA1_CH4_I2C2_TX = 0x30002000
DMA1_CH4_SPI2_RX = 0x30003000
DMA1_CH4_TIM2_CH4 = 0x30005000
DMA1_CH4_TIM3_CH1 = 0x30006000
DMA1_CH4_TIM3_TRIG = 0x30006000
DMA1_CH4_TIM16_CH1 = 0x30007000
DMA1_CH4_TIM16_UP = 0x30007000
DMA1_CH4_USART1_TX = 0x30008000
DMA1_CH4_USART2_TX = 0x30009000
DMA1_CH4_USART3_TX = 0x3000A000
DMA1_CH4_USART4_TX = 0x3000B000
DMA1_CH4_USART5_TX = 0x3000C000
DMA1_CH4_USART6_TX = 0x3000D000
DMA1_CH4_USART7_TX = 0x3000E000
DMA1_CH4_USART8_TX = 0x3000F000
DMA1_CH5_DEFAULT = 0x40000000
DMA1_CH5_I2C2_RX = 0x40020000
DMA1_CH5_SPI2_TX = 0x40030000
DMA1_CH5_TIM1_CH3 = 0x40040000
DMA1_CH5_USART1_RX = 0x40080000
DMA1_CH5_USART2_RX = 0x40090000
DMA1_CH5_USART3_RX = 0x400A0000
DMA1_CH5_USART4_RX = 0x400B0000
DMA1_CH5_USART5_RX = 0x400C0000
DMA1_CH5_USART6_RX = 0x400D0000
DMA1_CH5_USART7_RX = 0x400E0000
DMA1_CH5_USART8_RX = 0x400F0000
DMA1_CH6_DEFAULT = 0x50000000
DMA1_CH6_I2C1_TX = 0x50200000
DMA1_CH6_SPI2_RX = 0x50300000
DMA1_CH6_TIM1_CH1 = 0x50400000
DMA1_CH6_TIM1_CH2 = 0x50400000
DMA1_CH6_TIM1_CH3 = 0x50400000
DMA1_CH6_TIM3_CH1 = 0x50600000
DMA1_CH6_TIM3_TRIG = 0x50600000
DMA1_CH6_TIM16_CH1 = 0x50700000
DMA1_CH6_TIM16_UP = 0x50700000
DMA1_CH6_USART1_RX = 0x50800000
DMA1_CH6_USART2_RX = 0x50900000
DMA1_CH6_USART3_RX = 0x50A00000
DMA1_CH6_USART4_RX = 0x50B00000
DMA1_CH6_USART5_RX = 0x50C00000
DMA1_CH6_USART6_RX = 0x50D00000
DMA1_CH6_USART7_RX = 0x50E00000
DMA1_CH6_USART8_RX = 0x50F00000
DMA1_CH7_DEFAULT = 0x60000000
DMA1_CH7_I2C1_RX = 0x62000000
DMA1_CH7_SPI2_TX = 0x63000000
DMA1_CH7_TIM2_CH2 = 0x65000000
DMA1_CH7_TIM2_CH4 = 0x65000000
DMA1_CH7_TIM17_CH1 = 0x67000000
DMA1_CH7_TIM17_UP = 0x67000000
DMA1_CH7_USART1_TX = 0x68000000
DMA1_CH7_USART2_TX = 0x69000000
DMA1_CH7_USART3_TX = 0x6A000000
DMA1_CH7_USART4_TX = 0x6B000000
DMA1_CH7_USART5_TX = 0x6C000000
DMA1_CH7_USART6_TX = 0x6D000000
DMA1_CH7_USART7_TX = 0x6E000000
DMA1_CH7_USART8_TX = 0x6F000000
DMA2_CH1_DEFAULT = 0x0
DMA2_CH1_I2C2_TX = 0x2
DMA2_CH1_USART1_TX = 0x8
DMA2_CH1_USART2_TX = 0x9
DMA2_CH1_USART3_TX = 0xA
DMA2_CH1_USART4_TX = 0xB
DMA2_CH1_USART5_TX = 0xC
DMA2_CH1_USART6_TX = 0xD
DMA2_CH1_USART7_TX = 0xE
DMA2_CH1_USART8_TX = 0xF
DMA2_CH2_DEFAULT = 0x10000000
DMA2_CH2_I2C2_RX = 0x10000020
DMA2_CH2_USART1_RX = 0x10000080
DMA2_CH2_USART2_RX = 0x10000090
DMA2_CH2_USART3_RX = 0x100000A0
DMA2_CH2_USART4_RX = 0x100000B0
DMA2_CH2_USART5_RX = 0x100000C0
DMA2_CH2_USART6_RX = 0x100000D0
DMA2_CH2_USART7_RX = 0x100000E0
DMA2_CH2_USART8_RX = 0x100000F0
DMA2_CH3_DEFAULT = 0x20000000
DMA2_CH3_TIM6_UP = 0x20000100
DMA2_CH3_DAC_CH1 = 0x20000100
DMA2_CH3_SPI1_RX = 0x20000300
DMA2_CH3_USART1_RX = 0x20000800
DMA2_CH3_USART2_RX = 0x20000900
DMA2_CH3_USART3_RX = 0x20000A00
DMA2_CH3_USART4_RX = 0x20000B00
DMA2_CH3_USART5_RX = 0x20000C00
DMA2_CH3_USART6_RX = 0x20000D00
DMA2_CH3_USART7_RX = 0x20000E00
DMA2_CH3_USART8_RX = 0x20000F00
DMA2_CH4_DEFAULT = 0x30000000
DMA2_CH4_TIM7_UP = 0x30001000
DMA2_CH4_DAC_CH2 = 0x30001000
DMA2_CH4_SPI1_TX = 0x30003000
DMA2_CH4_USART1_TX = 0x30008000
DMA2_CH4_USART2_TX = 0x30009000
DMA2_CH4_USART3_TX = 0x3000A000
DMA2_CH4_USART4_TX = 0x3000B000
DMA2_CH4_USART5_TX = 0x3000C000
DMA2_CH4_USART6_TX = 0x3000D000
DMA2_CH4_USART7_TX = 0x3000E000
DMA2_CH4_USART8_TX = 0x3000F000
DMA2_CH5_DEFAULT = 0x40000000
DMA2_CH5_ADC = 0x40010000
DMA2_CH5_USART1_TX = 0x40080000
DMA2_CH5_USART2_TX = 0x40090000
DMA2_CH5_USART3_TX = 0x400A0000
DMA2_CH5_USART4_TX = 0x400B0000
DMA2_CH5_USART5_TX = 0x400C0000
DMA2_CH5_USART6_TX = 0x400D0000
DMA2_CH5_USART7_TX = 0x400E0000
DMA2_CH5_USART8_TX = 0x400F0000
DMA_IT_TC = 0x2
DMA_IT_HT = 0x4
DMA_IT_TE = 0x8
DMA1_IT_GL1 = 0x1
DMA1_IT_TC1 = 0x2
DMA1_IT_HT1 = 0x4
DMA1_IT_TE1 = 0x8
DMA1_IT_GL2 = 0x10
DMA1_IT_TC2 = 0x20
DMA1_IT_HT2 = 0x40
DMA1_IT_TE2 = 0x80
DMA1_IT_GL3 = 0x100
DMA1_IT_TC3 = 0x200
DMA1_IT_HT3 = 0x400
DMA1_IT_TE3 = 0x800
DMA1_IT_GL4 = 0x1000
DMA1_IT_TC4 = 0x2000
DMA1_IT_HT4 = 0x4000
DMA1_IT_TE4 = 0x8000
DMA1_IT_GL5 = 0x10000
DMA1_IT_TC5 = 0x20000
DMA1_IT_HT5 = 0x40000
DMA1_IT_TE5 = 0x80000
DMA1_IT_GL6 = 0x100000
DMA1_IT_TC6 = 0x200000
DMA1_IT_HT6 = 0x400000
DMA1_IT_TE6 = 0x800000
DMA1_IT_GL7 = 0x1000000
DMA1_IT_TC7 = 0x2000000
DMA1_IT_HT7 = 0x4000000
DMA1_IT_TE7 = 0x8000000
DMA2_IT_GL1 = 0x10000001
DMA2_IT_TC1 = 0x10000002
DMA2_IT_HT1 = 0x10000004
DMA2_IT_TE1 = 0x10000008
DMA2_IT_GL2 = 0x10000010
DMA2_IT_TC2 = 0x10000020
DMA2_IT_HT2 = 0x10000040
DMA2_IT_TE2 = 0x10000080
DMA2_IT_GL3 = 0x10000100
DMA2_IT_TC3 = 0x10000200
DMA2_IT_HT3 = 0x10000400
DMA2_IT_TE3 = 0x10000800
DMA2_IT_GL4 = 0x10001000
DMA2_IT_TC4 = 0x10002000
DMA2_IT_HT4 = 0x10004000
DMA2_IT_TE4 = 0x10008000
DMA2_IT_GL5 = 0x10010000
DMA2_IT_TC5 = 0x10020000
DMA2_IT_HT5 = 0x10040000
DMA2_IT_TE5 = 0x10080000
DMA1_FLAG_GL1 = 0x1
DMA1_FLAG_TC1 = 0x2
DMA1_FLAG_HT1 = 0x4
DMA1_FLAG_TE1 = 0x8
DMA1_FLAG_GL2 = 0x10
DMA1_FLAG_TC2 = 0x20
DMA1_FLAG_HT2 = 0x40
DMA1_FLAG_TE2 = 0x80
DMA1_FLAG_GL3 = 0x100
DMA1_FLAG_TC3 = 0x200
DMA1_FLAG_HT3 = 0x400
DMA1_FLAG_TE3 = 0x800
DMA1_FLAG_GL4 = 0x1000
DMA1_FLAG_TC4 = 0x2000
DMA1_FLAG_HT4 = 0x4000
DMA1_FLAG_TE4 = 0x8000
DMA1_FLAG_GL5 = 0x10000
DMA1_FLAG_TC5 = 0x20000
DMA1_FLAG_HT5 = 0x40000
DMA1_FLAG_TE5 = 0x80000
DMA1_FLAG_GL6 = 0x100000
DMA1_FLAG_TC6 = 0x200000
DMA1_FLAG_HT6 = 0x400000
DMA1_FLAG_TE6 = 0x800000
DMA1_FLAG_GL7 = 0x1000000
DMA1_FLAG_TC7 = 0x2000000
DMA1_FLAG_HT7 = 0x4000000
DMA1_FLAG_TE7 = 0x8000000
DMA2_FLAG_GL1 = 0x10000001
DMA2_FLAG_TC1 = 0x10000002
DMA2_FLAG_HT1 = 0x10000004
DMA2_FLAG_TE1 = 0x10000008
DMA2_FLAG_GL2 = 0x10000010
DMA2_FLAG_TC2 = 0x10000020
DMA2_FLAG_HT2 = 0x10000040
DMA2_FLAG_TE2 = 0x10000080
DMA2_FLAG_GL3 = 0x10000100
DMA2_FLAG_TC3 = 0x10000200
DMA2_FLAG_HT3 = 0x10000400
DMA2_FLAG_TE3 = 0x10000800
DMA2_FLAG_GL4 = 0x10001000
DMA2_FLAG_TC4 = 0x10002000
DMA2_FLAG_HT4 = 0x10004000
DMA2_FLAG_TE4 = 0x10008000
DMA2_FLAG_GL5 = 0x10010000
DMA2_FLAG_TC5 = 0x10020000
DMA2_FLAG_HT5 = 0x10040000
DMA2_FLAG_TE5 = 0x10080000
# struct DMA_InitTypeDef

class DMA_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DMA_PeripheralBaseAddr',	ctypes.c_uint32),
		('DMA_MemoryBaseAddr',	ctypes.c_uint32),
		('DMA_DIR',	ctypes.c_uint32),
		('DMA_BufferSize',	ctypes.c_uint32),
		('DMA_PeripheralInc',	ctypes.c_uint32),
		('DMA_MemoryInc',	ctypes.c_uint32),
		('DMA_PeripheralDataSize',	ctypes.c_uint32),
		('DMA_MemoryDataSize',	ctypes.c_uint32),
		('DMA_Mode',	ctypes.c_uint32),
		('DMA_Priority',	ctypes.c_uint32),
		('DMA_M2M',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_can.h : 

# empty define __STM32F0xx_CAN_H
CAN_InitStatus_Failed = 0x0
CAN_InitStatus_Success = 0x1
CANINITFAILED = 0x0
CANINITOK = 0x1
CAN_Mode_Normal = 0x0
CAN_Mode_LoopBack = 0x1
CAN_Mode_Silent = 0x2
CAN_Mode_Silent_LoopBack = 0x3
CAN_OperatingMode_Initialization = 0x0
CAN_OperatingMode_Normal = 0x1
CAN_OperatingMode_Sleep = 0x2
CAN_ModeStatus_Failed = 0x0
CAN_ModeStatus_Success = 0x1
CAN_SJW_1tq = 0x0
CAN_SJW_2tq = 0x1
CAN_SJW_3tq = 0x2
CAN_SJW_4tq = 0x3
CAN_BS1_1tq = 0x0
CAN_BS1_2tq = 0x1
CAN_BS1_3tq = 0x2
CAN_BS1_4tq = 0x3
CAN_BS1_5tq = 0x4
CAN_BS1_6tq = 0x5
CAN_BS1_7tq = 0x6
CAN_BS1_8tq = 0x7
CAN_BS1_9tq = 0x8
CAN_BS1_10tq = 0x9
CAN_BS1_11tq = 0xA
CAN_BS1_12tq = 0xB
CAN_BS1_13tq = 0xC
CAN_BS1_14tq = 0xD
CAN_BS1_15tq = 0xE
CAN_BS1_16tq = 0xF
CAN_BS2_1tq = 0x0
CAN_BS2_2tq = 0x1
CAN_BS2_3tq = 0x2
CAN_BS2_4tq = 0x3
CAN_BS2_5tq = 0x4
CAN_BS2_6tq = 0x5
CAN_BS2_7tq = 0x6
CAN_BS2_8tq = 0x7
CAN_FilterMode_IdMask = 0x0
CAN_FilterMode_IdList = 0x1
CAN_FilterScale_16bit = 0x0
CAN_FilterScale_32bit = 0x1
CAN_Filter_FIFO0 = 0x0
CAN_Filter_FIFO1 = 0x1
CAN_FilterFIFO0 = 0x0
CAN_FilterFIFO1 = 0x1
CAN_Id_Standard = 0x0
CAN_Id_Extended = 0x4
CAN_ID_STD = 0x0
CAN_ID_EXT = 0x4
CAN_RTR_Data = 0x0
CAN_RTR_Remote = 0x2
CAN_RTR_DATA = 0x0
CAN_RTR_REMOTE = 0x2
CAN_TxStatus_Failed = 0x0
CAN_TxStatus_Ok = 0x1
CAN_TxStatus_Pending = 0x2
CAN_TxStatus_NoMailBox = 0x4
CANTXFAILED = 0x0
CANTXOK = 0x1
CANTXPENDING = 0x2
CAN_NO_MB = 0x4
CAN_FIFO0 = 0x0
CAN_FIFO1 = 0x1
CAN_Sleep_Failed = 0x0
CAN_Sleep_Ok = 0x1
CANSLEEPFAILED = 0x0
CANSLEEPOK = 0x1
CAN_WakeUp_Failed = 0x0
CAN_WakeUp_Ok = 0x1
CANWAKEUPFAILED = 0x0
CANWAKEUPOK = 0x1
CAN_ErrorCode_NoErr = 0x0
CAN_ErrorCode_StuffErr = 0x10
CAN_ErrorCode_FormErr = 0x20
CAN_ErrorCode_ACKErr = 0x30
CAN_ErrorCode_BitRecessiveErr = 0x40
CAN_ErrorCode_BitDominantErr = 0x50
CAN_ErrorCode_CRCErr = 0x60
CAN_ErrorCode_SoftwareSetErr = 0x70
CAN_FLAG_RQCP0 = 0x38000001
CAN_FLAG_RQCP1 = 0x38000100
CAN_FLAG_RQCP2 = 0x38010000
CAN_FLAG_FMP0 = 0x12000003
CAN_FLAG_FF0 = 0x32000008
CAN_FLAG_FOV0 = 0x32000010
CAN_FLAG_FMP1 = 0x14000003
CAN_FLAG_FF1 = 0x34000008
CAN_FLAG_FOV1 = 0x34000010
CAN_FLAG_WKU = 0x31000008
CAN_FLAG_SLAK = 0x31000012
CAN_FLAG_EWG = 0x10F00001
CAN_FLAG_EPV = 0x10F00002
CAN_FLAG_BOF = 0x10F00004
CAN_FLAG_LEC = 0x30F00070
CAN_IT_TME = 0x1
CAN_IT_FMP0 = 0x2
CAN_IT_FF0 = 0x4
CAN_IT_FOV0 = 0x8
CAN_IT_FMP1 = 0x10
CAN_IT_FF1 = 0x20
CAN_IT_FOV1 = 0x40
CAN_IT_WKU = 0x10000
CAN_IT_SLK = 0x20000
CAN_IT_EWG = 0x100
CAN_IT_EPV = 0x200
CAN_IT_BOF = 0x400
CAN_IT_LEC = 0x800
CAN_IT_ERR = 0x8000
CAN_IT_RQCP0 = 0x1
CAN_IT_RQCP1 = 0x1
CAN_IT_RQCP2 = 0x1
# struct CAN_InitTypeDef

class CAN_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CAN_Prescaler',	ctypes.c_uint16),
		('CAN_Mode',	ctypes.c_uint8),
		('CAN_SJW',	ctypes.c_uint8),
		('CAN_BS1',	ctypes.c_uint8),
		('CAN_BS2',	ctypes.c_uint8),
		('CAN_TTCM',	ctypes.c_uint32),
		('CAN_ABOM',	ctypes.c_uint32),
		('CAN_AWUM',	ctypes.c_uint32),
		('CAN_NART',	ctypes.c_uint32),
		('CAN_RFLM',	ctypes.c_uint32),
		('CAN_TXFP',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CAN_FilterInitTypeDef

class CAN_FilterInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CAN_FilterIdHigh',	ctypes.c_uint16),
		('CAN_FilterIdLow',	ctypes.c_uint16),
		('CAN_FilterMaskIdHigh',	ctypes.c_uint16),
		('CAN_FilterMaskIdLow',	ctypes.c_uint16),
		('CAN_FilterFIFOAssignment',	ctypes.c_uint16),
		('CAN_FilterNumber',	ctypes.c_uint8),
		('CAN_FilterMode',	ctypes.c_uint8),
		('CAN_FilterScale',	ctypes.c_uint8),
		('CAN_FilterActivation',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CanTxMsg

class CanTxMsg(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('StdId',	ctypes.c_uint32),
		('ExtId',	ctypes.c_uint32),
		('IDE',	ctypes.c_uint8),
		('RTR',	ctypes.c_uint8),
		('DLC',	ctypes.c_uint8),
		('Data',	ctypes.c_uint8 * 8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CanRxMsg

class CanRxMsg(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('StdId',	ctypes.c_uint32),
		('ExtId',	ctypes.c_uint32),
		('IDE',	ctypes.c_uint8),
		('RTR',	ctypes.c_uint8),
		('DLC',	ctypes.c_uint8),
		('Data',	ctypes.c_uint8 * 8),
		('FMI',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_dbgmcu.h : 

# empty define __STM32F0XX_DBGMCU_H
DBGMCU_STOP = 0x2
DBGMCU_STANDBY = 0x4
DBGMCU_TIM2_STOP = 0x1
DBGMCU_TIM3_STOP = 0x2
DBGMCU_TIM6_STOP = 0x10
DBGMCU_TIM7_STOP = 0x20
DBGMCU_TIM14_STOP = 0x100
DBGMCU_RTC_STOP = 0x400
DBGMCU_WWDG_STOP = 0x800
DBGMCU_IWDG_STOP = 0x1000
DBGMCU_I2C1_SMBUS_TIMEOUT = 0x200000
# Skip DBGMCU_CAN1_STOP : no need parse
DBGMCU_TIM1_STOP = 0x800
DBGMCU_TIM15_STOP = 0x10000
DBGMCU_TIM16_STOP = 0x20000
DBGMCU_TIM17_STOP = 0x40000
# ----------------------------------------

# file stm32f0xx_dac.h : 

# empty define __STM32F0XX_DAC_H
DAC_Trigger_None = 0x0
DAC_Trigger_T6_TRGO = 0x4
DAC_Trigger_T3_TRGO = 0xC
DAC_Trigger_T7_TRGO = 0x14
DAC_Trigger_T15_TRGO = 0x1C
DAC_Trigger_T2_TRGO = 0x24
DAC_Trigger_Ext_IT9 = 0x34
DAC_Trigger_Software = 0x3C
DAC_WaveGeneration_None = 0x0
DAC_WaveGeneration_Noise = 0x40
DAC_WaveGeneration_Triangle = 0x80
DAC_LFSRUnmask_Bit0 = 0x0
DAC_LFSRUnmask_Bits1_0 = 0x100
DAC_LFSRUnmask_Bits2_0 = 0x200
DAC_LFSRUnmask_Bits3_0 = 0x300
DAC_LFSRUnmask_Bits4_0 = 0x400
DAC_LFSRUnmask_Bits5_0 = 0x500
DAC_LFSRUnmask_Bits6_0 = 0x600
DAC_LFSRUnmask_Bits7_0 = 0x700
DAC_LFSRUnmask_Bits8_0 = 0x800
DAC_LFSRUnmask_Bits9_0 = 0x900
DAC_LFSRUnmask_Bits10_0 = 0xA00
DAC_LFSRUnmask_Bits11_0 = 0xB00
DAC_TriangleAmplitude_1 = 0x0
DAC_TriangleAmplitude_3 = 0x100
DAC_TriangleAmplitude_7 = 0x200
DAC_TriangleAmplitude_15 = 0x300
DAC_TriangleAmplitude_31 = 0x400
DAC_TriangleAmplitude_63 = 0x500
DAC_TriangleAmplitude_127 = 0x600
DAC_TriangleAmplitude_255 = 0x700
DAC_TriangleAmplitude_511 = 0x800
DAC_TriangleAmplitude_1023 = 0x900
DAC_TriangleAmplitude_2047 = 0xA00
DAC_TriangleAmplitude_4095 = 0xB00
DAC_OutputBuffer_Enable = 0x0
DAC_OutputBuffer_Disable = 0x2
DAC_Channel_1 = 0x0
DAC_Channel_2 = 0x10
DAC_Align_12b_R = 0x0
DAC_Align_12b_L = 0x4
DAC_Align_8b_R = 0x8
DAC_Wave_Noise = 0x40
DAC_Wave_Triangle = 0x80
DAC_IT_DMAUDR = 0x2000
DAC_FLAG_DMAUDR = 0x2000
# struct DAC_InitTypeDef

class DAC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DAC_Trigger',	ctypes.c_uint32),
		('DAC_WaveGeneration',	ctypes.c_uint32),
		('DAC_LFSRUnmask_TriangleAmplitude',	ctypes.c_uint32),
		('DAC_OutputBuffer',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_pwr.h : 

# empty define __STM32F0XX_PWR_H
PWR_PVDLevel_0 = 0x0
PWR_PVDLevel_1 = 0x20
PWR_PVDLevel_2 = 0x40
PWR_PVDLevel_3 = 0x60
PWR_PVDLevel_4 = 0x80
PWR_PVDLevel_5 = 0xA0
PWR_PVDLevel_6 = 0xC0
PWR_PVDLevel_7 = 0xE0
PWR_WakeUpPin_1 = 0x100
PWR_WakeUpPin_2 = 0x200
PWR_WakeUpPin_3 = 0x400
PWR_WakeUpPin_4 = 0x800
PWR_WakeUpPin_5 = 0x1000
PWR_WakeUpPin_6 = 0x2000
PWR_WakeUpPin_7 = 0x4000
PWR_WakeUpPin_8 = 0x8000
PWR_Regulator_ON = 0x0
PWR_Regulator_LowPower = 0x1
PWR_SLEEPEntry_WFI = 0x1
PWR_SLEEPEntry_WFE = 0x2
PWR_STOPEntry_WFI = 0x1
PWR_STOPEntry_WFE = 0x2
PWR_STOPEntry_SLEEPONEXIT = 0x3
PWR_FLAG_WU = 0x1
PWR_FLAG_SB = 0x2
PWR_FLAG_PVDO = 0x4
PWR_FLAG_VREFINTRDY = 0x8
# ----------------------------------------

# file stm32f0xx_cec.h : 

# empty define __STM32F0XX_CEC_H
CEC_SignalFreeTime_Standard = 0x0
CEC_SignalFreeTime_1T = 0x1
CEC_SignalFreeTime_2T = 0x2
CEC_SignalFreeTime_3T = 0x3
CEC_SignalFreeTime_4T = 0x4
CEC_SignalFreeTime_5T = 0x5
CEC_SignalFreeTime_6T = 0x6
CEC_SignalFreeTime_7T = 0x7
CEC_RxTolerance_Standard = 0x0
CEC_RxTolerance_Extended = 0x8
CEC_StopReception_Off = 0x0
CEC_StopReception_On = 0x10
CEC_BitRisingError_Off = 0x0
CEC_BitRisingError_On = 0x20
CEC_LongBitPeriodError_Off = 0x0
CEC_LongBitPeriodError_On = 0x40
CEC_BRDNoGen_Off = 0x0
CEC_BRDNoGen_On = 0x80
CEC_SFTOption_Off = 0x0
CEC_SFTOption_On = 0x100
CEC_IT_TXACKE = 0x1000
CEC_IT_TXERR = 0x800
CEC_IT_TXUDR = 0x400
CEC_IT_TXEND = 0x200
CEC_IT_TXBR = 0x100
CEC_IT_ARBLST = 0x80
CEC_IT_RXACKE = 0x40
CEC_IT_LBPE = 0x20
CEC_IT_SBPE = 0x10
CEC_IT_BRE = 0x8
CEC_IT_RXOVR = 0x4
CEC_IT_RXEND = 0x2
CEC_IT_RXBR = 0x1
CEC_FLAG_TXACKE = 0x1000
CEC_FLAG_TXERR = 0x800
CEC_FLAG_TXUDR = 0x400
CEC_FLAG_TXEND = 0x200
CEC_FLAG_TXBR = 0x100
CEC_FLAG_ARBLST = 0x80
CEC_FLAG_RXACKE = 0x40
CEC_FLAG_LBPE = 0x20
CEC_FLAG_SBPE = 0x10
CEC_FLAG_BRE = 0x8
CEC_FLAG_RXOVR = 0x4
CEC_FLAG_RXEND = 0x2
CEC_FLAG_RXBR = 0x1
# struct CEC_InitTypeDef

class CEC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CEC_SignalFreeTime',	ctypes.c_uint32),
		('CEC_RxTolerance',	ctypes.c_uint32),
		('CEC_StopReception',	ctypes.c_uint32),
		('CEC_BitRisingError',	ctypes.c_uint32),
		('CEC_LongBitPeriodError',	ctypes.c_uint32),
		('CEC_BRDNoGen',	ctypes.c_uint32),
		('CEC_SFTOption',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx_wwdg.h : 

# empty define __STM32F0XX_WWDG_H
WWDG_Prescaler_1 = 0x0
WWDG_Prescaler_2 = 0x80
WWDG_Prescaler_4 = 0x100
WWDG_Prescaler_8 = 0x180
# ----------------------------------------

# file stm32f0xx_usart.h : 

# empty define __STM32F0XX_USART_H
USART_WordLength_8b = 0x0
USART_WordLength_9b = 0x1000
USART_WordLength_7b = 0x10001000
USART_StopBits_1 = 0x0
USART_StopBits_2 = 0x2000
USART_StopBits_1_5 = 0x3000
USART_Parity_No = 0x0
USART_Parity_Even = 0x400
USART_Parity_Odd = 0x600
USART_Mode_Rx = 0x4
USART_Mode_Tx = 0x8
USART_HardwareFlowControl_None = 0x0
USART_HardwareFlowControl_RTS = 0x100
USART_HardwareFlowControl_CTS = 0x200
USART_HardwareFlowControl_RTS_CTS = 0x300
USART_Clock_Disable = 0x0
USART_Clock_Enable = 0x800
USART_CPOL_Low = 0x0
USART_CPOL_High = 0x400
USART_CPHA_1Edge = 0x0
USART_CPHA_2Edge = 0x200
USART_LastBit_Disable = 0x0
USART_LastBit_Enable = 0x100
USART_DMAReq_Tx = 0x80
USART_DMAReq_Rx = 0x40
USART_DMAOnError_Enable = 0x0
USART_DMAOnError_Disable = 0x2000
USART_WakeUp_IdleLine = 0x0
USART_WakeUp_AddressMark = 0x800
USART_AddressLength_4b = 0x0
USART_AddressLength_7b = 0x10
USART_WakeUpSource_AddressMatch = 0x0
USART_WakeUpSource_StartBit = 0x200000
USART_WakeUpSource_RXNE = 0x300000
USART_LINBreakDetectLength_10b = 0x0
USART_LINBreakDetectLength_11b = 0x20
USART_IrDAMode_LowPower = 0x4
USART_IrDAMode_Normal = 0x0
USART_DEPolarity_High = 0x0
USART_DEPolarity_Low = 0x8000
USART_InvPin_Tx = 0x20000
USART_InvPin_Rx = 0x10000
USART_AutoBaudRate_StartBit = 0x0
USART_AutoBaudRate_FallingEdge = 0x200000
USART_OVRDetection_Enable = 0x0
USART_OVRDetection_Disable = 0x1000
USART_Request_ABRRQ = 0x1
USART_Request_SBKRQ = 0x2
USART_Request_MMRQ = 0x4
USART_Request_RXFRQ = 0x8
USART_Request_TXFRQ = 0x10
USART_FLAG_REACK = 0x400000
USART_FLAG_TEACK = 0x200000
USART_FLAG_WU = 0x100000
USART_FLAG_RWU = 0x80000
USART_FLAG_SBK = 0x40000
USART_FLAG_CM = 0x20000
USART_FLAG_BUSY = 0x10000
USART_FLAG_ABRF = 0x8000
USART_FLAG_ABRE = 0x4000
USART_FLAG_EOB = 0x1000
USART_FLAG_RTO = 0x800
USART_FLAG_nCTSS = 0x400
USART_FLAG_CTS = 0x200
USART_FLAG_LBD = 0x100
USART_FLAG_TXE = 0x80
USART_FLAG_TC = 0x40
USART_FLAG_RXNE = 0x20
USART_FLAG_IDLE = 0x10
USART_FLAG_ORE = 0x8
USART_FLAG_NE = 0x4
USART_FLAG_FE = 0x2
USART_FLAG_PE = 0x1
USART_IT_WU = 0x140316
USART_IT_CM = 0x11010E
USART_IT_EOB = 0xC011B
USART_IT_RTO = 0xB011A
USART_IT_PE = 0x108
USART_IT_TXE = 0x70107
USART_IT_TC = 0x60106
USART_IT_RXNE = 0x50105
USART_IT_IDLE = 0x40104
USART_IT_LBD = 0x80206
USART_IT_CTS = 0x9030A
USART_IT_ERR = 0x300
USART_IT_ORE = 0x30300
USART_IT_NE = 0x20300
USART_IT_FE = 0x10300
# struct USART_InitTypeDef

class USART_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('USART_BaudRate',	ctypes.c_uint32),
		('USART_WordLength',	ctypes.c_uint32),
		('USART_StopBits',	ctypes.c_uint32),
		('USART_Parity',	ctypes.c_uint32),
		('USART_Mode',	ctypes.c_uint32),
		('USART_HardwareFlowControl',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct USART_ClockInitTypeDef

class USART_ClockInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('USART_Clock',	ctypes.c_uint32),
		('USART_CPOL',	ctypes.c_uint32),
		('USART_CPHA',	ctypes.c_uint32),
		('USART_LastBit',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file core_cm0.h : 

# empty define __CORE_CM0_H_GENERIC
# Skip __CM0_CMSIS_VERSION_MAIN : no need parse
# Skip __CM0_CMSIS_VERSION_SUB : no need parse
# Skip __CM0_CMSIS_VERSION : no need parse
# Skip __CORTEX_M : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __FPU_USED : no need parse
# empty define __CORE_CM0_H_DEPENDANT
# Skip __CM0_REV : no need parse
# Skip __NVIC_PRIO_BITS : no need parse
# Skip __Vendor_SysTickConfig : no need parse
# Skip __I : no need parse
# Skip __I : no need parse
# Skip __O : no need parse
# Skip __IO : no need parse
# Skip SCB_CPUID_IMPLEMENTER_Pos : no need parse
# Skip SCB_CPUID_IMPLEMENTER_Msk : no need parse
# Skip SCB_CPUID_VARIANT_Pos : no need parse
# Skip SCB_CPUID_VARIANT_Msk : no need parse
# Skip SCB_CPUID_ARCHITECTURE_Pos : no need parse
# Skip SCB_CPUID_ARCHITECTURE_Msk : no need parse
# Skip SCB_CPUID_PARTNO_Pos : no need parse
# Skip SCB_CPUID_PARTNO_Msk : no need parse
# Skip SCB_CPUID_REVISION_Pos : no need parse
# Skip SCB_CPUID_REVISION_Msk : no need parse
# Skip SCB_ICSR_NMIPENDSET_Pos : no need parse
# Skip SCB_ICSR_NMIPENDSET_Msk : no need parse
# Skip SCB_ICSR_PENDSVSET_Pos : no need parse
# Skip SCB_ICSR_PENDSVSET_Msk : no need parse
# Skip SCB_ICSR_PENDSVCLR_Pos : no need parse
# Skip SCB_ICSR_PENDSVCLR_Msk : no need parse
# Skip SCB_ICSR_PENDSTSET_Pos : no need parse
# Skip SCB_ICSR_PENDSTSET_Msk : no need parse
# Skip SCB_ICSR_PENDSTCLR_Pos : no need parse
# Skip SCB_ICSR_PENDSTCLR_Msk : no need parse
# Skip SCB_ICSR_ISRPREEMPT_Pos : no need parse
# Skip SCB_ICSR_ISRPREEMPT_Msk : no need parse
# Skip SCB_ICSR_ISRPENDING_Pos : no need parse
# Skip SCB_ICSR_ISRPENDING_Msk : no need parse
# Skip SCB_ICSR_VECTPENDING_Pos : no need parse
# Skip SCB_ICSR_VECTPENDING_Msk : no need parse
# Skip SCB_ICSR_VECTACTIVE_Pos : no need parse
# Skip SCB_ICSR_VECTACTIVE_Msk : no need parse
# Skip SCB_AIRCR_VECTKEY_Pos : no need parse
# Skip SCB_AIRCR_VECTKEY_Msk : no need parse
# Skip SCB_AIRCR_VECTKEYSTAT_Pos : no need parse
# Skip SCB_AIRCR_VECTKEYSTAT_Msk : no need parse
# Skip SCB_AIRCR_ENDIANESS_Pos : no need parse
# Skip SCB_AIRCR_ENDIANESS_Msk : no need parse
# Skip SCB_AIRCR_SYSRESETREQ_Pos : no need parse
# Skip SCB_AIRCR_SYSRESETREQ_Msk : no need parse
# Skip SCB_AIRCR_VECTCLRACTIVE_Pos : no need parse
# Skip SCB_AIRCR_VECTCLRACTIVE_Msk : no need parse
# Skip SCB_SCR_SEVONPEND_Pos : no need parse
# Skip SCB_SCR_SEVONPEND_Msk : no need parse
# Skip SCB_SCR_SLEEPDEEP_Pos : no need parse
# Skip SCB_SCR_SLEEPDEEP_Msk : no need parse
# Skip SCB_SCR_SLEEPONEXIT_Pos : no need parse
# Skip SCB_SCR_SLEEPONEXIT_Msk : no need parse
# Skip SCB_CCR_STKALIGN_Pos : no need parse
# Skip SCB_CCR_STKALIGN_Msk : no need parse
# Skip SCB_CCR_UNALIGN_TRP_Pos : no need parse
# Skip SCB_CCR_UNALIGN_TRP_Msk : no need parse
# Skip SCB_SHCSR_SVCALLPENDED_Pos : no need parse
# Skip SCB_SHCSR_SVCALLPENDED_Msk : no need parse
# Skip SysTick_CTRL_COUNTFLAG_Pos : no need parse
# Skip SysTick_CTRL_COUNTFLAG_Msk : no need parse
# Skip SysTick_CTRL_CLKSOURCE_Pos : no need parse
# Skip SysTick_CTRL_CLKSOURCE_Msk : no need parse
# Skip SysTick_CTRL_TICKINT_Pos : no need parse
# Skip SysTick_CTRL_TICKINT_Msk : no need parse
# Skip SysTick_CTRL_ENABLE_Pos : no need parse
# Skip SysTick_CTRL_ENABLE_Msk : no need parse
# Skip SysTick_LOAD_RELOAD_Pos : no need parse
# Skip SysTick_LOAD_RELOAD_Msk : no need parse
# Skip SysTick_VAL_CURRENT_Pos : no need parse
# Skip SysTick_VAL_CURRENT_Msk : no need parse
# Skip SysTick_CALIB_NOREF_Pos : no need parse
# Skip SysTick_CALIB_NOREF_Msk : no need parse
# Skip SysTick_CALIB_SKEW_Pos : no need parse
# Skip SysTick_CALIB_SKEW_Msk : no need parse
# Skip SysTick_CALIB_TENMS_Pos : no need parse
# Skip SysTick_CALIB_TENMS_Msk : no need parse
# Skip SCS_BASE : no need parse
# Skip SysTick_BASE : no need parse
# Skip NVIC_BASE : no need parse
# Skip SCB_BASE : no need parse
# Skip SCB : no need parse
# Skip SysTick : no need parse
# Skip NVIC : no need parse
# struct union <anon-struct-1>::
# struct union <anon-struct-1>:: : parent
# struct APSR_Type
# struct APSR_Type : declaration_method is not struct
# struct union <anon-struct-2>::
# struct union <anon-struct-2>:: : parent
# struct IPSR_Type
# struct IPSR_Type : declaration_method is not struct
# struct union <anon-struct-3>::
# struct union <anon-struct-3>:: : parent
# struct xPSR_Type
# struct xPSR_Type : declaration_method is not struct
# struct union <anon-struct-4>::
# struct union <anon-struct-4>:: : parent
# struct CONTROL_Type
# struct CONTROL_Type : declaration_method is not struct
# struct NVIC_Type

class NVIC_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct SCB_Type

class SCB_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct SysTick_Type

class SysTick_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f0xx.h : 

# Enum FlagStatus , ITStatus
RESET = 0x0
SET = 0x1
# Enum FunctionalState
DISABLE = 0x0
ENABLE = 0x1
# Enum ErrorStatus
ERROR = 0x0
SUCCESS = 0x1
# empty define __STM32F0XX_H
# empty define STM32F051
# empty define STM32F031
# empty define STM32F072
# empty define STM32F030
HSE_VALUE = 0x7A1200
HSE_STARTUP_TIMEOUT = 0x5000
HSI_STARTUP_TIMEOUT = 0x5000
HSI_VALUE = 0x7A1200
HSI14_VALUE = 0xD59F80
HSI48_VALUE = 0x2DC6C00
LSI_VALUE = 0x9C40
LSE_VALUE = 0x8000
__STM32F0XX_STDPERIPH_VERSION_MAIN = 0x1
__STM32F0XX_STDPERIPH_VERSION_SUB1 = 0x5
__STM32F0XX_STDPERIPH_VERSION_SUB2 = 0x0
__STM32F0XX_STDPERIPH_VERSION_RC = 0x0
__STM32F0XX_STDPERIPH_VERSION = 0x1050000
__CM0_REV = 0x0
__MPU_PRESENT = 0x0
__NVIC_PRIO_BITS = 0x2
__Vendor_SysTickConfig = 0x0
# Skip CAL : no need parse
FLASH_BASE = 0x8000000
SRAM_BASE = 0x20000000
PERIPH_BASE = 0x40000000
APBPERIPH_BASE = 0x40000000
AHBPERIPH_BASE = 0x40020000
AHB2PERIPH_BASE = 0x48000000
TIM2_BASE = 0x40000000
TIM3_BASE = 0x40000400
TIM6_BASE = 0x40001000
TIM7_BASE = 0x40001400
TIM14_BASE = 0x40002000
RTC_BASE = 0x40002800
WWDG_BASE = 0x40002C00
IWDG_BASE = 0x40003000
SPI2_BASE = 0x40003800
USART2_BASE = 0x40004400
USART3_BASE = 0x40004800
USART4_BASE = 0x40004C00
USART5_BASE = 0x40005000
I2C1_BASE = 0x40005400
I2C2_BASE = 0x40005800
CAN_BASE = 0x40006400
CRS_BASE = 0x40006C00
PWR_BASE = 0x40007000
DAC_BASE = 0x40007400
CEC_BASE = 0x40007800
SYSCFG_BASE = 0x40010000
COMP_BASE = 0x4001001C
EXTI_BASE = 0x40010400
USART6_BASE = 0x40011400
USART7_BASE = 0x40011800
USART8_BASE = 0x40011C00
ADC1_BASE = 0x40012400
ADC_BASE = 0x40012708
TIM1_BASE = 0x40012C00
SPI1_BASE = 0x40013000
USART1_BASE = 0x40013800
TIM15_BASE = 0x40014000
TIM16_BASE = 0x40014400
TIM17_BASE = 0x40014800
DBGMCU_BASE = 0x40015800
DMA1_BASE = 0x40020000
DMA1_Channel1_BASE = 0x40020008
DMA1_Channel2_BASE = 0x4002001C
DMA1_Channel3_BASE = 0x40020030
DMA1_Channel4_BASE = 0x40020044
DMA1_Channel5_BASE = 0x40020058
DMA1_Channel6_BASE = 0x4002006C
DMA1_Channel7_BASE = 0x40020080
DMA2_BASE = 0x40020400
DMA2_Channel1_BASE = 0x40020408
DMA2_Channel2_BASE = 0x4002041C
DMA2_Channel3_BASE = 0x40020430
DMA2_Channel4_BASE = 0x40020444
DMA2_Channel5_BASE = 0x40020458
RCC_BASE = 0x40021000
FLASH_R_BASE = 0x40022000
OB_BASE = 0x1FFFF800
CRC_BASE = 0x40023000
TSC_BASE = 0x40024000
GPIOA_BASE = 0x48000000
GPIOB_BASE = 0x48000400
GPIOC_BASE = 0x48000800
GPIOD_BASE = 0x48000C00
GPIOE_BASE = 0x48001000
GPIOF_BASE = 0x48001400
TIM2 = 0x40000000
TIM3 = 0x40000400
TIM6 = 0x40001000
TIM7 = 0x40001400
TIM14 = 0x40002000
RTC = 0x40002800
WWDG = 0x40002C00
IWDG = 0x40003000
SPI2 = 0x40003800
USART2 = 0x40004400
USART3 = 0x40004800
USART4 = 0x40004C00
USART5 = 0x40005000
I2C1 = 0x40005400
I2C2 = 0x40005800
CAN = 0x40006400
CRS = 0x40006C00
PWR = 0x40007000
DAC = 0x40007400
CEC = 0x40007800
SYSCFG = 0x40010000
COMP = 0x4001001C
EXTI = 0x40010400
USART6 = 0x40011400
USART7 = 0x40011800
USART8 = 0x40011C00
ADC1 = 0x40012400
ADC = 0x40012708
TIM1 = 0x40012C00
SPI1 = 0x40013000
USART1 = 0x40013800
TIM15 = 0x40014000
TIM16 = 0x40014400
TIM17 = 0x40014800
DBGMCU = 0x40015800
DMA1 = 0x40020000
DMA1_Channel1 = 0x40020008
DMA1_Channel2 = 0x4002001C
DMA1_Channel3 = 0x40020030
DMA1_Channel4 = 0x40020044
DMA1_Channel5 = 0x40020058
DMA1_Channel6 = 0x4002006C
DMA1_Channel7 = 0x40020080
DMA2 = 0x40020400
DMA2_Channel1 = 0x40020408
DMA2_Channel2 = 0x4002041C
DMA2_Channel3 = 0x40020430
DMA2_Channel4 = 0x40020444
DMA2_Channel5 = 0x40020458
FLASH = 0x40022000
OB = 0x1FFFF800
RCC = 0x40021000
CRC = 0x40023000
TSC = 0x40024000
GPIOA = 0x48000000
GPIOB = 0x48000400
GPIOC = 0x48000800
GPIOD = 0x48000C00
GPIOE = 0x48001000
GPIOF = 0x48001400
ADC_ISR_AWD = 0x80
ADC_ISR_OVR = 0x10
ADC_ISR_EOSEQ = 0x8
ADC_ISR_EOC = 0x4
ADC_ISR_EOSMP = 0x2
ADC_ISR_ADRDY = 0x1
ADC_ISR_EOS = 0x8
ADC_IER_AWDIE = 0x80
ADC_IER_OVRIE = 0x10
ADC_IER_EOSEQIE = 0x8
ADC_IER_EOCIE = 0x4
ADC_IER_EOSMPIE = 0x2
ADC_IER_ADRDYIE = 0x1
ADC_IER_EOSIE = 0x8
ADC_CR_ADCAL = 0x80000000
ADC_CR_ADSTP = 0x10
ADC_CR_ADSTART = 0x4
ADC_CR_ADDIS = 0x2
ADC_CR_ADEN = 0x1
ADC_CFGR1_AWDCH = 0x7C000000
ADC_CFGR1_AWDCH_0 = 0x4000000
ADC_CFGR1_AWDCH_1 = 0x8000000
ADC_CFGR1_AWDCH_2 = 0x10000000
ADC_CFGR1_AWDCH_3 = 0x20000000
ADC_CFGR1_AWDCH_4 = 0x40000000
ADC_CFGR1_AWDEN = 0x800000
ADC_CFGR1_AWDSGL = 0x400000
ADC_CFGR1_DISCEN = 0x10000
ADC_CFGR1_AUTOFF = 0x8000
ADC_CFGR1_WAIT = 0x4000
ADC_CFGR1_CONT = 0x2000
ADC_CFGR1_OVRMOD = 0x1000
ADC_CFGR1_EXTEN = 0xC00
ADC_CFGR1_EXTEN_0 = 0x400
ADC_CFGR1_EXTEN_1 = 0x800
ADC_CFGR1_EXTSEL = 0x1C0
ADC_CFGR1_EXTSEL_0 = 0x40
ADC_CFGR1_EXTSEL_1 = 0x80
ADC_CFGR1_EXTSEL_2 = 0x100
ADC_CFGR1_ALIGN = 0x20
ADC_CFGR1_RES = 0x18
ADC_CFGR1_RES_0 = 0x8
ADC_CFGR1_RES_1 = 0x10
ADC_CFGR1_SCANDIR = 0x4
ADC_CFGR1_DMACFG = 0x2
ADC_CFGR1_DMAEN = 0x1
ADC_CFGR1_AUTDLY = 0x4000
ADC_CFGR2_CKMODE = 0xC0000000
ADC_CFGR2_CKMODE_1 = 0x80000000
ADC_CFGR2_CKMODE_0 = 0x40000000
ADC_CFGR2_JITOFFDIV4 = 0x80000000
ADC_CFGR2_JITOFFDIV2 = 0x40000000
ADC_SMPR_SMP = 0x7
ADC_SMPR_SMP_0 = 0x1
ADC_SMPR_SMP_1 = 0x2
ADC_SMPR_SMP_2 = 0x4
ADC_SMPR1_SMPR = 0x7
ADC_SMPR1_SMPR_0 = 0x1
ADC_SMPR1_SMPR_1 = 0x2
ADC_SMPR1_SMPR_2 = 0x4
ADC_TR_HT = 0xFFF0000
ADC_TR_LT = 0xFFF
ADC_HTR_HT = 0xFFF0000
ADC_LTR_LT = 0xFFF
ADC_CHSELR_CHSEL18 = 0x40000
ADC_CHSELR_CHSEL17 = 0x20000
ADC_CHSELR_CHSEL16 = 0x10000
ADC_CHSELR_CHSEL15 = 0x8000
ADC_CHSELR_CHSEL14 = 0x4000
ADC_CHSELR_CHSEL13 = 0x2000
ADC_CHSELR_CHSEL12 = 0x1000
ADC_CHSELR_CHSEL11 = 0x800
ADC_CHSELR_CHSEL10 = 0x400
ADC_CHSELR_CHSEL9 = 0x200
ADC_CHSELR_CHSEL8 = 0x100
ADC_CHSELR_CHSEL7 = 0x80
ADC_CHSELR_CHSEL6 = 0x40
ADC_CHSELR_CHSEL5 = 0x20
ADC_CHSELR_CHSEL4 = 0x10
ADC_CHSELR_CHSEL3 = 0x8
ADC_CHSELR_CHSEL2 = 0x4
ADC_CHSELR_CHSEL1 = 0x2
ADC_CHSELR_CHSEL0 = 0x1
ADC_DR_DATA = 0xFFFF
ADC_CCR_VBATEN = 0x1000000
ADC_CCR_TSEN = 0x800000
ADC_CCR_VREFEN = 0x400000
CAN_MCR_INRQ = 0x1
CAN_MCR_SLEEP = 0x2
CAN_MCR_TXFP = 0x4
CAN_MCR_RFLM = 0x8
CAN_MCR_NART = 0x10
CAN_MCR_AWUM = 0x20
CAN_MCR_ABOM = 0x40
CAN_MCR_TTCM = 0x80
CAN_MCR_RESET = 0x8000
CAN_MSR_INAK = 0x1
CAN_MSR_SLAK = 0x2
CAN_MSR_ERRI = 0x4
CAN_MSR_WKUI = 0x8
CAN_MSR_SLAKI = 0x10
CAN_MSR_TXM = 0x100
CAN_MSR_RXM = 0x200
CAN_MSR_SAMP = 0x400
CAN_MSR_RX = 0x800
CAN_TSR_RQCP0 = 0x1
CAN_TSR_TXOK0 = 0x2
CAN_TSR_ALST0 = 0x4
CAN_TSR_TERR0 = 0x8
CAN_TSR_ABRQ0 = 0x80
CAN_TSR_RQCP1 = 0x100
CAN_TSR_TXOK1 = 0x200
CAN_TSR_ALST1 = 0x400
CAN_TSR_TERR1 = 0x800
CAN_TSR_ABRQ1 = 0x8000
CAN_TSR_RQCP2 = 0x10000
CAN_TSR_TXOK2 = 0x20000
CAN_TSR_ALST2 = 0x40000
CAN_TSR_TERR2 = 0x80000
CAN_TSR_ABRQ2 = 0x800000
CAN_TSR_CODE = 0x3000000
CAN_TSR_TME = 0x1C000000
CAN_TSR_TME0 = 0x4000000
CAN_TSR_TME1 = 0x8000000
CAN_TSR_TME2 = 0x10000000
CAN_TSR_LOW = 0xE0000000
CAN_TSR_LOW0 = 0x20000000
CAN_TSR_LOW1 = 0x40000000
CAN_TSR_LOW2 = 0x80000000
CAN_RF0R_FMP0 = 0x3
CAN_RF0R_FULL0 = 0x8
CAN_RF0R_FOVR0 = 0x10
CAN_RF0R_RFOM0 = 0x20
CAN_RF1R_FMP1 = 0x3
CAN_RF1R_FULL1 = 0x8
CAN_RF1R_FOVR1 = 0x10
CAN_RF1R_RFOM1 = 0x20
CAN_IER_TMEIE = 0x1
CAN_IER_FMPIE0 = 0x2
CAN_IER_FFIE0 = 0x4
CAN_IER_FOVIE0 = 0x8
CAN_IER_FMPIE1 = 0x10
CAN_IER_FFIE1 = 0x20
CAN_IER_FOVIE1 = 0x40
CAN_IER_EWGIE = 0x100
CAN_IER_EPVIE = 0x200
CAN_IER_BOFIE = 0x400
CAN_IER_LECIE = 0x800
CAN_IER_ERRIE = 0x8000
CAN_IER_WKUIE = 0x10000
CAN_IER_SLKIE = 0x20000
CAN_ESR_EWGF = 0x1
CAN_ESR_EPVF = 0x2
CAN_ESR_BOFF = 0x4
CAN_ESR_LEC = 0x70
CAN_ESR_LEC_0 = 0x10
CAN_ESR_LEC_1 = 0x20
CAN_ESR_LEC_2 = 0x40
CAN_ESR_TEC = 0xFF0000
CAN_ESR_REC = 0xFF000000
CAN_BTR_BRP = 0x3FF
CAN_BTR_TS1 = 0xF0000
CAN_BTR_TS2 = 0x700000
CAN_BTR_SJW = 0x3000000
CAN_BTR_LBKM = 0x40000000
CAN_BTR_SILM = 0x80000000
CAN_TI0R_TXRQ = 0x1
CAN_TI0R_RTR = 0x2
CAN_TI0R_IDE = 0x4
CAN_TI0R_EXID = 0x1FFFF8
CAN_TI0R_STID = 0xFFE00000
CAN_TDT0R_DLC = 0xF
CAN_TDT0R_TGT = 0x100
CAN_TDT0R_TIME = 0xFFFF0000
CAN_TDL0R_DATA0 = 0xFF
CAN_TDL0R_DATA1 = 0xFF00
CAN_TDL0R_DATA2 = 0xFF0000
CAN_TDL0R_DATA3 = 0xFF000000
CAN_TDH0R_DATA4 = 0xFF
CAN_TDH0R_DATA5 = 0xFF00
CAN_TDH0R_DATA6 = 0xFF0000
CAN_TDH0R_DATA7 = 0xFF000000
CAN_TI1R_TXRQ = 0x1
CAN_TI1R_RTR = 0x2
CAN_TI1R_IDE = 0x4
CAN_TI1R_EXID = 0x1FFFF8
CAN_TI1R_STID = 0xFFE00000
CAN_TDT1R_DLC = 0xF
CAN_TDT1R_TGT = 0x100
CAN_TDT1R_TIME = 0xFFFF0000
CAN_TDL1R_DATA0 = 0xFF
CAN_TDL1R_DATA1 = 0xFF00
CAN_TDL1R_DATA2 = 0xFF0000
CAN_TDL1R_DATA3 = 0xFF000000
CAN_TDH1R_DATA4 = 0xFF
CAN_TDH1R_DATA5 = 0xFF00
CAN_TDH1R_DATA6 = 0xFF0000
CAN_TDH1R_DATA7 = 0xFF000000
CAN_TI2R_TXRQ = 0x1
CAN_TI2R_RTR = 0x2
CAN_TI2R_IDE = 0x4
CAN_TI2R_EXID = 0x1FFFF8
CAN_TI2R_STID = 0xFFE00000
CAN_TDT2R_DLC = 0xF
CAN_TDT2R_TGT = 0x100
CAN_TDT2R_TIME = 0xFFFF0000
CAN_TDL2R_DATA0 = 0xFF
CAN_TDL2R_DATA1 = 0xFF00
CAN_TDL2R_DATA2 = 0xFF0000
CAN_TDL2R_DATA3 = 0xFF000000
CAN_TDH2R_DATA4 = 0xFF
CAN_TDH2R_DATA5 = 0xFF00
CAN_TDH2R_DATA6 = 0xFF0000
CAN_TDH2R_DATA7 = 0xFF000000
CAN_RI0R_RTR = 0x2
CAN_RI0R_IDE = 0x4
CAN_RI0R_EXID = 0x1FFFF8
CAN_RI0R_STID = 0xFFE00000
CAN_RDT0R_DLC = 0xF
CAN_RDT0R_FMI = 0xFF00
CAN_RDT0R_TIME = 0xFFFF0000
CAN_RDL0R_DATA0 = 0xFF
CAN_RDL0R_DATA1 = 0xFF00
CAN_RDL0R_DATA2 = 0xFF0000
CAN_RDL0R_DATA3 = 0xFF000000
CAN_RDH0R_DATA4 = 0xFF
CAN_RDH0R_DATA5 = 0xFF00
CAN_RDH0R_DATA6 = 0xFF0000
CAN_RDH0R_DATA7 = 0xFF000000
CAN_RI1R_RTR = 0x2
CAN_RI1R_IDE = 0x4
CAN_RI1R_EXID = 0x1FFFF8
CAN_RI1R_STID = 0xFFE00000
CAN_RDT1R_DLC = 0xF
CAN_RDT1R_FMI = 0xFF00
CAN_RDT1R_TIME = 0xFFFF0000
CAN_RDL1R_DATA0 = 0xFF
CAN_RDL1R_DATA1 = 0xFF00
CAN_RDL1R_DATA2 = 0xFF0000
CAN_RDL1R_DATA3 = 0xFF000000
CAN_RDH1R_DATA4 = 0xFF
CAN_RDH1R_DATA5 = 0xFF00
CAN_RDH1R_DATA6 = 0xFF0000
CAN_RDH1R_DATA7 = 0xFF000000
CAN_FMR_FINIT = 0x1
CAN_FM1R_FBM = 0x3FFF
CAN_FM1R_FBM0 = 0x1
CAN_FM1R_FBM1 = 0x2
CAN_FM1R_FBM2 = 0x4
CAN_FM1R_FBM3 = 0x8
CAN_FM1R_FBM4 = 0x10
CAN_FM1R_FBM5 = 0x20
CAN_FM1R_FBM6 = 0x40
CAN_FM1R_FBM7 = 0x80
CAN_FM1R_FBM8 = 0x100
CAN_FM1R_FBM9 = 0x200
CAN_FM1R_FBM10 = 0x400
CAN_FM1R_FBM11 = 0x800
CAN_FM1R_FBM12 = 0x1000
CAN_FM1R_FBM13 = 0x2000
CAN_FS1R_FSC = 0x3FFF
CAN_FS1R_FSC0 = 0x1
CAN_FS1R_FSC1 = 0x2
CAN_FS1R_FSC2 = 0x4
CAN_FS1R_FSC3 = 0x8
CAN_FS1R_FSC4 = 0x10
CAN_FS1R_FSC5 = 0x20
CAN_FS1R_FSC6 = 0x40
CAN_FS1R_FSC7 = 0x80
CAN_FS1R_FSC8 = 0x100
CAN_FS1R_FSC9 = 0x200
CAN_FS1R_FSC10 = 0x400
CAN_FS1R_FSC11 = 0x800
CAN_FS1R_FSC12 = 0x1000
CAN_FS1R_FSC13 = 0x2000
CAN_FFA1R_FFA = 0x3FFF
CAN_FFA1R_FFA0 = 0x1
CAN_FFA1R_FFA1 = 0x2
CAN_FFA1R_FFA2 = 0x4
CAN_FFA1R_FFA3 = 0x8
CAN_FFA1R_FFA4 = 0x10
CAN_FFA1R_FFA5 = 0x20
CAN_FFA1R_FFA6 = 0x40
CAN_FFA1R_FFA7 = 0x80
CAN_FFA1R_FFA8 = 0x100
CAN_FFA1R_FFA9 = 0x200
CAN_FFA1R_FFA10 = 0x400
CAN_FFA1R_FFA11 = 0x800
CAN_FFA1R_FFA12 = 0x1000
CAN_FFA1R_FFA13 = 0x2000
CAN_FA1R_FACT = 0x3FFF
CAN_FA1R_FACT0 = 0x1
CAN_FA1R_FACT1 = 0x2
CAN_FA1R_FACT2 = 0x4
CAN_FA1R_FACT3 = 0x8
CAN_FA1R_FACT4 = 0x10
CAN_FA1R_FACT5 = 0x20
CAN_FA1R_FACT6 = 0x40
CAN_FA1R_FACT7 = 0x80
CAN_FA1R_FACT8 = 0x100
CAN_FA1R_FACT9 = 0x200
CAN_FA1R_FACT10 = 0x400
CAN_FA1R_FACT11 = 0x800
CAN_FA1R_FACT12 = 0x1000
CAN_FA1R_FACT13 = 0x2000
CAN_F0R1_FB0 = 0x1
CAN_F0R1_FB1 = 0x2
CAN_F0R1_FB2 = 0x4
CAN_F0R1_FB3 = 0x8
CAN_F0R1_FB4 = 0x10
CAN_F0R1_FB5 = 0x20
CAN_F0R1_FB6 = 0x40
CAN_F0R1_FB7 = 0x80
CAN_F0R1_FB8 = 0x100
CAN_F0R1_FB9 = 0x200
CAN_F0R1_FB10 = 0x400
CAN_F0R1_FB11 = 0x800
CAN_F0R1_FB12 = 0x1000
CAN_F0R1_FB13 = 0x2000
CAN_F0R1_FB14 = 0x4000
CAN_F0R1_FB15 = 0x8000
CAN_F0R1_FB16 = 0x10000
CAN_F0R1_FB17 = 0x20000
CAN_F0R1_FB18 = 0x40000
CAN_F0R1_FB19 = 0x80000
CAN_F0R1_FB20 = 0x100000
CAN_F0R1_FB21 = 0x200000
CAN_F0R1_FB22 = 0x400000
CAN_F0R1_FB23 = 0x800000
CAN_F0R1_FB24 = 0x1000000
CAN_F0R1_FB25 = 0x2000000
CAN_F0R1_FB26 = 0x4000000
CAN_F0R1_FB27 = 0x8000000
CAN_F0R1_FB28 = 0x10000000
CAN_F0R1_FB29 = 0x20000000
CAN_F0R1_FB30 = 0x40000000
CAN_F0R1_FB31 = 0x80000000
CAN_F1R1_FB0 = 0x1
CAN_F1R1_FB1 = 0x2
CAN_F1R1_FB2 = 0x4
CAN_F1R1_FB3 = 0x8
CAN_F1R1_FB4 = 0x10
CAN_F1R1_FB5 = 0x20
CAN_F1R1_FB6 = 0x40
CAN_F1R1_FB7 = 0x80
CAN_F1R1_FB8 = 0x100
CAN_F1R1_FB9 = 0x200
CAN_F1R1_FB10 = 0x400
CAN_F1R1_FB11 = 0x800
CAN_F1R1_FB12 = 0x1000
CAN_F1R1_FB13 = 0x2000
CAN_F1R1_FB14 = 0x4000
CAN_F1R1_FB15 = 0x8000
CAN_F1R1_FB16 = 0x10000
CAN_F1R1_FB17 = 0x20000
CAN_F1R1_FB18 = 0x40000
CAN_F1R1_FB19 = 0x80000
CAN_F1R1_FB20 = 0x100000
CAN_F1R1_FB21 = 0x200000
CAN_F1R1_FB22 = 0x400000
CAN_F1R1_FB23 = 0x800000
CAN_F1R1_FB24 = 0x1000000
CAN_F1R1_FB25 = 0x2000000
CAN_F1R1_FB26 = 0x4000000
CAN_F1R1_FB27 = 0x8000000
CAN_F1R1_FB28 = 0x10000000
CAN_F1R1_FB29 = 0x20000000
CAN_F1R1_FB30 = 0x40000000
CAN_F1R1_FB31 = 0x80000000
CAN_F2R1_FB0 = 0x1
CAN_F2R1_FB1 = 0x2
CAN_F2R1_FB2 = 0x4
CAN_F2R1_FB3 = 0x8
CAN_F2R1_FB4 = 0x10
CAN_F2R1_FB5 = 0x20
CAN_F2R1_FB6 = 0x40
CAN_F2R1_FB7 = 0x80
CAN_F2R1_FB8 = 0x100
CAN_F2R1_FB9 = 0x200
CAN_F2R1_FB10 = 0x400
CAN_F2R1_FB11 = 0x800
CAN_F2R1_FB12 = 0x1000
CAN_F2R1_FB13 = 0x2000
CAN_F2R1_FB14 = 0x4000
CAN_F2R1_FB15 = 0x8000
CAN_F2R1_FB16 = 0x10000
CAN_F2R1_FB17 = 0x20000
CAN_F2R1_FB18 = 0x40000
CAN_F2R1_FB19 = 0x80000
CAN_F2R1_FB20 = 0x100000
CAN_F2R1_FB21 = 0x200000
CAN_F2R1_FB22 = 0x400000
CAN_F2R1_FB23 = 0x800000
CAN_F2R1_FB24 = 0x1000000
CAN_F2R1_FB25 = 0x2000000
CAN_F2R1_FB26 = 0x4000000
CAN_F2R1_FB27 = 0x8000000
CAN_F2R1_FB28 = 0x10000000
CAN_F2R1_FB29 = 0x20000000
CAN_F2R1_FB30 = 0x40000000
CAN_F2R1_FB31 = 0x80000000
CAN_F3R1_FB0 = 0x1
CAN_F3R1_FB1 = 0x2
CAN_F3R1_FB2 = 0x4
CAN_F3R1_FB3 = 0x8
CAN_F3R1_FB4 = 0x10
CAN_F3R1_FB5 = 0x20
CAN_F3R1_FB6 = 0x40
CAN_F3R1_FB7 = 0x80
CAN_F3R1_FB8 = 0x100
CAN_F3R1_FB9 = 0x200
CAN_F3R1_FB10 = 0x400
CAN_F3R1_FB11 = 0x800
CAN_F3R1_FB12 = 0x1000
CAN_F3R1_FB13 = 0x2000
CAN_F3R1_FB14 = 0x4000
CAN_F3R1_FB15 = 0x8000
CAN_F3R1_FB16 = 0x10000
CAN_F3R1_FB17 = 0x20000
CAN_F3R1_FB18 = 0x40000
CAN_F3R1_FB19 = 0x80000
CAN_F3R1_FB20 = 0x100000
CAN_F3R1_FB21 = 0x200000
CAN_F3R1_FB22 = 0x400000
CAN_F3R1_FB23 = 0x800000
CAN_F3R1_FB24 = 0x1000000
CAN_F3R1_FB25 = 0x2000000
CAN_F3R1_FB26 = 0x4000000
CAN_F3R1_FB27 = 0x8000000
CAN_F3R1_FB28 = 0x10000000
CAN_F3R1_FB29 = 0x20000000
CAN_F3R1_FB30 = 0x40000000
CAN_F3R1_FB31 = 0x80000000
CAN_F4R1_FB0 = 0x1
CAN_F4R1_FB1 = 0x2
CAN_F4R1_FB2 = 0x4
CAN_F4R1_FB3 = 0x8
CAN_F4R1_FB4 = 0x10
CAN_F4R1_FB5 = 0x20
CAN_F4R1_FB6 = 0x40
CAN_F4R1_FB7 = 0x80
CAN_F4R1_FB8 = 0x100
CAN_F4R1_FB9 = 0x200
CAN_F4R1_FB10 = 0x400
CAN_F4R1_FB11 = 0x800
CAN_F4R1_FB12 = 0x1000
CAN_F4R1_FB13 = 0x2000
CAN_F4R1_FB14 = 0x4000
CAN_F4R1_FB15 = 0x8000
CAN_F4R1_FB16 = 0x10000
CAN_F4R1_FB17 = 0x20000
CAN_F4R1_FB18 = 0x40000
CAN_F4R1_FB19 = 0x80000
CAN_F4R1_FB20 = 0x100000
CAN_F4R1_FB21 = 0x200000
CAN_F4R1_FB22 = 0x400000
CAN_F4R1_FB23 = 0x800000
CAN_F4R1_FB24 = 0x1000000
CAN_F4R1_FB25 = 0x2000000
CAN_F4R1_FB26 = 0x4000000
CAN_F4R1_FB27 = 0x8000000
CAN_F4R1_FB28 = 0x10000000
CAN_F4R1_FB29 = 0x20000000
CAN_F4R1_FB30 = 0x40000000
CAN_F4R1_FB31 = 0x80000000
CAN_F5R1_FB0 = 0x1
CAN_F5R1_FB1 = 0x2
CAN_F5R1_FB2 = 0x4
CAN_F5R1_FB3 = 0x8
CAN_F5R1_FB4 = 0x10
CAN_F5R1_FB5 = 0x20
CAN_F5R1_FB6 = 0x40
CAN_F5R1_FB7 = 0x80
CAN_F5R1_FB8 = 0x100
CAN_F5R1_FB9 = 0x200
CAN_F5R1_FB10 = 0x400
CAN_F5R1_FB11 = 0x800
CAN_F5R1_FB12 = 0x1000
CAN_F5R1_FB13 = 0x2000
CAN_F5R1_FB14 = 0x4000
CAN_F5R1_FB15 = 0x8000
CAN_F5R1_FB16 = 0x10000
CAN_F5R1_FB17 = 0x20000
CAN_F5R1_FB18 = 0x40000
CAN_F5R1_FB19 = 0x80000
CAN_F5R1_FB20 = 0x100000
CAN_F5R1_FB21 = 0x200000
CAN_F5R1_FB22 = 0x400000
CAN_F5R1_FB23 = 0x800000
CAN_F5R1_FB24 = 0x1000000
CAN_F5R1_FB25 = 0x2000000
CAN_F5R1_FB26 = 0x4000000
CAN_F5R1_FB27 = 0x8000000
CAN_F5R1_FB28 = 0x10000000
CAN_F5R1_FB29 = 0x20000000
CAN_F5R1_FB30 = 0x40000000
CAN_F5R1_FB31 = 0x80000000
CAN_F6R1_FB0 = 0x1
CAN_F6R1_FB1 = 0x2
CAN_F6R1_FB2 = 0x4
CAN_F6R1_FB3 = 0x8
CAN_F6R1_FB4 = 0x10
CAN_F6R1_FB5 = 0x20
CAN_F6R1_FB6 = 0x40
CAN_F6R1_FB7 = 0x80
CAN_F6R1_FB8 = 0x100
CAN_F6R1_FB9 = 0x200
CAN_F6R1_FB10 = 0x400
CAN_F6R1_FB11 = 0x800
CAN_F6R1_FB12 = 0x1000
CAN_F6R1_FB13 = 0x2000
CAN_F6R1_FB14 = 0x4000
CAN_F6R1_FB15 = 0x8000
CAN_F6R1_FB16 = 0x10000
CAN_F6R1_FB17 = 0x20000
CAN_F6R1_FB18 = 0x40000
CAN_F6R1_FB19 = 0x80000
CAN_F6R1_FB20 = 0x100000
CAN_F6R1_FB21 = 0x200000
CAN_F6R1_FB22 = 0x400000
CAN_F6R1_FB23 = 0x800000
CAN_F6R1_FB24 = 0x1000000
CAN_F6R1_FB25 = 0x2000000
CAN_F6R1_FB26 = 0x4000000
CAN_F6R1_FB27 = 0x8000000
CAN_F6R1_FB28 = 0x10000000
CAN_F6R1_FB29 = 0x20000000
CAN_F6R1_FB30 = 0x40000000
CAN_F6R1_FB31 = 0x80000000
CAN_F7R1_FB0 = 0x1
CAN_F7R1_FB1 = 0x2
CAN_F7R1_FB2 = 0x4
CAN_F7R1_FB3 = 0x8
CAN_F7R1_FB4 = 0x10
CAN_F7R1_FB5 = 0x20
CAN_F7R1_FB6 = 0x40
CAN_F7R1_FB7 = 0x80
CAN_F7R1_FB8 = 0x100
CAN_F7R1_FB9 = 0x200
CAN_F7R1_FB10 = 0x400
CAN_F7R1_FB11 = 0x800
CAN_F7R1_FB12 = 0x1000
CAN_F7R1_FB13 = 0x2000
CAN_F7R1_FB14 = 0x4000
CAN_F7R1_FB15 = 0x8000
CAN_F7R1_FB16 = 0x10000
CAN_F7R1_FB17 = 0x20000
CAN_F7R1_FB18 = 0x40000
CAN_F7R1_FB19 = 0x80000
CAN_F7R1_FB20 = 0x100000
CAN_F7R1_FB21 = 0x200000
CAN_F7R1_FB22 = 0x400000
CAN_F7R1_FB23 = 0x800000
CAN_F7R1_FB24 = 0x1000000
CAN_F7R1_FB25 = 0x2000000
CAN_F7R1_FB26 = 0x4000000
CAN_F7R1_FB27 = 0x8000000
CAN_F7R1_FB28 = 0x10000000
CAN_F7R1_FB29 = 0x20000000
CAN_F7R1_FB30 = 0x40000000
CAN_F7R1_FB31 = 0x80000000
CAN_F8R1_FB0 = 0x1
CAN_F8R1_FB1 = 0x2
CAN_F8R1_FB2 = 0x4
CAN_F8R1_FB3 = 0x8
CAN_F8R1_FB4 = 0x10
CAN_F8R1_FB5 = 0x20
CAN_F8R1_FB6 = 0x40
CAN_F8R1_FB7 = 0x80
CAN_F8R1_FB8 = 0x100
CAN_F8R1_FB9 = 0x200
CAN_F8R1_FB10 = 0x400
CAN_F8R1_FB11 = 0x800
CAN_F8R1_FB12 = 0x1000
CAN_F8R1_FB13 = 0x2000
CAN_F8R1_FB14 = 0x4000
CAN_F8R1_FB15 = 0x8000
CAN_F8R1_FB16 = 0x10000
CAN_F8R1_FB17 = 0x20000
CAN_F8R1_FB18 = 0x40000
CAN_F8R1_FB19 = 0x80000
CAN_F8R1_FB20 = 0x100000
CAN_F8R1_FB21 = 0x200000
CAN_F8R1_FB22 = 0x400000
CAN_F8R1_FB23 = 0x800000
CAN_F8R1_FB24 = 0x1000000
CAN_F8R1_FB25 = 0x2000000
CAN_F8R1_FB26 = 0x4000000
CAN_F8R1_FB27 = 0x8000000
CAN_F8R1_FB28 = 0x10000000
CAN_F8R1_FB29 = 0x20000000
CAN_F8R1_FB30 = 0x40000000
CAN_F8R1_FB31 = 0x80000000
CAN_F9R1_FB0 = 0x1
CAN_F9R1_FB1 = 0x2
CAN_F9R1_FB2 = 0x4
CAN_F9R1_FB3 = 0x8
CAN_F9R1_FB4 = 0x10
CAN_F9R1_FB5 = 0x20
CAN_F9R1_FB6 = 0x40
CAN_F9R1_FB7 = 0x80
CAN_F9R1_FB8 = 0x100
CAN_F9R1_FB9 = 0x200
CAN_F9R1_FB10 = 0x400
CAN_F9R1_FB11 = 0x800
CAN_F9R1_FB12 = 0x1000
CAN_F9R1_FB13 = 0x2000
CAN_F9R1_FB14 = 0x4000
CAN_F9R1_FB15 = 0x8000
CAN_F9R1_FB16 = 0x10000
CAN_F9R1_FB17 = 0x20000
CAN_F9R1_FB18 = 0x40000
CAN_F9R1_FB19 = 0x80000
CAN_F9R1_FB20 = 0x100000
CAN_F9R1_FB21 = 0x200000
CAN_F9R1_FB22 = 0x400000
CAN_F9R1_FB23 = 0x800000
CAN_F9R1_FB24 = 0x1000000
CAN_F9R1_FB25 = 0x2000000
CAN_F9R1_FB26 = 0x4000000
CAN_F9R1_FB27 = 0x8000000
CAN_F9R1_FB28 = 0x10000000
CAN_F9R1_FB29 = 0x20000000
CAN_F9R1_FB30 = 0x40000000
CAN_F9R1_FB31 = 0x80000000
CAN_F10R1_FB0 = 0x1
CAN_F10R1_FB1 = 0x2
CAN_F10R1_FB2 = 0x4
CAN_F10R1_FB3 = 0x8
CAN_F10R1_FB4 = 0x10
CAN_F10R1_FB5 = 0x20
CAN_F10R1_FB6 = 0x40
CAN_F10R1_FB7 = 0x80
CAN_F10R1_FB8 = 0x100
CAN_F10R1_FB9 = 0x200
CAN_F10R1_FB10 = 0x400
CAN_F10R1_FB11 = 0x800
CAN_F10R1_FB12 = 0x1000
CAN_F10R1_FB13 = 0x2000
CAN_F10R1_FB14 = 0x4000
CAN_F10R1_FB15 = 0x8000
CAN_F10R1_FB16 = 0x10000
CAN_F10R1_FB17 = 0x20000
CAN_F10R1_FB18 = 0x40000
CAN_F10R1_FB19 = 0x80000
CAN_F10R1_FB20 = 0x100000
CAN_F10R1_FB21 = 0x200000
CAN_F10R1_FB22 = 0x400000
CAN_F10R1_FB23 = 0x800000
CAN_F10R1_FB24 = 0x1000000
CAN_F10R1_FB25 = 0x2000000
CAN_F10R1_FB26 = 0x4000000
CAN_F10R1_FB27 = 0x8000000
CAN_F10R1_FB28 = 0x10000000
CAN_F10R1_FB29 = 0x20000000
CAN_F10R1_FB30 = 0x40000000
CAN_F10R1_FB31 = 0x80000000
CAN_F11R1_FB0 = 0x1
CAN_F11R1_FB1 = 0x2
CAN_F11R1_FB2 = 0x4
CAN_F11R1_FB3 = 0x8
CAN_F11R1_FB4 = 0x10
CAN_F11R1_FB5 = 0x20
CAN_F11R1_FB6 = 0x40
CAN_F11R1_FB7 = 0x80
CAN_F11R1_FB8 = 0x100
CAN_F11R1_FB9 = 0x200
CAN_F11R1_FB10 = 0x400
CAN_F11R1_FB11 = 0x800
CAN_F11R1_FB12 = 0x1000
CAN_F11R1_FB13 = 0x2000
CAN_F11R1_FB14 = 0x4000
CAN_F11R1_FB15 = 0x8000
CAN_F11R1_FB16 = 0x10000
CAN_F11R1_FB17 = 0x20000
CAN_F11R1_FB18 = 0x40000
CAN_F11R1_FB19 = 0x80000
CAN_F11R1_FB20 = 0x100000
CAN_F11R1_FB21 = 0x200000
CAN_F11R1_FB22 = 0x400000
CAN_F11R1_FB23 = 0x800000
CAN_F11R1_FB24 = 0x1000000
CAN_F11R1_FB25 = 0x2000000
CAN_F11R1_FB26 = 0x4000000
CAN_F11R1_FB27 = 0x8000000
CAN_F11R1_FB28 = 0x10000000
CAN_F11R1_FB29 = 0x20000000
CAN_F11R1_FB30 = 0x40000000
CAN_F11R1_FB31 = 0x80000000
CAN_F12R1_FB0 = 0x1
CAN_F12R1_FB1 = 0x2
CAN_F12R1_FB2 = 0x4
CAN_F12R1_FB3 = 0x8
CAN_F12R1_FB4 = 0x10
CAN_F12R1_FB5 = 0x20
CAN_F12R1_FB6 = 0x40
CAN_F12R1_FB7 = 0x80
CAN_F12R1_FB8 = 0x100
CAN_F12R1_FB9 = 0x200
CAN_F12R1_FB10 = 0x400
CAN_F12R1_FB11 = 0x800
CAN_F12R1_FB12 = 0x1000
CAN_F12R1_FB13 = 0x2000
CAN_F12R1_FB14 = 0x4000
CAN_F12R1_FB15 = 0x8000
CAN_F12R1_FB16 = 0x10000
CAN_F12R1_FB17 = 0x20000
CAN_F12R1_FB18 = 0x40000
CAN_F12R1_FB19 = 0x80000
CAN_F12R1_FB20 = 0x100000
CAN_F12R1_FB21 = 0x200000
CAN_F12R1_FB22 = 0x400000
CAN_F12R1_FB23 = 0x800000
CAN_F12R1_FB24 = 0x1000000
CAN_F12R1_FB25 = 0x2000000
CAN_F12R1_FB26 = 0x4000000
CAN_F12R1_FB27 = 0x8000000
CAN_F12R1_FB28 = 0x10000000
CAN_F12R1_FB29 = 0x20000000
CAN_F12R1_FB30 = 0x40000000
CAN_F12R1_FB31 = 0x80000000
CAN_F13R1_FB0 = 0x1
CAN_F13R1_FB1 = 0x2
CAN_F13R1_FB2 = 0x4
CAN_F13R1_FB3 = 0x8
CAN_F13R1_FB4 = 0x10
CAN_F13R1_FB5 = 0x20
CAN_F13R1_FB6 = 0x40
CAN_F13R1_FB7 = 0x80
CAN_F13R1_FB8 = 0x100
CAN_F13R1_FB9 = 0x200
CAN_F13R1_FB10 = 0x400
CAN_F13R1_FB11 = 0x800
CAN_F13R1_FB12 = 0x1000
CAN_F13R1_FB13 = 0x2000
CAN_F13R1_FB14 = 0x4000
CAN_F13R1_FB15 = 0x8000
CAN_F13R1_FB16 = 0x10000
CAN_F13R1_FB17 = 0x20000
CAN_F13R1_FB18 = 0x40000
CAN_F13R1_FB19 = 0x80000
CAN_F13R1_FB20 = 0x100000
CAN_F13R1_FB21 = 0x200000
CAN_F13R1_FB22 = 0x400000
CAN_F13R1_FB23 = 0x800000
CAN_F13R1_FB24 = 0x1000000
CAN_F13R1_FB25 = 0x2000000
CAN_F13R1_FB26 = 0x4000000
CAN_F13R1_FB27 = 0x8000000
CAN_F13R1_FB28 = 0x10000000
CAN_F13R1_FB29 = 0x20000000
CAN_F13R1_FB30 = 0x40000000
CAN_F13R1_FB31 = 0x80000000
CAN_F0R2_FB0 = 0x1
CAN_F0R2_FB1 = 0x2
CAN_F0R2_FB2 = 0x4
CAN_F0R2_FB3 = 0x8
CAN_F0R2_FB4 = 0x10
CAN_F0R2_FB5 = 0x20
CAN_F0R2_FB6 = 0x40
CAN_F0R2_FB7 = 0x80
CAN_F0R2_FB8 = 0x100
CAN_F0R2_FB9 = 0x200
CAN_F0R2_FB10 = 0x400
CAN_F0R2_FB11 = 0x800
CAN_F0R2_FB12 = 0x1000
CAN_F0R2_FB13 = 0x2000
CAN_F0R2_FB14 = 0x4000
CAN_F0R2_FB15 = 0x8000
CAN_F0R2_FB16 = 0x10000
CAN_F0R2_FB17 = 0x20000
CAN_F0R2_FB18 = 0x40000
CAN_F0R2_FB19 = 0x80000
CAN_F0R2_FB20 = 0x100000
CAN_F0R2_FB21 = 0x200000
CAN_F0R2_FB22 = 0x400000
CAN_F0R2_FB23 = 0x800000
CAN_F0R2_FB24 = 0x1000000
CAN_F0R2_FB25 = 0x2000000
CAN_F0R2_FB26 = 0x4000000
CAN_F0R2_FB27 = 0x8000000
CAN_F0R2_FB28 = 0x10000000
CAN_F0R2_FB29 = 0x20000000
CAN_F0R2_FB30 = 0x40000000
CAN_F0R2_FB31 = 0x80000000
CAN_F1R2_FB0 = 0x1
CAN_F1R2_FB1 = 0x2
CAN_F1R2_FB2 = 0x4
CAN_F1R2_FB3 = 0x8
CAN_F1R2_FB4 = 0x10
CAN_F1R2_FB5 = 0x20
CAN_F1R2_FB6 = 0x40
CAN_F1R2_FB7 = 0x80
CAN_F1R2_FB8 = 0x100
CAN_F1R2_FB9 = 0x200
CAN_F1R2_FB10 = 0x400
CAN_F1R2_FB11 = 0x800
CAN_F1R2_FB12 = 0x1000
CAN_F1R2_FB13 = 0x2000
CAN_F1R2_FB14 = 0x4000
CAN_F1R2_FB15 = 0x8000
CAN_F1R2_FB16 = 0x10000
CAN_F1R2_FB17 = 0x20000
CAN_F1R2_FB18 = 0x40000
CAN_F1R2_FB19 = 0x80000
CAN_F1R2_FB20 = 0x100000
CAN_F1R2_FB21 = 0x200000
CAN_F1R2_FB22 = 0x400000
CAN_F1R2_FB23 = 0x800000
CAN_F1R2_FB24 = 0x1000000
CAN_F1R2_FB25 = 0x2000000
CAN_F1R2_FB26 = 0x4000000
CAN_F1R2_FB27 = 0x8000000
CAN_F1R2_FB28 = 0x10000000
CAN_F1R2_FB29 = 0x20000000
CAN_F1R2_FB30 = 0x40000000
CAN_F1R2_FB31 = 0x80000000
CAN_F2R2_FB0 = 0x1
CAN_F2R2_FB1 = 0x2
CAN_F2R2_FB2 = 0x4
CAN_F2R2_FB3 = 0x8
CAN_F2R2_FB4 = 0x10
CAN_F2R2_FB5 = 0x20
CAN_F2R2_FB6 = 0x40
CAN_F2R2_FB7 = 0x80
CAN_F2R2_FB8 = 0x100
CAN_F2R2_FB9 = 0x200
CAN_F2R2_FB10 = 0x400
CAN_F2R2_FB11 = 0x800
CAN_F2R2_FB12 = 0x1000
CAN_F2R2_FB13 = 0x2000
CAN_F2R2_FB14 = 0x4000
CAN_F2R2_FB15 = 0x8000
CAN_F2R2_FB16 = 0x10000
CAN_F2R2_FB17 = 0x20000
CAN_F2R2_FB18 = 0x40000
CAN_F2R2_FB19 = 0x80000
CAN_F2R2_FB20 = 0x100000
CAN_F2R2_FB21 = 0x200000
CAN_F2R2_FB22 = 0x400000
CAN_F2R2_FB23 = 0x800000
CAN_F2R2_FB24 = 0x1000000
CAN_F2R2_FB25 = 0x2000000
CAN_F2R2_FB26 = 0x4000000
CAN_F2R2_FB27 = 0x8000000
CAN_F2R2_FB28 = 0x10000000
CAN_F2R2_FB29 = 0x20000000
CAN_F2R2_FB30 = 0x40000000
CAN_F2R2_FB31 = 0x80000000
CAN_F3R2_FB0 = 0x1
CAN_F3R2_FB1 = 0x2
CAN_F3R2_FB2 = 0x4
CAN_F3R2_FB3 = 0x8
CAN_F3R2_FB4 = 0x10
CAN_F3R2_FB5 = 0x20
CAN_F3R2_FB6 = 0x40
CAN_F3R2_FB7 = 0x80
CAN_F3R2_FB8 = 0x100
CAN_F3R2_FB9 = 0x200
CAN_F3R2_FB10 = 0x400
CAN_F3R2_FB11 = 0x800
CAN_F3R2_FB12 = 0x1000
CAN_F3R2_FB13 = 0x2000
CAN_F3R2_FB14 = 0x4000
CAN_F3R2_FB15 = 0x8000
CAN_F3R2_FB16 = 0x10000
CAN_F3R2_FB17 = 0x20000
CAN_F3R2_FB18 = 0x40000
CAN_F3R2_FB19 = 0x80000
CAN_F3R2_FB20 = 0x100000
CAN_F3R2_FB21 = 0x200000
CAN_F3R2_FB22 = 0x400000
CAN_F3R2_FB23 = 0x800000
CAN_F3R2_FB24 = 0x1000000
CAN_F3R2_FB25 = 0x2000000
CAN_F3R2_FB26 = 0x4000000
CAN_F3R2_FB27 = 0x8000000
CAN_F3R2_FB28 = 0x10000000
CAN_F3R2_FB29 = 0x20000000
CAN_F3R2_FB30 = 0x40000000
CAN_F3R2_FB31 = 0x80000000
CAN_F4R2_FB0 = 0x1
CAN_F4R2_FB1 = 0x2
CAN_F4R2_FB2 = 0x4
CAN_F4R2_FB3 = 0x8
CAN_F4R2_FB4 = 0x10
CAN_F4R2_FB5 = 0x20
CAN_F4R2_FB6 = 0x40
CAN_F4R2_FB7 = 0x80
CAN_F4R2_FB8 = 0x100
CAN_F4R2_FB9 = 0x200
CAN_F4R2_FB10 = 0x400
CAN_F4R2_FB11 = 0x800
CAN_F4R2_FB12 = 0x1000
CAN_F4R2_FB13 = 0x2000
CAN_F4R2_FB14 = 0x4000
CAN_F4R2_FB15 = 0x8000
CAN_F4R2_FB16 = 0x10000
CAN_F4R2_FB17 = 0x20000
CAN_F4R2_FB18 = 0x40000
CAN_F4R2_FB19 = 0x80000
CAN_F4R2_FB20 = 0x100000
CAN_F4R2_FB21 = 0x200000
CAN_F4R2_FB22 = 0x400000
CAN_F4R2_FB23 = 0x800000
CAN_F4R2_FB24 = 0x1000000
CAN_F4R2_FB25 = 0x2000000
CAN_F4R2_FB26 = 0x4000000
CAN_F4R2_FB27 = 0x8000000
CAN_F4R2_FB28 = 0x10000000
CAN_F4R2_FB29 = 0x20000000
CAN_F4R2_FB30 = 0x40000000
CAN_F4R2_FB31 = 0x80000000
CAN_F5R2_FB0 = 0x1
CAN_F5R2_FB1 = 0x2
CAN_F5R2_FB2 = 0x4
CAN_F5R2_FB3 = 0x8
CAN_F5R2_FB4 = 0x10
CAN_F5R2_FB5 = 0x20
CAN_F5R2_FB6 = 0x40
CAN_F5R2_FB7 = 0x80
CAN_F5R2_FB8 = 0x100
CAN_F5R2_FB9 = 0x200
CAN_F5R2_FB10 = 0x400
CAN_F5R2_FB11 = 0x800
CAN_F5R2_FB12 = 0x1000
CAN_F5R2_FB13 = 0x2000
CAN_F5R2_FB14 = 0x4000
CAN_F5R2_FB15 = 0x8000
CAN_F5R2_FB16 = 0x10000
CAN_F5R2_FB17 = 0x20000
CAN_F5R2_FB18 = 0x40000
CAN_F5R2_FB19 = 0x80000
CAN_F5R2_FB20 = 0x100000
CAN_F5R2_FB21 = 0x200000
CAN_F5R2_FB22 = 0x400000
CAN_F5R2_FB23 = 0x800000
CAN_F5R2_FB24 = 0x1000000
CAN_F5R2_FB25 = 0x2000000
CAN_F5R2_FB26 = 0x4000000
CAN_F5R2_FB27 = 0x8000000
CAN_F5R2_FB28 = 0x10000000
CAN_F5R2_FB29 = 0x20000000
CAN_F5R2_FB30 = 0x40000000
CAN_F5R2_FB31 = 0x80000000
CAN_F6R2_FB0 = 0x1
CAN_F6R2_FB1 = 0x2
CAN_F6R2_FB2 = 0x4
CAN_F6R2_FB3 = 0x8
CAN_F6R2_FB4 = 0x10
CAN_F6R2_FB5 = 0x20
CAN_F6R2_FB6 = 0x40
CAN_F6R2_FB7 = 0x80
CAN_F6R2_FB8 = 0x100
CAN_F6R2_FB9 = 0x200
CAN_F6R2_FB10 = 0x400
CAN_F6R2_FB11 = 0x800
CAN_F6R2_FB12 = 0x1000
CAN_F6R2_FB13 = 0x2000
CAN_F6R2_FB14 = 0x4000
CAN_F6R2_FB15 = 0x8000
CAN_F6R2_FB16 = 0x10000
CAN_F6R2_FB17 = 0x20000
CAN_F6R2_FB18 = 0x40000
CAN_F6R2_FB19 = 0x80000
CAN_F6R2_FB20 = 0x100000
CAN_F6R2_FB21 = 0x200000
CAN_F6R2_FB22 = 0x400000
CAN_F6R2_FB23 = 0x800000
CAN_F6R2_FB24 = 0x1000000
CAN_F6R2_FB25 = 0x2000000
CAN_F6R2_FB26 = 0x4000000
CAN_F6R2_FB27 = 0x8000000
CAN_F6R2_FB28 = 0x10000000
CAN_F6R2_FB29 = 0x20000000
CAN_F6R2_FB30 = 0x40000000
CAN_F6R2_FB31 = 0x80000000
CAN_F7R2_FB0 = 0x1
CAN_F7R2_FB1 = 0x2
CAN_F7R2_FB2 = 0x4
CAN_F7R2_FB3 = 0x8
CAN_F7R2_FB4 = 0x10
CAN_F7R2_FB5 = 0x20
CAN_F7R2_FB6 = 0x40
CAN_F7R2_FB7 = 0x80
CAN_F7R2_FB8 = 0x100
CAN_F7R2_FB9 = 0x200
CAN_F7R2_FB10 = 0x400
CAN_F7R2_FB11 = 0x800
CAN_F7R2_FB12 = 0x1000
CAN_F7R2_FB13 = 0x2000
CAN_F7R2_FB14 = 0x4000
CAN_F7R2_FB15 = 0x8000
CAN_F7R2_FB16 = 0x10000
CAN_F7R2_FB17 = 0x20000
CAN_F7R2_FB18 = 0x40000
CAN_F7R2_FB19 = 0x80000
CAN_F7R2_FB20 = 0x100000
CAN_F7R2_FB21 = 0x200000
CAN_F7R2_FB22 = 0x400000
CAN_F7R2_FB23 = 0x800000
CAN_F7R2_FB24 = 0x1000000
CAN_F7R2_FB25 = 0x2000000
CAN_F7R2_FB26 = 0x4000000
CAN_F7R2_FB27 = 0x8000000
CAN_F7R2_FB28 = 0x10000000
CAN_F7R2_FB29 = 0x20000000
CAN_F7R2_FB30 = 0x40000000
CAN_F7R2_FB31 = 0x80000000
CAN_F8R2_FB0 = 0x1
CAN_F8R2_FB1 = 0x2
CAN_F8R2_FB2 = 0x4
CAN_F8R2_FB3 = 0x8
CAN_F8R2_FB4 = 0x10
CAN_F8R2_FB5 = 0x20
CAN_F8R2_FB6 = 0x40
CAN_F8R2_FB7 = 0x80
CAN_F8R2_FB8 = 0x100
CAN_F8R2_FB9 = 0x200
CAN_F8R2_FB10 = 0x400
CAN_F8R2_FB11 = 0x800
CAN_F8R2_FB12 = 0x1000
CAN_F8R2_FB13 = 0x2000
CAN_F8R2_FB14 = 0x4000
CAN_F8R2_FB15 = 0x8000
CAN_F8R2_FB16 = 0x10000
CAN_F8R2_FB17 = 0x20000
CAN_F8R2_FB18 = 0x40000
CAN_F8R2_FB19 = 0x80000
CAN_F8R2_FB20 = 0x100000
CAN_F8R2_FB21 = 0x200000
CAN_F8R2_FB22 = 0x400000
CAN_F8R2_FB23 = 0x800000
CAN_F8R2_FB24 = 0x1000000
CAN_F8R2_FB25 = 0x2000000
CAN_F8R2_FB26 = 0x4000000
CAN_F8R2_FB27 = 0x8000000
CAN_F8R2_FB28 = 0x10000000
CAN_F8R2_FB29 = 0x20000000
CAN_F8R2_FB30 = 0x40000000
CAN_F8R2_FB31 = 0x80000000
CAN_F9R2_FB0 = 0x1
CAN_F9R2_FB1 = 0x2
CAN_F9R2_FB2 = 0x4
CAN_F9R2_FB3 = 0x8
CAN_F9R2_FB4 = 0x10
CAN_F9R2_FB5 = 0x20
CAN_F9R2_FB6 = 0x40
CAN_F9R2_FB7 = 0x80
CAN_F9R2_FB8 = 0x100
CAN_F9R2_FB9 = 0x200
CAN_F9R2_FB10 = 0x400
CAN_F9R2_FB11 = 0x800
CAN_F9R2_FB12 = 0x1000
CAN_F9R2_FB13 = 0x2000
CAN_F9R2_FB14 = 0x4000
CAN_F9R2_FB15 = 0x8000
CAN_F9R2_FB16 = 0x10000
CAN_F9R2_FB17 = 0x20000
CAN_F9R2_FB18 = 0x40000
CAN_F9R2_FB19 = 0x80000
CAN_F9R2_FB20 = 0x100000
CAN_F9R2_FB21 = 0x200000
CAN_F9R2_FB22 = 0x400000
CAN_F9R2_FB23 = 0x800000
CAN_F9R2_FB24 = 0x1000000
CAN_F9R2_FB25 = 0x2000000
CAN_F9R2_FB26 = 0x4000000
CAN_F9R2_FB27 = 0x8000000
CAN_F9R2_FB28 = 0x10000000
CAN_F9R2_FB29 = 0x20000000
CAN_F9R2_FB30 = 0x40000000
CAN_F9R2_FB31 = 0x80000000
CAN_F10R2_FB0 = 0x1
CAN_F10R2_FB1 = 0x2
CAN_F10R2_FB2 = 0x4
CAN_F10R2_FB3 = 0x8
CAN_F10R2_FB4 = 0x10
CAN_F10R2_FB5 = 0x20
CAN_F10R2_FB6 = 0x40
CAN_F10R2_FB7 = 0x80
CAN_F10R2_FB8 = 0x100
CAN_F10R2_FB9 = 0x200
CAN_F10R2_FB10 = 0x400
CAN_F10R2_FB11 = 0x800
CAN_F10R2_FB12 = 0x1000
CAN_F10R2_FB13 = 0x2000
CAN_F10R2_FB14 = 0x4000
CAN_F10R2_FB15 = 0x8000
CAN_F10R2_FB16 = 0x10000
CAN_F10R2_FB17 = 0x20000
CAN_F10R2_FB18 = 0x40000
CAN_F10R2_FB19 = 0x80000
CAN_F10R2_FB20 = 0x100000
CAN_F10R2_FB21 = 0x200000
CAN_F10R2_FB22 = 0x400000
CAN_F10R2_FB23 = 0x800000
CAN_F10R2_FB24 = 0x1000000
CAN_F10R2_FB25 = 0x2000000
CAN_F10R2_FB26 = 0x4000000
CAN_F10R2_FB27 = 0x8000000
CAN_F10R2_FB28 = 0x10000000
CAN_F10R2_FB29 = 0x20000000
CAN_F10R2_FB30 = 0x40000000
CAN_F10R2_FB31 = 0x80000000
CAN_F11R2_FB0 = 0x1
CAN_F11R2_FB1 = 0x2
CAN_F11R2_FB2 = 0x4
CAN_F11R2_FB3 = 0x8
CAN_F11R2_FB4 = 0x10
CAN_F11R2_FB5 = 0x20
CAN_F11R2_FB6 = 0x40
CAN_F11R2_FB7 = 0x80
CAN_F11R2_FB8 = 0x100
CAN_F11R2_FB9 = 0x200
CAN_F11R2_FB10 = 0x400
CAN_F11R2_FB11 = 0x800
CAN_F11R2_FB12 = 0x1000
CAN_F11R2_FB13 = 0x2000
CAN_F11R2_FB14 = 0x4000
CAN_F11R2_FB15 = 0x8000
CAN_F11R2_FB16 = 0x10000
CAN_F11R2_FB17 = 0x20000
CAN_F11R2_FB18 = 0x40000
CAN_F11R2_FB19 = 0x80000
CAN_F11R2_FB20 = 0x100000
CAN_F11R2_FB21 = 0x200000
CAN_F11R2_FB22 = 0x400000
CAN_F11R2_FB23 = 0x800000
CAN_F11R2_FB24 = 0x1000000
CAN_F11R2_FB25 = 0x2000000
CAN_F11R2_FB26 = 0x4000000
CAN_F11R2_FB27 = 0x8000000
CAN_F11R2_FB28 = 0x10000000
CAN_F11R2_FB29 = 0x20000000
CAN_F11R2_FB30 = 0x40000000
CAN_F11R2_FB31 = 0x80000000
CAN_F12R2_FB0 = 0x1
CAN_F12R2_FB1 = 0x2
CAN_F12R2_FB2 = 0x4
CAN_F12R2_FB3 = 0x8
CAN_F12R2_FB4 = 0x10
CAN_F12R2_FB5 = 0x20
CAN_F12R2_FB6 = 0x40
CAN_F12R2_FB7 = 0x80
CAN_F12R2_FB8 = 0x100
CAN_F12R2_FB9 = 0x200
CAN_F12R2_FB10 = 0x400
CAN_F12R2_FB11 = 0x800
CAN_F12R2_FB12 = 0x1000
CAN_F12R2_FB13 = 0x2000
CAN_F12R2_FB14 = 0x4000
CAN_F12R2_FB15 = 0x8000
CAN_F12R2_FB16 = 0x10000
CAN_F12R2_FB17 = 0x20000
CAN_F12R2_FB18 = 0x40000
CAN_F12R2_FB19 = 0x80000
CAN_F12R2_FB20 = 0x100000
CAN_F12R2_FB21 = 0x200000
CAN_F12R2_FB22 = 0x400000
CAN_F12R2_FB23 = 0x800000
CAN_F12R2_FB24 = 0x1000000
CAN_F12R2_FB25 = 0x2000000
CAN_F12R2_FB26 = 0x4000000
CAN_F12R2_FB27 = 0x8000000
CAN_F12R2_FB28 = 0x10000000
CAN_F12R2_FB29 = 0x20000000
CAN_F12R2_FB30 = 0x40000000
CAN_F12R2_FB31 = 0x80000000
CAN_F13R2_FB0 = 0x1
CAN_F13R2_FB1 = 0x2
CAN_F13R2_FB2 = 0x4
CAN_F13R2_FB3 = 0x8
CAN_F13R2_FB4 = 0x10
CAN_F13R2_FB5 = 0x20
CAN_F13R2_FB6 = 0x40
CAN_F13R2_FB7 = 0x80
CAN_F13R2_FB8 = 0x100
CAN_F13R2_FB9 = 0x200
CAN_F13R2_FB10 = 0x400
CAN_F13R2_FB11 = 0x800
CAN_F13R2_FB12 = 0x1000
CAN_F13R2_FB13 = 0x2000
CAN_F13R2_FB14 = 0x4000
CAN_F13R2_FB15 = 0x8000
CAN_F13R2_FB16 = 0x10000
CAN_F13R2_FB17 = 0x20000
CAN_F13R2_FB18 = 0x40000
CAN_F13R2_FB19 = 0x80000
CAN_F13R2_FB20 = 0x100000
CAN_F13R2_FB21 = 0x200000
CAN_F13R2_FB22 = 0x400000
CAN_F13R2_FB23 = 0x800000
CAN_F13R2_FB24 = 0x1000000
CAN_F13R2_FB25 = 0x2000000
CAN_F13R2_FB26 = 0x4000000
CAN_F13R2_FB27 = 0x8000000
CAN_F13R2_FB28 = 0x10000000
CAN_F13R2_FB29 = 0x20000000
CAN_F13R2_FB30 = 0x40000000
CAN_F13R2_FB31 = 0x80000000
CEC_CR_CECEN = 0x1
CEC_CR_TXSOM = 0x2
CEC_CR_TXEOM = 0x4
CEC_CFGR_SFT = 0x7
CEC_CFGR_RXTOL = 0x8
CEC_CFGR_BRESTP = 0x10
CEC_CFGR_BREGEN = 0x20
CEC_CFGR_LREGEN = 0x40
CEC_CFGR_BRDNOGEN = 0x80
CEC_CFGR_SFTOPT = 0x100
CEC_CFGR_OAR = 0x7FFF0000
CEC_CFGR_LSTN = 0x80000000
CEC_TXDR_TXD = 0xFF
CEC_TXDR_RXD = 0xFF
CEC_ISR_RXBR = 0x1
CEC_ISR_RXEND = 0x2
CEC_ISR_RXOVR = 0x4
CEC_ISR_BRE = 0x8
CEC_ISR_SBPE = 0x10
CEC_ISR_LBPE = 0x20
CEC_ISR_RXACKE = 0x40
CEC_ISR_ARBLST = 0x80
CEC_ISR_TXBR = 0x100
CEC_ISR_TXEND = 0x200
CEC_ISR_TXUDR = 0x400
CEC_ISR_TXERR = 0x800
CEC_ISR_TXACKE = 0x1000
CEC_IER_RXBRIE = 0x1
CEC_IER_RXENDIE = 0x2
CEC_IER_RXOVRIE = 0x4
CEC_IER_BREIEIE = 0x8
CEC_IER_SBPEIE = 0x10
CEC_IER_LBPEIE = 0x20
CEC_IER_RXACKEIE = 0x40
CEC_IER_ARBLSTIE = 0x80
CEC_IER_TXBRIE = 0x100
CEC_IER_TXENDIE = 0x200
CEC_IER_TXUDRIE = 0x400
CEC_IER_TXERRIE = 0x800
CEC_IER_TXACKEIE = 0x1000
COMP_CSR_COMP1EN = 0x1
COMP_CSR_COMP1SW1 = 0x2
COMP_CSR_COMP1MODE = 0xC
COMP_CSR_COMP1MODE_0 = 0x4
COMP_CSR_COMP1MODE_1 = 0x8
COMP_CSR_COMP1INSEL = 0x70
COMP_CSR_COMP1INSEL_0 = 0x10
COMP_CSR_COMP1INSEL_1 = 0x20
COMP_CSR_COMP1INSEL_2 = 0x40
COMP_CSR_COMP1OUTSEL = 0x700
COMP_CSR_COMP1OUTSEL_0 = 0x100
COMP_CSR_COMP1OUTSEL_1 = 0x200
COMP_CSR_COMP1OUTSEL_2 = 0x400
COMP_CSR_COMP1POL = 0x800
COMP_CSR_COMP1HYST = 0x3000
COMP_CSR_COMP1HYST_0 = 0x1000
COMP_CSR_COMP1HYST_1 = 0x2000
COMP_CSR_COMP1OUT = 0x4000
COMP_CSR_COMP1LOCK = 0x8000
COMP_CSR_COMP2EN = 0x10000
COMP_CSR_COMP2MODE = 0xC0000
COMP_CSR_COMP2MODE_0 = 0x40000
COMP_CSR_COMP2MODE_1 = 0x80000
COMP_CSR_COMP2INSEL = 0x700000
COMP_CSR_COMP2INSEL_0 = 0x100000
COMP_CSR_COMP2INSEL_1 = 0x200000
COMP_CSR_COMP2INSEL_2 = 0x400000
COMP_CSR_WNDWEN = 0x800000
COMP_CSR_COMP2OUTSEL = 0x7000000
COMP_CSR_COMP2OUTSEL_0 = 0x1000000
COMP_CSR_COMP2OUTSEL_1 = 0x2000000
COMP_CSR_COMP2OUTSEL_2 = 0x4000000
COMP_CSR_COMP2POL = 0x8000000
COMP_CSR_COMP2HYST = 0x30000000
COMP_CSR_COMP2HYST_0 = 0x10000000
COMP_CSR_COMP2HYST_1 = 0x20000000
COMP_CSR_COMP2OUT = 0x40000000
COMP_CSR_COMP2LOCK = 0x80000000
CRC_DR_DR = 0xFFFFFFFF
CRC_IDR_IDR = 0xFF
CRC_CR_RESET = 0x1
CRC_CR_POLSIZE = 0x18
CRC_CR_POLSIZE_0 = 0x8
CRC_CR_POLSIZE_1 = 0x10
CRC_CR_REV_IN = 0x60
CRC_CR_REV_IN_0 = 0x20
CRC_CR_REV_IN_1 = 0x40
CRC_CR_REV_OUT = 0x80
CRC_INIT_INIT = 0xFFFFFFFF
CRC_POL_POL = 0xFFFFFFFF
CRS_CR_SYNCOKIE = 0x1
CRS_CR_SYNCWARNIE = 0x2
CRS_CR_ERRIE = 0x4
CRS_CR_ESYNCIE = 0x8
CRS_CR_CEN = 0x20
CRS_CR_AUTOTRIMEN = 0x40
CRS_CR_SWSYNC = 0x80
CRS_CR_TRIM = 0x3F00
CRS_CFGR_RELOAD = 0xFFFF
CRS_CFGR_FELIM = 0xFF0000
CRS_CFGR_SYNCDIV = 0x7000000
CRS_CFGR_SYNCDIV_0 = 0x1000000
CRS_CFGR_SYNCDIV_1 = 0x2000000
CRS_CFGR_SYNCDIV_2 = 0x4000000
CRS_CFGR_SYNCSRC = 0x30000000
CRS_CFGR_SYNCSRC_0 = 0x10000000
CRS_CFGR_SYNCSRC_1 = 0x20000000
CRS_CFGR_SYNCPOL = 0x80000000
CRS_ISR_SYNCOKF = 0x1
CRS_ISR_SYNCWARNF = 0x2
CRS_ISR_ERRF = 0x4
CRS_ISR_ESYNCF = 0x8
CRS_ISR_SYNCERR = 0x100
CRS_ISR_SYNCMISS = 0x200
CRS_ISR_TRIMOVF = 0x400
CRS_ISR_FEDIR = 0x8000
CRS_ISR_FECAP = 0xFFFF0000
CRS_ICR_SYNCOKC = 0x1
CRS_ICR_SYNCWARNC = 0x2
CRS_ICR_ERRC = 0x4
CRS_ICR_ESYNCC = 0x8
DAC_CR_EN1 = 0x1
DAC_CR_BOFF1 = 0x2
DAC_CR_TEN1 = 0x4
DAC_CR_TSEL1 = 0x38
DAC_CR_TSEL1_0 = 0x8
DAC_CR_TSEL1_1 = 0x10
DAC_CR_TSEL1_2 = 0x20
DAC_CR_WAVE1 = 0xC0
DAC_CR_WAVE1_0 = 0x40
DAC_CR_WAVE1_1 = 0x80
DAC_CR_MAMP1 = 0xF00
DAC_CR_MAMP1_0 = 0x100
DAC_CR_MAMP1_1 = 0x200
DAC_CR_MAMP1_2 = 0x400
DAC_CR_MAMP1_3 = 0x800
DAC_CR_DMAEN1 = 0x1000
DAC_CR_DMAUDRIE1 = 0x2000
DAC_CR_EN2 = 0x10000
DAC_CR_BOFF2 = 0x20000
DAC_CR_TEN2 = 0x40000
DAC_CR_TSEL2 = 0x380000
DAC_CR_TSEL2_0 = 0x80000
DAC_CR_TSEL2_1 = 0x100000
DAC_CR_TSEL2_2 = 0x200000
DAC_CR_WAVE2 = 0xC00000
DAC_CR_WAVE2_0 = 0x400000
DAC_CR_WAVE2_1 = 0x800000
DAC_CR_MAMP2 = 0xF000000
DAC_CR_MAMP2_0 = 0x1000000
DAC_CR_MAMP2_1 = 0x2000000
DAC_CR_MAMP2_2 = 0x4000000
DAC_CR_MAMP2_3 = 0x8000000
DAC_CR_DMAEN2 = 0x10000000
DAC_CR_DMAUDRIE2 = 0x20000000
DAC_SWTRIGR_SWTRIG1 = 0x1
DAC_SWTRIGR_SWTRIG2 = 0x2
DAC_DHR12R1_DACC1DHR = 0xFFF
DAC_DHR12L1_DACC1DHR = 0xFFF0
DAC_DHR8R1_DACC1DHR = 0xFF
DAC_DOR1_DACC1DOR = 0xFFF
DAC_SR_DMAUDR1 = 0x2000
DAC_SR_DMAUDR2 = 0x20000000
DBGMCU_IDCODE_DEV_ID = 0xFFF
DBGMCU_IDCODE_REV_ID = 0xFFFF0000
DBGMCU_IDCODE_REV_ID_0 = 0x10000
DBGMCU_IDCODE_REV_ID_1 = 0x20000
DBGMCU_IDCODE_REV_ID_2 = 0x40000
DBGMCU_IDCODE_REV_ID_3 = 0x80000
DBGMCU_IDCODE_REV_ID_4 = 0x100000
DBGMCU_IDCODE_REV_ID_5 = 0x200000
DBGMCU_IDCODE_REV_ID_6 = 0x400000
DBGMCU_IDCODE_REV_ID_7 = 0x800000
DBGMCU_IDCODE_REV_ID_8 = 0x1000000
DBGMCU_IDCODE_REV_ID_9 = 0x2000000
DBGMCU_IDCODE_REV_ID_10 = 0x4000000
DBGMCU_IDCODE_REV_ID_11 = 0x8000000
DBGMCU_IDCODE_REV_ID_12 = 0x10000000
DBGMCU_IDCODE_REV_ID_13 = 0x20000000
DBGMCU_IDCODE_REV_ID_14 = 0x40000000
DBGMCU_IDCODE_REV_ID_15 = 0x80000000
DBGMCU_CR_DBG_STOP = 0x2
DBGMCU_CR_DBG_STANDBY = 0x4
DBGMCU_APB1_FZ_DBG_TIM2_STOP = 0x1
DBGMCU_APB1_FZ_DBG_TIM3_STOP = 0x2
DBGMCU_APB1_FZ_DBG_TIM6_STOP = 0x10
DBGMCU_APB1_FZ_DBG_TIM7_STOP = 0x20
DBGMCU_APB1_FZ_DBG_TIM14_STOP = 0x100
DBGMCU_APB1_FZ_DBG_RTC_STOP = 0x400
DBGMCU_APB1_FZ_DBG_WWDG_STOP = 0x800
DBGMCU_APB1_FZ_DBG_IWDG_STOP = 0x1000
DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT = 0x200000
DBGMCU_APB1_FZ_DBG_CAN_STOP = 0x2000000
DBGMCU_APB2_FZ_DBG_TIM1_STOP = 0x800
DBGMCU_APB2_FZ_DBG_TIM15_STOP = 0x10000
DBGMCU_APB2_FZ_DBG_TIM16_STOP = 0x20000
DBGMCU_APB2_FZ_DBG_TIM17_STOP = 0x40000
DMA_ISR_GIF1 = 0x1
DMA_ISR_TCIF1 = 0x2
DMA_ISR_HTIF1 = 0x4
DMA_ISR_TEIF1 = 0x8
DMA_ISR_GIF2 = 0x10
DMA_ISR_TCIF2 = 0x20
DMA_ISR_HTIF2 = 0x40
DMA_ISR_TEIF2 = 0x80
DMA_ISR_GIF3 = 0x100
DMA_ISR_TCIF3 = 0x200
DMA_ISR_HTIF3 = 0x400
DMA_ISR_TEIF3 = 0x800
DMA_ISR_GIF4 = 0x1000
DMA_ISR_TCIF4 = 0x2000
DMA_ISR_HTIF4 = 0x4000
DMA_ISR_TEIF4 = 0x8000
DMA_ISR_GIF5 = 0x10000
DMA_ISR_TCIF5 = 0x20000
DMA_ISR_HTIF5 = 0x40000
DMA_ISR_TEIF5 = 0x80000
DMA_ISR_GIF6 = 0x100000
DMA_ISR_TCIF6 = 0x200000
DMA_ISR_HTIF6 = 0x400000
DMA_ISR_TEIF6 = 0x800000
DMA_ISR_GIF7 = 0x1000000
DMA_ISR_TCIF7 = 0x2000000
DMA_ISR_HTIF7 = 0x4000000
DMA_ISR_TEIF7 = 0x8000000
DMA_IFCR_CGIF1 = 0x1
DMA_IFCR_CTCIF1 = 0x2
DMA_IFCR_CHTIF1 = 0x4
DMA_IFCR_CTEIF1 = 0x8
DMA_IFCR_CGIF2 = 0x10
DMA_IFCR_CTCIF2 = 0x20
DMA_IFCR_CHTIF2 = 0x40
DMA_IFCR_CTEIF2 = 0x80
DMA_IFCR_CGIF3 = 0x100
DMA_IFCR_CTCIF3 = 0x200
DMA_IFCR_CHTIF3 = 0x400
DMA_IFCR_CTEIF3 = 0x800
DMA_IFCR_CGIF4 = 0x1000
DMA_IFCR_CTCIF4 = 0x2000
DMA_IFCR_CHTIF4 = 0x4000
DMA_IFCR_CTEIF4 = 0x8000
DMA_IFCR_CGIF5 = 0x10000
DMA_IFCR_CTCIF5 = 0x20000
DMA_IFCR_CHTIF5 = 0x40000
DMA_IFCR_CTEIF5 = 0x80000
DMA_IFCR_CGIF6 = 0x100000
DMA_IFCR_CTCIF6 = 0x200000
DMA_IFCR_CHTIF6 = 0x400000
DMA_IFCR_CTEIF6 = 0x800000
DMA_IFCR_CGIF7 = 0x1000000
DMA_IFCR_CTCIF7 = 0x2000000
DMA_IFCR_CHTIF7 = 0x4000000
DMA_IFCR_CTEIF7 = 0x8000000
DMA_CCR_EN = 0x1
DMA_CCR_TCIE = 0x2
DMA_CCR_HTIE = 0x4
DMA_CCR_TEIE = 0x8
DMA_CCR_DIR = 0x10
DMA_CCR_CIRC = 0x20
DMA_CCR_PINC = 0x40
DMA_CCR_MINC = 0x80
DMA_CCR_PSIZE = 0x300
DMA_CCR_PSIZE_0 = 0x100
DMA_CCR_PSIZE_1 = 0x200
DMA_CCR_MSIZE = 0xC00
DMA_CCR_MSIZE_0 = 0x400
DMA_CCR_MSIZE_1 = 0x800
DMA_CCR_PL = 0x3000
DMA_CCR_PL_0 = 0x1000
DMA_CCR_PL_1 = 0x2000
DMA_CCR_MEM2MEM = 0x4000
DMA_CNDTR_NDT = 0xFFFF
DMA_CPAR_PA = 0xFFFFFFFF
DMA_CMAR_MA = 0xFFFFFFFF
DMA_RMPCR1_DEFAULT = 0x0
DMA_RMPCR1_CH1_ADC = 0x1
DMA_RMPCR1_CH1_TIM17_CH1 = 0x7
DMA_RMPCR1_CH1_TIM17_UP = 0x7
DMA_RMPCR1_CH1_USART1_RX = 0x8
DMA_RMPCR1_CH1_USART2_RX = 0x9
DMA_RMPCR1_CH1_USART3_RX = 0xA
DMA_RMPCR1_CH1_USART4_RX = 0xB
DMA_RMPCR1_CH1_USART5_RX = 0xC
DMA_RMPCR1_CH1_USART6_RX = 0xD
DMA_RMPCR1_CH1_USART7_RX = 0xE
DMA_RMPCR1_CH1_USART8_RX = 0xF
DMA_RMPCR1_CH2_ADC = 0x10
DMA_RMPCR1_CH2_I2C1_TX = 0x20
DMA_RMPCR1_CH2_SPI_1RX = 0x30
DMA_RMPCR1_CH2_TIM1_CH1 = 0x40
DMA_RMPCR1_CH2_TIM17_CH1 = 0x70
DMA_RMPCR1_CH2_TIM17_UP = 0x70
DMA_RMPCR1_CH2_USART1_TX = 0x80
DMA_RMPCR1_CH2_USART2_TX = 0x90
DMA_RMPCR1_CH2_USART3_TX = 0xA0
DMA_RMPCR1_CH2_USART4_TX = 0xB0
DMA_RMPCR1_CH2_USART5_TX = 0xC0
DMA_RMPCR1_CH2_USART6_TX = 0xD0
DMA_RMPCR1_CH2_USART7_TX = 0xE0
DMA_RMPCR1_CH2_USART8_TX = 0xF0
DMA_RMPCR1_CH3_TIM6_UP = 0x100
DMA_RMPCR1_CH3_DAC_CH1 = 0x100
DMA_RMPCR1_CH3_I2C1_RX = 0x200
DMA_RMPCR1_CH3_SPI1_TX = 0x300
DMA_RMPCR1_CH3_TIM1_CH2 = 0x400
DMA_RMPCR1_CH3_TIM2_CH2 = 0x500
DMA_RMPCR1_CH3_TIM16_CH1 = 0x700
DMA_RMPCR1_CH3_TIM16_UP = 0x700
DMA_RMPCR1_CH3_USART1_RX = 0x800
DMA_RMPCR1_CH3_USART2_RX = 0x900
DMA_RMPCR1_CH3_USART3_RX = 0xA00
DMA_RMPCR1_CH3_USART4_RX = 0xB00
DMA_RMPCR1_CH3_USART5_RX = 0xC00
DMA_RMPCR1_CH3_USART6_RX = 0xD00
DMA_RMPCR1_CH3_USART7_RX = 0xE00
DMA_RMPCR1_CH3_USART8_RX = 0xF00
DMA_RMPCR1_CH4_TIM7_UP = 0x1000
DMA_RMPCR1_CH4_DAC_CH2 = 0x1000
DMA_RMPCR1_CH4_I2C2_TX = 0x2000
DMA_RMPCR1_CH4_SPI2_RX = 0x3000
DMA_RMPCR1_CH4_TIM2_CH4 = 0x5000
DMA_RMPCR1_CH4_TIM3_CH1 = 0x6000
DMA_RMPCR1_CH4_TIM3_TRIG = 0x6000
DMA_RMPCR1_CH4_TIM16_CH1 = 0x7000
DMA_RMPCR1_CH4_TIM16_UP = 0x7000
DMA_RMPCR1_CH4_USART1_TX = 0x8000
DMA_RMPCR1_CH4_USART2_TX = 0x9000
DMA_RMPCR1_CH4_USART3_TX = 0xA000
DMA_RMPCR1_CH4_USART4_TX = 0xB000
DMA_RMPCR1_CH4_USART5_TX = 0xC000
DMA_RMPCR1_CH4_USART6_TX = 0xD000
DMA_RMPCR1_CH4_USART7_TX = 0xE000
DMA_RMPCR1_CH4_USART8_TX = 0xF000
DMA_RMPCR1_CH5_I2C2_RX = 0x20000
DMA_RMPCR1_CH5_SPI2_TX = 0x30000
DMA_RMPCR1_CH5_TIM1_CH3 = 0x40000
DMA_RMPCR1_CH5_USART1_RX = 0x80000
DMA_RMPCR1_CH5_USART2_RX = 0x90000
DMA_RMPCR1_CH5_USART3_RX = 0xA0000
DMA_RMPCR1_CH5_USART4_RX = 0xB0000
DMA_RMPCR1_CH5_USART5_RX = 0xC0000
DMA_RMPCR1_CH5_USART6_RX = 0xD0000
DMA_RMPCR1_CH5_USART7_RX = 0xE0000
DMA_RMPCR1_CH5_USART8_RX = 0xF0000
DMA_RMPCR1_CH6_I2C1_TX = 0x200000
DMA_RMPCR1_CH6_SPI2_RX = 0x300000
DMA_RMPCR1_CH6_TIM1_CH1 = 0x400000
DMA_RMPCR1_CH6_TIM1_CH2 = 0x400000
DMA_RMPCR1_CH6_TIM1_CH3 = 0x400000
DMA_RMPCR1_CH6_TIM3_CH1 = 0x600000
DMA_RMPCR1_CH6_TIM3_TRIG = 0x600000
DMA_RMPCR1_CH6_TIM16_CH1 = 0x700000
DMA_RMPCR1_CH6_TIM16_UP = 0x700000
DMA_RMPCR1_CH6_USART1_RX = 0x800000
DMA_RMPCR1_CH6_USART2_RX = 0x900000
DMA_RMPCR1_CH6_USART3_RX = 0xA00000
DMA_RMPCR1_CH6_USART4_RX = 0xB00000
DMA_RMPCR1_CH6_USART5_RX = 0xC00000
DMA_RMPCR1_CH6_USART6_RX = 0xD00000
DMA_RMPCR1_CH6_USART7_RX = 0xE00000
DMA_RMPCR1_CH6_USART8_RX = 0xF00000
DMA_RMPCR1_CH7_I2C1_RX = 0x2000000
DMA_RMPCR1_CH7_SPI2_TX = 0x3000000
DMA_RMPCR1_CH7_TIM2_CH2 = 0x5000000
DMA_RMPCR1_CH7_TIM2_CH4 = 0x5000000
DMA_RMPCR1_CH7_TIM17_CH1 = 0x7000000
DMA_RMPCR1_CH7_TIM17_UP = 0x7000000
DMA_RMPCR1_CH7_USART1_TX = 0x8000000
DMA_RMPCR1_CH7_USART2_TX = 0x9000000
DMA_RMPCR1_CH7_USART3_TX = 0xA000000
DMA_RMPCR1_CH7_USART4_TX = 0xB000000
DMA_RMPCR1_CH7_USART5_TX = 0xC000000
DMA_RMPCR1_CH7_USART6_TX = 0xD000000
DMA_RMPCR1_CH7_USART7_TX = 0xE000000
DMA_RMPCR1_CH7_USART8_TX = 0xF000000
DMA_RMPCR2_DEFAULT = 0x0
DMA_RMPCR2_CH1_I2C2_TX = 0x2
DMA_RMPCR2_CH1_USART1_TX = 0x8
DMA_RMPCR2_CH1_USART2_TX = 0x9
DMA_RMPCR2_CH1_USART3_TX = 0xA
DMA_RMPCR2_CH1_USART4_TX = 0xB
DMA_RMPCR2_CH1_USART5_TX = 0xC
DMA_RMPCR2_CH1_USART6_TX = 0xD
DMA_RMPCR2_CH1_USART7_TX = 0xE
DMA_RMPCR2_CH1_USART8_TX = 0xF
DMA_RMPCR2_CH2_I2C2_RX = 0x20
DMA_RMPCR2_CH2_USART1_RX = 0x80
DMA_RMPCR2_CH2_USART2_RX = 0x90
DMA_RMPCR2_CH2_USART3_RX = 0xA0
DMA_RMPCR2_CH2_USART4_RX = 0xB0
DMA_RMPCR2_CH2_USART5_RX = 0xC0
DMA_RMPCR2_CH2_USART6_RX = 0xD0
DMA_RMPCR2_CH2_USART7_RX = 0xE0
DMA_RMPCR2_CH2_USART8_RX = 0xF0
DMA_RMPCR2_CH3_TIM6_UP = 0x100
DMA_RMPCR2_CH3_DAC_CH1 = 0x100
DMA_RMPCR2_CH3_SPI1_RX = 0x300
DMA_RMPCR2_CH3_USART1_RX = 0x800
DMA_RMPCR2_CH3_USART2_RX = 0x900
DMA_RMPCR2_CH3_USART3_RX = 0xA00
DMA_RMPCR2_CH3_USART4_RX = 0xB00
DMA_RMPCR2_CH3_USART5_RX = 0xC00
DMA_RMPCR2_CH3_USART6_RX = 0xD00
DMA_RMPCR2_CH3_USART7_RX = 0xE00
DMA_RMPCR2_CH3_USART8_RX = 0xF00
DMA_RMPCR2_CH4_TIM7_UP = 0x1000
DMA_RMPCR2_CH4_DAC_CH2 = 0x1000
DMA_RMPCR2_CH4_SPI1_TX = 0x3000
DMA_RMPCR2_CH4_USART1_TX = 0x8000
DMA_RMPCR2_CH4_USART2_TX = 0x9000
DMA_RMPCR2_CH4_USART3_TX = 0xA000
DMA_RMPCR2_CH4_USART4_TX = 0xB000
DMA_RMPCR2_CH4_USART5_TX = 0xC000
DMA_RMPCR2_CH4_USART6_TX = 0xD000
DMA_RMPCR2_CH4_USART7_TX = 0xE000
DMA_RMPCR2_CH4_USART8_TX = 0xF000
DMA_RMPCR2_CH5_ADC = 0x10000
DMA_RMPCR2_CH5_USART1_TX = 0x80000
DMA_RMPCR2_CH5_USART2_TX = 0x90000
DMA_RMPCR2_CH5_USART3_TX = 0xA0000
DMA_RMPCR2_CH5_USART4_TX = 0xB0000
DMA_RMPCR2_CH5_USART5_TX = 0xC0000
DMA_RMPCR2_CH5_USART6_TX = 0xD0000
DMA_RMPCR2_CH5_USART7_TX = 0xE0000
DMA_RMPCR2_CH5_USART8_TX = 0xF0000
EXTI_IMR_MR0 = 0x1
EXTI_IMR_MR1 = 0x2
EXTI_IMR_MR2 = 0x4
EXTI_IMR_MR3 = 0x8
EXTI_IMR_MR4 = 0x10
EXTI_IMR_MR5 = 0x20
EXTI_IMR_MR6 = 0x40
EXTI_IMR_MR7 = 0x80
EXTI_IMR_MR8 = 0x100
EXTI_IMR_MR9 = 0x200
EXTI_IMR_MR10 = 0x400
EXTI_IMR_MR11 = 0x800
EXTI_IMR_MR12 = 0x1000
EXTI_IMR_MR13 = 0x2000
EXTI_IMR_MR14 = 0x4000
EXTI_IMR_MR15 = 0x8000
EXTI_IMR_MR16 = 0x10000
EXTI_IMR_MR17 = 0x20000
EXTI_IMR_MR18 = 0x40000
EXTI_IMR_MR19 = 0x80000
EXTI_IMR_MR20 = 0x100000
EXTI_IMR_MR21 = 0x200000
EXTI_IMR_MR22 = 0x400000
EXTI_IMR_MR23 = 0x800000
EXTI_IMR_MR24 = 0x1000000
EXTI_IMR_MR25 = 0x2000000
EXTI_IMR_MR26 = 0x4000000
EXTI_IMR_MR27 = 0x8000000
EXTI_IMR_MR28 = 0x10000000
EXTI_IMR_MR29 = 0x20000000
EXTI_IMR_MR30 = 0x40000000
EXTI_IMR_MR31 = 0x80000000
EXTI_EMR_MR0 = 0x1
EXTI_EMR_MR1 = 0x2
EXTI_EMR_MR2 = 0x4
EXTI_EMR_MR3 = 0x8
EXTI_EMR_MR4 = 0x10
EXTI_EMR_MR5 = 0x20
EXTI_EMR_MR6 = 0x40
EXTI_EMR_MR7 = 0x80
EXTI_EMR_MR8 = 0x100
EXTI_EMR_MR9 = 0x200
EXTI_EMR_MR10 = 0x400
EXTI_EMR_MR11 = 0x800
EXTI_EMR_MR12 = 0x1000
EXTI_EMR_MR13 = 0x2000
EXTI_EMR_MR14 = 0x4000
EXTI_EMR_MR15 = 0x8000
EXTI_EMR_MR16 = 0x10000
EXTI_EMR_MR17 = 0x20000
EXTI_EMR_MR18 = 0x40000
EXTI_EMR_MR19 = 0x80000
EXTI_EMR_MR20 = 0x100000
EXTI_EMR_MR21 = 0x200000
EXTI_EMR_MR22 = 0x400000
EXTI_EMR_MR23 = 0x800000
EXTI_EMR_MR24 = 0x1000000
EXTI_EMR_MR25 = 0x2000000
EXTI_EMR_MR26 = 0x4000000
EXTI_EMR_MR27 = 0x8000000
EXTI_EMR_MR28 = 0x10000000
EXTI_EMR_MR29 = 0x20000000
EXTI_EMR_MR30 = 0x40000000
EXTI_EMR_MR31 = 0x80000000
EXTI_RTSR_TR0 = 0x1
EXTI_RTSR_TR1 = 0x2
EXTI_RTSR_TR2 = 0x4
EXTI_RTSR_TR3 = 0x8
EXTI_RTSR_TR4 = 0x10
EXTI_RTSR_TR5 = 0x20
EXTI_RTSR_TR6 = 0x40
EXTI_RTSR_TR7 = 0x80
EXTI_RTSR_TR8 = 0x100
EXTI_RTSR_TR9 = 0x200
EXTI_RTSR_TR10 = 0x400
EXTI_RTSR_TR11 = 0x800
EXTI_RTSR_TR12 = 0x1000
EXTI_RTSR_TR13 = 0x2000
EXTI_RTSR_TR14 = 0x4000
EXTI_RTSR_TR15 = 0x8000
EXTI_RTSR_TR16 = 0x10000
EXTI_RTSR_TR17 = 0x20000
EXTI_RTSR_TR19 = 0x80000
EXTI_RTSR_TR20 = 0x100000
EXTI_RTSR_TR21 = 0x200000
EXTI_RTSR_TR22 = 0x400000
EXTI_FTSR_TR0 = 0x1
EXTI_FTSR_TR1 = 0x2
EXTI_FTSR_TR2 = 0x4
EXTI_FTSR_TR3 = 0x8
EXTI_FTSR_TR4 = 0x10
EXTI_FTSR_TR5 = 0x20
EXTI_FTSR_TR6 = 0x40
EXTI_FTSR_TR7 = 0x80
EXTI_FTSR_TR8 = 0x100
EXTI_FTSR_TR9 = 0x200
EXTI_FTSR_TR10 = 0x400
EXTI_FTSR_TR11 = 0x800
EXTI_FTSR_TR12 = 0x1000
EXTI_FTSR_TR13 = 0x2000
EXTI_FTSR_TR14 = 0x4000
EXTI_FTSR_TR15 = 0x8000
EXTI_FTSR_TR16 = 0x10000
EXTI_FTSR_TR17 = 0x20000
EXTI_FTSR_TR19 = 0x80000
EXTI_FTSR_TR20 = 0x100000
EXTI_FTSR_TR21 = 0x200000
EXTI_FTSR_TR22 = 0x400000
EXTI_SWIER_SWIER0 = 0x1
EXTI_SWIER_SWIER1 = 0x2
EXTI_SWIER_SWIER2 = 0x4
EXTI_SWIER_SWIER3 = 0x8
EXTI_SWIER_SWIER4 = 0x10
EXTI_SWIER_SWIER5 = 0x20
EXTI_SWIER_SWIER6 = 0x40
EXTI_SWIER_SWIER7 = 0x80
EXTI_SWIER_SWIER8 = 0x100
EXTI_SWIER_SWIER9 = 0x200
EXTI_SWIER_SWIER10 = 0x400
EXTI_SWIER_SWIER11 = 0x800
EXTI_SWIER_SWIER12 = 0x1000
EXTI_SWIER_SWIER13 = 0x2000
EXTI_SWIER_SWIER14 = 0x4000
EXTI_SWIER_SWIER15 = 0x8000
EXTI_SWIER_SWIER16 = 0x10000
EXTI_SWIER_SWIER17 = 0x20000
EXTI_SWIER_SWIER19 = 0x80000
EXTI_SWIER_SWIER20 = 0x100000
EXTI_SWIER_SWIER21 = 0x200000
EXTI_SWIER_SWIER22 = 0x400000
EXTI_PR_PR0 = 0x1
EXTI_PR_PR1 = 0x2
EXTI_PR_PR2 = 0x4
EXTI_PR_PR3 = 0x8
EXTI_PR_PR4 = 0x10
EXTI_PR_PR5 = 0x20
EXTI_PR_PR6 = 0x40
EXTI_PR_PR7 = 0x80
EXTI_PR_PR8 = 0x100
EXTI_PR_PR9 = 0x200
EXTI_PR_PR10 = 0x400
EXTI_PR_PR11 = 0x800
EXTI_PR_PR12 = 0x1000
EXTI_PR_PR13 = 0x2000
EXTI_PR_PR14 = 0x4000
EXTI_PR_PR15 = 0x8000
EXTI_PR_PR16 = 0x10000
EXTI_PR_PR17 = 0x20000
EXTI_PR_PR19 = 0x80000
EXTI_PR_PR20 = 0x100000
EXTI_PR_PR21 = 0x200000
EXTI_PR_PR22 = 0x400000
FLASH_ACR_LATENCY = 0x1
FLASH_ACR_PRFTBE = 0x10
FLASH_ACR_PRFTBS = 0x20
FLASH_KEYR_FKEYR = 0xFFFFFFFF
FLASH_OPTKEYR_OPTKEYR = 0xFFFFFFFF
FLASH_FKEY1 = 0x45670123
FLASH_FKEY2 = 0xCDEF89AB
FLASH_OPTKEY1 = 0x45670123
FLASH_OPTKEY2 = 0xCDEF89AB
FLASH_SR_BSY = 0x1
FLASH_SR_PGERR = 0x4
FLASH_SR_WRPRTERR = 0x10
FLASH_SR_EOP = 0x20
FLASH_SR_WRPERR = 0x10
FLASH_CR_PG = 0x1
FLASH_CR_PER = 0x2
FLASH_CR_MER = 0x4
FLASH_CR_OPTPG = 0x10
FLASH_CR_OPTER = 0x20
FLASH_CR_STRT = 0x40
FLASH_CR_LOCK = 0x80
FLASH_CR_OPTWRE = 0x200
FLASH_CR_ERRIE = 0x400
FLASH_CR_EOPIE = 0x1000
FLASH_CR_OBL_LAUNCH = 0x2000
FLASH_AR_FAR = 0xFFFFFFFF
FLASH_OBR_OPTERR = 0x1
FLASH_OBR_RDPRT1 = 0x2
FLASH_OBR_RDPRT2 = 0x4
FLASH_OBR_USER = 0x3700
FLASH_OBR_IWDG_SW = 0x100
FLASH_OBR_nRST_STOP = 0x200
FLASH_OBR_nRST_STDBY = 0x400
FLASH_OBR_nBOOT0 = 0x800
FLASH_OBR_nBOOT1 = 0x1000
FLASH_OBR_VDDA_MONITOR = 0x2000
FLASH_OBR_RAM_PARITY_CHECK = 0x4000
FLASH_OBR_nBOOT0_SW = 0x8000
FLASH_OBR_DATA0 = 0xFF0000
FLASH_OBR_DATA1 = 0xFF000000
FLASH_OBR_BOOT1 = 0x1000
FLASH_OBR_VDDA_ANALOG = 0x2000
FLASH_WRPR_WRP = 0xFFFFFFFF
OB_RDP_RDP = 0xFF
OB_RDP_nRDP = 0xFF00
OB_USER_USER = 0xFF0000
OB_USER_nUSER = 0xFF000000
OB_WRP0_WRP0 = 0xFF
OB_WRP0_nWRP0 = 0xFF00
OB_WRP1_WRP1 = 0xFF0000
OB_WRP1_nWRP1 = 0xFF000000
OB_WRP2_WRP2 = 0xFF
OB_WRP2_nWRP2 = 0xFF00
OB_WRP3_WRP3 = 0xFF0000
OB_WRP3_nWRP3 = 0xFF000000
GPIO_MODER_MODER0 = 0x3
GPIO_MODER_MODER0_0 = 0x1
GPIO_MODER_MODER0_1 = 0x2
GPIO_MODER_MODER1 = 0xC
GPIO_MODER_MODER1_0 = 0x4
GPIO_MODER_MODER1_1 = 0x8
GPIO_MODER_MODER2 = 0x30
GPIO_MODER_MODER2_0 = 0x10
GPIO_MODER_MODER2_1 = 0x20
GPIO_MODER_MODER3 = 0xC0
GPIO_MODER_MODER3_0 = 0x40
GPIO_MODER_MODER3_1 = 0x80
GPIO_MODER_MODER4 = 0x300
GPIO_MODER_MODER4_0 = 0x100
GPIO_MODER_MODER4_1 = 0x200
GPIO_MODER_MODER5 = 0xC00
GPIO_MODER_MODER5_0 = 0x400
GPIO_MODER_MODER5_1 = 0x800
GPIO_MODER_MODER6 = 0x3000
GPIO_MODER_MODER6_0 = 0x1000
GPIO_MODER_MODER6_1 = 0x2000
GPIO_MODER_MODER7 = 0xC000
GPIO_MODER_MODER7_0 = 0x4000
GPIO_MODER_MODER7_1 = 0x8000
GPIO_MODER_MODER8 = 0x30000
GPIO_MODER_MODER8_0 = 0x10000
GPIO_MODER_MODER8_1 = 0x20000
GPIO_MODER_MODER9 = 0xC0000
GPIO_MODER_MODER9_0 = 0x40000
GPIO_MODER_MODER9_1 = 0x80000
GPIO_MODER_MODER10 = 0x300000
GPIO_MODER_MODER10_0 = 0x100000
GPIO_MODER_MODER10_1 = 0x200000
GPIO_MODER_MODER11 = 0xC00000
GPIO_MODER_MODER11_0 = 0x400000
GPIO_MODER_MODER11_1 = 0x800000
GPIO_MODER_MODER12 = 0x3000000
GPIO_MODER_MODER12_0 = 0x1000000
GPIO_MODER_MODER12_1 = 0x2000000
GPIO_MODER_MODER13 = 0xC000000
GPIO_MODER_MODER13_0 = 0x4000000
GPIO_MODER_MODER13_1 = 0x8000000
GPIO_MODER_MODER14 = 0x30000000
GPIO_MODER_MODER14_0 = 0x10000000
GPIO_MODER_MODER14_1 = 0x20000000
GPIO_MODER_MODER15 = 0xC0000000
GPIO_MODER_MODER15_0 = 0x40000000
GPIO_MODER_MODER15_1 = 0x80000000
GPIO_OTYPER_OT_0 = 0x1
GPIO_OTYPER_OT_1 = 0x2
GPIO_OTYPER_OT_2 = 0x4
GPIO_OTYPER_OT_3 = 0x8
GPIO_OTYPER_OT_4 = 0x10
GPIO_OTYPER_OT_5 = 0x20
GPIO_OTYPER_OT_6 = 0x40
GPIO_OTYPER_OT_7 = 0x80
GPIO_OTYPER_OT_8 = 0x100
GPIO_OTYPER_OT_9 = 0x200
GPIO_OTYPER_OT_10 = 0x400
GPIO_OTYPER_OT_11 = 0x800
GPIO_OTYPER_OT_12 = 0x1000
GPIO_OTYPER_OT_13 = 0x2000
GPIO_OTYPER_OT_14 = 0x4000
GPIO_OTYPER_OT_15 = 0x8000
GPIO_OSPEEDR_OSPEEDR0 = 0x3
GPIO_OSPEEDR_OSPEEDR0_0 = 0x1
GPIO_OSPEEDR_OSPEEDR0_1 = 0x2
GPIO_OSPEEDR_OSPEEDR1 = 0xC
GPIO_OSPEEDR_OSPEEDR1_0 = 0x4
GPIO_OSPEEDR_OSPEEDR1_1 = 0x8
GPIO_OSPEEDR_OSPEEDR2 = 0x30
GPIO_OSPEEDR_OSPEEDR2_0 = 0x10
GPIO_OSPEEDR_OSPEEDR2_1 = 0x20
GPIO_OSPEEDR_OSPEEDR3 = 0xC0
GPIO_OSPEEDR_OSPEEDR3_0 = 0x40
GPIO_OSPEEDR_OSPEEDR3_1 = 0x80
GPIO_OSPEEDR_OSPEEDR4 = 0x300
GPIO_OSPEEDR_OSPEEDR4_0 = 0x100
GPIO_OSPEEDR_OSPEEDR4_1 = 0x200
GPIO_OSPEEDR_OSPEEDR5 = 0xC00
GPIO_OSPEEDR_OSPEEDR5_0 = 0x400
GPIO_OSPEEDR_OSPEEDR5_1 = 0x800
GPIO_OSPEEDR_OSPEEDR6 = 0x3000
GPIO_OSPEEDR_OSPEEDR6_0 = 0x1000
GPIO_OSPEEDR_OSPEEDR6_1 = 0x2000
GPIO_OSPEEDR_OSPEEDR7 = 0xC000
GPIO_OSPEEDR_OSPEEDR7_0 = 0x4000
GPIO_OSPEEDR_OSPEEDR7_1 = 0x8000
GPIO_OSPEEDR_OSPEEDR8 = 0x30000
GPIO_OSPEEDR_OSPEEDR8_0 = 0x10000
GPIO_OSPEEDR_OSPEEDR8_1 = 0x20000
GPIO_OSPEEDR_OSPEEDR9 = 0xC0000
GPIO_OSPEEDR_OSPEEDR9_0 = 0x40000
GPIO_OSPEEDR_OSPEEDR9_1 = 0x80000
GPIO_OSPEEDR_OSPEEDR10 = 0x300000
GPIO_OSPEEDR_OSPEEDR10_0 = 0x100000
GPIO_OSPEEDR_OSPEEDR10_1 = 0x200000
GPIO_OSPEEDR_OSPEEDR11 = 0xC00000
GPIO_OSPEEDR_OSPEEDR11_0 = 0x400000
GPIO_OSPEEDR_OSPEEDR11_1 = 0x800000
GPIO_OSPEEDR_OSPEEDR12 = 0x3000000
GPIO_OSPEEDR_OSPEEDR12_0 = 0x1000000
GPIO_OSPEEDR_OSPEEDR12_1 = 0x2000000
GPIO_OSPEEDR_OSPEEDR13 = 0xC000000
GPIO_OSPEEDR_OSPEEDR13_0 = 0x4000000
GPIO_OSPEEDR_OSPEEDR13_1 = 0x8000000
GPIO_OSPEEDR_OSPEEDR14 = 0x30000000
GPIO_OSPEEDR_OSPEEDR14_0 = 0x10000000
GPIO_OSPEEDR_OSPEEDR14_1 = 0x20000000
GPIO_OSPEEDR_OSPEEDR15 = 0xC0000000
GPIO_OSPEEDR_OSPEEDR15_0 = 0x40000000
GPIO_OSPEEDR_OSPEEDR15_1 = 0x80000000
GPIO_OSPEEDER_OSPEEDR0 = 0x3
GPIO_OSPEEDER_OSPEEDR0_0 = 0x1
GPIO_OSPEEDER_OSPEEDR0_1 = 0x2
GPIO_OSPEEDER_OSPEEDR1 = 0xC
GPIO_OSPEEDER_OSPEEDR1_0 = 0x4
GPIO_OSPEEDER_OSPEEDR1_1 = 0x8
GPIO_OSPEEDER_OSPEEDR2 = 0x30
GPIO_OSPEEDER_OSPEEDR2_0 = 0x10
GPIO_OSPEEDER_OSPEEDR2_1 = 0x20
GPIO_OSPEEDER_OSPEEDR3 = 0xC0
GPIO_OSPEEDER_OSPEEDR3_0 = 0x40
GPIO_OSPEEDER_OSPEEDR3_1 = 0x80
GPIO_OSPEEDER_OSPEEDR4 = 0x300
GPIO_OSPEEDER_OSPEEDR4_0 = 0x100
GPIO_OSPEEDER_OSPEEDR4_1 = 0x200
GPIO_OSPEEDER_OSPEEDR5 = 0xC00
GPIO_OSPEEDER_OSPEEDR5_0 = 0x400
GPIO_OSPEEDER_OSPEEDR5_1 = 0x800
GPIO_OSPEEDER_OSPEEDR6 = 0x3000
GPIO_OSPEEDER_OSPEEDR6_0 = 0x1000
GPIO_OSPEEDER_OSPEEDR6_1 = 0x2000
GPIO_OSPEEDER_OSPEEDR7 = 0xC000
GPIO_OSPEEDER_OSPEEDR7_0 = 0x4000
GPIO_OSPEEDER_OSPEEDR7_1 = 0x8000
GPIO_OSPEEDER_OSPEEDR8 = 0x30000
GPIO_OSPEEDER_OSPEEDR8_0 = 0x10000
GPIO_OSPEEDER_OSPEEDR8_1 = 0x20000
GPIO_OSPEEDER_OSPEEDR9 = 0xC0000
GPIO_OSPEEDER_OSPEEDR9_0 = 0x40000
GPIO_OSPEEDER_OSPEEDR9_1 = 0x80000
GPIO_OSPEEDER_OSPEEDR10 = 0x300000
GPIO_OSPEEDER_OSPEEDR10_0 = 0x100000
GPIO_OSPEEDER_OSPEEDR10_1 = 0x200000
GPIO_OSPEEDER_OSPEEDR11 = 0xC00000
GPIO_OSPEEDER_OSPEEDR11_0 = 0x400000
GPIO_OSPEEDER_OSPEEDR11_1 = 0x800000
GPIO_OSPEEDER_OSPEEDR12 = 0x3000000
GPIO_OSPEEDER_OSPEEDR12_0 = 0x1000000
GPIO_OSPEEDER_OSPEEDR12_1 = 0x2000000
GPIO_OSPEEDER_OSPEEDR13 = 0xC000000
GPIO_OSPEEDER_OSPEEDR13_0 = 0x4000000
GPIO_OSPEEDER_OSPEEDR13_1 = 0x8000000
GPIO_OSPEEDER_OSPEEDR14 = 0x30000000
GPIO_OSPEEDER_OSPEEDR14_0 = 0x10000000
GPIO_OSPEEDER_OSPEEDR14_1 = 0x20000000
GPIO_OSPEEDER_OSPEEDR15 = 0xC0000000
GPIO_OSPEEDER_OSPEEDR15_0 = 0x40000000
GPIO_OSPEEDER_OSPEEDR15_1 = 0x80000000
GPIO_PUPDR_PUPDR0 = 0x3
GPIO_PUPDR_PUPDR0_0 = 0x1
GPIO_PUPDR_PUPDR0_1 = 0x2
GPIO_PUPDR_PUPDR1 = 0xC
GPIO_PUPDR_PUPDR1_0 = 0x4
GPIO_PUPDR_PUPDR1_1 = 0x8
GPIO_PUPDR_PUPDR2 = 0x30
GPIO_PUPDR_PUPDR2_0 = 0x10
GPIO_PUPDR_PUPDR2_1 = 0x20
GPIO_PUPDR_PUPDR3 = 0xC0
GPIO_PUPDR_PUPDR3_0 = 0x40
GPIO_PUPDR_PUPDR3_1 = 0x80
GPIO_PUPDR_PUPDR4 = 0x300
GPIO_PUPDR_PUPDR4_0 = 0x100
GPIO_PUPDR_PUPDR4_1 = 0x200
GPIO_PUPDR_PUPDR5 = 0xC00
GPIO_PUPDR_PUPDR5_0 = 0x400
GPIO_PUPDR_PUPDR5_1 = 0x800
GPIO_PUPDR_PUPDR6 = 0x3000
GPIO_PUPDR_PUPDR6_0 = 0x1000
GPIO_PUPDR_PUPDR6_1 = 0x2000
GPIO_PUPDR_PUPDR7 = 0xC000
GPIO_PUPDR_PUPDR7_0 = 0x4000
GPIO_PUPDR_PUPDR7_1 = 0x8000
GPIO_PUPDR_PUPDR8 = 0x30000
GPIO_PUPDR_PUPDR8_0 = 0x10000
GPIO_PUPDR_PUPDR8_1 = 0x20000
GPIO_PUPDR_PUPDR9 = 0xC0000
GPIO_PUPDR_PUPDR9_0 = 0x40000
GPIO_PUPDR_PUPDR9_1 = 0x80000
GPIO_PUPDR_PUPDR10 = 0x300000
GPIO_PUPDR_PUPDR10_0 = 0x100000
GPIO_PUPDR_PUPDR10_1 = 0x200000
GPIO_PUPDR_PUPDR11 = 0xC00000
GPIO_PUPDR_PUPDR11_0 = 0x400000
GPIO_PUPDR_PUPDR11_1 = 0x800000
GPIO_PUPDR_PUPDR12 = 0x3000000
GPIO_PUPDR_PUPDR12_0 = 0x1000000
GPIO_PUPDR_PUPDR12_1 = 0x2000000
GPIO_PUPDR_PUPDR13 = 0xC000000
GPIO_PUPDR_PUPDR13_0 = 0x4000000
GPIO_PUPDR_PUPDR13_1 = 0x8000000
GPIO_PUPDR_PUPDR14 = 0x30000000
GPIO_PUPDR_PUPDR14_0 = 0x10000000
GPIO_PUPDR_PUPDR14_1 = 0x20000000
GPIO_PUPDR_PUPDR15 = 0xC0000000
GPIO_PUPDR_PUPDR15_0 = 0x40000000
GPIO_PUPDR_PUPDR15_1 = 0x80000000
GPIO_IDR_0 = 0x1
GPIO_IDR_1 = 0x2
GPIO_IDR_2 = 0x4
GPIO_IDR_3 = 0x8
GPIO_IDR_4 = 0x10
GPIO_IDR_5 = 0x20
GPIO_IDR_6 = 0x40
GPIO_IDR_7 = 0x80
GPIO_IDR_8 = 0x100
GPIO_IDR_9 = 0x200
GPIO_IDR_10 = 0x400
GPIO_IDR_11 = 0x800
GPIO_IDR_12 = 0x1000
GPIO_IDR_13 = 0x2000
GPIO_IDR_14 = 0x4000
GPIO_IDR_15 = 0x8000
GPIO_ODR_0 = 0x1
GPIO_ODR_1 = 0x2
GPIO_ODR_2 = 0x4
GPIO_ODR_3 = 0x8
GPIO_ODR_4 = 0x10
GPIO_ODR_5 = 0x20
GPIO_ODR_6 = 0x40
GPIO_ODR_7 = 0x80
GPIO_ODR_8 = 0x100
GPIO_ODR_9 = 0x200
GPIO_ODR_10 = 0x400
GPIO_ODR_11 = 0x800
GPIO_ODR_12 = 0x1000
GPIO_ODR_13 = 0x2000
GPIO_ODR_14 = 0x4000
GPIO_ODR_15 = 0x8000
GPIO_BSRR_BS_0 = 0x1
GPIO_BSRR_BS_1 = 0x2
GPIO_BSRR_BS_2 = 0x4
GPIO_BSRR_BS_3 = 0x8
GPIO_BSRR_BS_4 = 0x10
GPIO_BSRR_BS_5 = 0x20
GPIO_BSRR_BS_6 = 0x40
GPIO_BSRR_BS_7 = 0x80
GPIO_BSRR_BS_8 = 0x100
GPIO_BSRR_BS_9 = 0x200
GPIO_BSRR_BS_10 = 0x400
GPIO_BSRR_BS_11 = 0x800
GPIO_BSRR_BS_12 = 0x1000
GPIO_BSRR_BS_13 = 0x2000
GPIO_BSRR_BS_14 = 0x4000
GPIO_BSRR_BS_15 = 0x8000
GPIO_BSRR_BR_0 = 0x10000
GPIO_BSRR_BR_1 = 0x20000
GPIO_BSRR_BR_2 = 0x40000
GPIO_BSRR_BR_3 = 0x80000
GPIO_BSRR_BR_4 = 0x100000
GPIO_BSRR_BR_5 = 0x200000
GPIO_BSRR_BR_6 = 0x400000
GPIO_BSRR_BR_7 = 0x800000
GPIO_BSRR_BR_8 = 0x1000000
GPIO_BSRR_BR_9 = 0x2000000
GPIO_BSRR_BR_10 = 0x4000000
GPIO_BSRR_BR_11 = 0x8000000
GPIO_BSRR_BR_12 = 0x10000000
GPIO_BSRR_BR_13 = 0x20000000
GPIO_BSRR_BR_14 = 0x40000000
GPIO_BSRR_BR_15 = 0x80000000
GPIO_LCKR_LCK0 = 0x1
GPIO_LCKR_LCK1 = 0x2
GPIO_LCKR_LCK2 = 0x4
GPIO_LCKR_LCK3 = 0x8
GPIO_LCKR_LCK4 = 0x10
GPIO_LCKR_LCK5 = 0x20
GPIO_LCKR_LCK6 = 0x40
GPIO_LCKR_LCK7 = 0x80
GPIO_LCKR_LCK8 = 0x100
GPIO_LCKR_LCK9 = 0x200
GPIO_LCKR_LCK10 = 0x400
GPIO_LCKR_LCK11 = 0x800
GPIO_LCKR_LCK12 = 0x1000
GPIO_LCKR_LCK13 = 0x2000
GPIO_LCKR_LCK14 = 0x4000
GPIO_LCKR_LCK15 = 0x8000
GPIO_LCKR_LCKK = 0x10000
GPIO_AFRL_AFR0 = 0xF
GPIO_AFRL_AFR1 = 0xF0
GPIO_AFRL_AFR2 = 0xF00
GPIO_AFRL_AFR3 = 0xF000
GPIO_AFRL_AFR4 = 0xF0000
GPIO_AFRL_AFR5 = 0xF00000
GPIO_AFRL_AFR6 = 0xF000000
GPIO_AFRL_AFR7 = 0xF0000000
GPIO_AFRH_AFR8 = 0xF
GPIO_AFRH_AFR9 = 0xF0
GPIO_AFRH_AFR10 = 0xF00
GPIO_AFRH_AFR11 = 0xF000
GPIO_AFRH_AFR12 = 0xF0000
GPIO_AFRH_AFR13 = 0xF00000
GPIO_AFRH_AFR14 = 0xF000000
GPIO_AFRH_AFR15 = 0xF0000000
GPIO_AFRL_AFRL0 = 0xF
GPIO_AFRL_AFRL1 = 0xF0
GPIO_AFRL_AFRL2 = 0xF00
GPIO_AFRL_AFRL3 = 0xF000
GPIO_AFRL_AFRL4 = 0xF0000
GPIO_AFRL_AFRL5 = 0xF00000
GPIO_AFRL_AFRL6 = 0xF000000
GPIO_AFRL_AFRL7 = 0xF0000000
GPIO_AFRH_AFRH0 = 0xF
GPIO_AFRH_AFRH1 = 0xF0
GPIO_AFRH_AFRH2 = 0xF00
GPIO_AFRH_AFRH3 = 0xF000
GPIO_AFRH_AFRH4 = 0xF0000
GPIO_AFRH_AFRH5 = 0xF00000
GPIO_AFRH_AFRH6 = 0xF000000
GPIO_AFRH_AFRH7 = 0xF0000000
GPIO_BRR_BR_0 = 0x1
GPIO_BRR_BR_1 = 0x2
GPIO_BRR_BR_2 = 0x4
GPIO_BRR_BR_3 = 0x8
GPIO_BRR_BR_4 = 0x10
GPIO_BRR_BR_5 = 0x20
GPIO_BRR_BR_6 = 0x40
GPIO_BRR_BR_7 = 0x80
GPIO_BRR_BR_8 = 0x100
GPIO_BRR_BR_9 = 0x200
GPIO_BRR_BR_10 = 0x400
GPIO_BRR_BR_11 = 0x800
GPIO_BRR_BR_12 = 0x1000
GPIO_BRR_BR_13 = 0x2000
GPIO_BRR_BR_14 = 0x4000
GPIO_BRR_BR_15 = 0x8000
I2C_CR1_PE = 0x1
I2C_CR1_TXIE = 0x2
I2C_CR1_RXIE = 0x4
I2C_CR1_ADDRIE = 0x8
I2C_CR1_NACKIE = 0x10
I2C_CR1_STOPIE = 0x20
I2C_CR1_TCIE = 0x40
I2C_CR1_ERRIE = 0x80
I2C_CR1_DFN = 0xF00
I2C_CR1_ANFOFF = 0x1000
I2C_CR1_SWRST = 0x2000
I2C_CR1_TXDMAEN = 0x4000
I2C_CR1_RXDMAEN = 0x8000
I2C_CR1_SBC = 0x10000
I2C_CR1_NOSTRETCH = 0x20000
I2C_CR1_WUPEN = 0x40000
I2C_CR1_GCEN = 0x80000
I2C_CR1_SMBHEN = 0x100000
I2C_CR1_SMBDEN = 0x200000
I2C_CR1_ALERTEN = 0x400000
I2C_CR1_PECEN = 0x800000
I2C_CR2_SADD = 0x3FF
I2C_CR2_RD_WRN = 0x400
I2C_CR2_ADD10 = 0x800
I2C_CR2_HEAD10R = 0x1000
I2C_CR2_START = 0x2000
I2C_CR2_STOP = 0x4000
I2C_CR2_NACK = 0x8000
I2C_CR2_NBYTES = 0xFF0000
I2C_CR2_RELOAD = 0x1000000
I2C_CR2_AUTOEND = 0x2000000
I2C_CR2_PECBYTE = 0x4000000
I2C_OAR1_OA1 = 0x3FF
I2C_OAR1_OA1MODE = 0x400
I2C_OAR1_OA1EN = 0x8000
I2C_OAR2_OA2 = 0xFE
I2C_OAR2_OA2MSK = 0x700
I2C_OAR2_OA2EN = 0x8000
I2C_TIMINGR_SCLL = 0xFF
I2C_TIMINGR_SCLH = 0xFF00
I2C_TIMINGR_SDADEL = 0xF0000
I2C_TIMINGR_SCLDEL = 0xF00000
I2C_TIMINGR_PRESC = 0xF0000000
I2C_TIMEOUTR_TIMEOUTA = 0xFFF
I2C_TIMEOUTR_TIDLE = 0x1000
I2C_TIMEOUTR_TIMOUTEN = 0x8000
I2C_TIMEOUTR_TIMEOUTB = 0xFFF0000
I2C_TIMEOUTR_TEXTEN = 0x80000000
I2C_ISR_TXE = 0x1
I2C_ISR_TXIS = 0x2
I2C_ISR_RXNE = 0x4
I2C_ISR_ADDR = 0x8
I2C_ISR_NACKF = 0x10
I2C_ISR_STOPF = 0x20
I2C_ISR_TC = 0x40
I2C_ISR_TCR = 0x80
I2C_ISR_BERR = 0x100
I2C_ISR_ARLO = 0x200
I2C_ISR_OVR = 0x400
I2C_ISR_PECERR = 0x800
I2C_ISR_TIMEOUT = 0x1000
I2C_ISR_ALERT = 0x2000
I2C_ISR_BUSY = 0x8000
I2C_ISR_DIR = 0x10000
I2C_ISR_ADDCODE = 0xFE0000
I2C_ICR_ADDRCF = 0x8
I2C_ICR_NACKCF = 0x10
I2C_ICR_STOPCF = 0x20
I2C_ICR_BERRCF = 0x100
I2C_ICR_ARLOCF = 0x200
I2C_ICR_OVRCF = 0x400
I2C_ICR_PECCF = 0x800
I2C_ICR_TIMOUTCF = 0x1000
I2C_ICR_ALERTCF = 0x2000
I2C_PECR_PEC = 0xFF
I2C_RXDR_RXDATA = 0xFF
I2C_TXDR_TXDATA = 0xFF
IWDG_KR_KEY = 0xFFFF
IWDG_PR_PR = 0x7
IWDG_PR_PR_0 = 0x1
IWDG_PR_PR_1 = 0x2
IWDG_PR_PR_2 = 0x4
IWDG_RLR_RL = 0xFFF
IWDG_SR_PVU = 0x1
IWDG_SR_RVU = 0x2
IWDG_SR_WVU = 0x4
IWDG_WINR_WIN = 0xFFF
PWR_CR_LPDS = 0x1
PWR_CR_PDDS = 0x2
PWR_CR_CWUF = 0x4
PWR_CR_CSBF = 0x8
PWR_CR_PVDE = 0x10
PWR_CR_PLS = 0xE0
PWR_CR_PLS_0 = 0x20
PWR_CR_PLS_1 = 0x40
PWR_CR_PLS_2 = 0x80
PWR_CR_PLS_LEV0 = 0x0
PWR_CR_PLS_LEV1 = 0x20
PWR_CR_PLS_LEV2 = 0x40
PWR_CR_PLS_LEV3 = 0x60
PWR_CR_PLS_LEV4 = 0x80
PWR_CR_PLS_LEV5 = 0xA0
PWR_CR_PLS_LEV6 = 0xC0
PWR_CR_PLS_LEV7 = 0xE0
PWR_CR_DBP = 0x100
PWR_CR_LPSDSR = 0x1
PWR_CSR_WUF = 0x1
PWR_CSR_SBF = 0x2
PWR_CSR_PVDO = 0x4
PWR_CSR_VREFINTRDY = 0x8
PWR_CSR_EWUP1 = 0x100
PWR_CSR_EWUP2 = 0x200
PWR_CSR_EWUP3 = 0x400
PWR_CSR_EWUP4 = 0x800
PWR_CSR_EWUP5 = 0x1000
PWR_CSR_EWUP6 = 0x2000
PWR_CSR_EWUP7 = 0x4000
PWR_CSR_EWUP8 = 0x8000
PWR_CSR_VREFINTRDYF = 0x8
RCC_CR_HSION = 0x1
RCC_CR_HSIRDY = 0x2
RCC_CR_HSITRIM = 0xF8
RCC_CR_HSICAL = 0xFF00
RCC_CR_HSEON = 0x10000
RCC_CR_HSERDY = 0x20000
RCC_CR_HSEBYP = 0x40000
RCC_CR_CSSON = 0x80000
RCC_CR_PLLON = 0x1000000
RCC_CR_PLLRDY = 0x2000000
RCC_CFGR_SW = 0x3
RCC_CFGR_SW_0 = 0x1
RCC_CFGR_SW_1 = 0x2
RCC_CFGR_SW_HSI = 0x0
RCC_CFGR_SW_HSE = 0x1
RCC_CFGR_SW_PLL = 0x2
RCC_CFGR_SW_HSI48 = 0x3
RCC_CFGR_SWS = 0xC
RCC_CFGR_SWS_0 = 0x4
RCC_CFGR_SWS_1 = 0x8
RCC_CFGR_SWS_HSI = 0x0
RCC_CFGR_SWS_HSE = 0x4
RCC_CFGR_SWS_PLL = 0x8
RCC_CFGR_SWS_HSI48 = 0xC
RCC_CFGR_HPRE = 0xF0
RCC_CFGR_HPRE_0 = 0x10
RCC_CFGR_HPRE_1 = 0x20
RCC_CFGR_HPRE_2 = 0x40
RCC_CFGR_HPRE_3 = 0x80
RCC_CFGR_HPRE_DIV1 = 0x0
RCC_CFGR_HPRE_DIV2 = 0x80
RCC_CFGR_HPRE_DIV4 = 0x90
RCC_CFGR_HPRE_DIV8 = 0xA0
RCC_CFGR_HPRE_DIV16 = 0xB0
RCC_CFGR_HPRE_DIV64 = 0xC0
RCC_CFGR_HPRE_DIV128 = 0xD0
RCC_CFGR_HPRE_DIV256 = 0xE0
RCC_CFGR_HPRE_DIV512 = 0xF0
RCC_CFGR_PPRE = 0x700
RCC_CFGR_PPRE_0 = 0x100
RCC_CFGR_PPRE_1 = 0x200
RCC_CFGR_PPRE_2 = 0x400
RCC_CFGR_PPRE_DIV1 = 0x0
RCC_CFGR_PPRE_DIV2 = 0x400
RCC_CFGR_PPRE_DIV4 = 0x500
RCC_CFGR_PPRE_DIV8 = 0x600
RCC_CFGR_PPRE_DIV16 = 0x700
RCC_CFGR_ADCPRE = 0x4000
RCC_CFGR_PLLSRC = 0x18000
RCC_CFGR_PLLSRC_0 = 0x8000
RCC_CFGR_PLLSRC_1 = 0x10000
RCC_CFGR_PLLSRC_PREDIV1 = 0x10000
RCC_CFGR_PLLSRC_HSI_DIV2 = 0x0
RCC_CFGR_PLLSRC_HSI_PREDIV = 0x8000
RCC_CFGR_PLLSRC_HSE_PREDIV = 0x10000
RCC_CFGR_PLLSRC_HSI48_PREDIV = 0x18000
RCC_CFGR_PLLXTPRE = 0x20000
RCC_CFGR_PLLXTPRE_PREDIV1 = 0x0
RCC_CFGR_PLLXTPRE_PREDIV1_Div2 = 0x20000
RCC_CFGR_PLLSRC_HSI_Div2 = 0x0
RCC_CFGR_PLLMUL = 0x3C0000
RCC_CFGR_PLLMUL_0 = 0x40000
RCC_CFGR_PLLMUL_1 = 0x80000
RCC_CFGR_PLLMUL_2 = 0x100000
RCC_CFGR_PLLMUL_3 = 0x200000
RCC_CFGR_PLLMUL2 = 0x0
RCC_CFGR_PLLMUL3 = 0x40000
RCC_CFGR_PLLMUL4 = 0x80000
RCC_CFGR_PLLMUL5 = 0xC0000
RCC_CFGR_PLLMUL6 = 0x100000
RCC_CFGR_PLLMUL7 = 0x140000
RCC_CFGR_PLLMUL8 = 0x180000
RCC_CFGR_PLLMUL9 = 0x1C0000
RCC_CFGR_PLLMUL10 = 0x200000
RCC_CFGR_PLLMUL11 = 0x240000
RCC_CFGR_PLLMUL12 = 0x280000
RCC_CFGR_PLLMUL13 = 0x2C0000
RCC_CFGR_PLLMUL14 = 0x300000
RCC_CFGR_PLLMUL15 = 0x340000
RCC_CFGR_PLLMUL16 = 0x380000
RCC_CFGR_PLLMULL = 0x3C0000
RCC_CFGR_PLLMULL_0 = 0x40000
RCC_CFGR_PLLMULL_1 = 0x80000
RCC_CFGR_PLLMULL_2 = 0x100000
RCC_CFGR_PLLMULL_3 = 0x200000
RCC_CFGR_PLLMULL2 = 0x0
RCC_CFGR_PLLMULL3 = 0x40000
RCC_CFGR_PLLMULL4 = 0x80000
RCC_CFGR_PLLMULL5 = 0xC0000
RCC_CFGR_PLLMULL6 = 0x100000
RCC_CFGR_PLLMULL7 = 0x140000
RCC_CFGR_PLLMULL8 = 0x180000
RCC_CFGR_PLLMULL9 = 0x1C0000
RCC_CFGR_PLLMULL10 = 0x200000
RCC_CFGR_PLLMULL11 = 0x240000
RCC_CFGR_PLLMULL12 = 0x280000
RCC_CFGR_PLLMULL13 = 0x2C0000
RCC_CFGR_PLLMULL14 = 0x300000
RCC_CFGR_PLLMULL15 = 0x340000
RCC_CFGR_PLLMULL16 = 0x380000
RCC_CFGR_MCO = 0xF000000
RCC_CFGR_MCO_0 = 0x1000000
RCC_CFGR_MCO_1 = 0x2000000
RCC_CFGR_MCO_2 = 0x4000000
RCC_CFGR_MCO_3 = 0x8000000
RCC_CFGR_MCO_NOCLOCK = 0x0
RCC_CFGR_MCO_HSI14 = 0x1000000
RCC_CFGR_MCO_LSI = 0x2000000
RCC_CFGR_MCO_LSE = 0x3000000
RCC_CFGR_MCO_SYSCLK = 0x4000000
RCC_CFGR_MCO_HSI = 0x5000000
RCC_CFGR_MCO_HSE = 0x6000000
RCC_CFGR_MCO_PLL = 0x7000000
RCC_CFGR_MCO_HSI48 = 0x8000000
RCC_CFGR_MCO_PRE = 0x70000000
RCC_CFGR_MCO_PRE_1 = 0x0
RCC_CFGR_MCO_PRE_2 = 0x10000000
RCC_CFGR_MCO_PRE_4 = 0x20000000
RCC_CFGR_MCO_PRE_8 = 0x30000000
RCC_CFGR_MCO_PRE_16 = 0x40000000
RCC_CFGR_MCO_PRE_32 = 0x50000000
RCC_CFGR_MCO_PRE_64 = 0x60000000
RCC_CFGR_MCO_PRE_128 = 0x70000000
RCC_CFGR_PLLNODIV = 0x80000000
RCC_CIR_LSIRDYF = 0x1
RCC_CIR_LSERDYF = 0x2
RCC_CIR_HSIRDYF = 0x4
RCC_CIR_HSERDYF = 0x8
RCC_CIR_PLLRDYF = 0x10
RCC_CIR_HSI14RDYF = 0x20
RCC_CIR_HSI48RDYF = 0x40
RCC_CIR_CSSF = 0x80
RCC_CIR_LSIRDYIE = 0x100
RCC_CIR_LSERDYIE = 0x200
RCC_CIR_HSIRDYIE = 0x400
RCC_CIR_HSERDYIE = 0x800
RCC_CIR_PLLRDYIE = 0x1000
RCC_CIR_HSI14RDYIE = 0x2000
RCC_CIR_HSI48RDYIE = 0x4000
RCC_CIR_LSIRDYC = 0x10000
RCC_CIR_LSERDYC = 0x20000
RCC_CIR_HSIRDYC = 0x40000
RCC_CIR_HSERDYC = 0x80000
RCC_CIR_PLLRDYC = 0x100000
RCC_CIR_HSI14RDYC = 0x200000
RCC_CIR_HSI48RDYC = 0x400000
RCC_CIR_CSSC = 0x800000
RCC_APB2RSTR_SYSCFGRST = 0x1
RCC_APB2RSTR_ADCRST = 0x200
RCC_APB2RSTR_USART8RST = 0x80
RCC_APB2RSTR_USART7RST = 0x40
RCC_APB2RSTR_USART6RST = 0x20
RCC_APB2RSTR_TIM1RST = 0x800
RCC_APB2RSTR_SPI1RST = 0x1000
RCC_APB2RSTR_USART1RST = 0x4000
RCC_APB2RSTR_TIM15RST = 0x10000
RCC_APB2RSTR_TIM16RST = 0x20000
RCC_APB2RSTR_TIM17RST = 0x40000
RCC_APB2RSTR_DBGMCURST = 0x400000
RCC_APB2RSTR_ADC1RST = 0x200
RCC_APB1RSTR_TIM2RST = 0x1
RCC_APB1RSTR_TIM3RST = 0x2
RCC_APB1RSTR_TIM6RST = 0x10
RCC_APB1RSTR_TIM7RST = 0x20
RCC_APB1RSTR_TIM14RST = 0x100
RCC_APB1RSTR_WWDGRST = 0x800
RCC_APB1RSTR_SPI2RST = 0x4000
RCC_APB1RSTR_USART2RST = 0x20000
RCC_APB1RSTR_USART3RST = 0x40000
RCC_APB1RSTR_USART4RST = 0x80000
RCC_APB1RSTR_USART5RST = 0x100000
RCC_APB1RSTR_I2C1RST = 0x200000
RCC_APB1RSTR_I2C2RST = 0x400000
RCC_APB1RSTR_USBRST = 0x800000
RCC_APB1RSTR_CANRST = 0x2000000
RCC_APB1RSTR_CRSRST = 0x8000000
RCC_APB1RSTR_PWRRST = 0x10000000
RCC_APB1RSTR_DACRST = 0x20000000
RCC_APB1RSTR_CECRST = 0x40000000
RCC_AHBENR_DMAEN = 0x1
RCC_AHBENR_DMA2EN = 0x2
RCC_AHBENR_SRAMEN = 0x4
RCC_AHBENR_FLITFEN = 0x10
RCC_AHBENR_CRCEN = 0x40
RCC_AHBENR_GPIOAEN = 0x20000
RCC_AHBENR_GPIOBEN = 0x40000
RCC_AHBENR_GPIOCEN = 0x80000
RCC_AHBENR_GPIODEN = 0x100000
RCC_AHBENR_GPIOEEN = 0x200000
RCC_AHBENR_GPIOFEN = 0x400000
RCC_AHBENR_TSCEN = 0x1000000
RCC_AHBENR_DMA1EN = 0x1
RCC_AHBENR_TSEN = 0x1000000
RCC_APB2ENR_SYSCFGCOMPEN = 0x1
RCC_APB2ENR_USART6EN = 0x20
RCC_APB2ENR_USART7EN = 0x40
RCC_APB2ENR_USART8EN = 0x80
RCC_APB2ENR_ADCEN = 0x200
RCC_APB2ENR_TIM1EN = 0x800
RCC_APB2ENR_SPI1EN = 0x1000
RCC_APB2ENR_USART1EN = 0x4000
RCC_APB2ENR_TIM15EN = 0x10000
RCC_APB2ENR_TIM16EN = 0x20000
RCC_APB2ENR_TIM17EN = 0x40000
RCC_APB2ENR_DBGMCUEN = 0x400000
RCC_APB2ENR_SYSCFGEN = 0x1
RCC_APB2ENR_ADC1EN = 0x200
RCC_APB1ENR_TIM2EN = 0x1
RCC_APB1ENR_TIM3EN = 0x2
RCC_APB1ENR_TIM6EN = 0x10
RCC_APB1ENR_TIM7EN = 0x20
RCC_APB1ENR_TIM14EN = 0x100
RCC_APB1ENR_WWDGEN = 0x800
RCC_APB1ENR_SPI2EN = 0x4000
RCC_APB1ENR_USART2EN = 0x20000
RCC_APB1ENR_USART3EN = 0x40000
RCC_APB1ENR_USART4EN = 0x80000
RCC_APB1ENR_USART5EN = 0x100000
RCC_APB1ENR_I2C1EN = 0x200000
RCC_APB1ENR_I2C2EN = 0x400000
RCC_APB1ENR_USBEN = 0x800000
RCC_APB1ENR_CANEN = 0x2000000
RCC_APB1ENR_CRSEN = 0x8000000
RCC_APB1ENR_PWREN = 0x10000000
RCC_APB1ENR_DACEN = 0x20000000
RCC_APB1ENR_CECEN = 0x40000000
RCC_BDCR_LSEON = 0x1
RCC_BDCR_LSERDY = 0x2
RCC_BDCR_LSEBYP = 0x4
RCC_BDCR_LSEDRV = 0x18
RCC_BDCR_LSEDRV_0 = 0x8
RCC_BDCR_LSEDRV_1 = 0x10
RCC_BDCR_RTCSEL = 0x300
RCC_BDCR_RTCSEL_0 = 0x100
RCC_BDCR_RTCSEL_1 = 0x200
RCC_BDCR_RTCSEL_NOCLOCK = 0x0
RCC_BDCR_RTCSEL_LSE = 0x100
RCC_BDCR_RTCSEL_LSI = 0x200
RCC_BDCR_RTCSEL_HSE = 0x300
RCC_BDCR_RTCEN = 0x8000
RCC_BDCR_BDRST = 0x10000
RCC_CSR_LSION = 0x1
RCC_CSR_LSIRDY = 0x2
RCC_CSR_V18PWRRSTF = 0x800000
RCC_CSR_RMVF = 0x1000000
RCC_CSR_OBLRSTF = 0x2000000
RCC_CSR_PINRSTF = 0x4000000
RCC_CSR_PORRSTF = 0x8000000
RCC_CSR_SFTRSTF = 0x10000000
RCC_CSR_IWDGRSTF = 0x20000000
RCC_CSR_WWDGRSTF = 0x40000000
RCC_CSR_LPWRRSTF = 0x80000000
RCC_CSR_OBL = 0x2000000
RCC_AHBRSTR_GPIOARST = 0x20000
RCC_AHBRSTR_GPIOBRST = 0x40000
RCC_AHBRSTR_GPIOCRST = 0x80000
RCC_AHBRSTR_GPIODRST = 0x10000
RCC_AHBRSTR_GPIOERST = 0x20000
RCC_AHBRSTR_GPIOFRST = 0x40000
RCC_AHBRSTR_TSCRST = 0x100000
RCC_AHBRSTR_TSRST = 0x100000
RCC_CFGR2_PREDIV1 = 0xF
RCC_CFGR2_PREDIV1_0 = 0x1
RCC_CFGR2_PREDIV1_1 = 0x2
RCC_CFGR2_PREDIV1_2 = 0x4
RCC_CFGR2_PREDIV1_3 = 0x8
RCC_CFGR2_PREDIV1_DIV1 = 0x0
RCC_CFGR2_PREDIV1_DIV2 = 0x1
RCC_CFGR2_PREDIV1_DIV3 = 0x2
RCC_CFGR2_PREDIV1_DIV4 = 0x3
RCC_CFGR2_PREDIV1_DIV5 = 0x4
RCC_CFGR2_PREDIV1_DIV6 = 0x5
RCC_CFGR2_PREDIV1_DIV7 = 0x6
RCC_CFGR2_PREDIV1_DIV8 = 0x7
RCC_CFGR2_PREDIV1_DIV9 = 0x8
RCC_CFGR2_PREDIV1_DIV10 = 0x9
RCC_CFGR2_PREDIV1_DIV11 = 0xA
RCC_CFGR2_PREDIV1_DIV12 = 0xB
RCC_CFGR2_PREDIV1_DIV13 = 0xC
RCC_CFGR2_PREDIV1_DIV14 = 0xD
RCC_CFGR2_PREDIV1_DIV15 = 0xE
RCC_CFGR2_PREDIV1_DIV16 = 0xF
RCC_CFGR3_USART1SW = 0x3
RCC_CFGR3_USART1SW_0 = 0x1
RCC_CFGR3_USART1SW_1 = 0x2
RCC_CFGR3_I2C1SW = 0x10
RCC_CFGR3_CECSW = 0x40
RCC_CFGR3_USBSW = 0x80
RCC_CFGR3_ADCSW = 0x100
RCC_CFGR3_USART2SW = 0x30000
RCC_CFGR3_USART2SW_0 = 0x10000
RCC_CFGR3_USART2SW_1 = 0x20000
RCC_CFGR3_USART3SW = 0xC0000
RCC_CFGR3_USART3SW_0 = 0x40000
RCC_CFGR3_USART3SW_1 = 0x80000
RCC_CR2_HSI14ON = 0x1
RCC_CR2_HSI14RDY = 0x2
RCC_CR2_HSI14DIS = 0x4
RCC_CR2_HSI14TRIM = 0xF8
RCC_CR2_HSI14CAL = 0xFF00
RCC_CR2_HSI48ON = 0x10000
RCC_CR2_HSI48RDY = 0x20000
RCC_CR2_HSI48CAL = 0xFF000000
RTC_TR_PM = 0x400000
RTC_TR_HT = 0x300000
RTC_TR_HT_0 = 0x100000
RTC_TR_HT_1 = 0x200000
RTC_TR_HU = 0xF0000
RTC_TR_HU_0 = 0x10000
RTC_TR_HU_1 = 0x20000
RTC_TR_HU_2 = 0x40000
RTC_TR_HU_3 = 0x80000
RTC_TR_MNT = 0x7000
RTC_TR_MNT_0 = 0x1000
RTC_TR_MNT_1 = 0x2000
RTC_TR_MNT_2 = 0x4000
RTC_TR_MNU = 0xF00
RTC_TR_MNU_0 = 0x100
RTC_TR_MNU_1 = 0x200
RTC_TR_MNU_2 = 0x400
RTC_TR_MNU_3 = 0x800
RTC_TR_ST = 0x70
RTC_TR_ST_0 = 0x10
RTC_TR_ST_1 = 0x20
RTC_TR_ST_2 = 0x40
RTC_TR_SU = 0xF
RTC_TR_SU_0 = 0x1
RTC_TR_SU_1 = 0x2
RTC_TR_SU_2 = 0x4
RTC_TR_SU_3 = 0x8
RTC_DR_YT = 0xF00000
RTC_DR_YT_0 = 0x100000
RTC_DR_YT_1 = 0x200000
RTC_DR_YT_2 = 0x400000
RTC_DR_YT_3 = 0x800000
RTC_DR_YU = 0xF0000
RTC_DR_YU_0 = 0x10000
RTC_DR_YU_1 = 0x20000
RTC_DR_YU_2 = 0x40000
RTC_DR_YU_3 = 0x80000
RTC_DR_WDU = 0xE000
RTC_DR_WDU_0 = 0x2000
RTC_DR_WDU_1 = 0x4000
RTC_DR_WDU_2 = 0x8000
RTC_DR_MT = 0x1000
RTC_DR_MU = 0xF00
RTC_DR_MU_0 = 0x100
RTC_DR_MU_1 = 0x200
RTC_DR_MU_2 = 0x400
RTC_DR_MU_3 = 0x800
RTC_DR_DT = 0x30
RTC_DR_DT_0 = 0x10
RTC_DR_DT_1 = 0x20
RTC_DR_DU = 0xF
RTC_DR_DU_0 = 0x1
RTC_DR_DU_1 = 0x2
RTC_DR_DU_2 = 0x4
RTC_DR_DU_3 = 0x8
RTC_CR_COE = 0x800000
RTC_CR_OSEL = 0x600000
RTC_CR_OSEL_0 = 0x200000
RTC_CR_OSEL_1 = 0x400000
RTC_CR_POL = 0x100000
RTC_CR_COSEL = 0x80000
RTC_CR_BKP = 0x40000
RTC_CR_SUB1H = 0x20000
RTC_CR_ADD1H = 0x10000
RTC_CR_TSIE = 0x8000
RTC_CR_WUTIE = 0x4000
RTC_CR_ALRAIE = 0x1000
RTC_CR_TSE = 0x800
RTC_CR_WUTE = 0x400
RTC_CR_ALRAE = 0x100
RTC_CR_FMT = 0x40
RTC_CR_BYPSHAD = 0x20
RTC_CR_REFCKON = 0x10
RTC_CR_TSEDGE = 0x8
RTC_CR_WUCKSEL = 0x7
RTC_CR_WUCKSEL_0 = 0x1
RTC_CR_WUCKSEL_1 = 0x2
RTC_CR_WUCKSEL_2 = 0x4
RTC_CR_BCK = 0x40000
RTC_CR_CALSEL = 0x80000
RTC_ISR_RECALPF = 0x10000
RTC_ISR_TAMP3F = 0x8000
RTC_ISR_TAMP2F = 0x4000
RTC_ISR_TAMP1F = 0x2000
RTC_ISR_TSOVF = 0x1000
RTC_ISR_TSF = 0x800
RTC_ISR_WUTF = 0x400
RTC_ISR_ALRAF = 0x100
RTC_ISR_INIT = 0x80
RTC_ISR_INITF = 0x40
RTC_ISR_RSF = 0x20
RTC_ISR_INITS = 0x10
RTC_ISR_SHPF = 0x8
RTC_ISR_WUTWF = 0x4
RTC_ISR_ALRAWF = 0x1
RTC_PRER_PREDIV_A = 0x7F0000
RTC_PRER_PREDIV_S = 0x7FFF
RTC_WUTR_WUT = 0xFFFF
RTC_ALRMAR_MSK4 = 0x80000000
RTC_ALRMAR_WDSEL = 0x40000000
RTC_ALRMAR_DT = 0x30000000
RTC_ALRMAR_DT_0 = 0x10000000
RTC_ALRMAR_DT_1 = 0x20000000
RTC_ALRMAR_DU = 0xF000000
RTC_ALRMAR_DU_0 = 0x1000000
RTC_ALRMAR_DU_1 = 0x2000000
RTC_ALRMAR_DU_2 = 0x4000000
RTC_ALRMAR_DU_3 = 0x8000000
RTC_ALRMAR_MSK3 = 0x800000
RTC_ALRMAR_PM = 0x400000
RTC_ALRMAR_HT = 0x300000
RTC_ALRMAR_HT_0 = 0x100000
RTC_ALRMAR_HT_1 = 0x200000
RTC_ALRMAR_HU = 0xF0000
RTC_ALRMAR_HU_0 = 0x10000
RTC_ALRMAR_HU_1 = 0x20000
RTC_ALRMAR_HU_2 = 0x40000
RTC_ALRMAR_HU_3 = 0x80000
RTC_ALRMAR_MSK2 = 0x8000
RTC_ALRMAR_MNT = 0x7000
RTC_ALRMAR_MNT_0 = 0x1000
RTC_ALRMAR_MNT_1 = 0x2000
RTC_ALRMAR_MNT_2 = 0x4000
RTC_ALRMAR_MNU = 0xF00
RTC_ALRMAR_MNU_0 = 0x100
RTC_ALRMAR_MNU_1 = 0x200
RTC_ALRMAR_MNU_2 = 0x400
RTC_ALRMAR_MNU_3 = 0x800
RTC_ALRMAR_MSK1 = 0x80
RTC_ALRMAR_ST = 0x70
RTC_ALRMAR_ST_0 = 0x10
RTC_ALRMAR_ST_1 = 0x20
RTC_ALRMAR_ST_2 = 0x40
RTC_ALRMAR_SU = 0xF
RTC_ALRMAR_SU_0 = 0x1
RTC_ALRMAR_SU_1 = 0x2
RTC_ALRMAR_SU_2 = 0x4
RTC_ALRMAR_SU_3 = 0x8
RTC_WPR_KEY = 0xFF
RTC_SSR_SS = 0x3FFFF
RTC_SHIFTR_SUBFS = 0x7FFF
RTC_SHIFTR_ADD1S = 0x80000000
RTC_TSTR_PM = 0x400000
RTC_TSTR_HT = 0x300000
RTC_TSTR_HT_0 = 0x100000
RTC_TSTR_HT_1 = 0x200000
RTC_TSTR_HU = 0xF0000
RTC_TSTR_HU_0 = 0x10000
RTC_TSTR_HU_1 = 0x20000
RTC_TSTR_HU_2 = 0x40000
RTC_TSTR_HU_3 = 0x80000
RTC_TSTR_MNT = 0x7000
RTC_TSTR_MNT_0 = 0x1000
RTC_TSTR_MNT_1 = 0x2000
RTC_TSTR_MNT_2 = 0x4000
RTC_TSTR_MNU = 0xF00
RTC_TSTR_MNU_0 = 0x100
RTC_TSTR_MNU_1 = 0x200
RTC_TSTR_MNU_2 = 0x400
RTC_TSTR_MNU_3 = 0x800
RTC_TSTR_ST = 0x70
RTC_TSTR_ST_0 = 0x10
RTC_TSTR_ST_1 = 0x20
RTC_TSTR_ST_2 = 0x40
RTC_TSTR_SU = 0xF
RTC_TSTR_SU_0 = 0x1
RTC_TSTR_SU_1 = 0x2
RTC_TSTR_SU_2 = 0x4
RTC_TSTR_SU_3 = 0x8
RTC_TSDR_WDU = 0xE000
RTC_TSDR_WDU_0 = 0x2000
RTC_TSDR_WDU_1 = 0x4000
RTC_TSDR_WDU_2 = 0x8000
RTC_TSDR_MT = 0x1000
RTC_TSDR_MU = 0xF00
RTC_TSDR_MU_0 = 0x100
RTC_TSDR_MU_1 = 0x200
RTC_TSDR_MU_2 = 0x400
RTC_TSDR_MU_3 = 0x800
RTC_TSDR_DT = 0x30
RTC_TSDR_DT_0 = 0x10
RTC_TSDR_DT_1 = 0x20
RTC_TSDR_DU = 0xF
RTC_TSDR_DU_0 = 0x1
RTC_TSDR_DU_1 = 0x2
RTC_TSDR_DU_2 = 0x4
RTC_TSDR_DU_3 = 0x8
RTC_TSSSR_SS = 0x3FFFF
RTC_CALR_CALP = 0x8000
RTC_CALR_CALW8 = 0x4000
RTC_CALR_CALW16 = 0x2000
RTC_CALR_CALM = 0x1FF
RTC_CALR_CALM_0 = 0x1
RTC_CALR_CALM_1 = 0x2
RTC_CALR_CALM_2 = 0x4
RTC_CALR_CALM_3 = 0x8
RTC_CALR_CALM_4 = 0x10
RTC_CALR_CALM_5 = 0x20
RTC_CALR_CALM_6 = 0x40
RTC_CALR_CALM_7 = 0x80
RTC_CALR_CALM_8 = 0x100
RTC_CAL_CALP = 0x8000
RTC_CAL_CALW8 = 0x4000
RTC_CAL_CALW16 = 0x2000
RTC_CAL_CALM = 0x1FF
RTC_CAL_CALM_0 = 0x1
RTC_CAL_CALM_1 = 0x2
RTC_CAL_CALM_2 = 0x4
RTC_CAL_CALM_3 = 0x8
RTC_CAL_CALM_4 = 0x10
RTC_CAL_CALM_5 = 0x20
RTC_CAL_CALM_6 = 0x40
RTC_CAL_CALM_7 = 0x80
RTC_CAL_CALM_8 = 0x100
RTC_TAFCR_PC15MODE = 0x800000
RTC_TAFCR_PC15VALUE = 0x400000
RTC_TAFCR_PC14MODE = 0x200000
RTC_TAFCR_PC14VALUE = 0x100000
RTC_TAFCR_PC13MODE = 0x80000
RTC_TAFCR_PC13VALUE = 0x40000
RTC_TAFCR_TAMPPUDIS = 0x8000
RTC_TAFCR_TAMPPRCH = 0x6000
RTC_TAFCR_TAMPPRCH_0 = 0x2000
RTC_TAFCR_TAMPPRCH_1 = 0x4000
RTC_TAFCR_TAMPFLT = 0x1800
RTC_TAFCR_TAMPFLT_0 = 0x800
RTC_TAFCR_TAMPFLT_1 = 0x1000
RTC_TAFCR_TAMPFREQ = 0x700
RTC_TAFCR_TAMPFREQ_0 = 0x100
RTC_TAFCR_TAMPFREQ_1 = 0x200
RTC_TAFCR_TAMPFREQ_2 = 0x400
RTC_TAFCR_TAMPTS = 0x80
RTC_TAFCR_TAMP3EDGE = 0x40
RTC_TAFCR_TAMP3E = 0x20
RTC_TAFCR_TAMP2EDGE = 0x10
RTC_TAFCR_TAMP2E = 0x8
RTC_TAFCR_TAMPIE = 0x4
RTC_TAFCR_TAMP1TRG = 0x2
RTC_TAFCR_TAMP1E = 0x1
RTC_TAFCR_ALARMOUTTYPE = 0x40000
RTC_ALRMASSR_MASKSS = 0xF000000
RTC_ALRMASSR_MASKSS_0 = 0x1000000
RTC_ALRMASSR_MASKSS_1 = 0x2000000
RTC_ALRMASSR_MASKSS_2 = 0x4000000
RTC_ALRMASSR_MASKSS_3 = 0x8000000
RTC_ALRMASSR_SS = 0x7FFF
RTC_BKP0R = 0xFFFFFFFF
RTC_BKP1R = 0xFFFFFFFF
RTC_BKP2R = 0xFFFFFFFF
RTC_BKP3R = 0xFFFFFFFF
RTC_BKP4R = 0xFFFFFFFF
SPI_CR1_CPHA = 0x1
SPI_CR1_CPOL = 0x2
SPI_CR1_MSTR = 0x4
SPI_CR1_BR = 0x38
SPI_CR1_BR_0 = 0x8
SPI_CR1_BR_1 = 0x10
SPI_CR1_BR_2 = 0x20
SPI_CR1_SPE = 0x40
SPI_CR1_LSBFIRST = 0x80
SPI_CR1_SSI = 0x100
SPI_CR1_SSM = 0x200
SPI_CR1_RXONLY = 0x400
SPI_CR1_CRCL = 0x800
SPI_CR1_CRCNEXT = 0x1000
SPI_CR1_CRCEN = 0x2000
SPI_CR1_BIDIOE = 0x4000
SPI_CR1_BIDIMODE = 0x8000
SPI_CR2_RXDMAEN = 0x1
SPI_CR2_TXDMAEN = 0x2
SPI_CR2_SSOE = 0x4
SPI_CR2_NSSP = 0x8
SPI_CR2_FRF = 0x10
SPI_CR2_ERRIE = 0x20
SPI_CR2_RXNEIE = 0x40
SPI_CR2_TXEIE = 0x80
SPI_CR2_DS = 0xF00
SPI_CR2_DS_0 = 0x100
SPI_CR2_DS_1 = 0x200
SPI_CR2_DS_2 = 0x400
SPI_CR2_DS_3 = 0x800
SPI_CR2_FRXTH = 0x1000
SPI_CR2_LDMARX = 0x2000
SPI_CR2_LDMATX = 0x4000
SPI_SR_RXNE = 0x1
SPI_SR_TXE = 0x2
SPI_SR_CHSIDE = 0x4
SPI_SR_UDR = 0x8
SPI_SR_CRCERR = 0x10
SPI_SR_MODF = 0x20
SPI_SR_OVR = 0x40
SPI_SR_BSY = 0x80
SPI_SR_FRE = 0x100
SPI_SR_FRLVL = 0x600
SPI_SR_FRLVL_0 = 0x200
SPI_SR_FRLVL_1 = 0x400
SPI_SR_FTLVL = 0x1800
SPI_SR_FTLVL_0 = 0x800
SPI_SR_FTLVL_1 = 0x1000
SPI_DR_DR = 0xFFFF
SPI_CRCPR_CRCPOLY = 0xFFFF
SPI_RXCRCR_RXCRC = 0xFFFF
SPI_TXCRCR_TXCRC = 0xFFFF
SPI_I2SCFGR_CHLEN = 0x1
SPI_I2SCFGR_DATLEN = 0x6
SPI_I2SCFGR_DATLEN_0 = 0x2
SPI_I2SCFGR_DATLEN_1 = 0x4
SPI_I2SCFGR_CKPOL = 0x8
SPI_I2SCFGR_I2SSTD = 0x30
SPI_I2SCFGR_I2SSTD_0 = 0x10
SPI_I2SCFGR_I2SSTD_1 = 0x20
SPI_I2SCFGR_PCMSYNC = 0x80
SPI_I2SCFGR_I2SCFG = 0x300
SPI_I2SCFGR_I2SCFG_0 = 0x100
SPI_I2SCFGR_I2SCFG_1 = 0x200
SPI_I2SCFGR_I2SE = 0x400
SPI_I2SCFGR_I2SMOD = 0x800
SPI_I2SPR_I2SDIV = 0xFF
SPI_I2SPR_ODD = 0x100
SPI_I2SPR_MCKOE = 0x200
SYSCFG_CFGR1_MEM_MODE = 0x3
SYSCFG_CFGR1_MEM_MODE_0 = 0x1
SYSCFG_CFGR1_MEM_MODE_1 = 0x2
SYSCFG_CFGR1_IRDA_ENV_SEL = 0xC0
SYSCFG_CFGR1_IRDA_ENV_SEL_0 = 0x40
SYSCFG_CFGR1_IRDA_ENV_SEL_1 = 0x80
SYSCFG_CFGR1_PA11_PA12_RMP = 0x10
SYSCFG_CFGR1_ADC_DMA_RMP = 0x100
SYSCFG_CFGR1_USART1TX_DMA_RMP = 0x200
SYSCFG_CFGR1_USART1RX_DMA_RMP = 0x400
SYSCFG_CFGR1_TIM16_DMA_RMP = 0x800
SYSCFG_CFGR1_TIM17_DMA_RMP = 0x1000
SYSCFG_CFGR1_TIM16_DMA_RMP2 = 0x2000
SYSCFG_CFGR1_TIM17_DMA_RMP2 = 0x4000
SYSCFG_CFGR1_I2C_FMP_PB6 = 0x10000
SYSCFG_CFGR1_I2C_FMP_PB7 = 0x20000
SYSCFG_CFGR1_I2C_FMP_PB8 = 0x40000
SYSCFG_CFGR1_I2C_FMP_PB9 = 0x80000
SYSCFG_CFGR1_I2C_FMP_I2C1 = 0x100000
SYSCFG_CFGR1_I2C_FMP_I2C2 = 0x200000
SYSCFG_CFGR1_I2C_FMP_PA9 = 0x400000
SYSCFG_CFGR1_I2C_FMP_PA10 = 0x800000
SYSCFG_CFGR1_SPI2_DMA_RMP = 0x1000000
SYSCFG_CFGR1_USART2_DMA_RMP = 0x2000000
SYSCFG_CFGR1_USART3_DMA_RMP = 0x4000000
SYSCFG_CFGR1_I2C1_DMA_RMP = 0x8000000
SYSCFG_CFGR1_TIM1_DMA_RMP = 0x10000000
SYSCFG_CFGR1_TIM2_DMA_RMP = 0x20000000
SYSCFG_CFGR1_TIM3_DMA_RMP = 0x40000000
SYSCFG_EXTICR1_EXTI0 = 0xF
SYSCFG_EXTICR1_EXTI1 = 0xF0
SYSCFG_EXTICR1_EXTI2 = 0xF00
SYSCFG_EXTICR1_EXTI3 = 0xF000
SYSCFG_EXTICR1_EXTI0_PA = 0x0
SYSCFG_EXTICR1_EXTI0_PB = 0x1
SYSCFG_EXTICR1_EXTI0_PC = 0x2
SYSCFG_EXTICR1_EXTI0_PD = 0x3
SYSCFG_EXTICR1_EXTI0_PE = 0x4
SYSCFG_EXTICR1_EXTI0_PF = 0x5
SYSCFG_EXTICR1_EXTI1_PA = 0x0
SYSCFG_EXTICR1_EXTI1_PB = 0x10
SYSCFG_EXTICR1_EXTI1_PC = 0x20
SYSCFG_EXTICR1_EXTI1_PD = 0x30
SYSCFG_EXTICR1_EXTI1_PE = 0x40
SYSCFG_EXTICR1_EXTI1_PF = 0x50
SYSCFG_EXTICR1_EXTI2_PA = 0x0
SYSCFG_EXTICR1_EXTI2_PB = 0x100
SYSCFG_EXTICR1_EXTI2_PC = 0x200
SYSCFG_EXTICR1_EXTI2_PD = 0x300
SYSCFG_EXTICR1_EXTI2_PE = 0x400
SYSCFG_EXTICR1_EXTI2_PF = 0x500
SYSCFG_EXTICR1_EXTI3_PA = 0x0
SYSCFG_EXTICR1_EXTI3_PB = 0x1000
SYSCFG_EXTICR1_EXTI3_PC = 0x2000
SYSCFG_EXTICR1_EXTI3_PD = 0x3000
SYSCFG_EXTICR1_EXTI3_PE = 0x4000
SYSCFG_EXTICR1_EXTI3_PF = 0x5000
SYSCFG_EXTICR2_EXTI4 = 0xF
SYSCFG_EXTICR2_EXTI5 = 0xF0
SYSCFG_EXTICR2_EXTI6 = 0xF00
SYSCFG_EXTICR2_EXTI7 = 0xF000
SYSCFG_EXTICR2_EXTI4_PA = 0x0
SYSCFG_EXTICR2_EXTI4_PB = 0x1
SYSCFG_EXTICR2_EXTI4_PC = 0x2
SYSCFG_EXTICR2_EXTI4_PD = 0x3
SYSCFG_EXTICR2_EXTI4_PE = 0x4
SYSCFG_EXTICR2_EXTI4_PF = 0x5
SYSCFG_EXTICR2_EXTI5_PA = 0x0
SYSCFG_EXTICR2_EXTI5_PB = 0x10
SYSCFG_EXTICR2_EXTI5_PC = 0x20
SYSCFG_EXTICR2_EXTI5_PD = 0x30
SYSCFG_EXTICR2_EXTI5_PE = 0x40
SYSCFG_EXTICR2_EXTI5_PF = 0x50
SYSCFG_EXTICR2_EXTI6_PA = 0x0
SYSCFG_EXTICR2_EXTI6_PB = 0x100
SYSCFG_EXTICR2_EXTI6_PC = 0x200
SYSCFG_EXTICR2_EXTI6_PD = 0x300
SYSCFG_EXTICR2_EXTI6_PE = 0x400
SYSCFG_EXTICR2_EXTI6_PF = 0x500
SYSCFG_EXTICR2_EXTI7_PA = 0x0
SYSCFG_EXTICR2_EXTI7_PB = 0x1000
SYSCFG_EXTICR2_EXTI7_PC = 0x2000
SYSCFG_EXTICR2_EXTI7_PD = 0x3000
SYSCFG_EXTICR2_EXTI7_PE = 0x4000
SYSCFG_EXTICR2_EXTI7_PF = 0x5000
SYSCFG_EXTICR3_EXTI8 = 0xF
SYSCFG_EXTICR3_EXTI9 = 0xF0
SYSCFG_EXTICR3_EXTI10 = 0xF00
SYSCFG_EXTICR3_EXTI11 = 0xF000
SYSCFG_EXTICR3_EXTI8_PA = 0x0
SYSCFG_EXTICR3_EXTI8_PB = 0x1
SYSCFG_EXTICR3_EXTI8_PC = 0x2
SYSCFG_EXTICR3_EXTI8_PD = 0x3
SYSCFG_EXTICR3_EXTI8_PE = 0x4
SYSCFG_EXTICR3_EXTI9_PA = 0x0
SYSCFG_EXTICR3_EXTI9_PB = 0x10
SYSCFG_EXTICR3_EXTI9_PC = 0x20
SYSCFG_EXTICR3_EXTI9_PD = 0x30
SYSCFG_EXTICR3_EXTI9_PE = 0x40
SYSCFG_EXTICR3_EXTI9_PF = 0x50
SYSCFG_EXTICR3_EXTI10_PA = 0x0
SYSCFG_EXTICR3_EXTI10_PB = 0x100
SYSCFG_EXTICR3_EXTI10_PC = 0x200
SYSCFG_EXTICR3_EXTI10_PD = 0x300
SYSCFG_EXTICR3_EXTI10_PE = 0x400
SYSCFG_EXTICR3_EXTI10_PF = 0x500
SYSCFG_EXTICR3_EXTI11_PA = 0x0
SYSCFG_EXTICR3_EXTI11_PB = 0x1000
SYSCFG_EXTICR3_EXTI11_PC = 0x2000
SYSCFG_EXTICR3_EXTI11_PD = 0x3000
SYSCFG_EXTICR3_EXTI11_PE = 0x4000
SYSCFG_EXTICR4_EXTI12 = 0xF
SYSCFG_EXTICR4_EXTI13 = 0xF0
SYSCFG_EXTICR4_EXTI14 = 0xF00
SYSCFG_EXTICR4_EXTI15 = 0xF000
SYSCFG_EXTICR4_EXTI12_PA = 0x0
SYSCFG_EXTICR4_EXTI12_PB = 0x1
SYSCFG_EXTICR4_EXTI12_PC = 0x2
SYSCFG_EXTICR4_EXTI12_PD = 0x3
SYSCFG_EXTICR4_EXTI12_PE = 0x4
SYSCFG_EXTICR4_EXTI13_PA = 0x0
SYSCFG_EXTICR4_EXTI13_PB = 0x10
SYSCFG_EXTICR4_EXTI13_PC = 0x20
SYSCFG_EXTICR4_EXTI13_PD = 0x30
SYSCFG_EXTICR4_EXTI13_PE = 0x40
SYSCFG_EXTICR4_EXTI14_PA = 0x0
SYSCFG_EXTICR4_EXTI14_PB = 0x100
SYSCFG_EXTICR4_EXTI14_PC = 0x200
SYSCFG_EXTICR4_EXTI14_PD = 0x300
SYSCFG_EXTICR4_EXTI14_PE = 0x400
SYSCFG_EXTICR4_EXTI15_PA = 0x0
SYSCFG_EXTICR4_EXTI15_PB = 0x1000
SYSCFG_EXTICR4_EXTI15_PC = 0x2000
SYSCFG_EXTICR4_EXTI15_PD = 0x3000
SYSCFG_EXTICR4_EXTI15_PE = 0x4000
SYSCFG_CFGR2_LOCKUP_LOCK = 0x1
SYSCFG_CFGR2_SRAM_PARITY_LOCK = 0x2
SYSCFG_CFGR2_PVD_LOCK = 0x4
SYSCFG_CFGR2_SRAM_PEF = 0x100
SYSCFG_CFGR2_SRAM_PE = 0x100
SYSCFG_ITLINE0_SR_EWDG = 0x1
SYSCFG_ITLINE1_SR_PVDOUT = 0x1
SYSCFG_ITLINE1_SR_VDDIO2 = 0x2
SYSCFG_ITLINE2_SR_RTC_WAKEUP = 0x1
SYSCFG_ITLINE2_SR_RTC_TSTAMP = 0x2
SYSCFG_ITLINE2_SR_RTC_ALRA = 0x3
SYSCFG_ITLINE3_SR_FLASH_ITF = 0x1
SYSCFG_ITLINE4_SR_CRS = 0x1
SYSCFG_ITLINE4_SR_CLK_CTRL = 0x2
SYSCFG_ITLINE5_SR_EXTI0 = 0x1
SYSCFG_ITLINE5_SR_EXTI1 = 0x2
SYSCFG_ITLINE6_SR_EXTI2 = 0x1
SYSCFG_ITLINE6_SR_EXTI3 = 0x2
SYSCFG_ITLINE7_SR_EXTI4 = 0x1
SYSCFG_ITLINE7_SR_EXTI5 = 0x2
SYSCFG_ITLINE7_SR_EXTI6 = 0x4
SYSCFG_ITLINE7_SR_EXTI7 = 0x8
SYSCFG_ITLINE7_SR_EXTI8 = 0x10
SYSCFG_ITLINE7_SR_EXTI9 = 0x20
SYSCFG_ITLINE7_SR_EXTI10 = 0x40
SYSCFG_ITLINE7_SR_EXTI11 = 0x80
SYSCFG_ITLINE7_SR_EXTI12 = 0x100
SYSCFG_ITLINE7_SR_EXTI13 = 0x200
SYSCFG_ITLINE7_SR_EXTI14 = 0x400
SYSCFG_ITLINE7_SR_EXTI15 = 0x800
SYSCFG_ITLINE8_SR_TSC_EOA = 0x1
SYSCFG_ITLINE8_SR_TSC_MCE = 0x2
SYSCFG_ITLINE9_SR_DMA1_CH1 = 0x1
SYSCFG_ITLINE10_SR_DMA1_CH2 = 0x1
SYSCFG_ITLINE10_SR_DMA1_CH3 = 0x2
SYSCFG_ITLINE10_SR_DMA2_CH1 = 0x4
SYSCFG_ITLINE10_SR_DMA2_CH2 = 0x8
SYSCFG_ITLINE11_SR_DMA1_CH4 = 0x1
SYSCFG_ITLINE11_SR_DMA1_CH5 = 0x2
SYSCFG_ITLINE11_SR_DMA1_CH6 = 0x4
SYSCFG_ITLINE11_SR_DMA1_CH7 = 0x8
SYSCFG_ITLINE11_SR_DMA2_CH3 = 0x10
SYSCFG_ITLINE11_SR_DMA2_CH4 = 0x20
SYSCFG_ITLINE11_SR_DMA2_CH5 = 0x40
SYSCFG_ITLINE12_SR_ADC = 0x1
SYSCFG_ITLINE12_SR_COMP1 = 0x2
SYSCFG_ITLINE12_SR_COMP2 = 0x4
SYSCFG_ITLINE13_SR_TIM1_BRK = 0x1
SYSCFG_ITLINE13_SR_TIM1_UPD = 0x2
SYSCFG_ITLINE13_SR_TIM1_TRG = 0x4
SYSCFG_ITLINE13_SR_TIM1_CCU = 0x8
SYSCFG_ITLINE14_SR_TIM1_CC = 0x1
SYSCFG_ITLINE15_SR_TIM2_GLB = 0x1
SYSCFG_ITLINE16_SR_TIM3_GLB = 0x1
SYSCFG_ITLINE17_SR_DAC = 0x1
SYSCFG_ITLINE17_SR_TIM6_GLB = 0x2
SYSCFG_ITLINE18_SR_TIM7_GLB = 0x1
SYSCFG_ITLINE19_SR_TIM14_GLB = 0x1
SYSCFG_ITLINE20_SR_TIM15_GLB = 0x1
SYSCFG_ITLINE21_SR_TIM16_GLB = 0x1
SYSCFG_ITLINE22_SR_TIM17_GLB = 0x1
SYSCFG_ITLINE23_SR_I2C1_GLB = 0x1
SYSCFG_ITLINE24_SR_I2C2_GLB = 0x1
SYSCFG_ITLINE25_SR_SPI1 = 0x1
SYSCFG_ITLINE26_SR_SPI2 = 0x1
SYSCFG_ITLINE27_SR_USART1_GLB = 0x1
SYSCFG_ITLINE28_SR_USART2_GLB = 0x1
SYSCFG_ITLINE29_SR_USART3_GLB = 0x1
SYSCFG_ITLINE29_SR_USART4_GLB = 0x2
SYSCFG_ITLINE29_SR_USART5_GLB = 0x4
SYSCFG_ITLINE29_SR_USART6_GLB = 0x8
SYSCFG_ITLINE29_SR_USART7_GLB = 0x10
SYSCFG_ITLINE29_SR_USART8_GLB = 0x20
SYSCFG_ITLINE30_SR_CAN = 0x1
SYSCFG_ITLINE30_SR_CEC = 0x2
TIM_CR1_CEN = 0x1
TIM_CR1_UDIS = 0x2
TIM_CR1_URS = 0x4
TIM_CR1_OPM = 0x8
TIM_CR1_DIR = 0x10
TIM_CR1_CMS = 0x60
TIM_CR1_CMS_0 = 0x20
TIM_CR1_CMS_1 = 0x40
TIM_CR1_ARPE = 0x80
TIM_CR1_CKD = 0x300
TIM_CR1_CKD_0 = 0x100
TIM_CR1_CKD_1 = 0x200
TIM_CR2_CCPC = 0x1
TIM_CR2_CCUS = 0x4
TIM_CR2_CCDS = 0x8
TIM_CR2_MMS = 0x70
TIM_CR2_MMS_0 = 0x10
TIM_CR2_MMS_1 = 0x20
TIM_CR2_MMS_2 = 0x40
TIM_CR2_TI1S = 0x80
TIM_CR2_OIS1 = 0x100
TIM_CR2_OIS1N = 0x200
TIM_CR2_OIS2 = 0x400
TIM_CR2_OIS2N = 0x800
TIM_CR2_OIS3 = 0x1000
TIM_CR2_OIS3N = 0x2000
TIM_CR2_OIS4 = 0x4000
TIM_SMCR_SMS = 0x7
TIM_SMCR_SMS_0 = 0x1
TIM_SMCR_SMS_1 = 0x2
TIM_SMCR_SMS_2 = 0x4
TIM_SMCR_OCCS = 0x8
TIM_SMCR_TS = 0x70
TIM_SMCR_TS_0 = 0x10
TIM_SMCR_TS_1 = 0x20
TIM_SMCR_TS_2 = 0x40
TIM_SMCR_MSM = 0x80
TIM_SMCR_ETF = 0xF00
TIM_SMCR_ETF_0 = 0x100
TIM_SMCR_ETF_1 = 0x200
TIM_SMCR_ETF_2 = 0x400
TIM_SMCR_ETF_3 = 0x800
TIM_SMCR_ETPS = 0x3000
TIM_SMCR_ETPS_0 = 0x1000
TIM_SMCR_ETPS_1 = 0x2000
TIM_SMCR_ECE = 0x4000
TIM_SMCR_ETP = 0x8000
TIM_DIER_UIE = 0x1
TIM_DIER_CC1IE = 0x2
TIM_DIER_CC2IE = 0x4
TIM_DIER_CC3IE = 0x8
TIM_DIER_CC4IE = 0x10
TIM_DIER_COMIE = 0x20
TIM_DIER_TIE = 0x40
TIM_DIER_BIE = 0x80
TIM_DIER_UDE = 0x100
TIM_DIER_CC1DE = 0x200
TIM_DIER_CC2DE = 0x400
TIM_DIER_CC3DE = 0x800
TIM_DIER_CC4DE = 0x1000
TIM_DIER_COMDE = 0x2000
TIM_DIER_TDE = 0x4000
TIM_SR_UIF = 0x1
TIM_SR_CC1IF = 0x2
TIM_SR_CC2IF = 0x4
TIM_SR_CC3IF = 0x8
TIM_SR_CC4IF = 0x10
TIM_SR_COMIF = 0x20
TIM_SR_TIF = 0x40
TIM_SR_BIF = 0x80
TIM_SR_CC1OF = 0x200
TIM_SR_CC2OF = 0x400
TIM_SR_CC3OF = 0x800
TIM_SR_CC4OF = 0x1000
TIM_EGR_UG = 0x1
TIM_EGR_CC1G = 0x2
TIM_EGR_CC2G = 0x4
TIM_EGR_CC3G = 0x8
TIM_EGR_CC4G = 0x10
TIM_EGR_COMG = 0x20
TIM_EGR_TG = 0x40
TIM_EGR_BG = 0x80
TIM_CCMR1_CC1S = 0x3
TIM_CCMR1_CC1S_0 = 0x1
TIM_CCMR1_CC1S_1 = 0x2
TIM_CCMR1_OC1FE = 0x4
TIM_CCMR1_OC1PE = 0x8
TIM_CCMR1_OC1M = 0x70
TIM_CCMR1_OC1M_0 = 0x10
TIM_CCMR1_OC1M_1 = 0x20
TIM_CCMR1_OC1M_2 = 0x40
TIM_CCMR1_OC1CE = 0x80
TIM_CCMR1_CC2S = 0x300
TIM_CCMR1_CC2S_0 = 0x100
TIM_CCMR1_CC2S_1 = 0x200
TIM_CCMR1_OC2FE = 0x400
TIM_CCMR1_OC2PE = 0x800
TIM_CCMR1_OC2M = 0x7000
TIM_CCMR1_OC2M_0 = 0x1000
TIM_CCMR1_OC2M_1 = 0x2000
TIM_CCMR1_OC2M_2 = 0x4000
TIM_CCMR1_OC2CE = 0x8000
TIM_CCMR1_IC1PSC = 0xC
TIM_CCMR1_IC1PSC_0 = 0x4
TIM_CCMR1_IC1PSC_1 = 0x8
TIM_CCMR1_IC1F = 0xF0
TIM_CCMR1_IC1F_0 = 0x10
TIM_CCMR1_IC1F_1 = 0x20
TIM_CCMR1_IC1F_2 = 0x40
TIM_CCMR1_IC1F_3 = 0x80
TIM_CCMR1_IC2PSC = 0xC00
TIM_CCMR1_IC2PSC_0 = 0x400
TIM_CCMR1_IC2PSC_1 = 0x800
TIM_CCMR1_IC2F = 0xF000
TIM_CCMR1_IC2F_0 = 0x1000
TIM_CCMR1_IC2F_1 = 0x2000
TIM_CCMR1_IC2F_2 = 0x4000
TIM_CCMR1_IC2F_3 = 0x8000
TIM_CCMR2_CC3S = 0x3
TIM_CCMR2_CC3S_0 = 0x1
TIM_CCMR2_CC3S_1 = 0x2
TIM_CCMR2_OC3FE = 0x4
TIM_CCMR2_OC3PE = 0x8
TIM_CCMR2_OC3M = 0x70
TIM_CCMR2_OC3M_0 = 0x10
TIM_CCMR2_OC3M_1 = 0x20
TIM_CCMR2_OC3M_2 = 0x40
TIM_CCMR2_OC3CE = 0x80
TIM_CCMR2_CC4S = 0x300
TIM_CCMR2_CC4S_0 = 0x100
TIM_CCMR2_CC4S_1 = 0x200
TIM_CCMR2_OC4FE = 0x400
TIM_CCMR2_OC4PE = 0x800
TIM_CCMR2_OC4M = 0x7000
TIM_CCMR2_OC4M_0 = 0x1000
TIM_CCMR2_OC4M_1 = 0x2000
TIM_CCMR2_OC4M_2 = 0x4000
TIM_CCMR2_OC4CE = 0x8000
TIM_CCMR2_IC3PSC = 0xC
TIM_CCMR2_IC3PSC_0 = 0x4
TIM_CCMR2_IC3PSC_1 = 0x8
TIM_CCMR2_IC3F = 0xF0
TIM_CCMR2_IC3F_0 = 0x10
TIM_CCMR2_IC3F_1 = 0x20
TIM_CCMR2_IC3F_2 = 0x40
TIM_CCMR2_IC3F_3 = 0x80
TIM_CCMR2_IC4PSC = 0xC00
TIM_CCMR2_IC4PSC_0 = 0x400
TIM_CCMR2_IC4PSC_1 = 0x800
TIM_CCMR2_IC4F = 0xF000
TIM_CCMR2_IC4F_0 = 0x1000
TIM_CCMR2_IC4F_1 = 0x2000
TIM_CCMR2_IC4F_2 = 0x4000
TIM_CCMR2_IC4F_3 = 0x8000
TIM_CCER_CC1E = 0x1
TIM_CCER_CC1P = 0x2
TIM_CCER_CC1NE = 0x4
TIM_CCER_CC1NP = 0x8
TIM_CCER_CC2E = 0x10
TIM_CCER_CC2P = 0x20
TIM_CCER_CC2NE = 0x40
TIM_CCER_CC2NP = 0x80
TIM_CCER_CC3E = 0x100
TIM_CCER_CC3P = 0x200
TIM_CCER_CC3NE = 0x400
TIM_CCER_CC3NP = 0x800
TIM_CCER_CC4E = 0x1000
TIM_CCER_CC4P = 0x2000
TIM_CCER_CC4NP = 0x8000
TIM_CNT_CNT = 0xFFFF
TIM_PSC_PSC = 0xFFFF
TIM_ARR_ARR = 0xFFFF
TIM_RCR_REP = 0xFF
TIM_CCR1_CCR1 = 0xFFFF
TIM_CCR2_CCR2 = 0xFFFF
TIM_CCR3_CCR3 = 0xFFFF
TIM_CCR4_CCR4 = 0xFFFF
TIM_BDTR_DTG = 0xFF
TIM_BDTR_DTG_0 = 0x1
TIM_BDTR_DTG_1 = 0x2
TIM_BDTR_DTG_2 = 0x4
TIM_BDTR_DTG_3 = 0x8
TIM_BDTR_DTG_4 = 0x10
TIM_BDTR_DTG_5 = 0x20
TIM_BDTR_DTG_6 = 0x40
TIM_BDTR_DTG_7 = 0x80
TIM_BDTR_LOCK = 0x300
TIM_BDTR_LOCK_0 = 0x100
TIM_BDTR_LOCK_1 = 0x200
TIM_BDTR_OSSI = 0x400
TIM_BDTR_OSSR = 0x800
TIM_BDTR_BKE = 0x1000
TIM_BDTR_BKP = 0x2000
TIM_BDTR_AOE = 0x4000
TIM_BDTR_MOE = 0x8000
TIM_DCR_DBA = 0x1F
TIM_DCR_DBA_0 = 0x1
TIM_DCR_DBA_1 = 0x2
TIM_DCR_DBA_2 = 0x4
TIM_DCR_DBA_3 = 0x8
TIM_DCR_DBA_4 = 0x10
TIM_DCR_DBL = 0x1F00
TIM_DCR_DBL_0 = 0x100
TIM_DCR_DBL_1 = 0x200
TIM_DCR_DBL_2 = 0x400
TIM_DCR_DBL_3 = 0x800
TIM_DCR_DBL_4 = 0x1000
TIM_DMAR_DMAB = 0xFFFF
TIM14_OR_TI1_RMP = 0x3
TIM14_OR_TI1_RMP_0 = 0x1
TIM14_OR_TI1_RMP_1 = 0x2
USART_CR1_UE = 0x1
USART_CR1_UESM = 0x2
USART_CR1_RE = 0x4
USART_CR1_TE = 0x8
USART_CR1_IDLEIE = 0x10
USART_CR1_RXNEIE = 0x20
USART_CR1_TCIE = 0x40
USART_CR1_TXEIE = 0x80
USART_CR1_PEIE = 0x100
USART_CR1_PS = 0x200
USART_CR1_PCE = 0x400
USART_CR1_WAKE = 0x800
USART_CR1_M = 0x1000
USART_CR1_MME = 0x2000
USART_CR1_CMIE = 0x4000
USART_CR1_OVER8 = 0x8000
USART_CR1_DEDT = 0x1F0000
USART_CR1_DEDT_0 = 0x10000
USART_CR1_DEDT_1 = 0x20000
USART_CR1_DEDT_2 = 0x40000
USART_CR1_DEDT_3 = 0x80000
USART_CR1_DEDT_4 = 0x100000
USART_CR1_DEAT = 0x3E00000
USART_CR1_DEAT_0 = 0x200000
USART_CR1_DEAT_1 = 0x400000
USART_CR1_DEAT_2 = 0x800000
USART_CR1_DEAT_3 = 0x1000000
USART_CR1_DEAT_4 = 0x2000000
USART_CR1_RTOIE = 0x4000000
USART_CR1_EOBIE = 0x8000000
USART_CR2_ADDM7 = 0x10
USART_CR2_LBDL = 0x20
USART_CR2_LBDIE = 0x40
USART_CR2_LBCL = 0x100
USART_CR2_CPHA = 0x200
USART_CR2_CPOL = 0x400
USART_CR2_CLKEN = 0x800
USART_CR2_STOP = 0x3000
USART_CR2_STOP_0 = 0x1000
USART_CR2_STOP_1 = 0x2000
USART_CR2_LINEN = 0x4000
USART_CR2_SWAP = 0x8000
USART_CR2_RXINV = 0x10000
USART_CR2_TXINV = 0x20000
USART_CR2_DATAINV = 0x40000
USART_CR2_MSBFIRST = 0x80000
USART_CR2_ABREN = 0x100000
USART_CR2_ABRMODE = 0x600000
USART_CR2_ABRMODE_0 = 0x200000
USART_CR2_ABRMODE_1 = 0x400000
USART_CR2_RTOEN = 0x800000
USART_CR2_ADD = 0xFF000000
USART_CR3_EIE = 0x1
USART_CR3_IREN = 0x2
USART_CR3_IRLP = 0x4
USART_CR3_HDSEL = 0x8
USART_CR3_NACK = 0x10
USART_CR3_SCEN = 0x20
USART_CR3_DMAR = 0x40
USART_CR3_DMAT = 0x80
USART_CR3_RTSE = 0x100
USART_CR3_CTSE = 0x200
USART_CR3_CTSIE = 0x400
USART_CR3_ONEBIT = 0x800
USART_CR3_OVRDIS = 0x1000
USART_CR3_DDRE = 0x2000
USART_CR3_DEM = 0x4000
USART_CR3_DEP = 0x8000
USART_CR3_SCARCNT = 0xE0000
USART_CR3_SCARCNT_0 = 0x20000
USART_CR3_SCARCNT_1 = 0x40000
USART_CR3_SCARCNT_2 = 0x80000
USART_CR3_WUS = 0x300000
USART_CR3_WUS_0 = 0x100000
USART_CR3_WUS_1 = 0x200000
USART_CR3_WUFIE = 0x400000
USART_BRR_DIV_FRACTION = 0xF
USART_BRR_DIV_MANTISSA = 0xFFF0
USART_GTPR_PSC = 0xFF
USART_GTPR_GT = 0xFF00
USART_RTOR_RTO = 0xFFFFFF
USART_RTOR_BLEN = 0xFF000000
USART_RQR_ABRRQ = 0x1
USART_RQR_SBKRQ = 0x2
USART_RQR_MMRQ = 0x4
USART_RQR_RXFRQ = 0x8
USART_RQR_TXFRQ = 0x10
USART_ISR_PE = 0x1
USART_ISR_FE = 0x2
USART_ISR_NE = 0x4
USART_ISR_ORE = 0x8
USART_ISR_IDLE = 0x10
USART_ISR_RXNE = 0x20
USART_ISR_TC = 0x40
USART_ISR_TXE = 0x80
USART_ISR_LBD = 0x100
USART_ISR_CTSIF = 0x200
USART_ISR_CTS = 0x400
USART_ISR_RTOF = 0x800
USART_ISR_EOBF = 0x1000
USART_ISR_ABRE = 0x4000
USART_ISR_ABRF = 0x8000
USART_ISR_BUSY = 0x10000
USART_ISR_CMF = 0x20000
USART_ISR_SBKF = 0x40000
USART_ISR_RWU = 0x80000
USART_ISR_WUF = 0x100000
USART_ISR_TEACK = 0x200000
USART_ISR_REACK = 0x400000
USART_ICR_PECF = 0x1
USART_ICR_FECF = 0x2
USART_ICR_NCF = 0x4
USART_ICR_ORECF = 0x8
USART_ICR_IDLECF = 0x10
USART_ICR_TCCF = 0x40
USART_ICR_LBDCF = 0x100
USART_ICR_CTSCF = 0x200
USART_ICR_RTOCF = 0x800
USART_ICR_EOBCF = 0x1000
USART_ICR_CMCF = 0x20000
USART_ICR_WUCF = 0x100000
USART_RDR_RDR = 0x1FF
USART_TDR_TDR = 0x1FF
WWDG_CR_T = 0x7F
WWDG_CR_T0 = 0x1
WWDG_CR_T1 = 0x2
WWDG_CR_T2 = 0x4
WWDG_CR_T3 = 0x8
WWDG_CR_T4 = 0x10
WWDG_CR_T5 = 0x20
WWDG_CR_T6 = 0x40
WWDG_CR_WDGA = 0x80
WWDG_CFR_W = 0x7F
WWDG_CFR_W0 = 0x1
WWDG_CFR_W1 = 0x2
WWDG_CFR_W2 = 0x4
WWDG_CFR_W3 = 0x8
WWDG_CFR_W4 = 0x10
WWDG_CFR_W5 = 0x20
WWDG_CFR_W6 = 0x40
WWDG_CFR_WDGTB = 0x180
WWDG_CFR_WDGTB0 = 0x80
WWDG_CFR_WDGTB1 = 0x100
WWDG_CFR_EWI = 0x200
WWDG_SR_EWIF = 0x1
PVD_IRQn = 0x1
RCC_IRQn = 0x4
TS_IRQn = 0x8
DMA1_Channel1_IRQn = 0x9
DMA1_Channel2_3_IRQn = 0xA
DMA1_Channel4_5_IRQn = 0xB
DMA1_Channel4_5_6_7_IRQn = 0xB
ADC1_IRQn = 0xC
USART3_4_IRQn = 0x1D
CEC_IRQn = 0x1E
# Skip PVD_IRQHandler : no need parse
# Skip RCC_IRQHandler : no need parse
# Skip TS_IRQHandler : no need parse
# Skip DMA1_Channel1_IRQHandler : no need parse
# Skip DMA1_Channel2_3_IRQHandler : no need parse
# Skip DMA1_Channel4_5_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip ADC1_IRQHandler : no need parse
# Skip USART3_4_IRQHandler : no need parse
# Skip CEC_IRQHandler : no need parse
PVD_IRQn = 0x1
RCC_IRQn = 0x4
TS_IRQn = 0x8
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Channel4_5_IRQn = 0xB
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
ADC1_IRQn = 0xC
USART3_8_IRQn = 0x1D
CEC_IRQn = 0x1E
# Skip PVD_IRQHandler : no need parse
# Skip RCC_IRQHandler : no need parse
# Skip TS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Channel4_5_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip ADC1_IRQHandler : no need parse
# Skip USART3_8_IRQHandler : no need parse
# Skip CEC_IRQHandler : no need parse
PVD_VDDIO2_IRQn = 0x1
RCC_CRS_IRQn = 0x4
TSC_IRQn = 0x8
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Channel4_5_6_7_IRQn = 0xB
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
ADC1_IRQn = 0xC
CEC_CAN_IRQn = 0x1E
# Skip PVD_VDDIO2_IRQHandler : no need parse
# Skip RCC_CRS_IRQHandler : no need parse
# Skip TSC_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip ADC1_IRQHandler : no need parse
# Skip CEC_CAN_IRQHandler : no need parse
PVD_IRQn = 0x1
RCC_IRQn = 0x4
TS_IRQn = 0x8
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Channel4_5_IRQn = 0xB
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
CEC_IRQn = 0x1E
# Skip PVD_IRQHandler : no need parse
# Skip RCC_IRQHandler : no need parse
# Skip TS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Channel4_5_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
# Skip CEC_IRQHandler : no need parse
PVD_VDDIO2_IRQn = 0x1
RCC_CRS_IRQn = 0x4
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Channel4_5_6_7_IRQn = 0xB
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
# Skip PVD_VDDIO2_IRQHandler : no need parse
# Skip RCC_CRS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
RCC_CRS_IRQn = 0x4
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Channel4_5_6_7_IRQn = 0xB
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
# Skip RCC_CRS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
RCC_CRS_IRQn = 0x4
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
DMA1_Channel4_5_6_7_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
TIM6_DAC_IRQn = 0x11
USART3_8_IRQn = 0x1D
# Skip USART3_6_IRQn : no need parse
# Skip RCC_CRS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
# Skip TIM6_DAC_IRQHandler : no need parse
# Skip USART3_8_IRQHandler : no need parse
# Skip USART3_6_IRQHandler : no need parse
RCC_CRS_IRQn = 0x4
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
DMA1_Channel4_5_6_7_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
# Skip RCC_CRS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
RCC_CRS_IRQn = 0x4
DMA1_Ch1_IRQn = 0x9
DMA1_Ch2_3_DMA2_Ch1_2_IRQn = 0xA
DMA1_Ch4_7_DMA2_Ch3_5_IRQn = 0xB
DMA1_Channel4_5_6_7_IRQn = 0xB
ADC1_COMP_IRQn = 0xC
TIM6_DAC_IRQn = 0x11
USART3_8_IRQn = 0x1D
USART3_4_IRQn = 0x1D
# Skip RCC_CRS_IRQHandler : no need parse
# Skip DMA1_Ch1_IRQHandler : no need parse
# Skip DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler : no need parse
# Skip DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler : no need parse
# Skip DMA1_Channel4_5_6_7_IRQHandler : no need parse
# Skip ADC1_COMP_IRQHandler : no need parse
# Skip TIM6_DAC_IRQHandler : no need parse
# Skip USART3_8_IRQHandler : no need parse
# Skip USART3_4_IRQHandler : no need parse
# struct ADC_TypeDef

class ADC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ISR',	ctypes.c_uint32),
		('IER',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
		('CFGR1',	ctypes.c_uint32),
		('CFGR2',	ctypes.c_uint32),
		('SMPR',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('TR',	ctypes.c_uint32),
		('RESERVED3',	ctypes.c_uint32),
		('CHSELR',	ctypes.c_uint32),
		('RESERVED4',	ctypes.c_uint32 * 5),
		('DR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ADC_Common_TypeDef

class ADC_Common_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CCR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CAN_TxMailBox_TypeDef

class CAN_TxMailBox_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TIR',	ctypes.c_uint32),
		('TDTR',	ctypes.c_uint32),
		('TDLR',	ctypes.c_uint32),
		('TDHR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CAN_FIFOMailBox_TypeDef

class CAN_FIFOMailBox_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RIR',	ctypes.c_uint32),
		('RDTR',	ctypes.c_uint32),
		('RDLR',	ctypes.c_uint32),
		('RDHR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CAN_FilterRegister_TypeDef

class CAN_FilterRegister_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('FR1',	ctypes.c_uint32),
		('FR2',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CAN_TypeDef
# struct CAN_TypeDef : field is class : sTxMailBox
# struct CEC_TypeDef

class CEC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('CFGR',	ctypes.c_uint32),
		('TXDR',	ctypes.c_uint32),
		('RXDR',	ctypes.c_uint32),
		('ISR',	ctypes.c_uint32),
		('IER',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct COMP_TypeDef

class COMP_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CSR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CRC_TypeDef

class CRC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DR',	ctypes.c_uint32),
		('IDR',	ctypes.c_uint8),
		('RESERVED0',	ctypes.c_uint8),
		('RESERVED1',	ctypes.c_uint16),
		('CR',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('INIT',	ctypes.c_uint32),
		('POL',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CRS_TypeDef

class CRS_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('CFGR',	ctypes.c_uint32),
		('ISR',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DAC_TypeDef

class DAC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('SWTRIGR',	ctypes.c_uint32),
		('DHR12R1',	ctypes.c_uint32),
		('DHR12L1',	ctypes.c_uint32),
		('DHR8R1',	ctypes.c_uint32),
		('DHR12R2',	ctypes.c_uint32),
		('DHR12L2',	ctypes.c_uint32),
		('DHR8R2',	ctypes.c_uint32),
		('DHR12RD',	ctypes.c_uint32),
		('DHR12LD',	ctypes.c_uint32),
		('DHR8RD',	ctypes.c_uint32),
		('DOR1',	ctypes.c_uint32),
		('DOR2',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DBGMCU_TypeDef

class DBGMCU_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('IDCODE',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
		('APB1FZ',	ctypes.c_uint32),
		('APB2FZ',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DMA_Channel_TypeDef

class DMA_Channel_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CCR',	ctypes.c_uint32),
		('CNDTR',	ctypes.c_uint32),
		('CPAR',	ctypes.c_uint32),
		('CMAR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DMA_TypeDef

class DMA_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ISR',	ctypes.c_uint32),
		('IFCR',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32 * 40),
		('RMPCR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct EXTI_TypeDef

class EXTI_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('IMR',	ctypes.c_uint32),
		('EMR',	ctypes.c_uint32),
		('RTSR',	ctypes.c_uint32),
		('FTSR',	ctypes.c_uint32),
		('SWIER',	ctypes.c_uint32),
		('PR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FLASH_TypeDef

class FLASH_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ACR',	ctypes.c_uint32),
		('KEYR',	ctypes.c_uint32),
		('OPTKEYR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
		('AR',	ctypes.c_uint32),
		('RESERVED',	ctypes.c_uint32),
		('OBR',	ctypes.c_uint32),
		('WRPR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct OB_TypeDef

class OB_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RDP',	ctypes.c_uint16),
		('USER',	ctypes.c_uint16),
		('DATA0',	ctypes.c_uint16),
		('DATA1',	ctypes.c_uint16),
		('WRP0',	ctypes.c_uint16),
		('WRP1',	ctypes.c_uint16),
		('WRP2',	ctypes.c_uint16),
		('WRP3',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct GPIO_TypeDef

class GPIO_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('MODER',	ctypes.c_uint32),
		('OTYPER',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('OSPEEDR',	ctypes.c_uint32),
		('PUPDR',	ctypes.c_uint32),
		('IDR',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('ODR',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('BSRR',	ctypes.c_uint32),
		('LCKR',	ctypes.c_uint32),
		('AFR',	ctypes.c_uint32 * 2),
		('BRR',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SYSCFG_TypeDef

class SYSCFG_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CFGR1',	ctypes.c_uint32),
		('RESERVED',	ctypes.c_uint32),
		('EXTICR',	ctypes.c_uint32 * 4),
		('CFGR2',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32 * 25),
		('IT_LINE_SR',	ctypes.c_uint32 * 32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct I2C_TypeDef

class I2C_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR1',	ctypes.c_uint32),
		('CR2',	ctypes.c_uint32),
		('OAR1',	ctypes.c_uint32),
		('OAR2',	ctypes.c_uint32),
		('TIMINGR',	ctypes.c_uint32),
		('TIMEOUTR',	ctypes.c_uint32),
		('ISR',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
		('PECR',	ctypes.c_uint32),
		('RXDR',	ctypes.c_uint32),
		('TXDR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct IWDG_TypeDef

class IWDG_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('KR',	ctypes.c_uint32),
		('PR',	ctypes.c_uint32),
		('RLR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('WINR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct PWR_TypeDef

class PWR_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('CSR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct RCC_TypeDef

class RCC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('CFGR',	ctypes.c_uint32),
		('CIR',	ctypes.c_uint32),
		('APB2RSTR',	ctypes.c_uint32),
		('APB1RSTR',	ctypes.c_uint32),
		('AHBENR',	ctypes.c_uint32),
		('APB2ENR',	ctypes.c_uint32),
		('APB1ENR',	ctypes.c_uint32),
		('BDCR',	ctypes.c_uint32),
		('CSR',	ctypes.c_uint32),
		('AHBRSTR',	ctypes.c_uint32),
		('CFGR2',	ctypes.c_uint32),
		('CFGR3',	ctypes.c_uint32),
		('CR2',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct RTC_TypeDef

class RTC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('TR',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
		('ISR',	ctypes.c_uint32),
		('PRER',	ctypes.c_uint32),
		('WUTR',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32),
		('ALRMAR',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('WPR',	ctypes.c_uint32),
		('SSR',	ctypes.c_uint32),
		('SHIFTR',	ctypes.c_uint32),
		('TSTR',	ctypes.c_uint32),
		('TSDR',	ctypes.c_uint32),
		('TSSSR',	ctypes.c_uint32),
		('CALR',	ctypes.c_uint32),
		('TAFCR',	ctypes.c_uint32),
		('ALRMASSR',	ctypes.c_uint32),
		('RESERVED3',	ctypes.c_uint32),
		('RESERVED4',	ctypes.c_uint32),
		('BKP0R',	ctypes.c_uint32),
		('BKP1R',	ctypes.c_uint32),
		('BKP2R',	ctypes.c_uint32),
		('BKP3R',	ctypes.c_uint32),
		('BKP4R',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SPI_TypeDef

class SPI_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR1',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('CR2',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('SR',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('DR',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('CRCPR',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('RXCRCR',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('TXCRCR',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
		('I2SCFGR',	ctypes.c_uint16),
		('RESERVED7',	ctypes.c_uint16),
		('I2SPR',	ctypes.c_uint16),
		('RESERVED8',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct TIM_TypeDef

class TIM_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR1',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('CR2',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('SMCR',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('DIER',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('SR',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('EGR',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('CCMR1',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
		('CCMR2',	ctypes.c_uint16),
		('RESERVED7',	ctypes.c_uint16),
		('CCER',	ctypes.c_uint16),
		('RESERVED8',	ctypes.c_uint16),
		('CNT',	ctypes.c_uint32),
		('PSC',	ctypes.c_uint16),
		('RESERVED10',	ctypes.c_uint16),
		('ARR',	ctypes.c_uint32),
		('RCR',	ctypes.c_uint16),
		('RESERVED12',	ctypes.c_uint16),
		('CCR1',	ctypes.c_uint32),
		('CCR2',	ctypes.c_uint32),
		('CCR3',	ctypes.c_uint32),
		('CCR4',	ctypes.c_uint32),
		('BDTR',	ctypes.c_uint16),
		('RESERVED17',	ctypes.c_uint16),
		('DCR',	ctypes.c_uint16),
		('RESERVED18',	ctypes.c_uint16),
		('DMAR',	ctypes.c_uint16),
		('RESERVED19',	ctypes.c_uint16),
		('OR',	ctypes.c_uint16),
		('RESERVED20',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct TSC_TypeDef

class TSC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('IER',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
		('ISR',	ctypes.c_uint32),
		('IOHCR',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32),
		('IOASCR',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('IOSCR',	ctypes.c_uint32),
		('RESERVED3',	ctypes.c_uint32),
		('IOCCR',	ctypes.c_uint32),
		('RESERVED4',	ctypes.c_uint32),
		('IOGCSR',	ctypes.c_uint32),
		('IOGXCR',	ctypes.c_uint32 * 8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct USART_TypeDef

class USART_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR1',	ctypes.c_uint32),
		('CR2',	ctypes.c_uint32),
		('CR3',	ctypes.c_uint32),
		('BRR',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('GTPR',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('RTOR',	ctypes.c_uint32),
		('RQR',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('ISR',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
		('RDR',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('TDR',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct WWDG_TypeDef

class WWDG_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('CFR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file system_stm32f0xx.h : 

# empty define __SYSTEM_STM32F0XX_H
# Skip SystemCoreClock : no need parse
# ----------------------------------------

# file stm32f0xx_conf.h : 

# empty define __STM32F0XX_CONF_H
# ----------------------------------------


__all__ =  ['__version__', '__RUN', '__HALT', '__ERROR', '__WARNING', '__INFO', '__DEBUG',
    '__ALL_LOG', 'DEFAULT_OPENOCD_PORT', 'DEFAULT_GDB_PORT', 'EXTI_Mode_Interrupt',
    'EXTI_Mode_Event', 'EXTI_Trigger_Rising', 'EXTI_Trigger_Falling',
    'EXTI_Trigger_Rising_Falling', 'EXTI_Line0', 'EXTI_Line1', 'EXTI_Line2',
    'EXTI_Line3', 'EXTI_Line4', 'EXTI_Line5', 'EXTI_Line6', 'EXTI_Line7', 'EXTI_Line8',
    'EXTI_Line9', 'EXTI_Line10', 'EXTI_Line11', 'EXTI_Line12', 'EXTI_Line13',
    'EXTI_Line14', 'EXTI_Line15', 'EXTI_Line16', 'EXTI_Line17', 'EXTI_Line18',
    'EXTI_Line19', 'EXTI_Line20', 'EXTI_Line21', 'EXTI_Line22', 'EXTI_Line23',
    'EXTI_Line25', 'EXTI_Line26', 'EXTI_Line27', 'EXTI_Line31', 'EXTI_InitTypeDef',
    'ADC_JitterOff_PCLKDiv2', 'ADC_JitterOff_PCLKDiv4', 'ADC_ClockMode_AsynClk',
    'ADC_ClockMode_SynClkDiv2', 'ADC_ClockMode_SynClkDiv4', 'ADC_Resolution_12b',
    'ADC_Resolution_10b', 'ADC_Resolution_8b', 'ADC_Resolution_6b',
    'ADC_ExternalTrigConvEdge_None', 'ADC_ExternalTrigConvEdge_Rising',
    'ADC_ExternalTrigConvEdge_Falling', 'ADC_ExternalTrigConvEdge_RisingFalling',
    'ADC_ExternalTrigConv_T1_TRGO', 'ADC_ExternalTrigConv_T1_CC4',
    'ADC_ExternalTrigConv_T2_TRGO', 'ADC_ExternalTrigConv_T3_TRGO',
    'ADC_ExternalTrigConv_T15_TRGO', 'ADC_DataAlign_Right', 'ADC_DataAlign_Left',
    'ADC_ScanDirection_Upward', 'ADC_ScanDirection_Backward', 'ADC_DMAMode_OneShot',
    'ADC_DMAMode_Circular', 'ADC_AnalogWatchdog_Channel_0',
    'ADC_AnalogWatchdog_Channel_1', 'ADC_AnalogWatchdog_Channel_2',
    'ADC_AnalogWatchdog_Channel_3', 'ADC_AnalogWatchdog_Channel_4',
    'ADC_AnalogWatchdog_Channel_5', 'ADC_AnalogWatchdog_Channel_6',
    'ADC_AnalogWatchdog_Channel_7', 'ADC_AnalogWatchdog_Channel_8',
    'ADC_AnalogWatchdog_Channel_9', 'ADC_AnalogWatchdog_Channel_10',
    'ADC_AnalogWatchdog_Channel_11', 'ADC_AnalogWatchdog_Channel_12',
    'ADC_AnalogWatchdog_Channel_13', 'ADC_AnalogWatchdog_Channel_14',
    'ADC_AnalogWatchdog_Channel_15', 'ADC_AnalogWatchdog_Channel_16',
    'ADC_AnalogWatchdog_Channel_17', 'ADC_AnalogWatchdog_Channel_18',
    'ADC_SampleTime_1_5Cycles', 'ADC_SampleTime_7_5Cycles', 'ADC_SampleTime_13_5Cycles',
    'ADC_SampleTime_28_5Cycles', 'ADC_SampleTime_41_5Cycles',
    'ADC_SampleTime_55_5Cycles', 'ADC_SampleTime_71_5Cycles',
    'ADC_SampleTime_239_5Cycles', 'ADC_Channel_0', 'ADC_Channel_1', 'ADC_Channel_2',
    'ADC_Channel_3', 'ADC_Channel_4', 'ADC_Channel_5', 'ADC_Channel_6', 'ADC_Channel_7',
    'ADC_Channel_8', 'ADC_Channel_9', 'ADC_Channel_10', 'ADC_Channel_11',
    'ADC_Channel_12', 'ADC_Channel_13', 'ADC_Channel_14', 'ADC_Channel_15',
    'ADC_Channel_16', 'ADC_Channel_17', 'ADC_Channel_18', 'ADC_Channel_TempSensor',
    'ADC_Channel_Vrefint', 'ADC_Channel_Vbat', 'ADC_IT_ADRDY', 'ADC_IT_EOSMP',
    'ADC_IT_EOC', 'ADC_IT_EOSEQ', 'ADC_IT_OVR', 'ADC_IT_AWD', 'ADC_FLAG_ADRDY',
    'ADC_FLAG_EOSMP', 'ADC_FLAG_EOC', 'ADC_FLAG_EOSEQ', 'ADC_FLAG_OVR', 'ADC_FLAG_AWD',
    'ADC_FLAG_ADEN', 'ADC_FLAG_ADDIS', 'ADC_FLAG_ADSTART', 'ADC_FLAG_ADSTP',
    'ADC_FLAG_ADCAL', 'ADC_InitTypeDef', 'SPI_Direction_2Lines_FullDuplex',
    'SPI_Direction_2Lines_RxOnly', 'SPI_Direction_1Line_Rx', 'SPI_Direction_1Line_Tx',
    'SPI_Mode_Master', 'SPI_Mode_Slave', 'SPI_DataSize_4b', 'SPI_DataSize_5b',
    'SPI_DataSize_6b', 'SPI_DataSize_7b', 'SPI_DataSize_8b', 'SPI_DataSize_9b',
    'SPI_DataSize_10b', 'SPI_DataSize_11b', 'SPI_DataSize_12b', 'SPI_DataSize_13b',
    'SPI_DataSize_14b', 'SPI_DataSize_15b', 'SPI_DataSize_16b', 'SPI_CRCLength_8b',
    'SPI_CRCLength_16b', 'SPI_CPOL_Low', 'SPI_CPOL_High', 'SPI_CPHA_1Edge',
    'SPI_CPHA_2Edge', 'SPI_NSS_Soft', 'SPI_NSS_Hard', 'SPI_BaudRatePrescaler_2',
    'SPI_BaudRatePrescaler_4', 'SPI_BaudRatePrescaler_8', 'SPI_BaudRatePrescaler_16',
    'SPI_BaudRatePrescaler_32', 'SPI_BaudRatePrescaler_64', 'SPI_BaudRatePrescaler_128',
    'SPI_BaudRatePrescaler_256', 'SPI_FirstBit_MSB', 'SPI_FirstBit_LSB',
    'I2S_Mode_SlaveTx', 'I2S_Mode_SlaveRx', 'I2S_Mode_MasterTx', 'I2S_Mode_MasterRx',
    'I2S_Standard_Phillips', 'I2S_Standard_MSB', 'I2S_Standard_LSB',
    'I2S_Standard_PCMShort', 'I2S_Standard_PCMLong', 'I2S_DataFormat_16b',
    'I2S_DataFormat_16bextended', 'I2S_DataFormat_24b', 'I2S_DataFormat_32b',
    'I2S_MCLKOutput_Enable', 'I2S_MCLKOutput_Disable', 'I2S_AudioFreq_192k',
    'I2S_AudioFreq_96k', 'I2S_AudioFreq_48k', 'I2S_AudioFreq_44k', 'I2S_AudioFreq_32k',
    'I2S_AudioFreq_22k', 'I2S_AudioFreq_16k', 'I2S_AudioFreq_11k', 'I2S_AudioFreq_8k',
    'I2S_AudioFreq_Default', 'I2S_CPOL_Low', 'I2S_CPOL_High', 'SPI_RxFIFOThreshold_HF',
    'SPI_RxFIFOThreshold_QF', 'SPI_I2S_DMAReq_Tx', 'SPI_I2S_DMAReq_Rx',
    'SPI_LastDMATransfer_TxEvenRxEven', 'SPI_LastDMATransfer_TxOddRxEven',
    'SPI_LastDMATransfer_TxEvenRxOdd', 'SPI_LastDMATransfer_TxOddRxOdd',
    'SPI_NSSInternalSoft_Set', 'SPI_NSSInternalSoft_Reset', 'SPI_CRC_Tx', 'SPI_CRC_Rx',
    'SPI_Direction_Rx', 'SPI_Direction_Tx', 'SPI_I2S_IT_TXE', 'SPI_I2S_IT_RXNE',
    'SPI_I2S_IT_ERR', 'I2S_IT_UDR', 'SPI_IT_MODF', 'SPI_I2S_IT_OVR', 'SPI_I2S_IT_FRE',
    'SPI_TransmissionFIFOStatus_Empty', 'SPI_TransmissionFIFOStatus_1QuarterFull',
    'SPI_TransmissionFIFOStatus_HalfFull', 'SPI_TransmissionFIFOStatus_Full',
    'SPI_ReceptionFIFOStatus_Empty', 'SPI_ReceptionFIFOStatus_1QuarterFull',
    'SPI_ReceptionFIFOStatus_HalfFull', 'SPI_ReceptionFIFOStatus_Full',
    'SPI_I2S_FLAG_RXNE', 'SPI_I2S_FLAG_TXE', 'I2S_FLAG_CHSIDE', 'I2S_FLAG_UDR',
    'SPI_FLAG_CRCERR', 'SPI_FLAG_MODF', 'SPI_I2S_FLAG_OVR', 'SPI_I2S_FLAG_BSY',
    'SPI_I2S_FLAG_FRE', 'SPI_InitTypeDef', 'I2S_InitTypeDef', 'IWDG_WriteAccess_Enable',
    'IWDG_WriteAccess_Disable', 'IWDG_Prescaler_4', 'IWDG_Prescaler_8',
    'IWDG_Prescaler_16', 'IWDG_Prescaler_32', 'IWDG_Prescaler_64', 'IWDG_Prescaler_128',
    'IWDG_Prescaler_256', 'IWDG_FLAG_PVU', 'IWDG_FLAG_RVU', 'IWDG_FLAG_WVU',
    'CRC_ReverseInputData_No', 'CRC_ReverseInputData_8bits',
    'CRC_ReverseInputData_16bits', 'CRC_ReverseInputData_32bits', 'CRC_PolSize_7',
    'CRC_PolSize_8', 'CRC_PolSize_16', 'CRC_PolSize_32', 'TIM_OCMode_Timing',
    'TIM_OCMode_Active', 'TIM_OCMode_Inactive', 'TIM_OCMode_Toggle', 'TIM_OCMode_PWM1',
    'TIM_OCMode_PWM2', 'TIM_OPMode_Single', 'TIM_OPMode_Repetitive', 'TIM_Channel_1',
    'TIM_Channel_2', 'TIM_Channel_3', 'TIM_Channel_4', 'TIM_CKD_DIV1', 'TIM_CKD_DIV2',
    'TIM_CKD_DIV4', 'TIM_CounterMode_Up', 'TIM_CounterMode_Down',
    'TIM_CounterMode_CenterAligned1', 'TIM_CounterMode_CenterAligned2',
    'TIM_CounterMode_CenterAligned3', 'TIM_OCPolarity_High', 'TIM_OCPolarity_Low',
    'TIM_OCNPolarity_High', 'TIM_OCNPolarity_Low', 'TIM_OutputState_Disable',
    'TIM_OutputState_Enable', 'TIM_OutputNState_Disable', 'TIM_OutputNState_Enable',
    'TIM_CCx_Enable', 'TIM_CCx_Disable', 'TIM_CCxN_Enable', 'TIM_CCxN_Disable',
    'TIM_Break_Enable', 'TIM_Break_Disable', 'TIM_BreakPolarity_Low',
    'TIM_BreakPolarity_High', 'TIM_AutomaticOutput_Enable',
    'TIM_AutomaticOutput_Disable', 'TIM_LOCKLevel_OFF', 'TIM_LOCKLevel_1',
    'TIM_LOCKLevel_2', 'TIM_LOCKLevel_3', 'TIM_OSSIState_Enable',
    'TIM_OSSIState_Disable', 'TIM_OSSRState_Enable', 'TIM_OSSRState_Disable',
    'TIM_OCIdleState_Set', 'TIM_OCIdleState_Reset', 'TIM_OCNIdleState_Set',
    'TIM_OCNIdleState_Reset', 'TIM_ICPolarity_Rising', 'TIM_ICPolarity_Falling',
    'TIM_ICPolarity_BothEdge', 'TIM_ICSelection_DirectTI', 'TIM_ICSelection_IndirectTI',
    'TIM_ICSelection_TRC', 'TIM_ICPSC_DIV1', 'TIM_ICPSC_DIV2', 'TIM_ICPSC_DIV4',
    'TIM_ICPSC_DIV8', 'TIM_IT_Update', 'TIM_IT_CC1', 'TIM_IT_CC2', 'TIM_IT_CC3',
    'TIM_IT_CC4', 'TIM_IT_COM', 'TIM_IT_Trigger', 'TIM_IT_Break', 'TIM_DMABase_CR1',
    'TIM_DMABase_CR2', 'TIM_DMABase_SMCR', 'TIM_DMABase_DIER', 'TIM_DMABase_SR',
    'TIM_DMABase_EGR', 'TIM_DMABase_CCMR1', 'TIM_DMABase_CCMR2', 'TIM_DMABase_CCER',
    'TIM_DMABase_CNT', 'TIM_DMABase_PSC', 'TIM_DMABase_ARR', 'TIM_DMABase_RCR',
    'TIM_DMABase_CCR1', 'TIM_DMABase_CCR2', 'TIM_DMABase_CCR3', 'TIM_DMABase_CCR4',
    'TIM_DMABase_BDTR', 'TIM_DMABase_DCR', 'TIM_DMABase_OR',
    'TIM_DMABurstLength_1Transfer', 'TIM_DMABurstLength_2Transfers',
    'TIM_DMABurstLength_3Transfers', 'TIM_DMABurstLength_4Transfers',
    'TIM_DMABurstLength_5Transfers', 'TIM_DMABurstLength_6Transfers',
    'TIM_DMABurstLength_7Transfers', 'TIM_DMABurstLength_8Transfers',
    'TIM_DMABurstLength_9Transfers', 'TIM_DMABurstLength_10Transfers',
    'TIM_DMABurstLength_11Transfers', 'TIM_DMABurstLength_12Transfers',
    'TIM_DMABurstLength_13Transfers', 'TIM_DMABurstLength_14Transfers',
    'TIM_DMABurstLength_15Transfers', 'TIM_DMABurstLength_16Transfers',
    'TIM_DMABurstLength_17Transfers', 'TIM_DMABurstLength_18Transfers',
    'TIM_DMA_Update', 'TIM_DMA_CC1', 'TIM_DMA_CC2', 'TIM_DMA_CC3', 'TIM_DMA_CC4',
    'TIM_DMA_COM', 'TIM_DMA_Trigger', 'TIM_ExtTRGPSC_OFF', 'TIM_ExtTRGPSC_DIV2',
    'TIM_ExtTRGPSC_DIV4', 'TIM_ExtTRGPSC_DIV8', 'TIM_TS_ITR0', 'TIM_TS_ITR1',
    'TIM_TS_ITR2', 'TIM_TS_ITR3', 'TIM_TS_TI1F_ED', 'TIM_TS_TI1FP1', 'TIM_TS_TI2FP2',
    'TIM_TS_ETRF', 'TIM_TIxExternalCLK1Source_TI1', 'TIM_TIxExternalCLK1Source_TI2',
    'TIM_TIxExternalCLK1Source_TI1ED', 'TIM_ExtTRGPolarity_Inverted',
    'TIM_ExtTRGPolarity_NonInverted', 'TIM_PSCReloadMode_Update',
    'TIM_PSCReloadMode_Immediate', 'TIM_ForcedAction_Active',
    'TIM_ForcedAction_InActive', 'TIM_EncoderMode_TI1', 'TIM_EncoderMode_TI2',
    'TIM_EncoderMode_TI12', 'TIM_EventSource_Update', 'TIM_EventSource_CC1',
    'TIM_EventSource_CC2', 'TIM_EventSource_CC3', 'TIM_EventSource_CC4',
    'TIM_EventSource_COM', 'TIM_EventSource_Trigger', 'TIM_EventSource_Break',
    'TIM_UpdateSource_Global', 'TIM_UpdateSource_Regular', 'TIM_OCPreload_Enable',
    'TIM_OCPreload_Disable', 'TIM_OCFast_Enable', 'TIM_OCFast_Disable',
    'TIM_OCClear_Enable', 'TIM_OCClear_Disable', 'TIM_TRGOSource_Reset',
    'TIM_TRGOSource_Enable', 'TIM_TRGOSource_Update', 'TIM_TRGOSource_OC1',
    'TIM_TRGOSource_OC1Ref', 'TIM_TRGOSource_OC2Ref', 'TIM_TRGOSource_OC3Ref',
    'TIM_TRGOSource_OC4Ref', 'TIM_SlaveMode_Reset', 'TIM_SlaveMode_Gated',
    'TIM_SlaveMode_Trigger', 'TIM_SlaveMode_External1', 'TIM_MasterSlaveMode_Enable',
    'TIM_MasterSlaveMode_Disable', 'TIM_FLAG_Update', 'TIM_FLAG_CC1', 'TIM_FLAG_CC2',
    'TIM_FLAG_CC3', 'TIM_FLAG_CC4', 'TIM_FLAG_COM', 'TIM_FLAG_Trigger',
    'TIM_FLAG_Break', 'TIM_FLAG_CC1OF', 'TIM_FLAG_CC2OF', 'TIM_FLAG_CC3OF',
    'TIM_FLAG_CC4OF', 'TIM_OCReferenceClear_ETRF', 'TIM_OCReferenceClear_OCREFCLR',
    'TIM14_GPIO', 'TIM14_RTC_CLK', 'TIM14_HSEDiv32', 'TIM14_MCO',
    'TIM_DMABurstLength_1Byte', 'TIM_DMABurstLength_2Bytes',
    'TIM_DMABurstLength_3Bytes', 'TIM_DMABurstLength_4Bytes',
    'TIM_DMABurstLength_5Bytes', 'TIM_DMABurstLength_6Bytes',
    'TIM_DMABurstLength_7Bytes', 'TIM_DMABurstLength_8Bytes',
    'TIM_DMABurstLength_9Bytes', 'TIM_DMABurstLength_10Bytes',
    'TIM_DMABurstLength_11Bytes', 'TIM_DMABurstLength_12Bytes',
    'TIM_DMABurstLength_13Bytes', 'TIM_DMABurstLength_14Bytes',
    'TIM_DMABurstLength_15Bytes', 'TIM_DMABurstLength_16Bytes',
    'TIM_DMABurstLength_17Bytes', 'TIM_DMABurstLength_18Bytes',
    'TIM_TimeBaseInitTypeDef', 'TIM_OCInitTypeDef', 'TIM_ICInitTypeDef',
    'TIM_BDTRInitTypeDef', 'CRS_IT_SYNCOK', 'CRS_IT_SYNCWARN', 'CRS_IT_ERR',
    'CRS_IT_ESYNC', 'CRS_IT_TRIMOVF', 'CRS_IT_SYNCERR', 'CRS_IT_SYNCMISS',
    'CRS_FLAG_SYNCOK', 'CRS_FLAG_SYNCWARN', 'CRS_FLAG_ERR', 'CRS_FLAG_ESYNC',
    'CRS_FLAG_TRIMOVF', 'CRS_FLAG_SYNCERR', 'CRS_FLAG_SYNCMISS', 'CRS_SYNCSource_GPIO',
    'CRS_SYNCSource_LSE', 'CRS_SYNCSource_USB', 'CRS_SYNC_Div1', 'CRS_SYNC_Div2',
    'CRS_SYNC_Div4', 'CRS_SYNC_Div8', 'CRS_SYNC_Div16', 'CRS_SYNC_Div32',
    'CRS_SYNC_Div64', 'CRS_SYNC_Div128', 'CRS_SYNCPolarity_Rising',
    'CRS_SYNCPolarity_Falling', 'GPIO_Mode_IN', 'GPIO_Mode_OUT', 'GPIO_Mode_AF',
    'GPIO_Mode_AN', 'GPIO_OType_PP', 'GPIO_OType_OD', 'GPIO_Speed_Level_1',
    'GPIO_Speed_Level_2', 'GPIO_Speed_Level_3', 'GPIO_PuPd_NOPULL', 'GPIO_PuPd_UP',
    'GPIO_PuPd_DOWN', 'Bit_RESET', 'Bit_SET', 'GPIO_Pin_0', 'GPIO_Pin_1', 'GPIO_Pin_2',
    'GPIO_Pin_3', 'GPIO_Pin_4', 'GPIO_Pin_5', 'GPIO_Pin_6', 'GPIO_Pin_7', 'GPIO_Pin_8',
    'GPIO_Pin_9', 'GPIO_Pin_10', 'GPIO_Pin_11', 'GPIO_Pin_12', 'GPIO_Pin_13',
    'GPIO_Pin_14', 'GPIO_Pin_15', 'GPIO_Pin_All', 'GPIO_PinSource0', 'GPIO_PinSource1',
    'GPIO_PinSource2', 'GPIO_PinSource3', 'GPIO_PinSource4', 'GPIO_PinSource5',
    'GPIO_PinSource6', 'GPIO_PinSource7', 'GPIO_PinSource8', 'GPIO_PinSource9',
    'GPIO_PinSource10', 'GPIO_PinSource11', 'GPIO_PinSource12', 'GPIO_PinSource13',
    'GPIO_PinSource14', 'GPIO_PinSource15', 'GPIO_AF_0', 'GPIO_AF_1', 'GPIO_AF_2',
    'GPIO_AF_3', 'GPIO_AF_4', 'GPIO_AF_5', 'GPIO_AF_6', 'GPIO_AF_7', 'GPIO_Speed_2MHz',
    'GPIO_Speed_10MHz', 'GPIO_Speed_50MHz', 'GPIO_InitTypeDef',
    'I2C_AnalogFilter_Enable', 'I2C_AnalogFilter_Disable', 'I2C_Mode_I2C',
    'I2C_Mode_SMBusDevice', 'I2C_Mode_SMBusHost', 'I2C_Ack_Enable', 'I2C_Ack_Disable',
    'I2C_AcknowledgedAddress_7bit', 'I2C_AcknowledgedAddress_10bit',
    'I2C_Direction_Transmitter', 'I2C_Direction_Receiver', 'I2C_DMAReq_Tx',
    'I2C_DMAReq_Rx', 'I2C_OA2_NoMask', 'I2C_OA2_Mask01', 'I2C_OA2_Mask02',
    'I2C_OA2_Mask03', 'I2C_OA2_Mask04', 'I2C_OA2_Mask05', 'I2C_OA2_Mask06',
    'I2C_OA2_Mask07', 'I2C_Register_CR1', 'I2C_Register_CR2', 'I2C_Register_OAR1',
    'I2C_Register_OAR2', 'I2C_Register_TIMINGR', 'I2C_Register_TIMEOUTR',
    'I2C_Register_ISR', 'I2C_Register_ICR', 'I2C_Register_PECR', 'I2C_Register_RXDR',
    'I2C_Register_TXDR', 'I2C_IT_ERRI', 'I2C_IT_TCI', 'I2C_IT_STOPI', 'I2C_IT_NACKI',
    'I2C_IT_ADDRI', 'I2C_IT_RXI', 'I2C_IT_TXI', 'I2C_FLAG_TXE', 'I2C_FLAG_TXIS',
    'I2C_FLAG_RXNE', 'I2C_FLAG_ADDR', 'I2C_FLAG_NACKF', 'I2C_FLAG_STOPF', 'I2C_FLAG_TC',
    'I2C_FLAG_TCR', 'I2C_FLAG_BERR', 'I2C_FLAG_ARLO', 'I2C_FLAG_OVR', 'I2C_FLAG_PECERR',
    'I2C_FLAG_TIMEOUT', 'I2C_FLAG_ALERT', 'I2C_FLAG_BUSY', 'I2C_IT_TXIS', 'I2C_IT_RXNE',
    'I2C_IT_ADDR', 'I2C_IT_NACKF', 'I2C_IT_STOPF', 'I2C_IT_TC', 'I2C_IT_TCR',
    'I2C_IT_BERR', 'I2C_IT_ARLO', 'I2C_IT_OVR', 'I2C_IT_PECERR', 'I2C_IT_TIMEOUT',
    'I2C_IT_ALERT', 'I2C_Reload_Mode', 'I2C_AutoEnd_Mode', 'I2C_SoftEnd_Mode',
    'I2C_No_StartStop', 'I2C_Generate_Stop', 'I2C_Generate_Start_Read',
    'I2C_Generate_Start_Write', 'I2C_InitTypeDef', 'EXTI_PortSourceGPIOA',
    'EXTI_PortSourceGPIOB', 'EXTI_PortSourceGPIOC', 'EXTI_PortSourceGPIOD',
    'EXTI_PortSourceGPIOE', 'EXTI_PortSourceGPIOF', 'EXTI_PinSource0',
    'EXTI_PinSource1', 'EXTI_PinSource2', 'EXTI_PinSource3', 'EXTI_PinSource4',
    'EXTI_PinSource5', 'EXTI_PinSource6', 'EXTI_PinSource7', 'EXTI_PinSource8',
    'EXTI_PinSource9', 'EXTI_PinSource10', 'EXTI_PinSource11', 'EXTI_PinSource12',
    'EXTI_PinSource13', 'EXTI_PinSource14', 'EXTI_PinSource15',
    'SYSCFG_MemoryRemap_Flash', 'SYSCFG_MemoryRemap_SystemMemory',
    'SYSCFG_MemoryRemap_SRAM', 'SYSCFG_DMARemap_TIM3', 'SYSCFG_DMARemap_TIM2',
    'SYSCFG_DMARemap_TIM1', 'SYSCFG_DMARemap_I2C1', 'SYSCFG_DMARemap_USART3',
    'SYSCFG_DMARemap_USART2', 'SYSCFG_DMARemap_SPI2', 'SYSCFG_DMARemap_TIM17_2',
    'SYSCFG_DMARemap_TIM16_2', 'SYSCFG_DMARemap_TIM17', 'SYSCFG_DMARemap_TIM16',
    'SYSCFG_DMARemap_USART1Rx', 'SYSCFG_DMARemap_USART1Tx', 'SYSCFG_DMARemap_ADC1',
    'SYSCFG_I2CFastModePlus_PB6', 'SYSCFG_I2CFastModePlus_PB7',
    'SYSCFG_I2CFastModePlus_PB8', 'SYSCFG_I2CFastModePlus_PB9',
    'SYSCFG_I2CFastModePlus_I2C1', 'SYSCFG_I2CFastModePlus_I2C2',
    'SYSCFG_I2CFastModePlus_PA9', 'SYSCFG_I2CFastModePlus_PA10', 'SYSCFG_Break_PVD',
    'SYSCFG_Break_SRAMParity', 'SYSCFG_Break_Lockup', 'SYSCFG_FLAG_PE',
    'SYSCFG_ITLINE0', 'SYSCFG_ITLINE1', 'SYSCFG_ITLINE2', 'SYSCFG_ITLINE3',
    'SYSCFG_ITLINE4', 'SYSCFG_ITLINE5', 'SYSCFG_ITLINE6', 'SYSCFG_ITLINE7',
    'SYSCFG_ITLINE8', 'SYSCFG_ITLINE9', 'SYSCFG_ITLINE10', 'SYSCFG_ITLINE11',
    'SYSCFG_ITLINE12', 'SYSCFG_ITLINE13', 'SYSCFG_ITLINE14', 'SYSCFG_ITLINE15',
    'SYSCFG_ITLINE16', 'SYSCFG_ITLINE17', 'SYSCFG_ITLINE18', 'SYSCFG_ITLINE19',
    'SYSCFG_ITLINE20', 'SYSCFG_ITLINE21', 'SYSCFG_ITLINE22', 'SYSCFG_ITLINE23',
    'SYSCFG_ITLINE24', 'SYSCFG_ITLINE25', 'SYSCFG_ITLINE26', 'SYSCFG_ITLINE27',
    'SYSCFG_ITLINE28', 'SYSCFG_ITLINE29', 'SYSCFG_ITLINE30', 'SYSCFG_ITLINE31',
    'ITLINE_EWDG', 'ITLINE_PVDOUT', 'ITLINE_VDDIO2', 'ITLINE_RTC_WAKEUP',
    'ITLINE_RTC_TSTAMP', 'ITLINE_RTC_ALRA', 'ITLINE_FLASH_ITF', 'ITLINE_CRS',
    'ITLINE_CLK_CTRL', 'ITLINE_EXTI0', 'ITLINE_EXTI1', 'ITLINE_EXTI2', 'ITLINE_EXTI3',
    'ITLINE_EXTI4', 'ITLINE_EXTI5', 'ITLINE_EXTI6', 'ITLINE_EXTI7', 'ITLINE_EXTI8',
    'ITLINE_EXTI9', 'ITLINE_EXTI10', 'ITLINE_EXTI11', 'ITLINE_EXTI12', 'ITLINE_EXTI13',
    'ITLINE_EXTI14', 'ITLINE_EXTI15', 'ITLINE_TSC_EOA', 'ITLINE_TSC_MCE',
    'ITLINE_DMA1_CH1', 'ITLINE_DMA1_CH2', 'ITLINE_DMA1_CH3', 'ITLINE_DMA2_CH1',
    'ITLINE_DMA2_CH2', 'ITLINE_DMA1_CH4', 'ITLINE_DMA1_CH5', 'ITLINE_DMA1_CH6',
    'ITLINE_DMA1_CH7', 'ITLINE_DMA2_CH3', 'ITLINE_DMA2_CH4', 'ITLINE_DMA2_CH5',
    'ITLINE_ADC', 'ITLINE_COMP1', 'ITLINE_COMP2', 'ITLINE_TIM1_BRK', 'ITLINE_TIM1_UPD',
    'ITLINE_TIM1_TRG', 'ITLINE_TIM1_CCU', 'ITLINE_TIM1_CC', 'ITLINE_TIM2',
    'ITLINE_TIM3', 'ITLINE_DAC', 'ITLINE_TIM6', 'ITLINE_TIM7', 'ITLINE_TIM14',
    'ITLINE_TIM15', 'ITLINE_TIM16', 'ITLINE_TIM17', 'ITLINE_I2C1', 'ITLINE_I2C2',
    'ITLINE_SPI1', 'ITLINE_SPI2', 'ITLINE_USART1', 'ITLINE_USART2', 'ITLINE_USART3',
    'ITLINE_USART4', 'ITLINE_USART5', 'ITLINE_USART6', 'ITLINE_USART7', 'ITLINE_USART8',
    'ITLINE_CAN', 'ITLINE_CEC', 'SYSCFG_IRDA_ENV_SEL_TIM16',
    'SYSCFG_IRDA_ENV_SEL_USART1', 'SYSCFG_IRDA_ENV_SEL_USART4', 'RTC_HourFormat_24',
    'RTC_HourFormat_12', 'RTC_H12_AM', 'RTC_H12_PM', 'RTC_Month_January',
    'RTC_Month_February', 'RTC_Month_March', 'RTC_Month_April', 'RTC_Month_May',
    'RTC_Month_June', 'RTC_Month_July', 'RTC_Month_August', 'RTC_Month_September',
    'RTC_Month_October', 'RTC_Month_November', 'RTC_Month_December',
    'RTC_Weekday_Monday', 'RTC_Weekday_Tuesday', 'RTC_Weekday_Wednesday',
    'RTC_Weekday_Thursday', 'RTC_Weekday_Friday', 'RTC_Weekday_Saturday',
    'RTC_Weekday_Sunday', 'RTC_AlarmDateWeekDaySel_Date',
    'RTC_AlarmDateWeekDaySel_WeekDay', 'RTC_AlarmMask_None',
    'RTC_AlarmMask_DateWeekDay', 'RTC_AlarmMask_Hours', 'RTC_AlarmMask_Minutes',
    'RTC_AlarmMask_Seconds', 'RTC_AlarmMask_All', 'RTC_Alarm_A',
    'RTC_AlarmSubSecondMask_All', 'RTC_AlarmSubSecondMask_SS14_1',
    'RTC_AlarmSubSecondMask_SS14_2', 'RTC_AlarmSubSecondMask_SS14_3',
    'RTC_AlarmSubSecondMask_SS14_4', 'RTC_AlarmSubSecondMask_SS14_5',
    'RTC_AlarmSubSecondMask_SS14_6', 'RTC_AlarmSubSecondMask_SS14_7',
    'RTC_AlarmSubSecondMask_SS14_8', 'RTC_AlarmSubSecondMask_SS14_9',
    'RTC_AlarmSubSecondMask_SS14_10', 'RTC_AlarmSubSecondMask_SS14_11',
    'RTC_AlarmSubSecondMask_SS14_12', 'RTC_AlarmSubSecondMask_SS14_13',
    'RTC_AlarmSubSecondMask_SS14', 'RTC_AlarmSubSecondMask_None',
    'RTC_WakeUpClock_RTCCLK_Div16', 'RTC_WakeUpClock_RTCCLK_Div8',
    'RTC_WakeUpClock_RTCCLK_Div4', 'RTC_WakeUpClock_RTCCLK_Div2',
    'RTC_WakeUpClock_CK_SPRE_16bits', 'RTC_WakeUpClock_CK_SPRE_17bits',
    'RTC_TimeStampEdge_Rising', 'RTC_TimeStampEdge_Falling', 'RTC_Output_Disable',
    'RTC_Output_AlarmA', 'RTC_Output_WakeUp', 'RTC_OutputPolarity_High',
    'RTC_OutputPolarity_Low', 'RTC_CalibOutput_512Hz', 'RTC_CalibOutput_1Hz',
    'RTC_SmoothCalibPeriod_32sec', 'RTC_SmoothCalibPeriod_16sec',
    'RTC_SmoothCalibPeriod_8sec', 'RTC_SmoothCalibPlusPulses_Set',
    'RTC_SmoothCalibPlusPulses_Reset', 'RTC_DayLightSaving_SUB1H',
    'RTC_DayLightSaving_ADD1H', 'RTC_StoreOperation_Reset', 'RTC_StoreOperation_Set',
    'RTC_TamperTrigger_RisingEdge', 'RTC_TamperTrigger_FallingEdge',
    'RTC_TamperTrigger_LowLevel', 'RTC_TamperTrigger_HighLevel',
    'RTC_TamperFilter_Disable', 'RTC_TamperFilter_2Sample', 'RTC_TamperFilter_4Sample',
    'RTC_TamperFilter_8Sample', 'RTC_TamperSamplingFreq_RTCCLK_Div32768',
    'RTC_TamperSamplingFreq_RTCCLK_Div16384', 'RTC_TamperSamplingFreq_RTCCLK_Div8192',
    'RTC_TamperSamplingFreq_RTCCLK_Div4096', 'RTC_TamperSamplingFreq_RTCCLK_Div2048',
    'RTC_TamperSamplingFreq_RTCCLK_Div1024', 'RTC_TamperSamplingFreq_RTCCLK_Div512',
    'RTC_TamperSamplingFreq_RTCCLK_Div256', 'RTC_TamperPrechargeDuration_1RTCCLK',
    'RTC_TamperPrechargeDuration_2RTCCLK', 'RTC_TamperPrechargeDuration_4RTCCLK',
    'RTC_TamperPrechargeDuration_8RTCCLK', 'RTC_Tamper_1', 'RTC_Tamper_2',
    'RTC_Tamper_3', 'RTC_OutputType_OpenDrain', 'RTC_OutputType_PushPull',
    'RTC_ShiftAdd1S_Reset', 'RTC_ShiftAdd1S_Set', 'RTC_BKP_DR0', 'RTC_BKP_DR1',
    'RTC_BKP_DR2', 'RTC_BKP_DR3', 'RTC_BKP_DR4', 'RTC_Format_BIN', 'RTC_Format_BCD',
    'RTC_FLAG_RECALPF', 'RTC_FLAG_TAMP3F', 'RTC_FLAG_TAMP2F', 'RTC_FLAG_TAMP1F',
    'RTC_FLAG_TSOVF', 'RTC_FLAG_TSF', 'RTC_FLAG_WUTF', 'RTC_FLAG_ALRAF',
    'RTC_FLAG_INITF', 'RTC_FLAG_RSF', 'RTC_FLAG_INITS', 'RTC_FLAG_SHPF',
    'RTC_FLAG_WUTWF', 'RTC_FLAG_ALRAWF', 'RTC_IT_TS', 'RTC_IT_WUT', 'RTC_IT_ALRA',
    'RTC_IT_TAMP', 'RTC_IT_TAMP1', 'RTC_IT_TAMP2', 'RTC_IT_TAMP3', 'RTC_InitTypeDef',
    'RTC_TimeTypeDef', 'RTC_DateTypeDef', 'NVIC_LP_SEVONPEND', 'NVIC_LP_SLEEPDEEP',
    'NVIC_LP_SLEEPONEXIT', 'SysTick_CLKSource_HCLK_Div8', 'SysTick_CLKSource_HCLK',
    'NVIC_InitTypeDef', 'COMP_Selection_COMP1', 'COMP_Selection_COMP2',
    'COMP_InvertingInput_1_4VREFINT', 'COMP_InvertingInput_1_2VREFINT',
    'COMP_InvertingInput_3_4VREFINT', 'COMP_InvertingInput_VREFINT',
    'COMP_InvertingInput_DAC1', 'COMP_InvertingInput_DAC2', 'COMP_InvertingInput_IO',
    'COMP_Output_None', 'COMP_Output_TIM1BKIN', 'COMP_Output_TIM1IC1',
    'COMP_Output_TIM1OCREFCLR', 'COMP_Output_TIM2IC4', 'COMP_Output_TIM2OCREFCLR',
    'COMP_Output_TIM3IC1', 'COMP_Output_TIM3OCREFCLR', 'COMP_OutputPol_NonInverted',
    'COMP_OutputPol_Inverted', 'COMP_Hysteresis_No', 'COMP_Hysteresis_Low',
    'COMP_Hysteresis_Medium', 'COMP_Hysteresis_High', 'COMP_Mode_HighSpeed',
    'COMP_Mode_MediumSpeed', 'COMP_Mode_LowPower', 'COMP_Mode_UltraLowPower',
    'COMP_OutputLevel_High', 'COMP_OutputLevel_Low', 'COMP_InitTypeDef', 'RCC_HSE_OFF',
    'RCC_HSE_ON', 'RCC_HSE_Bypass', 'RCC_PLLSource_HSI_Div2', 'RCC_PLLSource_PREDIV1',
    'RCC_PLLSource_HSE', 'RCC_PLLSource_HSI48', 'RCC_PLLSource_HSI', 'RCC_PLLMul_2',
    'RCC_PLLMul_3', 'RCC_PLLMul_4', 'RCC_PLLMul_5', 'RCC_PLLMul_6', 'RCC_PLLMul_7',
    'RCC_PLLMul_8', 'RCC_PLLMul_9', 'RCC_PLLMul_10', 'RCC_PLLMul_11', 'RCC_PLLMul_12',
    'RCC_PLLMul_13', 'RCC_PLLMul_14', 'RCC_PLLMul_15', 'RCC_PLLMul_16',
    'RCC_PREDIV1_Div1', 'RCC_PREDIV1_Div2', 'RCC_PREDIV1_Div3', 'RCC_PREDIV1_Div4',
    'RCC_PREDIV1_Div5', 'RCC_PREDIV1_Div6', 'RCC_PREDIV1_Div7', 'RCC_PREDIV1_Div8',
    'RCC_PREDIV1_Div9', 'RCC_PREDIV1_Div10', 'RCC_PREDIV1_Div11', 'RCC_PREDIV1_Div12',
    'RCC_PREDIV1_Div13', 'RCC_PREDIV1_Div14', 'RCC_PREDIV1_Div15', 'RCC_PREDIV1_Div16',
    'RCC_SYSCLKSource_HSI', 'RCC_SYSCLKSource_HSE', 'RCC_SYSCLKSource_PLLCLK',
    'RCC_SYSCLKSource_HSI48', 'RCC_SYSCLK_Div1', 'RCC_SYSCLK_Div2', 'RCC_SYSCLK_Div4',
    'RCC_SYSCLK_Div8', 'RCC_SYSCLK_Div16', 'RCC_SYSCLK_Div64', 'RCC_SYSCLK_Div128',
    'RCC_SYSCLK_Div256', 'RCC_SYSCLK_Div512', 'RCC_HCLK_Div1', 'RCC_HCLK_Div2',
    'RCC_HCLK_Div4', 'RCC_HCLK_Div8', 'RCC_HCLK_Div16', 'RCC_ADCCLK_HSI14',
    'RCC_ADCCLK_PCLK_Div2', 'RCC_ADCCLK_PCLK_Div4', 'RCC_CECCLK_HSI_Div244',
    'RCC_CECCLK_LSE', 'RCC_I2C1CLK_HSI', 'RCC_I2C1CLK_SYSCLK', 'RCC_USBCLK_HSI48',
    'RCC_USBCLK_PLLCLK', 'RCC_USART1CLK_PCLK', 'RCC_USART1CLK_SYSCLK',
    'RCC_USART1CLK_LSE', 'RCC_USART1CLK_HSI', 'RCC_USART2CLK_PCLK',
    'RCC_USART2CLK_SYSCLK', 'RCC_USART2CLK_LSE', 'RCC_USART2CLK_HSI',
    'RCC_USART3CLK_PCLK', 'RCC_USART3CLK_SYSCLK', 'RCC_USART3CLK_LSE',
    'RCC_USART3CLK_HSI', 'RCC_IT_LSIRDY', 'RCC_IT_LSERDY', 'RCC_IT_HSIRDY',
    'RCC_IT_HSERDY', 'RCC_IT_PLLRDY', 'RCC_IT_HSI14RDY', 'RCC_IT_HSI48RDY',
    'RCC_IT_CSS', 'RCC_LSE_OFF', 'RCC_LSE_ON', 'RCC_LSE_Bypass', 'RCC_RTCCLKSource_LSE',
    'RCC_RTCCLKSource_LSI', 'RCC_RTCCLKSource_HSE_Div32', 'RCC_LSEDrive_Low',
    'RCC_LSEDrive_MediumLow', 'RCC_LSEDrive_MediumHigh', 'RCC_LSEDrive_High',
    'RCC_AHBPeriph_GPIOA', 'RCC_AHBPeriph_GPIOB', 'RCC_AHBPeriph_GPIOC',
    'RCC_AHBPeriph_GPIOD', 'RCC_AHBPeriph_GPIOE', 'RCC_AHBPeriph_GPIOF',
    'RCC_AHBPeriph_TS', 'RCC_AHBPeriph_CRC', 'RCC_AHBPeriph_FLITF',
    'RCC_AHBPeriph_SRAM', 'RCC_AHBPeriph_DMA1', 'RCC_AHBPeriph_DMA2',
    'RCC_APB2Periph_SYSCFG', 'RCC_APB2Periph_USART6', 'RCC_APB2Periph_USART7',
    'RCC_APB2Periph_USART8', 'RCC_APB2Periph_ADC1', 'RCC_APB2Periph_TIM1',
    'RCC_APB2Periph_SPI1', 'RCC_APB2Periph_USART1', 'RCC_APB2Periph_TIM15',
    'RCC_APB2Periph_TIM16', 'RCC_APB2Periph_TIM17', 'RCC_APB2Periph_DBGMCU',
    'RCC_APB1Periph_TIM2', 'RCC_APB1Periph_TIM3', 'RCC_APB1Periph_TIM6',
    'RCC_APB1Periph_TIM7', 'RCC_APB1Periph_TIM14', 'RCC_APB1Periph_WWDG',
    'RCC_APB1Periph_SPI2', 'RCC_APB1Periph_USART2', 'RCC_APB1Periph_USART3',
    'RCC_APB1Periph_USART4', 'RCC_APB1Periph_USART5', 'RCC_APB1Periph_I2C1',
    'RCC_APB1Periph_I2C2', 'RCC_APB1Periph_USB', 'RCC_APB1Periph_CAN',
    'RCC_APB1Periph_CRS', 'RCC_APB1Periph_PWR', 'RCC_APB1Periph_DAC',
    'RCC_APB1Periph_CEC', 'RCC_MCOSource_NoClock', 'RCC_MCOSource_HSI14',
    'RCC_MCOSource_LSI', 'RCC_MCOSource_LSE', 'RCC_MCOSource_SYSCLK',
    'RCC_MCOSource_HSI', 'RCC_MCOSource_HSE', 'RCC_MCOSource_PLLCLK_Div2',
    'RCC_MCOSource_HSI48', 'RCC_MCOSource_PLLCLK', 'RCC_MCOPrescaler_1',
    'RCC_MCOPrescaler_2', 'RCC_MCOPrescaler_4', 'RCC_MCOPrescaler_8',
    'RCC_MCOPrescaler_16', 'RCC_MCOPrescaler_32', 'RCC_MCOPrescaler_64',
    'RCC_MCOPrescaler_128', 'RCC_FLAG_HSIRDY', 'RCC_FLAG_HSERDY', 'RCC_FLAG_PLLRDY',
    'RCC_FLAG_LSERDY', 'RCC_FLAG_LSIRDY', 'RCC_FLAG_V18PWRRSTF', 'RCC_FLAG_OBLRST',
    'RCC_FLAG_PINRST', 'RCC_FLAG_PORRST', 'RCC_FLAG_SFTRST', 'RCC_FLAG_IWDGRST',
    'RCC_FLAG_WWDGRST', 'RCC_FLAG_LPWRRST', 'RCC_FLAG_HSI14RDY', 'RCC_FLAG_HSI48RDY',
    'RCC_ClocksTypeDef', 'FLASH_BUSY', 'FLASH_ERROR_WRP', 'FLASH_ERROR_PROGRAM',
    'FLASH_COMPLETE', 'FLASH_TIMEOUT', 'FLASH_Latency_0', 'FLASH_Latency_1',
    'FLASH_IT_EOP', 'FLASH_IT_ERR', 'OB_WRP_AllPages', 'OB_WRP_Pages0to1',
    'OB_WRP_Pages2to3', 'OB_WRP_Pages4to5', 'OB_WRP_Pages6to7', 'OB_WRP_Pages8to9',
    'OB_WRP_Pages10to11', 'OB_WRP_Pages12to13', 'OB_WRP_Pages14to15',
    'OB_WRP_Pages16to17', 'OB_WRP_Pages18to19', 'OB_WRP_Pages20to21',
    'OB_WRP_Pages22to23', 'OB_WRP_Pages24to25', 'OB_WRP_Pages26to27',
    'OB_WRP_Pages28to29', 'OB_WRP_Pages30to31', 'OB_WRP_Pages32to33',
    'OB_WRP_Pages34to35', 'OB_WRP_Pages36to37', 'OB_WRP_Pages38to39',
    'OB_WRP_Pages40to41', 'OB_WRP_Pages42to43', 'OB_WRP_Pages44to45',
    'OB_WRP_Pages46to47', 'OB_WRP_Pages48to49', 'OB_WRP_Pages50to51',
    'OB_WRP_Pages52to53', 'OB_WRP_Pages54to55', 'OB_WRP_Pages56to57',
    'OB_WRP_Pages58to59', 'OB_WRP_Pages60to61', 'OB_WRP_Pages62to127',
    'OB_WRP_AllPages', 'OB_RDP_Level_0', 'OB_RDP_Level_1', 'OB_IWDG_SW', 'OB_IWDG_HW',
    'OB_STOP_NoRST', 'OB_STOP_RST', 'OB_STDBY_NoRST', 'OB_STDBY_RST', 'OB_BOOT1_RESET',
    'OB_BOOT1_SET', 'OB_BOOT0_RESET', 'OB_BOOT0_SET', 'OB_BOOT0_SW', 'OB_BOOT0_HW',
    'OB_VDDA_ANALOG_ON', 'OB_VDDA_ANALOG_OFF', 'OB_SRAM_PARITY_SET',
    'OB_SRAM_PARITY_RESET', 'FLASH_FLAG_BSY', 'FLASH_FLAG_PGERR', 'FLASH_FLAG_WRPERR',
    'FLASH_FLAG_EOP', 'FLASH_ER_PRG_TIMEOUT', 'FLASH_WRProt_AllPages',
    'DMA_DIR_PeripheralSRC', 'DMA_DIR_PeripheralDST', 'DMA_PeripheralInc_Disable',
    'DMA_PeripheralInc_Enable', 'DMA_MemoryInc_Disable', 'DMA_MemoryInc_Enable',
    'DMA_PeripheralDataSize_Byte', 'DMA_PeripheralDataSize_HalfWord',
    'DMA_PeripheralDataSize_Word', 'DMA_MemoryDataSize_Byte',
    'DMA_MemoryDataSize_HalfWord', 'DMA_MemoryDataSize_Word', 'DMA_Mode_Normal',
    'DMA_Mode_Circular', 'DMA_Priority_VeryHigh', 'DMA_Priority_High',
    'DMA_Priority_Medium', 'DMA_Priority_Low', 'DMA_M2M_Disable', 'DMA_M2M_Enable',
    'DMAx_CHANNEL1_RMP', 'DMAx_CHANNEL2_RMP', 'DMAx_CHANNEL3_RMP', 'DMAx_CHANNEL4_RMP',
    'DMAx_CHANNEL5_RMP', 'DMAx_CHANNEL6_RMP', 'DMAx_CHANNEL7_RMP', 'DMA1_CH1_DEFAULT',
    'DMA1_CH1_ADC', 'DMA1_CH1_TIM17_CH1', 'DMA1_CH1_TIM17_UP', 'DMA1_CH1_USART1_RX',
    'DMA1_CH1_USART2_RX', 'DMA1_CH1_USART3_RX', 'DMA1_CH1_USART4_RX',
    'DMA1_CH1_USART5_RX', 'DMA1_CH1_USART6_RX', 'DMA1_CH1_USART7_RX',
    'DMA1_CH1_USART8_RX', 'DMA1_CH2_DEFAULT', 'DMA1_CH2_ADC', 'DMA1_CH2_I2C1_TX',
    'DMA1_CH2_SPI1_RX', 'DMA1_CH2_TIM1_CH1', 'DMA1_CH2_TIM17_CH1', 'DMA1_CH2_TIM17_UP',
    'DMA1_CH2_USART1_TX', 'DMA1_CH2_USART2_TX', 'DMA1_CH2_USART3_TX',
    'DMA1_CH2_USART4_TX', 'DMA1_CH2_USART5_TX', 'DMA1_CH2_USART6_TX',
    'DMA1_CH2_USART7_TX', 'DMA1_CH2_USART8_TX', 'DMA1_CH3_DEFAULT', 'DMA1_CH3_TIM6_UP',
    'DMA1_CH3_DAC_CH1', 'DMA1_CH3_I2C1_RX', 'DMA1_CH3_SPI1_TX', 'DMA1_CH3_TIM1_CH2',
    'DMA1_CH3_TIM2_CH2', 'DMA1_CH3_TIM16_CH1', 'DMA1_CH3_TIM16_UP',
    'DMA1_CH3_USART1_RX', 'DMA1_CH3_USART2_RX', 'DMA1_CH3_USART3_RX',
    'DMA1_CH3_USART4_RX', 'DMA1_CH3_USART5_RX', 'DMA1_CH3_USART6_RX',
    'DMA1_CH3_USART7_RX', 'DMA1_CH3_USART8_RX', 'DMA1_CH4_DEFAULT', 'DMA1_CH4_TIM7_UP',
    'DMA1_CH4_DAC_CH2', 'DMA1_CH4_I2C2_TX', 'DMA1_CH4_SPI2_RX', 'DMA1_CH4_TIM2_CH4',
    'DMA1_CH4_TIM3_CH1', 'DMA1_CH4_TIM3_TRIG', 'DMA1_CH4_TIM16_CH1',
    'DMA1_CH4_TIM16_UP', 'DMA1_CH4_USART1_TX', 'DMA1_CH4_USART2_TX',
    'DMA1_CH4_USART3_TX', 'DMA1_CH4_USART4_TX', 'DMA1_CH4_USART5_TX',
    'DMA1_CH4_USART6_TX', 'DMA1_CH4_USART7_TX', 'DMA1_CH4_USART8_TX',
    'DMA1_CH5_DEFAULT', 'DMA1_CH5_I2C2_RX', 'DMA1_CH5_SPI2_TX', 'DMA1_CH5_TIM1_CH3',
    'DMA1_CH5_USART1_RX', 'DMA1_CH5_USART2_RX', 'DMA1_CH5_USART3_RX',
    'DMA1_CH5_USART4_RX', 'DMA1_CH5_USART5_RX', 'DMA1_CH5_USART6_RX',
    'DMA1_CH5_USART7_RX', 'DMA1_CH5_USART8_RX', 'DMA1_CH6_DEFAULT', 'DMA1_CH6_I2C1_TX',
    'DMA1_CH6_SPI2_RX', 'DMA1_CH6_TIM1_CH1', 'DMA1_CH6_TIM1_CH2', 'DMA1_CH6_TIM1_CH3',
    'DMA1_CH6_TIM3_CH1', 'DMA1_CH6_TIM3_TRIG', 'DMA1_CH6_TIM16_CH1',
    'DMA1_CH6_TIM16_UP', 'DMA1_CH6_USART1_RX', 'DMA1_CH6_USART2_RX',
    'DMA1_CH6_USART3_RX', 'DMA1_CH6_USART4_RX', 'DMA1_CH6_USART5_RX',
    'DMA1_CH6_USART6_RX', 'DMA1_CH6_USART7_RX', 'DMA1_CH6_USART8_RX',
    'DMA1_CH7_DEFAULT', 'DMA1_CH7_I2C1_RX', 'DMA1_CH7_SPI2_TX', 'DMA1_CH7_TIM2_CH2',
    'DMA1_CH7_TIM2_CH4', 'DMA1_CH7_TIM17_CH1', 'DMA1_CH7_TIM17_UP',
    'DMA1_CH7_USART1_TX', 'DMA1_CH7_USART2_TX', 'DMA1_CH7_USART3_TX',
    'DMA1_CH7_USART4_TX', 'DMA1_CH7_USART5_TX', 'DMA1_CH7_USART6_TX',
    'DMA1_CH7_USART7_TX', 'DMA1_CH7_USART8_TX', 'DMA2_CH1_DEFAULT', 'DMA2_CH1_I2C2_TX',
    'DMA2_CH1_USART1_TX', 'DMA2_CH1_USART2_TX', 'DMA2_CH1_USART3_TX',
    'DMA2_CH1_USART4_TX', 'DMA2_CH1_USART5_TX', 'DMA2_CH1_USART6_TX',
    'DMA2_CH1_USART7_TX', 'DMA2_CH1_USART8_TX', 'DMA2_CH2_DEFAULT', 'DMA2_CH2_I2C2_RX',
    'DMA2_CH2_USART1_RX', 'DMA2_CH2_USART2_RX', 'DMA2_CH2_USART3_RX',
    'DMA2_CH2_USART4_RX', 'DMA2_CH2_USART5_RX', 'DMA2_CH2_USART6_RX',
    'DMA2_CH2_USART7_RX', 'DMA2_CH2_USART8_RX', 'DMA2_CH3_DEFAULT', 'DMA2_CH3_TIM6_UP',
    'DMA2_CH3_DAC_CH1', 'DMA2_CH3_SPI1_RX', 'DMA2_CH3_USART1_RX', 'DMA2_CH3_USART2_RX',
    'DMA2_CH3_USART3_RX', 'DMA2_CH3_USART4_RX', 'DMA2_CH3_USART5_RX',
    'DMA2_CH3_USART6_RX', 'DMA2_CH3_USART7_RX', 'DMA2_CH3_USART8_RX',
    'DMA2_CH4_DEFAULT', 'DMA2_CH4_TIM7_UP', 'DMA2_CH4_DAC_CH2', 'DMA2_CH4_SPI1_TX',
    'DMA2_CH4_USART1_TX', 'DMA2_CH4_USART2_TX', 'DMA2_CH4_USART3_TX',
    'DMA2_CH4_USART4_TX', 'DMA2_CH4_USART5_TX', 'DMA2_CH4_USART6_TX',
    'DMA2_CH4_USART7_TX', 'DMA2_CH4_USART8_TX', 'DMA2_CH5_DEFAULT', 'DMA2_CH5_ADC',
    'DMA2_CH5_USART1_TX', 'DMA2_CH5_USART2_TX', 'DMA2_CH5_USART3_TX',
    'DMA2_CH5_USART4_TX', 'DMA2_CH5_USART5_TX', 'DMA2_CH5_USART6_TX',
    'DMA2_CH5_USART7_TX', 'DMA2_CH5_USART8_TX', 'DMA_IT_TC', 'DMA_IT_HT', 'DMA_IT_TE',
    'DMA1_IT_GL1', 'DMA1_IT_TC1', 'DMA1_IT_HT1', 'DMA1_IT_TE1', 'DMA1_IT_GL2',
    'DMA1_IT_TC2', 'DMA1_IT_HT2', 'DMA1_IT_TE2', 'DMA1_IT_GL3', 'DMA1_IT_TC3',
    'DMA1_IT_HT3', 'DMA1_IT_TE3', 'DMA1_IT_GL4', 'DMA1_IT_TC4', 'DMA1_IT_HT4',
    'DMA1_IT_TE4', 'DMA1_IT_GL5', 'DMA1_IT_TC5', 'DMA1_IT_HT5', 'DMA1_IT_TE5',
    'DMA1_IT_GL6', 'DMA1_IT_TC6', 'DMA1_IT_HT6', 'DMA1_IT_TE6', 'DMA1_IT_GL7',
    'DMA1_IT_TC7', 'DMA1_IT_HT7', 'DMA1_IT_TE7', 'DMA2_IT_GL1', 'DMA2_IT_TC1',
    'DMA2_IT_HT1', 'DMA2_IT_TE1', 'DMA2_IT_GL2', 'DMA2_IT_TC2', 'DMA2_IT_HT2',
    'DMA2_IT_TE2', 'DMA2_IT_GL3', 'DMA2_IT_TC3', 'DMA2_IT_HT3', 'DMA2_IT_TE3',
    'DMA2_IT_GL4', 'DMA2_IT_TC4', 'DMA2_IT_HT4', 'DMA2_IT_TE4', 'DMA2_IT_GL5',
    'DMA2_IT_TC5', 'DMA2_IT_HT5', 'DMA2_IT_TE5', 'DMA1_FLAG_GL1', 'DMA1_FLAG_TC1',
    'DMA1_FLAG_HT1', 'DMA1_FLAG_TE1', 'DMA1_FLAG_GL2', 'DMA1_FLAG_TC2', 'DMA1_FLAG_HT2',
    'DMA1_FLAG_TE2', 'DMA1_FLAG_GL3', 'DMA1_FLAG_TC3', 'DMA1_FLAG_HT3', 'DMA1_FLAG_TE3',
    'DMA1_FLAG_GL4', 'DMA1_FLAG_TC4', 'DMA1_FLAG_HT4', 'DMA1_FLAG_TE4', 'DMA1_FLAG_GL5',
    'DMA1_FLAG_TC5', 'DMA1_FLAG_HT5', 'DMA1_FLAG_TE5', 'DMA1_FLAG_GL6', 'DMA1_FLAG_TC6',
    'DMA1_FLAG_HT6', 'DMA1_FLAG_TE6', 'DMA1_FLAG_GL7', 'DMA1_FLAG_TC7', 'DMA1_FLAG_HT7',
    'DMA1_FLAG_TE7', 'DMA2_FLAG_GL1', 'DMA2_FLAG_TC1', 'DMA2_FLAG_HT1', 'DMA2_FLAG_TE1',
    'DMA2_FLAG_GL2', 'DMA2_FLAG_TC2', 'DMA2_FLAG_HT2', 'DMA2_FLAG_TE2', 'DMA2_FLAG_GL3',
    'DMA2_FLAG_TC3', 'DMA2_FLAG_HT3', 'DMA2_FLAG_TE3', 'DMA2_FLAG_GL4', 'DMA2_FLAG_TC4',
    'DMA2_FLAG_HT4', 'DMA2_FLAG_TE4', 'DMA2_FLAG_GL5', 'DMA2_FLAG_TC5', 'DMA2_FLAG_HT5',
    'DMA2_FLAG_TE5', 'DMA_InitTypeDef', 'CAN_InitStatus_Failed',
    'CAN_InitStatus_Success', 'CANINITFAILED', 'CANINITOK', 'CAN_Mode_Normal',
    'CAN_Mode_LoopBack', 'CAN_Mode_Silent', 'CAN_Mode_Silent_LoopBack',
    'CAN_OperatingMode_Initialization', 'CAN_OperatingMode_Normal',
    'CAN_OperatingMode_Sleep', 'CAN_ModeStatus_Failed', 'CAN_ModeStatus_Success',
    'CAN_SJW_1tq', 'CAN_SJW_2tq', 'CAN_SJW_3tq', 'CAN_SJW_4tq', 'CAN_BS1_1tq',
    'CAN_BS1_2tq', 'CAN_BS1_3tq', 'CAN_BS1_4tq', 'CAN_BS1_5tq', 'CAN_BS1_6tq',
    'CAN_BS1_7tq', 'CAN_BS1_8tq', 'CAN_BS1_9tq', 'CAN_BS1_10tq', 'CAN_BS1_11tq',
    'CAN_BS1_12tq', 'CAN_BS1_13tq', 'CAN_BS1_14tq', 'CAN_BS1_15tq', 'CAN_BS1_16tq',
    'CAN_BS2_1tq', 'CAN_BS2_2tq', 'CAN_BS2_3tq', 'CAN_BS2_4tq', 'CAN_BS2_5tq',
    'CAN_BS2_6tq', 'CAN_BS2_7tq', 'CAN_BS2_8tq', 'CAN_FilterMode_IdMask',
    'CAN_FilterMode_IdList', 'CAN_FilterScale_16bit', 'CAN_FilterScale_32bit',
    'CAN_Filter_FIFO0', 'CAN_Filter_FIFO1', 'CAN_FilterFIFO0', 'CAN_FilterFIFO1',
    'CAN_Id_Standard', 'CAN_Id_Extended', 'CAN_ID_STD', 'CAN_ID_EXT', 'CAN_RTR_Data',
    'CAN_RTR_Remote', 'CAN_RTR_DATA', 'CAN_RTR_REMOTE', 'CAN_TxStatus_Failed',
    'CAN_TxStatus_Ok', 'CAN_TxStatus_Pending', 'CAN_TxStatus_NoMailBox', 'CANTXFAILED',
    'CANTXOK', 'CANTXPENDING', 'CAN_NO_MB', 'CAN_FIFO0', 'CAN_FIFO1',
    'CAN_Sleep_Failed', 'CAN_Sleep_Ok', 'CANSLEEPFAILED', 'CANSLEEPOK',
    'CAN_WakeUp_Failed', 'CAN_WakeUp_Ok', 'CANWAKEUPFAILED', 'CANWAKEUPOK',
    'CAN_ErrorCode_NoErr', 'CAN_ErrorCode_StuffErr', 'CAN_ErrorCode_FormErr',
    'CAN_ErrorCode_ACKErr', 'CAN_ErrorCode_BitRecessiveErr',
    'CAN_ErrorCode_BitDominantErr', 'CAN_ErrorCode_CRCErr',
    'CAN_ErrorCode_SoftwareSetErr', 'CAN_FLAG_RQCP0', 'CAN_FLAG_RQCP1',
    'CAN_FLAG_RQCP2', 'CAN_FLAG_FMP0', 'CAN_FLAG_FF0', 'CAN_FLAG_FOV0', 'CAN_FLAG_FMP1',
    'CAN_FLAG_FF1', 'CAN_FLAG_FOV1', 'CAN_FLAG_WKU', 'CAN_FLAG_SLAK', 'CAN_FLAG_EWG',
    'CAN_FLAG_EPV', 'CAN_FLAG_BOF', 'CAN_FLAG_LEC', 'CAN_IT_TME', 'CAN_IT_FMP0',
    'CAN_IT_FF0', 'CAN_IT_FOV0', 'CAN_IT_FMP1', 'CAN_IT_FF1', 'CAN_IT_FOV1',
    'CAN_IT_WKU', 'CAN_IT_SLK', 'CAN_IT_EWG', 'CAN_IT_EPV', 'CAN_IT_BOF', 'CAN_IT_LEC',
    'CAN_IT_ERR', 'CAN_IT_RQCP0', 'CAN_IT_RQCP1', 'CAN_IT_RQCP2', 'CAN_InitTypeDef',
    'CAN_FilterInitTypeDef', 'CanTxMsg', 'CanRxMsg', 'DBGMCU_STOP', 'DBGMCU_STANDBY',
    'DBGMCU_TIM2_STOP', 'DBGMCU_TIM3_STOP', 'DBGMCU_TIM6_STOP', 'DBGMCU_TIM7_STOP',
    'DBGMCU_TIM14_STOP', 'DBGMCU_RTC_STOP', 'DBGMCU_WWDG_STOP', 'DBGMCU_IWDG_STOP',
    'DBGMCU_I2C1_SMBUS_TIMEOUT', 'DBGMCU_TIM1_STOP', 'DBGMCU_TIM15_STOP',
    'DBGMCU_TIM16_STOP', 'DBGMCU_TIM17_STOP', 'DAC_Trigger_None', 'DAC_Trigger_T6_TRGO',
    'DAC_Trigger_T3_TRGO', 'DAC_Trigger_T7_TRGO', 'DAC_Trigger_T15_TRGO',
    'DAC_Trigger_T2_TRGO', 'DAC_Trigger_Ext_IT9', 'DAC_Trigger_Software',
    'DAC_WaveGeneration_None', 'DAC_WaveGeneration_Noise',
    'DAC_WaveGeneration_Triangle', 'DAC_LFSRUnmask_Bit0', 'DAC_LFSRUnmask_Bits1_0',
    'DAC_LFSRUnmask_Bits2_0', 'DAC_LFSRUnmask_Bits3_0', 'DAC_LFSRUnmask_Bits4_0',
    'DAC_LFSRUnmask_Bits5_0', 'DAC_LFSRUnmask_Bits6_0', 'DAC_LFSRUnmask_Bits7_0',
    'DAC_LFSRUnmask_Bits8_0', 'DAC_LFSRUnmask_Bits9_0', 'DAC_LFSRUnmask_Bits10_0',
    'DAC_LFSRUnmask_Bits11_0', 'DAC_TriangleAmplitude_1', 'DAC_TriangleAmplitude_3',
    'DAC_TriangleAmplitude_7', 'DAC_TriangleAmplitude_15', 'DAC_TriangleAmplitude_31',
    'DAC_TriangleAmplitude_63', 'DAC_TriangleAmplitude_127',
    'DAC_TriangleAmplitude_255', 'DAC_TriangleAmplitude_511',
    'DAC_TriangleAmplitude_1023', 'DAC_TriangleAmplitude_2047',
    'DAC_TriangleAmplitude_4095', 'DAC_OutputBuffer_Enable', 'DAC_OutputBuffer_Disable',
    'DAC_Channel_1', 'DAC_Channel_2', 'DAC_Align_12b_R', 'DAC_Align_12b_L',
    'DAC_Align_8b_R', 'DAC_Wave_Noise', 'DAC_Wave_Triangle', 'DAC_IT_DMAUDR',
    'DAC_FLAG_DMAUDR', 'DAC_InitTypeDef', 'PWR_PVDLevel_0', 'PWR_PVDLevel_1',
    'PWR_PVDLevel_2', 'PWR_PVDLevel_3', 'PWR_PVDLevel_4', 'PWR_PVDLevel_5',
    'PWR_PVDLevel_6', 'PWR_PVDLevel_7', 'PWR_WakeUpPin_1', 'PWR_WakeUpPin_2',
    'PWR_WakeUpPin_3', 'PWR_WakeUpPin_4', 'PWR_WakeUpPin_5', 'PWR_WakeUpPin_6',
    'PWR_WakeUpPin_7', 'PWR_WakeUpPin_8', 'PWR_Regulator_ON', 'PWR_Regulator_LowPower',
    'PWR_SLEEPEntry_WFI', 'PWR_SLEEPEntry_WFE', 'PWR_STOPEntry_WFI',
    'PWR_STOPEntry_WFE', 'PWR_STOPEntry_SLEEPONEXIT', 'PWR_FLAG_WU', 'PWR_FLAG_SB',
    'PWR_FLAG_PVDO', 'PWR_FLAG_VREFINTRDY', 'CEC_SignalFreeTime_Standard',
    'CEC_SignalFreeTime_1T', 'CEC_SignalFreeTime_2T', 'CEC_SignalFreeTime_3T',
    'CEC_SignalFreeTime_4T', 'CEC_SignalFreeTime_5T', 'CEC_SignalFreeTime_6T',
    'CEC_SignalFreeTime_7T', 'CEC_RxTolerance_Standard', 'CEC_RxTolerance_Extended',
    'CEC_StopReception_Off', 'CEC_StopReception_On', 'CEC_BitRisingError_Off',
    'CEC_BitRisingError_On', 'CEC_LongBitPeriodError_Off', 'CEC_LongBitPeriodError_On',
    'CEC_BRDNoGen_Off', 'CEC_BRDNoGen_On', 'CEC_SFTOption_Off', 'CEC_SFTOption_On',
    'CEC_IT_TXACKE', 'CEC_IT_TXERR', 'CEC_IT_TXUDR', 'CEC_IT_TXEND', 'CEC_IT_TXBR',
    'CEC_IT_ARBLST', 'CEC_IT_RXACKE', 'CEC_IT_LBPE', 'CEC_IT_SBPE', 'CEC_IT_BRE',
    'CEC_IT_RXOVR', 'CEC_IT_RXEND', 'CEC_IT_RXBR', 'CEC_FLAG_TXACKE', 'CEC_FLAG_TXERR',
    'CEC_FLAG_TXUDR', 'CEC_FLAG_TXEND', 'CEC_FLAG_TXBR', 'CEC_FLAG_ARBLST',
    'CEC_FLAG_RXACKE', 'CEC_FLAG_LBPE', 'CEC_FLAG_SBPE', 'CEC_FLAG_BRE',
    'CEC_FLAG_RXOVR', 'CEC_FLAG_RXEND', 'CEC_FLAG_RXBR', 'CEC_InitTypeDef',
    'WWDG_Prescaler_1', 'WWDG_Prescaler_2', 'WWDG_Prescaler_4', 'WWDG_Prescaler_8',
    'USART_WordLength_8b', 'USART_WordLength_9b', 'USART_WordLength_7b',
    'USART_StopBits_1', 'USART_StopBits_2', 'USART_StopBits_1_5', 'USART_Parity_No',
    'USART_Parity_Even', 'USART_Parity_Odd', 'USART_Mode_Rx', 'USART_Mode_Tx',
    'USART_HardwareFlowControl_None', 'USART_HardwareFlowControl_RTS',
    'USART_HardwareFlowControl_CTS', 'USART_HardwareFlowControl_RTS_CTS',
    'USART_Clock_Disable', 'USART_Clock_Enable', 'USART_CPOL_Low', 'USART_CPOL_High',
    'USART_CPHA_1Edge', 'USART_CPHA_2Edge', 'USART_LastBit_Disable',
    'USART_LastBit_Enable', 'USART_DMAReq_Tx', 'USART_DMAReq_Rx',
    'USART_DMAOnError_Enable', 'USART_DMAOnError_Disable', 'USART_WakeUp_IdleLine',
    'USART_WakeUp_AddressMark', 'USART_AddressLength_4b', 'USART_AddressLength_7b',
    'USART_WakeUpSource_AddressMatch', 'USART_WakeUpSource_StartBit',
    'USART_WakeUpSource_RXNE', 'USART_LINBreakDetectLength_10b',
    'USART_LINBreakDetectLength_11b', 'USART_IrDAMode_LowPower',
    'USART_IrDAMode_Normal', 'USART_DEPolarity_High', 'USART_DEPolarity_Low',
    'USART_InvPin_Tx', 'USART_InvPin_Rx', 'USART_AutoBaudRate_StartBit',
    'USART_AutoBaudRate_FallingEdge', 'USART_OVRDetection_Enable',
    'USART_OVRDetection_Disable', 'USART_Request_ABRRQ', 'USART_Request_SBKRQ',
    'USART_Request_MMRQ', 'USART_Request_RXFRQ', 'USART_Request_TXFRQ',
    'USART_FLAG_REACK', 'USART_FLAG_TEACK', 'USART_FLAG_WU', 'USART_FLAG_RWU',
    'USART_FLAG_SBK', 'USART_FLAG_CM', 'USART_FLAG_BUSY', 'USART_FLAG_ABRF',
    'USART_FLAG_ABRE', 'USART_FLAG_EOB', 'USART_FLAG_RTO', 'USART_FLAG_nCTSS',
    'USART_FLAG_CTS', 'USART_FLAG_LBD', 'USART_FLAG_TXE', 'USART_FLAG_TC',
    'USART_FLAG_RXNE', 'USART_FLAG_IDLE', 'USART_FLAG_ORE', 'USART_FLAG_NE',
    'USART_FLAG_FE', 'USART_FLAG_PE', 'USART_IT_WU', 'USART_IT_CM', 'USART_IT_EOB',
    'USART_IT_RTO', 'USART_IT_PE', 'USART_IT_TXE', 'USART_IT_TC', 'USART_IT_RXNE',
    'USART_IT_IDLE', 'USART_IT_LBD', 'USART_IT_CTS', 'USART_IT_ERR', 'USART_IT_ORE',
    'USART_IT_NE', 'USART_IT_FE', 'USART_InitTypeDef', 'USART_ClockInitTypeDef',
    'NVIC_Type', 'SCB_Type', 'SysTick_Type', 'RESET', 'SET', 'DISABLE', 'ENABLE',
    'ERROR', 'SUCCESS', 'HSE_VALUE', 'HSE_STARTUP_TIMEOUT', 'HSI_STARTUP_TIMEOUT',
    'HSI_VALUE', 'HSI14_VALUE', 'HSI48_VALUE', 'LSI_VALUE', 'LSE_VALUE',
    '__STM32F0XX_STDPERIPH_VERSION_MAIN', '__STM32F0XX_STDPERIPH_VERSION_SUB1',
    '__STM32F0XX_STDPERIPH_VERSION_SUB2', '__STM32F0XX_STDPERIPH_VERSION_RC',
    '__STM32F0XX_STDPERIPH_VERSION', '__CM0_REV', '__MPU_PRESENT', '__NVIC_PRIO_BITS',
    '__Vendor_SysTickConfig', 'FLASH_BASE', 'SRAM_BASE', 'PERIPH_BASE',
    'APBPERIPH_BASE', 'AHBPERIPH_BASE', 'AHB2PERIPH_BASE', 'TIM2_BASE', 'TIM3_BASE',
    'TIM6_BASE', 'TIM7_BASE', 'TIM14_BASE', 'RTC_BASE', 'WWDG_BASE', 'IWDG_BASE',
    'SPI2_BASE', 'USART2_BASE', 'USART3_BASE', 'USART4_BASE', 'USART5_BASE',
    'I2C1_BASE', 'I2C2_BASE', 'CAN_BASE', 'CRS_BASE', 'PWR_BASE', 'DAC_BASE',
    'CEC_BASE', 'SYSCFG_BASE', 'COMP_BASE', 'EXTI_BASE', 'USART6_BASE', 'USART7_BASE',
    'USART8_BASE', 'ADC1_BASE', 'ADC_BASE', 'TIM1_BASE', 'SPI1_BASE', 'USART1_BASE',
    'TIM15_BASE', 'TIM16_BASE', 'TIM17_BASE', 'DBGMCU_BASE', 'DMA1_BASE',
    'DMA1_Channel1_BASE', 'DMA1_Channel2_BASE', 'DMA1_Channel3_BASE',
    'DMA1_Channel4_BASE', 'DMA1_Channel5_BASE', 'DMA1_Channel6_BASE',
    'DMA1_Channel7_BASE', 'DMA2_BASE', 'DMA2_Channel1_BASE', 'DMA2_Channel2_BASE',
    'DMA2_Channel3_BASE', 'DMA2_Channel4_BASE', 'DMA2_Channel5_BASE', 'RCC_BASE',
    'FLASH_R_BASE', 'OB_BASE', 'CRC_BASE', 'TSC_BASE', 'GPIOA_BASE', 'GPIOB_BASE',
    'GPIOC_BASE', 'GPIOD_BASE', 'GPIOE_BASE', 'GPIOF_BASE', 'TIM2', 'TIM3', 'TIM6',
    'TIM7', 'TIM14', 'RTC', 'WWDG', 'IWDG', 'SPI2', 'USART2', 'USART3', 'USART4',
    'USART5', 'I2C1', 'I2C2', 'CAN', 'CRS', 'PWR', 'DAC', 'CEC', 'SYSCFG', 'COMP',
    'EXTI', 'USART6', 'USART7', 'USART8', 'ADC1', 'ADC', 'TIM1', 'SPI1', 'USART1',
    'TIM15', 'TIM16', 'TIM17', 'DBGMCU', 'DMA1', 'DMA1_Channel1', 'DMA1_Channel2',
    'DMA1_Channel3', 'DMA1_Channel4', 'DMA1_Channel5', 'DMA1_Channel6', 'DMA1_Channel7',
    'DMA2', 'DMA2_Channel1', 'DMA2_Channel2', 'DMA2_Channel3', 'DMA2_Channel4',
    'DMA2_Channel5', 'FLASH', 'OB', 'RCC', 'CRC', 'TSC', 'GPIOA', 'GPIOB', 'GPIOC',
    'GPIOD', 'GPIOE', 'GPIOF', 'ADC_ISR_AWD', 'ADC_ISR_OVR', 'ADC_ISR_EOSEQ',
    'ADC_ISR_EOC', 'ADC_ISR_EOSMP', 'ADC_ISR_ADRDY', 'ADC_ISR_EOS', 'ADC_IER_AWDIE',
    'ADC_IER_OVRIE', 'ADC_IER_EOSEQIE', 'ADC_IER_EOCIE', 'ADC_IER_EOSMPIE',
    'ADC_IER_ADRDYIE', 'ADC_IER_EOSIE', 'ADC_CR_ADCAL', 'ADC_CR_ADSTP',
    'ADC_CR_ADSTART', 'ADC_CR_ADDIS', 'ADC_CR_ADEN', 'ADC_CFGR1_AWDCH',
    'ADC_CFGR1_AWDCH_0', 'ADC_CFGR1_AWDCH_1', 'ADC_CFGR1_AWDCH_2', 'ADC_CFGR1_AWDCH_3',
    'ADC_CFGR1_AWDCH_4', 'ADC_CFGR1_AWDEN', 'ADC_CFGR1_AWDSGL', 'ADC_CFGR1_DISCEN',
    'ADC_CFGR1_AUTOFF', 'ADC_CFGR1_WAIT', 'ADC_CFGR1_CONT', 'ADC_CFGR1_OVRMOD',
    'ADC_CFGR1_EXTEN', 'ADC_CFGR1_EXTEN_0', 'ADC_CFGR1_EXTEN_1', 'ADC_CFGR1_EXTSEL',
    'ADC_CFGR1_EXTSEL_0', 'ADC_CFGR1_EXTSEL_1', 'ADC_CFGR1_EXTSEL_2', 'ADC_CFGR1_ALIGN',
    'ADC_CFGR1_RES', 'ADC_CFGR1_RES_0', 'ADC_CFGR1_RES_1', 'ADC_CFGR1_SCANDIR',
    'ADC_CFGR1_DMACFG', 'ADC_CFGR1_DMAEN', 'ADC_CFGR1_AUTDLY', 'ADC_CFGR2_CKMODE',
    'ADC_CFGR2_CKMODE_1', 'ADC_CFGR2_CKMODE_0', 'ADC_CFGR2_JITOFFDIV4',
    'ADC_CFGR2_JITOFFDIV2', 'ADC_SMPR_SMP', 'ADC_SMPR_SMP_0', 'ADC_SMPR_SMP_1',
    'ADC_SMPR_SMP_2', 'ADC_SMPR1_SMPR', 'ADC_SMPR1_SMPR_0', 'ADC_SMPR1_SMPR_1',
    'ADC_SMPR1_SMPR_2', 'ADC_TR_HT', 'ADC_TR_LT', 'ADC_HTR_HT', 'ADC_LTR_LT',
    'ADC_CHSELR_CHSEL18', 'ADC_CHSELR_CHSEL17', 'ADC_CHSELR_CHSEL16',
    'ADC_CHSELR_CHSEL15', 'ADC_CHSELR_CHSEL14', 'ADC_CHSELR_CHSEL13',
    'ADC_CHSELR_CHSEL12', 'ADC_CHSELR_CHSEL11', 'ADC_CHSELR_CHSEL10',
    'ADC_CHSELR_CHSEL9', 'ADC_CHSELR_CHSEL8', 'ADC_CHSELR_CHSEL7', 'ADC_CHSELR_CHSEL6',
    'ADC_CHSELR_CHSEL5', 'ADC_CHSELR_CHSEL4', 'ADC_CHSELR_CHSEL3', 'ADC_CHSELR_CHSEL2',
    'ADC_CHSELR_CHSEL1', 'ADC_CHSELR_CHSEL0', 'ADC_DR_DATA', 'ADC_CCR_VBATEN',
    'ADC_CCR_TSEN', 'ADC_CCR_VREFEN', 'CAN_MCR_INRQ', 'CAN_MCR_SLEEP', 'CAN_MCR_TXFP',
    'CAN_MCR_RFLM', 'CAN_MCR_NART', 'CAN_MCR_AWUM', 'CAN_MCR_ABOM', 'CAN_MCR_TTCM',
    'CAN_MCR_RESET', 'CAN_MSR_INAK', 'CAN_MSR_SLAK', 'CAN_MSR_ERRI', 'CAN_MSR_WKUI',
    'CAN_MSR_SLAKI', 'CAN_MSR_TXM', 'CAN_MSR_RXM', 'CAN_MSR_SAMP', 'CAN_MSR_RX',
    'CAN_TSR_RQCP0', 'CAN_TSR_TXOK0', 'CAN_TSR_ALST0', 'CAN_TSR_TERR0', 'CAN_TSR_ABRQ0',
    'CAN_TSR_RQCP1', 'CAN_TSR_TXOK1', 'CAN_TSR_ALST1', 'CAN_TSR_TERR1', 'CAN_TSR_ABRQ1',
    'CAN_TSR_RQCP2', 'CAN_TSR_TXOK2', 'CAN_TSR_ALST2', 'CAN_TSR_TERR2', 'CAN_TSR_ABRQ2',
    'CAN_TSR_CODE', 'CAN_TSR_TME', 'CAN_TSR_TME0', 'CAN_TSR_TME1', 'CAN_TSR_TME2',
    'CAN_TSR_LOW', 'CAN_TSR_LOW0', 'CAN_TSR_LOW1', 'CAN_TSR_LOW2', 'CAN_RF0R_FMP0',
    'CAN_RF0R_FULL0', 'CAN_RF0R_FOVR0', 'CAN_RF0R_RFOM0', 'CAN_RF1R_FMP1',
    'CAN_RF1R_FULL1', 'CAN_RF1R_FOVR1', 'CAN_RF1R_RFOM1', 'CAN_IER_TMEIE',
    'CAN_IER_FMPIE0', 'CAN_IER_FFIE0', 'CAN_IER_FOVIE0', 'CAN_IER_FMPIE1',
    'CAN_IER_FFIE1', 'CAN_IER_FOVIE1', 'CAN_IER_EWGIE', 'CAN_IER_EPVIE',
    'CAN_IER_BOFIE', 'CAN_IER_LECIE', 'CAN_IER_ERRIE', 'CAN_IER_WKUIE', 'CAN_IER_SLKIE',
    'CAN_ESR_EWGF', 'CAN_ESR_EPVF', 'CAN_ESR_BOFF', 'CAN_ESR_LEC', 'CAN_ESR_LEC_0',
    'CAN_ESR_LEC_1', 'CAN_ESR_LEC_2', 'CAN_ESR_TEC', 'CAN_ESR_REC', 'CAN_BTR_BRP',
    'CAN_BTR_TS1', 'CAN_BTR_TS2', 'CAN_BTR_SJW', 'CAN_BTR_LBKM', 'CAN_BTR_SILM',
    'CAN_TI0R_TXRQ', 'CAN_TI0R_RTR', 'CAN_TI0R_IDE', 'CAN_TI0R_EXID', 'CAN_TI0R_STID',
    'CAN_TDT0R_DLC', 'CAN_TDT0R_TGT', 'CAN_TDT0R_TIME', 'CAN_TDL0R_DATA0',
    'CAN_TDL0R_DATA1', 'CAN_TDL0R_DATA2', 'CAN_TDL0R_DATA3', 'CAN_TDH0R_DATA4',
    'CAN_TDH0R_DATA5', 'CAN_TDH0R_DATA6', 'CAN_TDH0R_DATA7', 'CAN_TI1R_TXRQ',
    'CAN_TI1R_RTR', 'CAN_TI1R_IDE', 'CAN_TI1R_EXID', 'CAN_TI1R_STID', 'CAN_TDT1R_DLC',
    'CAN_TDT1R_TGT', 'CAN_TDT1R_TIME', 'CAN_TDL1R_DATA0', 'CAN_TDL1R_DATA1',
    'CAN_TDL1R_DATA2', 'CAN_TDL1R_DATA3', 'CAN_TDH1R_DATA4', 'CAN_TDH1R_DATA5',
    'CAN_TDH1R_DATA6', 'CAN_TDH1R_DATA7', 'CAN_TI2R_TXRQ', 'CAN_TI2R_RTR',
    'CAN_TI2R_IDE', 'CAN_TI2R_EXID', 'CAN_TI2R_STID', 'CAN_TDT2R_DLC', 'CAN_TDT2R_TGT',
    'CAN_TDT2R_TIME', 'CAN_TDL2R_DATA0', 'CAN_TDL2R_DATA1', 'CAN_TDL2R_DATA2',
    'CAN_TDL2R_DATA3', 'CAN_TDH2R_DATA4', 'CAN_TDH2R_DATA5', 'CAN_TDH2R_DATA6',
    'CAN_TDH2R_DATA7', 'CAN_RI0R_RTR', 'CAN_RI0R_IDE', 'CAN_RI0R_EXID', 'CAN_RI0R_STID',
    'CAN_RDT0R_DLC', 'CAN_RDT0R_FMI', 'CAN_RDT0R_TIME', 'CAN_RDL0R_DATA0',
    'CAN_RDL0R_DATA1', 'CAN_RDL0R_DATA2', 'CAN_RDL0R_DATA3', 'CAN_RDH0R_DATA4',
    'CAN_RDH0R_DATA5', 'CAN_RDH0R_DATA6', 'CAN_RDH0R_DATA7', 'CAN_RI1R_RTR',
    'CAN_RI1R_IDE', 'CAN_RI1R_EXID', 'CAN_RI1R_STID', 'CAN_RDT1R_DLC', 'CAN_RDT1R_FMI',
    'CAN_RDT1R_TIME', 'CAN_RDL1R_DATA0', 'CAN_RDL1R_DATA1', 'CAN_RDL1R_DATA2',
    'CAN_RDL1R_DATA3', 'CAN_RDH1R_DATA4', 'CAN_RDH1R_DATA5', 'CAN_RDH1R_DATA6',
    'CAN_RDH1R_DATA7', 'CAN_FMR_FINIT', 'CAN_FM1R_FBM', 'CAN_FM1R_FBM0',
    'CAN_FM1R_FBM1', 'CAN_FM1R_FBM2', 'CAN_FM1R_FBM3', 'CAN_FM1R_FBM4', 'CAN_FM1R_FBM5',
    'CAN_FM1R_FBM6', 'CAN_FM1R_FBM7', 'CAN_FM1R_FBM8', 'CAN_FM1R_FBM9',
    'CAN_FM1R_FBM10', 'CAN_FM1R_FBM11', 'CAN_FM1R_FBM12', 'CAN_FM1R_FBM13',
    'CAN_FS1R_FSC', 'CAN_FS1R_FSC0', 'CAN_FS1R_FSC1', 'CAN_FS1R_FSC2', 'CAN_FS1R_FSC3',
    'CAN_FS1R_FSC4', 'CAN_FS1R_FSC5', 'CAN_FS1R_FSC6', 'CAN_FS1R_FSC7', 'CAN_FS1R_FSC8',
    'CAN_FS1R_FSC9', 'CAN_FS1R_FSC10', 'CAN_FS1R_FSC11', 'CAN_FS1R_FSC12',
    'CAN_FS1R_FSC13', 'CAN_FFA1R_FFA', 'CAN_FFA1R_FFA0', 'CAN_FFA1R_FFA1',
    'CAN_FFA1R_FFA2', 'CAN_FFA1R_FFA3', 'CAN_FFA1R_FFA4', 'CAN_FFA1R_FFA5',
    'CAN_FFA1R_FFA6', 'CAN_FFA1R_FFA7', 'CAN_FFA1R_FFA8', 'CAN_FFA1R_FFA9',
    'CAN_FFA1R_FFA10', 'CAN_FFA1R_FFA11', 'CAN_FFA1R_FFA12', 'CAN_FFA1R_FFA13',
    'CAN_FA1R_FACT', 'CAN_FA1R_FACT0', 'CAN_FA1R_FACT1', 'CAN_FA1R_FACT2',
    'CAN_FA1R_FACT3', 'CAN_FA1R_FACT4', 'CAN_FA1R_FACT5', 'CAN_FA1R_FACT6',
    'CAN_FA1R_FACT7', 'CAN_FA1R_FACT8', 'CAN_FA1R_FACT9', 'CAN_FA1R_FACT10',
    'CAN_FA1R_FACT11', 'CAN_FA1R_FACT12', 'CAN_FA1R_FACT13', 'CAN_F0R1_FB0',
    'CAN_F0R1_FB1', 'CAN_F0R1_FB2', 'CAN_F0R1_FB3', 'CAN_F0R1_FB4', 'CAN_F0R1_FB5',
    'CAN_F0R1_FB6', 'CAN_F0R1_FB7', 'CAN_F0R1_FB8', 'CAN_F0R1_FB9', 'CAN_F0R1_FB10',
    'CAN_F0R1_FB11', 'CAN_F0R1_FB12', 'CAN_F0R1_FB13', 'CAN_F0R1_FB14', 'CAN_F0R1_FB15',
    'CAN_F0R1_FB16', 'CAN_F0R1_FB17', 'CAN_F0R1_FB18', 'CAN_F0R1_FB19', 'CAN_F0R1_FB20',
    'CAN_F0R1_FB21', 'CAN_F0R1_FB22', 'CAN_F0R1_FB23', 'CAN_F0R1_FB24', 'CAN_F0R1_FB25',
    'CAN_F0R1_FB26', 'CAN_F0R1_FB27', 'CAN_F0R1_FB28', 'CAN_F0R1_FB29', 'CAN_F0R1_FB30',
    'CAN_F0R1_FB31', 'CAN_F1R1_FB0', 'CAN_F1R1_FB1', 'CAN_F1R1_FB2', 'CAN_F1R1_FB3',
    'CAN_F1R1_FB4', 'CAN_F1R1_FB5', 'CAN_F1R1_FB6', 'CAN_F1R1_FB7', 'CAN_F1R1_FB8',
    'CAN_F1R1_FB9', 'CAN_F1R1_FB10', 'CAN_F1R1_FB11', 'CAN_F1R1_FB12', 'CAN_F1R1_FB13',
    'CAN_F1R1_FB14', 'CAN_F1R1_FB15', 'CAN_F1R1_FB16', 'CAN_F1R1_FB17', 'CAN_F1R1_FB18',
    'CAN_F1R1_FB19', 'CAN_F1R1_FB20', 'CAN_F1R1_FB21', 'CAN_F1R1_FB22', 'CAN_F1R1_FB23',
    'CAN_F1R1_FB24', 'CAN_F1R1_FB25', 'CAN_F1R1_FB26', 'CAN_F1R1_FB27', 'CAN_F1R1_FB28',
    'CAN_F1R1_FB29', 'CAN_F1R1_FB30', 'CAN_F1R1_FB31', 'CAN_F2R1_FB0', 'CAN_F2R1_FB1',
    'CAN_F2R1_FB2', 'CAN_F2R1_FB3', 'CAN_F2R1_FB4', 'CAN_F2R1_FB5', 'CAN_F2R1_FB6',
    'CAN_F2R1_FB7', 'CAN_F2R1_FB8', 'CAN_F2R1_FB9', 'CAN_F2R1_FB10', 'CAN_F2R1_FB11',
    'CAN_F2R1_FB12', 'CAN_F2R1_FB13', 'CAN_F2R1_FB14', 'CAN_F2R1_FB15', 'CAN_F2R1_FB16',
    'CAN_F2R1_FB17', 'CAN_F2R1_FB18', 'CAN_F2R1_FB19', 'CAN_F2R1_FB20', 'CAN_F2R1_FB21',
    'CAN_F2R1_FB22', 'CAN_F2R1_FB23', 'CAN_F2R1_FB24', 'CAN_F2R1_FB25', 'CAN_F2R1_FB26',
    'CAN_F2R1_FB27', 'CAN_F2R1_FB28', 'CAN_F2R1_FB29', 'CAN_F2R1_FB30', 'CAN_F2R1_FB31',
    'CAN_F3R1_FB0', 'CAN_F3R1_FB1', 'CAN_F3R1_FB2', 'CAN_F3R1_FB3', 'CAN_F3R1_FB4',
    'CAN_F3R1_FB5', 'CAN_F3R1_FB6', 'CAN_F3R1_FB7', 'CAN_F3R1_FB8', 'CAN_F3R1_FB9',
    'CAN_F3R1_FB10', 'CAN_F3R1_FB11', 'CAN_F3R1_FB12', 'CAN_F3R1_FB13', 'CAN_F3R1_FB14',
    'CAN_F3R1_FB15', 'CAN_F3R1_FB16', 'CAN_F3R1_FB17', 'CAN_F3R1_FB18', 'CAN_F3R1_FB19',
    'CAN_F3R1_FB20', 'CAN_F3R1_FB21', 'CAN_F3R1_FB22', 'CAN_F3R1_FB23', 'CAN_F3R1_FB24',
    'CAN_F3R1_FB25', 'CAN_F3R1_FB26', 'CAN_F3R1_FB27', 'CAN_F3R1_FB28', 'CAN_F3R1_FB29',
    'CAN_F3R1_FB30', 'CAN_F3R1_FB31', 'CAN_F4R1_FB0', 'CAN_F4R1_FB1', 'CAN_F4R1_FB2',
    'CAN_F4R1_FB3', 'CAN_F4R1_FB4', 'CAN_F4R1_FB5', 'CAN_F4R1_FB6', 'CAN_F4R1_FB7',
    'CAN_F4R1_FB8', 'CAN_F4R1_FB9', 'CAN_F4R1_FB10', 'CAN_F4R1_FB11', 'CAN_F4R1_FB12',
    'CAN_F4R1_FB13', 'CAN_F4R1_FB14', 'CAN_F4R1_FB15', 'CAN_F4R1_FB16', 'CAN_F4R1_FB17',
    'CAN_F4R1_FB18', 'CAN_F4R1_FB19', 'CAN_F4R1_FB20', 'CAN_F4R1_FB21', 'CAN_F4R1_FB22',
    'CAN_F4R1_FB23', 'CAN_F4R1_FB24', 'CAN_F4R1_FB25', 'CAN_F4R1_FB26', 'CAN_F4R1_FB27',
    'CAN_F4R1_FB28', 'CAN_F4R1_FB29', 'CAN_F4R1_FB30', 'CAN_F4R1_FB31', 'CAN_F5R1_FB0',
    'CAN_F5R1_FB1', 'CAN_F5R1_FB2', 'CAN_F5R1_FB3', 'CAN_F5R1_FB4', 'CAN_F5R1_FB5',
    'CAN_F5R1_FB6', 'CAN_F5R1_FB7', 'CAN_F5R1_FB8', 'CAN_F5R1_FB9', 'CAN_F5R1_FB10',
    'CAN_F5R1_FB11', 'CAN_F5R1_FB12', 'CAN_F5R1_FB13', 'CAN_F5R1_FB14', 'CAN_F5R1_FB15',
    'CAN_F5R1_FB16', 'CAN_F5R1_FB17', 'CAN_F5R1_FB18', 'CAN_F5R1_FB19', 'CAN_F5R1_FB20',
    'CAN_F5R1_FB21', 'CAN_F5R1_FB22', 'CAN_F5R1_FB23', 'CAN_F5R1_FB24', 'CAN_F5R1_FB25',
    'CAN_F5R1_FB26', 'CAN_F5R1_FB27', 'CAN_F5R1_FB28', 'CAN_F5R1_FB29', 'CAN_F5R1_FB30',
    'CAN_F5R1_FB31', 'CAN_F6R1_FB0', 'CAN_F6R1_FB1', 'CAN_F6R1_FB2', 'CAN_F6R1_FB3',
    'CAN_F6R1_FB4', 'CAN_F6R1_FB5', 'CAN_F6R1_FB6', 'CAN_F6R1_FB7', 'CAN_F6R1_FB8',
    'CAN_F6R1_FB9', 'CAN_F6R1_FB10', 'CAN_F6R1_FB11', 'CAN_F6R1_FB12', 'CAN_F6R1_FB13',
    'CAN_F6R1_FB14', 'CAN_F6R1_FB15', 'CAN_F6R1_FB16', 'CAN_F6R1_FB17', 'CAN_F6R1_FB18',
    'CAN_F6R1_FB19', 'CAN_F6R1_FB20', 'CAN_F6R1_FB21', 'CAN_F6R1_FB22', 'CAN_F6R1_FB23',
    'CAN_F6R1_FB24', 'CAN_F6R1_FB25', 'CAN_F6R1_FB26', 'CAN_F6R1_FB27', 'CAN_F6R1_FB28',
    'CAN_F6R1_FB29', 'CAN_F6R1_FB30', 'CAN_F6R1_FB31', 'CAN_F7R1_FB0', 'CAN_F7R1_FB1',
    'CAN_F7R1_FB2', 'CAN_F7R1_FB3', 'CAN_F7R1_FB4', 'CAN_F7R1_FB5', 'CAN_F7R1_FB6',
    'CAN_F7R1_FB7', 'CAN_F7R1_FB8', 'CAN_F7R1_FB9', 'CAN_F7R1_FB10', 'CAN_F7R1_FB11',
    'CAN_F7R1_FB12', 'CAN_F7R1_FB13', 'CAN_F7R1_FB14', 'CAN_F7R1_FB15', 'CAN_F7R1_FB16',
    'CAN_F7R1_FB17', 'CAN_F7R1_FB18', 'CAN_F7R1_FB19', 'CAN_F7R1_FB20', 'CAN_F7R1_FB21',
    'CAN_F7R1_FB22', 'CAN_F7R1_FB23', 'CAN_F7R1_FB24', 'CAN_F7R1_FB25', 'CAN_F7R1_FB26',
    'CAN_F7R1_FB27', 'CAN_F7R1_FB28', 'CAN_F7R1_FB29', 'CAN_F7R1_FB30', 'CAN_F7R1_FB31',
    'CAN_F8R1_FB0', 'CAN_F8R1_FB1', 'CAN_F8R1_FB2', 'CAN_F8R1_FB3', 'CAN_F8R1_FB4',
    'CAN_F8R1_FB5', 'CAN_F8R1_FB6', 'CAN_F8R1_FB7', 'CAN_F8R1_FB8', 'CAN_F8R1_FB9',
    'CAN_F8R1_FB10', 'CAN_F8R1_FB11', 'CAN_F8R1_FB12', 'CAN_F8R1_FB13', 'CAN_F8R1_FB14',
    'CAN_F8R1_FB15', 'CAN_F8R1_FB16', 'CAN_F8R1_FB17', 'CAN_F8R1_FB18', 'CAN_F8R1_FB19',
    'CAN_F8R1_FB20', 'CAN_F8R1_FB21', 'CAN_F8R1_FB22', 'CAN_F8R1_FB23', 'CAN_F8R1_FB24',
    'CAN_F8R1_FB25', 'CAN_F8R1_FB26', 'CAN_F8R1_FB27', 'CAN_F8R1_FB28', 'CAN_F8R1_FB29',
    'CAN_F8R1_FB30', 'CAN_F8R1_FB31', 'CAN_F9R1_FB0', 'CAN_F9R1_FB1', 'CAN_F9R1_FB2',
    'CAN_F9R1_FB3', 'CAN_F9R1_FB4', 'CAN_F9R1_FB5', 'CAN_F9R1_FB6', 'CAN_F9R1_FB7',
    'CAN_F9R1_FB8', 'CAN_F9R1_FB9', 'CAN_F9R1_FB10', 'CAN_F9R1_FB11', 'CAN_F9R1_FB12',
    'CAN_F9R1_FB13', 'CAN_F9R1_FB14', 'CAN_F9R1_FB15', 'CAN_F9R1_FB16', 'CAN_F9R1_FB17',
    'CAN_F9R1_FB18', 'CAN_F9R1_FB19', 'CAN_F9R1_FB20', 'CAN_F9R1_FB21', 'CAN_F9R1_FB22',
    'CAN_F9R1_FB23', 'CAN_F9R1_FB24', 'CAN_F9R1_FB25', 'CAN_F9R1_FB26', 'CAN_F9R1_FB27',
    'CAN_F9R1_FB28', 'CAN_F9R1_FB29', 'CAN_F9R1_FB30', 'CAN_F9R1_FB31', 'CAN_F10R1_FB0',
    'CAN_F10R1_FB1', 'CAN_F10R1_FB2', 'CAN_F10R1_FB3', 'CAN_F10R1_FB4', 'CAN_F10R1_FB5',
    'CAN_F10R1_FB6', 'CAN_F10R1_FB7', 'CAN_F10R1_FB8', 'CAN_F10R1_FB9',
    'CAN_F10R1_FB10', 'CAN_F10R1_FB11', 'CAN_F10R1_FB12', 'CAN_F10R1_FB13',
    'CAN_F10R1_FB14', 'CAN_F10R1_FB15', 'CAN_F10R1_FB16', 'CAN_F10R1_FB17',
    'CAN_F10R1_FB18', 'CAN_F10R1_FB19', 'CAN_F10R1_FB20', 'CAN_F10R1_FB21',
    'CAN_F10R1_FB22', 'CAN_F10R1_FB23', 'CAN_F10R1_FB24', 'CAN_F10R1_FB25',
    'CAN_F10R1_FB26', 'CAN_F10R1_FB27', 'CAN_F10R1_FB28', 'CAN_F10R1_FB29',
    'CAN_F10R1_FB30', 'CAN_F10R1_FB31', 'CAN_F11R1_FB0', 'CAN_F11R1_FB1',
    'CAN_F11R1_FB2', 'CAN_F11R1_FB3', 'CAN_F11R1_FB4', 'CAN_F11R1_FB5', 'CAN_F11R1_FB6',
    'CAN_F11R1_FB7', 'CAN_F11R1_FB8', 'CAN_F11R1_FB9', 'CAN_F11R1_FB10',
    'CAN_F11R1_FB11', 'CAN_F11R1_FB12', 'CAN_F11R1_FB13', 'CAN_F11R1_FB14',
    'CAN_F11R1_FB15', 'CAN_F11R1_FB16', 'CAN_F11R1_FB17', 'CAN_F11R1_FB18',
    'CAN_F11R1_FB19', 'CAN_F11R1_FB20', 'CAN_F11R1_FB21', 'CAN_F11R1_FB22',
    'CAN_F11R1_FB23', 'CAN_F11R1_FB24', 'CAN_F11R1_FB25', 'CAN_F11R1_FB26',
    'CAN_F11R1_FB27', 'CAN_F11R1_FB28', 'CAN_F11R1_FB29', 'CAN_F11R1_FB30',
    'CAN_F11R1_FB31', 'CAN_F12R1_FB0', 'CAN_F12R1_FB1', 'CAN_F12R1_FB2',
    'CAN_F12R1_FB3', 'CAN_F12R1_FB4', 'CAN_F12R1_FB5', 'CAN_F12R1_FB6', 'CAN_F12R1_FB7',
    'CAN_F12R1_FB8', 'CAN_F12R1_FB9', 'CAN_F12R1_FB10', 'CAN_F12R1_FB11',
    'CAN_F12R1_FB12', 'CAN_F12R1_FB13', 'CAN_F12R1_FB14', 'CAN_F12R1_FB15',
    'CAN_F12R1_FB16', 'CAN_F12R1_FB17', 'CAN_F12R1_FB18', 'CAN_F12R1_FB19',
    'CAN_F12R1_FB20', 'CAN_F12R1_FB21', 'CAN_F12R1_FB22', 'CAN_F12R1_FB23',
    'CAN_F12R1_FB24', 'CAN_F12R1_FB25', 'CAN_F12R1_FB26', 'CAN_F12R1_FB27',
    'CAN_F12R1_FB28', 'CAN_F12R1_FB29', 'CAN_F12R1_FB30', 'CAN_F12R1_FB31',
    'CAN_F13R1_FB0', 'CAN_F13R1_FB1', 'CAN_F13R1_FB2', 'CAN_F13R1_FB3', 'CAN_F13R1_FB4',
    'CAN_F13R1_FB5', 'CAN_F13R1_FB6', 'CAN_F13R1_FB7', 'CAN_F13R1_FB8', 'CAN_F13R1_FB9',
    'CAN_F13R1_FB10', 'CAN_F13R1_FB11', 'CAN_F13R1_FB12', 'CAN_F13R1_FB13',
    'CAN_F13R1_FB14', 'CAN_F13R1_FB15', 'CAN_F13R1_FB16', 'CAN_F13R1_FB17',
    'CAN_F13R1_FB18', 'CAN_F13R1_FB19', 'CAN_F13R1_FB20', 'CAN_F13R1_FB21',
    'CAN_F13R1_FB22', 'CAN_F13R1_FB23', 'CAN_F13R1_FB24', 'CAN_F13R1_FB25',
    'CAN_F13R1_FB26', 'CAN_F13R1_FB27', 'CAN_F13R1_FB28', 'CAN_F13R1_FB29',
    'CAN_F13R1_FB30', 'CAN_F13R1_FB31', 'CAN_F0R2_FB0', 'CAN_F0R2_FB1', 'CAN_F0R2_FB2',
    'CAN_F0R2_FB3', 'CAN_F0R2_FB4', 'CAN_F0R2_FB5', 'CAN_F0R2_FB6', 'CAN_F0R2_FB7',
    'CAN_F0R2_FB8', 'CAN_F0R2_FB9', 'CAN_F0R2_FB10', 'CAN_F0R2_FB11', 'CAN_F0R2_FB12',
    'CAN_F0R2_FB13', 'CAN_F0R2_FB14', 'CAN_F0R2_FB15', 'CAN_F0R2_FB16', 'CAN_F0R2_FB17',
    'CAN_F0R2_FB18', 'CAN_F0R2_FB19', 'CAN_F0R2_FB20', 'CAN_F0R2_FB21', 'CAN_F0R2_FB22',
    'CAN_F0R2_FB23', 'CAN_F0R2_FB24', 'CAN_F0R2_FB25', 'CAN_F0R2_FB26', 'CAN_F0R2_FB27',
    'CAN_F0R2_FB28', 'CAN_F0R2_FB29', 'CAN_F0R2_FB30', 'CAN_F0R2_FB31', 'CAN_F1R2_FB0',
    'CAN_F1R2_FB1', 'CAN_F1R2_FB2', 'CAN_F1R2_FB3', 'CAN_F1R2_FB4', 'CAN_F1R2_FB5',
    'CAN_F1R2_FB6', 'CAN_F1R2_FB7', 'CAN_F1R2_FB8', 'CAN_F1R2_FB9', 'CAN_F1R2_FB10',
    'CAN_F1R2_FB11', 'CAN_F1R2_FB12', 'CAN_F1R2_FB13', 'CAN_F1R2_FB14', 'CAN_F1R2_FB15',
    'CAN_F1R2_FB16', 'CAN_F1R2_FB17', 'CAN_F1R2_FB18', 'CAN_F1R2_FB19', 'CAN_F1R2_FB20',
    'CAN_F1R2_FB21', 'CAN_F1R2_FB22', 'CAN_F1R2_FB23', 'CAN_F1R2_FB24', 'CAN_F1R2_FB25',
    'CAN_F1R2_FB26', 'CAN_F1R2_FB27', 'CAN_F1R2_FB28', 'CAN_F1R2_FB29', 'CAN_F1R2_FB30',
    'CAN_F1R2_FB31', 'CAN_F2R2_FB0', 'CAN_F2R2_FB1', 'CAN_F2R2_FB2', 'CAN_F2R2_FB3',
    'CAN_F2R2_FB4', 'CAN_F2R2_FB5', 'CAN_F2R2_FB6', 'CAN_F2R2_FB7', 'CAN_F2R2_FB8',
    'CAN_F2R2_FB9', 'CAN_F2R2_FB10', 'CAN_F2R2_FB11', 'CAN_F2R2_FB12', 'CAN_F2R2_FB13',
    'CAN_F2R2_FB14', 'CAN_F2R2_FB15', 'CAN_F2R2_FB16', 'CAN_F2R2_FB17', 'CAN_F2R2_FB18',
    'CAN_F2R2_FB19', 'CAN_F2R2_FB20', 'CAN_F2R2_FB21', 'CAN_F2R2_FB22', 'CAN_F2R2_FB23',
    'CAN_F2R2_FB24', 'CAN_F2R2_FB25', 'CAN_F2R2_FB26', 'CAN_F2R2_FB27', 'CAN_F2R2_FB28',
    'CAN_F2R2_FB29', 'CAN_F2R2_FB30', 'CAN_F2R2_FB31', 'CAN_F3R2_FB0', 'CAN_F3R2_FB1',
    'CAN_F3R2_FB2', 'CAN_F3R2_FB3', 'CAN_F3R2_FB4', 'CAN_F3R2_FB5', 'CAN_F3R2_FB6',
    'CAN_F3R2_FB7', 'CAN_F3R2_FB8', 'CAN_F3R2_FB9', 'CAN_F3R2_FB10', 'CAN_F3R2_FB11',
    'CAN_F3R2_FB12', 'CAN_F3R2_FB13', 'CAN_F3R2_FB14', 'CAN_F3R2_FB15', 'CAN_F3R2_FB16',
    'CAN_F3R2_FB17', 'CAN_F3R2_FB18', 'CAN_F3R2_FB19', 'CAN_F3R2_FB20', 'CAN_F3R2_FB21',
    'CAN_F3R2_FB22', 'CAN_F3R2_FB23', 'CAN_F3R2_FB24', 'CAN_F3R2_FB25', 'CAN_F3R2_FB26',
    'CAN_F3R2_FB27', 'CAN_F3R2_FB28', 'CAN_F3R2_FB29', 'CAN_F3R2_FB30', 'CAN_F3R2_FB31',
    'CAN_F4R2_FB0', 'CAN_F4R2_FB1', 'CAN_F4R2_FB2', 'CAN_F4R2_FB3', 'CAN_F4R2_FB4',
    'CAN_F4R2_FB5', 'CAN_F4R2_FB6', 'CAN_F4R2_FB7', 'CAN_F4R2_FB8', 'CAN_F4R2_FB9',
    'CAN_F4R2_FB10', 'CAN_F4R2_FB11', 'CAN_F4R2_FB12', 'CAN_F4R2_FB13', 'CAN_F4R2_FB14',
    'CAN_F4R2_FB15', 'CAN_F4R2_FB16', 'CAN_F4R2_FB17', 'CAN_F4R2_FB18', 'CAN_F4R2_FB19',
    'CAN_F4R2_FB20', 'CAN_F4R2_FB21', 'CAN_F4R2_FB22', 'CAN_F4R2_FB23', 'CAN_F4R2_FB24',
    'CAN_F4R2_FB25', 'CAN_F4R2_FB26', 'CAN_F4R2_FB27', 'CAN_F4R2_FB28', 'CAN_F4R2_FB29',
    'CAN_F4R2_FB30', 'CAN_F4R2_FB31', 'CAN_F5R2_FB0', 'CAN_F5R2_FB1', 'CAN_F5R2_FB2',
    'CAN_F5R2_FB3', 'CAN_F5R2_FB4', 'CAN_F5R2_FB5', 'CAN_F5R2_FB6', 'CAN_F5R2_FB7',
    'CAN_F5R2_FB8', 'CAN_F5R2_FB9', 'CAN_F5R2_FB10', 'CAN_F5R2_FB11', 'CAN_F5R2_FB12',
    'CAN_F5R2_FB13', 'CAN_F5R2_FB14', 'CAN_F5R2_FB15', 'CAN_F5R2_FB16', 'CAN_F5R2_FB17',
    'CAN_F5R2_FB18', 'CAN_F5R2_FB19', 'CAN_F5R2_FB20', 'CAN_F5R2_FB21', 'CAN_F5R2_FB22',
    'CAN_F5R2_FB23', 'CAN_F5R2_FB24', 'CAN_F5R2_FB25', 'CAN_F5R2_FB26', 'CAN_F5R2_FB27',
    'CAN_F5R2_FB28', 'CAN_F5R2_FB29', 'CAN_F5R2_FB30', 'CAN_F5R2_FB31', 'CAN_F6R2_FB0',
    'CAN_F6R2_FB1', 'CAN_F6R2_FB2', 'CAN_F6R2_FB3', 'CAN_F6R2_FB4', 'CAN_F6R2_FB5',
    'CAN_F6R2_FB6', 'CAN_F6R2_FB7', 'CAN_F6R2_FB8', 'CAN_F6R2_FB9', 'CAN_F6R2_FB10',
    'CAN_F6R2_FB11', 'CAN_F6R2_FB12', 'CAN_F6R2_FB13', 'CAN_F6R2_FB14', 'CAN_F6R2_FB15',
    'CAN_F6R2_FB16', 'CAN_F6R2_FB17', 'CAN_F6R2_FB18', 'CAN_F6R2_FB19', 'CAN_F6R2_FB20',
    'CAN_F6R2_FB21', 'CAN_F6R2_FB22', 'CAN_F6R2_FB23', 'CAN_F6R2_FB24', 'CAN_F6R2_FB25',
    'CAN_F6R2_FB26', 'CAN_F6R2_FB27', 'CAN_F6R2_FB28', 'CAN_F6R2_FB29', 'CAN_F6R2_FB30',
    'CAN_F6R2_FB31', 'CAN_F7R2_FB0', 'CAN_F7R2_FB1', 'CAN_F7R2_FB2', 'CAN_F7R2_FB3',
    'CAN_F7R2_FB4', 'CAN_F7R2_FB5', 'CAN_F7R2_FB6', 'CAN_F7R2_FB7', 'CAN_F7R2_FB8',
    'CAN_F7R2_FB9', 'CAN_F7R2_FB10', 'CAN_F7R2_FB11', 'CAN_F7R2_FB12', 'CAN_F7R2_FB13',
    'CAN_F7R2_FB14', 'CAN_F7R2_FB15', 'CAN_F7R2_FB16', 'CAN_F7R2_FB17', 'CAN_F7R2_FB18',
    'CAN_F7R2_FB19', 'CAN_F7R2_FB20', 'CAN_F7R2_FB21', 'CAN_F7R2_FB22', 'CAN_F7R2_FB23',
    'CAN_F7R2_FB24', 'CAN_F7R2_FB25', 'CAN_F7R2_FB26', 'CAN_F7R2_FB27', 'CAN_F7R2_FB28',
    'CAN_F7R2_FB29', 'CAN_F7R2_FB30', 'CAN_F7R2_FB31', 'CAN_F8R2_FB0', 'CAN_F8R2_FB1',
    'CAN_F8R2_FB2', 'CAN_F8R2_FB3', 'CAN_F8R2_FB4', 'CAN_F8R2_FB5', 'CAN_F8R2_FB6',
    'CAN_F8R2_FB7', 'CAN_F8R2_FB8', 'CAN_F8R2_FB9', 'CAN_F8R2_FB10', 'CAN_F8R2_FB11',
    'CAN_F8R2_FB12', 'CAN_F8R2_FB13', 'CAN_F8R2_FB14', 'CAN_F8R2_FB15', 'CAN_F8R2_FB16',
    'CAN_F8R2_FB17', 'CAN_F8R2_FB18', 'CAN_F8R2_FB19', 'CAN_F8R2_FB20', 'CAN_F8R2_FB21',
    'CAN_F8R2_FB22', 'CAN_F8R2_FB23', 'CAN_F8R2_FB24', 'CAN_F8R2_FB25', 'CAN_F8R2_FB26',
    'CAN_F8R2_FB27', 'CAN_F8R2_FB28', 'CAN_F8R2_FB29', 'CAN_F8R2_FB30', 'CAN_F8R2_FB31',
    'CAN_F9R2_FB0', 'CAN_F9R2_FB1', 'CAN_F9R2_FB2', 'CAN_F9R2_FB3', 'CAN_F9R2_FB4',
    'CAN_F9R2_FB5', 'CAN_F9R2_FB6', 'CAN_F9R2_FB7', 'CAN_F9R2_FB8', 'CAN_F9R2_FB9',
    'CAN_F9R2_FB10', 'CAN_F9R2_FB11', 'CAN_F9R2_FB12', 'CAN_F9R2_FB13', 'CAN_F9R2_FB14',
    'CAN_F9R2_FB15', 'CAN_F9R2_FB16', 'CAN_F9R2_FB17', 'CAN_F9R2_FB18', 'CAN_F9R2_FB19',
    'CAN_F9R2_FB20', 'CAN_F9R2_FB21', 'CAN_F9R2_FB22', 'CAN_F9R2_FB23', 'CAN_F9R2_FB24',
    'CAN_F9R2_FB25', 'CAN_F9R2_FB26', 'CAN_F9R2_FB27', 'CAN_F9R2_FB28', 'CAN_F9R2_FB29',
    'CAN_F9R2_FB30', 'CAN_F9R2_FB31', 'CAN_F10R2_FB0', 'CAN_F10R2_FB1', 'CAN_F10R2_FB2',
    'CAN_F10R2_FB3', 'CAN_F10R2_FB4', 'CAN_F10R2_FB5', 'CAN_F10R2_FB6', 'CAN_F10R2_FB7',
    'CAN_F10R2_FB8', 'CAN_F10R2_FB9', 'CAN_F10R2_FB10', 'CAN_F10R2_FB11',
    'CAN_F10R2_FB12', 'CAN_F10R2_FB13', 'CAN_F10R2_FB14', 'CAN_F10R2_FB15',
    'CAN_F10R2_FB16', 'CAN_F10R2_FB17', 'CAN_F10R2_FB18', 'CAN_F10R2_FB19',
    'CAN_F10R2_FB20', 'CAN_F10R2_FB21', 'CAN_F10R2_FB22', 'CAN_F10R2_FB23',
    'CAN_F10R2_FB24', 'CAN_F10R2_FB25', 'CAN_F10R2_FB26', 'CAN_F10R2_FB27',
    'CAN_F10R2_FB28', 'CAN_F10R2_FB29', 'CAN_F10R2_FB30', 'CAN_F10R2_FB31',
    'CAN_F11R2_FB0', 'CAN_F11R2_FB1', 'CAN_F11R2_FB2', 'CAN_F11R2_FB3', 'CAN_F11R2_FB4',
    'CAN_F11R2_FB5', 'CAN_F11R2_FB6', 'CAN_F11R2_FB7', 'CAN_F11R2_FB8', 'CAN_F11R2_FB9',
    'CAN_F11R2_FB10', 'CAN_F11R2_FB11', 'CAN_F11R2_FB12', 'CAN_F11R2_FB13',
    'CAN_F11R2_FB14', 'CAN_F11R2_FB15', 'CAN_F11R2_FB16', 'CAN_F11R2_FB17',
    'CAN_F11R2_FB18', 'CAN_F11R2_FB19', 'CAN_F11R2_FB20', 'CAN_F11R2_FB21',
    'CAN_F11R2_FB22', 'CAN_F11R2_FB23', 'CAN_F11R2_FB24', 'CAN_F11R2_FB25',
    'CAN_F11R2_FB26', 'CAN_F11R2_FB27', 'CAN_F11R2_FB28', 'CAN_F11R2_FB29',
    'CAN_F11R2_FB30', 'CAN_F11R2_FB31', 'CAN_F12R2_FB0', 'CAN_F12R2_FB1',
    'CAN_F12R2_FB2', 'CAN_F12R2_FB3', 'CAN_F12R2_FB4', 'CAN_F12R2_FB5', 'CAN_F12R2_FB6',
    'CAN_F12R2_FB7', 'CAN_F12R2_FB8', 'CAN_F12R2_FB9', 'CAN_F12R2_FB10',
    'CAN_F12R2_FB11', 'CAN_F12R2_FB12', 'CAN_F12R2_FB13', 'CAN_F12R2_FB14',
    'CAN_F12R2_FB15', 'CAN_F12R2_FB16', 'CAN_F12R2_FB17', 'CAN_F12R2_FB18',
    'CAN_F12R2_FB19', 'CAN_F12R2_FB20', 'CAN_F12R2_FB21', 'CAN_F12R2_FB22',
    'CAN_F12R2_FB23', 'CAN_F12R2_FB24', 'CAN_F12R2_FB25', 'CAN_F12R2_FB26',
    'CAN_F12R2_FB27', 'CAN_F12R2_FB28', 'CAN_F12R2_FB29', 'CAN_F12R2_FB30',
    'CAN_F12R2_FB31', 'CAN_F13R2_FB0', 'CAN_F13R2_FB1', 'CAN_F13R2_FB2',
    'CAN_F13R2_FB3', 'CAN_F13R2_FB4', 'CAN_F13R2_FB5', 'CAN_F13R2_FB6', 'CAN_F13R2_FB7',
    'CAN_F13R2_FB8', 'CAN_F13R2_FB9', 'CAN_F13R2_FB10', 'CAN_F13R2_FB11',
    'CAN_F13R2_FB12', 'CAN_F13R2_FB13', 'CAN_F13R2_FB14', 'CAN_F13R2_FB15',
    'CAN_F13R2_FB16', 'CAN_F13R2_FB17', 'CAN_F13R2_FB18', 'CAN_F13R2_FB19',
    'CAN_F13R2_FB20', 'CAN_F13R2_FB21', 'CAN_F13R2_FB22', 'CAN_F13R2_FB23',
    'CAN_F13R2_FB24', 'CAN_F13R2_FB25', 'CAN_F13R2_FB26', 'CAN_F13R2_FB27',
    'CAN_F13R2_FB28', 'CAN_F13R2_FB29', 'CAN_F13R2_FB30', 'CAN_F13R2_FB31',
    'CEC_CR_CECEN', 'CEC_CR_TXSOM', 'CEC_CR_TXEOM', 'CEC_CFGR_SFT', 'CEC_CFGR_RXTOL',
    'CEC_CFGR_BRESTP', 'CEC_CFGR_BREGEN', 'CEC_CFGR_LREGEN', 'CEC_CFGR_BRDNOGEN',
    'CEC_CFGR_SFTOPT', 'CEC_CFGR_OAR', 'CEC_CFGR_LSTN', 'CEC_TXDR_TXD', 'CEC_TXDR_RXD',
    'CEC_ISR_RXBR', 'CEC_ISR_RXEND', 'CEC_ISR_RXOVR', 'CEC_ISR_BRE', 'CEC_ISR_SBPE',
    'CEC_ISR_LBPE', 'CEC_ISR_RXACKE', 'CEC_ISR_ARBLST', 'CEC_ISR_TXBR', 'CEC_ISR_TXEND',
    'CEC_ISR_TXUDR', 'CEC_ISR_TXERR', 'CEC_ISR_TXACKE', 'CEC_IER_RXBRIE',
    'CEC_IER_RXENDIE', 'CEC_IER_RXOVRIE', 'CEC_IER_BREIEIE', 'CEC_IER_SBPEIE',
    'CEC_IER_LBPEIE', 'CEC_IER_RXACKEIE', 'CEC_IER_ARBLSTIE', 'CEC_IER_TXBRIE',
    'CEC_IER_TXENDIE', 'CEC_IER_TXUDRIE', 'CEC_IER_TXERRIE', 'CEC_IER_TXACKEIE',
    'COMP_CSR_COMP1EN', 'COMP_CSR_COMP1SW1', 'COMP_CSR_COMP1MODE',
    'COMP_CSR_COMP1MODE_0', 'COMP_CSR_COMP1MODE_1', 'COMP_CSR_COMP1INSEL',
    'COMP_CSR_COMP1INSEL_0', 'COMP_CSR_COMP1INSEL_1', 'COMP_CSR_COMP1INSEL_2',
    'COMP_CSR_COMP1OUTSEL', 'COMP_CSR_COMP1OUTSEL_0', 'COMP_CSR_COMP1OUTSEL_1',
    'COMP_CSR_COMP1OUTSEL_2', 'COMP_CSR_COMP1POL', 'COMP_CSR_COMP1HYST',
    'COMP_CSR_COMP1HYST_0', 'COMP_CSR_COMP1HYST_1', 'COMP_CSR_COMP1OUT',
    'COMP_CSR_COMP1LOCK', 'COMP_CSR_COMP2EN', 'COMP_CSR_COMP2MODE',
    'COMP_CSR_COMP2MODE_0', 'COMP_CSR_COMP2MODE_1', 'COMP_CSR_COMP2INSEL',
    'COMP_CSR_COMP2INSEL_0', 'COMP_CSR_COMP2INSEL_1', 'COMP_CSR_COMP2INSEL_2',
    'COMP_CSR_WNDWEN', 'COMP_CSR_COMP2OUTSEL', 'COMP_CSR_COMP2OUTSEL_0',
    'COMP_CSR_COMP2OUTSEL_1', 'COMP_CSR_COMP2OUTSEL_2', 'COMP_CSR_COMP2POL',
    'COMP_CSR_COMP2HYST', 'COMP_CSR_COMP2HYST_0', 'COMP_CSR_COMP2HYST_1',
    'COMP_CSR_COMP2OUT', 'COMP_CSR_COMP2LOCK', 'CRC_DR_DR', 'CRC_IDR_IDR',
    'CRC_CR_RESET', 'CRC_CR_POLSIZE', 'CRC_CR_POLSIZE_0', 'CRC_CR_POLSIZE_1',
    'CRC_CR_REV_IN', 'CRC_CR_REV_IN_0', 'CRC_CR_REV_IN_1', 'CRC_CR_REV_OUT',
    'CRC_INIT_INIT', 'CRC_POL_POL', 'CRS_CR_SYNCOKIE', 'CRS_CR_SYNCWARNIE',
    'CRS_CR_ERRIE', 'CRS_CR_ESYNCIE', 'CRS_CR_CEN', 'CRS_CR_AUTOTRIMEN',
    'CRS_CR_SWSYNC', 'CRS_CR_TRIM', 'CRS_CFGR_RELOAD', 'CRS_CFGR_FELIM',
    'CRS_CFGR_SYNCDIV', 'CRS_CFGR_SYNCDIV_0', 'CRS_CFGR_SYNCDIV_1',
    'CRS_CFGR_SYNCDIV_2', 'CRS_CFGR_SYNCSRC', 'CRS_CFGR_SYNCSRC_0',
    'CRS_CFGR_SYNCSRC_1', 'CRS_CFGR_SYNCPOL', 'CRS_ISR_SYNCOKF', 'CRS_ISR_SYNCWARNF',
    'CRS_ISR_ERRF', 'CRS_ISR_ESYNCF', 'CRS_ISR_SYNCERR', 'CRS_ISR_SYNCMISS',
    'CRS_ISR_TRIMOVF', 'CRS_ISR_FEDIR', 'CRS_ISR_FECAP', 'CRS_ICR_SYNCOKC',
    'CRS_ICR_SYNCWARNC', 'CRS_ICR_ERRC', 'CRS_ICR_ESYNCC', 'DAC_CR_EN1', 'DAC_CR_BOFF1',
    'DAC_CR_TEN1', 'DAC_CR_TSEL1', 'DAC_CR_TSEL1_0', 'DAC_CR_TSEL1_1', 'DAC_CR_TSEL1_2',
    'DAC_CR_WAVE1', 'DAC_CR_WAVE1_0', 'DAC_CR_WAVE1_1', 'DAC_CR_MAMP1',
    'DAC_CR_MAMP1_0', 'DAC_CR_MAMP1_1', 'DAC_CR_MAMP1_2', 'DAC_CR_MAMP1_3',
    'DAC_CR_DMAEN1', 'DAC_CR_DMAUDRIE1', 'DAC_CR_EN2', 'DAC_CR_BOFF2', 'DAC_CR_TEN2',
    'DAC_CR_TSEL2', 'DAC_CR_TSEL2_0', 'DAC_CR_TSEL2_1', 'DAC_CR_TSEL2_2',
    'DAC_CR_WAVE2', 'DAC_CR_WAVE2_0', 'DAC_CR_WAVE2_1', 'DAC_CR_MAMP2',
    'DAC_CR_MAMP2_0', 'DAC_CR_MAMP2_1', 'DAC_CR_MAMP2_2', 'DAC_CR_MAMP2_3',
    'DAC_CR_DMAEN2', 'DAC_CR_DMAUDRIE2', 'DAC_SWTRIGR_SWTRIG1', 'DAC_SWTRIGR_SWTRIG2',
    'DAC_DHR12R1_DACC1DHR', 'DAC_DHR12L1_DACC1DHR', 'DAC_DHR8R1_DACC1DHR',
    'DAC_DOR1_DACC1DOR', 'DAC_SR_DMAUDR1', 'DAC_SR_DMAUDR2', 'DBGMCU_IDCODE_DEV_ID',
    'DBGMCU_IDCODE_REV_ID', 'DBGMCU_IDCODE_REV_ID_0', 'DBGMCU_IDCODE_REV_ID_1',
    'DBGMCU_IDCODE_REV_ID_2', 'DBGMCU_IDCODE_REV_ID_3', 'DBGMCU_IDCODE_REV_ID_4',
    'DBGMCU_IDCODE_REV_ID_5', 'DBGMCU_IDCODE_REV_ID_6', 'DBGMCU_IDCODE_REV_ID_7',
    'DBGMCU_IDCODE_REV_ID_8', 'DBGMCU_IDCODE_REV_ID_9', 'DBGMCU_IDCODE_REV_ID_10',
    'DBGMCU_IDCODE_REV_ID_11', 'DBGMCU_IDCODE_REV_ID_12', 'DBGMCU_IDCODE_REV_ID_13',
    'DBGMCU_IDCODE_REV_ID_14', 'DBGMCU_IDCODE_REV_ID_15', 'DBGMCU_CR_DBG_STOP',
    'DBGMCU_CR_DBG_STANDBY', 'DBGMCU_APB1_FZ_DBG_TIM2_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM3_STOP', 'DBGMCU_APB1_FZ_DBG_TIM6_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM7_STOP', 'DBGMCU_APB1_FZ_DBG_TIM14_STOP',
    'DBGMCU_APB1_FZ_DBG_RTC_STOP', 'DBGMCU_APB1_FZ_DBG_WWDG_STOP',
    'DBGMCU_APB1_FZ_DBG_IWDG_STOP', 'DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT',
    'DBGMCU_APB1_FZ_DBG_CAN_STOP', 'DBGMCU_APB2_FZ_DBG_TIM1_STOP',
    'DBGMCU_APB2_FZ_DBG_TIM15_STOP', 'DBGMCU_APB2_FZ_DBG_TIM16_STOP',
    'DBGMCU_APB2_FZ_DBG_TIM17_STOP', 'DMA_ISR_GIF1', 'DMA_ISR_TCIF1', 'DMA_ISR_HTIF1',
    'DMA_ISR_TEIF1', 'DMA_ISR_GIF2', 'DMA_ISR_TCIF2', 'DMA_ISR_HTIF2', 'DMA_ISR_TEIF2',
    'DMA_ISR_GIF3', 'DMA_ISR_TCIF3', 'DMA_ISR_HTIF3', 'DMA_ISR_TEIF3', 'DMA_ISR_GIF4',
    'DMA_ISR_TCIF4', 'DMA_ISR_HTIF4', 'DMA_ISR_TEIF4', 'DMA_ISR_GIF5', 'DMA_ISR_TCIF5',
    'DMA_ISR_HTIF5', 'DMA_ISR_TEIF5', 'DMA_ISR_GIF6', 'DMA_ISR_TCIF6', 'DMA_ISR_HTIF6',
    'DMA_ISR_TEIF6', 'DMA_ISR_GIF7', 'DMA_ISR_TCIF7', 'DMA_ISR_HTIF7', 'DMA_ISR_TEIF7',
    'DMA_IFCR_CGIF1', 'DMA_IFCR_CTCIF1', 'DMA_IFCR_CHTIF1', 'DMA_IFCR_CTEIF1',
    'DMA_IFCR_CGIF2', 'DMA_IFCR_CTCIF2', 'DMA_IFCR_CHTIF2', 'DMA_IFCR_CTEIF2',
    'DMA_IFCR_CGIF3', 'DMA_IFCR_CTCIF3', 'DMA_IFCR_CHTIF3', 'DMA_IFCR_CTEIF3',
    'DMA_IFCR_CGIF4', 'DMA_IFCR_CTCIF4', 'DMA_IFCR_CHTIF4', 'DMA_IFCR_CTEIF4',
    'DMA_IFCR_CGIF5', 'DMA_IFCR_CTCIF5', 'DMA_IFCR_CHTIF5', 'DMA_IFCR_CTEIF5',
    'DMA_IFCR_CGIF6', 'DMA_IFCR_CTCIF6', 'DMA_IFCR_CHTIF6', 'DMA_IFCR_CTEIF6',
    'DMA_IFCR_CGIF7', 'DMA_IFCR_CTCIF7', 'DMA_IFCR_CHTIF7', 'DMA_IFCR_CTEIF7',
    'DMA_CCR_EN', 'DMA_CCR_TCIE', 'DMA_CCR_HTIE', 'DMA_CCR_TEIE', 'DMA_CCR_DIR',
    'DMA_CCR_CIRC', 'DMA_CCR_PINC', 'DMA_CCR_MINC', 'DMA_CCR_PSIZE', 'DMA_CCR_PSIZE_0',
    'DMA_CCR_PSIZE_1', 'DMA_CCR_MSIZE', 'DMA_CCR_MSIZE_0', 'DMA_CCR_MSIZE_1',
    'DMA_CCR_PL', 'DMA_CCR_PL_0', 'DMA_CCR_PL_1', 'DMA_CCR_MEM2MEM', 'DMA_CNDTR_NDT',
    'DMA_CPAR_PA', 'DMA_CMAR_MA', 'DMA_RMPCR1_DEFAULT', 'DMA_RMPCR1_CH1_ADC',
    'DMA_RMPCR1_CH1_TIM17_CH1', 'DMA_RMPCR1_CH1_TIM17_UP', 'DMA_RMPCR1_CH1_USART1_RX',
    'DMA_RMPCR1_CH1_USART2_RX', 'DMA_RMPCR1_CH1_USART3_RX', 'DMA_RMPCR1_CH1_USART4_RX',
    'DMA_RMPCR1_CH1_USART5_RX', 'DMA_RMPCR1_CH1_USART6_RX', 'DMA_RMPCR1_CH1_USART7_RX',
    'DMA_RMPCR1_CH1_USART8_RX', 'DMA_RMPCR1_CH2_ADC', 'DMA_RMPCR1_CH2_I2C1_TX',
    'DMA_RMPCR1_CH2_SPI_1RX', 'DMA_RMPCR1_CH2_TIM1_CH1', 'DMA_RMPCR1_CH2_TIM17_CH1',
    'DMA_RMPCR1_CH2_TIM17_UP', 'DMA_RMPCR1_CH2_USART1_TX', 'DMA_RMPCR1_CH2_USART2_TX',
    'DMA_RMPCR1_CH2_USART3_TX', 'DMA_RMPCR1_CH2_USART4_TX', 'DMA_RMPCR1_CH2_USART5_TX',
    'DMA_RMPCR1_CH2_USART6_TX', 'DMA_RMPCR1_CH2_USART7_TX', 'DMA_RMPCR1_CH2_USART8_TX',
    'DMA_RMPCR1_CH3_TIM6_UP', 'DMA_RMPCR1_CH3_DAC_CH1', 'DMA_RMPCR1_CH3_I2C1_RX',
    'DMA_RMPCR1_CH3_SPI1_TX', 'DMA_RMPCR1_CH3_TIM1_CH2', 'DMA_RMPCR1_CH3_TIM2_CH2',
    'DMA_RMPCR1_CH3_TIM16_CH1', 'DMA_RMPCR1_CH3_TIM16_UP', 'DMA_RMPCR1_CH3_USART1_RX',
    'DMA_RMPCR1_CH3_USART2_RX', 'DMA_RMPCR1_CH3_USART3_RX', 'DMA_RMPCR1_CH3_USART4_RX',
    'DMA_RMPCR1_CH3_USART5_RX', 'DMA_RMPCR1_CH3_USART6_RX', 'DMA_RMPCR1_CH3_USART7_RX',
    'DMA_RMPCR1_CH3_USART8_RX', 'DMA_RMPCR1_CH4_TIM7_UP', 'DMA_RMPCR1_CH4_DAC_CH2',
    'DMA_RMPCR1_CH4_I2C2_TX', 'DMA_RMPCR1_CH4_SPI2_RX', 'DMA_RMPCR1_CH4_TIM2_CH4',
    'DMA_RMPCR1_CH4_TIM3_CH1', 'DMA_RMPCR1_CH4_TIM3_TRIG', 'DMA_RMPCR1_CH4_TIM16_CH1',
    'DMA_RMPCR1_CH4_TIM16_UP', 'DMA_RMPCR1_CH4_USART1_TX', 'DMA_RMPCR1_CH4_USART2_TX',
    'DMA_RMPCR1_CH4_USART3_TX', 'DMA_RMPCR1_CH4_USART4_TX', 'DMA_RMPCR1_CH4_USART5_TX',
    'DMA_RMPCR1_CH4_USART6_TX', 'DMA_RMPCR1_CH4_USART7_TX', 'DMA_RMPCR1_CH4_USART8_TX',
    'DMA_RMPCR1_CH5_I2C2_RX', 'DMA_RMPCR1_CH5_SPI2_TX', 'DMA_RMPCR1_CH5_TIM1_CH3',
    'DMA_RMPCR1_CH5_USART1_RX', 'DMA_RMPCR1_CH5_USART2_RX', 'DMA_RMPCR1_CH5_USART3_RX',
    'DMA_RMPCR1_CH5_USART4_RX', 'DMA_RMPCR1_CH5_USART5_RX', 'DMA_RMPCR1_CH5_USART6_RX',
    'DMA_RMPCR1_CH5_USART7_RX', 'DMA_RMPCR1_CH5_USART8_RX', 'DMA_RMPCR1_CH6_I2C1_TX',
    'DMA_RMPCR1_CH6_SPI2_RX', 'DMA_RMPCR1_CH6_TIM1_CH1', 'DMA_RMPCR1_CH6_TIM1_CH2',
    'DMA_RMPCR1_CH6_TIM1_CH3', 'DMA_RMPCR1_CH6_TIM3_CH1', 'DMA_RMPCR1_CH6_TIM3_TRIG',
    'DMA_RMPCR1_CH6_TIM16_CH1', 'DMA_RMPCR1_CH6_TIM16_UP', 'DMA_RMPCR1_CH6_USART1_RX',
    'DMA_RMPCR1_CH6_USART2_RX', 'DMA_RMPCR1_CH6_USART3_RX', 'DMA_RMPCR1_CH6_USART4_RX',
    'DMA_RMPCR1_CH6_USART5_RX', 'DMA_RMPCR1_CH6_USART6_RX', 'DMA_RMPCR1_CH6_USART7_RX',
    'DMA_RMPCR1_CH6_USART8_RX', 'DMA_RMPCR1_CH7_I2C1_RX', 'DMA_RMPCR1_CH7_SPI2_TX',
    'DMA_RMPCR1_CH7_TIM2_CH2', 'DMA_RMPCR1_CH7_TIM2_CH4', 'DMA_RMPCR1_CH7_TIM17_CH1',
    'DMA_RMPCR1_CH7_TIM17_UP', 'DMA_RMPCR1_CH7_USART1_TX', 'DMA_RMPCR1_CH7_USART2_TX',
    'DMA_RMPCR1_CH7_USART3_TX', 'DMA_RMPCR1_CH7_USART4_TX', 'DMA_RMPCR1_CH7_USART5_TX',
    'DMA_RMPCR1_CH7_USART6_TX', 'DMA_RMPCR1_CH7_USART7_TX', 'DMA_RMPCR1_CH7_USART8_TX',
    'DMA_RMPCR2_DEFAULT', 'DMA_RMPCR2_CH1_I2C2_TX', 'DMA_RMPCR2_CH1_USART1_TX',
    'DMA_RMPCR2_CH1_USART2_TX', 'DMA_RMPCR2_CH1_USART3_TX', 'DMA_RMPCR2_CH1_USART4_TX',
    'DMA_RMPCR2_CH1_USART5_TX', 'DMA_RMPCR2_CH1_USART6_TX', 'DMA_RMPCR2_CH1_USART7_TX',
    'DMA_RMPCR2_CH1_USART8_TX', 'DMA_RMPCR2_CH2_I2C2_RX', 'DMA_RMPCR2_CH2_USART1_RX',
    'DMA_RMPCR2_CH2_USART2_RX', 'DMA_RMPCR2_CH2_USART3_RX', 'DMA_RMPCR2_CH2_USART4_RX',
    'DMA_RMPCR2_CH2_USART5_RX', 'DMA_RMPCR2_CH2_USART6_RX', 'DMA_RMPCR2_CH2_USART7_RX',
    'DMA_RMPCR2_CH2_USART8_RX', 'DMA_RMPCR2_CH3_TIM6_UP', 'DMA_RMPCR2_CH3_DAC_CH1',
    'DMA_RMPCR2_CH3_SPI1_RX', 'DMA_RMPCR2_CH3_USART1_RX', 'DMA_RMPCR2_CH3_USART2_RX',
    'DMA_RMPCR2_CH3_USART3_RX', 'DMA_RMPCR2_CH3_USART4_RX', 'DMA_RMPCR2_CH3_USART5_RX',
    'DMA_RMPCR2_CH3_USART6_RX', 'DMA_RMPCR2_CH3_USART7_RX', 'DMA_RMPCR2_CH3_USART8_RX',
    'DMA_RMPCR2_CH4_TIM7_UP', 'DMA_RMPCR2_CH4_DAC_CH2', 'DMA_RMPCR2_CH4_SPI1_TX',
    'DMA_RMPCR2_CH4_USART1_TX', 'DMA_RMPCR2_CH4_USART2_TX', 'DMA_RMPCR2_CH4_USART3_TX',
    'DMA_RMPCR2_CH4_USART4_TX', 'DMA_RMPCR2_CH4_USART5_TX', 'DMA_RMPCR2_CH4_USART6_TX',
    'DMA_RMPCR2_CH4_USART7_TX', 'DMA_RMPCR2_CH4_USART8_TX', 'DMA_RMPCR2_CH5_ADC',
    'DMA_RMPCR2_CH5_USART1_TX', 'DMA_RMPCR2_CH5_USART2_TX', 'DMA_RMPCR2_CH5_USART3_TX',
    'DMA_RMPCR2_CH5_USART4_TX', 'DMA_RMPCR2_CH5_USART5_TX', 'DMA_RMPCR2_CH5_USART6_TX',
    'DMA_RMPCR2_CH5_USART7_TX', 'DMA_RMPCR2_CH5_USART8_TX', 'EXTI_IMR_MR0',
    'EXTI_IMR_MR1', 'EXTI_IMR_MR2', 'EXTI_IMR_MR3', 'EXTI_IMR_MR4', 'EXTI_IMR_MR5',
    'EXTI_IMR_MR6', 'EXTI_IMR_MR7', 'EXTI_IMR_MR8', 'EXTI_IMR_MR9', 'EXTI_IMR_MR10',
    'EXTI_IMR_MR11', 'EXTI_IMR_MR12', 'EXTI_IMR_MR13', 'EXTI_IMR_MR14', 'EXTI_IMR_MR15',
    'EXTI_IMR_MR16', 'EXTI_IMR_MR17', 'EXTI_IMR_MR18', 'EXTI_IMR_MR19', 'EXTI_IMR_MR20',
    'EXTI_IMR_MR21', 'EXTI_IMR_MR22', 'EXTI_IMR_MR23', 'EXTI_IMR_MR24', 'EXTI_IMR_MR25',
    'EXTI_IMR_MR26', 'EXTI_IMR_MR27', 'EXTI_IMR_MR28', 'EXTI_IMR_MR29', 'EXTI_IMR_MR30',
    'EXTI_IMR_MR31', 'EXTI_EMR_MR0', 'EXTI_EMR_MR1', 'EXTI_EMR_MR2', 'EXTI_EMR_MR3',
    'EXTI_EMR_MR4', 'EXTI_EMR_MR5', 'EXTI_EMR_MR6', 'EXTI_EMR_MR7', 'EXTI_EMR_MR8',
    'EXTI_EMR_MR9', 'EXTI_EMR_MR10', 'EXTI_EMR_MR11', 'EXTI_EMR_MR12', 'EXTI_EMR_MR13',
    'EXTI_EMR_MR14', 'EXTI_EMR_MR15', 'EXTI_EMR_MR16', 'EXTI_EMR_MR17', 'EXTI_EMR_MR18',
    'EXTI_EMR_MR19', 'EXTI_EMR_MR20', 'EXTI_EMR_MR21', 'EXTI_EMR_MR22', 'EXTI_EMR_MR23',
    'EXTI_EMR_MR24', 'EXTI_EMR_MR25', 'EXTI_EMR_MR26', 'EXTI_EMR_MR27', 'EXTI_EMR_MR28',
    'EXTI_EMR_MR29', 'EXTI_EMR_MR30', 'EXTI_EMR_MR31', 'EXTI_RTSR_TR0', 'EXTI_RTSR_TR1',
    'EXTI_RTSR_TR2', 'EXTI_RTSR_TR3', 'EXTI_RTSR_TR4', 'EXTI_RTSR_TR5', 'EXTI_RTSR_TR6',
    'EXTI_RTSR_TR7', 'EXTI_RTSR_TR8', 'EXTI_RTSR_TR9', 'EXTI_RTSR_TR10',
    'EXTI_RTSR_TR11', 'EXTI_RTSR_TR12', 'EXTI_RTSR_TR13', 'EXTI_RTSR_TR14',
    'EXTI_RTSR_TR15', 'EXTI_RTSR_TR16', 'EXTI_RTSR_TR17', 'EXTI_RTSR_TR19',
    'EXTI_RTSR_TR20', 'EXTI_RTSR_TR21', 'EXTI_RTSR_TR22', 'EXTI_FTSR_TR0',
    'EXTI_FTSR_TR1', 'EXTI_FTSR_TR2', 'EXTI_FTSR_TR3', 'EXTI_FTSR_TR4', 'EXTI_FTSR_TR5',
    'EXTI_FTSR_TR6', 'EXTI_FTSR_TR7', 'EXTI_FTSR_TR8', 'EXTI_FTSR_TR9',
    'EXTI_FTSR_TR10', 'EXTI_FTSR_TR11', 'EXTI_FTSR_TR12', 'EXTI_FTSR_TR13',
    'EXTI_FTSR_TR14', 'EXTI_FTSR_TR15', 'EXTI_FTSR_TR16', 'EXTI_FTSR_TR17',
    'EXTI_FTSR_TR19', 'EXTI_FTSR_TR20', 'EXTI_FTSR_TR21', 'EXTI_FTSR_TR22',
    'EXTI_SWIER_SWIER0', 'EXTI_SWIER_SWIER1', 'EXTI_SWIER_SWIER2', 'EXTI_SWIER_SWIER3',
    'EXTI_SWIER_SWIER4', 'EXTI_SWIER_SWIER5', 'EXTI_SWIER_SWIER6', 'EXTI_SWIER_SWIER7',
    'EXTI_SWIER_SWIER8', 'EXTI_SWIER_SWIER9', 'EXTI_SWIER_SWIER10',
    'EXTI_SWIER_SWIER11', 'EXTI_SWIER_SWIER12', 'EXTI_SWIER_SWIER13',
    'EXTI_SWIER_SWIER14', 'EXTI_SWIER_SWIER15', 'EXTI_SWIER_SWIER16',
    'EXTI_SWIER_SWIER17', 'EXTI_SWIER_SWIER19', 'EXTI_SWIER_SWIER20',
    'EXTI_SWIER_SWIER21', 'EXTI_SWIER_SWIER22', 'EXTI_PR_PR0', 'EXTI_PR_PR1',
    'EXTI_PR_PR2', 'EXTI_PR_PR3', 'EXTI_PR_PR4', 'EXTI_PR_PR5', 'EXTI_PR_PR6',
    'EXTI_PR_PR7', 'EXTI_PR_PR8', 'EXTI_PR_PR9', 'EXTI_PR_PR10', 'EXTI_PR_PR11',
    'EXTI_PR_PR12', 'EXTI_PR_PR13', 'EXTI_PR_PR14', 'EXTI_PR_PR15', 'EXTI_PR_PR16',
    'EXTI_PR_PR17', 'EXTI_PR_PR19', 'EXTI_PR_PR20', 'EXTI_PR_PR21', 'EXTI_PR_PR22',
    'FLASH_ACR_LATENCY', 'FLASH_ACR_PRFTBE', 'FLASH_ACR_PRFTBS', 'FLASH_KEYR_FKEYR',
    'FLASH_OPTKEYR_OPTKEYR', 'FLASH_FKEY1', 'FLASH_FKEY2', 'FLASH_OPTKEY1',
    'FLASH_OPTKEY2', 'FLASH_SR_BSY', 'FLASH_SR_PGERR', 'FLASH_SR_WRPRTERR',
    'FLASH_SR_EOP', 'FLASH_SR_WRPERR', 'FLASH_CR_PG', 'FLASH_CR_PER', 'FLASH_CR_MER',
    'FLASH_CR_OPTPG', 'FLASH_CR_OPTER', 'FLASH_CR_STRT', 'FLASH_CR_LOCK',
    'FLASH_CR_OPTWRE', 'FLASH_CR_ERRIE', 'FLASH_CR_EOPIE', 'FLASH_CR_OBL_LAUNCH',
    'FLASH_AR_FAR', 'FLASH_OBR_OPTERR', 'FLASH_OBR_RDPRT1', 'FLASH_OBR_RDPRT2',
    'FLASH_OBR_USER', 'FLASH_OBR_IWDG_SW', 'FLASH_OBR_nRST_STOP',
    'FLASH_OBR_nRST_STDBY', 'FLASH_OBR_nBOOT0', 'FLASH_OBR_nBOOT1',
    'FLASH_OBR_VDDA_MONITOR', 'FLASH_OBR_RAM_PARITY_CHECK', 'FLASH_OBR_nBOOT0_SW',
    'FLASH_OBR_DATA0', 'FLASH_OBR_DATA1', 'FLASH_OBR_BOOT1', 'FLASH_OBR_VDDA_ANALOG',
    'FLASH_WRPR_WRP', 'OB_RDP_RDP', 'OB_RDP_nRDP', 'OB_USER_USER', 'OB_USER_nUSER',
    'OB_WRP0_WRP0', 'OB_WRP0_nWRP0', 'OB_WRP1_WRP1', 'OB_WRP1_nWRP1', 'OB_WRP2_WRP2',
    'OB_WRP2_nWRP2', 'OB_WRP3_WRP3', 'OB_WRP3_nWRP3', 'GPIO_MODER_MODER0',
    'GPIO_MODER_MODER0_0', 'GPIO_MODER_MODER0_1', 'GPIO_MODER_MODER1',
    'GPIO_MODER_MODER1_0', 'GPIO_MODER_MODER1_1', 'GPIO_MODER_MODER2',
    'GPIO_MODER_MODER2_0', 'GPIO_MODER_MODER2_1', 'GPIO_MODER_MODER3',
    'GPIO_MODER_MODER3_0', 'GPIO_MODER_MODER3_1', 'GPIO_MODER_MODER4',
    'GPIO_MODER_MODER4_0', 'GPIO_MODER_MODER4_1', 'GPIO_MODER_MODER5',
    'GPIO_MODER_MODER5_0', 'GPIO_MODER_MODER5_1', 'GPIO_MODER_MODER6',
    'GPIO_MODER_MODER6_0', 'GPIO_MODER_MODER6_1', 'GPIO_MODER_MODER7',
    'GPIO_MODER_MODER7_0', 'GPIO_MODER_MODER7_1', 'GPIO_MODER_MODER8',
    'GPIO_MODER_MODER8_0', 'GPIO_MODER_MODER8_1', 'GPIO_MODER_MODER9',
    'GPIO_MODER_MODER9_0', 'GPIO_MODER_MODER9_1', 'GPIO_MODER_MODER10',
    'GPIO_MODER_MODER10_0', 'GPIO_MODER_MODER10_1', 'GPIO_MODER_MODER11',
    'GPIO_MODER_MODER11_0', 'GPIO_MODER_MODER11_1', 'GPIO_MODER_MODER12',
    'GPIO_MODER_MODER12_0', 'GPIO_MODER_MODER12_1', 'GPIO_MODER_MODER13',
    'GPIO_MODER_MODER13_0', 'GPIO_MODER_MODER13_1', 'GPIO_MODER_MODER14',
    'GPIO_MODER_MODER14_0', 'GPIO_MODER_MODER14_1', 'GPIO_MODER_MODER15',
    'GPIO_MODER_MODER15_0', 'GPIO_MODER_MODER15_1', 'GPIO_OTYPER_OT_0',
    'GPIO_OTYPER_OT_1', 'GPIO_OTYPER_OT_2', 'GPIO_OTYPER_OT_3', 'GPIO_OTYPER_OT_4',
    'GPIO_OTYPER_OT_5', 'GPIO_OTYPER_OT_6', 'GPIO_OTYPER_OT_7', 'GPIO_OTYPER_OT_8',
    'GPIO_OTYPER_OT_9', 'GPIO_OTYPER_OT_10', 'GPIO_OTYPER_OT_11', 'GPIO_OTYPER_OT_12',
    'GPIO_OTYPER_OT_13', 'GPIO_OTYPER_OT_14', 'GPIO_OTYPER_OT_15',
    'GPIO_OSPEEDR_OSPEEDR0', 'GPIO_OSPEEDR_OSPEEDR0_0', 'GPIO_OSPEEDR_OSPEEDR0_1',
    'GPIO_OSPEEDR_OSPEEDR1', 'GPIO_OSPEEDR_OSPEEDR1_0', 'GPIO_OSPEEDR_OSPEEDR1_1',
    'GPIO_OSPEEDR_OSPEEDR2', 'GPIO_OSPEEDR_OSPEEDR2_0', 'GPIO_OSPEEDR_OSPEEDR2_1',
    'GPIO_OSPEEDR_OSPEEDR3', 'GPIO_OSPEEDR_OSPEEDR3_0', 'GPIO_OSPEEDR_OSPEEDR3_1',
    'GPIO_OSPEEDR_OSPEEDR4', 'GPIO_OSPEEDR_OSPEEDR4_0', 'GPIO_OSPEEDR_OSPEEDR4_1',
    'GPIO_OSPEEDR_OSPEEDR5', 'GPIO_OSPEEDR_OSPEEDR5_0', 'GPIO_OSPEEDR_OSPEEDR5_1',
    'GPIO_OSPEEDR_OSPEEDR6', 'GPIO_OSPEEDR_OSPEEDR6_0', 'GPIO_OSPEEDR_OSPEEDR6_1',
    'GPIO_OSPEEDR_OSPEEDR7', 'GPIO_OSPEEDR_OSPEEDR7_0', 'GPIO_OSPEEDR_OSPEEDR7_1',
    'GPIO_OSPEEDR_OSPEEDR8', 'GPIO_OSPEEDR_OSPEEDR8_0', 'GPIO_OSPEEDR_OSPEEDR8_1',
    'GPIO_OSPEEDR_OSPEEDR9', 'GPIO_OSPEEDR_OSPEEDR9_0', 'GPIO_OSPEEDR_OSPEEDR9_1',
    'GPIO_OSPEEDR_OSPEEDR10', 'GPIO_OSPEEDR_OSPEEDR10_0', 'GPIO_OSPEEDR_OSPEEDR10_1',
    'GPIO_OSPEEDR_OSPEEDR11', 'GPIO_OSPEEDR_OSPEEDR11_0', 'GPIO_OSPEEDR_OSPEEDR11_1',
    'GPIO_OSPEEDR_OSPEEDR12', 'GPIO_OSPEEDR_OSPEEDR12_0', 'GPIO_OSPEEDR_OSPEEDR12_1',
    'GPIO_OSPEEDR_OSPEEDR13', 'GPIO_OSPEEDR_OSPEEDR13_0', 'GPIO_OSPEEDR_OSPEEDR13_1',
    'GPIO_OSPEEDR_OSPEEDR14', 'GPIO_OSPEEDR_OSPEEDR14_0', 'GPIO_OSPEEDR_OSPEEDR14_1',
    'GPIO_OSPEEDR_OSPEEDR15', 'GPIO_OSPEEDR_OSPEEDR15_0', 'GPIO_OSPEEDR_OSPEEDR15_1',
    'GPIO_OSPEEDER_OSPEEDR0', 'GPIO_OSPEEDER_OSPEEDR0_0', 'GPIO_OSPEEDER_OSPEEDR0_1',
    'GPIO_OSPEEDER_OSPEEDR1', 'GPIO_OSPEEDER_OSPEEDR1_0', 'GPIO_OSPEEDER_OSPEEDR1_1',
    'GPIO_OSPEEDER_OSPEEDR2', 'GPIO_OSPEEDER_OSPEEDR2_0', 'GPIO_OSPEEDER_OSPEEDR2_1',
    'GPIO_OSPEEDER_OSPEEDR3', 'GPIO_OSPEEDER_OSPEEDR3_0', 'GPIO_OSPEEDER_OSPEEDR3_1',
    'GPIO_OSPEEDER_OSPEEDR4', 'GPIO_OSPEEDER_OSPEEDR4_0', 'GPIO_OSPEEDER_OSPEEDR4_1',
    'GPIO_OSPEEDER_OSPEEDR5', 'GPIO_OSPEEDER_OSPEEDR5_0', 'GPIO_OSPEEDER_OSPEEDR5_1',
    'GPIO_OSPEEDER_OSPEEDR6', 'GPIO_OSPEEDER_OSPEEDR6_0', 'GPIO_OSPEEDER_OSPEEDR6_1',
    'GPIO_OSPEEDER_OSPEEDR7', 'GPIO_OSPEEDER_OSPEEDR7_0', 'GPIO_OSPEEDER_OSPEEDR7_1',
    'GPIO_OSPEEDER_OSPEEDR8', 'GPIO_OSPEEDER_OSPEEDR8_0', 'GPIO_OSPEEDER_OSPEEDR8_1',
    'GPIO_OSPEEDER_OSPEEDR9', 'GPIO_OSPEEDER_OSPEEDR9_0', 'GPIO_OSPEEDER_OSPEEDR9_1',
    'GPIO_OSPEEDER_OSPEEDR10', 'GPIO_OSPEEDER_OSPEEDR10_0', 'GPIO_OSPEEDER_OSPEEDR10_1',
    'GPIO_OSPEEDER_OSPEEDR11', 'GPIO_OSPEEDER_OSPEEDR11_0', 'GPIO_OSPEEDER_OSPEEDR11_1',
    'GPIO_OSPEEDER_OSPEEDR12', 'GPIO_OSPEEDER_OSPEEDR12_0', 'GPIO_OSPEEDER_OSPEEDR12_1',
    'GPIO_OSPEEDER_OSPEEDR13', 'GPIO_OSPEEDER_OSPEEDR13_0', 'GPIO_OSPEEDER_OSPEEDR13_1',
    'GPIO_OSPEEDER_OSPEEDR14', 'GPIO_OSPEEDER_OSPEEDR14_0', 'GPIO_OSPEEDER_OSPEEDR14_1',
    'GPIO_OSPEEDER_OSPEEDR15', 'GPIO_OSPEEDER_OSPEEDR15_0', 'GPIO_OSPEEDER_OSPEEDR15_1',
    'GPIO_PUPDR_PUPDR0', 'GPIO_PUPDR_PUPDR0_0', 'GPIO_PUPDR_PUPDR0_1',
    'GPIO_PUPDR_PUPDR1', 'GPIO_PUPDR_PUPDR1_0', 'GPIO_PUPDR_PUPDR1_1',
    'GPIO_PUPDR_PUPDR2', 'GPIO_PUPDR_PUPDR2_0', 'GPIO_PUPDR_PUPDR2_1',
    'GPIO_PUPDR_PUPDR3', 'GPIO_PUPDR_PUPDR3_0', 'GPIO_PUPDR_PUPDR3_1',
    'GPIO_PUPDR_PUPDR4', 'GPIO_PUPDR_PUPDR4_0', 'GPIO_PUPDR_PUPDR4_1',
    'GPIO_PUPDR_PUPDR5', 'GPIO_PUPDR_PUPDR5_0', 'GPIO_PUPDR_PUPDR5_1',
    'GPIO_PUPDR_PUPDR6', 'GPIO_PUPDR_PUPDR6_0', 'GPIO_PUPDR_PUPDR6_1',
    'GPIO_PUPDR_PUPDR7', 'GPIO_PUPDR_PUPDR7_0', 'GPIO_PUPDR_PUPDR7_1',
    'GPIO_PUPDR_PUPDR8', 'GPIO_PUPDR_PUPDR8_0', 'GPIO_PUPDR_PUPDR8_1',
    'GPIO_PUPDR_PUPDR9', 'GPIO_PUPDR_PUPDR9_0', 'GPIO_PUPDR_PUPDR9_1',
    'GPIO_PUPDR_PUPDR10', 'GPIO_PUPDR_PUPDR10_0', 'GPIO_PUPDR_PUPDR10_1',
    'GPIO_PUPDR_PUPDR11', 'GPIO_PUPDR_PUPDR11_0', 'GPIO_PUPDR_PUPDR11_1',
    'GPIO_PUPDR_PUPDR12', 'GPIO_PUPDR_PUPDR12_0', 'GPIO_PUPDR_PUPDR12_1',
    'GPIO_PUPDR_PUPDR13', 'GPIO_PUPDR_PUPDR13_0', 'GPIO_PUPDR_PUPDR13_1',
    'GPIO_PUPDR_PUPDR14', 'GPIO_PUPDR_PUPDR14_0', 'GPIO_PUPDR_PUPDR14_1',
    'GPIO_PUPDR_PUPDR15', 'GPIO_PUPDR_PUPDR15_0', 'GPIO_PUPDR_PUPDR15_1', 'GPIO_IDR_0',
    'GPIO_IDR_1', 'GPIO_IDR_2', 'GPIO_IDR_3', 'GPIO_IDR_4', 'GPIO_IDR_5', 'GPIO_IDR_6',
    'GPIO_IDR_7', 'GPIO_IDR_8', 'GPIO_IDR_9', 'GPIO_IDR_10', 'GPIO_IDR_11',
    'GPIO_IDR_12', 'GPIO_IDR_13', 'GPIO_IDR_14', 'GPIO_IDR_15', 'GPIO_ODR_0',
    'GPIO_ODR_1', 'GPIO_ODR_2', 'GPIO_ODR_3', 'GPIO_ODR_4', 'GPIO_ODR_5', 'GPIO_ODR_6',
    'GPIO_ODR_7', 'GPIO_ODR_8', 'GPIO_ODR_9', 'GPIO_ODR_10', 'GPIO_ODR_11',
    'GPIO_ODR_12', 'GPIO_ODR_13', 'GPIO_ODR_14', 'GPIO_ODR_15', 'GPIO_BSRR_BS_0',
    'GPIO_BSRR_BS_1', 'GPIO_BSRR_BS_2', 'GPIO_BSRR_BS_3', 'GPIO_BSRR_BS_4',
    'GPIO_BSRR_BS_5', 'GPIO_BSRR_BS_6', 'GPIO_BSRR_BS_7', 'GPIO_BSRR_BS_8',
    'GPIO_BSRR_BS_9', 'GPIO_BSRR_BS_10', 'GPIO_BSRR_BS_11', 'GPIO_BSRR_BS_12',
    'GPIO_BSRR_BS_13', 'GPIO_BSRR_BS_14', 'GPIO_BSRR_BS_15', 'GPIO_BSRR_BR_0',
    'GPIO_BSRR_BR_1', 'GPIO_BSRR_BR_2', 'GPIO_BSRR_BR_3', 'GPIO_BSRR_BR_4',
    'GPIO_BSRR_BR_5', 'GPIO_BSRR_BR_6', 'GPIO_BSRR_BR_7', 'GPIO_BSRR_BR_8',
    'GPIO_BSRR_BR_9', 'GPIO_BSRR_BR_10', 'GPIO_BSRR_BR_11', 'GPIO_BSRR_BR_12',
    'GPIO_BSRR_BR_13', 'GPIO_BSRR_BR_14', 'GPIO_BSRR_BR_15', 'GPIO_LCKR_LCK0',
    'GPIO_LCKR_LCK1', 'GPIO_LCKR_LCK2', 'GPIO_LCKR_LCK3', 'GPIO_LCKR_LCK4',
    'GPIO_LCKR_LCK5', 'GPIO_LCKR_LCK6', 'GPIO_LCKR_LCK7', 'GPIO_LCKR_LCK8',
    'GPIO_LCKR_LCK9', 'GPIO_LCKR_LCK10', 'GPIO_LCKR_LCK11', 'GPIO_LCKR_LCK12',
    'GPIO_LCKR_LCK13', 'GPIO_LCKR_LCK14', 'GPIO_LCKR_LCK15', 'GPIO_LCKR_LCKK',
    'GPIO_AFRL_AFR0', 'GPIO_AFRL_AFR1', 'GPIO_AFRL_AFR2', 'GPIO_AFRL_AFR3',
    'GPIO_AFRL_AFR4', 'GPIO_AFRL_AFR5', 'GPIO_AFRL_AFR6', 'GPIO_AFRL_AFR7',
    'GPIO_AFRH_AFR8', 'GPIO_AFRH_AFR9', 'GPIO_AFRH_AFR10', 'GPIO_AFRH_AFR11',
    'GPIO_AFRH_AFR12', 'GPIO_AFRH_AFR13', 'GPIO_AFRH_AFR14', 'GPIO_AFRH_AFR15',
    'GPIO_AFRL_AFRL0', 'GPIO_AFRL_AFRL1', 'GPIO_AFRL_AFRL2', 'GPIO_AFRL_AFRL3',
    'GPIO_AFRL_AFRL4', 'GPIO_AFRL_AFRL5', 'GPIO_AFRL_AFRL6', 'GPIO_AFRL_AFRL7',
    'GPIO_AFRH_AFRH0', 'GPIO_AFRH_AFRH1', 'GPIO_AFRH_AFRH2', 'GPIO_AFRH_AFRH3',
    'GPIO_AFRH_AFRH4', 'GPIO_AFRH_AFRH5', 'GPIO_AFRH_AFRH6', 'GPIO_AFRH_AFRH7',
    'GPIO_BRR_BR_0', 'GPIO_BRR_BR_1', 'GPIO_BRR_BR_2', 'GPIO_BRR_BR_3', 'GPIO_BRR_BR_4',
    'GPIO_BRR_BR_5', 'GPIO_BRR_BR_6', 'GPIO_BRR_BR_7', 'GPIO_BRR_BR_8', 'GPIO_BRR_BR_9',
    'GPIO_BRR_BR_10', 'GPIO_BRR_BR_11', 'GPIO_BRR_BR_12', 'GPIO_BRR_BR_13',
    'GPIO_BRR_BR_14', 'GPIO_BRR_BR_15', 'I2C_CR1_PE', 'I2C_CR1_TXIE', 'I2C_CR1_RXIE',
    'I2C_CR1_ADDRIE', 'I2C_CR1_NACKIE', 'I2C_CR1_STOPIE', 'I2C_CR1_TCIE',
    'I2C_CR1_ERRIE', 'I2C_CR1_DFN', 'I2C_CR1_ANFOFF', 'I2C_CR1_SWRST',
    'I2C_CR1_TXDMAEN', 'I2C_CR1_RXDMAEN', 'I2C_CR1_SBC', 'I2C_CR1_NOSTRETCH',
    'I2C_CR1_WUPEN', 'I2C_CR1_GCEN', 'I2C_CR1_SMBHEN', 'I2C_CR1_SMBDEN',
    'I2C_CR1_ALERTEN', 'I2C_CR1_PECEN', 'I2C_CR2_SADD', 'I2C_CR2_RD_WRN',
    'I2C_CR2_ADD10', 'I2C_CR2_HEAD10R', 'I2C_CR2_START', 'I2C_CR2_STOP', 'I2C_CR2_NACK',
    'I2C_CR2_NBYTES', 'I2C_CR2_RELOAD', 'I2C_CR2_AUTOEND', 'I2C_CR2_PECBYTE',
    'I2C_OAR1_OA1', 'I2C_OAR1_OA1MODE', 'I2C_OAR1_OA1EN', 'I2C_OAR2_OA2',
    'I2C_OAR2_OA2MSK', 'I2C_OAR2_OA2EN', 'I2C_TIMINGR_SCLL', 'I2C_TIMINGR_SCLH',
    'I2C_TIMINGR_SDADEL', 'I2C_TIMINGR_SCLDEL', 'I2C_TIMINGR_PRESC',
    'I2C_TIMEOUTR_TIMEOUTA', 'I2C_TIMEOUTR_TIDLE', 'I2C_TIMEOUTR_TIMOUTEN',
    'I2C_TIMEOUTR_TIMEOUTB', 'I2C_TIMEOUTR_TEXTEN', 'I2C_ISR_TXE', 'I2C_ISR_TXIS',
    'I2C_ISR_RXNE', 'I2C_ISR_ADDR', 'I2C_ISR_NACKF', 'I2C_ISR_STOPF', 'I2C_ISR_TC',
    'I2C_ISR_TCR', 'I2C_ISR_BERR', 'I2C_ISR_ARLO', 'I2C_ISR_OVR', 'I2C_ISR_PECERR',
    'I2C_ISR_TIMEOUT', 'I2C_ISR_ALERT', 'I2C_ISR_BUSY', 'I2C_ISR_DIR',
    'I2C_ISR_ADDCODE', 'I2C_ICR_ADDRCF', 'I2C_ICR_NACKCF', 'I2C_ICR_STOPCF',
    'I2C_ICR_BERRCF', 'I2C_ICR_ARLOCF', 'I2C_ICR_OVRCF', 'I2C_ICR_PECCF',
    'I2C_ICR_TIMOUTCF', 'I2C_ICR_ALERTCF', 'I2C_PECR_PEC', 'I2C_RXDR_RXDATA',
    'I2C_TXDR_TXDATA', 'IWDG_KR_KEY', 'IWDG_PR_PR', 'IWDG_PR_PR_0', 'IWDG_PR_PR_1',
    'IWDG_PR_PR_2', 'IWDG_RLR_RL', 'IWDG_SR_PVU', 'IWDG_SR_RVU', 'IWDG_SR_WVU',
    'IWDG_WINR_WIN', 'PWR_CR_LPDS', 'PWR_CR_PDDS', 'PWR_CR_CWUF', 'PWR_CR_CSBF',
    'PWR_CR_PVDE', 'PWR_CR_PLS', 'PWR_CR_PLS_0', 'PWR_CR_PLS_1', 'PWR_CR_PLS_2',
    'PWR_CR_PLS_LEV0', 'PWR_CR_PLS_LEV1', 'PWR_CR_PLS_LEV2', 'PWR_CR_PLS_LEV3',
    'PWR_CR_PLS_LEV4', 'PWR_CR_PLS_LEV5', 'PWR_CR_PLS_LEV6', 'PWR_CR_PLS_LEV7',
    'PWR_CR_DBP', 'PWR_CR_LPSDSR', 'PWR_CSR_WUF', 'PWR_CSR_SBF', 'PWR_CSR_PVDO',
    'PWR_CSR_VREFINTRDY', 'PWR_CSR_EWUP1', 'PWR_CSR_EWUP2', 'PWR_CSR_EWUP3',
    'PWR_CSR_EWUP4', 'PWR_CSR_EWUP5', 'PWR_CSR_EWUP6', 'PWR_CSR_EWUP7', 'PWR_CSR_EWUP8',
    'PWR_CSR_VREFINTRDYF', 'RCC_CR_HSION', 'RCC_CR_HSIRDY', 'RCC_CR_HSITRIM',
    'RCC_CR_HSICAL', 'RCC_CR_HSEON', 'RCC_CR_HSERDY', 'RCC_CR_HSEBYP', 'RCC_CR_CSSON',
    'RCC_CR_PLLON', 'RCC_CR_PLLRDY', 'RCC_CFGR_SW', 'RCC_CFGR_SW_0', 'RCC_CFGR_SW_1',
    'RCC_CFGR_SW_HSI', 'RCC_CFGR_SW_HSE', 'RCC_CFGR_SW_PLL', 'RCC_CFGR_SW_HSI48',
    'RCC_CFGR_SWS', 'RCC_CFGR_SWS_0', 'RCC_CFGR_SWS_1', 'RCC_CFGR_SWS_HSI',
    'RCC_CFGR_SWS_HSE', 'RCC_CFGR_SWS_PLL', 'RCC_CFGR_SWS_HSI48', 'RCC_CFGR_HPRE',
    'RCC_CFGR_HPRE_0', 'RCC_CFGR_HPRE_1', 'RCC_CFGR_HPRE_2', 'RCC_CFGR_HPRE_3',
    'RCC_CFGR_HPRE_DIV1', 'RCC_CFGR_HPRE_DIV2', 'RCC_CFGR_HPRE_DIV4',
    'RCC_CFGR_HPRE_DIV8', 'RCC_CFGR_HPRE_DIV16', 'RCC_CFGR_HPRE_DIV64',
    'RCC_CFGR_HPRE_DIV128', 'RCC_CFGR_HPRE_DIV256', 'RCC_CFGR_HPRE_DIV512',
    'RCC_CFGR_PPRE', 'RCC_CFGR_PPRE_0', 'RCC_CFGR_PPRE_1', 'RCC_CFGR_PPRE_2',
    'RCC_CFGR_PPRE_DIV1', 'RCC_CFGR_PPRE_DIV2', 'RCC_CFGR_PPRE_DIV4',
    'RCC_CFGR_PPRE_DIV8', 'RCC_CFGR_PPRE_DIV16', 'RCC_CFGR_ADCPRE', 'RCC_CFGR_PLLSRC',
    'RCC_CFGR_PLLSRC_0', 'RCC_CFGR_PLLSRC_1', 'RCC_CFGR_PLLSRC_PREDIV1',
    'RCC_CFGR_PLLSRC_HSI_DIV2', 'RCC_CFGR_PLLSRC_HSI_PREDIV',
    'RCC_CFGR_PLLSRC_HSE_PREDIV', 'RCC_CFGR_PLLSRC_HSI48_PREDIV', 'RCC_CFGR_PLLXTPRE',
    'RCC_CFGR_PLLXTPRE_PREDIV1', 'RCC_CFGR_PLLXTPRE_PREDIV1_Div2',
    'RCC_CFGR_PLLSRC_HSI_Div2', 'RCC_CFGR_PLLMUL', 'RCC_CFGR_PLLMUL_0',
    'RCC_CFGR_PLLMUL_1', 'RCC_CFGR_PLLMUL_2', 'RCC_CFGR_PLLMUL_3', 'RCC_CFGR_PLLMUL2',
    'RCC_CFGR_PLLMUL3', 'RCC_CFGR_PLLMUL4', 'RCC_CFGR_PLLMUL5', 'RCC_CFGR_PLLMUL6',
    'RCC_CFGR_PLLMUL7', 'RCC_CFGR_PLLMUL8', 'RCC_CFGR_PLLMUL9', 'RCC_CFGR_PLLMUL10',
    'RCC_CFGR_PLLMUL11', 'RCC_CFGR_PLLMUL12', 'RCC_CFGR_PLLMUL13', 'RCC_CFGR_PLLMUL14',
    'RCC_CFGR_PLLMUL15', 'RCC_CFGR_PLLMUL16', 'RCC_CFGR_PLLMULL', 'RCC_CFGR_PLLMULL_0',
    'RCC_CFGR_PLLMULL_1', 'RCC_CFGR_PLLMULL_2', 'RCC_CFGR_PLLMULL_3',
    'RCC_CFGR_PLLMULL2', 'RCC_CFGR_PLLMULL3', 'RCC_CFGR_PLLMULL4', 'RCC_CFGR_PLLMULL5',
    'RCC_CFGR_PLLMULL6', 'RCC_CFGR_PLLMULL7', 'RCC_CFGR_PLLMULL8', 'RCC_CFGR_PLLMULL9',
    'RCC_CFGR_PLLMULL10', 'RCC_CFGR_PLLMULL11', 'RCC_CFGR_PLLMULL12',
    'RCC_CFGR_PLLMULL13', 'RCC_CFGR_PLLMULL14', 'RCC_CFGR_PLLMULL15',
    'RCC_CFGR_PLLMULL16', 'RCC_CFGR_MCO', 'RCC_CFGR_MCO_0', 'RCC_CFGR_MCO_1',
    'RCC_CFGR_MCO_2', 'RCC_CFGR_MCO_3', 'RCC_CFGR_MCO_NOCLOCK', 'RCC_CFGR_MCO_HSI14',
    'RCC_CFGR_MCO_LSI', 'RCC_CFGR_MCO_LSE', 'RCC_CFGR_MCO_SYSCLK', 'RCC_CFGR_MCO_HSI',
    'RCC_CFGR_MCO_HSE', 'RCC_CFGR_MCO_PLL', 'RCC_CFGR_MCO_HSI48', 'RCC_CFGR_MCO_PRE',
    'RCC_CFGR_MCO_PRE_1', 'RCC_CFGR_MCO_PRE_2', 'RCC_CFGR_MCO_PRE_4',
    'RCC_CFGR_MCO_PRE_8', 'RCC_CFGR_MCO_PRE_16', 'RCC_CFGR_MCO_PRE_32',
    'RCC_CFGR_MCO_PRE_64', 'RCC_CFGR_MCO_PRE_128', 'RCC_CFGR_PLLNODIV',
    'RCC_CIR_LSIRDYF', 'RCC_CIR_LSERDYF', 'RCC_CIR_HSIRDYF', 'RCC_CIR_HSERDYF',
    'RCC_CIR_PLLRDYF', 'RCC_CIR_HSI14RDYF', 'RCC_CIR_HSI48RDYF', 'RCC_CIR_CSSF',
    'RCC_CIR_LSIRDYIE', 'RCC_CIR_LSERDYIE', 'RCC_CIR_HSIRDYIE', 'RCC_CIR_HSERDYIE',
    'RCC_CIR_PLLRDYIE', 'RCC_CIR_HSI14RDYIE', 'RCC_CIR_HSI48RDYIE', 'RCC_CIR_LSIRDYC',
    'RCC_CIR_LSERDYC', 'RCC_CIR_HSIRDYC', 'RCC_CIR_HSERDYC', 'RCC_CIR_PLLRDYC',
    'RCC_CIR_HSI14RDYC', 'RCC_CIR_HSI48RDYC', 'RCC_CIR_CSSC', 'RCC_APB2RSTR_SYSCFGRST',
    'RCC_APB2RSTR_ADCRST', 'RCC_APB2RSTR_USART8RST', 'RCC_APB2RSTR_USART7RST',
    'RCC_APB2RSTR_USART6RST', 'RCC_APB2RSTR_TIM1RST', 'RCC_APB2RSTR_SPI1RST',
    'RCC_APB2RSTR_USART1RST', 'RCC_APB2RSTR_TIM15RST', 'RCC_APB2RSTR_TIM16RST',
    'RCC_APB2RSTR_TIM17RST', 'RCC_APB2RSTR_DBGMCURST', 'RCC_APB2RSTR_ADC1RST',
    'RCC_APB1RSTR_TIM2RST', 'RCC_APB1RSTR_TIM3RST', 'RCC_APB1RSTR_TIM6RST',
    'RCC_APB1RSTR_TIM7RST', 'RCC_APB1RSTR_TIM14RST', 'RCC_APB1RSTR_WWDGRST',
    'RCC_APB1RSTR_SPI2RST', 'RCC_APB1RSTR_USART2RST', 'RCC_APB1RSTR_USART3RST',
    'RCC_APB1RSTR_USART4RST', 'RCC_APB1RSTR_USART5RST', 'RCC_APB1RSTR_I2C1RST',
    'RCC_APB1RSTR_I2C2RST', 'RCC_APB1RSTR_USBRST', 'RCC_APB1RSTR_CANRST',
    'RCC_APB1RSTR_CRSRST', 'RCC_APB1RSTR_PWRRST', 'RCC_APB1RSTR_DACRST',
    'RCC_APB1RSTR_CECRST', 'RCC_AHBENR_DMAEN', 'RCC_AHBENR_DMA2EN', 'RCC_AHBENR_SRAMEN',
    'RCC_AHBENR_FLITFEN', 'RCC_AHBENR_CRCEN', 'RCC_AHBENR_GPIOAEN',
    'RCC_AHBENR_GPIOBEN', 'RCC_AHBENR_GPIOCEN', 'RCC_AHBENR_GPIODEN',
    'RCC_AHBENR_GPIOEEN', 'RCC_AHBENR_GPIOFEN', 'RCC_AHBENR_TSCEN', 'RCC_AHBENR_DMA1EN',
    'RCC_AHBENR_TSEN', 'RCC_APB2ENR_SYSCFGCOMPEN', 'RCC_APB2ENR_USART6EN',
    'RCC_APB2ENR_USART7EN', 'RCC_APB2ENR_USART8EN', 'RCC_APB2ENR_ADCEN',
    'RCC_APB2ENR_TIM1EN', 'RCC_APB2ENR_SPI1EN', 'RCC_APB2ENR_USART1EN',
    'RCC_APB2ENR_TIM15EN', 'RCC_APB2ENR_TIM16EN', 'RCC_APB2ENR_TIM17EN',
    'RCC_APB2ENR_DBGMCUEN', 'RCC_APB2ENR_SYSCFGEN', 'RCC_APB2ENR_ADC1EN',
    'RCC_APB1ENR_TIM2EN', 'RCC_APB1ENR_TIM3EN', 'RCC_APB1ENR_TIM6EN',
    'RCC_APB1ENR_TIM7EN', 'RCC_APB1ENR_TIM14EN', 'RCC_APB1ENR_WWDGEN',
    'RCC_APB1ENR_SPI2EN', 'RCC_APB1ENR_USART2EN', 'RCC_APB1ENR_USART3EN',
    'RCC_APB1ENR_USART4EN', 'RCC_APB1ENR_USART5EN', 'RCC_APB1ENR_I2C1EN',
    'RCC_APB1ENR_I2C2EN', 'RCC_APB1ENR_USBEN', 'RCC_APB1ENR_CANEN', 'RCC_APB1ENR_CRSEN',
    'RCC_APB1ENR_PWREN', 'RCC_APB1ENR_DACEN', 'RCC_APB1ENR_CECEN', 'RCC_BDCR_LSEON',
    'RCC_BDCR_LSERDY', 'RCC_BDCR_LSEBYP', 'RCC_BDCR_LSEDRV', 'RCC_BDCR_LSEDRV_0',
    'RCC_BDCR_LSEDRV_1', 'RCC_BDCR_RTCSEL', 'RCC_BDCR_RTCSEL_0', 'RCC_BDCR_RTCSEL_1',
    'RCC_BDCR_RTCSEL_NOCLOCK', 'RCC_BDCR_RTCSEL_LSE', 'RCC_BDCR_RTCSEL_LSI',
    'RCC_BDCR_RTCSEL_HSE', 'RCC_BDCR_RTCEN', 'RCC_BDCR_BDRST', 'RCC_CSR_LSION',
    'RCC_CSR_LSIRDY', 'RCC_CSR_V18PWRRSTF', 'RCC_CSR_RMVF', 'RCC_CSR_OBLRSTF',
    'RCC_CSR_PINRSTF', 'RCC_CSR_PORRSTF', 'RCC_CSR_SFTRSTF', 'RCC_CSR_IWDGRSTF',
    'RCC_CSR_WWDGRSTF', 'RCC_CSR_LPWRRSTF', 'RCC_CSR_OBL', 'RCC_AHBRSTR_GPIOARST',
    'RCC_AHBRSTR_GPIOBRST', 'RCC_AHBRSTR_GPIOCRST', 'RCC_AHBRSTR_GPIODRST',
    'RCC_AHBRSTR_GPIOERST', 'RCC_AHBRSTR_GPIOFRST', 'RCC_AHBRSTR_TSCRST',
    'RCC_AHBRSTR_TSRST', 'RCC_CFGR2_PREDIV1', 'RCC_CFGR2_PREDIV1_0',
    'RCC_CFGR2_PREDIV1_1', 'RCC_CFGR2_PREDIV1_2', 'RCC_CFGR2_PREDIV1_3',
    'RCC_CFGR2_PREDIV1_DIV1', 'RCC_CFGR2_PREDIV1_DIV2', 'RCC_CFGR2_PREDIV1_DIV3',
    'RCC_CFGR2_PREDIV1_DIV4', 'RCC_CFGR2_PREDIV1_DIV5', 'RCC_CFGR2_PREDIV1_DIV6',
    'RCC_CFGR2_PREDIV1_DIV7', 'RCC_CFGR2_PREDIV1_DIV8', 'RCC_CFGR2_PREDIV1_DIV9',
    'RCC_CFGR2_PREDIV1_DIV10', 'RCC_CFGR2_PREDIV1_DIV11', 'RCC_CFGR2_PREDIV1_DIV12',
    'RCC_CFGR2_PREDIV1_DIV13', 'RCC_CFGR2_PREDIV1_DIV14', 'RCC_CFGR2_PREDIV1_DIV15',
    'RCC_CFGR2_PREDIV1_DIV16', 'RCC_CFGR3_USART1SW', 'RCC_CFGR3_USART1SW_0',
    'RCC_CFGR3_USART1SW_1', 'RCC_CFGR3_I2C1SW', 'RCC_CFGR3_CECSW', 'RCC_CFGR3_USBSW',
    'RCC_CFGR3_ADCSW', 'RCC_CFGR3_USART2SW', 'RCC_CFGR3_USART2SW_0',
    'RCC_CFGR3_USART2SW_1', 'RCC_CFGR3_USART3SW', 'RCC_CFGR3_USART3SW_0',
    'RCC_CFGR3_USART3SW_1', 'RCC_CR2_HSI14ON', 'RCC_CR2_HSI14RDY', 'RCC_CR2_HSI14DIS',
    'RCC_CR2_HSI14TRIM', 'RCC_CR2_HSI14CAL', 'RCC_CR2_HSI48ON', 'RCC_CR2_HSI48RDY',
    'RCC_CR2_HSI48CAL', 'RTC_TR_PM', 'RTC_TR_HT', 'RTC_TR_HT_0', 'RTC_TR_HT_1',
    'RTC_TR_HU', 'RTC_TR_HU_0', 'RTC_TR_HU_1', 'RTC_TR_HU_2', 'RTC_TR_HU_3',
    'RTC_TR_MNT', 'RTC_TR_MNT_0', 'RTC_TR_MNT_1', 'RTC_TR_MNT_2', 'RTC_TR_MNU',
    'RTC_TR_MNU_0', 'RTC_TR_MNU_1', 'RTC_TR_MNU_2', 'RTC_TR_MNU_3', 'RTC_TR_ST',
    'RTC_TR_ST_0', 'RTC_TR_ST_1', 'RTC_TR_ST_2', 'RTC_TR_SU', 'RTC_TR_SU_0',
    'RTC_TR_SU_1', 'RTC_TR_SU_2', 'RTC_TR_SU_3', 'RTC_DR_YT', 'RTC_DR_YT_0',
    'RTC_DR_YT_1', 'RTC_DR_YT_2', 'RTC_DR_YT_3', 'RTC_DR_YU', 'RTC_DR_YU_0',
    'RTC_DR_YU_1', 'RTC_DR_YU_2', 'RTC_DR_YU_3', 'RTC_DR_WDU', 'RTC_DR_WDU_0',
    'RTC_DR_WDU_1', 'RTC_DR_WDU_2', 'RTC_DR_MT', 'RTC_DR_MU', 'RTC_DR_MU_0',
    'RTC_DR_MU_1', 'RTC_DR_MU_2', 'RTC_DR_MU_3', 'RTC_DR_DT', 'RTC_DR_DT_0',
    'RTC_DR_DT_1', 'RTC_DR_DU', 'RTC_DR_DU_0', 'RTC_DR_DU_1', 'RTC_DR_DU_2',
    'RTC_DR_DU_3', 'RTC_CR_COE', 'RTC_CR_OSEL', 'RTC_CR_OSEL_0', 'RTC_CR_OSEL_1',
    'RTC_CR_POL', 'RTC_CR_COSEL', 'RTC_CR_BKP', 'RTC_CR_SUB1H', 'RTC_CR_ADD1H',
    'RTC_CR_TSIE', 'RTC_CR_WUTIE', 'RTC_CR_ALRAIE', 'RTC_CR_TSE', 'RTC_CR_WUTE',
    'RTC_CR_ALRAE', 'RTC_CR_FMT', 'RTC_CR_BYPSHAD', 'RTC_CR_REFCKON', 'RTC_CR_TSEDGE',
    'RTC_CR_WUCKSEL', 'RTC_CR_WUCKSEL_0', 'RTC_CR_WUCKSEL_1', 'RTC_CR_WUCKSEL_2',
    'RTC_CR_BCK', 'RTC_CR_CALSEL', 'RTC_ISR_RECALPF', 'RTC_ISR_TAMP3F',
    'RTC_ISR_TAMP2F', 'RTC_ISR_TAMP1F', 'RTC_ISR_TSOVF', 'RTC_ISR_TSF', 'RTC_ISR_WUTF',
    'RTC_ISR_ALRAF', 'RTC_ISR_INIT', 'RTC_ISR_INITF', 'RTC_ISR_RSF', 'RTC_ISR_INITS',
    'RTC_ISR_SHPF', 'RTC_ISR_WUTWF', 'RTC_ISR_ALRAWF', 'RTC_PRER_PREDIV_A',
    'RTC_PRER_PREDIV_S', 'RTC_WUTR_WUT', 'RTC_ALRMAR_MSK4', 'RTC_ALRMAR_WDSEL',
    'RTC_ALRMAR_DT', 'RTC_ALRMAR_DT_0', 'RTC_ALRMAR_DT_1', 'RTC_ALRMAR_DU',
    'RTC_ALRMAR_DU_0', 'RTC_ALRMAR_DU_1', 'RTC_ALRMAR_DU_2', 'RTC_ALRMAR_DU_3',
    'RTC_ALRMAR_MSK3', 'RTC_ALRMAR_PM', 'RTC_ALRMAR_HT', 'RTC_ALRMAR_HT_0',
    'RTC_ALRMAR_HT_1', 'RTC_ALRMAR_HU', 'RTC_ALRMAR_HU_0', 'RTC_ALRMAR_HU_1',
    'RTC_ALRMAR_HU_2', 'RTC_ALRMAR_HU_3', 'RTC_ALRMAR_MSK2', 'RTC_ALRMAR_MNT',
    'RTC_ALRMAR_MNT_0', 'RTC_ALRMAR_MNT_1', 'RTC_ALRMAR_MNT_2', 'RTC_ALRMAR_MNU',
    'RTC_ALRMAR_MNU_0', 'RTC_ALRMAR_MNU_1', 'RTC_ALRMAR_MNU_2', 'RTC_ALRMAR_MNU_3',
    'RTC_ALRMAR_MSK1', 'RTC_ALRMAR_ST', 'RTC_ALRMAR_ST_0', 'RTC_ALRMAR_ST_1',
    'RTC_ALRMAR_ST_2', 'RTC_ALRMAR_SU', 'RTC_ALRMAR_SU_0', 'RTC_ALRMAR_SU_1',
    'RTC_ALRMAR_SU_2', 'RTC_ALRMAR_SU_3', 'RTC_WPR_KEY', 'RTC_SSR_SS',
    'RTC_SHIFTR_SUBFS', 'RTC_SHIFTR_ADD1S', 'RTC_TSTR_PM', 'RTC_TSTR_HT',
    'RTC_TSTR_HT_0', 'RTC_TSTR_HT_1', 'RTC_TSTR_HU', 'RTC_TSTR_HU_0', 'RTC_TSTR_HU_1',
    'RTC_TSTR_HU_2', 'RTC_TSTR_HU_3', 'RTC_TSTR_MNT', 'RTC_TSTR_MNT_0',
    'RTC_TSTR_MNT_1', 'RTC_TSTR_MNT_2', 'RTC_TSTR_MNU', 'RTC_TSTR_MNU_0',
    'RTC_TSTR_MNU_1', 'RTC_TSTR_MNU_2', 'RTC_TSTR_MNU_3', 'RTC_TSTR_ST',
    'RTC_TSTR_ST_0', 'RTC_TSTR_ST_1', 'RTC_TSTR_ST_2', 'RTC_TSTR_SU', 'RTC_TSTR_SU_0',
    'RTC_TSTR_SU_1', 'RTC_TSTR_SU_2', 'RTC_TSTR_SU_3', 'RTC_TSDR_WDU', 'RTC_TSDR_WDU_0',
    'RTC_TSDR_WDU_1', 'RTC_TSDR_WDU_2', 'RTC_TSDR_MT', 'RTC_TSDR_MU', 'RTC_TSDR_MU_0',
    'RTC_TSDR_MU_1', 'RTC_TSDR_MU_2', 'RTC_TSDR_MU_3', 'RTC_TSDR_DT', 'RTC_TSDR_DT_0',
    'RTC_TSDR_DT_1', 'RTC_TSDR_DU', 'RTC_TSDR_DU_0', 'RTC_TSDR_DU_1', 'RTC_TSDR_DU_2',
    'RTC_TSDR_DU_3', 'RTC_TSSSR_SS', 'RTC_CALR_CALP', 'RTC_CALR_CALW8',
    'RTC_CALR_CALW16', 'RTC_CALR_CALM', 'RTC_CALR_CALM_0', 'RTC_CALR_CALM_1',
    'RTC_CALR_CALM_2', 'RTC_CALR_CALM_3', 'RTC_CALR_CALM_4', 'RTC_CALR_CALM_5',
    'RTC_CALR_CALM_6', 'RTC_CALR_CALM_7', 'RTC_CALR_CALM_8', 'RTC_CAL_CALP',
    'RTC_CAL_CALW8', 'RTC_CAL_CALW16', 'RTC_CAL_CALM', 'RTC_CAL_CALM_0',
    'RTC_CAL_CALM_1', 'RTC_CAL_CALM_2', 'RTC_CAL_CALM_3', 'RTC_CAL_CALM_4',
    'RTC_CAL_CALM_5', 'RTC_CAL_CALM_6', 'RTC_CAL_CALM_7', 'RTC_CAL_CALM_8',
    'RTC_TAFCR_PC15MODE', 'RTC_TAFCR_PC15VALUE', 'RTC_TAFCR_PC14MODE',
    'RTC_TAFCR_PC14VALUE', 'RTC_TAFCR_PC13MODE', 'RTC_TAFCR_PC13VALUE',
    'RTC_TAFCR_TAMPPUDIS', 'RTC_TAFCR_TAMPPRCH', 'RTC_TAFCR_TAMPPRCH_0',
    'RTC_TAFCR_TAMPPRCH_1', 'RTC_TAFCR_TAMPFLT', 'RTC_TAFCR_TAMPFLT_0',
    'RTC_TAFCR_TAMPFLT_1', 'RTC_TAFCR_TAMPFREQ', 'RTC_TAFCR_TAMPFREQ_0',
    'RTC_TAFCR_TAMPFREQ_1', 'RTC_TAFCR_TAMPFREQ_2', 'RTC_TAFCR_TAMPTS',
    'RTC_TAFCR_TAMP3EDGE', 'RTC_TAFCR_TAMP3E', 'RTC_TAFCR_TAMP2EDGE',
    'RTC_TAFCR_TAMP2E', 'RTC_TAFCR_TAMPIE', 'RTC_TAFCR_TAMP1TRG', 'RTC_TAFCR_TAMP1E',
    'RTC_TAFCR_ALARMOUTTYPE', 'RTC_ALRMASSR_MASKSS', 'RTC_ALRMASSR_MASKSS_0',
    'RTC_ALRMASSR_MASKSS_1', 'RTC_ALRMASSR_MASKSS_2', 'RTC_ALRMASSR_MASKSS_3',
    'RTC_ALRMASSR_SS', 'RTC_BKP0R', 'RTC_BKP1R', 'RTC_BKP2R', 'RTC_BKP3R', 'RTC_BKP4R',
    'SPI_CR1_CPHA', 'SPI_CR1_CPOL', 'SPI_CR1_MSTR', 'SPI_CR1_BR', 'SPI_CR1_BR_0',
    'SPI_CR1_BR_1', 'SPI_CR1_BR_2', 'SPI_CR1_SPE', 'SPI_CR1_LSBFIRST', 'SPI_CR1_SSI',
    'SPI_CR1_SSM', 'SPI_CR1_RXONLY', 'SPI_CR1_CRCL', 'SPI_CR1_CRCNEXT', 'SPI_CR1_CRCEN',
    'SPI_CR1_BIDIOE', 'SPI_CR1_BIDIMODE', 'SPI_CR2_RXDMAEN', 'SPI_CR2_TXDMAEN',
    'SPI_CR2_SSOE', 'SPI_CR2_NSSP', 'SPI_CR2_FRF', 'SPI_CR2_ERRIE', 'SPI_CR2_RXNEIE',
    'SPI_CR2_TXEIE', 'SPI_CR2_DS', 'SPI_CR2_DS_0', 'SPI_CR2_DS_1', 'SPI_CR2_DS_2',
    'SPI_CR2_DS_3', 'SPI_CR2_FRXTH', 'SPI_CR2_LDMARX', 'SPI_CR2_LDMATX', 'SPI_SR_RXNE',
    'SPI_SR_TXE', 'SPI_SR_CHSIDE', 'SPI_SR_UDR', 'SPI_SR_CRCERR', 'SPI_SR_MODF',
    'SPI_SR_OVR', 'SPI_SR_BSY', 'SPI_SR_FRE', 'SPI_SR_FRLVL', 'SPI_SR_FRLVL_0',
    'SPI_SR_FRLVL_1', 'SPI_SR_FTLVL', 'SPI_SR_FTLVL_0', 'SPI_SR_FTLVL_1', 'SPI_DR_DR',
    'SPI_CRCPR_CRCPOLY', 'SPI_RXCRCR_RXCRC', 'SPI_TXCRCR_TXCRC', 'SPI_I2SCFGR_CHLEN',
    'SPI_I2SCFGR_DATLEN', 'SPI_I2SCFGR_DATLEN_0', 'SPI_I2SCFGR_DATLEN_1',
    'SPI_I2SCFGR_CKPOL', 'SPI_I2SCFGR_I2SSTD', 'SPI_I2SCFGR_I2SSTD_0',
    'SPI_I2SCFGR_I2SSTD_1', 'SPI_I2SCFGR_PCMSYNC', 'SPI_I2SCFGR_I2SCFG',
    'SPI_I2SCFGR_I2SCFG_0', 'SPI_I2SCFGR_I2SCFG_1', 'SPI_I2SCFGR_I2SE',
    'SPI_I2SCFGR_I2SMOD', 'SPI_I2SPR_I2SDIV', 'SPI_I2SPR_ODD', 'SPI_I2SPR_MCKOE',
    'SYSCFG_CFGR1_MEM_MODE', 'SYSCFG_CFGR1_MEM_MODE_0', 'SYSCFG_CFGR1_MEM_MODE_1',
    'SYSCFG_CFGR1_IRDA_ENV_SEL', 'SYSCFG_CFGR1_IRDA_ENV_SEL_0',
    'SYSCFG_CFGR1_IRDA_ENV_SEL_1', 'SYSCFG_CFGR1_PA11_PA12_RMP',
    'SYSCFG_CFGR1_ADC_DMA_RMP', 'SYSCFG_CFGR1_USART1TX_DMA_RMP',
    'SYSCFG_CFGR1_USART1RX_DMA_RMP', 'SYSCFG_CFGR1_TIM16_DMA_RMP',
    'SYSCFG_CFGR1_TIM17_DMA_RMP', 'SYSCFG_CFGR1_TIM16_DMA_RMP2',
    'SYSCFG_CFGR1_TIM17_DMA_RMP2', 'SYSCFG_CFGR1_I2C_FMP_PB6',
    'SYSCFG_CFGR1_I2C_FMP_PB7', 'SYSCFG_CFGR1_I2C_FMP_PB8', 'SYSCFG_CFGR1_I2C_FMP_PB9',
    'SYSCFG_CFGR1_I2C_FMP_I2C1', 'SYSCFG_CFGR1_I2C_FMP_I2C2',
    'SYSCFG_CFGR1_I2C_FMP_PA9', 'SYSCFG_CFGR1_I2C_FMP_PA10',
    'SYSCFG_CFGR1_SPI2_DMA_RMP', 'SYSCFG_CFGR1_USART2_DMA_RMP',
    'SYSCFG_CFGR1_USART3_DMA_RMP', 'SYSCFG_CFGR1_I2C1_DMA_RMP',
    'SYSCFG_CFGR1_TIM1_DMA_RMP', 'SYSCFG_CFGR1_TIM2_DMA_RMP',
    'SYSCFG_CFGR1_TIM3_DMA_RMP', 'SYSCFG_EXTICR1_EXTI0', 'SYSCFG_EXTICR1_EXTI1',
    'SYSCFG_EXTICR1_EXTI2', 'SYSCFG_EXTICR1_EXTI3', 'SYSCFG_EXTICR1_EXTI0_PA',
    'SYSCFG_EXTICR1_EXTI0_PB', 'SYSCFG_EXTICR1_EXTI0_PC', 'SYSCFG_EXTICR1_EXTI0_PD',
    'SYSCFG_EXTICR1_EXTI0_PE', 'SYSCFG_EXTICR1_EXTI0_PF', 'SYSCFG_EXTICR1_EXTI1_PA',
    'SYSCFG_EXTICR1_EXTI1_PB', 'SYSCFG_EXTICR1_EXTI1_PC', 'SYSCFG_EXTICR1_EXTI1_PD',
    'SYSCFG_EXTICR1_EXTI1_PE', 'SYSCFG_EXTICR1_EXTI1_PF', 'SYSCFG_EXTICR1_EXTI2_PA',
    'SYSCFG_EXTICR1_EXTI2_PB', 'SYSCFG_EXTICR1_EXTI2_PC', 'SYSCFG_EXTICR1_EXTI2_PD',
    'SYSCFG_EXTICR1_EXTI2_PE', 'SYSCFG_EXTICR1_EXTI2_PF', 'SYSCFG_EXTICR1_EXTI3_PA',
    'SYSCFG_EXTICR1_EXTI3_PB', 'SYSCFG_EXTICR1_EXTI3_PC', 'SYSCFG_EXTICR1_EXTI3_PD',
    'SYSCFG_EXTICR1_EXTI3_PE', 'SYSCFG_EXTICR1_EXTI3_PF', 'SYSCFG_EXTICR2_EXTI4',
    'SYSCFG_EXTICR2_EXTI5', 'SYSCFG_EXTICR2_EXTI6', 'SYSCFG_EXTICR2_EXTI7',
    'SYSCFG_EXTICR2_EXTI4_PA', 'SYSCFG_EXTICR2_EXTI4_PB', 'SYSCFG_EXTICR2_EXTI4_PC',
    'SYSCFG_EXTICR2_EXTI4_PD', 'SYSCFG_EXTICR2_EXTI4_PE', 'SYSCFG_EXTICR2_EXTI4_PF',
    'SYSCFG_EXTICR2_EXTI5_PA', 'SYSCFG_EXTICR2_EXTI5_PB', 'SYSCFG_EXTICR2_EXTI5_PC',
    'SYSCFG_EXTICR2_EXTI5_PD', 'SYSCFG_EXTICR2_EXTI5_PE', 'SYSCFG_EXTICR2_EXTI5_PF',
    'SYSCFG_EXTICR2_EXTI6_PA', 'SYSCFG_EXTICR2_EXTI6_PB', 'SYSCFG_EXTICR2_EXTI6_PC',
    'SYSCFG_EXTICR2_EXTI6_PD', 'SYSCFG_EXTICR2_EXTI6_PE', 'SYSCFG_EXTICR2_EXTI6_PF',
    'SYSCFG_EXTICR2_EXTI7_PA', 'SYSCFG_EXTICR2_EXTI7_PB', 'SYSCFG_EXTICR2_EXTI7_PC',
    'SYSCFG_EXTICR2_EXTI7_PD', 'SYSCFG_EXTICR2_EXTI7_PE', 'SYSCFG_EXTICR2_EXTI7_PF',
    'SYSCFG_EXTICR3_EXTI8', 'SYSCFG_EXTICR3_EXTI9', 'SYSCFG_EXTICR3_EXTI10',
    'SYSCFG_EXTICR3_EXTI11', 'SYSCFG_EXTICR3_EXTI8_PA', 'SYSCFG_EXTICR3_EXTI8_PB',
    'SYSCFG_EXTICR3_EXTI8_PC', 'SYSCFG_EXTICR3_EXTI8_PD', 'SYSCFG_EXTICR3_EXTI8_PE',
    'SYSCFG_EXTICR3_EXTI9_PA', 'SYSCFG_EXTICR3_EXTI9_PB', 'SYSCFG_EXTICR3_EXTI9_PC',
    'SYSCFG_EXTICR3_EXTI9_PD', 'SYSCFG_EXTICR3_EXTI9_PE', 'SYSCFG_EXTICR3_EXTI9_PF',
    'SYSCFG_EXTICR3_EXTI10_PA', 'SYSCFG_EXTICR3_EXTI10_PB', 'SYSCFG_EXTICR3_EXTI10_PC',
    'SYSCFG_EXTICR3_EXTI10_PD', 'SYSCFG_EXTICR3_EXTI10_PE', 'SYSCFG_EXTICR3_EXTI10_PF',
    'SYSCFG_EXTICR3_EXTI11_PA', 'SYSCFG_EXTICR3_EXTI11_PB', 'SYSCFG_EXTICR3_EXTI11_PC',
    'SYSCFG_EXTICR3_EXTI11_PD', 'SYSCFG_EXTICR3_EXTI11_PE', 'SYSCFG_EXTICR4_EXTI12',
    'SYSCFG_EXTICR4_EXTI13', 'SYSCFG_EXTICR4_EXTI14', 'SYSCFG_EXTICR4_EXTI15',
    'SYSCFG_EXTICR4_EXTI12_PA', 'SYSCFG_EXTICR4_EXTI12_PB', 'SYSCFG_EXTICR4_EXTI12_PC',
    'SYSCFG_EXTICR4_EXTI12_PD', 'SYSCFG_EXTICR4_EXTI12_PE', 'SYSCFG_EXTICR4_EXTI13_PA',
    'SYSCFG_EXTICR4_EXTI13_PB', 'SYSCFG_EXTICR4_EXTI13_PC', 'SYSCFG_EXTICR4_EXTI13_PD',
    'SYSCFG_EXTICR4_EXTI13_PE', 'SYSCFG_EXTICR4_EXTI14_PA', 'SYSCFG_EXTICR4_EXTI14_PB',
    'SYSCFG_EXTICR4_EXTI14_PC', 'SYSCFG_EXTICR4_EXTI14_PD', 'SYSCFG_EXTICR4_EXTI14_PE',
    'SYSCFG_EXTICR4_EXTI15_PA', 'SYSCFG_EXTICR4_EXTI15_PB', 'SYSCFG_EXTICR4_EXTI15_PC',
    'SYSCFG_EXTICR4_EXTI15_PD', 'SYSCFG_EXTICR4_EXTI15_PE', 'SYSCFG_CFGR2_LOCKUP_LOCK',
    'SYSCFG_CFGR2_SRAM_PARITY_LOCK', 'SYSCFG_CFGR2_PVD_LOCK', 'SYSCFG_CFGR2_SRAM_PEF',
    'SYSCFG_CFGR2_SRAM_PE', 'SYSCFG_ITLINE0_SR_EWDG', 'SYSCFG_ITLINE1_SR_PVDOUT',
    'SYSCFG_ITLINE1_SR_VDDIO2', 'SYSCFG_ITLINE2_SR_RTC_WAKEUP',
    'SYSCFG_ITLINE2_SR_RTC_TSTAMP', 'SYSCFG_ITLINE2_SR_RTC_ALRA',
    'SYSCFG_ITLINE3_SR_FLASH_ITF', 'SYSCFG_ITLINE4_SR_CRS',
    'SYSCFG_ITLINE4_SR_CLK_CTRL', 'SYSCFG_ITLINE5_SR_EXTI0', 'SYSCFG_ITLINE5_SR_EXTI1',
    'SYSCFG_ITLINE6_SR_EXTI2', 'SYSCFG_ITLINE6_SR_EXTI3', 'SYSCFG_ITLINE7_SR_EXTI4',
    'SYSCFG_ITLINE7_SR_EXTI5', 'SYSCFG_ITLINE7_SR_EXTI6', 'SYSCFG_ITLINE7_SR_EXTI7',
    'SYSCFG_ITLINE7_SR_EXTI8', 'SYSCFG_ITLINE7_SR_EXTI9', 'SYSCFG_ITLINE7_SR_EXTI10',
    'SYSCFG_ITLINE7_SR_EXTI11', 'SYSCFG_ITLINE7_SR_EXTI12', 'SYSCFG_ITLINE7_SR_EXTI13',
    'SYSCFG_ITLINE7_SR_EXTI14', 'SYSCFG_ITLINE7_SR_EXTI15', 'SYSCFG_ITLINE8_SR_TSC_EOA',
    'SYSCFG_ITLINE8_SR_TSC_MCE', 'SYSCFG_ITLINE9_SR_DMA1_CH1',
    'SYSCFG_ITLINE10_SR_DMA1_CH2', 'SYSCFG_ITLINE10_SR_DMA1_CH3',
    'SYSCFG_ITLINE10_SR_DMA2_CH1', 'SYSCFG_ITLINE10_SR_DMA2_CH2',
    'SYSCFG_ITLINE11_SR_DMA1_CH4', 'SYSCFG_ITLINE11_SR_DMA1_CH5',
    'SYSCFG_ITLINE11_SR_DMA1_CH6', 'SYSCFG_ITLINE11_SR_DMA1_CH7',
    'SYSCFG_ITLINE11_SR_DMA2_CH3', 'SYSCFG_ITLINE11_SR_DMA2_CH4',
    'SYSCFG_ITLINE11_SR_DMA2_CH5', 'SYSCFG_ITLINE12_SR_ADC', 'SYSCFG_ITLINE12_SR_COMP1',
    'SYSCFG_ITLINE12_SR_COMP2', 'SYSCFG_ITLINE13_SR_TIM1_BRK',
    'SYSCFG_ITLINE13_SR_TIM1_UPD', 'SYSCFG_ITLINE13_SR_TIM1_TRG',
    'SYSCFG_ITLINE13_SR_TIM1_CCU', 'SYSCFG_ITLINE14_SR_TIM1_CC',
    'SYSCFG_ITLINE15_SR_TIM2_GLB', 'SYSCFG_ITLINE16_SR_TIM3_GLB',
    'SYSCFG_ITLINE17_SR_DAC', 'SYSCFG_ITLINE17_SR_TIM6_GLB',
    'SYSCFG_ITLINE18_SR_TIM7_GLB', 'SYSCFG_ITLINE19_SR_TIM14_GLB',
    'SYSCFG_ITLINE20_SR_TIM15_GLB', 'SYSCFG_ITLINE21_SR_TIM16_GLB',
    'SYSCFG_ITLINE22_SR_TIM17_GLB', 'SYSCFG_ITLINE23_SR_I2C1_GLB',
    'SYSCFG_ITLINE24_SR_I2C2_GLB', 'SYSCFG_ITLINE25_SR_SPI1', 'SYSCFG_ITLINE26_SR_SPI2',
    'SYSCFG_ITLINE27_SR_USART1_GLB', 'SYSCFG_ITLINE28_SR_USART2_GLB',
    'SYSCFG_ITLINE29_SR_USART3_GLB', 'SYSCFG_ITLINE29_SR_USART4_GLB',
    'SYSCFG_ITLINE29_SR_USART5_GLB', 'SYSCFG_ITLINE29_SR_USART6_GLB',
    'SYSCFG_ITLINE29_SR_USART7_GLB', 'SYSCFG_ITLINE29_SR_USART8_GLB',
    'SYSCFG_ITLINE30_SR_CAN', 'SYSCFG_ITLINE30_SR_CEC', 'TIM_CR1_CEN', 'TIM_CR1_UDIS',
    'TIM_CR1_URS', 'TIM_CR1_OPM', 'TIM_CR1_DIR', 'TIM_CR1_CMS', 'TIM_CR1_CMS_0',
    'TIM_CR1_CMS_1', 'TIM_CR1_ARPE', 'TIM_CR1_CKD', 'TIM_CR1_CKD_0', 'TIM_CR1_CKD_1',
    'TIM_CR2_CCPC', 'TIM_CR2_CCUS', 'TIM_CR2_CCDS', 'TIM_CR2_MMS', 'TIM_CR2_MMS_0',
    'TIM_CR2_MMS_1', 'TIM_CR2_MMS_2', 'TIM_CR2_TI1S', 'TIM_CR2_OIS1', 'TIM_CR2_OIS1N',
    'TIM_CR2_OIS2', 'TIM_CR2_OIS2N', 'TIM_CR2_OIS3', 'TIM_CR2_OIS3N', 'TIM_CR2_OIS4',
    'TIM_SMCR_SMS', 'TIM_SMCR_SMS_0', 'TIM_SMCR_SMS_1', 'TIM_SMCR_SMS_2',
    'TIM_SMCR_OCCS', 'TIM_SMCR_TS', 'TIM_SMCR_TS_0', 'TIM_SMCR_TS_1', 'TIM_SMCR_TS_2',
    'TIM_SMCR_MSM', 'TIM_SMCR_ETF', 'TIM_SMCR_ETF_0', 'TIM_SMCR_ETF_1',
    'TIM_SMCR_ETF_2', 'TIM_SMCR_ETF_3', 'TIM_SMCR_ETPS', 'TIM_SMCR_ETPS_0',
    'TIM_SMCR_ETPS_1', 'TIM_SMCR_ECE', 'TIM_SMCR_ETP', 'TIM_DIER_UIE', 'TIM_DIER_CC1IE',
    'TIM_DIER_CC2IE', 'TIM_DIER_CC3IE', 'TIM_DIER_CC4IE', 'TIM_DIER_COMIE',
    'TIM_DIER_TIE', 'TIM_DIER_BIE', 'TIM_DIER_UDE', 'TIM_DIER_CC1DE', 'TIM_DIER_CC2DE',
    'TIM_DIER_CC3DE', 'TIM_DIER_CC4DE', 'TIM_DIER_COMDE', 'TIM_DIER_TDE', 'TIM_SR_UIF',
    'TIM_SR_CC1IF', 'TIM_SR_CC2IF', 'TIM_SR_CC3IF', 'TIM_SR_CC4IF', 'TIM_SR_COMIF',
    'TIM_SR_TIF', 'TIM_SR_BIF', 'TIM_SR_CC1OF', 'TIM_SR_CC2OF', 'TIM_SR_CC3OF',
    'TIM_SR_CC4OF', 'TIM_EGR_UG', 'TIM_EGR_CC1G', 'TIM_EGR_CC2G', 'TIM_EGR_CC3G',
    'TIM_EGR_CC4G', 'TIM_EGR_COMG', 'TIM_EGR_TG', 'TIM_EGR_BG', 'TIM_CCMR1_CC1S',
    'TIM_CCMR1_CC1S_0', 'TIM_CCMR1_CC1S_1', 'TIM_CCMR1_OC1FE', 'TIM_CCMR1_OC1PE',
    'TIM_CCMR1_OC1M', 'TIM_CCMR1_OC1M_0', 'TIM_CCMR1_OC1M_1', 'TIM_CCMR1_OC1M_2',
    'TIM_CCMR1_OC1CE', 'TIM_CCMR1_CC2S', 'TIM_CCMR1_CC2S_0', 'TIM_CCMR1_CC2S_1',
    'TIM_CCMR1_OC2FE', 'TIM_CCMR1_OC2PE', 'TIM_CCMR1_OC2M', 'TIM_CCMR1_OC2M_0',
    'TIM_CCMR1_OC2M_1', 'TIM_CCMR1_OC2M_2', 'TIM_CCMR1_OC2CE', 'TIM_CCMR1_IC1PSC',
    'TIM_CCMR1_IC1PSC_0', 'TIM_CCMR1_IC1PSC_1', 'TIM_CCMR1_IC1F', 'TIM_CCMR1_IC1F_0',
    'TIM_CCMR1_IC1F_1', 'TIM_CCMR1_IC1F_2', 'TIM_CCMR1_IC1F_3', 'TIM_CCMR1_IC2PSC',
    'TIM_CCMR1_IC2PSC_0', 'TIM_CCMR1_IC2PSC_1', 'TIM_CCMR1_IC2F', 'TIM_CCMR1_IC2F_0',
    'TIM_CCMR1_IC2F_1', 'TIM_CCMR1_IC2F_2', 'TIM_CCMR1_IC2F_3', 'TIM_CCMR2_CC3S',
    'TIM_CCMR2_CC3S_0', 'TIM_CCMR2_CC3S_1', 'TIM_CCMR2_OC3FE', 'TIM_CCMR2_OC3PE',
    'TIM_CCMR2_OC3M', 'TIM_CCMR2_OC3M_0', 'TIM_CCMR2_OC3M_1', 'TIM_CCMR2_OC3M_2',
    'TIM_CCMR2_OC3CE', 'TIM_CCMR2_CC4S', 'TIM_CCMR2_CC4S_0', 'TIM_CCMR2_CC4S_1',
    'TIM_CCMR2_OC4FE', 'TIM_CCMR2_OC4PE', 'TIM_CCMR2_OC4M', 'TIM_CCMR2_OC4M_0',
    'TIM_CCMR2_OC4M_1', 'TIM_CCMR2_OC4M_2', 'TIM_CCMR2_OC4CE', 'TIM_CCMR2_IC3PSC',
    'TIM_CCMR2_IC3PSC_0', 'TIM_CCMR2_IC3PSC_1', 'TIM_CCMR2_IC3F', 'TIM_CCMR2_IC3F_0',
    'TIM_CCMR2_IC3F_1', 'TIM_CCMR2_IC3F_2', 'TIM_CCMR2_IC3F_3', 'TIM_CCMR2_IC4PSC',
    'TIM_CCMR2_IC4PSC_0', 'TIM_CCMR2_IC4PSC_1', 'TIM_CCMR2_IC4F', 'TIM_CCMR2_IC4F_0',
    'TIM_CCMR2_IC4F_1', 'TIM_CCMR2_IC4F_2', 'TIM_CCMR2_IC4F_3', 'TIM_CCER_CC1E',
    'TIM_CCER_CC1P', 'TIM_CCER_CC1NE', 'TIM_CCER_CC1NP', 'TIM_CCER_CC2E',
    'TIM_CCER_CC2P', 'TIM_CCER_CC2NE', 'TIM_CCER_CC2NP', 'TIM_CCER_CC3E',
    'TIM_CCER_CC3P', 'TIM_CCER_CC3NE', 'TIM_CCER_CC3NP', 'TIM_CCER_CC4E',
    'TIM_CCER_CC4P', 'TIM_CCER_CC4NP', 'TIM_CNT_CNT', 'TIM_PSC_PSC', 'TIM_ARR_ARR',
    'TIM_RCR_REP', 'TIM_CCR1_CCR1', 'TIM_CCR2_CCR2', 'TIM_CCR3_CCR3', 'TIM_CCR4_CCR4',
    'TIM_BDTR_DTG', 'TIM_BDTR_DTG_0', 'TIM_BDTR_DTG_1', 'TIM_BDTR_DTG_2',
    'TIM_BDTR_DTG_3', 'TIM_BDTR_DTG_4', 'TIM_BDTR_DTG_5', 'TIM_BDTR_DTG_6',
    'TIM_BDTR_DTG_7', 'TIM_BDTR_LOCK', 'TIM_BDTR_LOCK_0', 'TIM_BDTR_LOCK_1',
    'TIM_BDTR_OSSI', 'TIM_BDTR_OSSR', 'TIM_BDTR_BKE', 'TIM_BDTR_BKP', 'TIM_BDTR_AOE',
    'TIM_BDTR_MOE', 'TIM_DCR_DBA', 'TIM_DCR_DBA_0', 'TIM_DCR_DBA_1', 'TIM_DCR_DBA_2',
    'TIM_DCR_DBA_3', 'TIM_DCR_DBA_4', 'TIM_DCR_DBL', 'TIM_DCR_DBL_0', 'TIM_DCR_DBL_1',
    'TIM_DCR_DBL_2', 'TIM_DCR_DBL_3', 'TIM_DCR_DBL_4', 'TIM_DMAR_DMAB',
    'TIM14_OR_TI1_RMP', 'TIM14_OR_TI1_RMP_0', 'TIM14_OR_TI1_RMP_1', 'USART_CR1_UE',
    'USART_CR1_UESM', 'USART_CR1_RE', 'USART_CR1_TE', 'USART_CR1_IDLEIE',
    'USART_CR1_RXNEIE', 'USART_CR1_TCIE', 'USART_CR1_TXEIE', 'USART_CR1_PEIE',
    'USART_CR1_PS', 'USART_CR1_PCE', 'USART_CR1_WAKE', 'USART_CR1_M', 'USART_CR1_MME',
    'USART_CR1_CMIE', 'USART_CR1_OVER8', 'USART_CR1_DEDT', 'USART_CR1_DEDT_0',
    'USART_CR1_DEDT_1', 'USART_CR1_DEDT_2', 'USART_CR1_DEDT_3', 'USART_CR1_DEDT_4',
    'USART_CR1_DEAT', 'USART_CR1_DEAT_0', 'USART_CR1_DEAT_1', 'USART_CR1_DEAT_2',
    'USART_CR1_DEAT_3', 'USART_CR1_DEAT_4', 'USART_CR1_RTOIE', 'USART_CR1_EOBIE',
    'USART_CR2_ADDM7', 'USART_CR2_LBDL', 'USART_CR2_LBDIE', 'USART_CR2_LBCL',
    'USART_CR2_CPHA', 'USART_CR2_CPOL', 'USART_CR2_CLKEN', 'USART_CR2_STOP',
    'USART_CR2_STOP_0', 'USART_CR2_STOP_1', 'USART_CR2_LINEN', 'USART_CR2_SWAP',
    'USART_CR2_RXINV', 'USART_CR2_TXINV', 'USART_CR2_DATAINV', 'USART_CR2_MSBFIRST',
    'USART_CR2_ABREN', 'USART_CR2_ABRMODE', 'USART_CR2_ABRMODE_0',
    'USART_CR2_ABRMODE_1', 'USART_CR2_RTOEN', 'USART_CR2_ADD', 'USART_CR3_EIE',
    'USART_CR3_IREN', 'USART_CR3_IRLP', 'USART_CR3_HDSEL', 'USART_CR3_NACK',
    'USART_CR3_SCEN', 'USART_CR3_DMAR', 'USART_CR3_DMAT', 'USART_CR3_RTSE',
    'USART_CR3_CTSE', 'USART_CR3_CTSIE', 'USART_CR3_ONEBIT', 'USART_CR3_OVRDIS',
    'USART_CR3_DDRE', 'USART_CR3_DEM', 'USART_CR3_DEP', 'USART_CR3_SCARCNT',
    'USART_CR3_SCARCNT_0', 'USART_CR3_SCARCNT_1', 'USART_CR3_SCARCNT_2',
    'USART_CR3_WUS', 'USART_CR3_WUS_0', 'USART_CR3_WUS_1', 'USART_CR3_WUFIE',
    'USART_BRR_DIV_FRACTION', 'USART_BRR_DIV_MANTISSA', 'USART_GTPR_PSC',
    'USART_GTPR_GT', 'USART_RTOR_RTO', 'USART_RTOR_BLEN', 'USART_RQR_ABRRQ',
    'USART_RQR_SBKRQ', 'USART_RQR_MMRQ', 'USART_RQR_RXFRQ', 'USART_RQR_TXFRQ',
    'USART_ISR_PE', 'USART_ISR_FE', 'USART_ISR_NE', 'USART_ISR_ORE', 'USART_ISR_IDLE',
    'USART_ISR_RXNE', 'USART_ISR_TC', 'USART_ISR_TXE', 'USART_ISR_LBD',
    'USART_ISR_CTSIF', 'USART_ISR_CTS', 'USART_ISR_RTOF', 'USART_ISR_EOBF',
    'USART_ISR_ABRE', 'USART_ISR_ABRF', 'USART_ISR_BUSY', 'USART_ISR_CMF',
    'USART_ISR_SBKF', 'USART_ISR_RWU', 'USART_ISR_WUF', 'USART_ISR_TEACK',
    'USART_ISR_REACK', 'USART_ICR_PECF', 'USART_ICR_FECF', 'USART_ICR_NCF',
    'USART_ICR_ORECF', 'USART_ICR_IDLECF', 'USART_ICR_TCCF', 'USART_ICR_LBDCF',
    'USART_ICR_CTSCF', 'USART_ICR_RTOCF', 'USART_ICR_EOBCF', 'USART_ICR_CMCF',
    'USART_ICR_WUCF', 'USART_RDR_RDR', 'USART_TDR_TDR', 'WWDG_CR_T', 'WWDG_CR_T0',
    'WWDG_CR_T1', 'WWDG_CR_T2', 'WWDG_CR_T3', 'WWDG_CR_T4', 'WWDG_CR_T5', 'WWDG_CR_T6',
    'WWDG_CR_WDGA', 'WWDG_CFR_W', 'WWDG_CFR_W0', 'WWDG_CFR_W1', 'WWDG_CFR_W2',
    'WWDG_CFR_W3', 'WWDG_CFR_W4', 'WWDG_CFR_W5', 'WWDG_CFR_W6', 'WWDG_CFR_WDGTB',
    'WWDG_CFR_WDGTB0', 'WWDG_CFR_WDGTB1', 'WWDG_CFR_EWI', 'WWDG_SR_EWIF', 'PVD_IRQn',
    'RCC_IRQn', 'TS_IRQn', 'DMA1_Channel1_IRQn', 'DMA1_Channel2_3_IRQn',
    'DMA1_Channel4_5_IRQn', 'DMA1_Channel4_5_6_7_IRQn', 'ADC1_IRQn', 'USART3_4_IRQn',
    'CEC_IRQn', 'PVD_IRQn', 'RCC_IRQn', 'TS_IRQn', 'DMA1_Ch1_IRQn',
    'DMA1_Ch2_3_DMA2_Ch1_2_IRQn', 'DMA1_Channel4_5_IRQn', 'DMA1_Ch4_7_DMA2_Ch3_5_IRQn',
    'ADC1_IRQn', 'USART3_8_IRQn', 'CEC_IRQn', 'PVD_VDDIO2_IRQn', 'RCC_CRS_IRQn',
    'TSC_IRQn', 'DMA1_Ch1_IRQn', 'DMA1_Ch2_3_DMA2_Ch1_2_IRQn',
    'DMA1_Channel4_5_6_7_IRQn', 'DMA1_Ch4_7_DMA2_Ch3_5_IRQn', 'ADC1_IRQn',
    'CEC_CAN_IRQn', 'PVD_IRQn', 'RCC_IRQn', 'TS_IRQn', 'DMA1_Ch1_IRQn',
    'DMA1_Ch2_3_DMA2_Ch1_2_IRQn', 'DMA1_Channel4_5_IRQn', 'DMA1_Ch4_7_DMA2_Ch3_5_IRQn',
    'ADC1_COMP_IRQn', 'CEC_IRQn', 'PVD_VDDIO2_IRQn', 'RCC_CRS_IRQn', 'DMA1_Ch1_IRQn',
    'DMA1_Ch2_3_DMA2_Ch1_2_IRQn', 'DMA1_Channel4_5_6_7_IRQn',
    'DMA1_Ch4_7_DMA2_Ch3_5_IRQn', 'ADC1_COMP_IRQn', 'RCC_CRS_IRQn', 'DMA1_Ch1_IRQn',
    'DMA1_Ch2_3_DMA2_Ch1_2_IRQn', 'DMA1_Channel4_5_6_7_IRQn',
    'DMA1_Ch4_7_DMA2_Ch3_5_IRQn', 'ADC1_COMP_IRQn', 'RCC_CRS_IRQn', 'DMA1_Ch1_IRQn',
    'DMA1_Ch2_3_DMA2_Ch1_2_IRQn', 'DMA1_Ch4_7_DMA2_Ch3_5_IRQn',
    'DMA1_Channel4_5_6_7_IRQn', 'ADC1_COMP_IRQn', 'TIM6_DAC_IRQn', 'USART3_8_IRQn',
    'RCC_CRS_IRQn', 'DMA1_Ch1_IRQn', 'DMA1_Ch2_3_DMA2_Ch1_2_IRQn',
    'DMA1_Ch4_7_DMA2_Ch3_5_IRQn', 'DMA1_Channel4_5_6_7_IRQn', 'ADC1_COMP_IRQn',
    'RCC_CRS_IRQn', 'DMA1_Ch1_IRQn', 'DMA1_Ch2_3_DMA2_Ch1_2_IRQn',
    'DMA1_Ch4_7_DMA2_Ch3_5_IRQn', 'DMA1_Channel4_5_6_7_IRQn', 'ADC1_COMP_IRQn',
    'TIM6_DAC_IRQn', 'USART3_8_IRQn', 'USART3_4_IRQn', 'ADC_TypeDef',
    'ADC_Common_TypeDef', 'CAN_TxMailBox_TypeDef', 'CAN_FIFOMailBox_TypeDef',
    'CAN_FilterRegister_TypeDef', 'CEC_TypeDef', 'COMP_TypeDef', 'CRC_TypeDef',
    'CRS_TypeDef', 'DAC_TypeDef', 'DBGMCU_TypeDef', 'DMA_Channel_TypeDef',
    'DMA_TypeDef', 'EXTI_TypeDef', 'FLASH_TypeDef', 'OB_TypeDef', 'GPIO_TypeDef',
    'SYSCFG_TypeDef', 'I2C_TypeDef', 'IWDG_TypeDef', 'PWR_TypeDef', 'RCC_TypeDef',
    'RTC_TypeDef', 'SPI_TypeDef', 'TIM_TypeDef', 'TSC_TypeDef', 'USART_TypeDef',
    'WWDG_TypeDef']
