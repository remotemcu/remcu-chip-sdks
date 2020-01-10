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



__version__ = "v3.5.0-e20ebe28"
__RUN = 0
__HALT = 1
__ERROR = 0
__WARNING = 1
__INFO = 2
__DEBUG = 3
__ALL_LOG = 4
DEFAULT_OPENOCD_PORT = 6666
DEFAULT_GDB_PORT = 3333
# file stm32f10x_rtc.h : 

# empty define __STM32F10x_RTC_H
RTC_IT_OW = 0x4
RTC_IT_ALR = 0x2
RTC_IT_SEC = 0x1
RTC_FLAG_RTOFF = 0x20
RTC_FLAG_RSF = 0x8
RTC_FLAG_OW = 0x4
RTC_FLAG_ALR = 0x2
RTC_FLAG_SEC = 0x1
# ----------------------------------------

# file stm32f10x_pwr.h : 

# empty define __STM32F10x_PWR_H
PWR_PVDLevel_2V2 = 0x0
PWR_PVDLevel_2V3 = 0x20
PWR_PVDLevel_2V4 = 0x40
PWR_PVDLevel_2V5 = 0x60
PWR_PVDLevel_2V6 = 0x80
PWR_PVDLevel_2V7 = 0xA0
PWR_PVDLevel_2V8 = 0xC0
PWR_PVDLevel_2V9 = 0xE0
PWR_Regulator_ON = 0x0
PWR_Regulator_LowPower = 0x1
PWR_STOPEntry_WFI = 0x1
PWR_STOPEntry_WFE = 0x2
PWR_FLAG_WU = 0x1
PWR_FLAG_SB = 0x2
PWR_FLAG_PVDO = 0x4
# ----------------------------------------

# file stm32f10x_iwdg.h : 

# empty define __STM32F10x_IWDG_H
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
# ----------------------------------------

# file stm32f10x_usart.h : 

# empty define __STM32F10x_USART_H
USART_WordLength_8b = 0x0
USART_WordLength_9b = 0x1000
USART_StopBits_1 = 0x0
USART_StopBits_0_5 = 0x1000
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
USART_IT_PE = 0x28
USART_IT_TXE = 0x727
USART_IT_TC = 0x626
USART_IT_RXNE = 0x525
USART_IT_IDLE = 0x424
USART_IT_LBD = 0x846
USART_IT_CTS = 0x96A
USART_IT_ERR = 0x60
USART_IT_ORE = 0x360
USART_IT_NE = 0x260
USART_IT_FE = 0x160
USART_DMAReq_Tx = 0x80
USART_DMAReq_Rx = 0x40
USART_WakeUp_IdleLine = 0x0
USART_WakeUp_AddressMark = 0x800
USART_LINBreakDetectLength_10b = 0x0
USART_LINBreakDetectLength_11b = 0x20
USART_IrDAMode_LowPower = 0x4
USART_IrDAMode_Normal = 0x0
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
# struct USART_InitTypeDef

class USART_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('USART_BaudRate',	ctypes.c_uint32),
		('USART_WordLength',	ctypes.c_uint16),
		('USART_StopBits',	ctypes.c_uint16),
		('USART_Parity',	ctypes.c_uint16),
		('USART_Mode',	ctypes.c_uint16),
		('USART_HardwareFlowControl',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct USART_ClockInitTypeDef

class USART_ClockInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('USART_Clock',	ctypes.c_uint16),
		('USART_CPOL',	ctypes.c_uint16),
		('USART_CPHA',	ctypes.c_uint16),
		('USART_LastBit',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_dbgmcu.h : 

# empty define __STM32F10x_DBGMCU_H
DBGMCU_SLEEP = 0x1
DBGMCU_STOP = 0x2
DBGMCU_STANDBY = 0x4
DBGMCU_IWDG_STOP = 0x100
DBGMCU_WWDG_STOP = 0x200
DBGMCU_TIM1_STOP = 0x400
DBGMCU_TIM2_STOP = 0x800
DBGMCU_TIM3_STOP = 0x1000
DBGMCU_TIM4_STOP = 0x2000
DBGMCU_CAN1_STOP = 0x4000
DBGMCU_I2C1_SMBUS_TIMEOUT = 0x8000
DBGMCU_I2C2_SMBUS_TIMEOUT = 0x10000
DBGMCU_TIM8_STOP = 0x20000
DBGMCU_TIM5_STOP = 0x40000
DBGMCU_TIM6_STOP = 0x80000
DBGMCU_TIM7_STOP = 0x100000
DBGMCU_CAN2_STOP = 0x200000
DBGMCU_TIM15_STOP = 0x400000
DBGMCU_TIM16_STOP = 0x800000
DBGMCU_TIM17_STOP = 0x1000000
DBGMCU_TIM12_STOP = 0x2000000
DBGMCU_TIM13_STOP = 0x4000000
DBGMCU_TIM14_STOP = 0x8000000
DBGMCU_TIM9_STOP = 0x10000000
DBGMCU_TIM10_STOP = 0x20000000
DBGMCU_TIM11_STOP = 0x40000000
# ----------------------------------------

# file stm32f10x_exti.h : 

# Enum EXTIMode_TypeDef
EXTI_Mode_Interrupt = 0x0
EXTI_Mode_Event = 0x4
# Enum EXTITrigger_TypeDef
EXTI_Trigger_Rising = 0x8
EXTI_Trigger_Falling = 0xC
EXTI_Trigger_Rising_Falling = 0x10
# empty define __STM32F10x_EXTI_H
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

# file stm32f10x_spi.h : 

# empty define __STM32F10x_SPI_H
SPI_Direction_2Lines_FullDuplex = 0x0
SPI_Direction_2Lines_RxOnly = 0x400
SPI_Direction_1Line_Rx = 0x8000
SPI_Direction_1Line_Tx = 0xC000
SPI_Mode_Master = 0x104
SPI_Mode_Slave = 0x0
SPI_DataSize_16b = 0x800
SPI_DataSize_8b = 0x0
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
SPI_I2S_DMAReq_Tx = 0x2
SPI_I2S_DMAReq_Rx = 0x1
SPI_NSSInternalSoft_Set = 0x100
SPI_NSSInternalSoft_Reset = 0xFEFF
SPI_CRC_Tx = 0x0
SPI_CRC_Rx = 0x1
SPI_Direction_Rx = 0xBFFF
SPI_Direction_Tx = 0x4000
SPI_I2S_IT_TXE = 0x71
SPI_I2S_IT_RXNE = 0x60
SPI_I2S_IT_ERR = 0x50
SPI_I2S_IT_OVR = 0x56
SPI_IT_MODF = 0x55
SPI_IT_CRCERR = 0x54
I2S_IT_UDR = 0x53
SPI_I2S_FLAG_RXNE = 0x1
SPI_I2S_FLAG_TXE = 0x2
I2S_FLAG_CHSIDE = 0x4
I2S_FLAG_UDR = 0x8
SPI_FLAG_CRCERR = 0x10
SPI_FLAG_MODF = 0x20
SPI_I2S_FLAG_OVR = 0x40
SPI_I2S_FLAG_BSY = 0x80
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

# file stm32f10x_adc.h : 

# empty define __STM32F10x_ADC_H
ADC_Mode_Independent = 0x0
ADC_Mode_RegInjecSimult = 0x10000
ADC_Mode_RegSimult_AlterTrig = 0x20000
ADC_Mode_InjecSimult_FastInterl = 0x30000
ADC_Mode_InjecSimult_SlowInterl = 0x40000
ADC_Mode_InjecSimult = 0x50000
ADC_Mode_RegSimult = 0x60000
ADC_Mode_FastInterl = 0x70000
ADC_Mode_SlowInterl = 0x80000
ADC_Mode_AlterTrig = 0x90000
ADC_ExternalTrigConv_T1_CC1 = 0x0
ADC_ExternalTrigConv_T1_CC2 = 0x20000
ADC_ExternalTrigConv_T2_CC2 = 0x60000
ADC_ExternalTrigConv_T3_TRGO = 0x80000
ADC_ExternalTrigConv_T4_CC4 = 0xA0000
ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO = 0xC0000
ADC_ExternalTrigConv_T1_CC3 = 0x40000
ADC_ExternalTrigConv_None = 0xE0000
ADC_ExternalTrigConv_T3_CC1 = 0x0
ADC_ExternalTrigConv_T2_CC3 = 0x20000
ADC_ExternalTrigConv_T8_CC1 = 0x60000
ADC_ExternalTrigConv_T8_TRGO = 0x80000
ADC_ExternalTrigConv_T5_CC1 = 0xA0000
ADC_ExternalTrigConv_T5_CC3 = 0xC0000
ADC_DataAlign_Right = 0x0
ADC_DataAlign_Left = 0x800
ADC_Channel_0 = 0x0
ADC_Channel_1 = 0x1
ADC_Channel_2 = 0x2
ADC_Channel_3 = 0x3
ADC_Channel_4 = 0x4
ADC_Channel_5 = 0x5
ADC_Channel_6 = 0x6
ADC_Channel_7 = 0x7
ADC_Channel_8 = 0x8
ADC_Channel_9 = 0x9
ADC_Channel_10 = 0xA
ADC_Channel_11 = 0xB
ADC_Channel_12 = 0xC
ADC_Channel_13 = 0xD
ADC_Channel_14 = 0xE
ADC_Channel_15 = 0xF
ADC_Channel_16 = 0x10
ADC_Channel_17 = 0x11
ADC_Channel_TempSensor = 0x10
ADC_Channel_Vrefint = 0x11
ADC_SampleTime_1Cycles5 = 0x0
ADC_SampleTime_7Cycles5 = 0x1
ADC_SampleTime_13Cycles5 = 0x2
ADC_SampleTime_28Cycles5 = 0x3
ADC_SampleTime_41Cycles5 = 0x4
ADC_SampleTime_55Cycles5 = 0x5
ADC_SampleTime_71Cycles5 = 0x6
ADC_SampleTime_239Cycles5 = 0x7
ADC_ExternalTrigInjecConv_T2_TRGO = 0x2000
ADC_ExternalTrigInjecConv_T2_CC1 = 0x3000
ADC_ExternalTrigInjecConv_T3_CC4 = 0x4000
ADC_ExternalTrigInjecConv_T4_TRGO = 0x5000
ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4 = 0x6000
ADC_ExternalTrigInjecConv_T1_TRGO = 0x0
ADC_ExternalTrigInjecConv_T1_CC4 = 0x1000
ADC_ExternalTrigInjecConv_None = 0x7000
ADC_ExternalTrigInjecConv_T4_CC3 = 0x2000
ADC_ExternalTrigInjecConv_T8_CC2 = 0x3000
ADC_ExternalTrigInjecConv_T8_CC4 = 0x4000
ADC_ExternalTrigInjecConv_T5_TRGO = 0x5000
ADC_ExternalTrigInjecConv_T5_CC4 = 0x6000
ADC_InjectedChannel_1 = 0x14
ADC_InjectedChannel_2 = 0x18
ADC_InjectedChannel_3 = 0x1C
ADC_InjectedChannel_4 = 0x20
ADC_AnalogWatchdog_SingleRegEnable = 0x800200
ADC_AnalogWatchdog_SingleInjecEnable = 0x400200
ADC_AnalogWatchdog_SingleRegOrInjecEnable = 0xC00200
ADC_AnalogWatchdog_AllRegEnable = 0x800000
ADC_AnalogWatchdog_AllInjecEnable = 0x400000
ADC_AnalogWatchdog_AllRegAllInjecEnable = 0xC00000
ADC_AnalogWatchdog_None = 0x0
ADC_IT_EOC = 0x220
ADC_IT_AWD = 0x140
ADC_IT_JEOC = 0x480
ADC_FLAG_AWD = 0x1
ADC_FLAG_EOC = 0x2
ADC_FLAG_JEOC = 0x4
ADC_FLAG_JSTRT = 0x8
ADC_FLAG_STRT = 0x10
# struct ADC_InitTypeDef

class ADC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_Mode',	ctypes.c_uint32),
		('ADC_ScanConvMode',	ctypes.c_uint32),
		('ADC_ContinuousConvMode',	ctypes.c_uint32),
		('ADC_ExternalTrigConv',	ctypes.c_uint32),
		('ADC_DataAlign',	ctypes.c_uint32),
		('ADC_NbrOfChannel',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_can.h : 

# empty define __STM32F10x_CAN_H
CAN_InitStatus_Failed = 0x0
CAN_InitStatus_Success = 0x1
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
CAN_Id_Standard = 0x0
CAN_Id_Extended = 0x4
CAN_RTR_Data = 0x0
CAN_RTR_Remote = 0x2
CAN_TxStatus_Failed = 0x0
CAN_TxStatus_Ok = 0x1
CAN_TxStatus_Pending = 0x2
CAN_TxStatus_NoMailBox = 0x4
CAN_FIFO0 = 0x0
CAN_FIFO1 = 0x1
CAN_Sleep_Failed = 0x0
CAN_Sleep_Ok = 0x1
CAN_WakeUp_Failed = 0x0
CAN_WakeUp_Ok = 0x1
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
CANINITFAILED = 0x0
CANINITOK = 0x1
CAN_FilterFIFO0 = 0x0
CAN_FilterFIFO1 = 0x1
CAN_ID_STD = 0x0
CAN_ID_EXT = 0x4
CAN_RTR_DATA = 0x0
CAN_RTR_REMOTE = 0x2
CANTXFAILE = 0x0
CANTXOK = 0x1
CANTXPENDING = 0x2
CAN_NO_MB = 0x4
CANSLEEPFAILED = 0x0
CANSLEEPOK = 0x1
CANWAKEUPFAILED = 0x0
CANWAKEUPOK = 0x1
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

# file stm32f10x_crc.h : 

# empty define __STM32F10x_CRC_H
# ----------------------------------------

# file stm32f10x_bkp.h : 

# empty define __STM32F10x_BKP_H
BKP_TamperPinLevel_High = 0x0
BKP_TamperPinLevel_Low = 0x1
BKP_RTCOutputSource_None = 0x0
BKP_RTCOutputSource_CalibClock = 0x80
BKP_RTCOutputSource_Alarm = 0x100
BKP_RTCOutputSource_Second = 0x300
BKP_DR1 = 0x4
BKP_DR2 = 0x8
BKP_DR3 = 0xC
BKP_DR4 = 0x10
BKP_DR5 = 0x14
BKP_DR6 = 0x18
BKP_DR7 = 0x1C
BKP_DR8 = 0x20
BKP_DR9 = 0x24
BKP_DR10 = 0x28
BKP_DR11 = 0x40
BKP_DR12 = 0x44
BKP_DR13 = 0x48
BKP_DR14 = 0x4C
BKP_DR15 = 0x50
BKP_DR16 = 0x54
BKP_DR17 = 0x58
BKP_DR18 = 0x5C
BKP_DR19 = 0x60
BKP_DR20 = 0x64
BKP_DR21 = 0x68
BKP_DR22 = 0x6C
BKP_DR23 = 0x70
BKP_DR24 = 0x74
BKP_DR25 = 0x78
BKP_DR26 = 0x7C
BKP_DR27 = 0x80
BKP_DR28 = 0x84
BKP_DR29 = 0x88
BKP_DR30 = 0x8C
BKP_DR31 = 0x90
BKP_DR32 = 0x94
BKP_DR33 = 0x98
BKP_DR34 = 0x9C
BKP_DR35 = 0xA0
BKP_DR36 = 0xA4
BKP_DR37 = 0xA8
BKP_DR38 = 0xAC
BKP_DR39 = 0xB0
BKP_DR40 = 0xB4
BKP_DR41 = 0xB8
BKP_DR42 = 0xBC
# ----------------------------------------

# file stm32f10x_fsmc.h : 

# empty define __STM32F10x_FSMC_H
FSMC_Bank1_NORSRAM1 = 0x0
FSMC_Bank1_NORSRAM2 = 0x2
FSMC_Bank1_NORSRAM3 = 0x4
FSMC_Bank1_NORSRAM4 = 0x6
FSMC_Bank2_NAND = 0x10
FSMC_Bank3_NAND = 0x100
FSMC_Bank4_PCCARD = 0x1000
FSMC_DataAddressMux_Disable = 0x0
FSMC_DataAddressMux_Enable = 0x2
FSMC_MemoryType_SRAM = 0x0
FSMC_MemoryType_PSRAM = 0x4
FSMC_MemoryType_NOR = 0x8
FSMC_MemoryDataWidth_8b = 0x0
FSMC_MemoryDataWidth_16b = 0x10
FSMC_BurstAccessMode_Disable = 0x0
FSMC_BurstAccessMode_Enable = 0x100
FSMC_AsynchronousWait_Disable = 0x0
FSMC_AsynchronousWait_Enable = 0x8000
FSMC_WaitSignalPolarity_Low = 0x0
FSMC_WaitSignalPolarity_High = 0x200
FSMC_WrapMode_Disable = 0x0
FSMC_WrapMode_Enable = 0x400
FSMC_WaitSignalActive_BeforeWaitState = 0x0
FSMC_WaitSignalActive_DuringWaitState = 0x800
FSMC_WriteOperation_Disable = 0x0
FSMC_WriteOperation_Enable = 0x1000
FSMC_WaitSignal_Disable = 0x0
FSMC_WaitSignal_Enable = 0x2000
FSMC_ExtendedMode_Disable = 0x0
FSMC_ExtendedMode_Enable = 0x4000
FSMC_WriteBurst_Disable = 0x0
FSMC_WriteBurst_Enable = 0x80000
FSMC_AccessMode_A = 0x0
FSMC_AccessMode_B = 0x10000000
FSMC_AccessMode_C = 0x20000000
FSMC_AccessMode_D = 0x30000000
FSMC_Waitfeature_Disable = 0x0
FSMC_Waitfeature_Enable = 0x2
FSMC_ECC_Disable = 0x0
FSMC_ECC_Enable = 0x40
FSMC_ECCPageSize_256Bytes = 0x0
FSMC_ECCPageSize_512Bytes = 0x20000
FSMC_ECCPageSize_1024Bytes = 0x40000
FSMC_ECCPageSize_2048Bytes = 0x60000
FSMC_ECCPageSize_4096Bytes = 0x80000
FSMC_ECCPageSize_8192Bytes = 0xA0000
FSMC_IT_RisingEdge = 0x8
FSMC_IT_Level = 0x10
FSMC_IT_FallingEdge = 0x20
FSMC_FLAG_RisingEdge = 0x1
FSMC_FLAG_Level = 0x2
FSMC_FLAG_FallingEdge = 0x4
FSMC_FLAG_FEMPT = 0x40
# struct FSMC_NORSRAMTimingInitTypeDef

class FSMC_NORSRAMTimingInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('FSMC_AddressSetupTime',	ctypes.c_uint32),
		('FSMC_AddressHoldTime',	ctypes.c_uint32),
		('FSMC_DataSetupTime',	ctypes.c_uint32),
		('FSMC_BusTurnAroundDuration',	ctypes.c_uint32),
		('FSMC_CLKDivision',	ctypes.c_uint32),
		('FSMC_DataLatency',	ctypes.c_uint32),
		('FSMC_AccessMode',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_NORSRAMInitTypeDef
# struct FSMC_NORSRAMInitTypeDef : field is class : FSMC_ReadWriteTimingStruct
# struct FSMC_NAND_PCCARDTimingInitTypeDef

class FSMC_NAND_PCCARDTimingInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('FSMC_SetupTime',	ctypes.c_uint32),
		('FSMC_WaitSetupTime',	ctypes.c_uint32),
		('FSMC_HoldSetupTime',	ctypes.c_uint32),
		('FSMC_HiZSetupTime',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_NANDInitTypeDef
# struct FSMC_NANDInitTypeDef : field is class : FSMC_CommonSpaceTimingStruct
# struct FSMC_PCCARDInitTypeDef
# struct FSMC_PCCARDInitTypeDef : field is class : FSMC_CommonSpaceTimingStruct
# ----------------------------------------

# file misc.h : 

# empty define __MISC_H
NVIC_VectTab_RAM = 0x20000000
NVIC_VectTab_FLASH = 0x8000000
NVIC_LP_SEVONPEND = 0x10
NVIC_LP_SLEEPDEEP = 0x4
NVIC_LP_SLEEPONEXIT = 0x2
NVIC_PriorityGroup_0 = 0x700
NVIC_PriorityGroup_1 = 0x600
NVIC_PriorityGroup_2 = 0x500
NVIC_PriorityGroup_3 = 0x400
NVIC_PriorityGroup_4 = 0x300
SysTick_CLKSource_HCLK_Div8 = 0xFFFFFFFB
SysTick_CLKSource_HCLK = 0x4
# struct NVIC_InitTypeDef

class NVIC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('NVIC_IRQChannel',	ctypes.c_uint8),
		('NVIC_IRQChannelPreemptionPriority',	ctypes.c_uint8),
		('NVIC_IRQChannelSubPriority',	ctypes.c_uint8),
		('NVIC_IRQChannelCmd',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_gpio.h : 

# Enum GPIOSpeed_TypeDef
GPIO_Speed_10MHz = 0x1
GPIO_Speed_2MHz = 0x2
GPIO_Speed_50MHz = 0x3
# Enum GPIOMode_TypeDef
GPIO_Mode_AIN = 0x0
GPIO_Mode_IN_FLOATING = 0x4
GPIO_Mode_IPD = 0x28
GPIO_Mode_IPU = 0x48
GPIO_Mode_Out_OD = 0x14
GPIO_Mode_Out_PP = 0x10
GPIO_Mode_AF_OD = 0x1C
GPIO_Mode_AF_PP = 0x18
# Enum BitAction
Bit_RESET = 0x0
Bit_SET = 0x1
# empty define __STM32F10x_GPIO_H
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
GPIO_Remap_SPI1 = 0x1
GPIO_Remap_I2C1 = 0x2
GPIO_Remap_USART1 = 0x4
GPIO_Remap_USART2 = 0x8
GPIO_PartialRemap_USART3 = 0x140010
GPIO_FullRemap_USART3 = 0x140030
GPIO_PartialRemap_TIM1 = 0x160040
GPIO_FullRemap_TIM1 = 0x1600C0
GPIO_PartialRemap1_TIM2 = 0x180100
GPIO_PartialRemap2_TIM2 = 0x180200
GPIO_FullRemap_TIM2 = 0x180300
GPIO_PartialRemap_TIM3 = 0x1A0800
GPIO_FullRemap_TIM3 = 0x1A0C00
GPIO_Remap_TIM4 = 0x1000
GPIO_Remap1_CAN1 = 0x1D4000
GPIO_Remap2_CAN1 = 0x1D6000
GPIO_Remap_PD01 = 0x8000
GPIO_Remap_TIM5CH4_LSI = 0x200001
GPIO_Remap_ADC1_ETRGINJ = 0x200002
GPIO_Remap_ADC1_ETRGREG = 0x200004
GPIO_Remap_ADC2_ETRGINJ = 0x200008
GPIO_Remap_ADC2_ETRGREG = 0x200010
GPIO_Remap_ETH = 0x200020
GPIO_Remap_CAN2 = 0x200040
GPIO_Remap_SWJ_NoJTRST = 0x300100
GPIO_Remap_SWJ_JTAGDisable = 0x300200
GPIO_Remap_SWJ_Disable = 0x300400
GPIO_Remap_SPI3 = 0x201100
GPIO_Remap_TIM2ITR1_PTP_SOF = 0x202000
GPIO_Remap_PTP_PPS = 0x204000
GPIO_Remap_TIM15 = 0x80000001
GPIO_Remap_TIM16 = 0x80000002
GPIO_Remap_TIM17 = 0x80000004
GPIO_Remap_CEC = 0x80000008
GPIO_Remap_TIM1_DMA = 0x80000010
GPIO_Remap_TIM9 = 0x80000020
GPIO_Remap_TIM10 = 0x80000040
GPIO_Remap_TIM11 = 0x80000080
GPIO_Remap_TIM13 = 0x80000100
GPIO_Remap_TIM14 = 0x80000200
GPIO_Remap_FSMC_NADV = 0x80000400
GPIO_Remap_TIM67_DAC_DMA = 0x80000800
GPIO_Remap_TIM12 = 0x80001000
GPIO_Remap_MISC = 0x80002000
GPIO_PortSourceGPIOA = 0x0
GPIO_PortSourceGPIOB = 0x1
GPIO_PortSourceGPIOC = 0x2
GPIO_PortSourceGPIOD = 0x3
GPIO_PortSourceGPIOE = 0x4
GPIO_PortSourceGPIOF = 0x5
GPIO_PortSourceGPIOG = 0x6
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
GPIO_ETH_MediaInterface_MII = 0x0
GPIO_ETH_MediaInterface_RMII = 0x1
# struct GPIO_InitTypeDef

class GPIO_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('GPIO_Pin',	ctypes.c_uint16),
		('GPIO_Speed',	ctypes.c_uint32),
		('GPIO_Mode',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_dma.h : 

# empty define __STM32F10x_DMA_H
DMA_DIR_PeripheralDST = 0x10
DMA_DIR_PeripheralSRC = 0x0
DMA_PeripheralInc_Enable = 0x40
DMA_PeripheralInc_Disable = 0x0
DMA_MemoryInc_Enable = 0x80
DMA_MemoryInc_Disable = 0x0
DMA_PeripheralDataSize_Byte = 0x0
DMA_PeripheralDataSize_HalfWord = 0x100
DMA_PeripheralDataSize_Word = 0x200
DMA_MemoryDataSize_Byte = 0x0
DMA_MemoryDataSize_HalfWord = 0x400
DMA_MemoryDataSize_Word = 0x800
DMA_Mode_Circular = 0x20
DMA_Mode_Normal = 0x0
DMA_Priority_VeryHigh = 0x3000
DMA_Priority_High = 0x2000
DMA_Priority_Medium = 0x1000
DMA_Priority_Low = 0x0
DMA_M2M_Enable = 0x4000
DMA_M2M_Disable = 0x0
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

# file stm32f10x_i2c.h : 

# empty define __STM32F10x_I2C_H
I2C_Mode_I2C = 0x0
I2C_Mode_SMBusDevice = 0x2
I2C_Mode_SMBusHost = 0xA
I2C_DutyCycle_16_9 = 0x4000
I2C_DutyCycle_2 = 0xBFFF
I2C_Ack_Enable = 0x400
I2C_Ack_Disable = 0x0
I2C_Direction_Transmitter = 0x0
I2C_Direction_Receiver = 0x1
I2C_AcknowledgedAddress_7bit = 0x4000
I2C_AcknowledgedAddress_10bit = 0xC000
I2C_Register_CR1 = 0x0
I2C_Register_CR2 = 0x4
I2C_Register_OAR1 = 0x8
I2C_Register_OAR2 = 0xC
I2C_Register_DR = 0x10
I2C_Register_SR1 = 0x14
I2C_Register_SR2 = 0x18
I2C_Register_CCR = 0x1C
I2C_Register_TRISE = 0x20
I2C_SMBusAlert_Low = 0x2000
I2C_SMBusAlert_High = 0xDFFF
I2C_PECPosition_Next = 0x800
I2C_PECPosition_Current = 0xF7FF
I2C_NACKPosition_Next = 0x800
I2C_NACKPosition_Current = 0xF7FF
I2C_IT_BUF = 0x400
I2C_IT_EVT = 0x200
I2C_IT_ERR = 0x100
I2C_IT_SMBALERT = 0x1008000
I2C_IT_TIMEOUT = 0x1004000
I2C_IT_PECERR = 0x1001000
I2C_IT_OVR = 0x1000800
I2C_IT_AF = 0x1000400
I2C_IT_ARLO = 0x1000200
I2C_IT_BERR = 0x1000100
I2C_IT_TXE = 0x6000080
I2C_IT_RXNE = 0x6000040
I2C_IT_STOPF = 0x2000010
I2C_IT_ADD10 = 0x2000008
I2C_IT_BTF = 0x2000004
I2C_IT_ADDR = 0x2000002
I2C_IT_SB = 0x2000001
I2C_FLAG_DUALF = 0x800000
I2C_FLAG_SMBHOST = 0x400000
I2C_FLAG_SMBDEFAULT = 0x200000
I2C_FLAG_GENCALL = 0x100000
I2C_FLAG_TRA = 0x40000
I2C_FLAG_BUSY = 0x20000
I2C_FLAG_MSL = 0x10000
I2C_FLAG_SMBALERT = 0x10008000
I2C_FLAG_TIMEOUT = 0x10004000
I2C_FLAG_PECERR = 0x10001000
I2C_FLAG_OVR = 0x10000800
I2C_FLAG_AF = 0x10000400
I2C_FLAG_ARLO = 0x10000200
I2C_FLAG_BERR = 0x10000100
I2C_FLAG_TXE = 0x10000080
I2C_FLAG_RXNE = 0x10000040
I2C_FLAG_STOPF = 0x10000010
I2C_FLAG_ADD10 = 0x10000008
I2C_FLAG_BTF = 0x10000004
I2C_FLAG_ADDR = 0x10000002
I2C_FLAG_SB = 0x10000001
I2C_EVENT_MASTER_MODE_SELECT = 0x30001
I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED = 0x70082
I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED = 0x30002
I2C_EVENT_MASTER_MODE_ADDRESS10 = 0x30008
I2C_EVENT_MASTER_BYTE_RECEIVED = 0x30040
I2C_EVENT_MASTER_BYTE_TRANSMITTING = 0x70080
I2C_EVENT_MASTER_BYTE_TRANSMITTED = 0x70084
I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED = 0x20002
I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED = 0x60082
I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED = 0x820000
I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED = 0x860080
I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED = 0x120000
I2C_EVENT_SLAVE_BYTE_RECEIVED = 0x20040
I2C_EVENT_SLAVE_STOP_DETECTED = 0x10
I2C_EVENT_SLAVE_BYTE_TRANSMITTED = 0x60084
I2C_EVENT_SLAVE_BYTE_TRANSMITTING = 0x60080
I2C_EVENT_SLAVE_ACK_FAILURE = 0x400
# struct I2C_InitTypeDef

class I2C_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('I2C_ClockSpeed',	ctypes.c_uint32),
		('I2C_Mode',	ctypes.c_uint16),
		('I2C_DutyCycle',	ctypes.c_uint16),
		('I2C_OwnAddress1',	ctypes.c_uint16),
		('I2C_Ack',	ctypes.c_uint16),
		('I2C_AcknowledgedAddress',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_flash.h : 

# Enum FLASH_Status
FLASH_BUSY = 0x1
FLASH_ERROR_PG = 0x2
FLASH_ERROR_WRP = 0x3
FLASH_COMPLETE = 0x4
FLASH_TIMEOUT = 0x5
# empty define __STM32F10x_FLASH_H
FLASH_Latency_0 = 0x0
FLASH_Latency_1 = 0x1
FLASH_Latency_2 = 0x2
FLASH_HalfCycleAccess_Enable = 0x8
FLASH_HalfCycleAccess_Disable = 0x0
FLASH_PrefetchBuffer_Enable = 0x10
FLASH_PrefetchBuffer_Disable = 0x0
FLASH_WRProt_Pages0to3 = 0x1
FLASH_WRProt_Pages4to7 = 0x2
FLASH_WRProt_Pages8to11 = 0x4
FLASH_WRProt_Pages12to15 = 0x8
FLASH_WRProt_Pages16to19 = 0x10
FLASH_WRProt_Pages20to23 = 0x20
FLASH_WRProt_Pages24to27 = 0x40
FLASH_WRProt_Pages28to31 = 0x80
FLASH_WRProt_Pages32to35 = 0x100
FLASH_WRProt_Pages36to39 = 0x200
FLASH_WRProt_Pages40to43 = 0x400
FLASH_WRProt_Pages44to47 = 0x800
FLASH_WRProt_Pages48to51 = 0x1000
FLASH_WRProt_Pages52to55 = 0x2000
FLASH_WRProt_Pages56to59 = 0x4000
FLASH_WRProt_Pages60to63 = 0x8000
FLASH_WRProt_Pages64to67 = 0x10000
FLASH_WRProt_Pages68to71 = 0x20000
FLASH_WRProt_Pages72to75 = 0x40000
FLASH_WRProt_Pages76to79 = 0x80000
FLASH_WRProt_Pages80to83 = 0x100000
FLASH_WRProt_Pages84to87 = 0x200000
FLASH_WRProt_Pages88to91 = 0x400000
FLASH_WRProt_Pages92to95 = 0x800000
FLASH_WRProt_Pages96to99 = 0x1000000
FLASH_WRProt_Pages100to103 = 0x2000000
FLASH_WRProt_Pages104to107 = 0x4000000
FLASH_WRProt_Pages108to111 = 0x8000000
FLASH_WRProt_Pages112to115 = 0x10000000
FLASH_WRProt_Pages116to119 = 0x20000000
FLASH_WRProt_Pages120to123 = 0x40000000
FLASH_WRProt_Pages124to127 = 0x80000000
FLASH_WRProt_Pages0to1 = 0x1
FLASH_WRProt_Pages2to3 = 0x2
FLASH_WRProt_Pages4to5 = 0x4
FLASH_WRProt_Pages6to7 = 0x8
FLASH_WRProt_Pages8to9 = 0x10
FLASH_WRProt_Pages10to11 = 0x20
FLASH_WRProt_Pages12to13 = 0x40
FLASH_WRProt_Pages14to15 = 0x80
FLASH_WRProt_Pages16to17 = 0x100
FLASH_WRProt_Pages18to19 = 0x200
FLASH_WRProt_Pages20to21 = 0x400
FLASH_WRProt_Pages22to23 = 0x800
FLASH_WRProt_Pages24to25 = 0x1000
FLASH_WRProt_Pages26to27 = 0x2000
FLASH_WRProt_Pages28to29 = 0x4000
FLASH_WRProt_Pages30to31 = 0x8000
FLASH_WRProt_Pages32to33 = 0x10000
FLASH_WRProt_Pages34to35 = 0x20000
FLASH_WRProt_Pages36to37 = 0x40000
FLASH_WRProt_Pages38to39 = 0x80000
FLASH_WRProt_Pages40to41 = 0x100000
FLASH_WRProt_Pages42to43 = 0x200000
FLASH_WRProt_Pages44to45 = 0x400000
FLASH_WRProt_Pages46to47 = 0x800000
FLASH_WRProt_Pages48to49 = 0x1000000
FLASH_WRProt_Pages50to51 = 0x2000000
FLASH_WRProt_Pages52to53 = 0x4000000
FLASH_WRProt_Pages54to55 = 0x8000000
FLASH_WRProt_Pages56to57 = 0x10000000
FLASH_WRProt_Pages58to59 = 0x20000000
FLASH_WRProt_Pages60to61 = 0x40000000
FLASH_WRProt_Pages62to127 = 0x80000000
FLASH_WRProt_Pages62to255 = 0x80000000
FLASH_WRProt_Pages62to511 = 0x80000000
FLASH_WRProt_AllPages = 0xFFFFFFFF
OB_IWDG_SW = 0x1
OB_IWDG_HW = 0x0
OB_STOP_NoRST = 0x2
OB_STOP_RST = 0x0
OB_STDBY_NoRST = 0x4
OB_STDBY_RST = 0x0
# Skip FLASH_BOOT_Bank1 : no need parse
# Skip FLASH_BOOT_Bank2 : no need parse
# Skip FLASH_IT_BANK2_ERROR : no need parse
# Skip FLASH_IT_BANK2_EOP : no need parse
FLASH_IT_BANK1_ERROR = 0x400
FLASH_IT_BANK1_EOP = 0x1000
FLASH_IT_ERROR = 0x400
FLASH_IT_EOP = 0x1000
FLASH_IT_ERROR = 0x400
FLASH_IT_EOP = 0x1000
FLASH_IT_BANK1_ERROR = 0x400
FLASH_IT_BANK1_EOP = 0x1000
# Skip FLASH_FLAG_BANK2_BSY : no need parse
# Skip FLASH_FLAG_BANK2_EOP : no need parse
# Skip FLASH_FLAG_BANK2_PGERR : no need parse
# Skip FLASH_FLAG_BANK2_WRPRTERR : no need parse
FLASH_FLAG_BANK1_BSY = 0x1
FLASH_FLAG_BANK1_EOP = 0x20
FLASH_FLAG_BANK1_PGERR = 0x4
FLASH_FLAG_BANK1_WRPRTERR = 0x10
FLASH_FLAG_BSY = 0x1
FLASH_FLAG_EOP = 0x20
FLASH_FLAG_PGERR = 0x4
FLASH_FLAG_WRPRTERR = 0x10
FLASH_FLAG_OPTERR = 0x1
FLASH_FLAG_BSY = 0x1
FLASH_FLAG_EOP = 0x20
FLASH_FLAG_PGERR = 0x4
FLASH_FLAG_WRPRTERR = 0x10
FLASH_FLAG_OPTERR = 0x1
FLASH_FLAG_BANK1_BSY = 0x1
FLASH_FLAG_BANK1_EOP = 0x20
FLASH_FLAG_BANK1_PGERR = 0x4
FLASH_FLAG_BANK1_WRPRTERR = 0x10
# ----------------------------------------

# file stm32f10x_dac.h : 

# empty define __STM32F10x_DAC_H
DAC_Trigger_None = 0x0
DAC_Trigger_T6_TRGO = 0x4
DAC_Trigger_T8_TRGO = 0xC
DAC_Trigger_T3_TRGO = 0xC
DAC_Trigger_T7_TRGO = 0x14
DAC_Trigger_T5_TRGO = 0x1C
DAC_Trigger_T15_TRGO = 0x1C
DAC_Trigger_T2_TRGO = 0x24
DAC_Trigger_T4_TRGO = 0x2C
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
# Skip DAC_IT_DMAUDR : no need parse
# Skip DAC_FLAG_DMAUDR : no need parse
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

# file stm32f10x_cec.h : 

# empty define __STM32F10x_CEC_H
CEC_BitTimingStdMode = 0x0
CEC_BitTimingErrFreeMode = 0x4
CEC_BitPeriodStdMode = 0x0
CEC_BitPeriodFlexibleMode = 0x8
CEC_IT_TERR = 0x4
CEC_IT_TBTRF = 0x8
CEC_IT_RERR = 0x40
CEC_IT_RBTF = 0x80
CEC_FLAG_BTE = 0x10010000
CEC_FLAG_BPE = 0x10020000
CEC_FLAG_RBTFE = 0x10040000
CEC_FLAG_SBE = 0x10080000
CEC_FLAG_ACKE = 0x10100000
CEC_FLAG_LINE = 0x10200000
CEC_FLAG_TBTFE = 0x10400000
CEC_FLAG_TEOM = 0x2
CEC_FLAG_TERR = 0x4
CEC_FLAG_TBTRF = 0x8
CEC_FLAG_RSOM = 0x10
CEC_FLAG_REOM = 0x20
CEC_FLAG_RERR = 0x40
CEC_FLAG_RBTF = 0x80
# struct CEC_InitTypeDef

class CEC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CEC_BitTimingMode',	ctypes.c_uint16),
		('CEC_BitPeriodMode',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_wwdg.h : 

# empty define __STM32F10x_WWDG_H
WWDG_Prescaler_1 = 0x0
WWDG_Prescaler_2 = 0x80
WWDG_Prescaler_4 = 0x100
WWDG_Prescaler_8 = 0x180
# ----------------------------------------

# file stm32f10x_tim.h : 

# empty define __STM32F10x_TIM_H
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
		('TIM_Period',	ctypes.c_uint16),
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
		('TIM_Pulse',	ctypes.c_uint16),
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

# file stm32f10x_rcc.h : 

# empty define __STM32F10x_RCC_H
RCC_HSE_OFF = 0x0
RCC_HSE_ON = 0x10000
RCC_HSE_Bypass = 0x40000
RCC_PLLSource_HSI_Div2 = 0x0
RCC_PLLSource_HSE_Div1 = 0x10000
RCC_PLLSource_HSE_Div2 = 0x30000
# Skip RCC_PLLSource_PREDIV1 : no need parse
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
RCC_PLLMul_4 = 0x80000
RCC_PLLMul_5 = 0xC0000
RCC_PLLMul_6 = 0x100000
RCC_PLLMul_7 = 0x140000
RCC_PLLMul_8 = 0x180000
RCC_PLLMul_9 = 0x1C0000
# Skip RCC_PLLMul_6_5 : no need parse
# Skip RCC_PREDIV1_Div1 : no need parse
# Skip RCC_PREDIV1_Div2 : no need parse
# Skip RCC_PREDIV1_Div3 : no need parse
# Skip RCC_PREDIV1_Div4 : no need parse
# Skip RCC_PREDIV1_Div5 : no need parse
# Skip RCC_PREDIV1_Div6 : no need parse
# Skip RCC_PREDIV1_Div7 : no need parse
# Skip RCC_PREDIV1_Div8 : no need parse
# Skip RCC_PREDIV1_Div9 : no need parse
# Skip RCC_PREDIV1_Div10 : no need parse
# Skip RCC_PREDIV1_Div11 : no need parse
# Skip RCC_PREDIV1_Div12 : no need parse
# Skip RCC_PREDIV1_Div13 : no need parse
# Skip RCC_PREDIV1_Div14 : no need parse
# Skip RCC_PREDIV1_Div15 : no need parse
# Skip RCC_PREDIV1_Div16 : no need parse
# Skip RCC_PREDIV1_Source_HSE : no need parse
# Skip RCC_PREDIV1_Source_PLL2 : no need parse
# Skip RCC_PREDIV1_Source_HSE : no need parse
# Skip RCC_PREDIV2_Div1 : no need parse
# Skip RCC_PREDIV2_Div2 : no need parse
# Skip RCC_PREDIV2_Div3 : no need parse
# Skip RCC_PREDIV2_Div4 : no need parse
# Skip RCC_PREDIV2_Div5 : no need parse
# Skip RCC_PREDIV2_Div6 : no need parse
# Skip RCC_PREDIV2_Div7 : no need parse
# Skip RCC_PREDIV2_Div8 : no need parse
# Skip RCC_PREDIV2_Div9 : no need parse
# Skip RCC_PREDIV2_Div10 : no need parse
# Skip RCC_PREDIV2_Div11 : no need parse
# Skip RCC_PREDIV2_Div12 : no need parse
# Skip RCC_PREDIV2_Div13 : no need parse
# Skip RCC_PREDIV2_Div14 : no need parse
# Skip RCC_PREDIV2_Div15 : no need parse
# Skip RCC_PREDIV2_Div16 : no need parse
# Skip RCC_PLL2Mul_8 : no need parse
# Skip RCC_PLL2Mul_9 : no need parse
# Skip RCC_PLL2Mul_10 : no need parse
# Skip RCC_PLL2Mul_11 : no need parse
# Skip RCC_PLL2Mul_12 : no need parse
# Skip RCC_PLL2Mul_13 : no need parse
# Skip RCC_PLL2Mul_14 : no need parse
# Skip RCC_PLL2Mul_16 : no need parse
# Skip RCC_PLL2Mul_20 : no need parse
# Skip RCC_PLL3Mul_8 : no need parse
# Skip RCC_PLL3Mul_9 : no need parse
# Skip RCC_PLL3Mul_10 : no need parse
# Skip RCC_PLL3Mul_11 : no need parse
# Skip RCC_PLL3Mul_12 : no need parse
# Skip RCC_PLL3Mul_13 : no need parse
# Skip RCC_PLL3Mul_14 : no need parse
# Skip RCC_PLL3Mul_16 : no need parse
# Skip RCC_PLL3Mul_20 : no need parse
RCC_SYSCLKSource_HSI = 0x0
RCC_SYSCLKSource_HSE = 0x1
RCC_SYSCLKSource_PLLCLK = 0x2
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
RCC_IT_LSIRDY = 0x1
RCC_IT_LSERDY = 0x2
RCC_IT_HSIRDY = 0x4
RCC_IT_HSERDY = 0x8
RCC_IT_PLLRDY = 0x10
RCC_IT_CSS = 0x80
# Skip RCC_IT_PLL2RDY : no need parse
# Skip RCC_IT_PLL3RDY : no need parse
RCC_USBCLKSource_PLLCLK_1Div5 = 0x0
RCC_USBCLKSource_PLLCLK_Div1 = 0x1
# Skip RCC_OTGFSCLKSource_PLLVCO_Div3 : no need parse
# Skip RCC_OTGFSCLKSource_PLLVCO_Div2 : no need parse
# Skip RCC_I2S2CLKSource_SYSCLK : no need parse
# Skip RCC_I2S2CLKSource_PLL3_VCO : no need parse
# Skip RCC_I2S3CLKSource_SYSCLK : no need parse
# Skip RCC_I2S3CLKSource_PLL3_VCO : no need parse
RCC_PCLK2_Div2 = 0x0
RCC_PCLK2_Div4 = 0x4000
RCC_PCLK2_Div6 = 0x8000
RCC_PCLK2_Div8 = 0xC000
RCC_LSE_OFF = 0x0
RCC_LSE_ON = 0x1
RCC_LSE_Bypass = 0x4
RCC_RTCCLKSource_LSE = 0x100
RCC_RTCCLKSource_LSI = 0x200
RCC_RTCCLKSource_HSE_Div128 = 0x300
RCC_AHBPeriph_DMA1 = 0x1
RCC_AHBPeriph_DMA2 = 0x2
RCC_AHBPeriph_SRAM = 0x4
RCC_AHBPeriph_FLITF = 0x10
RCC_AHBPeriph_CRC = 0x40
RCC_AHBPeriph_FSMC = 0x100
RCC_AHBPeriph_SDIO = 0x400
# Skip RCC_AHBPeriph_OTG_FS : no need parse
# Skip RCC_AHBPeriph_ETH_MAC : no need parse
# Skip RCC_AHBPeriph_ETH_MAC_Tx : no need parse
# Skip RCC_AHBPeriph_ETH_MAC_Rx : no need parse
RCC_APB2Periph_AFIO = 0x1
RCC_APB2Periph_GPIOA = 0x4
RCC_APB2Periph_GPIOB = 0x8
RCC_APB2Periph_GPIOC = 0x10
RCC_APB2Periph_GPIOD = 0x20
RCC_APB2Periph_GPIOE = 0x40
RCC_APB2Periph_GPIOF = 0x80
RCC_APB2Periph_GPIOG = 0x100
RCC_APB2Periph_ADC1 = 0x200
RCC_APB2Periph_ADC2 = 0x400
RCC_APB2Periph_TIM1 = 0x800
RCC_APB2Periph_SPI1 = 0x1000
RCC_APB2Periph_TIM8 = 0x2000
RCC_APB2Periph_USART1 = 0x4000
RCC_APB2Periph_ADC3 = 0x8000
RCC_APB2Periph_TIM15 = 0x10000
RCC_APB2Periph_TIM16 = 0x20000
RCC_APB2Periph_TIM17 = 0x40000
RCC_APB2Periph_TIM9 = 0x80000
RCC_APB2Periph_TIM10 = 0x100000
RCC_APB2Periph_TIM11 = 0x200000
RCC_APB1Periph_TIM2 = 0x1
RCC_APB1Periph_TIM3 = 0x2
RCC_APB1Periph_TIM4 = 0x4
RCC_APB1Periph_TIM5 = 0x8
RCC_APB1Periph_TIM6 = 0x10
RCC_APB1Periph_TIM7 = 0x20
RCC_APB1Periph_TIM12 = 0x40
RCC_APB1Periph_TIM13 = 0x80
RCC_APB1Periph_TIM14 = 0x100
RCC_APB1Periph_WWDG = 0x800
RCC_APB1Periph_SPI2 = 0x4000
RCC_APB1Periph_SPI3 = 0x8000
RCC_APB1Periph_USART2 = 0x20000
RCC_APB1Periph_USART3 = 0x40000
RCC_APB1Periph_UART4 = 0x80000
RCC_APB1Periph_UART5 = 0x100000
RCC_APB1Periph_I2C1 = 0x200000
RCC_APB1Periph_I2C2 = 0x400000
RCC_APB1Periph_USB = 0x800000
RCC_APB1Periph_CAN1 = 0x2000000
RCC_APB1Periph_CAN2 = 0x4000000
RCC_APB1Periph_BKP = 0x8000000
RCC_APB1Periph_PWR = 0x10000000
RCC_APB1Periph_DAC = 0x20000000
RCC_APB1Periph_CEC = 0x40000000
RCC_MCO_NoClock = 0x0
RCC_MCO_SYSCLK = 0x4
RCC_MCO_HSI = 0x5
RCC_MCO_HSE = 0x6
RCC_MCO_PLLCLK_Div2 = 0x7
# Skip RCC_MCO_PLL2CLK : no need parse
# Skip RCC_MCO_PLL3CLK_Div2 : no need parse
# Skip RCC_MCO_XT1 : no need parse
# Skip RCC_MCO_PLL3CLK : no need parse
RCC_FLAG_HSIRDY = 0x21
RCC_FLAG_HSERDY = 0x31
RCC_FLAG_PLLRDY = 0x39
RCC_FLAG_LSERDY = 0x41
RCC_FLAG_LSIRDY = 0x61
RCC_FLAG_PINRST = 0x7A
RCC_FLAG_PORRST = 0x7B
RCC_FLAG_SFTRST = 0x7C
RCC_FLAG_IWDGRST = 0x7D
RCC_FLAG_WWDGRST = 0x7E
RCC_FLAG_LPWRRST = 0x7F
# Skip RCC_FLAG_PLL2RDY : no need parse
# Skip RCC_FLAG_PLL3RDY : no need parse
# struct RCC_ClocksTypeDef

class RCC_ClocksTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SYSCLK_Frequency',	ctypes.c_uint32),
		('HCLK_Frequency',	ctypes.c_uint32),
		('PCLK1_Frequency',	ctypes.c_uint32),
		('PCLK2_Frequency',	ctypes.c_uint32),
		('ADCCLK_Frequency',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x_sdio.h : 

# empty define __STM32F10x_SDIO_H
SDIO_ClockEdge_Rising = 0x0
SDIO_ClockEdge_Falling = 0x2000
SDIO_ClockBypass_Disable = 0x0
SDIO_ClockBypass_Enable = 0x400
SDIO_ClockPowerSave_Disable = 0x0
SDIO_ClockPowerSave_Enable = 0x200
SDIO_BusWide_1b = 0x0
SDIO_BusWide_4b = 0x800
SDIO_BusWide_8b = 0x1000
SDIO_HardwareFlowControl_Disable = 0x0
SDIO_HardwareFlowControl_Enable = 0x4000
SDIO_PowerState_OFF = 0x0
SDIO_PowerState_ON = 0x3
SDIO_IT_CCRCFAIL = 0x1
SDIO_IT_DCRCFAIL = 0x2
SDIO_IT_CTIMEOUT = 0x4
SDIO_IT_DTIMEOUT = 0x8
SDIO_IT_TXUNDERR = 0x10
SDIO_IT_RXOVERR = 0x20
SDIO_IT_CMDREND = 0x40
SDIO_IT_CMDSENT = 0x80
SDIO_IT_DATAEND = 0x100
SDIO_IT_STBITERR = 0x200
SDIO_IT_DBCKEND = 0x400
SDIO_IT_CMDACT = 0x800
SDIO_IT_TXACT = 0x1000
SDIO_IT_RXACT = 0x2000
SDIO_IT_TXFIFOHE = 0x4000
SDIO_IT_RXFIFOHF = 0x8000
SDIO_IT_TXFIFOF = 0x10000
SDIO_IT_RXFIFOF = 0x20000
SDIO_IT_TXFIFOE = 0x40000
SDIO_IT_RXFIFOE = 0x80000
SDIO_IT_TXDAVL = 0x100000
SDIO_IT_RXDAVL = 0x200000
SDIO_IT_SDIOIT = 0x400000
SDIO_IT_CEATAEND = 0x800000
SDIO_Response_No = 0x0
SDIO_Response_Short = 0x40
SDIO_Response_Long = 0xC0
SDIO_Wait_No = 0x0
SDIO_Wait_IT = 0x100
SDIO_Wait_Pend = 0x200
SDIO_CPSM_Disable = 0x0
SDIO_CPSM_Enable = 0x400
SDIO_RESP1 = 0x0
SDIO_RESP2 = 0x4
SDIO_RESP3 = 0x8
SDIO_RESP4 = 0xC
SDIO_DataBlockSize_1b = 0x0
SDIO_DataBlockSize_2b = 0x10
SDIO_DataBlockSize_4b = 0x20
SDIO_DataBlockSize_8b = 0x30
SDIO_DataBlockSize_16b = 0x40
SDIO_DataBlockSize_32b = 0x50
SDIO_DataBlockSize_64b = 0x60
SDIO_DataBlockSize_128b = 0x70
SDIO_DataBlockSize_256b = 0x80
SDIO_DataBlockSize_512b = 0x90
SDIO_DataBlockSize_1024b = 0xA0
SDIO_DataBlockSize_2048b = 0xB0
SDIO_DataBlockSize_4096b = 0xC0
SDIO_DataBlockSize_8192b = 0xD0
SDIO_DataBlockSize_16384b = 0xE0
SDIO_TransferDir_ToCard = 0x0
SDIO_TransferDir_ToSDIO = 0x2
SDIO_TransferMode_Block = 0x0
SDIO_TransferMode_Stream = 0x4
SDIO_DPSM_Disable = 0x0
SDIO_DPSM_Enable = 0x1
SDIO_FLAG_CCRCFAIL = 0x1
SDIO_FLAG_DCRCFAIL = 0x2
SDIO_FLAG_CTIMEOUT = 0x4
SDIO_FLAG_DTIMEOUT = 0x8
SDIO_FLAG_TXUNDERR = 0x10
SDIO_FLAG_RXOVERR = 0x20
SDIO_FLAG_CMDREND = 0x40
SDIO_FLAG_CMDSENT = 0x80
SDIO_FLAG_DATAEND = 0x100
SDIO_FLAG_STBITERR = 0x200
SDIO_FLAG_DBCKEND = 0x400
SDIO_FLAG_CMDACT = 0x800
SDIO_FLAG_TXACT = 0x1000
SDIO_FLAG_RXACT = 0x2000
SDIO_FLAG_TXFIFOHE = 0x4000
SDIO_FLAG_RXFIFOHF = 0x8000
SDIO_FLAG_TXFIFOF = 0x10000
SDIO_FLAG_RXFIFOF = 0x20000
SDIO_FLAG_TXFIFOE = 0x40000
SDIO_FLAG_RXFIFOE = 0x80000
SDIO_FLAG_TXDAVL = 0x100000
SDIO_FLAG_RXDAVL = 0x200000
SDIO_FLAG_SDIOIT = 0x400000
SDIO_FLAG_CEATAEND = 0x800000
SDIO_ReadWaitMode_CLK = 0x1
SDIO_ReadWaitMode_DATA2 = 0x0
# struct SDIO_InitTypeDef

class SDIO_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SDIO_ClockEdge',	ctypes.c_uint32),
		('SDIO_ClockBypass',	ctypes.c_uint32),
		('SDIO_ClockPowerSave',	ctypes.c_uint32),
		('SDIO_BusWide',	ctypes.c_uint32),
		('SDIO_HardwareFlowControl',	ctypes.c_uint32),
		('SDIO_ClockDiv',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SDIO_CmdInitTypeDef

class SDIO_CmdInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SDIO_Argument',	ctypes.c_uint32),
		('SDIO_CmdIndex',	ctypes.c_uint32),
		('SDIO_Response',	ctypes.c_uint32),
		('SDIO_Wait',	ctypes.c_uint32),
		('SDIO_CPSM',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SDIO_DataInitTypeDef

class SDIO_DataInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SDIO_DataTimeOut',	ctypes.c_uint32),
		('SDIO_DataLength',	ctypes.c_uint32),
		('SDIO_DataBlockSize',	ctypes.c_uint32),
		('SDIO_TransferDir',	ctypes.c_uint32),
		('SDIO_TransferMode',	ctypes.c_uint32),
		('SDIO_DPSM',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f10x.h : 

# Enum FlagStatus , ITStatus
RESET = 0x0
SET = 0x1
# Enum FunctionalState
DISABLE = 0x0
ENABLE = 0x1
# Enum ErrorStatus
ERROR = 0x0
SUCCESS = 0x1
# empty define __STM32F10x_H
HSE_VALUE = 0x7A1200
HSE_VALUE = 0x7A1200
HSE_STARTUP_TIMEOUT = 0x500
HSI_VALUE = 0x7A1200
__STM32F10X_STDPERIPH_VERSION_MAIN = 0x3
__STM32F10X_STDPERIPH_VERSION_SUB1 = 0x5
__STM32F10X_STDPERIPH_VERSION_SUB2 = 0x0
__STM32F10X_STDPERIPH_VERSION_RC = 0x0
__STM32F10X_STDPERIPH_VERSION = 0x3050000
__MPU_PRESENT = 0x0
__MPU_PRESENT = 0x0
__NVIC_PRIO_BITS = 0x4
__Vendor_SysTickConfig = 0x0
HSEStartUp_TimeOut = 0x500
HSE_Value = 0x7A1200
HSI_Value = 0x7A1200
FLASH_BASE = 0x8000000
SRAM_BASE = 0x20000000
PERIPH_BASE = 0x40000000
SRAM_BB_BASE = 0x22000000
PERIPH_BB_BASE = 0x42000000
FSMC_R_BASE = 0xA0000000
APB1PERIPH_BASE = 0x40000000
APB2PERIPH_BASE = 0x40010000
AHBPERIPH_BASE = 0x40020000
TIM2_BASE = 0x40000000
TIM3_BASE = 0x40000400
TIM4_BASE = 0x40000800
TIM5_BASE = 0x40000C00
TIM6_BASE = 0x40001000
TIM7_BASE = 0x40001400
TIM12_BASE = 0x40001800
TIM13_BASE = 0x40001C00
TIM14_BASE = 0x40002000
RTC_BASE = 0x40002800
WWDG_BASE = 0x40002C00
IWDG_BASE = 0x40003000
SPI2_BASE = 0x40003800
SPI3_BASE = 0x40003C00
USART2_BASE = 0x40004400
USART3_BASE = 0x40004800
UART4_BASE = 0x40004C00
UART5_BASE = 0x40005000
I2C1_BASE = 0x40005400
I2C2_BASE = 0x40005800
CAN1_BASE = 0x40006400
CAN2_BASE = 0x40006800
BKP_BASE = 0x40006C00
PWR_BASE = 0x40007000
DAC_BASE = 0x40007400
CEC_BASE = 0x40007800
AFIO_BASE = 0x40010000
EXTI_BASE = 0x40010400
GPIOA_BASE = 0x40010800
GPIOB_BASE = 0x40010C00
GPIOC_BASE = 0x40011000
GPIOD_BASE = 0x40011400
GPIOE_BASE = 0x40011800
GPIOF_BASE = 0x40011C00
GPIOG_BASE = 0x40012000
ADC1_BASE = 0x40012400
ADC2_BASE = 0x40012800
TIM1_BASE = 0x40012C00
SPI1_BASE = 0x40013000
TIM8_BASE = 0x40013400
USART1_BASE = 0x40013800
ADC3_BASE = 0x40013C00
TIM15_BASE = 0x40014000
TIM16_BASE = 0x40014400
TIM17_BASE = 0x40014800
TIM9_BASE = 0x40014C00
TIM10_BASE = 0x40015000
TIM11_BASE = 0x40015400
SDIO_BASE = 0x40018000
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
CRC_BASE = 0x40023000
FLASH_R_BASE = 0x40022000
OB_BASE = 0x1FFFF800
ETH_BASE = 0x40028000
ETH_MAC_BASE = 0x40028000
ETH_MMC_BASE = 0x40028100
ETH_PTP_BASE = 0x40028700
ETH_DMA_BASE = 0x40029000
FSMC_Bank1_R_BASE = 0xA0000000
FSMC_Bank1E_R_BASE = 0xA0000104
FSMC_Bank2_R_BASE = 0xA0000060
FSMC_Bank3_R_BASE = 0xA0000080
FSMC_Bank4_R_BASE = 0xA00000A0
DBGMCU_BASE = 0xE0042000
TIM2 = 0x40000000
TIM3 = 0x40000400
TIM4 = 0x40000800
TIM5 = 0x40000C00
TIM6 = 0x40001000
TIM7 = 0x40001400
TIM12 = 0x40001800
TIM13 = 0x40001C00
TIM14 = 0x40002000
RTC = 0x40002800
WWDG = 0x40002C00
IWDG = 0x40003000
SPI2 = 0x40003800
SPI3 = 0x40003C00
USART2 = 0x40004400
USART3 = 0x40004800
UART4 = 0x40004C00
UART5 = 0x40005000
I2C1 = 0x40005400
I2C2 = 0x40005800
CAN1 = 0x40006400
CAN2 = 0x40006800
BKP = 0x40006C00
PWR = 0x40007000
DAC = 0x40007400
CEC = 0x40007800
AFIO = 0x40010000
EXTI = 0x40010400
GPIOA = 0x40010800
GPIOB = 0x40010C00
GPIOC = 0x40011000
GPIOD = 0x40011400
GPIOE = 0x40011800
GPIOF = 0x40011C00
GPIOG = 0x40012000
ADC1 = 0x40012400
ADC2 = 0x40012800
TIM1 = 0x40012C00
SPI1 = 0x40013000
TIM8 = 0x40013400
USART1 = 0x40013800
ADC3 = 0x40013C00
TIM15 = 0x40014000
TIM16 = 0x40014400
TIM17 = 0x40014800
TIM9 = 0x40014C00
TIM10 = 0x40015000
TIM11 = 0x40015400
SDIO = 0x40018000
DMA1 = 0x40020000
DMA2 = 0x40020400
DMA1_Channel1 = 0x40020008
DMA1_Channel2 = 0x4002001C
DMA1_Channel3 = 0x40020030
DMA1_Channel4 = 0x40020044
DMA1_Channel5 = 0x40020058
DMA1_Channel6 = 0x4002006C
DMA1_Channel7 = 0x40020080
DMA2_Channel1 = 0x40020408
DMA2_Channel2 = 0x4002041C
DMA2_Channel3 = 0x40020430
DMA2_Channel4 = 0x40020444
DMA2_Channel5 = 0x40020458
RCC = 0x40021000
CRC = 0x40023000
FLASH = 0x40022000
OB = 0x1FFFF800
ETH = 0x40028000
FSMC_Bank1 = 0xA0000000
FSMC_Bank1E = 0xA0000104
FSMC_Bank2 = 0xA0000060
FSMC_Bank3 = 0xA0000080
FSMC_Bank4 = 0xA00000A0
DBGMCU = 0xE0042000
CRC_DR_DR = 0xFFFFFFFF
CRC_IDR_IDR = 0xFF
CRC_CR_RESET = 0x1
PWR_CR_LPDS = 0x1
PWR_CR_PDDS = 0x2
PWR_CR_CWUF = 0x4
PWR_CR_CSBF = 0x8
PWR_CR_PVDE = 0x10
PWR_CR_PLS = 0xE0
PWR_CR_PLS_0 = 0x20
PWR_CR_PLS_1 = 0x40
PWR_CR_PLS_2 = 0x80
PWR_CR_PLS_2V2 = 0x0
PWR_CR_PLS_2V3 = 0x20
PWR_CR_PLS_2V4 = 0x40
PWR_CR_PLS_2V5 = 0x60
PWR_CR_PLS_2V6 = 0x80
PWR_CR_PLS_2V7 = 0xA0
PWR_CR_PLS_2V8 = 0xC0
PWR_CR_PLS_2V9 = 0xE0
PWR_CR_DBP = 0x100
PWR_CSR_WUF = 0x1
PWR_CSR_SBF = 0x2
PWR_CSR_PVDO = 0x4
PWR_CSR_EWUP = 0x100
BKP_DR1_D = 0xFFFF
BKP_DR2_D = 0xFFFF
BKP_DR3_D = 0xFFFF
BKP_DR4_D = 0xFFFF
BKP_DR5_D = 0xFFFF
BKP_DR6_D = 0xFFFF
BKP_DR7_D = 0xFFFF
BKP_DR8_D = 0xFFFF
BKP_DR9_D = 0xFFFF
BKP_DR10_D = 0xFFFF
BKP_DR11_D = 0xFFFF
BKP_DR12_D = 0xFFFF
BKP_DR13_D = 0xFFFF
BKP_DR14_D = 0xFFFF
BKP_DR15_D = 0xFFFF
BKP_DR16_D = 0xFFFF
BKP_DR17_D = 0xFFFF
BKP_DR18_D = 0xFFFF
BKP_DR19_D = 0xFFFF
BKP_DR20_D = 0xFFFF
BKP_DR21_D = 0xFFFF
BKP_DR22_D = 0xFFFF
BKP_DR23_D = 0xFFFF
BKP_DR24_D = 0xFFFF
BKP_DR25_D = 0xFFFF
BKP_DR26_D = 0xFFFF
BKP_DR27_D = 0xFFFF
BKP_DR28_D = 0xFFFF
BKP_DR29_D = 0xFFFF
BKP_DR30_D = 0xFFFF
BKP_DR31_D = 0xFFFF
BKP_DR32_D = 0xFFFF
BKP_DR33_D = 0xFFFF
BKP_DR34_D = 0xFFFF
BKP_DR35_D = 0xFFFF
BKP_DR36_D = 0xFFFF
BKP_DR37_D = 0xFFFF
BKP_DR38_D = 0xFFFF
BKP_DR39_D = 0xFFFF
BKP_DR40_D = 0xFFFF
BKP_DR41_D = 0xFFFF
BKP_DR42_D = 0xFFFF
BKP_RTCCR_CAL = 0x7F
BKP_RTCCR_CCO = 0x80
BKP_RTCCR_ASOE = 0x100
BKP_RTCCR_ASOS = 0x200
BKP_CR_TPE = 0x1
BKP_CR_TPAL = 0x2
BKP_CSR_CTE = 0x1
BKP_CSR_CTI = 0x2
BKP_CSR_TPIE = 0x4
BKP_CSR_TEF = 0x100
BKP_CSR_TIF = 0x200
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
# Skip RCC_CR_PLL2ON : no need parse
# Skip RCC_CR_PLL2RDY : no need parse
# Skip RCC_CR_PLL3ON : no need parse
# Skip RCC_CR_PLL3RDY : no need parse
RCC_CFGR_SW = 0x3
RCC_CFGR_SW_0 = 0x1
RCC_CFGR_SW_1 = 0x2
RCC_CFGR_SW_HSI = 0x0
RCC_CFGR_SW_HSE = 0x1
RCC_CFGR_SW_PLL = 0x2
RCC_CFGR_SWS = 0xC
RCC_CFGR_SWS_0 = 0x4
RCC_CFGR_SWS_1 = 0x8
RCC_CFGR_SWS_HSI = 0x0
RCC_CFGR_SWS_HSE = 0x4
RCC_CFGR_SWS_PLL = 0x8
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
RCC_CFGR_PPRE1 = 0x700
RCC_CFGR_PPRE1_0 = 0x100
RCC_CFGR_PPRE1_1 = 0x200
RCC_CFGR_PPRE1_2 = 0x400
RCC_CFGR_PPRE1_DIV1 = 0x0
RCC_CFGR_PPRE1_DIV2 = 0x400
RCC_CFGR_PPRE1_DIV4 = 0x500
RCC_CFGR_PPRE1_DIV8 = 0x600
RCC_CFGR_PPRE1_DIV16 = 0x700
RCC_CFGR_PPRE2 = 0x3800
RCC_CFGR_PPRE2_0 = 0x800
RCC_CFGR_PPRE2_1 = 0x1000
RCC_CFGR_PPRE2_2 = 0x2000
RCC_CFGR_PPRE2_DIV1 = 0x0
RCC_CFGR_PPRE2_DIV2 = 0x2000
RCC_CFGR_PPRE2_DIV4 = 0x2800
RCC_CFGR_PPRE2_DIV8 = 0x3000
RCC_CFGR_PPRE2_DIV16 = 0x3800
RCC_CFGR_ADCPRE = 0xC000
RCC_CFGR_ADCPRE_0 = 0x4000
RCC_CFGR_ADCPRE_1 = 0x8000
RCC_CFGR_ADCPRE_DIV2 = 0x0
RCC_CFGR_ADCPRE_DIV4 = 0x4000
RCC_CFGR_ADCPRE_DIV6 = 0x8000
RCC_CFGR_ADCPRE_DIV8 = 0xC000
RCC_CFGR_PLLSRC = 0x10000
RCC_CFGR_PLLXTPRE = 0x20000
RCC_CFGR_PLLMULL = 0x3C0000
RCC_CFGR_PLLMULL_0 = 0x40000
RCC_CFGR_PLLMULL_1 = 0x80000
RCC_CFGR_PLLMULL_2 = 0x100000
RCC_CFGR_PLLMULL_3 = 0x200000
RCC_CFGR_PLLSRC_HSI_Div2 = 0x0
# Skip RCC_CFGR_PLLSRC_PREDIV1 : no need parse
# Skip RCC_CFGR_PLLXTPRE_PREDIV1 : no need parse
# Skip RCC_CFGR_PLLXTPRE_PREDIV1_Div2 : no need parse
RCC_CFGR_PLLMULL4 = 0x80000
RCC_CFGR_PLLMULL5 = 0xC0000
RCC_CFGR_PLLMULL6 = 0x100000
RCC_CFGR_PLLMULL7 = 0x140000
RCC_CFGR_PLLMULL8 = 0x180000
RCC_CFGR_PLLMULL9 = 0x1C0000
# Skip RCC_CFGR_PLLMULL6_5 : no need parse
# Skip RCC_CFGR_OTGFSPRE : no need parse
RCC_CFGR_MCO = 0x7000000
RCC_CFGR_MCO_0 = 0x1000000
RCC_CFGR_MCO_1 = 0x2000000
RCC_CFGR_MCO_2 = 0x4000000
# Skip RCC_CFGR_MCO_3 : no need parse
RCC_CFGR_MCO_NOCLOCK = 0x0
RCC_CFGR_MCO_SYSCLK = 0x4000000
RCC_CFGR_MCO_HSI = 0x5000000
RCC_CFGR_MCO_HSE = 0x6000000
# Skip RCC_CFGR_MCO_PLLCLK_Div2 : no need parse
# Skip RCC_CFGR_MCO_PLL2CLK : no need parse
# Skip RCC_CFGR_MCO_PLL3CLK_Div2 : no need parse
# Skip RCC_CFGR_MCO_Ext_HSE : no need parse
# Skip RCC_CFGR_MCO_PLL3CLK : no need parse
RCC_CFGR_PLLSRC_HSI_Div2 = 0x0
# Skip RCC_CFGR_PLLSRC_PREDIV1 : no need parse
# Skip RCC_CFGR_PLLXTPRE_PREDIV1 : no need parse
# Skip RCC_CFGR_PLLXTPRE_PREDIV1_Div2 : no need parse
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
RCC_CFGR_MCO = 0x7000000
RCC_CFGR_MCO_0 = 0x1000000
RCC_CFGR_MCO_1 = 0x2000000
RCC_CFGR_MCO_2 = 0x4000000
RCC_CFGR_MCO_NOCLOCK = 0x0
RCC_CFGR_MCO_SYSCLK = 0x4000000
RCC_CFGR_MCO_HSI = 0x5000000
RCC_CFGR_MCO_HSE = 0x6000000
RCC_CFGR_MCO_PLL = 0x7000000
RCC_CFGR_PLLSRC_HSI_Div2 = 0x0
RCC_CFGR_PLLSRC_HSE = 0x10000
RCC_CFGR_PLLXTPRE_HSE = 0x0
RCC_CFGR_PLLXTPRE_HSE_Div2 = 0x20000
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
RCC_CFGR_USBPRE = 0x400000
RCC_CFGR_MCO = 0x7000000
RCC_CFGR_MCO_0 = 0x1000000
RCC_CFGR_MCO_1 = 0x2000000
RCC_CFGR_MCO_2 = 0x4000000
RCC_CFGR_MCO_NOCLOCK = 0x0
RCC_CFGR_MCO_SYSCLK = 0x4000000
RCC_CFGR_MCO_HSI = 0x5000000
RCC_CFGR_MCO_HSE = 0x6000000
RCC_CFGR_MCO_PLL = 0x7000000
RCC_CIR_LSIRDYF = 0x1
RCC_CIR_LSERDYF = 0x2
RCC_CIR_HSIRDYF = 0x4
RCC_CIR_HSERDYF = 0x8
RCC_CIR_PLLRDYF = 0x10
RCC_CIR_CSSF = 0x80
RCC_CIR_LSIRDYIE = 0x100
RCC_CIR_LSERDYIE = 0x200
RCC_CIR_HSIRDYIE = 0x400
RCC_CIR_HSERDYIE = 0x800
RCC_CIR_PLLRDYIE = 0x1000
RCC_CIR_LSIRDYC = 0x10000
RCC_CIR_LSERDYC = 0x20000
RCC_CIR_HSIRDYC = 0x40000
RCC_CIR_HSERDYC = 0x80000
RCC_CIR_PLLRDYC = 0x100000
RCC_CIR_CSSC = 0x800000
# Skip RCC_CIR_PLL2RDYF : no need parse
# Skip RCC_CIR_PLL3RDYF : no need parse
# Skip RCC_CIR_PLL2RDYIE : no need parse
# Skip RCC_CIR_PLL3RDYIE : no need parse
# Skip RCC_CIR_PLL2RDYC : no need parse
# Skip RCC_CIR_PLL3RDYC : no need parse
RCC_APB2RSTR_AFIORST = 0x1
RCC_APB2RSTR_IOPARST = 0x4
RCC_APB2RSTR_IOPBRST = 0x8
RCC_APB2RSTR_IOPCRST = 0x10
RCC_APB2RSTR_IOPDRST = 0x20
RCC_APB2RSTR_ADC1RST = 0x200
RCC_APB2RSTR_ADC2RST = 0x400
RCC_APB2RSTR_TIM1RST = 0x800
RCC_APB2RSTR_SPI1RST = 0x1000
RCC_APB2RSTR_USART1RST = 0x4000
# Skip RCC_APB2RSTR_TIM15RST : no need parse
# Skip RCC_APB2RSTR_TIM16RST : no need parse
# Skip RCC_APB2RSTR_TIM17RST : no need parse
RCC_APB2RSTR_IOPERST = 0x40
# Skip RCC_APB2RSTR_IOPFRST : no need parse
# Skip RCC_APB2RSTR_IOPGRST : no need parse
# Skip RCC_APB2RSTR_TIM8RST : no need parse
# Skip RCC_APB2RSTR_ADC3RST : no need parse
# Skip RCC_APB2RSTR_IOPFRST : no need parse
# Skip RCC_APB2RSTR_IOPGRST : no need parse
# Skip RCC_APB2RSTR_TIM9RST : no need parse
# Skip RCC_APB2RSTR_TIM10RST : no need parse
# Skip RCC_APB2RSTR_TIM11RST : no need parse
RCC_APB1RSTR_TIM2RST = 0x1
RCC_APB1RSTR_TIM3RST = 0x2
RCC_APB1RSTR_WWDGRST = 0x800
RCC_APB1RSTR_USART2RST = 0x20000
RCC_APB1RSTR_I2C1RST = 0x200000
RCC_APB1RSTR_CAN1RST = 0x2000000
RCC_APB1RSTR_BKPRST = 0x8000000
RCC_APB1RSTR_PWRRST = 0x10000000
RCC_APB1RSTR_TIM4RST = 0x4
RCC_APB1RSTR_SPI2RST = 0x4000
RCC_APB1RSTR_USART3RST = 0x40000
RCC_APB1RSTR_I2C2RST = 0x400000
RCC_APB1RSTR_USBRST = 0x800000
# Skip RCC_APB1RSTR_TIM5RST : no need parse
# Skip RCC_APB1RSTR_TIM6RST : no need parse
# Skip RCC_APB1RSTR_TIM7RST : no need parse
# Skip RCC_APB1RSTR_SPI3RST : no need parse
# Skip RCC_APB1RSTR_UART4RST : no need parse
# Skip RCC_APB1RSTR_UART5RST : no need parse
# Skip RCC_APB1RSTR_DACRST : no need parse
# Skip RCC_APB1RSTR_TIM6RST : no need parse
# Skip RCC_APB1RSTR_TIM7RST : no need parse
# Skip RCC_APB1RSTR_DACRST : no need parse
# Skip RCC_APB1RSTR_CECRST : no need parse
# Skip RCC_APB1RSTR_TIM5RST : no need parse
# Skip RCC_APB1RSTR_TIM12RST : no need parse
# Skip RCC_APB1RSTR_TIM13RST : no need parse
# Skip RCC_APB1RSTR_TIM14RST : no need parse
# Skip RCC_APB1RSTR_SPI3RST : no need parse
# Skip RCC_APB1RSTR_UART4RST : no need parse
# Skip RCC_APB1RSTR_UART5RST : no need parse
# Skip RCC_APB1RSTR_CAN2RST : no need parse
# Skip RCC_APB1RSTR_TIM12RST : no need parse
# Skip RCC_APB1RSTR_TIM13RST : no need parse
# Skip RCC_APB1RSTR_TIM14RST : no need parse
RCC_AHBENR_DMA1EN = 0x1
RCC_AHBENR_SRAMEN = 0x4
RCC_AHBENR_FLITFEN = 0x10
RCC_AHBENR_CRCEN = 0x40
# Skip RCC_AHBENR_DMA2EN : no need parse
# Skip RCC_AHBENR_FSMCEN : no need parse
# Skip RCC_AHBENR_SDIOEN : no need parse
# Skip RCC_AHBENR_FSMCEN : no need parse
# Skip RCC_AHBENR_OTGFSEN : no need parse
# Skip RCC_AHBENR_ETHMACEN : no need parse
# Skip RCC_AHBENR_ETHMACTXEN : no need parse
# Skip RCC_AHBENR_ETHMACRXEN : no need parse
RCC_APB2ENR_AFIOEN = 0x1
RCC_APB2ENR_IOPAEN = 0x4
RCC_APB2ENR_IOPBEN = 0x8
RCC_APB2ENR_IOPCEN = 0x10
RCC_APB2ENR_IOPDEN = 0x20
RCC_APB2ENR_ADC1EN = 0x200
RCC_APB2ENR_ADC2EN = 0x400
RCC_APB2ENR_TIM1EN = 0x800
RCC_APB2ENR_SPI1EN = 0x1000
RCC_APB2ENR_USART1EN = 0x4000
# Skip RCC_APB2ENR_TIM15EN : no need parse
# Skip RCC_APB2ENR_TIM16EN : no need parse
# Skip RCC_APB2ENR_TIM17EN : no need parse
RCC_APB2ENR_IOPEEN = 0x40
# Skip RCC_APB2ENR_IOPFEN : no need parse
# Skip RCC_APB2ENR_IOPGEN : no need parse
# Skip RCC_APB2ENR_TIM8EN : no need parse
# Skip RCC_APB2ENR_ADC3EN : no need parse
# Skip RCC_APB2ENR_IOPFEN : no need parse
# Skip RCC_APB2ENR_IOPGEN : no need parse
# Skip RCC_APB2ENR_TIM9EN : no need parse
# Skip RCC_APB2ENR_TIM10EN : no need parse
# Skip RCC_APB2ENR_TIM11EN : no need parse
RCC_APB1ENR_TIM2EN = 0x1
RCC_APB1ENR_TIM3EN = 0x2
RCC_APB1ENR_WWDGEN = 0x800
RCC_APB1ENR_USART2EN = 0x20000
RCC_APB1ENR_I2C1EN = 0x200000
RCC_APB1ENR_CAN1EN = 0x2000000
RCC_APB1ENR_BKPEN = 0x8000000
RCC_APB1ENR_PWREN = 0x10000000
RCC_APB1ENR_TIM4EN = 0x4
RCC_APB1ENR_SPI2EN = 0x4000
RCC_APB1ENR_USART3EN = 0x40000
RCC_APB1ENR_I2C2EN = 0x400000
RCC_APB1ENR_USBEN = 0x800000
# Skip RCC_APB1ENR_TIM5EN : no need parse
# Skip RCC_APB1ENR_TIM6EN : no need parse
# Skip RCC_APB1ENR_TIM7EN : no need parse
# Skip RCC_APB1ENR_SPI3EN : no need parse
# Skip RCC_APB1ENR_UART4EN : no need parse
# Skip RCC_APB1ENR_UART5EN : no need parse
# Skip RCC_APB1ENR_DACEN : no need parse
# Skip RCC_APB1ENR_TIM6EN : no need parse
# Skip RCC_APB1ENR_TIM7EN : no need parse
# Skip RCC_APB1ENR_DACEN : no need parse
# Skip RCC_APB1ENR_CECEN : no need parse
# Skip RCC_APB1ENR_TIM5EN : no need parse
# Skip RCC_APB1ENR_TIM12EN : no need parse
# Skip RCC_APB1ENR_TIM13EN : no need parse
# Skip RCC_APB1ENR_TIM14EN : no need parse
# Skip RCC_APB1ENR_SPI3EN : no need parse
# Skip RCC_APB1ENR_UART4EN : no need parse
# Skip RCC_APB1ENR_UART5EN : no need parse
# Skip RCC_APB1ENR_CAN2EN : no need parse
# Skip RCC_APB1ENR_TIM12EN : no need parse
# Skip RCC_APB1ENR_TIM13EN : no need parse
# Skip RCC_APB1ENR_TIM14EN : no need parse
RCC_BDCR_LSEON = 0x1
RCC_BDCR_LSERDY = 0x2
RCC_BDCR_LSEBYP = 0x4
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
RCC_CSR_RMVF = 0x1000000
RCC_CSR_PINRSTF = 0x4000000
RCC_CSR_PORRSTF = 0x8000000
RCC_CSR_SFTRSTF = 0x10000000
RCC_CSR_IWDGRSTF = 0x20000000
RCC_CSR_WWDGRSTF = 0x40000000
RCC_CSR_LPWRRSTF = 0x80000000
# Skip RCC_AHBRSTR_OTGFSRST : no need parse
# Skip RCC_AHBRSTR_ETHMACRST : no need parse
# Skip RCC_CFGR2_PREDIV1 : no need parse
# Skip RCC_CFGR2_PREDIV1_0 : no need parse
# Skip RCC_CFGR2_PREDIV1_1 : no need parse
# Skip RCC_CFGR2_PREDIV1_2 : no need parse
# Skip RCC_CFGR2_PREDIV1_3 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV1 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV2 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV3 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV4 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV5 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV6 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV7 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV8 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV9 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV10 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV11 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV12 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV13 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV14 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV15 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV16 : no need parse
# Skip RCC_CFGR2_PREDIV2 : no need parse
# Skip RCC_CFGR2_PREDIV2_0 : no need parse
# Skip RCC_CFGR2_PREDIV2_1 : no need parse
# Skip RCC_CFGR2_PREDIV2_2 : no need parse
# Skip RCC_CFGR2_PREDIV2_3 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV1 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV2 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV3 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV4 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV5 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV6 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV7 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV8 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV9 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV10 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV11 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV12 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV13 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV14 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV15 : no need parse
# Skip RCC_CFGR2_PREDIV2_DIV16 : no need parse
# Skip RCC_CFGR2_PLL2MUL : no need parse
# Skip RCC_CFGR2_PLL2MUL_0 : no need parse
# Skip RCC_CFGR2_PLL2MUL_1 : no need parse
# Skip RCC_CFGR2_PLL2MUL_2 : no need parse
# Skip RCC_CFGR2_PLL2MUL_3 : no need parse
# Skip RCC_CFGR2_PLL2MUL8 : no need parse
# Skip RCC_CFGR2_PLL2MUL9 : no need parse
# Skip RCC_CFGR2_PLL2MUL10 : no need parse
# Skip RCC_CFGR2_PLL2MUL11 : no need parse
# Skip RCC_CFGR2_PLL2MUL12 : no need parse
# Skip RCC_CFGR2_PLL2MUL13 : no need parse
# Skip RCC_CFGR2_PLL2MUL14 : no need parse
# Skip RCC_CFGR2_PLL2MUL16 : no need parse
# Skip RCC_CFGR2_PLL2MUL20 : no need parse
# Skip RCC_CFGR2_PLL3MUL : no need parse
# Skip RCC_CFGR2_PLL3MUL_0 : no need parse
# Skip RCC_CFGR2_PLL3MUL_1 : no need parse
# Skip RCC_CFGR2_PLL3MUL_2 : no need parse
# Skip RCC_CFGR2_PLL3MUL_3 : no need parse
# Skip RCC_CFGR2_PLL3MUL8 : no need parse
# Skip RCC_CFGR2_PLL3MUL9 : no need parse
# Skip RCC_CFGR2_PLL3MUL10 : no need parse
# Skip RCC_CFGR2_PLL3MUL11 : no need parse
# Skip RCC_CFGR2_PLL3MUL12 : no need parse
# Skip RCC_CFGR2_PLL3MUL13 : no need parse
# Skip RCC_CFGR2_PLL3MUL14 : no need parse
# Skip RCC_CFGR2_PLL3MUL16 : no need parse
# Skip RCC_CFGR2_PLL3MUL20 : no need parse
# Skip RCC_CFGR2_PREDIV1SRC : no need parse
# Skip RCC_CFGR2_PREDIV1SRC_PLL2 : no need parse
# Skip RCC_CFGR2_PREDIV1SRC_HSE : no need parse
# Skip RCC_CFGR2_I2S2SRC : no need parse
# Skip RCC_CFGR2_I2S3SRC : no need parse
# Skip RCC_CFGR2_PREDIV1 : no need parse
# Skip RCC_CFGR2_PREDIV1_0 : no need parse
# Skip RCC_CFGR2_PREDIV1_1 : no need parse
# Skip RCC_CFGR2_PREDIV1_2 : no need parse
# Skip RCC_CFGR2_PREDIV1_3 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV1 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV2 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV3 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV4 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV5 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV6 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV7 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV8 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV9 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV10 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV11 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV12 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV13 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV14 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV15 : no need parse
# Skip RCC_CFGR2_PREDIV1_DIV16 : no need parse
GPIO_CRL_MODE = 0x33333333
GPIO_CRL_MODE0 = 0x3
GPIO_CRL_MODE0_0 = 0x1
GPIO_CRL_MODE0_1 = 0x2
GPIO_CRL_MODE1 = 0x30
GPIO_CRL_MODE1_0 = 0x10
GPIO_CRL_MODE1_1 = 0x20
GPIO_CRL_MODE2 = 0x300
GPIO_CRL_MODE2_0 = 0x100
GPIO_CRL_MODE2_1 = 0x200
GPIO_CRL_MODE3 = 0x3000
GPIO_CRL_MODE3_0 = 0x1000
GPIO_CRL_MODE3_1 = 0x2000
GPIO_CRL_MODE4 = 0x30000
GPIO_CRL_MODE4_0 = 0x10000
GPIO_CRL_MODE4_1 = 0x20000
GPIO_CRL_MODE5 = 0x300000
GPIO_CRL_MODE5_0 = 0x100000
GPIO_CRL_MODE5_1 = 0x200000
GPIO_CRL_MODE6 = 0x3000000
GPIO_CRL_MODE6_0 = 0x1000000
GPIO_CRL_MODE6_1 = 0x2000000
GPIO_CRL_MODE7 = 0x30000000
GPIO_CRL_MODE7_0 = 0x10000000
GPIO_CRL_MODE7_1 = 0x20000000
GPIO_CRL_CNF = 0xCCCCCCCC
GPIO_CRL_CNF0 = 0xC
GPIO_CRL_CNF0_0 = 0x4
GPIO_CRL_CNF0_1 = 0x8
GPIO_CRL_CNF1 = 0xC0
GPIO_CRL_CNF1_0 = 0x40
GPIO_CRL_CNF1_1 = 0x80
GPIO_CRL_CNF2 = 0xC00
GPIO_CRL_CNF2_0 = 0x400
GPIO_CRL_CNF2_1 = 0x800
GPIO_CRL_CNF3 = 0xC000
GPIO_CRL_CNF3_0 = 0x4000
GPIO_CRL_CNF3_1 = 0x8000
GPIO_CRL_CNF4 = 0xC0000
GPIO_CRL_CNF4_0 = 0x40000
GPIO_CRL_CNF4_1 = 0x80000
GPIO_CRL_CNF5 = 0xC00000
GPIO_CRL_CNF5_0 = 0x400000
GPIO_CRL_CNF5_1 = 0x800000
GPIO_CRL_CNF6 = 0xC000000
GPIO_CRL_CNF6_0 = 0x4000000
GPIO_CRL_CNF6_1 = 0x8000000
GPIO_CRL_CNF7 = 0xC0000000
GPIO_CRL_CNF7_0 = 0x40000000
GPIO_CRL_CNF7_1 = 0x80000000
GPIO_CRH_MODE = 0x33333333
GPIO_CRH_MODE8 = 0x3
GPIO_CRH_MODE8_0 = 0x1
GPIO_CRH_MODE8_1 = 0x2
GPIO_CRH_MODE9 = 0x30
GPIO_CRH_MODE9_0 = 0x10
GPIO_CRH_MODE9_1 = 0x20
GPIO_CRH_MODE10 = 0x300
GPIO_CRH_MODE10_0 = 0x100
GPIO_CRH_MODE10_1 = 0x200
GPIO_CRH_MODE11 = 0x3000
GPIO_CRH_MODE11_0 = 0x1000
GPIO_CRH_MODE11_1 = 0x2000
GPIO_CRH_MODE12 = 0x30000
GPIO_CRH_MODE12_0 = 0x10000
GPIO_CRH_MODE12_1 = 0x20000
GPIO_CRH_MODE13 = 0x300000
GPIO_CRH_MODE13_0 = 0x100000
GPIO_CRH_MODE13_1 = 0x200000
GPIO_CRH_MODE14 = 0x3000000
GPIO_CRH_MODE14_0 = 0x1000000
GPIO_CRH_MODE14_1 = 0x2000000
GPIO_CRH_MODE15 = 0x30000000
GPIO_CRH_MODE15_0 = 0x10000000
GPIO_CRH_MODE15_1 = 0x20000000
GPIO_CRH_CNF = 0xCCCCCCCC
GPIO_CRH_CNF8 = 0xC
GPIO_CRH_CNF8_0 = 0x4
GPIO_CRH_CNF8_1 = 0x8
GPIO_CRH_CNF9 = 0xC0
GPIO_CRH_CNF9_0 = 0x40
GPIO_CRH_CNF9_1 = 0x80
GPIO_CRH_CNF10 = 0xC00
GPIO_CRH_CNF10_0 = 0x400
GPIO_CRH_CNF10_1 = 0x800
GPIO_CRH_CNF11 = 0xC000
GPIO_CRH_CNF11_0 = 0x4000
GPIO_CRH_CNF11_1 = 0x8000
GPIO_CRH_CNF12 = 0xC0000
GPIO_CRH_CNF12_0 = 0x40000
GPIO_CRH_CNF12_1 = 0x80000
GPIO_CRH_CNF13 = 0xC00000
GPIO_CRH_CNF13_0 = 0x400000
GPIO_CRH_CNF13_1 = 0x800000
GPIO_CRH_CNF14 = 0xC000000
GPIO_CRH_CNF14_0 = 0x4000000
GPIO_CRH_CNF14_1 = 0x8000000
GPIO_CRH_CNF15 = 0xC0000000
GPIO_CRH_CNF15_0 = 0x40000000
GPIO_CRH_CNF15_1 = 0x80000000
GPIO_IDR_IDR0 = 0x1
GPIO_IDR_IDR1 = 0x2
GPIO_IDR_IDR2 = 0x4
GPIO_IDR_IDR3 = 0x8
GPIO_IDR_IDR4 = 0x10
GPIO_IDR_IDR5 = 0x20
GPIO_IDR_IDR6 = 0x40
GPIO_IDR_IDR7 = 0x80
GPIO_IDR_IDR8 = 0x100
GPIO_IDR_IDR9 = 0x200
GPIO_IDR_IDR10 = 0x400
GPIO_IDR_IDR11 = 0x800
GPIO_IDR_IDR12 = 0x1000
GPIO_IDR_IDR13 = 0x2000
GPIO_IDR_IDR14 = 0x4000
GPIO_IDR_IDR15 = 0x8000
GPIO_ODR_ODR0 = 0x1
GPIO_ODR_ODR1 = 0x2
GPIO_ODR_ODR2 = 0x4
GPIO_ODR_ODR3 = 0x8
GPIO_ODR_ODR4 = 0x10
GPIO_ODR_ODR5 = 0x20
GPIO_ODR_ODR6 = 0x40
GPIO_ODR_ODR7 = 0x80
GPIO_ODR_ODR8 = 0x100
GPIO_ODR_ODR9 = 0x200
GPIO_ODR_ODR10 = 0x400
GPIO_ODR_ODR11 = 0x800
GPIO_ODR_ODR12 = 0x1000
GPIO_ODR_ODR13 = 0x2000
GPIO_ODR_ODR14 = 0x4000
GPIO_ODR_ODR15 = 0x8000
GPIO_BSRR_BS0 = 0x1
GPIO_BSRR_BS1 = 0x2
GPIO_BSRR_BS2 = 0x4
GPIO_BSRR_BS3 = 0x8
GPIO_BSRR_BS4 = 0x10
GPIO_BSRR_BS5 = 0x20
GPIO_BSRR_BS6 = 0x40
GPIO_BSRR_BS7 = 0x80
GPIO_BSRR_BS8 = 0x100
GPIO_BSRR_BS9 = 0x200
GPIO_BSRR_BS10 = 0x400
GPIO_BSRR_BS11 = 0x800
GPIO_BSRR_BS12 = 0x1000
GPIO_BSRR_BS13 = 0x2000
GPIO_BSRR_BS14 = 0x4000
GPIO_BSRR_BS15 = 0x8000
GPIO_BSRR_BR0 = 0x10000
GPIO_BSRR_BR1 = 0x20000
GPIO_BSRR_BR2 = 0x40000
GPIO_BSRR_BR3 = 0x80000
GPIO_BSRR_BR4 = 0x100000
GPIO_BSRR_BR5 = 0x200000
GPIO_BSRR_BR6 = 0x400000
GPIO_BSRR_BR7 = 0x800000
GPIO_BSRR_BR8 = 0x1000000
GPIO_BSRR_BR9 = 0x2000000
GPIO_BSRR_BR10 = 0x4000000
GPIO_BSRR_BR11 = 0x8000000
GPIO_BSRR_BR12 = 0x10000000
GPIO_BSRR_BR13 = 0x20000000
GPIO_BSRR_BR14 = 0x40000000
GPIO_BSRR_BR15 = 0x80000000
GPIO_BRR_BR0 = 0x1
GPIO_BRR_BR1 = 0x2
GPIO_BRR_BR2 = 0x4
GPIO_BRR_BR3 = 0x8
GPIO_BRR_BR4 = 0x10
GPIO_BRR_BR5 = 0x20
GPIO_BRR_BR6 = 0x40
GPIO_BRR_BR7 = 0x80
GPIO_BRR_BR8 = 0x100
GPIO_BRR_BR9 = 0x200
GPIO_BRR_BR10 = 0x400
GPIO_BRR_BR11 = 0x800
GPIO_BRR_BR12 = 0x1000
GPIO_BRR_BR13 = 0x2000
GPIO_BRR_BR14 = 0x4000
GPIO_BRR_BR15 = 0x8000
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
AFIO_EVCR_PIN = 0xF
AFIO_EVCR_PIN_0 = 0x1
AFIO_EVCR_PIN_1 = 0x2
AFIO_EVCR_PIN_2 = 0x4
AFIO_EVCR_PIN_3 = 0x8
AFIO_EVCR_PIN_PX0 = 0x0
AFIO_EVCR_PIN_PX1 = 0x1
AFIO_EVCR_PIN_PX2 = 0x2
AFIO_EVCR_PIN_PX3 = 0x3
AFIO_EVCR_PIN_PX4 = 0x4
AFIO_EVCR_PIN_PX5 = 0x5
AFIO_EVCR_PIN_PX6 = 0x6
AFIO_EVCR_PIN_PX7 = 0x7
AFIO_EVCR_PIN_PX8 = 0x8
AFIO_EVCR_PIN_PX9 = 0x9
AFIO_EVCR_PIN_PX10 = 0xA
AFIO_EVCR_PIN_PX11 = 0xB
AFIO_EVCR_PIN_PX12 = 0xC
AFIO_EVCR_PIN_PX13 = 0xD
AFIO_EVCR_PIN_PX14 = 0xE
AFIO_EVCR_PIN_PX15 = 0xF
AFIO_EVCR_PORT = 0x70
AFIO_EVCR_PORT_0 = 0x10
AFIO_EVCR_PORT_1 = 0x20
AFIO_EVCR_PORT_2 = 0x40
AFIO_EVCR_PORT_PA = 0x0
AFIO_EVCR_PORT_PB = 0x10
AFIO_EVCR_PORT_PC = 0x20
AFIO_EVCR_PORT_PD = 0x30
AFIO_EVCR_PORT_PE = 0x40
AFIO_EVCR_EVOE = 0x80
AFIO_MAPR_SPI1_REMAP = 0x1
AFIO_MAPR_I2C1_REMAP = 0x2
AFIO_MAPR_USART1_REMAP = 0x4
AFIO_MAPR_USART2_REMAP = 0x8
AFIO_MAPR_USART3_REMAP = 0x30
AFIO_MAPR_USART3_REMAP_0 = 0x10
AFIO_MAPR_USART3_REMAP_1 = 0x20
AFIO_MAPR_USART3_REMAP_NOREMAP = 0x0
AFIO_MAPR_USART3_REMAP_PARTIALREMAP = 0x10
AFIO_MAPR_USART3_REMAP_FULLREMAP = 0x30
AFIO_MAPR_TIM1_REMAP = 0xC0
AFIO_MAPR_TIM1_REMAP_0 = 0x40
AFIO_MAPR_TIM1_REMAP_1 = 0x80
AFIO_MAPR_TIM1_REMAP_NOREMAP = 0x0
AFIO_MAPR_TIM1_REMAP_PARTIALREMAP = 0x40
AFIO_MAPR_TIM1_REMAP_FULLREMAP = 0xC0
AFIO_MAPR_TIM2_REMAP = 0x300
AFIO_MAPR_TIM2_REMAP_0 = 0x100
AFIO_MAPR_TIM2_REMAP_1 = 0x200
AFIO_MAPR_TIM2_REMAP_NOREMAP = 0x0
AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1 = 0x100
AFIO_MAPR_TIM2_REMAP_PARTIALREMAP2 = 0x200
AFIO_MAPR_TIM2_REMAP_FULLREMAP = 0x300
AFIO_MAPR_TIM3_REMAP = 0xC00
AFIO_MAPR_TIM3_REMAP_0 = 0x400
AFIO_MAPR_TIM3_REMAP_1 = 0x800
AFIO_MAPR_TIM3_REMAP_NOREMAP = 0x0
AFIO_MAPR_TIM3_REMAP_PARTIALREMAP = 0x800
AFIO_MAPR_TIM3_REMAP_FULLREMAP = 0xC00
AFIO_MAPR_TIM4_REMAP = 0x1000
AFIO_MAPR_CAN_REMAP = 0x6000
AFIO_MAPR_CAN_REMAP_0 = 0x2000
AFIO_MAPR_CAN_REMAP_1 = 0x4000
AFIO_MAPR_CAN_REMAP_REMAP1 = 0x0
AFIO_MAPR_CAN_REMAP_REMAP2 = 0x4000
AFIO_MAPR_CAN_REMAP_REMAP3 = 0x6000
AFIO_MAPR_PD01_REMAP = 0x8000
AFIO_MAPR_TIM5CH4_IREMAP = 0x10000
AFIO_MAPR_ADC1_ETRGINJ_REMAP = 0x20000
AFIO_MAPR_ADC1_ETRGREG_REMAP = 0x40000
AFIO_MAPR_ADC2_ETRGINJ_REMAP = 0x80000
AFIO_MAPR_ADC2_ETRGREG_REMAP = 0x100000
AFIO_MAPR_SWJ_CFG = 0x7000000
AFIO_MAPR_SWJ_CFG_0 = 0x1000000
AFIO_MAPR_SWJ_CFG_1 = 0x2000000
AFIO_MAPR_SWJ_CFG_2 = 0x4000000
AFIO_MAPR_SWJ_CFG_RESET = 0x0
AFIO_MAPR_SWJ_CFG_NOJNTRST = 0x1000000
AFIO_MAPR_SWJ_CFG_JTAGDISABLE = 0x2000000
AFIO_MAPR_SWJ_CFG_DISABLE = 0x4000000
# Skip AFIO_MAPR_ETH_REMAP : no need parse
# Skip AFIO_MAPR_CAN2_REMAP : no need parse
# Skip AFIO_MAPR_MII_RMII_SEL : no need parse
# Skip AFIO_MAPR_SPI3_REMAP : no need parse
# Skip AFIO_MAPR_TIM2ITR1_IREMAP : no need parse
# Skip AFIO_MAPR_PTP_PPS_REMAP : no need parse
AFIO_EXTICR1_EXTI0 = 0xF
AFIO_EXTICR1_EXTI1 = 0xF0
AFIO_EXTICR1_EXTI2 = 0xF00
AFIO_EXTICR1_EXTI3 = 0xF000
AFIO_EXTICR1_EXTI0_PA = 0x0
AFIO_EXTICR1_EXTI0_PB = 0x1
AFIO_EXTICR1_EXTI0_PC = 0x2
AFIO_EXTICR1_EXTI0_PD = 0x3
AFIO_EXTICR1_EXTI0_PE = 0x4
AFIO_EXTICR1_EXTI0_PF = 0x5
AFIO_EXTICR1_EXTI0_PG = 0x6
AFIO_EXTICR1_EXTI1_PA = 0x0
AFIO_EXTICR1_EXTI1_PB = 0x10
AFIO_EXTICR1_EXTI1_PC = 0x20
AFIO_EXTICR1_EXTI1_PD = 0x30
AFIO_EXTICR1_EXTI1_PE = 0x40
AFIO_EXTICR1_EXTI1_PF = 0x50
AFIO_EXTICR1_EXTI1_PG = 0x60
AFIO_EXTICR1_EXTI2_PA = 0x0
AFIO_EXTICR1_EXTI2_PB = 0x100
AFIO_EXTICR1_EXTI2_PC = 0x200
AFIO_EXTICR1_EXTI2_PD = 0x300
AFIO_EXTICR1_EXTI2_PE = 0x400
AFIO_EXTICR1_EXTI2_PF = 0x500
AFIO_EXTICR1_EXTI2_PG = 0x600
AFIO_EXTICR1_EXTI3_PA = 0x0
AFIO_EXTICR1_EXTI3_PB = 0x1000
AFIO_EXTICR1_EXTI3_PC = 0x2000
AFIO_EXTICR1_EXTI3_PD = 0x3000
AFIO_EXTICR1_EXTI3_PE = 0x4000
AFIO_EXTICR1_EXTI3_PF = 0x5000
AFIO_EXTICR1_EXTI3_PG = 0x6000
AFIO_EXTICR2_EXTI4 = 0xF
AFIO_EXTICR2_EXTI5 = 0xF0
AFIO_EXTICR2_EXTI6 = 0xF00
AFIO_EXTICR2_EXTI7 = 0xF000
AFIO_EXTICR2_EXTI4_PA = 0x0
AFIO_EXTICR2_EXTI4_PB = 0x1
AFIO_EXTICR2_EXTI4_PC = 0x2
AFIO_EXTICR2_EXTI4_PD = 0x3
AFIO_EXTICR2_EXTI4_PE = 0x4
AFIO_EXTICR2_EXTI4_PF = 0x5
AFIO_EXTICR2_EXTI4_PG = 0x6
AFIO_EXTICR2_EXTI5_PA = 0x0
AFIO_EXTICR2_EXTI5_PB = 0x10
AFIO_EXTICR2_EXTI5_PC = 0x20
AFIO_EXTICR2_EXTI5_PD = 0x30
AFIO_EXTICR2_EXTI5_PE = 0x40
AFIO_EXTICR2_EXTI5_PF = 0x50
AFIO_EXTICR2_EXTI5_PG = 0x60
AFIO_EXTICR2_EXTI6_PA = 0x0
AFIO_EXTICR2_EXTI6_PB = 0x100
AFIO_EXTICR2_EXTI6_PC = 0x200
AFIO_EXTICR2_EXTI6_PD = 0x300
AFIO_EXTICR2_EXTI6_PE = 0x400
AFIO_EXTICR2_EXTI6_PF = 0x500
AFIO_EXTICR2_EXTI6_PG = 0x600
AFIO_EXTICR2_EXTI7_PA = 0x0
AFIO_EXTICR2_EXTI7_PB = 0x1000
AFIO_EXTICR2_EXTI7_PC = 0x2000
AFIO_EXTICR2_EXTI7_PD = 0x3000
AFIO_EXTICR2_EXTI7_PE = 0x4000
AFIO_EXTICR2_EXTI7_PF = 0x5000
AFIO_EXTICR2_EXTI7_PG = 0x6000
AFIO_EXTICR3_EXTI8 = 0xF
AFIO_EXTICR3_EXTI9 = 0xF0
AFIO_EXTICR3_EXTI10 = 0xF00
AFIO_EXTICR3_EXTI11 = 0xF000
AFIO_EXTICR3_EXTI8_PA = 0x0
AFIO_EXTICR3_EXTI8_PB = 0x1
AFIO_EXTICR3_EXTI8_PC = 0x2
AFIO_EXTICR3_EXTI8_PD = 0x3
AFIO_EXTICR3_EXTI8_PE = 0x4
AFIO_EXTICR3_EXTI8_PF = 0x5
AFIO_EXTICR3_EXTI8_PG = 0x6
AFIO_EXTICR3_EXTI9_PA = 0x0
AFIO_EXTICR3_EXTI9_PB = 0x10
AFIO_EXTICR3_EXTI9_PC = 0x20
AFIO_EXTICR3_EXTI9_PD = 0x30
AFIO_EXTICR3_EXTI9_PE = 0x40
AFIO_EXTICR3_EXTI9_PF = 0x50
AFIO_EXTICR3_EXTI9_PG = 0x60
AFIO_EXTICR3_EXTI10_PA = 0x0
AFIO_EXTICR3_EXTI10_PB = 0x100
AFIO_EXTICR3_EXTI10_PC = 0x200
AFIO_EXTICR3_EXTI10_PD = 0x300
AFIO_EXTICR3_EXTI10_PE = 0x400
AFIO_EXTICR3_EXTI10_PF = 0x500
AFIO_EXTICR3_EXTI10_PG = 0x600
AFIO_EXTICR3_EXTI11_PA = 0x0
AFIO_EXTICR3_EXTI11_PB = 0x1000
AFIO_EXTICR3_EXTI11_PC = 0x2000
AFIO_EXTICR3_EXTI11_PD = 0x3000
AFIO_EXTICR3_EXTI11_PE = 0x4000
AFIO_EXTICR3_EXTI11_PF = 0x5000
AFIO_EXTICR3_EXTI11_PG = 0x6000
AFIO_EXTICR4_EXTI12 = 0xF
AFIO_EXTICR4_EXTI13 = 0xF0
AFIO_EXTICR4_EXTI14 = 0xF00
AFIO_EXTICR4_EXTI15 = 0xF000
AFIO_EXTICR4_EXTI12_PA = 0x0
AFIO_EXTICR4_EXTI12_PB = 0x1
AFIO_EXTICR4_EXTI12_PC = 0x2
AFIO_EXTICR4_EXTI12_PD = 0x3
AFIO_EXTICR4_EXTI12_PE = 0x4
AFIO_EXTICR4_EXTI12_PF = 0x5
AFIO_EXTICR4_EXTI12_PG = 0x6
AFIO_EXTICR4_EXTI13_PA = 0x0
AFIO_EXTICR4_EXTI13_PB = 0x10
AFIO_EXTICR4_EXTI13_PC = 0x20
AFIO_EXTICR4_EXTI13_PD = 0x30
AFIO_EXTICR4_EXTI13_PE = 0x40
AFIO_EXTICR4_EXTI13_PF = 0x50
AFIO_EXTICR4_EXTI13_PG = 0x60
AFIO_EXTICR4_EXTI14_PA = 0x0
AFIO_EXTICR4_EXTI14_PB = 0x100
AFIO_EXTICR4_EXTI14_PC = 0x200
AFIO_EXTICR4_EXTI14_PD = 0x300
AFIO_EXTICR4_EXTI14_PE = 0x400
AFIO_EXTICR4_EXTI14_PF = 0x500
AFIO_EXTICR4_EXTI14_PG = 0x600
AFIO_EXTICR4_EXTI15_PA = 0x0
AFIO_EXTICR4_EXTI15_PB = 0x1000
AFIO_EXTICR4_EXTI15_PC = 0x2000
AFIO_EXTICR4_EXTI15_PD = 0x3000
AFIO_EXTICR4_EXTI15_PE = 0x4000
AFIO_EXTICR4_EXTI15_PF = 0x5000
AFIO_EXTICR4_EXTI15_PG = 0x6000
# Skip AFIO_MAPR2_TIM15_REMAP : no need parse
# Skip AFIO_MAPR2_TIM16_REMAP : no need parse
# Skip AFIO_MAPR2_TIM17_REMAP : no need parse
# Skip AFIO_MAPR2_CEC_REMAP : no need parse
# Skip AFIO_MAPR2_TIM1_DMA_REMAP : no need parse
# Skip AFIO_MAPR2_TIM13_REMAP : no need parse
# Skip AFIO_MAPR2_TIM14_REMAP : no need parse
# Skip AFIO_MAPR2_FSMC_NADV_REMAP : no need parse
# Skip AFIO_MAPR2_TIM67_DAC_DMA_REMAP : no need parse
# Skip AFIO_MAPR2_TIM12_REMAP : no need parse
# Skip AFIO_MAPR2_MISC_REMAP : no need parse
# Skip AFIO_MAPR2_TIM9_REMAP : no need parse
# Skip AFIO_MAPR2_TIM10_REMAP : no need parse
# Skip AFIO_MAPR2_TIM11_REMAP : no need parse
# Skip AFIO_MAPR2_TIM13_REMAP : no need parse
# Skip AFIO_MAPR2_TIM14_REMAP : no need parse
# Skip AFIO_MAPR2_FSMC_NADV_REMAP : no need parse
SysTick_CTRL_ENABLE = 0x1
SysTick_CTRL_TICKINT = 0x2
SysTick_CTRL_CLKSOURCE = 0x4
SysTick_CTRL_COUNTFLAG = 0x10000
SysTick_LOAD_RELOAD = 0xFFFFFF
SysTick_VAL_CURRENT = 0xFFFFFF
SysTick_CALIB_TENMS = 0xFFFFFF
SysTick_CALIB_SKEW = 0x40000000
SysTick_CALIB_NOREF = 0x80000000
NVIC_ISER_SETENA = 0xFFFFFFFF
NVIC_ISER_SETENA_0 = 0x1
NVIC_ISER_SETENA_1 = 0x2
NVIC_ISER_SETENA_2 = 0x4
NVIC_ISER_SETENA_3 = 0x8
NVIC_ISER_SETENA_4 = 0x10
NVIC_ISER_SETENA_5 = 0x20
NVIC_ISER_SETENA_6 = 0x40
NVIC_ISER_SETENA_7 = 0x80
NVIC_ISER_SETENA_8 = 0x100
NVIC_ISER_SETENA_9 = 0x200
NVIC_ISER_SETENA_10 = 0x400
NVIC_ISER_SETENA_11 = 0x800
NVIC_ISER_SETENA_12 = 0x1000
NVIC_ISER_SETENA_13 = 0x2000
NVIC_ISER_SETENA_14 = 0x4000
NVIC_ISER_SETENA_15 = 0x8000
NVIC_ISER_SETENA_16 = 0x10000
NVIC_ISER_SETENA_17 = 0x20000
NVIC_ISER_SETENA_18 = 0x40000
NVIC_ISER_SETENA_19 = 0x80000
NVIC_ISER_SETENA_20 = 0x100000
NVIC_ISER_SETENA_21 = 0x200000
NVIC_ISER_SETENA_22 = 0x400000
NVIC_ISER_SETENA_23 = 0x800000
NVIC_ISER_SETENA_24 = 0x1000000
NVIC_ISER_SETENA_25 = 0x2000000
NVIC_ISER_SETENA_26 = 0x4000000
NVIC_ISER_SETENA_27 = 0x8000000
NVIC_ISER_SETENA_28 = 0x10000000
NVIC_ISER_SETENA_29 = 0x20000000
NVIC_ISER_SETENA_30 = 0x40000000
NVIC_ISER_SETENA_31 = 0x80000000
NVIC_ICER_CLRENA = 0xFFFFFFFF
NVIC_ICER_CLRENA_0 = 0x1
NVIC_ICER_CLRENA_1 = 0x2
NVIC_ICER_CLRENA_2 = 0x4
NVIC_ICER_CLRENA_3 = 0x8
NVIC_ICER_CLRENA_4 = 0x10
NVIC_ICER_CLRENA_5 = 0x20
NVIC_ICER_CLRENA_6 = 0x40
NVIC_ICER_CLRENA_7 = 0x80
NVIC_ICER_CLRENA_8 = 0x100
NVIC_ICER_CLRENA_9 = 0x200
NVIC_ICER_CLRENA_10 = 0x400
NVIC_ICER_CLRENA_11 = 0x800
NVIC_ICER_CLRENA_12 = 0x1000
NVIC_ICER_CLRENA_13 = 0x2000
NVIC_ICER_CLRENA_14 = 0x4000
NVIC_ICER_CLRENA_15 = 0x8000
NVIC_ICER_CLRENA_16 = 0x10000
NVIC_ICER_CLRENA_17 = 0x20000
NVIC_ICER_CLRENA_18 = 0x40000
NVIC_ICER_CLRENA_19 = 0x80000
NVIC_ICER_CLRENA_20 = 0x100000
NVIC_ICER_CLRENA_21 = 0x200000
NVIC_ICER_CLRENA_22 = 0x400000
NVIC_ICER_CLRENA_23 = 0x800000
NVIC_ICER_CLRENA_24 = 0x1000000
NVIC_ICER_CLRENA_25 = 0x2000000
NVIC_ICER_CLRENA_26 = 0x4000000
NVIC_ICER_CLRENA_27 = 0x8000000
NVIC_ICER_CLRENA_28 = 0x10000000
NVIC_ICER_CLRENA_29 = 0x20000000
NVIC_ICER_CLRENA_30 = 0x40000000
NVIC_ICER_CLRENA_31 = 0x80000000
NVIC_ISPR_SETPEND = 0xFFFFFFFF
NVIC_ISPR_SETPEND_0 = 0x1
NVIC_ISPR_SETPEND_1 = 0x2
NVIC_ISPR_SETPEND_2 = 0x4
NVIC_ISPR_SETPEND_3 = 0x8
NVIC_ISPR_SETPEND_4 = 0x10
NVIC_ISPR_SETPEND_5 = 0x20
NVIC_ISPR_SETPEND_6 = 0x40
NVIC_ISPR_SETPEND_7 = 0x80
NVIC_ISPR_SETPEND_8 = 0x100
NVIC_ISPR_SETPEND_9 = 0x200
NVIC_ISPR_SETPEND_10 = 0x400
NVIC_ISPR_SETPEND_11 = 0x800
NVIC_ISPR_SETPEND_12 = 0x1000
NVIC_ISPR_SETPEND_13 = 0x2000
NVIC_ISPR_SETPEND_14 = 0x4000
NVIC_ISPR_SETPEND_15 = 0x8000
NVIC_ISPR_SETPEND_16 = 0x10000
NVIC_ISPR_SETPEND_17 = 0x20000
NVIC_ISPR_SETPEND_18 = 0x40000
NVIC_ISPR_SETPEND_19 = 0x80000
NVIC_ISPR_SETPEND_20 = 0x100000
NVIC_ISPR_SETPEND_21 = 0x200000
NVIC_ISPR_SETPEND_22 = 0x400000
NVIC_ISPR_SETPEND_23 = 0x800000
NVIC_ISPR_SETPEND_24 = 0x1000000
NVIC_ISPR_SETPEND_25 = 0x2000000
NVIC_ISPR_SETPEND_26 = 0x4000000
NVIC_ISPR_SETPEND_27 = 0x8000000
NVIC_ISPR_SETPEND_28 = 0x10000000
NVIC_ISPR_SETPEND_29 = 0x20000000
NVIC_ISPR_SETPEND_30 = 0x40000000
NVIC_ISPR_SETPEND_31 = 0x80000000
NVIC_ICPR_CLRPEND = 0xFFFFFFFF
NVIC_ICPR_CLRPEND_0 = 0x1
NVIC_ICPR_CLRPEND_1 = 0x2
NVIC_ICPR_CLRPEND_2 = 0x4
NVIC_ICPR_CLRPEND_3 = 0x8
NVIC_ICPR_CLRPEND_4 = 0x10
NVIC_ICPR_CLRPEND_5 = 0x20
NVIC_ICPR_CLRPEND_6 = 0x40
NVIC_ICPR_CLRPEND_7 = 0x80
NVIC_ICPR_CLRPEND_8 = 0x100
NVIC_ICPR_CLRPEND_9 = 0x200
NVIC_ICPR_CLRPEND_10 = 0x400
NVIC_ICPR_CLRPEND_11 = 0x800
NVIC_ICPR_CLRPEND_12 = 0x1000
NVIC_ICPR_CLRPEND_13 = 0x2000
NVIC_ICPR_CLRPEND_14 = 0x4000
NVIC_ICPR_CLRPEND_15 = 0x8000
NVIC_ICPR_CLRPEND_16 = 0x10000
NVIC_ICPR_CLRPEND_17 = 0x20000
NVIC_ICPR_CLRPEND_18 = 0x40000
NVIC_ICPR_CLRPEND_19 = 0x80000
NVIC_ICPR_CLRPEND_20 = 0x100000
NVIC_ICPR_CLRPEND_21 = 0x200000
NVIC_ICPR_CLRPEND_22 = 0x400000
NVIC_ICPR_CLRPEND_23 = 0x800000
NVIC_ICPR_CLRPEND_24 = 0x1000000
NVIC_ICPR_CLRPEND_25 = 0x2000000
NVIC_ICPR_CLRPEND_26 = 0x4000000
NVIC_ICPR_CLRPEND_27 = 0x8000000
NVIC_ICPR_CLRPEND_28 = 0x10000000
NVIC_ICPR_CLRPEND_29 = 0x20000000
NVIC_ICPR_CLRPEND_30 = 0x40000000
NVIC_ICPR_CLRPEND_31 = 0x80000000
NVIC_IABR_ACTIVE = 0xFFFFFFFF
NVIC_IABR_ACTIVE_0 = 0x1
NVIC_IABR_ACTIVE_1 = 0x2
NVIC_IABR_ACTIVE_2 = 0x4
NVIC_IABR_ACTIVE_3 = 0x8
NVIC_IABR_ACTIVE_4 = 0x10
NVIC_IABR_ACTIVE_5 = 0x20
NVIC_IABR_ACTIVE_6 = 0x40
NVIC_IABR_ACTIVE_7 = 0x80
NVIC_IABR_ACTIVE_8 = 0x100
NVIC_IABR_ACTIVE_9 = 0x200
NVIC_IABR_ACTIVE_10 = 0x400
NVIC_IABR_ACTIVE_11 = 0x800
NVIC_IABR_ACTIVE_12 = 0x1000
NVIC_IABR_ACTIVE_13 = 0x2000
NVIC_IABR_ACTIVE_14 = 0x4000
NVIC_IABR_ACTIVE_15 = 0x8000
NVIC_IABR_ACTIVE_16 = 0x10000
NVIC_IABR_ACTIVE_17 = 0x20000
NVIC_IABR_ACTIVE_18 = 0x40000
NVIC_IABR_ACTIVE_19 = 0x80000
NVIC_IABR_ACTIVE_20 = 0x100000
NVIC_IABR_ACTIVE_21 = 0x200000
NVIC_IABR_ACTIVE_22 = 0x400000
NVIC_IABR_ACTIVE_23 = 0x800000
NVIC_IABR_ACTIVE_24 = 0x1000000
NVIC_IABR_ACTIVE_25 = 0x2000000
NVIC_IABR_ACTIVE_26 = 0x4000000
NVIC_IABR_ACTIVE_27 = 0x8000000
NVIC_IABR_ACTIVE_28 = 0x10000000
NVIC_IABR_ACTIVE_29 = 0x20000000
NVIC_IABR_ACTIVE_30 = 0x40000000
NVIC_IABR_ACTIVE_31 = 0x80000000
NVIC_IPR0_PRI_0 = 0xFF
NVIC_IPR0_PRI_1 = 0xFF00
NVIC_IPR0_PRI_2 = 0xFF0000
NVIC_IPR0_PRI_3 = 0xFF000000
NVIC_IPR1_PRI_4 = 0xFF
NVIC_IPR1_PRI_5 = 0xFF00
NVIC_IPR1_PRI_6 = 0xFF0000
NVIC_IPR1_PRI_7 = 0xFF000000
NVIC_IPR2_PRI_8 = 0xFF
NVIC_IPR2_PRI_9 = 0xFF00
NVIC_IPR2_PRI_10 = 0xFF0000
NVIC_IPR2_PRI_11 = 0xFF000000
NVIC_IPR3_PRI_12 = 0xFF
NVIC_IPR3_PRI_13 = 0xFF00
NVIC_IPR3_PRI_14 = 0xFF0000
NVIC_IPR3_PRI_15 = 0xFF000000
NVIC_IPR4_PRI_16 = 0xFF
NVIC_IPR4_PRI_17 = 0xFF00
NVIC_IPR4_PRI_18 = 0xFF0000
NVIC_IPR4_PRI_19 = 0xFF000000
NVIC_IPR5_PRI_20 = 0xFF
NVIC_IPR5_PRI_21 = 0xFF00
NVIC_IPR5_PRI_22 = 0xFF0000
NVIC_IPR5_PRI_23 = 0xFF000000
NVIC_IPR6_PRI_24 = 0xFF
NVIC_IPR6_PRI_25 = 0xFF00
NVIC_IPR6_PRI_26 = 0xFF0000
NVIC_IPR6_PRI_27 = 0xFF000000
NVIC_IPR7_PRI_28 = 0xFF
NVIC_IPR7_PRI_29 = 0xFF00
NVIC_IPR7_PRI_30 = 0xFF0000
NVIC_IPR7_PRI_31 = 0xFF000000
SCB_CPUID_REVISION = 0xF
SCB_CPUID_PARTNO = 0xFFF0
SCB_CPUID_Constant = 0xF0000
SCB_CPUID_VARIANT = 0xF00000
SCB_CPUID_IMPLEMENTER = 0xFF000000
SCB_ICSR_VECTACTIVE = 0x1FF
SCB_ICSR_RETTOBASE = 0x800
SCB_ICSR_VECTPENDING = 0x3FF000
SCB_ICSR_ISRPENDING = 0x400000
SCB_ICSR_ISRPREEMPT = 0x800000
SCB_ICSR_PENDSTCLR = 0x2000000
SCB_ICSR_PENDSTSET = 0x4000000
SCB_ICSR_PENDSVCLR = 0x8000000
SCB_ICSR_PENDSVSET = 0x10000000
SCB_ICSR_NMIPENDSET = 0x80000000
SCB_VTOR_TBLOFF = 0x1FFFFF80
SCB_VTOR_TBLBASE = 0x20000000
SCB_AIRCR_VECTRESET = 0x1
SCB_AIRCR_VECTCLRACTIVE = 0x2
SCB_AIRCR_SYSRESETREQ = 0x4
SCB_AIRCR_PRIGROUP = 0x700
SCB_AIRCR_PRIGROUP_0 = 0x100
SCB_AIRCR_PRIGROUP_1 = 0x200
SCB_AIRCR_PRIGROUP_2 = 0x400
SCB_AIRCR_PRIGROUP0 = 0x0
SCB_AIRCR_PRIGROUP1 = 0x100
SCB_AIRCR_PRIGROUP2 = 0x200
SCB_AIRCR_PRIGROUP3 = 0x300
SCB_AIRCR_PRIGROUP4 = 0x400
SCB_AIRCR_PRIGROUP5 = 0x500
SCB_AIRCR_PRIGROUP6 = 0x600
SCB_AIRCR_PRIGROUP7 = 0x700
SCB_AIRCR_ENDIANESS = 0x8000
SCB_AIRCR_VECTKEY = 0xFFFF0000
SCB_SCR_SLEEPONEXIT = 0x2
SCB_SCR_SLEEPDEEP = 0x4
SCB_SCR_SEVONPEND = 0x10
SCB_CCR_NONBASETHRDENA = 0x1
SCB_CCR_USERSETMPEND = 0x2
SCB_CCR_UNALIGN_TRP = 0x8
SCB_CCR_DIV_0_TRP = 0x10
SCB_CCR_BFHFNMIGN = 0x100
SCB_CCR_STKALIGN = 0x200
SCB_SHPR_PRI_N = 0xFF
SCB_SHPR_PRI_N1 = 0xFF00
SCB_SHPR_PRI_N2 = 0xFF0000
SCB_SHPR_PRI_N3 = 0xFF000000
SCB_SHCSR_MEMFAULTACT = 0x1
SCB_SHCSR_BUSFAULTACT = 0x2
SCB_SHCSR_USGFAULTACT = 0x8
SCB_SHCSR_SVCALLACT = 0x80
SCB_SHCSR_MONITORACT = 0x100
SCB_SHCSR_PENDSVACT = 0x400
SCB_SHCSR_SYSTICKACT = 0x800
SCB_SHCSR_USGFAULTPENDED = 0x1000
SCB_SHCSR_MEMFAULTPENDED = 0x2000
SCB_SHCSR_BUSFAULTPENDED = 0x4000
SCB_SHCSR_SVCALLPENDED = 0x8000
SCB_SHCSR_MEMFAULTENA = 0x10000
SCB_SHCSR_BUSFAULTENA = 0x20000
SCB_SHCSR_USGFAULTENA = 0x40000
SCB_CFSR_IACCVIOL = 0x1
SCB_CFSR_DACCVIOL = 0x2
SCB_CFSR_MUNSTKERR = 0x8
SCB_CFSR_MSTKERR = 0x10
SCB_CFSR_MMARVALID = 0x80
SCB_CFSR_IBUSERR = 0x100
SCB_CFSR_PRECISERR = 0x200
SCB_CFSR_IMPRECISERR = 0x400
SCB_CFSR_UNSTKERR = 0x800
SCB_CFSR_STKERR = 0x1000
SCB_CFSR_BFARVALID = 0x8000
SCB_CFSR_UNDEFINSTR = 0x10000
SCB_CFSR_INVSTATE = 0x20000
SCB_CFSR_INVPC = 0x40000
SCB_CFSR_NOCP = 0x80000
SCB_CFSR_UNALIGNED = 0x1000000
SCB_CFSR_DIVBYZERO = 0x2000000
SCB_HFSR_VECTTBL = 0x2
SCB_HFSR_FORCED = 0x40000000
SCB_HFSR_DEBUGEVT = 0x80000000
SCB_DFSR_HALTED = 0x1
SCB_DFSR_BKPT = 0x2
SCB_DFSR_DWTTRAP = 0x4
SCB_DFSR_VCATCH = 0x8
SCB_DFSR_EXTERNAL = 0x10
SCB_MMFAR_ADDRESS = 0xFFFFFFFF
SCB_BFAR_ADDRESS = 0xFFFFFFFF
SCB_AFSR_IMPDEF = 0xFFFFFFFF
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
EXTI_RTSR_TR18 = 0x40000
EXTI_RTSR_TR19 = 0x80000
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
EXTI_FTSR_TR18 = 0x40000
EXTI_FTSR_TR19 = 0x80000
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
EXTI_SWIER_SWIER18 = 0x40000
EXTI_SWIER_SWIER19 = 0x80000
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
EXTI_PR_PR18 = 0x40000
EXTI_PR_PR19 = 0x80000
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
DMA_CCR1_EN = 0x1
DMA_CCR1_TCIE = 0x2
DMA_CCR1_HTIE = 0x4
DMA_CCR1_TEIE = 0x8
DMA_CCR1_DIR = 0x10
DMA_CCR1_CIRC = 0x20
DMA_CCR1_PINC = 0x40
DMA_CCR1_MINC = 0x80
DMA_CCR1_PSIZE = 0x300
DMA_CCR1_PSIZE_0 = 0x100
DMA_CCR1_PSIZE_1 = 0x200
DMA_CCR1_MSIZE = 0xC00
DMA_CCR1_MSIZE_0 = 0x400
DMA_CCR1_MSIZE_1 = 0x800
DMA_CCR1_PL = 0x3000
DMA_CCR1_PL_0 = 0x1000
DMA_CCR1_PL_1 = 0x2000
DMA_CCR1_MEM2MEM = 0x4000
DMA_CCR2_EN = 0x1
DMA_CCR2_TCIE = 0x2
DMA_CCR2_HTIE = 0x4
DMA_CCR2_TEIE = 0x8
DMA_CCR2_DIR = 0x10
DMA_CCR2_CIRC = 0x20
DMA_CCR2_PINC = 0x40
DMA_CCR2_MINC = 0x80
DMA_CCR2_PSIZE = 0x300
DMA_CCR2_PSIZE_0 = 0x100
DMA_CCR2_PSIZE_1 = 0x200
DMA_CCR2_MSIZE = 0xC00
DMA_CCR2_MSIZE_0 = 0x400
DMA_CCR2_MSIZE_1 = 0x800
DMA_CCR2_PL = 0x3000
DMA_CCR2_PL_0 = 0x1000
DMA_CCR2_PL_1 = 0x2000
DMA_CCR2_MEM2MEM = 0x4000
DMA_CCR3_EN = 0x1
DMA_CCR3_TCIE = 0x2
DMA_CCR3_HTIE = 0x4
DMA_CCR3_TEIE = 0x8
DMA_CCR3_DIR = 0x10
DMA_CCR3_CIRC = 0x20
DMA_CCR3_PINC = 0x40
DMA_CCR3_MINC = 0x80
DMA_CCR3_PSIZE = 0x300
DMA_CCR3_PSIZE_0 = 0x100
DMA_CCR3_PSIZE_1 = 0x200
DMA_CCR3_MSIZE = 0xC00
DMA_CCR3_MSIZE_0 = 0x400
DMA_CCR3_MSIZE_1 = 0x800
DMA_CCR3_PL = 0x3000
DMA_CCR3_PL_0 = 0x1000
DMA_CCR3_PL_1 = 0x2000
DMA_CCR3_MEM2MEM = 0x4000
DMA_CCR4_EN = 0x1
DMA_CCR4_TCIE = 0x2
DMA_CCR4_HTIE = 0x4
DMA_CCR4_TEIE = 0x8
DMA_CCR4_DIR = 0x10
DMA_CCR4_CIRC = 0x20
DMA_CCR4_PINC = 0x40
DMA_CCR4_MINC = 0x80
DMA_CCR4_PSIZE = 0x300
DMA_CCR4_PSIZE_0 = 0x100
DMA_CCR4_PSIZE_1 = 0x200
DMA_CCR4_MSIZE = 0xC00
DMA_CCR4_MSIZE_0 = 0x400
DMA_CCR4_MSIZE_1 = 0x800
DMA_CCR4_PL = 0x3000
DMA_CCR4_PL_0 = 0x1000
DMA_CCR4_PL_1 = 0x2000
DMA_CCR4_MEM2MEM = 0x4000
DMA_CCR5_EN = 0x1
DMA_CCR5_TCIE = 0x2
DMA_CCR5_HTIE = 0x4
DMA_CCR5_TEIE = 0x8
DMA_CCR5_DIR = 0x10
DMA_CCR5_CIRC = 0x20
DMA_CCR5_PINC = 0x40
DMA_CCR5_MINC = 0x80
DMA_CCR5_PSIZE = 0x300
DMA_CCR5_PSIZE_0 = 0x100
DMA_CCR5_PSIZE_1 = 0x200
DMA_CCR5_MSIZE = 0xC00
DMA_CCR5_MSIZE_0 = 0x400
DMA_CCR5_MSIZE_1 = 0x800
DMA_CCR5_PL = 0x3000
DMA_CCR5_PL_0 = 0x1000
DMA_CCR5_PL_1 = 0x2000
DMA_CCR5_MEM2MEM = 0x4000
DMA_CCR6_EN = 0x1
DMA_CCR6_TCIE = 0x2
DMA_CCR6_HTIE = 0x4
DMA_CCR6_TEIE = 0x8
DMA_CCR6_DIR = 0x10
DMA_CCR6_CIRC = 0x20
DMA_CCR6_PINC = 0x40
DMA_CCR6_MINC = 0x80
DMA_CCR6_PSIZE = 0x300
DMA_CCR6_PSIZE_0 = 0x100
DMA_CCR6_PSIZE_1 = 0x200
DMA_CCR6_MSIZE = 0xC00
DMA_CCR6_MSIZE_0 = 0x400
DMA_CCR6_MSIZE_1 = 0x800
DMA_CCR6_PL = 0x3000
DMA_CCR6_PL_0 = 0x1000
DMA_CCR6_PL_1 = 0x2000
DMA_CCR6_MEM2MEM = 0x4000
DMA_CCR7_EN = 0x1
DMA_CCR7_TCIE = 0x2
DMA_CCR7_HTIE = 0x4
DMA_CCR7_TEIE = 0x8
DMA_CCR7_DIR = 0x10
DMA_CCR7_CIRC = 0x20
DMA_CCR7_PINC = 0x40
DMA_CCR7_MINC = 0x80
DMA_CCR7_PSIZE = 0x300
DMA_CCR7_PSIZE_0 = 0x100
DMA_CCR7_PSIZE_1 = 0x200
DMA_CCR7_MSIZE = 0xC00
DMA_CCR7_MSIZE_0 = 0x400
DMA_CCR7_MSIZE_1 = 0x800
DMA_CCR7_PL = 0x3000
DMA_CCR7_PL_0 = 0x1000
DMA_CCR7_PL_1 = 0x2000
DMA_CCR7_MEM2MEM = 0x4000
DMA_CNDTR1_NDT = 0xFFFF
DMA_CNDTR2_NDT = 0xFFFF
DMA_CNDTR3_NDT = 0xFFFF
DMA_CNDTR4_NDT = 0xFFFF
DMA_CNDTR5_NDT = 0xFFFF
DMA_CNDTR6_NDT = 0xFFFF
DMA_CNDTR7_NDT = 0xFFFF
DMA_CPAR1_PA = 0xFFFFFFFF
DMA_CPAR2_PA = 0xFFFFFFFF
DMA_CPAR3_PA = 0xFFFFFFFF
DMA_CPAR4_PA = 0xFFFFFFFF
DMA_CPAR5_PA = 0xFFFFFFFF
DMA_CPAR6_PA = 0xFFFFFFFF
DMA_CPAR7_PA = 0xFFFFFFFF
DMA_CMAR1_MA = 0xFFFFFFFF
DMA_CMAR2_MA = 0xFFFFFFFF
DMA_CMAR3_MA = 0xFFFFFFFF
DMA_CMAR4_MA = 0xFFFFFFFF
DMA_CMAR5_MA = 0xFFFFFFFF
DMA_CMAR6_MA = 0xFFFFFFFF
DMA_CMAR7_MA = 0xFFFFFFFF
ADC_SR_AWD = 0x1
ADC_SR_EOC = 0x2
ADC_SR_JEOC = 0x4
ADC_SR_JSTRT = 0x8
ADC_SR_STRT = 0x10
ADC_CR1_AWDCH = 0x1F
ADC_CR1_AWDCH_0 = 0x1
ADC_CR1_AWDCH_1 = 0x2
ADC_CR1_AWDCH_2 = 0x4
ADC_CR1_AWDCH_3 = 0x8
ADC_CR1_AWDCH_4 = 0x10
ADC_CR1_EOCIE = 0x20
ADC_CR1_AWDIE = 0x40
ADC_CR1_JEOCIE = 0x80
ADC_CR1_SCAN = 0x100
ADC_CR1_AWDSGL = 0x200
ADC_CR1_JAUTO = 0x400
ADC_CR1_DISCEN = 0x800
ADC_CR1_JDISCEN = 0x1000
ADC_CR1_DISCNUM = 0xE000
ADC_CR1_DISCNUM_0 = 0x2000
ADC_CR1_DISCNUM_1 = 0x4000
ADC_CR1_DISCNUM_2 = 0x8000
ADC_CR1_DUALMOD = 0xF0000
ADC_CR1_DUALMOD_0 = 0x10000
ADC_CR1_DUALMOD_1 = 0x20000
ADC_CR1_DUALMOD_2 = 0x40000
ADC_CR1_DUALMOD_3 = 0x80000
ADC_CR1_JAWDEN = 0x400000
ADC_CR1_AWDEN = 0x800000
ADC_CR2_ADON = 0x1
ADC_CR2_CONT = 0x2
ADC_CR2_CAL = 0x4
ADC_CR2_RSTCAL = 0x8
ADC_CR2_DMA = 0x100
ADC_CR2_ALIGN = 0x800
ADC_CR2_JEXTSEL = 0x7000
ADC_CR2_JEXTSEL_0 = 0x1000
ADC_CR2_JEXTSEL_1 = 0x2000
ADC_CR2_JEXTSEL_2 = 0x4000
ADC_CR2_JEXTTRIG = 0x8000
ADC_CR2_EXTSEL = 0xE0000
ADC_CR2_EXTSEL_0 = 0x20000
ADC_CR2_EXTSEL_1 = 0x40000
ADC_CR2_EXTSEL_2 = 0x80000
ADC_CR2_EXTTRIG = 0x100000
ADC_CR2_JSWSTART = 0x200000
ADC_CR2_SWSTART = 0x400000
ADC_CR2_TSVREFE = 0x800000
ADC_SMPR1_SMP10 = 0x7
ADC_SMPR1_SMP10_0 = 0x1
ADC_SMPR1_SMP10_1 = 0x2
ADC_SMPR1_SMP10_2 = 0x4
ADC_SMPR1_SMP11 = 0x38
ADC_SMPR1_SMP11_0 = 0x8
ADC_SMPR1_SMP11_1 = 0x10
ADC_SMPR1_SMP11_2 = 0x20
ADC_SMPR1_SMP12 = 0x1C0
ADC_SMPR1_SMP12_0 = 0x40
ADC_SMPR1_SMP12_1 = 0x80
ADC_SMPR1_SMP12_2 = 0x100
ADC_SMPR1_SMP13 = 0xE00
ADC_SMPR1_SMP13_0 = 0x200
ADC_SMPR1_SMP13_1 = 0x400
ADC_SMPR1_SMP13_2 = 0x800
ADC_SMPR1_SMP14 = 0x7000
ADC_SMPR1_SMP14_0 = 0x1000
ADC_SMPR1_SMP14_1 = 0x2000
ADC_SMPR1_SMP14_2 = 0x4000
ADC_SMPR1_SMP15 = 0x38000
ADC_SMPR1_SMP15_0 = 0x8000
ADC_SMPR1_SMP15_1 = 0x10000
ADC_SMPR1_SMP15_2 = 0x20000
ADC_SMPR1_SMP16 = 0x1C0000
ADC_SMPR1_SMP16_0 = 0x40000
ADC_SMPR1_SMP16_1 = 0x80000
ADC_SMPR1_SMP16_2 = 0x100000
ADC_SMPR1_SMP17 = 0xE00000
ADC_SMPR1_SMP17_0 = 0x200000
ADC_SMPR1_SMP17_1 = 0x400000
ADC_SMPR1_SMP17_2 = 0x800000
ADC_SMPR2_SMP0 = 0x7
ADC_SMPR2_SMP0_0 = 0x1
ADC_SMPR2_SMP0_1 = 0x2
ADC_SMPR2_SMP0_2 = 0x4
ADC_SMPR2_SMP1 = 0x38
ADC_SMPR2_SMP1_0 = 0x8
ADC_SMPR2_SMP1_1 = 0x10
ADC_SMPR2_SMP1_2 = 0x20
ADC_SMPR2_SMP2 = 0x1C0
ADC_SMPR2_SMP2_0 = 0x40
ADC_SMPR2_SMP2_1 = 0x80
ADC_SMPR2_SMP2_2 = 0x100
ADC_SMPR2_SMP3 = 0xE00
ADC_SMPR2_SMP3_0 = 0x200
ADC_SMPR2_SMP3_1 = 0x400
ADC_SMPR2_SMP3_2 = 0x800
ADC_SMPR2_SMP4 = 0x7000
ADC_SMPR2_SMP4_0 = 0x1000
ADC_SMPR2_SMP4_1 = 0x2000
ADC_SMPR2_SMP4_2 = 0x4000
ADC_SMPR2_SMP5 = 0x38000
ADC_SMPR2_SMP5_0 = 0x8000
ADC_SMPR2_SMP5_1 = 0x10000
ADC_SMPR2_SMP5_2 = 0x20000
ADC_SMPR2_SMP6 = 0x1C0000
ADC_SMPR2_SMP6_0 = 0x40000
ADC_SMPR2_SMP6_1 = 0x80000
ADC_SMPR2_SMP6_2 = 0x100000
ADC_SMPR2_SMP7 = 0xE00000
ADC_SMPR2_SMP7_0 = 0x200000
ADC_SMPR2_SMP7_1 = 0x400000
ADC_SMPR2_SMP7_2 = 0x800000
ADC_SMPR2_SMP8 = 0x7000000
ADC_SMPR2_SMP8_0 = 0x1000000
ADC_SMPR2_SMP8_1 = 0x2000000
ADC_SMPR2_SMP8_2 = 0x4000000
ADC_SMPR2_SMP9 = 0x38000000
ADC_SMPR2_SMP9_0 = 0x8000000
ADC_SMPR2_SMP9_1 = 0x10000000
ADC_SMPR2_SMP9_2 = 0x20000000
ADC_JOFR1_JOFFSET1 = 0xFFF
ADC_JOFR2_JOFFSET2 = 0xFFF
ADC_JOFR3_JOFFSET3 = 0xFFF
ADC_JOFR4_JOFFSET4 = 0xFFF
ADC_HTR_HT = 0xFFF
ADC_LTR_LT = 0xFFF
ADC_SQR1_SQ13 = 0x1F
ADC_SQR1_SQ13_0 = 0x1
ADC_SQR1_SQ13_1 = 0x2
ADC_SQR1_SQ13_2 = 0x4
ADC_SQR1_SQ13_3 = 0x8
ADC_SQR1_SQ13_4 = 0x10
ADC_SQR1_SQ14 = 0x3E0
ADC_SQR1_SQ14_0 = 0x20
ADC_SQR1_SQ14_1 = 0x40
ADC_SQR1_SQ14_2 = 0x80
ADC_SQR1_SQ14_3 = 0x100
ADC_SQR1_SQ14_4 = 0x200
ADC_SQR1_SQ15 = 0x7C00
ADC_SQR1_SQ15_0 = 0x400
ADC_SQR1_SQ15_1 = 0x800
ADC_SQR1_SQ15_2 = 0x1000
ADC_SQR1_SQ15_3 = 0x2000
ADC_SQR1_SQ15_4 = 0x4000
ADC_SQR1_SQ16 = 0xF8000
ADC_SQR1_SQ16_0 = 0x8000
ADC_SQR1_SQ16_1 = 0x10000
ADC_SQR1_SQ16_2 = 0x20000
ADC_SQR1_SQ16_3 = 0x40000
ADC_SQR1_SQ16_4 = 0x80000
ADC_SQR1_L = 0xF00000
ADC_SQR1_L_0 = 0x100000
ADC_SQR1_L_1 = 0x200000
ADC_SQR1_L_2 = 0x400000
ADC_SQR1_L_3 = 0x800000
ADC_SQR2_SQ7 = 0x1F
ADC_SQR2_SQ7_0 = 0x1
ADC_SQR2_SQ7_1 = 0x2
ADC_SQR2_SQ7_2 = 0x4
ADC_SQR2_SQ7_3 = 0x8
ADC_SQR2_SQ7_4 = 0x10
ADC_SQR2_SQ8 = 0x3E0
ADC_SQR2_SQ8_0 = 0x20
ADC_SQR2_SQ8_1 = 0x40
ADC_SQR2_SQ8_2 = 0x80
ADC_SQR2_SQ8_3 = 0x100
ADC_SQR2_SQ8_4 = 0x200
ADC_SQR2_SQ9 = 0x7C00
ADC_SQR2_SQ9_0 = 0x400
ADC_SQR2_SQ9_1 = 0x800
ADC_SQR2_SQ9_2 = 0x1000
ADC_SQR2_SQ9_3 = 0x2000
ADC_SQR2_SQ9_4 = 0x4000
ADC_SQR2_SQ10 = 0xF8000
ADC_SQR2_SQ10_0 = 0x8000
ADC_SQR2_SQ10_1 = 0x10000
ADC_SQR2_SQ10_2 = 0x20000
ADC_SQR2_SQ10_3 = 0x40000
ADC_SQR2_SQ10_4 = 0x80000
ADC_SQR2_SQ11 = 0x1F00000
ADC_SQR2_SQ11_0 = 0x100000
ADC_SQR2_SQ11_1 = 0x200000
ADC_SQR2_SQ11_2 = 0x400000
ADC_SQR2_SQ11_3 = 0x800000
ADC_SQR2_SQ11_4 = 0x1000000
ADC_SQR2_SQ12 = 0x3E000000
ADC_SQR2_SQ12_0 = 0x2000000
ADC_SQR2_SQ12_1 = 0x4000000
ADC_SQR2_SQ12_2 = 0x8000000
ADC_SQR2_SQ12_3 = 0x10000000
ADC_SQR2_SQ12_4 = 0x20000000
ADC_SQR3_SQ1 = 0x1F
ADC_SQR3_SQ1_0 = 0x1
ADC_SQR3_SQ1_1 = 0x2
ADC_SQR3_SQ1_2 = 0x4
ADC_SQR3_SQ1_3 = 0x8
ADC_SQR3_SQ1_4 = 0x10
ADC_SQR3_SQ2 = 0x3E0
ADC_SQR3_SQ2_0 = 0x20
ADC_SQR3_SQ2_1 = 0x40
ADC_SQR3_SQ2_2 = 0x80
ADC_SQR3_SQ2_3 = 0x100
ADC_SQR3_SQ2_4 = 0x200
ADC_SQR3_SQ3 = 0x7C00
ADC_SQR3_SQ3_0 = 0x400
ADC_SQR3_SQ3_1 = 0x800
ADC_SQR3_SQ3_2 = 0x1000
ADC_SQR3_SQ3_3 = 0x2000
ADC_SQR3_SQ3_4 = 0x4000
ADC_SQR3_SQ4 = 0xF8000
ADC_SQR3_SQ4_0 = 0x8000
ADC_SQR3_SQ4_1 = 0x10000
ADC_SQR3_SQ4_2 = 0x20000
ADC_SQR3_SQ4_3 = 0x40000
ADC_SQR3_SQ4_4 = 0x80000
ADC_SQR3_SQ5 = 0x1F00000
ADC_SQR3_SQ5_0 = 0x100000
ADC_SQR3_SQ5_1 = 0x200000
ADC_SQR3_SQ5_2 = 0x400000
ADC_SQR3_SQ5_3 = 0x800000
ADC_SQR3_SQ5_4 = 0x1000000
ADC_SQR3_SQ6 = 0x3E000000
ADC_SQR3_SQ6_0 = 0x2000000
ADC_SQR3_SQ6_1 = 0x4000000
ADC_SQR3_SQ6_2 = 0x8000000
ADC_SQR3_SQ6_3 = 0x10000000
ADC_SQR3_SQ6_4 = 0x20000000
ADC_JSQR_JSQ1 = 0x1F
ADC_JSQR_JSQ1_0 = 0x1
ADC_JSQR_JSQ1_1 = 0x2
ADC_JSQR_JSQ1_2 = 0x4
ADC_JSQR_JSQ1_3 = 0x8
ADC_JSQR_JSQ1_4 = 0x10
ADC_JSQR_JSQ2 = 0x3E0
ADC_JSQR_JSQ2_0 = 0x20
ADC_JSQR_JSQ2_1 = 0x40
ADC_JSQR_JSQ2_2 = 0x80
ADC_JSQR_JSQ2_3 = 0x100
ADC_JSQR_JSQ2_4 = 0x200
ADC_JSQR_JSQ3 = 0x7C00
ADC_JSQR_JSQ3_0 = 0x400
ADC_JSQR_JSQ3_1 = 0x800
ADC_JSQR_JSQ3_2 = 0x1000
ADC_JSQR_JSQ3_3 = 0x2000
ADC_JSQR_JSQ3_4 = 0x4000
ADC_JSQR_JSQ4 = 0xF8000
ADC_JSQR_JSQ4_0 = 0x8000
ADC_JSQR_JSQ4_1 = 0x10000
ADC_JSQR_JSQ4_2 = 0x20000
ADC_JSQR_JSQ4_3 = 0x40000
ADC_JSQR_JSQ4_4 = 0x80000
ADC_JSQR_JL = 0x300000
ADC_JSQR_JL_0 = 0x100000
ADC_JSQR_JL_1 = 0x200000
ADC_JDR1_JDATA = 0xFFFF
ADC_JDR2_JDATA = 0xFFFF
ADC_JDR3_JDATA = 0xFFFF
ADC_JDR4_JDATA = 0xFFFF
ADC_DR_DATA = 0xFFFF
ADC_DR_ADC2DATA = 0xFFFF0000
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
DAC_SWTRIGR_SWTRIG1 = 0x1
DAC_SWTRIGR_SWTRIG2 = 0x2
DAC_DHR12R1_DACC1DHR = 0xFFF
DAC_DHR12L1_DACC1DHR = 0xFFF0
DAC_DHR8R1_DACC1DHR = 0xFF
DAC_DHR12R2_DACC2DHR = 0xFFF
DAC_DHR12L2_DACC2DHR = 0xFFF0
DAC_DHR8R2_DACC2DHR = 0xFF
DAC_DHR12RD_DACC1DHR = 0xFFF
DAC_DHR12RD_DACC2DHR = 0xFFF0000
DAC_DHR12LD_DACC1DHR = 0xFFF0
DAC_DHR12LD_DACC2DHR = 0xFFF00000
DAC_DHR8RD_DACC1DHR = 0xFF
DAC_DHR8RD_DACC2DHR = 0xFF00
DAC_DOR1_DACC1DOR = 0xFFF
DAC_DOR2_DACC2DOR = 0xFFF
DAC_SR_DMAUDR1 = 0x2000
DAC_SR_DMAUDR2 = 0x20000000
CEC_CFGR_PE = 0x1
CEC_CFGR_IE = 0x2
CEC_CFGR_BTEM = 0x4
CEC_CFGR_BPEM = 0x8
CEC_OAR_OA = 0xF
CEC_OAR_OA_0 = 0x1
CEC_OAR_OA_1 = 0x2
CEC_OAR_OA_2 = 0x4
CEC_OAR_OA_3 = 0x8
CEC_PRES_PRES = 0x3FFF
CEC_ESR_BTE = 0x1
CEC_ESR_BPE = 0x2
CEC_ESR_RBTFE = 0x4
CEC_ESR_SBE = 0x8
CEC_ESR_ACKE = 0x10
CEC_ESR_LINE = 0x20
CEC_ESR_TBTFE = 0x40
CEC_CSR_TSOM = 0x1
CEC_CSR_TEOM = 0x2
CEC_CSR_TERR = 0x4
CEC_CSR_TBTRF = 0x8
CEC_CSR_RSOM = 0x10
CEC_CSR_REOM = 0x20
CEC_CSR_RERR = 0x40
CEC_CSR_RBTF = 0x80
CEC_TXD_TXD = 0xFF
CEC_RXD_RXD = 0xFF
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
RTC_CRH_SECIE = 0x1
RTC_CRH_ALRIE = 0x2
RTC_CRH_OWIE = 0x4
RTC_CRL_SECF = 0x1
RTC_CRL_ALRF = 0x2
RTC_CRL_OWF = 0x4
RTC_CRL_RSF = 0x8
RTC_CRL_CNF = 0x10
RTC_CRL_RTOFF = 0x20
RTC_PRLH_PRL = 0xF
RTC_PRLL_PRL = 0xFFFF
RTC_DIVH_RTC_DIV = 0xF
RTC_DIVL_RTC_DIV = 0xFFFF
RTC_CNTH_RTC_CNT = 0xFFFF
RTC_CNTL_RTC_CNT = 0xFFFF
RTC_ALRH_RTC_ALR = 0xFFFF
RTC_ALRL_RTC_ALR = 0xFFFF
IWDG_KR_KEY = 0xFFFF
IWDG_PR_PR = 0x7
IWDG_PR_PR_0 = 0x1
IWDG_PR_PR_1 = 0x2
IWDG_PR_PR_2 = 0x4
IWDG_RLR_RL = 0xFFF
IWDG_SR_PVU = 0x1
IWDG_SR_RVU = 0x2
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
FSMC_BCR1_MBKEN = 0x1
FSMC_BCR1_MUXEN = 0x2
FSMC_BCR1_MTYP = 0xC
FSMC_BCR1_MTYP_0 = 0x4
FSMC_BCR1_MTYP_1 = 0x8
FSMC_BCR1_MWID = 0x30
FSMC_BCR1_MWID_0 = 0x10
FSMC_BCR1_MWID_1 = 0x20
FSMC_BCR1_FACCEN = 0x40
FSMC_BCR1_BURSTEN = 0x100
FSMC_BCR1_WAITPOL = 0x200
FSMC_BCR1_WRAPMOD = 0x400
FSMC_BCR1_WAITCFG = 0x800
FSMC_BCR1_WREN = 0x1000
FSMC_BCR1_WAITEN = 0x2000
FSMC_BCR1_EXTMOD = 0x4000
FSMC_BCR1_ASYNCWAIT = 0x8000
FSMC_BCR1_CBURSTRW = 0x80000
FSMC_BCR2_MBKEN = 0x1
FSMC_BCR2_MUXEN = 0x2
FSMC_BCR2_MTYP = 0xC
FSMC_BCR2_MTYP_0 = 0x4
FSMC_BCR2_MTYP_1 = 0x8
FSMC_BCR2_MWID = 0x30
FSMC_BCR2_MWID_0 = 0x10
FSMC_BCR2_MWID_1 = 0x20
FSMC_BCR2_FACCEN = 0x40
FSMC_BCR2_BURSTEN = 0x100
FSMC_BCR2_WAITPOL = 0x200
FSMC_BCR2_WRAPMOD = 0x400
FSMC_BCR2_WAITCFG = 0x800
FSMC_BCR2_WREN = 0x1000
FSMC_BCR2_WAITEN = 0x2000
FSMC_BCR2_EXTMOD = 0x4000
FSMC_BCR2_ASYNCWAIT = 0x8000
FSMC_BCR2_CBURSTRW = 0x80000
FSMC_BCR3_MBKEN = 0x1
FSMC_BCR3_MUXEN = 0x2
FSMC_BCR3_MTYP = 0xC
FSMC_BCR3_MTYP_0 = 0x4
FSMC_BCR3_MTYP_1 = 0x8
FSMC_BCR3_MWID = 0x30
FSMC_BCR3_MWID_0 = 0x10
FSMC_BCR3_MWID_1 = 0x20
FSMC_BCR3_FACCEN = 0x40
FSMC_BCR3_BURSTEN = 0x100
FSMC_BCR3_WAITPOL = 0x200
FSMC_BCR3_WRAPMOD = 0x400
FSMC_BCR3_WAITCFG = 0x800
FSMC_BCR3_WREN = 0x1000
FSMC_BCR3_WAITEN = 0x2000
FSMC_BCR3_EXTMOD = 0x4000
FSMC_BCR3_ASYNCWAIT = 0x8000
FSMC_BCR3_CBURSTRW = 0x80000
FSMC_BCR4_MBKEN = 0x1
FSMC_BCR4_MUXEN = 0x2
FSMC_BCR4_MTYP = 0xC
FSMC_BCR4_MTYP_0 = 0x4
FSMC_BCR4_MTYP_1 = 0x8
FSMC_BCR4_MWID = 0x30
FSMC_BCR4_MWID_0 = 0x10
FSMC_BCR4_MWID_1 = 0x20
FSMC_BCR4_FACCEN = 0x40
FSMC_BCR4_BURSTEN = 0x100
FSMC_BCR4_WAITPOL = 0x200
FSMC_BCR4_WRAPMOD = 0x400
FSMC_BCR4_WAITCFG = 0x800
FSMC_BCR4_WREN = 0x1000
FSMC_BCR4_WAITEN = 0x2000
FSMC_BCR4_EXTMOD = 0x4000
FSMC_BCR4_ASYNCWAIT = 0x8000
FSMC_BCR4_CBURSTRW = 0x80000
FSMC_BTR1_ADDSET = 0xF
FSMC_BTR1_ADDSET_0 = 0x1
FSMC_BTR1_ADDSET_1 = 0x2
FSMC_BTR1_ADDSET_2 = 0x4
FSMC_BTR1_ADDSET_3 = 0x8
FSMC_BTR1_ADDHLD = 0xF0
FSMC_BTR1_ADDHLD_0 = 0x10
FSMC_BTR1_ADDHLD_1 = 0x20
FSMC_BTR1_ADDHLD_2 = 0x40
FSMC_BTR1_ADDHLD_3 = 0x80
FSMC_BTR1_DATAST = 0xFF00
FSMC_BTR1_DATAST_0 = 0x100
FSMC_BTR1_DATAST_1 = 0x200
FSMC_BTR1_DATAST_2 = 0x400
FSMC_BTR1_DATAST_3 = 0x800
FSMC_BTR1_BUSTURN = 0xF0000
FSMC_BTR1_BUSTURN_0 = 0x10000
FSMC_BTR1_BUSTURN_1 = 0x20000
FSMC_BTR1_BUSTURN_2 = 0x40000
FSMC_BTR1_BUSTURN_3 = 0x80000
FSMC_BTR1_CLKDIV = 0xF00000
FSMC_BTR1_CLKDIV_0 = 0x100000
FSMC_BTR1_CLKDIV_1 = 0x200000
FSMC_BTR1_CLKDIV_2 = 0x400000
FSMC_BTR1_CLKDIV_3 = 0x800000
FSMC_BTR1_DATLAT = 0xF000000
FSMC_BTR1_DATLAT_0 = 0x1000000
FSMC_BTR1_DATLAT_1 = 0x2000000
FSMC_BTR1_DATLAT_2 = 0x4000000
FSMC_BTR1_DATLAT_3 = 0x8000000
FSMC_BTR1_ACCMOD = 0x30000000
FSMC_BTR1_ACCMOD_0 = 0x10000000
FSMC_BTR1_ACCMOD_1 = 0x20000000
FSMC_BTR2_ADDSET = 0xF
FSMC_BTR2_ADDSET_0 = 0x1
FSMC_BTR2_ADDSET_1 = 0x2
FSMC_BTR2_ADDSET_2 = 0x4
FSMC_BTR2_ADDSET_3 = 0x8
FSMC_BTR2_ADDHLD = 0xF0
FSMC_BTR2_ADDHLD_0 = 0x10
FSMC_BTR2_ADDHLD_1 = 0x20
FSMC_BTR2_ADDHLD_2 = 0x40
FSMC_BTR2_ADDHLD_3 = 0x80
FSMC_BTR2_DATAST = 0xFF00
FSMC_BTR2_DATAST_0 = 0x100
FSMC_BTR2_DATAST_1 = 0x200
FSMC_BTR2_DATAST_2 = 0x400
FSMC_BTR2_DATAST_3 = 0x800
FSMC_BTR2_BUSTURN = 0xF0000
FSMC_BTR2_BUSTURN_0 = 0x10000
FSMC_BTR2_BUSTURN_1 = 0x20000
FSMC_BTR2_BUSTURN_2 = 0x40000
FSMC_BTR2_BUSTURN_3 = 0x80000
FSMC_BTR2_CLKDIV = 0xF00000
FSMC_BTR2_CLKDIV_0 = 0x100000
FSMC_BTR2_CLKDIV_1 = 0x200000
FSMC_BTR2_CLKDIV_2 = 0x400000
FSMC_BTR2_CLKDIV_3 = 0x800000
FSMC_BTR2_DATLAT = 0xF000000
FSMC_BTR2_DATLAT_0 = 0x1000000
FSMC_BTR2_DATLAT_1 = 0x2000000
FSMC_BTR2_DATLAT_2 = 0x4000000
FSMC_BTR2_DATLAT_3 = 0x8000000
FSMC_BTR2_ACCMOD = 0x30000000
FSMC_BTR2_ACCMOD_0 = 0x10000000
FSMC_BTR2_ACCMOD_1 = 0x20000000
FSMC_BTR3_ADDSET = 0xF
FSMC_BTR3_ADDSET_0 = 0x1
FSMC_BTR3_ADDSET_1 = 0x2
FSMC_BTR3_ADDSET_2 = 0x4
FSMC_BTR3_ADDSET_3 = 0x8
FSMC_BTR3_ADDHLD = 0xF0
FSMC_BTR3_ADDHLD_0 = 0x10
FSMC_BTR3_ADDHLD_1 = 0x20
FSMC_BTR3_ADDHLD_2 = 0x40
FSMC_BTR3_ADDHLD_3 = 0x80
FSMC_BTR3_DATAST = 0xFF00
FSMC_BTR3_DATAST_0 = 0x100
FSMC_BTR3_DATAST_1 = 0x200
FSMC_BTR3_DATAST_2 = 0x400
FSMC_BTR3_DATAST_3 = 0x800
FSMC_BTR3_BUSTURN = 0xF0000
FSMC_BTR3_BUSTURN_0 = 0x10000
FSMC_BTR3_BUSTURN_1 = 0x20000
FSMC_BTR3_BUSTURN_2 = 0x40000
FSMC_BTR3_BUSTURN_3 = 0x80000
FSMC_BTR3_CLKDIV = 0xF00000
FSMC_BTR3_CLKDIV_0 = 0x100000
FSMC_BTR3_CLKDIV_1 = 0x200000
FSMC_BTR3_CLKDIV_2 = 0x400000
FSMC_BTR3_CLKDIV_3 = 0x800000
FSMC_BTR3_DATLAT = 0xF000000
FSMC_BTR3_DATLAT_0 = 0x1000000
FSMC_BTR3_DATLAT_1 = 0x2000000
FSMC_BTR3_DATLAT_2 = 0x4000000
FSMC_BTR3_DATLAT_3 = 0x8000000
FSMC_BTR3_ACCMOD = 0x30000000
FSMC_BTR3_ACCMOD_0 = 0x10000000
FSMC_BTR3_ACCMOD_1 = 0x20000000
FSMC_BTR4_ADDSET = 0xF
FSMC_BTR4_ADDSET_0 = 0x1
FSMC_BTR4_ADDSET_1 = 0x2
FSMC_BTR4_ADDSET_2 = 0x4
FSMC_BTR4_ADDSET_3 = 0x8
FSMC_BTR4_ADDHLD = 0xF0
FSMC_BTR4_ADDHLD_0 = 0x10
FSMC_BTR4_ADDHLD_1 = 0x20
FSMC_BTR4_ADDHLD_2 = 0x40
FSMC_BTR4_ADDHLD_3 = 0x80
FSMC_BTR4_DATAST = 0xFF00
FSMC_BTR4_DATAST_0 = 0x100
FSMC_BTR4_DATAST_1 = 0x200
FSMC_BTR4_DATAST_2 = 0x400
FSMC_BTR4_DATAST_3 = 0x800
FSMC_BTR4_BUSTURN = 0xF0000
FSMC_BTR4_BUSTURN_0 = 0x10000
FSMC_BTR4_BUSTURN_1 = 0x20000
FSMC_BTR4_BUSTURN_2 = 0x40000
FSMC_BTR4_BUSTURN_3 = 0x80000
FSMC_BTR4_CLKDIV = 0xF00000
FSMC_BTR4_CLKDIV_0 = 0x100000
FSMC_BTR4_CLKDIV_1 = 0x200000
FSMC_BTR4_CLKDIV_2 = 0x400000
FSMC_BTR4_CLKDIV_3 = 0x800000
FSMC_BTR4_DATLAT = 0xF000000
FSMC_BTR4_DATLAT_0 = 0x1000000
FSMC_BTR4_DATLAT_1 = 0x2000000
FSMC_BTR4_DATLAT_2 = 0x4000000
FSMC_BTR4_DATLAT_3 = 0x8000000
FSMC_BTR4_ACCMOD = 0x30000000
FSMC_BTR4_ACCMOD_0 = 0x10000000
FSMC_BTR4_ACCMOD_1 = 0x20000000
FSMC_BWTR1_ADDSET = 0xF
FSMC_BWTR1_ADDSET_0 = 0x1
FSMC_BWTR1_ADDSET_1 = 0x2
FSMC_BWTR1_ADDSET_2 = 0x4
FSMC_BWTR1_ADDSET_3 = 0x8
FSMC_BWTR1_ADDHLD = 0xF0
FSMC_BWTR1_ADDHLD_0 = 0x10
FSMC_BWTR1_ADDHLD_1 = 0x20
FSMC_BWTR1_ADDHLD_2 = 0x40
FSMC_BWTR1_ADDHLD_3 = 0x80
FSMC_BWTR1_DATAST = 0xFF00
FSMC_BWTR1_DATAST_0 = 0x100
FSMC_BWTR1_DATAST_1 = 0x200
FSMC_BWTR1_DATAST_2 = 0x400
FSMC_BWTR1_DATAST_3 = 0x800
FSMC_BWTR1_CLKDIV = 0xF00000
FSMC_BWTR1_CLKDIV_0 = 0x100000
FSMC_BWTR1_CLKDIV_1 = 0x200000
FSMC_BWTR1_CLKDIV_2 = 0x400000
FSMC_BWTR1_CLKDIV_3 = 0x800000
FSMC_BWTR1_DATLAT = 0xF000000
FSMC_BWTR1_DATLAT_0 = 0x1000000
FSMC_BWTR1_DATLAT_1 = 0x2000000
FSMC_BWTR1_DATLAT_2 = 0x4000000
FSMC_BWTR1_DATLAT_3 = 0x8000000
FSMC_BWTR1_ACCMOD = 0x30000000
FSMC_BWTR1_ACCMOD_0 = 0x10000000
FSMC_BWTR1_ACCMOD_1 = 0x20000000
FSMC_BWTR2_ADDSET = 0xF
FSMC_BWTR2_ADDSET_0 = 0x1
FSMC_BWTR2_ADDSET_1 = 0x2
FSMC_BWTR2_ADDSET_2 = 0x4
FSMC_BWTR2_ADDSET_3 = 0x8
FSMC_BWTR2_ADDHLD = 0xF0
FSMC_BWTR2_ADDHLD_0 = 0x10
FSMC_BWTR2_ADDHLD_1 = 0x20
FSMC_BWTR2_ADDHLD_2 = 0x40
FSMC_BWTR2_ADDHLD_3 = 0x80
FSMC_BWTR2_DATAST = 0xFF00
FSMC_BWTR2_DATAST_0 = 0x100
FSMC_BWTR2_DATAST_1 = 0x200
FSMC_BWTR2_DATAST_2 = 0x400
FSMC_BWTR2_DATAST_3 = 0x800
FSMC_BWTR2_CLKDIV = 0xF00000
FSMC_BWTR2_CLKDIV_0 = 0x100000
FSMC_BWTR2_CLKDIV_1 = 0x200000
FSMC_BWTR2_CLKDIV_2 = 0x400000
FSMC_BWTR2_CLKDIV_3 = 0x800000
FSMC_BWTR2_DATLAT = 0xF000000
FSMC_BWTR2_DATLAT_0 = 0x1000000
FSMC_BWTR2_DATLAT_1 = 0x2000000
FSMC_BWTR2_DATLAT_2 = 0x4000000
FSMC_BWTR2_DATLAT_3 = 0x8000000
FSMC_BWTR2_ACCMOD = 0x30000000
FSMC_BWTR2_ACCMOD_0 = 0x10000000
FSMC_BWTR2_ACCMOD_1 = 0x20000000
FSMC_BWTR3_ADDSET = 0xF
FSMC_BWTR3_ADDSET_0 = 0x1
FSMC_BWTR3_ADDSET_1 = 0x2
FSMC_BWTR3_ADDSET_2 = 0x4
FSMC_BWTR3_ADDSET_3 = 0x8
FSMC_BWTR3_ADDHLD = 0xF0
FSMC_BWTR3_ADDHLD_0 = 0x10
FSMC_BWTR3_ADDHLD_1 = 0x20
FSMC_BWTR3_ADDHLD_2 = 0x40
FSMC_BWTR3_ADDHLD_3 = 0x80
FSMC_BWTR3_DATAST = 0xFF00
FSMC_BWTR3_DATAST_0 = 0x100
FSMC_BWTR3_DATAST_1 = 0x200
FSMC_BWTR3_DATAST_2 = 0x400
FSMC_BWTR3_DATAST_3 = 0x800
FSMC_BWTR3_CLKDIV = 0xF00000
FSMC_BWTR3_CLKDIV_0 = 0x100000
FSMC_BWTR3_CLKDIV_1 = 0x200000
FSMC_BWTR3_CLKDIV_2 = 0x400000
FSMC_BWTR3_CLKDIV_3 = 0x800000
FSMC_BWTR3_DATLAT = 0xF000000
FSMC_BWTR3_DATLAT_0 = 0x1000000
FSMC_BWTR3_DATLAT_1 = 0x2000000
FSMC_BWTR3_DATLAT_2 = 0x4000000
FSMC_BWTR3_DATLAT_3 = 0x8000000
FSMC_BWTR3_ACCMOD = 0x30000000
FSMC_BWTR3_ACCMOD_0 = 0x10000000
FSMC_BWTR3_ACCMOD_1 = 0x20000000
FSMC_BWTR4_ADDSET = 0xF
FSMC_BWTR4_ADDSET_0 = 0x1
FSMC_BWTR4_ADDSET_1 = 0x2
FSMC_BWTR4_ADDSET_2 = 0x4
FSMC_BWTR4_ADDSET_3 = 0x8
FSMC_BWTR4_ADDHLD = 0xF0
FSMC_BWTR4_ADDHLD_0 = 0x10
FSMC_BWTR4_ADDHLD_1 = 0x20
FSMC_BWTR4_ADDHLD_2 = 0x40
FSMC_BWTR4_ADDHLD_3 = 0x80
FSMC_BWTR4_DATAST = 0xFF00
FSMC_BWTR4_DATAST_0 = 0x100
FSMC_BWTR4_DATAST_1 = 0x200
FSMC_BWTR4_DATAST_2 = 0x400
FSMC_BWTR4_DATAST_3 = 0x800
FSMC_BWTR4_CLKDIV = 0xF00000
FSMC_BWTR4_CLKDIV_0 = 0x100000
FSMC_BWTR4_CLKDIV_1 = 0x200000
FSMC_BWTR4_CLKDIV_2 = 0x400000
FSMC_BWTR4_CLKDIV_3 = 0x800000
FSMC_BWTR4_DATLAT = 0xF000000
FSMC_BWTR4_DATLAT_0 = 0x1000000
FSMC_BWTR4_DATLAT_1 = 0x2000000
FSMC_BWTR4_DATLAT_2 = 0x4000000
FSMC_BWTR4_DATLAT_3 = 0x8000000
FSMC_BWTR4_ACCMOD = 0x30000000
FSMC_BWTR4_ACCMOD_0 = 0x10000000
FSMC_BWTR4_ACCMOD_1 = 0x20000000
FSMC_PCR2_PWAITEN = 0x2
FSMC_PCR2_PBKEN = 0x4
FSMC_PCR2_PTYP = 0x8
FSMC_PCR2_PWID = 0x30
FSMC_PCR2_PWID_0 = 0x10
FSMC_PCR2_PWID_1 = 0x20
FSMC_PCR2_ECCEN = 0x40
FSMC_PCR2_TCLR = 0x1E00
FSMC_PCR2_TCLR_0 = 0x200
FSMC_PCR2_TCLR_1 = 0x400
FSMC_PCR2_TCLR_2 = 0x800
FSMC_PCR2_TCLR_3 = 0x1000
FSMC_PCR2_TAR = 0x1E000
FSMC_PCR2_TAR_0 = 0x2000
FSMC_PCR2_TAR_1 = 0x4000
FSMC_PCR2_TAR_2 = 0x8000
FSMC_PCR2_TAR_3 = 0x10000
FSMC_PCR2_ECCPS = 0xE0000
FSMC_PCR2_ECCPS_0 = 0x20000
FSMC_PCR2_ECCPS_1 = 0x40000
FSMC_PCR2_ECCPS_2 = 0x80000
FSMC_PCR3_PWAITEN = 0x2
FSMC_PCR3_PBKEN = 0x4
FSMC_PCR3_PTYP = 0x8
FSMC_PCR3_PWID = 0x30
FSMC_PCR3_PWID_0 = 0x10
FSMC_PCR3_PWID_1 = 0x20
FSMC_PCR3_ECCEN = 0x40
FSMC_PCR3_TCLR = 0x1E00
FSMC_PCR3_TCLR_0 = 0x200
FSMC_PCR3_TCLR_1 = 0x400
FSMC_PCR3_TCLR_2 = 0x800
FSMC_PCR3_TCLR_3 = 0x1000
FSMC_PCR3_TAR = 0x1E000
FSMC_PCR3_TAR_0 = 0x2000
FSMC_PCR3_TAR_1 = 0x4000
FSMC_PCR3_TAR_2 = 0x8000
FSMC_PCR3_TAR_3 = 0x10000
FSMC_PCR3_ECCPS = 0xE0000
FSMC_PCR3_ECCPS_0 = 0x20000
FSMC_PCR3_ECCPS_1 = 0x40000
FSMC_PCR3_ECCPS_2 = 0x80000
FSMC_PCR4_PWAITEN = 0x2
FSMC_PCR4_PBKEN = 0x4
FSMC_PCR4_PTYP = 0x8
FSMC_PCR4_PWID = 0x30
FSMC_PCR4_PWID_0 = 0x10
FSMC_PCR4_PWID_1 = 0x20
FSMC_PCR4_ECCEN = 0x40
FSMC_PCR4_TCLR = 0x1E00
FSMC_PCR4_TCLR_0 = 0x200
FSMC_PCR4_TCLR_1 = 0x400
FSMC_PCR4_TCLR_2 = 0x800
FSMC_PCR4_TCLR_3 = 0x1000
FSMC_PCR4_TAR = 0x1E000
FSMC_PCR4_TAR_0 = 0x2000
FSMC_PCR4_TAR_1 = 0x4000
FSMC_PCR4_TAR_2 = 0x8000
FSMC_PCR4_TAR_3 = 0x10000
FSMC_PCR4_ECCPS = 0xE0000
FSMC_PCR4_ECCPS_0 = 0x20000
FSMC_PCR4_ECCPS_1 = 0x40000
FSMC_PCR4_ECCPS_2 = 0x80000
FSMC_SR2_IRS = 0x1
FSMC_SR2_ILS = 0x2
FSMC_SR2_IFS = 0x4
FSMC_SR2_IREN = 0x8
FSMC_SR2_ILEN = 0x10
FSMC_SR2_IFEN = 0x20
FSMC_SR2_FEMPT = 0x40
FSMC_SR3_IRS = 0x1
FSMC_SR3_ILS = 0x2
FSMC_SR3_IFS = 0x4
FSMC_SR3_IREN = 0x8
FSMC_SR3_ILEN = 0x10
FSMC_SR3_IFEN = 0x20
FSMC_SR3_FEMPT = 0x40
FSMC_SR4_IRS = 0x1
FSMC_SR4_ILS = 0x2
FSMC_SR4_IFS = 0x4
FSMC_SR4_IREN = 0x8
FSMC_SR4_ILEN = 0x10
FSMC_SR4_IFEN = 0x20
FSMC_SR4_FEMPT = 0x40
FSMC_PMEM2_MEMSET2 = 0xFF
FSMC_PMEM2_MEMSET2_0 = 0x1
FSMC_PMEM2_MEMSET2_1 = 0x2
FSMC_PMEM2_MEMSET2_2 = 0x4
FSMC_PMEM2_MEMSET2_3 = 0x8
FSMC_PMEM2_MEMSET2_4 = 0x10
FSMC_PMEM2_MEMSET2_5 = 0x20
FSMC_PMEM2_MEMSET2_6 = 0x40
FSMC_PMEM2_MEMSET2_7 = 0x80
FSMC_PMEM2_MEMWAIT2 = 0xFF00
FSMC_PMEM2_MEMWAIT2_0 = 0x100
FSMC_PMEM2_MEMWAIT2_1 = 0x200
FSMC_PMEM2_MEMWAIT2_2 = 0x400
FSMC_PMEM2_MEMWAIT2_3 = 0x800
FSMC_PMEM2_MEMWAIT2_4 = 0x1000
FSMC_PMEM2_MEMWAIT2_5 = 0x2000
FSMC_PMEM2_MEMWAIT2_6 = 0x4000
FSMC_PMEM2_MEMWAIT2_7 = 0x8000
FSMC_PMEM2_MEMHOLD2 = 0xFF0000
FSMC_PMEM2_MEMHOLD2_0 = 0x10000
FSMC_PMEM2_MEMHOLD2_1 = 0x20000
FSMC_PMEM2_MEMHOLD2_2 = 0x40000
FSMC_PMEM2_MEMHOLD2_3 = 0x80000
FSMC_PMEM2_MEMHOLD2_4 = 0x100000
FSMC_PMEM2_MEMHOLD2_5 = 0x200000
FSMC_PMEM2_MEMHOLD2_6 = 0x400000
FSMC_PMEM2_MEMHOLD2_7 = 0x800000
FSMC_PMEM2_MEMHIZ2 = 0xFF000000
FSMC_PMEM2_MEMHIZ2_0 = 0x1000000
FSMC_PMEM2_MEMHIZ2_1 = 0x2000000
FSMC_PMEM2_MEMHIZ2_2 = 0x4000000
FSMC_PMEM2_MEMHIZ2_3 = 0x8000000
FSMC_PMEM2_MEMHIZ2_4 = 0x10000000
FSMC_PMEM2_MEMHIZ2_5 = 0x20000000
FSMC_PMEM2_MEMHIZ2_6 = 0x40000000
FSMC_PMEM2_MEMHIZ2_7 = 0x80000000
FSMC_PMEM3_MEMSET3 = 0xFF
FSMC_PMEM3_MEMSET3_0 = 0x1
FSMC_PMEM3_MEMSET3_1 = 0x2
FSMC_PMEM3_MEMSET3_2 = 0x4
FSMC_PMEM3_MEMSET3_3 = 0x8
FSMC_PMEM3_MEMSET3_4 = 0x10
FSMC_PMEM3_MEMSET3_5 = 0x20
FSMC_PMEM3_MEMSET3_6 = 0x40
FSMC_PMEM3_MEMSET3_7 = 0x80
FSMC_PMEM3_MEMWAIT3 = 0xFF00
FSMC_PMEM3_MEMWAIT3_0 = 0x100
FSMC_PMEM3_MEMWAIT3_1 = 0x200
FSMC_PMEM3_MEMWAIT3_2 = 0x400
FSMC_PMEM3_MEMWAIT3_3 = 0x800
FSMC_PMEM3_MEMWAIT3_4 = 0x1000
FSMC_PMEM3_MEMWAIT3_5 = 0x2000
FSMC_PMEM3_MEMWAIT3_6 = 0x4000
FSMC_PMEM3_MEMWAIT3_7 = 0x8000
FSMC_PMEM3_MEMHOLD3 = 0xFF0000
FSMC_PMEM3_MEMHOLD3_0 = 0x10000
FSMC_PMEM3_MEMHOLD3_1 = 0x20000
FSMC_PMEM3_MEMHOLD3_2 = 0x40000
FSMC_PMEM3_MEMHOLD3_3 = 0x80000
FSMC_PMEM3_MEMHOLD3_4 = 0x100000
FSMC_PMEM3_MEMHOLD3_5 = 0x200000
FSMC_PMEM3_MEMHOLD3_6 = 0x400000
FSMC_PMEM3_MEMHOLD3_7 = 0x800000
FSMC_PMEM3_MEMHIZ3 = 0xFF000000
FSMC_PMEM3_MEMHIZ3_0 = 0x1000000
FSMC_PMEM3_MEMHIZ3_1 = 0x2000000
FSMC_PMEM3_MEMHIZ3_2 = 0x4000000
FSMC_PMEM3_MEMHIZ3_3 = 0x8000000
FSMC_PMEM3_MEMHIZ3_4 = 0x10000000
FSMC_PMEM3_MEMHIZ3_5 = 0x20000000
FSMC_PMEM3_MEMHIZ3_6 = 0x40000000
FSMC_PMEM3_MEMHIZ3_7 = 0x80000000
FSMC_PMEM4_MEMSET4 = 0xFF
FSMC_PMEM4_MEMSET4_0 = 0x1
FSMC_PMEM4_MEMSET4_1 = 0x2
FSMC_PMEM4_MEMSET4_2 = 0x4
FSMC_PMEM4_MEMSET4_3 = 0x8
FSMC_PMEM4_MEMSET4_4 = 0x10
FSMC_PMEM4_MEMSET4_5 = 0x20
FSMC_PMEM4_MEMSET4_6 = 0x40
FSMC_PMEM4_MEMSET4_7 = 0x80
FSMC_PMEM4_MEMWAIT4 = 0xFF00
FSMC_PMEM4_MEMWAIT4_0 = 0x100
FSMC_PMEM4_MEMWAIT4_1 = 0x200
FSMC_PMEM4_MEMWAIT4_2 = 0x400
FSMC_PMEM4_MEMWAIT4_3 = 0x800
FSMC_PMEM4_MEMWAIT4_4 = 0x1000
FSMC_PMEM4_MEMWAIT4_5 = 0x2000
FSMC_PMEM4_MEMWAIT4_6 = 0x4000
FSMC_PMEM4_MEMWAIT4_7 = 0x8000
FSMC_PMEM4_MEMHOLD4 = 0xFF0000
FSMC_PMEM4_MEMHOLD4_0 = 0x10000
FSMC_PMEM4_MEMHOLD4_1 = 0x20000
FSMC_PMEM4_MEMHOLD4_2 = 0x40000
FSMC_PMEM4_MEMHOLD4_3 = 0x80000
FSMC_PMEM4_MEMHOLD4_4 = 0x100000
FSMC_PMEM4_MEMHOLD4_5 = 0x200000
FSMC_PMEM4_MEMHOLD4_6 = 0x400000
FSMC_PMEM4_MEMHOLD4_7 = 0x800000
FSMC_PMEM4_MEMHIZ4 = 0xFF000000
FSMC_PMEM4_MEMHIZ4_0 = 0x1000000
FSMC_PMEM4_MEMHIZ4_1 = 0x2000000
FSMC_PMEM4_MEMHIZ4_2 = 0x4000000
FSMC_PMEM4_MEMHIZ4_3 = 0x8000000
FSMC_PMEM4_MEMHIZ4_4 = 0x10000000
FSMC_PMEM4_MEMHIZ4_5 = 0x20000000
FSMC_PMEM4_MEMHIZ4_6 = 0x40000000
FSMC_PMEM4_MEMHIZ4_7 = 0x80000000
FSMC_PATT2_ATTSET2 = 0xFF
FSMC_PATT2_ATTSET2_0 = 0x1
FSMC_PATT2_ATTSET2_1 = 0x2
FSMC_PATT2_ATTSET2_2 = 0x4
FSMC_PATT2_ATTSET2_3 = 0x8
FSMC_PATT2_ATTSET2_4 = 0x10
FSMC_PATT2_ATTSET2_5 = 0x20
FSMC_PATT2_ATTSET2_6 = 0x40
FSMC_PATT2_ATTSET2_7 = 0x80
FSMC_PATT2_ATTWAIT2 = 0xFF00
FSMC_PATT2_ATTWAIT2_0 = 0x100
FSMC_PATT2_ATTWAIT2_1 = 0x200
FSMC_PATT2_ATTWAIT2_2 = 0x400
FSMC_PATT2_ATTWAIT2_3 = 0x800
FSMC_PATT2_ATTWAIT2_4 = 0x1000
FSMC_PATT2_ATTWAIT2_5 = 0x2000
FSMC_PATT2_ATTWAIT2_6 = 0x4000
FSMC_PATT2_ATTWAIT2_7 = 0x8000
FSMC_PATT2_ATTHOLD2 = 0xFF0000
FSMC_PATT2_ATTHOLD2_0 = 0x10000
FSMC_PATT2_ATTHOLD2_1 = 0x20000
FSMC_PATT2_ATTHOLD2_2 = 0x40000
FSMC_PATT2_ATTHOLD2_3 = 0x80000
FSMC_PATT2_ATTHOLD2_4 = 0x100000
FSMC_PATT2_ATTHOLD2_5 = 0x200000
FSMC_PATT2_ATTHOLD2_6 = 0x400000
FSMC_PATT2_ATTHOLD2_7 = 0x800000
FSMC_PATT2_ATTHIZ2 = 0xFF000000
FSMC_PATT2_ATTHIZ2_0 = 0x1000000
FSMC_PATT2_ATTHIZ2_1 = 0x2000000
FSMC_PATT2_ATTHIZ2_2 = 0x4000000
FSMC_PATT2_ATTHIZ2_3 = 0x8000000
FSMC_PATT2_ATTHIZ2_4 = 0x10000000
FSMC_PATT2_ATTHIZ2_5 = 0x20000000
FSMC_PATT2_ATTHIZ2_6 = 0x40000000
FSMC_PATT2_ATTHIZ2_7 = 0x80000000
FSMC_PATT3_ATTSET3 = 0xFF
FSMC_PATT3_ATTSET3_0 = 0x1
FSMC_PATT3_ATTSET3_1 = 0x2
FSMC_PATT3_ATTSET3_2 = 0x4
FSMC_PATT3_ATTSET3_3 = 0x8
FSMC_PATT3_ATTSET3_4 = 0x10
FSMC_PATT3_ATTSET3_5 = 0x20
FSMC_PATT3_ATTSET3_6 = 0x40
FSMC_PATT3_ATTSET3_7 = 0x80
FSMC_PATT3_ATTWAIT3 = 0xFF00
FSMC_PATT3_ATTWAIT3_0 = 0x100
FSMC_PATT3_ATTWAIT3_1 = 0x200
FSMC_PATT3_ATTWAIT3_2 = 0x400
FSMC_PATT3_ATTWAIT3_3 = 0x800
FSMC_PATT3_ATTWAIT3_4 = 0x1000
FSMC_PATT3_ATTWAIT3_5 = 0x2000
FSMC_PATT3_ATTWAIT3_6 = 0x4000
FSMC_PATT3_ATTWAIT3_7 = 0x8000
FSMC_PATT3_ATTHOLD3 = 0xFF0000
FSMC_PATT3_ATTHOLD3_0 = 0x10000
FSMC_PATT3_ATTHOLD3_1 = 0x20000
FSMC_PATT3_ATTHOLD3_2 = 0x40000
FSMC_PATT3_ATTHOLD3_3 = 0x80000
FSMC_PATT3_ATTHOLD3_4 = 0x100000
FSMC_PATT3_ATTHOLD3_5 = 0x200000
FSMC_PATT3_ATTHOLD3_6 = 0x400000
FSMC_PATT3_ATTHOLD3_7 = 0x800000
FSMC_PATT3_ATTHIZ3 = 0xFF000000
FSMC_PATT3_ATTHIZ3_0 = 0x1000000
FSMC_PATT3_ATTHIZ3_1 = 0x2000000
FSMC_PATT3_ATTHIZ3_2 = 0x4000000
FSMC_PATT3_ATTHIZ3_3 = 0x8000000
FSMC_PATT3_ATTHIZ3_4 = 0x10000000
FSMC_PATT3_ATTHIZ3_5 = 0x20000000
FSMC_PATT3_ATTHIZ3_6 = 0x40000000
FSMC_PATT3_ATTHIZ3_7 = 0x80000000
FSMC_PATT4_ATTSET4 = 0xFF
FSMC_PATT4_ATTSET4_0 = 0x1
FSMC_PATT4_ATTSET4_1 = 0x2
FSMC_PATT4_ATTSET4_2 = 0x4
FSMC_PATT4_ATTSET4_3 = 0x8
FSMC_PATT4_ATTSET4_4 = 0x10
FSMC_PATT4_ATTSET4_5 = 0x20
FSMC_PATT4_ATTSET4_6 = 0x40
FSMC_PATT4_ATTSET4_7 = 0x80
FSMC_PATT4_ATTWAIT4 = 0xFF00
FSMC_PATT4_ATTWAIT4_0 = 0x100
FSMC_PATT4_ATTWAIT4_1 = 0x200
FSMC_PATT4_ATTWAIT4_2 = 0x400
FSMC_PATT4_ATTWAIT4_3 = 0x800
FSMC_PATT4_ATTWAIT4_4 = 0x1000
FSMC_PATT4_ATTWAIT4_5 = 0x2000
FSMC_PATT4_ATTWAIT4_6 = 0x4000
FSMC_PATT4_ATTWAIT4_7 = 0x8000
FSMC_PATT4_ATTHOLD4 = 0xFF0000
FSMC_PATT4_ATTHOLD4_0 = 0x10000
FSMC_PATT4_ATTHOLD4_1 = 0x20000
FSMC_PATT4_ATTHOLD4_2 = 0x40000
FSMC_PATT4_ATTHOLD4_3 = 0x80000
FSMC_PATT4_ATTHOLD4_4 = 0x100000
FSMC_PATT4_ATTHOLD4_5 = 0x200000
FSMC_PATT4_ATTHOLD4_6 = 0x400000
FSMC_PATT4_ATTHOLD4_7 = 0x800000
FSMC_PATT4_ATTHIZ4 = 0xFF000000
FSMC_PATT4_ATTHIZ4_0 = 0x1000000
FSMC_PATT4_ATTHIZ4_1 = 0x2000000
FSMC_PATT4_ATTHIZ4_2 = 0x4000000
FSMC_PATT4_ATTHIZ4_3 = 0x8000000
FSMC_PATT4_ATTHIZ4_4 = 0x10000000
FSMC_PATT4_ATTHIZ4_5 = 0x20000000
FSMC_PATT4_ATTHIZ4_6 = 0x40000000
FSMC_PATT4_ATTHIZ4_7 = 0x80000000
FSMC_PIO4_IOSET4 = 0xFF
FSMC_PIO4_IOSET4_0 = 0x1
FSMC_PIO4_IOSET4_1 = 0x2
FSMC_PIO4_IOSET4_2 = 0x4
FSMC_PIO4_IOSET4_3 = 0x8
FSMC_PIO4_IOSET4_4 = 0x10
FSMC_PIO4_IOSET4_5 = 0x20
FSMC_PIO4_IOSET4_6 = 0x40
FSMC_PIO4_IOSET4_7 = 0x80
FSMC_PIO4_IOWAIT4 = 0xFF00
FSMC_PIO4_IOWAIT4_0 = 0x100
FSMC_PIO4_IOWAIT4_1 = 0x200
FSMC_PIO4_IOWAIT4_2 = 0x400
FSMC_PIO4_IOWAIT4_3 = 0x800
FSMC_PIO4_IOWAIT4_4 = 0x1000
FSMC_PIO4_IOWAIT4_5 = 0x2000
FSMC_PIO4_IOWAIT4_6 = 0x4000
FSMC_PIO4_IOWAIT4_7 = 0x8000
FSMC_PIO4_IOHOLD4 = 0xFF0000
FSMC_PIO4_IOHOLD4_0 = 0x10000
FSMC_PIO4_IOHOLD4_1 = 0x20000
FSMC_PIO4_IOHOLD4_2 = 0x40000
FSMC_PIO4_IOHOLD4_3 = 0x80000
FSMC_PIO4_IOHOLD4_4 = 0x100000
FSMC_PIO4_IOHOLD4_5 = 0x200000
FSMC_PIO4_IOHOLD4_6 = 0x400000
FSMC_PIO4_IOHOLD4_7 = 0x800000
FSMC_PIO4_IOHIZ4 = 0xFF000000
FSMC_PIO4_IOHIZ4_0 = 0x1000000
FSMC_PIO4_IOHIZ4_1 = 0x2000000
FSMC_PIO4_IOHIZ4_2 = 0x4000000
FSMC_PIO4_IOHIZ4_3 = 0x8000000
FSMC_PIO4_IOHIZ4_4 = 0x10000000
FSMC_PIO4_IOHIZ4_5 = 0x20000000
FSMC_PIO4_IOHIZ4_6 = 0x40000000
FSMC_PIO4_IOHIZ4_7 = 0x80000000
FSMC_ECCR2_ECC2 = 0xFFFFFFFF
FSMC_ECCR3_ECC3 = 0xFFFFFFFF
SDIO_POWER_PWRCTRL = 0x3
SDIO_POWER_PWRCTRL_0 = 0x1
SDIO_POWER_PWRCTRL_1 = 0x2
SDIO_CLKCR_CLKDIV = 0xFF
SDIO_CLKCR_CLKEN = 0x100
SDIO_CLKCR_PWRSAV = 0x200
SDIO_CLKCR_BYPASS = 0x400
SDIO_CLKCR_WIDBUS = 0x1800
SDIO_CLKCR_WIDBUS_0 = 0x800
SDIO_CLKCR_WIDBUS_1 = 0x1000
SDIO_CLKCR_NEGEDGE = 0x2000
SDIO_CLKCR_HWFC_EN = 0x4000
SDIO_ARG_CMDARG = 0xFFFFFFFF
SDIO_CMD_CMDINDEX = 0x3F
SDIO_CMD_WAITRESP = 0xC0
SDIO_CMD_WAITRESP_0 = 0x40
SDIO_CMD_WAITRESP_1 = 0x80
SDIO_CMD_WAITINT = 0x100
SDIO_CMD_WAITPEND = 0x200
SDIO_CMD_CPSMEN = 0x400
SDIO_CMD_SDIOSUSPEND = 0x800
SDIO_CMD_ENCMDCOMPL = 0x1000
SDIO_CMD_NIEN = 0x2000
SDIO_CMD_CEATACMD = 0x4000
SDIO_RESPCMD_RESPCMD = 0x3F
SDIO_RESP0_CARDSTATUS0 = 0xFFFFFFFF
SDIO_RESP1_CARDSTATUS1 = 0xFFFFFFFF
SDIO_RESP2_CARDSTATUS2 = 0xFFFFFFFF
SDIO_RESP3_CARDSTATUS3 = 0xFFFFFFFF
SDIO_RESP4_CARDSTATUS4 = 0xFFFFFFFF
SDIO_DTIMER_DATATIME = 0xFFFFFFFF
SDIO_DLEN_DATALENGTH = 0x1FFFFFF
SDIO_DCTRL_DTEN = 0x1
SDIO_DCTRL_DTDIR = 0x2
SDIO_DCTRL_DTMODE = 0x4
SDIO_DCTRL_DMAEN = 0x8
SDIO_DCTRL_DBLOCKSIZE = 0xF0
SDIO_DCTRL_DBLOCKSIZE_0 = 0x10
SDIO_DCTRL_DBLOCKSIZE_1 = 0x20
SDIO_DCTRL_DBLOCKSIZE_2 = 0x40
SDIO_DCTRL_DBLOCKSIZE_3 = 0x80
SDIO_DCTRL_RWSTART = 0x100
SDIO_DCTRL_RWSTOP = 0x200
SDIO_DCTRL_RWMOD = 0x400
SDIO_DCTRL_SDIOEN = 0x800
SDIO_DCOUNT_DATACOUNT = 0x1FFFFFF
SDIO_STA_CCRCFAIL = 0x1
SDIO_STA_DCRCFAIL = 0x2
SDIO_STA_CTIMEOUT = 0x4
SDIO_STA_DTIMEOUT = 0x8
SDIO_STA_TXUNDERR = 0x10
SDIO_STA_RXOVERR = 0x20
SDIO_STA_CMDREND = 0x40
SDIO_STA_CMDSENT = 0x80
SDIO_STA_DATAEND = 0x100
SDIO_STA_STBITERR = 0x200
SDIO_STA_DBCKEND = 0x400
SDIO_STA_CMDACT = 0x800
SDIO_STA_TXACT = 0x1000
SDIO_STA_RXACT = 0x2000
SDIO_STA_TXFIFOHE = 0x4000
SDIO_STA_RXFIFOHF = 0x8000
SDIO_STA_TXFIFOF = 0x10000
SDIO_STA_RXFIFOF = 0x20000
SDIO_STA_TXFIFOE = 0x40000
SDIO_STA_RXFIFOE = 0x80000
SDIO_STA_TXDAVL = 0x100000
SDIO_STA_RXDAVL = 0x200000
SDIO_STA_SDIOIT = 0x400000
SDIO_STA_CEATAEND = 0x800000
SDIO_ICR_CCRCFAILC = 0x1
SDIO_ICR_DCRCFAILC = 0x2
SDIO_ICR_CTIMEOUTC = 0x4
SDIO_ICR_DTIMEOUTC = 0x8
SDIO_ICR_TXUNDERRC = 0x10
SDIO_ICR_RXOVERRC = 0x20
SDIO_ICR_CMDRENDC = 0x40
SDIO_ICR_CMDSENTC = 0x80
SDIO_ICR_DATAENDC = 0x100
SDIO_ICR_STBITERRC = 0x200
SDIO_ICR_DBCKENDC = 0x400
SDIO_ICR_SDIOITC = 0x400000
SDIO_ICR_CEATAENDC = 0x800000
SDIO_MASK_CCRCFAILIE = 0x1
SDIO_MASK_DCRCFAILIE = 0x2
SDIO_MASK_CTIMEOUTIE = 0x4
SDIO_MASK_DTIMEOUTIE = 0x8
SDIO_MASK_TXUNDERRIE = 0x10
SDIO_MASK_RXOVERRIE = 0x20
SDIO_MASK_CMDRENDIE = 0x40
SDIO_MASK_CMDSENTIE = 0x80
SDIO_MASK_DATAENDIE = 0x100
SDIO_MASK_STBITERRIE = 0x200
SDIO_MASK_DBCKENDIE = 0x400
SDIO_MASK_CMDACTIE = 0x800
SDIO_MASK_TXACTIE = 0x1000
SDIO_MASK_RXACTIE = 0x2000
SDIO_MASK_TXFIFOHEIE = 0x4000
SDIO_MASK_RXFIFOHFIE = 0x8000
SDIO_MASK_TXFIFOFIE = 0x10000
SDIO_MASK_RXFIFOFIE = 0x20000
SDIO_MASK_TXFIFOEIE = 0x40000
SDIO_MASK_RXFIFOEIE = 0x80000
SDIO_MASK_TXDAVLIE = 0x100000
SDIO_MASK_RXDAVLIE = 0x200000
SDIO_MASK_SDIOITIE = 0x400000
SDIO_MASK_CEATAENDIE = 0x800000
SDIO_FIFOCNT_FIFOCOUNT = 0xFFFFFF
SDIO_FIFO_FIFODATA = 0xFFFFFFFF
USB_EP0R_EA = 0xF
USB_EP0R_STAT_TX = 0x30
USB_EP0R_STAT_TX_0 = 0x10
USB_EP0R_STAT_TX_1 = 0x20
USB_EP0R_DTOG_TX = 0x40
USB_EP0R_CTR_TX = 0x80
USB_EP0R_EP_KIND = 0x100
USB_EP0R_EP_TYPE = 0x600
USB_EP0R_EP_TYPE_0 = 0x200
USB_EP0R_EP_TYPE_1 = 0x400
USB_EP0R_SETUP = 0x800
USB_EP0R_STAT_RX = 0x3000
USB_EP0R_STAT_RX_0 = 0x1000
USB_EP0R_STAT_RX_1 = 0x2000
USB_EP0R_DTOG_RX = 0x4000
USB_EP0R_CTR_RX = 0x8000
USB_EP1R_EA = 0xF
USB_EP1R_STAT_TX = 0x30
USB_EP1R_STAT_TX_0 = 0x10
USB_EP1R_STAT_TX_1 = 0x20
USB_EP1R_DTOG_TX = 0x40
USB_EP1R_CTR_TX = 0x80
USB_EP1R_EP_KIND = 0x100
USB_EP1R_EP_TYPE = 0x600
USB_EP1R_EP_TYPE_0 = 0x200
USB_EP1R_EP_TYPE_1 = 0x400
USB_EP1R_SETUP = 0x800
USB_EP1R_STAT_RX = 0x3000
USB_EP1R_STAT_RX_0 = 0x1000
USB_EP1R_STAT_RX_1 = 0x2000
USB_EP1R_DTOG_RX = 0x4000
USB_EP1R_CTR_RX = 0x8000
USB_EP2R_EA = 0xF
USB_EP2R_STAT_TX = 0x30
USB_EP2R_STAT_TX_0 = 0x10
USB_EP2R_STAT_TX_1 = 0x20
USB_EP2R_DTOG_TX = 0x40
USB_EP2R_CTR_TX = 0x80
USB_EP2R_EP_KIND = 0x100
USB_EP2R_EP_TYPE = 0x600
USB_EP2R_EP_TYPE_0 = 0x200
USB_EP2R_EP_TYPE_1 = 0x400
USB_EP2R_SETUP = 0x800
USB_EP2R_STAT_RX = 0x3000
USB_EP2R_STAT_RX_0 = 0x1000
USB_EP2R_STAT_RX_1 = 0x2000
USB_EP2R_DTOG_RX = 0x4000
USB_EP2R_CTR_RX = 0x8000
USB_EP3R_EA = 0xF
USB_EP3R_STAT_TX = 0x30
USB_EP3R_STAT_TX_0 = 0x10
USB_EP3R_STAT_TX_1 = 0x20
USB_EP3R_DTOG_TX = 0x40
USB_EP3R_CTR_TX = 0x80
USB_EP3R_EP_KIND = 0x100
USB_EP3R_EP_TYPE = 0x600
USB_EP3R_EP_TYPE_0 = 0x200
USB_EP3R_EP_TYPE_1 = 0x400
USB_EP3R_SETUP = 0x800
USB_EP3R_STAT_RX = 0x3000
USB_EP3R_STAT_RX_0 = 0x1000
USB_EP3R_STAT_RX_1 = 0x2000
USB_EP3R_DTOG_RX = 0x4000
USB_EP3R_CTR_RX = 0x8000
USB_EP4R_EA = 0xF
USB_EP4R_STAT_TX = 0x30
USB_EP4R_STAT_TX_0 = 0x10
USB_EP4R_STAT_TX_1 = 0x20
USB_EP4R_DTOG_TX = 0x40
USB_EP4R_CTR_TX = 0x80
USB_EP4R_EP_KIND = 0x100
USB_EP4R_EP_TYPE = 0x600
USB_EP4R_EP_TYPE_0 = 0x200
USB_EP4R_EP_TYPE_1 = 0x400
USB_EP4R_SETUP = 0x800
USB_EP4R_STAT_RX = 0x3000
USB_EP4R_STAT_RX_0 = 0x1000
USB_EP4R_STAT_RX_1 = 0x2000
USB_EP4R_DTOG_RX = 0x4000
USB_EP4R_CTR_RX = 0x8000
USB_EP5R_EA = 0xF
USB_EP5R_STAT_TX = 0x30
USB_EP5R_STAT_TX_0 = 0x10
USB_EP5R_STAT_TX_1 = 0x20
USB_EP5R_DTOG_TX = 0x40
USB_EP5R_CTR_TX = 0x80
USB_EP5R_EP_KIND = 0x100
USB_EP5R_EP_TYPE = 0x600
USB_EP5R_EP_TYPE_0 = 0x200
USB_EP5R_EP_TYPE_1 = 0x400
USB_EP5R_SETUP = 0x800
USB_EP5R_STAT_RX = 0x3000
USB_EP5R_STAT_RX_0 = 0x1000
USB_EP5R_STAT_RX_1 = 0x2000
USB_EP5R_DTOG_RX = 0x4000
USB_EP5R_CTR_RX = 0x8000
USB_EP6R_EA = 0xF
USB_EP6R_STAT_TX = 0x30
USB_EP6R_STAT_TX_0 = 0x10
USB_EP6R_STAT_TX_1 = 0x20
USB_EP6R_DTOG_TX = 0x40
USB_EP6R_CTR_TX = 0x80
USB_EP6R_EP_KIND = 0x100
USB_EP6R_EP_TYPE = 0x600
USB_EP6R_EP_TYPE_0 = 0x200
USB_EP6R_EP_TYPE_1 = 0x400
USB_EP6R_SETUP = 0x800
USB_EP6R_STAT_RX = 0x3000
USB_EP6R_STAT_RX_0 = 0x1000
USB_EP6R_STAT_RX_1 = 0x2000
USB_EP6R_DTOG_RX = 0x4000
USB_EP6R_CTR_RX = 0x8000
USB_EP7R_EA = 0xF
USB_EP7R_STAT_TX = 0x30
USB_EP7R_STAT_TX_0 = 0x10
USB_EP7R_STAT_TX_1 = 0x20
USB_EP7R_DTOG_TX = 0x40
USB_EP7R_CTR_TX = 0x80
USB_EP7R_EP_KIND = 0x100
USB_EP7R_EP_TYPE = 0x600
USB_EP7R_EP_TYPE_0 = 0x200
USB_EP7R_EP_TYPE_1 = 0x400
USB_EP7R_SETUP = 0x800
USB_EP7R_STAT_RX = 0x3000
USB_EP7R_STAT_RX_0 = 0x1000
USB_EP7R_STAT_RX_1 = 0x2000
USB_EP7R_DTOG_RX = 0x4000
USB_EP7R_CTR_RX = 0x8000
USB_CNTR_FRES = 0x1
USB_CNTR_PDWN = 0x2
USB_CNTR_LP_MODE = 0x4
USB_CNTR_FSUSP = 0x8
USB_CNTR_RESUME = 0x10
USB_CNTR_ESOFM = 0x100
USB_CNTR_SOFM = 0x200
USB_CNTR_RESETM = 0x400
USB_CNTR_SUSPM = 0x800
USB_CNTR_WKUPM = 0x1000
USB_CNTR_ERRM = 0x2000
USB_CNTR_PMAOVRM = 0x4000
USB_CNTR_CTRM = 0x8000
USB_ISTR_EP_ID = 0xF
USB_ISTR_DIR = 0x10
USB_ISTR_ESOF = 0x100
USB_ISTR_SOF = 0x200
USB_ISTR_RESET = 0x400
USB_ISTR_SUSP = 0x800
USB_ISTR_WKUP = 0x1000
USB_ISTR_ERR = 0x2000
USB_ISTR_PMAOVR = 0x4000
USB_ISTR_CTR = 0x8000
USB_FNR_FN = 0x7FF
USB_FNR_LSOF = 0x1800
USB_FNR_LCK = 0x2000
USB_FNR_RXDM = 0x4000
USB_FNR_RXDP = 0x8000
USB_DADDR_ADD = 0x7F
USB_DADDR_ADD0 = 0x1
USB_DADDR_ADD1 = 0x2
USB_DADDR_ADD2 = 0x4
USB_DADDR_ADD3 = 0x8
USB_DADDR_ADD4 = 0x10
USB_DADDR_ADD5 = 0x20
USB_DADDR_ADD6 = 0x40
USB_DADDR_EF = 0x80
USB_BTABLE_BTABLE = 0xFFF8
USB_ADDR0_TX_ADDR0_TX = 0xFFFE
USB_ADDR1_TX_ADDR1_TX = 0xFFFE
USB_ADDR2_TX_ADDR2_TX = 0xFFFE
USB_ADDR3_TX_ADDR3_TX = 0xFFFE
USB_ADDR4_TX_ADDR4_TX = 0xFFFE
USB_ADDR5_TX_ADDR5_TX = 0xFFFE
USB_ADDR6_TX_ADDR6_TX = 0xFFFE
USB_ADDR7_TX_ADDR7_TX = 0xFFFE
USB_COUNT0_TX_COUNT0_TX = 0x3FF
USB_COUNT1_TX_COUNT1_TX = 0x3FF
USB_COUNT2_TX_COUNT2_TX = 0x3FF
USB_COUNT3_TX_COUNT3_TX = 0x3FF
USB_COUNT4_TX_COUNT4_TX = 0x3FF
USB_COUNT5_TX_COUNT5_TX = 0x3FF
USB_COUNT6_TX_COUNT6_TX = 0x3FF
USB_COUNT7_TX_COUNT7_TX = 0x3FF
USB_COUNT0_TX_0_COUNT0_TX_0 = 0x3FF
USB_COUNT0_TX_1_COUNT0_TX_1 = 0x3FF0000
USB_COUNT1_TX_0_COUNT1_TX_0 = 0x3FF
USB_COUNT1_TX_1_COUNT1_TX_1 = 0x3FF0000
USB_COUNT2_TX_0_COUNT2_TX_0 = 0x3FF
USB_COUNT2_TX_1_COUNT2_TX_1 = 0x3FF0000
USB_COUNT3_TX_0_COUNT3_TX_0 = 0x3FF
USB_COUNT3_TX_1_COUNT3_TX_1 = 0x0
USB_COUNT4_TX_0_COUNT4_TX_0 = 0x3FF
USB_COUNT4_TX_1_COUNT4_TX_1 = 0x3FF0000
USB_COUNT5_TX_0_COUNT5_TX_0 = 0x3FF
USB_COUNT5_TX_1_COUNT5_TX_1 = 0x3FF0000
USB_COUNT6_TX_0_COUNT6_TX_0 = 0x3FF
USB_COUNT6_TX_1_COUNT6_TX_1 = 0x3FF0000
USB_COUNT7_TX_0_COUNT7_TX_0 = 0x3FF
USB_COUNT7_TX_1_COUNT7_TX_1 = 0x3FF0000
USB_ADDR0_RX_ADDR0_RX = 0xFFFE
USB_ADDR1_RX_ADDR1_RX = 0xFFFE
USB_ADDR2_RX_ADDR2_RX = 0xFFFE
USB_ADDR3_RX_ADDR3_RX = 0xFFFE
USB_ADDR4_RX_ADDR4_RX = 0xFFFE
USB_ADDR5_RX_ADDR5_RX = 0xFFFE
USB_ADDR6_RX_ADDR6_RX = 0xFFFE
USB_ADDR7_RX_ADDR7_RX = 0xFFFE
USB_COUNT0_RX_COUNT0_RX = 0x3FF
USB_COUNT0_RX_NUM_BLOCK = 0x7C00
USB_COUNT0_RX_NUM_BLOCK_0 = 0x400
USB_COUNT0_RX_NUM_BLOCK_1 = 0x800
USB_COUNT0_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT0_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT0_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT0_RX_BLSIZE = 0x8000
USB_COUNT1_RX_COUNT1_RX = 0x3FF
USB_COUNT1_RX_NUM_BLOCK = 0x7C00
USB_COUNT1_RX_NUM_BLOCK_0 = 0x400
USB_COUNT1_RX_NUM_BLOCK_1 = 0x800
USB_COUNT1_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT1_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT1_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT1_RX_BLSIZE = 0x8000
USB_COUNT2_RX_COUNT2_RX = 0x3FF
USB_COUNT2_RX_NUM_BLOCK = 0x7C00
USB_COUNT2_RX_NUM_BLOCK_0 = 0x400
USB_COUNT2_RX_NUM_BLOCK_1 = 0x800
USB_COUNT2_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT2_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT2_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT2_RX_BLSIZE = 0x8000
USB_COUNT3_RX_COUNT3_RX = 0x3FF
USB_COUNT3_RX_NUM_BLOCK = 0x7C00
USB_COUNT3_RX_NUM_BLOCK_0 = 0x400
USB_COUNT3_RX_NUM_BLOCK_1 = 0x800
USB_COUNT3_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT3_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT3_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT3_RX_BLSIZE = 0x8000
USB_COUNT4_RX_COUNT4_RX = 0x3FF
USB_COUNT4_RX_NUM_BLOCK = 0x7C00
USB_COUNT4_RX_NUM_BLOCK_0 = 0x400
USB_COUNT4_RX_NUM_BLOCK_1 = 0x800
USB_COUNT4_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT4_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT4_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT4_RX_BLSIZE = 0x8000
USB_COUNT5_RX_COUNT5_RX = 0x3FF
USB_COUNT5_RX_NUM_BLOCK = 0x7C00
USB_COUNT5_RX_NUM_BLOCK_0 = 0x400
USB_COUNT5_RX_NUM_BLOCK_1 = 0x800
USB_COUNT5_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT5_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT5_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT5_RX_BLSIZE = 0x8000
USB_COUNT6_RX_COUNT6_RX = 0x3FF
USB_COUNT6_RX_NUM_BLOCK = 0x7C00
USB_COUNT6_RX_NUM_BLOCK_0 = 0x400
USB_COUNT6_RX_NUM_BLOCK_1 = 0x800
USB_COUNT6_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT6_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT6_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT6_RX_BLSIZE = 0x8000
USB_COUNT7_RX_COUNT7_RX = 0x3FF
USB_COUNT7_RX_NUM_BLOCK = 0x7C00
USB_COUNT7_RX_NUM_BLOCK_0 = 0x400
USB_COUNT7_RX_NUM_BLOCK_1 = 0x800
USB_COUNT7_RX_NUM_BLOCK_2 = 0x1000
USB_COUNT7_RX_NUM_BLOCK_3 = 0x2000
USB_COUNT7_RX_NUM_BLOCK_4 = 0x4000
USB_COUNT7_RX_BLSIZE = 0x8000
USB_COUNT0_RX_0_COUNT0_RX_0 = 0x3FF
USB_COUNT0_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT0_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT0_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT0_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT0_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT0_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT0_RX_0_BLSIZE_0 = 0x8000
USB_COUNT0_RX_1_COUNT0_RX_1 = 0x3FF0000
USB_COUNT0_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT0_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT0_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT0_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT0_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT0_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT0_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT1_RX_0_COUNT1_RX_0 = 0x3FF
USB_COUNT1_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT1_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT1_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT1_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT1_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT1_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT1_RX_0_BLSIZE_0 = 0x8000
USB_COUNT1_RX_1_COUNT1_RX_1 = 0x3FF0000
USB_COUNT1_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT1_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT1_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT1_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT1_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT1_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT1_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT2_RX_0_COUNT2_RX_0 = 0x3FF
USB_COUNT2_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT2_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT2_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT2_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT2_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT2_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT2_RX_0_BLSIZE_0 = 0x8000
USB_COUNT2_RX_1_COUNT2_RX_1 = 0x3FF0000
USB_COUNT2_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT2_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT2_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT2_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT2_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT2_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT2_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT3_RX_0_COUNT3_RX_0 = 0x3FF
USB_COUNT3_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT3_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT3_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT3_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT3_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT3_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT3_RX_0_BLSIZE_0 = 0x8000
USB_COUNT3_RX_1_COUNT3_RX_1 = 0x3FF0000
USB_COUNT3_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT3_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT3_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT3_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT3_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT3_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT3_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT4_RX_0_COUNT4_RX_0 = 0x3FF
USB_COUNT4_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT4_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT4_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT4_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT4_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT4_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT4_RX_0_BLSIZE_0 = 0x8000
USB_COUNT4_RX_1_COUNT4_RX_1 = 0x3FF0000
USB_COUNT4_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT4_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT4_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT4_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT4_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT4_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT4_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT5_RX_0_COUNT5_RX_0 = 0x3FF
USB_COUNT5_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT5_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT5_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT5_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT5_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT5_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT5_RX_0_BLSIZE_0 = 0x8000
USB_COUNT5_RX_1_COUNT5_RX_1 = 0x3FF0000
USB_COUNT5_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT5_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT5_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT5_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT5_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT5_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT5_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT6_RX_0_COUNT6_RX_0 = 0x3FF
USB_COUNT6_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT6_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT6_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT6_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT6_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT6_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT6_RX_0_BLSIZE_0 = 0x8000
USB_COUNT6_RX_1_COUNT6_RX_1 = 0x3FF0000
USB_COUNT6_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT6_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT6_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT6_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT6_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT6_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT6_RX_1_BLSIZE_1 = 0x80000000
USB_COUNT7_RX_0_COUNT7_RX_0 = 0x3FF
USB_COUNT7_RX_0_NUM_BLOCK_0 = 0x7C00
USB_COUNT7_RX_0_NUM_BLOCK_0_0 = 0x400
USB_COUNT7_RX_0_NUM_BLOCK_0_1 = 0x800
USB_COUNT7_RX_0_NUM_BLOCK_0_2 = 0x1000
USB_COUNT7_RX_0_NUM_BLOCK_0_3 = 0x2000
USB_COUNT7_RX_0_NUM_BLOCK_0_4 = 0x4000
USB_COUNT7_RX_0_BLSIZE_0 = 0x8000
USB_COUNT7_RX_1_COUNT7_RX_1 = 0x3FF0000
USB_COUNT7_RX_1_NUM_BLOCK_1 = 0x7C000000
USB_COUNT7_RX_1_NUM_BLOCK_1_0 = 0x4000000
USB_COUNT7_RX_1_NUM_BLOCK_1_1 = 0x8000000
USB_COUNT7_RX_1_NUM_BLOCK_1_2 = 0x10000000
USB_COUNT7_RX_1_NUM_BLOCK_1_3 = 0x20000000
USB_COUNT7_RX_1_NUM_BLOCK_1_4 = 0x40000000
USB_COUNT7_RX_1_BLSIZE_1 = 0x80000000
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
SPI_CR1_DFF = 0x800
SPI_CR1_CRCNEXT = 0x1000
SPI_CR1_CRCEN = 0x2000
SPI_CR1_BIDIOE = 0x4000
SPI_CR1_BIDIMODE = 0x8000
SPI_CR2_RXDMAEN = 0x1
SPI_CR2_TXDMAEN = 0x2
SPI_CR2_SSOE = 0x4
SPI_CR2_ERRIE = 0x20
SPI_CR2_RXNEIE = 0x40
SPI_CR2_TXEIE = 0x80
SPI_SR_RXNE = 0x1
SPI_SR_TXE = 0x2
SPI_SR_CHSIDE = 0x4
SPI_SR_UDR = 0x8
SPI_SR_CRCERR = 0x10
SPI_SR_MODF = 0x20
SPI_SR_OVR = 0x40
SPI_SR_BSY = 0x80
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
I2C_CR1_PE = 0x1
I2C_CR1_SMBUS = 0x2
I2C_CR1_SMBTYPE = 0x8
I2C_CR1_ENARP = 0x10
I2C_CR1_ENPEC = 0x20
I2C_CR1_ENGC = 0x40
I2C_CR1_NOSTRETCH = 0x80
I2C_CR1_START = 0x100
I2C_CR1_STOP = 0x200
I2C_CR1_ACK = 0x400
I2C_CR1_POS = 0x800
I2C_CR1_PEC = 0x1000
I2C_CR1_ALERT = 0x2000
I2C_CR1_SWRST = 0x8000
I2C_CR2_FREQ = 0x3F
I2C_CR2_FREQ_0 = 0x1
I2C_CR2_FREQ_1 = 0x2
I2C_CR2_FREQ_2 = 0x4
I2C_CR2_FREQ_3 = 0x8
I2C_CR2_FREQ_4 = 0x10
I2C_CR2_FREQ_5 = 0x20
I2C_CR2_ITERREN = 0x100
I2C_CR2_ITEVTEN = 0x200
I2C_CR2_ITBUFEN = 0x400
I2C_CR2_DMAEN = 0x800
I2C_CR2_LAST = 0x1000
I2C_OAR1_ADD1_7 = 0xFE
I2C_OAR1_ADD8_9 = 0x300
I2C_OAR1_ADD0 = 0x1
I2C_OAR1_ADD1 = 0x2
I2C_OAR1_ADD2 = 0x4
I2C_OAR1_ADD3 = 0x8
I2C_OAR1_ADD4 = 0x10
I2C_OAR1_ADD5 = 0x20
I2C_OAR1_ADD6 = 0x40
I2C_OAR1_ADD7 = 0x80
I2C_OAR1_ADD8 = 0x100
I2C_OAR1_ADD9 = 0x200
I2C_OAR1_ADDMODE = 0x8000
I2C_OAR2_ENDUAL = 0x1
I2C_OAR2_ADD2 = 0xFE
I2C_DR_DR = 0xFF
I2C_SR1_SB = 0x1
I2C_SR1_ADDR = 0x2
I2C_SR1_BTF = 0x4
I2C_SR1_ADD10 = 0x8
I2C_SR1_STOPF = 0x10
I2C_SR1_RXNE = 0x40
I2C_SR1_TXE = 0x80
I2C_SR1_BERR = 0x100
I2C_SR1_ARLO = 0x200
I2C_SR1_AF = 0x400
I2C_SR1_OVR = 0x800
I2C_SR1_PECERR = 0x1000
I2C_SR1_TIMEOUT = 0x4000
I2C_SR1_SMBALERT = 0x8000
I2C_SR2_MSL = 0x1
I2C_SR2_BUSY = 0x2
I2C_SR2_TRA = 0x4
I2C_SR2_GENCALL = 0x10
I2C_SR2_SMBDEFAULT = 0x20
I2C_SR2_SMBHOST = 0x40
I2C_SR2_DUALF = 0x80
I2C_SR2_PEC = 0xFF00
I2C_CCR_CCR = 0xFFF
I2C_CCR_DUTY = 0x4000
I2C_CCR_FS = 0x8000
I2C_TRISE_TRISE = 0x3F
USART_SR_PE = 0x1
USART_SR_FE = 0x2
USART_SR_NE = 0x4
USART_SR_ORE = 0x8
USART_SR_IDLE = 0x10
USART_SR_RXNE = 0x20
USART_SR_TC = 0x40
USART_SR_TXE = 0x80
USART_SR_LBD = 0x100
USART_SR_CTS = 0x200
USART_DR_DR = 0x1FF
USART_BRR_DIV_Fraction = 0xF
USART_BRR_DIV_Mantissa = 0xFFF0
USART_CR1_SBK = 0x1
USART_CR1_RWU = 0x2
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
USART_CR1_UE = 0x2000
USART_CR1_OVER8 = 0x8000
USART_CR2_ADD = 0xF
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
USART_GTPR_PSC = 0xFF
USART_GTPR_PSC_0 = 0x1
USART_GTPR_PSC_1 = 0x2
USART_GTPR_PSC_2 = 0x4
USART_GTPR_PSC_3 = 0x8
USART_GTPR_PSC_4 = 0x10
USART_GTPR_PSC_5 = 0x20
USART_GTPR_PSC_6 = 0x40
USART_GTPR_PSC_7 = 0x80
USART_GTPR_GT = 0xFF00
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
DBGMCU_CR_DBG_SLEEP = 0x1
DBGMCU_CR_DBG_STOP = 0x2
DBGMCU_CR_DBG_STANDBY = 0x4
DBGMCU_CR_TRACE_IOEN = 0x20
DBGMCU_CR_TRACE_MODE = 0xC0
DBGMCU_CR_TRACE_MODE_0 = 0x40
DBGMCU_CR_TRACE_MODE_1 = 0x80
DBGMCU_CR_DBG_IWDG_STOP = 0x100
DBGMCU_CR_DBG_WWDG_STOP = 0x200
DBGMCU_CR_DBG_TIM1_STOP = 0x400
DBGMCU_CR_DBG_TIM2_STOP = 0x800
DBGMCU_CR_DBG_TIM3_STOP = 0x1000
DBGMCU_CR_DBG_TIM4_STOP = 0x2000
DBGMCU_CR_DBG_CAN1_STOP = 0x4000
DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT = 0x8000
DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT = 0x10000
DBGMCU_CR_DBG_TIM8_STOP = 0x20000
DBGMCU_CR_DBG_TIM5_STOP = 0x40000
DBGMCU_CR_DBG_TIM6_STOP = 0x80000
DBGMCU_CR_DBG_TIM7_STOP = 0x100000
DBGMCU_CR_DBG_CAN2_STOP = 0x200000
DBGMCU_CR_DBG_TIM15_STOP = 0x400000
DBGMCU_CR_DBG_TIM16_STOP = 0x800000
DBGMCU_CR_DBG_TIM17_STOP = 0x1000000
DBGMCU_CR_DBG_TIM12_STOP = 0x2000000
DBGMCU_CR_DBG_TIM13_STOP = 0x4000000
DBGMCU_CR_DBG_TIM14_STOP = 0x8000000
DBGMCU_CR_DBG_TIM9_STOP = 0x10000000
DBGMCU_CR_DBG_TIM10_STOP = 0x20000000
DBGMCU_CR_DBG_TIM11_STOP = 0x40000000
FLASH_ACR_LATENCY = 0x3
FLASH_ACR_LATENCY_0 = 0x0
FLASH_ACR_LATENCY_1 = 0x1
FLASH_ACR_LATENCY_2 = 0x2
FLASH_ACR_HLFCYA = 0x8
FLASH_ACR_PRFTBE = 0x10
FLASH_ACR_PRFTBS = 0x20
FLASH_KEYR_FKEYR = 0xFFFFFFFF
FLASH_OPTKEYR_OPTKEYR = 0xFFFFFFFF
FLASH_SR_BSY = 0x1
FLASH_SR_PGERR = 0x4
FLASH_SR_WRPRTERR = 0x10
FLASH_SR_EOP = 0x20
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
FLASH_AR_FAR = 0xFFFFFFFF
FLASH_OBR_OPTERR = 0x1
FLASH_OBR_RDPRT = 0x2
FLASH_OBR_USER = 0x3FC
FLASH_OBR_WDG_SW = 0x4
FLASH_OBR_nRST_STOP = 0x8
FLASH_OBR_nRST_STDBY = 0x10
FLASH_OBR_BFB2 = 0x20
FLASH_WRPR_WRP = 0xFFFFFFFF
FLASH_RDP_RDP = 0xFF
FLASH_RDP_nRDP = 0xFF00
FLASH_USER_USER = 0xFF0000
FLASH_USER_nUSER = 0xFF000000
FLASH_Data0_Data0 = 0xFF
FLASH_Data0_nData0 = 0xFF00
FLASH_Data1_Data1 = 0xFF0000
FLASH_Data1_nData1 = 0xFF000000
FLASH_WRP0_WRP0 = 0xFF
FLASH_WRP0_nWRP0 = 0xFF00
FLASH_WRP1_WRP1 = 0xFF0000
FLASH_WRP1_nWRP1 = 0xFF000000
FLASH_WRP2_WRP2 = 0xFF
FLASH_WRP2_nWRP2 = 0xFF00
FLASH_WRP3_WRP3 = 0xFF0000
FLASH_WRP3_nWRP3 = 0xFF000000
# Skip ETH_MACCR_WD : no need parse
# Skip ETH_MACCR_JD : no need parse
# Skip ETH_MACCR_IFG : no need parse
# Skip ETH_MACCR_IFG_96Bit : no need parse
# Skip ETH_MACCR_IFG_88Bit : no need parse
# Skip ETH_MACCR_IFG_80Bit : no need parse
# Skip ETH_MACCR_IFG_72Bit : no need parse
# Skip ETH_MACCR_IFG_64Bit : no need parse
# Skip ETH_MACCR_IFG_56Bit : no need parse
# Skip ETH_MACCR_IFG_48Bit : no need parse
# Skip ETH_MACCR_IFG_40Bit : no need parse
# Skip ETH_MACCR_CSD : no need parse
# Skip ETH_MACCR_FES : no need parse
# Skip ETH_MACCR_ROD : no need parse
# Skip ETH_MACCR_LM : no need parse
# Skip ETH_MACCR_DM : no need parse
# Skip ETH_MACCR_IPCO : no need parse
# Skip ETH_MACCR_RD : no need parse
# Skip ETH_MACCR_APCS : no need parse
# Skip ETH_MACCR_BL : no need parse
# Skip ETH_MACCR_BL_10 : no need parse
# Skip ETH_MACCR_BL_8 : no need parse
# Skip ETH_MACCR_BL_4 : no need parse
# Skip ETH_MACCR_BL_1 : no need parse
# Skip ETH_MACCR_DC : no need parse
# Skip ETH_MACCR_TE : no need parse
# Skip ETH_MACCR_RE : no need parse
# Skip ETH_MACFFR_RA : no need parse
# Skip ETH_MACFFR_HPF : no need parse
# Skip ETH_MACFFR_SAF : no need parse
# Skip ETH_MACFFR_SAIF : no need parse
# Skip ETH_MACFFR_PCF : no need parse
# Skip ETH_MACFFR_PCF_BlockAll : no need parse
# Skip ETH_MACFFR_PCF_ForwardAll : no need parse
# Skip ETH_MACFFR_PCF_ForwardPassedAddrFilter : no need parse
# Skip ETH_MACFFR_BFD : no need parse
# Skip ETH_MACFFR_PAM : no need parse
# Skip ETH_MACFFR_DAIF : no need parse
# Skip ETH_MACFFR_HM : no need parse
# Skip ETH_MACFFR_HU : no need parse
# Skip ETH_MACFFR_PM : no need parse
# Skip ETH_MACHTHR_HTH : no need parse
# Skip ETH_MACHTLR_HTL : no need parse
# Skip ETH_MACMIIAR_PA : no need parse
# Skip ETH_MACMIIAR_MR : no need parse
# Skip ETH_MACMIIAR_CR : no need parse
# Skip ETH_MACMIIAR_CR_Div42 : no need parse
# Skip ETH_MACMIIAR_CR_Div16 : no need parse
# Skip ETH_MACMIIAR_CR_Div26 : no need parse
# Skip ETH_MACMIIAR_MW : no need parse
# Skip ETH_MACMIIAR_MB : no need parse
# Skip ETH_MACMIIDR_MD : no need parse
# Skip ETH_MACFCR_PT : no need parse
# Skip ETH_MACFCR_ZQPD : no need parse
# Skip ETH_MACFCR_PLT : no need parse
# Skip ETH_MACFCR_PLT_Minus4 : no need parse
# Skip ETH_MACFCR_PLT_Minus28 : no need parse
# Skip ETH_MACFCR_PLT_Minus144 : no need parse
# Skip ETH_MACFCR_PLT_Minus256 : no need parse
# Skip ETH_MACFCR_UPFD : no need parse
# Skip ETH_MACFCR_RFCE : no need parse
# Skip ETH_MACFCR_TFCE : no need parse
# Skip ETH_MACFCR_FCBBPA : no need parse
# Skip ETH_MACVLANTR_VLANTC : no need parse
# Skip ETH_MACVLANTR_VLANTI : no need parse
# Skip ETH_MACRWUFFR_D : no need parse
# Skip ETH_MACPMTCSR_WFFRPR : no need parse
# Skip ETH_MACPMTCSR_GU : no need parse
# Skip ETH_MACPMTCSR_WFR : no need parse
# Skip ETH_MACPMTCSR_MPR : no need parse
# Skip ETH_MACPMTCSR_WFE : no need parse
# Skip ETH_MACPMTCSR_MPE : no need parse
# Skip ETH_MACPMTCSR_PD : no need parse
# Skip ETH_MACSR_TSTS : no need parse
# Skip ETH_MACSR_MMCTS : no need parse
# Skip ETH_MACSR_MMMCRS : no need parse
# Skip ETH_MACSR_MMCS : no need parse
# Skip ETH_MACSR_PMTS : no need parse
# Skip ETH_MACIMR_TSTIM : no need parse
# Skip ETH_MACIMR_PMTIM : no need parse
# Skip ETH_MACA0HR_MACA0H : no need parse
# Skip ETH_MACA0LR_MACA0L : no need parse
# Skip ETH_MACA1HR_AE : no need parse
# Skip ETH_MACA1HR_SA : no need parse
# Skip ETH_MACA1HR_MBC : no need parse
# Skip ETH_MACA1HR_MBC_HBits15_8 : no need parse
# Skip ETH_MACA1HR_MBC_HBits7_0 : no need parse
# Skip ETH_MACA1HR_MBC_LBits31_24 : no need parse
# Skip ETH_MACA1HR_MBC_LBits23_16 : no need parse
# Skip ETH_MACA1HR_MBC_LBits15_8 : no need parse
# Skip ETH_MACA1HR_MBC_LBits7_0 : no need parse
# Skip ETH_MACA1HR_MACA1H : no need parse
# Skip ETH_MACA1LR_MACA1L : no need parse
# Skip ETH_MACA2HR_AE : no need parse
# Skip ETH_MACA2HR_SA : no need parse
# Skip ETH_MACA2HR_MBC : no need parse
# Skip ETH_MACA2HR_MBC_HBits15_8 : no need parse
# Skip ETH_MACA2HR_MBC_HBits7_0 : no need parse
# Skip ETH_MACA2HR_MBC_LBits31_24 : no need parse
# Skip ETH_MACA2HR_MBC_LBits23_16 : no need parse
# Skip ETH_MACA2HR_MBC_LBits15_8 : no need parse
# Skip ETH_MACA2HR_MBC_LBits7_0 : no need parse
# Skip ETH_MACA2HR_MACA2H : no need parse
# Skip ETH_MACA2LR_MACA2L : no need parse
# Skip ETH_MACA3HR_AE : no need parse
# Skip ETH_MACA3HR_SA : no need parse
# Skip ETH_MACA3HR_MBC : no need parse
# Skip ETH_MACA3HR_MBC_HBits15_8 : no need parse
# Skip ETH_MACA3HR_MBC_HBits7_0 : no need parse
# Skip ETH_MACA3HR_MBC_LBits31_24 : no need parse
# Skip ETH_MACA3HR_MBC_LBits23_16 : no need parse
# Skip ETH_MACA3HR_MBC_LBits15_8 : no need parse
# Skip ETH_MACA3HR_MBC_LBits7_0 : no need parse
# Skip ETH_MACA3HR_MACA3H : no need parse
# Skip ETH_MACA3LR_MACA3L : no need parse
# Skip ETH_MMCCR_MCF : no need parse
# Skip ETH_MMCCR_ROR : no need parse
# Skip ETH_MMCCR_CSR : no need parse
# Skip ETH_MMCCR_CR : no need parse
# Skip ETH_MMCRIR_RGUFS : no need parse
# Skip ETH_MMCRIR_RFAES : no need parse
# Skip ETH_MMCRIR_RFCES : no need parse
# Skip ETH_MMCTIR_TGFS : no need parse
# Skip ETH_MMCTIR_TGFMSCS : no need parse
# Skip ETH_MMCTIR_TGFSCS : no need parse
# Skip ETH_MMCRIMR_RGUFM : no need parse
# Skip ETH_MMCRIMR_RFAEM : no need parse
# Skip ETH_MMCRIMR_RFCEM : no need parse
# Skip ETH_MMCTIMR_TGFM : no need parse
# Skip ETH_MMCTIMR_TGFMSCM : no need parse
# Skip ETH_MMCTIMR_TGFSCM : no need parse
# Skip ETH_MMCTGFSCCR_TGFSCC : no need parse
# Skip ETH_MMCTGFMSCCR_TGFMSCC : no need parse
# Skip ETH_MMCTGFCR_TGFC : no need parse
# Skip ETH_MMCRFCECR_RFCEC : no need parse
# Skip ETH_MMCRFAECR_RFAEC : no need parse
# Skip ETH_MMCRGUFCR_RGUFC : no need parse
# Skip ETH_PTPTSCR_TSARU : no need parse
# Skip ETH_PTPTSCR_TSITE : no need parse
# Skip ETH_PTPTSCR_TSSTU : no need parse
# Skip ETH_PTPTSCR_TSSTI : no need parse
# Skip ETH_PTPTSCR_TSFCU : no need parse
# Skip ETH_PTPTSCR_TSE : no need parse
# Skip ETH_PTPSSIR_STSSI : no need parse
# Skip ETH_PTPTSHR_STS : no need parse
# Skip ETH_PTPTSLR_STPNS : no need parse
# Skip ETH_PTPTSLR_STSS : no need parse
# Skip ETH_PTPTSHUR_TSUS : no need parse
# Skip ETH_PTPTSLUR_TSUPNS : no need parse
# Skip ETH_PTPTSLUR_TSUSS : no need parse
# Skip ETH_PTPTSAR_TSA : no need parse
# Skip ETH_PTPTTHR_TTSH : no need parse
# Skip ETH_PTPTTLR_TTSL : no need parse
# Skip ETH_DMABMR_AAB : no need parse
# Skip ETH_DMABMR_FPM : no need parse
# Skip ETH_DMABMR_USP : no need parse
# Skip ETH_DMABMR_RDP : no need parse
# Skip ETH_DMABMR_RDP_1Beat : no need parse
# Skip ETH_DMABMR_RDP_2Beat : no need parse
# Skip ETH_DMABMR_RDP_4Beat : no need parse
# Skip ETH_DMABMR_RDP_8Beat : no need parse
# Skip ETH_DMABMR_RDP_16Beat : no need parse
# Skip ETH_DMABMR_RDP_32Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_4Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_8Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_16Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_32Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_64Beat : no need parse
# Skip ETH_DMABMR_RDP_4xPBL_128Beat : no need parse
# Skip ETH_DMABMR_FB : no need parse
# Skip ETH_DMABMR_RTPR : no need parse
# Skip ETH_DMABMR_RTPR_1_1 : no need parse
# Skip ETH_DMABMR_RTPR_2_1 : no need parse
# Skip ETH_DMABMR_RTPR_3_1 : no need parse
# Skip ETH_DMABMR_RTPR_4_1 : no need parse
# Skip ETH_DMABMR_PBL : no need parse
# Skip ETH_DMABMR_PBL_1Beat : no need parse
# Skip ETH_DMABMR_PBL_2Beat : no need parse
# Skip ETH_DMABMR_PBL_4Beat : no need parse
# Skip ETH_DMABMR_PBL_8Beat : no need parse
# Skip ETH_DMABMR_PBL_16Beat : no need parse
# Skip ETH_DMABMR_PBL_32Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_4Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_8Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_16Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_32Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_64Beat : no need parse
# Skip ETH_DMABMR_PBL_4xPBL_128Beat : no need parse
# Skip ETH_DMABMR_DSL : no need parse
# Skip ETH_DMABMR_DA : no need parse
# Skip ETH_DMABMR_SR : no need parse
# Skip ETH_DMATPDR_TPD : no need parse
# Skip ETH_DMARPDR_RPD : no need parse
# Skip ETH_DMARDLAR_SRL : no need parse
# Skip ETH_DMATDLAR_STL : no need parse
# Skip ETH_DMASR_TSTS : no need parse
# Skip ETH_DMASR_PMTS : no need parse
# Skip ETH_DMASR_MMCS : no need parse
# Skip ETH_DMASR_EBS : no need parse
# Skip ETH_DMASR_EBS_DescAccess : no need parse
# Skip ETH_DMASR_EBS_ReadTransf : no need parse
# Skip ETH_DMASR_EBS_DataTransfTx : no need parse
# Skip ETH_DMASR_TPS : no need parse
# Skip ETH_DMASR_TPS_Stopped : no need parse
# Skip ETH_DMASR_TPS_Fetching : no need parse
# Skip ETH_DMASR_TPS_Waiting : no need parse
# Skip ETH_DMASR_TPS_Reading : no need parse
# Skip ETH_DMASR_TPS_Suspended : no need parse
# Skip ETH_DMASR_TPS_Closing : no need parse
# Skip ETH_DMASR_RPS : no need parse
# Skip ETH_DMASR_RPS_Stopped : no need parse
# Skip ETH_DMASR_RPS_Fetching : no need parse
# Skip ETH_DMASR_RPS_Waiting : no need parse
# Skip ETH_DMASR_RPS_Suspended : no need parse
# Skip ETH_DMASR_RPS_Closing : no need parse
# Skip ETH_DMASR_RPS_Queuing : no need parse
# Skip ETH_DMASR_NIS : no need parse
# Skip ETH_DMASR_AIS : no need parse
# Skip ETH_DMASR_ERS : no need parse
# Skip ETH_DMASR_FBES : no need parse
# Skip ETH_DMASR_ETS : no need parse
# Skip ETH_DMASR_RWTS : no need parse
# Skip ETH_DMASR_RPSS : no need parse
# Skip ETH_DMASR_RBUS : no need parse
# Skip ETH_DMASR_RS : no need parse
# Skip ETH_DMASR_TUS : no need parse
# Skip ETH_DMASR_ROS : no need parse
# Skip ETH_DMASR_TJTS : no need parse
# Skip ETH_DMASR_TBUS : no need parse
# Skip ETH_DMASR_TPSS : no need parse
# Skip ETH_DMASR_TS : no need parse
# Skip ETH_DMAOMR_DTCEFD : no need parse
# Skip ETH_DMAOMR_RSF : no need parse
# Skip ETH_DMAOMR_DFRF : no need parse
# Skip ETH_DMAOMR_TSF : no need parse
# Skip ETH_DMAOMR_FTF : no need parse
# Skip ETH_DMAOMR_TTC : no need parse
# Skip ETH_DMAOMR_TTC_64Bytes : no need parse
# Skip ETH_DMAOMR_TTC_128Bytes : no need parse
# Skip ETH_DMAOMR_TTC_192Bytes : no need parse
# Skip ETH_DMAOMR_TTC_256Bytes : no need parse
# Skip ETH_DMAOMR_TTC_40Bytes : no need parse
# Skip ETH_DMAOMR_TTC_32Bytes : no need parse
# Skip ETH_DMAOMR_TTC_24Bytes : no need parse
# Skip ETH_DMAOMR_TTC_16Bytes : no need parse
# Skip ETH_DMAOMR_ST : no need parse
# Skip ETH_DMAOMR_FEF : no need parse
# Skip ETH_DMAOMR_FUGF : no need parse
# Skip ETH_DMAOMR_RTC : no need parse
# Skip ETH_DMAOMR_RTC_64Bytes : no need parse
# Skip ETH_DMAOMR_RTC_32Bytes : no need parse
# Skip ETH_DMAOMR_RTC_96Bytes : no need parse
# Skip ETH_DMAOMR_RTC_128Bytes : no need parse
# Skip ETH_DMAOMR_OSF : no need parse
# Skip ETH_DMAOMR_SR : no need parse
# Skip ETH_DMAIER_NISE : no need parse
# Skip ETH_DMAIER_AISE : no need parse
# Skip ETH_DMAIER_ERIE : no need parse
# Skip ETH_DMAIER_FBEIE : no need parse
# Skip ETH_DMAIER_ETIE : no need parse
# Skip ETH_DMAIER_RWTIE : no need parse
# Skip ETH_DMAIER_RPSIE : no need parse
# Skip ETH_DMAIER_RBUIE : no need parse
# Skip ETH_DMAIER_RIE : no need parse
# Skip ETH_DMAIER_TUIE : no need parse
# Skip ETH_DMAIER_ROIE : no need parse
# Skip ETH_DMAIER_TJTIE : no need parse
# Skip ETH_DMAIER_TBUIE : no need parse
# Skip ETH_DMAIER_TPSIE : no need parse
# Skip ETH_DMAIER_TIE : no need parse
# Skip ETH_DMAMFBOCR_OFOC : no need parse
# Skip ETH_DMAMFBOCR_MFA : no need parse
# Skip ETH_DMAMFBOCR_OMFC : no need parse
# Skip ETH_DMAMFBOCR_MFC : no need parse
# Skip ETH_DMACHTDR_HTDAP : no need parse
# Skip ETH_DMACHRDR_HRDAP : no need parse
# Skip ETH_DMACHTBAR_HTBAP : no need parse
# Skip ETH_DMACHRBAR_HRBAP : no need parse
# struct ADC_TypeDef

class ADC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SR',	ctypes.c_uint32),
		('CR1',	ctypes.c_uint32),
		('CR2',	ctypes.c_uint32),
		('SMPR1',	ctypes.c_uint32),
		('SMPR2',	ctypes.c_uint32),
		('JOFR1',	ctypes.c_uint32),
		('JOFR2',	ctypes.c_uint32),
		('JOFR3',	ctypes.c_uint32),
		('JOFR4',	ctypes.c_uint32),
		('HTR',	ctypes.c_uint32),
		('LTR',	ctypes.c_uint32),
		('SQR1',	ctypes.c_uint32),
		('SQR2',	ctypes.c_uint32),
		('SQR3',	ctypes.c_uint32),
		('JSQR',	ctypes.c_uint32),
		('JDR1',	ctypes.c_uint32),
		('JDR2',	ctypes.c_uint32),
		('JDR3',	ctypes.c_uint32),
		('JDR4',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct BKP_TypeDef

class BKP_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('RESERVED0',	ctypes.c_uint32),
		('DR1',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('DR2',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('DR3',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('DR4',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('DR5',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('DR6',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
		('DR7',	ctypes.c_uint16),
		('RESERVED7',	ctypes.c_uint16),
		('DR8',	ctypes.c_uint16),
		('RESERVED8',	ctypes.c_uint16),
		('DR9',	ctypes.c_uint16),
		('RESERVED9',	ctypes.c_uint16),
		('DR10',	ctypes.c_uint16),
		('RESERVED10',	ctypes.c_uint16),
		('RTCCR',	ctypes.c_uint16),
		('RESERVED11',	ctypes.c_uint16),
		('CR',	ctypes.c_uint16),
		('RESERVED12',	ctypes.c_uint16),
		('CSR',	ctypes.c_uint16),
		('RESERVED13',	ctypes.c_uint16 * 5),
		('DR11',	ctypes.c_uint16),
		('RESERVED14',	ctypes.c_uint16),
		('DR12',	ctypes.c_uint16),
		('RESERVED15',	ctypes.c_uint16),
		('DR13',	ctypes.c_uint16),
		('RESERVED16',	ctypes.c_uint16),
		('DR14',	ctypes.c_uint16),
		('RESERVED17',	ctypes.c_uint16),
		('DR15',	ctypes.c_uint16),
		('RESERVED18',	ctypes.c_uint16),
		('DR16',	ctypes.c_uint16),
		('RESERVED19',	ctypes.c_uint16),
		('DR17',	ctypes.c_uint16),
		('RESERVED20',	ctypes.c_uint16),
		('DR18',	ctypes.c_uint16),
		('RESERVED21',	ctypes.c_uint16),
		('DR19',	ctypes.c_uint16),
		('RESERVED22',	ctypes.c_uint16),
		('DR20',	ctypes.c_uint16),
		('RESERVED23',	ctypes.c_uint16),
		('DR21',	ctypes.c_uint16),
		('RESERVED24',	ctypes.c_uint16),
		('DR22',	ctypes.c_uint16),
		('RESERVED25',	ctypes.c_uint16),
		('DR23',	ctypes.c_uint16),
		('RESERVED26',	ctypes.c_uint16),
		('DR24',	ctypes.c_uint16),
		('RESERVED27',	ctypes.c_uint16),
		('DR25',	ctypes.c_uint16),
		('RESERVED28',	ctypes.c_uint16),
		('DR26',	ctypes.c_uint16),
		('RESERVED29',	ctypes.c_uint16),
		('DR27',	ctypes.c_uint16),
		('RESERVED30',	ctypes.c_uint16),
		('DR28',	ctypes.c_uint16),
		('RESERVED31',	ctypes.c_uint16),
		('DR29',	ctypes.c_uint16),
		('RESERVED32',	ctypes.c_uint16),
		('DR30',	ctypes.c_uint16),
		('RESERVED33',	ctypes.c_uint16),
		('DR31',	ctypes.c_uint16),
		('RESERVED34',	ctypes.c_uint16),
		('DR32',	ctypes.c_uint16),
		('RESERVED35',	ctypes.c_uint16),
		('DR33',	ctypes.c_uint16),
		('RESERVED36',	ctypes.c_uint16),
		('DR34',	ctypes.c_uint16),
		('RESERVED37',	ctypes.c_uint16),
		('DR35',	ctypes.c_uint16),
		('RESERVED38',	ctypes.c_uint16),
		('DR36',	ctypes.c_uint16),
		('RESERVED39',	ctypes.c_uint16),
		('DR37',	ctypes.c_uint16),
		('RESERVED40',	ctypes.c_uint16),
		('DR38',	ctypes.c_uint16),
		('RESERVED41',	ctypes.c_uint16),
		('DR39',	ctypes.c_uint16),
		('RESERVED42',	ctypes.c_uint16),
		('DR40',	ctypes.c_uint16),
		('RESERVED43',	ctypes.c_uint16),
		('DR41',	ctypes.c_uint16),
		('RESERVED44',	ctypes.c_uint16),
		('DR42',	ctypes.c_uint16),
		('RESERVED45',	ctypes.c_uint16),
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
		('CFGR',	ctypes.c_uint32),
		('OAR',	ctypes.c_uint32),
		('PRES',	ctypes.c_uint32),
		('ESR',	ctypes.c_uint32),
		('CSR',	ctypes.c_uint32),
		('TXD',	ctypes.c_uint32),
		('RXD',	ctypes.c_uint32),
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
	]
	def ref(self):
		return ctypes.byref(self)

# struct DBGMCU_TypeDef

class DBGMCU_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('IDCODE',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
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
	]
	def ref(self):
		return ctypes.byref(self)

# struct ETH_TypeDef

class ETH_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('MACCR',	ctypes.c_uint32),
		('MACFFR',	ctypes.c_uint32),
		('MACHTHR',	ctypes.c_uint32),
		('MACHTLR',	ctypes.c_uint32),
		('MACMIIAR',	ctypes.c_uint32),
		('MACMIIDR',	ctypes.c_uint32),
		('MACFCR',	ctypes.c_uint32),
		('MACVLANTR',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32 * 2),
		('MACRWUFFR',	ctypes.c_uint32),
		('MACPMTCSR',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32 * 2),
		('MACSR',	ctypes.c_uint32),
		('MACIMR',	ctypes.c_uint32),
		('MACA0HR',	ctypes.c_uint32),
		('MACA0LR',	ctypes.c_uint32),
		('MACA1HR',	ctypes.c_uint32),
		('MACA1LR',	ctypes.c_uint32),
		('MACA2HR',	ctypes.c_uint32),
		('MACA2LR',	ctypes.c_uint32),
		('MACA3HR',	ctypes.c_uint32),
		('MACA3LR',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32 * 40),
		('MMCCR',	ctypes.c_uint32),
		('MMCRIR',	ctypes.c_uint32),
		('MMCTIR',	ctypes.c_uint32),
		('MMCRIMR',	ctypes.c_uint32),
		('MMCTIMR',	ctypes.c_uint32),
		('RESERVED3',	ctypes.c_uint32 * 14),
		('MMCTGFSCCR',	ctypes.c_uint32),
		('MMCTGFMSCCR',	ctypes.c_uint32),
		('RESERVED4',	ctypes.c_uint32 * 5),
		('MMCTGFCR',	ctypes.c_uint32),
		('RESERVED5',	ctypes.c_uint32 * 10),
		('MMCRFCECR',	ctypes.c_uint32),
		('MMCRFAECR',	ctypes.c_uint32),
		('RESERVED6',	ctypes.c_uint32 * 10),
		('MMCRGUFCR',	ctypes.c_uint32),
		('RESERVED7',	ctypes.c_uint32 * 334),
		('PTPTSCR',	ctypes.c_uint32),
		('PTPSSIR',	ctypes.c_uint32),
		('PTPTSHR',	ctypes.c_uint32),
		('PTPTSLR',	ctypes.c_uint32),
		('PTPTSHUR',	ctypes.c_uint32),
		('PTPTSLUR',	ctypes.c_uint32),
		('PTPTSAR',	ctypes.c_uint32),
		('PTPTTHR',	ctypes.c_uint32),
		('PTPTTLR',	ctypes.c_uint32),
		('RESERVED8',	ctypes.c_uint32 * 567),
		('DMABMR',	ctypes.c_uint32),
		('DMATPDR',	ctypes.c_uint32),
		('DMARPDR',	ctypes.c_uint32),
		('DMARDLAR',	ctypes.c_uint32),
		('DMATDLAR',	ctypes.c_uint32),
		('DMASR',	ctypes.c_uint32),
		('DMAOMR',	ctypes.c_uint32),
		('DMAIER',	ctypes.c_uint32),
		('DMAMFBOCR',	ctypes.c_uint32),
		('RESERVED9',	ctypes.c_uint32 * 9),
		('DMACHTDR',	ctypes.c_uint32),
		('DMACHRDR',	ctypes.c_uint32),
		('DMACHTBAR',	ctypes.c_uint32),
		('DMACHRBAR',	ctypes.c_uint32),
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
		('Data0',	ctypes.c_uint16),
		('Data1',	ctypes.c_uint16),
		('WRP0',	ctypes.c_uint16),
		('WRP1',	ctypes.c_uint16),
		('WRP2',	ctypes.c_uint16),
		('WRP3',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank1_TypeDef

class FSMC_Bank1_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('BTCR',	ctypes.c_uint32 * 8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank1E_TypeDef

class FSMC_Bank1E_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('BWTR',	ctypes.c_uint32 * 7),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank2_TypeDef

class FSMC_Bank2_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('PCR2',	ctypes.c_uint32),
		('SR2',	ctypes.c_uint32),
		('PMEM2',	ctypes.c_uint32),
		('PATT2',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32),
		('ECCR2',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank3_TypeDef

class FSMC_Bank3_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('PCR3',	ctypes.c_uint32),
		('SR3',	ctypes.c_uint32),
		('PMEM3',	ctypes.c_uint32),
		('PATT3',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32),
		('ECCR3',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank4_TypeDef

class FSMC_Bank4_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('PCR4',	ctypes.c_uint32),
		('SR4',	ctypes.c_uint32),
		('PMEM4',	ctypes.c_uint32),
		('PATT4',	ctypes.c_uint32),
		('PIO4',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct GPIO_TypeDef

class GPIO_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CRL',	ctypes.c_uint32),
		('CRH',	ctypes.c_uint32),
		('IDR',	ctypes.c_uint32),
		('ODR',	ctypes.c_uint32),
		('BSRR',	ctypes.c_uint32),
		('BRR',	ctypes.c_uint32),
		('LCKR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct AFIO_TypeDef

class AFIO_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('EVCR',	ctypes.c_uint32),
		('MAPR',	ctypes.c_uint32),
		('EXTICR',	ctypes.c_uint32 * 4),
		('RESERVED0',	ctypes.c_uint32),
		('MAPR2',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct I2C_TypeDef

class I2C_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR1',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('CR2',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('OAR1',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('OAR2',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('DR',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('SR1',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('SR2',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
		('CCR',	ctypes.c_uint16),
		('RESERVED7',	ctypes.c_uint16),
		('TRISE',	ctypes.c_uint16),
		('RESERVED8',	ctypes.c_uint16),
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
	]
	def ref(self):
		return ctypes.byref(self)

# struct RTC_TypeDef

class RTC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CRH',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('CRL',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('PRLH',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('PRLL',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('DIVH',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('DIVL',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('CNTH',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
		('CNTL',	ctypes.c_uint16),
		('RESERVED7',	ctypes.c_uint16),
		('ALRH',	ctypes.c_uint16),
		('RESERVED8',	ctypes.c_uint16),
		('ALRL',	ctypes.c_uint16),
		('RESERVED9',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SDIO_TypeDef

class SDIO_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('POWER',	ctypes.c_uint32),
		('CLKCR',	ctypes.c_uint32),
		('ARG',	ctypes.c_uint32),
		('CMD',	ctypes.c_uint32),
		('RESPCMD',	ctypes.c_uint32),
		('RESP1',	ctypes.c_uint32),
		('RESP2',	ctypes.c_uint32),
		('RESP3',	ctypes.c_uint32),
		('RESP4',	ctypes.c_uint32),
		('DTIMER',	ctypes.c_uint32),
		('DLEN',	ctypes.c_uint32),
		('DCTRL',	ctypes.c_uint32),
		('DCOUNT',	ctypes.c_uint32),
		('STA',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
		('MASK',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32 * 2),
		('FIFOCNT',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32 * 13),
		('FIFO',	ctypes.c_uint32),
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
		('CNT',	ctypes.c_uint16),
		('RESERVED9',	ctypes.c_uint16),
		('PSC',	ctypes.c_uint16),
		('RESERVED10',	ctypes.c_uint16),
		('ARR',	ctypes.c_uint16),
		('RESERVED11',	ctypes.c_uint16),
		('RCR',	ctypes.c_uint16),
		('RESERVED12',	ctypes.c_uint16),
		('CCR1',	ctypes.c_uint16),
		('RESERVED13',	ctypes.c_uint16),
		('CCR2',	ctypes.c_uint16),
		('RESERVED14',	ctypes.c_uint16),
		('CCR3',	ctypes.c_uint16),
		('RESERVED15',	ctypes.c_uint16),
		('CCR4',	ctypes.c_uint16),
		('RESERVED16',	ctypes.c_uint16),
		('BDTR',	ctypes.c_uint16),
		('RESERVED17',	ctypes.c_uint16),
		('DCR',	ctypes.c_uint16),
		('RESERVED18',	ctypes.c_uint16),
		('DMAR',	ctypes.c_uint16),
		('RESERVED19',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct USART_TypeDef

class USART_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SR',	ctypes.c_uint16),
		('RESERVED0',	ctypes.c_uint16),
		('DR',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
		('BRR',	ctypes.c_uint16),
		('RESERVED2',	ctypes.c_uint16),
		('CR1',	ctypes.c_uint16),
		('RESERVED3',	ctypes.c_uint16),
		('CR2',	ctypes.c_uint16),
		('RESERVED4',	ctypes.c_uint16),
		('CR3',	ctypes.c_uint16),
		('RESERVED5',	ctypes.c_uint16),
		('GTPR',	ctypes.c_uint16),
		('RESERVED6',	ctypes.c_uint16),
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

# file system_stm32f10x.h : 

# empty define __SYSTEM_STM32F10X_H
# Skip SystemCoreClock : no need parse
# ----------------------------------------


__all__ =  ['__version__', '__RUN', '__HALT', '__ERROR', '__WARNING', '__INFO', '__DEBUG',
    '__ALL_LOG', 'DEFAULT_OPENOCD_PORT', 'DEFAULT_GDB_PORT', 'RTC_IT_OW', 'RTC_IT_ALR',
    'RTC_IT_SEC', 'RTC_FLAG_RTOFF', 'RTC_FLAG_RSF', 'RTC_FLAG_OW', 'RTC_FLAG_ALR',
    'RTC_FLAG_SEC', 'PWR_PVDLevel_2V2', 'PWR_PVDLevel_2V3', 'PWR_PVDLevel_2V4',
    'PWR_PVDLevel_2V5', 'PWR_PVDLevel_2V6', 'PWR_PVDLevel_2V7', 'PWR_PVDLevel_2V8',
    'PWR_PVDLevel_2V9', 'PWR_Regulator_ON', 'PWR_Regulator_LowPower',
    'PWR_STOPEntry_WFI', 'PWR_STOPEntry_WFE', 'PWR_FLAG_WU', 'PWR_FLAG_SB',
    'PWR_FLAG_PVDO', 'IWDG_WriteAccess_Enable', 'IWDG_WriteAccess_Disable',
    'IWDG_Prescaler_4', 'IWDG_Prescaler_8', 'IWDG_Prescaler_16', 'IWDG_Prescaler_32',
    'IWDG_Prescaler_64', 'IWDG_Prescaler_128', 'IWDG_Prescaler_256', 'IWDG_FLAG_PVU',
    'IWDG_FLAG_RVU', 'USART_WordLength_8b', 'USART_WordLength_9b', 'USART_StopBits_1',
    'USART_StopBits_0_5', 'USART_StopBits_2', 'USART_StopBits_1_5', 'USART_Parity_No',
    'USART_Parity_Even', 'USART_Parity_Odd', 'USART_Mode_Rx', 'USART_Mode_Tx',
    'USART_HardwareFlowControl_None', 'USART_HardwareFlowControl_RTS',
    'USART_HardwareFlowControl_CTS', 'USART_HardwareFlowControl_RTS_CTS',
    'USART_Clock_Disable', 'USART_Clock_Enable', 'USART_CPOL_Low', 'USART_CPOL_High',
    'USART_CPHA_1Edge', 'USART_CPHA_2Edge', 'USART_LastBit_Disable',
    'USART_LastBit_Enable', 'USART_IT_PE', 'USART_IT_TXE', 'USART_IT_TC',
    'USART_IT_RXNE', 'USART_IT_IDLE', 'USART_IT_LBD', 'USART_IT_CTS', 'USART_IT_ERR',
    'USART_IT_ORE', 'USART_IT_NE', 'USART_IT_FE', 'USART_DMAReq_Tx', 'USART_DMAReq_Rx',
    'USART_WakeUp_IdleLine', 'USART_WakeUp_AddressMark',
    'USART_LINBreakDetectLength_10b', 'USART_LINBreakDetectLength_11b',
    'USART_IrDAMode_LowPower', 'USART_IrDAMode_Normal', 'USART_FLAG_CTS',
    'USART_FLAG_LBD', 'USART_FLAG_TXE', 'USART_FLAG_TC', 'USART_FLAG_RXNE',
    'USART_FLAG_IDLE', 'USART_FLAG_ORE', 'USART_FLAG_NE', 'USART_FLAG_FE',
    'USART_FLAG_PE', 'USART_InitTypeDef', 'USART_ClockInitTypeDef', 'DBGMCU_SLEEP',
    'DBGMCU_STOP', 'DBGMCU_STANDBY', 'DBGMCU_IWDG_STOP', 'DBGMCU_WWDG_STOP',
    'DBGMCU_TIM1_STOP', 'DBGMCU_TIM2_STOP', 'DBGMCU_TIM3_STOP', 'DBGMCU_TIM4_STOP',
    'DBGMCU_CAN1_STOP', 'DBGMCU_I2C1_SMBUS_TIMEOUT', 'DBGMCU_I2C2_SMBUS_TIMEOUT',
    'DBGMCU_TIM8_STOP', 'DBGMCU_TIM5_STOP', 'DBGMCU_TIM6_STOP', 'DBGMCU_TIM7_STOP',
    'DBGMCU_CAN2_STOP', 'DBGMCU_TIM15_STOP', 'DBGMCU_TIM16_STOP', 'DBGMCU_TIM17_STOP',
    'DBGMCU_TIM12_STOP', 'DBGMCU_TIM13_STOP', 'DBGMCU_TIM14_STOP', 'DBGMCU_TIM9_STOP',
    'DBGMCU_TIM10_STOP', 'DBGMCU_TIM11_STOP', 'EXTI_Mode_Interrupt', 'EXTI_Mode_Event',
    'EXTI_Trigger_Rising', 'EXTI_Trigger_Falling', 'EXTI_Trigger_Rising_Falling',
    'EXTI_Line0', 'EXTI_Line1', 'EXTI_Line2', 'EXTI_Line3', 'EXTI_Line4', 'EXTI_Line5',
    'EXTI_Line6', 'EXTI_Line7', 'EXTI_Line8', 'EXTI_Line9', 'EXTI_Line10',
    'EXTI_Line11', 'EXTI_Line12', 'EXTI_Line13', 'EXTI_Line14', 'EXTI_Line15',
    'EXTI_Line16', 'EXTI_Line17', 'EXTI_Line18', 'EXTI_Line19', 'EXTI_InitTypeDef',
    'SPI_Direction_2Lines_FullDuplex', 'SPI_Direction_2Lines_RxOnly',
    'SPI_Direction_1Line_Rx', 'SPI_Direction_1Line_Tx', 'SPI_Mode_Master',
    'SPI_Mode_Slave', 'SPI_DataSize_16b', 'SPI_DataSize_8b', 'SPI_CPOL_Low',
    'SPI_CPOL_High', 'SPI_CPHA_1Edge', 'SPI_CPHA_2Edge', 'SPI_NSS_Soft', 'SPI_NSS_Hard',
    'SPI_BaudRatePrescaler_2', 'SPI_BaudRatePrescaler_4', 'SPI_BaudRatePrescaler_8',
    'SPI_BaudRatePrescaler_16', 'SPI_BaudRatePrescaler_32', 'SPI_BaudRatePrescaler_64',
    'SPI_BaudRatePrescaler_128', 'SPI_BaudRatePrescaler_256', 'SPI_FirstBit_MSB',
    'SPI_FirstBit_LSB', 'I2S_Mode_SlaveTx', 'I2S_Mode_SlaveRx', 'I2S_Mode_MasterTx',
    'I2S_Mode_MasterRx', 'I2S_Standard_Phillips', 'I2S_Standard_MSB',
    'I2S_Standard_LSB', 'I2S_Standard_PCMShort', 'I2S_Standard_PCMLong',
    'I2S_DataFormat_16b', 'I2S_DataFormat_16bextended', 'I2S_DataFormat_24b',
    'I2S_DataFormat_32b', 'I2S_MCLKOutput_Enable', 'I2S_MCLKOutput_Disable',
    'I2S_AudioFreq_192k', 'I2S_AudioFreq_96k', 'I2S_AudioFreq_48k', 'I2S_AudioFreq_44k',
    'I2S_AudioFreq_32k', 'I2S_AudioFreq_22k', 'I2S_AudioFreq_16k', 'I2S_AudioFreq_11k',
    'I2S_AudioFreq_8k', 'I2S_AudioFreq_Default', 'I2S_CPOL_Low', 'I2S_CPOL_High',
    'SPI_I2S_DMAReq_Tx', 'SPI_I2S_DMAReq_Rx', 'SPI_NSSInternalSoft_Set',
    'SPI_NSSInternalSoft_Reset', 'SPI_CRC_Tx', 'SPI_CRC_Rx', 'SPI_Direction_Rx',
    'SPI_Direction_Tx', 'SPI_I2S_IT_TXE', 'SPI_I2S_IT_RXNE', 'SPI_I2S_IT_ERR',
    'SPI_I2S_IT_OVR', 'SPI_IT_MODF', 'SPI_IT_CRCERR', 'I2S_IT_UDR', 'SPI_I2S_FLAG_RXNE',
    'SPI_I2S_FLAG_TXE', 'I2S_FLAG_CHSIDE', 'I2S_FLAG_UDR', 'SPI_FLAG_CRCERR',
    'SPI_FLAG_MODF', 'SPI_I2S_FLAG_OVR', 'SPI_I2S_FLAG_BSY', 'SPI_InitTypeDef',
    'I2S_InitTypeDef', 'ADC_Mode_Independent', 'ADC_Mode_RegInjecSimult',
    'ADC_Mode_RegSimult_AlterTrig', 'ADC_Mode_InjecSimult_FastInterl',
    'ADC_Mode_InjecSimult_SlowInterl', 'ADC_Mode_InjecSimult', 'ADC_Mode_RegSimult',
    'ADC_Mode_FastInterl', 'ADC_Mode_SlowInterl', 'ADC_Mode_AlterTrig',
    'ADC_ExternalTrigConv_T1_CC1', 'ADC_ExternalTrigConv_T1_CC2',
    'ADC_ExternalTrigConv_T2_CC2', 'ADC_ExternalTrigConv_T3_TRGO',
    'ADC_ExternalTrigConv_T4_CC4', 'ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO',
    'ADC_ExternalTrigConv_T1_CC3', 'ADC_ExternalTrigConv_None',
    'ADC_ExternalTrigConv_T3_CC1', 'ADC_ExternalTrigConv_T2_CC3',
    'ADC_ExternalTrigConv_T8_CC1', 'ADC_ExternalTrigConv_T8_TRGO',
    'ADC_ExternalTrigConv_T5_CC1', 'ADC_ExternalTrigConv_T5_CC3', 'ADC_DataAlign_Right',
    'ADC_DataAlign_Left', 'ADC_Channel_0', 'ADC_Channel_1', 'ADC_Channel_2',
    'ADC_Channel_3', 'ADC_Channel_4', 'ADC_Channel_5', 'ADC_Channel_6', 'ADC_Channel_7',
    'ADC_Channel_8', 'ADC_Channel_9', 'ADC_Channel_10', 'ADC_Channel_11',
    'ADC_Channel_12', 'ADC_Channel_13', 'ADC_Channel_14', 'ADC_Channel_15',
    'ADC_Channel_16', 'ADC_Channel_17', 'ADC_Channel_TempSensor', 'ADC_Channel_Vrefint',
    'ADC_SampleTime_1Cycles5', 'ADC_SampleTime_7Cycles5', 'ADC_SampleTime_13Cycles5',
    'ADC_SampleTime_28Cycles5', 'ADC_SampleTime_41Cycles5', 'ADC_SampleTime_55Cycles5',
    'ADC_SampleTime_71Cycles5', 'ADC_SampleTime_239Cycles5',
    'ADC_ExternalTrigInjecConv_T2_TRGO', 'ADC_ExternalTrigInjecConv_T2_CC1',
    'ADC_ExternalTrigInjecConv_T3_CC4', 'ADC_ExternalTrigInjecConv_T4_TRGO',
    'ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4', 'ADC_ExternalTrigInjecConv_T1_TRGO',
    'ADC_ExternalTrigInjecConv_T1_CC4', 'ADC_ExternalTrigInjecConv_None',
    'ADC_ExternalTrigInjecConv_T4_CC3', 'ADC_ExternalTrigInjecConv_T8_CC2',
    'ADC_ExternalTrigInjecConv_T8_CC4', 'ADC_ExternalTrigInjecConv_T5_TRGO',
    'ADC_ExternalTrigInjecConv_T5_CC4', 'ADC_InjectedChannel_1',
    'ADC_InjectedChannel_2', 'ADC_InjectedChannel_3', 'ADC_InjectedChannel_4',
    'ADC_AnalogWatchdog_SingleRegEnable', 'ADC_AnalogWatchdog_SingleInjecEnable',
    'ADC_AnalogWatchdog_SingleRegOrInjecEnable', 'ADC_AnalogWatchdog_AllRegEnable',
    'ADC_AnalogWatchdog_AllInjecEnable', 'ADC_AnalogWatchdog_AllRegAllInjecEnable',
    'ADC_AnalogWatchdog_None', 'ADC_IT_EOC', 'ADC_IT_AWD', 'ADC_IT_JEOC',
    'ADC_FLAG_AWD', 'ADC_FLAG_EOC', 'ADC_FLAG_JEOC', 'ADC_FLAG_JSTRT', 'ADC_FLAG_STRT',
    'ADC_InitTypeDef', 'CAN_InitStatus_Failed', 'CAN_InitStatus_Success',
    'CAN_Mode_Normal', 'CAN_Mode_LoopBack', 'CAN_Mode_Silent',
    'CAN_Mode_Silent_LoopBack', 'CAN_OperatingMode_Initialization',
    'CAN_OperatingMode_Normal', 'CAN_OperatingMode_Sleep', 'CAN_ModeStatus_Failed',
    'CAN_ModeStatus_Success', 'CAN_SJW_1tq', 'CAN_SJW_2tq', 'CAN_SJW_3tq',
    'CAN_SJW_4tq', 'CAN_BS1_1tq', 'CAN_BS1_2tq', 'CAN_BS1_3tq', 'CAN_BS1_4tq',
    'CAN_BS1_5tq', 'CAN_BS1_6tq', 'CAN_BS1_7tq', 'CAN_BS1_8tq', 'CAN_BS1_9tq',
    'CAN_BS1_10tq', 'CAN_BS1_11tq', 'CAN_BS1_12tq', 'CAN_BS1_13tq', 'CAN_BS1_14tq',
    'CAN_BS1_15tq', 'CAN_BS1_16tq', 'CAN_BS2_1tq', 'CAN_BS2_2tq', 'CAN_BS2_3tq',
    'CAN_BS2_4tq', 'CAN_BS2_5tq', 'CAN_BS2_6tq', 'CAN_BS2_7tq', 'CAN_BS2_8tq',
    'CAN_FilterMode_IdMask', 'CAN_FilterMode_IdList', 'CAN_FilterScale_16bit',
    'CAN_FilterScale_32bit', 'CAN_Filter_FIFO0', 'CAN_Filter_FIFO1', 'CAN_Id_Standard',
    'CAN_Id_Extended', 'CAN_RTR_Data', 'CAN_RTR_Remote', 'CAN_TxStatus_Failed',
    'CAN_TxStatus_Ok', 'CAN_TxStatus_Pending', 'CAN_TxStatus_NoMailBox', 'CAN_FIFO0',
    'CAN_FIFO1', 'CAN_Sleep_Failed', 'CAN_Sleep_Ok', 'CAN_WakeUp_Failed',
    'CAN_WakeUp_Ok', 'CAN_ErrorCode_NoErr', 'CAN_ErrorCode_StuffErr',
    'CAN_ErrorCode_FormErr', 'CAN_ErrorCode_ACKErr', 'CAN_ErrorCode_BitRecessiveErr',
    'CAN_ErrorCode_BitDominantErr', 'CAN_ErrorCode_CRCErr',
    'CAN_ErrorCode_SoftwareSetErr', 'CAN_FLAG_RQCP0', 'CAN_FLAG_RQCP1',
    'CAN_FLAG_RQCP2', 'CAN_FLAG_FMP0', 'CAN_FLAG_FF0', 'CAN_FLAG_FOV0', 'CAN_FLAG_FMP1',
    'CAN_FLAG_FF1', 'CAN_FLAG_FOV1', 'CAN_FLAG_WKU', 'CAN_FLAG_SLAK', 'CAN_FLAG_EWG',
    'CAN_FLAG_EPV', 'CAN_FLAG_BOF', 'CAN_FLAG_LEC', 'CAN_IT_TME', 'CAN_IT_FMP0',
    'CAN_IT_FF0', 'CAN_IT_FOV0', 'CAN_IT_FMP1', 'CAN_IT_FF1', 'CAN_IT_FOV1',
    'CAN_IT_WKU', 'CAN_IT_SLK', 'CAN_IT_EWG', 'CAN_IT_EPV', 'CAN_IT_BOF', 'CAN_IT_LEC',
    'CAN_IT_ERR', 'CAN_IT_RQCP0', 'CAN_IT_RQCP1', 'CAN_IT_RQCP2', 'CANINITFAILED',
    'CANINITOK', 'CAN_FilterFIFO0', 'CAN_FilterFIFO1', 'CAN_ID_STD', 'CAN_ID_EXT',
    'CAN_RTR_DATA', 'CAN_RTR_REMOTE', 'CANTXFAILE', 'CANTXOK', 'CANTXPENDING',
    'CAN_NO_MB', 'CANSLEEPFAILED', 'CANSLEEPOK', 'CANWAKEUPFAILED', 'CANWAKEUPOK',
    'CAN_InitTypeDef', 'CAN_FilterInitTypeDef', 'CanTxMsg', 'CanRxMsg',
    'BKP_TamperPinLevel_High', 'BKP_TamperPinLevel_Low', 'BKP_RTCOutputSource_None',
    'BKP_RTCOutputSource_CalibClock', 'BKP_RTCOutputSource_Alarm',
    'BKP_RTCOutputSource_Second', 'BKP_DR1', 'BKP_DR2', 'BKP_DR3', 'BKP_DR4', 'BKP_DR5',
    'BKP_DR6', 'BKP_DR7', 'BKP_DR8', 'BKP_DR9', 'BKP_DR10', 'BKP_DR11', 'BKP_DR12',
    'BKP_DR13', 'BKP_DR14', 'BKP_DR15', 'BKP_DR16', 'BKP_DR17', 'BKP_DR18', 'BKP_DR19',
    'BKP_DR20', 'BKP_DR21', 'BKP_DR22', 'BKP_DR23', 'BKP_DR24', 'BKP_DR25', 'BKP_DR26',
    'BKP_DR27', 'BKP_DR28', 'BKP_DR29', 'BKP_DR30', 'BKP_DR31', 'BKP_DR32', 'BKP_DR33',
    'BKP_DR34', 'BKP_DR35', 'BKP_DR36', 'BKP_DR37', 'BKP_DR38', 'BKP_DR39', 'BKP_DR40',
    'BKP_DR41', 'BKP_DR42', 'FSMC_Bank1_NORSRAM1', 'FSMC_Bank1_NORSRAM2',
    'FSMC_Bank1_NORSRAM3', 'FSMC_Bank1_NORSRAM4', 'FSMC_Bank2_NAND', 'FSMC_Bank3_NAND',
    'FSMC_Bank4_PCCARD', 'FSMC_DataAddressMux_Disable', 'FSMC_DataAddressMux_Enable',
    'FSMC_MemoryType_SRAM', 'FSMC_MemoryType_PSRAM', 'FSMC_MemoryType_NOR',
    'FSMC_MemoryDataWidth_8b', 'FSMC_MemoryDataWidth_16b',
    'FSMC_BurstAccessMode_Disable', 'FSMC_BurstAccessMode_Enable',
    'FSMC_AsynchronousWait_Disable', 'FSMC_AsynchronousWait_Enable',
    'FSMC_WaitSignalPolarity_Low', 'FSMC_WaitSignalPolarity_High',
    'FSMC_WrapMode_Disable', 'FSMC_WrapMode_Enable',
    'FSMC_WaitSignalActive_BeforeWaitState', 'FSMC_WaitSignalActive_DuringWaitState',
    'FSMC_WriteOperation_Disable', 'FSMC_WriteOperation_Enable',
    'FSMC_WaitSignal_Disable', 'FSMC_WaitSignal_Enable', 'FSMC_ExtendedMode_Disable',
    'FSMC_ExtendedMode_Enable', 'FSMC_WriteBurst_Disable', 'FSMC_WriteBurst_Enable',
    'FSMC_AccessMode_A', 'FSMC_AccessMode_B', 'FSMC_AccessMode_C', 'FSMC_AccessMode_D',
    'FSMC_Waitfeature_Disable', 'FSMC_Waitfeature_Enable', 'FSMC_ECC_Disable',
    'FSMC_ECC_Enable', 'FSMC_ECCPageSize_256Bytes', 'FSMC_ECCPageSize_512Bytes',
    'FSMC_ECCPageSize_1024Bytes', 'FSMC_ECCPageSize_2048Bytes',
    'FSMC_ECCPageSize_4096Bytes', 'FSMC_ECCPageSize_8192Bytes', 'FSMC_IT_RisingEdge',
    'FSMC_IT_Level', 'FSMC_IT_FallingEdge', 'FSMC_FLAG_RisingEdge', 'FSMC_FLAG_Level',
    'FSMC_FLAG_FallingEdge', 'FSMC_FLAG_FEMPT', 'FSMC_NORSRAMTimingInitTypeDef',
    'FSMC_NAND_PCCARDTimingInitTypeDef', 'NVIC_VectTab_RAM', 'NVIC_VectTab_FLASH',
    'NVIC_LP_SEVONPEND', 'NVIC_LP_SLEEPDEEP', 'NVIC_LP_SLEEPONEXIT',
    'NVIC_PriorityGroup_0', 'NVIC_PriorityGroup_1', 'NVIC_PriorityGroup_2',
    'NVIC_PriorityGroup_3', 'NVIC_PriorityGroup_4', 'SysTick_CLKSource_HCLK_Div8',
    'SysTick_CLKSource_HCLK', 'NVIC_InitTypeDef', 'GPIO_Speed_10MHz', 'GPIO_Speed_2MHz',
    'GPIO_Speed_50MHz', 'GPIO_Mode_AIN', 'GPIO_Mode_IN_FLOATING', 'GPIO_Mode_IPD',
    'GPIO_Mode_IPU', 'GPIO_Mode_Out_OD', 'GPIO_Mode_Out_PP', 'GPIO_Mode_AF_OD',
    'GPIO_Mode_AF_PP', 'Bit_RESET', 'Bit_SET', 'GPIO_Pin_0', 'GPIO_Pin_1', 'GPIO_Pin_2',
    'GPIO_Pin_3', 'GPIO_Pin_4', 'GPIO_Pin_5', 'GPIO_Pin_6', 'GPIO_Pin_7', 'GPIO_Pin_8',
    'GPIO_Pin_9', 'GPIO_Pin_10', 'GPIO_Pin_11', 'GPIO_Pin_12', 'GPIO_Pin_13',
    'GPIO_Pin_14', 'GPIO_Pin_15', 'GPIO_Pin_All', 'GPIO_Remap_SPI1', 'GPIO_Remap_I2C1',
    'GPIO_Remap_USART1', 'GPIO_Remap_USART2', 'GPIO_PartialRemap_USART3',
    'GPIO_FullRemap_USART3', 'GPIO_PartialRemap_TIM1', 'GPIO_FullRemap_TIM1',
    'GPIO_PartialRemap1_TIM2', 'GPIO_PartialRemap2_TIM2', 'GPIO_FullRemap_TIM2',
    'GPIO_PartialRemap_TIM3', 'GPIO_FullRemap_TIM3', 'GPIO_Remap_TIM4',
    'GPIO_Remap1_CAN1', 'GPIO_Remap2_CAN1', 'GPIO_Remap_PD01', 'GPIO_Remap_TIM5CH4_LSI',
    'GPIO_Remap_ADC1_ETRGINJ', 'GPIO_Remap_ADC1_ETRGREG', 'GPIO_Remap_ADC2_ETRGINJ',
    'GPIO_Remap_ADC2_ETRGREG', 'GPIO_Remap_ETH', 'GPIO_Remap_CAN2',
    'GPIO_Remap_SWJ_NoJTRST', 'GPIO_Remap_SWJ_JTAGDisable', 'GPIO_Remap_SWJ_Disable',
    'GPIO_Remap_SPI3', 'GPIO_Remap_TIM2ITR1_PTP_SOF', 'GPIO_Remap_PTP_PPS',
    'GPIO_Remap_TIM15', 'GPIO_Remap_TIM16', 'GPIO_Remap_TIM17', 'GPIO_Remap_CEC',
    'GPIO_Remap_TIM1_DMA', 'GPIO_Remap_TIM9', 'GPIO_Remap_TIM10', 'GPIO_Remap_TIM11',
    'GPIO_Remap_TIM13', 'GPIO_Remap_TIM14', 'GPIO_Remap_FSMC_NADV',
    'GPIO_Remap_TIM67_DAC_DMA', 'GPIO_Remap_TIM12', 'GPIO_Remap_MISC',
    'GPIO_PortSourceGPIOA', 'GPIO_PortSourceGPIOB', 'GPIO_PortSourceGPIOC',
    'GPIO_PortSourceGPIOD', 'GPIO_PortSourceGPIOE', 'GPIO_PortSourceGPIOF',
    'GPIO_PortSourceGPIOG', 'GPIO_PinSource0', 'GPIO_PinSource1', 'GPIO_PinSource2',
    'GPIO_PinSource3', 'GPIO_PinSource4', 'GPIO_PinSource5', 'GPIO_PinSource6',
    'GPIO_PinSource7', 'GPIO_PinSource8', 'GPIO_PinSource9', 'GPIO_PinSource10',
    'GPIO_PinSource11', 'GPIO_PinSource12', 'GPIO_PinSource13', 'GPIO_PinSource14',
    'GPIO_PinSource15', 'GPIO_ETH_MediaInterface_MII', 'GPIO_ETH_MediaInterface_RMII',
    'GPIO_InitTypeDef', 'DMA_DIR_PeripheralDST', 'DMA_DIR_PeripheralSRC',
    'DMA_PeripheralInc_Enable', 'DMA_PeripheralInc_Disable', 'DMA_MemoryInc_Enable',
    'DMA_MemoryInc_Disable', 'DMA_PeripheralDataSize_Byte',
    'DMA_PeripheralDataSize_HalfWord', 'DMA_PeripheralDataSize_Word',
    'DMA_MemoryDataSize_Byte', 'DMA_MemoryDataSize_HalfWord', 'DMA_MemoryDataSize_Word',
    'DMA_Mode_Circular', 'DMA_Mode_Normal', 'DMA_Priority_VeryHigh',
    'DMA_Priority_High', 'DMA_Priority_Medium', 'DMA_Priority_Low', 'DMA_M2M_Enable',
    'DMA_M2M_Disable', 'DMA_IT_TC', 'DMA_IT_HT', 'DMA_IT_TE', 'DMA1_IT_GL1',
    'DMA1_IT_TC1', 'DMA1_IT_HT1', 'DMA1_IT_TE1', 'DMA1_IT_GL2', 'DMA1_IT_TC2',
    'DMA1_IT_HT2', 'DMA1_IT_TE2', 'DMA1_IT_GL3', 'DMA1_IT_TC3', 'DMA1_IT_HT3',
    'DMA1_IT_TE3', 'DMA1_IT_GL4', 'DMA1_IT_TC4', 'DMA1_IT_HT4', 'DMA1_IT_TE4',
    'DMA1_IT_GL5', 'DMA1_IT_TC5', 'DMA1_IT_HT5', 'DMA1_IT_TE5', 'DMA1_IT_GL6',
    'DMA1_IT_TC6', 'DMA1_IT_HT6', 'DMA1_IT_TE6', 'DMA1_IT_GL7', 'DMA1_IT_TC7',
    'DMA1_IT_HT7', 'DMA1_IT_TE7', 'DMA2_IT_GL1', 'DMA2_IT_TC1', 'DMA2_IT_HT1',
    'DMA2_IT_TE1', 'DMA2_IT_GL2', 'DMA2_IT_TC2', 'DMA2_IT_HT2', 'DMA2_IT_TE2',
    'DMA2_IT_GL3', 'DMA2_IT_TC3', 'DMA2_IT_HT3', 'DMA2_IT_TE3', 'DMA2_IT_GL4',
    'DMA2_IT_TC4', 'DMA2_IT_HT4', 'DMA2_IT_TE4', 'DMA2_IT_GL5', 'DMA2_IT_TC5',
    'DMA2_IT_HT5', 'DMA2_IT_TE5', 'DMA1_FLAG_GL1', 'DMA1_FLAG_TC1', 'DMA1_FLAG_HT1',
    'DMA1_FLAG_TE1', 'DMA1_FLAG_GL2', 'DMA1_FLAG_TC2', 'DMA1_FLAG_HT2', 'DMA1_FLAG_TE2',
    'DMA1_FLAG_GL3', 'DMA1_FLAG_TC3', 'DMA1_FLAG_HT3', 'DMA1_FLAG_TE3', 'DMA1_FLAG_GL4',
    'DMA1_FLAG_TC4', 'DMA1_FLAG_HT4', 'DMA1_FLAG_TE4', 'DMA1_FLAG_GL5', 'DMA1_FLAG_TC5',
    'DMA1_FLAG_HT5', 'DMA1_FLAG_TE5', 'DMA1_FLAG_GL6', 'DMA1_FLAG_TC6', 'DMA1_FLAG_HT6',
    'DMA1_FLAG_TE6', 'DMA1_FLAG_GL7', 'DMA1_FLAG_TC7', 'DMA1_FLAG_HT7', 'DMA1_FLAG_TE7',
    'DMA2_FLAG_GL1', 'DMA2_FLAG_TC1', 'DMA2_FLAG_HT1', 'DMA2_FLAG_TE1', 'DMA2_FLAG_GL2',
    'DMA2_FLAG_TC2', 'DMA2_FLAG_HT2', 'DMA2_FLAG_TE2', 'DMA2_FLAG_GL3', 'DMA2_FLAG_TC3',
    'DMA2_FLAG_HT3', 'DMA2_FLAG_TE3', 'DMA2_FLAG_GL4', 'DMA2_FLAG_TC4', 'DMA2_FLAG_HT4',
    'DMA2_FLAG_TE4', 'DMA2_FLAG_GL5', 'DMA2_FLAG_TC5', 'DMA2_FLAG_HT5', 'DMA2_FLAG_TE5',
    'DMA_InitTypeDef', 'I2C_Mode_I2C', 'I2C_Mode_SMBusDevice', 'I2C_Mode_SMBusHost',
    'I2C_DutyCycle_16_9', 'I2C_DutyCycle_2', 'I2C_Ack_Enable', 'I2C_Ack_Disable',
    'I2C_Direction_Transmitter', 'I2C_Direction_Receiver',
    'I2C_AcknowledgedAddress_7bit', 'I2C_AcknowledgedAddress_10bit', 'I2C_Register_CR1',
    'I2C_Register_CR2', 'I2C_Register_OAR1', 'I2C_Register_OAR2', 'I2C_Register_DR',
    'I2C_Register_SR1', 'I2C_Register_SR2', 'I2C_Register_CCR', 'I2C_Register_TRISE',
    'I2C_SMBusAlert_Low', 'I2C_SMBusAlert_High', 'I2C_PECPosition_Next',
    'I2C_PECPosition_Current', 'I2C_NACKPosition_Next', 'I2C_NACKPosition_Current',
    'I2C_IT_BUF', 'I2C_IT_EVT', 'I2C_IT_ERR', 'I2C_IT_SMBALERT', 'I2C_IT_TIMEOUT',
    'I2C_IT_PECERR', 'I2C_IT_OVR', 'I2C_IT_AF', 'I2C_IT_ARLO', 'I2C_IT_BERR',
    'I2C_IT_TXE', 'I2C_IT_RXNE', 'I2C_IT_STOPF', 'I2C_IT_ADD10', 'I2C_IT_BTF',
    'I2C_IT_ADDR', 'I2C_IT_SB', 'I2C_FLAG_DUALF', 'I2C_FLAG_SMBHOST',
    'I2C_FLAG_SMBDEFAULT', 'I2C_FLAG_GENCALL', 'I2C_FLAG_TRA', 'I2C_FLAG_BUSY',
    'I2C_FLAG_MSL', 'I2C_FLAG_SMBALERT', 'I2C_FLAG_TIMEOUT', 'I2C_FLAG_PECERR',
    'I2C_FLAG_OVR', 'I2C_FLAG_AF', 'I2C_FLAG_ARLO', 'I2C_FLAG_BERR', 'I2C_FLAG_TXE',
    'I2C_FLAG_RXNE', 'I2C_FLAG_STOPF', 'I2C_FLAG_ADD10', 'I2C_FLAG_BTF',
    'I2C_FLAG_ADDR', 'I2C_FLAG_SB', 'I2C_EVENT_MASTER_MODE_SELECT',
    'I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED',
    'I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED', 'I2C_EVENT_MASTER_MODE_ADDRESS10',
    'I2C_EVENT_MASTER_BYTE_RECEIVED', 'I2C_EVENT_MASTER_BYTE_TRANSMITTING',
    'I2C_EVENT_MASTER_BYTE_TRANSMITTED', 'I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED',
    'I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED',
    'I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED',
    'I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED',
    'I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED', 'I2C_EVENT_SLAVE_BYTE_RECEIVED',
    'I2C_EVENT_SLAVE_STOP_DETECTED', 'I2C_EVENT_SLAVE_BYTE_TRANSMITTED',
    'I2C_EVENT_SLAVE_BYTE_TRANSMITTING', 'I2C_EVENT_SLAVE_ACK_FAILURE',
    'I2C_InitTypeDef', 'FLASH_BUSY', 'FLASH_ERROR_PG', 'FLASH_ERROR_WRP',
    'FLASH_COMPLETE', 'FLASH_TIMEOUT', 'FLASH_Latency_0', 'FLASH_Latency_1',
    'FLASH_Latency_2', 'FLASH_HalfCycleAccess_Enable', 'FLASH_HalfCycleAccess_Disable',
    'FLASH_PrefetchBuffer_Enable', 'FLASH_PrefetchBuffer_Disable',
    'FLASH_WRProt_Pages0to3', 'FLASH_WRProt_Pages4to7', 'FLASH_WRProt_Pages8to11',
    'FLASH_WRProt_Pages12to15', 'FLASH_WRProt_Pages16to19', 'FLASH_WRProt_Pages20to23',
    'FLASH_WRProt_Pages24to27', 'FLASH_WRProt_Pages28to31', 'FLASH_WRProt_Pages32to35',
    'FLASH_WRProt_Pages36to39', 'FLASH_WRProt_Pages40to43', 'FLASH_WRProt_Pages44to47',
    'FLASH_WRProt_Pages48to51', 'FLASH_WRProt_Pages52to55', 'FLASH_WRProt_Pages56to59',
    'FLASH_WRProt_Pages60to63', 'FLASH_WRProt_Pages64to67', 'FLASH_WRProt_Pages68to71',
    'FLASH_WRProt_Pages72to75', 'FLASH_WRProt_Pages76to79', 'FLASH_WRProt_Pages80to83',
    'FLASH_WRProt_Pages84to87', 'FLASH_WRProt_Pages88to91', 'FLASH_WRProt_Pages92to95',
    'FLASH_WRProt_Pages96to99', 'FLASH_WRProt_Pages100to103',
    'FLASH_WRProt_Pages104to107', 'FLASH_WRProt_Pages108to111',
    'FLASH_WRProt_Pages112to115', 'FLASH_WRProt_Pages116to119',
    'FLASH_WRProt_Pages120to123', 'FLASH_WRProt_Pages124to127',
    'FLASH_WRProt_Pages0to1', 'FLASH_WRProt_Pages2to3', 'FLASH_WRProt_Pages4to5',
    'FLASH_WRProt_Pages6to7', 'FLASH_WRProt_Pages8to9', 'FLASH_WRProt_Pages10to11',
    'FLASH_WRProt_Pages12to13', 'FLASH_WRProt_Pages14to15', 'FLASH_WRProt_Pages16to17',
    'FLASH_WRProt_Pages18to19', 'FLASH_WRProt_Pages20to21', 'FLASH_WRProt_Pages22to23',
    'FLASH_WRProt_Pages24to25', 'FLASH_WRProt_Pages26to27', 'FLASH_WRProt_Pages28to29',
    'FLASH_WRProt_Pages30to31', 'FLASH_WRProt_Pages32to33', 'FLASH_WRProt_Pages34to35',
    'FLASH_WRProt_Pages36to37', 'FLASH_WRProt_Pages38to39', 'FLASH_WRProt_Pages40to41',
    'FLASH_WRProt_Pages42to43', 'FLASH_WRProt_Pages44to45', 'FLASH_WRProt_Pages46to47',
    'FLASH_WRProt_Pages48to49', 'FLASH_WRProt_Pages50to51', 'FLASH_WRProt_Pages52to53',
    'FLASH_WRProt_Pages54to55', 'FLASH_WRProt_Pages56to57', 'FLASH_WRProt_Pages58to59',
    'FLASH_WRProt_Pages60to61', 'FLASH_WRProt_Pages62to127',
    'FLASH_WRProt_Pages62to255', 'FLASH_WRProt_Pages62to511', 'FLASH_WRProt_AllPages',
    'OB_IWDG_SW', 'OB_IWDG_HW', 'OB_STOP_NoRST', 'OB_STOP_RST', 'OB_STDBY_NoRST',
    'OB_STDBY_RST', 'FLASH_IT_BANK1_ERROR', 'FLASH_IT_BANK1_EOP', 'FLASH_IT_ERROR',
    'FLASH_IT_EOP', 'FLASH_IT_ERROR', 'FLASH_IT_EOP', 'FLASH_IT_BANK1_ERROR',
    'FLASH_IT_BANK1_EOP', 'FLASH_FLAG_BANK1_BSY', 'FLASH_FLAG_BANK1_EOP',
    'FLASH_FLAG_BANK1_PGERR', 'FLASH_FLAG_BANK1_WRPRTERR', 'FLASH_FLAG_BSY',
    'FLASH_FLAG_EOP', 'FLASH_FLAG_PGERR', 'FLASH_FLAG_WRPRTERR', 'FLASH_FLAG_OPTERR',
    'FLASH_FLAG_BSY', 'FLASH_FLAG_EOP', 'FLASH_FLAG_PGERR', 'FLASH_FLAG_WRPRTERR',
    'FLASH_FLAG_OPTERR', 'FLASH_FLAG_BANK1_BSY', 'FLASH_FLAG_BANK1_EOP',
    'FLASH_FLAG_BANK1_PGERR', 'FLASH_FLAG_BANK1_WRPRTERR', 'DAC_Trigger_None',
    'DAC_Trigger_T6_TRGO', 'DAC_Trigger_T8_TRGO', 'DAC_Trigger_T3_TRGO',
    'DAC_Trigger_T7_TRGO', 'DAC_Trigger_T5_TRGO', 'DAC_Trigger_T15_TRGO',
    'DAC_Trigger_T2_TRGO', 'DAC_Trigger_T4_TRGO', 'DAC_Trigger_Ext_IT9',
    'DAC_Trigger_Software', 'DAC_WaveGeneration_None', 'DAC_WaveGeneration_Noise',
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
    'DAC_Align_8b_R', 'DAC_Wave_Noise', 'DAC_Wave_Triangle', 'DAC_InitTypeDef',
    'CEC_BitTimingStdMode', 'CEC_BitTimingErrFreeMode', 'CEC_BitPeriodStdMode',
    'CEC_BitPeriodFlexibleMode', 'CEC_IT_TERR', 'CEC_IT_TBTRF', 'CEC_IT_RERR',
    'CEC_IT_RBTF', 'CEC_FLAG_BTE', 'CEC_FLAG_BPE', 'CEC_FLAG_RBTFE', 'CEC_FLAG_SBE',
    'CEC_FLAG_ACKE', 'CEC_FLAG_LINE', 'CEC_FLAG_TBTFE', 'CEC_FLAG_TEOM',
    'CEC_FLAG_TERR', 'CEC_FLAG_TBTRF', 'CEC_FLAG_RSOM', 'CEC_FLAG_REOM',
    'CEC_FLAG_RERR', 'CEC_FLAG_RBTF', 'CEC_InitTypeDef', 'WWDG_Prescaler_1',
    'WWDG_Prescaler_2', 'WWDG_Prescaler_4', 'WWDG_Prescaler_8', 'TIM_OCMode_Timing',
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
    'TIM_DMABase_BDTR', 'TIM_DMABase_DCR', 'TIM_DMABurstLength_1Transfer',
    'TIM_DMABurstLength_2Transfers', 'TIM_DMABurstLength_3Transfers',
    'TIM_DMABurstLength_4Transfers', 'TIM_DMABurstLength_5Transfers',
    'TIM_DMABurstLength_6Transfers', 'TIM_DMABurstLength_7Transfers',
    'TIM_DMABurstLength_8Transfers', 'TIM_DMABurstLength_9Transfers',
    'TIM_DMABurstLength_10Transfers', 'TIM_DMABurstLength_11Transfers',
    'TIM_DMABurstLength_12Transfers', 'TIM_DMABurstLength_13Transfers',
    'TIM_DMABurstLength_14Transfers', 'TIM_DMABurstLength_15Transfers',
    'TIM_DMABurstLength_16Transfers', 'TIM_DMABurstLength_17Transfers',
    'TIM_DMABurstLength_18Transfers', 'TIM_DMA_Update', 'TIM_DMA_CC1', 'TIM_DMA_CC2',
    'TIM_DMA_CC3', 'TIM_DMA_CC4', 'TIM_DMA_COM', 'TIM_DMA_Trigger', 'TIM_ExtTRGPSC_OFF',
    'TIM_ExtTRGPSC_DIV2', 'TIM_ExtTRGPSC_DIV4', 'TIM_ExtTRGPSC_DIV8', 'TIM_TS_ITR0',
    'TIM_TS_ITR1', 'TIM_TS_ITR2', 'TIM_TS_ITR3', 'TIM_TS_TI1F_ED', 'TIM_TS_TI1FP1',
    'TIM_TS_TI2FP2', 'TIM_TS_ETRF', 'TIM_TIxExternalCLK1Source_TI1',
    'TIM_TIxExternalCLK1Source_TI2', 'TIM_TIxExternalCLK1Source_TI1ED',
    'TIM_ExtTRGPolarity_Inverted', 'TIM_ExtTRGPolarity_NonInverted',
    'TIM_PSCReloadMode_Update', 'TIM_PSCReloadMode_Immediate',
    'TIM_ForcedAction_Active', 'TIM_ForcedAction_InActive', 'TIM_EncoderMode_TI1',
    'TIM_EncoderMode_TI2', 'TIM_EncoderMode_TI12', 'TIM_EventSource_Update',
    'TIM_EventSource_CC1', 'TIM_EventSource_CC2', 'TIM_EventSource_CC3',
    'TIM_EventSource_CC4', 'TIM_EventSource_COM', 'TIM_EventSource_Trigger',
    'TIM_EventSource_Break', 'TIM_UpdateSource_Global', 'TIM_UpdateSource_Regular',
    'TIM_OCPreload_Enable', 'TIM_OCPreload_Disable', 'TIM_OCFast_Enable',
    'TIM_OCFast_Disable', 'TIM_OCClear_Enable', 'TIM_OCClear_Disable',
    'TIM_TRGOSource_Reset', 'TIM_TRGOSource_Enable', 'TIM_TRGOSource_Update',
    'TIM_TRGOSource_OC1', 'TIM_TRGOSource_OC1Ref', 'TIM_TRGOSource_OC2Ref',
    'TIM_TRGOSource_OC3Ref', 'TIM_TRGOSource_OC4Ref', 'TIM_SlaveMode_Reset',
    'TIM_SlaveMode_Gated', 'TIM_SlaveMode_Trigger', 'TIM_SlaveMode_External1',
    'TIM_MasterSlaveMode_Enable', 'TIM_MasterSlaveMode_Disable', 'TIM_FLAG_Update',
    'TIM_FLAG_CC1', 'TIM_FLAG_CC2', 'TIM_FLAG_CC3', 'TIM_FLAG_CC4', 'TIM_FLAG_COM',
    'TIM_FLAG_Trigger', 'TIM_FLAG_Break', 'TIM_FLAG_CC1OF', 'TIM_FLAG_CC2OF',
    'TIM_FLAG_CC3OF', 'TIM_FLAG_CC4OF', 'TIM_DMABurstLength_1Byte',
    'TIM_DMABurstLength_2Bytes', 'TIM_DMABurstLength_3Bytes',
    'TIM_DMABurstLength_4Bytes', 'TIM_DMABurstLength_5Bytes',
    'TIM_DMABurstLength_6Bytes', 'TIM_DMABurstLength_7Bytes',
    'TIM_DMABurstLength_8Bytes', 'TIM_DMABurstLength_9Bytes',
    'TIM_DMABurstLength_10Bytes', 'TIM_DMABurstLength_11Bytes',
    'TIM_DMABurstLength_12Bytes', 'TIM_DMABurstLength_13Bytes',
    'TIM_DMABurstLength_14Bytes', 'TIM_DMABurstLength_15Bytes',
    'TIM_DMABurstLength_16Bytes', 'TIM_DMABurstLength_17Bytes',
    'TIM_DMABurstLength_18Bytes', 'TIM_TimeBaseInitTypeDef', 'TIM_OCInitTypeDef',
    'TIM_ICInitTypeDef', 'TIM_BDTRInitTypeDef', 'RCC_HSE_OFF', 'RCC_HSE_ON',
    'RCC_HSE_Bypass', 'RCC_PLLSource_HSI_Div2', 'RCC_PLLSource_HSE_Div1',
    'RCC_PLLSource_HSE_Div2', 'RCC_PLLMul_2', 'RCC_PLLMul_3', 'RCC_PLLMul_4',
    'RCC_PLLMul_5', 'RCC_PLLMul_6', 'RCC_PLLMul_7', 'RCC_PLLMul_8', 'RCC_PLLMul_9',
    'RCC_PLLMul_10', 'RCC_PLLMul_11', 'RCC_PLLMul_12', 'RCC_PLLMul_13', 'RCC_PLLMul_14',
    'RCC_PLLMul_15', 'RCC_PLLMul_16', 'RCC_PLLMul_4', 'RCC_PLLMul_5', 'RCC_PLLMul_6',
    'RCC_PLLMul_7', 'RCC_PLLMul_8', 'RCC_PLLMul_9', 'RCC_SYSCLKSource_HSI',
    'RCC_SYSCLKSource_HSE', 'RCC_SYSCLKSource_PLLCLK', 'RCC_SYSCLK_Div1',
    'RCC_SYSCLK_Div2', 'RCC_SYSCLK_Div4', 'RCC_SYSCLK_Div8', 'RCC_SYSCLK_Div16',
    'RCC_SYSCLK_Div64', 'RCC_SYSCLK_Div128', 'RCC_SYSCLK_Div256', 'RCC_SYSCLK_Div512',
    'RCC_HCLK_Div1', 'RCC_HCLK_Div2', 'RCC_HCLK_Div4', 'RCC_HCLK_Div8',
    'RCC_HCLK_Div16', 'RCC_IT_LSIRDY', 'RCC_IT_LSERDY', 'RCC_IT_HSIRDY',
    'RCC_IT_HSERDY', 'RCC_IT_PLLRDY', 'RCC_IT_CSS', 'RCC_USBCLKSource_PLLCLK_1Div5',
    'RCC_USBCLKSource_PLLCLK_Div1', 'RCC_PCLK2_Div2', 'RCC_PCLK2_Div4',
    'RCC_PCLK2_Div6', 'RCC_PCLK2_Div8', 'RCC_LSE_OFF', 'RCC_LSE_ON', 'RCC_LSE_Bypass',
    'RCC_RTCCLKSource_LSE', 'RCC_RTCCLKSource_LSI', 'RCC_RTCCLKSource_HSE_Div128',
    'RCC_AHBPeriph_DMA1', 'RCC_AHBPeriph_DMA2', 'RCC_AHBPeriph_SRAM',
    'RCC_AHBPeriph_FLITF', 'RCC_AHBPeriph_CRC', 'RCC_AHBPeriph_FSMC',
    'RCC_AHBPeriph_SDIO', 'RCC_APB2Periph_AFIO', 'RCC_APB2Periph_GPIOA',
    'RCC_APB2Periph_GPIOB', 'RCC_APB2Periph_GPIOC', 'RCC_APB2Periph_GPIOD',
    'RCC_APB2Periph_GPIOE', 'RCC_APB2Periph_GPIOF', 'RCC_APB2Periph_GPIOG',
    'RCC_APB2Periph_ADC1', 'RCC_APB2Periph_ADC2', 'RCC_APB2Periph_TIM1',
    'RCC_APB2Periph_SPI1', 'RCC_APB2Periph_TIM8', 'RCC_APB2Periph_USART1',
    'RCC_APB2Periph_ADC3', 'RCC_APB2Periph_TIM15', 'RCC_APB2Periph_TIM16',
    'RCC_APB2Periph_TIM17', 'RCC_APB2Periph_TIM9', 'RCC_APB2Periph_TIM10',
    'RCC_APB2Periph_TIM11', 'RCC_APB1Periph_TIM2', 'RCC_APB1Periph_TIM3',
    'RCC_APB1Periph_TIM4', 'RCC_APB1Periph_TIM5', 'RCC_APB1Periph_TIM6',
    'RCC_APB1Periph_TIM7', 'RCC_APB1Periph_TIM12', 'RCC_APB1Periph_TIM13',
    'RCC_APB1Periph_TIM14', 'RCC_APB1Periph_WWDG', 'RCC_APB1Periph_SPI2',
    'RCC_APB1Periph_SPI3', 'RCC_APB1Periph_USART2', 'RCC_APB1Periph_USART3',
    'RCC_APB1Periph_UART4', 'RCC_APB1Periph_UART5', 'RCC_APB1Periph_I2C1',
    'RCC_APB1Periph_I2C2', 'RCC_APB1Periph_USB', 'RCC_APB1Periph_CAN1',
    'RCC_APB1Periph_CAN2', 'RCC_APB1Periph_BKP', 'RCC_APB1Periph_PWR',
    'RCC_APB1Periph_DAC', 'RCC_APB1Periph_CEC', 'RCC_MCO_NoClock', 'RCC_MCO_SYSCLK',
    'RCC_MCO_HSI', 'RCC_MCO_HSE', 'RCC_MCO_PLLCLK_Div2', 'RCC_FLAG_HSIRDY',
    'RCC_FLAG_HSERDY', 'RCC_FLAG_PLLRDY', 'RCC_FLAG_LSERDY', 'RCC_FLAG_LSIRDY',
    'RCC_FLAG_PINRST', 'RCC_FLAG_PORRST', 'RCC_FLAG_SFTRST', 'RCC_FLAG_IWDGRST',
    'RCC_FLAG_WWDGRST', 'RCC_FLAG_LPWRRST', 'RCC_ClocksTypeDef',
    'SDIO_ClockEdge_Rising', 'SDIO_ClockEdge_Falling', 'SDIO_ClockBypass_Disable',
    'SDIO_ClockBypass_Enable', 'SDIO_ClockPowerSave_Disable',
    'SDIO_ClockPowerSave_Enable', 'SDIO_BusWide_1b', 'SDIO_BusWide_4b',
    'SDIO_BusWide_8b', 'SDIO_HardwareFlowControl_Disable',
    'SDIO_HardwareFlowControl_Enable', 'SDIO_PowerState_OFF', 'SDIO_PowerState_ON',
    'SDIO_IT_CCRCFAIL', 'SDIO_IT_DCRCFAIL', 'SDIO_IT_CTIMEOUT', 'SDIO_IT_DTIMEOUT',
    'SDIO_IT_TXUNDERR', 'SDIO_IT_RXOVERR', 'SDIO_IT_CMDREND', 'SDIO_IT_CMDSENT',
    'SDIO_IT_DATAEND', 'SDIO_IT_STBITERR', 'SDIO_IT_DBCKEND', 'SDIO_IT_CMDACT',
    'SDIO_IT_TXACT', 'SDIO_IT_RXACT', 'SDIO_IT_TXFIFOHE', 'SDIO_IT_RXFIFOHF',
    'SDIO_IT_TXFIFOF', 'SDIO_IT_RXFIFOF', 'SDIO_IT_TXFIFOE', 'SDIO_IT_RXFIFOE',
    'SDIO_IT_TXDAVL', 'SDIO_IT_RXDAVL', 'SDIO_IT_SDIOIT', 'SDIO_IT_CEATAEND',
    'SDIO_Response_No', 'SDIO_Response_Short', 'SDIO_Response_Long', 'SDIO_Wait_No',
    'SDIO_Wait_IT', 'SDIO_Wait_Pend', 'SDIO_CPSM_Disable', 'SDIO_CPSM_Enable',
    'SDIO_RESP1', 'SDIO_RESP2', 'SDIO_RESP3', 'SDIO_RESP4', 'SDIO_DataBlockSize_1b',
    'SDIO_DataBlockSize_2b', 'SDIO_DataBlockSize_4b', 'SDIO_DataBlockSize_8b',
    'SDIO_DataBlockSize_16b', 'SDIO_DataBlockSize_32b', 'SDIO_DataBlockSize_64b',
    'SDIO_DataBlockSize_128b', 'SDIO_DataBlockSize_256b', 'SDIO_DataBlockSize_512b',
    'SDIO_DataBlockSize_1024b', 'SDIO_DataBlockSize_2048b', 'SDIO_DataBlockSize_4096b',
    'SDIO_DataBlockSize_8192b', 'SDIO_DataBlockSize_16384b', 'SDIO_TransferDir_ToCard',
    'SDIO_TransferDir_ToSDIO', 'SDIO_TransferMode_Block', 'SDIO_TransferMode_Stream',
    'SDIO_DPSM_Disable', 'SDIO_DPSM_Enable', 'SDIO_FLAG_CCRCFAIL', 'SDIO_FLAG_DCRCFAIL',
    'SDIO_FLAG_CTIMEOUT', 'SDIO_FLAG_DTIMEOUT', 'SDIO_FLAG_TXUNDERR',
    'SDIO_FLAG_RXOVERR', 'SDIO_FLAG_CMDREND', 'SDIO_FLAG_CMDSENT', 'SDIO_FLAG_DATAEND',
    'SDIO_FLAG_STBITERR', 'SDIO_FLAG_DBCKEND', 'SDIO_FLAG_CMDACT', 'SDIO_FLAG_TXACT',
    'SDIO_FLAG_RXACT', 'SDIO_FLAG_TXFIFOHE', 'SDIO_FLAG_RXFIFOHF', 'SDIO_FLAG_TXFIFOF',
    'SDIO_FLAG_RXFIFOF', 'SDIO_FLAG_TXFIFOE', 'SDIO_FLAG_RXFIFOE', 'SDIO_FLAG_TXDAVL',
    'SDIO_FLAG_RXDAVL', 'SDIO_FLAG_SDIOIT', 'SDIO_FLAG_CEATAEND',
    'SDIO_ReadWaitMode_CLK', 'SDIO_ReadWaitMode_DATA2', 'SDIO_InitTypeDef',
    'SDIO_CmdInitTypeDef', 'SDIO_DataInitTypeDef', 'RESET', 'SET', 'DISABLE', 'ENABLE',
    'ERROR', 'SUCCESS', 'HSE_VALUE', 'HSE_VALUE', 'HSE_STARTUP_TIMEOUT', 'HSI_VALUE',
    '__STM32F10X_STDPERIPH_VERSION_MAIN', '__STM32F10X_STDPERIPH_VERSION_SUB1',
    '__STM32F10X_STDPERIPH_VERSION_SUB2', '__STM32F10X_STDPERIPH_VERSION_RC',
    '__STM32F10X_STDPERIPH_VERSION', '__MPU_PRESENT', '__MPU_PRESENT',
    '__NVIC_PRIO_BITS', '__Vendor_SysTickConfig', 'HSEStartUp_TimeOut', 'HSE_Value',
    'HSI_Value', 'FLASH_BASE', 'SRAM_BASE', 'PERIPH_BASE', 'SRAM_BB_BASE',
    'PERIPH_BB_BASE', 'FSMC_R_BASE', 'APB1PERIPH_BASE', 'APB2PERIPH_BASE',
    'AHBPERIPH_BASE', 'TIM2_BASE', 'TIM3_BASE', 'TIM4_BASE', 'TIM5_BASE', 'TIM6_BASE',
    'TIM7_BASE', 'TIM12_BASE', 'TIM13_BASE', 'TIM14_BASE', 'RTC_BASE', 'WWDG_BASE',
    'IWDG_BASE', 'SPI2_BASE', 'SPI3_BASE', 'USART2_BASE', 'USART3_BASE', 'UART4_BASE',
    'UART5_BASE', 'I2C1_BASE', 'I2C2_BASE', 'CAN1_BASE', 'CAN2_BASE', 'BKP_BASE',
    'PWR_BASE', 'DAC_BASE', 'CEC_BASE', 'AFIO_BASE', 'EXTI_BASE', 'GPIOA_BASE',
    'GPIOB_BASE', 'GPIOC_BASE', 'GPIOD_BASE', 'GPIOE_BASE', 'GPIOF_BASE', 'GPIOG_BASE',
    'ADC1_BASE', 'ADC2_BASE', 'TIM1_BASE', 'SPI1_BASE', 'TIM8_BASE', 'USART1_BASE',
    'ADC3_BASE', 'TIM15_BASE', 'TIM16_BASE', 'TIM17_BASE', 'TIM9_BASE', 'TIM10_BASE',
    'TIM11_BASE', 'SDIO_BASE', 'DMA1_BASE', 'DMA1_Channel1_BASE', 'DMA1_Channel2_BASE',
    'DMA1_Channel3_BASE', 'DMA1_Channel4_BASE', 'DMA1_Channel5_BASE',
    'DMA1_Channel6_BASE', 'DMA1_Channel7_BASE', 'DMA2_BASE', 'DMA2_Channel1_BASE',
    'DMA2_Channel2_BASE', 'DMA2_Channel3_BASE', 'DMA2_Channel4_BASE',
    'DMA2_Channel5_BASE', 'RCC_BASE', 'CRC_BASE', 'FLASH_R_BASE', 'OB_BASE', 'ETH_BASE',
    'ETH_MAC_BASE', 'ETH_MMC_BASE', 'ETH_PTP_BASE', 'ETH_DMA_BASE', 'FSMC_Bank1_R_BASE',
    'FSMC_Bank1E_R_BASE', 'FSMC_Bank2_R_BASE', 'FSMC_Bank3_R_BASE', 'FSMC_Bank4_R_BASE',
    'DBGMCU_BASE', 'TIM2', 'TIM3', 'TIM4', 'TIM5', 'TIM6', 'TIM7', 'TIM12', 'TIM13',
    'TIM14', 'RTC', 'WWDG', 'IWDG', 'SPI2', 'SPI3', 'USART2', 'USART3', 'UART4',
    'UART5', 'I2C1', 'I2C2', 'CAN1', 'CAN2', 'BKP', 'PWR', 'DAC', 'CEC', 'AFIO', 'EXTI',
    'GPIOA', 'GPIOB', 'GPIOC', 'GPIOD', 'GPIOE', 'GPIOF', 'GPIOG', 'ADC1', 'ADC2',
    'TIM1', 'SPI1', 'TIM8', 'USART1', 'ADC3', 'TIM15', 'TIM16', 'TIM17', 'TIM9',
    'TIM10', 'TIM11', 'SDIO', 'DMA1', 'DMA2', 'DMA1_Channel1', 'DMA1_Channel2',
    'DMA1_Channel3', 'DMA1_Channel4', 'DMA1_Channel5', 'DMA1_Channel6', 'DMA1_Channel7',
    'DMA2_Channel1', 'DMA2_Channel2', 'DMA2_Channel3', 'DMA2_Channel4', 'DMA2_Channel5',
    'RCC', 'CRC', 'FLASH', 'OB', 'ETH', 'FSMC_Bank1', 'FSMC_Bank1E', 'FSMC_Bank2',
    'FSMC_Bank3', 'FSMC_Bank4', 'DBGMCU', 'CRC_DR_DR', 'CRC_IDR_IDR', 'CRC_CR_RESET',
    'PWR_CR_LPDS', 'PWR_CR_PDDS', 'PWR_CR_CWUF', 'PWR_CR_CSBF', 'PWR_CR_PVDE',
    'PWR_CR_PLS', 'PWR_CR_PLS_0', 'PWR_CR_PLS_1', 'PWR_CR_PLS_2', 'PWR_CR_PLS_2V2',
    'PWR_CR_PLS_2V3', 'PWR_CR_PLS_2V4', 'PWR_CR_PLS_2V5', 'PWR_CR_PLS_2V6',
    'PWR_CR_PLS_2V7', 'PWR_CR_PLS_2V8', 'PWR_CR_PLS_2V9', 'PWR_CR_DBP', 'PWR_CSR_WUF',
    'PWR_CSR_SBF', 'PWR_CSR_PVDO', 'PWR_CSR_EWUP', 'BKP_DR1_D', 'BKP_DR2_D',
    'BKP_DR3_D', 'BKP_DR4_D', 'BKP_DR5_D', 'BKP_DR6_D', 'BKP_DR7_D', 'BKP_DR8_D',
    'BKP_DR9_D', 'BKP_DR10_D', 'BKP_DR11_D', 'BKP_DR12_D', 'BKP_DR13_D', 'BKP_DR14_D',
    'BKP_DR15_D', 'BKP_DR16_D', 'BKP_DR17_D', 'BKP_DR18_D', 'BKP_DR19_D', 'BKP_DR20_D',
    'BKP_DR21_D', 'BKP_DR22_D', 'BKP_DR23_D', 'BKP_DR24_D', 'BKP_DR25_D', 'BKP_DR26_D',
    'BKP_DR27_D', 'BKP_DR28_D', 'BKP_DR29_D', 'BKP_DR30_D', 'BKP_DR31_D', 'BKP_DR32_D',
    'BKP_DR33_D', 'BKP_DR34_D', 'BKP_DR35_D', 'BKP_DR36_D', 'BKP_DR37_D', 'BKP_DR38_D',
    'BKP_DR39_D', 'BKP_DR40_D', 'BKP_DR41_D', 'BKP_DR42_D', 'BKP_RTCCR_CAL',
    'BKP_RTCCR_CCO', 'BKP_RTCCR_ASOE', 'BKP_RTCCR_ASOS', 'BKP_CR_TPE', 'BKP_CR_TPAL',
    'BKP_CSR_CTE', 'BKP_CSR_CTI', 'BKP_CSR_TPIE', 'BKP_CSR_TEF', 'BKP_CSR_TIF',
    'RCC_CR_HSION', 'RCC_CR_HSIRDY', 'RCC_CR_HSITRIM', 'RCC_CR_HSICAL', 'RCC_CR_HSEON',
    'RCC_CR_HSERDY', 'RCC_CR_HSEBYP', 'RCC_CR_CSSON', 'RCC_CR_PLLON', 'RCC_CR_PLLRDY',
    'RCC_CFGR_SW', 'RCC_CFGR_SW_0', 'RCC_CFGR_SW_1', 'RCC_CFGR_SW_HSI',
    'RCC_CFGR_SW_HSE', 'RCC_CFGR_SW_PLL', 'RCC_CFGR_SWS', 'RCC_CFGR_SWS_0',
    'RCC_CFGR_SWS_1', 'RCC_CFGR_SWS_HSI', 'RCC_CFGR_SWS_HSE', 'RCC_CFGR_SWS_PLL',
    'RCC_CFGR_HPRE', 'RCC_CFGR_HPRE_0', 'RCC_CFGR_HPRE_1', 'RCC_CFGR_HPRE_2',
    'RCC_CFGR_HPRE_3', 'RCC_CFGR_HPRE_DIV1', 'RCC_CFGR_HPRE_DIV2', 'RCC_CFGR_HPRE_DIV4',
    'RCC_CFGR_HPRE_DIV8', 'RCC_CFGR_HPRE_DIV16', 'RCC_CFGR_HPRE_DIV64',
    'RCC_CFGR_HPRE_DIV128', 'RCC_CFGR_HPRE_DIV256', 'RCC_CFGR_HPRE_DIV512',
    'RCC_CFGR_PPRE1', 'RCC_CFGR_PPRE1_0', 'RCC_CFGR_PPRE1_1', 'RCC_CFGR_PPRE1_2',
    'RCC_CFGR_PPRE1_DIV1', 'RCC_CFGR_PPRE1_DIV2', 'RCC_CFGR_PPRE1_DIV4',
    'RCC_CFGR_PPRE1_DIV8', 'RCC_CFGR_PPRE1_DIV16', 'RCC_CFGR_PPRE2', 'RCC_CFGR_PPRE2_0',
    'RCC_CFGR_PPRE2_1', 'RCC_CFGR_PPRE2_2', 'RCC_CFGR_PPRE2_DIV1',
    'RCC_CFGR_PPRE2_DIV2', 'RCC_CFGR_PPRE2_DIV4', 'RCC_CFGR_PPRE2_DIV8',
    'RCC_CFGR_PPRE2_DIV16', 'RCC_CFGR_ADCPRE', 'RCC_CFGR_ADCPRE_0', 'RCC_CFGR_ADCPRE_1',
    'RCC_CFGR_ADCPRE_DIV2', 'RCC_CFGR_ADCPRE_DIV4', 'RCC_CFGR_ADCPRE_DIV6',
    'RCC_CFGR_ADCPRE_DIV8', 'RCC_CFGR_PLLSRC', 'RCC_CFGR_PLLXTPRE', 'RCC_CFGR_PLLMULL',
    'RCC_CFGR_PLLMULL_0', 'RCC_CFGR_PLLMULL_1', 'RCC_CFGR_PLLMULL_2',
    'RCC_CFGR_PLLMULL_3', 'RCC_CFGR_PLLSRC_HSI_Div2', 'RCC_CFGR_PLLMULL4',
    'RCC_CFGR_PLLMULL5', 'RCC_CFGR_PLLMULL6', 'RCC_CFGR_PLLMULL7', 'RCC_CFGR_PLLMULL8',
    'RCC_CFGR_PLLMULL9', 'RCC_CFGR_MCO', 'RCC_CFGR_MCO_0', 'RCC_CFGR_MCO_1',
    'RCC_CFGR_MCO_2', 'RCC_CFGR_MCO_NOCLOCK', 'RCC_CFGR_MCO_SYSCLK', 'RCC_CFGR_MCO_HSI',
    'RCC_CFGR_MCO_HSE', 'RCC_CFGR_PLLSRC_HSI_Div2', 'RCC_CFGR_PLLMULL2',
    'RCC_CFGR_PLLMULL3', 'RCC_CFGR_PLLMULL4', 'RCC_CFGR_PLLMULL5', 'RCC_CFGR_PLLMULL6',
    'RCC_CFGR_PLLMULL7', 'RCC_CFGR_PLLMULL8', 'RCC_CFGR_PLLMULL9', 'RCC_CFGR_PLLMULL10',
    'RCC_CFGR_PLLMULL11', 'RCC_CFGR_PLLMULL12', 'RCC_CFGR_PLLMULL13',
    'RCC_CFGR_PLLMULL14', 'RCC_CFGR_PLLMULL15', 'RCC_CFGR_PLLMULL16', 'RCC_CFGR_MCO',
    'RCC_CFGR_MCO_0', 'RCC_CFGR_MCO_1', 'RCC_CFGR_MCO_2', 'RCC_CFGR_MCO_NOCLOCK',
    'RCC_CFGR_MCO_SYSCLK', 'RCC_CFGR_MCO_HSI', 'RCC_CFGR_MCO_HSE', 'RCC_CFGR_MCO_PLL',
    'RCC_CFGR_PLLSRC_HSI_Div2', 'RCC_CFGR_PLLSRC_HSE', 'RCC_CFGR_PLLXTPRE_HSE',
    'RCC_CFGR_PLLXTPRE_HSE_Div2', 'RCC_CFGR_PLLMULL2', 'RCC_CFGR_PLLMULL3',
    'RCC_CFGR_PLLMULL4', 'RCC_CFGR_PLLMULL5', 'RCC_CFGR_PLLMULL6', 'RCC_CFGR_PLLMULL7',
    'RCC_CFGR_PLLMULL8', 'RCC_CFGR_PLLMULL9', 'RCC_CFGR_PLLMULL10',
    'RCC_CFGR_PLLMULL11', 'RCC_CFGR_PLLMULL12', 'RCC_CFGR_PLLMULL13',
    'RCC_CFGR_PLLMULL14', 'RCC_CFGR_PLLMULL15', 'RCC_CFGR_PLLMULL16', 'RCC_CFGR_USBPRE',
    'RCC_CFGR_MCO', 'RCC_CFGR_MCO_0', 'RCC_CFGR_MCO_1', 'RCC_CFGR_MCO_2',
    'RCC_CFGR_MCO_NOCLOCK', 'RCC_CFGR_MCO_SYSCLK', 'RCC_CFGR_MCO_HSI',
    'RCC_CFGR_MCO_HSE', 'RCC_CFGR_MCO_PLL', 'RCC_CIR_LSIRDYF', 'RCC_CIR_LSERDYF',
    'RCC_CIR_HSIRDYF', 'RCC_CIR_HSERDYF', 'RCC_CIR_PLLRDYF', 'RCC_CIR_CSSF',
    'RCC_CIR_LSIRDYIE', 'RCC_CIR_LSERDYIE', 'RCC_CIR_HSIRDYIE', 'RCC_CIR_HSERDYIE',
    'RCC_CIR_PLLRDYIE', 'RCC_CIR_LSIRDYC', 'RCC_CIR_LSERDYC', 'RCC_CIR_HSIRDYC',
    'RCC_CIR_HSERDYC', 'RCC_CIR_PLLRDYC', 'RCC_CIR_CSSC', 'RCC_APB2RSTR_AFIORST',
    'RCC_APB2RSTR_IOPARST', 'RCC_APB2RSTR_IOPBRST', 'RCC_APB2RSTR_IOPCRST',
    'RCC_APB2RSTR_IOPDRST', 'RCC_APB2RSTR_ADC1RST', 'RCC_APB2RSTR_ADC2RST',
    'RCC_APB2RSTR_TIM1RST', 'RCC_APB2RSTR_SPI1RST', 'RCC_APB2RSTR_USART1RST',
    'RCC_APB2RSTR_IOPERST', 'RCC_APB1RSTR_TIM2RST', 'RCC_APB1RSTR_TIM3RST',
    'RCC_APB1RSTR_WWDGRST', 'RCC_APB1RSTR_USART2RST', 'RCC_APB1RSTR_I2C1RST',
    'RCC_APB1RSTR_CAN1RST', 'RCC_APB1RSTR_BKPRST', 'RCC_APB1RSTR_PWRRST',
    'RCC_APB1RSTR_TIM4RST', 'RCC_APB1RSTR_SPI2RST', 'RCC_APB1RSTR_USART3RST',
    'RCC_APB1RSTR_I2C2RST', 'RCC_APB1RSTR_USBRST', 'RCC_AHBENR_DMA1EN',
    'RCC_AHBENR_SRAMEN', 'RCC_AHBENR_FLITFEN', 'RCC_AHBENR_CRCEN', 'RCC_APB2ENR_AFIOEN',
    'RCC_APB2ENR_IOPAEN', 'RCC_APB2ENR_IOPBEN', 'RCC_APB2ENR_IOPCEN',
    'RCC_APB2ENR_IOPDEN', 'RCC_APB2ENR_ADC1EN', 'RCC_APB2ENR_ADC2EN',
    'RCC_APB2ENR_TIM1EN', 'RCC_APB2ENR_SPI1EN', 'RCC_APB2ENR_USART1EN',
    'RCC_APB2ENR_IOPEEN', 'RCC_APB1ENR_TIM2EN', 'RCC_APB1ENR_TIM3EN',
    'RCC_APB1ENR_WWDGEN', 'RCC_APB1ENR_USART2EN', 'RCC_APB1ENR_I2C1EN',
    'RCC_APB1ENR_CAN1EN', 'RCC_APB1ENR_BKPEN', 'RCC_APB1ENR_PWREN',
    'RCC_APB1ENR_TIM4EN', 'RCC_APB1ENR_SPI2EN', 'RCC_APB1ENR_USART3EN',
    'RCC_APB1ENR_I2C2EN', 'RCC_APB1ENR_USBEN', 'RCC_BDCR_LSEON', 'RCC_BDCR_LSERDY',
    'RCC_BDCR_LSEBYP', 'RCC_BDCR_RTCSEL', 'RCC_BDCR_RTCSEL_0', 'RCC_BDCR_RTCSEL_1',
    'RCC_BDCR_RTCSEL_NOCLOCK', 'RCC_BDCR_RTCSEL_LSE', 'RCC_BDCR_RTCSEL_LSI',
    'RCC_BDCR_RTCSEL_HSE', 'RCC_BDCR_RTCEN', 'RCC_BDCR_BDRST', 'RCC_CSR_LSION',
    'RCC_CSR_LSIRDY', 'RCC_CSR_RMVF', 'RCC_CSR_PINRSTF', 'RCC_CSR_PORRSTF',
    'RCC_CSR_SFTRSTF', 'RCC_CSR_IWDGRSTF', 'RCC_CSR_WWDGRSTF', 'RCC_CSR_LPWRRSTF',
    'GPIO_CRL_MODE', 'GPIO_CRL_MODE0', 'GPIO_CRL_MODE0_0', 'GPIO_CRL_MODE0_1',
    'GPIO_CRL_MODE1', 'GPIO_CRL_MODE1_0', 'GPIO_CRL_MODE1_1', 'GPIO_CRL_MODE2',
    'GPIO_CRL_MODE2_0', 'GPIO_CRL_MODE2_1', 'GPIO_CRL_MODE3', 'GPIO_CRL_MODE3_0',
    'GPIO_CRL_MODE3_1', 'GPIO_CRL_MODE4', 'GPIO_CRL_MODE4_0', 'GPIO_CRL_MODE4_1',
    'GPIO_CRL_MODE5', 'GPIO_CRL_MODE5_0', 'GPIO_CRL_MODE5_1', 'GPIO_CRL_MODE6',
    'GPIO_CRL_MODE6_0', 'GPIO_CRL_MODE6_1', 'GPIO_CRL_MODE7', 'GPIO_CRL_MODE7_0',
    'GPIO_CRL_MODE7_1', 'GPIO_CRL_CNF', 'GPIO_CRL_CNF0', 'GPIO_CRL_CNF0_0',
    'GPIO_CRL_CNF0_1', 'GPIO_CRL_CNF1', 'GPIO_CRL_CNF1_0', 'GPIO_CRL_CNF1_1',
    'GPIO_CRL_CNF2', 'GPIO_CRL_CNF2_0', 'GPIO_CRL_CNF2_1', 'GPIO_CRL_CNF3',
    'GPIO_CRL_CNF3_0', 'GPIO_CRL_CNF3_1', 'GPIO_CRL_CNF4', 'GPIO_CRL_CNF4_0',
    'GPIO_CRL_CNF4_1', 'GPIO_CRL_CNF5', 'GPIO_CRL_CNF5_0', 'GPIO_CRL_CNF5_1',
    'GPIO_CRL_CNF6', 'GPIO_CRL_CNF6_0', 'GPIO_CRL_CNF6_1', 'GPIO_CRL_CNF7',
    'GPIO_CRL_CNF7_0', 'GPIO_CRL_CNF7_1', 'GPIO_CRH_MODE', 'GPIO_CRH_MODE8',
    'GPIO_CRH_MODE8_0', 'GPIO_CRH_MODE8_1', 'GPIO_CRH_MODE9', 'GPIO_CRH_MODE9_0',
    'GPIO_CRH_MODE9_1', 'GPIO_CRH_MODE10', 'GPIO_CRH_MODE10_0', 'GPIO_CRH_MODE10_1',
    'GPIO_CRH_MODE11', 'GPIO_CRH_MODE11_0', 'GPIO_CRH_MODE11_1', 'GPIO_CRH_MODE12',
    'GPIO_CRH_MODE12_0', 'GPIO_CRH_MODE12_1', 'GPIO_CRH_MODE13', 'GPIO_CRH_MODE13_0',
    'GPIO_CRH_MODE13_1', 'GPIO_CRH_MODE14', 'GPIO_CRH_MODE14_0', 'GPIO_CRH_MODE14_1',
    'GPIO_CRH_MODE15', 'GPIO_CRH_MODE15_0', 'GPIO_CRH_MODE15_1', 'GPIO_CRH_CNF',
    'GPIO_CRH_CNF8', 'GPIO_CRH_CNF8_0', 'GPIO_CRH_CNF8_1', 'GPIO_CRH_CNF9',
    'GPIO_CRH_CNF9_0', 'GPIO_CRH_CNF9_1', 'GPIO_CRH_CNF10', 'GPIO_CRH_CNF10_0',
    'GPIO_CRH_CNF10_1', 'GPIO_CRH_CNF11', 'GPIO_CRH_CNF11_0', 'GPIO_CRH_CNF11_1',
    'GPIO_CRH_CNF12', 'GPIO_CRH_CNF12_0', 'GPIO_CRH_CNF12_1', 'GPIO_CRH_CNF13',
    'GPIO_CRH_CNF13_0', 'GPIO_CRH_CNF13_1', 'GPIO_CRH_CNF14', 'GPIO_CRH_CNF14_0',
    'GPIO_CRH_CNF14_1', 'GPIO_CRH_CNF15', 'GPIO_CRH_CNF15_0', 'GPIO_CRH_CNF15_1',
    'GPIO_IDR_IDR0', 'GPIO_IDR_IDR1', 'GPIO_IDR_IDR2', 'GPIO_IDR_IDR3', 'GPIO_IDR_IDR4',
    'GPIO_IDR_IDR5', 'GPIO_IDR_IDR6', 'GPIO_IDR_IDR7', 'GPIO_IDR_IDR8', 'GPIO_IDR_IDR9',
    'GPIO_IDR_IDR10', 'GPIO_IDR_IDR11', 'GPIO_IDR_IDR12', 'GPIO_IDR_IDR13',
    'GPIO_IDR_IDR14', 'GPIO_IDR_IDR15', 'GPIO_ODR_ODR0', 'GPIO_ODR_ODR1',
    'GPIO_ODR_ODR2', 'GPIO_ODR_ODR3', 'GPIO_ODR_ODR4', 'GPIO_ODR_ODR5', 'GPIO_ODR_ODR6',
    'GPIO_ODR_ODR7', 'GPIO_ODR_ODR8', 'GPIO_ODR_ODR9', 'GPIO_ODR_ODR10',
    'GPIO_ODR_ODR11', 'GPIO_ODR_ODR12', 'GPIO_ODR_ODR13', 'GPIO_ODR_ODR14',
    'GPIO_ODR_ODR15', 'GPIO_BSRR_BS0', 'GPIO_BSRR_BS1', 'GPIO_BSRR_BS2',
    'GPIO_BSRR_BS3', 'GPIO_BSRR_BS4', 'GPIO_BSRR_BS5', 'GPIO_BSRR_BS6', 'GPIO_BSRR_BS7',
    'GPIO_BSRR_BS8', 'GPIO_BSRR_BS9', 'GPIO_BSRR_BS10', 'GPIO_BSRR_BS11',
    'GPIO_BSRR_BS12', 'GPIO_BSRR_BS13', 'GPIO_BSRR_BS14', 'GPIO_BSRR_BS15',
    'GPIO_BSRR_BR0', 'GPIO_BSRR_BR1', 'GPIO_BSRR_BR2', 'GPIO_BSRR_BR3', 'GPIO_BSRR_BR4',
    'GPIO_BSRR_BR5', 'GPIO_BSRR_BR6', 'GPIO_BSRR_BR7', 'GPIO_BSRR_BR8', 'GPIO_BSRR_BR9',
    'GPIO_BSRR_BR10', 'GPIO_BSRR_BR11', 'GPIO_BSRR_BR12', 'GPIO_BSRR_BR13',
    'GPIO_BSRR_BR14', 'GPIO_BSRR_BR15', 'GPIO_BRR_BR0', 'GPIO_BRR_BR1', 'GPIO_BRR_BR2',
    'GPIO_BRR_BR3', 'GPIO_BRR_BR4', 'GPIO_BRR_BR5', 'GPIO_BRR_BR6', 'GPIO_BRR_BR7',
    'GPIO_BRR_BR8', 'GPIO_BRR_BR9', 'GPIO_BRR_BR10', 'GPIO_BRR_BR11', 'GPIO_BRR_BR12',
    'GPIO_BRR_BR13', 'GPIO_BRR_BR14', 'GPIO_BRR_BR15', 'GPIO_LCKR_LCK0',
    'GPIO_LCKR_LCK1', 'GPIO_LCKR_LCK2', 'GPIO_LCKR_LCK3', 'GPIO_LCKR_LCK4',
    'GPIO_LCKR_LCK5', 'GPIO_LCKR_LCK6', 'GPIO_LCKR_LCK7', 'GPIO_LCKR_LCK8',
    'GPIO_LCKR_LCK9', 'GPIO_LCKR_LCK10', 'GPIO_LCKR_LCK11', 'GPIO_LCKR_LCK12',
    'GPIO_LCKR_LCK13', 'GPIO_LCKR_LCK14', 'GPIO_LCKR_LCK15', 'GPIO_LCKR_LCKK',
    'AFIO_EVCR_PIN', 'AFIO_EVCR_PIN_0', 'AFIO_EVCR_PIN_1', 'AFIO_EVCR_PIN_2',
    'AFIO_EVCR_PIN_3', 'AFIO_EVCR_PIN_PX0', 'AFIO_EVCR_PIN_PX1', 'AFIO_EVCR_PIN_PX2',
    'AFIO_EVCR_PIN_PX3', 'AFIO_EVCR_PIN_PX4', 'AFIO_EVCR_PIN_PX5', 'AFIO_EVCR_PIN_PX6',
    'AFIO_EVCR_PIN_PX7', 'AFIO_EVCR_PIN_PX8', 'AFIO_EVCR_PIN_PX9', 'AFIO_EVCR_PIN_PX10',
    'AFIO_EVCR_PIN_PX11', 'AFIO_EVCR_PIN_PX12', 'AFIO_EVCR_PIN_PX13',
    'AFIO_EVCR_PIN_PX14', 'AFIO_EVCR_PIN_PX15', 'AFIO_EVCR_PORT', 'AFIO_EVCR_PORT_0',
    'AFIO_EVCR_PORT_1', 'AFIO_EVCR_PORT_2', 'AFIO_EVCR_PORT_PA', 'AFIO_EVCR_PORT_PB',
    'AFIO_EVCR_PORT_PC', 'AFIO_EVCR_PORT_PD', 'AFIO_EVCR_PORT_PE', 'AFIO_EVCR_EVOE',
    'AFIO_MAPR_SPI1_REMAP', 'AFIO_MAPR_I2C1_REMAP', 'AFIO_MAPR_USART1_REMAP',
    'AFIO_MAPR_USART2_REMAP', 'AFIO_MAPR_USART3_REMAP', 'AFIO_MAPR_USART3_REMAP_0',
    'AFIO_MAPR_USART3_REMAP_1', 'AFIO_MAPR_USART3_REMAP_NOREMAP',
    'AFIO_MAPR_USART3_REMAP_PARTIALREMAP', 'AFIO_MAPR_USART3_REMAP_FULLREMAP',
    'AFIO_MAPR_TIM1_REMAP', 'AFIO_MAPR_TIM1_REMAP_0', 'AFIO_MAPR_TIM1_REMAP_1',
    'AFIO_MAPR_TIM1_REMAP_NOREMAP', 'AFIO_MAPR_TIM1_REMAP_PARTIALREMAP',
    'AFIO_MAPR_TIM1_REMAP_FULLREMAP', 'AFIO_MAPR_TIM2_REMAP', 'AFIO_MAPR_TIM2_REMAP_0',
    'AFIO_MAPR_TIM2_REMAP_1', 'AFIO_MAPR_TIM2_REMAP_NOREMAP',
    'AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1', 'AFIO_MAPR_TIM2_REMAP_PARTIALREMAP2',
    'AFIO_MAPR_TIM2_REMAP_FULLREMAP', 'AFIO_MAPR_TIM3_REMAP', 'AFIO_MAPR_TIM3_REMAP_0',
    'AFIO_MAPR_TIM3_REMAP_1', 'AFIO_MAPR_TIM3_REMAP_NOREMAP',
    'AFIO_MAPR_TIM3_REMAP_PARTIALREMAP', 'AFIO_MAPR_TIM3_REMAP_FULLREMAP',
    'AFIO_MAPR_TIM4_REMAP', 'AFIO_MAPR_CAN_REMAP', 'AFIO_MAPR_CAN_REMAP_0',
    'AFIO_MAPR_CAN_REMAP_1', 'AFIO_MAPR_CAN_REMAP_REMAP1', 'AFIO_MAPR_CAN_REMAP_REMAP2',
    'AFIO_MAPR_CAN_REMAP_REMAP3', 'AFIO_MAPR_PD01_REMAP', 'AFIO_MAPR_TIM5CH4_IREMAP',
    'AFIO_MAPR_ADC1_ETRGINJ_REMAP', 'AFIO_MAPR_ADC1_ETRGREG_REMAP',
    'AFIO_MAPR_ADC2_ETRGINJ_REMAP', 'AFIO_MAPR_ADC2_ETRGREG_REMAP', 'AFIO_MAPR_SWJ_CFG',
    'AFIO_MAPR_SWJ_CFG_0', 'AFIO_MAPR_SWJ_CFG_1', 'AFIO_MAPR_SWJ_CFG_2',
    'AFIO_MAPR_SWJ_CFG_RESET', 'AFIO_MAPR_SWJ_CFG_NOJNTRST',
    'AFIO_MAPR_SWJ_CFG_JTAGDISABLE', 'AFIO_MAPR_SWJ_CFG_DISABLE', 'AFIO_EXTICR1_EXTI0',
    'AFIO_EXTICR1_EXTI1', 'AFIO_EXTICR1_EXTI2', 'AFIO_EXTICR1_EXTI3',
    'AFIO_EXTICR1_EXTI0_PA', 'AFIO_EXTICR1_EXTI0_PB', 'AFIO_EXTICR1_EXTI0_PC',
    'AFIO_EXTICR1_EXTI0_PD', 'AFIO_EXTICR1_EXTI0_PE', 'AFIO_EXTICR1_EXTI0_PF',
    'AFIO_EXTICR1_EXTI0_PG', 'AFIO_EXTICR1_EXTI1_PA', 'AFIO_EXTICR1_EXTI1_PB',
    'AFIO_EXTICR1_EXTI1_PC', 'AFIO_EXTICR1_EXTI1_PD', 'AFIO_EXTICR1_EXTI1_PE',
    'AFIO_EXTICR1_EXTI1_PF', 'AFIO_EXTICR1_EXTI1_PG', 'AFIO_EXTICR1_EXTI2_PA',
    'AFIO_EXTICR1_EXTI2_PB', 'AFIO_EXTICR1_EXTI2_PC', 'AFIO_EXTICR1_EXTI2_PD',
    'AFIO_EXTICR1_EXTI2_PE', 'AFIO_EXTICR1_EXTI2_PF', 'AFIO_EXTICR1_EXTI2_PG',
    'AFIO_EXTICR1_EXTI3_PA', 'AFIO_EXTICR1_EXTI3_PB', 'AFIO_EXTICR1_EXTI3_PC',
    'AFIO_EXTICR1_EXTI3_PD', 'AFIO_EXTICR1_EXTI3_PE', 'AFIO_EXTICR1_EXTI3_PF',
    'AFIO_EXTICR1_EXTI3_PG', 'AFIO_EXTICR2_EXTI4', 'AFIO_EXTICR2_EXTI5',
    'AFIO_EXTICR2_EXTI6', 'AFIO_EXTICR2_EXTI7', 'AFIO_EXTICR2_EXTI4_PA',
    'AFIO_EXTICR2_EXTI4_PB', 'AFIO_EXTICR2_EXTI4_PC', 'AFIO_EXTICR2_EXTI4_PD',
    'AFIO_EXTICR2_EXTI4_PE', 'AFIO_EXTICR2_EXTI4_PF', 'AFIO_EXTICR2_EXTI4_PG',
    'AFIO_EXTICR2_EXTI5_PA', 'AFIO_EXTICR2_EXTI5_PB', 'AFIO_EXTICR2_EXTI5_PC',
    'AFIO_EXTICR2_EXTI5_PD', 'AFIO_EXTICR2_EXTI5_PE', 'AFIO_EXTICR2_EXTI5_PF',
    'AFIO_EXTICR2_EXTI5_PG', 'AFIO_EXTICR2_EXTI6_PA', 'AFIO_EXTICR2_EXTI6_PB',
    'AFIO_EXTICR2_EXTI6_PC', 'AFIO_EXTICR2_EXTI6_PD', 'AFIO_EXTICR2_EXTI6_PE',
    'AFIO_EXTICR2_EXTI6_PF', 'AFIO_EXTICR2_EXTI6_PG', 'AFIO_EXTICR2_EXTI7_PA',
    'AFIO_EXTICR2_EXTI7_PB', 'AFIO_EXTICR2_EXTI7_PC', 'AFIO_EXTICR2_EXTI7_PD',
    'AFIO_EXTICR2_EXTI7_PE', 'AFIO_EXTICR2_EXTI7_PF', 'AFIO_EXTICR2_EXTI7_PG',
    'AFIO_EXTICR3_EXTI8', 'AFIO_EXTICR3_EXTI9', 'AFIO_EXTICR3_EXTI10',
    'AFIO_EXTICR3_EXTI11', 'AFIO_EXTICR3_EXTI8_PA', 'AFIO_EXTICR3_EXTI8_PB',
    'AFIO_EXTICR3_EXTI8_PC', 'AFIO_EXTICR3_EXTI8_PD', 'AFIO_EXTICR3_EXTI8_PE',
    'AFIO_EXTICR3_EXTI8_PF', 'AFIO_EXTICR3_EXTI8_PG', 'AFIO_EXTICR3_EXTI9_PA',
    'AFIO_EXTICR3_EXTI9_PB', 'AFIO_EXTICR3_EXTI9_PC', 'AFIO_EXTICR3_EXTI9_PD',
    'AFIO_EXTICR3_EXTI9_PE', 'AFIO_EXTICR3_EXTI9_PF', 'AFIO_EXTICR3_EXTI9_PG',
    'AFIO_EXTICR3_EXTI10_PA', 'AFIO_EXTICR3_EXTI10_PB', 'AFIO_EXTICR3_EXTI10_PC',
    'AFIO_EXTICR3_EXTI10_PD', 'AFIO_EXTICR3_EXTI10_PE', 'AFIO_EXTICR3_EXTI10_PF',
    'AFIO_EXTICR3_EXTI10_PG', 'AFIO_EXTICR3_EXTI11_PA', 'AFIO_EXTICR3_EXTI11_PB',
    'AFIO_EXTICR3_EXTI11_PC', 'AFIO_EXTICR3_EXTI11_PD', 'AFIO_EXTICR3_EXTI11_PE',
    'AFIO_EXTICR3_EXTI11_PF', 'AFIO_EXTICR3_EXTI11_PG', 'AFIO_EXTICR4_EXTI12',
    'AFIO_EXTICR4_EXTI13', 'AFIO_EXTICR4_EXTI14', 'AFIO_EXTICR4_EXTI15',
    'AFIO_EXTICR4_EXTI12_PA', 'AFIO_EXTICR4_EXTI12_PB', 'AFIO_EXTICR4_EXTI12_PC',
    'AFIO_EXTICR4_EXTI12_PD', 'AFIO_EXTICR4_EXTI12_PE', 'AFIO_EXTICR4_EXTI12_PF',
    'AFIO_EXTICR4_EXTI12_PG', 'AFIO_EXTICR4_EXTI13_PA', 'AFIO_EXTICR4_EXTI13_PB',
    'AFIO_EXTICR4_EXTI13_PC', 'AFIO_EXTICR4_EXTI13_PD', 'AFIO_EXTICR4_EXTI13_PE',
    'AFIO_EXTICR4_EXTI13_PF', 'AFIO_EXTICR4_EXTI13_PG', 'AFIO_EXTICR4_EXTI14_PA',
    'AFIO_EXTICR4_EXTI14_PB', 'AFIO_EXTICR4_EXTI14_PC', 'AFIO_EXTICR4_EXTI14_PD',
    'AFIO_EXTICR4_EXTI14_PE', 'AFIO_EXTICR4_EXTI14_PF', 'AFIO_EXTICR4_EXTI14_PG',
    'AFIO_EXTICR4_EXTI15_PA', 'AFIO_EXTICR4_EXTI15_PB', 'AFIO_EXTICR4_EXTI15_PC',
    'AFIO_EXTICR4_EXTI15_PD', 'AFIO_EXTICR4_EXTI15_PE', 'AFIO_EXTICR4_EXTI15_PF',
    'AFIO_EXTICR4_EXTI15_PG', 'SysTick_CTRL_ENABLE', 'SysTick_CTRL_TICKINT',
    'SysTick_CTRL_CLKSOURCE', 'SysTick_CTRL_COUNTFLAG', 'SysTick_LOAD_RELOAD',
    'SysTick_VAL_CURRENT', 'SysTick_CALIB_TENMS', 'SysTick_CALIB_SKEW',
    'SysTick_CALIB_NOREF', 'NVIC_ISER_SETENA', 'NVIC_ISER_SETENA_0',
    'NVIC_ISER_SETENA_1', 'NVIC_ISER_SETENA_2', 'NVIC_ISER_SETENA_3',
    'NVIC_ISER_SETENA_4', 'NVIC_ISER_SETENA_5', 'NVIC_ISER_SETENA_6',
    'NVIC_ISER_SETENA_7', 'NVIC_ISER_SETENA_8', 'NVIC_ISER_SETENA_9',
    'NVIC_ISER_SETENA_10', 'NVIC_ISER_SETENA_11', 'NVIC_ISER_SETENA_12',
    'NVIC_ISER_SETENA_13', 'NVIC_ISER_SETENA_14', 'NVIC_ISER_SETENA_15',
    'NVIC_ISER_SETENA_16', 'NVIC_ISER_SETENA_17', 'NVIC_ISER_SETENA_18',
    'NVIC_ISER_SETENA_19', 'NVIC_ISER_SETENA_20', 'NVIC_ISER_SETENA_21',
    'NVIC_ISER_SETENA_22', 'NVIC_ISER_SETENA_23', 'NVIC_ISER_SETENA_24',
    'NVIC_ISER_SETENA_25', 'NVIC_ISER_SETENA_26', 'NVIC_ISER_SETENA_27',
    'NVIC_ISER_SETENA_28', 'NVIC_ISER_SETENA_29', 'NVIC_ISER_SETENA_30',
    'NVIC_ISER_SETENA_31', 'NVIC_ICER_CLRENA', 'NVIC_ICER_CLRENA_0',
    'NVIC_ICER_CLRENA_1', 'NVIC_ICER_CLRENA_2', 'NVIC_ICER_CLRENA_3',
    'NVIC_ICER_CLRENA_4', 'NVIC_ICER_CLRENA_5', 'NVIC_ICER_CLRENA_6',
    'NVIC_ICER_CLRENA_7', 'NVIC_ICER_CLRENA_8', 'NVIC_ICER_CLRENA_9',
    'NVIC_ICER_CLRENA_10', 'NVIC_ICER_CLRENA_11', 'NVIC_ICER_CLRENA_12',
    'NVIC_ICER_CLRENA_13', 'NVIC_ICER_CLRENA_14', 'NVIC_ICER_CLRENA_15',
    'NVIC_ICER_CLRENA_16', 'NVIC_ICER_CLRENA_17', 'NVIC_ICER_CLRENA_18',
    'NVIC_ICER_CLRENA_19', 'NVIC_ICER_CLRENA_20', 'NVIC_ICER_CLRENA_21',
    'NVIC_ICER_CLRENA_22', 'NVIC_ICER_CLRENA_23', 'NVIC_ICER_CLRENA_24',
    'NVIC_ICER_CLRENA_25', 'NVIC_ICER_CLRENA_26', 'NVIC_ICER_CLRENA_27',
    'NVIC_ICER_CLRENA_28', 'NVIC_ICER_CLRENA_29', 'NVIC_ICER_CLRENA_30',
    'NVIC_ICER_CLRENA_31', 'NVIC_ISPR_SETPEND', 'NVIC_ISPR_SETPEND_0',
    'NVIC_ISPR_SETPEND_1', 'NVIC_ISPR_SETPEND_2', 'NVIC_ISPR_SETPEND_3',
    'NVIC_ISPR_SETPEND_4', 'NVIC_ISPR_SETPEND_5', 'NVIC_ISPR_SETPEND_6',
    'NVIC_ISPR_SETPEND_7', 'NVIC_ISPR_SETPEND_8', 'NVIC_ISPR_SETPEND_9',
    'NVIC_ISPR_SETPEND_10', 'NVIC_ISPR_SETPEND_11', 'NVIC_ISPR_SETPEND_12',
    'NVIC_ISPR_SETPEND_13', 'NVIC_ISPR_SETPEND_14', 'NVIC_ISPR_SETPEND_15',
    'NVIC_ISPR_SETPEND_16', 'NVIC_ISPR_SETPEND_17', 'NVIC_ISPR_SETPEND_18',
    'NVIC_ISPR_SETPEND_19', 'NVIC_ISPR_SETPEND_20', 'NVIC_ISPR_SETPEND_21',
    'NVIC_ISPR_SETPEND_22', 'NVIC_ISPR_SETPEND_23', 'NVIC_ISPR_SETPEND_24',
    'NVIC_ISPR_SETPEND_25', 'NVIC_ISPR_SETPEND_26', 'NVIC_ISPR_SETPEND_27',
    'NVIC_ISPR_SETPEND_28', 'NVIC_ISPR_SETPEND_29', 'NVIC_ISPR_SETPEND_30',
    'NVIC_ISPR_SETPEND_31', 'NVIC_ICPR_CLRPEND', 'NVIC_ICPR_CLRPEND_0',
    'NVIC_ICPR_CLRPEND_1', 'NVIC_ICPR_CLRPEND_2', 'NVIC_ICPR_CLRPEND_3',
    'NVIC_ICPR_CLRPEND_4', 'NVIC_ICPR_CLRPEND_5', 'NVIC_ICPR_CLRPEND_6',
    'NVIC_ICPR_CLRPEND_7', 'NVIC_ICPR_CLRPEND_8', 'NVIC_ICPR_CLRPEND_9',
    'NVIC_ICPR_CLRPEND_10', 'NVIC_ICPR_CLRPEND_11', 'NVIC_ICPR_CLRPEND_12',
    'NVIC_ICPR_CLRPEND_13', 'NVIC_ICPR_CLRPEND_14', 'NVIC_ICPR_CLRPEND_15',
    'NVIC_ICPR_CLRPEND_16', 'NVIC_ICPR_CLRPEND_17', 'NVIC_ICPR_CLRPEND_18',
    'NVIC_ICPR_CLRPEND_19', 'NVIC_ICPR_CLRPEND_20', 'NVIC_ICPR_CLRPEND_21',
    'NVIC_ICPR_CLRPEND_22', 'NVIC_ICPR_CLRPEND_23', 'NVIC_ICPR_CLRPEND_24',
    'NVIC_ICPR_CLRPEND_25', 'NVIC_ICPR_CLRPEND_26', 'NVIC_ICPR_CLRPEND_27',
    'NVIC_ICPR_CLRPEND_28', 'NVIC_ICPR_CLRPEND_29', 'NVIC_ICPR_CLRPEND_30',
    'NVIC_ICPR_CLRPEND_31', 'NVIC_IABR_ACTIVE', 'NVIC_IABR_ACTIVE_0',
    'NVIC_IABR_ACTIVE_1', 'NVIC_IABR_ACTIVE_2', 'NVIC_IABR_ACTIVE_3',
    'NVIC_IABR_ACTIVE_4', 'NVIC_IABR_ACTIVE_5', 'NVIC_IABR_ACTIVE_6',
    'NVIC_IABR_ACTIVE_7', 'NVIC_IABR_ACTIVE_8', 'NVIC_IABR_ACTIVE_9',
    'NVIC_IABR_ACTIVE_10', 'NVIC_IABR_ACTIVE_11', 'NVIC_IABR_ACTIVE_12',
    'NVIC_IABR_ACTIVE_13', 'NVIC_IABR_ACTIVE_14', 'NVIC_IABR_ACTIVE_15',
    'NVIC_IABR_ACTIVE_16', 'NVIC_IABR_ACTIVE_17', 'NVIC_IABR_ACTIVE_18',
    'NVIC_IABR_ACTIVE_19', 'NVIC_IABR_ACTIVE_20', 'NVIC_IABR_ACTIVE_21',
    'NVIC_IABR_ACTIVE_22', 'NVIC_IABR_ACTIVE_23', 'NVIC_IABR_ACTIVE_24',
    'NVIC_IABR_ACTIVE_25', 'NVIC_IABR_ACTIVE_26', 'NVIC_IABR_ACTIVE_27',
    'NVIC_IABR_ACTIVE_28', 'NVIC_IABR_ACTIVE_29', 'NVIC_IABR_ACTIVE_30',
    'NVIC_IABR_ACTIVE_31', 'NVIC_IPR0_PRI_0', 'NVIC_IPR0_PRI_1', 'NVIC_IPR0_PRI_2',
    'NVIC_IPR0_PRI_3', 'NVIC_IPR1_PRI_4', 'NVIC_IPR1_PRI_5', 'NVIC_IPR1_PRI_6',
    'NVIC_IPR1_PRI_7', 'NVIC_IPR2_PRI_8', 'NVIC_IPR2_PRI_9', 'NVIC_IPR2_PRI_10',
    'NVIC_IPR2_PRI_11', 'NVIC_IPR3_PRI_12', 'NVIC_IPR3_PRI_13', 'NVIC_IPR3_PRI_14',
    'NVIC_IPR3_PRI_15', 'NVIC_IPR4_PRI_16', 'NVIC_IPR4_PRI_17', 'NVIC_IPR4_PRI_18',
    'NVIC_IPR4_PRI_19', 'NVIC_IPR5_PRI_20', 'NVIC_IPR5_PRI_21', 'NVIC_IPR5_PRI_22',
    'NVIC_IPR5_PRI_23', 'NVIC_IPR6_PRI_24', 'NVIC_IPR6_PRI_25', 'NVIC_IPR6_PRI_26',
    'NVIC_IPR6_PRI_27', 'NVIC_IPR7_PRI_28', 'NVIC_IPR7_PRI_29', 'NVIC_IPR7_PRI_30',
    'NVIC_IPR7_PRI_31', 'SCB_CPUID_REVISION', 'SCB_CPUID_PARTNO', 'SCB_CPUID_Constant',
    'SCB_CPUID_VARIANT', 'SCB_CPUID_IMPLEMENTER', 'SCB_ICSR_VECTACTIVE',
    'SCB_ICSR_RETTOBASE', 'SCB_ICSR_VECTPENDING', 'SCB_ICSR_ISRPENDING',
    'SCB_ICSR_ISRPREEMPT', 'SCB_ICSR_PENDSTCLR', 'SCB_ICSR_PENDSTSET',
    'SCB_ICSR_PENDSVCLR', 'SCB_ICSR_PENDSVSET', 'SCB_ICSR_NMIPENDSET',
    'SCB_VTOR_TBLOFF', 'SCB_VTOR_TBLBASE', 'SCB_AIRCR_VECTRESET',
    'SCB_AIRCR_VECTCLRACTIVE', 'SCB_AIRCR_SYSRESETREQ', 'SCB_AIRCR_PRIGROUP',
    'SCB_AIRCR_PRIGROUP_0', 'SCB_AIRCR_PRIGROUP_1', 'SCB_AIRCR_PRIGROUP_2',
    'SCB_AIRCR_PRIGROUP0', 'SCB_AIRCR_PRIGROUP1', 'SCB_AIRCR_PRIGROUP2',
    'SCB_AIRCR_PRIGROUP3', 'SCB_AIRCR_PRIGROUP4', 'SCB_AIRCR_PRIGROUP5',
    'SCB_AIRCR_PRIGROUP6', 'SCB_AIRCR_PRIGROUP7', 'SCB_AIRCR_ENDIANESS',
    'SCB_AIRCR_VECTKEY', 'SCB_SCR_SLEEPONEXIT', 'SCB_SCR_SLEEPDEEP',
    'SCB_SCR_SEVONPEND', 'SCB_CCR_NONBASETHRDENA', 'SCB_CCR_USERSETMPEND',
    'SCB_CCR_UNALIGN_TRP', 'SCB_CCR_DIV_0_TRP', 'SCB_CCR_BFHFNMIGN', 'SCB_CCR_STKALIGN',
    'SCB_SHPR_PRI_N', 'SCB_SHPR_PRI_N1', 'SCB_SHPR_PRI_N2', 'SCB_SHPR_PRI_N3',
    'SCB_SHCSR_MEMFAULTACT', 'SCB_SHCSR_BUSFAULTACT', 'SCB_SHCSR_USGFAULTACT',
    'SCB_SHCSR_SVCALLACT', 'SCB_SHCSR_MONITORACT', 'SCB_SHCSR_PENDSVACT',
    'SCB_SHCSR_SYSTICKACT', 'SCB_SHCSR_USGFAULTPENDED', 'SCB_SHCSR_MEMFAULTPENDED',
    'SCB_SHCSR_BUSFAULTPENDED', 'SCB_SHCSR_SVCALLPENDED', 'SCB_SHCSR_MEMFAULTENA',
    'SCB_SHCSR_BUSFAULTENA', 'SCB_SHCSR_USGFAULTENA', 'SCB_CFSR_IACCVIOL',
    'SCB_CFSR_DACCVIOL', 'SCB_CFSR_MUNSTKERR', 'SCB_CFSR_MSTKERR', 'SCB_CFSR_MMARVALID',
    'SCB_CFSR_IBUSERR', 'SCB_CFSR_PRECISERR', 'SCB_CFSR_IMPRECISERR',
    'SCB_CFSR_UNSTKERR', 'SCB_CFSR_STKERR', 'SCB_CFSR_BFARVALID', 'SCB_CFSR_UNDEFINSTR',
    'SCB_CFSR_INVSTATE', 'SCB_CFSR_INVPC', 'SCB_CFSR_NOCP', 'SCB_CFSR_UNALIGNED',
    'SCB_CFSR_DIVBYZERO', 'SCB_HFSR_VECTTBL', 'SCB_HFSR_FORCED', 'SCB_HFSR_DEBUGEVT',
    'SCB_DFSR_HALTED', 'SCB_DFSR_BKPT', 'SCB_DFSR_DWTTRAP', 'SCB_DFSR_VCATCH',
    'SCB_DFSR_EXTERNAL', 'SCB_MMFAR_ADDRESS', 'SCB_BFAR_ADDRESS', 'SCB_AFSR_IMPDEF',
    'EXTI_IMR_MR0', 'EXTI_IMR_MR1', 'EXTI_IMR_MR2', 'EXTI_IMR_MR3', 'EXTI_IMR_MR4',
    'EXTI_IMR_MR5', 'EXTI_IMR_MR6', 'EXTI_IMR_MR7', 'EXTI_IMR_MR8', 'EXTI_IMR_MR9',
    'EXTI_IMR_MR10', 'EXTI_IMR_MR11', 'EXTI_IMR_MR12', 'EXTI_IMR_MR13', 'EXTI_IMR_MR14',
    'EXTI_IMR_MR15', 'EXTI_IMR_MR16', 'EXTI_IMR_MR17', 'EXTI_IMR_MR18', 'EXTI_IMR_MR19',
    'EXTI_EMR_MR0', 'EXTI_EMR_MR1', 'EXTI_EMR_MR2', 'EXTI_EMR_MR3', 'EXTI_EMR_MR4',
    'EXTI_EMR_MR5', 'EXTI_EMR_MR6', 'EXTI_EMR_MR7', 'EXTI_EMR_MR8', 'EXTI_EMR_MR9',
    'EXTI_EMR_MR10', 'EXTI_EMR_MR11', 'EXTI_EMR_MR12', 'EXTI_EMR_MR13', 'EXTI_EMR_MR14',
    'EXTI_EMR_MR15', 'EXTI_EMR_MR16', 'EXTI_EMR_MR17', 'EXTI_EMR_MR18', 'EXTI_EMR_MR19',
    'EXTI_RTSR_TR0', 'EXTI_RTSR_TR1', 'EXTI_RTSR_TR2', 'EXTI_RTSR_TR3', 'EXTI_RTSR_TR4',
    'EXTI_RTSR_TR5', 'EXTI_RTSR_TR6', 'EXTI_RTSR_TR7', 'EXTI_RTSR_TR8', 'EXTI_RTSR_TR9',
    'EXTI_RTSR_TR10', 'EXTI_RTSR_TR11', 'EXTI_RTSR_TR12', 'EXTI_RTSR_TR13',
    'EXTI_RTSR_TR14', 'EXTI_RTSR_TR15', 'EXTI_RTSR_TR16', 'EXTI_RTSR_TR17',
    'EXTI_RTSR_TR18', 'EXTI_RTSR_TR19', 'EXTI_FTSR_TR0', 'EXTI_FTSR_TR1',
    'EXTI_FTSR_TR2', 'EXTI_FTSR_TR3', 'EXTI_FTSR_TR4', 'EXTI_FTSR_TR5', 'EXTI_FTSR_TR6',
    'EXTI_FTSR_TR7', 'EXTI_FTSR_TR8', 'EXTI_FTSR_TR9', 'EXTI_FTSR_TR10',
    'EXTI_FTSR_TR11', 'EXTI_FTSR_TR12', 'EXTI_FTSR_TR13', 'EXTI_FTSR_TR14',
    'EXTI_FTSR_TR15', 'EXTI_FTSR_TR16', 'EXTI_FTSR_TR17', 'EXTI_FTSR_TR18',
    'EXTI_FTSR_TR19', 'EXTI_SWIER_SWIER0', 'EXTI_SWIER_SWIER1', 'EXTI_SWIER_SWIER2',
    'EXTI_SWIER_SWIER3', 'EXTI_SWIER_SWIER4', 'EXTI_SWIER_SWIER5', 'EXTI_SWIER_SWIER6',
    'EXTI_SWIER_SWIER7', 'EXTI_SWIER_SWIER8', 'EXTI_SWIER_SWIER9', 'EXTI_SWIER_SWIER10',
    'EXTI_SWIER_SWIER11', 'EXTI_SWIER_SWIER12', 'EXTI_SWIER_SWIER13',
    'EXTI_SWIER_SWIER14', 'EXTI_SWIER_SWIER15', 'EXTI_SWIER_SWIER16',
    'EXTI_SWIER_SWIER17', 'EXTI_SWIER_SWIER18', 'EXTI_SWIER_SWIER19', 'EXTI_PR_PR0',
    'EXTI_PR_PR1', 'EXTI_PR_PR2', 'EXTI_PR_PR3', 'EXTI_PR_PR4', 'EXTI_PR_PR5',
    'EXTI_PR_PR6', 'EXTI_PR_PR7', 'EXTI_PR_PR8', 'EXTI_PR_PR9', 'EXTI_PR_PR10',
    'EXTI_PR_PR11', 'EXTI_PR_PR12', 'EXTI_PR_PR13', 'EXTI_PR_PR14', 'EXTI_PR_PR15',
    'EXTI_PR_PR16', 'EXTI_PR_PR17', 'EXTI_PR_PR18', 'EXTI_PR_PR19', 'DMA_ISR_GIF1',
    'DMA_ISR_TCIF1', 'DMA_ISR_HTIF1', 'DMA_ISR_TEIF1', 'DMA_ISR_GIF2', 'DMA_ISR_TCIF2',
    'DMA_ISR_HTIF2', 'DMA_ISR_TEIF2', 'DMA_ISR_GIF3', 'DMA_ISR_TCIF3', 'DMA_ISR_HTIF3',
    'DMA_ISR_TEIF3', 'DMA_ISR_GIF4', 'DMA_ISR_TCIF4', 'DMA_ISR_HTIF4', 'DMA_ISR_TEIF4',
    'DMA_ISR_GIF5', 'DMA_ISR_TCIF5', 'DMA_ISR_HTIF5', 'DMA_ISR_TEIF5', 'DMA_ISR_GIF6',
    'DMA_ISR_TCIF6', 'DMA_ISR_HTIF6', 'DMA_ISR_TEIF6', 'DMA_ISR_GIF7', 'DMA_ISR_TCIF7',
    'DMA_ISR_HTIF7', 'DMA_ISR_TEIF7', 'DMA_IFCR_CGIF1', 'DMA_IFCR_CTCIF1',
    'DMA_IFCR_CHTIF1', 'DMA_IFCR_CTEIF1', 'DMA_IFCR_CGIF2', 'DMA_IFCR_CTCIF2',
    'DMA_IFCR_CHTIF2', 'DMA_IFCR_CTEIF2', 'DMA_IFCR_CGIF3', 'DMA_IFCR_CTCIF3',
    'DMA_IFCR_CHTIF3', 'DMA_IFCR_CTEIF3', 'DMA_IFCR_CGIF4', 'DMA_IFCR_CTCIF4',
    'DMA_IFCR_CHTIF4', 'DMA_IFCR_CTEIF4', 'DMA_IFCR_CGIF5', 'DMA_IFCR_CTCIF5',
    'DMA_IFCR_CHTIF5', 'DMA_IFCR_CTEIF5', 'DMA_IFCR_CGIF6', 'DMA_IFCR_CTCIF6',
    'DMA_IFCR_CHTIF6', 'DMA_IFCR_CTEIF6', 'DMA_IFCR_CGIF7', 'DMA_IFCR_CTCIF7',
    'DMA_IFCR_CHTIF7', 'DMA_IFCR_CTEIF7', 'DMA_CCR1_EN', 'DMA_CCR1_TCIE',
    'DMA_CCR1_HTIE', 'DMA_CCR1_TEIE', 'DMA_CCR1_DIR', 'DMA_CCR1_CIRC', 'DMA_CCR1_PINC',
    'DMA_CCR1_MINC', 'DMA_CCR1_PSIZE', 'DMA_CCR1_PSIZE_0', 'DMA_CCR1_PSIZE_1',
    'DMA_CCR1_MSIZE', 'DMA_CCR1_MSIZE_0', 'DMA_CCR1_MSIZE_1', 'DMA_CCR1_PL',
    'DMA_CCR1_PL_0', 'DMA_CCR1_PL_1', 'DMA_CCR1_MEM2MEM', 'DMA_CCR2_EN',
    'DMA_CCR2_TCIE', 'DMA_CCR2_HTIE', 'DMA_CCR2_TEIE', 'DMA_CCR2_DIR', 'DMA_CCR2_CIRC',
    'DMA_CCR2_PINC', 'DMA_CCR2_MINC', 'DMA_CCR2_PSIZE', 'DMA_CCR2_PSIZE_0',
    'DMA_CCR2_PSIZE_1', 'DMA_CCR2_MSIZE', 'DMA_CCR2_MSIZE_0', 'DMA_CCR2_MSIZE_1',
    'DMA_CCR2_PL', 'DMA_CCR2_PL_0', 'DMA_CCR2_PL_1', 'DMA_CCR2_MEM2MEM', 'DMA_CCR3_EN',
    'DMA_CCR3_TCIE', 'DMA_CCR3_HTIE', 'DMA_CCR3_TEIE', 'DMA_CCR3_DIR', 'DMA_CCR3_CIRC',
    'DMA_CCR3_PINC', 'DMA_CCR3_MINC', 'DMA_CCR3_PSIZE', 'DMA_CCR3_PSIZE_0',
    'DMA_CCR3_PSIZE_1', 'DMA_CCR3_MSIZE', 'DMA_CCR3_MSIZE_0', 'DMA_CCR3_MSIZE_1',
    'DMA_CCR3_PL', 'DMA_CCR3_PL_0', 'DMA_CCR3_PL_1', 'DMA_CCR3_MEM2MEM', 'DMA_CCR4_EN',
    'DMA_CCR4_TCIE', 'DMA_CCR4_HTIE', 'DMA_CCR4_TEIE', 'DMA_CCR4_DIR', 'DMA_CCR4_CIRC',
    'DMA_CCR4_PINC', 'DMA_CCR4_MINC', 'DMA_CCR4_PSIZE', 'DMA_CCR4_PSIZE_0',
    'DMA_CCR4_PSIZE_1', 'DMA_CCR4_MSIZE', 'DMA_CCR4_MSIZE_0', 'DMA_CCR4_MSIZE_1',
    'DMA_CCR4_PL', 'DMA_CCR4_PL_0', 'DMA_CCR4_PL_1', 'DMA_CCR4_MEM2MEM', 'DMA_CCR5_EN',
    'DMA_CCR5_TCIE', 'DMA_CCR5_HTIE', 'DMA_CCR5_TEIE', 'DMA_CCR5_DIR', 'DMA_CCR5_CIRC',
    'DMA_CCR5_PINC', 'DMA_CCR5_MINC', 'DMA_CCR5_PSIZE', 'DMA_CCR5_PSIZE_0',
    'DMA_CCR5_PSIZE_1', 'DMA_CCR5_MSIZE', 'DMA_CCR5_MSIZE_0', 'DMA_CCR5_MSIZE_1',
    'DMA_CCR5_PL', 'DMA_CCR5_PL_0', 'DMA_CCR5_PL_1', 'DMA_CCR5_MEM2MEM', 'DMA_CCR6_EN',
    'DMA_CCR6_TCIE', 'DMA_CCR6_HTIE', 'DMA_CCR6_TEIE', 'DMA_CCR6_DIR', 'DMA_CCR6_CIRC',
    'DMA_CCR6_PINC', 'DMA_CCR6_MINC', 'DMA_CCR6_PSIZE', 'DMA_CCR6_PSIZE_0',
    'DMA_CCR6_PSIZE_1', 'DMA_CCR6_MSIZE', 'DMA_CCR6_MSIZE_0', 'DMA_CCR6_MSIZE_1',
    'DMA_CCR6_PL', 'DMA_CCR6_PL_0', 'DMA_CCR6_PL_1', 'DMA_CCR6_MEM2MEM', 'DMA_CCR7_EN',
    'DMA_CCR7_TCIE', 'DMA_CCR7_HTIE', 'DMA_CCR7_TEIE', 'DMA_CCR7_DIR', 'DMA_CCR7_CIRC',
    'DMA_CCR7_PINC', 'DMA_CCR7_MINC', 'DMA_CCR7_PSIZE', 'DMA_CCR7_PSIZE_0',
    'DMA_CCR7_PSIZE_1', 'DMA_CCR7_MSIZE', 'DMA_CCR7_MSIZE_0', 'DMA_CCR7_MSIZE_1',
    'DMA_CCR7_PL', 'DMA_CCR7_PL_0', 'DMA_CCR7_PL_1', 'DMA_CCR7_MEM2MEM',
    'DMA_CNDTR1_NDT', 'DMA_CNDTR2_NDT', 'DMA_CNDTR3_NDT', 'DMA_CNDTR4_NDT',
    'DMA_CNDTR5_NDT', 'DMA_CNDTR6_NDT', 'DMA_CNDTR7_NDT', 'DMA_CPAR1_PA',
    'DMA_CPAR2_PA', 'DMA_CPAR3_PA', 'DMA_CPAR4_PA', 'DMA_CPAR5_PA', 'DMA_CPAR6_PA',
    'DMA_CPAR7_PA', 'DMA_CMAR1_MA', 'DMA_CMAR2_MA', 'DMA_CMAR3_MA', 'DMA_CMAR4_MA',
    'DMA_CMAR5_MA', 'DMA_CMAR6_MA', 'DMA_CMAR7_MA', 'ADC_SR_AWD', 'ADC_SR_EOC',
    'ADC_SR_JEOC', 'ADC_SR_JSTRT', 'ADC_SR_STRT', 'ADC_CR1_AWDCH', 'ADC_CR1_AWDCH_0',
    'ADC_CR1_AWDCH_1', 'ADC_CR1_AWDCH_2', 'ADC_CR1_AWDCH_3', 'ADC_CR1_AWDCH_4',
    'ADC_CR1_EOCIE', 'ADC_CR1_AWDIE', 'ADC_CR1_JEOCIE', 'ADC_CR1_SCAN',
    'ADC_CR1_AWDSGL', 'ADC_CR1_JAUTO', 'ADC_CR1_DISCEN', 'ADC_CR1_JDISCEN',
    'ADC_CR1_DISCNUM', 'ADC_CR1_DISCNUM_0', 'ADC_CR1_DISCNUM_1', 'ADC_CR1_DISCNUM_2',
    'ADC_CR1_DUALMOD', 'ADC_CR1_DUALMOD_0', 'ADC_CR1_DUALMOD_1', 'ADC_CR1_DUALMOD_2',
    'ADC_CR1_DUALMOD_3', 'ADC_CR1_JAWDEN', 'ADC_CR1_AWDEN', 'ADC_CR2_ADON',
    'ADC_CR2_CONT', 'ADC_CR2_CAL', 'ADC_CR2_RSTCAL', 'ADC_CR2_DMA', 'ADC_CR2_ALIGN',
    'ADC_CR2_JEXTSEL', 'ADC_CR2_JEXTSEL_0', 'ADC_CR2_JEXTSEL_1', 'ADC_CR2_JEXTSEL_2',
    'ADC_CR2_JEXTTRIG', 'ADC_CR2_EXTSEL', 'ADC_CR2_EXTSEL_0', 'ADC_CR2_EXTSEL_1',
    'ADC_CR2_EXTSEL_2', 'ADC_CR2_EXTTRIG', 'ADC_CR2_JSWSTART', 'ADC_CR2_SWSTART',
    'ADC_CR2_TSVREFE', 'ADC_SMPR1_SMP10', 'ADC_SMPR1_SMP10_0', 'ADC_SMPR1_SMP10_1',
    'ADC_SMPR1_SMP10_2', 'ADC_SMPR1_SMP11', 'ADC_SMPR1_SMP11_0', 'ADC_SMPR1_SMP11_1',
    'ADC_SMPR1_SMP11_2', 'ADC_SMPR1_SMP12', 'ADC_SMPR1_SMP12_0', 'ADC_SMPR1_SMP12_1',
    'ADC_SMPR1_SMP12_2', 'ADC_SMPR1_SMP13', 'ADC_SMPR1_SMP13_0', 'ADC_SMPR1_SMP13_1',
    'ADC_SMPR1_SMP13_2', 'ADC_SMPR1_SMP14', 'ADC_SMPR1_SMP14_0', 'ADC_SMPR1_SMP14_1',
    'ADC_SMPR1_SMP14_2', 'ADC_SMPR1_SMP15', 'ADC_SMPR1_SMP15_0', 'ADC_SMPR1_SMP15_1',
    'ADC_SMPR1_SMP15_2', 'ADC_SMPR1_SMP16', 'ADC_SMPR1_SMP16_0', 'ADC_SMPR1_SMP16_1',
    'ADC_SMPR1_SMP16_2', 'ADC_SMPR1_SMP17', 'ADC_SMPR1_SMP17_0', 'ADC_SMPR1_SMP17_1',
    'ADC_SMPR1_SMP17_2', 'ADC_SMPR2_SMP0', 'ADC_SMPR2_SMP0_0', 'ADC_SMPR2_SMP0_1',
    'ADC_SMPR2_SMP0_2', 'ADC_SMPR2_SMP1', 'ADC_SMPR2_SMP1_0', 'ADC_SMPR2_SMP1_1',
    'ADC_SMPR2_SMP1_2', 'ADC_SMPR2_SMP2', 'ADC_SMPR2_SMP2_0', 'ADC_SMPR2_SMP2_1',
    'ADC_SMPR2_SMP2_2', 'ADC_SMPR2_SMP3', 'ADC_SMPR2_SMP3_0', 'ADC_SMPR2_SMP3_1',
    'ADC_SMPR2_SMP3_2', 'ADC_SMPR2_SMP4', 'ADC_SMPR2_SMP4_0', 'ADC_SMPR2_SMP4_1',
    'ADC_SMPR2_SMP4_2', 'ADC_SMPR2_SMP5', 'ADC_SMPR2_SMP5_0', 'ADC_SMPR2_SMP5_1',
    'ADC_SMPR2_SMP5_2', 'ADC_SMPR2_SMP6', 'ADC_SMPR2_SMP6_0', 'ADC_SMPR2_SMP6_1',
    'ADC_SMPR2_SMP6_2', 'ADC_SMPR2_SMP7', 'ADC_SMPR2_SMP7_0', 'ADC_SMPR2_SMP7_1',
    'ADC_SMPR2_SMP7_2', 'ADC_SMPR2_SMP8', 'ADC_SMPR2_SMP8_0', 'ADC_SMPR2_SMP8_1',
    'ADC_SMPR2_SMP8_2', 'ADC_SMPR2_SMP9', 'ADC_SMPR2_SMP9_0', 'ADC_SMPR2_SMP9_1',
    'ADC_SMPR2_SMP9_2', 'ADC_JOFR1_JOFFSET1', 'ADC_JOFR2_JOFFSET2',
    'ADC_JOFR3_JOFFSET3', 'ADC_JOFR4_JOFFSET4', 'ADC_HTR_HT', 'ADC_LTR_LT',
    'ADC_SQR1_SQ13', 'ADC_SQR1_SQ13_0', 'ADC_SQR1_SQ13_1', 'ADC_SQR1_SQ13_2',
    'ADC_SQR1_SQ13_3', 'ADC_SQR1_SQ13_4', 'ADC_SQR1_SQ14', 'ADC_SQR1_SQ14_0',
    'ADC_SQR1_SQ14_1', 'ADC_SQR1_SQ14_2', 'ADC_SQR1_SQ14_3', 'ADC_SQR1_SQ14_4',
    'ADC_SQR1_SQ15', 'ADC_SQR1_SQ15_0', 'ADC_SQR1_SQ15_1', 'ADC_SQR1_SQ15_2',
    'ADC_SQR1_SQ15_3', 'ADC_SQR1_SQ15_4', 'ADC_SQR1_SQ16', 'ADC_SQR1_SQ16_0',
    'ADC_SQR1_SQ16_1', 'ADC_SQR1_SQ16_2', 'ADC_SQR1_SQ16_3', 'ADC_SQR1_SQ16_4',
    'ADC_SQR1_L', 'ADC_SQR1_L_0', 'ADC_SQR1_L_1', 'ADC_SQR1_L_2', 'ADC_SQR1_L_3',
    'ADC_SQR2_SQ7', 'ADC_SQR2_SQ7_0', 'ADC_SQR2_SQ7_1', 'ADC_SQR2_SQ7_2',
    'ADC_SQR2_SQ7_3', 'ADC_SQR2_SQ7_4', 'ADC_SQR2_SQ8', 'ADC_SQR2_SQ8_0',
    'ADC_SQR2_SQ8_1', 'ADC_SQR2_SQ8_2', 'ADC_SQR2_SQ8_3', 'ADC_SQR2_SQ8_4',
    'ADC_SQR2_SQ9', 'ADC_SQR2_SQ9_0', 'ADC_SQR2_SQ9_1', 'ADC_SQR2_SQ9_2',
    'ADC_SQR2_SQ9_3', 'ADC_SQR2_SQ9_4', 'ADC_SQR2_SQ10', 'ADC_SQR2_SQ10_0',
    'ADC_SQR2_SQ10_1', 'ADC_SQR2_SQ10_2', 'ADC_SQR2_SQ10_3', 'ADC_SQR2_SQ10_4',
    'ADC_SQR2_SQ11', 'ADC_SQR2_SQ11_0', 'ADC_SQR2_SQ11_1', 'ADC_SQR2_SQ11_2',
    'ADC_SQR2_SQ11_3', 'ADC_SQR2_SQ11_4', 'ADC_SQR2_SQ12', 'ADC_SQR2_SQ12_0',
    'ADC_SQR2_SQ12_1', 'ADC_SQR2_SQ12_2', 'ADC_SQR2_SQ12_3', 'ADC_SQR2_SQ12_4',
    'ADC_SQR3_SQ1', 'ADC_SQR3_SQ1_0', 'ADC_SQR3_SQ1_1', 'ADC_SQR3_SQ1_2',
    'ADC_SQR3_SQ1_3', 'ADC_SQR3_SQ1_4', 'ADC_SQR3_SQ2', 'ADC_SQR3_SQ2_0',
    'ADC_SQR3_SQ2_1', 'ADC_SQR3_SQ2_2', 'ADC_SQR3_SQ2_3', 'ADC_SQR3_SQ2_4',
    'ADC_SQR3_SQ3', 'ADC_SQR3_SQ3_0', 'ADC_SQR3_SQ3_1', 'ADC_SQR3_SQ3_2',
    'ADC_SQR3_SQ3_3', 'ADC_SQR3_SQ3_4', 'ADC_SQR3_SQ4', 'ADC_SQR3_SQ4_0',
    'ADC_SQR3_SQ4_1', 'ADC_SQR3_SQ4_2', 'ADC_SQR3_SQ4_3', 'ADC_SQR3_SQ4_4',
    'ADC_SQR3_SQ5', 'ADC_SQR3_SQ5_0', 'ADC_SQR3_SQ5_1', 'ADC_SQR3_SQ5_2',
    'ADC_SQR3_SQ5_3', 'ADC_SQR3_SQ5_4', 'ADC_SQR3_SQ6', 'ADC_SQR3_SQ6_0',
    'ADC_SQR3_SQ6_1', 'ADC_SQR3_SQ6_2', 'ADC_SQR3_SQ6_3', 'ADC_SQR3_SQ6_4',
    'ADC_JSQR_JSQ1', 'ADC_JSQR_JSQ1_0', 'ADC_JSQR_JSQ1_1', 'ADC_JSQR_JSQ1_2',
    'ADC_JSQR_JSQ1_3', 'ADC_JSQR_JSQ1_4', 'ADC_JSQR_JSQ2', 'ADC_JSQR_JSQ2_0',
    'ADC_JSQR_JSQ2_1', 'ADC_JSQR_JSQ2_2', 'ADC_JSQR_JSQ2_3', 'ADC_JSQR_JSQ2_4',
    'ADC_JSQR_JSQ3', 'ADC_JSQR_JSQ3_0', 'ADC_JSQR_JSQ3_1', 'ADC_JSQR_JSQ3_2',
    'ADC_JSQR_JSQ3_3', 'ADC_JSQR_JSQ3_4', 'ADC_JSQR_JSQ4', 'ADC_JSQR_JSQ4_0',
    'ADC_JSQR_JSQ4_1', 'ADC_JSQR_JSQ4_2', 'ADC_JSQR_JSQ4_3', 'ADC_JSQR_JSQ4_4',
    'ADC_JSQR_JL', 'ADC_JSQR_JL_0', 'ADC_JSQR_JL_1', 'ADC_JDR1_JDATA', 'ADC_JDR2_JDATA',
    'ADC_JDR3_JDATA', 'ADC_JDR4_JDATA', 'ADC_DR_DATA', 'ADC_DR_ADC2DATA', 'DAC_CR_EN1',
    'DAC_CR_BOFF1', 'DAC_CR_TEN1', 'DAC_CR_TSEL1', 'DAC_CR_TSEL1_0', 'DAC_CR_TSEL1_1',
    'DAC_CR_TSEL1_2', 'DAC_CR_WAVE1', 'DAC_CR_WAVE1_0', 'DAC_CR_WAVE1_1',
    'DAC_CR_MAMP1', 'DAC_CR_MAMP1_0', 'DAC_CR_MAMP1_1', 'DAC_CR_MAMP1_2',
    'DAC_CR_MAMP1_3', 'DAC_CR_DMAEN1', 'DAC_CR_EN2', 'DAC_CR_BOFF2', 'DAC_CR_TEN2',
    'DAC_CR_TSEL2', 'DAC_CR_TSEL2_0', 'DAC_CR_TSEL2_1', 'DAC_CR_TSEL2_2',
    'DAC_CR_WAVE2', 'DAC_CR_WAVE2_0', 'DAC_CR_WAVE2_1', 'DAC_CR_MAMP2',
    'DAC_CR_MAMP2_0', 'DAC_CR_MAMP2_1', 'DAC_CR_MAMP2_2', 'DAC_CR_MAMP2_3',
    'DAC_CR_DMAEN2', 'DAC_SWTRIGR_SWTRIG1', 'DAC_SWTRIGR_SWTRIG2',
    'DAC_DHR12R1_DACC1DHR', 'DAC_DHR12L1_DACC1DHR', 'DAC_DHR8R1_DACC1DHR',
    'DAC_DHR12R2_DACC2DHR', 'DAC_DHR12L2_DACC2DHR', 'DAC_DHR8R2_DACC2DHR',
    'DAC_DHR12RD_DACC1DHR', 'DAC_DHR12RD_DACC2DHR', 'DAC_DHR12LD_DACC1DHR',
    'DAC_DHR12LD_DACC2DHR', 'DAC_DHR8RD_DACC1DHR', 'DAC_DHR8RD_DACC2DHR',
    'DAC_DOR1_DACC1DOR', 'DAC_DOR2_DACC2DOR', 'DAC_SR_DMAUDR1', 'DAC_SR_DMAUDR2',
    'CEC_CFGR_PE', 'CEC_CFGR_IE', 'CEC_CFGR_BTEM', 'CEC_CFGR_BPEM', 'CEC_OAR_OA',
    'CEC_OAR_OA_0', 'CEC_OAR_OA_1', 'CEC_OAR_OA_2', 'CEC_OAR_OA_3', 'CEC_PRES_PRES',
    'CEC_ESR_BTE', 'CEC_ESR_BPE', 'CEC_ESR_RBTFE', 'CEC_ESR_SBE', 'CEC_ESR_ACKE',
    'CEC_ESR_LINE', 'CEC_ESR_TBTFE', 'CEC_CSR_TSOM', 'CEC_CSR_TEOM', 'CEC_CSR_TERR',
    'CEC_CSR_TBTRF', 'CEC_CSR_RSOM', 'CEC_CSR_REOM', 'CEC_CSR_RERR', 'CEC_CSR_RBTF',
    'CEC_TXD_TXD', 'CEC_RXD_RXD', 'TIM_CR1_CEN', 'TIM_CR1_UDIS', 'TIM_CR1_URS',
    'TIM_CR1_OPM', 'TIM_CR1_DIR', 'TIM_CR1_CMS', 'TIM_CR1_CMS_0', 'TIM_CR1_CMS_1',
    'TIM_CR1_ARPE', 'TIM_CR1_CKD', 'TIM_CR1_CKD_0', 'TIM_CR1_CKD_1', 'TIM_CR2_CCPC',
    'TIM_CR2_CCUS', 'TIM_CR2_CCDS', 'TIM_CR2_MMS', 'TIM_CR2_MMS_0', 'TIM_CR2_MMS_1',
    'TIM_CR2_MMS_2', 'TIM_CR2_TI1S', 'TIM_CR2_OIS1', 'TIM_CR2_OIS1N', 'TIM_CR2_OIS2',
    'TIM_CR2_OIS2N', 'TIM_CR2_OIS3', 'TIM_CR2_OIS3N', 'TIM_CR2_OIS4', 'TIM_SMCR_SMS',
    'TIM_SMCR_SMS_0', 'TIM_SMCR_SMS_1', 'TIM_SMCR_SMS_2', 'TIM_SMCR_TS',
    'TIM_SMCR_TS_0', 'TIM_SMCR_TS_1', 'TIM_SMCR_TS_2', 'TIM_SMCR_MSM', 'TIM_SMCR_ETF',
    'TIM_SMCR_ETF_0', 'TIM_SMCR_ETF_1', 'TIM_SMCR_ETF_2', 'TIM_SMCR_ETF_3',
    'TIM_SMCR_ETPS', 'TIM_SMCR_ETPS_0', 'TIM_SMCR_ETPS_1', 'TIM_SMCR_ECE',
    'TIM_SMCR_ETP', 'TIM_DIER_UIE', 'TIM_DIER_CC1IE', 'TIM_DIER_CC2IE',
    'TIM_DIER_CC3IE', 'TIM_DIER_CC4IE', 'TIM_DIER_COMIE', 'TIM_DIER_TIE',
    'TIM_DIER_BIE', 'TIM_DIER_UDE', 'TIM_DIER_CC1DE', 'TIM_DIER_CC2DE',
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
    'TIM_DCR_DBL_2', 'TIM_DCR_DBL_3', 'TIM_DCR_DBL_4', 'TIM_DMAR_DMAB', 'RTC_CRH_SECIE',
    'RTC_CRH_ALRIE', 'RTC_CRH_OWIE', 'RTC_CRL_SECF', 'RTC_CRL_ALRF', 'RTC_CRL_OWF',
    'RTC_CRL_RSF', 'RTC_CRL_CNF', 'RTC_CRL_RTOFF', 'RTC_PRLH_PRL', 'RTC_PRLL_PRL',
    'RTC_DIVH_RTC_DIV', 'RTC_DIVL_RTC_DIV', 'RTC_CNTH_RTC_CNT', 'RTC_CNTL_RTC_CNT',
    'RTC_ALRH_RTC_ALR', 'RTC_ALRL_RTC_ALR', 'IWDG_KR_KEY', 'IWDG_PR_PR', 'IWDG_PR_PR_0',
    'IWDG_PR_PR_1', 'IWDG_PR_PR_2', 'IWDG_RLR_RL', 'IWDG_SR_PVU', 'IWDG_SR_RVU',
    'WWDG_CR_T', 'WWDG_CR_T0', 'WWDG_CR_T1', 'WWDG_CR_T2', 'WWDG_CR_T3', 'WWDG_CR_T4',
    'WWDG_CR_T5', 'WWDG_CR_T6', 'WWDG_CR_WDGA', 'WWDG_CFR_W', 'WWDG_CFR_W0',
    'WWDG_CFR_W1', 'WWDG_CFR_W2', 'WWDG_CFR_W3', 'WWDG_CFR_W4', 'WWDG_CFR_W5',
    'WWDG_CFR_W6', 'WWDG_CFR_WDGTB', 'WWDG_CFR_WDGTB0', 'WWDG_CFR_WDGTB1',
    'WWDG_CFR_EWI', 'WWDG_SR_EWIF', 'FSMC_BCR1_MBKEN', 'FSMC_BCR1_MUXEN',
    'FSMC_BCR1_MTYP', 'FSMC_BCR1_MTYP_0', 'FSMC_BCR1_MTYP_1', 'FSMC_BCR1_MWID',
    'FSMC_BCR1_MWID_0', 'FSMC_BCR1_MWID_1', 'FSMC_BCR1_FACCEN', 'FSMC_BCR1_BURSTEN',
    'FSMC_BCR1_WAITPOL', 'FSMC_BCR1_WRAPMOD', 'FSMC_BCR1_WAITCFG', 'FSMC_BCR1_WREN',
    'FSMC_BCR1_WAITEN', 'FSMC_BCR1_EXTMOD', 'FSMC_BCR1_ASYNCWAIT', 'FSMC_BCR1_CBURSTRW',
    'FSMC_BCR2_MBKEN', 'FSMC_BCR2_MUXEN', 'FSMC_BCR2_MTYP', 'FSMC_BCR2_MTYP_0',
    'FSMC_BCR2_MTYP_1', 'FSMC_BCR2_MWID', 'FSMC_BCR2_MWID_0', 'FSMC_BCR2_MWID_1',
    'FSMC_BCR2_FACCEN', 'FSMC_BCR2_BURSTEN', 'FSMC_BCR2_WAITPOL', 'FSMC_BCR2_WRAPMOD',
    'FSMC_BCR2_WAITCFG', 'FSMC_BCR2_WREN', 'FSMC_BCR2_WAITEN', 'FSMC_BCR2_EXTMOD',
    'FSMC_BCR2_ASYNCWAIT', 'FSMC_BCR2_CBURSTRW', 'FSMC_BCR3_MBKEN', 'FSMC_BCR3_MUXEN',
    'FSMC_BCR3_MTYP', 'FSMC_BCR3_MTYP_0', 'FSMC_BCR3_MTYP_1', 'FSMC_BCR3_MWID',
    'FSMC_BCR3_MWID_0', 'FSMC_BCR3_MWID_1', 'FSMC_BCR3_FACCEN', 'FSMC_BCR3_BURSTEN',
    'FSMC_BCR3_WAITPOL', 'FSMC_BCR3_WRAPMOD', 'FSMC_BCR3_WAITCFG', 'FSMC_BCR3_WREN',
    'FSMC_BCR3_WAITEN', 'FSMC_BCR3_EXTMOD', 'FSMC_BCR3_ASYNCWAIT', 'FSMC_BCR3_CBURSTRW',
    'FSMC_BCR4_MBKEN', 'FSMC_BCR4_MUXEN', 'FSMC_BCR4_MTYP', 'FSMC_BCR4_MTYP_0',
    'FSMC_BCR4_MTYP_1', 'FSMC_BCR4_MWID', 'FSMC_BCR4_MWID_0', 'FSMC_BCR4_MWID_1',
    'FSMC_BCR4_FACCEN', 'FSMC_BCR4_BURSTEN', 'FSMC_BCR4_WAITPOL', 'FSMC_BCR4_WRAPMOD',
    'FSMC_BCR4_WAITCFG', 'FSMC_BCR4_WREN', 'FSMC_BCR4_WAITEN', 'FSMC_BCR4_EXTMOD',
    'FSMC_BCR4_ASYNCWAIT', 'FSMC_BCR4_CBURSTRW', 'FSMC_BTR1_ADDSET',
    'FSMC_BTR1_ADDSET_0', 'FSMC_BTR1_ADDSET_1', 'FSMC_BTR1_ADDSET_2',
    'FSMC_BTR1_ADDSET_3', 'FSMC_BTR1_ADDHLD', 'FSMC_BTR1_ADDHLD_0',
    'FSMC_BTR1_ADDHLD_1', 'FSMC_BTR1_ADDHLD_2', 'FSMC_BTR1_ADDHLD_3',
    'FSMC_BTR1_DATAST', 'FSMC_BTR1_DATAST_0', 'FSMC_BTR1_DATAST_1',
    'FSMC_BTR1_DATAST_2', 'FSMC_BTR1_DATAST_3', 'FSMC_BTR1_BUSTURN',
    'FSMC_BTR1_BUSTURN_0', 'FSMC_BTR1_BUSTURN_1', 'FSMC_BTR1_BUSTURN_2',
    'FSMC_BTR1_BUSTURN_3', 'FSMC_BTR1_CLKDIV', 'FSMC_BTR1_CLKDIV_0',
    'FSMC_BTR1_CLKDIV_1', 'FSMC_BTR1_CLKDIV_2', 'FSMC_BTR1_CLKDIV_3',
    'FSMC_BTR1_DATLAT', 'FSMC_BTR1_DATLAT_0', 'FSMC_BTR1_DATLAT_1',
    'FSMC_BTR1_DATLAT_2', 'FSMC_BTR1_DATLAT_3', 'FSMC_BTR1_ACCMOD',
    'FSMC_BTR1_ACCMOD_0', 'FSMC_BTR1_ACCMOD_1', 'FSMC_BTR2_ADDSET',
    'FSMC_BTR2_ADDSET_0', 'FSMC_BTR2_ADDSET_1', 'FSMC_BTR2_ADDSET_2',
    'FSMC_BTR2_ADDSET_3', 'FSMC_BTR2_ADDHLD', 'FSMC_BTR2_ADDHLD_0',
    'FSMC_BTR2_ADDHLD_1', 'FSMC_BTR2_ADDHLD_2', 'FSMC_BTR2_ADDHLD_3',
    'FSMC_BTR2_DATAST', 'FSMC_BTR2_DATAST_0', 'FSMC_BTR2_DATAST_1',
    'FSMC_BTR2_DATAST_2', 'FSMC_BTR2_DATAST_3', 'FSMC_BTR2_BUSTURN',
    'FSMC_BTR2_BUSTURN_0', 'FSMC_BTR2_BUSTURN_1', 'FSMC_BTR2_BUSTURN_2',
    'FSMC_BTR2_BUSTURN_3', 'FSMC_BTR2_CLKDIV', 'FSMC_BTR2_CLKDIV_0',
    'FSMC_BTR2_CLKDIV_1', 'FSMC_BTR2_CLKDIV_2', 'FSMC_BTR2_CLKDIV_3',
    'FSMC_BTR2_DATLAT', 'FSMC_BTR2_DATLAT_0', 'FSMC_BTR2_DATLAT_1',
    'FSMC_BTR2_DATLAT_2', 'FSMC_BTR2_DATLAT_3', 'FSMC_BTR2_ACCMOD',
    'FSMC_BTR2_ACCMOD_0', 'FSMC_BTR2_ACCMOD_1', 'FSMC_BTR3_ADDSET',
    'FSMC_BTR3_ADDSET_0', 'FSMC_BTR3_ADDSET_1', 'FSMC_BTR3_ADDSET_2',
    'FSMC_BTR3_ADDSET_3', 'FSMC_BTR3_ADDHLD', 'FSMC_BTR3_ADDHLD_0',
    'FSMC_BTR3_ADDHLD_1', 'FSMC_BTR3_ADDHLD_2', 'FSMC_BTR3_ADDHLD_3',
    'FSMC_BTR3_DATAST', 'FSMC_BTR3_DATAST_0', 'FSMC_BTR3_DATAST_1',
    'FSMC_BTR3_DATAST_2', 'FSMC_BTR3_DATAST_3', 'FSMC_BTR3_BUSTURN',
    'FSMC_BTR3_BUSTURN_0', 'FSMC_BTR3_BUSTURN_1', 'FSMC_BTR3_BUSTURN_2',
    'FSMC_BTR3_BUSTURN_3', 'FSMC_BTR3_CLKDIV', 'FSMC_BTR3_CLKDIV_0',
    'FSMC_BTR3_CLKDIV_1', 'FSMC_BTR3_CLKDIV_2', 'FSMC_BTR3_CLKDIV_3',
    'FSMC_BTR3_DATLAT', 'FSMC_BTR3_DATLAT_0', 'FSMC_BTR3_DATLAT_1',
    'FSMC_BTR3_DATLAT_2', 'FSMC_BTR3_DATLAT_3', 'FSMC_BTR3_ACCMOD',
    'FSMC_BTR3_ACCMOD_0', 'FSMC_BTR3_ACCMOD_1', 'FSMC_BTR4_ADDSET',
    'FSMC_BTR4_ADDSET_0', 'FSMC_BTR4_ADDSET_1', 'FSMC_BTR4_ADDSET_2',
    'FSMC_BTR4_ADDSET_3', 'FSMC_BTR4_ADDHLD', 'FSMC_BTR4_ADDHLD_0',
    'FSMC_BTR4_ADDHLD_1', 'FSMC_BTR4_ADDHLD_2', 'FSMC_BTR4_ADDHLD_3',
    'FSMC_BTR4_DATAST', 'FSMC_BTR4_DATAST_0', 'FSMC_BTR4_DATAST_1',
    'FSMC_BTR4_DATAST_2', 'FSMC_BTR4_DATAST_3', 'FSMC_BTR4_BUSTURN',
    'FSMC_BTR4_BUSTURN_0', 'FSMC_BTR4_BUSTURN_1', 'FSMC_BTR4_BUSTURN_2',
    'FSMC_BTR4_BUSTURN_3', 'FSMC_BTR4_CLKDIV', 'FSMC_BTR4_CLKDIV_0',
    'FSMC_BTR4_CLKDIV_1', 'FSMC_BTR4_CLKDIV_2', 'FSMC_BTR4_CLKDIV_3',
    'FSMC_BTR4_DATLAT', 'FSMC_BTR4_DATLAT_0', 'FSMC_BTR4_DATLAT_1',
    'FSMC_BTR4_DATLAT_2', 'FSMC_BTR4_DATLAT_3', 'FSMC_BTR4_ACCMOD',
    'FSMC_BTR4_ACCMOD_0', 'FSMC_BTR4_ACCMOD_1', 'FSMC_BWTR1_ADDSET',
    'FSMC_BWTR1_ADDSET_0', 'FSMC_BWTR1_ADDSET_1', 'FSMC_BWTR1_ADDSET_2',
    'FSMC_BWTR1_ADDSET_3', 'FSMC_BWTR1_ADDHLD', 'FSMC_BWTR1_ADDHLD_0',
    'FSMC_BWTR1_ADDHLD_1', 'FSMC_BWTR1_ADDHLD_2', 'FSMC_BWTR1_ADDHLD_3',
    'FSMC_BWTR1_DATAST', 'FSMC_BWTR1_DATAST_0', 'FSMC_BWTR1_DATAST_1',
    'FSMC_BWTR1_DATAST_2', 'FSMC_BWTR1_DATAST_3', 'FSMC_BWTR1_CLKDIV',
    'FSMC_BWTR1_CLKDIV_0', 'FSMC_BWTR1_CLKDIV_1', 'FSMC_BWTR1_CLKDIV_2',
    'FSMC_BWTR1_CLKDIV_3', 'FSMC_BWTR1_DATLAT', 'FSMC_BWTR1_DATLAT_0',
    'FSMC_BWTR1_DATLAT_1', 'FSMC_BWTR1_DATLAT_2', 'FSMC_BWTR1_DATLAT_3',
    'FSMC_BWTR1_ACCMOD', 'FSMC_BWTR1_ACCMOD_0', 'FSMC_BWTR1_ACCMOD_1',
    'FSMC_BWTR2_ADDSET', 'FSMC_BWTR2_ADDSET_0', 'FSMC_BWTR2_ADDSET_1',
    'FSMC_BWTR2_ADDSET_2', 'FSMC_BWTR2_ADDSET_3', 'FSMC_BWTR2_ADDHLD',
    'FSMC_BWTR2_ADDHLD_0', 'FSMC_BWTR2_ADDHLD_1', 'FSMC_BWTR2_ADDHLD_2',
    'FSMC_BWTR2_ADDHLD_3', 'FSMC_BWTR2_DATAST', 'FSMC_BWTR2_DATAST_0',
    'FSMC_BWTR2_DATAST_1', 'FSMC_BWTR2_DATAST_2', 'FSMC_BWTR2_DATAST_3',
    'FSMC_BWTR2_CLKDIV', 'FSMC_BWTR2_CLKDIV_0', 'FSMC_BWTR2_CLKDIV_1',
    'FSMC_BWTR2_CLKDIV_2', 'FSMC_BWTR2_CLKDIV_3', 'FSMC_BWTR2_DATLAT',
    'FSMC_BWTR2_DATLAT_0', 'FSMC_BWTR2_DATLAT_1', 'FSMC_BWTR2_DATLAT_2',
    'FSMC_BWTR2_DATLAT_3', 'FSMC_BWTR2_ACCMOD', 'FSMC_BWTR2_ACCMOD_0',
    'FSMC_BWTR2_ACCMOD_1', 'FSMC_BWTR3_ADDSET', 'FSMC_BWTR3_ADDSET_0',
    'FSMC_BWTR3_ADDSET_1', 'FSMC_BWTR3_ADDSET_2', 'FSMC_BWTR3_ADDSET_3',
    'FSMC_BWTR3_ADDHLD', 'FSMC_BWTR3_ADDHLD_0', 'FSMC_BWTR3_ADDHLD_1',
    'FSMC_BWTR3_ADDHLD_2', 'FSMC_BWTR3_ADDHLD_3', 'FSMC_BWTR3_DATAST',
    'FSMC_BWTR3_DATAST_0', 'FSMC_BWTR3_DATAST_1', 'FSMC_BWTR3_DATAST_2',
    'FSMC_BWTR3_DATAST_3', 'FSMC_BWTR3_CLKDIV', 'FSMC_BWTR3_CLKDIV_0',
    'FSMC_BWTR3_CLKDIV_1', 'FSMC_BWTR3_CLKDIV_2', 'FSMC_BWTR3_CLKDIV_3',
    'FSMC_BWTR3_DATLAT', 'FSMC_BWTR3_DATLAT_0', 'FSMC_BWTR3_DATLAT_1',
    'FSMC_BWTR3_DATLAT_2', 'FSMC_BWTR3_DATLAT_3', 'FSMC_BWTR3_ACCMOD',
    'FSMC_BWTR3_ACCMOD_0', 'FSMC_BWTR3_ACCMOD_1', 'FSMC_BWTR4_ADDSET',
    'FSMC_BWTR4_ADDSET_0', 'FSMC_BWTR4_ADDSET_1', 'FSMC_BWTR4_ADDSET_2',
    'FSMC_BWTR4_ADDSET_3', 'FSMC_BWTR4_ADDHLD', 'FSMC_BWTR4_ADDHLD_0',
    'FSMC_BWTR4_ADDHLD_1', 'FSMC_BWTR4_ADDHLD_2', 'FSMC_BWTR4_ADDHLD_3',
    'FSMC_BWTR4_DATAST', 'FSMC_BWTR4_DATAST_0', 'FSMC_BWTR4_DATAST_1',
    'FSMC_BWTR4_DATAST_2', 'FSMC_BWTR4_DATAST_3', 'FSMC_BWTR4_CLKDIV',
    'FSMC_BWTR4_CLKDIV_0', 'FSMC_BWTR4_CLKDIV_1', 'FSMC_BWTR4_CLKDIV_2',
    'FSMC_BWTR4_CLKDIV_3', 'FSMC_BWTR4_DATLAT', 'FSMC_BWTR4_DATLAT_0',
    'FSMC_BWTR4_DATLAT_1', 'FSMC_BWTR4_DATLAT_2', 'FSMC_BWTR4_DATLAT_3',
    'FSMC_BWTR4_ACCMOD', 'FSMC_BWTR4_ACCMOD_0', 'FSMC_BWTR4_ACCMOD_1',
    'FSMC_PCR2_PWAITEN', 'FSMC_PCR2_PBKEN', 'FSMC_PCR2_PTYP', 'FSMC_PCR2_PWID',
    'FSMC_PCR2_PWID_0', 'FSMC_PCR2_PWID_1', 'FSMC_PCR2_ECCEN', 'FSMC_PCR2_TCLR',
    'FSMC_PCR2_TCLR_0', 'FSMC_PCR2_TCLR_1', 'FSMC_PCR2_TCLR_2', 'FSMC_PCR2_TCLR_3',
    'FSMC_PCR2_TAR', 'FSMC_PCR2_TAR_0', 'FSMC_PCR2_TAR_1', 'FSMC_PCR2_TAR_2',
    'FSMC_PCR2_TAR_3', 'FSMC_PCR2_ECCPS', 'FSMC_PCR2_ECCPS_0', 'FSMC_PCR2_ECCPS_1',
    'FSMC_PCR2_ECCPS_2', 'FSMC_PCR3_PWAITEN', 'FSMC_PCR3_PBKEN', 'FSMC_PCR3_PTYP',
    'FSMC_PCR3_PWID', 'FSMC_PCR3_PWID_0', 'FSMC_PCR3_PWID_1', 'FSMC_PCR3_ECCEN',
    'FSMC_PCR3_TCLR', 'FSMC_PCR3_TCLR_0', 'FSMC_PCR3_TCLR_1', 'FSMC_PCR3_TCLR_2',
    'FSMC_PCR3_TCLR_3', 'FSMC_PCR3_TAR', 'FSMC_PCR3_TAR_0', 'FSMC_PCR3_TAR_1',
    'FSMC_PCR3_TAR_2', 'FSMC_PCR3_TAR_3', 'FSMC_PCR3_ECCPS', 'FSMC_PCR3_ECCPS_0',
    'FSMC_PCR3_ECCPS_1', 'FSMC_PCR3_ECCPS_2', 'FSMC_PCR4_PWAITEN', 'FSMC_PCR4_PBKEN',
    'FSMC_PCR4_PTYP', 'FSMC_PCR4_PWID', 'FSMC_PCR4_PWID_0', 'FSMC_PCR4_PWID_1',
    'FSMC_PCR4_ECCEN', 'FSMC_PCR4_TCLR', 'FSMC_PCR4_TCLR_0', 'FSMC_PCR4_TCLR_1',
    'FSMC_PCR4_TCLR_2', 'FSMC_PCR4_TCLR_3', 'FSMC_PCR4_TAR', 'FSMC_PCR4_TAR_0',
    'FSMC_PCR4_TAR_1', 'FSMC_PCR4_TAR_2', 'FSMC_PCR4_TAR_3', 'FSMC_PCR4_ECCPS',
    'FSMC_PCR4_ECCPS_0', 'FSMC_PCR4_ECCPS_1', 'FSMC_PCR4_ECCPS_2', 'FSMC_SR2_IRS',
    'FSMC_SR2_ILS', 'FSMC_SR2_IFS', 'FSMC_SR2_IREN', 'FSMC_SR2_ILEN', 'FSMC_SR2_IFEN',
    'FSMC_SR2_FEMPT', 'FSMC_SR3_IRS', 'FSMC_SR3_ILS', 'FSMC_SR3_IFS', 'FSMC_SR3_IREN',
    'FSMC_SR3_ILEN', 'FSMC_SR3_IFEN', 'FSMC_SR3_FEMPT', 'FSMC_SR4_IRS', 'FSMC_SR4_ILS',
    'FSMC_SR4_IFS', 'FSMC_SR4_IREN', 'FSMC_SR4_ILEN', 'FSMC_SR4_IFEN', 'FSMC_SR4_FEMPT',
    'FSMC_PMEM2_MEMSET2', 'FSMC_PMEM2_MEMSET2_0', 'FSMC_PMEM2_MEMSET2_1',
    'FSMC_PMEM2_MEMSET2_2', 'FSMC_PMEM2_MEMSET2_3', 'FSMC_PMEM2_MEMSET2_4',
    'FSMC_PMEM2_MEMSET2_5', 'FSMC_PMEM2_MEMSET2_6', 'FSMC_PMEM2_MEMSET2_7',
    'FSMC_PMEM2_MEMWAIT2', 'FSMC_PMEM2_MEMWAIT2_0', 'FSMC_PMEM2_MEMWAIT2_1',
    'FSMC_PMEM2_MEMWAIT2_2', 'FSMC_PMEM2_MEMWAIT2_3', 'FSMC_PMEM2_MEMWAIT2_4',
    'FSMC_PMEM2_MEMWAIT2_5', 'FSMC_PMEM2_MEMWAIT2_6', 'FSMC_PMEM2_MEMWAIT2_7',
    'FSMC_PMEM2_MEMHOLD2', 'FSMC_PMEM2_MEMHOLD2_0', 'FSMC_PMEM2_MEMHOLD2_1',
    'FSMC_PMEM2_MEMHOLD2_2', 'FSMC_PMEM2_MEMHOLD2_3', 'FSMC_PMEM2_MEMHOLD2_4',
    'FSMC_PMEM2_MEMHOLD2_5', 'FSMC_PMEM2_MEMHOLD2_6', 'FSMC_PMEM2_MEMHOLD2_7',
    'FSMC_PMEM2_MEMHIZ2', 'FSMC_PMEM2_MEMHIZ2_0', 'FSMC_PMEM2_MEMHIZ2_1',
    'FSMC_PMEM2_MEMHIZ2_2', 'FSMC_PMEM2_MEMHIZ2_3', 'FSMC_PMEM2_MEMHIZ2_4',
    'FSMC_PMEM2_MEMHIZ2_5', 'FSMC_PMEM2_MEMHIZ2_6', 'FSMC_PMEM2_MEMHIZ2_7',
    'FSMC_PMEM3_MEMSET3', 'FSMC_PMEM3_MEMSET3_0', 'FSMC_PMEM3_MEMSET3_1',
    'FSMC_PMEM3_MEMSET3_2', 'FSMC_PMEM3_MEMSET3_3', 'FSMC_PMEM3_MEMSET3_4',
    'FSMC_PMEM3_MEMSET3_5', 'FSMC_PMEM3_MEMSET3_6', 'FSMC_PMEM3_MEMSET3_7',
    'FSMC_PMEM3_MEMWAIT3', 'FSMC_PMEM3_MEMWAIT3_0', 'FSMC_PMEM3_MEMWAIT3_1',
    'FSMC_PMEM3_MEMWAIT3_2', 'FSMC_PMEM3_MEMWAIT3_3', 'FSMC_PMEM3_MEMWAIT3_4',
    'FSMC_PMEM3_MEMWAIT3_5', 'FSMC_PMEM3_MEMWAIT3_6', 'FSMC_PMEM3_MEMWAIT3_7',
    'FSMC_PMEM3_MEMHOLD3', 'FSMC_PMEM3_MEMHOLD3_0', 'FSMC_PMEM3_MEMHOLD3_1',
    'FSMC_PMEM3_MEMHOLD3_2', 'FSMC_PMEM3_MEMHOLD3_3', 'FSMC_PMEM3_MEMHOLD3_4',
    'FSMC_PMEM3_MEMHOLD3_5', 'FSMC_PMEM3_MEMHOLD3_6', 'FSMC_PMEM3_MEMHOLD3_7',
    'FSMC_PMEM3_MEMHIZ3', 'FSMC_PMEM3_MEMHIZ3_0', 'FSMC_PMEM3_MEMHIZ3_1',
    'FSMC_PMEM3_MEMHIZ3_2', 'FSMC_PMEM3_MEMHIZ3_3', 'FSMC_PMEM3_MEMHIZ3_4',
    'FSMC_PMEM3_MEMHIZ3_5', 'FSMC_PMEM3_MEMHIZ3_6', 'FSMC_PMEM3_MEMHIZ3_7',
    'FSMC_PMEM4_MEMSET4', 'FSMC_PMEM4_MEMSET4_0', 'FSMC_PMEM4_MEMSET4_1',
    'FSMC_PMEM4_MEMSET4_2', 'FSMC_PMEM4_MEMSET4_3', 'FSMC_PMEM4_MEMSET4_4',
    'FSMC_PMEM4_MEMSET4_5', 'FSMC_PMEM4_MEMSET4_6', 'FSMC_PMEM4_MEMSET4_7',
    'FSMC_PMEM4_MEMWAIT4', 'FSMC_PMEM4_MEMWAIT4_0', 'FSMC_PMEM4_MEMWAIT4_1',
    'FSMC_PMEM4_MEMWAIT4_2', 'FSMC_PMEM4_MEMWAIT4_3', 'FSMC_PMEM4_MEMWAIT4_4',
    'FSMC_PMEM4_MEMWAIT4_5', 'FSMC_PMEM4_MEMWAIT4_6', 'FSMC_PMEM4_MEMWAIT4_7',
    'FSMC_PMEM4_MEMHOLD4', 'FSMC_PMEM4_MEMHOLD4_0', 'FSMC_PMEM4_MEMHOLD4_1',
    'FSMC_PMEM4_MEMHOLD4_2', 'FSMC_PMEM4_MEMHOLD4_3', 'FSMC_PMEM4_MEMHOLD4_4',
    'FSMC_PMEM4_MEMHOLD4_5', 'FSMC_PMEM4_MEMHOLD4_6', 'FSMC_PMEM4_MEMHOLD4_7',
    'FSMC_PMEM4_MEMHIZ4', 'FSMC_PMEM4_MEMHIZ4_0', 'FSMC_PMEM4_MEMHIZ4_1',
    'FSMC_PMEM4_MEMHIZ4_2', 'FSMC_PMEM4_MEMHIZ4_3', 'FSMC_PMEM4_MEMHIZ4_4',
    'FSMC_PMEM4_MEMHIZ4_5', 'FSMC_PMEM4_MEMHIZ4_6', 'FSMC_PMEM4_MEMHIZ4_7',
    'FSMC_PATT2_ATTSET2', 'FSMC_PATT2_ATTSET2_0', 'FSMC_PATT2_ATTSET2_1',
    'FSMC_PATT2_ATTSET2_2', 'FSMC_PATT2_ATTSET2_3', 'FSMC_PATT2_ATTSET2_4',
    'FSMC_PATT2_ATTSET2_5', 'FSMC_PATT2_ATTSET2_6', 'FSMC_PATT2_ATTSET2_7',
    'FSMC_PATT2_ATTWAIT2', 'FSMC_PATT2_ATTWAIT2_0', 'FSMC_PATT2_ATTWAIT2_1',
    'FSMC_PATT2_ATTWAIT2_2', 'FSMC_PATT2_ATTWAIT2_3', 'FSMC_PATT2_ATTWAIT2_4',
    'FSMC_PATT2_ATTWAIT2_5', 'FSMC_PATT2_ATTWAIT2_6', 'FSMC_PATT2_ATTWAIT2_7',
    'FSMC_PATT2_ATTHOLD2', 'FSMC_PATT2_ATTHOLD2_0', 'FSMC_PATT2_ATTHOLD2_1',
    'FSMC_PATT2_ATTHOLD2_2', 'FSMC_PATT2_ATTHOLD2_3', 'FSMC_PATT2_ATTHOLD2_4',
    'FSMC_PATT2_ATTHOLD2_5', 'FSMC_PATT2_ATTHOLD2_6', 'FSMC_PATT2_ATTHOLD2_7',
    'FSMC_PATT2_ATTHIZ2', 'FSMC_PATT2_ATTHIZ2_0', 'FSMC_PATT2_ATTHIZ2_1',
    'FSMC_PATT2_ATTHIZ2_2', 'FSMC_PATT2_ATTHIZ2_3', 'FSMC_PATT2_ATTHIZ2_4',
    'FSMC_PATT2_ATTHIZ2_5', 'FSMC_PATT2_ATTHIZ2_6', 'FSMC_PATT2_ATTHIZ2_7',
    'FSMC_PATT3_ATTSET3', 'FSMC_PATT3_ATTSET3_0', 'FSMC_PATT3_ATTSET3_1',
    'FSMC_PATT3_ATTSET3_2', 'FSMC_PATT3_ATTSET3_3', 'FSMC_PATT3_ATTSET3_4',
    'FSMC_PATT3_ATTSET3_5', 'FSMC_PATT3_ATTSET3_6', 'FSMC_PATT3_ATTSET3_7',
    'FSMC_PATT3_ATTWAIT3', 'FSMC_PATT3_ATTWAIT3_0', 'FSMC_PATT3_ATTWAIT3_1',
    'FSMC_PATT3_ATTWAIT3_2', 'FSMC_PATT3_ATTWAIT3_3', 'FSMC_PATT3_ATTWAIT3_4',
    'FSMC_PATT3_ATTWAIT3_5', 'FSMC_PATT3_ATTWAIT3_6', 'FSMC_PATT3_ATTWAIT3_7',
    'FSMC_PATT3_ATTHOLD3', 'FSMC_PATT3_ATTHOLD3_0', 'FSMC_PATT3_ATTHOLD3_1',
    'FSMC_PATT3_ATTHOLD3_2', 'FSMC_PATT3_ATTHOLD3_3', 'FSMC_PATT3_ATTHOLD3_4',
    'FSMC_PATT3_ATTHOLD3_5', 'FSMC_PATT3_ATTHOLD3_6', 'FSMC_PATT3_ATTHOLD3_7',
    'FSMC_PATT3_ATTHIZ3', 'FSMC_PATT3_ATTHIZ3_0', 'FSMC_PATT3_ATTHIZ3_1',
    'FSMC_PATT3_ATTHIZ3_2', 'FSMC_PATT3_ATTHIZ3_3', 'FSMC_PATT3_ATTHIZ3_4',
    'FSMC_PATT3_ATTHIZ3_5', 'FSMC_PATT3_ATTHIZ3_6', 'FSMC_PATT3_ATTHIZ3_7',
    'FSMC_PATT4_ATTSET4', 'FSMC_PATT4_ATTSET4_0', 'FSMC_PATT4_ATTSET4_1',
    'FSMC_PATT4_ATTSET4_2', 'FSMC_PATT4_ATTSET4_3', 'FSMC_PATT4_ATTSET4_4',
    'FSMC_PATT4_ATTSET4_5', 'FSMC_PATT4_ATTSET4_6', 'FSMC_PATT4_ATTSET4_7',
    'FSMC_PATT4_ATTWAIT4', 'FSMC_PATT4_ATTWAIT4_0', 'FSMC_PATT4_ATTWAIT4_1',
    'FSMC_PATT4_ATTWAIT4_2', 'FSMC_PATT4_ATTWAIT4_3', 'FSMC_PATT4_ATTWAIT4_4',
    'FSMC_PATT4_ATTWAIT4_5', 'FSMC_PATT4_ATTWAIT4_6', 'FSMC_PATT4_ATTWAIT4_7',
    'FSMC_PATT4_ATTHOLD4', 'FSMC_PATT4_ATTHOLD4_0', 'FSMC_PATT4_ATTHOLD4_1',
    'FSMC_PATT4_ATTHOLD4_2', 'FSMC_PATT4_ATTHOLD4_3', 'FSMC_PATT4_ATTHOLD4_4',
    'FSMC_PATT4_ATTHOLD4_5', 'FSMC_PATT4_ATTHOLD4_6', 'FSMC_PATT4_ATTHOLD4_7',
    'FSMC_PATT4_ATTHIZ4', 'FSMC_PATT4_ATTHIZ4_0', 'FSMC_PATT4_ATTHIZ4_1',
    'FSMC_PATT4_ATTHIZ4_2', 'FSMC_PATT4_ATTHIZ4_3', 'FSMC_PATT4_ATTHIZ4_4',
    'FSMC_PATT4_ATTHIZ4_5', 'FSMC_PATT4_ATTHIZ4_6', 'FSMC_PATT4_ATTHIZ4_7',
    'FSMC_PIO4_IOSET4', 'FSMC_PIO4_IOSET4_0', 'FSMC_PIO4_IOSET4_1',
    'FSMC_PIO4_IOSET4_2', 'FSMC_PIO4_IOSET4_3', 'FSMC_PIO4_IOSET4_4',
    'FSMC_PIO4_IOSET4_5', 'FSMC_PIO4_IOSET4_6', 'FSMC_PIO4_IOSET4_7',
    'FSMC_PIO4_IOWAIT4', 'FSMC_PIO4_IOWAIT4_0', 'FSMC_PIO4_IOWAIT4_1',
    'FSMC_PIO4_IOWAIT4_2', 'FSMC_PIO4_IOWAIT4_3', 'FSMC_PIO4_IOWAIT4_4',
    'FSMC_PIO4_IOWAIT4_5', 'FSMC_PIO4_IOWAIT4_6', 'FSMC_PIO4_IOWAIT4_7',
    'FSMC_PIO4_IOHOLD4', 'FSMC_PIO4_IOHOLD4_0', 'FSMC_PIO4_IOHOLD4_1',
    'FSMC_PIO4_IOHOLD4_2', 'FSMC_PIO4_IOHOLD4_3', 'FSMC_PIO4_IOHOLD4_4',
    'FSMC_PIO4_IOHOLD4_5', 'FSMC_PIO4_IOHOLD4_6', 'FSMC_PIO4_IOHOLD4_7',
    'FSMC_PIO4_IOHIZ4', 'FSMC_PIO4_IOHIZ4_0', 'FSMC_PIO4_IOHIZ4_1',
    'FSMC_PIO4_IOHIZ4_2', 'FSMC_PIO4_IOHIZ4_3', 'FSMC_PIO4_IOHIZ4_4',
    'FSMC_PIO4_IOHIZ4_5', 'FSMC_PIO4_IOHIZ4_6', 'FSMC_PIO4_IOHIZ4_7', 'FSMC_ECCR2_ECC2',
    'FSMC_ECCR3_ECC3', 'SDIO_POWER_PWRCTRL', 'SDIO_POWER_PWRCTRL_0',
    'SDIO_POWER_PWRCTRL_1', 'SDIO_CLKCR_CLKDIV', 'SDIO_CLKCR_CLKEN',
    'SDIO_CLKCR_PWRSAV', 'SDIO_CLKCR_BYPASS', 'SDIO_CLKCR_WIDBUS',
    'SDIO_CLKCR_WIDBUS_0', 'SDIO_CLKCR_WIDBUS_1', 'SDIO_CLKCR_NEGEDGE',
    'SDIO_CLKCR_HWFC_EN', 'SDIO_ARG_CMDARG', 'SDIO_CMD_CMDINDEX', 'SDIO_CMD_WAITRESP',
    'SDIO_CMD_WAITRESP_0', 'SDIO_CMD_WAITRESP_1', 'SDIO_CMD_WAITINT',
    'SDIO_CMD_WAITPEND', 'SDIO_CMD_CPSMEN', 'SDIO_CMD_SDIOSUSPEND',
    'SDIO_CMD_ENCMDCOMPL', 'SDIO_CMD_NIEN', 'SDIO_CMD_CEATACMD', 'SDIO_RESPCMD_RESPCMD',
    'SDIO_RESP0_CARDSTATUS0', 'SDIO_RESP1_CARDSTATUS1', 'SDIO_RESP2_CARDSTATUS2',
    'SDIO_RESP3_CARDSTATUS3', 'SDIO_RESP4_CARDSTATUS4', 'SDIO_DTIMER_DATATIME',
    'SDIO_DLEN_DATALENGTH', 'SDIO_DCTRL_DTEN', 'SDIO_DCTRL_DTDIR', 'SDIO_DCTRL_DTMODE',
    'SDIO_DCTRL_DMAEN', 'SDIO_DCTRL_DBLOCKSIZE', 'SDIO_DCTRL_DBLOCKSIZE_0',
    'SDIO_DCTRL_DBLOCKSIZE_1', 'SDIO_DCTRL_DBLOCKSIZE_2', 'SDIO_DCTRL_DBLOCKSIZE_3',
    'SDIO_DCTRL_RWSTART', 'SDIO_DCTRL_RWSTOP', 'SDIO_DCTRL_RWMOD', 'SDIO_DCTRL_SDIOEN',
    'SDIO_DCOUNT_DATACOUNT', 'SDIO_STA_CCRCFAIL', 'SDIO_STA_DCRCFAIL',
    'SDIO_STA_CTIMEOUT', 'SDIO_STA_DTIMEOUT', 'SDIO_STA_TXUNDERR', 'SDIO_STA_RXOVERR',
    'SDIO_STA_CMDREND', 'SDIO_STA_CMDSENT', 'SDIO_STA_DATAEND', 'SDIO_STA_STBITERR',
    'SDIO_STA_DBCKEND', 'SDIO_STA_CMDACT', 'SDIO_STA_TXACT', 'SDIO_STA_RXACT',
    'SDIO_STA_TXFIFOHE', 'SDIO_STA_RXFIFOHF', 'SDIO_STA_TXFIFOF', 'SDIO_STA_RXFIFOF',
    'SDIO_STA_TXFIFOE', 'SDIO_STA_RXFIFOE', 'SDIO_STA_TXDAVL', 'SDIO_STA_RXDAVL',
    'SDIO_STA_SDIOIT', 'SDIO_STA_CEATAEND', 'SDIO_ICR_CCRCFAILC', 'SDIO_ICR_DCRCFAILC',
    'SDIO_ICR_CTIMEOUTC', 'SDIO_ICR_DTIMEOUTC', 'SDIO_ICR_TXUNDERRC',
    'SDIO_ICR_RXOVERRC', 'SDIO_ICR_CMDRENDC', 'SDIO_ICR_CMDSENTC', 'SDIO_ICR_DATAENDC',
    'SDIO_ICR_STBITERRC', 'SDIO_ICR_DBCKENDC', 'SDIO_ICR_SDIOITC', 'SDIO_ICR_CEATAENDC',
    'SDIO_MASK_CCRCFAILIE', 'SDIO_MASK_DCRCFAILIE', 'SDIO_MASK_CTIMEOUTIE',
    'SDIO_MASK_DTIMEOUTIE', 'SDIO_MASK_TXUNDERRIE', 'SDIO_MASK_RXOVERRIE',
    'SDIO_MASK_CMDRENDIE', 'SDIO_MASK_CMDSENTIE', 'SDIO_MASK_DATAENDIE',
    'SDIO_MASK_STBITERRIE', 'SDIO_MASK_DBCKENDIE', 'SDIO_MASK_CMDACTIE',
    'SDIO_MASK_TXACTIE', 'SDIO_MASK_RXACTIE', 'SDIO_MASK_TXFIFOHEIE',
    'SDIO_MASK_RXFIFOHFIE', 'SDIO_MASK_TXFIFOFIE', 'SDIO_MASK_RXFIFOFIE',
    'SDIO_MASK_TXFIFOEIE', 'SDIO_MASK_RXFIFOEIE', 'SDIO_MASK_TXDAVLIE',
    'SDIO_MASK_RXDAVLIE', 'SDIO_MASK_SDIOITIE', 'SDIO_MASK_CEATAENDIE',
    'SDIO_FIFOCNT_FIFOCOUNT', 'SDIO_FIFO_FIFODATA', 'USB_EP0R_EA', 'USB_EP0R_STAT_TX',
    'USB_EP0R_STAT_TX_0', 'USB_EP0R_STAT_TX_1', 'USB_EP0R_DTOG_TX', 'USB_EP0R_CTR_TX',
    'USB_EP0R_EP_KIND', 'USB_EP0R_EP_TYPE', 'USB_EP0R_EP_TYPE_0', 'USB_EP0R_EP_TYPE_1',
    'USB_EP0R_SETUP', 'USB_EP0R_STAT_RX', 'USB_EP0R_STAT_RX_0', 'USB_EP0R_STAT_RX_1',
    'USB_EP0R_DTOG_RX', 'USB_EP0R_CTR_RX', 'USB_EP1R_EA', 'USB_EP1R_STAT_TX',
    'USB_EP1R_STAT_TX_0', 'USB_EP1R_STAT_TX_1', 'USB_EP1R_DTOG_TX', 'USB_EP1R_CTR_TX',
    'USB_EP1R_EP_KIND', 'USB_EP1R_EP_TYPE', 'USB_EP1R_EP_TYPE_0', 'USB_EP1R_EP_TYPE_1',
    'USB_EP1R_SETUP', 'USB_EP1R_STAT_RX', 'USB_EP1R_STAT_RX_0', 'USB_EP1R_STAT_RX_1',
    'USB_EP1R_DTOG_RX', 'USB_EP1R_CTR_RX', 'USB_EP2R_EA', 'USB_EP2R_STAT_TX',
    'USB_EP2R_STAT_TX_0', 'USB_EP2R_STAT_TX_1', 'USB_EP2R_DTOG_TX', 'USB_EP2R_CTR_TX',
    'USB_EP2R_EP_KIND', 'USB_EP2R_EP_TYPE', 'USB_EP2R_EP_TYPE_0', 'USB_EP2R_EP_TYPE_1',
    'USB_EP2R_SETUP', 'USB_EP2R_STAT_RX', 'USB_EP2R_STAT_RX_0', 'USB_EP2R_STAT_RX_1',
    'USB_EP2R_DTOG_RX', 'USB_EP2R_CTR_RX', 'USB_EP3R_EA', 'USB_EP3R_STAT_TX',
    'USB_EP3R_STAT_TX_0', 'USB_EP3R_STAT_TX_1', 'USB_EP3R_DTOG_TX', 'USB_EP3R_CTR_TX',
    'USB_EP3R_EP_KIND', 'USB_EP3R_EP_TYPE', 'USB_EP3R_EP_TYPE_0', 'USB_EP3R_EP_TYPE_1',
    'USB_EP3R_SETUP', 'USB_EP3R_STAT_RX', 'USB_EP3R_STAT_RX_0', 'USB_EP3R_STAT_RX_1',
    'USB_EP3R_DTOG_RX', 'USB_EP3R_CTR_RX', 'USB_EP4R_EA', 'USB_EP4R_STAT_TX',
    'USB_EP4R_STAT_TX_0', 'USB_EP4R_STAT_TX_1', 'USB_EP4R_DTOG_TX', 'USB_EP4R_CTR_TX',
    'USB_EP4R_EP_KIND', 'USB_EP4R_EP_TYPE', 'USB_EP4R_EP_TYPE_0', 'USB_EP4R_EP_TYPE_1',
    'USB_EP4R_SETUP', 'USB_EP4R_STAT_RX', 'USB_EP4R_STAT_RX_0', 'USB_EP4R_STAT_RX_1',
    'USB_EP4R_DTOG_RX', 'USB_EP4R_CTR_RX', 'USB_EP5R_EA', 'USB_EP5R_STAT_TX',
    'USB_EP5R_STAT_TX_0', 'USB_EP5R_STAT_TX_1', 'USB_EP5R_DTOG_TX', 'USB_EP5R_CTR_TX',
    'USB_EP5R_EP_KIND', 'USB_EP5R_EP_TYPE', 'USB_EP5R_EP_TYPE_0', 'USB_EP5R_EP_TYPE_1',
    'USB_EP5R_SETUP', 'USB_EP5R_STAT_RX', 'USB_EP5R_STAT_RX_0', 'USB_EP5R_STAT_RX_1',
    'USB_EP5R_DTOG_RX', 'USB_EP5R_CTR_RX', 'USB_EP6R_EA', 'USB_EP6R_STAT_TX',
    'USB_EP6R_STAT_TX_0', 'USB_EP6R_STAT_TX_1', 'USB_EP6R_DTOG_TX', 'USB_EP6R_CTR_TX',
    'USB_EP6R_EP_KIND', 'USB_EP6R_EP_TYPE', 'USB_EP6R_EP_TYPE_0', 'USB_EP6R_EP_TYPE_1',
    'USB_EP6R_SETUP', 'USB_EP6R_STAT_RX', 'USB_EP6R_STAT_RX_0', 'USB_EP6R_STAT_RX_1',
    'USB_EP6R_DTOG_RX', 'USB_EP6R_CTR_RX', 'USB_EP7R_EA', 'USB_EP7R_STAT_TX',
    'USB_EP7R_STAT_TX_0', 'USB_EP7R_STAT_TX_1', 'USB_EP7R_DTOG_TX', 'USB_EP7R_CTR_TX',
    'USB_EP7R_EP_KIND', 'USB_EP7R_EP_TYPE', 'USB_EP7R_EP_TYPE_0', 'USB_EP7R_EP_TYPE_1',
    'USB_EP7R_SETUP', 'USB_EP7R_STAT_RX', 'USB_EP7R_STAT_RX_0', 'USB_EP7R_STAT_RX_1',
    'USB_EP7R_DTOG_RX', 'USB_EP7R_CTR_RX', 'USB_CNTR_FRES', 'USB_CNTR_PDWN',
    'USB_CNTR_LP_MODE', 'USB_CNTR_FSUSP', 'USB_CNTR_RESUME', 'USB_CNTR_ESOFM',
    'USB_CNTR_SOFM', 'USB_CNTR_RESETM', 'USB_CNTR_SUSPM', 'USB_CNTR_WKUPM',
    'USB_CNTR_ERRM', 'USB_CNTR_PMAOVRM', 'USB_CNTR_CTRM', 'USB_ISTR_EP_ID',
    'USB_ISTR_DIR', 'USB_ISTR_ESOF', 'USB_ISTR_SOF', 'USB_ISTR_RESET', 'USB_ISTR_SUSP',
    'USB_ISTR_WKUP', 'USB_ISTR_ERR', 'USB_ISTR_PMAOVR', 'USB_ISTR_CTR', 'USB_FNR_FN',
    'USB_FNR_LSOF', 'USB_FNR_LCK', 'USB_FNR_RXDM', 'USB_FNR_RXDP', 'USB_DADDR_ADD',
    'USB_DADDR_ADD0', 'USB_DADDR_ADD1', 'USB_DADDR_ADD2', 'USB_DADDR_ADD3',
    'USB_DADDR_ADD4', 'USB_DADDR_ADD5', 'USB_DADDR_ADD6', 'USB_DADDR_EF',
    'USB_BTABLE_BTABLE', 'USB_ADDR0_TX_ADDR0_TX', 'USB_ADDR1_TX_ADDR1_TX',
    'USB_ADDR2_TX_ADDR2_TX', 'USB_ADDR3_TX_ADDR3_TX', 'USB_ADDR4_TX_ADDR4_TX',
    'USB_ADDR5_TX_ADDR5_TX', 'USB_ADDR6_TX_ADDR6_TX', 'USB_ADDR7_TX_ADDR7_TX',
    'USB_COUNT0_TX_COUNT0_TX', 'USB_COUNT1_TX_COUNT1_TX', 'USB_COUNT2_TX_COUNT2_TX',
    'USB_COUNT3_TX_COUNT3_TX', 'USB_COUNT4_TX_COUNT4_TX', 'USB_COUNT5_TX_COUNT5_TX',
    'USB_COUNT6_TX_COUNT6_TX', 'USB_COUNT7_TX_COUNT7_TX', 'USB_COUNT0_TX_0_COUNT0_TX_0',
    'USB_COUNT0_TX_1_COUNT0_TX_1', 'USB_COUNT1_TX_0_COUNT1_TX_0',
    'USB_COUNT1_TX_1_COUNT1_TX_1', 'USB_COUNT2_TX_0_COUNT2_TX_0',
    'USB_COUNT2_TX_1_COUNT2_TX_1', 'USB_COUNT3_TX_0_COUNT3_TX_0',
    'USB_COUNT3_TX_1_COUNT3_TX_1', 'USB_COUNT4_TX_0_COUNT4_TX_0',
    'USB_COUNT4_TX_1_COUNT4_TX_1', 'USB_COUNT5_TX_0_COUNT5_TX_0',
    'USB_COUNT5_TX_1_COUNT5_TX_1', 'USB_COUNT6_TX_0_COUNT6_TX_0',
    'USB_COUNT6_TX_1_COUNT6_TX_1', 'USB_COUNT7_TX_0_COUNT7_TX_0',
    'USB_COUNT7_TX_1_COUNT7_TX_1', 'USB_ADDR0_RX_ADDR0_RX', 'USB_ADDR1_RX_ADDR1_RX',
    'USB_ADDR2_RX_ADDR2_RX', 'USB_ADDR3_RX_ADDR3_RX', 'USB_ADDR4_RX_ADDR4_RX',
    'USB_ADDR5_RX_ADDR5_RX', 'USB_ADDR6_RX_ADDR6_RX', 'USB_ADDR7_RX_ADDR7_RX',
    'USB_COUNT0_RX_COUNT0_RX', 'USB_COUNT0_RX_NUM_BLOCK', 'USB_COUNT0_RX_NUM_BLOCK_0',
    'USB_COUNT0_RX_NUM_BLOCK_1', 'USB_COUNT0_RX_NUM_BLOCK_2',
    'USB_COUNT0_RX_NUM_BLOCK_3', 'USB_COUNT0_RX_NUM_BLOCK_4', 'USB_COUNT0_RX_BLSIZE',
    'USB_COUNT1_RX_COUNT1_RX', 'USB_COUNT1_RX_NUM_BLOCK', 'USB_COUNT1_RX_NUM_BLOCK_0',
    'USB_COUNT1_RX_NUM_BLOCK_1', 'USB_COUNT1_RX_NUM_BLOCK_2',
    'USB_COUNT1_RX_NUM_BLOCK_3', 'USB_COUNT1_RX_NUM_BLOCK_4', 'USB_COUNT1_RX_BLSIZE',
    'USB_COUNT2_RX_COUNT2_RX', 'USB_COUNT2_RX_NUM_BLOCK', 'USB_COUNT2_RX_NUM_BLOCK_0',
    'USB_COUNT2_RX_NUM_BLOCK_1', 'USB_COUNT2_RX_NUM_BLOCK_2',
    'USB_COUNT2_RX_NUM_BLOCK_3', 'USB_COUNT2_RX_NUM_BLOCK_4', 'USB_COUNT2_RX_BLSIZE',
    'USB_COUNT3_RX_COUNT3_RX', 'USB_COUNT3_RX_NUM_BLOCK', 'USB_COUNT3_RX_NUM_BLOCK_0',
    'USB_COUNT3_RX_NUM_BLOCK_1', 'USB_COUNT3_RX_NUM_BLOCK_2',
    'USB_COUNT3_RX_NUM_BLOCK_3', 'USB_COUNT3_RX_NUM_BLOCK_4', 'USB_COUNT3_RX_BLSIZE',
    'USB_COUNT4_RX_COUNT4_RX', 'USB_COUNT4_RX_NUM_BLOCK', 'USB_COUNT4_RX_NUM_BLOCK_0',
    'USB_COUNT4_RX_NUM_BLOCK_1', 'USB_COUNT4_RX_NUM_BLOCK_2',
    'USB_COUNT4_RX_NUM_BLOCK_3', 'USB_COUNT4_RX_NUM_BLOCK_4', 'USB_COUNT4_RX_BLSIZE',
    'USB_COUNT5_RX_COUNT5_RX', 'USB_COUNT5_RX_NUM_BLOCK', 'USB_COUNT5_RX_NUM_BLOCK_0',
    'USB_COUNT5_RX_NUM_BLOCK_1', 'USB_COUNT5_RX_NUM_BLOCK_2',
    'USB_COUNT5_RX_NUM_BLOCK_3', 'USB_COUNT5_RX_NUM_BLOCK_4', 'USB_COUNT5_RX_BLSIZE',
    'USB_COUNT6_RX_COUNT6_RX', 'USB_COUNT6_RX_NUM_BLOCK', 'USB_COUNT6_RX_NUM_BLOCK_0',
    'USB_COUNT6_RX_NUM_BLOCK_1', 'USB_COUNT6_RX_NUM_BLOCK_2',
    'USB_COUNT6_RX_NUM_BLOCK_3', 'USB_COUNT6_RX_NUM_BLOCK_4', 'USB_COUNT6_RX_BLSIZE',
    'USB_COUNT7_RX_COUNT7_RX', 'USB_COUNT7_RX_NUM_BLOCK', 'USB_COUNT7_RX_NUM_BLOCK_0',
    'USB_COUNT7_RX_NUM_BLOCK_1', 'USB_COUNT7_RX_NUM_BLOCK_2',
    'USB_COUNT7_RX_NUM_BLOCK_3', 'USB_COUNT7_RX_NUM_BLOCK_4', 'USB_COUNT7_RX_BLSIZE',
    'USB_COUNT0_RX_0_COUNT0_RX_0', 'USB_COUNT0_RX_0_NUM_BLOCK_0',
    'USB_COUNT0_RX_0_NUM_BLOCK_0_0', 'USB_COUNT0_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT0_RX_0_NUM_BLOCK_0_2', 'USB_COUNT0_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT0_RX_0_NUM_BLOCK_0_4', 'USB_COUNT0_RX_0_BLSIZE_0',
    'USB_COUNT0_RX_1_COUNT0_RX_1', 'USB_COUNT0_RX_1_NUM_BLOCK_1',
    'USB_COUNT0_RX_1_NUM_BLOCK_1_0', 'USB_COUNT0_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT0_RX_1_NUM_BLOCK_1_2', 'USB_COUNT0_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT0_RX_1_NUM_BLOCK_1_4', 'USB_COUNT0_RX_1_BLSIZE_1',
    'USB_COUNT1_RX_0_COUNT1_RX_0', 'USB_COUNT1_RX_0_NUM_BLOCK_0',
    'USB_COUNT1_RX_0_NUM_BLOCK_0_0', 'USB_COUNT1_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT1_RX_0_NUM_BLOCK_0_2', 'USB_COUNT1_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT1_RX_0_NUM_BLOCK_0_4', 'USB_COUNT1_RX_0_BLSIZE_0',
    'USB_COUNT1_RX_1_COUNT1_RX_1', 'USB_COUNT1_RX_1_NUM_BLOCK_1',
    'USB_COUNT1_RX_1_NUM_BLOCK_1_0', 'USB_COUNT1_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT1_RX_1_NUM_BLOCK_1_2', 'USB_COUNT1_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT1_RX_1_NUM_BLOCK_1_4', 'USB_COUNT1_RX_1_BLSIZE_1',
    'USB_COUNT2_RX_0_COUNT2_RX_0', 'USB_COUNT2_RX_0_NUM_BLOCK_0',
    'USB_COUNT2_RX_0_NUM_BLOCK_0_0', 'USB_COUNT2_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT2_RX_0_NUM_BLOCK_0_2', 'USB_COUNT2_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT2_RX_0_NUM_BLOCK_0_4', 'USB_COUNT2_RX_0_BLSIZE_0',
    'USB_COUNT2_RX_1_COUNT2_RX_1', 'USB_COUNT2_RX_1_NUM_BLOCK_1',
    'USB_COUNT2_RX_1_NUM_BLOCK_1_0', 'USB_COUNT2_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT2_RX_1_NUM_BLOCK_1_2', 'USB_COUNT2_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT2_RX_1_NUM_BLOCK_1_4', 'USB_COUNT2_RX_1_BLSIZE_1',
    'USB_COUNT3_RX_0_COUNT3_RX_0', 'USB_COUNT3_RX_0_NUM_BLOCK_0',
    'USB_COUNT3_RX_0_NUM_BLOCK_0_0', 'USB_COUNT3_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT3_RX_0_NUM_BLOCK_0_2', 'USB_COUNT3_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT3_RX_0_NUM_BLOCK_0_4', 'USB_COUNT3_RX_0_BLSIZE_0',
    'USB_COUNT3_RX_1_COUNT3_RX_1', 'USB_COUNT3_RX_1_NUM_BLOCK_1',
    'USB_COUNT3_RX_1_NUM_BLOCK_1_0', 'USB_COUNT3_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT3_RX_1_NUM_BLOCK_1_2', 'USB_COUNT3_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT3_RX_1_NUM_BLOCK_1_4', 'USB_COUNT3_RX_1_BLSIZE_1',
    'USB_COUNT4_RX_0_COUNT4_RX_0', 'USB_COUNT4_RX_0_NUM_BLOCK_0',
    'USB_COUNT4_RX_0_NUM_BLOCK_0_0', 'USB_COUNT4_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT4_RX_0_NUM_BLOCK_0_2', 'USB_COUNT4_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT4_RX_0_NUM_BLOCK_0_4', 'USB_COUNT4_RX_0_BLSIZE_0',
    'USB_COUNT4_RX_1_COUNT4_RX_1', 'USB_COUNT4_RX_1_NUM_BLOCK_1',
    'USB_COUNT4_RX_1_NUM_BLOCK_1_0', 'USB_COUNT4_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT4_RX_1_NUM_BLOCK_1_2', 'USB_COUNT4_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT4_RX_1_NUM_BLOCK_1_4', 'USB_COUNT4_RX_1_BLSIZE_1',
    'USB_COUNT5_RX_0_COUNT5_RX_0', 'USB_COUNT5_RX_0_NUM_BLOCK_0',
    'USB_COUNT5_RX_0_NUM_BLOCK_0_0', 'USB_COUNT5_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT5_RX_0_NUM_BLOCK_0_2', 'USB_COUNT5_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT5_RX_0_NUM_BLOCK_0_4', 'USB_COUNT5_RX_0_BLSIZE_0',
    'USB_COUNT5_RX_1_COUNT5_RX_1', 'USB_COUNT5_RX_1_NUM_BLOCK_1',
    'USB_COUNT5_RX_1_NUM_BLOCK_1_0', 'USB_COUNT5_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT5_RX_1_NUM_BLOCK_1_2', 'USB_COUNT5_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT5_RX_1_NUM_BLOCK_1_4', 'USB_COUNT5_RX_1_BLSIZE_1',
    'USB_COUNT6_RX_0_COUNT6_RX_0', 'USB_COUNT6_RX_0_NUM_BLOCK_0',
    'USB_COUNT6_RX_0_NUM_BLOCK_0_0', 'USB_COUNT6_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT6_RX_0_NUM_BLOCK_0_2', 'USB_COUNT6_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT6_RX_0_NUM_BLOCK_0_4', 'USB_COUNT6_RX_0_BLSIZE_0',
    'USB_COUNT6_RX_1_COUNT6_RX_1', 'USB_COUNT6_RX_1_NUM_BLOCK_1',
    'USB_COUNT6_RX_1_NUM_BLOCK_1_0', 'USB_COUNT6_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT6_RX_1_NUM_BLOCK_1_2', 'USB_COUNT6_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT6_RX_1_NUM_BLOCK_1_4', 'USB_COUNT6_RX_1_BLSIZE_1',
    'USB_COUNT7_RX_0_COUNT7_RX_0', 'USB_COUNT7_RX_0_NUM_BLOCK_0',
    'USB_COUNT7_RX_0_NUM_BLOCK_0_0', 'USB_COUNT7_RX_0_NUM_BLOCK_0_1',
    'USB_COUNT7_RX_0_NUM_BLOCK_0_2', 'USB_COUNT7_RX_0_NUM_BLOCK_0_3',
    'USB_COUNT7_RX_0_NUM_BLOCK_0_4', 'USB_COUNT7_RX_0_BLSIZE_0',
    'USB_COUNT7_RX_1_COUNT7_RX_1', 'USB_COUNT7_RX_1_NUM_BLOCK_1',
    'USB_COUNT7_RX_1_NUM_BLOCK_1_0', 'USB_COUNT7_RX_1_NUM_BLOCK_1_1',
    'USB_COUNT7_RX_1_NUM_BLOCK_1_2', 'USB_COUNT7_RX_1_NUM_BLOCK_1_3',
    'USB_COUNT7_RX_1_NUM_BLOCK_1_4', 'USB_COUNT7_RX_1_BLSIZE_1', 'CAN_MCR_INRQ',
    'CAN_MCR_SLEEP', 'CAN_MCR_TXFP', 'CAN_MCR_RFLM', 'CAN_MCR_NART', 'CAN_MCR_AWUM',
    'CAN_MCR_ABOM', 'CAN_MCR_TTCM', 'CAN_MCR_RESET', 'CAN_MSR_INAK', 'CAN_MSR_SLAK',
    'CAN_MSR_ERRI', 'CAN_MSR_WKUI', 'CAN_MSR_SLAKI', 'CAN_MSR_TXM', 'CAN_MSR_RXM',
    'CAN_MSR_SAMP', 'CAN_MSR_RX', 'CAN_TSR_RQCP0', 'CAN_TSR_TXOK0', 'CAN_TSR_ALST0',
    'CAN_TSR_TERR0', 'CAN_TSR_ABRQ0', 'CAN_TSR_RQCP1', 'CAN_TSR_TXOK1', 'CAN_TSR_ALST1',
    'CAN_TSR_TERR1', 'CAN_TSR_ABRQ1', 'CAN_TSR_RQCP2', 'CAN_TSR_TXOK2', 'CAN_TSR_ALST2',
    'CAN_TSR_TERR2', 'CAN_TSR_ABRQ2', 'CAN_TSR_CODE', 'CAN_TSR_TME', 'CAN_TSR_TME0',
    'CAN_TSR_TME1', 'CAN_TSR_TME2', 'CAN_TSR_LOW', 'CAN_TSR_LOW0', 'CAN_TSR_LOW1',
    'CAN_TSR_LOW2', 'CAN_RF0R_FMP0', 'CAN_RF0R_FULL0', 'CAN_RF0R_FOVR0',
    'CAN_RF0R_RFOM0', 'CAN_RF1R_FMP1', 'CAN_RF1R_FULL1', 'CAN_RF1R_FOVR1',
    'CAN_RF1R_RFOM1', 'CAN_IER_TMEIE', 'CAN_IER_FMPIE0', 'CAN_IER_FFIE0',
    'CAN_IER_FOVIE0', 'CAN_IER_FMPIE1', 'CAN_IER_FFIE1', 'CAN_IER_FOVIE1',
    'CAN_IER_EWGIE', 'CAN_IER_EPVIE', 'CAN_IER_BOFIE', 'CAN_IER_LECIE', 'CAN_IER_ERRIE',
    'CAN_IER_WKUIE', 'CAN_IER_SLKIE', 'CAN_ESR_EWGF', 'CAN_ESR_EPVF', 'CAN_ESR_BOFF',
    'CAN_ESR_LEC', 'CAN_ESR_LEC_0', 'CAN_ESR_LEC_1', 'CAN_ESR_LEC_2', 'CAN_ESR_TEC',
    'CAN_ESR_REC', 'CAN_BTR_BRP', 'CAN_BTR_TS1', 'CAN_BTR_TS2', 'CAN_BTR_SJW',
    'CAN_BTR_LBKM', 'CAN_BTR_SILM', 'CAN_TI0R_TXRQ', 'CAN_TI0R_RTR', 'CAN_TI0R_IDE',
    'CAN_TI0R_EXID', 'CAN_TI0R_STID', 'CAN_TDT0R_DLC', 'CAN_TDT0R_TGT',
    'CAN_TDT0R_TIME', 'CAN_TDL0R_DATA0', 'CAN_TDL0R_DATA1', 'CAN_TDL0R_DATA2',
    'CAN_TDL0R_DATA3', 'CAN_TDH0R_DATA4', 'CAN_TDH0R_DATA5', 'CAN_TDH0R_DATA6',
    'CAN_TDH0R_DATA7', 'CAN_TI1R_TXRQ', 'CAN_TI1R_RTR', 'CAN_TI1R_IDE', 'CAN_TI1R_EXID',
    'CAN_TI1R_STID', 'CAN_TDT1R_DLC', 'CAN_TDT1R_TGT', 'CAN_TDT1R_TIME',
    'CAN_TDL1R_DATA0', 'CAN_TDL1R_DATA1', 'CAN_TDL1R_DATA2', 'CAN_TDL1R_DATA3',
    'CAN_TDH1R_DATA4', 'CAN_TDH1R_DATA5', 'CAN_TDH1R_DATA6', 'CAN_TDH1R_DATA7',
    'CAN_TI2R_TXRQ', 'CAN_TI2R_RTR', 'CAN_TI2R_IDE', 'CAN_TI2R_EXID', 'CAN_TI2R_STID',
    'CAN_TDT2R_DLC', 'CAN_TDT2R_TGT', 'CAN_TDT2R_TIME', 'CAN_TDL2R_DATA0',
    'CAN_TDL2R_DATA1', 'CAN_TDL2R_DATA2', 'CAN_TDL2R_DATA3', 'CAN_TDH2R_DATA4',
    'CAN_TDH2R_DATA5', 'CAN_TDH2R_DATA6', 'CAN_TDH2R_DATA7', 'CAN_RI0R_RTR',
    'CAN_RI0R_IDE', 'CAN_RI0R_EXID', 'CAN_RI0R_STID', 'CAN_RDT0R_DLC', 'CAN_RDT0R_FMI',
    'CAN_RDT0R_TIME', 'CAN_RDL0R_DATA0', 'CAN_RDL0R_DATA1', 'CAN_RDL0R_DATA2',
    'CAN_RDL0R_DATA3', 'CAN_RDH0R_DATA4', 'CAN_RDH0R_DATA5', 'CAN_RDH0R_DATA6',
    'CAN_RDH0R_DATA7', 'CAN_RI1R_RTR', 'CAN_RI1R_IDE', 'CAN_RI1R_EXID', 'CAN_RI1R_STID',
    'CAN_RDT1R_DLC', 'CAN_RDT1R_FMI', 'CAN_RDT1R_TIME', 'CAN_RDL1R_DATA0',
    'CAN_RDL1R_DATA1', 'CAN_RDL1R_DATA2', 'CAN_RDL1R_DATA3', 'CAN_RDH1R_DATA4',
    'CAN_RDH1R_DATA5', 'CAN_RDH1R_DATA6', 'CAN_RDH1R_DATA7', 'CAN_FMR_FINIT',
    'CAN_FM1R_FBM', 'CAN_FM1R_FBM0', 'CAN_FM1R_FBM1', 'CAN_FM1R_FBM2', 'CAN_FM1R_FBM3',
    'CAN_FM1R_FBM4', 'CAN_FM1R_FBM5', 'CAN_FM1R_FBM6', 'CAN_FM1R_FBM7', 'CAN_FM1R_FBM8',
    'CAN_FM1R_FBM9', 'CAN_FM1R_FBM10', 'CAN_FM1R_FBM11', 'CAN_FM1R_FBM12',
    'CAN_FM1R_FBM13', 'CAN_FS1R_FSC', 'CAN_FS1R_FSC0', 'CAN_FS1R_FSC1', 'CAN_FS1R_FSC2',
    'CAN_FS1R_FSC3', 'CAN_FS1R_FSC4', 'CAN_FS1R_FSC5', 'CAN_FS1R_FSC6', 'CAN_FS1R_FSC7',
    'CAN_FS1R_FSC8', 'CAN_FS1R_FSC9', 'CAN_FS1R_FSC10', 'CAN_FS1R_FSC11',
    'CAN_FS1R_FSC12', 'CAN_FS1R_FSC13', 'CAN_FFA1R_FFA', 'CAN_FFA1R_FFA0',
    'CAN_FFA1R_FFA1', 'CAN_FFA1R_FFA2', 'CAN_FFA1R_FFA3', 'CAN_FFA1R_FFA4',
    'CAN_FFA1R_FFA5', 'CAN_FFA1R_FFA6', 'CAN_FFA1R_FFA7', 'CAN_FFA1R_FFA8',
    'CAN_FFA1R_FFA9', 'CAN_FFA1R_FFA10', 'CAN_FFA1R_FFA11', 'CAN_FFA1R_FFA12',
    'CAN_FFA1R_FFA13', 'CAN_FA1R_FACT', 'CAN_FA1R_FACT0', 'CAN_FA1R_FACT1',
    'CAN_FA1R_FACT2', 'CAN_FA1R_FACT3', 'CAN_FA1R_FACT4', 'CAN_FA1R_FACT5',
    'CAN_FA1R_FACT6', 'CAN_FA1R_FACT7', 'CAN_FA1R_FACT8', 'CAN_FA1R_FACT9',
    'CAN_FA1R_FACT10', 'CAN_FA1R_FACT11', 'CAN_FA1R_FACT12', 'CAN_FA1R_FACT13',
    'CAN_F0R1_FB0', 'CAN_F0R1_FB1', 'CAN_F0R1_FB2', 'CAN_F0R1_FB3', 'CAN_F0R1_FB4',
    'CAN_F0R1_FB5', 'CAN_F0R1_FB6', 'CAN_F0R1_FB7', 'CAN_F0R1_FB8', 'CAN_F0R1_FB9',
    'CAN_F0R1_FB10', 'CAN_F0R1_FB11', 'CAN_F0R1_FB12', 'CAN_F0R1_FB13', 'CAN_F0R1_FB14',
    'CAN_F0R1_FB15', 'CAN_F0R1_FB16', 'CAN_F0R1_FB17', 'CAN_F0R1_FB18', 'CAN_F0R1_FB19',
    'CAN_F0R1_FB20', 'CAN_F0R1_FB21', 'CAN_F0R1_FB22', 'CAN_F0R1_FB23', 'CAN_F0R1_FB24',
    'CAN_F0R1_FB25', 'CAN_F0R1_FB26', 'CAN_F0R1_FB27', 'CAN_F0R1_FB28', 'CAN_F0R1_FB29',
    'CAN_F0R1_FB30', 'CAN_F0R1_FB31', 'CAN_F1R1_FB0', 'CAN_F1R1_FB1', 'CAN_F1R1_FB2',
    'CAN_F1R1_FB3', 'CAN_F1R1_FB4', 'CAN_F1R1_FB5', 'CAN_F1R1_FB6', 'CAN_F1R1_FB7',
    'CAN_F1R1_FB8', 'CAN_F1R1_FB9', 'CAN_F1R1_FB10', 'CAN_F1R1_FB11', 'CAN_F1R1_FB12',
    'CAN_F1R1_FB13', 'CAN_F1R1_FB14', 'CAN_F1R1_FB15', 'CAN_F1R1_FB16', 'CAN_F1R1_FB17',
    'CAN_F1R1_FB18', 'CAN_F1R1_FB19', 'CAN_F1R1_FB20', 'CAN_F1R1_FB21', 'CAN_F1R1_FB22',
    'CAN_F1R1_FB23', 'CAN_F1R1_FB24', 'CAN_F1R1_FB25', 'CAN_F1R1_FB26', 'CAN_F1R1_FB27',
    'CAN_F1R1_FB28', 'CAN_F1R1_FB29', 'CAN_F1R1_FB30', 'CAN_F1R1_FB31', 'CAN_F2R1_FB0',
    'CAN_F2R1_FB1', 'CAN_F2R1_FB2', 'CAN_F2R1_FB3', 'CAN_F2R1_FB4', 'CAN_F2R1_FB5',
    'CAN_F2R1_FB6', 'CAN_F2R1_FB7', 'CAN_F2R1_FB8', 'CAN_F2R1_FB9', 'CAN_F2R1_FB10',
    'CAN_F2R1_FB11', 'CAN_F2R1_FB12', 'CAN_F2R1_FB13', 'CAN_F2R1_FB14', 'CAN_F2R1_FB15',
    'CAN_F2R1_FB16', 'CAN_F2R1_FB17', 'CAN_F2R1_FB18', 'CAN_F2R1_FB19', 'CAN_F2R1_FB20',
    'CAN_F2R1_FB21', 'CAN_F2R1_FB22', 'CAN_F2R1_FB23', 'CAN_F2R1_FB24', 'CAN_F2R1_FB25',
    'CAN_F2R1_FB26', 'CAN_F2R1_FB27', 'CAN_F2R1_FB28', 'CAN_F2R1_FB29', 'CAN_F2R1_FB30',
    'CAN_F2R1_FB31', 'CAN_F3R1_FB0', 'CAN_F3R1_FB1', 'CAN_F3R1_FB2', 'CAN_F3R1_FB3',
    'CAN_F3R1_FB4', 'CAN_F3R1_FB5', 'CAN_F3R1_FB6', 'CAN_F3R1_FB7', 'CAN_F3R1_FB8',
    'CAN_F3R1_FB9', 'CAN_F3R1_FB10', 'CAN_F3R1_FB11', 'CAN_F3R1_FB12', 'CAN_F3R1_FB13',
    'CAN_F3R1_FB14', 'CAN_F3R1_FB15', 'CAN_F3R1_FB16', 'CAN_F3R1_FB17', 'CAN_F3R1_FB18',
    'CAN_F3R1_FB19', 'CAN_F3R1_FB20', 'CAN_F3R1_FB21', 'CAN_F3R1_FB22', 'CAN_F3R1_FB23',
    'CAN_F3R1_FB24', 'CAN_F3R1_FB25', 'CAN_F3R1_FB26', 'CAN_F3R1_FB27', 'CAN_F3R1_FB28',
    'CAN_F3R1_FB29', 'CAN_F3R1_FB30', 'CAN_F3R1_FB31', 'CAN_F4R1_FB0', 'CAN_F4R1_FB1',
    'CAN_F4R1_FB2', 'CAN_F4R1_FB3', 'CAN_F4R1_FB4', 'CAN_F4R1_FB5', 'CAN_F4R1_FB6',
    'CAN_F4R1_FB7', 'CAN_F4R1_FB8', 'CAN_F4R1_FB9', 'CAN_F4R1_FB10', 'CAN_F4R1_FB11',
    'CAN_F4R1_FB12', 'CAN_F4R1_FB13', 'CAN_F4R1_FB14', 'CAN_F4R1_FB15', 'CAN_F4R1_FB16',
    'CAN_F4R1_FB17', 'CAN_F4R1_FB18', 'CAN_F4R1_FB19', 'CAN_F4R1_FB20', 'CAN_F4R1_FB21',
    'CAN_F4R1_FB22', 'CAN_F4R1_FB23', 'CAN_F4R1_FB24', 'CAN_F4R1_FB25', 'CAN_F4R1_FB26',
    'CAN_F4R1_FB27', 'CAN_F4R1_FB28', 'CAN_F4R1_FB29', 'CAN_F4R1_FB30', 'CAN_F4R1_FB31',
    'CAN_F5R1_FB0', 'CAN_F5R1_FB1', 'CAN_F5R1_FB2', 'CAN_F5R1_FB3', 'CAN_F5R1_FB4',
    'CAN_F5R1_FB5', 'CAN_F5R1_FB6', 'CAN_F5R1_FB7', 'CAN_F5R1_FB8', 'CAN_F5R1_FB9',
    'CAN_F5R1_FB10', 'CAN_F5R1_FB11', 'CAN_F5R1_FB12', 'CAN_F5R1_FB13', 'CAN_F5R1_FB14',
    'CAN_F5R1_FB15', 'CAN_F5R1_FB16', 'CAN_F5R1_FB17', 'CAN_F5R1_FB18', 'CAN_F5R1_FB19',
    'CAN_F5R1_FB20', 'CAN_F5R1_FB21', 'CAN_F5R1_FB22', 'CAN_F5R1_FB23', 'CAN_F5R1_FB24',
    'CAN_F5R1_FB25', 'CAN_F5R1_FB26', 'CAN_F5R1_FB27', 'CAN_F5R1_FB28', 'CAN_F5R1_FB29',
    'CAN_F5R1_FB30', 'CAN_F5R1_FB31', 'CAN_F6R1_FB0', 'CAN_F6R1_FB1', 'CAN_F6R1_FB2',
    'CAN_F6R1_FB3', 'CAN_F6R1_FB4', 'CAN_F6R1_FB5', 'CAN_F6R1_FB6', 'CAN_F6R1_FB7',
    'CAN_F6R1_FB8', 'CAN_F6R1_FB9', 'CAN_F6R1_FB10', 'CAN_F6R1_FB11', 'CAN_F6R1_FB12',
    'CAN_F6R1_FB13', 'CAN_F6R1_FB14', 'CAN_F6R1_FB15', 'CAN_F6R1_FB16', 'CAN_F6R1_FB17',
    'CAN_F6R1_FB18', 'CAN_F6R1_FB19', 'CAN_F6R1_FB20', 'CAN_F6R1_FB21', 'CAN_F6R1_FB22',
    'CAN_F6R1_FB23', 'CAN_F6R1_FB24', 'CAN_F6R1_FB25', 'CAN_F6R1_FB26', 'CAN_F6R1_FB27',
    'CAN_F6R1_FB28', 'CAN_F6R1_FB29', 'CAN_F6R1_FB30', 'CAN_F6R1_FB31', 'CAN_F7R1_FB0',
    'CAN_F7R1_FB1', 'CAN_F7R1_FB2', 'CAN_F7R1_FB3', 'CAN_F7R1_FB4', 'CAN_F7R1_FB5',
    'CAN_F7R1_FB6', 'CAN_F7R1_FB7', 'CAN_F7R1_FB8', 'CAN_F7R1_FB9', 'CAN_F7R1_FB10',
    'CAN_F7R1_FB11', 'CAN_F7R1_FB12', 'CAN_F7R1_FB13', 'CAN_F7R1_FB14', 'CAN_F7R1_FB15',
    'CAN_F7R1_FB16', 'CAN_F7R1_FB17', 'CAN_F7R1_FB18', 'CAN_F7R1_FB19', 'CAN_F7R1_FB20',
    'CAN_F7R1_FB21', 'CAN_F7R1_FB22', 'CAN_F7R1_FB23', 'CAN_F7R1_FB24', 'CAN_F7R1_FB25',
    'CAN_F7R1_FB26', 'CAN_F7R1_FB27', 'CAN_F7R1_FB28', 'CAN_F7R1_FB29', 'CAN_F7R1_FB30',
    'CAN_F7R1_FB31', 'CAN_F8R1_FB0', 'CAN_F8R1_FB1', 'CAN_F8R1_FB2', 'CAN_F8R1_FB3',
    'CAN_F8R1_FB4', 'CAN_F8R1_FB5', 'CAN_F8R1_FB6', 'CAN_F8R1_FB7', 'CAN_F8R1_FB8',
    'CAN_F8R1_FB9', 'CAN_F8R1_FB10', 'CAN_F8R1_FB11', 'CAN_F8R1_FB12', 'CAN_F8R1_FB13',
    'CAN_F8R1_FB14', 'CAN_F8R1_FB15', 'CAN_F8R1_FB16', 'CAN_F8R1_FB17', 'CAN_F8R1_FB18',
    'CAN_F8R1_FB19', 'CAN_F8R1_FB20', 'CAN_F8R1_FB21', 'CAN_F8R1_FB22', 'CAN_F8R1_FB23',
    'CAN_F8R1_FB24', 'CAN_F8R1_FB25', 'CAN_F8R1_FB26', 'CAN_F8R1_FB27', 'CAN_F8R1_FB28',
    'CAN_F8R1_FB29', 'CAN_F8R1_FB30', 'CAN_F8R1_FB31', 'CAN_F9R1_FB0', 'CAN_F9R1_FB1',
    'CAN_F9R1_FB2', 'CAN_F9R1_FB3', 'CAN_F9R1_FB4', 'CAN_F9R1_FB5', 'CAN_F9R1_FB6',
    'CAN_F9R1_FB7', 'CAN_F9R1_FB8', 'CAN_F9R1_FB9', 'CAN_F9R1_FB10', 'CAN_F9R1_FB11',
    'CAN_F9R1_FB12', 'CAN_F9R1_FB13', 'CAN_F9R1_FB14', 'CAN_F9R1_FB15', 'CAN_F9R1_FB16',
    'CAN_F9R1_FB17', 'CAN_F9R1_FB18', 'CAN_F9R1_FB19', 'CAN_F9R1_FB20', 'CAN_F9R1_FB21',
    'CAN_F9R1_FB22', 'CAN_F9R1_FB23', 'CAN_F9R1_FB24', 'CAN_F9R1_FB25', 'CAN_F9R1_FB26',
    'CAN_F9R1_FB27', 'CAN_F9R1_FB28', 'CAN_F9R1_FB29', 'CAN_F9R1_FB30', 'CAN_F9R1_FB31',
    'CAN_F10R1_FB0', 'CAN_F10R1_FB1', 'CAN_F10R1_FB2', 'CAN_F10R1_FB3', 'CAN_F10R1_FB4',
    'CAN_F10R1_FB5', 'CAN_F10R1_FB6', 'CAN_F10R1_FB7', 'CAN_F10R1_FB8', 'CAN_F10R1_FB9',
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
    'SPI_CR1_CPHA', 'SPI_CR1_CPOL', 'SPI_CR1_MSTR', 'SPI_CR1_BR', 'SPI_CR1_BR_0',
    'SPI_CR1_BR_1', 'SPI_CR1_BR_2', 'SPI_CR1_SPE', 'SPI_CR1_LSBFIRST', 'SPI_CR1_SSI',
    'SPI_CR1_SSM', 'SPI_CR1_RXONLY', 'SPI_CR1_DFF', 'SPI_CR1_CRCNEXT', 'SPI_CR1_CRCEN',
    'SPI_CR1_BIDIOE', 'SPI_CR1_BIDIMODE', 'SPI_CR2_RXDMAEN', 'SPI_CR2_TXDMAEN',
    'SPI_CR2_SSOE', 'SPI_CR2_ERRIE', 'SPI_CR2_RXNEIE', 'SPI_CR2_TXEIE', 'SPI_SR_RXNE',
    'SPI_SR_TXE', 'SPI_SR_CHSIDE', 'SPI_SR_UDR', 'SPI_SR_CRCERR', 'SPI_SR_MODF',
    'SPI_SR_OVR', 'SPI_SR_BSY', 'SPI_DR_DR', 'SPI_CRCPR_CRCPOLY', 'SPI_RXCRCR_RXCRC',
    'SPI_TXCRCR_TXCRC', 'SPI_I2SCFGR_CHLEN', 'SPI_I2SCFGR_DATLEN',
    'SPI_I2SCFGR_DATLEN_0', 'SPI_I2SCFGR_DATLEN_1', 'SPI_I2SCFGR_CKPOL',
    'SPI_I2SCFGR_I2SSTD', 'SPI_I2SCFGR_I2SSTD_0', 'SPI_I2SCFGR_I2SSTD_1',
    'SPI_I2SCFGR_PCMSYNC', 'SPI_I2SCFGR_I2SCFG', 'SPI_I2SCFGR_I2SCFG_0',
    'SPI_I2SCFGR_I2SCFG_1', 'SPI_I2SCFGR_I2SE', 'SPI_I2SCFGR_I2SMOD',
    'SPI_I2SPR_I2SDIV', 'SPI_I2SPR_ODD', 'SPI_I2SPR_MCKOE', 'I2C_CR1_PE',
    'I2C_CR1_SMBUS', 'I2C_CR1_SMBTYPE', 'I2C_CR1_ENARP', 'I2C_CR1_ENPEC',
    'I2C_CR1_ENGC', 'I2C_CR1_NOSTRETCH', 'I2C_CR1_START', 'I2C_CR1_STOP', 'I2C_CR1_ACK',
    'I2C_CR1_POS', 'I2C_CR1_PEC', 'I2C_CR1_ALERT', 'I2C_CR1_SWRST', 'I2C_CR2_FREQ',
    'I2C_CR2_FREQ_0', 'I2C_CR2_FREQ_1', 'I2C_CR2_FREQ_2', 'I2C_CR2_FREQ_3',
    'I2C_CR2_FREQ_4', 'I2C_CR2_FREQ_5', 'I2C_CR2_ITERREN', 'I2C_CR2_ITEVTEN',
    'I2C_CR2_ITBUFEN', 'I2C_CR2_DMAEN', 'I2C_CR2_LAST', 'I2C_OAR1_ADD1_7',
    'I2C_OAR1_ADD8_9', 'I2C_OAR1_ADD0', 'I2C_OAR1_ADD1', 'I2C_OAR1_ADD2',
    'I2C_OAR1_ADD3', 'I2C_OAR1_ADD4', 'I2C_OAR1_ADD5', 'I2C_OAR1_ADD6', 'I2C_OAR1_ADD7',
    'I2C_OAR1_ADD8', 'I2C_OAR1_ADD9', 'I2C_OAR1_ADDMODE', 'I2C_OAR2_ENDUAL',
    'I2C_OAR2_ADD2', 'I2C_DR_DR', 'I2C_SR1_SB', 'I2C_SR1_ADDR', 'I2C_SR1_BTF',
    'I2C_SR1_ADD10', 'I2C_SR1_STOPF', 'I2C_SR1_RXNE', 'I2C_SR1_TXE', 'I2C_SR1_BERR',
    'I2C_SR1_ARLO', 'I2C_SR1_AF', 'I2C_SR1_OVR', 'I2C_SR1_PECERR', 'I2C_SR1_TIMEOUT',
    'I2C_SR1_SMBALERT', 'I2C_SR2_MSL', 'I2C_SR2_BUSY', 'I2C_SR2_TRA', 'I2C_SR2_GENCALL',
    'I2C_SR2_SMBDEFAULT', 'I2C_SR2_SMBHOST', 'I2C_SR2_DUALF', 'I2C_SR2_PEC',
    'I2C_CCR_CCR', 'I2C_CCR_DUTY', 'I2C_CCR_FS', 'I2C_TRISE_TRISE', 'USART_SR_PE',
    'USART_SR_FE', 'USART_SR_NE', 'USART_SR_ORE', 'USART_SR_IDLE', 'USART_SR_RXNE',
    'USART_SR_TC', 'USART_SR_TXE', 'USART_SR_LBD', 'USART_SR_CTS', 'USART_DR_DR',
    'USART_BRR_DIV_Fraction', 'USART_BRR_DIV_Mantissa', 'USART_CR1_SBK',
    'USART_CR1_RWU', 'USART_CR1_RE', 'USART_CR1_TE', 'USART_CR1_IDLEIE',
    'USART_CR1_RXNEIE', 'USART_CR1_TCIE', 'USART_CR1_TXEIE', 'USART_CR1_PEIE',
    'USART_CR1_PS', 'USART_CR1_PCE', 'USART_CR1_WAKE', 'USART_CR1_M', 'USART_CR1_UE',
    'USART_CR1_OVER8', 'USART_CR2_ADD', 'USART_CR2_LBDL', 'USART_CR2_LBDIE',
    'USART_CR2_LBCL', 'USART_CR2_CPHA', 'USART_CR2_CPOL', 'USART_CR2_CLKEN',
    'USART_CR2_STOP', 'USART_CR2_STOP_0', 'USART_CR2_STOP_1', 'USART_CR2_LINEN',
    'USART_CR3_EIE', 'USART_CR3_IREN', 'USART_CR3_IRLP', 'USART_CR3_HDSEL',
    'USART_CR3_NACK', 'USART_CR3_SCEN', 'USART_CR3_DMAR', 'USART_CR3_DMAT',
    'USART_CR3_RTSE', 'USART_CR3_CTSE', 'USART_CR3_CTSIE', 'USART_CR3_ONEBIT',
    'USART_GTPR_PSC', 'USART_GTPR_PSC_0', 'USART_GTPR_PSC_1', 'USART_GTPR_PSC_2',
    'USART_GTPR_PSC_3', 'USART_GTPR_PSC_4', 'USART_GTPR_PSC_5', 'USART_GTPR_PSC_6',
    'USART_GTPR_PSC_7', 'USART_GTPR_GT', 'DBGMCU_IDCODE_DEV_ID', 'DBGMCU_IDCODE_REV_ID',
    'DBGMCU_IDCODE_REV_ID_0', 'DBGMCU_IDCODE_REV_ID_1', 'DBGMCU_IDCODE_REV_ID_2',
    'DBGMCU_IDCODE_REV_ID_3', 'DBGMCU_IDCODE_REV_ID_4', 'DBGMCU_IDCODE_REV_ID_5',
    'DBGMCU_IDCODE_REV_ID_6', 'DBGMCU_IDCODE_REV_ID_7', 'DBGMCU_IDCODE_REV_ID_8',
    'DBGMCU_IDCODE_REV_ID_9', 'DBGMCU_IDCODE_REV_ID_10', 'DBGMCU_IDCODE_REV_ID_11',
    'DBGMCU_IDCODE_REV_ID_12', 'DBGMCU_IDCODE_REV_ID_13', 'DBGMCU_IDCODE_REV_ID_14',
    'DBGMCU_IDCODE_REV_ID_15', 'DBGMCU_CR_DBG_SLEEP', 'DBGMCU_CR_DBG_STOP',
    'DBGMCU_CR_DBG_STANDBY', 'DBGMCU_CR_TRACE_IOEN', 'DBGMCU_CR_TRACE_MODE',
    'DBGMCU_CR_TRACE_MODE_0', 'DBGMCU_CR_TRACE_MODE_1', 'DBGMCU_CR_DBG_IWDG_STOP',
    'DBGMCU_CR_DBG_WWDG_STOP', 'DBGMCU_CR_DBG_TIM1_STOP', 'DBGMCU_CR_DBG_TIM2_STOP',
    'DBGMCU_CR_DBG_TIM3_STOP', 'DBGMCU_CR_DBG_TIM4_STOP', 'DBGMCU_CR_DBG_CAN1_STOP',
    'DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT', 'DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT',
    'DBGMCU_CR_DBG_TIM8_STOP', 'DBGMCU_CR_DBG_TIM5_STOP', 'DBGMCU_CR_DBG_TIM6_STOP',
    'DBGMCU_CR_DBG_TIM7_STOP', 'DBGMCU_CR_DBG_CAN2_STOP', 'DBGMCU_CR_DBG_TIM15_STOP',
    'DBGMCU_CR_DBG_TIM16_STOP', 'DBGMCU_CR_DBG_TIM17_STOP', 'DBGMCU_CR_DBG_TIM12_STOP',
    'DBGMCU_CR_DBG_TIM13_STOP', 'DBGMCU_CR_DBG_TIM14_STOP', 'DBGMCU_CR_DBG_TIM9_STOP',
    'DBGMCU_CR_DBG_TIM10_STOP', 'DBGMCU_CR_DBG_TIM11_STOP', 'FLASH_ACR_LATENCY',
    'FLASH_ACR_LATENCY_0', 'FLASH_ACR_LATENCY_1', 'FLASH_ACR_LATENCY_2',
    'FLASH_ACR_HLFCYA', 'FLASH_ACR_PRFTBE', 'FLASH_ACR_PRFTBS', 'FLASH_KEYR_FKEYR',
    'FLASH_OPTKEYR_OPTKEYR', 'FLASH_SR_BSY', 'FLASH_SR_PGERR', 'FLASH_SR_WRPRTERR',
    'FLASH_SR_EOP', 'FLASH_CR_PG', 'FLASH_CR_PER', 'FLASH_CR_MER', 'FLASH_CR_OPTPG',
    'FLASH_CR_OPTER', 'FLASH_CR_STRT', 'FLASH_CR_LOCK', 'FLASH_CR_OPTWRE',
    'FLASH_CR_ERRIE', 'FLASH_CR_EOPIE', 'FLASH_AR_FAR', 'FLASH_OBR_OPTERR',
    'FLASH_OBR_RDPRT', 'FLASH_OBR_USER', 'FLASH_OBR_WDG_SW', 'FLASH_OBR_nRST_STOP',
    'FLASH_OBR_nRST_STDBY', 'FLASH_OBR_BFB2', 'FLASH_WRPR_WRP', 'FLASH_RDP_RDP',
    'FLASH_RDP_nRDP', 'FLASH_USER_USER', 'FLASH_USER_nUSER', 'FLASH_Data0_Data0',
    'FLASH_Data0_nData0', 'FLASH_Data1_Data1', 'FLASH_Data1_nData1', 'FLASH_WRP0_WRP0',
    'FLASH_WRP0_nWRP0', 'FLASH_WRP1_WRP1', 'FLASH_WRP1_nWRP1', 'FLASH_WRP2_WRP2',
    'FLASH_WRP2_nWRP2', 'FLASH_WRP3_WRP3', 'FLASH_WRP3_nWRP3', 'ADC_TypeDef',
    'BKP_TypeDef', 'CAN_TxMailBox_TypeDef', 'CAN_FIFOMailBox_TypeDef',
    'CAN_FilterRegister_TypeDef', 'CEC_TypeDef', 'CRC_TypeDef', 'DAC_TypeDef',
    'DBGMCU_TypeDef', 'DMA_Channel_TypeDef', 'DMA_TypeDef', 'ETH_TypeDef',
    'EXTI_TypeDef', 'FLASH_TypeDef', 'OB_TypeDef', 'FSMC_Bank1_TypeDef',
    'FSMC_Bank1E_TypeDef', 'FSMC_Bank2_TypeDef', 'FSMC_Bank3_TypeDef',
    'FSMC_Bank4_TypeDef', 'GPIO_TypeDef', 'AFIO_TypeDef', 'I2C_TypeDef', 'IWDG_TypeDef',
    'PWR_TypeDef', 'RCC_TypeDef', 'RTC_TypeDef', 'SDIO_TypeDef', 'SPI_TypeDef',
    'TIM_TypeDef', 'USART_TypeDef', 'WWDG_TypeDef']
