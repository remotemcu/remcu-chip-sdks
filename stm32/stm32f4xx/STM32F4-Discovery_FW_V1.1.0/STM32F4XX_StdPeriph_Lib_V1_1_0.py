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
# version: 1.0r
#
# word size : 32 bit
# pointer size : 64 bit
#
#


import ctypes



__RUN = 0
__HALT = 1
__ERROR = 0
__WARNING = 1
__INFO = 2
__DEBUG = 3
__ALL_LOG = 4
DEFAULT_OPENOCD_PORT = 6666
DEFAULT_GDB_PORT = 3333
# file stm32f4xx_tim.h : 

# empty define __STM32F4xx_TIM_H
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
TIM2_TIM8_TRGO = 0x0
TIM2_ETH_PTP = 0x400
TIM2_USBFS_SOF = 0x800
TIM2_USBHS_SOF = 0xC00
TIM5_GPIO = 0x0
TIM5_LSI = 0x40
TIM5_LSE = 0x80
TIM5_RTC = 0xC0
TIM11_GPIO = 0x0
TIM11_HSE = 0x2
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

# file stm32f4xx_iwdg.h : 

# empty define __STM32F4xx_IWDG_H
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

# file stm32f4xx_flash.h : 

# Enum FLASH_Status
FLASH_BUSY = 0x1
FLASH_ERROR_PGS = 0x2
FLASH_ERROR_PGP = 0x3
FLASH_ERROR_PGA = 0x4
FLASH_ERROR_WRP = 0x5
FLASH_ERROR_PROGRAM = 0x6
FLASH_ERROR_OPERATION = 0x7
FLASH_COMPLETE = 0x8
# empty define __STM32F4xx_FLASH_H
FLASH_Latency_0 = 0x0
FLASH_Latency_1 = 0x1
FLASH_Latency_2 = 0x2
FLASH_Latency_3 = 0x3
FLASH_Latency_4 = 0x4
FLASH_Latency_5 = 0x5
FLASH_Latency_6 = 0x6
FLASH_Latency_7 = 0x7
VoltageRange_1 = 0x0
VoltageRange_2 = 0x1
VoltageRange_3 = 0x2
VoltageRange_4 = 0x3
FLASH_Sector_0 = 0x0
FLASH_Sector_1 = 0x8
FLASH_Sector_2 = 0x10
FLASH_Sector_3 = 0x18
FLASH_Sector_4 = 0x20
FLASH_Sector_5 = 0x28
FLASH_Sector_6 = 0x30
FLASH_Sector_7 = 0x38
FLASH_Sector_8 = 0x40
FLASH_Sector_9 = 0x48
FLASH_Sector_10 = 0x50
FLASH_Sector_11 = 0x58
OB_WRP_Sector_0 = 0x1
OB_WRP_Sector_1 = 0x2
OB_WRP_Sector_2 = 0x4
OB_WRP_Sector_3 = 0x8
OB_WRP_Sector_4 = 0x10
OB_WRP_Sector_5 = 0x20
OB_WRP_Sector_6 = 0x40
OB_WRP_Sector_7 = 0x80
OB_WRP_Sector_8 = 0x100
OB_WRP_Sector_9 = 0x200
OB_WRP_Sector_10 = 0x400
OB_WRP_Sector_11 = 0x800
OB_WRP_Sector_All = 0xFFF
OB_RDP_Level_0 = 0xAA
OB_RDP_Level_1 = 0x55
OB_IWDG_SW = 0x20
OB_IWDG_HW = 0x0
OB_STOP_NoRST = 0x40
OB_STOP_RST = 0x0
OB_STDBY_NoRST = 0x80
OB_STDBY_RST = 0x0
OB_BOR_LEVEL3 = 0x0
OB_BOR_LEVEL2 = 0x4
OB_BOR_LEVEL1 = 0x8
OB_BOR_OFF = 0xC
FLASH_IT_EOP = 0x1000000
FLASH_IT_ERR = 0x2000000
FLASH_FLAG_EOP = 0x1
FLASH_FLAG_OPERR = 0x2
FLASH_FLAG_WRPERR = 0x10
FLASH_FLAG_PGAERR = 0x20
FLASH_FLAG_PGPERR = 0x40
FLASH_FLAG_PGSERR = 0x80
FLASH_FLAG_BSY = 0x10000
FLASH_PSIZE_BYTE = 0x0
FLASH_PSIZE_HALF_WORD = 0x100
FLASH_PSIZE_WORD = 0x200
FLASH_PSIZE_DOUBLE_WORD = 0x300
CR_PSIZE_MASK = 0xFFFFFCFF
RDP_KEY = 0xA5
FLASH_KEY1 = 0x45670123
FLASH_KEY2 = 0xCDEF89AB
FLASH_OPT_KEY1 = 0x8192A3B
FLASH_OPT_KEY2 = 0x4C5D6E7F
ACR_BYTE0_ADDRESS = 0x40023C00
OPTCR_BYTE0_ADDRESS = 0x40023C14
OPTCR_BYTE1_ADDRESS = 0x40023C15
OPTCR_BYTE2_ADDRESS = 0x40023C16
# ----------------------------------------

# file stm32f4xx_crc.h : 

# empty define __STM32F4xx_CRC_H
# ----------------------------------------

# file stm32f4xx_pwr.h : 

# empty define __STM32F4xx_PWR_H
PWR_PVDLevel_0 = 0x0
PWR_PVDLevel_1 = 0x20
PWR_PVDLevel_2 = 0x40
PWR_PVDLevel_3 = 0x60
PWR_PVDLevel_4 = 0x80
PWR_PVDLevel_5 = 0xA0
PWR_PVDLevel_6 = 0xC0
PWR_PVDLevel_7 = 0xE0
PWR_Regulator_ON = 0x0
PWR_Regulator_LowPower = 0x1
PWR_STOPEntry_WFI = 0x1
PWR_STOPEntry_WFE = 0x2
PWR_Regulator_Voltage_Scale1 = 0x4000
PWR_Regulator_Voltage_Scale2 = 0x0
PWR_FLAG_WU = 0x1
PWR_FLAG_SB = 0x2
PWR_FLAG_PVDO = 0x4
PWR_FLAG_BRR = 0x8
PWR_FLAG_VOSRDY = 0x4000
PWR_FLAG_REGRDY = 0x4000
# ----------------------------------------

# file stm32f4xx_gpio.h : 

# Enum GPIOMode_TypeDef
GPIO_Mode_IN = 0x0
GPIO_Mode_OUT = 0x1
GPIO_Mode_AF = 0x2
GPIO_Mode_AN = 0x3
# Enum GPIOOType_TypeDef
GPIO_OType_PP = 0x0
GPIO_OType_OD = 0x1
# Enum GPIOSpeed_TypeDef
GPIO_Speed_2MHz = 0x0
GPIO_Speed_25MHz = 0x1
GPIO_Speed_50MHz = 0x2
GPIO_Speed_100MHz = 0x3
# Enum GPIOPuPd_TypeDef
GPIO_PuPd_NOPULL = 0x0
GPIO_PuPd_UP = 0x1
GPIO_PuPd_DOWN = 0x2
# Enum BitAction
Bit_RESET = 0x0
Bit_SET = 0x1
# empty define __STM32F4xx_GPIO_H
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
GPIO_AF_RTC_50Hz = 0x0
GPIO_AF_MCO = 0x0
GPIO_AF_TAMPER = 0x0
GPIO_AF_SWJ = 0x0
GPIO_AF_TRACE = 0x0
GPIO_AF_TIM1 = 0x1
GPIO_AF_TIM2 = 0x1
GPIO_AF_TIM3 = 0x2
GPIO_AF_TIM4 = 0x2
GPIO_AF_TIM5 = 0x2
GPIO_AF_TIM8 = 0x3
GPIO_AF_TIM9 = 0x3
GPIO_AF_TIM10 = 0x3
GPIO_AF_TIM11 = 0x3
GPIO_AF_I2C1 = 0x4
GPIO_AF_I2C2 = 0x4
GPIO_AF_I2C3 = 0x4
GPIO_AF_SPI1 = 0x5
GPIO_AF_SPI2 = 0x5
GPIO_AF_SPI3 = 0x6
GPIO_AF_USART1 = 0x7
GPIO_AF_USART2 = 0x7
GPIO_AF_USART3 = 0x7
GPIO_AF_I2S3ext = 0x7
GPIO_AF_UART4 = 0x8
GPIO_AF_UART5 = 0x8
GPIO_AF_USART6 = 0x8
GPIO_AF_CAN1 = 0x9
GPIO_AF_CAN2 = 0x9
GPIO_AF_TIM12 = 0x9
GPIO_AF_TIM13 = 0x9
GPIO_AF_TIM14 = 0x9
GPIO_AF_OTG_FS = 0xA
GPIO_AF_OTG_HS = 0xA
GPIO_AF_ETH = 0xB
GPIO_AF_FSMC = 0xC
GPIO_AF_OTG_HS_FS = 0xC
GPIO_AF_SDIO = 0xC
GPIO_AF_DCMI = 0xD
GPIO_AF_EVENTOUT = 0xF
GPIO_Mode_AIN = 0x3
GPIO_AF_OTG1_FS = 0xA
GPIO_AF_OTG2_HS = 0xA
GPIO_AF_OTG2_FS = 0xC
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

# file stm32f4xx_adc.h : 

# empty define __STM32F4xx_ADC_H
ADC_Mode_Independent = 0x0
ADC_DualMode_RegSimult_InjecSimult = 0x1
ADC_DualMode_RegSimult_AlterTrig = 0x2
ADC_DualMode_InjecSimult = 0x5
ADC_DualMode_RegSimult = 0x6
ADC_DualMode_Interl = 0x7
ADC_DualMode_AlterTrig = 0x9
ADC_TripleMode_RegSimult_InjecSimult = 0x11
ADC_TripleMode_RegSimult_AlterTrig = 0x12
ADC_TripleMode_InjecSimult = 0x15
ADC_TripleMode_RegSimult = 0x16
ADC_TripleMode_Interl = 0x17
ADC_TripleMode_AlterTrig = 0x19
ADC_Prescaler_Div2 = 0x0
ADC_Prescaler_Div4 = 0x10000
ADC_Prescaler_Div6 = 0x20000
ADC_Prescaler_Div8 = 0x30000
ADC_DMAAccessMode_Disabled = 0x0
ADC_DMAAccessMode_1 = 0x4000
ADC_DMAAccessMode_2 = 0x8000
ADC_DMAAccessMode_3 = 0xC000
ADC_TwoSamplingDelay_5Cycles = 0x0
ADC_TwoSamplingDelay_6Cycles = 0x100
ADC_TwoSamplingDelay_7Cycles = 0x200
ADC_TwoSamplingDelay_8Cycles = 0x300
ADC_TwoSamplingDelay_9Cycles = 0x400
ADC_TwoSamplingDelay_10Cycles = 0x500
ADC_TwoSamplingDelay_11Cycles = 0x600
ADC_TwoSamplingDelay_12Cycles = 0x700
ADC_TwoSamplingDelay_13Cycles = 0x800
ADC_TwoSamplingDelay_14Cycles = 0x900
ADC_TwoSamplingDelay_15Cycles = 0xA00
ADC_TwoSamplingDelay_16Cycles = 0xB00
ADC_TwoSamplingDelay_17Cycles = 0xC00
ADC_TwoSamplingDelay_18Cycles = 0xD00
ADC_TwoSamplingDelay_19Cycles = 0xE00
ADC_TwoSamplingDelay_20Cycles = 0xF00
ADC_Resolution_12b = 0x0
ADC_Resolution_10b = 0x1000000
ADC_Resolution_8b = 0x2000000
ADC_Resolution_6b = 0x3000000
ADC_ExternalTrigConvEdge_None = 0x0
ADC_ExternalTrigConvEdge_Rising = 0x10000000
ADC_ExternalTrigConvEdge_Falling = 0x20000000
ADC_ExternalTrigConvEdge_RisingFalling = 0x30000000
ADC_ExternalTrigConv_T1_CC1 = 0x0
ADC_ExternalTrigConv_T1_CC2 = 0x1000000
ADC_ExternalTrigConv_T1_CC3 = 0x2000000
ADC_ExternalTrigConv_T2_CC2 = 0x3000000
ADC_ExternalTrigConv_T2_CC3 = 0x4000000
ADC_ExternalTrigConv_T2_CC4 = 0x5000000
ADC_ExternalTrigConv_T2_TRGO = 0x6000000
ADC_ExternalTrigConv_T3_CC1 = 0x7000000
ADC_ExternalTrigConv_T3_TRGO = 0x8000000
ADC_ExternalTrigConv_T4_CC4 = 0x9000000
ADC_ExternalTrigConv_T5_CC1 = 0xA000000
ADC_ExternalTrigConv_T5_CC2 = 0xB000000
ADC_ExternalTrigConv_T5_CC3 = 0xC000000
ADC_ExternalTrigConv_T8_CC1 = 0xD000000
ADC_ExternalTrigConv_T8_TRGO = 0xE000000
ADC_ExternalTrigConv_Ext_IT11 = 0xF000000
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
ADC_Channel_18 = 0x12
ADC_Channel_TempSensor = 0x10
ADC_Channel_Vrefint = 0x11
ADC_Channel_Vbat = 0x12
ADC_SampleTime_3Cycles = 0x0
ADC_SampleTime_15Cycles = 0x1
ADC_SampleTime_28Cycles = 0x2
ADC_SampleTime_56Cycles = 0x3
ADC_SampleTime_84Cycles = 0x4
ADC_SampleTime_112Cycles = 0x5
ADC_SampleTime_144Cycles = 0x6
ADC_SampleTime_480Cycles = 0x7
ADC_ExternalTrigInjecConvEdge_None = 0x0
ADC_ExternalTrigInjecConvEdge_Rising = 0x100000
ADC_ExternalTrigInjecConvEdge_Falling = 0x200000
ADC_ExternalTrigInjecConvEdge_RisingFalling = 0x300000
ADC_ExternalTrigInjecConv_T1_CC4 = 0x0
ADC_ExternalTrigInjecConv_T1_TRGO = 0x10000
ADC_ExternalTrigInjecConv_T2_CC1 = 0x20000
ADC_ExternalTrigInjecConv_T2_TRGO = 0x30000
ADC_ExternalTrigInjecConv_T3_CC2 = 0x40000
ADC_ExternalTrigInjecConv_T3_CC4 = 0x50000
ADC_ExternalTrigInjecConv_T4_CC1 = 0x60000
ADC_ExternalTrigInjecConv_T4_CC2 = 0x70000
ADC_ExternalTrigInjecConv_T4_CC3 = 0x80000
ADC_ExternalTrigInjecConv_T4_TRGO = 0x90000
ADC_ExternalTrigInjecConv_T5_CC4 = 0xA0000
ADC_ExternalTrigInjecConv_T5_TRGO = 0xB0000
ADC_ExternalTrigInjecConv_T8_CC2 = 0xC0000
ADC_ExternalTrigInjecConv_T8_CC3 = 0xD0000
ADC_ExternalTrigInjecConv_T8_CC4 = 0xE0000
ADC_ExternalTrigInjecConv_Ext_IT15 = 0xF0000
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
ADC_IT_EOC = 0x205
ADC_IT_AWD = 0x106
ADC_IT_JEOC = 0x407
ADC_IT_OVR = 0x201A
ADC_FLAG_AWD = 0x1
ADC_FLAG_EOC = 0x2
ADC_FLAG_JEOC = 0x4
ADC_FLAG_JSTRT = 0x8
ADC_FLAG_STRT = 0x10
ADC_FLAG_OVR = 0x20
# struct ADC_InitTypeDef

class ADC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_Resolution',	ctypes.c_uint32),
		('ADC_ScanConvMode',	ctypes.c_uint32),
		('ADC_ContinuousConvMode',	ctypes.c_uint32),
		('ADC_ExternalTrigConvEdge',	ctypes.c_uint32),
		('ADC_ExternalTrigConv',	ctypes.c_uint32),
		('ADC_DataAlign',	ctypes.c_uint32),
		('ADC_NbrOfConversion',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ADC_CommonInitTypeDef

class ADC_CommonInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_Mode',	ctypes.c_uint32),
		('ADC_Prescaler',	ctypes.c_uint32),
		('ADC_DMAAccessMode',	ctypes.c_uint32),
		('ADC_TwoSamplingDelay',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f4xx_wwdg.h : 

# empty define __STM32F4xx_WWDG_H
WWDG_Prescaler_1 = 0x0
WWDG_Prescaler_2 = 0x80
WWDG_Prescaler_4 = 0x100
WWDG_Prescaler_8 = 0x180
# ----------------------------------------

# file stm32f4xx_usart.h : 

# empty define __STM32F4xx_USART_H
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
USART_IT_ORE_RX = 0x325
USART_IT_IDLE = 0x424
USART_IT_LBD = 0x846
USART_IT_CTS = 0x96A
USART_IT_ERR = 0x60
USART_IT_ORE_ER = 0x360
USART_IT_NE = 0x260
USART_IT_FE = 0x160
USART_IT_ORE = 0x360
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

# file stm32f4xx_dcmi.h : 

# empty define __STM32F4xx_DCMI_H
DCMI_CaptureMode_Continuous = 0x0
DCMI_CaptureMode_SnapShot = 0x2
DCMI_SynchroMode_Hardware = 0x0
DCMI_SynchroMode_Embedded = 0x10
DCMI_PCKPolarity_Falling = 0x0
DCMI_PCKPolarity_Rising = 0x20
DCMI_VSPolarity_Low = 0x0
DCMI_VSPolarity_High = 0x80
DCMI_HSPolarity_Low = 0x0
DCMI_HSPolarity_High = 0x40
DCMI_CaptureRate_All_Frame = 0x0
DCMI_CaptureRate_1of2_Frame = 0x100
DCMI_CaptureRate_1of4_Frame = 0x200
DCMI_ExtendedDataMode_8b = 0x0
DCMI_ExtendedDataMode_10b = 0x400
DCMI_ExtendedDataMode_12b = 0x800
DCMI_ExtendedDataMode_14b = 0xC00
DCMI_IT_FRAME = 0x1
DCMI_IT_OVF = 0x2
DCMI_IT_ERR = 0x4
DCMI_IT_VSYNC = 0x8
DCMI_IT_LINE = 0x10
DCMI_FLAG_HSYNC = 0x2001
DCMI_FLAG_VSYNC = 0x2002
DCMI_FLAG_FNE = 0x2004
DCMI_FLAG_FRAMERI = 0x1
DCMI_FLAG_OVFRI = 0x2
DCMI_FLAG_ERRRI = 0x4
DCMI_FLAG_VSYNCRI = 0x8
DCMI_FLAG_LINERI = 0x10
DCMI_FLAG_FRAMEMI = 0x1001
DCMI_FLAG_OVFMI = 0x1002
DCMI_FLAG_ERRMI = 0x1004
DCMI_FLAG_VSYNCMI = 0x1008
DCMI_FLAG_LINEMI = 0x1010
# struct DCMI_InitTypeDef

class DCMI_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DCMI_CaptureMode',	ctypes.c_uint16),
		('DCMI_SynchroMode',	ctypes.c_uint16),
		('DCMI_PCKPolarity',	ctypes.c_uint16),
		('DCMI_VSPolarity',	ctypes.c_uint16),
		('DCMI_HSPolarity',	ctypes.c_uint16),
		('DCMI_CaptureRate',	ctypes.c_uint16),
		('DCMI_ExtendedDataMode',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DCMI_CROPInitTypeDef

class DCMI_CROPInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DCMI_VerticalStartLine',	ctypes.c_uint16),
		('DCMI_HorizontalOffsetCount',	ctypes.c_uint16),
		('DCMI_VerticalLineCount',	ctypes.c_uint16),
		('DCMI_CaptureCount',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DCMI_CodesInitTypeDef

class DCMI_CodesInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DCMI_FrameStartCode',	ctypes.c_uint8),
		('DCMI_LineStartCode',	ctypes.c_uint8),
		('DCMI_LineEndCode',	ctypes.c_uint8),
		('DCMI_FrameEndCode',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f4xx_exti.h : 

# Enum EXTIMode_TypeDef
EXTI_Mode_Interrupt = 0x0
EXTI_Mode_Event = 0x4
# Enum EXTITrigger_TypeDef
EXTI_Trigger_Rising = 0x8
EXTI_Trigger_Falling = 0xC
EXTI_Trigger_Rising_Falling = 0x10
# empty define __STM32F4xx_EXTI_H
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

# file stm32f4xx_rcc.h : 

# empty define __STM32F4xx_RCC_H
RCC_HSE_OFF = 0x0
RCC_HSE_ON = 0x1
RCC_HSE_Bypass = 0x5
RCC_PLLSource_HSI = 0x0
RCC_PLLSource_HSE = 0x400000
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
RCC_HCLK_Div2 = 0x1000
RCC_HCLK_Div4 = 0x1400
RCC_HCLK_Div8 = 0x1800
RCC_HCLK_Div16 = 0x1C00
RCC_IT_LSIRDY = 0x1
RCC_IT_LSERDY = 0x2
RCC_IT_HSIRDY = 0x4
RCC_IT_HSERDY = 0x8
RCC_IT_PLLRDY = 0x10
RCC_IT_PLLI2SRDY = 0x20
RCC_IT_CSS = 0x80
RCC_LSE_OFF = 0x0
RCC_LSE_ON = 0x1
RCC_LSE_Bypass = 0x4
RCC_RTCCLKSource_LSE = 0x100
RCC_RTCCLKSource_LSI = 0x200
RCC_RTCCLKSource_HSE_Div2 = 0x20300
RCC_RTCCLKSource_HSE_Div3 = 0x30300
RCC_RTCCLKSource_HSE_Div4 = 0x40300
RCC_RTCCLKSource_HSE_Div5 = 0x50300
RCC_RTCCLKSource_HSE_Div6 = 0x60300
RCC_RTCCLKSource_HSE_Div7 = 0x70300
RCC_RTCCLKSource_HSE_Div8 = 0x80300
RCC_RTCCLKSource_HSE_Div9 = 0x90300
RCC_RTCCLKSource_HSE_Div10 = 0xA0300
RCC_RTCCLKSource_HSE_Div11 = 0xB0300
RCC_RTCCLKSource_HSE_Div12 = 0xC0300
RCC_RTCCLKSource_HSE_Div13 = 0xD0300
RCC_RTCCLKSource_HSE_Div14 = 0xE0300
RCC_RTCCLKSource_HSE_Div15 = 0xF0300
RCC_RTCCLKSource_HSE_Div16 = 0x100300
RCC_RTCCLKSource_HSE_Div17 = 0x110300
RCC_RTCCLKSource_HSE_Div18 = 0x120300
RCC_RTCCLKSource_HSE_Div19 = 0x130300
RCC_RTCCLKSource_HSE_Div20 = 0x140300
RCC_RTCCLKSource_HSE_Div21 = 0x150300
RCC_RTCCLKSource_HSE_Div22 = 0x160300
RCC_RTCCLKSource_HSE_Div23 = 0x170300
RCC_RTCCLKSource_HSE_Div24 = 0x180300
RCC_RTCCLKSource_HSE_Div25 = 0x190300
RCC_RTCCLKSource_HSE_Div26 = 0x1A0300
RCC_RTCCLKSource_HSE_Div27 = 0x1B0300
RCC_RTCCLKSource_HSE_Div28 = 0x1C0300
RCC_RTCCLKSource_HSE_Div29 = 0x1D0300
RCC_RTCCLKSource_HSE_Div30 = 0x1E0300
RCC_RTCCLKSource_HSE_Div31 = 0x1F0300
RCC_I2S2CLKSource_PLLI2S = 0x0
RCC_I2S2CLKSource_Ext = 0x1
RCC_AHB1Periph_GPIOA = 0x1
RCC_AHB1Periph_GPIOB = 0x2
RCC_AHB1Periph_GPIOC = 0x4
RCC_AHB1Periph_GPIOD = 0x8
RCC_AHB1Periph_GPIOE = 0x10
RCC_AHB1Periph_GPIOF = 0x20
RCC_AHB1Periph_GPIOG = 0x40
RCC_AHB1Periph_GPIOH = 0x80
RCC_AHB1Periph_GPIOI = 0x100
RCC_AHB1Periph_CRC = 0x1000
RCC_AHB1Periph_FLITF = 0x8000
RCC_AHB1Periph_SRAM1 = 0x10000
RCC_AHB1Periph_SRAM2 = 0x20000
RCC_AHB1Periph_BKPSRAM = 0x40000
RCC_AHB1Periph_CCMDATARAMEN = 0x100000
RCC_AHB1Periph_DMA1 = 0x200000
RCC_AHB1Periph_DMA2 = 0x400000
RCC_AHB1Periph_ETH_MAC = 0x2000000
RCC_AHB1Periph_ETH_MAC_Tx = 0x4000000
RCC_AHB1Periph_ETH_MAC_Rx = 0x8000000
RCC_AHB1Periph_ETH_MAC_PTP = 0x10000000
RCC_AHB1Periph_OTG_HS = 0x20000000
RCC_AHB1Periph_OTG_HS_ULPI = 0x40000000
RCC_AHB2Periph_DCMI = 0x1
RCC_AHB2Periph_CRYP = 0x10
RCC_AHB2Periph_HASH = 0x20
RCC_AHB2Periph_RNG = 0x40
RCC_AHB2Periph_OTG_FS = 0x80
RCC_AHB3Periph_FSMC = 0x1
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
RCC_APB1Periph_I2C3 = 0x800000
RCC_APB1Periph_CAN1 = 0x2000000
RCC_APB1Periph_CAN2 = 0x4000000
RCC_APB1Periph_PWR = 0x10000000
RCC_APB1Periph_DAC = 0x20000000
RCC_APB2Periph_TIM1 = 0x1
RCC_APB2Periph_TIM8 = 0x2
RCC_APB2Periph_USART1 = 0x10
RCC_APB2Periph_USART6 = 0x20
RCC_APB2Periph_ADC = 0x100
RCC_APB2Periph_ADC1 = 0x100
RCC_APB2Periph_ADC2 = 0x200
RCC_APB2Periph_ADC3 = 0x400
RCC_APB2Periph_SDIO = 0x800
RCC_APB2Periph_SPI1 = 0x1000
RCC_APB2Periph_SYSCFG = 0x4000
RCC_APB2Periph_TIM9 = 0x10000
RCC_APB2Periph_TIM10 = 0x20000
RCC_APB2Periph_TIM11 = 0x40000
RCC_MCO1Source_HSI = 0x0
RCC_MCO1Source_LSE = 0x200000
RCC_MCO1Source_HSE = 0x400000
RCC_MCO1Source_PLLCLK = 0x600000
RCC_MCO1Div_1 = 0x0
RCC_MCO1Div_2 = 0x4000000
RCC_MCO1Div_3 = 0x5000000
RCC_MCO1Div_4 = 0x6000000
RCC_MCO1Div_5 = 0x7000000
RCC_MCO2Source_SYSCLK = 0x0
RCC_MCO2Source_PLLI2SCLK = 0x40000000
RCC_MCO2Source_HSE = 0x80000000
RCC_MCO2Source_PLLCLK = 0xC0000000
RCC_MCO2Div_1 = 0x0
RCC_MCO2Div_2 = 0x20000000
RCC_MCO2Div_3 = 0x28000000
RCC_MCO2Div_4 = 0x30000000
RCC_MCO2Div_5 = 0x38000000
RCC_FLAG_HSIRDY = 0x21
RCC_FLAG_HSERDY = 0x31
RCC_FLAG_PLLRDY = 0x39
RCC_FLAG_PLLI2SRDY = 0x3B
RCC_FLAG_LSERDY = 0x41
RCC_FLAG_LSIRDY = 0x61
RCC_FLAG_BORRST = 0x79
RCC_FLAG_PINRST = 0x7A
RCC_FLAG_PORRST = 0x7B
RCC_FLAG_SFTRST = 0x7C
RCC_FLAG_IWDGRST = 0x7D
RCC_FLAG_WWDGRST = 0x7E
RCC_FLAG_LPWRRST = 0x7F
# struct RCC_ClocksTypeDef

class RCC_ClocksTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SYSCLK_Frequency',	ctypes.c_uint32),
		('HCLK_Frequency',	ctypes.c_uint32),
		('PCLK1_Frequency',	ctypes.c_uint32),
		('PCLK2_Frequency',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f4xx_dma.h : 

# empty define __STM32F4xx_DMA_H
DMA_Channel_0 = 0x0
DMA_Channel_1 = 0x2000000
DMA_Channel_2 = 0x4000000
DMA_Channel_3 = 0x6000000
DMA_Channel_4 = 0x8000000
DMA_Channel_5 = 0xA000000
DMA_Channel_6 = 0xC000000
DMA_Channel_7 = 0xE000000
DMA_DIR_PeripheralToMemory = 0x0
DMA_DIR_MemoryToPeripheral = 0x40
DMA_DIR_MemoryToMemory = 0x80
DMA_PeripheralInc_Enable = 0x200
DMA_PeripheralInc_Disable = 0x0
DMA_MemoryInc_Enable = 0x400
DMA_MemoryInc_Disable = 0x0
DMA_PeripheralDataSize_Byte = 0x0
DMA_PeripheralDataSize_HalfWord = 0x800
DMA_PeripheralDataSize_Word = 0x1000
DMA_MemoryDataSize_Byte = 0x0
DMA_MemoryDataSize_HalfWord = 0x2000
DMA_MemoryDataSize_Word = 0x4000
DMA_Mode_Normal = 0x0
DMA_Mode_Circular = 0x100
DMA_Priority_Low = 0x0
DMA_Priority_Medium = 0x10000
DMA_Priority_High = 0x20000
DMA_Priority_VeryHigh = 0x30000
DMA_FIFOMode_Disable = 0x0
DMA_FIFOMode_Enable = 0x4
DMA_FIFOThreshold_1QuarterFull = 0x0
DMA_FIFOThreshold_HalfFull = 0x1
DMA_FIFOThreshold_3QuartersFull = 0x2
DMA_FIFOThreshold_Full = 0x3
DMA_MemoryBurst_Single = 0x0
DMA_MemoryBurst_INC4 = 0x800000
DMA_MemoryBurst_INC8 = 0x1000000
DMA_MemoryBurst_INC16 = 0x1800000
DMA_PeripheralBurst_Single = 0x0
DMA_PeripheralBurst_INC4 = 0x200000
DMA_PeripheralBurst_INC8 = 0x400000
DMA_PeripheralBurst_INC16 = 0x600000
DMA_FIFOStatus_Less1QuarterFull = 0x0
DMA_FIFOStatus_1QuarterFull = 0x8
DMA_FIFOStatus_HalfFull = 0x10
DMA_FIFOStatus_3QuartersFull = 0x18
DMA_FIFOStatus_Empty = 0x20
DMA_FIFOStatus_Full = 0x28
DMA_FLAG_FEIF0 = 0x10800001
DMA_FLAG_DMEIF0 = 0x10800004
DMA_FLAG_TEIF0 = 0x10000008
DMA_FLAG_HTIF0 = 0x10000010
DMA_FLAG_TCIF0 = 0x10000020
DMA_FLAG_FEIF1 = 0x10000040
DMA_FLAG_DMEIF1 = 0x10000100
DMA_FLAG_TEIF1 = 0x10000200
DMA_FLAG_HTIF1 = 0x10000400
DMA_FLAG_TCIF1 = 0x10000800
DMA_FLAG_FEIF2 = 0x10010000
DMA_FLAG_DMEIF2 = 0x10040000
DMA_FLAG_TEIF2 = 0x10080000
DMA_FLAG_HTIF2 = 0x10100000
DMA_FLAG_TCIF2 = 0x10200000
DMA_FLAG_FEIF3 = 0x10400000
DMA_FLAG_DMEIF3 = 0x11000000
DMA_FLAG_TEIF3 = 0x12000000
DMA_FLAG_HTIF3 = 0x14000000
DMA_FLAG_TCIF3 = 0x18000000
DMA_FLAG_FEIF4 = 0x20000001
DMA_FLAG_DMEIF4 = 0x20000004
DMA_FLAG_TEIF4 = 0x20000008
DMA_FLAG_HTIF4 = 0x20000010
DMA_FLAG_TCIF4 = 0x20000020
DMA_FLAG_FEIF5 = 0x20000040
DMA_FLAG_DMEIF5 = 0x20000100
DMA_FLAG_TEIF5 = 0x20000200
DMA_FLAG_HTIF5 = 0x20000400
DMA_FLAG_TCIF5 = 0x20000800
DMA_FLAG_FEIF6 = 0x20010000
DMA_FLAG_DMEIF6 = 0x20040000
DMA_FLAG_TEIF6 = 0x20080000
DMA_FLAG_HTIF6 = 0x20100000
DMA_FLAG_TCIF6 = 0x20200000
DMA_FLAG_FEIF7 = 0x20400000
DMA_FLAG_DMEIF7 = 0x21000000
DMA_FLAG_TEIF7 = 0x22000000
DMA_FLAG_HTIF7 = 0x24000000
DMA_FLAG_TCIF7 = 0x28000000
DMA_IT_TC = 0x10
DMA_IT_HT = 0x8
DMA_IT_TE = 0x4
DMA_IT_DME = 0x2
DMA_IT_FE = 0x80
DMA_IT_FEIF0 = 0x90000001
DMA_IT_DMEIF0 = 0x10001004
DMA_IT_TEIF0 = 0x10002008
DMA_IT_HTIF0 = 0x10004010
DMA_IT_TCIF0 = 0x10008020
DMA_IT_FEIF1 = 0x90000040
DMA_IT_DMEIF1 = 0x10001100
DMA_IT_TEIF1 = 0x10002200
DMA_IT_HTIF1 = 0x10004400
DMA_IT_TCIF1 = 0x10008800
DMA_IT_FEIF2 = 0x90010000
DMA_IT_DMEIF2 = 0x10041000
DMA_IT_TEIF2 = 0x10082000
DMA_IT_HTIF2 = 0x10104000
DMA_IT_TCIF2 = 0x10208000
DMA_IT_FEIF3 = 0x90400000
DMA_IT_DMEIF3 = 0x11001000
DMA_IT_TEIF3 = 0x12002000
DMA_IT_HTIF3 = 0x14004000
DMA_IT_TCIF3 = 0x18008000
DMA_IT_FEIF4 = 0xA0000001
DMA_IT_DMEIF4 = 0x20001004
DMA_IT_TEIF4 = 0x20002008
DMA_IT_HTIF4 = 0x20004010
DMA_IT_TCIF4 = 0x20008020
DMA_IT_FEIF5 = 0xA0000040
DMA_IT_DMEIF5 = 0x20001100
DMA_IT_TEIF5 = 0x20002200
DMA_IT_HTIF5 = 0x20004400
DMA_IT_TCIF5 = 0x20008800
DMA_IT_FEIF6 = 0xA0010000
DMA_IT_DMEIF6 = 0x20041000
DMA_IT_TEIF6 = 0x20082000
DMA_IT_HTIF6 = 0x20104000
DMA_IT_TCIF6 = 0x20208000
DMA_IT_FEIF7 = 0xA0400000
DMA_IT_DMEIF7 = 0x21001000
DMA_IT_TEIF7 = 0x22002000
DMA_IT_HTIF7 = 0x24004000
DMA_IT_TCIF7 = 0x28008000
DMA_PINCOS_Psize = 0x0
DMA_PINCOS_WordAligned = 0x8000
DMA_FlowCtrl_Memory = 0x0
DMA_FlowCtrl_Peripheral = 0x20
DMA_Memory_0 = 0x0
DMA_Memory_1 = 0x80000
# struct DMA_InitTypeDef

class DMA_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DMA_Channel',	ctypes.c_uint32),
		('DMA_PeripheralBaseAddr',	ctypes.c_uint32),
		('DMA_Memory0BaseAddr',	ctypes.c_uint32),
		('DMA_DIR',	ctypes.c_uint32),
		('DMA_BufferSize',	ctypes.c_uint32),
		('DMA_PeripheralInc',	ctypes.c_uint32),
		('DMA_MemoryInc',	ctypes.c_uint32),
		('DMA_PeripheralDataSize',	ctypes.c_uint32),
		('DMA_MemoryDataSize',	ctypes.c_uint32),
		('DMA_Mode',	ctypes.c_uint32),
		('DMA_Priority',	ctypes.c_uint32),
		('DMA_FIFOMode',	ctypes.c_uint32),
		('DMA_FIFOThreshold',	ctypes.c_uint32),
		('DMA_MemoryBurst',	ctypes.c_uint32),
		('DMA_PeripheralBurst',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f4xx_hash.h : 

# empty define __STM32F4xx_HASH_H
HASH_AlgoSelection_SHA1 = 0x0
HASH_AlgoSelection_MD5 = 0x80
HASH_AlgoMode_HASH = 0x0
HASH_AlgoMode_HMAC = 0x40
HASH_DataType_32b = 0x0
HASH_DataType_16b = 0x10
HASH_DataType_8b = 0x20
HASH_DataType_1b = 0x30
HASH_HMACKeyType_ShortKey = 0x0
HASH_HMACKeyType_LongKey = 0x10000
HASH_IT_DINI = 0x1
HASH_IT_DCI = 0x2
HASH_FLAG_DINIS = 0x1
HASH_FLAG_DCIS = 0x2
HASH_FLAG_DMAS = 0x4
HASH_FLAG_BUSY = 0x8
HASH_FLAG_DINNE = 0x1000
# struct HASH_InitTypeDef

class HASH_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('HASH_AlgoSelection',	ctypes.c_uint32),
		('HASH_AlgoMode',	ctypes.c_uint32),
		('HASH_DataType',	ctypes.c_uint32),
		('HASH_HMACKeyType',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct HASH_MsgDigest
# struct HASH_MsgDigest : field is array
# struct HASH_Context
# struct HASH_Context : field is array
# ----------------------------------------

# file stm32f4xx_fsmc.h : 

# empty define __STM32F4xx_FSMC_H
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
# struct FSMC_NORSRAMInitTypeDef : field is class
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
# struct FSMC_NANDInitTypeDef : field is class
# struct FSMC_PCCARDInitTypeDef
# struct FSMC_PCCARDInitTypeDef : field is class
# ----------------------------------------

# file stm32f4xx_spi.h : 

# empty define __STM32F4xx_SPI_H
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
I2S_IT_UDR = 0x53
SPI_I2S_IT_TIFRFE = 0x58
SPI_I2S_IT_OVR = 0x56
SPI_IT_MODF = 0x55
SPI_IT_CRCERR = 0x54
SPI_I2S_FLAG_RXNE = 0x1
SPI_I2S_FLAG_TXE = 0x2
I2S_FLAG_CHSIDE = 0x4
I2S_FLAG_UDR = 0x8
SPI_FLAG_CRCERR = 0x10
SPI_FLAG_MODF = 0x20
SPI_I2S_FLAG_OVR = 0x40
SPI_I2S_FLAG_BSY = 0x80
SPI_I2S_FLAG_TIFRFE = 0x100
SPI_DMAReq_Tx = 0x2
SPI_DMAReq_Rx = 0x1
SPI_IT_TXE = 0x71
SPI_IT_RXNE = 0x60
SPI_IT_ERR = 0x50
SPI_IT_OVR = 0x56
SPI_FLAG_RXNE = 0x1
SPI_FLAG_TXE = 0x2
SPI_FLAG_OVR = 0x40
SPI_FLAG_BSY = 0x80
# Skip SPI_DeInit : no need parse
# Skip SPI_ITConfig : no need parse
# Skip SPI_DMACmd : no need parse
# Skip SPI_SendData : no need parse
# Skip SPI_ReceiveData : no need parse
# Skip SPI_GetFlagStatus : no need parse
# Skip SPI_ClearFlag : no need parse
# Skip SPI_GetITStatus : no need parse
# Skip SPI_ClearITPendingBit : no need parse
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

# file stm32f4xx_cryp.h : 

# empty define __STM32F4xx_CRYP_H
CRYP_AlgoDir_Encrypt = 0x0
CRYP_AlgoDir_Decrypt = 0x4
CRYP_AlgoMode_TDES_ECB = 0x0
CRYP_AlgoMode_TDES_CBC = 0x8
CRYP_AlgoMode_DES_ECB = 0x10
CRYP_AlgoMode_DES_CBC = 0x18
CRYP_AlgoMode_AES_ECB = 0x20
CRYP_AlgoMode_AES_CBC = 0x28
CRYP_AlgoMode_AES_CTR = 0x30
CRYP_AlgoMode_AES_Key = 0x38
CRYP_DataType_32b = 0x0
CRYP_DataType_16b = 0x40
CRYP_DataType_8b = 0x80
CRYP_DataType_1b = 0xC0
CRYP_KeySize_128b = 0x0
CRYP_KeySize_192b = 0x100
CRYP_KeySize_256b = 0x200
CRYP_FLAG_BUSY = 0x10
CRYP_FLAG_IFEM = 0x1
CRYP_FLAG_IFNF = 0x2
CRYP_FLAG_INRIS = 0x22
CRYP_FLAG_OFNE = 0x4
CRYP_FLAG_OFFU = 0x8
CRYP_FLAG_OUTRIS = 0x21
CRYP_IT_INI = 0x1
CRYP_IT_OUTI = 0x2
MODE_ENCRYPT = 0x1
MODE_DECRYPT = 0x0
CRYP_DMAReq_DataIN = 0x1
CRYP_DMAReq_DataOUT = 0x2
# struct CRYP_InitTypeDef

class CRYP_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CRYP_AlgoDir',	ctypes.c_uint16),
		('CRYP_AlgoMode',	ctypes.c_uint16),
		('CRYP_DataType',	ctypes.c_uint16),
		('CRYP_KeySize',	ctypes.c_uint16),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CRYP_KeyInitTypeDef

class CRYP_KeyInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CRYP_Key0Left',	ctypes.c_uint32),
		('CRYP_Key0Right',	ctypes.c_uint32),
		('CRYP_Key1Left',	ctypes.c_uint32),
		('CRYP_Key1Right',	ctypes.c_uint32),
		('CRYP_Key2Left',	ctypes.c_uint32),
		('CRYP_Key2Right',	ctypes.c_uint32),
		('CRYP_Key3Left',	ctypes.c_uint32),
		('CRYP_Key3Right',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CRYP_IVInitTypeDef

class CRYP_IVInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CRYP_IV0Left',	ctypes.c_uint32),
		('CRYP_IV0Right',	ctypes.c_uint32),
		('CRYP_IV1Left',	ctypes.c_uint32),
		('CRYP_IV1Right',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct CRYP_Context

class CRYP_Context(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR_bits9to2',	ctypes.c_uint32),
		('CRYP_IV0LR',	ctypes.c_uint32),
		('CRYP_IV0RR',	ctypes.c_uint32),
		('CRYP_IV1LR',	ctypes.c_uint32),
		('CRYP_IV1RR',	ctypes.c_uint32),
		('CRYP_K0LR',	ctypes.c_uint32),
		('CRYP_K0RR',	ctypes.c_uint32),
		('CRYP_K1LR',	ctypes.c_uint32),
		('CRYP_K1RR',	ctypes.c_uint32),
		('CRYP_K2LR',	ctypes.c_uint32),
		('CRYP_K2RR',	ctypes.c_uint32),
		('CRYP_K3LR',	ctypes.c_uint32),
		('CRYP_K3RR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

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

# file stm32f4xx_dbgmcu.h : 

# empty define __STM32F4xx_DBGMCU_H
DBGMCU_SLEEP = 0x1
DBGMCU_STOP = 0x2
DBGMCU_STANDBY = 0x4
DBGMCU_TIM2_STOP = 0x1
DBGMCU_TIM3_STOP = 0x2
DBGMCU_TIM4_STOP = 0x4
DBGMCU_TIM5_STOP = 0x8
DBGMCU_TIM6_STOP = 0x10
DBGMCU_TIM7_STOP = 0x20
DBGMCU_TIM12_STOP = 0x40
DBGMCU_TIM13_STOP = 0x80
DBGMCU_TIM14_STOP = 0x100
DBGMCU_RTC_STOP = 0x400
DBGMCU_WWDG_STOP = 0x800
DBGMCU_IWDG_STOP = 0x1000
DBGMCU_I2C1_SMBUS_TIMEOUT = 0x200000
DBGMCU_I2C2_SMBUS_TIMEOUT = 0x400000
DBGMCU_I2C3_SMBUS_TIMEOUT = 0x800000
DBGMCU_CAN1_STOP = 0x2000000
DBGMCU_CAN2_STOP = 0x4000000
DBGMCU_TIM1_STOP = 0x1
DBGMCU_TIM8_STOP = 0x2
DBGMCU_TIM9_STOP = 0x10000
DBGMCU_TIM10_STOP = 0x20000
DBGMCU_TIM11_STOP = 0x40000
# ----------------------------------------

# file stm32f4xx_syscfg.h : 

# empty define __STM32F4xx_SYSCFG_H
EXTI_PortSourceGPIOA = 0x0
EXTI_PortSourceGPIOB = 0x1
EXTI_PortSourceGPIOC = 0x2
EXTI_PortSourceGPIOD = 0x3
EXTI_PortSourceGPIOE = 0x4
EXTI_PortSourceGPIOF = 0x5
EXTI_PortSourceGPIOG = 0x6
EXTI_PortSourceGPIOH = 0x7
EXTI_PortSourceGPIOI = 0x8
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
SYSCFG_MemoryRemap_SystemFlash = 0x1
SYSCFG_MemoryRemap_FSMC = 0x2
SYSCFG_MemoryRemap_SRAM = 0x3
SYSCFG_ETH_MediaInterface_MII = 0x0
SYSCFG_ETH_MediaInterface_RMII = 0x1
# ----------------------------------------

# file stm32f4xx_i2c.h : 

# empty define __STM32F4xx_I2C_H
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
I2C_NACKPosition_Next = 0x800
I2C_NACKPosition_Current = 0xF7FF
I2C_SMBusAlert_Low = 0x2000
I2C_SMBusAlert_High = 0xDFFF
I2C_PECPosition_Next = 0x800
I2C_PECPosition_Current = 0xF7FF
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

# file stm32f4xx_dac.h : 

# empty define __STM32F4xx_DAC_H
DAC_Trigger_None = 0x0
DAC_Trigger_T2_TRGO = 0x24
DAC_Trigger_T4_TRGO = 0x2C
DAC_Trigger_T5_TRGO = 0x1C
DAC_Trigger_T6_TRGO = 0x4
DAC_Trigger_T7_TRGO = 0x14
DAC_Trigger_T8_TRGO = 0xC
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

# file stm32f4xx_rtc.h : 

# empty define __STM32F4xx_RTC_H
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
RTC_Alarm_B = 0x200
RTC_AlarmSubSecondMask_All = 0x0
RTC_AlarmSubSecondMask_SS14_1 = 0x1000000
RTC_AlarmSubSecondMask_SS14_2 = 0x2000000
RTC_AlarmSubSecondMask_SS14_3 = 0x3000000
RTC_AlarmSubSecondMask_SS14_4 = 0x4000000
RTC_AlarmSubSecondMask_SS14_5 = 0x5000000
RTC_AlarmSubSecondMask_SS14_6 = 0x6000000
RTC_AlarmSubSecondMask_SS14_7 = 0x7000000
RTC_AlarmSubSecondMask_SS14_8 = 0x8000000
RTC_AlarmSubSecondMask_SS14_9 = 0x9000000
RTC_AlarmSubSecondMask_SS14_10 = 0xA000000
RTC_AlarmSubSecondMask_SS14_11 = 0xB000000
RTC_AlarmSubSecondMask_SS14_12 = 0xC000000
RTC_AlarmSubSecondMask_SS14_13 = 0xD000000
RTC_AlarmSubSecondMask_SS14 = 0xE000000
RTC_AlarmSubSecondMask_None = 0xF000000
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
RTC_Output_AlarmB = 0x400000
RTC_Output_WakeUp = 0x600000
RTC_OutputPolarity_High = 0x0
RTC_OutputPolarity_Low = 0x100000
RTC_CalibSign_Positive = 0x0
RTC_CalibSign_Negative = 0x80
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
RTC_TamperPin_PC13 = 0x0
RTC_TamperPin_PI8 = 0x10000
RTC_TimeStampPin_PC13 = 0x0
RTC_TimeStampPin_PI8 = 0x20000
RTC_OutputType_OpenDrain = 0x0
RTC_OutputType_PushPull = 0x40000
RTC_ShiftAdd1S_Reset = 0x0
RTC_ShiftAdd1S_Set = 0x80000000
RTC_BKP_DR0 = 0x0
RTC_BKP_DR1 = 0x1
RTC_BKP_DR2 = 0x2
RTC_BKP_DR3 = 0x3
RTC_BKP_DR4 = 0x4
RTC_BKP_DR5 = 0x5
RTC_BKP_DR6 = 0x6
RTC_BKP_DR7 = 0x7
RTC_BKP_DR8 = 0x8
RTC_BKP_DR9 = 0x9
RTC_BKP_DR10 = 0xA
RTC_BKP_DR11 = 0xB
RTC_BKP_DR12 = 0xC
RTC_BKP_DR13 = 0xD
RTC_BKP_DR14 = 0xE
RTC_BKP_DR15 = 0xF
RTC_BKP_DR16 = 0x10
RTC_BKP_DR17 = 0x11
RTC_BKP_DR18 = 0x12
RTC_BKP_DR19 = 0x13
RTC_Format_BIN = 0x0
RTC_Format_BCD = 0x1
RTC_FLAG_RECALPF = 0x10000
RTC_FLAG_TAMP1F = 0x2000
RTC_FLAG_TSOVF = 0x1000
RTC_FLAG_TSF = 0x800
RTC_FLAG_WUTF = 0x400
RTC_FLAG_ALRBF = 0x200
RTC_FLAG_ALRAF = 0x100
RTC_FLAG_INITF = 0x40
RTC_FLAG_RSF = 0x20
RTC_FLAG_INITS = 0x10
RTC_FLAG_SHPF = 0x8
RTC_FLAG_WUTWF = 0x4
RTC_FLAG_ALRBWF = 0x2
RTC_FLAG_ALRAWF = 0x1
RTC_IT_TS = 0x8000
RTC_IT_WUT = 0x4000
RTC_IT_ALRB = 0x2000
RTC_IT_ALRA = 0x1000
RTC_IT_TAMP = 0x4
RTC_IT_TAMP1 = 0x20000
# Skip RTC_DigitalCalibConfig : no need parse
# Skip RTC_DigitalCalibCmd : no need parse
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
# struct RTC_AlarmTypeDef : field is class
# ----------------------------------------

# file stm32f4xx_sdio.h : 

# empty define __STM32F4xx_SDIO_H
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
SDIO_ReadWaitMode_CLK = 0x0
SDIO_ReadWaitMode_DATA2 = 0x1
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

# file stm32f4xx_rng.h : 

# empty define __STM32F4xx_RNG_H
RNG_FLAG_DRDY = 0x1
RNG_FLAG_CECS = 0x2
RNG_FLAG_SECS = 0x4
RNG_IT_CEI = 0x20
RNG_IT_SEI = 0x40
# ----------------------------------------

# file stm32f4xx_can.h : 

# empty define __STM32F4xx_CAN_H
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
# struct CanTxMsg : field is array
# struct CanRxMsg
# struct CanRxMsg : field is array
# ----------------------------------------

# file stm32f4xx.h : 

# Enum IRQn_Type
NonMaskableInt_IRQn = 0xFFFFFFF2
MemoryManagement_IRQn = 0xFFFFFFF4
BusFault_IRQn = 0xFFFFFFF5
UsageFault_IRQn = 0xFFFFFFF6
SVCall_IRQn = 0xFFFFFFFB
DebugMonitor_IRQn = 0xFFFFFFFC
PendSV_IRQn = 0xFFFFFFFE
SysTick_IRQn = 0xFFFFFFFF
WWDG_IRQn = 0x0
PVD_IRQn = 0x1
TAMP_STAMP_IRQn = 0x2
RTC_WKUP_IRQn = 0x3
FLASH_IRQn = 0x4
RCC_IRQn = 0x5
EXTI0_IRQn = 0x6
EXTI1_IRQn = 0x7
EXTI2_IRQn = 0x8
EXTI3_IRQn = 0x9
EXTI4_IRQn = 0xA
DMA1_Stream0_IRQn = 0xB
DMA1_Stream1_IRQn = 0xC
DMA1_Stream2_IRQn = 0xD
DMA1_Stream3_IRQn = 0xE
DMA1_Stream4_IRQn = 0xF
DMA1_Stream5_IRQn = 0x10
DMA1_Stream6_IRQn = 0x11
ADC_IRQn = 0x12
CAN1_TX_IRQn = 0x13
CAN1_RX0_IRQn = 0x14
CAN1_RX1_IRQn = 0x15
CAN1_SCE_IRQn = 0x16
EXTI9_5_IRQn = 0x17
TIM1_BRK_TIM9_IRQn = 0x18
TIM1_UP_TIM10_IRQn = 0x19
TIM1_TRG_COM_TIM11_IRQn = 0x1A
TIM1_CC_IRQn = 0x1B
TIM2_IRQn = 0x1C
TIM3_IRQn = 0x1D
TIM4_IRQn = 0x1E
I2C1_EV_IRQn = 0x1F
I2C1_ER_IRQn = 0x20
I2C2_EV_IRQn = 0x21
I2C2_ER_IRQn = 0x22
SPI1_IRQn = 0x23
SPI2_IRQn = 0x24
USART1_IRQn = 0x25
USART2_IRQn = 0x26
USART3_IRQn = 0x27
EXTI15_10_IRQn = 0x28
RTC_Alarm_IRQn = 0x29
OTG_FS_WKUP_IRQn = 0x2A
TIM8_BRK_TIM12_IRQn = 0x2B
TIM8_UP_TIM13_IRQn = 0x2C
TIM8_TRG_COM_TIM14_IRQn = 0x2D
TIM8_CC_IRQn = 0x2E
DMA1_Stream7_IRQn = 0x2F
FSMC_IRQn = 0x30
SDIO_IRQn = 0x31
TIM5_IRQn = 0x32
SPI3_IRQn = 0x33
UART4_IRQn = 0x34
UART5_IRQn = 0x35
TIM6_DAC_IRQn = 0x36
TIM7_IRQn = 0x37
DMA2_Stream0_IRQn = 0x38
DMA2_Stream1_IRQn = 0x39
DMA2_Stream2_IRQn = 0x3A
DMA2_Stream3_IRQn = 0x3B
DMA2_Stream4_IRQn = 0x3C
ETH_IRQn = 0x3D
ETH_WKUP_IRQn = 0x3E
CAN2_TX_IRQn = 0x3F
CAN2_RX0_IRQn = 0x40
CAN2_RX1_IRQn = 0x41
CAN2_SCE_IRQn = 0x42
OTG_FS_IRQn = 0x43
DMA2_Stream5_IRQn = 0x44
DMA2_Stream6_IRQn = 0x45
DMA2_Stream7_IRQn = 0x46
USART6_IRQn = 0x47
I2C3_EV_IRQn = 0x48
I2C3_ER_IRQn = 0x49
OTG_HS_EP1_OUT_IRQn = 0x4A
OTG_HS_EP1_IN_IRQn = 0x4B
OTG_HS_WKUP_IRQn = 0x4C
OTG_HS_IRQn = 0x4D
DCMI_IRQn = 0x4E
CRYP_IRQn = 0x4F
HASH_RNG_IRQn = 0x50
FPU_IRQn = 0x51
# Enum FlagStatus , ITStatus
RESET = 0x0
SET = 0x1
# Enum FunctionalState
DISABLE = 0x0
ENABLE = 0x1
# Enum ErrorStatus
ERROR = 0x0
SUCCESS = 0x1
# empty define __STM32F4xx_H
# empty define STM32F4XX
HSE_VALUE = 0x7A1200
HSE_STARTUP_TIMEOUT = 0x500
HSI_VALUE = 0xF42400
__STM32F4XX_STDPERIPH_VERSION_MAIN = 0x1
__STM32F4XX_STDPERIPH_VERSION_SUB1 = 0x0
__STM32F4XX_STDPERIPH_VERSION_SUB2 = 0x0
__STM32F4XX_STDPERIPH_VERSION_RC = 0x0
__STM32F4XX_STDPERIPH_VERSION = 0x1000000
__CM4_REV = 0x1
__MPU_PRESENT = 0x1
__NVIC_PRIO_BITS = 0x4
__Vendor_SysTickConfig = 0x0
__FPU_PRESENT = 0x1
FLASH_BASE = 0x8000000
CCMDATARAM_BASE = 0x10000000
SRAM1_BASE = 0x20000000
SRAM2_BASE = 0x2001C000
PERIPH_BASE = 0x40000000
BKPSRAM_BASE = 0x40024000
FSMC_R_BASE = 0xA0000000
CCMDATARAM_BB_BASE = 0x12000000
SRAM1_BB_BASE = 0x22000000
SRAM2_BB_BASE = 0x2201C000
PERIPH_BB_BASE = 0x42000000
BKPSRAM_BB_BASE = 0x42024000
SRAM_BASE = 0x20000000
SRAM_BB_BASE = 0x22000000
APB1PERIPH_BASE = 0x40000000
APB2PERIPH_BASE = 0x40010000
AHB1PERIPH_BASE = 0x40020000
AHB2PERIPH_BASE = 0x50000000
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
I2S2ext_BASE = 0x40003400
SPI2_BASE = 0x40003800
SPI3_BASE = 0x40003C00
I2S3ext_BASE = 0x40004000
USART2_BASE = 0x40004400
USART3_BASE = 0x40004800
UART4_BASE = 0x40004C00
UART5_BASE = 0x40005000
I2C1_BASE = 0x40005400
I2C2_BASE = 0x40005800
I2C3_BASE = 0x40005C00
CAN1_BASE = 0x40006400
CAN2_BASE = 0x40006800
PWR_BASE = 0x40007000
DAC_BASE = 0x40007400
TIM1_BASE = 0x40010000
TIM8_BASE = 0x40010400
USART1_BASE = 0x40011000
USART6_BASE = 0x40011400
ADC1_BASE = 0x40012000
ADC2_BASE = 0x40012100
ADC3_BASE = 0x40012200
ADC_BASE = 0x40012300
SDIO_BASE = 0x40012C00
SPI1_BASE = 0x40013000
SYSCFG_BASE = 0x40013800
EXTI_BASE = 0x40013C00
TIM9_BASE = 0x40014000
TIM10_BASE = 0x40014400
TIM11_BASE = 0x40014800
GPIOA_BASE = 0x40020000
GPIOB_BASE = 0x40020400
GPIOC_BASE = 0x40020800
GPIOD_BASE = 0x40020C00
GPIOE_BASE = 0x40021000
GPIOF_BASE = 0x40021400
GPIOG_BASE = 0x40021800
GPIOH_BASE = 0x40021C00
GPIOI_BASE = 0x40022000
CRC_BASE = 0x40023000
RCC_BASE = 0x40023800
FLASH_R_BASE = 0x40023C00
DMA1_BASE = 0x40026000
DMA1_Stream0_BASE = 0x40026010
DMA1_Stream1_BASE = 0x40026028
DMA1_Stream2_BASE = 0x40026040
DMA1_Stream3_BASE = 0x40026058
DMA1_Stream4_BASE = 0x40026070
DMA1_Stream5_BASE = 0x40026088
DMA1_Stream6_BASE = 0x400260A0
DMA1_Stream7_BASE = 0x400260B8
DMA2_BASE = 0x40026400
DMA2_Stream0_BASE = 0x40026410
DMA2_Stream1_BASE = 0x40026428
DMA2_Stream2_BASE = 0x40026440
DMA2_Stream3_BASE = 0x40026458
DMA2_Stream4_BASE = 0x40026470
DMA2_Stream5_BASE = 0x40026488
DMA2_Stream6_BASE = 0x400264A0
DMA2_Stream7_BASE = 0x400264B8
ETH_BASE = 0x40028000
ETH_MAC_BASE = 0x40028000
ETH_MMC_BASE = 0x40028100
ETH_PTP_BASE = 0x40028700
ETH_DMA_BASE = 0x40029000
DCMI_BASE = 0x50050000
CRYP_BASE = 0x50060000
HASH_BASE = 0x50060400
RNG_BASE = 0x50060800
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
I2S2ext = 0x40003400
SPI2 = 0x40003800
SPI3 = 0x40003C00
I2S3ext = 0x40004000
USART2 = 0x40004400
USART3 = 0x40004800
UART4 = 0x40004C00
UART5 = 0x40005000
I2C1 = 0x40005400
I2C2 = 0x40005800
I2C3 = 0x40005C00
CAN1 = 0x40006400
CAN2 = 0x40006800
PWR = 0x40007000
DAC = 0x40007400
TIM1 = 0x40010000
TIM8 = 0x40010400
USART1 = 0x40011000
USART6 = 0x40011400
ADC = 0x40012300
ADC1 = 0x40012000
ADC2 = 0x40012100
ADC3 = 0x40012200
SDIO = 0x40012C00
SPI1 = 0x40013000
SYSCFG = 0x40013800
EXTI = 0x40013C00
TIM9 = 0x40014000
TIM10 = 0x40014400
TIM11 = 0x40014800
GPIOA = 0x40020000
GPIOB = 0x40020400
GPIOC = 0x40020800
GPIOD = 0x40020C00
GPIOE = 0x40021000
GPIOF = 0x40021400
GPIOG = 0x40021800
GPIOH = 0x40021C00
GPIOI = 0x40022000
CRC = 0x40023000
RCC = 0x40023800
FLASH = 0x40023C00
DMA1 = 0x40026000
DMA1_Stream0 = 0x40026010
DMA1_Stream1 = 0x40026028
DMA1_Stream2 = 0x40026040
DMA1_Stream3 = 0x40026058
DMA1_Stream4 = 0x40026070
DMA1_Stream5 = 0x40026088
DMA1_Stream6 = 0x400260A0
DMA1_Stream7 = 0x400260B8
DMA2 = 0x40026400
DMA2_Stream0 = 0x40026410
DMA2_Stream1 = 0x40026428
DMA2_Stream2 = 0x40026440
DMA2_Stream3 = 0x40026458
DMA2_Stream4 = 0x40026470
DMA2_Stream5 = 0x40026488
DMA2_Stream6 = 0x400264A0
DMA2_Stream7 = 0x400264B8
ETH = 0x40028000
DCMI = 0x50050000
CRYP = 0x50060000
HASH = 0x50060400
RNG = 0x50060800
FSMC_Bank1 = 0xA0000000
FSMC_Bank1E = 0xA0000104
FSMC_Bank2 = 0xA0000060
FSMC_Bank3 = 0xA0000080
FSMC_Bank4 = 0xA00000A0
DBGMCU = 0xE0042000
ADC_SR_AWD = 0x1
ADC_SR_EOC = 0x2
ADC_SR_JEOC = 0x4
ADC_SR_JSTRT = 0x8
ADC_SR_STRT = 0x10
ADC_SR_OVR = 0x20
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
ADC_CR1_JAWDEN = 0x400000
ADC_CR1_AWDEN = 0x800000
ADC_CR1_RES = 0x3000000
ADC_CR1_RES_0 = 0x1000000
ADC_CR1_RES_1 = 0x2000000
ADC_CR1_OVRIE = 0x4000000
ADC_CR2_ADON = 0x1
ADC_CR2_CONT = 0x2
ADC_CR2_DMA = 0x100
ADC_CR2_DDS = 0x200
ADC_CR2_EOCS = 0x400
ADC_CR2_ALIGN = 0x800
ADC_CR2_JEXTSEL = 0xF0000
ADC_CR2_JEXTSEL_0 = 0x10000
ADC_CR2_JEXTSEL_1 = 0x20000
ADC_CR2_JEXTSEL_2 = 0x40000
ADC_CR2_JEXTSEL_3 = 0x80000
ADC_CR2_JEXTEN = 0x300000
ADC_CR2_JEXTEN_0 = 0x100000
ADC_CR2_JEXTEN_1 = 0x200000
ADC_CR2_JSWSTART = 0x400000
ADC_CR2_EXTSEL = 0xF000000
ADC_CR2_EXTSEL_0 = 0x1000000
ADC_CR2_EXTSEL_1 = 0x2000000
ADC_CR2_EXTSEL_2 = 0x4000000
ADC_CR2_EXTSEL_3 = 0x8000000
ADC_CR2_EXTEN = 0x30000000
ADC_CR2_EXTEN_0 = 0x10000000
ADC_CR2_EXTEN_1 = 0x20000000
ADC_CR2_SWSTART = 0x40000000
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
ADC_SMPR1_SMP18 = 0x7000000
ADC_SMPR1_SMP18_0 = 0x1000000
ADC_SMPR1_SMP18_1 = 0x2000000
ADC_SMPR1_SMP18_2 = 0x4000000
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
ADC_CSR_AWD1 = 0x1
ADC_CSR_EOC1 = 0x2
ADC_CSR_JEOC1 = 0x4
ADC_CSR_JSTRT1 = 0x8
ADC_CSR_STRT1 = 0x10
ADC_CSR_DOVR1 = 0x20
ADC_CSR_AWD2 = 0x100
ADC_CSR_EOC2 = 0x200
ADC_CSR_JEOC2 = 0x400
ADC_CSR_JSTRT2 = 0x800
ADC_CSR_STRT2 = 0x1000
ADC_CSR_DOVR2 = 0x2000
ADC_CSR_AWD3 = 0x10000
ADC_CSR_EOC3 = 0x20000
ADC_CSR_JEOC3 = 0x40000
ADC_CSR_JSTRT3 = 0x80000
ADC_CSR_STRT3 = 0x100000
ADC_CSR_DOVR3 = 0x200000
ADC_CCR_MULTI = 0x1F
ADC_CCR_MULTI_0 = 0x1
ADC_CCR_MULTI_1 = 0x2
ADC_CCR_MULTI_2 = 0x4
ADC_CCR_MULTI_3 = 0x8
ADC_CCR_MULTI_4 = 0x10
ADC_CCR_DELAY = 0xF00
ADC_CCR_DELAY_0 = 0x100
ADC_CCR_DELAY_1 = 0x200
ADC_CCR_DELAY_2 = 0x400
ADC_CCR_DELAY_3 = 0x800
ADC_CCR_DDS = 0x2000
ADC_CCR_DMA = 0xC000
ADC_CCR_DMA_0 = 0x4000
ADC_CCR_DMA_1 = 0x8000
ADC_CCR_ADCPRE = 0x30000
ADC_CCR_ADCPRE_0 = 0x10000
ADC_CCR_ADCPRE_1 = 0x20000
ADC_CCR_VBATE = 0x400000
ADC_CCR_TSVREFE = 0x800000
ADC_CDR_DATA1 = 0xFFFF
ADC_CDR_DATA2 = 0xFFFF0000
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
CRC_DR_DR = 0xFFFFFFFF
CRC_IDR_IDR = 0xFF
CRC_CR_RESET = 0x1
CRYP_CR_ALGODIR = 0x4
CRYP_CR_ALGOMODE = 0x38
CRYP_CR_ALGOMODE_0 = 0x8
CRYP_CR_ALGOMODE_1 = 0x10
CRYP_CR_ALGOMODE_2 = 0x20
CRYP_CR_ALGOMODE_TDES_ECB = 0x0
CRYP_CR_ALGOMODE_TDES_CBC = 0x8
CRYP_CR_ALGOMODE_DES_ECB = 0x10
CRYP_CR_ALGOMODE_DES_CBC = 0x18
CRYP_CR_ALGOMODE_AES_ECB = 0x20
CRYP_CR_ALGOMODE_AES_CBC = 0x28
CRYP_CR_ALGOMODE_AES_CTR = 0x30
CRYP_CR_ALGOMODE_AES_KEY = 0x38
CRYP_CR_DATATYPE = 0xC0
CRYP_CR_DATATYPE_0 = 0x40
CRYP_CR_DATATYPE_1 = 0x80
CRYP_CR_KEYSIZE = 0x300
CRYP_CR_KEYSIZE_0 = 0x100
CRYP_CR_KEYSIZE_1 = 0x200
CRYP_CR_FFLUSH = 0x4000
CRYP_CR_CRYPEN = 0x8000
CRYP_SR_IFEM = 0x1
CRYP_SR_IFNF = 0x2
CRYP_SR_OFNE = 0x4
CRYP_SR_OFFU = 0x8
CRYP_SR_BUSY = 0x10
CRYP_DMACR_DIEN = 0x1
CRYP_DMACR_DOEN = 0x2
CRYP_IMSCR_INIM = 0x1
CRYP_IMSCR_OUTIM = 0x2
CRYP_RISR_OUTRIS = 0x1
CRYP_RISR_INRIS = 0x2
CRYP_MISR_INMIS = 0x1
CRYP_MISR_OUTMIS = 0x2
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
DCMI_CR_CAPTURE = 0x1
DCMI_CR_CM = 0x2
DCMI_CR_CROP = 0x4
DCMI_CR_JPEG = 0x8
DCMI_CR_ESS = 0x10
DCMI_CR_PCKPOL = 0x20
DCMI_CR_HSPOL = 0x40
DCMI_CR_VSPOL = 0x80
DCMI_CR_FCRC_0 = 0x100
DCMI_CR_FCRC_1 = 0x200
DCMI_CR_EDM_0 = 0x400
DCMI_CR_EDM_1 = 0x800
DCMI_CR_CRE = 0x1000
DCMI_CR_ENABLE = 0x4000
DCMI_SR_HSYNC = 0x1
DCMI_SR_VSYNC = 0x2
DCMI_SR_FNE = 0x4
DCMI_RISR_FRAME_RIS = 0x1
DCMI_RISR_OVF_RIS = 0x2
DCMI_RISR_ERR_RIS = 0x4
DCMI_RISR_VSYNC_RIS = 0x8
DCMI_RISR_LINE_RIS = 0x10
DCMI_IER_FRAME_IE = 0x1
DCMI_IER_OVF_IE = 0x2
DCMI_IER_ERR_IE = 0x4
DCMI_IER_VSYNC_IE = 0x8
DCMI_IER_LINE_IE = 0x10
DCMI_MISR_FRAME_MIS = 0x1
DCMI_MISR_OVF_MIS = 0x2
DCMI_MISR_ERR_MIS = 0x4
DCMI_MISR_VSYNC_MIS = 0x8
DCMI_MISR_LINE_MIS = 0x10
DCMI_ICR_FRAME_ISC = 0x1
DCMI_ICR_OVF_ISC = 0x2
DCMI_ICR_ERR_ISC = 0x4
DCMI_ICR_VSYNC_ISC = 0x8
DCMI_ICR_LINE_ISC = 0x10
DMA_SxCR_CHSEL = 0xE000000
DMA_SxCR_CHSEL_0 = 0x2000000
DMA_SxCR_CHSEL_1 = 0x4000000
DMA_SxCR_CHSEL_2 = 0x8000000
DMA_SxCR_MBURST = 0x1800000
DMA_SxCR_MBURST_0 = 0x800000
DMA_SxCR_MBURST_1 = 0x1000000
DMA_SxCR_PBURST = 0x600000
DMA_SxCR_PBURST_0 = 0x200000
DMA_SxCR_PBURST_1 = 0x400000
DMA_SxCR_ACK = 0x100000
DMA_SxCR_CT = 0x80000
DMA_SxCR_DBM = 0x40000
DMA_SxCR_PL = 0x30000
DMA_SxCR_PL_0 = 0x10000
DMA_SxCR_PL_1 = 0x20000
DMA_SxCR_PINCOS = 0x8000
DMA_SxCR_MSIZE = 0x6000
DMA_SxCR_MSIZE_0 = 0x2000
DMA_SxCR_MSIZE_1 = 0x4000
DMA_SxCR_PSIZE = 0x1800
DMA_SxCR_PSIZE_0 = 0x800
DMA_SxCR_PSIZE_1 = 0x1000
DMA_SxCR_MINC = 0x400
DMA_SxCR_PINC = 0x200
DMA_SxCR_CIRC = 0x100
DMA_SxCR_DIR = 0xC0
DMA_SxCR_DIR_0 = 0x40
DMA_SxCR_DIR_1 = 0x80
DMA_SxCR_PFCTRL = 0x20
DMA_SxCR_TCIE = 0x10
DMA_SxCR_HTIE = 0x8
DMA_SxCR_TEIE = 0x4
DMA_SxCR_DMEIE = 0x2
DMA_SxCR_EN = 0x1
DMA_SxNDT = 0xFFFF
DMA_SxNDT_0 = 0x1
DMA_SxNDT_1 = 0x2
DMA_SxNDT_2 = 0x4
DMA_SxNDT_3 = 0x8
DMA_SxNDT_4 = 0x10
DMA_SxNDT_5 = 0x20
DMA_SxNDT_6 = 0x40
DMA_SxNDT_7 = 0x80
DMA_SxNDT_8 = 0x100
DMA_SxNDT_9 = 0x200
DMA_SxNDT_10 = 0x400
DMA_SxNDT_11 = 0x800
DMA_SxNDT_12 = 0x1000
DMA_SxNDT_13 = 0x2000
DMA_SxNDT_14 = 0x4000
DMA_SxNDT_15 = 0x8000
DMA_SxFCR_FEIE = 0x80
DMA_SxFCR_FS = 0x38
DMA_SxFCR_FS_0 = 0x8
DMA_SxFCR_FS_1 = 0x10
DMA_SxFCR_FS_2 = 0x20
DMA_SxFCR_DMDIS = 0x4
DMA_SxFCR_FTH = 0x3
DMA_SxFCR_FTH_0 = 0x1
DMA_SxFCR_FTH_1 = 0x2
DMA_LISR_TCIF3 = 0x8000000
DMA_LISR_HTIF3 = 0x4000000
DMA_LISR_TEIF3 = 0x2000000
DMA_LISR_DMEIF3 = 0x1000000
DMA_LISR_FEIF3 = 0x400000
DMA_LISR_TCIF2 = 0x200000
DMA_LISR_HTIF2 = 0x100000
DMA_LISR_TEIF2 = 0x80000
DMA_LISR_DMEIF2 = 0x40000
DMA_LISR_FEIF2 = 0x10000
DMA_LISR_TCIF1 = 0x800
DMA_LISR_HTIF1 = 0x400
DMA_LISR_TEIF1 = 0x200
DMA_LISR_DMEIF1 = 0x100
DMA_LISR_FEIF1 = 0x40
DMA_LISR_TCIF0 = 0x20
DMA_LISR_HTIF0 = 0x10
DMA_LISR_TEIF0 = 0x8
DMA_LISR_DMEIF0 = 0x4
DMA_LISR_FEIF0 = 0x1
DMA_HISR_TCIF7 = 0x8000000
DMA_HISR_HTIF7 = 0x4000000
DMA_HISR_TEIF7 = 0x2000000
DMA_HISR_DMEIF7 = 0x1000000
DMA_HISR_FEIF7 = 0x400000
DMA_HISR_TCIF6 = 0x200000
DMA_HISR_HTIF6 = 0x100000
DMA_HISR_TEIF6 = 0x80000
DMA_HISR_DMEIF6 = 0x40000
DMA_HISR_FEIF6 = 0x10000
DMA_HISR_TCIF5 = 0x800
DMA_HISR_HTIF5 = 0x400
DMA_HISR_TEIF5 = 0x200
DMA_HISR_DMEIF5 = 0x100
DMA_HISR_FEIF5 = 0x40
DMA_HISR_TCIF4 = 0x20
DMA_HISR_HTIF4 = 0x10
DMA_HISR_TEIF4 = 0x8
DMA_HISR_DMEIF4 = 0x4
DMA_HISR_FEIF4 = 0x1
DMA_LIFCR_CTCIF3 = 0x8000000
DMA_LIFCR_CHTIF3 = 0x4000000
DMA_LIFCR_CTEIF3 = 0x2000000
DMA_LIFCR_CDMEIF3 = 0x1000000
DMA_LIFCR_CFEIF3 = 0x400000
DMA_LIFCR_CTCIF2 = 0x200000
DMA_LIFCR_CHTIF2 = 0x100000
DMA_LIFCR_CTEIF2 = 0x80000
DMA_LIFCR_CDMEIF2 = 0x40000
DMA_LIFCR_CFEIF2 = 0x10000
DMA_LIFCR_CTCIF1 = 0x800
DMA_LIFCR_CHTIF1 = 0x400
DMA_LIFCR_CTEIF1 = 0x200
DMA_LIFCR_CDMEIF1 = 0x100
DMA_LIFCR_CFEIF1 = 0x40
DMA_LIFCR_CTCIF0 = 0x20
DMA_LIFCR_CHTIF0 = 0x10
DMA_LIFCR_CTEIF0 = 0x8
DMA_LIFCR_CDMEIF0 = 0x4
DMA_LIFCR_CFEIF0 = 0x1
DMA_HIFCR_CTCIF7 = 0x8000000
DMA_HIFCR_CHTIF7 = 0x4000000
DMA_HIFCR_CTEIF7 = 0x2000000
DMA_HIFCR_CDMEIF7 = 0x1000000
DMA_HIFCR_CFEIF7 = 0x400000
DMA_HIFCR_CTCIF6 = 0x200000
DMA_HIFCR_CHTIF6 = 0x100000
DMA_HIFCR_CTEIF6 = 0x80000
DMA_HIFCR_CDMEIF6 = 0x40000
DMA_HIFCR_CFEIF6 = 0x10000
DMA_HIFCR_CTCIF5 = 0x800
DMA_HIFCR_CHTIF5 = 0x400
DMA_HIFCR_CTEIF5 = 0x200
DMA_HIFCR_CDMEIF5 = 0x100
DMA_HIFCR_CFEIF5 = 0x40
DMA_HIFCR_CTCIF4 = 0x20
DMA_HIFCR_CHTIF4 = 0x10
DMA_HIFCR_CTEIF4 = 0x8
DMA_HIFCR_CDMEIF4 = 0x4
DMA_HIFCR_CFEIF4 = 0x1
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
FLASH_ACR_LATENCY = 0x7
FLASH_ACR_LATENCY_0WS = 0x0
FLASH_ACR_LATENCY_1WS = 0x1
FLASH_ACR_LATENCY_2WS = 0x2
FLASH_ACR_LATENCY_3WS = 0x3
FLASH_ACR_LATENCY_4WS = 0x4
FLASH_ACR_LATENCY_5WS = 0x5
FLASH_ACR_LATENCY_6WS = 0x6
FLASH_ACR_LATENCY_7WS = 0x7
FLASH_ACR_PRFTEN = 0x100
FLASH_ACR_ICEN = 0x200
FLASH_ACR_DCEN = 0x400
FLASH_ACR_ICRST = 0x800
FLASH_ACR_DCRST = 0x1000
FLASH_ACR_BYTE0_ADDRESS = 0x40023C00
FLASH_ACR_BYTE2_ADDRESS = 0x40023C03
FLASH_SR_EOP = 0x1
FLASH_SR_SOP = 0x2
FLASH_SR_WRPERR = 0x10
FLASH_SR_PGAERR = 0x20
FLASH_SR_PGPERR = 0x40
FLASH_SR_PGSERR = 0x80
FLASH_SR_BSY = 0x10000
FLASH_CR_PG = 0x1
FLASH_CR_SER = 0x2
FLASH_CR_MER = 0x4
FLASH_CR_SNB_0 = 0x8
FLASH_CR_SNB_1 = 0x10
FLASH_CR_SNB_2 = 0x20
FLASH_CR_SNB_3 = 0x40
FLASH_CR_PSIZE_0 = 0x100
FLASH_CR_PSIZE_1 = 0x200
FLASH_CR_STRT = 0x10000
FLASH_CR_EOPIE = 0x1000000
FLASH_CR_LOCK = 0x80000000
FLASH_OPTCR_OPTLOCK = 0x1
FLASH_OPTCR_OPTSTRT = 0x2
FLASH_OPTCR_BOR_LEV_0 = 0x4
FLASH_OPTCR_BOR_LEV_1 = 0x8
FLASH_OPTCR_BOR_LEV = 0xC
FLASH_OPTCR_WDG_SW = 0x20
FLASH_OPTCR_nRST_STOP = 0x40
FLASH_OPTCR_nRST_STDBY = 0x80
FLASH_OPTCR_RDP_0 = 0x100
FLASH_OPTCR_RDP_1 = 0x200
FLASH_OPTCR_RDP_2 = 0x400
FLASH_OPTCR_RDP_3 = 0x800
FLASH_OPTCR_RDP_4 = 0x1000
FLASH_OPTCR_RDP_5 = 0x2000
FLASH_OPTCR_RDP_6 = 0x4000
FLASH_OPTCR_RDP_7 = 0x8000
FLASH_OPTCR_nWRP_0 = 0x10000
FLASH_OPTCR_nWRP_1 = 0x20000
FLASH_OPTCR_nWRP_2 = 0x40000
FLASH_OPTCR_nWRP_3 = 0x80000
FLASH_OPTCR_nWRP_4 = 0x100000
FLASH_OPTCR_nWRP_5 = 0x200000
FLASH_OPTCR_nWRP_6 = 0x400000
FLASH_OPTCR_nWRP_7 = 0x800000
FLASH_OPTCR_nWRP_8 = 0x1000000
FLASH_OPTCR_nWRP_9 = 0x2000000
FLASH_OPTCR_nWRP_10 = 0x4000000
FLASH_OPTCR_nWRP_11 = 0x8000000
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
GPIO_IDR_IDR_0 = 0x1
GPIO_IDR_IDR_1 = 0x2
GPIO_IDR_IDR_2 = 0x4
GPIO_IDR_IDR_3 = 0x8
GPIO_IDR_IDR_4 = 0x10
GPIO_IDR_IDR_5 = 0x20
GPIO_IDR_IDR_6 = 0x40
GPIO_IDR_IDR_7 = 0x80
GPIO_IDR_IDR_8 = 0x100
GPIO_IDR_IDR_9 = 0x200
GPIO_IDR_IDR_10 = 0x400
GPIO_IDR_IDR_11 = 0x800
GPIO_IDR_IDR_12 = 0x1000
GPIO_IDR_IDR_13 = 0x2000
GPIO_IDR_IDR_14 = 0x4000
GPIO_IDR_IDR_15 = 0x8000
GPIO_OTYPER_IDR_0 = 0x1
GPIO_OTYPER_IDR_1 = 0x2
GPIO_OTYPER_IDR_2 = 0x4
GPIO_OTYPER_IDR_3 = 0x8
GPIO_OTYPER_IDR_4 = 0x10
GPIO_OTYPER_IDR_5 = 0x20
GPIO_OTYPER_IDR_6 = 0x40
GPIO_OTYPER_IDR_7 = 0x80
GPIO_OTYPER_IDR_8 = 0x100
GPIO_OTYPER_IDR_9 = 0x200
GPIO_OTYPER_IDR_10 = 0x400
GPIO_OTYPER_IDR_11 = 0x800
GPIO_OTYPER_IDR_12 = 0x1000
GPIO_OTYPER_IDR_13 = 0x2000
GPIO_OTYPER_IDR_14 = 0x4000
GPIO_OTYPER_IDR_15 = 0x8000
GPIO_ODR_ODR_0 = 0x1
GPIO_ODR_ODR_1 = 0x2
GPIO_ODR_ODR_2 = 0x4
GPIO_ODR_ODR_3 = 0x8
GPIO_ODR_ODR_4 = 0x10
GPIO_ODR_ODR_5 = 0x20
GPIO_ODR_ODR_6 = 0x40
GPIO_ODR_ODR_7 = 0x80
GPIO_ODR_ODR_8 = 0x100
GPIO_ODR_ODR_9 = 0x200
GPIO_ODR_ODR_10 = 0x400
GPIO_ODR_ODR_11 = 0x800
GPIO_ODR_ODR_12 = 0x1000
GPIO_ODR_ODR_13 = 0x2000
GPIO_ODR_ODR_14 = 0x4000
GPIO_ODR_ODR_15 = 0x8000
GPIO_OTYPER_ODR_0 = 0x1
GPIO_OTYPER_ODR_1 = 0x2
GPIO_OTYPER_ODR_2 = 0x4
GPIO_OTYPER_ODR_3 = 0x8
GPIO_OTYPER_ODR_4 = 0x10
GPIO_OTYPER_ODR_5 = 0x20
GPIO_OTYPER_ODR_6 = 0x40
GPIO_OTYPER_ODR_7 = 0x80
GPIO_OTYPER_ODR_8 = 0x100
GPIO_OTYPER_ODR_9 = 0x200
GPIO_OTYPER_ODR_10 = 0x400
GPIO_OTYPER_ODR_11 = 0x800
GPIO_OTYPER_ODR_12 = 0x1000
GPIO_OTYPER_ODR_13 = 0x2000
GPIO_OTYPER_ODR_14 = 0x4000
GPIO_OTYPER_ODR_15 = 0x8000
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
HASH_CR_INIT = 0x4
HASH_CR_DMAE = 0x8
HASH_CR_DATATYPE = 0x30
HASH_CR_DATATYPE_0 = 0x10
HASH_CR_DATATYPE_1 = 0x20
HASH_CR_MODE = 0x40
HASH_CR_ALGO = 0x80
HASH_CR_NBW = 0xF00
HASH_CR_NBW_0 = 0x100
HASH_CR_NBW_1 = 0x200
HASH_CR_NBW_2 = 0x400
HASH_CR_NBW_3 = 0x800
HASH_CR_DINNE = 0x1000
HASH_CR_LKEY = 0x10000
HASH_STR_NBW = 0x1F
HASH_STR_NBW_0 = 0x1
HASH_STR_NBW_1 = 0x2
HASH_STR_NBW_2 = 0x4
HASH_STR_NBW_3 = 0x8
HASH_STR_NBW_4 = 0x10
HASH_STR_DCAL = 0x100
HASH_IMR_DINIM = 0x1
HASH_IMR_DCIM = 0x2
HASH_SR_DINIS = 0x1
HASH_SR_DCIS = 0x2
HASH_SR_DMAS = 0x4
HASH_SR_BUSY = 0x8
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
IWDG_KR_KEY = 0xFFFF
IWDG_PR_PR = 0x7
IWDG_PR_PR_0 = 0x1
IWDG_PR_PR_1 = 0x2
IWDG_PR_PR_2 = 0x4
IWDG_RLR_RL = 0xFFF
IWDG_SR_PVU = 0x1
IWDG_SR_RVU = 0x2
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
PWR_CR_FPDS = 0x200
PWR_CR_VOS = 0x4000
PWR_CR_PMODE = 0x4000
PWR_CSR_WUF = 0x1
PWR_CSR_SBF = 0x2
PWR_CSR_PVDO = 0x4
PWR_CSR_BRR = 0x8
PWR_CSR_EWUP = 0x100
PWR_CSR_BRE = 0x200
PWR_CSR_VOSRDY = 0x4000
PWR_CSR_REGRDY = 0x4000
RCC_CR_HSION = 0x1
RCC_CR_HSIRDY = 0x2
RCC_CR_HSITRIM = 0xF8
RCC_CR_HSITRIM_0 = 0x8
RCC_CR_HSITRIM_1 = 0x10
RCC_CR_HSITRIM_2 = 0x20
RCC_CR_HSITRIM_3 = 0x40
RCC_CR_HSITRIM_4 = 0x80
RCC_CR_HSICAL = 0xFF00
RCC_CR_HSICAL_0 = 0x100
RCC_CR_HSICAL_1 = 0x200
RCC_CR_HSICAL_2 = 0x400
RCC_CR_HSICAL_3 = 0x800
RCC_CR_HSICAL_4 = 0x1000
RCC_CR_HSICAL_5 = 0x2000
RCC_CR_HSICAL_6 = 0x4000
RCC_CR_HSICAL_7 = 0x8000
RCC_CR_HSEON = 0x10000
RCC_CR_HSERDY = 0x20000
RCC_CR_HSEBYP = 0x40000
RCC_CR_CSSON = 0x80000
RCC_CR_PLLON = 0x1000000
RCC_CR_PLLRDY = 0x2000000
RCC_CR_PLLI2SON = 0x4000000
RCC_CR_PLLI2SRDY = 0x8000000
RCC_PLLCFGR_PLLM = 0x3F
RCC_PLLCFGR_PLLM_0 = 0x1
RCC_PLLCFGR_PLLM_1 = 0x2
RCC_PLLCFGR_PLLM_2 = 0x4
RCC_PLLCFGR_PLLM_3 = 0x8
RCC_PLLCFGR_PLLM_4 = 0x10
RCC_PLLCFGR_PLLM_5 = 0x20
RCC_PLLCFGR_PLLN = 0x7FC0
RCC_PLLCFGR_PLLN_0 = 0x40
RCC_PLLCFGR_PLLN_1 = 0x80
RCC_PLLCFGR_PLLN_2 = 0x100
RCC_PLLCFGR_PLLN_3 = 0x200
RCC_PLLCFGR_PLLN_4 = 0x400
RCC_PLLCFGR_PLLN_5 = 0x800
RCC_PLLCFGR_PLLN_6 = 0x1000
RCC_PLLCFGR_PLLN_7 = 0x2000
RCC_PLLCFGR_PLLN_8 = 0x4000
RCC_PLLCFGR_PLLP = 0x30000
RCC_PLLCFGR_PLLP_0 = 0x10000
RCC_PLLCFGR_PLLP_1 = 0x20000
RCC_PLLCFGR_PLLSRC = 0x400000
RCC_PLLCFGR_PLLSRC_HSE = 0x400000
RCC_PLLCFGR_PLLSRC_HSI = 0x0
RCC_PLLCFGR_PLLQ = 0xF000000
RCC_PLLCFGR_PLLQ_0 = 0x1000000
RCC_PLLCFGR_PLLQ_1 = 0x2000000
RCC_PLLCFGR_PLLQ_2 = 0x4000000
RCC_PLLCFGR_PLLQ_3 = 0x8000000
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
RCC_CFGR_PPRE1 = 0x1C00
RCC_CFGR_PPRE1_0 = 0x400
RCC_CFGR_PPRE1_1 = 0x800
RCC_CFGR_PPRE1_2 = 0x1000
RCC_CFGR_PPRE1_DIV1 = 0x0
RCC_CFGR_PPRE1_DIV2 = 0x1000
RCC_CFGR_PPRE1_DIV4 = 0x1400
RCC_CFGR_PPRE1_DIV8 = 0x1800
RCC_CFGR_PPRE1_DIV16 = 0x1C00
RCC_CFGR_PPRE2 = 0xE000
RCC_CFGR_PPRE2_0 = 0x2000
RCC_CFGR_PPRE2_1 = 0x4000
RCC_CFGR_PPRE2_2 = 0x8000
RCC_CFGR_PPRE2_DIV1 = 0x0
RCC_CFGR_PPRE2_DIV2 = 0x8000
RCC_CFGR_PPRE2_DIV4 = 0xA000
RCC_CFGR_PPRE2_DIV8 = 0xC000
RCC_CFGR_PPRE2_DIV16 = 0xE000
RCC_CFGR_RTCPRE = 0x1F0000
RCC_CFGR_RTCPRE_0 = 0x10000
RCC_CFGR_RTCPRE_1 = 0x20000
RCC_CFGR_RTCPRE_2 = 0x40000
RCC_CFGR_RTCPRE_3 = 0x80000
RCC_CFGR_RTCPRE_4 = 0x100000
RCC_CFGR_MCO1 = 0x600000
RCC_CFGR_MCO1_0 = 0x200000
RCC_CFGR_MCO1_1 = 0x400000
RCC_CFGR_I2SSRC = 0x800000
RCC_CFGR_MCO1PRE = 0x7000000
RCC_CFGR_MCO1PRE_0 = 0x1000000
RCC_CFGR_MCO1PRE_1 = 0x2000000
RCC_CFGR_MCO1PRE_2 = 0x4000000
RCC_CFGR_MCO2PRE = 0x38000000
RCC_CFGR_MCO2PRE_0 = 0x8000000
RCC_CFGR_MCO2PRE_1 = 0x10000000
RCC_CFGR_MCO2PRE_2 = 0x20000000
RCC_CFGR_MCO2 = 0xC0000000
RCC_CFGR_MCO2_0 = 0x40000000
RCC_CFGR_MCO2_1 = 0x80000000
RCC_CIR_LSIRDYF = 0x1
RCC_CIR_LSERDYF = 0x2
RCC_CIR_HSIRDYF = 0x4
RCC_CIR_HSERDYF = 0x8
RCC_CIR_PLLRDYF = 0x10
RCC_CIR_PLLI2SRDYF = 0x20
RCC_CIR_CSSF = 0x80
RCC_CIR_LSIRDYIE = 0x100
RCC_CIR_LSERDYIE = 0x200
RCC_CIR_HSIRDYIE = 0x400
RCC_CIR_HSERDYIE = 0x800
RCC_CIR_PLLRDYIE = 0x1000
RCC_CIR_PLLI2SRDYIE = 0x2000
RCC_CIR_LSIRDYC = 0x10000
RCC_CIR_LSERDYC = 0x20000
RCC_CIR_HSIRDYC = 0x40000
RCC_CIR_HSERDYC = 0x80000
RCC_CIR_PLLRDYC = 0x100000
RCC_CIR_PLLI2SRDYC = 0x200000
RCC_CIR_CSSC = 0x800000
RCC_AHB1RSTR_GPIOARST = 0x1
RCC_AHB1RSTR_GPIOBRST = 0x2
RCC_AHB1RSTR_GPIOCRST = 0x4
RCC_AHB1RSTR_GPIODRST = 0x8
RCC_AHB1RSTR_GPIOERST = 0x10
RCC_AHB1RSTR_GPIOFRST = 0x20
RCC_AHB1RSTR_GPIOGRST = 0x40
RCC_AHB1RSTR_GPIOHRST = 0x80
RCC_AHB1RSTR_GPIOIRST = 0x100
RCC_AHB1RSTR_CRCRST = 0x1000
RCC_AHB1RSTR_DMA1RST = 0x200000
RCC_AHB1RSTR_DMA2RST = 0x400000
RCC_AHB1RSTR_ETHMACRST = 0x2000000
RCC_AHB1RSTR_OTGHRST = 0x10000000
RCC_AHB2RSTR_DCMIRST = 0x1
RCC_AHB2RSTR_CRYPRST = 0x10
RCC_AHB2RSTR_HSAHRST = 0x20
RCC_AHB2RSTR_RNGRST = 0x40
RCC_AHB2RSTR_OTGFSRST = 0x80
RCC_AHB3RSTR_FSMCRST = 0x1
RCC_APB1RSTR_TIM2RST = 0x1
RCC_APB1RSTR_TIM3RST = 0x2
RCC_APB1RSTR_TIM4RST = 0x4
RCC_APB1RSTR_TIM5RST = 0x8
RCC_APB1RSTR_TIM6RST = 0x10
RCC_APB1RSTR_TIM7RST = 0x20
RCC_APB1RSTR_TIM12RST = 0x40
RCC_APB1RSTR_TIM13RST = 0x80
RCC_APB1RSTR_TIM14RST = 0x100
RCC_APB1RSTR_WWDGEN = 0x800
RCC_APB1RSTR_SPI2RST = 0x8000
RCC_APB1RSTR_SPI3RST = 0x10000
RCC_APB1RSTR_USART2RST = 0x20000
RCC_APB1RSTR_USART3RST = 0x40000
RCC_APB1RSTR_UART4RST = 0x80000
RCC_APB1RSTR_UART5RST = 0x100000
RCC_APB1RSTR_I2C1RST = 0x200000
RCC_APB1RSTR_I2C2RST = 0x400000
RCC_APB1RSTR_I2C3RST = 0x800000
RCC_APB1RSTR_CAN1RST = 0x2000000
RCC_APB1RSTR_CAN2RST = 0x4000000
RCC_APB1RSTR_PWRRST = 0x10000000
RCC_APB1RSTR_DACRST = 0x20000000
RCC_APB2RSTR_TIM1RST = 0x1
RCC_APB2RSTR_TIM8RST = 0x2
RCC_APB2RSTR_USART1RST = 0x10
RCC_APB2RSTR_USART6RST = 0x20
RCC_APB2RSTR_ADCRST = 0x100
RCC_APB2RSTR_SDIORST = 0x800
RCC_APB2RSTR_SPI1RST = 0x1000
RCC_APB2RSTR_SYSCFGRST = 0x4000
RCC_APB2RSTR_TIM9RST = 0x10000
RCC_APB2RSTR_TIM10RST = 0x20000
RCC_APB2RSTR_TIM11RST = 0x40000
RCC_APB2RSTR_SPI1 = 0x1000
RCC_AHB1ENR_GPIOAEN = 0x1
RCC_AHB1ENR_GPIOBEN = 0x2
RCC_AHB1ENR_GPIOCEN = 0x4
RCC_AHB1ENR_GPIODEN = 0x8
RCC_AHB1ENR_GPIOEEN = 0x10
RCC_AHB1ENR_GPIOFEN = 0x20
RCC_AHB1ENR_GPIOGEN = 0x40
RCC_AHB1ENR_GPIOHEN = 0x80
RCC_AHB1ENR_GPIOIEN = 0x100
RCC_AHB1ENR_CRCEN = 0x1000
RCC_AHB1ENR_BKPSRAMEN = 0x40000
RCC_AHB1ENR_CCMDATARAMEN = 0x100000
RCC_AHB1ENR_DMA1EN = 0x200000
RCC_AHB1ENR_DMA2EN = 0x400000
RCC_AHB1ENR_ETHMACEN = 0x2000000
RCC_AHB1ENR_ETHMACTXEN = 0x4000000
RCC_AHB1ENR_ETHMACRXEN = 0x8000000
RCC_AHB1ENR_ETHMACPTPEN = 0x10000000
RCC_AHB1ENR_OTGHSEN = 0x20000000
RCC_AHB1ENR_OTGHSULPIEN = 0x40000000
RCC_AHB2ENR_DCMIEN = 0x1
RCC_AHB2ENR_CRYPEN = 0x10
RCC_AHB2ENR_HASHEN = 0x20
RCC_AHB2ENR_RNGEN = 0x40
RCC_AHB2ENR_OTGFSEN = 0x80
RCC_AHB3ENR_FSMCEN = 0x1
RCC_APB1ENR_TIM2EN = 0x1
RCC_APB1ENR_TIM3EN = 0x2
RCC_APB1ENR_TIM4EN = 0x4
RCC_APB1ENR_TIM5EN = 0x8
RCC_APB1ENR_TIM6EN = 0x10
RCC_APB1ENR_TIM7EN = 0x20
RCC_APB1ENR_TIM12EN = 0x40
RCC_APB1ENR_TIM13EN = 0x80
RCC_APB1ENR_TIM14EN = 0x100
RCC_APB1ENR_WWDGEN = 0x800
RCC_APB1ENR_SPI2EN = 0x4000
RCC_APB1ENR_SPI3EN = 0x8000
RCC_APB1ENR_USART2EN = 0x20000
RCC_APB1ENR_USART3EN = 0x40000
RCC_APB1ENR_UART4EN = 0x80000
RCC_APB1ENR_UART5EN = 0x100000
RCC_APB1ENR_I2C1EN = 0x200000
RCC_APB1ENR_I2C2EN = 0x400000
RCC_APB1ENR_I2C3EN = 0x800000
RCC_APB1ENR_CAN1EN = 0x2000000
RCC_APB1ENR_CAN2EN = 0x4000000
RCC_APB1ENR_PWREN = 0x10000000
RCC_APB1ENR_DACEN = 0x20000000
RCC_APB2ENR_TIM1EN = 0x1
RCC_APB2ENR_TIM8EN = 0x2
RCC_APB2ENR_USART1EN = 0x10
RCC_APB2ENR_USART6EN = 0x20
RCC_APB2ENR_ADC1EN = 0x100
RCC_APB2ENR_ADC2EN = 0x200
RCC_APB2ENR_ADC3EN = 0x400
RCC_APB2ENR_SDIOEN = 0x800
RCC_APB2ENR_SPI1EN = 0x1000
RCC_APB2ENR_SYSCFGEN = 0x4000
RCC_APB2ENR_TIM11EN = 0x40000
RCC_APB2ENR_TIM10EN = 0x20000
RCC_APB2ENR_TIM9EN = 0x10000
RCC_AHB1LPENR_GPIOALPEN = 0x1
RCC_AHB1LPENR_GPIOBLPEN = 0x2
RCC_AHB1LPENR_GPIOCLPEN = 0x4
RCC_AHB1LPENR_GPIODLPEN = 0x8
RCC_AHB1LPENR_GPIOELPEN = 0x10
RCC_AHB1LPENR_GPIOFLPEN = 0x20
RCC_AHB1LPENR_GPIOGLPEN = 0x40
RCC_AHB1LPENR_GPIOHLPEN = 0x80
RCC_AHB1LPENR_GPIOILPEN = 0x100
RCC_AHB1LPENR_CRCLPEN = 0x1000
RCC_AHB1LPENR_FLITFLPEN = 0x8000
RCC_AHB1LPENR_SRAM1LPEN = 0x10000
RCC_AHB1LPENR_SRAM2LPEN = 0x20000
RCC_AHB1LPENR_BKPSRAMLPEN = 0x40000
RCC_AHB1LPENR_DMA1LPEN = 0x200000
RCC_AHB1LPENR_DMA2LPEN = 0x400000
RCC_AHB1LPENR_ETHMACLPEN = 0x2000000
RCC_AHB1LPENR_ETHMACTXLPEN = 0x4000000
RCC_AHB1LPENR_ETHMACRXLPEN = 0x8000000
RCC_AHB1LPENR_ETHMACPTPLPEN = 0x10000000
RCC_AHB1LPENR_OTGHSLPEN = 0x20000000
RCC_AHB1LPENR_OTGHSULPILPEN = 0x40000000
RCC_AHB2LPENR_DCMILPEN = 0x1
RCC_AHB2LPENR_CRYPLPEN = 0x10
RCC_AHB2LPENR_HASHLPEN = 0x20
RCC_AHB2LPENR_RNGLPEN = 0x40
RCC_AHB2LPENR_OTGFSLPEN = 0x80
RCC_AHB3LPENR_FSMCLPEN = 0x1
RCC_APB1LPENR_TIM2LPEN = 0x1
RCC_APB1LPENR_TIM3LPEN = 0x2
RCC_APB1LPENR_TIM4LPEN = 0x4
RCC_APB1LPENR_TIM5LPEN = 0x8
RCC_APB1LPENR_TIM6LPEN = 0x10
RCC_APB1LPENR_TIM7LPEN = 0x20
RCC_APB1LPENR_TIM12LPEN = 0x40
RCC_APB1LPENR_TIM13LPEN = 0x80
RCC_APB1LPENR_TIM14LPEN = 0x100
RCC_APB1LPENR_WWDGLPEN = 0x800
RCC_APB1LPENR_SPI2LPEN = 0x4000
RCC_APB1LPENR_SPI3LPEN = 0x8000
RCC_APB1LPENR_USART2LPEN = 0x20000
RCC_APB1LPENR_USART3LPEN = 0x40000
RCC_APB1LPENR_UART4LPEN = 0x80000
RCC_APB1LPENR_UART5LPEN = 0x100000
RCC_APB1LPENR_I2C1LPEN = 0x200000
RCC_APB1LPENR_I2C2LPEN = 0x400000
RCC_APB1LPENR_I2C3LPEN = 0x800000
RCC_APB1LPENR_CAN1LPEN = 0x2000000
RCC_APB1LPENR_CAN2LPEN = 0x4000000
RCC_APB1LPENR_PWRLPEN = 0x10000000
RCC_APB1LPENR_DACLPEN = 0x20000000
RCC_APB2LPENR_TIM1LPEN = 0x1
RCC_APB2LPENR_TIM8LPEN = 0x2
RCC_APB2LPENR_USART1LPEN = 0x10
RCC_APB2LPENR_USART6LPEN = 0x20
RCC_APB2LPENR_ADC1LPEN = 0x100
RCC_APB2LPENR_ADC2PEN = 0x200
RCC_APB2LPENR_ADC3LPEN = 0x400
RCC_APB2LPENR_SDIOLPEN = 0x800
RCC_APB2LPENR_SPI1LPEN = 0x1000
RCC_APB2LPENR_SYSCFGLPEN = 0x4000
RCC_APB2LPENR_TIM9LPEN = 0x10000
RCC_APB2LPENR_TIM10LPEN = 0x20000
RCC_APB2LPENR_TIM11LPEN = 0x40000
RCC_BDCR_LSEON = 0x1
RCC_BDCR_LSERDY = 0x2
RCC_BDCR_LSEBYP = 0x4
RCC_BDCR_RTCSEL = 0x300
RCC_BDCR_RTCSEL_0 = 0x100
RCC_BDCR_RTCSEL_1 = 0x200
RCC_BDCR_RTCEN = 0x8000
RCC_BDCR_BDRST = 0x10000
RCC_CSR_LSION = 0x1
RCC_CSR_LSIRDY = 0x2
RCC_CSR_RMVF = 0x1000000
RCC_CSR_BORRSTF = 0x2000000
RCC_CSR_PADRSTF = 0x4000000
RCC_CSR_PORRSTF = 0x8000000
RCC_CSR_SFTRSTF = 0x10000000
RCC_CSR_WDGRSTF = 0x20000000
RCC_CSR_WWDGRSTF = 0x40000000
RCC_CSR_LPWRRSTF = 0x80000000
RCC_SSCGR_MODPER = 0x1FFF
RCC_SSCGR_INCSTEP = 0xFFFE000
RCC_SSCGR_SPREADSEL = 0x40000000
RCC_SSCGR_SSCGEN = 0x80000000
RCC_PLLI2SCFGR_PLLI2SN = 0x7FC0
RCC_PLLI2SCFGR_PLLI2SR = 0x70000000
RNG_CR_RNGEN = 0x4
RNG_CR_IE = 0x8
RNG_SR_DRDY = 0x1
RNG_SR_CECS = 0x2
RNG_SR_SECS = 0x4
RNG_SR_CEIS = 0x20
RNG_SR_SEIS = 0x40
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
RTC_CR_BCK = 0x40000
RTC_CR_SUB1H = 0x20000
RTC_CR_ADD1H = 0x10000
RTC_CR_TSIE = 0x8000
RTC_CR_WUTIE = 0x4000
RTC_CR_ALRBIE = 0x2000
RTC_CR_ALRAIE = 0x1000
RTC_CR_TSE = 0x800
RTC_CR_WUTE = 0x400
RTC_CR_ALRBE = 0x200
RTC_CR_ALRAE = 0x100
RTC_CR_DCE = 0x80
RTC_CR_FMT = 0x40
RTC_CR_BYPSHAD = 0x20
RTC_CR_REFCKON = 0x10
RTC_CR_TSEDGE = 0x8
RTC_CR_WUCKSEL = 0x7
RTC_CR_WUCKSEL_0 = 0x1
RTC_CR_WUCKSEL_1 = 0x2
RTC_CR_WUCKSEL_2 = 0x4
RTC_ISR_RECALPF = 0x10000
RTC_ISR_TAMP1F = 0x2000
RTC_ISR_TSOVF = 0x1000
RTC_ISR_TSF = 0x800
RTC_ISR_WUTF = 0x400
RTC_ISR_ALRBF = 0x200
RTC_ISR_ALRAF = 0x100
RTC_ISR_INIT = 0x80
RTC_ISR_INITF = 0x40
RTC_ISR_RSF = 0x20
RTC_ISR_INITS = 0x10
RTC_ISR_SHPF = 0x8
RTC_ISR_WUTWF = 0x4
RTC_ISR_ALRBWF = 0x2
RTC_ISR_ALRAWF = 0x1
RTC_PRER_PREDIV_A = 0x7F0000
RTC_PRER_PREDIV_S = 0x1FFF
RTC_WUTR_WUT = 0xFFFF
RTC_CALIBR_DCS = 0x80
RTC_CALIBR_DC = 0x1F
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
RTC_ALRMBR_MSK4 = 0x80000000
RTC_ALRMBR_WDSEL = 0x40000000
RTC_ALRMBR_DT = 0x30000000
RTC_ALRMBR_DT_0 = 0x10000000
RTC_ALRMBR_DT_1 = 0x20000000
RTC_ALRMBR_DU = 0xF000000
RTC_ALRMBR_DU_0 = 0x1000000
RTC_ALRMBR_DU_1 = 0x2000000
RTC_ALRMBR_DU_2 = 0x4000000
RTC_ALRMBR_DU_3 = 0x8000000
RTC_ALRMBR_MSK3 = 0x800000
RTC_ALRMBR_PM = 0x400000
RTC_ALRMBR_HT = 0x300000
RTC_ALRMBR_HT_0 = 0x100000
RTC_ALRMBR_HT_1 = 0x200000
RTC_ALRMBR_HU = 0xF0000
RTC_ALRMBR_HU_0 = 0x10000
RTC_ALRMBR_HU_1 = 0x20000
RTC_ALRMBR_HU_2 = 0x40000
RTC_ALRMBR_HU_3 = 0x80000
RTC_ALRMBR_MSK2 = 0x8000
RTC_ALRMBR_MNT = 0x7000
RTC_ALRMBR_MNT_0 = 0x1000
RTC_ALRMBR_MNT_1 = 0x2000
RTC_ALRMBR_MNT_2 = 0x4000
RTC_ALRMBR_MNU = 0xF00
RTC_ALRMBR_MNU_0 = 0x100
RTC_ALRMBR_MNU_1 = 0x200
RTC_ALRMBR_MNU_2 = 0x400
RTC_ALRMBR_MNU_3 = 0x800
RTC_ALRMBR_MSK1 = 0x80
RTC_ALRMBR_ST = 0x70
RTC_ALRMBR_ST_0 = 0x10
RTC_ALRMBR_ST_1 = 0x20
RTC_ALRMBR_ST_2 = 0x40
RTC_ALRMBR_SU = 0xF
RTC_ALRMBR_SU_0 = 0x1
RTC_ALRMBR_SU_1 = 0x2
RTC_ALRMBR_SU_2 = 0x4
RTC_ALRMBR_SU_3 = 0x8
RTC_WPR_KEY = 0xFF
RTC_SSR_SS = 0xFFFF
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
RTC_TSSSR_SS = 0xFFFF
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
RTC_TAFCR_ALARMOUTTYPE = 0x40000
RTC_TAFCR_TSINSEL = 0x20000
RTC_TAFCR_TAMPINSEL = 0x10000
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
RTC_TAFCR_TAMPIE = 0x4
RTC_TAFCR_TAMP1TRG = 0x2
RTC_TAFCR_TAMP1E = 0x1
RTC_ALRMASSR_MASKSS = 0xF000000
RTC_ALRMASSR_MASKSS_0 = 0x1000000
RTC_ALRMASSR_MASKSS_1 = 0x2000000
RTC_ALRMASSR_MASKSS_2 = 0x4000000
RTC_ALRMASSR_MASKSS_3 = 0x8000000
RTC_ALRMASSR_SS = 0x7FFF
RTC_ALRMBSSR_MASKSS = 0xF000000
RTC_ALRMBSSR_MASKSS_0 = 0x1000000
RTC_ALRMBSSR_MASKSS_1 = 0x2000000
RTC_ALRMBSSR_MASKSS_2 = 0x4000000
RTC_ALRMBSSR_MASKSS_3 = 0x8000000
RTC_ALRMBSSR_SS = 0x7FFF
RTC_BKP0R = 0xFFFFFFFF
RTC_BKP1R = 0xFFFFFFFF
RTC_BKP2R = 0xFFFFFFFF
RTC_BKP3R = 0xFFFFFFFF
RTC_BKP4R = 0xFFFFFFFF
RTC_BKP5R = 0xFFFFFFFF
RTC_BKP6R = 0xFFFFFFFF
RTC_BKP7R = 0xFFFFFFFF
RTC_BKP8R = 0xFFFFFFFF
RTC_BKP9R = 0xFFFFFFFF
RTC_BKP10R = 0xFFFFFFFF
RTC_BKP11R = 0xFFFFFFFF
RTC_BKP12R = 0xFFFFFFFF
RTC_BKP13R = 0xFFFFFFFF
RTC_BKP14R = 0xFFFFFFFF
RTC_BKP15R = 0xFFFFFFFF
RTC_BKP16R = 0xFFFFFFFF
RTC_BKP17R = 0xFFFFFFFF
RTC_BKP18R = 0xFFFFFFFF
RTC_BKP19R = 0xFFFFFFFF
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
SYSCFG_MEMRMP_MEM_MODE = 0x3
SYSCFG_MEMRMP_MEM_MODE_0 = 0x1
SYSCFG_MEMRMP_MEM_MODE_1 = 0x2
SYSCFG_PMC_MII_RMII_SEL = 0x800000
SYSCFG_PMC_MII_RMII = 0x800000
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
SYSCFG_EXTICR1_EXTI0_PG = 0x6
SYSCFG_EXTICR1_EXTI0_PH = 0x7
SYSCFG_EXTICR1_EXTI0_PI = 0x8
SYSCFG_EXTICR1_EXTI1_PA = 0x0
SYSCFG_EXTICR1_EXTI1_PB = 0x10
SYSCFG_EXTICR1_EXTI1_PC = 0x20
SYSCFG_EXTICR1_EXTI1_PD = 0x30
SYSCFG_EXTICR1_EXTI1_PE = 0x40
SYSCFG_EXTICR1_EXTI1_PF = 0x50
SYSCFG_EXTICR1_EXTI1_PG = 0x60
SYSCFG_EXTICR1_EXTI1_PH = 0x70
SYSCFG_EXTICR1_EXTI1_PI = 0x80
SYSCFG_EXTICR1_EXTI2_PA = 0x0
SYSCFG_EXTICR1_EXTI2_PB = 0x100
SYSCFG_EXTICR1_EXTI2_PC = 0x200
SYSCFG_EXTICR1_EXTI2_PD = 0x300
SYSCFG_EXTICR1_EXTI2_PE = 0x400
SYSCFG_EXTICR1_EXTI2_PF = 0x500
SYSCFG_EXTICR1_EXTI2_PG = 0x600
SYSCFG_EXTICR1_EXTI2_PH = 0x700
SYSCFG_EXTICR1_EXTI2_PI = 0x800
SYSCFG_EXTICR1_EXTI3_PA = 0x0
SYSCFG_EXTICR1_EXTI3_PB = 0x1000
SYSCFG_EXTICR1_EXTI3_PC = 0x2000
SYSCFG_EXTICR1_EXTI3_PD = 0x3000
SYSCFG_EXTICR1_EXTI3_PE = 0x4000
SYSCFG_EXTICR1_EXTI3_PF = 0x5000
SYSCFG_EXTICR1_EXTI3_PG = 0x6000
SYSCFG_EXTICR1_EXTI3_PH = 0x7000
SYSCFG_EXTICR1_EXTI3_PI = 0x8000
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
SYSCFG_EXTICR2_EXTI4_PG = 0x6
SYSCFG_EXTICR2_EXTI4_PH = 0x7
SYSCFG_EXTICR2_EXTI4_PI = 0x8
SYSCFG_EXTICR2_EXTI5_PA = 0x0
SYSCFG_EXTICR2_EXTI5_PB = 0x10
SYSCFG_EXTICR2_EXTI5_PC = 0x20
SYSCFG_EXTICR2_EXTI5_PD = 0x30
SYSCFG_EXTICR2_EXTI5_PE = 0x40
SYSCFG_EXTICR2_EXTI5_PF = 0x50
SYSCFG_EXTICR2_EXTI5_PG = 0x60
SYSCFG_EXTICR2_EXTI5_PH = 0x70
SYSCFG_EXTICR2_EXTI5_PI = 0x80
SYSCFG_EXTICR2_EXTI6_PA = 0x0
SYSCFG_EXTICR2_EXTI6_PB = 0x100
SYSCFG_EXTICR2_EXTI6_PC = 0x200
SYSCFG_EXTICR2_EXTI6_PD = 0x300
SYSCFG_EXTICR2_EXTI6_PE = 0x400
SYSCFG_EXTICR2_EXTI6_PF = 0x500
SYSCFG_EXTICR2_EXTI6_PG = 0x600
SYSCFG_EXTICR2_EXTI6_PH = 0x700
SYSCFG_EXTICR2_EXTI6_PI = 0x800
SYSCFG_EXTICR2_EXTI7_PA = 0x0
SYSCFG_EXTICR2_EXTI7_PB = 0x1000
SYSCFG_EXTICR2_EXTI7_PC = 0x2000
SYSCFG_EXTICR2_EXTI7_PD = 0x3000
SYSCFG_EXTICR2_EXTI7_PE = 0x4000
SYSCFG_EXTICR2_EXTI7_PF = 0x5000
SYSCFG_EXTICR2_EXTI7_PG = 0x6000
SYSCFG_EXTICR2_EXTI7_PH = 0x7000
SYSCFG_EXTICR2_EXTI7_PI = 0x8000
SYSCFG_EXTICR3_EXTI8 = 0xF
SYSCFG_EXTICR3_EXTI9 = 0xF0
SYSCFG_EXTICR3_EXTI10 = 0xF00
SYSCFG_EXTICR3_EXTI11 = 0xF000
SYSCFG_EXTICR3_EXTI8_PA = 0x0
SYSCFG_EXTICR3_EXTI8_PB = 0x1
SYSCFG_EXTICR3_EXTI8_PC = 0x2
SYSCFG_EXTICR3_EXTI8_PD = 0x3
SYSCFG_EXTICR3_EXTI8_PE = 0x4
SYSCFG_EXTICR3_EXTI8_PF = 0x5
SYSCFG_EXTICR3_EXTI8_PG = 0x6
SYSCFG_EXTICR3_EXTI8_PH = 0x7
SYSCFG_EXTICR3_EXTI8_PI = 0x8
SYSCFG_EXTICR3_EXTI9_PA = 0x0
SYSCFG_EXTICR3_EXTI9_PB = 0x10
SYSCFG_EXTICR3_EXTI9_PC = 0x20
SYSCFG_EXTICR3_EXTI9_PD = 0x30
SYSCFG_EXTICR3_EXTI9_PE = 0x40
SYSCFG_EXTICR3_EXTI9_PF = 0x50
SYSCFG_EXTICR3_EXTI9_PG = 0x60
SYSCFG_EXTICR3_EXTI9_PH = 0x70
SYSCFG_EXTICR3_EXTI9_PI = 0x80
SYSCFG_EXTICR3_EXTI10_PA = 0x0
SYSCFG_EXTICR3_EXTI10_PB = 0x100
SYSCFG_EXTICR3_EXTI10_PC = 0x200
SYSCFG_EXTICR3_EXTI10_PD = 0x300
SYSCFG_EXTICR3_EXTI10_PE = 0x400
SYSCFG_EXTICR3_EXTI10_PF = 0x500
SYSCFG_EXTICR3_EXTI10_PG = 0x600
SYSCFG_EXTICR3_EXTI10_PH = 0x700
SYSCFG_EXTICR3_EXTI10_PI = 0x800
SYSCFG_EXTICR3_EXTI11_PA = 0x0
SYSCFG_EXTICR3_EXTI11_PB = 0x1000
SYSCFG_EXTICR3_EXTI11_PC = 0x2000
SYSCFG_EXTICR3_EXTI11_PD = 0x3000
SYSCFG_EXTICR3_EXTI11_PE = 0x4000
SYSCFG_EXTICR3_EXTI11_PF = 0x5000
SYSCFG_EXTICR3_EXTI11_PG = 0x6000
SYSCFG_EXTICR3_EXTI11_PH = 0x7000
SYSCFG_EXTICR3_EXTI11_PI = 0x8000
SYSCFG_EXTICR4_EXTI12 = 0xF
SYSCFG_EXTICR4_EXTI13 = 0xF0
SYSCFG_EXTICR4_EXTI14 = 0xF00
SYSCFG_EXTICR4_EXTI15 = 0xF000
SYSCFG_EXTICR4_EXTI12_PA = 0x0
SYSCFG_EXTICR4_EXTI12_PB = 0x1
SYSCFG_EXTICR4_EXTI12_PC = 0x2
SYSCFG_EXTICR4_EXTI12_PD = 0x3
SYSCFG_EXTICR4_EXTI12_PE = 0x4
SYSCFG_EXTICR4_EXTI12_PF = 0x5
SYSCFG_EXTICR4_EXTI12_PG = 0x6
SYSCFG_EXTICR3_EXTI12_PH = 0x7
SYSCFG_EXTICR4_EXTI13_PA = 0x0
SYSCFG_EXTICR4_EXTI13_PB = 0x10
SYSCFG_EXTICR4_EXTI13_PC = 0x20
SYSCFG_EXTICR4_EXTI13_PD = 0x30
SYSCFG_EXTICR4_EXTI13_PE = 0x40
SYSCFG_EXTICR4_EXTI13_PF = 0x50
SYSCFG_EXTICR4_EXTI13_PG = 0x60
SYSCFG_EXTICR3_EXTI13_PH = 0x70
SYSCFG_EXTICR4_EXTI14_PA = 0x0
SYSCFG_EXTICR4_EXTI14_PB = 0x100
SYSCFG_EXTICR4_EXTI14_PC = 0x200
SYSCFG_EXTICR4_EXTI14_PD = 0x300
SYSCFG_EXTICR4_EXTI14_PE = 0x400
SYSCFG_EXTICR4_EXTI14_PF = 0x500
SYSCFG_EXTICR4_EXTI14_PG = 0x600
SYSCFG_EXTICR3_EXTI14_PH = 0x700
SYSCFG_EXTICR4_EXTI15_PA = 0x0
SYSCFG_EXTICR4_EXTI15_PB = 0x1000
SYSCFG_EXTICR4_EXTI15_PC = 0x2000
SYSCFG_EXTICR4_EXTI15_PD = 0x3000
SYSCFG_EXTICR4_EXTI15_PE = 0x4000
SYSCFG_EXTICR4_EXTI15_PF = 0x5000
SYSCFG_EXTICR4_EXTI15_PG = 0x6000
SYSCFG_EXTICR3_EXTI15_PH = 0x7000
SYSCFG_CMPCR_CMP_PD = 0x1
SYSCFG_CMPCR_READY = 0x100
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
TIM_OR_TI4_RMP = 0xC0
TIM_OR_TI4_RMP_0 = 0x40
TIM_OR_TI4_RMP_1 = 0x80
TIM_OR_ITR1_RMP = 0xC00
TIM_OR_ITR1_RMP_0 = 0x400
TIM_OR_ITR1_RMP_1 = 0x800
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
DBGMCU_IDCODE_DEV_ID = 0xFFF
DBGMCU_IDCODE_REV_ID = 0xFFFF0000
DBGMCU_CR_DBG_SLEEP = 0x1
DBGMCU_CR_DBG_STOP = 0x2
DBGMCU_CR_DBG_STANDBY = 0x4
DBGMCU_CR_TRACE_IOEN = 0x20
DBGMCU_CR_TRACE_MODE = 0xC0
DBGMCU_CR_TRACE_MODE_0 = 0x40
DBGMCU_CR_TRACE_MODE_1 = 0x80
DBGMCU_APB1_FZ_DBG_TIM2_STOP = 0x1
DBGMCU_APB1_FZ_DBG_TIM3_STOP = 0x2
DBGMCU_APB1_FZ_DBG_TIM4_STOP = 0x4
DBGMCU_APB1_FZ_DBG_TIM5_STOP = 0x8
DBGMCU_APB1_FZ_DBG_TIM6_STOP = 0x10
DBGMCU_APB1_FZ_DBG_TIM7_STOP = 0x20
DBGMCU_APB1_FZ_DBG_TIM12_STOP = 0x40
DBGMCU_APB1_FZ_DBG_TIM13_STOP = 0x80
DBGMCU_APB1_FZ_DBG_TIM14_STOP = 0x100
DBGMCU_APB1_FZ_DBG_RTC_STOP = 0x400
DBGMCU_APB1_FZ_DBG_WWDG_STOP = 0x800
DBGMCU_APB1_FZ_DBG_IWDG_STOP = 0x1000
DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT = 0x200000
DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT = 0x400000
DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT = 0x800000
DBGMCU_APB1_FZ_DBG_CAN1_STOP = 0x2000000
DBGMCU_APB1_FZ_DBG_CAN2_STOP = 0x4000000
DBGMCU_APB1_FZ_DBG_IWDEG_STOP = 0x1000
DBGMCU_APB1_FZ_DBG_TIM1_STOP = 0x1
DBGMCU_APB1_FZ_DBG_TIM8_STOP = 0x2
DBGMCU_APB1_FZ_DBG_TIM9_STOP = 0x10000
DBGMCU_APB1_FZ_DBG_TIM10_STOP = 0x20000
DBGMCU_APB1_FZ_DBG_TIM11_STOP = 0x40000
ETH_MACCR_WD = 0x800000
ETH_MACCR_JD = 0x400000
ETH_MACCR_IFG = 0xE0000
ETH_MACCR_IFG_96Bit = 0x0
ETH_MACCR_IFG_88Bit = 0x20000
ETH_MACCR_IFG_80Bit = 0x40000
ETH_MACCR_IFG_72Bit = 0x60000
ETH_MACCR_IFG_64Bit = 0x80000
ETH_MACCR_IFG_56Bit = 0xA0000
ETH_MACCR_IFG_48Bit = 0xC0000
ETH_MACCR_IFG_40Bit = 0xE0000
ETH_MACCR_CSD = 0x10000
ETH_MACCR_FES = 0x4000
ETH_MACCR_ROD = 0x2000
ETH_MACCR_LM = 0x1000
ETH_MACCR_DM = 0x800
ETH_MACCR_IPCO = 0x400
ETH_MACCR_RD = 0x200
ETH_MACCR_APCS = 0x80
ETH_MACCR_BL = 0x60
ETH_MACCR_BL_10 = 0x0
ETH_MACCR_BL_8 = 0x20
ETH_MACCR_BL_4 = 0x40
ETH_MACCR_BL_1 = 0x60
ETH_MACCR_DC = 0x10
ETH_MACCR_TE = 0x8
ETH_MACCR_RE = 0x4
ETH_MACFFR_RA = 0x80000000
ETH_MACFFR_HPF = 0x400
ETH_MACFFR_SAF = 0x200
ETH_MACFFR_SAIF = 0x100
ETH_MACFFR_PCF = 0xC0
ETH_MACFFR_PCF_BlockAll = 0x40
ETH_MACFFR_PCF_ForwardAll = 0x80
ETH_MACFFR_PCF_ForwardPassedAddrFilter = 0xC0
ETH_MACFFR_BFD = 0x20
ETH_MACFFR_PAM = 0x10
ETH_MACFFR_DAIF = 0x8
ETH_MACFFR_HM = 0x4
ETH_MACFFR_HU = 0x2
ETH_MACFFR_PM = 0x1
ETH_MACHTHR_HTH = 0xFFFFFFFF
ETH_MACHTLR_HTL = 0xFFFFFFFF
ETH_MACMIIAR_PA = 0xF800
ETH_MACMIIAR_MR = 0x7C0
ETH_MACMIIAR_CR = 0x1C
ETH_MACMIIAR_CR_Div42 = 0x0
ETH_MACMIIAR_CR_Div62 = 0x4
ETH_MACMIIAR_CR_Div16 = 0x8
ETH_MACMIIAR_CR_Div26 = 0xC
ETH_MACMIIAR_CR_Div102 = 0x10
ETH_MACMIIAR_MW = 0x2
ETH_MACMIIAR_MB = 0x1
ETH_MACMIIDR_MD = 0xFFFF
ETH_MACFCR_PT = 0xFFFF0000
ETH_MACFCR_ZQPD = 0x80
ETH_MACFCR_PLT = 0x30
ETH_MACFCR_PLT_Minus4 = 0x0
ETH_MACFCR_PLT_Minus28 = 0x10
ETH_MACFCR_PLT_Minus144 = 0x20
ETH_MACFCR_PLT_Minus256 = 0x30
ETH_MACFCR_UPFD = 0x8
ETH_MACFCR_RFCE = 0x4
ETH_MACFCR_TFCE = 0x2
ETH_MACFCR_FCBBPA = 0x1
ETH_MACVLANTR_VLANTC = 0x10000
ETH_MACVLANTR_VLANTI = 0xFFFF
ETH_MACRWUFFR_D = 0xFFFFFFFF
ETH_MACPMTCSR_WFFRPR = 0x80000000
ETH_MACPMTCSR_GU = 0x200
ETH_MACPMTCSR_WFR = 0x40
ETH_MACPMTCSR_MPR = 0x20
ETH_MACPMTCSR_WFE = 0x4
ETH_MACPMTCSR_MPE = 0x2
ETH_MACPMTCSR_PD = 0x1
ETH_MACSR_TSTS = 0x200
ETH_MACSR_MMCTS = 0x40
ETH_MACSR_MMMCRS = 0x20
ETH_MACSR_MMCS = 0x10
ETH_MACSR_PMTS = 0x8
ETH_MACIMR_TSTIM = 0x200
ETH_MACIMR_PMTIM = 0x8
ETH_MACA0HR_MACA0H = 0xFFFF
ETH_MACA0LR_MACA0L = 0xFFFFFFFF
ETH_MACA1HR_AE = 0x80000000
ETH_MACA1HR_SA = 0x40000000
ETH_MACA1HR_MBC = 0x3F000000
ETH_MACA1HR_MBC_HBits15_8 = 0x20000000
ETH_MACA1HR_MBC_HBits7_0 = 0x10000000
ETH_MACA1HR_MBC_LBits31_24 = 0x8000000
ETH_MACA1HR_MBC_LBits23_16 = 0x4000000
ETH_MACA1HR_MBC_LBits15_8 = 0x2000000
ETH_MACA1HR_MBC_LBits7_0 = 0x1000000
ETH_MACA1HR_MACA1H = 0xFFFF
ETH_MACA1LR_MACA1L = 0xFFFFFFFF
ETH_MACA2HR_AE = 0x80000000
ETH_MACA2HR_SA = 0x40000000
ETH_MACA2HR_MBC = 0x3F000000
ETH_MACA2HR_MBC_HBits15_8 = 0x20000000
ETH_MACA2HR_MBC_HBits7_0 = 0x10000000
ETH_MACA2HR_MBC_LBits31_24 = 0x8000000
ETH_MACA2HR_MBC_LBits23_16 = 0x4000000
ETH_MACA2HR_MBC_LBits15_8 = 0x2000000
ETH_MACA2HR_MBC_LBits7_0 = 0x1000000
ETH_MACA2HR_MACA2H = 0xFFFF
ETH_MACA2LR_MACA2L = 0xFFFFFFFF
ETH_MACA3HR_AE = 0x80000000
ETH_MACA3HR_SA = 0x40000000
ETH_MACA3HR_MBC = 0x3F000000
ETH_MACA3HR_MBC_HBits15_8 = 0x20000000
ETH_MACA3HR_MBC_HBits7_0 = 0x10000000
ETH_MACA3HR_MBC_LBits31_24 = 0x8000000
ETH_MACA3HR_MBC_LBits23_16 = 0x4000000
ETH_MACA3HR_MBC_LBits15_8 = 0x2000000
ETH_MACA3HR_MBC_LBits7_0 = 0x1000000
ETH_MACA3HR_MACA3H = 0xFFFF
ETH_MACA3LR_MACA3L = 0xFFFFFFFF
ETH_MMCCR_MCFHP = 0x20
ETH_MMCCR_MCP = 0x10
ETH_MMCCR_MCF = 0x8
ETH_MMCCR_ROR = 0x4
ETH_MMCCR_CSR = 0x2
ETH_MMCCR_CR = 0x1
ETH_MMCRIR_RGUFS = 0x20000
ETH_MMCRIR_RFAES = 0x40
ETH_MMCRIR_RFCES = 0x20
ETH_MMCTIR_TGFS = 0x200000
ETH_MMCTIR_TGFMSCS = 0x8000
ETH_MMCTIR_TGFSCS = 0x4000
ETH_MMCRIMR_RGUFM = 0x20000
ETH_MMCRIMR_RFAEM = 0x40
ETH_MMCRIMR_RFCEM = 0x20
ETH_MMCTIMR_TGFM = 0x200000
ETH_MMCTIMR_TGFMSCM = 0x8000
ETH_MMCTIMR_TGFSCM = 0x4000
ETH_MMCTGFSCCR_TGFSCC = 0xFFFFFFFF
ETH_MMCTGFMSCCR_TGFMSCC = 0xFFFFFFFF
ETH_MMCTGFCR_TGFC = 0xFFFFFFFF
ETH_MMCRFCECR_RFCEC = 0xFFFFFFFF
ETH_MMCRFAECR_RFAEC = 0xFFFFFFFF
ETH_MMCRGUFCR_RGUFC = 0xFFFFFFFF
ETH_PTPTSCR_TSCNT = 0x30000
ETH_PTPTSSR_TSSMRME = 0x8000
ETH_PTPTSSR_TSSEME = 0x4000
ETH_PTPTSSR_TSSIPV4FE = 0x2000
ETH_PTPTSSR_TSSIPV6FE = 0x1000
ETH_PTPTSSR_TSSPTPOEFE = 0x800
ETH_PTPTSSR_TSPTPPSV2E = 0x400
ETH_PTPTSSR_TSSSR = 0x200
ETH_PTPTSSR_TSSARFE = 0x100
ETH_PTPTSCR_TSARU = 0x20
ETH_PTPTSCR_TSITE = 0x10
ETH_PTPTSCR_TSSTU = 0x8
ETH_PTPTSCR_TSSTI = 0x4
ETH_PTPTSCR_TSFCU = 0x2
ETH_PTPTSCR_TSE = 0x1
ETH_PTPSSIR_STSSI = 0xFF
ETH_PTPTSHR_STS = 0xFFFFFFFF
ETH_PTPTSLR_STPNS = 0x80000000
ETH_PTPTSLR_STSS = 0x7FFFFFFF
ETH_PTPTSHUR_TSUS = 0xFFFFFFFF
ETH_PTPTSLUR_TSUPNS = 0x80000000
ETH_PTPTSLUR_TSUSS = 0x7FFFFFFF
ETH_PTPTSAR_TSA = 0xFFFFFFFF
ETH_PTPTTHR_TTSH = 0xFFFFFFFF
ETH_PTPTTLR_TTSL = 0xFFFFFFFF
ETH_PTPTSSR_TSTTR = 0x20
ETH_PTPTSSR_TSSO = 0x10
ETH_DMABMR_AAB = 0x2000000
ETH_DMABMR_FPM = 0x1000000
ETH_DMABMR_USP = 0x800000
ETH_DMABMR_RDP = 0x7E0000
ETH_DMABMR_RDP_1Beat = 0x20000
ETH_DMABMR_RDP_2Beat = 0x40000
ETH_DMABMR_RDP_4Beat = 0x80000
ETH_DMABMR_RDP_8Beat = 0x100000
ETH_DMABMR_RDP_16Beat = 0x200000
ETH_DMABMR_RDP_32Beat = 0x400000
ETH_DMABMR_RDP_4xPBL_4Beat = 0x1020000
ETH_DMABMR_RDP_4xPBL_8Beat = 0x1040000
ETH_DMABMR_RDP_4xPBL_16Beat = 0x1080000
ETH_DMABMR_RDP_4xPBL_32Beat = 0x1100000
ETH_DMABMR_RDP_4xPBL_64Beat = 0x1200000
ETH_DMABMR_RDP_4xPBL_128Beat = 0x1400000
ETH_DMABMR_FB = 0x10000
ETH_DMABMR_RTPR = 0xC000
ETH_DMABMR_RTPR_1_1 = 0x0
ETH_DMABMR_RTPR_2_1 = 0x4000
ETH_DMABMR_RTPR_3_1 = 0x8000
ETH_DMABMR_RTPR_4_1 = 0xC000
ETH_DMABMR_PBL = 0x3F00
ETH_DMABMR_PBL_1Beat = 0x100
ETH_DMABMR_PBL_2Beat = 0x200
ETH_DMABMR_PBL_4Beat = 0x400
ETH_DMABMR_PBL_8Beat = 0x800
ETH_DMABMR_PBL_16Beat = 0x1000
ETH_DMABMR_PBL_32Beat = 0x2000
ETH_DMABMR_PBL_4xPBL_4Beat = 0x1000100
ETH_DMABMR_PBL_4xPBL_8Beat = 0x1000200
ETH_DMABMR_PBL_4xPBL_16Beat = 0x1000400
ETH_DMABMR_PBL_4xPBL_32Beat = 0x1000800
ETH_DMABMR_PBL_4xPBL_64Beat = 0x1001000
ETH_DMABMR_PBL_4xPBL_128Beat = 0x1002000
ETH_DMABMR_EDE = 0x80
ETH_DMABMR_DSL = 0x7C
ETH_DMABMR_DA = 0x2
ETH_DMABMR_SR = 0x1
ETH_DMATPDR_TPD = 0xFFFFFFFF
ETH_DMARPDR_RPD = 0xFFFFFFFF
ETH_DMARDLAR_SRL = 0xFFFFFFFF
ETH_DMATDLAR_STL = 0xFFFFFFFF
ETH_DMASR_TSTS = 0x20000000
ETH_DMASR_PMTS = 0x10000000
ETH_DMASR_MMCS = 0x8000000
ETH_DMASR_EBS = 0x3800000
ETH_DMASR_EBS_DescAccess = 0x2000000
ETH_DMASR_EBS_ReadTransf = 0x1000000
ETH_DMASR_EBS_DataTransfTx = 0x800000
ETH_DMASR_TPS = 0x700000
ETH_DMASR_TPS_Stopped = 0x0
ETH_DMASR_TPS_Fetching = 0x100000
ETH_DMASR_TPS_Waiting = 0x200000
ETH_DMASR_TPS_Reading = 0x300000
ETH_DMASR_TPS_Suspended = 0x600000
ETH_DMASR_TPS_Closing = 0x700000
ETH_DMASR_RPS = 0xE0000
ETH_DMASR_RPS_Stopped = 0x0
ETH_DMASR_RPS_Fetching = 0x20000
ETH_DMASR_RPS_Waiting = 0x60000
ETH_DMASR_RPS_Suspended = 0x80000
ETH_DMASR_RPS_Closing = 0xA0000
ETH_DMASR_RPS_Queuing = 0xE0000
ETH_DMASR_NIS = 0x10000
ETH_DMASR_AIS = 0x8000
ETH_DMASR_ERS = 0x4000
ETH_DMASR_FBES = 0x2000
ETH_DMASR_ETS = 0x400
ETH_DMASR_RWTS = 0x200
ETH_DMASR_RPSS = 0x100
ETH_DMASR_RBUS = 0x80
ETH_DMASR_RS = 0x40
ETH_DMASR_TUS = 0x20
ETH_DMASR_ROS = 0x10
ETH_DMASR_TJTS = 0x8
ETH_DMASR_TBUS = 0x4
ETH_DMASR_TPSS = 0x2
ETH_DMASR_TS = 0x1
ETH_DMAOMR_DTCEFD = 0x4000000
ETH_DMAOMR_RSF = 0x2000000
ETH_DMAOMR_DFRF = 0x1000000
ETH_DMAOMR_TSF = 0x200000
ETH_DMAOMR_FTF = 0x100000
ETH_DMAOMR_TTC = 0x1C000
ETH_DMAOMR_TTC_64Bytes = 0x0
ETH_DMAOMR_TTC_128Bytes = 0x4000
ETH_DMAOMR_TTC_192Bytes = 0x8000
ETH_DMAOMR_TTC_256Bytes = 0xC000
ETH_DMAOMR_TTC_40Bytes = 0x10000
ETH_DMAOMR_TTC_32Bytes = 0x14000
ETH_DMAOMR_TTC_24Bytes = 0x18000
ETH_DMAOMR_TTC_16Bytes = 0x1C000
ETH_DMAOMR_ST = 0x2000
ETH_DMAOMR_FEF = 0x80
ETH_DMAOMR_FUGF = 0x40
ETH_DMAOMR_RTC = 0x18
ETH_DMAOMR_RTC_64Bytes = 0x0
ETH_DMAOMR_RTC_32Bytes = 0x8
ETH_DMAOMR_RTC_96Bytes = 0x10
ETH_DMAOMR_RTC_128Bytes = 0x18
ETH_DMAOMR_OSF = 0x4
ETH_DMAOMR_SR = 0x2
ETH_DMAIER_NISE = 0x10000
ETH_DMAIER_AISE = 0x8000
ETH_DMAIER_ERIE = 0x4000
ETH_DMAIER_FBEIE = 0x2000
ETH_DMAIER_ETIE = 0x400
ETH_DMAIER_RWTIE = 0x200
ETH_DMAIER_RPSIE = 0x100
ETH_DMAIER_RBUIE = 0x80
ETH_DMAIER_RIE = 0x40
ETH_DMAIER_TUIE = 0x20
ETH_DMAIER_ROIE = 0x10
ETH_DMAIER_TJTIE = 0x8
ETH_DMAIER_TBUIE = 0x4
ETH_DMAIER_TPSIE = 0x2
ETH_DMAIER_TIE = 0x1
ETH_DMAMFBOCR_OFOC = 0x10000000
ETH_DMAMFBOCR_MFA = 0xFFE0000
ETH_DMAMFBOCR_OMFC = 0x10000
ETH_DMAMFBOCR_MFC = 0xFFFF
ETH_DMACHTDR_HTDAP = 0xFFFFFFFF
ETH_DMACHRDR_HRDAP = 0xFFFFFFFF
ETH_DMACHTBAR_HTBAP = 0xFFFFFFFF
ETH_DMACHRBAR_HRBAP = 0xFFFFFFFF
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

# struct ADC_Common_TypeDef

class ADC_Common_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CSR',	ctypes.c_uint32),
		('CCR',	ctypes.c_uint32),
		('CDR',	ctypes.c_uint32),
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
# struct CAN_TypeDef : field is array
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

# struct DCMI_TypeDef

class DCMI_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('RISR',	ctypes.c_uint32),
		('IER',	ctypes.c_uint32),
		('MISR',	ctypes.c_uint32),
		('ICR',	ctypes.c_uint32),
		('ESCR',	ctypes.c_uint32),
		('ESUR',	ctypes.c_uint32),
		('CWSTRTR',	ctypes.c_uint32),
		('CWSIZER',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DMA_Stream_TypeDef

class DMA_Stream_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('NDTR',	ctypes.c_uint32),
		('PAR',	ctypes.c_uint32),
		('M0AR',	ctypes.c_uint32),
		('M1AR',	ctypes.c_uint32),
		('FCR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct DMA_TypeDef

class DMA_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('LISR',	ctypes.c_uint32),
		('HISR',	ctypes.c_uint32),
		('LIFCR',	ctypes.c_uint32),
		('HIFCR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ETH_TypeDef
# struct ETH_TypeDef : field is array
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
		('OPTCR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct FSMC_Bank1_TypeDef
# struct FSMC_Bank1_TypeDef : field is array
# struct FSMC_Bank1E_TypeDef
# struct FSMC_Bank1E_TypeDef : field is array
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
# struct GPIO_TypeDef : field is array
# struct SYSCFG_TypeDef
# struct SYSCFG_TypeDef : field is array
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
# struct RCC_TypeDef : field is array
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
		('CALIBR',	ctypes.c_uint32),
		('ALRMAR',	ctypes.c_uint32),
		('ALRMBR',	ctypes.c_uint32),
		('WPR',	ctypes.c_uint32),
		('SSR',	ctypes.c_uint32),
		('SHIFTR',	ctypes.c_uint32),
		('TSTR',	ctypes.c_uint32),
		('TSDR',	ctypes.c_uint32),
		('TSSSR',	ctypes.c_uint32),
		('CALR',	ctypes.c_uint32),
		('TAFCR',	ctypes.c_uint32),
		('ALRMASSR',	ctypes.c_uint32),
		('ALRMBSSR',	ctypes.c_uint32),
		('RESERVED7',	ctypes.c_uint32),
		('BKP0R',	ctypes.c_uint32),
		('BKP1R',	ctypes.c_uint32),
		('BKP2R',	ctypes.c_uint32),
		('BKP3R',	ctypes.c_uint32),
		('BKP4R',	ctypes.c_uint32),
		('BKP5R',	ctypes.c_uint32),
		('BKP6R',	ctypes.c_uint32),
		('BKP7R',	ctypes.c_uint32),
		('BKP8R',	ctypes.c_uint32),
		('BKP9R',	ctypes.c_uint32),
		('BKP10R',	ctypes.c_uint32),
		('BKP11R',	ctypes.c_uint32),
		('BKP12R',	ctypes.c_uint32),
		('BKP13R',	ctypes.c_uint32),
		('BKP14R',	ctypes.c_uint32),
		('BKP15R',	ctypes.c_uint32),
		('BKP16R',	ctypes.c_uint32),
		('BKP17R',	ctypes.c_uint32),
		('BKP18R',	ctypes.c_uint32),
		('BKP19R',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SDIO_TypeDef
# struct SDIO_TypeDef : field is array
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
		('RESERVED9',	ctypes.c_uint16),
		('ARR',	ctypes.c_uint32),
		('RCR',	ctypes.c_uint16),
		('RESERVED10',	ctypes.c_uint16),
		('CCR1',	ctypes.c_uint32),
		('CCR2',	ctypes.c_uint32),
		('CCR3',	ctypes.c_uint32),
		('CCR4',	ctypes.c_uint32),
		('BDTR',	ctypes.c_uint16),
		('RESERVED11',	ctypes.c_uint16),
		('DCR',	ctypes.c_uint16),
		('RESERVED12',	ctypes.c_uint16),
		('DMAR',	ctypes.c_uint16),
		('RESERVED13',	ctypes.c_uint16),
		('OR',	ctypes.c_uint16),
		('RESERVED14',	ctypes.c_uint16),
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

# struct CRYP_TypeDef

class CRYP_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
		('DOUT',	ctypes.c_uint32),
		('DMACR',	ctypes.c_uint32),
		('IMSCR',	ctypes.c_uint32),
		('RISR',	ctypes.c_uint32),
		('MISR',	ctypes.c_uint32),
		('K0LR',	ctypes.c_uint32),
		('K0RR',	ctypes.c_uint32),
		('K1LR',	ctypes.c_uint32),
		('K1RR',	ctypes.c_uint32),
		('K2LR',	ctypes.c_uint32),
		('K2RR',	ctypes.c_uint32),
		('K3LR',	ctypes.c_uint32),
		('K3RR',	ctypes.c_uint32),
		('IV0LR',	ctypes.c_uint32),
		('IV0RR',	ctypes.c_uint32),
		('IV1LR',	ctypes.c_uint32),
		('IV1RR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct HASH_TypeDef
# struct HASH_TypeDef : field is array
# struct RNG_TypeDef

class RNG_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CR',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file system_stm32f4xx.h : 

# empty define __SYSTEM_STM32F4XX_H
# Skip SystemCoreClock : no need parse
# ----------------------------------------


__all__ =  ['__RUN', '__HALT', '__ERROR', '__WARNING', '__INFO', '__DEBUG', '__ALL_LOG',
    'DEFAULT_OPENOCD_PORT', 'DEFAULT_GDB_PORT', 'TIM_OCMode_Timing',
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
    'TIM_MasterSlaveMode_Disable', 'TIM2_TIM8_TRGO', 'TIM2_ETH_PTP', 'TIM2_USBFS_SOF',
    'TIM2_USBHS_SOF', 'TIM5_GPIO', 'TIM5_LSI', 'TIM5_LSE', 'TIM5_RTC', 'TIM11_GPIO',
    'TIM11_HSE', 'TIM_FLAG_Update', 'TIM_FLAG_CC1', 'TIM_FLAG_CC2', 'TIM_FLAG_CC3',
    'TIM_FLAG_CC4', 'TIM_FLAG_COM', 'TIM_FLAG_Trigger', 'TIM_FLAG_Break',
    'TIM_FLAG_CC1OF', 'TIM_FLAG_CC2OF', 'TIM_FLAG_CC3OF', 'TIM_FLAG_CC4OF',
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
    'TIM_BDTRInitTypeDef', 'IWDG_WriteAccess_Enable', 'IWDG_WriteAccess_Disable',
    'IWDG_Prescaler_4', 'IWDG_Prescaler_8', 'IWDG_Prescaler_16', 'IWDG_Prescaler_32',
    'IWDG_Prescaler_64', 'IWDG_Prescaler_128', 'IWDG_Prescaler_256', 'IWDG_FLAG_PVU',
    'IWDG_FLAG_RVU', 'FLASH_BUSY', 'FLASH_ERROR_PGS', 'FLASH_ERROR_PGP',
    'FLASH_ERROR_PGA', 'FLASH_ERROR_WRP', 'FLASH_ERROR_PROGRAM',
    'FLASH_ERROR_OPERATION', 'FLASH_COMPLETE', 'FLASH_Latency_0', 'FLASH_Latency_1',
    'FLASH_Latency_2', 'FLASH_Latency_3', 'FLASH_Latency_4', 'FLASH_Latency_5',
    'FLASH_Latency_6', 'FLASH_Latency_7', 'VoltageRange_1', 'VoltageRange_2',
    'VoltageRange_3', 'VoltageRange_4', 'FLASH_Sector_0', 'FLASH_Sector_1',
    'FLASH_Sector_2', 'FLASH_Sector_3', 'FLASH_Sector_4', 'FLASH_Sector_5',
    'FLASH_Sector_6', 'FLASH_Sector_7', 'FLASH_Sector_8', 'FLASH_Sector_9',
    'FLASH_Sector_10', 'FLASH_Sector_11', 'OB_WRP_Sector_0', 'OB_WRP_Sector_1',
    'OB_WRP_Sector_2', 'OB_WRP_Sector_3', 'OB_WRP_Sector_4', 'OB_WRP_Sector_5',
    'OB_WRP_Sector_6', 'OB_WRP_Sector_7', 'OB_WRP_Sector_8', 'OB_WRP_Sector_9',
    'OB_WRP_Sector_10', 'OB_WRP_Sector_11', 'OB_WRP_Sector_All', 'OB_RDP_Level_0',
    'OB_RDP_Level_1', 'OB_IWDG_SW', 'OB_IWDG_HW', 'OB_STOP_NoRST', 'OB_STOP_RST',
    'OB_STDBY_NoRST', 'OB_STDBY_RST', 'OB_BOR_LEVEL3', 'OB_BOR_LEVEL2', 'OB_BOR_LEVEL1',
    'OB_BOR_OFF', 'FLASH_IT_EOP', 'FLASH_IT_ERR', 'FLASH_FLAG_EOP', 'FLASH_FLAG_OPERR',
    'FLASH_FLAG_WRPERR', 'FLASH_FLAG_PGAERR', 'FLASH_FLAG_PGPERR', 'FLASH_FLAG_PGSERR',
    'FLASH_FLAG_BSY', 'FLASH_PSIZE_BYTE', 'FLASH_PSIZE_HALF_WORD', 'FLASH_PSIZE_WORD',
    'FLASH_PSIZE_DOUBLE_WORD', 'CR_PSIZE_MASK', 'RDP_KEY', 'FLASH_KEY1', 'FLASH_KEY2',
    'FLASH_OPT_KEY1', 'FLASH_OPT_KEY2', 'ACR_BYTE0_ADDRESS', 'OPTCR_BYTE0_ADDRESS',
    'OPTCR_BYTE1_ADDRESS', 'OPTCR_BYTE2_ADDRESS', 'PWR_PVDLevel_0', 'PWR_PVDLevel_1',
    'PWR_PVDLevel_2', 'PWR_PVDLevel_3', 'PWR_PVDLevel_4', 'PWR_PVDLevel_5',
    'PWR_PVDLevel_6', 'PWR_PVDLevel_7', 'PWR_Regulator_ON', 'PWR_Regulator_LowPower',
    'PWR_STOPEntry_WFI', 'PWR_STOPEntry_WFE', 'PWR_Regulator_Voltage_Scale1',
    'PWR_Regulator_Voltage_Scale2', 'PWR_FLAG_WU', 'PWR_FLAG_SB', 'PWR_FLAG_PVDO',
    'PWR_FLAG_BRR', 'PWR_FLAG_VOSRDY', 'PWR_FLAG_REGRDY', 'GPIO_Mode_IN',
    'GPIO_Mode_OUT', 'GPIO_Mode_AF', 'GPIO_Mode_AN', 'GPIO_OType_PP', 'GPIO_OType_OD',
    'GPIO_Speed_2MHz', 'GPIO_Speed_25MHz', 'GPIO_Speed_50MHz', 'GPIO_Speed_100MHz',
    'GPIO_PuPd_NOPULL', 'GPIO_PuPd_UP', 'GPIO_PuPd_DOWN', 'Bit_RESET', 'Bit_SET',
    'GPIO_Pin_0', 'GPIO_Pin_1', 'GPIO_Pin_2', 'GPIO_Pin_3', 'GPIO_Pin_4', 'GPIO_Pin_5',
    'GPIO_Pin_6', 'GPIO_Pin_7', 'GPIO_Pin_8', 'GPIO_Pin_9', 'GPIO_Pin_10',
    'GPIO_Pin_11', 'GPIO_Pin_12', 'GPIO_Pin_13', 'GPIO_Pin_14', 'GPIO_Pin_15',
    'GPIO_Pin_All', 'GPIO_PinSource0', 'GPIO_PinSource1', 'GPIO_PinSource2',
    'GPIO_PinSource3', 'GPIO_PinSource4', 'GPIO_PinSource5', 'GPIO_PinSource6',
    'GPIO_PinSource7', 'GPIO_PinSource8', 'GPIO_PinSource9', 'GPIO_PinSource10',
    'GPIO_PinSource11', 'GPIO_PinSource12', 'GPIO_PinSource13', 'GPIO_PinSource14',
    'GPIO_PinSource15', 'GPIO_AF_RTC_50Hz', 'GPIO_AF_MCO', 'GPIO_AF_TAMPER',
    'GPIO_AF_SWJ', 'GPIO_AF_TRACE', 'GPIO_AF_TIM1', 'GPIO_AF_TIM2', 'GPIO_AF_TIM3',
    'GPIO_AF_TIM4', 'GPIO_AF_TIM5', 'GPIO_AF_TIM8', 'GPIO_AF_TIM9', 'GPIO_AF_TIM10',
    'GPIO_AF_TIM11', 'GPIO_AF_I2C1', 'GPIO_AF_I2C2', 'GPIO_AF_I2C3', 'GPIO_AF_SPI1',
    'GPIO_AF_SPI2', 'GPIO_AF_SPI3', 'GPIO_AF_USART1', 'GPIO_AF_USART2',
    'GPIO_AF_USART3', 'GPIO_AF_I2S3ext', 'GPIO_AF_UART4', 'GPIO_AF_UART5',
    'GPIO_AF_USART6', 'GPIO_AF_CAN1', 'GPIO_AF_CAN2', 'GPIO_AF_TIM12', 'GPIO_AF_TIM13',
    'GPIO_AF_TIM14', 'GPIO_AF_OTG_FS', 'GPIO_AF_OTG_HS', 'GPIO_AF_ETH', 'GPIO_AF_FSMC',
    'GPIO_AF_OTG_HS_FS', 'GPIO_AF_SDIO', 'GPIO_AF_DCMI', 'GPIO_AF_EVENTOUT',
    'GPIO_Mode_AIN', 'GPIO_AF_OTG1_FS', 'GPIO_AF_OTG2_HS', 'GPIO_AF_OTG2_FS',
    'GPIO_InitTypeDef', 'ADC_Mode_Independent', 'ADC_DualMode_RegSimult_InjecSimult',
    'ADC_DualMode_RegSimult_AlterTrig', 'ADC_DualMode_InjecSimult',
    'ADC_DualMode_RegSimult', 'ADC_DualMode_Interl', 'ADC_DualMode_AlterTrig',
    'ADC_TripleMode_RegSimult_InjecSimult', 'ADC_TripleMode_RegSimult_AlterTrig',
    'ADC_TripleMode_InjecSimult', 'ADC_TripleMode_RegSimult', 'ADC_TripleMode_Interl',
    'ADC_TripleMode_AlterTrig', 'ADC_Prescaler_Div2', 'ADC_Prescaler_Div4',
    'ADC_Prescaler_Div6', 'ADC_Prescaler_Div8', 'ADC_DMAAccessMode_Disabled',
    'ADC_DMAAccessMode_1', 'ADC_DMAAccessMode_2', 'ADC_DMAAccessMode_3',
    'ADC_TwoSamplingDelay_5Cycles', 'ADC_TwoSamplingDelay_6Cycles',
    'ADC_TwoSamplingDelay_7Cycles', 'ADC_TwoSamplingDelay_8Cycles',
    'ADC_TwoSamplingDelay_9Cycles', 'ADC_TwoSamplingDelay_10Cycles',
    'ADC_TwoSamplingDelay_11Cycles', 'ADC_TwoSamplingDelay_12Cycles',
    'ADC_TwoSamplingDelay_13Cycles', 'ADC_TwoSamplingDelay_14Cycles',
    'ADC_TwoSamplingDelay_15Cycles', 'ADC_TwoSamplingDelay_16Cycles',
    'ADC_TwoSamplingDelay_17Cycles', 'ADC_TwoSamplingDelay_18Cycles',
    'ADC_TwoSamplingDelay_19Cycles', 'ADC_TwoSamplingDelay_20Cycles',
    'ADC_Resolution_12b', 'ADC_Resolution_10b', 'ADC_Resolution_8b',
    'ADC_Resolution_6b', 'ADC_ExternalTrigConvEdge_None',
    'ADC_ExternalTrigConvEdge_Rising', 'ADC_ExternalTrigConvEdge_Falling',
    'ADC_ExternalTrigConvEdge_RisingFalling', 'ADC_ExternalTrigConv_T1_CC1',
    'ADC_ExternalTrigConv_T1_CC2', 'ADC_ExternalTrigConv_T1_CC3',
    'ADC_ExternalTrigConv_T2_CC2', 'ADC_ExternalTrigConv_T2_CC3',
    'ADC_ExternalTrigConv_T2_CC4', 'ADC_ExternalTrigConv_T2_TRGO',
    'ADC_ExternalTrigConv_T3_CC1', 'ADC_ExternalTrigConv_T3_TRGO',
    'ADC_ExternalTrigConv_T4_CC4', 'ADC_ExternalTrigConv_T5_CC1',
    'ADC_ExternalTrigConv_T5_CC2', 'ADC_ExternalTrigConv_T5_CC3',
    'ADC_ExternalTrigConv_T8_CC1', 'ADC_ExternalTrigConv_T8_TRGO',
    'ADC_ExternalTrigConv_Ext_IT11', 'ADC_DataAlign_Right', 'ADC_DataAlign_Left',
    'ADC_Channel_0', 'ADC_Channel_1', 'ADC_Channel_2', 'ADC_Channel_3', 'ADC_Channel_4',
    'ADC_Channel_5', 'ADC_Channel_6', 'ADC_Channel_7', 'ADC_Channel_8', 'ADC_Channel_9',
    'ADC_Channel_10', 'ADC_Channel_11', 'ADC_Channel_12', 'ADC_Channel_13',
    'ADC_Channel_14', 'ADC_Channel_15', 'ADC_Channel_16', 'ADC_Channel_17',
    'ADC_Channel_18', 'ADC_Channel_TempSensor', 'ADC_Channel_Vrefint',
    'ADC_Channel_Vbat', 'ADC_SampleTime_3Cycles', 'ADC_SampleTime_15Cycles',
    'ADC_SampleTime_28Cycles', 'ADC_SampleTime_56Cycles', 'ADC_SampleTime_84Cycles',
    'ADC_SampleTime_112Cycles', 'ADC_SampleTime_144Cycles', 'ADC_SampleTime_480Cycles',
    'ADC_ExternalTrigInjecConvEdge_None', 'ADC_ExternalTrigInjecConvEdge_Rising',
    'ADC_ExternalTrigInjecConvEdge_Falling',
    'ADC_ExternalTrigInjecConvEdge_RisingFalling', 'ADC_ExternalTrigInjecConv_T1_CC4',
    'ADC_ExternalTrigInjecConv_T1_TRGO', 'ADC_ExternalTrigInjecConv_T2_CC1',
    'ADC_ExternalTrigInjecConv_T2_TRGO', 'ADC_ExternalTrigInjecConv_T3_CC2',
    'ADC_ExternalTrigInjecConv_T3_CC4', 'ADC_ExternalTrigInjecConv_T4_CC1',
    'ADC_ExternalTrigInjecConv_T4_CC2', 'ADC_ExternalTrigInjecConv_T4_CC3',
    'ADC_ExternalTrigInjecConv_T4_TRGO', 'ADC_ExternalTrigInjecConv_T5_CC4',
    'ADC_ExternalTrigInjecConv_T5_TRGO', 'ADC_ExternalTrigInjecConv_T8_CC2',
    'ADC_ExternalTrigInjecConv_T8_CC3', 'ADC_ExternalTrigInjecConv_T8_CC4',
    'ADC_ExternalTrigInjecConv_Ext_IT15', 'ADC_InjectedChannel_1',
    'ADC_InjectedChannel_2', 'ADC_InjectedChannel_3', 'ADC_InjectedChannel_4',
    'ADC_AnalogWatchdog_SingleRegEnable', 'ADC_AnalogWatchdog_SingleInjecEnable',
    'ADC_AnalogWatchdog_SingleRegOrInjecEnable', 'ADC_AnalogWatchdog_AllRegEnable',
    'ADC_AnalogWatchdog_AllInjecEnable', 'ADC_AnalogWatchdog_AllRegAllInjecEnable',
    'ADC_AnalogWatchdog_None', 'ADC_IT_EOC', 'ADC_IT_AWD', 'ADC_IT_JEOC', 'ADC_IT_OVR',
    'ADC_FLAG_AWD', 'ADC_FLAG_EOC', 'ADC_FLAG_JEOC', 'ADC_FLAG_JSTRT', 'ADC_FLAG_STRT',
    'ADC_FLAG_OVR', 'ADC_InitTypeDef', 'ADC_CommonInitTypeDef', 'WWDG_Prescaler_1',
    'WWDG_Prescaler_2', 'WWDG_Prescaler_4', 'WWDG_Prescaler_8', 'USART_WordLength_8b',
    'USART_WordLength_9b', 'USART_StopBits_1', 'USART_StopBits_0_5', 'USART_StopBits_2',
    'USART_StopBits_1_5', 'USART_Parity_No', 'USART_Parity_Even', 'USART_Parity_Odd',
    'USART_Mode_Rx', 'USART_Mode_Tx', 'USART_HardwareFlowControl_None',
    'USART_HardwareFlowControl_RTS', 'USART_HardwareFlowControl_CTS',
    'USART_HardwareFlowControl_RTS_CTS', 'USART_Clock_Disable', 'USART_Clock_Enable',
    'USART_CPOL_Low', 'USART_CPOL_High', 'USART_CPHA_1Edge', 'USART_CPHA_2Edge',
    'USART_LastBit_Disable', 'USART_LastBit_Enable', 'USART_IT_PE', 'USART_IT_TXE',
    'USART_IT_TC', 'USART_IT_RXNE', 'USART_IT_ORE_RX', 'USART_IT_IDLE', 'USART_IT_LBD',
    'USART_IT_CTS', 'USART_IT_ERR', 'USART_IT_ORE_ER', 'USART_IT_NE', 'USART_IT_FE',
    'USART_IT_ORE', 'USART_DMAReq_Tx', 'USART_DMAReq_Rx', 'USART_WakeUp_IdleLine',
    'USART_WakeUp_AddressMark', 'USART_LINBreakDetectLength_10b',
    'USART_LINBreakDetectLength_11b', 'USART_IrDAMode_LowPower',
    'USART_IrDAMode_Normal', 'USART_FLAG_CTS', 'USART_FLAG_LBD', 'USART_FLAG_TXE',
    'USART_FLAG_TC', 'USART_FLAG_RXNE', 'USART_FLAG_IDLE', 'USART_FLAG_ORE',
    'USART_FLAG_NE', 'USART_FLAG_FE', 'USART_FLAG_PE', 'USART_InitTypeDef',
    'USART_ClockInitTypeDef', 'DCMI_CaptureMode_Continuous',
    'DCMI_CaptureMode_SnapShot', 'DCMI_SynchroMode_Hardware',
    'DCMI_SynchroMode_Embedded', 'DCMI_PCKPolarity_Falling', 'DCMI_PCKPolarity_Rising',
    'DCMI_VSPolarity_Low', 'DCMI_VSPolarity_High', 'DCMI_HSPolarity_Low',
    'DCMI_HSPolarity_High', 'DCMI_CaptureRate_All_Frame', 'DCMI_CaptureRate_1of2_Frame',
    'DCMI_CaptureRate_1of4_Frame', 'DCMI_ExtendedDataMode_8b',
    'DCMI_ExtendedDataMode_10b', 'DCMI_ExtendedDataMode_12b',
    'DCMI_ExtendedDataMode_14b', 'DCMI_IT_FRAME', 'DCMI_IT_OVF', 'DCMI_IT_ERR',
    'DCMI_IT_VSYNC', 'DCMI_IT_LINE', 'DCMI_FLAG_HSYNC', 'DCMI_FLAG_VSYNC',
    'DCMI_FLAG_FNE', 'DCMI_FLAG_FRAMERI', 'DCMI_FLAG_OVFRI', 'DCMI_FLAG_ERRRI',
    'DCMI_FLAG_VSYNCRI', 'DCMI_FLAG_LINERI', 'DCMI_FLAG_FRAMEMI', 'DCMI_FLAG_OVFMI',
    'DCMI_FLAG_ERRMI', 'DCMI_FLAG_VSYNCMI', 'DCMI_FLAG_LINEMI', 'DCMI_InitTypeDef',
    'DCMI_CROPInitTypeDef', 'DCMI_CodesInitTypeDef', 'EXTI_Mode_Interrupt',
    'EXTI_Mode_Event', 'EXTI_Trigger_Rising', 'EXTI_Trigger_Falling',
    'EXTI_Trigger_Rising_Falling', 'EXTI_Line0', 'EXTI_Line1', 'EXTI_Line2',
    'EXTI_Line3', 'EXTI_Line4', 'EXTI_Line5', 'EXTI_Line6', 'EXTI_Line7', 'EXTI_Line8',
    'EXTI_Line9', 'EXTI_Line10', 'EXTI_Line11', 'EXTI_Line12', 'EXTI_Line13',
    'EXTI_Line14', 'EXTI_Line15', 'EXTI_Line16', 'EXTI_Line17', 'EXTI_Line18',
    'EXTI_Line19', 'EXTI_Line20', 'EXTI_Line21', 'EXTI_Line22', 'EXTI_InitTypeDef',
    'RCC_HSE_OFF', 'RCC_HSE_ON', 'RCC_HSE_Bypass', 'RCC_PLLSource_HSI',
    'RCC_PLLSource_HSE', 'RCC_SYSCLKSource_HSI', 'RCC_SYSCLKSource_HSE',
    'RCC_SYSCLKSource_PLLCLK', 'RCC_SYSCLK_Div1', 'RCC_SYSCLK_Div2', 'RCC_SYSCLK_Div4',
    'RCC_SYSCLK_Div8', 'RCC_SYSCLK_Div16', 'RCC_SYSCLK_Div64', 'RCC_SYSCLK_Div128',
    'RCC_SYSCLK_Div256', 'RCC_SYSCLK_Div512', 'RCC_HCLK_Div1', 'RCC_HCLK_Div2',
    'RCC_HCLK_Div4', 'RCC_HCLK_Div8', 'RCC_HCLK_Div16', 'RCC_IT_LSIRDY',
    'RCC_IT_LSERDY', 'RCC_IT_HSIRDY', 'RCC_IT_HSERDY', 'RCC_IT_PLLRDY',
    'RCC_IT_PLLI2SRDY', 'RCC_IT_CSS', 'RCC_LSE_OFF', 'RCC_LSE_ON', 'RCC_LSE_Bypass',
    'RCC_RTCCLKSource_LSE', 'RCC_RTCCLKSource_LSI', 'RCC_RTCCLKSource_HSE_Div2',
    'RCC_RTCCLKSource_HSE_Div3', 'RCC_RTCCLKSource_HSE_Div4',
    'RCC_RTCCLKSource_HSE_Div5', 'RCC_RTCCLKSource_HSE_Div6',
    'RCC_RTCCLKSource_HSE_Div7', 'RCC_RTCCLKSource_HSE_Div8',
    'RCC_RTCCLKSource_HSE_Div9', 'RCC_RTCCLKSource_HSE_Div10',
    'RCC_RTCCLKSource_HSE_Div11', 'RCC_RTCCLKSource_HSE_Div12',
    'RCC_RTCCLKSource_HSE_Div13', 'RCC_RTCCLKSource_HSE_Div14',
    'RCC_RTCCLKSource_HSE_Div15', 'RCC_RTCCLKSource_HSE_Div16',
    'RCC_RTCCLKSource_HSE_Div17', 'RCC_RTCCLKSource_HSE_Div18',
    'RCC_RTCCLKSource_HSE_Div19', 'RCC_RTCCLKSource_HSE_Div20',
    'RCC_RTCCLKSource_HSE_Div21', 'RCC_RTCCLKSource_HSE_Div22',
    'RCC_RTCCLKSource_HSE_Div23', 'RCC_RTCCLKSource_HSE_Div24',
    'RCC_RTCCLKSource_HSE_Div25', 'RCC_RTCCLKSource_HSE_Div26',
    'RCC_RTCCLKSource_HSE_Div27', 'RCC_RTCCLKSource_HSE_Div28',
    'RCC_RTCCLKSource_HSE_Div29', 'RCC_RTCCLKSource_HSE_Div30',
    'RCC_RTCCLKSource_HSE_Div31', 'RCC_I2S2CLKSource_PLLI2S', 'RCC_I2S2CLKSource_Ext',
    'RCC_AHB1Periph_GPIOA', 'RCC_AHB1Periph_GPIOB', 'RCC_AHB1Periph_GPIOC',
    'RCC_AHB1Periph_GPIOD', 'RCC_AHB1Periph_GPIOE', 'RCC_AHB1Periph_GPIOF',
    'RCC_AHB1Periph_GPIOG', 'RCC_AHB1Periph_GPIOH', 'RCC_AHB1Periph_GPIOI',
    'RCC_AHB1Periph_CRC', 'RCC_AHB1Periph_FLITF', 'RCC_AHB1Periph_SRAM1',
    'RCC_AHB1Periph_SRAM2', 'RCC_AHB1Periph_BKPSRAM', 'RCC_AHB1Periph_CCMDATARAMEN',
    'RCC_AHB1Periph_DMA1', 'RCC_AHB1Periph_DMA2', 'RCC_AHB1Periph_ETH_MAC',
    'RCC_AHB1Periph_ETH_MAC_Tx', 'RCC_AHB1Periph_ETH_MAC_Rx',
    'RCC_AHB1Periph_ETH_MAC_PTP', 'RCC_AHB1Periph_OTG_HS', 'RCC_AHB1Periph_OTG_HS_ULPI',
    'RCC_AHB2Periph_DCMI', 'RCC_AHB2Periph_CRYP', 'RCC_AHB2Periph_HASH',
    'RCC_AHB2Periph_RNG', 'RCC_AHB2Periph_OTG_FS', 'RCC_AHB3Periph_FSMC',
    'RCC_APB1Periph_TIM2', 'RCC_APB1Periph_TIM3', 'RCC_APB1Periph_TIM4',
    'RCC_APB1Periph_TIM5', 'RCC_APB1Periph_TIM6', 'RCC_APB1Periph_TIM7',
    'RCC_APB1Periph_TIM12', 'RCC_APB1Periph_TIM13', 'RCC_APB1Periph_TIM14',
    'RCC_APB1Periph_WWDG', 'RCC_APB1Periph_SPI2', 'RCC_APB1Periph_SPI3',
    'RCC_APB1Periph_USART2', 'RCC_APB1Periph_USART3', 'RCC_APB1Periph_UART4',
    'RCC_APB1Periph_UART5', 'RCC_APB1Periph_I2C1', 'RCC_APB1Periph_I2C2',
    'RCC_APB1Periph_I2C3', 'RCC_APB1Periph_CAN1', 'RCC_APB1Periph_CAN2',
    'RCC_APB1Periph_PWR', 'RCC_APB1Periph_DAC', 'RCC_APB2Periph_TIM1',
    'RCC_APB2Periph_TIM8', 'RCC_APB2Periph_USART1', 'RCC_APB2Periph_USART6',
    'RCC_APB2Periph_ADC', 'RCC_APB2Periph_ADC1', 'RCC_APB2Periph_ADC2',
    'RCC_APB2Periph_ADC3', 'RCC_APB2Periph_SDIO', 'RCC_APB2Periph_SPI1',
    'RCC_APB2Periph_SYSCFG', 'RCC_APB2Periph_TIM9', 'RCC_APB2Periph_TIM10',
    'RCC_APB2Periph_TIM11', 'RCC_MCO1Source_HSI', 'RCC_MCO1Source_LSE',
    'RCC_MCO1Source_HSE', 'RCC_MCO1Source_PLLCLK', 'RCC_MCO1Div_1', 'RCC_MCO1Div_2',
    'RCC_MCO1Div_3', 'RCC_MCO1Div_4', 'RCC_MCO1Div_5', 'RCC_MCO2Source_SYSCLK',
    'RCC_MCO2Source_PLLI2SCLK', 'RCC_MCO2Source_HSE', 'RCC_MCO2Source_PLLCLK',
    'RCC_MCO2Div_1', 'RCC_MCO2Div_2', 'RCC_MCO2Div_3', 'RCC_MCO2Div_4', 'RCC_MCO2Div_5',
    'RCC_FLAG_HSIRDY', 'RCC_FLAG_HSERDY', 'RCC_FLAG_PLLRDY', 'RCC_FLAG_PLLI2SRDY',
    'RCC_FLAG_LSERDY', 'RCC_FLAG_LSIRDY', 'RCC_FLAG_BORRST', 'RCC_FLAG_PINRST',
    'RCC_FLAG_PORRST', 'RCC_FLAG_SFTRST', 'RCC_FLAG_IWDGRST', 'RCC_FLAG_WWDGRST',
    'RCC_FLAG_LPWRRST', 'RCC_ClocksTypeDef', 'DMA_Channel_0', 'DMA_Channel_1',
    'DMA_Channel_2', 'DMA_Channel_3', 'DMA_Channel_4', 'DMA_Channel_5', 'DMA_Channel_6',
    'DMA_Channel_7', 'DMA_DIR_PeripheralToMemory', 'DMA_DIR_MemoryToPeripheral',
    'DMA_DIR_MemoryToMemory', 'DMA_PeripheralInc_Enable', 'DMA_PeripheralInc_Disable',
    'DMA_MemoryInc_Enable', 'DMA_MemoryInc_Disable', 'DMA_PeripheralDataSize_Byte',
    'DMA_PeripheralDataSize_HalfWord', 'DMA_PeripheralDataSize_Word',
    'DMA_MemoryDataSize_Byte', 'DMA_MemoryDataSize_HalfWord', 'DMA_MemoryDataSize_Word',
    'DMA_Mode_Normal', 'DMA_Mode_Circular', 'DMA_Priority_Low', 'DMA_Priority_Medium',
    'DMA_Priority_High', 'DMA_Priority_VeryHigh', 'DMA_FIFOMode_Disable',
    'DMA_FIFOMode_Enable', 'DMA_FIFOThreshold_1QuarterFull',
    'DMA_FIFOThreshold_HalfFull', 'DMA_FIFOThreshold_3QuartersFull',
    'DMA_FIFOThreshold_Full', 'DMA_MemoryBurst_Single', 'DMA_MemoryBurst_INC4',
    'DMA_MemoryBurst_INC8', 'DMA_MemoryBurst_INC16', 'DMA_PeripheralBurst_Single',
    'DMA_PeripheralBurst_INC4', 'DMA_PeripheralBurst_INC8', 'DMA_PeripheralBurst_INC16',
    'DMA_FIFOStatus_Less1QuarterFull', 'DMA_FIFOStatus_1QuarterFull',
    'DMA_FIFOStatus_HalfFull', 'DMA_FIFOStatus_3QuartersFull', 'DMA_FIFOStatus_Empty',
    'DMA_FIFOStatus_Full', 'DMA_FLAG_FEIF0', 'DMA_FLAG_DMEIF0', 'DMA_FLAG_TEIF0',
    'DMA_FLAG_HTIF0', 'DMA_FLAG_TCIF0', 'DMA_FLAG_FEIF1', 'DMA_FLAG_DMEIF1',
    'DMA_FLAG_TEIF1', 'DMA_FLAG_HTIF1', 'DMA_FLAG_TCIF1', 'DMA_FLAG_FEIF2',
    'DMA_FLAG_DMEIF2', 'DMA_FLAG_TEIF2', 'DMA_FLAG_HTIF2', 'DMA_FLAG_TCIF2',
    'DMA_FLAG_FEIF3', 'DMA_FLAG_DMEIF3', 'DMA_FLAG_TEIF3', 'DMA_FLAG_HTIF3',
    'DMA_FLAG_TCIF3', 'DMA_FLAG_FEIF4', 'DMA_FLAG_DMEIF4', 'DMA_FLAG_TEIF4',
    'DMA_FLAG_HTIF4', 'DMA_FLAG_TCIF4', 'DMA_FLAG_FEIF5', 'DMA_FLAG_DMEIF5',
    'DMA_FLAG_TEIF5', 'DMA_FLAG_HTIF5', 'DMA_FLAG_TCIF5', 'DMA_FLAG_FEIF6',
    'DMA_FLAG_DMEIF6', 'DMA_FLAG_TEIF6', 'DMA_FLAG_HTIF6', 'DMA_FLAG_TCIF6',
    'DMA_FLAG_FEIF7', 'DMA_FLAG_DMEIF7', 'DMA_FLAG_TEIF7', 'DMA_FLAG_HTIF7',
    'DMA_FLAG_TCIF7', 'DMA_IT_TC', 'DMA_IT_HT', 'DMA_IT_TE', 'DMA_IT_DME', 'DMA_IT_FE',
    'DMA_IT_FEIF0', 'DMA_IT_DMEIF0', 'DMA_IT_TEIF0', 'DMA_IT_HTIF0', 'DMA_IT_TCIF0',
    'DMA_IT_FEIF1', 'DMA_IT_DMEIF1', 'DMA_IT_TEIF1', 'DMA_IT_HTIF1', 'DMA_IT_TCIF1',
    'DMA_IT_FEIF2', 'DMA_IT_DMEIF2', 'DMA_IT_TEIF2', 'DMA_IT_HTIF2', 'DMA_IT_TCIF2',
    'DMA_IT_FEIF3', 'DMA_IT_DMEIF3', 'DMA_IT_TEIF3', 'DMA_IT_HTIF3', 'DMA_IT_TCIF3',
    'DMA_IT_FEIF4', 'DMA_IT_DMEIF4', 'DMA_IT_TEIF4', 'DMA_IT_HTIF4', 'DMA_IT_TCIF4',
    'DMA_IT_FEIF5', 'DMA_IT_DMEIF5', 'DMA_IT_TEIF5', 'DMA_IT_HTIF5', 'DMA_IT_TCIF5',
    'DMA_IT_FEIF6', 'DMA_IT_DMEIF6', 'DMA_IT_TEIF6', 'DMA_IT_HTIF6', 'DMA_IT_TCIF6',
    'DMA_IT_FEIF7', 'DMA_IT_DMEIF7', 'DMA_IT_TEIF7', 'DMA_IT_HTIF7', 'DMA_IT_TCIF7',
    'DMA_PINCOS_Psize', 'DMA_PINCOS_WordAligned', 'DMA_FlowCtrl_Memory',
    'DMA_FlowCtrl_Peripheral', 'DMA_Memory_0', 'DMA_Memory_1', 'DMA_InitTypeDef',
    'HASH_AlgoSelection_SHA1', 'HASH_AlgoSelection_MD5', 'HASH_AlgoMode_HASH',
    'HASH_AlgoMode_HMAC', 'HASH_DataType_32b', 'HASH_DataType_16b', 'HASH_DataType_8b',
    'HASH_DataType_1b', 'HASH_HMACKeyType_ShortKey', 'HASH_HMACKeyType_LongKey',
    'HASH_IT_DINI', 'HASH_IT_DCI', 'HASH_FLAG_DINIS', 'HASH_FLAG_DCIS',
    'HASH_FLAG_DMAS', 'HASH_FLAG_BUSY', 'HASH_FLAG_DINNE', 'HASH_InitTypeDef',
    'FSMC_Bank1_NORSRAM1', 'FSMC_Bank1_NORSRAM2', 'FSMC_Bank1_NORSRAM3',
    'FSMC_Bank1_NORSRAM4', 'FSMC_Bank2_NAND', 'FSMC_Bank3_NAND', 'FSMC_Bank4_PCCARD',
    'FSMC_DataAddressMux_Disable', 'FSMC_DataAddressMux_Enable', 'FSMC_MemoryType_SRAM',
    'FSMC_MemoryType_PSRAM', 'FSMC_MemoryType_NOR', 'FSMC_MemoryDataWidth_8b',
    'FSMC_MemoryDataWidth_16b', 'FSMC_BurstAccessMode_Disable',
    'FSMC_BurstAccessMode_Enable', 'FSMC_AsynchronousWait_Disable',
    'FSMC_AsynchronousWait_Enable', 'FSMC_WaitSignalPolarity_Low',
    'FSMC_WaitSignalPolarity_High', 'FSMC_WrapMode_Disable', 'FSMC_WrapMode_Enable',
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
    'FSMC_NAND_PCCARDTimingInitTypeDef', 'SPI_Direction_2Lines_FullDuplex',
    'SPI_Direction_2Lines_RxOnly', 'SPI_Direction_1Line_Rx', 'SPI_Direction_1Line_Tx',
    'SPI_Mode_Master', 'SPI_Mode_Slave', 'SPI_DataSize_16b', 'SPI_DataSize_8b',
    'SPI_CPOL_Low', 'SPI_CPOL_High', 'SPI_CPHA_1Edge', 'SPI_CPHA_2Edge', 'SPI_NSS_Soft',
    'SPI_NSS_Hard', 'SPI_BaudRatePrescaler_2', 'SPI_BaudRatePrescaler_4',
    'SPI_BaudRatePrescaler_8', 'SPI_BaudRatePrescaler_16', 'SPI_BaudRatePrescaler_32',
    'SPI_BaudRatePrescaler_64', 'SPI_BaudRatePrescaler_128',
    'SPI_BaudRatePrescaler_256', 'SPI_FirstBit_MSB', 'SPI_FirstBit_LSB',
    'I2S_Mode_SlaveTx', 'I2S_Mode_SlaveRx', 'I2S_Mode_MasterTx', 'I2S_Mode_MasterRx',
    'I2S_Standard_Phillips', 'I2S_Standard_MSB', 'I2S_Standard_LSB',
    'I2S_Standard_PCMShort', 'I2S_Standard_PCMLong', 'I2S_DataFormat_16b',
    'I2S_DataFormat_16bextended', 'I2S_DataFormat_24b', 'I2S_DataFormat_32b',
    'I2S_MCLKOutput_Enable', 'I2S_MCLKOutput_Disable', 'I2S_AudioFreq_192k',
    'I2S_AudioFreq_96k', 'I2S_AudioFreq_48k', 'I2S_AudioFreq_44k', 'I2S_AudioFreq_32k',
    'I2S_AudioFreq_22k', 'I2S_AudioFreq_16k', 'I2S_AudioFreq_11k', 'I2S_AudioFreq_8k',
    'I2S_AudioFreq_Default', 'I2S_CPOL_Low', 'I2S_CPOL_High', 'SPI_I2S_DMAReq_Tx',
    'SPI_I2S_DMAReq_Rx', 'SPI_NSSInternalSoft_Set', 'SPI_NSSInternalSoft_Reset',
    'SPI_CRC_Tx', 'SPI_CRC_Rx', 'SPI_Direction_Rx', 'SPI_Direction_Tx',
    'SPI_I2S_IT_TXE', 'SPI_I2S_IT_RXNE', 'SPI_I2S_IT_ERR', 'I2S_IT_UDR',
    'SPI_I2S_IT_TIFRFE', 'SPI_I2S_IT_OVR', 'SPI_IT_MODF', 'SPI_IT_CRCERR',
    'SPI_I2S_FLAG_RXNE', 'SPI_I2S_FLAG_TXE', 'I2S_FLAG_CHSIDE', 'I2S_FLAG_UDR',
    'SPI_FLAG_CRCERR', 'SPI_FLAG_MODF', 'SPI_I2S_FLAG_OVR', 'SPI_I2S_FLAG_BSY',
    'SPI_I2S_FLAG_TIFRFE', 'SPI_DMAReq_Tx', 'SPI_DMAReq_Rx', 'SPI_IT_TXE',
    'SPI_IT_RXNE', 'SPI_IT_ERR', 'SPI_IT_OVR', 'SPI_FLAG_RXNE', 'SPI_FLAG_TXE',
    'SPI_FLAG_OVR', 'SPI_FLAG_BSY', 'SPI_InitTypeDef', 'I2S_InitTypeDef',
    'CRYP_AlgoDir_Encrypt', 'CRYP_AlgoDir_Decrypt', 'CRYP_AlgoMode_TDES_ECB',
    'CRYP_AlgoMode_TDES_CBC', 'CRYP_AlgoMode_DES_ECB', 'CRYP_AlgoMode_DES_CBC',
    'CRYP_AlgoMode_AES_ECB', 'CRYP_AlgoMode_AES_CBC', 'CRYP_AlgoMode_AES_CTR',
    'CRYP_AlgoMode_AES_Key', 'CRYP_DataType_32b', 'CRYP_DataType_16b',
    'CRYP_DataType_8b', 'CRYP_DataType_1b', 'CRYP_KeySize_128b', 'CRYP_KeySize_192b',
    'CRYP_KeySize_256b', 'CRYP_FLAG_BUSY', 'CRYP_FLAG_IFEM', 'CRYP_FLAG_IFNF',
    'CRYP_FLAG_INRIS', 'CRYP_FLAG_OFNE', 'CRYP_FLAG_OFFU', 'CRYP_FLAG_OUTRIS',
    'CRYP_IT_INI', 'CRYP_IT_OUTI', 'MODE_ENCRYPT', 'MODE_DECRYPT', 'CRYP_DMAReq_DataIN',
    'CRYP_DMAReq_DataOUT', 'CRYP_InitTypeDef', 'CRYP_KeyInitTypeDef',
    'CRYP_IVInitTypeDef', 'CRYP_Context', 'NVIC_VectTab_RAM', 'NVIC_VectTab_FLASH',
    'NVIC_LP_SEVONPEND', 'NVIC_LP_SLEEPDEEP', 'NVIC_LP_SLEEPONEXIT',
    'NVIC_PriorityGroup_0', 'NVIC_PriorityGroup_1', 'NVIC_PriorityGroup_2',
    'NVIC_PriorityGroup_3', 'NVIC_PriorityGroup_4', 'SysTick_CLKSource_HCLK_Div8',
    'SysTick_CLKSource_HCLK', 'NVIC_InitTypeDef', 'DBGMCU_SLEEP', 'DBGMCU_STOP',
    'DBGMCU_STANDBY', 'DBGMCU_TIM2_STOP', 'DBGMCU_TIM3_STOP', 'DBGMCU_TIM4_STOP',
    'DBGMCU_TIM5_STOP', 'DBGMCU_TIM6_STOP', 'DBGMCU_TIM7_STOP', 'DBGMCU_TIM12_STOP',
    'DBGMCU_TIM13_STOP', 'DBGMCU_TIM14_STOP', 'DBGMCU_RTC_STOP', 'DBGMCU_WWDG_STOP',
    'DBGMCU_IWDG_STOP', 'DBGMCU_I2C1_SMBUS_TIMEOUT', 'DBGMCU_I2C2_SMBUS_TIMEOUT',
    'DBGMCU_I2C3_SMBUS_TIMEOUT', 'DBGMCU_CAN1_STOP', 'DBGMCU_CAN2_STOP',
    'DBGMCU_TIM1_STOP', 'DBGMCU_TIM8_STOP', 'DBGMCU_TIM9_STOP', 'DBGMCU_TIM10_STOP',
    'DBGMCU_TIM11_STOP', 'EXTI_PortSourceGPIOA', 'EXTI_PortSourceGPIOB',
    'EXTI_PortSourceGPIOC', 'EXTI_PortSourceGPIOD', 'EXTI_PortSourceGPIOE',
    'EXTI_PortSourceGPIOF', 'EXTI_PortSourceGPIOG', 'EXTI_PortSourceGPIOH',
    'EXTI_PortSourceGPIOI', 'EXTI_PinSource0', 'EXTI_PinSource1', 'EXTI_PinSource2',
    'EXTI_PinSource3', 'EXTI_PinSource4', 'EXTI_PinSource5', 'EXTI_PinSource6',
    'EXTI_PinSource7', 'EXTI_PinSource8', 'EXTI_PinSource9', 'EXTI_PinSource10',
    'EXTI_PinSource11', 'EXTI_PinSource12', 'EXTI_PinSource13', 'EXTI_PinSource14',
    'EXTI_PinSource15', 'SYSCFG_MemoryRemap_Flash', 'SYSCFG_MemoryRemap_SystemFlash',
    'SYSCFG_MemoryRemap_FSMC', 'SYSCFG_MemoryRemap_SRAM',
    'SYSCFG_ETH_MediaInterface_MII', 'SYSCFG_ETH_MediaInterface_RMII', 'I2C_Mode_I2C',
    'I2C_Mode_SMBusDevice', 'I2C_Mode_SMBusHost', 'I2C_DutyCycle_16_9',
    'I2C_DutyCycle_2', 'I2C_Ack_Enable', 'I2C_Ack_Disable', 'I2C_Direction_Transmitter',
    'I2C_Direction_Receiver', 'I2C_AcknowledgedAddress_7bit',
    'I2C_AcknowledgedAddress_10bit', 'I2C_Register_CR1', 'I2C_Register_CR2',
    'I2C_Register_OAR1', 'I2C_Register_OAR2', 'I2C_Register_DR', 'I2C_Register_SR1',
    'I2C_Register_SR2', 'I2C_Register_CCR', 'I2C_Register_TRISE',
    'I2C_NACKPosition_Next', 'I2C_NACKPosition_Current', 'I2C_SMBusAlert_Low',
    'I2C_SMBusAlert_High', 'I2C_PECPosition_Next', 'I2C_PECPosition_Current',
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
    'I2C_InitTypeDef', 'DAC_Trigger_None', 'DAC_Trigger_T2_TRGO', 'DAC_Trigger_T4_TRGO',
    'DAC_Trigger_T5_TRGO', 'DAC_Trigger_T6_TRGO', 'DAC_Trigger_T7_TRGO',
    'DAC_Trigger_T8_TRGO', 'DAC_Trigger_Ext_IT9', 'DAC_Trigger_Software',
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
    'DAC_FLAG_DMAUDR', 'DAC_InitTypeDef', 'RTC_HourFormat_24', 'RTC_HourFormat_12',
    'RTC_H12_AM', 'RTC_H12_PM', 'RTC_Month_January', 'RTC_Month_February',
    'RTC_Month_March', 'RTC_Month_April', 'RTC_Month_May', 'RTC_Month_June',
    'RTC_Month_July', 'RTC_Month_August', 'RTC_Month_September', 'RTC_Month_October',
    'RTC_Month_November', 'RTC_Month_December', 'RTC_Weekday_Monday',
    'RTC_Weekday_Tuesday', 'RTC_Weekday_Wednesday', 'RTC_Weekday_Thursday',
    'RTC_Weekday_Friday', 'RTC_Weekday_Saturday', 'RTC_Weekday_Sunday',
    'RTC_AlarmDateWeekDaySel_Date', 'RTC_AlarmDateWeekDaySel_WeekDay',
    'RTC_AlarmMask_None', 'RTC_AlarmMask_DateWeekDay', 'RTC_AlarmMask_Hours',
    'RTC_AlarmMask_Minutes', 'RTC_AlarmMask_Seconds', 'RTC_AlarmMask_All',
    'RTC_Alarm_A', 'RTC_Alarm_B', 'RTC_AlarmSubSecondMask_All',
    'RTC_AlarmSubSecondMask_SS14_1', 'RTC_AlarmSubSecondMask_SS14_2',
    'RTC_AlarmSubSecondMask_SS14_3', 'RTC_AlarmSubSecondMask_SS14_4',
    'RTC_AlarmSubSecondMask_SS14_5', 'RTC_AlarmSubSecondMask_SS14_6',
    'RTC_AlarmSubSecondMask_SS14_7', 'RTC_AlarmSubSecondMask_SS14_8',
    'RTC_AlarmSubSecondMask_SS14_9', 'RTC_AlarmSubSecondMask_SS14_10',
    'RTC_AlarmSubSecondMask_SS14_11', 'RTC_AlarmSubSecondMask_SS14_12',
    'RTC_AlarmSubSecondMask_SS14_13', 'RTC_AlarmSubSecondMask_SS14',
    'RTC_AlarmSubSecondMask_None', 'RTC_WakeUpClock_RTCCLK_Div16',
    'RTC_WakeUpClock_RTCCLK_Div8', 'RTC_WakeUpClock_RTCCLK_Div4',
    'RTC_WakeUpClock_RTCCLK_Div2', 'RTC_WakeUpClock_CK_SPRE_16bits',
    'RTC_WakeUpClock_CK_SPRE_17bits', 'RTC_TimeStampEdge_Rising',
    'RTC_TimeStampEdge_Falling', 'RTC_Output_Disable', 'RTC_Output_AlarmA',
    'RTC_Output_AlarmB', 'RTC_Output_WakeUp', 'RTC_OutputPolarity_High',
    'RTC_OutputPolarity_Low', 'RTC_CalibSign_Positive', 'RTC_CalibSign_Negative',
    'RTC_CalibOutput_512Hz', 'RTC_CalibOutput_1Hz', 'RTC_SmoothCalibPeriod_32sec',
    'RTC_SmoothCalibPeriod_16sec', 'RTC_SmoothCalibPeriod_8sec',
    'RTC_SmoothCalibPlusPulses_Set', 'RTC_SmoothCalibPlusPulses_Reset',
    'RTC_DayLightSaving_SUB1H', 'RTC_DayLightSaving_ADD1H', 'RTC_StoreOperation_Reset',
    'RTC_StoreOperation_Set', 'RTC_TamperTrigger_RisingEdge',
    'RTC_TamperTrigger_FallingEdge', 'RTC_TamperTrigger_LowLevel',
    'RTC_TamperTrigger_HighLevel', 'RTC_TamperFilter_Disable',
    'RTC_TamperFilter_2Sample', 'RTC_TamperFilter_4Sample', 'RTC_TamperFilter_8Sample',
    'RTC_TamperSamplingFreq_RTCCLK_Div32768', 'RTC_TamperSamplingFreq_RTCCLK_Div16384',
    'RTC_TamperSamplingFreq_RTCCLK_Div8192', 'RTC_TamperSamplingFreq_RTCCLK_Div4096',
    'RTC_TamperSamplingFreq_RTCCLK_Div2048', 'RTC_TamperSamplingFreq_RTCCLK_Div1024',
    'RTC_TamperSamplingFreq_RTCCLK_Div512', 'RTC_TamperSamplingFreq_RTCCLK_Div256',
    'RTC_TamperPrechargeDuration_1RTCCLK', 'RTC_TamperPrechargeDuration_2RTCCLK',
    'RTC_TamperPrechargeDuration_4RTCCLK', 'RTC_TamperPrechargeDuration_8RTCCLK',
    'RTC_Tamper_1', 'RTC_TamperPin_PC13', 'RTC_TamperPin_PI8', 'RTC_TimeStampPin_PC13',
    'RTC_TimeStampPin_PI8', 'RTC_OutputType_OpenDrain', 'RTC_OutputType_PushPull',
    'RTC_ShiftAdd1S_Reset', 'RTC_ShiftAdd1S_Set', 'RTC_BKP_DR0', 'RTC_BKP_DR1',
    'RTC_BKP_DR2', 'RTC_BKP_DR3', 'RTC_BKP_DR4', 'RTC_BKP_DR5', 'RTC_BKP_DR6',
    'RTC_BKP_DR7', 'RTC_BKP_DR8', 'RTC_BKP_DR9', 'RTC_BKP_DR10', 'RTC_BKP_DR11',
    'RTC_BKP_DR12', 'RTC_BKP_DR13', 'RTC_BKP_DR14', 'RTC_BKP_DR15', 'RTC_BKP_DR16',
    'RTC_BKP_DR17', 'RTC_BKP_DR18', 'RTC_BKP_DR19', 'RTC_Format_BIN', 'RTC_Format_BCD',
    'RTC_FLAG_RECALPF', 'RTC_FLAG_TAMP1F', 'RTC_FLAG_TSOVF', 'RTC_FLAG_TSF',
    'RTC_FLAG_WUTF', 'RTC_FLAG_ALRBF', 'RTC_FLAG_ALRAF', 'RTC_FLAG_INITF',
    'RTC_FLAG_RSF', 'RTC_FLAG_INITS', 'RTC_FLAG_SHPF', 'RTC_FLAG_WUTWF',
    'RTC_FLAG_ALRBWF', 'RTC_FLAG_ALRAWF', 'RTC_IT_TS', 'RTC_IT_WUT', 'RTC_IT_ALRB',
    'RTC_IT_ALRA', 'RTC_IT_TAMP', 'RTC_IT_TAMP1', 'RTC_InitTypeDef', 'RTC_TimeTypeDef',
    'RTC_DateTypeDef', 'SDIO_ClockEdge_Rising', 'SDIO_ClockEdge_Falling',
    'SDIO_ClockBypass_Disable', 'SDIO_ClockBypass_Enable',
    'SDIO_ClockPowerSave_Disable', 'SDIO_ClockPowerSave_Enable', 'SDIO_BusWide_1b',
    'SDIO_BusWide_4b', 'SDIO_BusWide_8b', 'SDIO_HardwareFlowControl_Disable',
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
    'SDIO_CmdInitTypeDef', 'SDIO_DataInitTypeDef', 'RNG_FLAG_DRDY', 'RNG_FLAG_CECS',
    'RNG_FLAG_SECS', 'RNG_IT_CEI', 'RNG_IT_SEI', 'CAN_InitStatus_Failed',
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
    'CAN_FilterInitTypeDef', 'NonMaskableInt_IRQn', 'MemoryManagement_IRQn',
    'BusFault_IRQn', 'UsageFault_IRQn', 'SVCall_IRQn', 'DebugMonitor_IRQn',
    'PendSV_IRQn', 'SysTick_IRQn', 'WWDG_IRQn', 'PVD_IRQn', 'TAMP_STAMP_IRQn',
    'RTC_WKUP_IRQn', 'FLASH_IRQn', 'RCC_IRQn', 'EXTI0_IRQn', 'EXTI1_IRQn', 'EXTI2_IRQn',
    'EXTI3_IRQn', 'EXTI4_IRQn', 'DMA1_Stream0_IRQn', 'DMA1_Stream1_IRQn',
    'DMA1_Stream2_IRQn', 'DMA1_Stream3_IRQn', 'DMA1_Stream4_IRQn', 'DMA1_Stream5_IRQn',
    'DMA1_Stream6_IRQn', 'ADC_IRQn', 'CAN1_TX_IRQn', 'CAN1_RX0_IRQn', 'CAN1_RX1_IRQn',
    'CAN1_SCE_IRQn', 'EXTI9_5_IRQn', 'TIM1_BRK_TIM9_IRQn', 'TIM1_UP_TIM10_IRQn',
    'TIM1_TRG_COM_TIM11_IRQn', 'TIM1_CC_IRQn', 'TIM2_IRQn', 'TIM3_IRQn', 'TIM4_IRQn',
    'I2C1_EV_IRQn', 'I2C1_ER_IRQn', 'I2C2_EV_IRQn', 'I2C2_ER_IRQn', 'SPI1_IRQn',
    'SPI2_IRQn', 'USART1_IRQn', 'USART2_IRQn', 'USART3_IRQn', 'EXTI15_10_IRQn',
    'RTC_Alarm_IRQn', 'OTG_FS_WKUP_IRQn', 'TIM8_BRK_TIM12_IRQn', 'TIM8_UP_TIM13_IRQn',
    'TIM8_TRG_COM_TIM14_IRQn', 'TIM8_CC_IRQn', 'DMA1_Stream7_IRQn', 'FSMC_IRQn',
    'SDIO_IRQn', 'TIM5_IRQn', 'SPI3_IRQn', 'UART4_IRQn', 'UART5_IRQn', 'TIM6_DAC_IRQn',
    'TIM7_IRQn', 'DMA2_Stream0_IRQn', 'DMA2_Stream1_IRQn', 'DMA2_Stream2_IRQn',
    'DMA2_Stream3_IRQn', 'DMA2_Stream4_IRQn', 'ETH_IRQn', 'ETH_WKUP_IRQn',
    'CAN2_TX_IRQn', 'CAN2_RX0_IRQn', 'CAN2_RX1_IRQn', 'CAN2_SCE_IRQn', 'OTG_FS_IRQn',
    'DMA2_Stream5_IRQn', 'DMA2_Stream6_IRQn', 'DMA2_Stream7_IRQn', 'USART6_IRQn',
    'I2C3_EV_IRQn', 'I2C3_ER_IRQn', 'OTG_HS_EP1_OUT_IRQn', 'OTG_HS_EP1_IN_IRQn',
    'OTG_HS_WKUP_IRQn', 'OTG_HS_IRQn', 'DCMI_IRQn', 'CRYP_IRQn', 'HASH_RNG_IRQn',
    'FPU_IRQn', 'RESET', 'SET', 'DISABLE', 'ENABLE', 'ERROR', 'SUCCESS', 'HSE_VALUE',
    'HSE_STARTUP_TIMEOUT', 'HSI_VALUE', '__STM32F4XX_STDPERIPH_VERSION_MAIN',
    '__STM32F4XX_STDPERIPH_VERSION_SUB1', '__STM32F4XX_STDPERIPH_VERSION_SUB2',
    '__STM32F4XX_STDPERIPH_VERSION_RC', '__STM32F4XX_STDPERIPH_VERSION', '__CM4_REV',
    '__MPU_PRESENT', '__NVIC_PRIO_BITS', '__Vendor_SysTickConfig', '__FPU_PRESENT',
    'FLASH_BASE', 'CCMDATARAM_BASE', 'SRAM1_BASE', 'SRAM2_BASE', 'PERIPH_BASE',
    'BKPSRAM_BASE', 'FSMC_R_BASE', 'CCMDATARAM_BB_BASE', 'SRAM1_BB_BASE',
    'SRAM2_BB_BASE', 'PERIPH_BB_BASE', 'BKPSRAM_BB_BASE', 'SRAM_BASE', 'SRAM_BB_BASE',
    'APB1PERIPH_BASE', 'APB2PERIPH_BASE', 'AHB1PERIPH_BASE', 'AHB2PERIPH_BASE',
    'TIM2_BASE', 'TIM3_BASE', 'TIM4_BASE', 'TIM5_BASE', 'TIM6_BASE', 'TIM7_BASE',
    'TIM12_BASE', 'TIM13_BASE', 'TIM14_BASE', 'RTC_BASE', 'WWDG_BASE', 'IWDG_BASE',
    'I2S2ext_BASE', 'SPI2_BASE', 'SPI3_BASE', 'I2S3ext_BASE', 'USART2_BASE',
    'USART3_BASE', 'UART4_BASE', 'UART5_BASE', 'I2C1_BASE', 'I2C2_BASE', 'I2C3_BASE',
    'CAN1_BASE', 'CAN2_BASE', 'PWR_BASE', 'DAC_BASE', 'TIM1_BASE', 'TIM8_BASE',
    'USART1_BASE', 'USART6_BASE', 'ADC1_BASE', 'ADC2_BASE', 'ADC3_BASE', 'ADC_BASE',
    'SDIO_BASE', 'SPI1_BASE', 'SYSCFG_BASE', 'EXTI_BASE', 'TIM9_BASE', 'TIM10_BASE',
    'TIM11_BASE', 'GPIOA_BASE', 'GPIOB_BASE', 'GPIOC_BASE', 'GPIOD_BASE', 'GPIOE_BASE',
    'GPIOF_BASE', 'GPIOG_BASE', 'GPIOH_BASE', 'GPIOI_BASE', 'CRC_BASE', 'RCC_BASE',
    'FLASH_R_BASE', 'DMA1_BASE', 'DMA1_Stream0_BASE', 'DMA1_Stream1_BASE',
    'DMA1_Stream2_BASE', 'DMA1_Stream3_BASE', 'DMA1_Stream4_BASE', 'DMA1_Stream5_BASE',
    'DMA1_Stream6_BASE', 'DMA1_Stream7_BASE', 'DMA2_BASE', 'DMA2_Stream0_BASE',
    'DMA2_Stream1_BASE', 'DMA2_Stream2_BASE', 'DMA2_Stream3_BASE', 'DMA2_Stream4_BASE',
    'DMA2_Stream5_BASE', 'DMA2_Stream6_BASE', 'DMA2_Stream7_BASE', 'ETH_BASE',
    'ETH_MAC_BASE', 'ETH_MMC_BASE', 'ETH_PTP_BASE', 'ETH_DMA_BASE', 'DCMI_BASE',
    'CRYP_BASE', 'HASH_BASE', 'RNG_BASE', 'FSMC_Bank1_R_BASE', 'FSMC_Bank1E_R_BASE',
    'FSMC_Bank2_R_BASE', 'FSMC_Bank3_R_BASE', 'FSMC_Bank4_R_BASE', 'DBGMCU_BASE',
    'TIM2', 'TIM3', 'TIM4', 'TIM5', 'TIM6', 'TIM7', 'TIM12', 'TIM13', 'TIM14', 'RTC',
    'WWDG', 'IWDG', 'I2S2ext', 'SPI2', 'SPI3', 'I2S3ext', 'USART2', 'USART3', 'UART4',
    'UART5', 'I2C1', 'I2C2', 'I2C3', 'CAN1', 'CAN2', 'PWR', 'DAC', 'TIM1', 'TIM8',
    'USART1', 'USART6', 'ADC', 'ADC1', 'ADC2', 'ADC3', 'SDIO', 'SPI1', 'SYSCFG', 'EXTI',
    'TIM9', 'TIM10', 'TIM11', 'GPIOA', 'GPIOB', 'GPIOC', 'GPIOD', 'GPIOE', 'GPIOF',
    'GPIOG', 'GPIOH', 'GPIOI', 'CRC', 'RCC', 'FLASH', 'DMA1', 'DMA1_Stream0',
    'DMA1_Stream1', 'DMA1_Stream2', 'DMA1_Stream3', 'DMA1_Stream4', 'DMA1_Stream5',
    'DMA1_Stream6', 'DMA1_Stream7', 'DMA2', 'DMA2_Stream0', 'DMA2_Stream1',
    'DMA2_Stream2', 'DMA2_Stream3', 'DMA2_Stream4', 'DMA2_Stream5', 'DMA2_Stream6',
    'DMA2_Stream7', 'ETH', 'DCMI', 'CRYP', 'HASH', 'RNG', 'FSMC_Bank1', 'FSMC_Bank1E',
    'FSMC_Bank2', 'FSMC_Bank3', 'FSMC_Bank4', 'DBGMCU', 'ADC_SR_AWD', 'ADC_SR_EOC',
    'ADC_SR_JEOC', 'ADC_SR_JSTRT', 'ADC_SR_STRT', 'ADC_SR_OVR', 'ADC_CR1_AWDCH',
    'ADC_CR1_AWDCH_0', 'ADC_CR1_AWDCH_1', 'ADC_CR1_AWDCH_2', 'ADC_CR1_AWDCH_3',
    'ADC_CR1_AWDCH_4', 'ADC_CR1_EOCIE', 'ADC_CR1_AWDIE', 'ADC_CR1_JEOCIE',
    'ADC_CR1_SCAN', 'ADC_CR1_AWDSGL', 'ADC_CR1_JAUTO', 'ADC_CR1_DISCEN',
    'ADC_CR1_JDISCEN', 'ADC_CR1_DISCNUM', 'ADC_CR1_DISCNUM_0', 'ADC_CR1_DISCNUM_1',
    'ADC_CR1_DISCNUM_2', 'ADC_CR1_JAWDEN', 'ADC_CR1_AWDEN', 'ADC_CR1_RES',
    'ADC_CR1_RES_0', 'ADC_CR1_RES_1', 'ADC_CR1_OVRIE', 'ADC_CR2_ADON', 'ADC_CR2_CONT',
    'ADC_CR2_DMA', 'ADC_CR2_DDS', 'ADC_CR2_EOCS', 'ADC_CR2_ALIGN', 'ADC_CR2_JEXTSEL',
    'ADC_CR2_JEXTSEL_0', 'ADC_CR2_JEXTSEL_1', 'ADC_CR2_JEXTSEL_2', 'ADC_CR2_JEXTSEL_3',
    'ADC_CR2_JEXTEN', 'ADC_CR2_JEXTEN_0', 'ADC_CR2_JEXTEN_1', 'ADC_CR2_JSWSTART',
    'ADC_CR2_EXTSEL', 'ADC_CR2_EXTSEL_0', 'ADC_CR2_EXTSEL_1', 'ADC_CR2_EXTSEL_2',
    'ADC_CR2_EXTSEL_3', 'ADC_CR2_EXTEN', 'ADC_CR2_EXTEN_0', 'ADC_CR2_EXTEN_1',
    'ADC_CR2_SWSTART', 'ADC_SMPR1_SMP10', 'ADC_SMPR1_SMP10_0', 'ADC_SMPR1_SMP10_1',
    'ADC_SMPR1_SMP10_2', 'ADC_SMPR1_SMP11', 'ADC_SMPR1_SMP11_0', 'ADC_SMPR1_SMP11_1',
    'ADC_SMPR1_SMP11_2', 'ADC_SMPR1_SMP12', 'ADC_SMPR1_SMP12_0', 'ADC_SMPR1_SMP12_1',
    'ADC_SMPR1_SMP12_2', 'ADC_SMPR1_SMP13', 'ADC_SMPR1_SMP13_0', 'ADC_SMPR1_SMP13_1',
    'ADC_SMPR1_SMP13_2', 'ADC_SMPR1_SMP14', 'ADC_SMPR1_SMP14_0', 'ADC_SMPR1_SMP14_1',
    'ADC_SMPR1_SMP14_2', 'ADC_SMPR1_SMP15', 'ADC_SMPR1_SMP15_0', 'ADC_SMPR1_SMP15_1',
    'ADC_SMPR1_SMP15_2', 'ADC_SMPR1_SMP16', 'ADC_SMPR1_SMP16_0', 'ADC_SMPR1_SMP16_1',
    'ADC_SMPR1_SMP16_2', 'ADC_SMPR1_SMP17', 'ADC_SMPR1_SMP17_0', 'ADC_SMPR1_SMP17_1',
    'ADC_SMPR1_SMP17_2', 'ADC_SMPR1_SMP18', 'ADC_SMPR1_SMP18_0', 'ADC_SMPR1_SMP18_1',
    'ADC_SMPR1_SMP18_2', 'ADC_SMPR2_SMP0', 'ADC_SMPR2_SMP0_0', 'ADC_SMPR2_SMP0_1',
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
    'ADC_JDR3_JDATA', 'ADC_JDR4_JDATA', 'ADC_DR_DATA', 'ADC_DR_ADC2DATA',
    'ADC_CSR_AWD1', 'ADC_CSR_EOC1', 'ADC_CSR_JEOC1', 'ADC_CSR_JSTRT1', 'ADC_CSR_STRT1',
    'ADC_CSR_DOVR1', 'ADC_CSR_AWD2', 'ADC_CSR_EOC2', 'ADC_CSR_JEOC2', 'ADC_CSR_JSTRT2',
    'ADC_CSR_STRT2', 'ADC_CSR_DOVR2', 'ADC_CSR_AWD3', 'ADC_CSR_EOC3', 'ADC_CSR_JEOC3',
    'ADC_CSR_JSTRT3', 'ADC_CSR_STRT3', 'ADC_CSR_DOVR3', 'ADC_CCR_MULTI',
    'ADC_CCR_MULTI_0', 'ADC_CCR_MULTI_1', 'ADC_CCR_MULTI_2', 'ADC_CCR_MULTI_3',
    'ADC_CCR_MULTI_4', 'ADC_CCR_DELAY', 'ADC_CCR_DELAY_0', 'ADC_CCR_DELAY_1',
    'ADC_CCR_DELAY_2', 'ADC_CCR_DELAY_3', 'ADC_CCR_DDS', 'ADC_CCR_DMA', 'ADC_CCR_DMA_0',
    'ADC_CCR_DMA_1', 'ADC_CCR_ADCPRE', 'ADC_CCR_ADCPRE_0', 'ADC_CCR_ADCPRE_1',
    'ADC_CCR_VBATE', 'ADC_CCR_TSVREFE', 'ADC_CDR_DATA1', 'ADC_CDR_DATA2',
    'CAN_MCR_INRQ', 'CAN_MCR_SLEEP', 'CAN_MCR_TXFP', 'CAN_MCR_RFLM', 'CAN_MCR_NART',
    'CAN_MCR_AWUM', 'CAN_MCR_ABOM', 'CAN_MCR_TTCM', 'CAN_MCR_RESET', 'CAN_MSR_INAK',
    'CAN_MSR_SLAK', 'CAN_MSR_ERRI', 'CAN_MSR_WKUI', 'CAN_MSR_SLAKI', 'CAN_MSR_TXM',
    'CAN_MSR_RXM', 'CAN_MSR_SAMP', 'CAN_MSR_RX', 'CAN_TSR_RQCP0', 'CAN_TSR_TXOK0',
    'CAN_TSR_ALST0', 'CAN_TSR_TERR0', 'CAN_TSR_ABRQ0', 'CAN_TSR_RQCP1', 'CAN_TSR_TXOK1',
    'CAN_TSR_ALST1', 'CAN_TSR_TERR1', 'CAN_TSR_ABRQ1', 'CAN_TSR_RQCP2', 'CAN_TSR_TXOK2',
    'CAN_TSR_ALST2', 'CAN_TSR_TERR2', 'CAN_TSR_ABRQ2', 'CAN_TSR_CODE', 'CAN_TSR_TME',
    'CAN_TSR_TME0', 'CAN_TSR_TME1', 'CAN_TSR_TME2', 'CAN_TSR_LOW', 'CAN_TSR_LOW0',
    'CAN_TSR_LOW1', 'CAN_TSR_LOW2', 'CAN_RF0R_FMP0', 'CAN_RF0R_FULL0', 'CAN_RF0R_FOVR0',
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
    'CAN_F13R2_FB28', 'CAN_F13R2_FB29', 'CAN_F13R2_FB30', 'CAN_F13R2_FB31', 'CRC_DR_DR',
    'CRC_IDR_IDR', 'CRC_CR_RESET', 'CRYP_CR_ALGODIR', 'CRYP_CR_ALGOMODE',
    'CRYP_CR_ALGOMODE_0', 'CRYP_CR_ALGOMODE_1', 'CRYP_CR_ALGOMODE_2',
    'CRYP_CR_ALGOMODE_TDES_ECB', 'CRYP_CR_ALGOMODE_TDES_CBC',
    'CRYP_CR_ALGOMODE_DES_ECB', 'CRYP_CR_ALGOMODE_DES_CBC', 'CRYP_CR_ALGOMODE_AES_ECB',
    'CRYP_CR_ALGOMODE_AES_CBC', 'CRYP_CR_ALGOMODE_AES_CTR', 'CRYP_CR_ALGOMODE_AES_KEY',
    'CRYP_CR_DATATYPE', 'CRYP_CR_DATATYPE_0', 'CRYP_CR_DATATYPE_1', 'CRYP_CR_KEYSIZE',
    'CRYP_CR_KEYSIZE_0', 'CRYP_CR_KEYSIZE_1', 'CRYP_CR_FFLUSH', 'CRYP_CR_CRYPEN',
    'CRYP_SR_IFEM', 'CRYP_SR_IFNF', 'CRYP_SR_OFNE', 'CRYP_SR_OFFU', 'CRYP_SR_BUSY',
    'CRYP_DMACR_DIEN', 'CRYP_DMACR_DOEN', 'CRYP_IMSCR_INIM', 'CRYP_IMSCR_OUTIM',
    'CRYP_RISR_OUTRIS', 'CRYP_RISR_INRIS', 'CRYP_MISR_INMIS', 'CRYP_MISR_OUTMIS',
    'DAC_CR_EN1', 'DAC_CR_BOFF1', 'DAC_CR_TEN1', 'DAC_CR_TSEL1', 'DAC_CR_TSEL1_0',
    'DAC_CR_TSEL1_1', 'DAC_CR_TSEL1_2', 'DAC_CR_WAVE1', 'DAC_CR_WAVE1_0',
    'DAC_CR_WAVE1_1', 'DAC_CR_MAMP1', 'DAC_CR_MAMP1_0', 'DAC_CR_MAMP1_1',
    'DAC_CR_MAMP1_2', 'DAC_CR_MAMP1_3', 'DAC_CR_DMAEN1', 'DAC_CR_EN2', 'DAC_CR_BOFF2',
    'DAC_CR_TEN2', 'DAC_CR_TSEL2', 'DAC_CR_TSEL2_0', 'DAC_CR_TSEL2_1', 'DAC_CR_TSEL2_2',
    'DAC_CR_WAVE2', 'DAC_CR_WAVE2_0', 'DAC_CR_WAVE2_1', 'DAC_CR_MAMP2',
    'DAC_CR_MAMP2_0', 'DAC_CR_MAMP2_1', 'DAC_CR_MAMP2_2', 'DAC_CR_MAMP2_3',
    'DAC_CR_DMAEN2', 'DAC_SWTRIGR_SWTRIG1', 'DAC_SWTRIGR_SWTRIG2',
    'DAC_DHR12R1_DACC1DHR', 'DAC_DHR12L1_DACC1DHR', 'DAC_DHR8R1_DACC1DHR',
    'DAC_DHR12R2_DACC2DHR', 'DAC_DHR12L2_DACC2DHR', 'DAC_DHR8R2_DACC2DHR',
    'DAC_DHR12RD_DACC1DHR', 'DAC_DHR12RD_DACC2DHR', 'DAC_DHR12LD_DACC1DHR',
    'DAC_DHR12LD_DACC2DHR', 'DAC_DHR8RD_DACC1DHR', 'DAC_DHR8RD_DACC2DHR',
    'DAC_DOR1_DACC1DOR', 'DAC_DOR2_DACC2DOR', 'DAC_SR_DMAUDR1', 'DAC_SR_DMAUDR2',
    'DCMI_CR_CAPTURE', 'DCMI_CR_CM', 'DCMI_CR_CROP', 'DCMI_CR_JPEG', 'DCMI_CR_ESS',
    'DCMI_CR_PCKPOL', 'DCMI_CR_HSPOL', 'DCMI_CR_VSPOL', 'DCMI_CR_FCRC_0',
    'DCMI_CR_FCRC_1', 'DCMI_CR_EDM_0', 'DCMI_CR_EDM_1', 'DCMI_CR_CRE', 'DCMI_CR_ENABLE',
    'DCMI_SR_HSYNC', 'DCMI_SR_VSYNC', 'DCMI_SR_FNE', 'DCMI_RISR_FRAME_RIS',
    'DCMI_RISR_OVF_RIS', 'DCMI_RISR_ERR_RIS', 'DCMI_RISR_VSYNC_RIS',
    'DCMI_RISR_LINE_RIS', 'DCMI_IER_FRAME_IE', 'DCMI_IER_OVF_IE', 'DCMI_IER_ERR_IE',
    'DCMI_IER_VSYNC_IE', 'DCMI_IER_LINE_IE', 'DCMI_MISR_FRAME_MIS', 'DCMI_MISR_OVF_MIS',
    'DCMI_MISR_ERR_MIS', 'DCMI_MISR_VSYNC_MIS', 'DCMI_MISR_LINE_MIS',
    'DCMI_ICR_FRAME_ISC', 'DCMI_ICR_OVF_ISC', 'DCMI_ICR_ERR_ISC', 'DCMI_ICR_VSYNC_ISC',
    'DCMI_ICR_LINE_ISC', 'DMA_SxCR_CHSEL', 'DMA_SxCR_CHSEL_0', 'DMA_SxCR_CHSEL_1',
    'DMA_SxCR_CHSEL_2', 'DMA_SxCR_MBURST', 'DMA_SxCR_MBURST_0', 'DMA_SxCR_MBURST_1',
    'DMA_SxCR_PBURST', 'DMA_SxCR_PBURST_0', 'DMA_SxCR_PBURST_1', 'DMA_SxCR_ACK',
    'DMA_SxCR_CT', 'DMA_SxCR_DBM', 'DMA_SxCR_PL', 'DMA_SxCR_PL_0', 'DMA_SxCR_PL_1',
    'DMA_SxCR_PINCOS', 'DMA_SxCR_MSIZE', 'DMA_SxCR_MSIZE_0', 'DMA_SxCR_MSIZE_1',
    'DMA_SxCR_PSIZE', 'DMA_SxCR_PSIZE_0', 'DMA_SxCR_PSIZE_1', 'DMA_SxCR_MINC',
    'DMA_SxCR_PINC', 'DMA_SxCR_CIRC', 'DMA_SxCR_DIR', 'DMA_SxCR_DIR_0',
    'DMA_SxCR_DIR_1', 'DMA_SxCR_PFCTRL', 'DMA_SxCR_TCIE', 'DMA_SxCR_HTIE',
    'DMA_SxCR_TEIE', 'DMA_SxCR_DMEIE', 'DMA_SxCR_EN', 'DMA_SxNDT', 'DMA_SxNDT_0',
    'DMA_SxNDT_1', 'DMA_SxNDT_2', 'DMA_SxNDT_3', 'DMA_SxNDT_4', 'DMA_SxNDT_5',
    'DMA_SxNDT_6', 'DMA_SxNDT_7', 'DMA_SxNDT_8', 'DMA_SxNDT_9', 'DMA_SxNDT_10',
    'DMA_SxNDT_11', 'DMA_SxNDT_12', 'DMA_SxNDT_13', 'DMA_SxNDT_14', 'DMA_SxNDT_15',
    'DMA_SxFCR_FEIE', 'DMA_SxFCR_FS', 'DMA_SxFCR_FS_0', 'DMA_SxFCR_FS_1',
    'DMA_SxFCR_FS_2', 'DMA_SxFCR_DMDIS', 'DMA_SxFCR_FTH', 'DMA_SxFCR_FTH_0',
    'DMA_SxFCR_FTH_1', 'DMA_LISR_TCIF3', 'DMA_LISR_HTIF3', 'DMA_LISR_TEIF3',
    'DMA_LISR_DMEIF3', 'DMA_LISR_FEIF3', 'DMA_LISR_TCIF2', 'DMA_LISR_HTIF2',
    'DMA_LISR_TEIF2', 'DMA_LISR_DMEIF2', 'DMA_LISR_FEIF2', 'DMA_LISR_TCIF1',
    'DMA_LISR_HTIF1', 'DMA_LISR_TEIF1', 'DMA_LISR_DMEIF1', 'DMA_LISR_FEIF1',
    'DMA_LISR_TCIF0', 'DMA_LISR_HTIF0', 'DMA_LISR_TEIF0', 'DMA_LISR_DMEIF0',
    'DMA_LISR_FEIF0', 'DMA_HISR_TCIF7', 'DMA_HISR_HTIF7', 'DMA_HISR_TEIF7',
    'DMA_HISR_DMEIF7', 'DMA_HISR_FEIF7', 'DMA_HISR_TCIF6', 'DMA_HISR_HTIF6',
    'DMA_HISR_TEIF6', 'DMA_HISR_DMEIF6', 'DMA_HISR_FEIF6', 'DMA_HISR_TCIF5',
    'DMA_HISR_HTIF5', 'DMA_HISR_TEIF5', 'DMA_HISR_DMEIF5', 'DMA_HISR_FEIF5',
    'DMA_HISR_TCIF4', 'DMA_HISR_HTIF4', 'DMA_HISR_TEIF4', 'DMA_HISR_DMEIF4',
    'DMA_HISR_FEIF4', 'DMA_LIFCR_CTCIF3', 'DMA_LIFCR_CHTIF3', 'DMA_LIFCR_CTEIF3',
    'DMA_LIFCR_CDMEIF3', 'DMA_LIFCR_CFEIF3', 'DMA_LIFCR_CTCIF2', 'DMA_LIFCR_CHTIF2',
    'DMA_LIFCR_CTEIF2', 'DMA_LIFCR_CDMEIF2', 'DMA_LIFCR_CFEIF2', 'DMA_LIFCR_CTCIF1',
    'DMA_LIFCR_CHTIF1', 'DMA_LIFCR_CTEIF1', 'DMA_LIFCR_CDMEIF1', 'DMA_LIFCR_CFEIF1',
    'DMA_LIFCR_CTCIF0', 'DMA_LIFCR_CHTIF0', 'DMA_LIFCR_CTEIF0', 'DMA_LIFCR_CDMEIF0',
    'DMA_LIFCR_CFEIF0', 'DMA_HIFCR_CTCIF7', 'DMA_HIFCR_CHTIF7', 'DMA_HIFCR_CTEIF7',
    'DMA_HIFCR_CDMEIF7', 'DMA_HIFCR_CFEIF7', 'DMA_HIFCR_CTCIF6', 'DMA_HIFCR_CHTIF6',
    'DMA_HIFCR_CTEIF6', 'DMA_HIFCR_CDMEIF6', 'DMA_HIFCR_CFEIF6', 'DMA_HIFCR_CTCIF5',
    'DMA_HIFCR_CHTIF5', 'DMA_HIFCR_CTEIF5', 'DMA_HIFCR_CDMEIF5', 'DMA_HIFCR_CFEIF5',
    'DMA_HIFCR_CTCIF4', 'DMA_HIFCR_CHTIF4', 'DMA_HIFCR_CTEIF4', 'DMA_HIFCR_CDMEIF4',
    'DMA_HIFCR_CFEIF4', 'EXTI_IMR_MR0', 'EXTI_IMR_MR1', 'EXTI_IMR_MR2', 'EXTI_IMR_MR3',
    'EXTI_IMR_MR4', 'EXTI_IMR_MR5', 'EXTI_IMR_MR6', 'EXTI_IMR_MR7', 'EXTI_IMR_MR8',
    'EXTI_IMR_MR9', 'EXTI_IMR_MR10', 'EXTI_IMR_MR11', 'EXTI_IMR_MR12', 'EXTI_IMR_MR13',
    'EXTI_IMR_MR14', 'EXTI_IMR_MR15', 'EXTI_IMR_MR16', 'EXTI_IMR_MR17', 'EXTI_IMR_MR18',
    'EXTI_IMR_MR19', 'EXTI_EMR_MR0', 'EXTI_EMR_MR1', 'EXTI_EMR_MR2', 'EXTI_EMR_MR3',
    'EXTI_EMR_MR4', 'EXTI_EMR_MR5', 'EXTI_EMR_MR6', 'EXTI_EMR_MR7', 'EXTI_EMR_MR8',
    'EXTI_EMR_MR9', 'EXTI_EMR_MR10', 'EXTI_EMR_MR11', 'EXTI_EMR_MR12', 'EXTI_EMR_MR13',
    'EXTI_EMR_MR14', 'EXTI_EMR_MR15', 'EXTI_EMR_MR16', 'EXTI_EMR_MR17', 'EXTI_EMR_MR18',
    'EXTI_EMR_MR19', 'EXTI_RTSR_TR0', 'EXTI_RTSR_TR1', 'EXTI_RTSR_TR2', 'EXTI_RTSR_TR3',
    'EXTI_RTSR_TR4', 'EXTI_RTSR_TR5', 'EXTI_RTSR_TR6', 'EXTI_RTSR_TR7', 'EXTI_RTSR_TR8',
    'EXTI_RTSR_TR9', 'EXTI_RTSR_TR10', 'EXTI_RTSR_TR11', 'EXTI_RTSR_TR12',
    'EXTI_RTSR_TR13', 'EXTI_RTSR_TR14', 'EXTI_RTSR_TR15', 'EXTI_RTSR_TR16',
    'EXTI_RTSR_TR17', 'EXTI_RTSR_TR18', 'EXTI_RTSR_TR19', 'EXTI_FTSR_TR0',
    'EXTI_FTSR_TR1', 'EXTI_FTSR_TR2', 'EXTI_FTSR_TR3', 'EXTI_FTSR_TR4', 'EXTI_FTSR_TR5',
    'EXTI_FTSR_TR6', 'EXTI_FTSR_TR7', 'EXTI_FTSR_TR8', 'EXTI_FTSR_TR9',
    'EXTI_FTSR_TR10', 'EXTI_FTSR_TR11', 'EXTI_FTSR_TR12', 'EXTI_FTSR_TR13',
    'EXTI_FTSR_TR14', 'EXTI_FTSR_TR15', 'EXTI_FTSR_TR16', 'EXTI_FTSR_TR17',
    'EXTI_FTSR_TR18', 'EXTI_FTSR_TR19', 'EXTI_SWIER_SWIER0', 'EXTI_SWIER_SWIER1',
    'EXTI_SWIER_SWIER2', 'EXTI_SWIER_SWIER3', 'EXTI_SWIER_SWIER4', 'EXTI_SWIER_SWIER5',
    'EXTI_SWIER_SWIER6', 'EXTI_SWIER_SWIER7', 'EXTI_SWIER_SWIER8', 'EXTI_SWIER_SWIER9',
    'EXTI_SWIER_SWIER10', 'EXTI_SWIER_SWIER11', 'EXTI_SWIER_SWIER12',
    'EXTI_SWIER_SWIER13', 'EXTI_SWIER_SWIER14', 'EXTI_SWIER_SWIER15',
    'EXTI_SWIER_SWIER16', 'EXTI_SWIER_SWIER17', 'EXTI_SWIER_SWIER18',
    'EXTI_SWIER_SWIER19', 'EXTI_PR_PR0', 'EXTI_PR_PR1', 'EXTI_PR_PR2', 'EXTI_PR_PR3',
    'EXTI_PR_PR4', 'EXTI_PR_PR5', 'EXTI_PR_PR6', 'EXTI_PR_PR7', 'EXTI_PR_PR8',
    'EXTI_PR_PR9', 'EXTI_PR_PR10', 'EXTI_PR_PR11', 'EXTI_PR_PR12', 'EXTI_PR_PR13',
    'EXTI_PR_PR14', 'EXTI_PR_PR15', 'EXTI_PR_PR16', 'EXTI_PR_PR17', 'EXTI_PR_PR18',
    'EXTI_PR_PR19', 'FLASH_ACR_LATENCY', 'FLASH_ACR_LATENCY_0WS',
    'FLASH_ACR_LATENCY_1WS', 'FLASH_ACR_LATENCY_2WS', 'FLASH_ACR_LATENCY_3WS',
    'FLASH_ACR_LATENCY_4WS', 'FLASH_ACR_LATENCY_5WS', 'FLASH_ACR_LATENCY_6WS',
    'FLASH_ACR_LATENCY_7WS', 'FLASH_ACR_PRFTEN', 'FLASH_ACR_ICEN', 'FLASH_ACR_DCEN',
    'FLASH_ACR_ICRST', 'FLASH_ACR_DCRST', 'FLASH_ACR_BYTE0_ADDRESS',
    'FLASH_ACR_BYTE2_ADDRESS', 'FLASH_SR_EOP', 'FLASH_SR_SOP', 'FLASH_SR_WRPERR',
    'FLASH_SR_PGAERR', 'FLASH_SR_PGPERR', 'FLASH_SR_PGSERR', 'FLASH_SR_BSY',
    'FLASH_CR_PG', 'FLASH_CR_SER', 'FLASH_CR_MER', 'FLASH_CR_SNB_0', 'FLASH_CR_SNB_1',
    'FLASH_CR_SNB_2', 'FLASH_CR_SNB_3', 'FLASH_CR_PSIZE_0', 'FLASH_CR_PSIZE_1',
    'FLASH_CR_STRT', 'FLASH_CR_EOPIE', 'FLASH_CR_LOCK', 'FLASH_OPTCR_OPTLOCK',
    'FLASH_OPTCR_OPTSTRT', 'FLASH_OPTCR_BOR_LEV_0', 'FLASH_OPTCR_BOR_LEV_1',
    'FLASH_OPTCR_BOR_LEV', 'FLASH_OPTCR_WDG_SW', 'FLASH_OPTCR_nRST_STOP',
    'FLASH_OPTCR_nRST_STDBY', 'FLASH_OPTCR_RDP_0', 'FLASH_OPTCR_RDP_1',
    'FLASH_OPTCR_RDP_2', 'FLASH_OPTCR_RDP_3', 'FLASH_OPTCR_RDP_4', 'FLASH_OPTCR_RDP_5',
    'FLASH_OPTCR_RDP_6', 'FLASH_OPTCR_RDP_7', 'FLASH_OPTCR_nWRP_0',
    'FLASH_OPTCR_nWRP_1', 'FLASH_OPTCR_nWRP_2', 'FLASH_OPTCR_nWRP_3',
    'FLASH_OPTCR_nWRP_4', 'FLASH_OPTCR_nWRP_5', 'FLASH_OPTCR_nWRP_6',
    'FLASH_OPTCR_nWRP_7', 'FLASH_OPTCR_nWRP_8', 'FLASH_OPTCR_nWRP_9',
    'FLASH_OPTCR_nWRP_10', 'FLASH_OPTCR_nWRP_11', 'FSMC_BCR1_MBKEN', 'FSMC_BCR1_MUXEN',
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
    'FSMC_ECCR3_ECC3', 'GPIO_MODER_MODER0', 'GPIO_MODER_MODER0_0',
    'GPIO_MODER_MODER0_1', 'GPIO_MODER_MODER1', 'GPIO_MODER_MODER1_0',
    'GPIO_MODER_MODER1_1', 'GPIO_MODER_MODER2', 'GPIO_MODER_MODER2_0',
    'GPIO_MODER_MODER2_1', 'GPIO_MODER_MODER3', 'GPIO_MODER_MODER3_0',
    'GPIO_MODER_MODER3_1', 'GPIO_MODER_MODER4', 'GPIO_MODER_MODER4_0',
    'GPIO_MODER_MODER4_1', 'GPIO_MODER_MODER5', 'GPIO_MODER_MODER5_0',
    'GPIO_MODER_MODER5_1', 'GPIO_MODER_MODER6', 'GPIO_MODER_MODER6_0',
    'GPIO_MODER_MODER6_1', 'GPIO_MODER_MODER7', 'GPIO_MODER_MODER7_0',
    'GPIO_MODER_MODER7_1', 'GPIO_MODER_MODER8', 'GPIO_MODER_MODER8_0',
    'GPIO_MODER_MODER8_1', 'GPIO_MODER_MODER9', 'GPIO_MODER_MODER9_0',
    'GPIO_MODER_MODER9_1', 'GPIO_MODER_MODER10', 'GPIO_MODER_MODER10_0',
    'GPIO_MODER_MODER10_1', 'GPIO_MODER_MODER11', 'GPIO_MODER_MODER11_0',
    'GPIO_MODER_MODER11_1', 'GPIO_MODER_MODER12', 'GPIO_MODER_MODER12_0',
    'GPIO_MODER_MODER12_1', 'GPIO_MODER_MODER13', 'GPIO_MODER_MODER13_0',
    'GPIO_MODER_MODER13_1', 'GPIO_MODER_MODER14', 'GPIO_MODER_MODER14_0',
    'GPIO_MODER_MODER14_1', 'GPIO_MODER_MODER15', 'GPIO_MODER_MODER15_0',
    'GPIO_MODER_MODER15_1', 'GPIO_OTYPER_OT_0', 'GPIO_OTYPER_OT_1', 'GPIO_OTYPER_OT_2',
    'GPIO_OTYPER_OT_3', 'GPIO_OTYPER_OT_4', 'GPIO_OTYPER_OT_5', 'GPIO_OTYPER_OT_6',
    'GPIO_OTYPER_OT_7', 'GPIO_OTYPER_OT_8', 'GPIO_OTYPER_OT_9', 'GPIO_OTYPER_OT_10',
    'GPIO_OTYPER_OT_11', 'GPIO_OTYPER_OT_12', 'GPIO_OTYPER_OT_13', 'GPIO_OTYPER_OT_14',
    'GPIO_OTYPER_OT_15', 'GPIO_OSPEEDER_OSPEEDR0', 'GPIO_OSPEEDER_OSPEEDR0_0',
    'GPIO_OSPEEDER_OSPEEDR0_1', 'GPIO_OSPEEDER_OSPEEDR1', 'GPIO_OSPEEDER_OSPEEDR1_0',
    'GPIO_OSPEEDER_OSPEEDR1_1', 'GPIO_OSPEEDER_OSPEEDR2', 'GPIO_OSPEEDER_OSPEEDR2_0',
    'GPIO_OSPEEDER_OSPEEDR2_1', 'GPIO_OSPEEDER_OSPEEDR3', 'GPIO_OSPEEDER_OSPEEDR3_0',
    'GPIO_OSPEEDER_OSPEEDR3_1', 'GPIO_OSPEEDER_OSPEEDR4', 'GPIO_OSPEEDER_OSPEEDR4_0',
    'GPIO_OSPEEDER_OSPEEDR4_1', 'GPIO_OSPEEDER_OSPEEDR5', 'GPIO_OSPEEDER_OSPEEDR5_0',
    'GPIO_OSPEEDER_OSPEEDR5_1', 'GPIO_OSPEEDER_OSPEEDR6', 'GPIO_OSPEEDER_OSPEEDR6_0',
    'GPIO_OSPEEDER_OSPEEDR6_1', 'GPIO_OSPEEDER_OSPEEDR7', 'GPIO_OSPEEDER_OSPEEDR7_0',
    'GPIO_OSPEEDER_OSPEEDR7_1', 'GPIO_OSPEEDER_OSPEEDR8', 'GPIO_OSPEEDER_OSPEEDR8_0',
    'GPIO_OSPEEDER_OSPEEDR8_1', 'GPIO_OSPEEDER_OSPEEDR9', 'GPIO_OSPEEDER_OSPEEDR9_0',
    'GPIO_OSPEEDER_OSPEEDR9_1', 'GPIO_OSPEEDER_OSPEEDR10', 'GPIO_OSPEEDER_OSPEEDR10_0',
    'GPIO_OSPEEDER_OSPEEDR10_1', 'GPIO_OSPEEDER_OSPEEDR11', 'GPIO_OSPEEDER_OSPEEDR11_0',
    'GPIO_OSPEEDER_OSPEEDR11_1', 'GPIO_OSPEEDER_OSPEEDR12', 'GPIO_OSPEEDER_OSPEEDR12_0',
    'GPIO_OSPEEDER_OSPEEDR12_1', 'GPIO_OSPEEDER_OSPEEDR13', 'GPIO_OSPEEDER_OSPEEDR13_0',
    'GPIO_OSPEEDER_OSPEEDR13_1', 'GPIO_OSPEEDER_OSPEEDR14', 'GPIO_OSPEEDER_OSPEEDR14_0',
    'GPIO_OSPEEDER_OSPEEDR14_1', 'GPIO_OSPEEDER_OSPEEDR15', 'GPIO_OSPEEDER_OSPEEDR15_0',
    'GPIO_OSPEEDER_OSPEEDR15_1', 'GPIO_PUPDR_PUPDR0', 'GPIO_PUPDR_PUPDR0_0',
    'GPIO_PUPDR_PUPDR0_1', 'GPIO_PUPDR_PUPDR1', 'GPIO_PUPDR_PUPDR1_0',
    'GPIO_PUPDR_PUPDR1_1', 'GPIO_PUPDR_PUPDR2', 'GPIO_PUPDR_PUPDR2_0',
    'GPIO_PUPDR_PUPDR2_1', 'GPIO_PUPDR_PUPDR3', 'GPIO_PUPDR_PUPDR3_0',
    'GPIO_PUPDR_PUPDR3_1', 'GPIO_PUPDR_PUPDR4', 'GPIO_PUPDR_PUPDR4_0',
    'GPIO_PUPDR_PUPDR4_1', 'GPIO_PUPDR_PUPDR5', 'GPIO_PUPDR_PUPDR5_0',
    'GPIO_PUPDR_PUPDR5_1', 'GPIO_PUPDR_PUPDR6', 'GPIO_PUPDR_PUPDR6_0',
    'GPIO_PUPDR_PUPDR6_1', 'GPIO_PUPDR_PUPDR7', 'GPIO_PUPDR_PUPDR7_0',
    'GPIO_PUPDR_PUPDR7_1', 'GPIO_PUPDR_PUPDR8', 'GPIO_PUPDR_PUPDR8_0',
    'GPIO_PUPDR_PUPDR8_1', 'GPIO_PUPDR_PUPDR9', 'GPIO_PUPDR_PUPDR9_0',
    'GPIO_PUPDR_PUPDR9_1', 'GPIO_PUPDR_PUPDR10', 'GPIO_PUPDR_PUPDR10_0',
    'GPIO_PUPDR_PUPDR10_1', 'GPIO_PUPDR_PUPDR11', 'GPIO_PUPDR_PUPDR11_0',
    'GPIO_PUPDR_PUPDR11_1', 'GPIO_PUPDR_PUPDR12', 'GPIO_PUPDR_PUPDR12_0',
    'GPIO_PUPDR_PUPDR12_1', 'GPIO_PUPDR_PUPDR13', 'GPIO_PUPDR_PUPDR13_0',
    'GPIO_PUPDR_PUPDR13_1', 'GPIO_PUPDR_PUPDR14', 'GPIO_PUPDR_PUPDR14_0',
    'GPIO_PUPDR_PUPDR14_1', 'GPIO_PUPDR_PUPDR15', 'GPIO_PUPDR_PUPDR15_0',
    'GPIO_PUPDR_PUPDR15_1', 'GPIO_IDR_IDR_0', 'GPIO_IDR_IDR_1', 'GPIO_IDR_IDR_2',
    'GPIO_IDR_IDR_3', 'GPIO_IDR_IDR_4', 'GPIO_IDR_IDR_5', 'GPIO_IDR_IDR_6',
    'GPIO_IDR_IDR_7', 'GPIO_IDR_IDR_8', 'GPIO_IDR_IDR_9', 'GPIO_IDR_IDR_10',
    'GPIO_IDR_IDR_11', 'GPIO_IDR_IDR_12', 'GPIO_IDR_IDR_13', 'GPIO_IDR_IDR_14',
    'GPIO_IDR_IDR_15', 'GPIO_OTYPER_IDR_0', 'GPIO_OTYPER_IDR_1', 'GPIO_OTYPER_IDR_2',
    'GPIO_OTYPER_IDR_3', 'GPIO_OTYPER_IDR_4', 'GPIO_OTYPER_IDR_5', 'GPIO_OTYPER_IDR_6',
    'GPIO_OTYPER_IDR_7', 'GPIO_OTYPER_IDR_8', 'GPIO_OTYPER_IDR_9', 'GPIO_OTYPER_IDR_10',
    'GPIO_OTYPER_IDR_11', 'GPIO_OTYPER_IDR_12', 'GPIO_OTYPER_IDR_13',
    'GPIO_OTYPER_IDR_14', 'GPIO_OTYPER_IDR_15', 'GPIO_ODR_ODR_0', 'GPIO_ODR_ODR_1',
    'GPIO_ODR_ODR_2', 'GPIO_ODR_ODR_3', 'GPIO_ODR_ODR_4', 'GPIO_ODR_ODR_5',
    'GPIO_ODR_ODR_6', 'GPIO_ODR_ODR_7', 'GPIO_ODR_ODR_8', 'GPIO_ODR_ODR_9',
    'GPIO_ODR_ODR_10', 'GPIO_ODR_ODR_11', 'GPIO_ODR_ODR_12', 'GPIO_ODR_ODR_13',
    'GPIO_ODR_ODR_14', 'GPIO_ODR_ODR_15', 'GPIO_OTYPER_ODR_0', 'GPIO_OTYPER_ODR_1',
    'GPIO_OTYPER_ODR_2', 'GPIO_OTYPER_ODR_3', 'GPIO_OTYPER_ODR_4', 'GPIO_OTYPER_ODR_5',
    'GPIO_OTYPER_ODR_6', 'GPIO_OTYPER_ODR_7', 'GPIO_OTYPER_ODR_8', 'GPIO_OTYPER_ODR_9',
    'GPIO_OTYPER_ODR_10', 'GPIO_OTYPER_ODR_11', 'GPIO_OTYPER_ODR_12',
    'GPIO_OTYPER_ODR_13', 'GPIO_OTYPER_ODR_14', 'GPIO_OTYPER_ODR_15', 'GPIO_BSRR_BS_0',
    'GPIO_BSRR_BS_1', 'GPIO_BSRR_BS_2', 'GPIO_BSRR_BS_3', 'GPIO_BSRR_BS_4',
    'GPIO_BSRR_BS_5', 'GPIO_BSRR_BS_6', 'GPIO_BSRR_BS_7', 'GPIO_BSRR_BS_8',
    'GPIO_BSRR_BS_9', 'GPIO_BSRR_BS_10', 'GPIO_BSRR_BS_11', 'GPIO_BSRR_BS_12',
    'GPIO_BSRR_BS_13', 'GPIO_BSRR_BS_14', 'GPIO_BSRR_BS_15', 'GPIO_BSRR_BR_0',
    'GPIO_BSRR_BR_1', 'GPIO_BSRR_BR_2', 'GPIO_BSRR_BR_3', 'GPIO_BSRR_BR_4',
    'GPIO_BSRR_BR_5', 'GPIO_BSRR_BR_6', 'GPIO_BSRR_BR_7', 'GPIO_BSRR_BR_8',
    'GPIO_BSRR_BR_9', 'GPIO_BSRR_BR_10', 'GPIO_BSRR_BR_11', 'GPIO_BSRR_BR_12',
    'GPIO_BSRR_BR_13', 'GPIO_BSRR_BR_14', 'GPIO_BSRR_BR_15', 'HASH_CR_INIT',
    'HASH_CR_DMAE', 'HASH_CR_DATATYPE', 'HASH_CR_DATATYPE_0', 'HASH_CR_DATATYPE_1',
    'HASH_CR_MODE', 'HASH_CR_ALGO', 'HASH_CR_NBW', 'HASH_CR_NBW_0', 'HASH_CR_NBW_1',
    'HASH_CR_NBW_2', 'HASH_CR_NBW_3', 'HASH_CR_DINNE', 'HASH_CR_LKEY', 'HASH_STR_NBW',
    'HASH_STR_NBW_0', 'HASH_STR_NBW_1', 'HASH_STR_NBW_2', 'HASH_STR_NBW_3',
    'HASH_STR_NBW_4', 'HASH_STR_DCAL', 'HASH_IMR_DINIM', 'HASH_IMR_DCIM',
    'HASH_SR_DINIS', 'HASH_SR_DCIS', 'HASH_SR_DMAS', 'HASH_SR_BUSY', 'I2C_CR1_PE',
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
    'I2C_CCR_CCR', 'I2C_CCR_DUTY', 'I2C_CCR_FS', 'I2C_TRISE_TRISE', 'IWDG_KR_KEY',
    'IWDG_PR_PR', 'IWDG_PR_PR_0', 'IWDG_PR_PR_1', 'IWDG_PR_PR_2', 'IWDG_RLR_RL',
    'IWDG_SR_PVU', 'IWDG_SR_RVU', 'PWR_CR_LPDS', 'PWR_CR_PDDS', 'PWR_CR_CWUF',
    'PWR_CR_CSBF', 'PWR_CR_PVDE', 'PWR_CR_PLS', 'PWR_CR_PLS_0', 'PWR_CR_PLS_1',
    'PWR_CR_PLS_2', 'PWR_CR_PLS_LEV0', 'PWR_CR_PLS_LEV1', 'PWR_CR_PLS_LEV2',
    'PWR_CR_PLS_LEV3', 'PWR_CR_PLS_LEV4', 'PWR_CR_PLS_LEV5', 'PWR_CR_PLS_LEV6',
    'PWR_CR_PLS_LEV7', 'PWR_CR_DBP', 'PWR_CR_FPDS', 'PWR_CR_VOS', 'PWR_CR_PMODE',
    'PWR_CSR_WUF', 'PWR_CSR_SBF', 'PWR_CSR_PVDO', 'PWR_CSR_BRR', 'PWR_CSR_EWUP',
    'PWR_CSR_BRE', 'PWR_CSR_VOSRDY', 'PWR_CSR_REGRDY', 'RCC_CR_HSION', 'RCC_CR_HSIRDY',
    'RCC_CR_HSITRIM', 'RCC_CR_HSITRIM_0', 'RCC_CR_HSITRIM_1', 'RCC_CR_HSITRIM_2',
    'RCC_CR_HSITRIM_3', 'RCC_CR_HSITRIM_4', 'RCC_CR_HSICAL', 'RCC_CR_HSICAL_0',
    'RCC_CR_HSICAL_1', 'RCC_CR_HSICAL_2', 'RCC_CR_HSICAL_3', 'RCC_CR_HSICAL_4',
    'RCC_CR_HSICAL_5', 'RCC_CR_HSICAL_6', 'RCC_CR_HSICAL_7', 'RCC_CR_HSEON',
    'RCC_CR_HSERDY', 'RCC_CR_HSEBYP', 'RCC_CR_CSSON', 'RCC_CR_PLLON', 'RCC_CR_PLLRDY',
    'RCC_CR_PLLI2SON', 'RCC_CR_PLLI2SRDY', 'RCC_PLLCFGR_PLLM', 'RCC_PLLCFGR_PLLM_0',
    'RCC_PLLCFGR_PLLM_1', 'RCC_PLLCFGR_PLLM_2', 'RCC_PLLCFGR_PLLM_3',
    'RCC_PLLCFGR_PLLM_4', 'RCC_PLLCFGR_PLLM_5', 'RCC_PLLCFGR_PLLN',
    'RCC_PLLCFGR_PLLN_0', 'RCC_PLLCFGR_PLLN_1', 'RCC_PLLCFGR_PLLN_2',
    'RCC_PLLCFGR_PLLN_3', 'RCC_PLLCFGR_PLLN_4', 'RCC_PLLCFGR_PLLN_5',
    'RCC_PLLCFGR_PLLN_6', 'RCC_PLLCFGR_PLLN_7', 'RCC_PLLCFGR_PLLN_8',
    'RCC_PLLCFGR_PLLP', 'RCC_PLLCFGR_PLLP_0', 'RCC_PLLCFGR_PLLP_1',
    'RCC_PLLCFGR_PLLSRC', 'RCC_PLLCFGR_PLLSRC_HSE', 'RCC_PLLCFGR_PLLSRC_HSI',
    'RCC_PLLCFGR_PLLQ', 'RCC_PLLCFGR_PLLQ_0', 'RCC_PLLCFGR_PLLQ_1',
    'RCC_PLLCFGR_PLLQ_2', 'RCC_PLLCFGR_PLLQ_3', 'RCC_CFGR_SW', 'RCC_CFGR_SW_0',
    'RCC_CFGR_SW_1', 'RCC_CFGR_SW_HSI', 'RCC_CFGR_SW_HSE', 'RCC_CFGR_SW_PLL',
    'RCC_CFGR_SWS', 'RCC_CFGR_SWS_0', 'RCC_CFGR_SWS_1', 'RCC_CFGR_SWS_HSI',
    'RCC_CFGR_SWS_HSE', 'RCC_CFGR_SWS_PLL', 'RCC_CFGR_HPRE', 'RCC_CFGR_HPRE_0',
    'RCC_CFGR_HPRE_1', 'RCC_CFGR_HPRE_2', 'RCC_CFGR_HPRE_3', 'RCC_CFGR_HPRE_DIV1',
    'RCC_CFGR_HPRE_DIV2', 'RCC_CFGR_HPRE_DIV4', 'RCC_CFGR_HPRE_DIV8',
    'RCC_CFGR_HPRE_DIV16', 'RCC_CFGR_HPRE_DIV64', 'RCC_CFGR_HPRE_DIV128',
    'RCC_CFGR_HPRE_DIV256', 'RCC_CFGR_HPRE_DIV512', 'RCC_CFGR_PPRE1',
    'RCC_CFGR_PPRE1_0', 'RCC_CFGR_PPRE1_1', 'RCC_CFGR_PPRE1_2', 'RCC_CFGR_PPRE1_DIV1',
    'RCC_CFGR_PPRE1_DIV2', 'RCC_CFGR_PPRE1_DIV4', 'RCC_CFGR_PPRE1_DIV8',
    'RCC_CFGR_PPRE1_DIV16', 'RCC_CFGR_PPRE2', 'RCC_CFGR_PPRE2_0', 'RCC_CFGR_PPRE2_1',
    'RCC_CFGR_PPRE2_2', 'RCC_CFGR_PPRE2_DIV1', 'RCC_CFGR_PPRE2_DIV2',
    'RCC_CFGR_PPRE2_DIV4', 'RCC_CFGR_PPRE2_DIV8', 'RCC_CFGR_PPRE2_DIV16',
    'RCC_CFGR_RTCPRE', 'RCC_CFGR_RTCPRE_0', 'RCC_CFGR_RTCPRE_1', 'RCC_CFGR_RTCPRE_2',
    'RCC_CFGR_RTCPRE_3', 'RCC_CFGR_RTCPRE_4', 'RCC_CFGR_MCO1', 'RCC_CFGR_MCO1_0',
    'RCC_CFGR_MCO1_1', 'RCC_CFGR_I2SSRC', 'RCC_CFGR_MCO1PRE', 'RCC_CFGR_MCO1PRE_0',
    'RCC_CFGR_MCO1PRE_1', 'RCC_CFGR_MCO1PRE_2', 'RCC_CFGR_MCO2PRE',
    'RCC_CFGR_MCO2PRE_0', 'RCC_CFGR_MCO2PRE_1', 'RCC_CFGR_MCO2PRE_2', 'RCC_CFGR_MCO2',
    'RCC_CFGR_MCO2_0', 'RCC_CFGR_MCO2_1', 'RCC_CIR_LSIRDYF', 'RCC_CIR_LSERDYF',
    'RCC_CIR_HSIRDYF', 'RCC_CIR_HSERDYF', 'RCC_CIR_PLLRDYF', 'RCC_CIR_PLLI2SRDYF',
    'RCC_CIR_CSSF', 'RCC_CIR_LSIRDYIE', 'RCC_CIR_LSERDYIE', 'RCC_CIR_HSIRDYIE',
    'RCC_CIR_HSERDYIE', 'RCC_CIR_PLLRDYIE', 'RCC_CIR_PLLI2SRDYIE', 'RCC_CIR_LSIRDYC',
    'RCC_CIR_LSERDYC', 'RCC_CIR_HSIRDYC', 'RCC_CIR_HSERDYC', 'RCC_CIR_PLLRDYC',
    'RCC_CIR_PLLI2SRDYC', 'RCC_CIR_CSSC', 'RCC_AHB1RSTR_GPIOARST',
    'RCC_AHB1RSTR_GPIOBRST', 'RCC_AHB1RSTR_GPIOCRST', 'RCC_AHB1RSTR_GPIODRST',
    'RCC_AHB1RSTR_GPIOERST', 'RCC_AHB1RSTR_GPIOFRST', 'RCC_AHB1RSTR_GPIOGRST',
    'RCC_AHB1RSTR_GPIOHRST', 'RCC_AHB1RSTR_GPIOIRST', 'RCC_AHB1RSTR_CRCRST',
    'RCC_AHB1RSTR_DMA1RST', 'RCC_AHB1RSTR_DMA2RST', 'RCC_AHB1RSTR_ETHMACRST',
    'RCC_AHB1RSTR_OTGHRST', 'RCC_AHB2RSTR_DCMIRST', 'RCC_AHB2RSTR_CRYPRST',
    'RCC_AHB2RSTR_HSAHRST', 'RCC_AHB2RSTR_RNGRST', 'RCC_AHB2RSTR_OTGFSRST',
    'RCC_AHB3RSTR_FSMCRST', 'RCC_APB1RSTR_TIM2RST', 'RCC_APB1RSTR_TIM3RST',
    'RCC_APB1RSTR_TIM4RST', 'RCC_APB1RSTR_TIM5RST', 'RCC_APB1RSTR_TIM6RST',
    'RCC_APB1RSTR_TIM7RST', 'RCC_APB1RSTR_TIM12RST', 'RCC_APB1RSTR_TIM13RST',
    'RCC_APB1RSTR_TIM14RST', 'RCC_APB1RSTR_WWDGEN', 'RCC_APB1RSTR_SPI2RST',
    'RCC_APB1RSTR_SPI3RST', 'RCC_APB1RSTR_USART2RST', 'RCC_APB1RSTR_USART3RST',
    'RCC_APB1RSTR_UART4RST', 'RCC_APB1RSTR_UART5RST', 'RCC_APB1RSTR_I2C1RST',
    'RCC_APB1RSTR_I2C2RST', 'RCC_APB1RSTR_I2C3RST', 'RCC_APB1RSTR_CAN1RST',
    'RCC_APB1RSTR_CAN2RST', 'RCC_APB1RSTR_PWRRST', 'RCC_APB1RSTR_DACRST',
    'RCC_APB2RSTR_TIM1RST', 'RCC_APB2RSTR_TIM8RST', 'RCC_APB2RSTR_USART1RST',
    'RCC_APB2RSTR_USART6RST', 'RCC_APB2RSTR_ADCRST', 'RCC_APB2RSTR_SDIORST',
    'RCC_APB2RSTR_SPI1RST', 'RCC_APB2RSTR_SYSCFGRST', 'RCC_APB2RSTR_TIM9RST',
    'RCC_APB2RSTR_TIM10RST', 'RCC_APB2RSTR_TIM11RST', 'RCC_APB2RSTR_SPI1',
    'RCC_AHB1ENR_GPIOAEN', 'RCC_AHB1ENR_GPIOBEN', 'RCC_AHB1ENR_GPIOCEN',
    'RCC_AHB1ENR_GPIODEN', 'RCC_AHB1ENR_GPIOEEN', 'RCC_AHB1ENR_GPIOFEN',
    'RCC_AHB1ENR_GPIOGEN', 'RCC_AHB1ENR_GPIOHEN', 'RCC_AHB1ENR_GPIOIEN',
    'RCC_AHB1ENR_CRCEN', 'RCC_AHB1ENR_BKPSRAMEN', 'RCC_AHB1ENR_CCMDATARAMEN',
    'RCC_AHB1ENR_DMA1EN', 'RCC_AHB1ENR_DMA2EN', 'RCC_AHB1ENR_ETHMACEN',
    'RCC_AHB1ENR_ETHMACTXEN', 'RCC_AHB1ENR_ETHMACRXEN', 'RCC_AHB1ENR_ETHMACPTPEN',
    'RCC_AHB1ENR_OTGHSEN', 'RCC_AHB1ENR_OTGHSULPIEN', 'RCC_AHB2ENR_DCMIEN',
    'RCC_AHB2ENR_CRYPEN', 'RCC_AHB2ENR_HASHEN', 'RCC_AHB2ENR_RNGEN',
    'RCC_AHB2ENR_OTGFSEN', 'RCC_AHB3ENR_FSMCEN', 'RCC_APB1ENR_TIM2EN',
    'RCC_APB1ENR_TIM3EN', 'RCC_APB1ENR_TIM4EN', 'RCC_APB1ENR_TIM5EN',
    'RCC_APB1ENR_TIM6EN', 'RCC_APB1ENR_TIM7EN', 'RCC_APB1ENR_TIM12EN',
    'RCC_APB1ENR_TIM13EN', 'RCC_APB1ENR_TIM14EN', 'RCC_APB1ENR_WWDGEN',
    'RCC_APB1ENR_SPI2EN', 'RCC_APB1ENR_SPI3EN', 'RCC_APB1ENR_USART2EN',
    'RCC_APB1ENR_USART3EN', 'RCC_APB1ENR_UART4EN', 'RCC_APB1ENR_UART5EN',
    'RCC_APB1ENR_I2C1EN', 'RCC_APB1ENR_I2C2EN', 'RCC_APB1ENR_I2C3EN',
    'RCC_APB1ENR_CAN1EN', 'RCC_APB1ENR_CAN2EN', 'RCC_APB1ENR_PWREN',
    'RCC_APB1ENR_DACEN', 'RCC_APB2ENR_TIM1EN', 'RCC_APB2ENR_TIM8EN',
    'RCC_APB2ENR_USART1EN', 'RCC_APB2ENR_USART6EN', 'RCC_APB2ENR_ADC1EN',
    'RCC_APB2ENR_ADC2EN', 'RCC_APB2ENR_ADC3EN', 'RCC_APB2ENR_SDIOEN',
    'RCC_APB2ENR_SPI1EN', 'RCC_APB2ENR_SYSCFGEN', 'RCC_APB2ENR_TIM11EN',
    'RCC_APB2ENR_TIM10EN', 'RCC_APB2ENR_TIM9EN', 'RCC_AHB1LPENR_GPIOALPEN',
    'RCC_AHB1LPENR_GPIOBLPEN', 'RCC_AHB1LPENR_GPIOCLPEN', 'RCC_AHB1LPENR_GPIODLPEN',
    'RCC_AHB1LPENR_GPIOELPEN', 'RCC_AHB1LPENR_GPIOFLPEN', 'RCC_AHB1LPENR_GPIOGLPEN',
    'RCC_AHB1LPENR_GPIOHLPEN', 'RCC_AHB1LPENR_GPIOILPEN', 'RCC_AHB1LPENR_CRCLPEN',
    'RCC_AHB1LPENR_FLITFLPEN', 'RCC_AHB1LPENR_SRAM1LPEN', 'RCC_AHB1LPENR_SRAM2LPEN',
    'RCC_AHB1LPENR_BKPSRAMLPEN', 'RCC_AHB1LPENR_DMA1LPEN', 'RCC_AHB1LPENR_DMA2LPEN',
    'RCC_AHB1LPENR_ETHMACLPEN', 'RCC_AHB1LPENR_ETHMACTXLPEN',
    'RCC_AHB1LPENR_ETHMACRXLPEN', 'RCC_AHB1LPENR_ETHMACPTPLPEN',
    'RCC_AHB1LPENR_OTGHSLPEN', 'RCC_AHB1LPENR_OTGHSULPILPEN', 'RCC_AHB2LPENR_DCMILPEN',
    'RCC_AHB2LPENR_CRYPLPEN', 'RCC_AHB2LPENR_HASHLPEN', 'RCC_AHB2LPENR_RNGLPEN',
    'RCC_AHB2LPENR_OTGFSLPEN', 'RCC_AHB3LPENR_FSMCLPEN', 'RCC_APB1LPENR_TIM2LPEN',
    'RCC_APB1LPENR_TIM3LPEN', 'RCC_APB1LPENR_TIM4LPEN', 'RCC_APB1LPENR_TIM5LPEN',
    'RCC_APB1LPENR_TIM6LPEN', 'RCC_APB1LPENR_TIM7LPEN', 'RCC_APB1LPENR_TIM12LPEN',
    'RCC_APB1LPENR_TIM13LPEN', 'RCC_APB1LPENR_TIM14LPEN', 'RCC_APB1LPENR_WWDGLPEN',
    'RCC_APB1LPENR_SPI2LPEN', 'RCC_APB1LPENR_SPI3LPEN', 'RCC_APB1LPENR_USART2LPEN',
    'RCC_APB1LPENR_USART3LPEN', 'RCC_APB1LPENR_UART4LPEN', 'RCC_APB1LPENR_UART5LPEN',
    'RCC_APB1LPENR_I2C1LPEN', 'RCC_APB1LPENR_I2C2LPEN', 'RCC_APB1LPENR_I2C3LPEN',
    'RCC_APB1LPENR_CAN1LPEN', 'RCC_APB1LPENR_CAN2LPEN', 'RCC_APB1LPENR_PWRLPEN',
    'RCC_APB1LPENR_DACLPEN', 'RCC_APB2LPENR_TIM1LPEN', 'RCC_APB2LPENR_TIM8LPEN',
    'RCC_APB2LPENR_USART1LPEN', 'RCC_APB2LPENR_USART6LPEN', 'RCC_APB2LPENR_ADC1LPEN',
    'RCC_APB2LPENR_ADC2PEN', 'RCC_APB2LPENR_ADC3LPEN', 'RCC_APB2LPENR_SDIOLPEN',
    'RCC_APB2LPENR_SPI1LPEN', 'RCC_APB2LPENR_SYSCFGLPEN', 'RCC_APB2LPENR_TIM9LPEN',
    'RCC_APB2LPENR_TIM10LPEN', 'RCC_APB2LPENR_TIM11LPEN', 'RCC_BDCR_LSEON',
    'RCC_BDCR_LSERDY', 'RCC_BDCR_LSEBYP', 'RCC_BDCR_RTCSEL', 'RCC_BDCR_RTCSEL_0',
    'RCC_BDCR_RTCSEL_1', 'RCC_BDCR_RTCEN', 'RCC_BDCR_BDRST', 'RCC_CSR_LSION',
    'RCC_CSR_LSIRDY', 'RCC_CSR_RMVF', 'RCC_CSR_BORRSTF', 'RCC_CSR_PADRSTF',
    'RCC_CSR_PORRSTF', 'RCC_CSR_SFTRSTF', 'RCC_CSR_WDGRSTF', 'RCC_CSR_WWDGRSTF',
    'RCC_CSR_LPWRRSTF', 'RCC_SSCGR_MODPER', 'RCC_SSCGR_INCSTEP', 'RCC_SSCGR_SPREADSEL',
    'RCC_SSCGR_SSCGEN', 'RCC_PLLI2SCFGR_PLLI2SN', 'RCC_PLLI2SCFGR_PLLI2SR',
    'RNG_CR_RNGEN', 'RNG_CR_IE', 'RNG_SR_DRDY', 'RNG_SR_CECS', 'RNG_SR_SECS',
    'RNG_SR_CEIS', 'RNG_SR_SEIS', 'RTC_TR_PM', 'RTC_TR_HT', 'RTC_TR_HT_0',
    'RTC_TR_HT_1', 'RTC_TR_HU', 'RTC_TR_HU_0', 'RTC_TR_HU_1', 'RTC_TR_HU_2',
    'RTC_TR_HU_3', 'RTC_TR_MNT', 'RTC_TR_MNT_0', 'RTC_TR_MNT_1', 'RTC_TR_MNT_2',
    'RTC_TR_MNU', 'RTC_TR_MNU_0', 'RTC_TR_MNU_1', 'RTC_TR_MNU_2', 'RTC_TR_MNU_3',
    'RTC_TR_ST', 'RTC_TR_ST_0', 'RTC_TR_ST_1', 'RTC_TR_ST_2', 'RTC_TR_SU',
    'RTC_TR_SU_0', 'RTC_TR_SU_1', 'RTC_TR_SU_2', 'RTC_TR_SU_3', 'RTC_DR_YT',
    'RTC_DR_YT_0', 'RTC_DR_YT_1', 'RTC_DR_YT_2', 'RTC_DR_YT_3', 'RTC_DR_YU',
    'RTC_DR_YU_0', 'RTC_DR_YU_1', 'RTC_DR_YU_2', 'RTC_DR_YU_3', 'RTC_DR_WDU',
    'RTC_DR_WDU_0', 'RTC_DR_WDU_1', 'RTC_DR_WDU_2', 'RTC_DR_MT', 'RTC_DR_MU',
    'RTC_DR_MU_0', 'RTC_DR_MU_1', 'RTC_DR_MU_2', 'RTC_DR_MU_3', 'RTC_DR_DT',
    'RTC_DR_DT_0', 'RTC_DR_DT_1', 'RTC_DR_DU', 'RTC_DR_DU_0', 'RTC_DR_DU_1',
    'RTC_DR_DU_2', 'RTC_DR_DU_3', 'RTC_CR_COE', 'RTC_CR_OSEL', 'RTC_CR_OSEL_0',
    'RTC_CR_OSEL_1', 'RTC_CR_POL', 'RTC_CR_COSEL', 'RTC_CR_BCK', 'RTC_CR_SUB1H',
    'RTC_CR_ADD1H', 'RTC_CR_TSIE', 'RTC_CR_WUTIE', 'RTC_CR_ALRBIE', 'RTC_CR_ALRAIE',
    'RTC_CR_TSE', 'RTC_CR_WUTE', 'RTC_CR_ALRBE', 'RTC_CR_ALRAE', 'RTC_CR_DCE',
    'RTC_CR_FMT', 'RTC_CR_BYPSHAD', 'RTC_CR_REFCKON', 'RTC_CR_TSEDGE', 'RTC_CR_WUCKSEL',
    'RTC_CR_WUCKSEL_0', 'RTC_CR_WUCKSEL_1', 'RTC_CR_WUCKSEL_2', 'RTC_ISR_RECALPF',
    'RTC_ISR_TAMP1F', 'RTC_ISR_TSOVF', 'RTC_ISR_TSF', 'RTC_ISR_WUTF', 'RTC_ISR_ALRBF',
    'RTC_ISR_ALRAF', 'RTC_ISR_INIT', 'RTC_ISR_INITF', 'RTC_ISR_RSF', 'RTC_ISR_INITS',
    'RTC_ISR_SHPF', 'RTC_ISR_WUTWF', 'RTC_ISR_ALRBWF', 'RTC_ISR_ALRAWF',
    'RTC_PRER_PREDIV_A', 'RTC_PRER_PREDIV_S', 'RTC_WUTR_WUT', 'RTC_CALIBR_DCS',
    'RTC_CALIBR_DC', 'RTC_ALRMAR_MSK4', 'RTC_ALRMAR_WDSEL', 'RTC_ALRMAR_DT',
    'RTC_ALRMAR_DT_0', 'RTC_ALRMAR_DT_1', 'RTC_ALRMAR_DU', 'RTC_ALRMAR_DU_0',
    'RTC_ALRMAR_DU_1', 'RTC_ALRMAR_DU_2', 'RTC_ALRMAR_DU_3', 'RTC_ALRMAR_MSK3',
    'RTC_ALRMAR_PM', 'RTC_ALRMAR_HT', 'RTC_ALRMAR_HT_0', 'RTC_ALRMAR_HT_1',
    'RTC_ALRMAR_HU', 'RTC_ALRMAR_HU_0', 'RTC_ALRMAR_HU_1', 'RTC_ALRMAR_HU_2',
    'RTC_ALRMAR_HU_3', 'RTC_ALRMAR_MSK2', 'RTC_ALRMAR_MNT', 'RTC_ALRMAR_MNT_0',
    'RTC_ALRMAR_MNT_1', 'RTC_ALRMAR_MNT_2', 'RTC_ALRMAR_MNU', 'RTC_ALRMAR_MNU_0',
    'RTC_ALRMAR_MNU_1', 'RTC_ALRMAR_MNU_2', 'RTC_ALRMAR_MNU_3', 'RTC_ALRMAR_MSK1',
    'RTC_ALRMAR_ST', 'RTC_ALRMAR_ST_0', 'RTC_ALRMAR_ST_1', 'RTC_ALRMAR_ST_2',
    'RTC_ALRMAR_SU', 'RTC_ALRMAR_SU_0', 'RTC_ALRMAR_SU_1', 'RTC_ALRMAR_SU_2',
    'RTC_ALRMAR_SU_3', 'RTC_ALRMBR_MSK4', 'RTC_ALRMBR_WDSEL', 'RTC_ALRMBR_DT',
    'RTC_ALRMBR_DT_0', 'RTC_ALRMBR_DT_1', 'RTC_ALRMBR_DU', 'RTC_ALRMBR_DU_0',
    'RTC_ALRMBR_DU_1', 'RTC_ALRMBR_DU_2', 'RTC_ALRMBR_DU_3', 'RTC_ALRMBR_MSK3',
    'RTC_ALRMBR_PM', 'RTC_ALRMBR_HT', 'RTC_ALRMBR_HT_0', 'RTC_ALRMBR_HT_1',
    'RTC_ALRMBR_HU', 'RTC_ALRMBR_HU_0', 'RTC_ALRMBR_HU_1', 'RTC_ALRMBR_HU_2',
    'RTC_ALRMBR_HU_3', 'RTC_ALRMBR_MSK2', 'RTC_ALRMBR_MNT', 'RTC_ALRMBR_MNT_0',
    'RTC_ALRMBR_MNT_1', 'RTC_ALRMBR_MNT_2', 'RTC_ALRMBR_MNU', 'RTC_ALRMBR_MNU_0',
    'RTC_ALRMBR_MNU_1', 'RTC_ALRMBR_MNU_2', 'RTC_ALRMBR_MNU_3', 'RTC_ALRMBR_MSK1',
    'RTC_ALRMBR_ST', 'RTC_ALRMBR_ST_0', 'RTC_ALRMBR_ST_1', 'RTC_ALRMBR_ST_2',
    'RTC_ALRMBR_SU', 'RTC_ALRMBR_SU_0', 'RTC_ALRMBR_SU_1', 'RTC_ALRMBR_SU_2',
    'RTC_ALRMBR_SU_3', 'RTC_WPR_KEY', 'RTC_SSR_SS', 'RTC_SHIFTR_SUBFS',
    'RTC_SHIFTR_ADD1S', 'RTC_TSTR_PM', 'RTC_TSTR_HT', 'RTC_TSTR_HT_0', 'RTC_TSTR_HT_1',
    'RTC_TSTR_HU', 'RTC_TSTR_HU_0', 'RTC_TSTR_HU_1', 'RTC_TSTR_HU_2', 'RTC_TSTR_HU_3',
    'RTC_TSTR_MNT', 'RTC_TSTR_MNT_0', 'RTC_TSTR_MNT_1', 'RTC_TSTR_MNT_2',
    'RTC_TSTR_MNU', 'RTC_TSTR_MNU_0', 'RTC_TSTR_MNU_1', 'RTC_TSTR_MNU_2',
    'RTC_TSTR_MNU_3', 'RTC_TSTR_ST', 'RTC_TSTR_ST_0', 'RTC_TSTR_ST_1', 'RTC_TSTR_ST_2',
    'RTC_TSTR_SU', 'RTC_TSTR_SU_0', 'RTC_TSTR_SU_1', 'RTC_TSTR_SU_2', 'RTC_TSTR_SU_3',
    'RTC_TSDR_WDU', 'RTC_TSDR_WDU_0', 'RTC_TSDR_WDU_1', 'RTC_TSDR_WDU_2', 'RTC_TSDR_MT',
    'RTC_TSDR_MU', 'RTC_TSDR_MU_0', 'RTC_TSDR_MU_1', 'RTC_TSDR_MU_2', 'RTC_TSDR_MU_3',
    'RTC_TSDR_DT', 'RTC_TSDR_DT_0', 'RTC_TSDR_DT_1', 'RTC_TSDR_DU', 'RTC_TSDR_DU_0',
    'RTC_TSDR_DU_1', 'RTC_TSDR_DU_2', 'RTC_TSDR_DU_3', 'RTC_TSSSR_SS', 'RTC_CALR_CALP',
    'RTC_CALR_CALW8', 'RTC_CALR_CALW16', 'RTC_CALR_CALM', 'RTC_CALR_CALM_0',
    'RTC_CALR_CALM_1', 'RTC_CALR_CALM_2', 'RTC_CALR_CALM_3', 'RTC_CALR_CALM_4',
    'RTC_CALR_CALM_5', 'RTC_CALR_CALM_6', 'RTC_CALR_CALM_7', 'RTC_CALR_CALM_8',
    'RTC_TAFCR_ALARMOUTTYPE', 'RTC_TAFCR_TSINSEL', 'RTC_TAFCR_TAMPINSEL',
    'RTC_TAFCR_TAMPPUDIS', 'RTC_TAFCR_TAMPPRCH', 'RTC_TAFCR_TAMPPRCH_0',
    'RTC_TAFCR_TAMPPRCH_1', 'RTC_TAFCR_TAMPFLT', 'RTC_TAFCR_TAMPFLT_0',
    'RTC_TAFCR_TAMPFLT_1', 'RTC_TAFCR_TAMPFREQ', 'RTC_TAFCR_TAMPFREQ_0',
    'RTC_TAFCR_TAMPFREQ_1', 'RTC_TAFCR_TAMPFREQ_2', 'RTC_TAFCR_TAMPTS',
    'RTC_TAFCR_TAMPIE', 'RTC_TAFCR_TAMP1TRG', 'RTC_TAFCR_TAMP1E', 'RTC_ALRMASSR_MASKSS',
    'RTC_ALRMASSR_MASKSS_0', 'RTC_ALRMASSR_MASKSS_1', 'RTC_ALRMASSR_MASKSS_2',
    'RTC_ALRMASSR_MASKSS_3', 'RTC_ALRMASSR_SS', 'RTC_ALRMBSSR_MASKSS',
    'RTC_ALRMBSSR_MASKSS_0', 'RTC_ALRMBSSR_MASKSS_1', 'RTC_ALRMBSSR_MASKSS_2',
    'RTC_ALRMBSSR_MASKSS_3', 'RTC_ALRMBSSR_SS', 'RTC_BKP0R', 'RTC_BKP1R', 'RTC_BKP2R',
    'RTC_BKP3R', 'RTC_BKP4R', 'RTC_BKP5R', 'RTC_BKP6R', 'RTC_BKP7R', 'RTC_BKP8R',
    'RTC_BKP9R', 'RTC_BKP10R', 'RTC_BKP11R', 'RTC_BKP12R', 'RTC_BKP13R', 'RTC_BKP14R',
    'RTC_BKP15R', 'RTC_BKP16R', 'RTC_BKP17R', 'RTC_BKP18R', 'RTC_BKP19R',
    'SDIO_POWER_PWRCTRL', 'SDIO_POWER_PWRCTRL_0', 'SDIO_POWER_PWRCTRL_1',
    'SDIO_CLKCR_CLKDIV', 'SDIO_CLKCR_CLKEN', 'SDIO_CLKCR_PWRSAV', 'SDIO_CLKCR_BYPASS',
    'SDIO_CLKCR_WIDBUS', 'SDIO_CLKCR_WIDBUS_0', 'SDIO_CLKCR_WIDBUS_1',
    'SDIO_CLKCR_NEGEDGE', 'SDIO_CLKCR_HWFC_EN', 'SDIO_ARG_CMDARG', 'SDIO_CMD_CMDINDEX',
    'SDIO_CMD_WAITRESP', 'SDIO_CMD_WAITRESP_0', 'SDIO_CMD_WAITRESP_1',
    'SDIO_CMD_WAITINT', 'SDIO_CMD_WAITPEND', 'SDIO_CMD_CPSMEN', 'SDIO_CMD_SDIOSUSPEND',
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
    'SDIO_FIFOCNT_FIFOCOUNT', 'SDIO_FIFO_FIFODATA', 'SPI_CR1_CPHA', 'SPI_CR1_CPOL',
    'SPI_CR1_MSTR', 'SPI_CR1_BR', 'SPI_CR1_BR_0', 'SPI_CR1_BR_1', 'SPI_CR1_BR_2',
    'SPI_CR1_SPE', 'SPI_CR1_LSBFIRST', 'SPI_CR1_SSI', 'SPI_CR1_SSM', 'SPI_CR1_RXONLY',
    'SPI_CR1_DFF', 'SPI_CR1_CRCNEXT', 'SPI_CR1_CRCEN', 'SPI_CR1_BIDIOE',
    'SPI_CR1_BIDIMODE', 'SPI_CR2_RXDMAEN', 'SPI_CR2_TXDMAEN', 'SPI_CR2_SSOE',
    'SPI_CR2_ERRIE', 'SPI_CR2_RXNEIE', 'SPI_CR2_TXEIE', 'SPI_SR_RXNE', 'SPI_SR_TXE',
    'SPI_SR_CHSIDE', 'SPI_SR_UDR', 'SPI_SR_CRCERR', 'SPI_SR_MODF', 'SPI_SR_OVR',
    'SPI_SR_BSY', 'SPI_DR_DR', 'SPI_CRCPR_CRCPOLY', 'SPI_RXCRCR_RXCRC',
    'SPI_TXCRCR_TXCRC', 'SPI_I2SCFGR_CHLEN', 'SPI_I2SCFGR_DATLEN',
    'SPI_I2SCFGR_DATLEN_0', 'SPI_I2SCFGR_DATLEN_1', 'SPI_I2SCFGR_CKPOL',
    'SPI_I2SCFGR_I2SSTD', 'SPI_I2SCFGR_I2SSTD_0', 'SPI_I2SCFGR_I2SSTD_1',
    'SPI_I2SCFGR_PCMSYNC', 'SPI_I2SCFGR_I2SCFG', 'SPI_I2SCFGR_I2SCFG_0',
    'SPI_I2SCFGR_I2SCFG_1', 'SPI_I2SCFGR_I2SE', 'SPI_I2SCFGR_I2SMOD',
    'SPI_I2SPR_I2SDIV', 'SPI_I2SPR_ODD', 'SPI_I2SPR_MCKOE', 'SYSCFG_MEMRMP_MEM_MODE',
    'SYSCFG_MEMRMP_MEM_MODE_0', 'SYSCFG_MEMRMP_MEM_MODE_1', 'SYSCFG_PMC_MII_RMII_SEL',
    'SYSCFG_PMC_MII_RMII', 'SYSCFG_EXTICR1_EXTI0', 'SYSCFG_EXTICR1_EXTI1',
    'SYSCFG_EXTICR1_EXTI2', 'SYSCFG_EXTICR1_EXTI3', 'SYSCFG_EXTICR1_EXTI0_PA',
    'SYSCFG_EXTICR1_EXTI0_PB', 'SYSCFG_EXTICR1_EXTI0_PC', 'SYSCFG_EXTICR1_EXTI0_PD',
    'SYSCFG_EXTICR1_EXTI0_PE', 'SYSCFG_EXTICR1_EXTI0_PF', 'SYSCFG_EXTICR1_EXTI0_PG',
    'SYSCFG_EXTICR1_EXTI0_PH', 'SYSCFG_EXTICR1_EXTI0_PI', 'SYSCFG_EXTICR1_EXTI1_PA',
    'SYSCFG_EXTICR1_EXTI1_PB', 'SYSCFG_EXTICR1_EXTI1_PC', 'SYSCFG_EXTICR1_EXTI1_PD',
    'SYSCFG_EXTICR1_EXTI1_PE', 'SYSCFG_EXTICR1_EXTI1_PF', 'SYSCFG_EXTICR1_EXTI1_PG',
    'SYSCFG_EXTICR1_EXTI1_PH', 'SYSCFG_EXTICR1_EXTI1_PI', 'SYSCFG_EXTICR1_EXTI2_PA',
    'SYSCFG_EXTICR1_EXTI2_PB', 'SYSCFG_EXTICR1_EXTI2_PC', 'SYSCFG_EXTICR1_EXTI2_PD',
    'SYSCFG_EXTICR1_EXTI2_PE', 'SYSCFG_EXTICR1_EXTI2_PF', 'SYSCFG_EXTICR1_EXTI2_PG',
    'SYSCFG_EXTICR1_EXTI2_PH', 'SYSCFG_EXTICR1_EXTI2_PI', 'SYSCFG_EXTICR1_EXTI3_PA',
    'SYSCFG_EXTICR1_EXTI3_PB', 'SYSCFG_EXTICR1_EXTI3_PC', 'SYSCFG_EXTICR1_EXTI3_PD',
    'SYSCFG_EXTICR1_EXTI3_PE', 'SYSCFG_EXTICR1_EXTI3_PF', 'SYSCFG_EXTICR1_EXTI3_PG',
    'SYSCFG_EXTICR1_EXTI3_PH', 'SYSCFG_EXTICR1_EXTI3_PI', 'SYSCFG_EXTICR2_EXTI4',
    'SYSCFG_EXTICR2_EXTI5', 'SYSCFG_EXTICR2_EXTI6', 'SYSCFG_EXTICR2_EXTI7',
    'SYSCFG_EXTICR2_EXTI4_PA', 'SYSCFG_EXTICR2_EXTI4_PB', 'SYSCFG_EXTICR2_EXTI4_PC',
    'SYSCFG_EXTICR2_EXTI4_PD', 'SYSCFG_EXTICR2_EXTI4_PE', 'SYSCFG_EXTICR2_EXTI4_PF',
    'SYSCFG_EXTICR2_EXTI4_PG', 'SYSCFG_EXTICR2_EXTI4_PH', 'SYSCFG_EXTICR2_EXTI4_PI',
    'SYSCFG_EXTICR2_EXTI5_PA', 'SYSCFG_EXTICR2_EXTI5_PB', 'SYSCFG_EXTICR2_EXTI5_PC',
    'SYSCFG_EXTICR2_EXTI5_PD', 'SYSCFG_EXTICR2_EXTI5_PE', 'SYSCFG_EXTICR2_EXTI5_PF',
    'SYSCFG_EXTICR2_EXTI5_PG', 'SYSCFG_EXTICR2_EXTI5_PH', 'SYSCFG_EXTICR2_EXTI5_PI',
    'SYSCFG_EXTICR2_EXTI6_PA', 'SYSCFG_EXTICR2_EXTI6_PB', 'SYSCFG_EXTICR2_EXTI6_PC',
    'SYSCFG_EXTICR2_EXTI6_PD', 'SYSCFG_EXTICR2_EXTI6_PE', 'SYSCFG_EXTICR2_EXTI6_PF',
    'SYSCFG_EXTICR2_EXTI6_PG', 'SYSCFG_EXTICR2_EXTI6_PH', 'SYSCFG_EXTICR2_EXTI6_PI',
    'SYSCFG_EXTICR2_EXTI7_PA', 'SYSCFG_EXTICR2_EXTI7_PB', 'SYSCFG_EXTICR2_EXTI7_PC',
    'SYSCFG_EXTICR2_EXTI7_PD', 'SYSCFG_EXTICR2_EXTI7_PE', 'SYSCFG_EXTICR2_EXTI7_PF',
    'SYSCFG_EXTICR2_EXTI7_PG', 'SYSCFG_EXTICR2_EXTI7_PH', 'SYSCFG_EXTICR2_EXTI7_PI',
    'SYSCFG_EXTICR3_EXTI8', 'SYSCFG_EXTICR3_EXTI9', 'SYSCFG_EXTICR3_EXTI10',
    'SYSCFG_EXTICR3_EXTI11', 'SYSCFG_EXTICR3_EXTI8_PA', 'SYSCFG_EXTICR3_EXTI8_PB',
    'SYSCFG_EXTICR3_EXTI8_PC', 'SYSCFG_EXTICR3_EXTI8_PD', 'SYSCFG_EXTICR3_EXTI8_PE',
    'SYSCFG_EXTICR3_EXTI8_PF', 'SYSCFG_EXTICR3_EXTI8_PG', 'SYSCFG_EXTICR3_EXTI8_PH',
    'SYSCFG_EXTICR3_EXTI8_PI', 'SYSCFG_EXTICR3_EXTI9_PA', 'SYSCFG_EXTICR3_EXTI9_PB',
    'SYSCFG_EXTICR3_EXTI9_PC', 'SYSCFG_EXTICR3_EXTI9_PD', 'SYSCFG_EXTICR3_EXTI9_PE',
    'SYSCFG_EXTICR3_EXTI9_PF', 'SYSCFG_EXTICR3_EXTI9_PG', 'SYSCFG_EXTICR3_EXTI9_PH',
    'SYSCFG_EXTICR3_EXTI9_PI', 'SYSCFG_EXTICR3_EXTI10_PA', 'SYSCFG_EXTICR3_EXTI10_PB',
    'SYSCFG_EXTICR3_EXTI10_PC', 'SYSCFG_EXTICR3_EXTI10_PD', 'SYSCFG_EXTICR3_EXTI10_PE',
    'SYSCFG_EXTICR3_EXTI10_PF', 'SYSCFG_EXTICR3_EXTI10_PG', 'SYSCFG_EXTICR3_EXTI10_PH',
    'SYSCFG_EXTICR3_EXTI10_PI', 'SYSCFG_EXTICR3_EXTI11_PA', 'SYSCFG_EXTICR3_EXTI11_PB',
    'SYSCFG_EXTICR3_EXTI11_PC', 'SYSCFG_EXTICR3_EXTI11_PD', 'SYSCFG_EXTICR3_EXTI11_PE',
    'SYSCFG_EXTICR3_EXTI11_PF', 'SYSCFG_EXTICR3_EXTI11_PG', 'SYSCFG_EXTICR3_EXTI11_PH',
    'SYSCFG_EXTICR3_EXTI11_PI', 'SYSCFG_EXTICR4_EXTI12', 'SYSCFG_EXTICR4_EXTI13',
    'SYSCFG_EXTICR4_EXTI14', 'SYSCFG_EXTICR4_EXTI15', 'SYSCFG_EXTICR4_EXTI12_PA',
    'SYSCFG_EXTICR4_EXTI12_PB', 'SYSCFG_EXTICR4_EXTI12_PC', 'SYSCFG_EXTICR4_EXTI12_PD',
    'SYSCFG_EXTICR4_EXTI12_PE', 'SYSCFG_EXTICR4_EXTI12_PF', 'SYSCFG_EXTICR4_EXTI12_PG',
    'SYSCFG_EXTICR3_EXTI12_PH', 'SYSCFG_EXTICR4_EXTI13_PA', 'SYSCFG_EXTICR4_EXTI13_PB',
    'SYSCFG_EXTICR4_EXTI13_PC', 'SYSCFG_EXTICR4_EXTI13_PD', 'SYSCFG_EXTICR4_EXTI13_PE',
    'SYSCFG_EXTICR4_EXTI13_PF', 'SYSCFG_EXTICR4_EXTI13_PG', 'SYSCFG_EXTICR3_EXTI13_PH',
    'SYSCFG_EXTICR4_EXTI14_PA', 'SYSCFG_EXTICR4_EXTI14_PB', 'SYSCFG_EXTICR4_EXTI14_PC',
    'SYSCFG_EXTICR4_EXTI14_PD', 'SYSCFG_EXTICR4_EXTI14_PE', 'SYSCFG_EXTICR4_EXTI14_PF',
    'SYSCFG_EXTICR4_EXTI14_PG', 'SYSCFG_EXTICR3_EXTI14_PH', 'SYSCFG_EXTICR4_EXTI15_PA',
    'SYSCFG_EXTICR4_EXTI15_PB', 'SYSCFG_EXTICR4_EXTI15_PC', 'SYSCFG_EXTICR4_EXTI15_PD',
    'SYSCFG_EXTICR4_EXTI15_PE', 'SYSCFG_EXTICR4_EXTI15_PF', 'SYSCFG_EXTICR4_EXTI15_PG',
    'SYSCFG_EXTICR3_EXTI15_PH', 'SYSCFG_CMPCR_CMP_PD', 'SYSCFG_CMPCR_READY',
    'TIM_CR1_CEN', 'TIM_CR1_UDIS', 'TIM_CR1_URS', 'TIM_CR1_OPM', 'TIM_CR1_DIR',
    'TIM_CR1_CMS', 'TIM_CR1_CMS_0', 'TIM_CR1_CMS_1', 'TIM_CR1_ARPE', 'TIM_CR1_CKD',
    'TIM_CR1_CKD_0', 'TIM_CR1_CKD_1', 'TIM_CR2_CCPC', 'TIM_CR2_CCUS', 'TIM_CR2_CCDS',
    'TIM_CR2_MMS', 'TIM_CR2_MMS_0', 'TIM_CR2_MMS_1', 'TIM_CR2_MMS_2', 'TIM_CR2_TI1S',
    'TIM_CR2_OIS1', 'TIM_CR2_OIS1N', 'TIM_CR2_OIS2', 'TIM_CR2_OIS2N', 'TIM_CR2_OIS3',
    'TIM_CR2_OIS3N', 'TIM_CR2_OIS4', 'TIM_SMCR_SMS', 'TIM_SMCR_SMS_0', 'TIM_SMCR_SMS_1',
    'TIM_SMCR_SMS_2', 'TIM_SMCR_TS', 'TIM_SMCR_TS_0', 'TIM_SMCR_TS_1', 'TIM_SMCR_TS_2',
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
    'TIM_OR_TI4_RMP', 'TIM_OR_TI4_RMP_0', 'TIM_OR_TI4_RMP_1', 'TIM_OR_ITR1_RMP',
    'TIM_OR_ITR1_RMP_0', 'TIM_OR_ITR1_RMP_1', 'USART_SR_PE', 'USART_SR_FE',
    'USART_SR_NE', 'USART_SR_ORE', 'USART_SR_IDLE', 'USART_SR_RXNE', 'USART_SR_TC',
    'USART_SR_TXE', 'USART_SR_LBD', 'USART_SR_CTS', 'USART_DR_DR',
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
    'USART_GTPR_PSC_7', 'USART_GTPR_GT', 'WWDG_CR_T', 'WWDG_CR_T0', 'WWDG_CR_T1',
    'WWDG_CR_T2', 'WWDG_CR_T3', 'WWDG_CR_T4', 'WWDG_CR_T5', 'WWDG_CR_T6',
    'WWDG_CR_WDGA', 'WWDG_CFR_W', 'WWDG_CFR_W0', 'WWDG_CFR_W1', 'WWDG_CFR_W2',
    'WWDG_CFR_W3', 'WWDG_CFR_W4', 'WWDG_CFR_W5', 'WWDG_CFR_W6', 'WWDG_CFR_WDGTB',
    'WWDG_CFR_WDGTB0', 'WWDG_CFR_WDGTB1', 'WWDG_CFR_EWI', 'WWDG_SR_EWIF',
    'DBGMCU_IDCODE_DEV_ID', 'DBGMCU_IDCODE_REV_ID', 'DBGMCU_CR_DBG_SLEEP',
    'DBGMCU_CR_DBG_STOP', 'DBGMCU_CR_DBG_STANDBY', 'DBGMCU_CR_TRACE_IOEN',
    'DBGMCU_CR_TRACE_MODE', 'DBGMCU_CR_TRACE_MODE_0', 'DBGMCU_CR_TRACE_MODE_1',
    'DBGMCU_APB1_FZ_DBG_TIM2_STOP', 'DBGMCU_APB1_FZ_DBG_TIM3_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM4_STOP', 'DBGMCU_APB1_FZ_DBG_TIM5_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM6_STOP', 'DBGMCU_APB1_FZ_DBG_TIM7_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM12_STOP', 'DBGMCU_APB1_FZ_DBG_TIM13_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM14_STOP', 'DBGMCU_APB1_FZ_DBG_RTC_STOP',
    'DBGMCU_APB1_FZ_DBG_WWDG_STOP', 'DBGMCU_APB1_FZ_DBG_IWDG_STOP',
    'DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT', 'DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT',
    'DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT', 'DBGMCU_APB1_FZ_DBG_CAN1_STOP',
    'DBGMCU_APB1_FZ_DBG_CAN2_STOP', 'DBGMCU_APB1_FZ_DBG_IWDEG_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM1_STOP', 'DBGMCU_APB1_FZ_DBG_TIM8_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM9_STOP', 'DBGMCU_APB1_FZ_DBG_TIM10_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM11_STOP', 'ETH_MACCR_WD', 'ETH_MACCR_JD', 'ETH_MACCR_IFG',
    'ETH_MACCR_IFG_96Bit', 'ETH_MACCR_IFG_88Bit', 'ETH_MACCR_IFG_80Bit',
    'ETH_MACCR_IFG_72Bit', 'ETH_MACCR_IFG_64Bit', 'ETH_MACCR_IFG_56Bit',
    'ETH_MACCR_IFG_48Bit', 'ETH_MACCR_IFG_40Bit', 'ETH_MACCR_CSD', 'ETH_MACCR_FES',
    'ETH_MACCR_ROD', 'ETH_MACCR_LM', 'ETH_MACCR_DM', 'ETH_MACCR_IPCO', 'ETH_MACCR_RD',
    'ETH_MACCR_APCS', 'ETH_MACCR_BL', 'ETH_MACCR_BL_10', 'ETH_MACCR_BL_8',
    'ETH_MACCR_BL_4', 'ETH_MACCR_BL_1', 'ETH_MACCR_DC', 'ETH_MACCR_TE', 'ETH_MACCR_RE',
    'ETH_MACFFR_RA', 'ETH_MACFFR_HPF', 'ETH_MACFFR_SAF', 'ETH_MACFFR_SAIF',
    'ETH_MACFFR_PCF', 'ETH_MACFFR_PCF_BlockAll', 'ETH_MACFFR_PCF_ForwardAll',
    'ETH_MACFFR_PCF_ForwardPassedAddrFilter', 'ETH_MACFFR_BFD', 'ETH_MACFFR_PAM',
    'ETH_MACFFR_DAIF', 'ETH_MACFFR_HM', 'ETH_MACFFR_HU', 'ETH_MACFFR_PM',
    'ETH_MACHTHR_HTH', 'ETH_MACHTLR_HTL', 'ETH_MACMIIAR_PA', 'ETH_MACMIIAR_MR',
    'ETH_MACMIIAR_CR', 'ETH_MACMIIAR_CR_Div42', 'ETH_MACMIIAR_CR_Div62',
    'ETH_MACMIIAR_CR_Div16', 'ETH_MACMIIAR_CR_Div26', 'ETH_MACMIIAR_CR_Div102',
    'ETH_MACMIIAR_MW', 'ETH_MACMIIAR_MB', 'ETH_MACMIIDR_MD', 'ETH_MACFCR_PT',
    'ETH_MACFCR_ZQPD', 'ETH_MACFCR_PLT', 'ETH_MACFCR_PLT_Minus4',
    'ETH_MACFCR_PLT_Minus28', 'ETH_MACFCR_PLT_Minus144', 'ETH_MACFCR_PLT_Minus256',
    'ETH_MACFCR_UPFD', 'ETH_MACFCR_RFCE', 'ETH_MACFCR_TFCE', 'ETH_MACFCR_FCBBPA',
    'ETH_MACVLANTR_VLANTC', 'ETH_MACVLANTR_VLANTI', 'ETH_MACRWUFFR_D',
    'ETH_MACPMTCSR_WFFRPR', 'ETH_MACPMTCSR_GU', 'ETH_MACPMTCSR_WFR',
    'ETH_MACPMTCSR_MPR', 'ETH_MACPMTCSR_WFE', 'ETH_MACPMTCSR_MPE', 'ETH_MACPMTCSR_PD',
    'ETH_MACSR_TSTS', 'ETH_MACSR_MMCTS', 'ETH_MACSR_MMMCRS', 'ETH_MACSR_MMCS',
    'ETH_MACSR_PMTS', 'ETH_MACIMR_TSTIM', 'ETH_MACIMR_PMTIM', 'ETH_MACA0HR_MACA0H',
    'ETH_MACA0LR_MACA0L', 'ETH_MACA1HR_AE', 'ETH_MACA1HR_SA', 'ETH_MACA1HR_MBC',
    'ETH_MACA1HR_MBC_HBits15_8', 'ETH_MACA1HR_MBC_HBits7_0',
    'ETH_MACA1HR_MBC_LBits31_24', 'ETH_MACA1HR_MBC_LBits23_16',
    'ETH_MACA1HR_MBC_LBits15_8', 'ETH_MACA1HR_MBC_LBits7_0', 'ETH_MACA1HR_MACA1H',
    'ETH_MACA1LR_MACA1L', 'ETH_MACA2HR_AE', 'ETH_MACA2HR_SA', 'ETH_MACA2HR_MBC',
    'ETH_MACA2HR_MBC_HBits15_8', 'ETH_MACA2HR_MBC_HBits7_0',
    'ETH_MACA2HR_MBC_LBits31_24', 'ETH_MACA2HR_MBC_LBits23_16',
    'ETH_MACA2HR_MBC_LBits15_8', 'ETH_MACA2HR_MBC_LBits7_0', 'ETH_MACA2HR_MACA2H',
    'ETH_MACA2LR_MACA2L', 'ETH_MACA3HR_AE', 'ETH_MACA3HR_SA', 'ETH_MACA3HR_MBC',
    'ETH_MACA3HR_MBC_HBits15_8', 'ETH_MACA3HR_MBC_HBits7_0',
    'ETH_MACA3HR_MBC_LBits31_24', 'ETH_MACA3HR_MBC_LBits23_16',
    'ETH_MACA3HR_MBC_LBits15_8', 'ETH_MACA3HR_MBC_LBits7_0', 'ETH_MACA3HR_MACA3H',
    'ETH_MACA3LR_MACA3L', 'ETH_MMCCR_MCFHP', 'ETH_MMCCR_MCP', 'ETH_MMCCR_MCF',
    'ETH_MMCCR_ROR', 'ETH_MMCCR_CSR', 'ETH_MMCCR_CR', 'ETH_MMCRIR_RGUFS',
    'ETH_MMCRIR_RFAES', 'ETH_MMCRIR_RFCES', 'ETH_MMCTIR_TGFS', 'ETH_MMCTIR_TGFMSCS',
    'ETH_MMCTIR_TGFSCS', 'ETH_MMCRIMR_RGUFM', 'ETH_MMCRIMR_RFAEM', 'ETH_MMCRIMR_RFCEM',
    'ETH_MMCTIMR_TGFM', 'ETH_MMCTIMR_TGFMSCM', 'ETH_MMCTIMR_TGFSCM',
    'ETH_MMCTGFSCCR_TGFSCC', 'ETH_MMCTGFMSCCR_TGFMSCC', 'ETH_MMCTGFCR_TGFC',
    'ETH_MMCRFCECR_RFCEC', 'ETH_MMCRFAECR_RFAEC', 'ETH_MMCRGUFCR_RGUFC',
    'ETH_PTPTSCR_TSCNT', 'ETH_PTPTSSR_TSSMRME', 'ETH_PTPTSSR_TSSEME',
    'ETH_PTPTSSR_TSSIPV4FE', 'ETH_PTPTSSR_TSSIPV6FE', 'ETH_PTPTSSR_TSSPTPOEFE',
    'ETH_PTPTSSR_TSPTPPSV2E', 'ETH_PTPTSSR_TSSSR', 'ETH_PTPTSSR_TSSARFE',
    'ETH_PTPTSCR_TSARU', 'ETH_PTPTSCR_TSITE', 'ETH_PTPTSCR_TSSTU', 'ETH_PTPTSCR_TSSTI',
    'ETH_PTPTSCR_TSFCU', 'ETH_PTPTSCR_TSE', 'ETH_PTPSSIR_STSSI', 'ETH_PTPTSHR_STS',
    'ETH_PTPTSLR_STPNS', 'ETH_PTPTSLR_STSS', 'ETH_PTPTSHUR_TSUS', 'ETH_PTPTSLUR_TSUPNS',
    'ETH_PTPTSLUR_TSUSS', 'ETH_PTPTSAR_TSA', 'ETH_PTPTTHR_TTSH', 'ETH_PTPTTLR_TTSL',
    'ETH_PTPTSSR_TSTTR', 'ETH_PTPTSSR_TSSO', 'ETH_DMABMR_AAB', 'ETH_DMABMR_FPM',
    'ETH_DMABMR_USP', 'ETH_DMABMR_RDP', 'ETH_DMABMR_RDP_1Beat', 'ETH_DMABMR_RDP_2Beat',
    'ETH_DMABMR_RDP_4Beat', 'ETH_DMABMR_RDP_8Beat', 'ETH_DMABMR_RDP_16Beat',
    'ETH_DMABMR_RDP_32Beat', 'ETH_DMABMR_RDP_4xPBL_4Beat', 'ETH_DMABMR_RDP_4xPBL_8Beat',
    'ETH_DMABMR_RDP_4xPBL_16Beat', 'ETH_DMABMR_RDP_4xPBL_32Beat',
    'ETH_DMABMR_RDP_4xPBL_64Beat', 'ETH_DMABMR_RDP_4xPBL_128Beat', 'ETH_DMABMR_FB',
    'ETH_DMABMR_RTPR', 'ETH_DMABMR_RTPR_1_1', 'ETH_DMABMR_RTPR_2_1',
    'ETH_DMABMR_RTPR_3_1', 'ETH_DMABMR_RTPR_4_1', 'ETH_DMABMR_PBL',
    'ETH_DMABMR_PBL_1Beat', 'ETH_DMABMR_PBL_2Beat', 'ETH_DMABMR_PBL_4Beat',
    'ETH_DMABMR_PBL_8Beat', 'ETH_DMABMR_PBL_16Beat', 'ETH_DMABMR_PBL_32Beat',
    'ETH_DMABMR_PBL_4xPBL_4Beat', 'ETH_DMABMR_PBL_4xPBL_8Beat',
    'ETH_DMABMR_PBL_4xPBL_16Beat', 'ETH_DMABMR_PBL_4xPBL_32Beat',
    'ETH_DMABMR_PBL_4xPBL_64Beat', 'ETH_DMABMR_PBL_4xPBL_128Beat', 'ETH_DMABMR_EDE',
    'ETH_DMABMR_DSL', 'ETH_DMABMR_DA', 'ETH_DMABMR_SR', 'ETH_DMATPDR_TPD',
    'ETH_DMARPDR_RPD', 'ETH_DMARDLAR_SRL', 'ETH_DMATDLAR_STL', 'ETH_DMASR_TSTS',
    'ETH_DMASR_PMTS', 'ETH_DMASR_MMCS', 'ETH_DMASR_EBS', 'ETH_DMASR_EBS_DescAccess',
    'ETH_DMASR_EBS_ReadTransf', 'ETH_DMASR_EBS_DataTransfTx', 'ETH_DMASR_TPS',
    'ETH_DMASR_TPS_Stopped', 'ETH_DMASR_TPS_Fetching', 'ETH_DMASR_TPS_Waiting',
    'ETH_DMASR_TPS_Reading', 'ETH_DMASR_TPS_Suspended', 'ETH_DMASR_TPS_Closing',
    'ETH_DMASR_RPS', 'ETH_DMASR_RPS_Stopped', 'ETH_DMASR_RPS_Fetching',
    'ETH_DMASR_RPS_Waiting', 'ETH_DMASR_RPS_Suspended', 'ETH_DMASR_RPS_Closing',
    'ETH_DMASR_RPS_Queuing', 'ETH_DMASR_NIS', 'ETH_DMASR_AIS', 'ETH_DMASR_ERS',
    'ETH_DMASR_FBES', 'ETH_DMASR_ETS', 'ETH_DMASR_RWTS', 'ETH_DMASR_RPSS',
    'ETH_DMASR_RBUS', 'ETH_DMASR_RS', 'ETH_DMASR_TUS', 'ETH_DMASR_ROS',
    'ETH_DMASR_TJTS', 'ETH_DMASR_TBUS', 'ETH_DMASR_TPSS', 'ETH_DMASR_TS',
    'ETH_DMAOMR_DTCEFD', 'ETH_DMAOMR_RSF', 'ETH_DMAOMR_DFRF', 'ETH_DMAOMR_TSF',
    'ETH_DMAOMR_FTF', 'ETH_DMAOMR_TTC', 'ETH_DMAOMR_TTC_64Bytes',
    'ETH_DMAOMR_TTC_128Bytes', 'ETH_DMAOMR_TTC_192Bytes', 'ETH_DMAOMR_TTC_256Bytes',
    'ETH_DMAOMR_TTC_40Bytes', 'ETH_DMAOMR_TTC_32Bytes', 'ETH_DMAOMR_TTC_24Bytes',
    'ETH_DMAOMR_TTC_16Bytes', 'ETH_DMAOMR_ST', 'ETH_DMAOMR_FEF', 'ETH_DMAOMR_FUGF',
    'ETH_DMAOMR_RTC', 'ETH_DMAOMR_RTC_64Bytes', 'ETH_DMAOMR_RTC_32Bytes',
    'ETH_DMAOMR_RTC_96Bytes', 'ETH_DMAOMR_RTC_128Bytes', 'ETH_DMAOMR_OSF',
    'ETH_DMAOMR_SR', 'ETH_DMAIER_NISE', 'ETH_DMAIER_AISE', 'ETH_DMAIER_ERIE',
    'ETH_DMAIER_FBEIE', 'ETH_DMAIER_ETIE', 'ETH_DMAIER_RWTIE', 'ETH_DMAIER_RPSIE',
    'ETH_DMAIER_RBUIE', 'ETH_DMAIER_RIE', 'ETH_DMAIER_TUIE', 'ETH_DMAIER_ROIE',
    'ETH_DMAIER_TJTIE', 'ETH_DMAIER_TBUIE', 'ETH_DMAIER_TPSIE', 'ETH_DMAIER_TIE',
    'ETH_DMAMFBOCR_OFOC', 'ETH_DMAMFBOCR_MFA', 'ETH_DMAMFBOCR_OMFC',
    'ETH_DMAMFBOCR_MFC', 'ETH_DMACHTDR_HTDAP', 'ETH_DMACHRDR_HRDAP',
    'ETH_DMACHTBAR_HTBAP', 'ETH_DMACHRBAR_HRBAP', 'ADC_TypeDef', 'ADC_Common_TypeDef',
    'CAN_TxMailBox_TypeDef', 'CAN_FIFOMailBox_TypeDef', 'CAN_FilterRegister_TypeDef',
    'CRC_TypeDef', 'DAC_TypeDef', 'DBGMCU_TypeDef', 'DCMI_TypeDef',
    'DMA_Stream_TypeDef', 'DMA_TypeDef', 'EXTI_TypeDef', 'FLASH_TypeDef',
    'FSMC_Bank2_TypeDef', 'FSMC_Bank3_TypeDef', 'FSMC_Bank4_TypeDef', 'I2C_TypeDef',
    'IWDG_TypeDef', 'PWR_TypeDef', 'RTC_TypeDef', 'SPI_TypeDef', 'TIM_TypeDef',
    'USART_TypeDef', 'WWDG_TypeDef', 'CRYP_TypeDef', 'RNG_TypeDef']
