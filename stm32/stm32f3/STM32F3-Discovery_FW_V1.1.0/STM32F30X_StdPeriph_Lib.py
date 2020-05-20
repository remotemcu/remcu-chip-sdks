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



__version__ = "V1.1.0-458e5695"
__RUN = 0
__HALT = 1
__ERROR = 0
__WARNING = 1
__INFO = 2
__DEBUG = 3
__ALL_LOG = 4
DEFAULT_OPENOCD_PORT = 6666
DEFAULT_GDB_PORT = 3333
# file stm32f30x_comp.h : 

# empty define __STM32F30x_COMP_H
COMP_Selection_COMP1 = 0x0
COMP_Selection_COMP2 = 0x4
COMP_Selection_COMP3 = 0x8
COMP_Selection_COMP4 = 0xC
COMP_Selection_COMP5 = 0x10
COMP_Selection_COMP6 = 0x14
COMP_Selection_COMP7 = 0x18
# fun define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
#                                    ((PERIPH) == COMP_Selection_COMP2) || \
#                                    ((PERIPH) == COMP_Selection_COMP3) || \
#                                    ((PERIPH) == COMP_Selection_COMP4) || \
#                                    ((PERIPH) == COMP_Selection_COMP5) || \
#                                    ((PERIPH) == COMP_Selection_COMP6) || \
#                                    ((PERIPH) == COMP_Selection_COMP7))
COMP_InvertingInput_1_4VREFINT = 0x0
COMP_InvertingInput_1_2VREFINT = 0x10
COMP_InvertingInput_3_4VREFINT = 0x20
COMP_InvertingInput_VREFINT = 0x30
COMP_InvertingInput_DAC1 = 0x40
COMP_InvertingInput_DAC2 = 0x50
COMP_InvertingInput_IO1 = 0x60
COMP_InvertingInput_IO2 = 0x70
# fun define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
#                                        ((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
#                                        ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
#                                        ((INPUT) == COMP_InvertingInput_VREFINT)    || \
#                                        ((INPUT) == COMP_InvertingInput_DAC1)       || \
#                                        ((INPUT) == COMP_InvertingInput_DAC2)       || \
#                                        ((INPUT) == COMP_InvertingInput_IO1)        || \
#                                        ((INPUT) == COMP_InvertingInput_IO2))
COMP_NonInvertingInput_IO1 = 0x0
COMP_NonInvertingInput_IO2 = 0x80
# fun define IS_COMP_NONINVERTING_INPUT(INPUT) (((INPUT) == COMP_NonInvertingInput_IO1) || \
#                                           ((INPUT) == COMP_NonInvertingInput_IO2))
COMP_Output_None = 0x0
COMP_Output_TIM1BKIN = 0x400
COMP_Output_TIM1BKIN2 = 0x800
COMP_Output_TIM8BKIN = 0xC00
COMP_Output_TIM8BKIN2 = 0x1000
COMP_Output_TIM1BKIN2_TIM8BKIN2 = 0x1400
COMP_Output_TIM1OCREFCLR = 0x1800
COMP_Output_TIM1IC1 = 0x1C00
COMP_Output_TIM2IC4 = 0x2000
COMP_Output_TIM2OCREFCLR = 0x2400
COMP_Output_TIM3IC1 = 0x2800
COMP_Output_TIM3OCREFCLR = 0x2C00
COMP_Output_TIM4IC1 = 0x1C00
COMP_Output_TIM3IC2 = 0x2000
COMP_Output_TIM15IC1 = 0x2800
COMP_Output_TIM15BKIN = 0x2C00
COMP_Output_TIM3IC3 = 0x1800
COMP_Output_TIM8OCREFCLR = 0x1C00
COMP_Output_TIM15IC2 = 0x2000
COMP_Output_TIM4IC2 = 0x2400
COMP_Output_TIM15OCREFCLR = 0x2800
COMP_Output_TIM2IC1 = 0x1800
COMP_Output_TIM17IC1 = 0x2000
COMP_Output_TIM4IC3 = 0x2400
COMP_Output_TIM16BKIN = 0x2800
COMP_Output_TIM2IC2 = 0x1800
COMP_Output_COMP6TIM2OCREFCLR = 0x2000
COMP_Output_TIM16OCREFCLR = 0x2400
COMP_Output_TIM16IC1 = 0x2800
COMP_Output_TIM4IC4 = 0x2C00
COMP_Output_TIM2IC3 = 0x2000
COMP_Output_TIM1IC2 = 0x2400
COMP_Output_TIM17OCREFCLR = 0x2800
COMP_Output_TIM17BKIN = 0x2C00
# fun define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)                || \
#                                ((OUTPUT) == COMP_Output_TIM1BKIN)            || \
#                                ((OUTPUT) == COMP_Output_TIM1IC1)             || \
#                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR)        || \
#                                ((OUTPUT) == COMP_Output_TIM2IC4)             || \
#                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
#                                ((OUTPUT) == COMP_Output_COMP6TIM2OCREFCLR)   || \
#                                ((OUTPUT) == COMP_Output_TIM3IC1)             || \
#                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR)        || \
#                                ((OUTPUT) == COMP_Output_TIM8BKIN)            || \
#                                ((OUTPUT) == COMP_Output_TIM1BKIN2)           || \
#                                ((OUTPUT) == COMP_Output_TIM8BKIN2)           || \
#                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
#                                ((OUTPUT) == COMP_Output_TIM1BKIN2_TIM8BKIN2) || \
#                                ((OUTPUT) == COMP_Output_TIM3IC2)             || \
#                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
#                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
#                                ((OUTPUT) == COMP_Output_TIM15BKIN)           || \
#                                ((OUTPUT) == COMP_Output_TIM8OCREFCLR)        || \
#                                ((OUTPUT) == COMP_Output_TIM3IC3)             || \
#                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
#                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
#                                ((OUTPUT) == COMP_Output_TIM2IC1)             || \
#                                ((OUTPUT) == COMP_Output_TIM4IC3)             || \
#                                ((OUTPUT) == COMP_Output_TIM16BKIN)           || \
#                                ((OUTPUT) == COMP_Output_TIM17IC1)            || \
#                                ((OUTPUT) == COMP_Output_TIM2IC2)             || \
#                                ((OUTPUT) == COMP_Output_TIM16IC1)            || \
#                                ((OUTPUT) == COMP_Output_TIM4IC4)             || \
#                                ((OUTPUT) == COMP_Output_TIM16OCREFCLR)       || \
#                                ((OUTPUT) == COMP_Output_TIM2IC3)             || \
#                                ((OUTPUT) == COMP_Output_TIM1IC2)             || \
#                                ((OUTPUT) == COMP_Output_TIM17BKIN)           || \
#                                ((OUTPUT) == COMP_Output_TIM17OCREFCLR))
COMP_BlankingSrce_None = 0x0
COMP_BlankingSrce_TIM1OC5 = 0x40000
COMP_BlankingSrce_TIM2OC3 = 0x80000
COMP_BlankingSrce_TIM3OC3 = 0xC0000
COMP_BlankingSrce_TIM2OC4 = 0xC0000
COMP_BlankingSrce_TIM8OC5 = 0x80000
COMP_BlankingSrce_TIM3OC4 = 0x40000
COMP_BlankingSrce_TIM15OC1 = 0xC0000
COMP_BlankingSrce_TIM15OC2 = 0x100000
# fun define IS_COMP_BLANKING_SOURCE(SOURCE) (((SOURCE) == COMP_BlankingSrce_None)     || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM1OC5)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC3)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC3)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC4)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM8OC5)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC4)  || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC1) || \
#                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC2))
COMP_OutputPol_NonInverted = 0x0
COMP_OutputPol_Inverted = 0x8000
# fun define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
#                                 ((POL) == COMP_OutputPol_Inverted))
COMP_Hysteresis_No = 0x0
COMP_Hysteresis_Low = 0x10000
COMP_Hysteresis_Medium = 0x20000
COMP_Hysteresis_High = 0x30000
# fun define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No)     || \
#                                           ((HYSTERESIS) == COMP_Hysteresis_Low)    || \
#                                           ((HYSTERESIS) == COMP_Hysteresis_Medium) || \
#                                           ((HYSTERESIS) == COMP_Hysteresis_High))
COMP_Mode_HighSpeed = 0x0
COMP_Mode_MediumSpeed = 0x4
COMP_Mode_LowPower = 0x8
COMP_Mode_UltraLowPower = 0xC
# fun define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
#                               ((MODE) == COMP_Mode_LowPower)      || \
#                               ((MODE) == COMP_Mode_MediumSpeed)   || \
#                               ((MODE) == COMP_Mode_HighSpeed))
COMP_OutputLevel_High = 0x40000000
COMP_OutputLevel_Low = 0x0
# fun define IS_COMP_WINDOW(WINDOW)  (((WINDOW) == COMP_Selection_COMP2) || \
#                                 ((WINDOW) == COMP_Selection_COMP4) || \
#                                 ((WINDOW) == COMP_Selection_COMP6))
# struct COMP_InitTypeDef

class COMP_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('COMP_InvertingInput',	ctypes.c_uint32),
		('COMP_NonInvertingInput',	ctypes.c_uint32),
		('COMP_Output',	ctypes.c_uint32),
		('COMP_BlankingSrce',	ctypes.c_uint32),
		('COMP_OutputPol',	ctypes.c_uint32),
		('COMP_Hysteresis',	ctypes.c_uint32),
		('COMP_Mode',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f30x_crc.h : 

# empty define __STM32F30x_CRC_H
CRC_ReverseInputData_No = 0x0
CRC_ReverseInputData_8bits = 0x20
CRC_ReverseInputData_16bits = 0x40
CRC_ReverseInputData_32bits = 0x60
# fun define IS_CRC_REVERSE_INPUT_DATA(DATA) (((DATA) == CRC_ReverseInputData_No)     || \
#                                         ((DATA) == CRC_ReverseInputData_8bits)  || \
#                                         ((DATA) == CRC_ReverseInputData_16bits) || \
#                                         ((DATA) == CRC_ReverseInputData_32bits))
CRC_PolSize_7 = 0x18
CRC_PolSize_8 = 0x10
CRC_PolSize_16 = 0x8
CRC_PolSize_32 = 0x0
# fun define IS_CRC_POL_SIZE(SIZE) (((SIZE) == CRC_PolSize_7)  || \
#                               ((SIZE) == CRC_PolSize_8)  || \
#                               ((SIZE) == CRC_PolSize_16) || \
#                               ((SIZE) == CRC_PolSize_32))
# ----------------------------------------

# file stm32f30x_usart.h : 

# empty define __STM32F30x_USART_H
# fun define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == USART1) || \
#                                     ((PERIPH) == USART2) || \
#                                     ((PERIPH) == USART3) || \
#                                     ((PERIPH) == UART4) || \
#                                     ((PERIPH) == UART5))
# fun define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || \
#                                     ((PERIPH) == USART2) || \
#                                     ((PERIPH) == USART3))
# fun define IS_USART_1234_PERIPH(PERIPH) (((PERIPH) == USART1) || \
#                                      ((PERIPH) == USART2) || \
#                                      ((PERIPH) == USART3) || \
#                                      ((PERIPH) == UART4))
USART_WordLength_8b = 0x0
USART_WordLength_9b = 0x1000
# fun define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
#                                      ((LENGTH) == USART_WordLength_9b))
USART_StopBits_1 = 0x0
USART_StopBits_2 = 0x2000
USART_StopBits_1_5 = 0x3000
# fun define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
#                                     ((STOPBITS) == USART_StopBits_2) || \
#                                     ((STOPBITS) == USART_StopBits_1_5))
USART_Parity_No = 0x0
USART_Parity_Even = 0x400
USART_Parity_Odd = 0x600
# fun define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No) || \
#                                 ((PARITY) == USART_Parity_Even) || \
#                                 ((PARITY) == USART_Parity_Odd))
USART_Mode_Rx = 0x4
USART_Mode_Tx = 0x8
# fun define IS_USART_MODE(MODE) ((((MODE) & (uint32_t)0xFFFFFFF3) == 0x00) && \
#                              ((MODE) != (uint32_t)0x00))
USART_HardwareFlowControl_None = 0x0
USART_HardwareFlowControl_RTS = 0x100
USART_HardwareFlowControl_CTS = 0x200
USART_HardwareFlowControl_RTS_CTS = 0x300
# fun define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
#                              (((CONTROL) == USART_HardwareFlowControl_None) || \
#                               ((CONTROL) == USART_HardwareFlowControl_RTS) || \
#                               ((CONTROL) == USART_HardwareFlowControl_CTS) || \
#                               ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
USART_Clock_Disable = 0x0
USART_Clock_Enable = 0x800
# fun define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
#                               ((CLOCK) == USART_Clock_Enable))
USART_CPOL_Low = 0x0
USART_CPOL_High = 0x400
# fun define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))
USART_CPHA_1Edge = 0x0
USART_CPHA_2Edge = 0x200
# fun define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))
USART_LastBit_Disable = 0x0
USART_LastBit_Enable = 0x100
# fun define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
#                                   ((LASTBIT) == USART_LastBit_Enable))
USART_DMAReq_Tx = 0x80
USART_DMAReq_Rx = 0x40
# fun define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint32_t)0xFFFFFF3F) == 0x00) && \
#                                  ((DMAREQ) != (uint32_t)0x00))
USART_DMAOnError_Enable = 0x0
USART_DMAOnError_Disable = 0x2000
# fun define IS_USART_DMAONERROR(DMAERROR) (((DMAERROR) == USART_DMAOnError_Disable)|| \
#                                       ((DMAERROR) == USART_DMAOnError_Enable))
USART_WakeUp_IdleLine = 0x0
USART_WakeUp_AddressMark = 0x800
# fun define IS_USART_MUTEMODE_WAKEUP(WAKEUP) (((WAKEUP) == USART_WakeUp_IdleLine) || \
#                                          ((WAKEUP) == USART_WakeUp_AddressMark))
USART_AddressLength_4b = 0x0
USART_AddressLength_7b = 0x10
# fun define IS_USART_ADDRESS_DETECTION(ADDRESS) (((ADDRESS) == USART_AddressLength_4b) || \
#                                             ((ADDRESS) == USART_AddressLength_7b))
USART_WakeUpSource_AddressMatch = 0x0
USART_WakeUpSource_StartBit = 0x200000
USART_WakeUpSource_RXNE = 0x300000
# fun define IS_USART_STOPMODE_WAKEUPSOURCE(SOURCE) (((SOURCE) == USART_WakeUpSource_AddressMatch) || \
#                                                ((SOURCE) == USART_WakeUpSource_StartBit) || \
#                                                ((SOURCE) == USART_WakeUpSource_RXNE))
USART_LINBreakDetectLength_10b = 0x0
USART_LINBreakDetectLength_11b = 0x20
# fun define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
#                               (((LENGTH) == USART_LINBreakDetectLength_10b) || \
#                                ((LENGTH) == USART_LINBreakDetectLength_11b))
USART_IrDAMode_LowPower = 0x4
USART_IrDAMode_Normal = 0x0
# fun define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IrDAMode_LowPower) || \
#                                  ((MODE) == USART_IrDAMode_Normal))
USART_DEPolarity_High = 0x0
USART_DEPolarity_Low = 0x8000
# fun define IS_USART_DE_POLARITY(POLARITY) (((POLARITY) == USART_DEPolarity_Low) || \
#                                        ((POLARITY) == USART_DEPolarity_High))
USART_InvPin_Tx = 0x20000
USART_InvPin_Rx = 0x10000
# fun define IS_USART_INVERSTION_PIN(PIN) ((((PIN) & (uint32_t)0xFFFCFFFF) == 0x00) && \
#                                       ((PIN) != (uint32_t)0x00))
USART_AutoBaudRate_StartBit = 0x0
USART_AutoBaudRate_FallingEdge = 0x200000
USART_AutoBaudRate_0x7FFrame = 0x400000
USART_AutoBaudRate_0x55Frame = 0x600000
# fun define IS_USART_AUTOBAUDRATE_MODE(MODE) (((MODE) == USART_AutoBaudRate_StartBit) || \
#                                          ((MODE) == USART_AutoBaudRate_FallingEdge) || \
#                                          ((MODE) == USART_AutoBaudRate_0x7FFrame) || \
#                                          ((MODE) == USART_AutoBaudRate_0x55Frame))
USART_OVRDetection_Enable = 0x0
USART_OVRDetection_Disable = 0x1000
# fun define IS_USART_OVRDETECTION(OVR) (((OVR) == USART_OVRDetection_Enable)|| \
#                                    ((OVR) == USART_OVRDetection_Disable))
USART_Request_ABRRQ = 0x1
USART_Request_SBKRQ = 0x2
USART_Request_MMRQ = 0x4
USART_Request_RXFRQ = 0x8
USART_Request_TXFRQ = 0x10
# fun define IS_USART_REQUEST(REQUEST) (((REQUEST) == USART_Request_TXFRQ) || \
#                                   ((REQUEST) == USART_Request_RXFRQ) || \
#                                   ((REQUEST) == USART_Request_MMRQ) || \
#                                   ((REQUEST) == USART_Request_SBKRQ) || \
#                                   ((REQUEST) == USART_Request_ABRRQ))
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
# fun define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
#                             ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
#                             ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
#                             ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
#                             ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
#                             ((FLAG) == USART_FLAG_nCTSS) || ((FLAG) == USART_FLAG_RTO) || \
#                             ((FLAG) == USART_FLAG_EOB) || ((FLAG) == USART_FLAG_ABRE) || \
#                             ((FLAG) == USART_FLAG_ABRF) || ((FLAG) == USART_FLAG_BUSY) || \
#                             ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_SBK) || \
#                             ((FLAG) == USART_FLAG_RWU) || ((FLAG) == USART_FLAG_WU) || \
#                             ((FLAG) == USART_FLAG_TEACK)|| ((FLAG) == USART_FLAG_REACK))
# fun define IS_USART_CLEAR_FLAG(FLAG) (((FLAG) == USART_FLAG_WU) || ((FLAG) == USART_FLAG_TC) || \
#                                   ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_ORE) || \
#                                   ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
#                                   ((FLAG) == USART_FLAG_LBD) || ((FLAG) == USART_FLAG_CTS) || \
#                                   ((FLAG) == USART_FLAG_RTO) || ((FLAG) == USART_FLAG_EOB) || \
#                                   ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_PE))
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
# fun define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
#                                ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
#                                ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
#                                ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR) || \
#                                ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
#                                ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))
# fun define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
#                             ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
#                             ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
#                             ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
#                             ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE) || \
#                             ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
#                             ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))
# fun define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_PE) || \
#                               ((IT) == USART_IT_FE) || ((IT) == USART_IT_NE) || \
#                               ((IT) == USART_IT_ORE) || ((IT) == USART_IT_IDLE) || \
#                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS) || \
#                               ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
#                               ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))
# fun define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x005B8D81))
# fun define IS_USART_DE_ASSERTION_DEASSERTION_TIME(TIME) ((TIME) <= 0x1F)
# fun define IS_USART_AUTO_RETRY_COUNTER(COUNTER) ((COUNTER) <= 0x7)
# fun define IS_USART_TIMEOUT(TIMEOUT) ((TIMEOUT) <= 0x00FFFFFF)
# fun define IS_USART_DATA(DATA) ((DATA) <= 0x1FF)
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

# file stm32f30x_rtc.h : 

# empty define __STM32F30x_RTC_H
RTC_HourFormat_24 = 0x0
RTC_HourFormat_12 = 0x40
# fun define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HourFormat_12) || \
#                                        ((FORMAT) == RTC_HourFormat_24))
# fun define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= 0x7F)
# fun define IS_RTC_SYNCH_PREDIV(PREDIV)    ((PREDIV) <= 0x7FFF)
# fun define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
# fun define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
# fun define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
# fun define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)
RTC_H12_AM = 0x0
RTC_H12_PM = 0x40
# fun define IS_RTC_H12(PM) (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))
# fun define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)
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
# fun define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
# fun define IS_RTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))
RTC_Weekday_Monday = 0x1
RTC_Weekday_Tuesday = 0x2
RTC_Weekday_Wednesday = 0x3
RTC_Weekday_Thursday = 0x4
RTC_Weekday_Friday = 0x5
RTC_Weekday_Saturday = 0x6
RTC_Weekday_Sunday = 0x7
# fun define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Tuesday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Wednesday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Thursday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Friday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Saturday) || \
#                                 ((WEEKDAY) == RTC_Weekday_Sunday))
# fun define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
# fun define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Tuesday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Wednesday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Thursday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Friday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Saturday) || \
#                                                    ((WEEKDAY) == RTC_Weekday_Sunday))
RTC_AlarmDateWeekDaySel_Date = 0x0
RTC_AlarmDateWeekDaySel_WeekDay = 0x40000000
# fun define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date) || \
#                                            ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay))
RTC_AlarmMask_None = 0x0
RTC_AlarmMask_DateWeekDay = 0x80000000
RTC_AlarmMask_Hours = 0x800000
RTC_AlarmMask_Minutes = 0x8000
RTC_AlarmMask_Seconds = 0x80
RTC_AlarmMask_All = 0x80808080
# fun define IS_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)
RTC_Alarm_A = 0x100
RTC_Alarm_B = 0x200
# fun define IS_RTC_ALARM(ALARM)     (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
# fun define IS_RTC_CMD_ALARM(ALARM) (((ALARM) & (RTC_Alarm_A | RTC_Alarm_B)) != (uint32_t)RESET)
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
# fun define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == RTC_AlarmSubSecondMask_All) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_1) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_2) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_3) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_4) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_5) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_6) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_7) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_8) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_9) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_10) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_11) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_12) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14_13) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_SS14) || \
#                                              ((MASK) == RTC_AlarmSubSecondMask_None))
# fun define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)
RTC_WakeUpClock_RTCCLK_Div16 = 0x0
RTC_WakeUpClock_RTCCLK_Div8 = 0x1
RTC_WakeUpClock_RTCCLK_Div4 = 0x2
RTC_WakeUpClock_RTCCLK_Div2 = 0x3
RTC_WakeUpClock_CK_SPRE_16bits = 0x4
RTC_WakeUpClock_CK_SPRE_17bits = 0x6
# fun define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WakeUpClock_RTCCLK_Div16) || \
#                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div8) || \
#                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div4) || \
#                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div2) || \
#                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_16bits) || \
#                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_17bits))
# fun define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)
RTC_TimeStampEdge_Rising = 0x0
RTC_TimeStampEdge_Falling = 0x8
# fun define IS_RTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TimeStampEdge_Rising) || \
#                                     ((EDGE) == RTC_TimeStampEdge_Falling))
RTC_Output_Disable = 0x0
RTC_Output_AlarmA = 0x200000
RTC_Output_AlarmB = 0x400000
RTC_Output_WakeUp = 0x600000
# fun define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == RTC_Output_Disable) || \
#                               ((OUTPUT) == RTC_Output_AlarmA) || \
#                               ((OUTPUT) == RTC_Output_AlarmB) || \
#                               ((OUTPUT) == RTC_Output_WakeUp))
RTC_OutputPolarity_High = 0x0
RTC_OutputPolarity_Low = 0x100000
# fun define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OutputPolarity_High) || \
#                                ((POL) == RTC_OutputPolarity_Low))
RTC_CalibSign_Positive = 0x0
RTC_CalibSign_Negative = 0x80
# fun define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == RTC_CalibSign_Positive) || \
#                                 ((SIGN) == RTC_CalibSign_Negative))
# fun define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20)
RTC_CalibOutput_512Hz = 0x0
RTC_CalibOutput_1Hz = 0x80000
# fun define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == RTC_CalibOutput_512Hz) || \
#                                      ((OUTPUT) == RTC_CalibOutput_1Hz))
RTC_SmoothCalibPeriod_32sec = 0x0
RTC_SmoothCalibPeriod_16sec = 0x2000
RTC_SmoothCalibPeriod_8sec = 0x4000
# fun define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SmoothCalibPeriod_32sec) || \
#                                             ((PERIOD) == RTC_SmoothCalibPeriod_16sec) || \
#                                             ((PERIOD) == RTC_SmoothCalibPeriod_8sec))
RTC_SmoothCalibPlusPulses_Set = 0x8000
RTC_SmoothCalibPlusPulses_Reset = 0x0
# fun define IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SmoothCalibPlusPulses_Set) || \
#                                         ((PLUS) == RTC_SmoothCalibPlusPulses_Reset))
# fun define IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000001FF)
RTC_DayLightSaving_SUB1H = 0x20000
RTC_DayLightSaving_ADD1H = 0x10000
# fun define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == RTC_DayLightSaving_SUB1H) || \
#                                      ((SAVE) == RTC_DayLightSaving_ADD1H))
RTC_StoreOperation_Reset = 0x0
RTC_StoreOperation_Set = 0x40000
# fun define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_StoreOperation_Reset) || \
#                                           ((OPERATION) == RTC_StoreOperation_Set))
RTC_TamperTrigger_RisingEdge = 0x0
RTC_TamperTrigger_FallingEdge = 0x1
RTC_TamperTrigger_LowLevel = 0x0
RTC_TamperTrigger_HighLevel = 0x1
# fun define IS_RTC_TAMPER_TRIGGER(TRIGGER) (((TRIGGER) == RTC_TamperTrigger_RisingEdge) || \
#                                        ((TRIGGER) == RTC_TamperTrigger_FallingEdge) || \
#                                        ((TRIGGER) == RTC_TamperTrigger_LowLevel) || \
#                                        ((TRIGGER) == RTC_TamperTrigger_HighLevel))
RTC_TamperFilter_Disable = 0x0
RTC_TamperFilter_2Sample = 0x800
RTC_TamperFilter_4Sample = 0x1000
RTC_TamperFilter_8Sample = 0x1800
# fun define IS_RTC_TAMPER_FILTER(FILTER) (((FILTER) == RTC_TamperFilter_Disable) || \
#                                      ((FILTER) == RTC_TamperFilter_2Sample) || \
#                                      ((FILTER) == RTC_TamperFilter_4Sample) || \
#                                      ((FILTER) == RTC_TamperFilter_8Sample))
RTC_TamperSamplingFreq_RTCCLK_Div32768 = 0x0
RTC_TamperSamplingFreq_RTCCLK_Div16384 = 0x100
RTC_TamperSamplingFreq_RTCCLK_Div8192 = 0x200
RTC_TamperSamplingFreq_RTCCLK_Div4096 = 0x300
RTC_TamperSamplingFreq_RTCCLK_Div2048 = 0x400
RTC_TamperSamplingFreq_RTCCLK_Div1024 = 0x500
RTC_TamperSamplingFreq_RTCCLK_Div512 = 0x600
RTC_TamperSamplingFreq_RTCCLK_Div256 = 0x700
# fun define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div32768) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div16384) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div8192) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div4096) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div2048) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div1024) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div512) || \
#                                           ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div256))
RTC_TamperPrechargeDuration_1RTCCLK = 0x0
RTC_TamperPrechargeDuration_2RTCCLK = 0x2000
RTC_TamperPrechargeDuration_4RTCCLK = 0x4000
RTC_TamperPrechargeDuration_8RTCCLK = 0x6000
# fun define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == RTC_TamperPrechargeDuration_1RTCCLK) || \
#                                                    ((DURATION) == RTC_TamperPrechargeDuration_2RTCCLK) || \
#                                                    ((DURATION) == RTC_TamperPrechargeDuration_4RTCCLK) || \
#                                                    ((DURATION) == RTC_TamperPrechargeDuration_8RTCCLK))
RTC_Tamper_1 = 0x1
RTC_Tamper_2 = 0x8
RTC_Tamper_3 = 0x20
# fun define IS_RTC_TAMPER(TAMPER) ((((TAMPER) & (uint32_t)0xFFFFFFD6) == 0x00) && ((TAMPER) != (uint32_t)RESET))
RTC_OutputType_OpenDrain = 0x0
RTC_OutputType_PushPull = 0x40000
# fun define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == RTC_OutputType_OpenDrain) || \
#                                  ((TYPE) == RTC_OutputType_PushPull))
RTC_ShiftAdd1S_Reset = 0x0
RTC_ShiftAdd1S_Set = 0x80000000
# fun define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_ShiftAdd1S_Reset) || \
#                                 ((SEL) == RTC_ShiftAdd1S_Set))
# fun define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)
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
# fun define IS_RTC_BKP(BKP)                   (((BKP) == RTC_BKP_DR0) || \
#                                           ((BKP) == RTC_BKP_DR1) || \
#                                           ((BKP) == RTC_BKP_DR2) || \
#                                           ((BKP) == RTC_BKP_DR3) || \
#                                           ((BKP) == RTC_BKP_DR4) || \
#                                           ((BKP) == RTC_BKP_DR5) || \
#                                           ((BKP) == RTC_BKP_DR6) || \
#                                           ((BKP) == RTC_BKP_DR7) || \
#                                           ((BKP) == RTC_BKP_DR8) || \
#                                           ((BKP) == RTC_BKP_DR9) || \
#                                           ((BKP) == RTC_BKP_DR10) || \
#                                           ((BKP) == RTC_BKP_DR11) || \
#                                           ((BKP) == RTC_BKP_DR12) || \
#                                           ((BKP) == RTC_BKP_DR13) || \
#                                           ((BKP) == RTC_BKP_DR14) || \
#                                           ((BKP) == RTC_BKP_DR15))
RTC_Format_BIN = 0x0
RTC_Format_BCD = 0x1
# fun define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))
RTC_FLAG_RECALPF = 0x10000
RTC_FLAG_TAMP3F = 0x8000
RTC_FLAG_TAMP2F = 0x4000
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
# fun define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_TSOVF) || ((FLAG) == RTC_FLAG_TSF) || \
#                               ((FLAG) == RTC_FLAG_WUTF) || ((FLAG) == RTC_FLAG_ALRBF) || \
#                               ((FLAG) == RTC_FLAG_ALRAF) || ((FLAG) == RTC_FLAG_INITF) || \
#                               ((FLAG) == RTC_FLAG_RSF) || ((FLAG) == RTC_FLAG_WUTWF) || \
#                               ((FLAG) == RTC_FLAG_ALRBWF) || ((FLAG) == RTC_FLAG_ALRAWF) || \
#                               ((FLAG) == RTC_FLAG_TAMP1F) || ((FLAG) == RTC_FLAG_TAMP2F) || \
#                                ((FLAG) == RTC_FLAG_TAMP3F) || ((FLAG) == RTC_FLAG_RECALPF) || \
#                                ((FLAG) == RTC_FLAG_SHPF))
# fun define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF00DF) == (uint32_t)RESET))
RTC_IT_TS = 0x8000
RTC_IT_WUT = 0x4000
RTC_IT_ALRB = 0x2000
RTC_IT_ALRA = 0x1000
RTC_IT_TAMP = 0x4
RTC_IT_TAMP1 = 0x20000
RTC_IT_TAMP2 = 0x40000
RTC_IT_TAMP3 = 0x80000
# fun define IS_RTC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF0FFB) == (uint32_t)RESET))
# fun define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_TS)    || ((IT) == RTC_IT_WUT) || \
#                           ((IT) == RTC_IT_ALRB)  || ((IT) == RTC_IT_ALRA) || \
#                           ((IT) == RTC_IT_TAMP1) || ((IT) == RTC_IT_TAMP2) || \
#                           ((IT) == RTC_IT_TAMP3))
# fun define IS_RTC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFF10FFF) == (uint32_t)RESET))
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

# file stm32f30x_syscfg.h : 

# empty define __STM32F30x_SYSCFG_H
EXTI_PortSourceGPIOA = 0x0
EXTI_PortSourceGPIOB = 0x1
EXTI_PortSourceGPIOC = 0x2
EXTI_PortSourceGPIOD = 0x3
EXTI_PortSourceGPIOE = 0x4
EXTI_PortSourceGPIOF = 0x5
# fun define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
#                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
#                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
#                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
#                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
#                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF))
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
# fun define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
#                                       ((PINSOURCE) == EXTI_PinSource1) || \
#                                       ((PINSOURCE) == EXTI_PinSource2) || \
#                                       ((PINSOURCE) == EXTI_PinSource3) || \
#                                       ((PINSOURCE) == EXTI_PinSource4) || \
#                                       ((PINSOURCE) == EXTI_PinSource5) || \
#                                       ((PINSOURCE) == EXTI_PinSource6) || \
#                                       ((PINSOURCE) == EXTI_PinSource7) || \
#                                       ((PINSOURCE) == EXTI_PinSource8) || \
#                                       ((PINSOURCE) == EXTI_PinSource9) || \
#                                       ((PINSOURCE) == EXTI_PinSource10) || \
#                                       ((PINSOURCE) == EXTI_PinSource11) || \
#                                       ((PINSOURCE) == EXTI_PinSource12) || \
#                                       ((PINSOURCE) == EXTI_PinSource13) || \
#                                       ((PINSOURCE) == EXTI_PinSource14) || \
#                                       ((PINSOURCE) == EXTI_PinSource15))
SYSCFG_MemoryRemap_Flash = 0x0
SYSCFG_MemoryRemap_SystemMemory = 0x1
SYSCFG_MemoryRemap_SRAM = 0x3
# fun define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash)        || \
#                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
#                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM))
SYSCFG_DMARemap_TIM17 = 0x1000
SYSCFG_DMARemap_TIM16 = 0x800
SYSCFG_DMARemap_TIM6DAC1 = 0x2000
SYSCFG_DMARemap_TIM7DAC2 = 0x4000
SYSCFG_DMARemap_ADC2ADC4 = 0x100
# fun define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17)    || \
#                                    ((REMAP) == SYSCFG_DMARemap_TIM16)    || \
#                                    ((REMAP) == SYSCFG_DMARemap_TIM6DAC1) || \
#                                    ((REMAP) == SYSCFG_DMARemap_TIM7DAC2) || \
#                                    ((REMAP) == SYSCFG_DMARemap_ADC2ADC4))
SYSCFG_TriggerRemap_DACTIM3 = 0x80
SYSCFG_TriggerRemap_TIM1TIM17 = 0x40
# fun define IS_SYSCFG_TRIGGER_REMAP(REMAP) (((REMAP) == SYSCFG_TriggerRemap_DACTIM3)  || \
#                                        ((REMAP) == SYSCFG_TriggerRemap_TIM1TIM17))
SYSCFG_EncoderRemap_No = 0x0
SYSCFG_EncoderRemap_TIM2 = 0x400000
SYSCFG_EncoderRemap_TIM3 = 0x800000
SYSCFG_EncoderRemap_TIM4 = 0xC00000
# fun define IS_SYSCFG_ENCODER_REMAP(REMAP) (((REMAP) == SYSCFG_EncoderRemap_No)    || \
#                                        ((REMAP) == SYSCFG_EncoderRemap_TIM2)  || \
#                                        ((REMAP) == SYSCFG_EncoderRemap_TIM3)  || \
#                                        ((REMAP) == SYSCFG_EncoderRemap_TIM4))
SYSCFG_I2CFastModePlus_PB6 = 0x10000
SYSCFG_I2CFastModePlus_PB7 = 0x20000
SYSCFG_I2CFastModePlus_PB8 = 0x40000
SYSCFG_I2CFastModePlus_PB9 = 0x80000
SYSCFG_I2CFastModePlus_I2C1 = 0x100000
SYSCFG_I2CFastModePlus_I2C2 = 0x200000
# fun define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
#                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
#                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
#                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
#                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
#                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2))
SYSCFG_IT_IXC = 0x80000000
SYSCFG_IT_IDC = 0x40000000
SYSCFG_IT_OFC = 0x20000000
SYSCFG_IT_UFC = 0x10000000
SYSCFG_IT_DZC = 0x8000000
SYSCFG_IT_IOC = 0x4000000
# fun define IS_SYSCFG_IT(IT) ((((IT) & (uint32_t)0x03FFFFFF) == 0) && ((IT) != 0))
SYSCFG_Break_PVD = 0x4
SYSCFG_Break_SRAMParity = 0x2
SYSCFG_Break_Lockup = 0x1
# fun define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
#                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
#                                       ((CONFIG) == SYSCFG_Break_Lockup))
SYSCFG_SRAMWRP_Page0 = 0x1
SYSCFG_SRAMWRP_Page1 = 0x2
SYSCFG_SRAMWRP_Page2 = 0x4
SYSCFG_SRAMWRP_Page3 = 0x8
SYSCFG_SRAMWRP_Page4 = 0x10
SYSCFG_SRAMWRP_Page5 = 0x20
SYSCFG_SRAMWRP_Page6 = 0x40
SYSCFG_SRAMWRP_Page7 = 0x80
# fun define IS_SYSCFG_PAGE(PAGE)((((PAGE) & (uint32_t)0xFFFFFF00) == 0x00000000) && ((PAGE) != 0x00000000))
SYSCFG_FLAG_PE = 0x100
# fun define IS_SYSCFG_FLAG(FLAG) (((FLAG) == SYSCFG_FLAG_PE))
# ----------------------------------------

# file stm32f30x_pwr.h : 

# empty define __STM32F30x_PWR_H
PWR_PVDLevel_0 = 0x0
PWR_PVDLevel_1 = 0x20
PWR_PVDLevel_2 = 0x40
PWR_PVDLevel_3 = 0x60
PWR_PVDLevel_4 = 0x80
PWR_PVDLevel_5 = 0xA0
PWR_PVDLevel_6 = 0xC0
PWR_PVDLevel_7 = 0xE0
# fun define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
#                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
#                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
#                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
PWR_WakeUpPin_1 = 0x100
PWR_WakeUpPin_2 = 0x200
PWR_WakeUpPin_3 = 0x400
# fun define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || \
#                                ((PIN) == PWR_WakeUpPin_2) || \
#                                ((PIN) == PWR_WakeUpPin_3))
PWR_Regulator_ON = 0x0
PWR_Regulator_LowPower = 0x1
# fun define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
#                                     ((REGULATOR) == PWR_Regulator_LowPower))
PWR_SLEEPEntry_WFI = 0x1
PWR_SLEEPEntry_WFE = 0x2
# fun define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))
PWR_STOPEntry_WFI = 0x1
PWR_STOPEntry_WFE = 0x2
# fun define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))
PWR_FLAG_WU = 0x1
PWR_FLAG_SB = 0x2
PWR_FLAG_PVDO = 0x4
PWR_FLAG_VREFINTRDY = 0x8
# fun define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
#                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))
# fun define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
# ----------------------------------------

# file stm32f30x_spi.h : 

# empty define __STM32F30x_SPI_H
# fun define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
#                                   ((PERIPH) == SPI2) || \
#                                   ((PERIPH) == SPI3))
# fun define IS_SPI_ALL_PERIPH_EXT(PERIPH) (((PERIPH) == SPI1) || \
#                                       ((PERIPH) == SPI2) || \
#                                       ((PERIPH) == SPI3) || \
#                                       ((PERIPH) == I2S2ext) || \
#                                       ((PERIPH) == I2S3ext))
# fun define IS_SPI_23_PERIPH(PERIPH)  (((PERIPH) == SPI2) || \
#                                   ((PERIPH) == SPI3))
# fun define IS_SPI_23_PERIPH_EXT(PERIPH)  (((PERIPH) == SPI2) || \
#                                       ((PERIPH) == SPI3) || \
#                                       ((PERIPH) == I2S2ext) || \
#                                       ((PERIPH) == I2S3ext))
# fun define IS_I2S_EXT_PERIPH(PERIPH)  (((PERIPH) == I2S2ext) || \
#                                    ((PERIPH) == I2S3ext))
SPI_Direction_2Lines_FullDuplex = 0x0
SPI_Direction_2Lines_RxOnly = 0x400
SPI_Direction_1Line_Rx = 0x8000
SPI_Direction_1Line_Tx = 0xC000
# fun define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
#                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
#                                     ((MODE) == SPI_Direction_1Line_Rx) || \
#                                     ((MODE) == SPI_Direction_1Line_Tx))
SPI_Mode_Master = 0x104
SPI_Mode_Slave = 0x0
# fun define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
#                           ((MODE) == SPI_Mode_Slave))
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
# fun define IS_SPI_DATA_SIZE(SIZE) (((SIZE) == SPI_DataSize_4b) || \
#                                ((SIZE) == SPI_DataSize_5b) || \
#                                ((SIZE) == SPI_DataSize_6b) || \
#                                ((SIZE) == SPI_DataSize_7b) || \
#                                ((SIZE) == SPI_DataSize_8b) || \
#                                ((SIZE) == SPI_DataSize_9b) || \
#                                ((SIZE) == SPI_DataSize_10b) || \
#                                ((SIZE) == SPI_DataSize_11b) || \
#                                ((SIZE) == SPI_DataSize_12b) || \
#                                ((SIZE) == SPI_DataSize_13b) || \
#                                ((SIZE) == SPI_DataSize_14b) || \
#                                ((SIZE) == SPI_DataSize_15b) || \
#                                ((SIZE) == SPI_DataSize_16b))
SPI_CRCLength_8b = 0x0
SPI_CRCLength_16b = 0x800
# fun define IS_SPI_CRC_LENGTH(LENGTH) (((LENGTH) == SPI_CRCLength_8b) || \
#                                   ((LENGTH) == SPI_CRCLength_16b))
SPI_CPOL_Low = 0x0
SPI_CPOL_High = 0x2
# fun define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
#                           ((CPOL) == SPI_CPOL_High))
SPI_CPHA_1Edge = 0x0
SPI_CPHA_2Edge = 0x1
# fun define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
#                           ((CPHA) == SPI_CPHA_2Edge))
SPI_NSS_Soft = 0x200
SPI_NSS_Hard = 0x0
# fun define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
#                         ((NSS) == SPI_NSS_Hard))
SPI_BaudRatePrescaler_2 = 0x0
SPI_BaudRatePrescaler_4 = 0x8
SPI_BaudRatePrescaler_8 = 0x10
SPI_BaudRatePrescaler_16 = 0x18
SPI_BaudRatePrescaler_32 = 0x20
SPI_BaudRatePrescaler_64 = 0x28
SPI_BaudRatePrescaler_128 = 0x30
SPI_BaudRatePrescaler_256 = 0x38
# fun define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
#                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
SPI_FirstBit_MSB = 0x0
SPI_FirstBit_LSB = 0x80
# fun define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
#                               ((BIT) == SPI_FirstBit_LSB))
I2S_Mode_SlaveTx = 0x0
I2S_Mode_SlaveRx = 0x100
I2S_Mode_MasterTx = 0x200
I2S_Mode_MasterRx = 0x300
# fun define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
#                           ((MODE) == I2S_Mode_SlaveRx) || \
#                           ((MODE) == I2S_Mode_MasterTx)|| \
#                           ((MODE) == I2S_Mode_MasterRx))
I2S_Standard_Phillips = 0x0
I2S_Standard_MSB = 0x10
I2S_Standard_LSB = 0x20
I2S_Standard_PCMShort = 0x30
I2S_Standard_PCMLong = 0xB0
# fun define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
#                                   ((STANDARD) == I2S_Standard_MSB) || \
#                                   ((STANDARD) == I2S_Standard_LSB) || \
#                                   ((STANDARD) == I2S_Standard_PCMShort) || \
#                                   ((STANDARD) == I2S_Standard_PCMLong))
I2S_DataFormat_16b = 0x0
I2S_DataFormat_16bextended = 0x1
I2S_DataFormat_24b = 0x3
I2S_DataFormat_32b = 0x5
# fun define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
#                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
#                                    ((FORMAT) == I2S_DataFormat_24b) || \
#                                    ((FORMAT) == I2S_DataFormat_32b))
I2S_MCLKOutput_Enable = 0x200
I2S_MCLKOutput_Disable = 0x0
# fun define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
#                                    ((OUTPUT) == I2S_MCLKOutput_Disable))
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
# fun define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
#                                 ((FREQ) <= I2S_AudioFreq_192k)) || \
#                                 ((FREQ) == I2S_AudioFreq_Default))
I2S_CPOL_Low = 0x0
I2S_CPOL_High = 0x8
# fun define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
#                           ((CPOL) == I2S_CPOL_High))
SPI_RxFIFOThreshold_HF = 0x0
SPI_RxFIFOThreshold_QF = 0x1000
# fun define IS_SPI_RX_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SPI_RxFIFOThreshold_HF) || \
#                                             ((THRESHOLD) == SPI_RxFIFOThreshold_QF))
SPI_I2S_DMAReq_Tx = 0x2
SPI_I2S_DMAReq_Rx = 0x1
# fun define IS_SPI_I2S_DMA_REQ(REQ) ((((REQ) & (uint16_t)0xFFFC) == 0x00) && ((REQ) != 0x00))
SPI_LastDMATransfer_TxEvenRxEven = 0x0
SPI_LastDMATransfer_TxOddRxEven = 0x4000
SPI_LastDMATransfer_TxEvenRxOdd = 0x2000
SPI_LastDMATransfer_TxOddRxOdd = 0x6000
# fun define IS_SPI_LAST_DMA_TRANSFER(TRANSFER) (((TRANSFER) == SPI_LastDMATransfer_TxEvenRxEven) || \
#                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxEven) || \
#                                            ((TRANSFER) == SPI_LastDMATransfer_TxEvenRxOdd) || \
#                                            ((TRANSFER) == SPI_LastDMATransfer_TxOddRxOdd))
SPI_NSSInternalSoft_Set = 0x100
SPI_NSSInternalSoft_Reset = 0xFEFF
# fun define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
#                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))
SPI_CRC_Tx = 0x0
SPI_CRC_Rx = 0x1
# fun define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))
SPI_Direction_Rx = 0xBFFF
SPI_Direction_Tx = 0x4000
# fun define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
#                                     ((DIRECTION) == SPI_Direction_Tx))
SPI_I2S_IT_TXE = 0x71
SPI_I2S_IT_RXNE = 0x60
SPI_I2S_IT_ERR = 0x50
# fun define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
#                                  ((IT) == SPI_I2S_IT_RXNE) || \
#                                  ((IT) == SPI_I2S_IT_ERR))
I2S_IT_UDR = 0x53
SPI_IT_MODF = 0x55
SPI_I2S_IT_OVR = 0x56
SPI_I2S_IT_FRE = 0x58
# fun define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
#                               ((IT) == SPI_I2S_IT_OVR) || ((IT) == SPI_IT_MODF) || \
#                               ((IT) == SPI_I2S_IT_FRE)|| ((IT) == I2S_IT_UDR))
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
# fun define IS_SPI_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
# fun define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
#                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
#                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
#                                   ((FLAG) == SPI_I2S_FLAG_FRE)|| ((FLAG) == I2S_FLAG_CHSIDE)|| \
#                                   ((FLAG) == I2S_FLAG_UDR))
# fun define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)
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

# file stm32f30x_flash.h : 

# Enum FLASH_Status
FLASH_BUSY = 0x1
FLASH_ERROR_WRP = 0x2
FLASH_ERROR_PROGRAM = 0x3
FLASH_COMPLETE = 0x4
FLASH_TIMEOUT = 0x5
# empty define __STM32F30x_FLASH_H
FLASH_Latency_0 = 0x0
FLASH_Latency_1 = 0x1
FLASH_Latency_2 = 0x2
# fun define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
#                                   ((LATENCY) == FLASH_Latency_1) || \
#                                   ((LATENCY) == FLASH_Latency_2))
FLASH_IT_EOP = 0x1000
FLASH_IT_ERR = 0x400
# fun define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
# fun define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0803FFFF))
# fun define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806))
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
OB_WRP_AllPages = 0xFFFFFFFF
# fun define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))
OB_RDP_Level_0 = 0xAA
OB_RDP_Level_1 = 0xBB
# fun define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
#                          ((LEVEL) == OB_RDP_Level_1))/*||\
#                          ((LEVEL) == OB_RDP_Level_2))*/
OB_IWDG_SW = 0x1
OB_IWDG_HW = 0x0
# fun define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))
OB_STOP_NoRST = 0x2
OB_STOP_RST = 0x0
# fun define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))
OB_STDBY_NoRST = 0x4
OB_STDBY_RST = 0x0
# fun define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))
OB_BOOT1_RESET = 0x0
OB_BOOT1_SET = 0x10
# fun define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))
OB_VDDA_ANALOG_ON = 0x20
OB_VDDA_ANALOG_OFF = 0x0
# fun define IS_OB_VDDA_ANALOG(ANALOG) (((ANALOG) == OB_VDDA_ANALOG_ON) || ((ANALOG) == OB_VDDA_ANALOG_OFF))
OB_SRAM_PARITY_SET = 0x0
OB_SRAM_PARITY_RESET = 0x40
# fun define IS_OB_SRAM_PARITY(PARITY) (((PARITY) == OB_SRAM_PARITY_SET) || ((PARITY) == OB_SRAM_PARITY_RESET))
FLASH_FLAG_BSY = 0x1
FLASH_FLAG_PGERR = 0x4
FLASH_FLAG_WRPERR = 0x10
FLASH_FLAG_EOP = 0x20
# fun define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFC3) == 0x00000000) && ((FLAG) != 0x00000000))
# fun define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR) || \
#                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP))
FLASH_ER_PRG_TIMEOUT = 0xB0000
# ----------------------------------------

# file stm32f30x_rcc.h : 

# empty define __STM32F30x_RCC_H
RCC_HSE_OFF = 0x0
RCC_HSE_ON = 0x1
RCC_HSE_Bypass = 0x5
# fun define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
#                         ((HSE) == RCC_HSE_Bypass))
RCC_PLLSource_HSI_Div2 = 0x0
RCC_PLLSource_PREDIV1 = 0x10000
# fun define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
#                                   ((SOURCE) == RCC_PLLSource_PREDIV1))
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
# fun define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
#                             ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
#                             ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
#                             ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
#                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
#                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
#                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
#                             ((MUL) == RCC_PLLMul_16))
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
# fun define IS_RCC_PREDIV1(PREDIV1) (((PREDIV1) == RCC_PREDIV1_Div1) || ((PREDIV1) == RCC_PREDIV1_Div2) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div3) || ((PREDIV1) == RCC_PREDIV1_Div4) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div5) || ((PREDIV1) == RCC_PREDIV1_Div6) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div7) || ((PREDIV1) == RCC_PREDIV1_Div8) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div9) || ((PREDIV1) == RCC_PREDIV1_Div10) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div11) || ((PREDIV1) == RCC_PREDIV1_Div12) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div13) || ((PREDIV1) == RCC_PREDIV1_Div14) || \
#                                 ((PREDIV1) == RCC_PREDIV1_Div15) || ((PREDIV1) == RCC_PREDIV1_Div16))
RCC_SYSCLKSource_HSI = 0x0
RCC_SYSCLKSource_HSE = 0x1
RCC_SYSCLKSource_PLLCLK = 0x2
# fun define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
#                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
#                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
RCC_SYSCLK_Div1 = 0x0
RCC_SYSCLK_Div2 = 0x80
RCC_SYSCLK_Div4 = 0x90
RCC_SYSCLK_Div8 = 0xA0
RCC_SYSCLK_Div16 = 0xB0
RCC_SYSCLK_Div64 = 0xC0
RCC_SYSCLK_Div128 = 0xD0
RCC_SYSCLK_Div256 = 0xE0
RCC_SYSCLK_Div512 = 0xF0
# fun define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
#                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
#                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
#                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
#                           ((HCLK) == RCC_SYSCLK_Div512))
RCC_HCLK_Div1 = 0x0
RCC_HCLK_Div2 = 0x400
RCC_HCLK_Div4 = 0x500
RCC_HCLK_Div8 = 0x600
RCC_HCLK_Div16 = 0x700
# fun define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
#                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
#                           ((PCLK) == RCC_HCLK_Div16))
RCC_ADC12PLLCLK_OFF = 0x0
RCC_ADC12PLLCLK_Div1 = 0x100
RCC_ADC12PLLCLK_Div2 = 0x110
RCC_ADC12PLLCLK_Div4 = 0x120
RCC_ADC12PLLCLK_Div6 = 0x130
RCC_ADC12PLLCLK_Div8 = 0x140
RCC_ADC12PLLCLK_Div10 = 0x150
RCC_ADC12PLLCLK_Div12 = 0x160
RCC_ADC12PLLCLK_Div16 = 0x170
RCC_ADC12PLLCLK_Div32 = 0x180
RCC_ADC12PLLCLK_Div64 = 0x190
RCC_ADC12PLLCLK_Div128 = 0x1A0
RCC_ADC12PLLCLK_Div256 = 0x1B0
RCC_ADC34PLLCLK_OFF = 0x10000000
RCC_ADC34PLLCLK_Div1 = 0x10002000
RCC_ADC34PLLCLK_Div2 = 0x10002200
RCC_ADC34PLLCLK_Div4 = 0x10002400
RCC_ADC34PLLCLK_Div6 = 0x10002600
RCC_ADC34PLLCLK_Div8 = 0x10002800
RCC_ADC34PLLCLK_Div10 = 0x10002A00
RCC_ADC34PLLCLK_Div12 = 0x10002C00
RCC_ADC34PLLCLK_Div16 = 0x10002E00
RCC_ADC34PLLCLK_Div32 = 0x10003000
RCC_ADC34PLLCLK_Div64 = 0x10003200
RCC_ADC34PLLCLK_Div128 = 0x10003400
RCC_ADC34PLLCLK_Div256 = 0x10003600
# fun define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_ADC12PLLCLK_OFF) || ((ADCCLK) == RCC_ADC12PLLCLK_Div1) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div2) || ((ADCCLK) == RCC_ADC12PLLCLK_Div4) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div6) || ((ADCCLK) == RCC_ADC12PLLCLK_Div8) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div10) || ((ADCCLK) == RCC_ADC12PLLCLK_Div12) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div16) || ((ADCCLK) == RCC_ADC12PLLCLK_Div32) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div64) || ((ADCCLK) == RCC_ADC12PLLCLK_Div128) || \
#                               ((ADCCLK) == RCC_ADC12PLLCLK_Div256) || ((ADCCLK) == RCC_ADC34PLLCLK_OFF) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div1) || ((ADCCLK) == RCC_ADC34PLLCLK_Div2) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div4) || ((ADCCLK) == RCC_ADC34PLLCLK_Div6) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div8) || ((ADCCLK) == RCC_ADC34PLLCLK_Div10) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div12) || ((ADCCLK) == RCC_ADC34PLLCLK_Div16) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div32) || ((ADCCLK) == RCC_ADC34PLLCLK_Div64) || \
#                               ((ADCCLK) == RCC_ADC34PLLCLK_Div128) || ((ADCCLK) == RCC_ADC34PLLCLK_Div256))
RCC_TIM1CLK_HCLK = 0x0
RCC_TIM1CLK_PLLCLK = 0x100
RCC_TIM8CLK_HCLK = 0x10000000
RCC_TIM8CLK_PLLCLK = 0x10000200
# fun define IS_RCC_TIMCLK(TIMCLK) (((TIMCLK) == RCC_TIM1CLK_HCLK) || ((TIMCLK) == RCC_TIM1CLK_PLLCLK) || \
#                               ((TIMCLK) == RCC_TIM8CLK_HCLK) || ((TIMCLK) == RCC_TIM8CLK_PLLCLK))
RCC_I2C1CLK_HSI = 0x0
RCC_I2C1CLK_SYSCLK = 0x10
RCC_I2C2CLK_HSI = 0x10000000
RCC_I2C2CLK_SYSCLK = 0x10000020
# fun define IS_RCC_I2CCLK(I2CCLK) (((I2CCLK) == RCC_I2C1CLK_HSI) || ((I2CCLK) == RCC_I2C1CLK_SYSCLK) || \
#                               ((I2CCLK) == RCC_I2C2CLK_HSI) || ((I2CCLK) == RCC_I2C2CLK_SYSCLK))
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
RCC_UART4CLK_PCLK = 0x40000000
RCC_UART4CLK_SYSCLK = 0x40100000
RCC_UART4CLK_LSE = 0x40200000
RCC_UART4CLK_HSI = 0x40300000
RCC_UART5CLK_PCLK = 0x50000000
RCC_UART5CLK_SYSCLK = 0x50400000
RCC_UART5CLK_LSE = 0x50800000
RCC_UART5CLK_HSI = 0x50C00000
# fun define IS_RCC_USARTCLK(USARTCLK) (((USARTCLK) == RCC_USART1CLK_PCLK) || ((USARTCLK) == RCC_USART1CLK_SYSCLK) || \
#                                   ((USARTCLK) == RCC_USART1CLK_LSE) || ((USARTCLK) == RCC_USART1CLK_HSI) ||\
#                                   ((USARTCLK) == RCC_USART2CLK_PCLK) || ((USARTCLK) == RCC_USART2CLK_SYSCLK) || \
#                                   ((USARTCLK) == RCC_USART2CLK_LSE) || ((USARTCLK) == RCC_USART2CLK_HSI) || \
#                                   ((USARTCLK) == RCC_USART3CLK_PCLK) || ((USARTCLK) == RCC_USART3CLK_SYSCLK) || \
#                                   ((USARTCLK) == RCC_USART3CLK_LSE) || ((USARTCLK) == RCC_USART3CLK_HSI) || \
#                                   ((USARTCLK) == RCC_UART4CLK_PCLK) || ((USARTCLK) == RCC_UART4CLK_SYSCLK) || \
#                                   ((USARTCLK) == RCC_UART4CLK_LSE) || ((USARTCLK) == RCC_UART4CLK_HSI) || \
#                                   ((USARTCLK) == RCC_UART5CLK_PCLK) || ((USARTCLK) == RCC_UART5CLK_SYSCLK) || \
#                                   ((USARTCLK) == RCC_UART5CLK_LSE) || ((USARTCLK) == RCC_UART5CLK_HSI))
RCC_IT_LSIRDY = 0x1
RCC_IT_LSERDY = 0x2
RCC_IT_HSIRDY = 0x4
RCC_IT_HSERDY = 0x8
RCC_IT_PLLRDY = 0x10
RCC_IT_CSS = 0x80
# fun define IS_RCC_IT(IT) ((((IT) & (uint8_t)0xC0) == 0x00) && ((IT) != 0x00))
# fun define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
#                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
#                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
# fun define IS_RCC_CLEAR_IT(IT) ((((IT) & (uint8_t)0x40) == 0x00) && ((IT) != 0x00))
RCC_LSE_OFF = 0x0
RCC_LSE_ON = 0x1
RCC_LSE_Bypass = 0x5
# fun define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
#                         ((LSE) == RCC_LSE_Bypass))
RCC_RTCCLKSource_LSE = 0x100
RCC_RTCCLKSource_LSI = 0x200
RCC_RTCCLKSource_HSE_Div32 = 0x300
# fun define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
#                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
#                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div32))
RCC_I2S2CLKSource_SYSCLK = 0x0
RCC_I2S2CLKSource_Ext = 0x1
# fun define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_SYSCLK) || ((SOURCE) == RCC_I2S2CLKSource_Ext))
RCC_LSEDrive_Low = 0x0
RCC_LSEDrive_MediumLow = 0x8
RCC_LSEDrive_MediumHigh = 0x10
RCC_LSEDrive_High = 0x18
# fun define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDrive_Low) || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
#                                 ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
RCC_AHBPeriph_ADC34 = 0x20000000
RCC_AHBPeriph_ADC12 = 0x10000000
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
RCC_AHBPeriph_DMA2 = 0x2
RCC_AHBPeriph_DMA1 = 0x1
# fun define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xCE81FFA8) == 0x00) && ((PERIPH) != 0x00))
# fun define IS_RCC_AHB_RST_PERIPH(PERIPH) ((((PERIPH) & 0xCE81FFFF) == 0x00) && ((PERIPH) != 0x00))
RCC_APB2Periph_SYSCFG = 0x1
RCC_APB2Periph_TIM1 = 0x800
RCC_APB2Periph_SPI1 = 0x1000
RCC_APB2Periph_TIM8 = 0x2000
RCC_APB2Periph_USART1 = 0x4000
RCC_APB2Periph_TIM15 = 0x10000
RCC_APB2Periph_TIM16 = 0x20000
RCC_APB2Periph_TIM17 = 0x40000
# fun define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFF887FE) == 0x00) && ((PERIPH) != 0x00))
RCC_APB1Periph_TIM2 = 0x1
RCC_APB1Periph_TIM3 = 0x2
RCC_APB1Periph_TIM4 = 0x4
RCC_APB1Periph_TIM6 = 0x10
RCC_APB1Periph_TIM7 = 0x20
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
RCC_APB1Periph_PWR = 0x10000000
RCC_APB1Periph_DAC = 0x20000000
# fun define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0xCD0137C8) == 0x00) && ((PERIPH) != 0x00))
RCC_MCOSource_NoClock = 0x0
RCC_MCOSource_LSI = 0x2
RCC_MCOSource_LSE = 0x3
RCC_MCOSource_SYSCLK = 0x4
RCC_MCOSource_HSI = 0x5
RCC_MCOSource_HSE = 0x6
RCC_MCOSource_PLLCLK_Div2 = 0x7
# fun define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSource_NoClock) ||((SOURCE) == RCC_MCOSource_SYSCLK) ||\
#                                    ((SOURCE) == RCC_MCOSource_HSI)  || ((SOURCE) == RCC_MCOSource_HSE) || \
#                                    ((SOURCE) == RCC_MCOSource_LSI)  || ((SOURCE) == RCC_MCOSource_LSE) || \
#                                    ((SOURCE) == RCC_MCOSource_PLLCLK_Div2))
RCC_USBCLKSource_PLLCLK_1Div5 = 0x0
RCC_USBCLKSource_PLLCLK_Div1 = 0x1
# fun define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
#                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))
RCC_FLAG_HSIRDY = 0x1
RCC_FLAG_HSERDY = 0x11
RCC_FLAG_PLLRDY = 0x19
RCC_FLAG_MCOF = 0x9C
RCC_FLAG_LSERDY = 0x21
RCC_FLAG_LSIRDY = 0x41
RCC_FLAG_OBLRST = 0x59
RCC_FLAG_PINRST = 0x5A
RCC_FLAG_PORRST = 0x5B
RCC_FLAG_SFTRST = 0x5C
RCC_FLAG_IWDGRST = 0x5D
RCC_FLAG_WWDGRST = 0x5E
RCC_FLAG_LPWRRST = 0x5F
# fun define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
#                           ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
#                           ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_OBLRST) || \
#                           ((FLAG) == RCC_FLAG_PINRST) || ((FLAG) == RCC_FLAG_PORRST) || \
#                           ((FLAG) == RCC_FLAG_SFTRST) || ((FLAG) == RCC_FLAG_IWDGRST)|| \
#                           ((FLAG) == RCC_FLAG_WWDGRST)|| ((FLAG) == RCC_FLAG_LPWRRST)|| \
#                           ((FLAG) == RCC_FLAG_MCOF))
# fun define IS_RCC_HSI_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
# struct RCC_ClocksTypeDef

class RCC_ClocksTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('SYSCLK_Frequency',	ctypes.c_uint32),
		('HCLK_Frequency',	ctypes.c_uint32),
		('PCLK1_Frequency',	ctypes.c_uint32),
		('PCLK2_Frequency',	ctypes.c_uint32),
		('ADC12CLK_Frequency',	ctypes.c_uint32),
		('ADC34CLK_Frequency',	ctypes.c_uint32),
		('I2C1CLK_Frequency',	ctypes.c_uint32),
		('I2C2CLK_Frequency',	ctypes.c_uint32),
		('TIM1CLK_Frequency',	ctypes.c_uint32),
		('TIM8CLK_Frequency',	ctypes.c_uint32),
		('USART1CLK_Frequency',	ctypes.c_uint32),
		('USART2CLK_Frequency',	ctypes.c_uint32),
		('USART3CLK_Frequency',	ctypes.c_uint32),
		('UART4CLK_Frequency',	ctypes.c_uint32),
		('UART5CLK_Frequency',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f30x_iwdg.h : 

# empty define __STM32F30X_IWDG_H
IWDG_WriteAccess_Enable = 0x5555
IWDG_WriteAccess_Disable = 0x0
# fun define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
#                                      ((ACCESS) == IWDG_WriteAccess_Disable))
IWDG_Prescaler_4 = 0x0
IWDG_Prescaler_8 = 0x1
IWDG_Prescaler_16 = 0x2
IWDG_Prescaler_32 = 0x3
IWDG_Prescaler_64 = 0x4
IWDG_Prescaler_128 = 0x5
IWDG_Prescaler_256 = 0x6
# fun define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4)  || \
#                                      ((PRESCALER) == IWDG_Prescaler_8)  || \
#                                      ((PRESCALER) == IWDG_Prescaler_16) || \
#                                      ((PRESCALER) == IWDG_Prescaler_32) || \
#                                      ((PRESCALER) == IWDG_Prescaler_64) || \
#                                      ((PRESCALER) == IWDG_Prescaler_128)|| \
#                                      ((PRESCALER) == IWDG_Prescaler_256))
IWDG_FLAG_PVU = 0x1
IWDG_FLAG_RVU = 0x2
IWDG_FLAG_WVU = 0x2
# fun define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU)  || \
#                            ((FLAG) == IWDG_FLAG_WVU))
# fun define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)
# fun define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
# ----------------------------------------

# file stm32f30x_exti.h : 

# Enum EXTIMode_TypeDef
EXTI_Mode_Interrupt = 0x0
EXTI_Mode_Event = 0x4
# Enum EXTITrigger_TypeDef
EXTI_Trigger_Rising = 0x8
EXTI_Trigger_Falling = 0xC
EXTI_Trigger_Rising_Falling = 0x10
# empty define __STM32F30x_EXTI_H
# fun define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))
# fun define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
#                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
#                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
EXTI_Line0 = 0x0
EXTI_Line1 = 0x1
EXTI_Line2 = 0x2
EXTI_Line3 = 0x3
EXTI_Line4 = 0x4
EXTI_Line5 = 0x5
EXTI_Line6 = 0x6
EXTI_Line7 = 0x7
EXTI_Line8 = 0x8
EXTI_Line9 = 0x9
EXTI_Line10 = 0xA
EXTI_Line11 = 0xB
EXTI_Line12 = 0xC
EXTI_Line13 = 0xD
EXTI_Line14 = 0xE
EXTI_Line15 = 0xF
EXTI_Line16 = 0x10
EXTI_Line17 = 0x11
EXTI_Line18 = 0x12
EXTI_Line19 = 0x13
EXTI_Line20 = 0x14
EXTI_Line21 = 0x15
EXTI_Line22 = 0x16
EXTI_Line23 = 0x17
EXTI_Line24 = 0x18
EXTI_Line25 = 0x19
EXTI_Line26 = 0x1A
EXTI_Line27 = 0x1B
EXTI_Line28 = 0x1C
EXTI_Line29 = 0x1D
EXTI_Line30 = 0x1E
EXTI_Line31 = 0x1F
EXTI_Line32 = 0x20
EXTI_Line33 = 0x21
EXTI_Line34 = 0x22
EXTI_Line35 = 0x23
# fun define IS_EXTI_LINE_ALL(LINE) ((LINE) <= 0x23)
# fun define IS_EXTI_LINE_EXT(LINE) (((LINE) <= 0x16) || (((LINE) == EXTI_Line29) || ((LINE) == EXTI_Line30) || \
#                               ((LINE) == EXTI_Line31) || ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33)))
# fun define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
#                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
#                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
#                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
#                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
#                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
#                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
#                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
#                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
#                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
#                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
#                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line29) || \
#                                ((LINE) == EXTI_Line30) || ((LINE) == EXTI_Line31) || \
#                                ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33))
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

# file stm32f30x_dac.h : 

# empty define __STM32F30x_DAC_H
DAC_CR_DMAUDRIE = 0x2000
DAC_Trigger_None = 0x0
DAC_Trigger_T2_TRGO = 0x24
DAC_Trigger_T3_TRGO = 0xC
DAC_Trigger_T4_TRGO = 0x2C
DAC_Trigger_T6_TRGO = 0x4
DAC_Trigger_T7_TRGO = 0x14
DAC_Trigger_T8_TRGO = 0xC
DAC_Trigger_T15_TRGO = 0x1C
DAC_Trigger_Ext_IT9 = 0x34
DAC_Trigger_Software = 0x3C
# fun define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None)     || \
#                                 ((TRIGGER) == DAC_Trigger_T2_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T3_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T4_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T6_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T7_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T8_TRGO)  || \
#                                 ((TRIGGER) == DAC_Trigger_T15_TRGO) || \
#                                 ((TRIGGER) == DAC_Trigger_Ext_IT9)  || \
#                                 ((TRIGGER) == DAC_Trigger_Software))
DAC_WaveGeneration_None = 0x0
DAC_WaveGeneration_Noise = 0x40
DAC_WaveGeneration_Triangle = 0x80
# fun define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None)  || \
#                                    ((WAVE) == DAC_WaveGeneration_Noise) || \
#                                    ((WAVE) == DAC_WaveGeneration_Triangle))
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
# fun define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUnmask_Bit0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits1_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits2_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits3_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits4_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits5_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits6_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits7_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits8_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits9_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits10_0) || \
#                                                      ((VALUE) == DAC_LFSRUnmask_Bits11_0) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_1) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_3) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_7) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_15) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_31) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_63) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_127) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_255) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_511) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_1023) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_2047) || \
#                                                      ((VALUE) == DAC_TriangleAmplitude_4095))
DAC_OutputBuffer_Enable = 0x0
DAC_OutputBuffer_Disable = 0x2
# fun define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
#                                           ((STATE) == DAC_OutputBuffer_Disable))
DAC_Channel_1 = 0x0
DAC_Channel_2 = 0x10
# fun define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
#                                 ((CHANNEL) == DAC_Channel_2))
DAC_Align_12b_R = 0x0
DAC_Align_12b_L = 0x4
DAC_Align_8b_R = 0x8
# fun define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
#                             ((ALIGN) == DAC_Align_12b_L) || \
#                             ((ALIGN) == DAC_Align_8b_R))
DAC_Wave_Noise = 0x40
DAC_Wave_Triangle = 0x80
# fun define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || \
#                           ((WAVE) == DAC_Wave_Triangle))
# fun define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0)
DAC_IT_DMAUDR = 0x2000
# fun define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR))
DAC_FLAG_DMAUDR = 0x2000
# fun define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))
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

# file stm32f30x_gpio.h : 

# Enum GPIOMode_TypeDef
GPIO_Mode_IN = 0x0
GPIO_Mode_OUT = 0x1
GPIO_Mode_AF = 0x2
GPIO_Mode_AN = 0x3
# Enum GPIOOType_TypeDef
GPIO_OType_PP = 0x0
GPIO_OType_OD = 0x1
# Enum GPIOSpeed_TypeDef
GPIO_Speed_2MHz = 0x1
GPIO_Speed_10MHz = 0x2
GPIO_Speed_50MHz = 0x3
# Enum GPIOPuPd_TypeDef
GPIO_PuPd_NOPULL = 0x0
GPIO_PuPd_UP = 0x1
GPIO_PuPd_DOWN = 0x2
# Enum BitAction
Bit_RESET = 0x0
Bit_SET = 0x1
# empty define __STM32F30x_GPIO_H
# fun define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
#                                    ((PERIPH) == GPIOB) || \
#                                    ((PERIPH) == GPIOC) || \
#                                    ((PERIPH) == GPIOD) || \
#                                    ((PERIPH) == GPIOE) || \
#                                    ((PERIPH) == GPIOF))
# fun define IS_GPIO_LIST_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
#                                     ((PERIPH) == GPIOB) || \
#                                     ((PERIPH) == GPIOD))
# fun define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)|| ((MODE) == GPIO_Mode_OUT) || \
#                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))
# fun define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))
# fun define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_2MHz) || \
#                              ((SPEED) == GPIO_Speed_10MHz)||  ((SPEED) == GPIO_Speed_50MHz))
# fun define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
#                            ((PUPD) == GPIO_PuPd_DOWN))
# fun define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
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
# fun define IS_GPIO_PIN(PIN) ((PIN) != (uint16_t)0x00)
# fun define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
#                              ((PIN) == GPIO_Pin_1) || \
#                              ((PIN) == GPIO_Pin_2) || \
#                              ((PIN) == GPIO_Pin_3) || \
#                              ((PIN) == GPIO_Pin_4) || \
#                              ((PIN) == GPIO_Pin_5) || \
#                              ((PIN) == GPIO_Pin_6) || \
#                              ((PIN) == GPIO_Pin_7) || \
#                              ((PIN) == GPIO_Pin_8) || \
#                              ((PIN) == GPIO_Pin_9) || \
#                              ((PIN) == GPIO_Pin_10) || \
#                              ((PIN) == GPIO_Pin_11) || \
#                              ((PIN) == GPIO_Pin_12) || \
#                              ((PIN) == GPIO_Pin_13) || \
#                              ((PIN) == GPIO_Pin_14) || \
#                              ((PIN) == GPIO_Pin_15))
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
# fun define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
#                                       ((PINSOURCE) == GPIO_PinSource1) || \
#                                       ((PINSOURCE) == GPIO_PinSource2) || \
#                                       ((PINSOURCE) == GPIO_PinSource3) || \
#                                       ((PINSOURCE) == GPIO_PinSource4) || \
#                                       ((PINSOURCE) == GPIO_PinSource5) || \
#                                       ((PINSOURCE) == GPIO_PinSource6) || \
#                                       ((PINSOURCE) == GPIO_PinSource7) || \
#                                       ((PINSOURCE) == GPIO_PinSource8) || \
#                                       ((PINSOURCE) == GPIO_PinSource9) || \
#                                       ((PINSOURCE) == GPIO_PinSource10) || \
#                                       ((PINSOURCE) == GPIO_PinSource11) || \
#                                       ((PINSOURCE) == GPIO_PinSource12) || \
#                                       ((PINSOURCE) == GPIO_PinSource13) || \
#                                       ((PINSOURCE) == GPIO_PinSource14) || \
#                                       ((PINSOURCE) == GPIO_PinSource15))
GPIO_AF_0 = 0x0
GPIO_AF_1 = 0x1
GPIO_AF_2 = 0x2
GPIO_AF_3 = 0x3
GPIO_AF_4 = 0x4
GPIO_AF_5 = 0x5
GPIO_AF_6 = 0x6
GPIO_AF_7 = 0x7
GPIO_AF_8 = 0x8
GPIO_AF_9 = 0x9
GPIO_AF_10 = 0xA
GPIO_AF_11 = 0xB
GPIO_AF_12 = 0xE
GPIO_AF_14 = 0xE
GPIO_AF_15 = 0xF
# fun define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0)||((AF) == GPIO_AF_1)||\
#                          ((AF) == GPIO_AF_2)||((AF) == GPIO_AF_3)||\
#                          ((AF) == GPIO_AF_4)||((AF) == GPIO_AF_5)||\
#                          ((AF) == GPIO_AF_6)||((AF) == GPIO_AF_7)||\
#                          ((AF) == GPIO_AF_8)||((AF) == GPIO_AF_9)||\
#                          ((AF) == GPIO_AF_10)||((AF) == GPIO_AF_11)||\
#                          ((AF) == GPIO_AF_14)||((AF) == GPIO_AF_15))
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

# file stm32f30x_tim.h : 

# empty define __stm32f30x_TIM_H
# fun define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                   ((PERIPH) == TIM2) || \
#                                   ((PERIPH) == TIM3) || \
#                                   ((PERIPH) == TIM4) || \
#                                   ((PERIPH) == TIM6) || \
#                                   ((PERIPH) == TIM7) || \
#                                   ((PERIPH) == TIM8) || \
#                                   ((PERIPH) == TIM15) || \
#                                   ((PERIPH) == TIM16) || \
#                                   ((PERIPH) == TIM17))
# fun define IS_TIM_LIST1_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM2) || \
#                                     ((PERIPH) == TIM3) || \
#                                     ((PERIPH) == TIM4) || \
#                                     ((PERIPH) == TIM8) || \
#                                     ((PERIPH) == TIM15) || \
#                                     ((PERIPH) == TIM16) || \
#                                     ((PERIPH) == TIM17))
# fun define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM2) || \
#                                     ((PERIPH) == TIM3) || \
#                                     ((PERIPH) == TIM4) || \
#                                     ((PERIPH) == TIM8) || \
#                                     ((PERIPH) == TIM15))
# fun define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM2) || \
#                                     ((PERIPH) == TIM3) || \
#                                     ((PERIPH) == TIM4) || \
#                                     ((PERIPH) == TIM8))
# fun define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) ||\
#                                     ((PERIPH) == TIM8))
# fun define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM2) || \
#                                     ((PERIPH) == TIM3) || \
#                                     ((PERIPH) == TIM4) || \
#                                     ((PERIPH) == TIM6) || \
#                                     ((PERIPH) == TIM7) || \
#                                     ((PERIPH) == TIM8))
# fun define IS_TIM_LIST6_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM8) || \
#                                     ((PERIPH) == TIM15) || \
#                                     ((PERIPH) == TIM16) || \
#                                     ((PERIPH) == TIM17))
# fun define IS_TIM_LIST7_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
#                                     ((PERIPH) == TIM2) || \
#                                     ((PERIPH) == TIM3) || \
#                                     ((PERIPH) == TIM4) || \
#                                     ((PERIPH) == TIM6) || \
#                                     ((PERIPH) == TIM7) || \
#                                     ((PERIPH) == TIM8) || \
#                                     ((PERIPH) == TIM15))
# fun define IS_TIM_LIST8_PERIPH(PERIPH) (((PERIPH) == TIM16)||  \
#                                     ((PERIPH) == TIM1)||\
#                                     ((PERIPH) == TIM8))
TIM_OCMode_Timing = 0x0
TIM_OCMode_Active = 0x10
TIM_OCMode_Inactive = 0x20
TIM_OCMode_Toggle = 0x30
TIM_OCMode_PWM1 = 0x60
TIM_OCMode_PWM2 = 0x70
TIM_OCMode_Retrigerrable_OPM1 = 0x10000
TIM_OCMode_Retrigerrable_OPM2 = 0x10010
TIM_OCMode_Combined_PWM1 = 0x10040
TIM_OCMode_Combined_PWM2 = 0x10050
TIM_OCMode_Asymmetric_PWM1 = 0x10060
TIM_OCMode_Asymmetric_PWM2 = 0x10070
# fun define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
#                              ((MODE) == TIM_OCMode_Active) || \
#                              ((MODE) == TIM_OCMode_Inactive) || \
#                              ((MODE) == TIM_OCMode_Toggle)|| \
#                              ((MODE) == TIM_OCMode_PWM1) || \
#                              ((MODE) == TIM_OCMode_PWM2) || \
#                              ((MODE) == TIM_OCMode_Retrigerrable_OPM1) || \
#                              ((MODE) == TIM_OCMode_Retrigerrable_OPM2) || \
#                              ((MODE) == TIM_OCMode_Combined_PWM1) || \
#                              ((MODE) == TIM_OCMode_Combined_PWM2) || \
#                              ((MODE) == TIM_OCMode_Asymmetric_PWM1) || \
#                              ((MODE) == TIM_OCMode_Asymmetric_PWM2))
# fun define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
#                          ((MODE) == TIM_OCMode_Active) || \
#                          ((MODE) == TIM_OCMode_Inactive) || \
#                          ((MODE) == TIM_OCMode_Toggle)|| \
#                          ((MODE) == TIM_OCMode_PWM1) || \
#                          ((MODE) == TIM_OCMode_PWM2) ||	\
#                          ((MODE) == TIM_ForcedAction_Active) || \
#                          ((MODE) == TIM_ForcedAction_InActive) || \
#                          ((MODE) == TIM_OCMode_Retrigerrable_OPM1) || \
#                          ((MODE) == TIM_OCMode_Retrigerrable_OPM2) || \
#                          ((MODE) == TIM_OCMode_Combined_PWM1) || \
#                          ((MODE) == TIM_OCMode_Combined_PWM2) || \
#                          ((MODE) == TIM_OCMode_Asymmetric_PWM1) || \
#                          ((MODE) == TIM_OCMode_Asymmetric_PWM2))
TIM_OPMode_Single = 0x8
TIM_OPMode_Repetitive = 0x0
# fun define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
#                               ((MODE) == TIM_OPMode_Repetitive))
TIM_Channel_1 = 0x0
TIM_Channel_2 = 0x4
TIM_Channel_3 = 0x8
TIM_Channel_4 = 0xC
TIM_Channel_5 = 0x10
TIM_Channel_6 = 0x14
# fun define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
#                                 ((CHANNEL) == TIM_Channel_2) || \
#                                 ((CHANNEL) == TIM_Channel_3) || \
#                                 ((CHANNEL) == TIM_Channel_4))
# fun define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
#                                      ((CHANNEL) == TIM_Channel_2))
# fun define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
#                                               ((CHANNEL) == TIM_Channel_2) || \
#                                               ((CHANNEL) == TIM_Channel_3))
TIM_CKD_DIV1 = 0x0
TIM_CKD_DIV2 = 0x100
TIM_CKD_DIV4 = 0x200
# fun define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
#                             ((DIV) == TIM_CKD_DIV2) || \
#                             ((DIV) == TIM_CKD_DIV4))
TIM_CounterMode_Up = 0x0
TIM_CounterMode_Down = 0x10
TIM_CounterMode_CenterAligned1 = 0x20
TIM_CounterMode_CenterAligned2 = 0x40
TIM_CounterMode_CenterAligned3 = 0x60
# fun define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
#                                   ((MODE) == TIM_CounterMode_Down) || \
#                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
#                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
#                                   ((MODE) == TIM_CounterMode_CenterAligned3))
TIM_OCPolarity_High = 0x0
TIM_OCPolarity_Low = 0x2
# fun define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
#                                      ((POLARITY) == TIM_OCPolarity_Low))
TIM_OCNPolarity_High = 0x0
TIM_OCNPolarity_Low = 0x8
# fun define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
#                                       ((POLARITY) == TIM_OCNPolarity_Low))
TIM_OutputState_Disable = 0x0
TIM_OutputState_Enable = 0x1
# fun define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
#                                    ((STATE) == TIM_OutputState_Enable))
TIM_OutputNState_Disable = 0x0
TIM_OutputNState_Enable = 0x4
# fun define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
#                                     ((STATE) == TIM_OutputNState_Enable))
TIM_CCx_Enable = 0x1
TIM_CCx_Disable = 0x0
# fun define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
#                         ((CCX) == TIM_CCx_Disable))
TIM_CCxN_Enable = 0x4
TIM_CCxN_Disable = 0x0
# fun define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
#                           ((CCXN) == TIM_CCxN_Disable))
TIM_Break_Enable = 0x1000
TIM_Break_Disable = 0x0
# fun define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
#                                   ((STATE) == TIM_Break_Disable))
TIM_Break1_Enable = 0x1000
TIM_Break1_Disable = 0x0
# fun define IS_TIM_BREAK1_STATE(STATE) (((STATE) == TIM_Break1_Enable) || \
#                                   ((STATE) == TIM_Break1_Disable))
TIM_Break2_Enable = 0x1000000
TIM_Break2_Disable = 0x0
# fun define IS_TIM_BREAK2_STATE(STATE) (((STATE) == TIM_Break2_Enable) || \
#                                   ((STATE) == TIM_Break2_Disable))
TIM_BreakPolarity_Low = 0x0
TIM_BreakPolarity_High = 0x2000
# fun define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
#                                         ((POLARITY) == TIM_BreakPolarity_High))
TIM_Break1Polarity_Low = 0x0
TIM_Break1Polarity_High = 0x2000
# fun define IS_TIM_BREAK1_POLARITY(POLARITY) (((POLARITY) == TIM_Break1Polarity_Low) || \
#                                         ((POLARITY) == TIM_Break1Polarity_High))
TIM_Break2Polarity_Low = 0x0
TIM_Break2Polarity_High = 0x2000000
# fun define IS_TIM_BREAK2_POLARITY(POLARITY) (((POLARITY) == TIM_Break2Polarity_Low) || \
#                                         ((POLARITY) == TIM_Break2Polarity_High))
# fun define IS_TIM_BREAK1_FILTER(FILTER) ((FILTER) <= 0xF)
# fun define IS_TIM_BREAK2_FILTER(FILTER) ((FILTER) <= 0xF)
TIM_AutomaticOutput_Enable = 0x4000
TIM_AutomaticOutput_Disable = 0x0
# fun define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
#                                              ((STATE) == TIM_AutomaticOutput_Disable))
TIM_LOCKLevel_OFF = 0x0
TIM_LOCKLevel_1 = 0x100
TIM_LOCKLevel_2 = 0x200
TIM_LOCKLevel_3 = 0x300
# fun define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
#                                  ((LEVEL) == TIM_LOCKLevel_1) || \
#                                  ((LEVEL) == TIM_LOCKLevel_2) || \
#                                  ((LEVEL) == TIM_LOCKLevel_3))
TIM_OSSIState_Enable = 0x400
TIM_OSSIState_Disable = 0x0
# fun define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
#                                  ((STATE) == TIM_OSSIState_Disable))
TIM_OSSRState_Enable = 0x800
TIM_OSSRState_Disable = 0x0
# fun define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
#                                  ((STATE) == TIM_OSSRState_Disable))
TIM_OCIdleState_Set = 0x100
TIM_OCIdleState_Reset = 0x0
# fun define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
#                                    ((STATE) == TIM_OCIdleState_Reset))
TIM_OCNIdleState_Set = 0x200
TIM_OCNIdleState_Reset = 0x0
# fun define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
#                                     ((STATE) == TIM_OCNIdleState_Reset))
TIM_ICPolarity_Rising = 0x0
TIM_ICPolarity_Falling = 0x2
TIM_ICPolarity_BothEdge = 0xA
# fun define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
#                                      ((POLARITY) == TIM_ICPolarity_Falling)|| \
#                                      ((POLARITY) == TIM_ICPolarity_BothEdge))
TIM_ICSelection_DirectTI = 0x1
TIM_ICSelection_IndirectTI = 0x2
TIM_ICSelection_TRC = 0x3
# fun define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
#                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
#                                        ((SELECTION) == TIM_ICSelection_TRC))
TIM_ICPSC_DIV1 = 0x0
TIM_ICPSC_DIV2 = 0x4
TIM_ICPSC_DIV4 = 0x8
TIM_ICPSC_DIV8 = 0xC
# fun define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
#                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
#                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
#                                        ((PRESCALER) == TIM_ICPSC_DIV8))
TIM_IT_Update = 0x1
TIM_IT_CC1 = 0x2
TIM_IT_CC2 = 0x4
TIM_IT_CC3 = 0x8
TIM_IT_CC4 = 0x10
TIM_IT_COM = 0x20
TIM_IT_Trigger = 0x40
TIM_IT_Break = 0x80
# fun define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))
# fun define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
#                           ((IT) == TIM_IT_CC1) || \
#                           ((IT) == TIM_IT_CC2) || \
#                           ((IT) == TIM_IT_CC3) || \
#                           ((IT) == TIM_IT_CC4) || \
#                           ((IT) == TIM_IT_COM) || \
#                           ((IT) == TIM_IT_Trigger) || \
#                           ((IT) == TIM_IT_Break))
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
TIM_DMABase_CCMR3 = 0x14
TIM_DMABase_CCR5 = 0x15
TIM_DMABase_CCR6 = 0x16
# fun define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
#                               ((BASE) == TIM_DMABase_CR2) || \
#                               ((BASE) == TIM_DMABase_SMCR) || \
#                               ((BASE) == TIM_DMABase_DIER) || \
#                               ((BASE) == TIM_DMABase_SR) || \
#                               ((BASE) == TIM_DMABase_EGR) || \
#                               ((BASE) == TIM_DMABase_CCMR1) || \
#                               ((BASE) == TIM_DMABase_CCMR2) || \
#                               ((BASE) == TIM_DMABase_CCER) || \
#                               ((BASE) == TIM_DMABase_CNT) || \
#                               ((BASE) == TIM_DMABase_PSC) || \
#                               ((BASE) == TIM_DMABase_ARR) || \
#                               ((BASE) == TIM_DMABase_RCR) || \
#                               ((BASE) == TIM_DMABase_CCR1) || \
#                               ((BASE) == TIM_DMABase_CCR2) || \
#                               ((BASE) == TIM_DMABase_CCR3) || \
#                               ((BASE) == TIM_DMABase_CCR4) || \
#                               ((BASE) == TIM_DMABase_BDTR) || \
#                               ((BASE) == TIM_DMABase_DCR) || \
#                               ((BASE) == TIM_DMABase_OR) || \
#                               ((BASE) == TIM_DMABase_CCMR3) || \
#                               ((BASE) == TIM_DMABase_CCR5) || \
#                               ((BASE) == TIM_DMABase_CCR6))
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
# fun define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer) || \
#                                   ((LENGTH) == TIM_DMABurstLength_2Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_3Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_4Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_5Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_6Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_7Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_8Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_9Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
#                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))
TIM_DMA_Update = 0x100
TIM_DMA_CC1 = 0x200
TIM_DMA_CC2 = 0x400
TIM_DMA_CC3 = 0x800
TIM_DMA_CC4 = 0x1000
TIM_DMA_COM = 0x2000
TIM_DMA_Trigger = 0x4000
# fun define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))
TIM_ExtTRGPSC_OFF = 0x0
TIM_ExtTRGPSC_DIV2 = 0x1000
TIM_ExtTRGPSC_DIV4 = 0x2000
TIM_ExtTRGPSC_DIV8 = 0x3000
# fun define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
#                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
#                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
#                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
TIM_TS_ITR0 = 0x0
TIM_TS_ITR1 = 0x10
TIM_TS_ITR2 = 0x20
TIM_TS_ITR3 = 0x30
TIM_TS_TI1F_ED = 0x40
TIM_TS_TI1FP1 = 0x50
TIM_TS_TI2FP2 = 0x60
TIM_TS_ETRF = 0x70
# fun define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
#                                             ((SELECTION) == TIM_TS_ITR1) || \
#                                             ((SELECTION) == TIM_TS_ITR2) || \
#                                             ((SELECTION) == TIM_TS_ITR3) || \
#                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
#                                             ((SELECTION) == TIM_TS_TI1FP1) || \
#                                             ((SELECTION) == TIM_TS_TI2FP2) || \
#                                             ((SELECTION) == TIM_TS_ETRF))
# fun define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
#                                                      ((SELECTION) == TIM_TS_ITR1) || \
#                                                      ((SELECTION) == TIM_TS_ITR2) || \
#                                                      ((SELECTION) == TIM_TS_ITR3))
TIM_TIxExternalCLK1Source_TI1 = 0x50
TIM_TIxExternalCLK1Source_TI2 = 0x60
TIM_TIxExternalCLK1Source_TI1ED = 0x40
TIM_ExtTRGPolarity_Inverted = 0x8000
TIM_ExtTRGPolarity_NonInverted = 0x0
# fun define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
#                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
TIM_PSCReloadMode_Update = 0x0
TIM_PSCReloadMode_Immediate = 0x1
# fun define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
#                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
TIM_ForcedAction_Active = 0x50
TIM_ForcedAction_InActive = 0x40
# fun define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
#                                      ((ACTION) == TIM_ForcedAction_InActive))
TIM_EncoderMode_TI1 = 0x1
TIM_EncoderMode_TI2 = 0x2
TIM_EncoderMode_TI12 = 0x3
# fun define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
#                                   ((MODE) == TIM_EncoderMode_TI2) || \
#                                   ((MODE) == TIM_EncoderMode_TI12))
TIM_EventSource_Update = 0x1
TIM_EventSource_CC1 = 0x2
TIM_EventSource_CC2 = 0x4
TIM_EventSource_CC3 = 0x8
TIM_EventSource_CC4 = 0x10
TIM_EventSource_COM = 0x20
TIM_EventSource_Trigger = 0x40
TIM_EventSource_Break = 0x80
TIM_EventSource_Break2 = 0x100
# fun define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFE00) == 0x0000) && ((SOURCE) != 0x0000))
TIM_UpdateSource_Global = 0x0
TIM_UpdateSource_Regular = 0x1
# fun define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
#                                      ((SOURCE) == TIM_UpdateSource_Regular))
TIM_OCPreload_Enable = 0x8
TIM_OCPreload_Disable = 0x0
# fun define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
#                                       ((STATE) == TIM_OCPreload_Disable))
TIM_OCFast_Enable = 0x4
TIM_OCFast_Disable = 0x0
# fun define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
#                                    ((STATE) == TIM_OCFast_Disable))
TIM_OCClear_Enable = 0x80
TIM_OCClear_Disable = 0x0
# fun define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
#                                     ((STATE) == TIM_OCClear_Disable))
TIM_TRGOSource_Reset = 0x0
TIM_TRGOSource_Enable = 0x10
TIM_TRGOSource_Update = 0x20
TIM_TRGOSource_OC1 = 0x30
TIM_TRGOSource_OC1Ref = 0x40
TIM_TRGOSource_OC2Ref = 0x50
TIM_TRGOSource_OC3Ref = 0x60
TIM_TRGOSource_OC4Ref = 0x70
# fun define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
#                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
#                                    ((SOURCE) == TIM_TRGOSource_Update) || \
#                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
#                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
#                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
#                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
#                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
TIM_TRGO2Source_Reset = 0x0
TIM_TRGO2Source_Enable = 0x100000
TIM_TRGO2Source_Update = 0x200000
TIM_TRGO2Source_OC1 = 0x300000
TIM_TRGO2Source_OC1Ref = 0x400000
TIM_TRGO2Source_OC2Ref = 0x500000
TIM_TRGO2Source_OC3Ref = 0x600000
TIM_TRGO2Source_OC4Ref = 0x700000
TIM_TRGO2Source_OC5Ref = 0x800000
TIM_TRGO2Source_OC6Ref = 0x900000
TIM_TRGO2Source_OC4Ref_RisingFalling = 0xA00000
TIM_TRGO2Source_OC6Ref_RisingFalling = 0xB00000
TIM_TRGO2Source_OC4RefRising_OC6RefRising = 0xC00000
TIM_TRGO2Source_OC4RefRising_OC6RefFalling = 0xD00000
TIM_TRGO2Source_OC5RefRising_OC6RefRising = 0xE00000
TIM_TRGO2Source_OC5RefRising_OC6RefFalling = 0xF00000
# fun define IS_TIM_TRGO2_SOURCE(SOURCE) (((SOURCE) == TIM_TRGO2Source_Reset) || \
#                                     ((SOURCE) == TIM_TRGO2Source_Enable) || \
#                                     ((SOURCE) == TIM_TRGO2Source_Update) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC1) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC1Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC2Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC3Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC4Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC5Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC6Ref) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC4Ref_RisingFalling) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC6Ref_RisingFalling) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC4RefRising_OC6RefRising) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC4RefRising_OC6RefFalling) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC5RefRising_OC6RefRising) || \
#                                     ((SOURCE) == TIM_TRGO2Source_OC5RefRising_OC6RefFalling))
TIM_SlaveMode_Reset = 0x4
TIM_SlaveMode_Gated = 0x5
TIM_SlaveMode_Trigger = 0x6
TIM_SlaveMode_External1 = 0x7
TIM_SlaveMode_Combined_ResetTrigger = 0x10000
# fun define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
#                                 ((MODE) == TIM_SlaveMode_Gated) || \
#                                 ((MODE) == TIM_SlaveMode_Trigger) || \
#                                 ((MODE) == TIM_SlaveMode_External1) || \
#                                 ((MODE) == TIM_SlaveMode_Combined_ResetTrigger))
TIM_MasterSlaveMode_Enable = 0x80
TIM_MasterSlaveMode_Disable = 0x0
# fun define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
#                                 ((STATE) == TIM_MasterSlaveMode_Disable))
TIM16_GPIO = 0x0
TIM16_RTC_CLK = 0x1
TIM16_HSEDiv32 = 0x2
TIM16_MCO = 0x3
TIM1_ADC1_AWDG1 = 0x1
TIM1_ADC1_AWDG2 = 0x2
TIM1_ADC1_AWDG3 = 0x3
TIM1_ADC4_AWDG1 = 0x4
TIM1_ADC4_AWDG2 = 0x8
TIM1_ADC4_AWDG3 = 0xC
TIM8_ADC2_AWDG1 = 0x1
TIM8_ADC2_AWDG2 = 0x2
TIM8_ADC2_AWDG3 = 0x3
TIM8_ADC3_AWDG1 = 0x4
TIM8_ADC3_AWDG2 = 0x8
TIM8_ADC3_AWDG3 = 0xC
# fun define IS_TIM_REMAP(TIM_REMAP)  (((TIM_REMAP) == TIM16_GPIO)|| \
#                                  ((TIM_REMAP) == TIM16_RTC_CLK) || \
#                                  ((TIM_REMAP) == TIM16_HSEDiv32) || \
#                                  ((TIM_REMAP) == TIM16_MCO) ||\
#                                  ((TIM_REMAP) == TIM1_ADC1_AWDG1) ||\
#                                  ((TIM_REMAP) == TIM1_ADC1_AWDG2) ||\
#                                  ((TIM_REMAP) == TIM1_ADC1_AWDG3) ||\
#                                  ((TIM_REMAP) == TIM1_ADC4_AWDG1) ||\
#                                  ((TIM_REMAP) == TIM1_ADC4_AWDG2) ||\
#                                  ((TIM_REMAP) == TIM1_ADC4_AWDG3) ||\
#                                  ((TIM_REMAP) == TIM8_ADC2_AWDG1) ||\
#                                  ((TIM_REMAP) == TIM8_ADC2_AWDG2) ||\
#                                  ((TIM_REMAP) == TIM8_ADC2_AWDG3) ||\
#                                  ((TIM_REMAP) == TIM8_ADC3_AWDG1) ||\
#                                  ((TIM_REMAP) == TIM8_ADC3_AWDG2) ||\
#                                  ((TIM_REMAP) == TIM8_ADC3_AWDG3))
TIM_FLAG_Update = 0x1
TIM_FLAG_CC1 = 0x2
TIM_FLAG_CC2 = 0x4
TIM_FLAG_CC3 = 0x8
TIM_FLAG_CC4 = 0x10
TIM_FLAG_COM = 0x20
TIM_FLAG_Trigger = 0x40
TIM_FLAG_Break = 0x80
TIM_FLAG_Break2 = 0x100
TIM_FLAG_CC1OF = 0x200
TIM_FLAG_CC2OF = 0x400
TIM_FLAG_CC3OF = 0x800
TIM_FLAG_CC4OF = 0x1000
TIM_FLAG_CC5 = 0x10000
TIM_FLAG_CC6 = 0x20000
# fun define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
#                               ((FLAG) == TIM_FLAG_CC1) || \
#                               ((FLAG) == TIM_FLAG_CC2) || \
#                               ((FLAG) == TIM_FLAG_CC3) || \
#                               ((FLAG) == TIM_FLAG_CC4) || \
#                               ((FLAG) == TIM_FLAG_COM) || \
#                               ((FLAG) == TIM_FLAG_Trigger) || \
#                               ((FLAG) == TIM_FLAG_Break) || \
#                               ((FLAG) == TIM_FLAG_Break2) || \
#                               ((FLAG) == TIM_FLAG_CC1OF) || \
#                               ((FLAG) == TIM_FLAG_CC2OF) || \
#                               ((FLAG) == TIM_FLAG_CC3OF) || \
#                               ((FLAG) == TIM_FLAG_CC4OF) ||\
#                               ((FLAG) == TIM_FLAG_CC5) ||\
#                               ((FLAG) == TIM_FLAG_CC6))
# fun define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint32_t)0xE000) == 0x0000) && ((TIM_FLAG) != 0x0000))
TIM_OCReferenceClear_ETRF = 0x8
TIM_OCReferenceClear_OCREFCLR = 0x0
# fun define TIM_OCREFERENCECECLEAR_SOURCE(SOURCE) (((SOURCE) == TIM_OCReferenceClear_ETRF) || \
#                                              ((SOURCE) == TIM_OCReferenceClear_OCREFCLR))
# fun define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)
# fun define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)
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
		('TIM_OCMode',	ctypes.c_uint32),
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

# file stm32f30x_misc.h : 

# empty define __STM32F30x_MISC_H
NVIC_VectTab_RAM = 0x20000000
NVIC_VectTab_FLASH = 0x8000000
# fun define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
#                                  ((VECTTAB) == NVIC_VectTab_FLASH))
NVIC_LP_SEVONPEND = 0x10
NVIC_LP_SLEEPDEEP = 0x4
NVIC_LP_SLEEPONEXIT = 0x2
# fun define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
#                        ((LP) == NVIC_LP_SLEEPDEEP) || \
#                        ((LP) == NVIC_LP_SLEEPONEXIT))
NVIC_PriorityGroup_0 = 0x700
NVIC_PriorityGroup_1 = 0x600
NVIC_PriorityGroup_2 = 0x500
NVIC_PriorityGroup_3 = 0x400
NVIC_PriorityGroup_4 = 0x300
# fun define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
#                                       ((GROUP) == NVIC_PriorityGroup_1) || \
#                                       ((GROUP) == NVIC_PriorityGroup_2) || \
#                                       ((GROUP) == NVIC_PriorityGroup_3) || \
#                                       ((GROUP) == NVIC_PriorityGroup_4))
# fun define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)
# fun define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)
# fun define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)
SysTick_CLKSource_HCLK_Div8 = 0xFFFFFFFB
SysTick_CLKSource_HCLK = 0x4
# fun define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
#                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))
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

# file stm32f30x_dbgmcu.h : 

# empty define __STM32F30x_DBGMCU_H
DBGMCU_SLEEP = 0x1
DBGMCU_STOP = 0x2
DBGMCU_STANDBY = 0x4
# fun define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00))
DBGMCU_TIM2_STOP = 0x1
DBGMCU_TIM3_STOP = 0x2
DBGMCU_TIM4_STOP = 0x4
DBGMCU_TIM6_STOP = 0x10
DBGMCU_TIM7_STOP = 0x20
DBGMCU_RTC_STOP = 0x400
DBGMCU_WWDG_STOP = 0x800
DBGMCU_IWDG_STOP = 0x1000
DBGMCU_I2C1_SMBUS_TIMEOUT = 0x200000
DBGMCU_I2C2_SMBUS_TIMEOUT = 0x400000
DBGMCU_CAN1_STOP = 0x2000000
# fun define IS_DBGMCU_APB1PERIPH(PERIPH) ((((PERIPH) & 0xFD9FE3C8) == 0x00) && ((PERIPH) != 0x00))
DBGMCU_TIM1_STOP = 0x1
DBGMCU_TIM8_STOP = 0x2
DBGMCU_TIM15_STOP = 0x4
DBGMCU_TIM16_STOP = 0x8
DBGMCU_TIM17_STOP = 0x10
# fun define IS_DBGMCU_APB2PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFE0) == 0x00) && ((PERIPH) != 0x00))
# ----------------------------------------

# file stm32f30x_i2c.h : 

# empty define __STM32F30x_I2C_H
# fun define IS_I2C_ALL_PERIPH(PERIPH)       (((PERIPH) == I2C1) || \
#                                         ((PERIPH) == I2C2))
I2C_AnalogFilter_Enable = 0x0
I2C_AnalogFilter_Disable = 0x1000
# fun define IS_I2C_ANALOG_FILTER(FILTER)    (((FILTER) == I2C_AnalogFilter_Enable) || \
#                                         ((FILTER) == I2C_AnalogFilter_Disable))
# fun define IS_I2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000F)
I2C_Mode_I2C = 0x0
I2C_Mode_SMBusDevice = 0x200000
I2C_Mode_SMBusHost = 0x100000
# fun define IS_I2C_MODE(MODE)               (((MODE) == I2C_Mode_I2C) || \
#                                         ((MODE) == I2C_Mode_SMBusDevice) || \
#                                         ((MODE) == I2C_Mode_SMBusHost))
I2C_Ack_Enable = 0x0
I2C_Ack_Disable = 0x8000
# fun define IS_I2C_ACK(ACK)                 (((ACK) == I2C_Ack_Enable) || \
#                                         ((ACK) == I2C_Ack_Disable))
I2C_AcknowledgedAddress_7bit = 0x0
I2C_AcknowledgedAddress_10bit = 0x400
# fun define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
#                                             ((ADDRESS) == I2C_AcknowledgedAddress_10bit))
# fun define IS_I2C_OWN_ADDRESS1(ADDRESS1)   ((ADDRESS1) <= (uint32_t)0x000003FF)
I2C_Direction_Transmitter = 0x0
I2C_Direction_Receiver = 0x400
# fun define IS_I2C_DIRECTION(DIRECTION)     (((DIRECTION) == I2C_Direction_Transmitter) || \
#                                         ((DIRECTION) == I2C_Direction_Receiver))
I2C_DMAReq_Tx = 0x4000
I2C_DMAReq_Rx = 0x8000
# fun define IS_I2C_DMA_REQ(REQ)             ((((REQ) & (uint32_t)0xFFFF3FFF) == 0x00) && ((REQ) != 0x00))
# fun define IS_I2C_SLAVE_ADDRESS(ADDRESS)   ((ADDRESS) <= (uint16_t)0x03FF)
# fun define IS_I2C_OWN_ADDRESS2(ADDRESS2)   ((ADDRESS2) <= (uint16_t)0x00FF)
I2C_OA2_NoMask = 0x0
I2C_OA2_Mask01 = 0x1
I2C_OA2_Mask02 = 0x2
I2C_OA2_Mask03 = 0x3
I2C_OA2_Mask04 = 0x4
I2C_OA2_Mask05 = 0x5
I2C_OA2_Mask06 = 0x6
I2C_OA2_Mask07 = 0x7
# fun define IS_I2C_OWN_ADDRESS2_MASK(MASK)  (((MASK) == I2C_OA2_NoMask) || \
#                                         ((MASK) == I2C_OA2_Mask01) || \
#                                         ((MASK) == I2C_OA2_Mask02) || \
#                                         ((MASK) == I2C_OA2_Mask03) || \
#                                         ((MASK) == I2C_OA2_Mask04) || \
#                                         ((MASK) == I2C_OA2_Mask05) || \
#                                         ((MASK) == I2C_OA2_Mask06) || \
#                                         ((MASK) == I2C_OA2_Mask07))
# fun define IS_I2C_TIMEOUT(TIMEOUT)   ((TIMEOUT) <= (uint16_t)0x0FFF)
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
# fun define IS_I2C_REGISTER(REGISTER)       (((REGISTER) == I2C_Register_CR1) || \
#                                         ((REGISTER) == I2C_Register_CR2) || \
#                                         ((REGISTER) == I2C_Register_OAR1) || \
#                                         ((REGISTER) == I2C_Register_OAR2) || \
#                                         ((REGISTER) == I2C_Register_TIMINGR) || \
#                                         ((REGISTER) == I2C_Register_TIMEOUTR) || \
#                                         ((REGISTER) == I2C_Register_ISR) || \
#                                         ((REGISTER) == I2C_Register_ICR) || \
#                                         ((REGISTER) == I2C_Register_PECR) || \
#                                         ((REGISTER) == I2C_Register_RXDR) || \
#                                         ((REGISTER) == I2C_Register_TXDR))
I2C_IT_ERRI = 0x80
I2C_IT_TCI = 0x40
I2C_IT_STOPI = 0x20
I2C_IT_NACKI = 0x10
I2C_IT_ADDRI = 0x8
I2C_IT_RXI = 0x4
I2C_IT_TXI = 0x2
# fun define IS_I2C_CONFIG_IT(IT)            ((((IT) & (uint32_t)0xFFFFFF01) == 0x00) && ((IT) != 0x00))
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
# fun define IS_I2C_CLEAR_FLAG(FLAG)         ((((FLAG) & (uint32_t)0xFFFF4000) == 0x00) && ((FLAG) != 0x00))
# fun define IS_I2C_GET_FLAG(FLAG)           (((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_TXIS) || \
#                                         ((FLAG) == I2C_FLAG_RXNE) || ((FLAG) == I2C_FLAG_ADDR) || \
#                                         ((FLAG) == I2C_FLAG_NACKF) || ((FLAG) == I2C_FLAG_STOPF) || \
#                                         ((FLAG) == I2C_FLAG_TC) || ((FLAG) == I2C_FLAG_TCR) || \
#                                         ((FLAG) == I2C_FLAG_BERR) || ((FLAG) == I2C_FLAG_ARLO) || \
#                                         ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_PECERR) || \
#                                         ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_ALERT) || \
#                                         ((FLAG) == I2C_FLAG_BUSY))
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
# fun define IS_I2C_CLEAR_IT(IT)             ((((IT) & (uint32_t)0xFFFFC001) == 0x00) && ((IT) != 0x00))
# fun define IS_I2C_GET_IT(IT)               (((IT) == I2C_IT_TXIS) || ((IT) == I2C_IT_RXNE) || \
#                                         ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_NACKF) || \
#                                         ((IT) == I2C_IT_STOPF) || ((IT) == I2C_IT_TC) || \
#                                         ((IT) == I2C_IT_TCR) || ((IT) == I2C_IT_BERR) || \
#                                         ((IT) == I2C_IT_ARLO) || ((IT) == I2C_IT_OVR) || \
#                                         ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_TIMEOUT) || \
#                                         ((IT) == I2C_IT_ALERT))
I2C_Reload_Mode = 0x1000000
I2C_AutoEnd_Mode = 0x2000000
I2C_SoftEnd_Mode = 0x0
# fun define IS_RELOAD_END_MODE(MODE)        (((MODE) == I2C_Reload_Mode) || \
#                                         ((MODE) == I2C_AutoEnd_Mode) || \
#                                         ((MODE) == I2C_SoftEnd_Mode))
I2C_No_StartStop = 0x0
I2C_Generate_Stop = 0x4000
I2C_Generate_Start_Read = 0x2400
I2C_Generate_Start_Write = 0x2000
# fun define IS_START_STOP_MODE(MODE)        (((MODE) == I2C_Generate_Stop) || \
#                                         ((MODE) == I2C_Generate_Start_Read) || \
#                                         ((MODE) == I2C_Generate_Start_Write) || \
#                                         ((MODE) == I2C_No_StartStop))
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

# file stm32f30x_dma.h : 

# empty define __STM32F30X_DMA_H
# fun define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
#                                   ((PERIPH) == DMA1_Channel2) || \
#                                   ((PERIPH) == DMA1_Channel3) || \
#                                   ((PERIPH) == DMA1_Channel4) || \
#                                   ((PERIPH) == DMA1_Channel5) || \
#                                   ((PERIPH) == DMA1_Channel6) || \
#                                   ((PERIPH) == DMA1_Channel7) || \
#                                   ((PERIPH) == DMA2_Channel1) || \
#                                   ((PERIPH) == DMA2_Channel2) || \
#                                   ((PERIPH) == DMA2_Channel3) || \
#                                   ((PERIPH) == DMA2_Channel4) || \
#                                   ((PERIPH) == DMA2_Channel5))
DMA_DIR_PeripheralSRC = 0x0
DMA_DIR_PeripheralDST = 0x10
# fun define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
#                         ((DIR) == DMA_DIR_PeripheralDST))
DMA_PeripheralInc_Disable = 0x0
DMA_PeripheralInc_Enable = 0x40
# fun define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
#                                            ((STATE) == DMA_PeripheralInc_Enable))
DMA_MemoryInc_Disable = 0x0
DMA_MemoryInc_Enable = 0x80
# fun define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
#                                        ((STATE) == DMA_MemoryInc_Enable))
DMA_PeripheralDataSize_Byte = 0x0
DMA_PeripheralDataSize_HalfWord = 0x100
DMA_PeripheralDataSize_Word = 0x200
# fun define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
#                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
#                                           ((SIZE) == DMA_PeripheralDataSize_Word))
DMA_MemoryDataSize_Byte = 0x0
DMA_MemoryDataSize_HalfWord = 0x400
DMA_MemoryDataSize_Word = 0x800
# fun define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
#                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
#                                       ((SIZE) == DMA_MemoryDataSize_Word))
DMA_Mode_Normal = 0x0
DMA_Mode_Circular = 0x20
# fun define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))
DMA_Priority_VeryHigh = 0x3000
DMA_Priority_High = 0x2000
DMA_Priority_Medium = 0x1000
DMA_Priority_Low = 0x0
# fun define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
#                                   ((PRIORITY) == DMA_Priority_High) || \
#                                   ((PRIORITY) == DMA_Priority_Medium) || \
#                                   ((PRIORITY) == DMA_Priority_Low))
DMA_M2M_Disable = 0x0
DMA_M2M_Enable = 0x4000
# fun define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))
DMA_IT_TC = 0x2
DMA_IT_HT = 0x4
DMA_IT_TE = 0x8
# fun define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))
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
# fun define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00))
# fun define IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || \
#                           ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || \
#                           ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || \
#                           ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || \
#                           ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || \
#                           ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || \
#                           ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || \
#                           ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || \
#                           ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || \
#                           ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || \
#                           ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || \
#                           ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || \
#                           ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || \
#                           ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7) || \
#                           ((IT) == DMA2_IT_GL1) || ((IT) == DMA2_IT_TC1) || \
#                           ((IT) == DMA2_IT_HT1) || ((IT) == DMA2_IT_TE1) || \
#                           ((IT) == DMA2_IT_GL2) || ((IT) == DMA2_IT_TC2) || \
#                           ((IT) == DMA2_IT_HT2) || ((IT) == DMA2_IT_TE2) || \
#                           ((IT) == DMA2_IT_GL3) || ((IT) == DMA2_IT_TC3) || \
#                           ((IT) == DMA2_IT_HT3) || ((IT) == DMA2_IT_TE3) || \
#                           ((IT) == DMA2_IT_GL4) || ((IT) == DMA2_IT_TC4) || \
#                           ((IT) == DMA2_IT_HT4) || ((IT) == DMA2_IT_TE4) || \
#                           ((IT) == DMA2_IT_GL5) || ((IT) == DMA2_IT_TC5) || \
#                           ((IT) == DMA2_IT_HT5) || ((IT) == DMA2_IT_TE5))
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
# fun define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00))
# fun define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || \
#                               ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || \
#                               ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || \
#                               ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || \
#                               ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || \
#                               ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || \
#                               ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || \
#                               ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || \
#                               ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || \
#                               ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || \
#                               ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || \
#                               ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || \
#                               ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || \
#                               ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7) || \
#                               ((FLAG) == DMA2_FLAG_GL1) || ((FLAG) == DMA2_FLAG_TC1) || \
#                               ((FLAG) == DMA2_FLAG_HT1) || ((FLAG) == DMA2_FLAG_TE1) || \
#                               ((FLAG) == DMA2_FLAG_GL2) || ((FLAG) == DMA2_FLAG_TC2) || \
#                               ((FLAG) == DMA2_FLAG_HT2) || ((FLAG) == DMA2_FLAG_TE2) || \
#                               ((FLAG) == DMA2_FLAG_GL3) || ((FLAG) == DMA2_FLAG_TC3) || \
#                               ((FLAG) == DMA2_FLAG_HT3) || ((FLAG) == DMA2_FLAG_TE3) || \
#                               ((FLAG) == DMA2_FLAG_GL4) || ((FLAG) == DMA2_FLAG_TC4) || \
#                               ((FLAG) == DMA2_FLAG_HT4) || ((FLAG) == DMA2_FLAG_TE4) || \
#                               ((FLAG) == DMA2_FLAG_GL5) || ((FLAG) == DMA2_FLAG_TC5) || \
#                               ((FLAG) == DMA2_FLAG_HT5) || ((FLAG) == DMA2_FLAG_TE5))
# struct DMA_InitTypeDef

class DMA_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('DMA_PeripheralBaseAddr',	ctypes.c_uint32),
		('DMA_MemoryBaseAddr',	ctypes.c_uint32),
		('DMA_DIR',	ctypes.c_uint32),
		('DMA_BufferSize',	ctypes.c_uint16),
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

# file stm32f30x_adc.h : 

# empty define __STM32F30x_ADC_H
# fun define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
#                                   ((PERIPH) == ADC2) || \
#                                   ((PERIPH) == ADC3) || \
#                                   ((PERIPH) == ADC4))
# fun define IS_ADC_DMA_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
#                                   ((PERIPH) == ADC2) || \
#                                   ((PERIPH) == ADC3) || \
#                                   ((PERIPH) == ADC4))
ADC_ContinuousConvMode_Enable = 0x2000
ADC_ContinuousConvMode_Disable = 0x0
# fun define IS_ADC_CONVMODE(MODE) (((MODE) == ADC_ContinuousConvMode_Enable) || \
#                               ((MODE) == ADC_ContinuousConvMode_Disable))
ADC_OverrunMode_Enable = 0x1000
ADC_OverrunMode_Disable = 0x0
# fun define IS_ADC_OVRUNMODE(MODE) (((MODE) == ADC_OverrunMode_Enable) || \
#                                ((MODE) == ADC_OverrunMode_Disable))
ADC_AutoInjec_Enable = 0x2000000
ADC_AutoInjec_Disable = 0x0
# fun define IS_ADC_AUTOINJECMODE(MODE) (((MODE) == ADC_AutoInjec_Enable) || \
#                                    ((MODE) == ADC_AutoInjec_Disable))
ADC_Resolution_12b = 0x0
ADC_Resolution_10b = 0x8
ADC_Resolution_8b = 0x10
ADC_Resolution_6b = 0x18
# fun define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
#                                       ((RESOLUTION) == ADC_Resolution_10b) || \
#                                       ((RESOLUTION) == ADC_Resolution_8b) || \
#                                       ((RESOLUTION) == ADC_Resolution_6b))
ADC_ExternalTrigEventEdge_None = 0x0
ADC_ExternalTrigEventEdge_RisingEdge = 0x400
ADC_ExternalTrigEventEdge_FallingEdge = 0x800
ADC_ExternalTrigEventEdge_BothEdge = 0xC00
# fun define IS_EXTERNALTRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigEventEdge_None) || \
#                                    ((EDGE) == ADC_ExternalTrigEventEdge_RisingEdge) || \
#                                    ((EDGE) == ADC_ExternalTrigEventEdge_FallingEdge) || \
#                                    ((EDGE) == ADC_ExternalTrigEventEdge_BothEdge))
ADC_ExternalTrigInjecEventEdge_None = 0x0
ADC_ExternalTrigInjecEventEdge_RisingEdge = 0x40
ADC_ExternalTrigInjecEventEdge_FallingEdge = 0x80
ADC_ExternalTrigInjecEventEdge_BothEdge = 0xC0
# fun define IS_EXTERNALTRIGINJ_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigInjecEventEdge_None) || \
#                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_RisingEdge) || \
#                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_FallingEdge) || \
#                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_BothEdge))
ADC_ExternalTrigConvEvent_0 = 0x0
ADC_ExternalTrigConvEvent_1 = 0x40
ADC_ExternalTrigConvEvent_2 = 0x80
ADC_ExternalTrigConvEvent_3 = 0xC0
ADC_ExternalTrigConvEvent_4 = 0x100
ADC_ExternalTrigConvEvent_5 = 0x140
ADC_ExternalTrigConvEvent_6 = 0x180
ADC_ExternalTrigConvEvent_7 = 0x1C0
ADC_ExternalTrigConvEvent_8 = 0x200
ADC_ExternalTrigConvEvent_9 = 0x240
ADC_ExternalTrigConvEvent_10 = 0x280
ADC_ExternalTrigConvEvent_11 = 0x2C0
ADC_ExternalTrigConvEvent_12 = 0x300
ADC_ExternalTrigConvEvent_13 = 0x340
ADC_ExternalTrigConvEvent_14 = 0x380
ADC_ExternalTrigConvEvent_15 = 0x3C0
# fun define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConvEvent_0) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_1) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_2) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_3) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_4) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_5) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_6) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_7) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_8) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_9) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_10) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_11) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_12) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_13) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_14) || \
#                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_15))
ADC_ExternalTrigInjecConvEvent_0 = 0x0
ADC_ExternalTrigInjecConvEvent_1 = 0x4
ADC_ExternalTrigInjecConvEvent_2 = 0x8
ADC_ExternalTrigInjecConvEvent_3 = 0xC
ADC_ExternalTrigInjecConvEvent_4 = 0x10
ADC_ExternalTrigInjecConvEvent_5 = 0x14
ADC_ExternalTrigInjecConvEvent_6 = 0x18
ADC_ExternalTrigInjecConvEvent_7 = 0x1C
ADC_ExternalTrigInjecConvEvent_8 = 0x20
ADC_ExternalTrigInjecConvEvent_9 = 0x24
ADC_ExternalTrigInjecConvEvent_10 = 0x28
ADC_ExternalTrigInjecConvEvent_11 = 0x2C
ADC_ExternalTrigInjecConvEvent_12 = 0x30
ADC_ExternalTrigInjecConvEvent_13 = 0x34
ADC_ExternalTrigInjecConvEvent_14 = 0x38
ADC_ExternalTrigInjecConvEvent_15 = 0x3C
# fun define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_ExternalTrigInjecConvEvent_0) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_1) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_2) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_3) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_4) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_5) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_6) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_7) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_8) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_9) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_10) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_11) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_12) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_13) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_14) || \
#                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_15))
ADC_DataAlign_Right = 0x0
ADC_DataAlign_Left = 0x20
# fun define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
#                                  ((ALIGN) == ADC_DataAlign_Left))
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
ADC_Channel_Vrefint = 0x12
ADC_Channel_Vbat = 0x11
# fun define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
#                                 ((CHANNEL) == ADC_Channel_2)  || \
#                                 ((CHANNEL) == ADC_Channel_3)  || \
#                                 ((CHANNEL) == ADC_Channel_4)  || \
#                                 ((CHANNEL) == ADC_Channel_5)  || \
#                                 ((CHANNEL) == ADC_Channel_6)  || \
#                                 ((CHANNEL) == ADC_Channel_7)  || \
#                                 ((CHANNEL) == ADC_Channel_8)  || \
#                                 ((CHANNEL) == ADC_Channel_9)  || \
#                                 ((CHANNEL) == ADC_Channel_10) || \
#                                 ((CHANNEL) == ADC_Channel_11) || \
#                                 ((CHANNEL) == ADC_Channel_12) || \
#                                 ((CHANNEL) == ADC_Channel_13) || \
#                                 ((CHANNEL) == ADC_Channel_14) || \
#                                 ((CHANNEL) == ADC_Channel_15) || \
#                                 ((CHANNEL) == ADC_Channel_16) || \
#                                 ((CHANNEL) == ADC_Channel_17) || \
#                                 ((CHANNEL) == ADC_Channel_18))
# fun define IS_ADC_DIFFCHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
#                                     ((CHANNEL) == ADC_Channel_2)  || \
#                                     ((CHANNEL) == ADC_Channel_3)  || \
#                                     ((CHANNEL) == ADC_Channel_4)  || \
#                                     ((CHANNEL) == ADC_Channel_5)  || \
#                                     ((CHANNEL) == ADC_Channel_6)  || \
#                                     ((CHANNEL) == ADC_Channel_7)  || \
#                                     ((CHANNEL) == ADC_Channel_8)  || \
#                                     ((CHANNEL) == ADC_Channel_9)  || \
#                                     ((CHANNEL) == ADC_Channel_10) || \
#                                     ((CHANNEL) == ADC_Channel_11) || \
#                                     ((CHANNEL) == ADC_Channel_12) || \
#                                     ((CHANNEL) == ADC_Channel_13) || \
#                                     ((CHANNEL) == ADC_Channel_14))
ADC_Mode_Independent = 0x0
ADC_Mode_CombRegSimulInjSimul = 0x1
ADC_Mode_CombRegSimulAltTrig = 0x2
ADC_Mode_InjSimul = 0x5
ADC_Mode_RegSimul = 0x6
ADC_Mode_Interleave = 0x7
ADC_Mode_AltTrig = 0x9
# fun define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) || \
#                           ((MODE) == ADC_Mode_CombRegSimulInjSimul) || \
#                           ((MODE) == ADC_Mode_CombRegSimulAltTrig) || \
#                           ((MODE) == ADC_Mode_InjSimul) || \
#                           ((MODE) == ADC_Mode_RegSimul) || \
#                           ((MODE) == ADC_Mode_Interleave) || \
#                           ((MODE) == ADC_Mode_AltTrig))
ADC_Clock_AsynClkMode = 0x0
ADC_Clock_SynClkModeDiv1 = 0x10000
ADC_Clock_SynClkModeDiv2 = 0x20000
ADC_Clock_SynClkModeDiv4 = 0x30000
# fun define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_Clock_AsynClkMode) ||\
#				((CLOCK) == ADC_Clock_SynClkModeDiv1) ||\
#				((CLOCK) == ADC_Clock_SynClkModeDiv2)||\
#				((CLOCK) == ADC_Clock_SynClkModeDiv4))
ADC_DMAAccessMode_Disabled = 0x0
ADC_DMAAccessMode_1 = 0x8000
ADC_DMAAccessMode_2 = 0xC000
# fun define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAAccessMode_Disabled) || \
#                                      ((MODE) == ADC_DMAAccessMode_1) || \
#                                      ((MODE) == ADC_DMAAccessMode_2))
ADC_SampleTime_1Cycles5 = 0x0
ADC_SampleTime_2Cycles5 = 0x1
ADC_SampleTime_4Cycles5 = 0x2
ADC_SampleTime_7Cycles5 = 0x3
ADC_SampleTime_19Cycles5 = 0x4
ADC_SampleTime_61Cycles5 = 0x5
ADC_SampleTime_181Cycles5 = 0x6
ADC_SampleTime_601Cycles5 = 0x7
# fun define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_2Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_4Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_7Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_19Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_61Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_181Cycles5) || \
#                                  ((TIME) == ADC_SampleTime_601Cycles5))
ADC_InjectedChannel_1 = 0x1
ADC_InjectedChannel_2 = 0x2
ADC_InjectedChannel_3 = 0x3
ADC_InjectedChannel_4 = 0x4
# fun define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
#                                          ((CHANNEL) == ADC_InjectedChannel_2) || \
#                                          ((CHANNEL) == ADC_InjectedChannel_3) || \
#                                          ((CHANNEL) == ADC_InjectedChannel_4))
ADC_AnalogWatchdog_SingleRegEnable = 0xC00000
ADC_AnalogWatchdog_SingleInjecEnable = 0x1400000
ADC_AnalogWatchdog_SingleRegOrInjecEnable = 0x1C00000
ADC_AnalogWatchdog_AllRegEnable = 0x800000
ADC_AnalogWatchdog_AllInjecEnable = 0x1000000
ADC_AnalogWatchdog_AllRegAllInjecEnable = 0x1800000
ADC_AnalogWatchdog_None = 0x0
# fun define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
#                                          ((WATCHDOG) == ADC_AnalogWatchdog_None))
ADC_CalibrationMode_Single = 0x0
ADC_CalibrationMode_Differential = 0x40000000
# fun define IS_ADC_CALIBRATION_MODE(MODE) (((MODE) == ADC_CalibrationMode_Single) ||((MODE) == ADC_CalibrationMode_Differential))
ADC_DMAMode_OneShot = 0x0
ADC_DMAMode_Circular = 0x2
# fun define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || ((MODE) == ADC_DMAMode_Circular))
ADC_IT_RDY = 0x1
ADC_IT_EOSMP = 0x2
ADC_IT_EOC = 0x4
ADC_IT_EOS = 0x8
ADC_IT_OVR = 0x10
ADC_IT_JEOC = 0x20
ADC_IT_JEOS = 0x40
ADC_IT_AWD1 = 0x80
ADC_IT_AWD2 = 0x100
ADC_IT_AWD3 = 0x200
ADC_IT_JQOVF = 0x400
# fun define IS_ADC_IT(IT) ((((IT) & (uint16_t)0xF800) == 0x0000) && ((IT) != 0x0000))
# fun define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_RDY) || ((IT) == ADC_IT_EOSMP) || \
#                           ((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_EOS) || \
#                           ((IT) == ADC_IT_OVR) || ((IT) == ADC_IT_EOS) || \
#                           ((IT) == ADC_IT_JEOS) || ((IT) == ADC_IT_AWD1) || \
#                           ((IT) == ADC_IT_AWD2) || ((IT) == ADC_IT_AWD3) || \
#                           ((IT) == ADC_IT_JQOVF))
ADC_FLAG_RDY = 0x1
ADC_FLAG_EOSMP = 0x2
ADC_FLAG_EOC = 0x4
ADC_FLAG_EOS = 0x8
ADC_FLAG_OVR = 0x10
ADC_FLAG_JEOC = 0x20
ADC_FLAG_JEOS = 0x40
ADC_FLAG_AWD1 = 0x80
ADC_FLAG_AWD2 = 0x100
ADC_FLAG_AWD3 = 0x200
ADC_FLAG_JQOVF = 0x400
# fun define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xF800) == 0x0000) && ((FLAG) != 0x0000))
# fun define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_RDY) || ((FLAG) == ADC_FLAG_EOSMP) || \
#                               ((FLAG) == ADC_FLAG_EOC) || ((FLAG) == ADC_FLAG_EOS) || \
#                               ((FLAG) == ADC_FLAG_OVR) || ((FLAG) == ADC_FLAG_JEOC) || \
#                               ((FLAG) == ADC_FLAG_JEOS) || ((FLAG) == ADC_FLAG_AWD1) || \
#                               ((FLAG) == ADC_FLAG_AWD2) || ((FLAG) == ADC_FLAG_AWD3) || \
#                               ((FLAG) == ADC_FLAG_JQOVF))
ADC_FLAG_MSTRDY = 0x1
ADC_FLAG_MSTEOSMP = 0x2
ADC_FLAG_MSTEOC = 0x4
ADC_FLAG_MSTEOS = 0x8
ADC_FLAG_MSTOVR = 0x10
ADC_FLAG_MSTJEOC = 0x20
ADC_FLAG_MSTJEOS = 0x40
ADC_FLAG_MSTAWD1 = 0x80
ADC_FLAG_MSTAWD2 = 0x100
ADC_FLAG_MSTAWD3 = 0x200
ADC_FLAG_MSTJQOVF = 0x400
ADC_FLAG_SLVRDY = 0x10000
ADC_FLAG_SLVEOSMP = 0x20000
ADC_FLAG_SLVEOC = 0x40000
ADC_FLAG_SLVEOS = 0x80000
ADC_FLAG_SLVOVR = 0x100000
ADC_FLAG_SLVJEOC = 0x200000
ADC_FLAG_SLVJEOS = 0x400000
ADC_FLAG_SLVAWD1 = 0x800000
ADC_FLAG_SLVAWD2 = 0x1000000
ADC_FLAG_SLVAWD3 = 0x2000000
ADC_FLAG_SLVJQOVF = 0x4000000
# fun define IS_ADC_CLEAR_COMMONFLAG(FLAG) ((((FLAG) & (uint32_t)0xF800F800) == 0x0000) && ((FLAG) != 0x00000000))
# fun define IS_ADC_GET_COMMONFLAG(FLAG) (((FLAG) == ADC_FLAG_MSTRDY) || ((FLAG) == ADC_FLAG_MSTEOSMP) || \
#                                     ((FLAG) == ADC_FLAG_MSTEOC) || ((FLAG) == ADC_FLAG_MSTEOS) || \
#                                     ((FLAG) == ADC_FLAG_MSTOVR) || ((FLAG) == ADC_FLAG_MSTEOS) || \
#                                     ((FLAG) == ADC_FLAG_MSTJEOS) || ((FLAG) == ADC_FLAG_MSTAWD1) || \
#                                     ((FLAG) == ADC_FLAG_MSTAWD2) || ((FLAG) == ADC_FLAG_MSTAWD3) || \
#                                     ((FLAG) == ADC_FLAG_MSTJQOVF) || \
#                                     ((FLAG) == ADC_FLAG_SLVRDY) || ((FLAG) == ADC_FLAG_SLVEOSMP) || \
#                                     ((FLAG) == ADC_FLAG_SLVEOC) || ((FLAG) == ADC_FLAG_SLVEOS) || \
#                                     ((FLAG) == ADC_FLAG_SLVOVR) || ((FLAG) == ADC_FLAG_SLVEOS) || \
#                                     ((FLAG) == ADC_FLAG_SLVJEOS) || ((FLAG) == ADC_FLAG_SLVAWD1) || \
#                                     ((FLAG) == ADC_FLAG_SLVAWD2) || ((FLAG) == ADC_FLAG_SLVAWD3) || \
#                                     ((FLAG) == ADC_FLAG_SLVJQOVF))
# fun define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)
# fun define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)
# fun define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))
# fun define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
# fun define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))
# fun define IS_ADC_TWOSAMPLING_DELAY(DELAY)	(((DELAY) <= 0xF))
# struct ADC_InitTypeDef

class ADC_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_ContinuousConvMode',	ctypes.c_uint32),
		('ADC_Resolution',	ctypes.c_uint32),
		('ADC_ExternalTrigConvEvent',	ctypes.c_uint32),
		('ADC_ExternalTrigEventEdge',	ctypes.c_uint32),
		('ADC_DataAlign',	ctypes.c_uint32),
		('ADC_OverrunMode',	ctypes.c_uint32),
		('ADC_AutoInjMode',	ctypes.c_uint32),
		('ADC_NbrOfRegChannel',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ADC_InjectedInitTypeDef

class ADC_InjectedInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_ExternalTrigInjecConvEvent',	ctypes.c_uint32),
		('ADC_ExternalTrigInjecEventEdge',	ctypes.c_uint32),
		('ADC_NbrOfInjecChannel',	ctypes.c_uint8),
		('ADC_InjecSequence1',	ctypes.c_uint32),
		('ADC_InjecSequence2',	ctypes.c_uint32),
		('ADC_InjecSequence3',	ctypes.c_uint32),
		('ADC_InjecSequence4',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ADC_CommonInitTypeDef

class ADC_CommonInitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ADC_Mode',	ctypes.c_uint32),
		('ADC_Clock',	ctypes.c_uint32),
		('ADC_DMAAccessMode',	ctypes.c_uint32),
		('ADC_DMAMode',	ctypes.c_uint32),
		('ADC_TwoSamplingDelay',	ctypes.c_uint8),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f30x_wwdg.h : 

# empty define __STM32F30X_WWDG_H
WWDG_Prescaler_1 = 0x0
WWDG_Prescaler_2 = 0x80
WWDG_Prescaler_4 = 0x100
WWDG_Prescaler_8 = 0x180
# fun define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
#                                      ((PRESCALER) == WWDG_Prescaler_2) || \
#                                      ((PRESCALER) == WWDG_Prescaler_4) || \
#                                      ((PRESCALER) == WWDG_Prescaler_8))
# fun define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
# fun define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))
# ----------------------------------------

# file stm32f30x_opamp.h : 

# empty define __STM32F30x_OPAMP_H
OPAMP_Selection_OPAMP1 = 0x0
OPAMP_Selection_OPAMP2 = 0x4
OPAMP_Selection_OPAMP3 = 0x8
OPAMP_Selection_OPAMP4 = 0xC
# fun define IS_OPAMP_ALL_PERIPH(PERIPH) (((PERIPH) == OPAMP_Selection_OPAMP1) || \
#                                     ((PERIPH) == OPAMP_Selection_OPAMP2) || \
#                                     ((PERIPH) == OPAMP_Selection_OPAMP3) || \
#                                     ((PERIPH) == OPAMP_Selection_OPAMP4))
OPAMP_InvertingInput_IO1 = 0x0
OPAMP_InvertingInput_IO2 = 0x20
OPAMP_InvertingInput_PGA = 0x40
OPAMP_InvertingInput_Vout = 0x60
# fun define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_InvertingInput_IO1) || \
#                                         ((INPUT) == OPAMP_InvertingInput_IO2) || \
#                                         ((INPUT) == OPAMP_InvertingInput_PGA) || \
#                                         ((INPUT) == OPAMP_InvertingInput_Vout))
OPAMP_NonInvertingInput_IO1 = 0x0
OPAMP_NonInvertingInput_IO2 = 0x4
OPAMP_NonInvertingInput_IO3 = 0x8
OPAMP_NonInvertingInput_IO4 = 0xC
# fun define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NonInvertingInput_IO1) || \
#                                            ((INPUT) == OPAMP_NonInvertingInput_IO2) || \
#                                            ((INPUT) == OPAMP_NonInvertingInput_IO3) || \
#                                            ((INPUT) == OPAMP_NonInvertingInput_IO4))
OPAMP_OPAMP_PGAGain_2 = 0x0
OPAMP_OPAMP_PGAGain_4 = 0x4000
OPAMP_OPAMP_PGAGain_8 = 0x8000
OPAMP_OPAMP_PGAGain_16 = 0xC000
# fun define IS_OPAMP_PGAGAIN(GAIN) (((GAIN) == OPAMP_OPAMP_PGAGain_2) || \
#                                ((GAIN) == OPAMP_OPAMP_PGAGain_4) || \
#                                ((GAIN) == OPAMP_OPAMP_PGAGain_8) || \
#                                ((GAIN) == OPAMP_OPAMP_PGAGain_16))
OPAMP_PGAConnect_No = 0x0
OPAMP_PGAConnect_IO1 = 0x20000
OPAMP_PGAConnect_IO2 = 0x30000
# fun define IS_OPAMP_PGACONNECT(CONNECT) (((CONNECT) == OPAMP_PGAConnect_No)  || \
#                                      ((CONNECT) == OPAMP_PGAConnect_IO1) || \
#                                      ((CONNECT) == OPAMP_PGAConnect_IO2))
# fun define IS_OPAMP_SECONDARY_INVINPUT(INVINPUT) (((INVINPUT) == OPAMP_InvertingInput_IO1) || \
#                                               ((INVINPUT) == OPAMP_InvertingInput_IO2))
OPAMP_Input_Inverting = 0x18
OPAMP_Input_NonInverting = 0x13
# fun define IS_OPAMP_INPUT(INPUT) (((INPUT) == OPAMP_Input_Inverting) || \
#                               ((INPUT) == OPAMP_Input_NonInverting))
OPAMP_Vref_3VDDA = 0x0
OPAMP_Vref_10VDDA = 0x1000
OPAMP_Vref_50VDDA = 0x2000
OPAMP_Vref_90VDDA = 0x3000
# fun define IS_OPAMP_VREF(VREF) (((VREF) == OPAMP_Vref_3VDDA)  || \
#                             ((VREF) == OPAMP_Vref_10VDDA) || \
#                             ((VREF) == OPAMP_Vref_50VDDA) || \
#                             ((VREF) == OPAMP_Vref_90VDDA))
OPAMP_Trimming_Factory = 0x0
OPAMP_Trimming_User = 0x40000
# fun define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_Trimming_Factory) || \
#                                     ((TRIMMING) == OPAMP_Trimming_User))
# fun define IS_OPAMP_TRIMMINGVALUE(VALUE) ((VALUE) <= 0x0000001F) /*!< Trimming value */
OPAMP_OutputLevel_High = 0x40000000
OPAMP_OutputLevel_Low = 0x0
# struct OPAMP_InitTypeDef

class OPAMP_InitTypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('OPAMP_InvertingInput',	ctypes.c_uint32),
		('OPAMP_NonInvertingInput',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f30x_can.h : 

# empty define __STM32F30x_CAN_H
# fun define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN1))
CAN_InitStatus_Failed = 0x0
CAN_InitStatus_Success = 0x1
CANINITFAILED = 0x0
CANINITOK = 0x1
CAN_Mode_Normal = 0x0
CAN_Mode_LoopBack = 0x1
CAN_Mode_Silent = 0x2
CAN_Mode_Silent_LoopBack = 0x3
# fun define IS_CAN_MODE(MODE) (((MODE) == CAN_Mode_Normal) || \
#                           ((MODE) == CAN_Mode_LoopBack)|| \
#                           ((MODE) == CAN_Mode_Silent) || \
#                           ((MODE) == CAN_Mode_Silent_LoopBack))
CAN_OperatingMode_Initialization = 0x0
CAN_OperatingMode_Normal = 0x1
CAN_OperatingMode_Sleep = 0x2
# fun define IS_CAN_OPERATING_MODE(MODE) (((MODE) == CAN_OperatingMode_Initialization) ||\
#                                    ((MODE) == CAN_OperatingMode_Normal)|| \
#																		((MODE) == CAN_OperatingMode_Sleep))
CAN_ModeStatus_Failed = 0x0
CAN_ModeStatus_Success = 0x1
CAN_SJW_1tq = 0x0
CAN_SJW_2tq = 0x1
CAN_SJW_3tq = 0x2
CAN_SJW_4tq = 0x3
# fun define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq)|| \
#                         ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq))
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
# fun define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)
CAN_BS2_1tq = 0x0
CAN_BS2_2tq = 0x1
CAN_BS2_3tq = 0x2
CAN_BS2_4tq = 0x3
CAN_BS2_5tq = 0x4
CAN_BS2_6tq = 0x5
CAN_BS2_7tq = 0x6
CAN_BS2_8tq = 0x7
# fun define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)
# fun define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1) && ((PRESCALER) <= 1024))
# fun define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)
CAN_FilterMode_IdMask = 0x0
CAN_FilterMode_IdList = 0x1
# fun define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FilterMode_IdMask) || \
#                                  ((MODE) == CAN_FilterMode_IdList))
CAN_FilterScale_16bit = 0x0
CAN_FilterScale_32bit = 0x1
# fun define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FilterScale_16bit) || \
#                                    ((SCALE) == CAN_FilterScale_32bit))
CAN_Filter_FIFO0 = 0x0
CAN_Filter_FIFO1 = 0x1
# fun define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FilterFIFO0) || \
#                                  ((FIFO) == CAN_FilterFIFO1))
CAN_FilterFIFO0 = 0x0
CAN_FilterFIFO1 = 0x1
# fun define IS_CAN_BANKNUMBER(BANKNUMBER) (((BANKNUMBER) >= 1) && ((BANKNUMBER) <= 27))
# fun define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((uint8_t)0x02))
# fun define IS_CAN_STDID(STDID)   ((STDID) <= ((uint32_t)0x7FF))
# fun define IS_CAN_EXTID(EXTID)   ((EXTID) <= ((uint32_t)0x1FFFFFFF))
# fun define IS_CAN_DLC(DLC)       ((DLC) <= ((uint8_t)0x08))
CAN_Id_Standard = 0x0
CAN_Id_Extended = 0x4
# fun define IS_CAN_IDTYPE(IDTYPE) (((IDTYPE) == CAN_Id_Standard) || \
#                               ((IDTYPE) == CAN_Id_Extended))
CAN_ID_STD = 0x0
CAN_ID_EXT = 0x4
CAN_RTR_Data = 0x0
CAN_RTR_Remote = 0x2
# fun define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_Data) || ((RTR) == CAN_RTR_Remote))
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
# fun define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))
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
# fun define IS_CAN_GET_FLAG(FLAG) (((FLAG) == CAN_FLAG_LEC)  || ((FLAG) == CAN_FLAG_BOF)   || \
#                               ((FLAG) == CAN_FLAG_EPV)  || ((FLAG) == CAN_FLAG_EWG)   || \
#                               ((FLAG) == CAN_FLAG_WKU)  || ((FLAG) == CAN_FLAG_FOV0)  || \
#                               ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FMP0)  || \
#                               ((FLAG) == CAN_FLAG_FOV1) || ((FLAG) == CAN_FLAG_FF1)   || \
#                               ((FLAG) == CAN_FLAG_FMP1) || ((FLAG) == CAN_FLAG_RQCP2) || \
#                               ((FLAG) == CAN_FLAG_RQCP1)|| ((FLAG) == CAN_FLAG_RQCP0) || \
#                               ((FLAG) == CAN_FLAG_SLAK ))
# fun define IS_CAN_CLEAR_FLAG(FLAG)(((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_RQCP2) || \
#                                ((FLAG) == CAN_FLAG_RQCP1)  || ((FLAG) == CAN_FLAG_RQCP0) || \
#                                ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FOV0) ||\
#                                ((FLAG) == CAN_FLAG_FF1) || ((FLAG) == CAN_FLAG_FOV1) || \
#                                ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_SLAK))
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
# fun define IS_CAN_IT(IT)        (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FMP0)  ||\
#                             ((IT) == CAN_IT_FF0)  || ((IT) == CAN_IT_FOV0)  ||\
#                             ((IT) == CAN_IT_FMP1) || ((IT) == CAN_IT_FF1)   ||\
#                             ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG)   ||\
#                             ((IT) == CAN_IT_EPV)  || ((IT) == CAN_IT_BOF)   ||\
#                             ((IT) == CAN_IT_LEC)  || ((IT) == CAN_IT_ERR)   ||\
#                             ((IT) == CAN_IT_WKU)  || ((IT) == CAN_IT_SLK))
# fun define IS_CAN_CLEAR_IT(IT) (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FF0)    ||\
#                             ((IT) == CAN_IT_FOV0)|| ((IT) == CAN_IT_FF1)    ||\
#                             ((IT) == CAN_IT_FOV1)|| ((IT) == CAN_IT_EWG)    ||\
#                             ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF)    ||\
#                             ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR)    ||\
#                             ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK))
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

# file core_cm4.h : 

# empty define __CORE_CM4_H_GENERIC
__CM4_CMSIS_VERSION_MAIN = 0x3
__CM4_CMSIS_VERSION_SUB = 0x0
__CM4_CMSIS_VERSION = 0x30000
__CORTEX_M = 0x4
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __ASM : no need parse
# Skip __INLINE : no need parse
# Skip __STATIC_INLINE : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# Skip __FPU_USED : no need parse
# empty define __CORE_CM4_H_DEPENDANT
# Skip __CM4_REV : no need parse
# Skip __FPU_PRESENT : no need parse
# Skip __MPU_PRESENT : no need parse
# Skip __NVIC_PRIO_BITS : no need parse
# Skip __Vendor_SysTickConfig : no need parse
# Skip __I : no need parse
# Skip __I : no need parse
# Skip __O : no need parse
# Skip __IO : no need parse
# Skip NVIC_STIR_INTID_Pos : no need parse
# Skip NVIC_STIR_INTID_Msk : no need parse
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
# Skip SCB_ICSR_RETTOBASE_Pos : no need parse
# Skip SCB_ICSR_RETTOBASE_Msk : no need parse
# Skip SCB_ICSR_VECTACTIVE_Pos : no need parse
# Skip SCB_ICSR_VECTACTIVE_Msk : no need parse
# Skip SCB_VTOR_TBLOFF_Pos : no need parse
# Skip SCB_VTOR_TBLOFF_Msk : no need parse
# Skip SCB_AIRCR_VECTKEY_Pos : no need parse
# Skip SCB_AIRCR_VECTKEY_Msk : no need parse
# Skip SCB_AIRCR_VECTKEYSTAT_Pos : no need parse
# Skip SCB_AIRCR_VECTKEYSTAT_Msk : no need parse
# Skip SCB_AIRCR_ENDIANESS_Pos : no need parse
# Skip SCB_AIRCR_ENDIANESS_Msk : no need parse
# Skip SCB_AIRCR_PRIGROUP_Pos : no need parse
# Skip SCB_AIRCR_PRIGROUP_Msk : no need parse
# Skip SCB_AIRCR_SYSRESETREQ_Pos : no need parse
# Skip SCB_AIRCR_SYSRESETREQ_Msk : no need parse
# Skip SCB_AIRCR_VECTCLRACTIVE_Pos : no need parse
# Skip SCB_AIRCR_VECTCLRACTIVE_Msk : no need parse
# Skip SCB_AIRCR_VECTRESET_Pos : no need parse
# Skip SCB_AIRCR_VECTRESET_Msk : no need parse
# Skip SCB_SCR_SEVONPEND_Pos : no need parse
# Skip SCB_SCR_SEVONPEND_Msk : no need parse
# Skip SCB_SCR_SLEEPDEEP_Pos : no need parse
# Skip SCB_SCR_SLEEPDEEP_Msk : no need parse
# Skip SCB_SCR_SLEEPONEXIT_Pos : no need parse
# Skip SCB_SCR_SLEEPONEXIT_Msk : no need parse
# Skip SCB_CCR_STKALIGN_Pos : no need parse
# Skip SCB_CCR_STKALIGN_Msk : no need parse
# Skip SCB_CCR_BFHFNMIGN_Pos : no need parse
# Skip SCB_CCR_BFHFNMIGN_Msk : no need parse
# Skip SCB_CCR_DIV_0_TRP_Pos : no need parse
# Skip SCB_CCR_DIV_0_TRP_Msk : no need parse
# Skip SCB_CCR_UNALIGN_TRP_Pos : no need parse
# Skip SCB_CCR_UNALIGN_TRP_Msk : no need parse
# Skip SCB_CCR_USERSETMPEND_Pos : no need parse
# Skip SCB_CCR_USERSETMPEND_Msk : no need parse
# Skip SCB_CCR_NONBASETHRDENA_Pos : no need parse
# Skip SCB_CCR_NONBASETHRDENA_Msk : no need parse
# Skip SCB_SHCSR_USGFAULTENA_Pos : no need parse
# Skip SCB_SHCSR_USGFAULTENA_Msk : no need parse
# Skip SCB_SHCSR_BUSFAULTENA_Pos : no need parse
# Skip SCB_SHCSR_BUSFAULTENA_Msk : no need parse
# Skip SCB_SHCSR_MEMFAULTENA_Pos : no need parse
# Skip SCB_SHCSR_MEMFAULTENA_Msk : no need parse
# Skip SCB_SHCSR_SVCALLPENDED_Pos : no need parse
# Skip SCB_SHCSR_SVCALLPENDED_Msk : no need parse
# Skip SCB_SHCSR_BUSFAULTPENDED_Pos : no need parse
# Skip SCB_SHCSR_BUSFAULTPENDED_Msk : no need parse
# Skip SCB_SHCSR_MEMFAULTPENDED_Pos : no need parse
# Skip SCB_SHCSR_MEMFAULTPENDED_Msk : no need parse
# Skip SCB_SHCSR_USGFAULTPENDED_Pos : no need parse
# Skip SCB_SHCSR_USGFAULTPENDED_Msk : no need parse
# Skip SCB_SHCSR_SYSTICKACT_Pos : no need parse
# Skip SCB_SHCSR_SYSTICKACT_Msk : no need parse
# Skip SCB_SHCSR_PENDSVACT_Pos : no need parse
# Skip SCB_SHCSR_PENDSVACT_Msk : no need parse
# Skip SCB_SHCSR_MONITORACT_Pos : no need parse
# Skip SCB_SHCSR_MONITORACT_Msk : no need parse
# Skip SCB_SHCSR_SVCALLACT_Pos : no need parse
# Skip SCB_SHCSR_SVCALLACT_Msk : no need parse
# Skip SCB_SHCSR_USGFAULTACT_Pos : no need parse
# Skip SCB_SHCSR_USGFAULTACT_Msk : no need parse
# Skip SCB_SHCSR_BUSFAULTACT_Pos : no need parse
# Skip SCB_SHCSR_BUSFAULTACT_Msk : no need parse
# Skip SCB_SHCSR_MEMFAULTACT_Pos : no need parse
# Skip SCB_SHCSR_MEMFAULTACT_Msk : no need parse
# Skip SCB_CFSR_USGFAULTSR_Pos : no need parse
# Skip SCB_CFSR_USGFAULTSR_Msk : no need parse
# Skip SCB_CFSR_BUSFAULTSR_Pos : no need parse
# Skip SCB_CFSR_BUSFAULTSR_Msk : no need parse
# Skip SCB_CFSR_MEMFAULTSR_Pos : no need parse
# Skip SCB_CFSR_MEMFAULTSR_Msk : no need parse
# Skip SCB_HFSR_DEBUGEVT_Pos : no need parse
# Skip SCB_HFSR_DEBUGEVT_Msk : no need parse
# Skip SCB_HFSR_FORCED_Pos : no need parse
# Skip SCB_HFSR_FORCED_Msk : no need parse
# Skip SCB_HFSR_VECTTBL_Pos : no need parse
# Skip SCB_HFSR_VECTTBL_Msk : no need parse
# Skip SCB_DFSR_EXTERNAL_Pos : no need parse
# Skip SCB_DFSR_EXTERNAL_Msk : no need parse
# Skip SCB_DFSR_VCATCH_Pos : no need parse
# Skip SCB_DFSR_VCATCH_Msk : no need parse
# Skip SCB_DFSR_DWTTRAP_Pos : no need parse
# Skip SCB_DFSR_DWTTRAP_Msk : no need parse
# Skip SCB_DFSR_BKPT_Pos : no need parse
# Skip SCB_DFSR_BKPT_Msk : no need parse
# Skip SCB_DFSR_HALTED_Pos : no need parse
# Skip SCB_DFSR_HALTED_Msk : no need parse
# Skip SCnSCB_ICTR_INTLINESNUM_Pos : no need parse
# Skip SCnSCB_ICTR_INTLINESNUM_Msk : no need parse
# Skip SCnSCB_ACTLR_DISOOFP_Pos : no need parse
# Skip SCnSCB_ACTLR_DISOOFP_Msk : no need parse
# Skip SCnSCB_ACTLR_DISFPCA_Pos : no need parse
# Skip SCnSCB_ACTLR_DISFPCA_Msk : no need parse
# Skip SCnSCB_ACTLR_DISFOLD_Pos : no need parse
# Skip SCnSCB_ACTLR_DISFOLD_Msk : no need parse
# Skip SCnSCB_ACTLR_DISDEFWBUF_Pos : no need parse
# Skip SCnSCB_ACTLR_DISDEFWBUF_Msk : no need parse
# Skip SCnSCB_ACTLR_DISMCYCINT_Pos : no need parse
# Skip SCnSCB_ACTLR_DISMCYCINT_Msk : no need parse
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
# Skip ITM_TPR_PRIVMASK_Pos : no need parse
# Skip ITM_TPR_PRIVMASK_Msk : no need parse
# Skip ITM_TCR_BUSY_Pos : no need parse
# Skip ITM_TCR_BUSY_Msk : no need parse
# Skip ITM_TCR_TraceBusID_Pos : no need parse
# Skip ITM_TCR_TraceBusID_Msk : no need parse
# Skip ITM_TCR_GTSFREQ_Pos : no need parse
# Skip ITM_TCR_GTSFREQ_Msk : no need parse
# Skip ITM_TCR_TSPrescale_Pos : no need parse
# Skip ITM_TCR_TSPrescale_Msk : no need parse
# Skip ITM_TCR_SWOENA_Pos : no need parse
# Skip ITM_TCR_SWOENA_Msk : no need parse
# Skip ITM_TCR_TXENA_Pos : no need parse
# Skip ITM_TCR_TXENA_Msk : no need parse
# Skip ITM_TCR_SYNCENA_Pos : no need parse
# Skip ITM_TCR_SYNCENA_Msk : no need parse
# Skip ITM_TCR_TSENA_Pos : no need parse
# Skip ITM_TCR_TSENA_Msk : no need parse
# Skip ITM_TCR_ITMENA_Pos : no need parse
# Skip ITM_TCR_ITMENA_Msk : no need parse
# Skip DWT_CTRL_NUMCOMP_Pos : no need parse
# Skip DWT_CTRL_NUMCOMP_Msk : no need parse
# Skip DWT_CTRL_NOTRCPKT_Pos : no need parse
# Skip DWT_CTRL_NOTRCPKT_Msk : no need parse
# Skip DWT_CTRL_NOEXTTRIG_Pos : no need parse
# Skip DWT_CTRL_NOEXTTRIG_Msk : no need parse
# Skip DWT_CTRL_NOCYCCNT_Pos : no need parse
# Skip DWT_CTRL_NOCYCCNT_Msk : no need parse
# Skip DWT_CTRL_NOPRFCNT_Pos : no need parse
# Skip DWT_CTRL_NOPRFCNT_Msk : no need parse
# Skip DWT_CTRL_CYCEVTENA_Pos : no need parse
# Skip DWT_CTRL_CYCEVTENA_Msk : no need parse
# Skip DWT_CTRL_FOLDEVTENA_Pos : no need parse
# Skip DWT_CTRL_FOLDEVTENA_Msk : no need parse
# Skip DWT_CTRL_LSUEVTENA_Pos : no need parse
# Skip DWT_CTRL_LSUEVTENA_Msk : no need parse
# Skip DWT_CTRL_SLEEPEVTENA_Pos : no need parse
# Skip DWT_CTRL_SLEEPEVTENA_Msk : no need parse
# Skip DWT_CTRL_EXCEVTENA_Pos : no need parse
# Skip DWT_CTRL_EXCEVTENA_Msk : no need parse
# Skip DWT_CTRL_CPIEVTENA_Pos : no need parse
# Skip DWT_CTRL_CPIEVTENA_Msk : no need parse
# Skip DWT_CTRL_EXCTRCENA_Pos : no need parse
# Skip DWT_CTRL_EXCTRCENA_Msk : no need parse
# Skip DWT_CTRL_PCSAMPLENA_Pos : no need parse
# Skip DWT_CTRL_PCSAMPLENA_Msk : no need parse
# Skip DWT_CTRL_SYNCTAP_Pos : no need parse
# Skip DWT_CTRL_SYNCTAP_Msk : no need parse
# Skip DWT_CTRL_CYCTAP_Pos : no need parse
# Skip DWT_CTRL_CYCTAP_Msk : no need parse
# Skip DWT_CTRL_POSTINIT_Pos : no need parse
# Skip DWT_CTRL_POSTINIT_Msk : no need parse
# Skip DWT_CTRL_POSTPRESET_Pos : no need parse
# Skip DWT_CTRL_POSTPRESET_Msk : no need parse
# Skip DWT_CTRL_CYCCNTENA_Pos : no need parse
# Skip DWT_CTRL_CYCCNTENA_Msk : no need parse
# Skip DWT_CPICNT_CPICNT_Pos : no need parse
# Skip DWT_CPICNT_CPICNT_Msk : no need parse
# Skip DWT_EXCCNT_EXCCNT_Pos : no need parse
# Skip DWT_EXCCNT_EXCCNT_Msk : no need parse
# Skip DWT_SLEEPCNT_SLEEPCNT_Pos : no need parse
# Skip DWT_SLEEPCNT_SLEEPCNT_Msk : no need parse
# Skip DWT_LSUCNT_LSUCNT_Pos : no need parse
# Skip DWT_LSUCNT_LSUCNT_Msk : no need parse
# Skip DWT_FOLDCNT_FOLDCNT_Pos : no need parse
# Skip DWT_FOLDCNT_FOLDCNT_Msk : no need parse
# Skip DWT_MASK_MASK_Pos : no need parse
# Skip DWT_MASK_MASK_Msk : no need parse
# Skip DWT_FUNCTION_MATCHED_Pos : no need parse
# Skip DWT_FUNCTION_MATCHED_Msk : no need parse
# Skip DWT_FUNCTION_DATAVADDR1_Pos : no need parse
# Skip DWT_FUNCTION_DATAVADDR1_Msk : no need parse
# Skip DWT_FUNCTION_DATAVADDR0_Pos : no need parse
# Skip DWT_FUNCTION_DATAVADDR0_Msk : no need parse
# Skip DWT_FUNCTION_DATAVSIZE_Pos : no need parse
# Skip DWT_FUNCTION_DATAVSIZE_Msk : no need parse
# Skip DWT_FUNCTION_LNK1ENA_Pos : no need parse
# Skip DWT_FUNCTION_LNK1ENA_Msk : no need parse
# Skip DWT_FUNCTION_DATAVMATCH_Pos : no need parse
# Skip DWT_FUNCTION_DATAVMATCH_Msk : no need parse
# Skip DWT_FUNCTION_CYCMATCH_Pos : no need parse
# Skip DWT_FUNCTION_CYCMATCH_Msk : no need parse
# Skip DWT_FUNCTION_EMITRANGE_Pos : no need parse
# Skip DWT_FUNCTION_EMITRANGE_Msk : no need parse
# Skip DWT_FUNCTION_FUNCTION_Pos : no need parse
# Skip DWT_FUNCTION_FUNCTION_Msk : no need parse
# Skip TPI_ACPR_PRESCALER_Pos : no need parse
# Skip TPI_ACPR_PRESCALER_Msk : no need parse
# Skip TPI_SPPR_TXMODE_Pos : no need parse
# Skip TPI_SPPR_TXMODE_Msk : no need parse
# Skip TPI_FFSR_FtNonStop_Pos : no need parse
# Skip TPI_FFSR_FtNonStop_Msk : no need parse
# Skip TPI_FFSR_TCPresent_Pos : no need parse
# Skip TPI_FFSR_TCPresent_Msk : no need parse
# Skip TPI_FFSR_FtStopped_Pos : no need parse
# Skip TPI_FFSR_FtStopped_Msk : no need parse
# Skip TPI_FFSR_FlInProg_Pos : no need parse
# Skip TPI_FFSR_FlInProg_Msk : no need parse
# Skip TPI_FFCR_TrigIn_Pos : no need parse
# Skip TPI_FFCR_TrigIn_Msk : no need parse
# Skip TPI_FFCR_EnFCont_Pos : no need parse
# Skip TPI_FFCR_EnFCont_Msk : no need parse
# Skip TPI_TRIGGER_TRIGGER_Pos : no need parse
# Skip TPI_TRIGGER_TRIGGER_Msk : no need parse
# Skip TPI_FIFO0_ITM_ATVALID_Pos : no need parse
# Skip TPI_FIFO0_ITM_ATVALID_Msk : no need parse
# Skip TPI_FIFO0_ITM_bytecount_Pos : no need parse
# Skip TPI_FIFO0_ITM_bytecount_Msk : no need parse
# Skip TPI_FIFO0_ETM_ATVALID_Pos : no need parse
# Skip TPI_FIFO0_ETM_ATVALID_Msk : no need parse
# Skip TPI_FIFO0_ETM_bytecount_Pos : no need parse
# Skip TPI_FIFO0_ETM_bytecount_Msk : no need parse
# Skip TPI_FIFO0_ETM2_Pos : no need parse
# Skip TPI_FIFO0_ETM2_Msk : no need parse
# Skip TPI_FIFO0_ETM1_Pos : no need parse
# Skip TPI_FIFO0_ETM1_Msk : no need parse
# Skip TPI_FIFO0_ETM0_Pos : no need parse
# Skip TPI_FIFO0_ETM0_Msk : no need parse
# Skip TPI_ITATBCTR2_ATREADY_Pos : no need parse
# Skip TPI_ITATBCTR2_ATREADY_Msk : no need parse
# Skip TPI_FIFO1_ITM_ATVALID_Pos : no need parse
# Skip TPI_FIFO1_ITM_ATVALID_Msk : no need parse
# Skip TPI_FIFO1_ITM_bytecount_Pos : no need parse
# Skip TPI_FIFO1_ITM_bytecount_Msk : no need parse
# Skip TPI_FIFO1_ETM_ATVALID_Pos : no need parse
# Skip TPI_FIFO1_ETM_ATVALID_Msk : no need parse
# Skip TPI_FIFO1_ETM_bytecount_Pos : no need parse
# Skip TPI_FIFO1_ETM_bytecount_Msk : no need parse
# Skip TPI_FIFO1_ITM2_Pos : no need parse
# Skip TPI_FIFO1_ITM2_Msk : no need parse
# Skip TPI_FIFO1_ITM1_Pos : no need parse
# Skip TPI_FIFO1_ITM1_Msk : no need parse
# Skip TPI_FIFO1_ITM0_Pos : no need parse
# Skip TPI_FIFO1_ITM0_Msk : no need parse
# Skip TPI_ITATBCTR0_ATREADY_Pos : no need parse
# Skip TPI_ITATBCTR0_ATREADY_Msk : no need parse
# Skip TPI_ITCTRL_Mode_Pos : no need parse
# Skip TPI_ITCTRL_Mode_Msk : no need parse
# Skip TPI_DEVID_NRZVALID_Pos : no need parse
# Skip TPI_DEVID_NRZVALID_Msk : no need parse
# Skip TPI_DEVID_MANCVALID_Pos : no need parse
# Skip TPI_DEVID_MANCVALID_Msk : no need parse
# Skip TPI_DEVID_PTINVALID_Pos : no need parse
# Skip TPI_DEVID_PTINVALID_Msk : no need parse
# Skip TPI_DEVID_MinBufSz_Pos : no need parse
# Skip TPI_DEVID_MinBufSz_Msk : no need parse
# Skip TPI_DEVID_AsynClkIn_Pos : no need parse
# Skip TPI_DEVID_AsynClkIn_Msk : no need parse
# Skip TPI_DEVID_NrTraceInput_Pos : no need parse
# Skip TPI_DEVID_NrTraceInput_Msk : no need parse
# Skip TPI_DEVTYPE_SubType_Pos : no need parse
# Skip TPI_DEVTYPE_SubType_Msk : no need parse
# Skip TPI_DEVTYPE_MajorType_Pos : no need parse
# Skip TPI_DEVTYPE_MajorType_Msk : no need parse
# Skip MPU_TYPE_IREGION_Pos : no need parse
# Skip MPU_TYPE_IREGION_Msk : no need parse
# Skip MPU_TYPE_DREGION_Pos : no need parse
# Skip MPU_TYPE_DREGION_Msk : no need parse
# Skip MPU_TYPE_SEPARATE_Pos : no need parse
# Skip MPU_TYPE_SEPARATE_Msk : no need parse
# Skip MPU_CTRL_PRIVDEFENA_Pos : no need parse
# Skip MPU_CTRL_PRIVDEFENA_Msk : no need parse
# Skip MPU_CTRL_HFNMIENA_Pos : no need parse
# Skip MPU_CTRL_HFNMIENA_Msk : no need parse
# Skip MPU_CTRL_ENABLE_Pos : no need parse
# Skip MPU_CTRL_ENABLE_Msk : no need parse
# Skip MPU_RNR_REGION_Pos : no need parse
# Skip MPU_RNR_REGION_Msk : no need parse
# Skip MPU_RBAR_ADDR_Pos : no need parse
# Skip MPU_RBAR_ADDR_Msk : no need parse
# Skip MPU_RBAR_VALID_Pos : no need parse
# Skip MPU_RBAR_VALID_Msk : no need parse
# Skip MPU_RBAR_REGION_Pos : no need parse
# Skip MPU_RBAR_REGION_Msk : no need parse
# Skip MPU_RASR_ATTRS_Pos : no need parse
# Skip MPU_RASR_ATTRS_Msk : no need parse
# Skip MPU_RASR_SRD_Pos : no need parse
# Skip MPU_RASR_SRD_Msk : no need parse
# Skip MPU_RASR_SIZE_Pos : no need parse
# Skip MPU_RASR_SIZE_Msk : no need parse
# Skip MPU_RASR_ENABLE_Pos : no need parse
# Skip MPU_RASR_ENABLE_Msk : no need parse
# Skip FPU_FPCCR_ASPEN_Pos : no need parse
# Skip FPU_FPCCR_ASPEN_Msk : no need parse
# Skip FPU_FPCCR_LSPEN_Pos : no need parse
# Skip FPU_FPCCR_LSPEN_Msk : no need parse
# Skip FPU_FPCCR_MONRDY_Pos : no need parse
# Skip FPU_FPCCR_MONRDY_Msk : no need parse
# Skip FPU_FPCCR_BFRDY_Pos : no need parse
# Skip FPU_FPCCR_BFRDY_Msk : no need parse
# Skip FPU_FPCCR_MMRDY_Pos : no need parse
# Skip FPU_FPCCR_MMRDY_Msk : no need parse
# Skip FPU_FPCCR_HFRDY_Pos : no need parse
# Skip FPU_FPCCR_HFRDY_Msk : no need parse
# Skip FPU_FPCCR_THREAD_Pos : no need parse
# Skip FPU_FPCCR_THREAD_Msk : no need parse
# Skip FPU_FPCCR_USER_Pos : no need parse
# Skip FPU_FPCCR_USER_Msk : no need parse
# Skip FPU_FPCCR_LSPACT_Pos : no need parse
# Skip FPU_FPCCR_LSPACT_Msk : no need parse
# Skip FPU_FPCAR_ADDRESS_Pos : no need parse
# Skip FPU_FPCAR_ADDRESS_Msk : no need parse
# Skip FPU_FPDSCR_AHP_Pos : no need parse
# Skip FPU_FPDSCR_AHP_Msk : no need parse
# Skip FPU_FPDSCR_DN_Pos : no need parse
# Skip FPU_FPDSCR_DN_Msk : no need parse
# Skip FPU_FPDSCR_FZ_Pos : no need parse
# Skip FPU_FPDSCR_FZ_Msk : no need parse
# Skip FPU_FPDSCR_RMode_Pos : no need parse
# Skip FPU_FPDSCR_RMode_Msk : no need parse
# Skip FPU_MVFR0_FP_rounding_modes_Pos : no need parse
# Skip FPU_MVFR0_FP_rounding_modes_Msk : no need parse
# Skip FPU_MVFR0_Short_vectors_Pos : no need parse
# Skip FPU_MVFR0_Short_vectors_Msk : no need parse
# Skip FPU_MVFR0_Square_root_Pos : no need parse
# Skip FPU_MVFR0_Square_root_Msk : no need parse
# Skip FPU_MVFR0_Divide_Pos : no need parse
# Skip FPU_MVFR0_Divide_Msk : no need parse
# Skip FPU_MVFR0_FP_excep_trapping_Pos : no need parse
# Skip FPU_MVFR0_FP_excep_trapping_Msk : no need parse
# Skip FPU_MVFR0_Double_precision_Pos : no need parse
# Skip FPU_MVFR0_Double_precision_Msk : no need parse
# Skip FPU_MVFR0_Single_precision_Pos : no need parse
# Skip FPU_MVFR0_Single_precision_Msk : no need parse
# Skip FPU_MVFR0_A_SIMD_registers_Pos : no need parse
# Skip FPU_MVFR0_A_SIMD_registers_Msk : no need parse
# Skip FPU_MVFR1_FP_fused_MAC_Pos : no need parse
# Skip FPU_MVFR1_FP_fused_MAC_Msk : no need parse
# Skip FPU_MVFR1_FP_HPFP_Pos : no need parse
# Skip FPU_MVFR1_FP_HPFP_Msk : no need parse
# Skip FPU_MVFR1_D_NaN_mode_Pos : no need parse
# Skip FPU_MVFR1_D_NaN_mode_Msk : no need parse
# Skip FPU_MVFR1_FtZ_mode_Pos : no need parse
# Skip FPU_MVFR1_FtZ_mode_Msk : no need parse
# Skip CoreDebug_DHCSR_DBGKEY_Pos : no need parse
# Skip CoreDebug_DHCSR_DBGKEY_Msk : no need parse
# Skip CoreDebug_DHCSR_S_RESET_ST_Pos : no need parse
# Skip CoreDebug_DHCSR_S_RESET_ST_Msk : no need parse
# Skip CoreDebug_DHCSR_S_RETIRE_ST_Pos : no need parse
# Skip CoreDebug_DHCSR_S_RETIRE_ST_Msk : no need parse
# Skip CoreDebug_DHCSR_S_LOCKUP_Pos : no need parse
# Skip CoreDebug_DHCSR_S_LOCKUP_Msk : no need parse
# Skip CoreDebug_DHCSR_S_SLEEP_Pos : no need parse
# Skip CoreDebug_DHCSR_S_SLEEP_Msk : no need parse
# Skip CoreDebug_DHCSR_S_HALT_Pos : no need parse
# Skip CoreDebug_DHCSR_S_HALT_Msk : no need parse
# Skip CoreDebug_DHCSR_S_REGRDY_Pos : no need parse
# Skip CoreDebug_DHCSR_S_REGRDY_Msk : no need parse
# Skip CoreDebug_DHCSR_C_SNAPSTALL_Pos : no need parse
# Skip CoreDebug_DHCSR_C_SNAPSTALL_Msk : no need parse
# Skip CoreDebug_DHCSR_C_MASKINTS_Pos : no need parse
# Skip CoreDebug_DHCSR_C_MASKINTS_Msk : no need parse
# Skip CoreDebug_DHCSR_C_STEP_Pos : no need parse
# Skip CoreDebug_DHCSR_C_STEP_Msk : no need parse
# Skip CoreDebug_DHCSR_C_HALT_Pos : no need parse
# Skip CoreDebug_DHCSR_C_HALT_Msk : no need parse
# Skip CoreDebug_DHCSR_C_DEBUGEN_Pos : no need parse
# Skip CoreDebug_DHCSR_C_DEBUGEN_Msk : no need parse
# Skip CoreDebug_DCRSR_REGWnR_Pos : no need parse
# Skip CoreDebug_DCRSR_REGWnR_Msk : no need parse
# Skip CoreDebug_DCRSR_REGSEL_Pos : no need parse
# Skip CoreDebug_DCRSR_REGSEL_Msk : no need parse
# Skip CoreDebug_DEMCR_TRCENA_Pos : no need parse
# Skip CoreDebug_DEMCR_TRCENA_Msk : no need parse
# Skip CoreDebug_DEMCR_MON_REQ_Pos : no need parse
# Skip CoreDebug_DEMCR_MON_REQ_Msk : no need parse
# Skip CoreDebug_DEMCR_MON_STEP_Pos : no need parse
# Skip CoreDebug_DEMCR_MON_STEP_Msk : no need parse
# Skip CoreDebug_DEMCR_MON_PEND_Pos : no need parse
# Skip CoreDebug_DEMCR_MON_PEND_Msk : no need parse
# Skip CoreDebug_DEMCR_MON_EN_Pos : no need parse
# Skip CoreDebug_DEMCR_MON_EN_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_HARDERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_HARDERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_INTERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_INTERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_BUSERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_BUSERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_STATERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_STATERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_CHKERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_CHKERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_NOCPERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_NOCPERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_MMERR_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_MMERR_Msk : no need parse
# Skip CoreDebug_DEMCR_VC_CORERESET_Pos : no need parse
# Skip CoreDebug_DEMCR_VC_CORERESET_Msk : no need parse
# Skip SCS_BASE : no need parse
# Skip ITM_BASE : no need parse
# Skip DWT_BASE : no need parse
# Skip TPI_BASE : no need parse
# Skip CoreDebug_BASE : no need parse
# Skip SysTick_BASE : no need parse
# Skip NVIC_BASE : no need parse
# Skip SCB_BASE : no need parse
# Skip SCnSCB : no need parse
# Skip SCB : no need parse
# Skip SysTick : no need parse
# Skip NVIC : no need parse
# Skip ITM : no need parse
# Skip DWT : no need parse
# Skip TPI : no need parse
# Skip CoreDebug : no need parse
# Skip MPU_BASE : no need parse
# Skip MPU : no need parse
# Skip FPU_BASE : no need parse
# Skip FPU : no need parse
# Skip ITM_RXBUFFER_EMPTY : no need parse
# Skip ITM_RxBuffer : no need parse
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

# struct SCnSCB_Type

class SCnSCB_Type(ctypes.Structure):
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

# struct ITM_Type

class ITM_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct DWT_Type

class DWT_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct TPI_Type

class TPI_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct MPU_Type

class MPU_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct FPU_Type

class FPU_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# struct CoreDebug_Type

class CoreDebug_Type(ctypes.Structure):
	_pack_ = False
	_fields_ = [
	]
	def ref(self):
		return ctypes.byref(self)

# ----------------------------------------

# file stm32f30x.h : 

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
TAMPER_STAMP_IRQn = 0x2
RTC_WKUP_IRQn = 0x3
FLASH_IRQn = 0x4
RCC_IRQn = 0x5
EXTI0_IRQn = 0x6
EXTI1_IRQn = 0x7
EXTI2_TS_IRQn = 0x8
EXTI3_IRQn = 0x9
EXTI4_IRQn = 0xA
DMA1_Channel1_IRQn = 0xB
DMA1_Channel2_IRQn = 0xC
DMA1_Channel3_IRQn = 0xD
DMA1_Channel4_IRQn = 0xE
DMA1_Channel5_IRQn = 0xF
DMA1_Channel6_IRQn = 0x10
DMA1_Channel7_IRQn = 0x11
ADC1_2_IRQn = 0x12
USB_HP_CAN1_TX_IRQn = 0x13
USB_LP_CAN1_RX0_IRQn = 0x14
CAN1_RX1_IRQn = 0x15
CAN1_SCE_IRQn = 0x16
EXTI9_5_IRQn = 0x17
TIM1_BRK_TIM15_IRQn = 0x18
TIM1_UP_TIM16_IRQn = 0x19
TIM1_TRG_COM_TIM17_IRQn = 0x1A
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
USBWakeUp_IRQn = 0x2A
TIM8_BRK_IRQn = 0x2B
TIM8_UP_IRQn = 0x2C
TIM8_TRG_COM_IRQn = 0x2D
TIM8_CC_IRQn = 0x2E
ADC3_IRQn = 0x2F
SPI3_IRQn = 0x33
UART4_IRQn = 0x34
UART5_IRQn = 0x35
TIM6_DAC_IRQn = 0x36
TIM7_IRQn = 0x37
DMA2_Channel1_IRQn = 0x38
DMA2_Channel2_IRQn = 0x39
DMA2_Channel3_IRQn = 0x3A
DMA2_Channel4_IRQn = 0x3B
DMA2_Channel5_IRQn = 0x3C
ADC4_IRQn = 0x3D
COMP1_2_3_IRQn = 0x40
COMP4_5_6_IRQn = 0x41
COMP7_IRQn = 0x42
USB_HP_IRQn = 0x4A
USB_LP_IRQn = 0x4B
USBWakeUp_RMP_IRQn = 0x4C
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
# empty define __STM32F30x_H
# empty define STM32F30X
HSE_VALUE = 0x7A1200
HSE_STARTUP_TIMEOUT = 0x500
HSI_STARTUP_TIMEOUT = 0x500
HSI_VALUE = 0x7A1200
LSI_VALUE = 0x9C40
LSE_VALUE = 0x8000
__STM32F30X_STDPERIPH_VERSION_MAIN = 0x1
__STM32F30X_STDPERIPH_VERSION_SUB1 = 0x0
__STM32F30X_STDPERIPH_VERSION_SUB2 = 0x0
__STM32F30X_STDPERIPH_VERSION_RC = 0x0
__STM32F30X_STDPERIPH_VERSION = 0x1000000
__CM4_REV = 0x1
__MPU_PRESENT = 0x1
__NVIC_PRIO_BITS = 0x4
__Vendor_SysTickConfig = 0x0
__FPU_PRESENT = 0x1
# fun define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
FLASH_BASE = 0x8000000
SRAM_BASE = 0x20000000
PERIPH_BASE = 0x40000000
SRAM_BB_BASE = 0x22000000
PERIPH_BB_BASE = 0x42000000
APB1PERIPH_BASE = 0x40000000
APB2PERIPH_BASE = 0x40010000
AHB1PERIPH_BASE = 0x40020000
AHB2PERIPH_BASE = 0x48000000
AHB3PERIPH_BASE = 0x50000000
TIM2_BASE = 0x40000000
TIM3_BASE = 0x40000400
TIM4_BASE = 0x40000800
TIM6_BASE = 0x40001000
TIM7_BASE = 0x40001400
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
CAN1_BASE = 0x40006400
PWR_BASE = 0x40007000
DAC_BASE = 0x40007400
SYSCFG_BASE = 0x40010000
COMP_BASE = 0x4001001C
COMP1_BASE = 0x4001001C
COMP2_BASE = 0x40010020
COMP3_BASE = 0x40010024
COMP4_BASE = 0x40010028
COMP5_BASE = 0x4001002C
COMP6_BASE = 0x40010030
COMP7_BASE = 0x40010034
OPAMP_BASE = 0x40010038
OPAMP1_BASE = 0x40010038
OPAMP2_BASE = 0x4001003C
OPAMP3_BASE = 0x40010040
OPAMP4_BASE = 0x40010044
EXTI_BASE = 0x40010400
TIM1_BASE = 0x40012C00
SPI1_BASE = 0x40013000
TIM8_BASE = 0x40013400
USART1_BASE = 0x40013800
TIM15_BASE = 0x40014000
TIM16_BASE = 0x40014400
TIM17_BASE = 0x40014800
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
ADC1_BASE = 0x50000000
ADC2_BASE = 0x50000100
ADC1_2_BASE = 0x50000300
ADC3_BASE = 0x50000400
ADC4_BASE = 0x50000500
ADC3_4_BASE = 0x50000700
DBGMCU_BASE = 0xE0042000
TIM2 = 0x40000000
TIM3 = 0x40000400
TIM4 = 0x40000800
TIM6 = 0x40001000
TIM7 = 0x40001400
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
CAN1 = 0x40006400
PWR = 0x40007000
DAC = 0x40007400
SYSCFG = 0x40010000
COMP = 0x4001001C
COMP1 = 0x4001001C
COMP2 = 0x40010020
COMP3 = 0x40010024
COMP4 = 0x40010028
COMP5 = 0x4001002C
COMP6 = 0x40010030
COMP7 = 0x40010034
OPAMP = 0x40010038
OPAMP1 = 0x40010038
OPAMP2 = 0x4001003C
OPAMP3 = 0x40010040
OPAMP4 = 0x40010044
EXTI = 0x40010400
TIM1 = 0x40012C00
SPI1 = 0x40013000
TIM8 = 0x40013400
USART1 = 0x40013800
TIM15 = 0x40014000
TIM16 = 0x40014400
TIM17 = 0x40014800
DBGMCU = 0xE0042000
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
RCC = 0x40021000
FLASH = 0x40022000
OB = 0x1FFFF800
CRC = 0x40023000
TSC = 0x40024000
GPIOA = 0x48000000
GPIOB = 0x48000400
GPIOC = 0x48000800
GPIOD = 0x48000C00
GPIOE = 0x48001000
GPIOF = 0x48001400
ADC1 = 0x50000000
ADC2 = 0x50000100
ADC3 = 0x50000400
ADC4 = 0x50000500
ADC1_2 = 0x50000300
ADC3_4 = 0x50000700
ADC_ISR_ADRD = 0x1
ADC_ISR_EOSMP = 0x2
ADC_ISR_EOC = 0x4
ADC_ISR_EOS = 0x8
ADC_ISR_OVR = 0x10
ADC_ISR_JEOC = 0x20
ADC_ISR_JEOS = 0x40
ADC_ISR_AWD1 = 0x80
ADC_ISR_AWD2 = 0x100
ADC_ISR_AWD3 = 0x200
ADC_ISR_JQOVF = 0x400
ADC_IER_RDY = 0x1
ADC_IER_EOSMP = 0x2
ADC_IER_EOC = 0x4
ADC_IER_EOS = 0x8
ADC_IER_OVR = 0x10
ADC_IER_JEOC = 0x20
ADC_IER_JEOS = 0x40
ADC_IER_AWD1 = 0x80
ADC_IER_AWD2 = 0x100
ADC_IER_AWD3 = 0x200
ADC_IER_JQOVF = 0x400
ADC_CR_ADEN = 0x1
ADC_CR_ADDIS = 0x2
ADC_CR_ADSTART = 0x4
ADC_CR_JADSTART = 0x8
ADC_CR_ADSTP = 0x10
ADC_CR_JADSTP = 0x20
ADC_CR_ADVREGEN = 0x30000000
ADC_CR_ADVREGEN_0 = 0x10000000
ADC_CR_ADVREGEN_1 = 0x20000000
ADC_CR_ADCALDIF = 0x40000000
ADC_CR_ADCAL = 0x80000000
ADC_CFGR_DMAEN = 0x1
ADC_CFGR_DMACFG = 0x2
ADC_CFGR_RES = 0x18
ADC_CFGR_RES_0 = 0x8
ADC_CFGR_RES_1 = 0x10
ADC_CFGR_ALIGN = 0x20
ADC_CFGR_EXTSEL = 0x3C0
ADC_CFGR_EXTSEL_0 = 0x40
ADC_CFGR_EXTSEL_1 = 0x80
ADC_CFGR_EXTSEL_2 = 0x100
ADC_CFGR_EXTSEL_3 = 0x200
ADC_CFGR_EXTEN = 0xC00
ADC_CFGR_EXTEN_0 = 0x400
ADC_CFGR_EXTEN_1 = 0x800
ADC_CFGR_OVRMOD = 0x1000
ADC_CFGR_CONT = 0x2000
ADC_CFGR_AUTDLY = 0x4000
ADC_CFGR_AUTOFF = 0x8000
ADC_CFGR_DISCEN = 0x10000
ADC_CFGR_DISCNUM = 0xE0000
ADC_CFGR_DISCNUM_0 = 0x20000
ADC_CFGR_DISCNUM_1 = 0x40000
ADC_CFGR_DISCNUM_2 = 0x80000
ADC_CFGR_JDISCEN = 0x100000
ADC_CFGR_JQM = 0x200000
ADC_CFGR_AWD1SGL = 0x400000
ADC_CFGR_AWD1EN = 0x800000
ADC_CFGR_JAWD1EN = 0x1000000
ADC_CFGR_JAUTO = 0x2000000
ADC_CFGR_AWD1CH = 0x7C000000
ADC_CFGR_AWD1CH_0 = 0x4000000
ADC_CFGR_AWD1CH_1 = 0x8000000
ADC_CFGR_AWD1CH_2 = 0x10000000
ADC_CFGR_AWD1CH_3 = 0x20000000
ADC_CFGR_AWD1CH_4 = 0x40000000
ADC_SMPR1_SMP0 = 0x7
ADC_SMPR1_SMP0_0 = 0x1
ADC_SMPR1_SMP0_1 = 0x2
ADC_SMPR1_SMP0_2 = 0x4
ADC_SMPR1_SMP1 = 0x38
ADC_SMPR1_SMP1_0 = 0x8
ADC_SMPR1_SMP1_1 = 0x10
ADC_SMPR1_SMP1_2 = 0x20
ADC_SMPR1_SMP2 = 0x1C0
ADC_SMPR1_SMP2_0 = 0x40
ADC_SMPR1_SMP2_1 = 0x80
ADC_SMPR1_SMP2_2 = 0x100
ADC_SMPR1_SMP3 = 0xE00
ADC_SMPR1_SMP3_0 = 0x200
ADC_SMPR1_SMP3_1 = 0x400
ADC_SMPR1_SMP3_2 = 0x800
ADC_SMPR1_SMP4 = 0x7000
ADC_SMPR1_SMP4_0 = 0x1000
ADC_SMPR1_SMP4_1 = 0x2000
ADC_SMPR1_SMP4_2 = 0x4000
ADC_SMPR1_SMP5 = 0x38000
ADC_SMPR1_SMP5_0 = 0x8000
ADC_SMPR1_SMP5_1 = 0x10000
ADC_SMPR1_SMP5_2 = 0x20000
ADC_SMPR1_SMP6 = 0x1C0000
ADC_SMPR1_SMP6_0 = 0x40000
ADC_SMPR1_SMP6_1 = 0x80000
ADC_SMPR1_SMP6_2 = 0x100000
ADC_SMPR1_SMP7 = 0xE00000
ADC_SMPR1_SMP7_0 = 0x200000
ADC_SMPR1_SMP7_1 = 0x400000
ADC_SMPR1_SMP7_2 = 0x800000
ADC_SMPR1_SMP8 = 0x7000000
ADC_SMPR1_SMP8_0 = 0x1000000
ADC_SMPR1_SMP8_1 = 0x2000000
ADC_SMPR1_SMP8_2 = 0x4000000
ADC_SMPR1_SMP9 = 0x38000000
ADC_SMPR1_SMP9_0 = 0x8000000
ADC_SMPR1_SMP9_1 = 0x10000000
ADC_SMPR1_SMP9_2 = 0x20000000
ADC_SMPR2_SMP10 = 0x7
ADC_SMPR2_SMP10_0 = 0x1
ADC_SMPR2_SMP10_1 = 0x2
ADC_SMPR2_SMP10_2 = 0x4
ADC_SMPR2_SMP11 = 0x38
ADC_SMPR2_SMP11_0 = 0x8
ADC_SMPR2_SMP11_1 = 0x10
ADC_SMPR2_SMP11_2 = 0x20
ADC_SMPR2_SMP12 = 0x1C0
ADC_SMPR2_SMP12_0 = 0x40
ADC_SMPR2_SMP12_1 = 0x80
ADC_SMPR2_SMP12_2 = 0x100
ADC_SMPR2_SMP13 = 0xE00
ADC_SMPR2_SMP13_0 = 0x200
ADC_SMPR2_SMP13_1 = 0x400
ADC_SMPR2_SMP13_2 = 0x800
ADC_SMPR2_SMP14 = 0x7000
ADC_SMPR2_SMP14_0 = 0x1000
ADC_SMPR2_SMP14_1 = 0x2000
ADC_SMPR2_SMP14_2 = 0x4000
ADC_SMPR2_SMP15 = 0x38000
ADC_SMPR2_SMP15_0 = 0x8000
ADC_SMPR2_SMP15_1 = 0x10000
ADC_SMPR2_SMP15_2 = 0x20000
ADC_SMPR2_SMP16 = 0x1C0000
ADC_SMPR2_SMP16_0 = 0x40000
ADC_SMPR2_SMP16_1 = 0x80000
ADC_SMPR2_SMP16_2 = 0x100000
ADC_SMPR2_SMP17 = 0xE00000
ADC_SMPR2_SMP17_0 = 0x200000
ADC_SMPR2_SMP17_1 = 0x400000
ADC_SMPR2_SMP17_2 = 0x800000
ADC_SMPR2_SMP18 = 0x7000000
ADC_SMPR2_SMP18_0 = 0x1000000
ADC_SMPR2_SMP18_1 = 0x2000000
ADC_SMPR2_SMP18_2 = 0x4000000
ADC_TR1_LT1 = 0xFFF
ADC_TR1_LT1_0 = 0x1
ADC_TR1_LT1_1 = 0x2
ADC_TR1_LT1_2 = 0x4
ADC_TR1_LT1_3 = 0x8
ADC_TR1_LT1_4 = 0x10
ADC_TR1_LT1_5 = 0x20
ADC_TR1_LT1_6 = 0x40
ADC_TR1_LT1_7 = 0x80
ADC_TR1_LT1_8 = 0x100
ADC_TR1_LT1_9 = 0x200
ADC_TR1_LT1_10 = 0x400
ADC_TR1_LT1_11 = 0x800
ADC_TR1_HT1 = 0xFFF0000
ADC_TR1_HT1_0 = 0x10000
ADC_TR1_HT1_1 = 0x20000
ADC_TR1_HT1_2 = 0x40000
ADC_TR1_HT1_3 = 0x80000
ADC_TR1_HT1_4 = 0x100000
ADC_TR1_HT1_5 = 0x200000
ADC_TR1_HT1_6 = 0x400000
ADC_TR1_HT1_7 = 0x800000
ADC_TR1_HT1_8 = 0x1000000
ADC_TR1_HT1_9 = 0x2000000
ADC_TR1_HT1_10 = 0x4000000
ADC_TR1_HT1_11 = 0x8000000
ADC_TR2_LT2 = 0xFF
ADC_TR2_LT2_0 = 0x1
ADC_TR2_LT2_1 = 0x2
ADC_TR2_LT2_2 = 0x4
ADC_TR2_LT2_3 = 0x8
ADC_TR2_LT2_4 = 0x10
ADC_TR2_LT2_5 = 0x20
ADC_TR2_LT2_6 = 0x40
ADC_TR2_LT2_7 = 0x80
ADC_TR2_HT2 = 0xFF0000
ADC_TR2_HT2_0 = 0x10000
ADC_TR2_HT2_1 = 0x20000
ADC_TR2_HT2_2 = 0x40000
ADC_TR2_HT2_3 = 0x80000
ADC_TR2_HT2_4 = 0x100000
ADC_TR2_HT2_5 = 0x200000
ADC_TR2_HT2_6 = 0x400000
ADC_TR2_HT2_7 = 0x800000
ADC_TR3_LT3 = 0xFF
ADC_TR3_LT3_0 = 0x1
ADC_TR3_LT3_1 = 0x2
ADC_TR3_LT3_2 = 0x4
ADC_TR3_LT3_3 = 0x8
ADC_TR3_LT3_4 = 0x10
ADC_TR3_LT3_5 = 0x20
ADC_TR3_LT3_6 = 0x40
ADC_TR3_LT3_7 = 0x80
ADC_TR3_HT3 = 0xFF0000
ADC_TR3_HT3_0 = 0x10000
ADC_TR3_HT3_1 = 0x20000
ADC_TR3_HT3_2 = 0x40000
ADC_TR3_HT3_3 = 0x80000
ADC_TR3_HT3_4 = 0x100000
ADC_TR3_HT3_5 = 0x200000
ADC_TR3_HT3_6 = 0x400000
ADC_TR3_HT3_7 = 0x800000
ADC_SQR1_L = 0xF
ADC_SQR1_L_0 = 0x1
ADC_SQR1_L_1 = 0x2
ADC_SQR1_L_2 = 0x4
ADC_SQR1_L_3 = 0x8
ADC_SQR1_SQ1 = 0x7C0
ADC_SQR1_SQ1_0 = 0x40
ADC_SQR1_SQ1_1 = 0x80
ADC_SQR1_SQ1_2 = 0x100
ADC_SQR1_SQ1_3 = 0x200
ADC_SQR1_SQ1_4 = 0x400
ADC_SQR1_SQ2 = 0x1F000
ADC_SQR1_SQ2_0 = 0x1000
ADC_SQR1_SQ2_1 = 0x2000
ADC_SQR1_SQ2_2 = 0x4000
ADC_SQR1_SQ2_3 = 0x8000
ADC_SQR1_SQ2_4 = 0x10000
ADC_SQR1_SQ3 = 0x7C0000
ADC_SQR1_SQ3_0 = 0x40000
ADC_SQR1_SQ3_1 = 0x80000
ADC_SQR1_SQ3_2 = 0x100000
ADC_SQR1_SQ3_3 = 0x200000
ADC_SQR1_SQ3_4 = 0x400000
ADC_SQR1_SQ4 = 0x1F000000
ADC_SQR1_SQ4_0 = 0x1000000
ADC_SQR1_SQ4_1 = 0x2000000
ADC_SQR1_SQ4_2 = 0x4000000
ADC_SQR1_SQ4_3 = 0x8000000
ADC_SQR1_SQ4_4 = 0x10000000
ADC_SQR2_SQ5 = 0x1F
ADC_SQR2_SQ5_0 = 0x1
ADC_SQR2_SQ5_1 = 0x2
ADC_SQR2_SQ5_2 = 0x4
ADC_SQR2_SQ5_3 = 0x8
ADC_SQR2_SQ5_4 = 0x10
ADC_SQR2_SQ6 = 0x7C0
ADC_SQR2_SQ6_0 = 0x40
ADC_SQR2_SQ6_1 = 0x80
ADC_SQR2_SQ6_2 = 0x100
ADC_SQR2_SQ6_3 = 0x200
ADC_SQR2_SQ6_4 = 0x400
ADC_SQR2_SQ7 = 0x1F000
ADC_SQR2_SQ7_0 = 0x1000
ADC_SQR2_SQ7_1 = 0x2000
ADC_SQR2_SQ7_2 = 0x4000
ADC_SQR2_SQ7_3 = 0x8000
ADC_SQR2_SQ7_4 = 0x10000
ADC_SQR2_SQ8 = 0x7C0000
ADC_SQR2_SQ8_0 = 0x40000
ADC_SQR2_SQ8_1 = 0x80000
ADC_SQR2_SQ8_2 = 0x100000
ADC_SQR2_SQ8_3 = 0x200000
ADC_SQR2_SQ8_4 = 0x400000
ADC_SQR2_SQ9 = 0x1F000000
ADC_SQR2_SQ9_0 = 0x1000000
ADC_SQR2_SQ9_1 = 0x2000000
ADC_SQR2_SQ9_2 = 0x4000000
ADC_SQR2_SQ9_3 = 0x8000000
ADC_SQR2_SQ9_4 = 0x10000000
ADC_SQR3_SQ10 = 0x1F
ADC_SQR3_SQ10_0 = 0x1
ADC_SQR3_SQ10_1 = 0x2
ADC_SQR3_SQ10_2 = 0x4
ADC_SQR3_SQ10_3 = 0x8
ADC_SQR3_SQ10_4 = 0x10
ADC_SQR3_SQ11 = 0x7C0
ADC_SQR3_SQ11_0 = 0x40
ADC_SQR3_SQ11_1 = 0x80
ADC_SQR3_SQ11_2 = 0x100
ADC_SQR3_SQ11_3 = 0x200
ADC_SQR3_SQ11_4 = 0x400
ADC_SQR3_SQ12 = 0x1F000
ADC_SQR3_SQ12_0 = 0x1000
ADC_SQR3_SQ12_1 = 0x2000
ADC_SQR3_SQ12_2 = 0x4000
ADC_SQR3_SQ12_3 = 0x8000
ADC_SQR3_SQ12_4 = 0x10000
ADC_SQR3_SQ13 = 0x7C0000
ADC_SQR3_SQ13_0 = 0x40000
ADC_SQR3_SQ13_1 = 0x80000
ADC_SQR3_SQ13_2 = 0x100000
ADC_SQR3_SQ13_3 = 0x200000
ADC_SQR3_SQ13_4 = 0x400000
ADC_SQR3_SQ14 = 0x1F000000
ADC_SQR3_SQ14_0 = 0x1000000
ADC_SQR3_SQ14_1 = 0x2000000
ADC_SQR3_SQ14_2 = 0x4000000
ADC_SQR3_SQ14_3 = 0x8000000
ADC_SQR3_SQ14_4 = 0x10000000
ADC_SQR3_SQ15 = 0x1F
ADC_SQR3_SQ15_0 = 0x1
ADC_SQR3_SQ15_1 = 0x2
ADC_SQR3_SQ15_2 = 0x4
ADC_SQR3_SQ15_3 = 0x8
ADC_SQR3_SQ15_4 = 0x10
ADC_SQR3_SQ16 = 0x7C0
ADC_SQR3_SQ16_0 = 0x40
ADC_SQR3_SQ16_1 = 0x80
ADC_SQR3_SQ16_2 = 0x100
ADC_SQR3_SQ16_3 = 0x200
ADC_SQR3_SQ16_4 = 0x400
ADC_DR_RDATA = 0xFFFF
ADC_DR_RDATA_0 = 0x1
ADC_DR_RDATA_1 = 0x2
ADC_DR_RDATA_2 = 0x4
ADC_DR_RDATA_3 = 0x8
ADC_DR_RDATA_4 = 0x10
ADC_DR_RDATA_5 = 0x20
ADC_DR_RDATA_6 = 0x40
ADC_DR_RDATA_7 = 0x80
ADC_DR_RDATA_8 = 0x100
ADC_DR_RDATA_9 = 0x200
ADC_DR_RDATA_10 = 0x400
ADC_DR_RDATA_11 = 0x800
ADC_DR_RDATA_12 = 0x1000
ADC_DR_RDATA_13 = 0x2000
ADC_DR_RDATA_14 = 0x4000
ADC_DR_RDATA_15 = 0x8000
ADC_JSQR_JL = 0x3
ADC_JSQR_JL_0 = 0x1
ADC_JSQR_JL_1 = 0x2
ADC_JSQR_JEXTSEL = 0x3C
ADC_JSQR_JEXTSEL_0 = 0x4
ADC_JSQR_JEXTSEL_1 = 0x8
ADC_JSQR_JEXTSEL_2 = 0x10
ADC_JSQR_JEXTSEL_3 = 0x20
ADC_JSQR_JEXTEN = 0xC0
ADC_JSQR_JEXTEN_0 = 0x40
ADC_JSQR_JEXTEN_1 = 0x80
ADC_JSQR_JSQ1 = 0x1F00
ADC_JSQR_JSQ1_0 = 0x100
ADC_JSQR_JSQ1_1 = 0x200
ADC_JSQR_JSQ1_2 = 0x400
ADC_JSQR_JSQ1_3 = 0x800
ADC_JSQR_JSQ1_4 = 0x1000
ADC_JSQR_JSQ2 = 0x7C000
ADC_JSQR_JSQ2_0 = 0x4000
ADC_JSQR_JSQ2_1 = 0x8000
ADC_JSQR_JSQ2_2 = 0x10000
ADC_JSQR_JSQ2_3 = 0x20000
ADC_JSQR_JSQ2_4 = 0x40000
ADC_JSQR_JSQ3 = 0x1F00000
ADC_JSQR_JSQ3_0 = 0x100000
ADC_JSQR_JSQ3_1 = 0x200000
ADC_JSQR_JSQ3_2 = 0x400000
ADC_JSQR_JSQ3_3 = 0x800000
ADC_JSQR_JSQ3_4 = 0x1000000
ADC_JSQR_JSQ4 = 0x7C000000
ADC_JSQR_JSQ4_0 = 0x4000000
ADC_JSQR_JSQ4_1 = 0x8000000
ADC_JSQR_JSQ4_2 = 0x10000000
ADC_JSQR_JSQ4_3 = 0x20000000
ADC_JSQR_JSQ4_4 = 0x40000000
ADC_OFR1_OFFSET1 = 0xFFF
ADC_OFR1_OFFSET1_0 = 0x1
ADC_OFR1_OFFSET1_1 = 0x2
ADC_OFR1_OFFSET1_2 = 0x4
ADC_OFR1_OFFSET1_3 = 0x8
ADC_OFR1_OFFSET1_4 = 0x10
ADC_OFR1_OFFSET1_5 = 0x20
ADC_OFR1_OFFSET1_6 = 0x40
ADC_OFR1_OFFSET1_7 = 0x80
ADC_OFR1_OFFSET1_8 = 0x100
ADC_OFR1_OFFSET1_9 = 0x200
ADC_OFR1_OFFSET1_10 = 0x400
ADC_OFR1_OFFSET1_11 = 0x800
ADC_OFR1_OFFSET1_CH = 0x7C000000
ADC_OFR1_OFFSET1_CH_0 = 0x4000000
ADC_OFR1_OFFSET1_CH_1 = 0x8000000
ADC_OFR1_OFFSET1_CH_2 = 0x10000000
ADC_OFR1_OFFSET1_CH_3 = 0x20000000
ADC_OFR1_OFFSET1_CH_4 = 0x40000000
ADC_OFR1_OFFSET1_EN = 0x80000000
ADC_OFR2_OFFSET2 = 0xFFF
ADC_OFR2_OFFSET2_0 = 0x1
ADC_OFR2_OFFSET2_1 = 0x2
ADC_OFR2_OFFSET2_2 = 0x4
ADC_OFR2_OFFSET2_3 = 0x8
ADC_OFR2_OFFSET2_4 = 0x10
ADC_OFR2_OFFSET2_5 = 0x20
ADC_OFR2_OFFSET2_6 = 0x40
ADC_OFR2_OFFSET2_7 = 0x80
ADC_OFR2_OFFSET2_8 = 0x100
ADC_OFR2_OFFSET2_9 = 0x200
ADC_OFR2_OFFSET2_10 = 0x400
ADC_OFR2_OFFSET2_11 = 0x800
ADC_OFR2_OFFSET2_CH = 0x7C000000
ADC_OFR2_OFFSET2_CH_0 = 0x4000000
ADC_OFR2_OFFSET2_CH_1 = 0x8000000
ADC_OFR2_OFFSET2_CH_2 = 0x10000000
ADC_OFR2_OFFSET2_CH_3 = 0x20000000
ADC_OFR2_OFFSET2_CH_4 = 0x40000000
ADC_OFR2_OFFSET2_EN = 0x80000000
ADC_OFR3_OFFSET3 = 0xFFF
ADC_OFR3_OFFSET3_0 = 0x1
ADC_OFR3_OFFSET3_1 = 0x2
ADC_OFR3_OFFSET3_2 = 0x4
ADC_OFR3_OFFSET3_3 = 0x8
ADC_OFR3_OFFSET3_4 = 0x10
ADC_OFR3_OFFSET3_5 = 0x20
ADC_OFR3_OFFSET3_6 = 0x40
ADC_OFR3_OFFSET3_7 = 0x80
ADC_OFR3_OFFSET3_8 = 0x100
ADC_OFR3_OFFSET3_9 = 0x200
ADC_OFR3_OFFSET3_10 = 0x400
ADC_OFR3_OFFSET3_11 = 0x800
ADC_OFR3_OFFSET3_CH = 0x7C000000
ADC_OFR3_OFFSET3_CH_0 = 0x4000000
ADC_OFR3_OFFSET3_CH_1 = 0x8000000
ADC_OFR3_OFFSET3_CH_2 = 0x10000000
ADC_OFR3_OFFSET3_CH_3 = 0x20000000
ADC_OFR3_OFFSET3_CH_4 = 0x40000000
ADC_OFR3_OFFSET3_EN = 0x80000000
ADC_OFR4_OFFSET4 = 0xFFF
ADC_OFR4_OFFSET4_0 = 0x1
ADC_OFR4_OFFSET4_1 = 0x2
ADC_OFR4_OFFSET4_2 = 0x4
ADC_OFR4_OFFSET4_3 = 0x8
ADC_OFR4_OFFSET4_4 = 0x10
ADC_OFR4_OFFSET4_5 = 0x20
ADC_OFR4_OFFSET4_6 = 0x40
ADC_OFR4_OFFSET4_7 = 0x80
ADC_OFR4_OFFSET4_8 = 0x100
ADC_OFR4_OFFSET4_9 = 0x200
ADC_OFR4_OFFSET4_10 = 0x400
ADC_OFR4_OFFSET4_11 = 0x800
ADC_OFR4_OFFSET4_CH = 0x7C000000
ADC_OFR4_OFFSET4_CH_0 = 0x4000000
ADC_OFR4_OFFSET4_CH_1 = 0x8000000
ADC_OFR4_OFFSET4_CH_2 = 0x10000000
ADC_OFR4_OFFSET4_CH_3 = 0x20000000
ADC_OFR4_OFFSET4_CH_4 = 0x40000000
ADC_OFR4_OFFSET4_EN = 0x80000000
ADC_JDR1_JDATA = 0xFFFF
ADC_JDR1_JDATA_0 = 0x1
ADC_JDR1_JDATA_1 = 0x2
ADC_JDR1_JDATA_2 = 0x4
ADC_JDR1_JDATA_3 = 0x8
ADC_JDR1_JDATA_4 = 0x10
ADC_JDR1_JDATA_5 = 0x20
ADC_JDR1_JDATA_6 = 0x40
ADC_JDR1_JDATA_7 = 0x80
ADC_JDR1_JDATA_8 = 0x100
ADC_JDR1_JDATA_9 = 0x200
ADC_JDR1_JDATA_10 = 0x400
ADC_JDR1_JDATA_11 = 0x800
ADC_JDR1_JDATA_12 = 0x1000
ADC_JDR1_JDATA_13 = 0x2000
ADC_JDR1_JDATA_14 = 0x4000
ADC_JDR1_JDATA_15 = 0x8000
ADC_JDR2_JDATA = 0xFFFF
ADC_JDR2_JDATA_0 = 0x1
ADC_JDR2_JDATA_1 = 0x2
ADC_JDR2_JDATA_2 = 0x4
ADC_JDR2_JDATA_3 = 0x8
ADC_JDR2_JDATA_4 = 0x10
ADC_JDR2_JDATA_5 = 0x20
ADC_JDR2_JDATA_6 = 0x40
ADC_JDR2_JDATA_7 = 0x80
ADC_JDR2_JDATA_8 = 0x100
ADC_JDR2_JDATA_9 = 0x200
ADC_JDR2_JDATA_10 = 0x400
ADC_JDR2_JDATA_11 = 0x800
ADC_JDR2_JDATA_12 = 0x1000
ADC_JDR2_JDATA_13 = 0x2000
ADC_JDR2_JDATA_14 = 0x4000
ADC_JDR2_JDATA_15 = 0x8000
ADC_JDR3_JDATA = 0xFFFF
ADC_JDR3_JDATA_0 = 0x1
ADC_JDR3_JDATA_1 = 0x2
ADC_JDR3_JDATA_2 = 0x4
ADC_JDR3_JDATA_3 = 0x8
ADC_JDR3_JDATA_4 = 0x10
ADC_JDR3_JDATA_5 = 0x20
ADC_JDR3_JDATA_6 = 0x40
ADC_JDR3_JDATA_7 = 0x80
ADC_JDR3_JDATA_8 = 0x100
ADC_JDR3_JDATA_9 = 0x200
ADC_JDR3_JDATA_10 = 0x400
ADC_JDR3_JDATA_11 = 0x800
ADC_JDR3_JDATA_12 = 0x1000
ADC_JDR3_JDATA_13 = 0x2000
ADC_JDR3_JDATA_14 = 0x4000
ADC_JDR3_JDATA_15 = 0x8000
ADC_JDR4_JDATA = 0xFFFF
ADC_JDR4_JDATA_0 = 0x1
ADC_JDR4_JDATA_1 = 0x2
ADC_JDR4_JDATA_2 = 0x4
ADC_JDR4_JDATA_3 = 0x8
ADC_JDR4_JDATA_4 = 0x10
ADC_JDR4_JDATA_5 = 0x20
ADC_JDR4_JDATA_6 = 0x40
ADC_JDR4_JDATA_7 = 0x80
ADC_JDR4_JDATA_8 = 0x100
ADC_JDR4_JDATA_9 = 0x200
ADC_JDR4_JDATA_10 = 0x400
ADC_JDR4_JDATA_11 = 0x800
ADC_JDR4_JDATA_12 = 0x1000
ADC_JDR4_JDATA_13 = 0x2000
ADC_JDR4_JDATA_14 = 0x4000
ADC_JDR4_JDATA_15 = 0x8000
ADC_AWD2CR_AWD2CH = 0x7FFFE
ADC_AWD2CR_AWD2CH_0 = 0x2
ADC_AWD2CR_AWD2CH_1 = 0x4
ADC_AWD2CR_AWD2CH_2 = 0x8
ADC_AWD2CR_AWD2CH_3 = 0x10
ADC_AWD2CR_AWD2CH_4 = 0x20
ADC_AWD2CR_AWD2CH_5 = 0x40
ADC_AWD2CR_AWD2CH_6 = 0x80
ADC_AWD2CR_AWD2CH_7 = 0x100
ADC_AWD2CR_AWD2CH_8 = 0x200
ADC_AWD2CR_AWD2CH_9 = 0x400
ADC_AWD2CR_AWD2CH_10 = 0x800
ADC_AWD2CR_AWD2CH_11 = 0x1000
ADC_AWD2CR_AWD2CH_12 = 0x2000
ADC_AWD2CR_AWD2CH_13 = 0x4000
ADC_AWD2CR_AWD2CH_14 = 0x8000
ADC_AWD2CR_AWD2CH_15 = 0x10000
ADC_AWD2CR_AWD2CH_16 = 0x20000
ADC_AWD2CR_AWD2CH_17 = 0x30000
ADC_AWD3CR_AWD3CH = 0x7FFFE
ADC_AWD3CR_AWD3CH_0 = 0x2
ADC_AWD3CR_AWD3CH_1 = 0x4
ADC_AWD3CR_AWD3CH_2 = 0x8
ADC_AWD3CR_AWD3CH_3 = 0x10
ADC_AWD3CR_AWD3CH_4 = 0x20
ADC_AWD3CR_AWD3CH_5 = 0x40
ADC_AWD3CR_AWD3CH_6 = 0x80
ADC_AWD3CR_AWD3CH_7 = 0x100
ADC_AWD3CR_AWD3CH_8 = 0x200
ADC_AWD3CR_AWD3CH_9 = 0x400
ADC_AWD3CR_AWD3CH_10 = 0x800
ADC_AWD3CR_AWD3CH_11 = 0x1000
ADC_AWD3CR_AWD3CH_12 = 0x2000
ADC_AWD3CR_AWD3CH_13 = 0x4000
ADC_AWD3CR_AWD3CH_14 = 0x8000
ADC_AWD3CR_AWD3CH_15 = 0x10000
ADC_AWD3CR_AWD3CH_16 = 0x20000
ADC_AWD3CR_AWD3CH_17 = 0x30000
ADC_DIFSEL_DIFSEL = 0x7FFFE
ADC_DIFSEL_DIFSEL_0 = 0x2
ADC_DIFSEL_DIFSEL_1 = 0x4
ADC_DIFSEL_DIFSEL_2 = 0x8
ADC_DIFSEL_DIFSEL_3 = 0x10
ADC_DIFSEL_DIFSEL_4 = 0x20
ADC_DIFSEL_DIFSEL_5 = 0x40
ADC_DIFSEL_DIFSEL_6 = 0x80
ADC_DIFSEL_DIFSEL_7 = 0x100
ADC_DIFSEL_DIFSEL_8 = 0x200
ADC_DIFSEL_DIFSEL_9 = 0x400
ADC_DIFSEL_DIFSEL_10 = 0x800
ADC_DIFSEL_DIFSEL_11 = 0x1000
ADC_DIFSEL_DIFSEL_12 = 0x2000
ADC_DIFSEL_DIFSEL_13 = 0x4000
ADC_DIFSEL_DIFSEL_14 = 0x8000
ADC_DIFSEL_DIFSEL_15 = 0x10000
ADC_DIFSEL_DIFSEL_16 = 0x20000
ADC_DIFSEL_DIFSEL_17 = 0x30000
ADC_CALFACT_CALFACT_S = 0x7F
ADC_CALFACT_CALFACT_S_0 = 0x1
ADC_CALFACT_CALFACT_S_1 = 0x2
ADC_CALFACT_CALFACT_S_2 = 0x4
ADC_CALFACT_CALFACT_S_3 = 0x8
ADC_CALFACT_CALFACT_S_4 = 0x10
ADC_CALFACT_CALFACT_S_5 = 0x20
ADC_CALFACT_CALFACT_S_6 = 0x40
ADC_CALFACT_CALFACT_D = 0x7F0000
ADC_CALFACT_CALFACT_D_0 = 0x10000
ADC_CALFACT_CALFACT_D_1 = 0x20000
ADC_CALFACT_CALFACT_D_2 = 0x40000
ADC_CALFACT_CALFACT_D_3 = 0x80000
ADC_CALFACT_CALFACT_D_4 = 0x100000
ADC_CALFACT_CALFACT_D_5 = 0x200000
ADC_CALFACT_CALFACT_D_6 = 0x400000
ADC12_CSR_ADRDY_MST = 0x1
ADC12_CSR_ADRDY_EOSMP_MST = 0x2
ADC12_CSR_ADRDY_EOC_MST = 0x4
ADC12_CSR_ADRDY_EOS_MST = 0x8
ADC12_CSR_ADRDY_OVR_MST = 0x10
ADC12_CSR_ADRDY_JEOC_MST = 0x20
ADC12_CSR_ADRDY_JEOS_MST = 0x40
ADC12_CSR_AWD1_MST = 0x80
ADC12_CSR_AWD2_MST = 0x100
ADC12_CSR_AWD3_MST = 0x200
ADC12_CSR_JQOVF_MST = 0x400
ADC12_CSR_ADRDY_SLV = 0x10000
ADC12_CSR_ADRDY_EOSMP_SLV = 0x20000
ADC12_CSR_ADRDY_EOC_SLV = 0x40000
ADC12_CSR_ADRDY_EOS_SLV = 0x80000
ADC12_CSR_ADRDY_OVR_SLV = 0x100000
ADC12_CSR_ADRDY_JEOC_SLV = 0x200000
ADC12_CSR_ADRDY_JEOS_SLV = 0x400000
ADC12_CSR_AWD1_SLV = 0x800000
ADC12_CSR_AWD2_SLV = 0x1000000
ADC12_CSR_AWD3_SLV = 0x2000000
ADC12_CSR_JQOVF_SLV = 0x4000000
ADC34_CSR_ADRDY_MST = 0x1
ADC34_CSR_ADRDY_EOSMP_MST = 0x2
ADC34_CSR_ADRDY_EOC_MST = 0x4
ADC34_CSR_ADRDY_EOS_MST = 0x8
ADC34_CSR_ADRDY_OVR_MST = 0x10
ADC34_CSR_ADRDY_JEOC_MST = 0x20
ADC34_CSR_ADRDY_JEOS_MST = 0x40
ADC34_CSR_AWD1_MST = 0x80
ADC34_CSR_AWD2_MST = 0x100
ADC34_CSR_AWD3_MST = 0x200
ADC34_CSR_JQOVF_MST = 0x400
ADC34_CSR_ADRDY_SLV = 0x10000
ADC34_CSR_ADRDY_EOSMP_SLV = 0x20000
ADC34_CSR_ADRDY_EOC_SLV = 0x40000
ADC34_CSR_ADRDY_EOS_SLV = 0x80000
ADC12_CSR_ADRDY_OVR_SLV = 0x100000
ADC34_CSR_ADRDY_JEOC_SLV = 0x200000
ADC34_CSR_ADRDY_JEOS_SLV = 0x400000
ADC34_CSR_AWD1_SLV = 0x800000
ADC34_CSR_AWD2_SLV = 0x1000000
ADC34_CSR_AWD3_SLV = 0x2000000
ADC34_CSR_JQOVF_SLV = 0x4000000
ADC12_CCR_MULTI = 0x1F
ADC12_CCR_MULTI_0 = 0x1
ADC12_CCR_MULTI_1 = 0x2
ADC12_CCR_MULTI_2 = 0x4
ADC12_CCR_MULTI_3 = 0x8
ADC12_CCR_MULTI_4 = 0x10
ADC12_CCR_DELAY = 0xF00
ADC12_CCR_DELAY_0 = 0x100
ADC12_CCR_DELAY_1 = 0x200
ADC12_CCR_DELAY_2 = 0x400
ADC12_CCR_DELAY_3 = 0x800
ADC12_CCR_DMACFG = 0x2000
ADC12_CCR_MDMA = 0xC000
ADC12_CCR_MDMA_0 = 0x4000
ADC12_CCR_MDMA_1 = 0x8000
ADC12_CCR_CKMODE = 0x30000
ADC12_CCR_CKMODE_0 = 0x10000
ADC12_CCR_CKMODE_1 = 0x20000
ADC12_CCR_VREFEN = 0x400000
ADC12_CCR_TSEN = 0x800000
ADC12_CCR_VBATEN = 0x1000000
ADC34_CCR_MULTI = 0x1F
ADC34_CCR_MULTI_0 = 0x1
ADC34_CCR_MULTI_1 = 0x2
ADC34_CCR_MULTI_2 = 0x4
ADC34_CCR_MULTI_3 = 0x8
ADC34_CCR_MULTI_4 = 0x10
ADC34_CCR_DELAY = 0xF00
ADC34_CCR_DELAY_0 = 0x100
ADC34_CCR_DELAY_1 = 0x200
ADC34_CCR_DELAY_2 = 0x400
ADC34_CCR_DELAY_3 = 0x800
ADC34_CCR_DMACFG = 0x2000
ADC34_CCR_MDMA = 0xC000
ADC34_CCR_MDMA_0 = 0x4000
ADC34_CCR_MDMA_1 = 0x8000
ADC34_CCR_CKMODE = 0x30000
ADC34_CCR_CKMODE_0 = 0x10000
ADC34_CCR_CKMODE_1 = 0x20000
ADC34_CCR_VREFEN = 0x400000
ADC34_CCR_TSEN = 0x800000
ADC34_CCR_VBATEN = 0x1000000
ADC12_CDR_RDATA_MST = 0xFFFF
ADC12_CDR_RDATA_MST_0 = 0x1
ADC12_CDR_RDATA_MST_1 = 0x2
ADC12_CDR_RDATA_MST_2 = 0x4
ADC12_CDR_RDATA_MST_3 = 0x8
ADC12_CDR_RDATA_MST_4 = 0x10
ADC12_CDR_RDATA_MST_5 = 0x20
ADC12_CDR_RDATA_MST_6 = 0x40
ADC12_CDR_RDATA_MST_7 = 0x80
ADC12_CDR_RDATA_MST_8 = 0x100
ADC12_CDR_RDATA_MST_9 = 0x200
ADC12_CDR_RDATA_MST_10 = 0x400
ADC12_CDR_RDATA_MST_11 = 0x800
ADC12_CDR_RDATA_MST_12 = 0x1000
ADC12_CDR_RDATA_MST_13 = 0x2000
ADC12_CDR_RDATA_MST_14 = 0x4000
ADC12_CDR_RDATA_MST_15 = 0x8000
ADC12_CDR_RDATA_SLV = 0xFFFF0000
ADC12_CDR_RDATA_SLV_0 = 0x10000
ADC12_CDR_RDATA_SLV_1 = 0x20000
ADC12_CDR_RDATA_SLV_2 = 0x40000
ADC12_CDR_RDATA_SLV_3 = 0x80000
ADC12_CDR_RDATA_SLV_4 = 0x100000
ADC12_CDR_RDATA_SLV_5 = 0x200000
ADC12_CDR_RDATA_SLV_6 = 0x400000
ADC12_CDR_RDATA_SLV_7 = 0x800000
ADC12_CDR_RDATA_SLV_8 = 0x1000000
ADC12_CDR_RDATA_SLV_9 = 0x2000000
ADC12_CDR_RDATA_SLV_10 = 0x4000000
ADC12_CDR_RDATA_SLV_11 = 0x8000000
ADC12_CDR_RDATA_SLV_12 = 0x10000000
ADC12_CDR_RDATA_SLV_13 = 0x20000000
ADC12_CDR_RDATA_SLV_14 = 0x40000000
ADC12_CDR_RDATA_SLV_15 = 0x80000000
ADC34_CDR_RDATA_MST = 0xFFFF
ADC34_CDR_RDATA_MST_0 = 0x1
ADC34_CDR_RDATA_MST_1 = 0x2
ADC34_CDR_RDATA_MST_2 = 0x4
ADC34_CDR_RDATA_MST_3 = 0x8
ADC34_CDR_RDATA_MST_4 = 0x10
ADC34_CDR_RDATA_MST_5 = 0x20
ADC34_CDR_RDATA_MST_6 = 0x40
ADC34_CDR_RDATA_MST_7 = 0x80
ADC34_CDR_RDATA_MST_8 = 0x100
ADC34_CDR_RDATA_MST_9 = 0x200
ADC34_CDR_RDATA_MST_10 = 0x400
ADC34_CDR_RDATA_MST_11 = 0x800
ADC34_CDR_RDATA_MST_12 = 0x1000
ADC34_CDR_RDATA_MST_13 = 0x2000
ADC34_CDR_RDATA_MST_14 = 0x4000
ADC34_CDR_RDATA_MST_15 = 0x8000
ADC34_CDR_RDATA_SLV = 0xFFFF0000
ADC34_CDR_RDATA_SLV_0 = 0x10000
ADC34_CDR_RDATA_SLV_1 = 0x20000
ADC34_CDR_RDATA_SLV_2 = 0x40000
ADC34_CDR_RDATA_SLV_3 = 0x80000
ADC34_CDR_RDATA_SLV_4 = 0x100000
ADC34_CDR_RDATA_SLV_5 = 0x200000
ADC34_CDR_RDATA_SLV_6 = 0x400000
ADC34_CDR_RDATA_SLV_7 = 0x800000
ADC34_CDR_RDATA_SLV_8 = 0x1000000
ADC34_CDR_RDATA_SLV_9 = 0x2000000
ADC34_CDR_RDATA_SLV_10 = 0x4000000
ADC34_CDR_RDATA_SLV_11 = 0x8000000
ADC34_CDR_RDATA_SLV_12 = 0x10000000
ADC34_CDR_RDATA_SLV_13 = 0x20000000
ADC34_CDR_RDATA_SLV_14 = 0x40000000
ADC34_CDR_RDATA_SLV_15 = 0x80000000
COMP1_CSR_COMP1EN = 0x1
COMP1_CSR_COMP1SW1 = 0x2
COMP1_CSR_COMP1MODE = 0xC
COMP1_CSR_COMP1MODE_0 = 0x4
COMP1_CSR_COMP1MODE_1 = 0x8
COMP1_CSR_COMP1INSEL = 0x70
COMP1_CSR_COMP1INSEL_0 = 0x10
COMP1_CSR_COMP1INSEL_1 = 0x20
COMP1_CSR_COMP1INSEL_2 = 0x40
COMP1_CSR_COMP1NONINSEL = 0x80
COMP1_CSR_COMP1OUTSEL = 0x3C00
COMP1_CSR_COMP1OUTSEL_0 = 0x400
COMP1_CSR_COMP1OUTSEL_1 = 0x800
COMP1_CSR_COMP1OUTSEL_2 = 0x1000
COMP1_CSR_COMP1OUTSEL_3 = 0x2000
COMP1_CSR_COMP1POL = 0x8000
COMP1_CSR_COMP1HYST = 0x30000
COMP1_CSR_COMP1HYST_0 = 0x10000
COMP1_CSR_COMP1HYST_1 = 0x20000
COMP1_CSR_COMP1BLANKING = 0xC0000
COMP1_CSR_COMP1BLANKING_0 = 0x40000
COMP1_CSR_COMP1BLANKING_1 = 0x80000
COMP1_CSR_COMP1BLANKING_2 = 0x100000
COMP1_CSR_COMP1OUT = 0x40000000
COMP1_CSR_COMP1LOCK = 0x80000000
COMP2_CSR_COMP2EN = 0x1
COMP2_CSR_COMP2MODE = 0xC
COMP2_CSR_COMP2MODE_0 = 0x4
COMP2_CSR_COMP2MODE_1 = 0x8
COMP2_CSR_COMP2INSEL = 0x70
COMP2_CSR_COMP2INSEL_0 = 0x10
COMP2_CSR_COMP2INSEL_1 = 0x20
COMP2_CSR_COMP2INSEL_2 = 0x40
COMP2_CSR_COMP2NONINSEL = 0x80
COMP2_CSR_COMP2WNDWEN = 0x200
COMP2_CSR_COMP2OUTSEL = 0x3C00
COMP2_CSR_COMP2OUTSEL_0 = 0x400
COMP2_CSR_COMP2OUTSEL_1 = 0x800
COMP2_CSR_COMP2OUTSEL_2 = 0x1000
COMP2_CSR_COMP2OUTSEL_3 = 0x2000
COMP2_CSR_COMP2POL = 0x8000
COMP2_CSR_COMP2HYST = 0x30000
COMP2_CSR_COMP2HYST_0 = 0x10000
COMP2_CSR_COMP2HYST_1 = 0x20000
COMP2_CSR_COMP2BLANKING = 0xC0000
COMP2_CSR_COMP2BLANKING_0 = 0x40000
COMP2_CSR_COMP2BLANKING_1 = 0x80000
COMP2_CSR_COMP2BLANKING_2 = 0x100000
COMP2_CSR_COMP2OUT = 0x40000000
COMP2_CSR_COMP2LOCK = 0x80000000
COMP3_CSR_COMP3EN = 0x1
COMP3_CSR_COMP3MODE = 0xC
COMP3_CSR_COMP3MODE_0 = 0x4
COMP3_CSR_COMP3MODE_1 = 0x8
COMP3_CSR_COMP3INSEL = 0x70
COMP3_CSR_COMP3INSEL_0 = 0x10
COMP3_CSR_COMP3INSEL_1 = 0x20
COMP3_CSR_COMP3INSEL_2 = 0x40
COMP3_CSR_COMP3NONINSEL = 0x80
COMP3_CSR_COMP3OUTSEL = 0x3C00
COMP3_CSR_COMP3OUTSEL_0 = 0x400
COMP3_CSR_COMP3OUTSEL_1 = 0x800
COMP3_CSR_COMP3OUTSEL_2 = 0x1000
COMP3_CSR_COMP3OUTSEL_3 = 0x2000
COMP3_CSR_COMP3POL = 0x8000
COMP3_CSR_COMP3HYST = 0x30000
COMP3_CSR_COMP3HYST_0 = 0x10000
COMP3_CSR_COMP3HYST_1 = 0x20000
COMP3_CSR_COMP3BLANKING = 0xC0000
COMP3_CSR_COMP3BLANKING_0 = 0x40000
COMP3_CSR_COMP3BLANKING_1 = 0x80000
COMP3_CSR_COMP3BLANKING_2 = 0x100000
COMP3_CSR_COMP3OUT = 0x40000000
COMP3_CSR_COMP3LOCK = 0x80000000
COMP4_CSR_COMP4EN = 0x1
COMP4_CSR_COMP4MODE = 0xC
COMP4_CSR_COMP4MODE_0 = 0x4
COMP4_CSR_COMP4MODE_1 = 0x8
COMP4_CSR_COMP4INSEL = 0x70
COMP4_CSR_COMP4INSEL_0 = 0x10
COMP4_CSR_COMP4INSEL_1 = 0x20
COMP4_CSR_COMP4INSEL_2 = 0x40
COMP4_CSR_COMP4NONINSEL = 0x80
COMP4_CSR_COMP4WNDWEN = 0x200
COMP4_CSR_COMP4OUTSEL = 0x3C00
COMP4_CSR_COMP4OUTSEL_0 = 0x400
COMP4_CSR_COMP4OUTSEL_1 = 0x800
COMP4_CSR_COMP4OUTSEL_2 = 0x1000
COMP4_CSR_COMP4OUTSEL_3 = 0x2000
COMP4_CSR_COMP4POL = 0x8000
COMP4_CSR_COMP4HYST = 0x30000
COMP4_CSR_COMP4HYST_0 = 0x10000
COMP4_CSR_COMP4HYST_1 = 0x20000
COMP4_CSR_COMP4BLANKING = 0xC0000
COMP4_CSR_COMP4BLANKING_0 = 0x40000
COMP4_CSR_COMP4BLANKING_1 = 0x80000
COMP4_CSR_COMP4BLANKING_2 = 0x100000
COMP4_CSR_COMP4OUT = 0x40000000
COMP4_CSR_COMP4LOCK = 0x80000000
COMP5_CSR_COMP5EN = 0x1
COMP5_CSR_COMP5MODE = 0xC
COMP5_CSR_COMP5MODE_0 = 0x4
COMP5_CSR_COMP5MODE_1 = 0x8
COMP5_CSR_COMP5INSEL = 0x70
COMP5_CSR_COMP5INSEL_0 = 0x10
COMP5_CSR_COMP5INSEL_1 = 0x20
COMP5_CSR_COMP5INSEL_2 = 0x40
COMP5_CSR_COMP5NONINSEL = 0x80
COMP5_CSR_COMP5OUTSEL = 0x3C00
COMP5_CSR_COMP5OUTSEL_0 = 0x400
COMP5_CSR_COMP5OUTSEL_1 = 0x800
COMP5_CSR_COMP5OUTSEL_2 = 0x1000
COMP5_CSR_COMP5OUTSEL_3 = 0x2000
COMP5_CSR_COMP5POL = 0x8000
COMP5_CSR_COMP5HYST = 0x30000
COMP5_CSR_COMP5HYST_0 = 0x10000
COMP5_CSR_COMP5HYST_1 = 0x20000
COMP5_CSR_COMP5BLANKING = 0xC0000
COMP5_CSR_COMP5BLANKING_0 = 0x40000
COMP5_CSR_COMP5BLANKING_1 = 0x80000
COMP5_CSR_COMP5BLANKING_2 = 0x100000
COMP5_CSR_COMP5OUT = 0x40000000
COMP5_CSR_COMP5LOCK = 0x80000000
COMP6_CSR_COMP6EN = 0x1
COMP6_CSR_COMP6MODE = 0xC
COMP6_CSR_COMP6MODE_0 = 0x4
COMP6_CSR_COMP6MODE_1 = 0x8
COMP6_CSR_COMP6INSEL = 0x70
COMP6_CSR_COMP6INSEL_0 = 0x10
COMP6_CSR_COMP6INSEL_1 = 0x20
COMP6_CSR_COMP6INSEL_2 = 0x40
COMP6_CSR_COMP6NONINSEL = 0x80
COMP6_CSR_COMP6WNDWEN = 0x200
COMP6_CSR_COMP6OUTSEL = 0x3C00
COMP6_CSR_COMP6OUTSEL_0 = 0x400
COMP6_CSR_COMP6OUTSEL_1 = 0x800
COMP6_CSR_COMP6OUTSEL_2 = 0x1000
COMP6_CSR_COMP6OUTSEL_3 = 0x2000
COMP6_CSR_COMP6POL = 0x8000
COMP6_CSR_COMP6HYST = 0x30000
COMP6_CSR_COMP6HYST_0 = 0x10000
COMP6_CSR_COMP6HYST_1 = 0x20000
COMP6_CSR_COMP6BLANKING = 0xC0000
COMP6_CSR_COMP6BLANKING_0 = 0x40000
COMP6_CSR_COMP6BLANKING_1 = 0x80000
COMP6_CSR_COMP6BLANKING_2 = 0x100000
COMP6_CSR_COMP6OUT = 0x40000000
COMP6_CSR_COMP6LOCK = 0x80000000
COMP7_CSR_COMP7EN = 0x1
COMP7_CSR_COMP7MODE = 0xC
COMP7_CSR_COMP7MODE_0 = 0x4
COMP7_CSR_COMP7MODE_1 = 0x8
COMP7_CSR_COMP7INSEL = 0x70
COMP7_CSR_COMP7INSEL_0 = 0x10
COMP7_CSR_COMP7INSEL_1 = 0x20
COMP7_CSR_COMP7INSEL_2 = 0x40
COMP7_CSR_COMP7NONINSEL = 0x80
COMP7_CSR_COMP7OUTSEL = 0x3C00
COMP7_CSR_COMP7OUTSEL_0 = 0x400
COMP7_CSR_COMP7OUTSEL_1 = 0x800
COMP7_CSR_COMP7OUTSEL_2 = 0x1000
COMP7_CSR_COMP7OUTSEL_3 = 0x2000
COMP7_CSR_COMP7POL = 0x8000
COMP7_CSR_COMP7HYST = 0x30000
COMP7_CSR_COMP7HYST_0 = 0x10000
COMP7_CSR_COMP7HYST_1 = 0x20000
COMP7_CSR_COMP7BLANKING = 0xC0000
COMP7_CSR_COMP7BLANKING_0 = 0x40000
COMP7_CSR_COMP7BLANKING_1 = 0x80000
COMP7_CSR_COMP7BLANKING_2 = 0x100000
COMP7_CSR_COMP7OUT = 0x40000000
COMP7_CSR_COMP7LOCK = 0x80000000
COMP_CSR_COMPxEN = 0x1
COMP_CSR_COMP1SW1 = 0x2
COMP_CSR_COMPxMODE = 0xC
COMP_CSR_COMPxMODE_0 = 0x4
COMP_CSR_COMPxMODE_1 = 0x8
COMP_CSR_COMPxINSEL = 0x70
COMP_CSR_COMPxINSEL_0 = 0x10
COMP_CSR_COMPxINSEL_1 = 0x20
COMP_CSR_COMPxINSEL_2 = 0x40
COMP_CSR_COMPxNONINSEL = 0x80
COMP_CSR_COMPxWNDWEN = 0x200
COMP_CSR_COMPxOUTSEL = 0x3C00
COMP_CSR_COMPxOUTSEL_0 = 0x400
COMP_CSR_COMPxOUTSEL_1 = 0x800
COMP_CSR_COMPxOUTSEL_2 = 0x1000
COMP_CSR_COMPxOUTSEL_3 = 0x2000
COMP_CSR_COMPxPOL = 0x8000
COMP_CSR_COMPxHYST = 0x30000
COMP_CSR_COMPxHYST_0 = 0x10000
COMP_CSR_COMPxHYST_1 = 0x20000
COMP_CSR_COMPxBLANKING = 0xC0000
COMP_CSR_COMPxBLANKING_0 = 0x40000
COMP_CSR_COMPxBLANKING_1 = 0x80000
COMP_CSR_COMPxBLANKING_2 = 0x100000
COMP_CSR_COMPxOUT = 0x40000000
COMP_CSR_COMPxLOCK = 0x80000000
OPAMP1_CSR_OPAMP1EN = 0x1
OPAMP1_CSR_FORCEVP = 0x2
OPAMP1_CSR_VPSEL = 0xC
OPAMP1_CSR_VPSEL_0 = 0x4
OPAMP1_CSR_VPSEL_1 = 0x8
OPAMP1_CSR_VMSEL = 0x60
OPAMP1_CSR_VMSEL_0 = 0x20
OPAMP1_CSR_VMSEL_1 = 0x40
OPAMP1_CSR_TCMEN = 0x80
OPAMP1_CSR_VMSSEL = 0x100
OPAMP1_CSR_VPSSEL = 0x600
OPAMP1_CSR_VPSSEL_0 = 0x200
OPAMP1_CSR_VPSSEL_1 = 0x400
OPAMP1_CSR_CALON = 0x800
OPAMP1_CSR_CALSEL = 0x3000
OPAMP1_CSR_CALSEL_0 = 0x1000
OPAMP1_CSR_CALSEL_1 = 0x2000
OPAMP1_CSR_PGGAIN = 0x3C000
OPAMP1_CSR_PGGAIN_0 = 0x4000
OPAMP1_CSR_PGGAIN_1 = 0x8000
OPAMP1_CSR_PGGAIN_2 = 0x10000
OPAMP1_CSR_PGGAIN_3 = 0x20000
OPAMP1_CSR_USERTRIM = 0x40000
OPAMP1_CSR_TRIMOFFSETP = 0xF80000
OPAMP1_CSR_TRIMOFFSETN = 0x1F000000
OPAMP1_CSR_TSTREF = 0x20000000
OPAMP1_CSR_OUTCAL = 0x40000000
OPAMP1_CSR_LOCK = 0x80000000
OPAMP2_CSR_OPAMP2EN = 0x1
OPAMP2_CSR_FORCEVP = 0x2
OPAMP2_CSR_VPSEL = 0xC
OPAMP2_CSR_VPSEL_0 = 0x4
OPAMP2_CSR_VPSEL_1 = 0x8
OPAMP2_CSR_VMSEL = 0x60
OPAMP2_CSR_VMSEL_0 = 0x20
OPAMP2_CSR_VMSEL_1 = 0x40
OPAMP2_CSR_TCMEN = 0x80
OPAMP2_CSR_VMSSEL = 0x100
OPAMP2_CSR_VPSSEL = 0x600
OPAMP2_CSR_VPSSEL_0 = 0x200
OPAMP2_CSR_VPSSEL_1 = 0x400
OPAMP2_CSR_CALON = 0x800
OPAMP2_CSR_CALSEL = 0x3000
OPAMP2_CSR_CALSEL_0 = 0x1000
OPAMP2_CSR_CALSEL_1 = 0x2000
OPAMP2_CSR_PGGAIN = 0x3C000
OPAMP2_CSR_PGGAIN_0 = 0x4000
OPAMP2_CSR_PGGAIN_1 = 0x8000
OPAMP2_CSR_PGGAIN_2 = 0x10000
OPAMP2_CSR_PGGAIN_3 = 0x20000
OPAMP2_CSR_USERTRIM = 0x40000
OPAMP2_CSR_TRIMOFFSETP = 0xF80000
OPAMP2_CSR_TRIMOFFSETN = 0x1F000000
OPAMP2_CSR_TSTREF = 0x20000000
OPAMP2_CSR_OUTCAL = 0x40000000
OPAMP2_CSR_LOCK = 0x80000000
OPAMP3_CSR_OPAMP3EN = 0x1
OPAMP3_CSR_FORCEVP = 0x2
OPAMP3_CSR_VPSEL = 0xC
OPAMP3_CSR_VPSEL_0 = 0x4
OPAMP3_CSR_VPSEL_1 = 0x8
OPAMP3_CSR_VMSEL = 0x60
OPAMP3_CSR_VMSEL_0 = 0x20
OPAMP3_CSR_VMSEL_1 = 0x40
OPAMP3_CSR_TCMEN = 0x80
OPAMP3_CSR_VMSSEL = 0x100
OPAMP3_CSR_VPSSEL = 0x600
OPAMP3_CSR_VPSSEL_0 = 0x200
OPAMP3_CSR_VPSSEL_1 = 0x400
OPAMP3_CSR_CALON = 0x800
OPAMP3_CSR_CALSEL = 0x3000
OPAMP3_CSR_CALSEL_0 = 0x1000
OPAMP3_CSR_CALSEL_1 = 0x2000
OPAMP3_CSR_PGGAIN = 0x3C000
OPAMP3_CSR_PGGAIN_0 = 0x4000
OPAMP3_CSR_PGGAIN_1 = 0x8000
OPAMP3_CSR_PGGAIN_2 = 0x10000
OPAMP3_CSR_PGGAIN_3 = 0x20000
OPAMP3_CSR_USERTRIM = 0x40000
OPAMP3_CSR_TRIMOFFSETP = 0xF80000
OPAMP3_CSR_TRIMOFFSETN = 0x1F000000
OPAMP3_CSR_TSTREF = 0x20000000
OPAMP3_CSR_OUTCAL = 0x40000000
OPAMP3_CSR_LOCK = 0x80000000
OPAMP4_CSR_OPAMP4EN = 0x1
OPAMP4_CSR_FORCEVP = 0x2
OPAMP4_CSR_VPSEL = 0xC
OPAMP4_CSR_VPSEL_0 = 0x4
OPAMP4_CSR_VPSEL_1 = 0x8
OPAMP4_CSR_VMSEL = 0x60
OPAMP4_CSR_VMSEL_0 = 0x20
OPAMP4_CSR_VMSEL_1 = 0x40
OPAMP4_CSR_TCMEN = 0x80
OPAMP4_CSR_VMSSEL = 0x100
OPAMP4_CSR_VPSSEL = 0x600
OPAMP4_CSR_VPSSEL_0 = 0x200
OPAMP4_CSR_VPSSEL_1 = 0x400
OPAMP4_CSR_CALON = 0x800
OPAMP4_CSR_CALSEL = 0x3000
OPAMP4_CSR_CALSEL_0 = 0x1000
OPAMP4_CSR_CALSEL_1 = 0x2000
OPAMP4_CSR_PGGAIN = 0x3C000
OPAMP4_CSR_PGGAIN_0 = 0x4000
OPAMP4_CSR_PGGAIN_1 = 0x8000
OPAMP4_CSR_PGGAIN_2 = 0x10000
OPAMP4_CSR_PGGAIN_3 = 0x20000
OPAMP4_CSR_USERTRIM = 0x40000
OPAMP4_CSR_TRIMOFFSETP = 0xF80000
OPAMP4_CSR_TRIMOFFSETN = 0x1F000000
OPAMP4_CSR_TSTREF = 0x20000000
OPAMP4_CSR_OUTCAL = 0x40000000
OPAMP4_CSR_LOCK = 0x80000000
OPAMP_CSR_OPAMPxEN = 0x1
OPAMP_CSR_FORCEVP = 0x2
OPAMP_CSR_VPSEL = 0xC
OPAMP_CSR_VPSEL_0 = 0x4
OPAMP_CSR_VPSEL_1 = 0x8
OPAMP_CSR_VMSEL = 0x60
OPAMP_CSR_VMSEL_0 = 0x20
OPAMP_CSR_VMSEL_1 = 0x40
OPAMP_CSR_TCMEN = 0x80
OPAMP_CSR_VMSSEL = 0x100
OPAMP_CSR_VPSSEL = 0x600
OPAMP_CSR_VPSSEL_0 = 0x200
OPAMP_CSR_VPSSEL_1 = 0x400
OPAMP_CSR_CALON = 0x800
OPAMP_CSR_CALSEL = 0x3000
OPAMP_CSR_CALSEL_0 = 0x1000
OPAMP_CSR_CALSEL_1 = 0x2000
OPAMP_CSR_PGGAIN = 0x3C000
OPAMP_CSR_PGGAIN_0 = 0x4000
OPAMP_CSR_PGGAIN_1 = 0x8000
OPAMP_CSR_PGGAIN_2 = 0x10000
OPAMP_CSR_PGGAIN_3 = 0x20000
OPAMP_CSR_USERTRIM = 0x40000
OPAMP_CSR_TRIMOFFSETP = 0xF80000
OPAMP_CSR_TRIMOFFSETN = 0x1F000000
OPAMP_CSR_TSTREF = 0x20000000
OPAMP_CSR_OUTCAL = 0x40000000
OPAMP_CSR_LOCK = 0x80000000
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
CRC_CR_POLSIZE = 0x18
CRC_CR_POLSIZE_0 = 0x8
CRC_CR_POLSIZE_1 = 0x10
CRC_CR_REV_IN = 0x60
CRC_CR_REV_IN_0 = 0x20
CRC_CR_REV_IN_1 = 0x40
CRC_CR_REV_OUT = 0x80
CRC_INIT_INIT = 0xFFFFFFFF
CRC_POL_POL = 0xFFFFFFFF
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
DBGMCU_APB1_FZ_DBG_TIM6_STOP = 0x10
DBGMCU_APB1_FZ_DBG_TIM7_STOP = 0x20
DBGMCU_APB1_FZ_DBG_RTC_STOP = 0x400
DBGMCU_APB1_FZ_DBG_WWDG_STOP = 0x800
DBGMCU_APB1_FZ_DBG_IWDG_STOP = 0x1000
DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT = 0x200000
DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT = 0x400000
DBGMCU_APB1_FZ_DBG_CAN1_STOP = 0x2000000
DBGMCU_APB2_FZ_DBG_TIM1_STOP = 0x1
DBGMCU_APB2_FZ_DBG_TIM8_STOP = 0x2
DBGMCU_APB2_FZ_DBG_TIM15_STOP = 0x4
DBGMCU_APB2_FZ_DBG_TIM16_STOP = 0x8
DBGMCU_APB2_FZ_DBG_TIM17_STOP = 0x10
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
EXTI_RTSR_TR20 = 0x100000
EXTI_RTSR_TR21 = 0x200000
EXTI_RTSR_TR22 = 0x400000
EXTI_RTSR_TR23 = 0x800000
EXTI_RTSR_TR24 = 0x1000000
EXTI_RTSR_TR25 = 0x2000000
EXTI_RTSR_TR26 = 0x4000000
EXTI_RTSR_TR27 = 0x8000000
EXTI_RTSR_TR28 = 0x10000000
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
EXTI_FTSR_TR20 = 0x100000
EXTI_FTSR_TR21 = 0x200000
EXTI_FTSR_TR22 = 0x400000
EXTI_FTSR_TR23 = 0x800000
EXTI_FTSR_TR24 = 0x1000000
EXTI_FTSR_TR25 = 0x2000000
EXTI_FTSR_TR26 = 0x4000000
EXTI_FTSR_TR27 = 0x8000000
EXTI_FTSR_TR28 = 0x10000000
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
EXTI_SWIER_SWIER20 = 0x100000
EXTI_SWIER_SWIER21 = 0x200000
EXTI_SWIER_SWIER22 = 0x400000
EXTI_SWIER_SWIER23 = 0x800000
EXTI_SWIER_SWIER24 = 0x1000000
EXTI_SWIER_SWIER25 = 0x2000000
EXTI_SWIER_SWIER26 = 0x4000000
EXTI_SWIER_SWIER27 = 0x8000000
EXTI_SWIER_SWIER28 = 0x10000000
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
EXTI_PR_PR20 = 0x100000
EXTI_PR_PR21 = 0x200000
EXTI_PR_PR22 = 0x400000
EXTI_PR_PR23 = 0x800000
EXTI_PR_PR24 = 0x1000000
EXTI_PR_PR25 = 0x2000000
EXTI_PR_PR26 = 0x4000000
EXTI_PR_PR27 = 0x8000000
EXTI_PR_PR28 = 0x10000000
FLASH_ACR_LATENCY = 0x3
FLASH_ACR_LATENCY_0 = 0x1
FLASH_ACR_LATENCY_1 = 0x2
FLASH_ACR_HLFCYA = 0x8
FLASH_ACR_PRFTBE = 0x10
FLASH_ACR_PRFTBS = 0x20
FLASH_KEYR_FKEYR = 0xFFFFFFFF
RDP_KEY = 0xA5
FLASH_KEY1 = 0x45670123
FLASH_KEY2 = 0xCDEF89AB
FLASH_OPTKEYR_OPTKEYR = 0xFFFFFFFF
FLASH_OPTKEY1 = 0x45670123
FLASH_OPTKEY2 = 0xCDEF89AB
FLASH_SR_BSY = 0x1
FLASH_SR_PGERR = 0x4
FLASH_SR_WRPERR = 0x10
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
FLASH_CR_OBL_LAUNCH = 0x2000
FLASH_AR_FAR = 0xFFFFFFFF
FLASH_OBR_OPTERR = 0x1
FLASH_OBR_RDPRT1 = 0x2
FLASH_OBR_RDPRT2 = 0x4
FLASH_OBR_USER = 0x3700
FLASH_OBR_IWDG_SW = 0x100
FLASH_OBR_nRST_STOP = 0x200
FLASH_OBR_nRST_STDBY = 0x400
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
PWR_CR_LPSDSR = 0x1
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
PWR_CSR_WUF = 0x1
PWR_CSR_SBF = 0x2
PWR_CSR_PVDO = 0x4
PWR_CSR_VREFINTRDYF = 0x8
PWR_CSR_EWUP1 = 0x100
PWR_CSR_EWUP2 = 0x200
PWR_CSR_EWUP3 = 0x400
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
RCC_CFGR_PLLSRC = 0x10000
RCC_CFGR_PLLXTPRE = 0x20000
RCC_CFGR_PLLMULL = 0x3C0000
RCC_CFGR_PLLMULL_0 = 0x40000
RCC_CFGR_PLLMULL_1 = 0x80000
RCC_CFGR_PLLMULL_2 = 0x100000
RCC_CFGR_PLLMULL_3 = 0x200000
RCC_CFGR_PLLSRC_HSI_Div2 = 0x0
RCC_CFGR_PLLSRC_PREDIV1 = 0x10000
RCC_CFGR_PLLXTPRE_PREDIV1 = 0x0
RCC_CFGR_PLLXTPRE_PREDIV1_Div2 = 0x20000
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
RCC_CFGR_I2SSRC = 0x800000
RCC_CFGR_MCO = 0x7000000
RCC_CFGR_MCO_0 = 0x1000000
RCC_CFGR_MCO_1 = 0x2000000
RCC_CFGR_MCO_2 = 0x4000000
RCC_CFGR_MCO_NOCLOCK = 0x0
RCC_CFGR_MCO_LSI = 0x2000000
RCC_CFGR_MCO_LSE = 0x3000000
RCC_CFGR_MCO_SYSCLK = 0x4000000
RCC_CFGR_MCO_HSI = 0x5000000
RCC_CFGR_MCO_HSE = 0x6000000
RCC_CFGR_MCO_PLL = 0x7000000
RCC_CFGR_MCOF = 0x10000000
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
RCC_APB2RSTR_SYSCFGRST = 0x1
RCC_APB2RSTR_TIM1RST = 0x200
RCC_APB2RSTR_SPI1RST = 0x1000
RCC_APB2RSTR_TIM8RST = 0x200
RCC_APB2RSTR_USART1RST = 0x4000
RCC_APB2RSTR_TIM15RST = 0x10000
RCC_APB2RSTR_TIM16RST = 0x20000
RCC_APB2RSTR_TIM17RST = 0x40000
RCC_APB1RSTR_TIM2RST = 0x1
RCC_APB1RSTR_TIM3RST = 0x2
RCC_APB1RSTR_TIM4RST = 0x4
RCC_APB1RSTR_TIM6RST = 0x10
RCC_APB1RSTR_TIM7RST = 0x20
RCC_APB1RSTR_WWDGRST = 0x800
RCC_APB1RSTR_SPI2RST = 0x4000
RCC_APB1RSTR_SPI3RST = 0x8000
RCC_APB1RSTR_USART2RST = 0x20000
RCC_APB1RSTR_USART3RST = 0x40000
RCC_APB1RSTR_UART4RST = 0x80000
RCC_APB1RSTR_UART5RST = 0x100000
RCC_APB1RSTR_I2C1RST = 0x200000
RCC_APB1RSTR_I2C2RST = 0x400000
RCC_APB1RSTR_USBRST = 0x800000
RCC_APB1RSTR_CAN1RST = 0x2000000
RCC_APB1RSTR_PWRRST = 0x10000000
RCC_APB1RSTR_DACRST = 0x20000000
RCC_AHBENR_DMA1EN = 0x1
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
RCC_AHBENR_TSEN = 0x1000000
RCC_AHBENR_ADC12EN = 0x10000000
RCC_AHBENR_ADC34EN = 0x20000000
RCC_APB2ENR_SYSCFGEN = 0x1
RCC_APB2ENR_TIM1EN = 0x800
RCC_APB2ENR_SPI1EN = 0x1000
RCC_APB2ENR_TIM8EN = 0x2000
RCC_APB2ENR_USART1EN = 0x4000
RCC_APB2ENR_TIM15EN = 0x10000
RCC_APB2ENR_TIM16EN = 0x20000
RCC_APB2ENR_TIM17EN = 0x40000
RCC_APB1ENR_TIM2EN = 0x1
RCC_APB1ENR_TIM3EN = 0x2
RCC_APB1ENR_TIM4EN = 0x4
RCC_APB1ENR_TIM6EN = 0x10
RCC_APB1ENR_TIM7EN = 0x20
RCC_APB1ENR_WWDGEN = 0x800
RCC_APB1ENR_SPI2EN = 0x4000
RCC_APB1ENR_SPI3EN = 0x8000
RCC_APB1ENR_USART2EN = 0x20000
RCC_APB1ENR_USART3EN = 0x40000
RCC_APB1ENR_UART3EN = 0x80000
RCC_APB1ENR_UART4EN = 0x100000
RCC_APB1ENR_I2C1EN = 0x200000
RCC_APB1ENR_I2C2EN = 0x400000
RCC_APB1ENR_USBEN = 0x800000
RCC_APB1ENR_CAN1EN = 0x2000000
RCC_APB1ENR_PWREN = 0x10000000
RCC_APB1ENR_DACEN = 0x20000000
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
RCC_CSR_RMVF = 0x1000000
RCC_CSR_OBLRSTF = 0x2000000
RCC_CSR_PINRSTF = 0x4000000
RCC_CSR_PORRSTF = 0x8000000
RCC_CSR_SFTRSTF = 0x10000000
RCC_CSR_IWDGRSTF = 0x20000000
RCC_CSR_WWDGRSTF = 0x40000000
RCC_CSR_LPWRRSTF = 0x80000000
RCC_AHBRSTR_GPIOARST = 0x20000
RCC_AHBRSTR_GPIOBRST = 0x40000
RCC_AHBRSTR_GPIOCRST = 0x80000
RCC_AHBRSTR_GPIODRST = 0x10000
RCC_AHBRSTR_GPIOFRST = 0x40000
RCC_AHBRSTR_TSRST = 0x100000
RCC_AHBRSTR_ADC12RST = 0x1000000
RCC_AHBRSTR_ADC34RST = 0x2000000
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
RCC_CFGR2_ADCPRE12 = 0x1F0
RCC_CFGR2_ADCPRE12_0 = 0x10
RCC_CFGR2_ADCPRE12_1 = 0x20
RCC_CFGR2_ADCPRE12_2 = 0x40
RCC_CFGR2_ADCPRE12_3 = 0x80
RCC_CFGR2_ADCPRE12_4 = 0x100
RCC_CFGR2_ADCPRE12_NO = 0x0
RCC_CFGR2_ADCPRE12_DIV1 = 0x100
RCC_CFGR2_ADCPRE12_DIV2 = 0x110
RCC_CFGR2_ADCPRE12_DIV4 = 0x120
RCC_CFGR2_ADCPRE12_DIV6 = 0x130
RCC_CFGR2_ADCPRE12_DIV8 = 0x140
RCC_CFGR2_ADCPRE12_DIV10 = 0x150
RCC_CFGR2_ADCPRE12_DIV12 = 0x160
RCC_CFGR2_ADCPRE12_DIV16 = 0x170
RCC_CFGR2_ADCPRE12_DIV32 = 0x180
RCC_CFGR2_ADCPRE12_DIV64 = 0x190
RCC_CFGR2_ADCPRE12_DIV128 = 0x1A0
RCC_CFGR2_ADCPRE12_DIV256 = 0x1B0
RCC_CFGR2_ADCPRE34 = 0x3E00
RCC_CFGR2_ADCPRE34_0 = 0x200
RCC_CFGR2_ADCPRE34_1 = 0x400
RCC_CFGR2_ADCPRE34_2 = 0x800
RCC_CFGR2_ADCPRE34_3 = 0x1000
RCC_CFGR2_ADCPRE34_4 = 0x2000
RCC_CFGR2_ADCPRE34_NO = 0x0
RCC_CFGR2_ADCPRE34_DIV1 = 0x2000
RCC_CFGR2_ADCPRE34_DIV2 = 0x2200
RCC_CFGR2_ADCPRE34_DIV4 = 0x2400
RCC_CFGR2_ADCPRE34_DIV6 = 0x2600
RCC_CFGR2_ADCPRE34_DIV8 = 0x2800
RCC_CFGR2_ADCPRE34_DIV10 = 0x2A00
RCC_CFGR2_ADCPRE34_DIV12 = 0x2C00
RCC_CFGR2_ADCPRE34_DIV16 = 0x2E00
RCC_CFGR2_ADCPRE34_DIV32 = 0x3000
RCC_CFGR2_ADCPRE34_DIV64 = 0x3200
RCC_CFGR2_ADCPRE34_DIV128 = 0x3400
RCC_CFGR2_ADCPRE34_DIV256 = 0x3600
RCC_CFGR3_USART1SW = 0x3
RCC_CFGR3_USART1SW_0 = 0x1
RCC_CFGR3_USART1SW_1 = 0x2
RCC_CFGR3_I2CSW = 0x30
RCC_CFGR3_I2C1SW = 0x10
RCC_CFGR3_I2C2SW = 0x20
RCC_CFGR3_TIMSW = 0x300
RCC_CFGR3_TIM1SW = 0x100
RCC_CFGR3_TIM8SW = 0x200
RCC_CFGR3_USART2SW = 0x30000
RCC_CFGR3_USART2SW_0 = 0x10000
RCC_CFGR3_USART2SW_1 = 0x20000
RCC_CFGR3_USART3SW = 0xC0000
RCC_CFGR3_USART3SW_0 = 0x40000
RCC_CFGR3_USART3SW_1 = 0x80000
RCC_CFGR3_UART4SW = 0x300000
RCC_CFGR3_UART4SW_0 = 0x100000
RCC_CFGR3_UART4SW_1 = 0x200000
RCC_CFGR3_UART5SW = 0xC00000
RCC_CFGR3_UART5SW_0 = 0x400000
RCC_CFGR3_UART5SW_1 = 0x800000
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
RTC_CR_FMT = 0x40
RTC_CR_BYPSHAD = 0x20
RTC_CR_REFCKON = 0x10
RTC_CR_TSEDGE = 0x8
RTC_CR_WUCKSEL = 0x7
RTC_CR_WUCKSEL_0 = 0x1
RTC_CR_WUCKSEL_1 = 0x2
RTC_CR_WUCKSEL_2 = 0x4
RTC_ISR_RECALPF = 0x10000
RTC_ISR_TAMP3F = 0x8000
RTC_ISR_TAMP2F = 0x4000
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
RTC_TAFCR_TAMP3TRG = 0x40
RTC_TAFCR_TAMP3E = 0x20
RTC_TAFCR_TAMP2TRG = 0x10
RTC_TAFCR_TAMP2E = 0x8
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
SYSCFG_CFGR1_USB_IT_RMP = 0x20
SYSCFG_CFGR1_TIM1_ITR3_RMP = 0x40
SYSCFG_CFGR1_DAC_TRIG_RMP = 0x80
SYSCFG_CFGR1_ADC24_DMA_RMP = 0x100
SYSCFG_CFGR1_TIM16_DMA_RMP = 0x800
SYSCFG_CFGR1_TIM17_DMA_RMP = 0x1000
SYSCFG_CFGR1_TIM6DAC1_DMA_RMP = 0x2000
SYSCFG_CFGR1_TIM7DAC2_DMA_RMP = 0x4000
SYSCFG_CFGR1_I2C_PB6_FMP = 0x10000
SYSCFG_CFGR1_I2C_PB7_FMP = 0x20000
SYSCFG_CFGR1_I2C_PB8_FMP = 0x40000
SYSCFG_CFGR1_I2C_PB9_FMP = 0x80000
SYSCFG_CFGR1_I2C1_FMP = 0x100000
SYSCFG_CFGR1_I2C2_FMP = 0x200000
SYSCFG_CFGR1_ENCODER_MODE = 0xC00000
SYSCFG_CFGR1_ENCODER_MODE_0 = 0x400000
SYSCFG_CFGR1_ENCODER_MODE_1 = 0x800000
SYSCFG_CFGR1_FPU_IE = 0xFC000000
SYSCFG_CFGR1_FPU_IE_0 = 0x4000000
SYSCFG_CFGR1_FPU_IE_1 = 0x8000000
SYSCFG_CFGR1_FPU_IE_2 = 0x10000000
SYSCFG_CFGR1_FPU_IE_3 = 0x20000000
SYSCFG_CFGR1_FPU_IE_4 = 0x40000000
SYSCFG_CFGR1_FPU_IE_5 = 0x80000000
SYSCFG_RCR_PAGE0 = 0x1
SYSCFG_RCR_PAGE1 = 0x2
SYSCFG_RCR_PAGE2 = 0x4
SYSCFG_RCR_PAGE3 = 0x8
SYSCFG_RCR_PAGE4 = 0x10
SYSCFG_RCR_PAGE5 = 0x20
SYSCFG_RCR_PAGE6 = 0x40
SYSCFG_RCR_PAGE7 = 0x80
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
SYSCFG_EXTIRCR_EXTI4 = 0xF
SYSCFG_EXTIRCR_EXTI5 = 0xF0
SYSCFG_EXTIRCR_EXTI6 = 0xF00
SYSCFG_EXTIRCR_EXTI7 = 0xF000
SYSCFG_EXTIRCR_EXTI4_PA = 0x0
SYSCFG_EXTIRCR_EXTI4_PB = 0x1
SYSCFG_EXTIRCR_EXTI4_PC = 0x2
SYSCFG_EXTIRCR_EXTI4_PD = 0x3
SYSCFG_EXTIRCR_EXTI4_PE = 0x4
SYSCFG_EXTIRCR_EXTI4_PF = 0x5
SYSCFG_EXTIRCR_EXTI5_PA = 0x0
SYSCFG_EXTIRCR_EXTI5_PB = 0x10
SYSCFG_EXTIRCR_EXTI5_PC = 0x20
SYSCFG_EXTIRCR_EXTI5_PD = 0x30
SYSCFG_EXTIRCR_EXTI5_PE = 0x40
SYSCFG_EXTIRCR_EXTI5_PF = 0x50
SYSCFG_EXTIRCR_EXTI6_PA = 0x0
SYSCFG_EXTIRCR_EXTI6_PB = 0x100
SYSCFG_EXTIRCR_EXTI6_PC = 0x200
SYSCFG_EXTIRCR_EXTI6_PD = 0x300
SYSCFG_EXTIRCR_EXTI6_PE = 0x400
SYSCFG_EXTIRCR_EXTI6_PF = 0x500
SYSCFG_EXTIRCR_EXTI7_PA = 0x0
SYSCFG_EXTIRCR_EXTI7_PB = 0x1000
SYSCFG_EXTIRCR_EXTI7_PC = 0x2000
SYSCFG_EXTIRCR_EXTI7_PD = 0x3000
SYSCFG_EXTIRCR_EXTI7_PE = 0x4000
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
SYSCFG_CFGR2_BYP_ADDR_PAR = 0x10
SYSCFG_CFGR2_SRAM_PE = 0x100
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
TIM_CR1_UIFREMAP = 0x800
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
TIM_CR2_OIS5 = 0x10000
TIM_CR2_OIS6 = 0x20000
TIM_CR2_MMS2 = 0xF00000
TIM_CR2_MMS2_0 = 0x100000
TIM_CR2_MMS2_1 = 0x200000
TIM_CR2_MMS2_2 = 0x400000
TIM_CR2_MMS2_3 = 0x800000
TIM_SMCR_SMS = 0x10007
TIM_SMCR_SMS_0 = 0x1
TIM_SMCR_SMS_1 = 0x2
TIM_SMCR_SMS_2 = 0x4
TIM_SMCR_SMS_3 = 0x10000
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
TIM_SR_B2IF = 0x100
TIM_SR_CC1OF = 0x200
TIM_SR_CC2OF = 0x400
TIM_SR_CC3OF = 0x800
TIM_SR_CC4OF = 0x1000
TIM_SR_CC5IF = 0x10000
TIM_SR_CC6IF = 0x20000
TIM_EGR_UG = 0x1
TIM_EGR_CC1G = 0x2
TIM_EGR_CC2G = 0x4
TIM_EGR_CC3G = 0x8
TIM_EGR_CC4G = 0x10
TIM_EGR_COMG = 0x20
TIM_EGR_TG = 0x40
TIM_EGR_BG = 0x80
TIM_EGR_B2G = 0x100
TIM_CCMR1_CC1S = 0x3
TIM_CCMR1_CC1S_0 = 0x1
TIM_CCMR1_CC1S_1 = 0x2
TIM_CCMR1_OC1FE = 0x4
TIM_CCMR1_OC1PE = 0x8
TIM_CCMR1_OC1M = 0x10070
TIM_CCMR1_OC1M_0 = 0x10
TIM_CCMR1_OC1M_1 = 0x20
TIM_CCMR1_OC1M_2 = 0x40
TIM_CCMR1_OC1M_3 = 0x10000
TIM_CCMR1_OC1CE = 0x80
TIM_CCMR1_CC2S = 0x300
TIM_CCMR1_CC2S_0 = 0x100
TIM_CCMR1_CC2S_1 = 0x200
TIM_CCMR1_OC2FE = 0x400
TIM_CCMR1_OC2PE = 0x800
TIM_CCMR1_OC2M = 0x1007000
TIM_CCMR1_OC2M_0 = 0x1000
TIM_CCMR1_OC2M_1 = 0x2000
TIM_CCMR1_OC2M_2 = 0x4000
TIM_CCMR1_OC2M_3 = 0x1000000
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
TIM_CCMR2_OC3M_3 = 0x10000
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
TIM_CCMR2_OC4M_3 = 0x100000
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
TIM_CCER_CC5E = 0x10000
TIM_CCER_CC5P = 0x20000
TIM_CCER_CC6E = 0x100000
TIM_CCER_CC6P = 0x200000
TIM_CNT_CNT = 0xFFFFFFFF
TIM_CNT_UIFCPY = 0x80000000
TIM_PSC_PSC = 0xFFFF
TIM_ARR_ARR = 0xFFFFFFFF
TIM_RCR_REP = 0xFF
TIM_CCR1_CCR1 = 0xFFFF
TIM_CCR2_CCR2 = 0xFFFF
TIM_CCR3_CCR3 = 0xFFFF
TIM_CCR4_CCR4 = 0xFFFF
TIM_CCR5_CCR5 = 0xFFFFFFFF
TIM_CCR5_GC5C1 = 0x20000000
TIM_CCR5_GC5C2 = 0x40000000
TIM_CCR5_GC5C3 = 0x80000000
TIM_CCR6_CCR6 = 0xFFFF
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
TIM_BDTR_BKF = 0xF0000
TIM_BDTR_BK2F = 0xF00000
TIM_BDTR_BK2E = 0x1000000
TIM_BDTR_BK2P = 0x2000000
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
TIM16_OR_TI1_RMP = 0xC0
TIM16_OR_TI1_RMP_0 = 0x40
TIM16_OR_TI1_RMP_1 = 0x80
TIM1_OR_ETR_RMP = 0xF
TIM1_OR_ETR_RMP_0 = 0x1
TIM1_OR_ETR_RMP_1 = 0x2
TIM1_OR_ETR_RMP_2 = 0x4
TIM1_OR_ETR_RMP_3 = 0x8
TIM8_OR_ETR_RMP = 0xF
TIM8_OR_ETR_RMP_0 = 0x1
TIM8_OR_ETR_RMP_1 = 0x2
TIM8_OR_ETR_RMP_2 = 0x4
TIM8_OR_ETR_RMP_3 = 0x8
TIM_CCMR3_OC5FE = 0x4
TIM_CCMR3_OC5PE = 0x8
TIM_CCMR3_OC5M = 0x70
TIM_CCMR3_OC5M_0 = 0x10
TIM_CCMR3_OC5M_1 = 0x20
TIM_CCMR3_OC5M_2 = 0x40
TIM_CCMR3_OC5M_3 = 0x10000
TIM_CCMR3_OC5CE = 0x80
TIM_CCMR3_OC6FE = 0x400
TIM_CCMR3_OC6PE = 0x800
TIM_CCMR3_OC6M = 0x7000
TIM_CCMR3_OC6M_0 = 0x1000
TIM_CCMR3_OC6M_1 = 0x2000
TIM_CCMR3_OC6M_2 = 0x4000
TIM_CCMR3_OC6M_3 = 0x100000
TIM_CCMR3_OC6CE = 0x8000
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
# fun define SET_BIT(REG, BIT)     ((REG) |= (BIT))
# fun define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
# fun define READ_BIT(REG, BIT)    ((REG) & (BIT))
# fun define CLEAR_REG(REG)        ((REG) = (0x0))
# fun define WRITE_REG(REG, VAL)   ((REG) = (VAL))
# fun define READ_REG(REG)         ((REG))
# fun define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
# struct ADC_TypeDef

class ADC_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('ISR',	ctypes.c_uint32),
		('IER',	ctypes.c_uint32),
		('CR',	ctypes.c_uint32),
		('CFGR',	ctypes.c_uint32),
		('RESERVED0',	ctypes.c_uint32),
		('SMPR1',	ctypes.c_uint32),
		('SMPR2',	ctypes.c_uint32),
		('RESERVED1',	ctypes.c_uint32),
		('TR1',	ctypes.c_uint32),
		('TR2',	ctypes.c_uint32),
		('TR3',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('SQR1',	ctypes.c_uint32),
		('SQR2',	ctypes.c_uint32),
		('SQR3',	ctypes.c_uint32),
		('SQR4',	ctypes.c_uint32),
		('DR',	ctypes.c_uint32),
		('RESERVED3',	ctypes.c_uint32),
		('RESERVED4',	ctypes.c_uint32),
		('JSQR',	ctypes.c_uint32),
		('RESERVED5',	ctypes.c_uint32 * 4),
		('OFR1',	ctypes.c_uint32),
		('OFR2',	ctypes.c_uint32),
		('OFR3',	ctypes.c_uint32),
		('OFR4',	ctypes.c_uint32),
		('RESERVED6',	ctypes.c_uint32 * 4),
		('JDR1',	ctypes.c_uint32),
		('JDR2',	ctypes.c_uint32),
		('JDR3',	ctypes.c_uint32),
		('JDR4',	ctypes.c_uint32),
		('RESERVED7',	ctypes.c_uint32 * 4),
		('AWD2CR',	ctypes.c_uint32),
		('AWD3CR',	ctypes.c_uint32),
		('RESERVED8',	ctypes.c_uint32),
		('RESERVED9',	ctypes.c_uint32),
		('DIFSEL',	ctypes.c_uint32),
		('CALFACT',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct ADC_Common_TypeDef

class ADC_Common_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CSR',	ctypes.c_uint32),
		('RESERVED',	ctypes.c_uint32),
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
# struct CAN_TypeDef : field is class : sTxMailBox
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
		('RESERVED1',	ctypes.c_uint32),
		('RESERVED2',	ctypes.c_uint32),
		('IMR2',	ctypes.c_uint32),
		('EMR2',	ctypes.c_uint32),
		('RTSR2',	ctypes.c_uint32),
		('FTSR2',	ctypes.c_uint32),
		('SWIER2',	ctypes.c_uint32),
		('PR2',	ctypes.c_uint32),
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
		('RESERVED0',	ctypes.c_uint16),
		('RESERVED1',	ctypes.c_uint16),
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

# struct OPAMP_TypeDef

class OPAMP_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CSR',	ctypes.c_uint32),
	]
	def ref(self):
		return ctypes.byref(self)

# struct SYSCFG_TypeDef

class SYSCFG_TypeDef(ctypes.Structure):
	_pack_ = False
	_fields_ = [
		('CFGR1',	ctypes.c_uint32),
		('RCR',	ctypes.c_uint32),
		('EXTICR',	ctypes.c_uint32 * 4),
		('CFGR2',	ctypes.c_uint32),
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
		('RESERVED0',	ctypes.c_uint32),
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
		('CR2',	ctypes.c_uint32),
		('SMCR',	ctypes.c_uint32),
		('DIER',	ctypes.c_uint32),
		('SR',	ctypes.c_uint32),
		('EGR',	ctypes.c_uint32),
		('CCMR1',	ctypes.c_uint32),
		('CCMR2',	ctypes.c_uint32),
		('CCER',	ctypes.c_uint32),
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
		('BDTR',	ctypes.c_uint32),
		('DCR',	ctypes.c_uint16),
		('RESERVED12',	ctypes.c_uint16),
		('DMAR',	ctypes.c_uint16),
		('RESERVED13',	ctypes.c_uint16),
		('OR',	ctypes.c_uint16),
		('CCMR3',	ctypes.c_uint32),
		('CCR5',	ctypes.c_uint32),
		('CCR6',	ctypes.c_uint32),
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

# file system_stm32f30x.h : 

# empty define __SYSTEM_STM32F30X_H
# Skip SystemCoreClock : no need parse
# ----------------------------------------

# file stm32f30x_conf.h : 

# empty define __STM32F30X_CONF_H
# fun define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
# fun define assert_param(expr) ((void)0)
# ----------------------------------------


__all__ =  ['__version__', '__RUN', '__HALT', '__ERROR', '__WARNING', '__INFO', '__DEBUG',
    '__ALL_LOG', 'DEFAULT_OPENOCD_PORT', 'DEFAULT_GDB_PORT', 'COMP_Selection_COMP1',
    'COMP_Selection_COMP2', 'COMP_Selection_COMP3', 'COMP_Selection_COMP4',
    'COMP_Selection_COMP5', 'COMP_Selection_COMP6', 'COMP_Selection_COMP7',
    'COMP_InvertingInput_1_4VREFINT', 'COMP_InvertingInput_1_2VREFINT',
    'COMP_InvertingInput_3_4VREFINT', 'COMP_InvertingInput_VREFINT',
    'COMP_InvertingInput_DAC1', 'COMP_InvertingInput_DAC2', 'COMP_InvertingInput_IO1',
    'COMP_InvertingInput_IO2', 'COMP_NonInvertingInput_IO1',
    'COMP_NonInvertingInput_IO2', 'COMP_Output_None', 'COMP_Output_TIM1BKIN',
    'COMP_Output_TIM1BKIN2', 'COMP_Output_TIM8BKIN', 'COMP_Output_TIM8BKIN2',
    'COMP_Output_TIM1BKIN2_TIM8BKIN2', 'COMP_Output_TIM1OCREFCLR',
    'COMP_Output_TIM1IC1', 'COMP_Output_TIM2IC4', 'COMP_Output_TIM2OCREFCLR',
    'COMP_Output_TIM3IC1', 'COMP_Output_TIM3OCREFCLR', 'COMP_Output_TIM4IC1',
    'COMP_Output_TIM3IC2', 'COMP_Output_TIM15IC1', 'COMP_Output_TIM15BKIN',
    'COMP_Output_TIM3IC3', 'COMP_Output_TIM8OCREFCLR', 'COMP_Output_TIM15IC2',
    'COMP_Output_TIM4IC2', 'COMP_Output_TIM15OCREFCLR', 'COMP_Output_TIM2IC1',
    'COMP_Output_TIM17IC1', 'COMP_Output_TIM4IC3', 'COMP_Output_TIM16BKIN',
    'COMP_Output_TIM2IC2', 'COMP_Output_COMP6TIM2OCREFCLR', 'COMP_Output_TIM16OCREFCLR',
    'COMP_Output_TIM16IC1', 'COMP_Output_TIM4IC4', 'COMP_Output_TIM2IC3',
    'COMP_Output_TIM1IC2', 'COMP_Output_TIM17OCREFCLR', 'COMP_Output_TIM17BKIN',
    'COMP_BlankingSrce_None', 'COMP_BlankingSrce_TIM1OC5', 'COMP_BlankingSrce_TIM2OC3',
    'COMP_BlankingSrce_TIM3OC3', 'COMP_BlankingSrce_TIM2OC4',
    'COMP_BlankingSrce_TIM8OC5', 'COMP_BlankingSrce_TIM3OC4',
    'COMP_BlankingSrce_TIM15OC1', 'COMP_BlankingSrce_TIM15OC2',
    'COMP_OutputPol_NonInverted', 'COMP_OutputPol_Inverted', 'COMP_Hysteresis_No',
    'COMP_Hysteresis_Low', 'COMP_Hysteresis_Medium', 'COMP_Hysteresis_High',
    'COMP_Mode_HighSpeed', 'COMP_Mode_MediumSpeed', 'COMP_Mode_LowPower',
    'COMP_Mode_UltraLowPower', 'COMP_OutputLevel_High', 'COMP_OutputLevel_Low',
    'COMP_InitTypeDef', 'CRC_ReverseInputData_No', 'CRC_ReverseInputData_8bits',
    'CRC_ReverseInputData_16bits', 'CRC_ReverseInputData_32bits', 'CRC_PolSize_7',
    'CRC_PolSize_8', 'CRC_PolSize_16', 'CRC_PolSize_32', 'USART_WordLength_8b',
    'USART_WordLength_9b', 'USART_StopBits_1', 'USART_StopBits_2', 'USART_StopBits_1_5',
    'USART_Parity_No', 'USART_Parity_Even', 'USART_Parity_Odd', 'USART_Mode_Rx',
    'USART_Mode_Tx', 'USART_HardwareFlowControl_None', 'USART_HardwareFlowControl_RTS',
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
    'USART_AutoBaudRate_FallingEdge', 'USART_AutoBaudRate_0x7FFrame',
    'USART_AutoBaudRate_0x55Frame', 'USART_OVRDetection_Enable',
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
    'RTC_HourFormat_24', 'RTC_HourFormat_12', 'RTC_H12_AM', 'RTC_H12_PM',
    'RTC_Month_January', 'RTC_Month_February', 'RTC_Month_March', 'RTC_Month_April',
    'RTC_Month_May', 'RTC_Month_June', 'RTC_Month_July', 'RTC_Month_August',
    'RTC_Month_September', 'RTC_Month_October', 'RTC_Month_November',
    'RTC_Month_December', 'RTC_Weekday_Monday', 'RTC_Weekday_Tuesday',
    'RTC_Weekday_Wednesday', 'RTC_Weekday_Thursday', 'RTC_Weekday_Friday',
    'RTC_Weekday_Saturday', 'RTC_Weekday_Sunday', 'RTC_AlarmDateWeekDaySel_Date',
    'RTC_AlarmDateWeekDaySel_WeekDay', 'RTC_AlarmMask_None',
    'RTC_AlarmMask_DateWeekDay', 'RTC_AlarmMask_Hours', 'RTC_AlarmMask_Minutes',
    'RTC_AlarmMask_Seconds', 'RTC_AlarmMask_All', 'RTC_Alarm_A', 'RTC_Alarm_B',
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
    'RTC_Output_AlarmA', 'RTC_Output_AlarmB', 'RTC_Output_WakeUp',
    'RTC_OutputPolarity_High', 'RTC_OutputPolarity_Low', 'RTC_CalibSign_Positive',
    'RTC_CalibSign_Negative', 'RTC_CalibOutput_512Hz', 'RTC_CalibOutput_1Hz',
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
    'RTC_BKP_DR2', 'RTC_BKP_DR3', 'RTC_BKP_DR4', 'RTC_BKP_DR5', 'RTC_BKP_DR6',
    'RTC_BKP_DR7', 'RTC_BKP_DR8', 'RTC_BKP_DR9', 'RTC_BKP_DR10', 'RTC_BKP_DR11',
    'RTC_BKP_DR12', 'RTC_BKP_DR13', 'RTC_BKP_DR14', 'RTC_BKP_DR15', 'RTC_Format_BIN',
    'RTC_Format_BCD', 'RTC_FLAG_RECALPF', 'RTC_FLAG_TAMP3F', 'RTC_FLAG_TAMP2F',
    'RTC_FLAG_TAMP1F', 'RTC_FLAG_TSOVF', 'RTC_FLAG_TSF', 'RTC_FLAG_WUTF',
    'RTC_FLAG_ALRBF', 'RTC_FLAG_ALRAF', 'RTC_FLAG_INITF', 'RTC_FLAG_RSF',
    'RTC_FLAG_INITS', 'RTC_FLAG_SHPF', 'RTC_FLAG_WUTWF', 'RTC_FLAG_ALRBWF',
    'RTC_FLAG_ALRAWF', 'RTC_IT_TS', 'RTC_IT_WUT', 'RTC_IT_ALRB', 'RTC_IT_ALRA',
    'RTC_IT_TAMP', 'RTC_IT_TAMP1', 'RTC_IT_TAMP2', 'RTC_IT_TAMP3', 'RTC_InitTypeDef',
    'RTC_TimeTypeDef', 'RTC_DateTypeDef', 'EXTI_PortSourceGPIOA',
    'EXTI_PortSourceGPIOB', 'EXTI_PortSourceGPIOC', 'EXTI_PortSourceGPIOD',
    'EXTI_PortSourceGPIOE', 'EXTI_PortSourceGPIOF', 'EXTI_PinSource0',
    'EXTI_PinSource1', 'EXTI_PinSource2', 'EXTI_PinSource3', 'EXTI_PinSource4',
    'EXTI_PinSource5', 'EXTI_PinSource6', 'EXTI_PinSource7', 'EXTI_PinSource8',
    'EXTI_PinSource9', 'EXTI_PinSource10', 'EXTI_PinSource11', 'EXTI_PinSource12',
    'EXTI_PinSource13', 'EXTI_PinSource14', 'EXTI_PinSource15',
    'SYSCFG_MemoryRemap_Flash', 'SYSCFG_MemoryRemap_SystemMemory',
    'SYSCFG_MemoryRemap_SRAM', 'SYSCFG_DMARemap_TIM17', 'SYSCFG_DMARemap_TIM16',
    'SYSCFG_DMARemap_TIM6DAC1', 'SYSCFG_DMARemap_TIM7DAC2', 'SYSCFG_DMARemap_ADC2ADC4',
    'SYSCFG_TriggerRemap_DACTIM3', 'SYSCFG_TriggerRemap_TIM1TIM17',
    'SYSCFG_EncoderRemap_No', 'SYSCFG_EncoderRemap_TIM2', 'SYSCFG_EncoderRemap_TIM3',
    'SYSCFG_EncoderRemap_TIM4', 'SYSCFG_I2CFastModePlus_PB6',
    'SYSCFG_I2CFastModePlus_PB7', 'SYSCFG_I2CFastModePlus_PB8',
    'SYSCFG_I2CFastModePlus_PB9', 'SYSCFG_I2CFastModePlus_I2C1',
    'SYSCFG_I2CFastModePlus_I2C2', 'SYSCFG_IT_IXC', 'SYSCFG_IT_IDC', 'SYSCFG_IT_OFC',
    'SYSCFG_IT_UFC', 'SYSCFG_IT_DZC', 'SYSCFG_IT_IOC', 'SYSCFG_Break_PVD',
    'SYSCFG_Break_SRAMParity', 'SYSCFG_Break_Lockup', 'SYSCFG_SRAMWRP_Page0',
    'SYSCFG_SRAMWRP_Page1', 'SYSCFG_SRAMWRP_Page2', 'SYSCFG_SRAMWRP_Page3',
    'SYSCFG_SRAMWRP_Page4', 'SYSCFG_SRAMWRP_Page5', 'SYSCFG_SRAMWRP_Page6',
    'SYSCFG_SRAMWRP_Page7', 'SYSCFG_FLAG_PE', 'PWR_PVDLevel_0', 'PWR_PVDLevel_1',
    'PWR_PVDLevel_2', 'PWR_PVDLevel_3', 'PWR_PVDLevel_4', 'PWR_PVDLevel_5',
    'PWR_PVDLevel_6', 'PWR_PVDLevel_7', 'PWR_WakeUpPin_1', 'PWR_WakeUpPin_2',
    'PWR_WakeUpPin_3', 'PWR_Regulator_ON', 'PWR_Regulator_LowPower',
    'PWR_SLEEPEntry_WFI', 'PWR_SLEEPEntry_WFE', 'PWR_STOPEntry_WFI',
    'PWR_STOPEntry_WFE', 'PWR_FLAG_WU', 'PWR_FLAG_SB', 'PWR_FLAG_PVDO',
    'PWR_FLAG_VREFINTRDY', 'SPI_Direction_2Lines_FullDuplex',
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
    'SPI_I2S_FLAG_FRE', 'SPI_InitTypeDef', 'I2S_InitTypeDef', 'FLASH_BUSY',
    'FLASH_ERROR_WRP', 'FLASH_ERROR_PROGRAM', 'FLASH_COMPLETE', 'FLASH_TIMEOUT',
    'FLASH_Latency_0', 'FLASH_Latency_1', 'FLASH_Latency_2', 'FLASH_IT_EOP',
    'FLASH_IT_ERR', 'OB_WRP_Pages0to1', 'OB_WRP_Pages2to3', 'OB_WRP_Pages4to5',
    'OB_WRP_Pages6to7', 'OB_WRP_Pages8to9', 'OB_WRP_Pages10to11', 'OB_WRP_Pages12to13',
    'OB_WRP_Pages14to15', 'OB_WRP_Pages16to17', 'OB_WRP_Pages18to19',
    'OB_WRP_Pages20to21', 'OB_WRP_Pages22to23', 'OB_WRP_Pages24to25',
    'OB_WRP_Pages26to27', 'OB_WRP_Pages28to29', 'OB_WRP_Pages30to31',
    'OB_WRP_Pages32to33', 'OB_WRP_Pages34to35', 'OB_WRP_Pages36to37',
    'OB_WRP_Pages38to39', 'OB_WRP_Pages40to41', 'OB_WRP_Pages42to43',
    'OB_WRP_Pages44to45', 'OB_WRP_Pages46to47', 'OB_WRP_Pages48to49',
    'OB_WRP_Pages50to51', 'OB_WRP_Pages52to53', 'OB_WRP_Pages54to55',
    'OB_WRP_Pages56to57', 'OB_WRP_Pages58to59', 'OB_WRP_Pages60to61',
    'OB_WRP_Pages62to127', 'OB_WRP_AllPages', 'OB_RDP_Level_0', 'OB_RDP_Level_1',
    'OB_IWDG_SW', 'OB_IWDG_HW', 'OB_STOP_NoRST', 'OB_STOP_RST', 'OB_STDBY_NoRST',
    'OB_STDBY_RST', 'OB_BOOT1_RESET', 'OB_BOOT1_SET', 'OB_VDDA_ANALOG_ON',
    'OB_VDDA_ANALOG_OFF', 'OB_SRAM_PARITY_SET', 'OB_SRAM_PARITY_RESET',
    'FLASH_FLAG_BSY', 'FLASH_FLAG_PGERR', 'FLASH_FLAG_WRPERR', 'FLASH_FLAG_EOP',
    'FLASH_ER_PRG_TIMEOUT', 'RCC_HSE_OFF', 'RCC_HSE_ON', 'RCC_HSE_Bypass',
    'RCC_PLLSource_HSI_Div2', 'RCC_PLLSource_PREDIV1', 'RCC_PLLMul_2', 'RCC_PLLMul_3',
    'RCC_PLLMul_4', 'RCC_PLLMul_5', 'RCC_PLLMul_6', 'RCC_PLLMul_7', 'RCC_PLLMul_8',
    'RCC_PLLMul_9', 'RCC_PLLMul_10', 'RCC_PLLMul_11', 'RCC_PLLMul_12', 'RCC_PLLMul_13',
    'RCC_PLLMul_14', 'RCC_PLLMul_15', 'RCC_PLLMul_16', 'RCC_PREDIV1_Div1',
    'RCC_PREDIV1_Div2', 'RCC_PREDIV1_Div3', 'RCC_PREDIV1_Div4', 'RCC_PREDIV1_Div5',
    'RCC_PREDIV1_Div6', 'RCC_PREDIV1_Div7', 'RCC_PREDIV1_Div8', 'RCC_PREDIV1_Div9',
    'RCC_PREDIV1_Div10', 'RCC_PREDIV1_Div11', 'RCC_PREDIV1_Div12', 'RCC_PREDIV1_Div13',
    'RCC_PREDIV1_Div14', 'RCC_PREDIV1_Div15', 'RCC_PREDIV1_Div16',
    'RCC_SYSCLKSource_HSI', 'RCC_SYSCLKSource_HSE', 'RCC_SYSCLKSource_PLLCLK',
    'RCC_SYSCLK_Div1', 'RCC_SYSCLK_Div2', 'RCC_SYSCLK_Div4', 'RCC_SYSCLK_Div8',
    'RCC_SYSCLK_Div16', 'RCC_SYSCLK_Div64', 'RCC_SYSCLK_Div128', 'RCC_SYSCLK_Div256',
    'RCC_SYSCLK_Div512', 'RCC_HCLK_Div1', 'RCC_HCLK_Div2', 'RCC_HCLK_Div4',
    'RCC_HCLK_Div8', 'RCC_HCLK_Div16', 'RCC_ADC12PLLCLK_OFF', 'RCC_ADC12PLLCLK_Div1',
    'RCC_ADC12PLLCLK_Div2', 'RCC_ADC12PLLCLK_Div4', 'RCC_ADC12PLLCLK_Div6',
    'RCC_ADC12PLLCLK_Div8', 'RCC_ADC12PLLCLK_Div10', 'RCC_ADC12PLLCLK_Div12',
    'RCC_ADC12PLLCLK_Div16', 'RCC_ADC12PLLCLK_Div32', 'RCC_ADC12PLLCLK_Div64',
    'RCC_ADC12PLLCLK_Div128', 'RCC_ADC12PLLCLK_Div256', 'RCC_ADC34PLLCLK_OFF',
    'RCC_ADC34PLLCLK_Div1', 'RCC_ADC34PLLCLK_Div2', 'RCC_ADC34PLLCLK_Div4',
    'RCC_ADC34PLLCLK_Div6', 'RCC_ADC34PLLCLK_Div8', 'RCC_ADC34PLLCLK_Div10',
    'RCC_ADC34PLLCLK_Div12', 'RCC_ADC34PLLCLK_Div16', 'RCC_ADC34PLLCLK_Div32',
    'RCC_ADC34PLLCLK_Div64', 'RCC_ADC34PLLCLK_Div128', 'RCC_ADC34PLLCLK_Div256',
    'RCC_TIM1CLK_HCLK', 'RCC_TIM1CLK_PLLCLK', 'RCC_TIM8CLK_HCLK', 'RCC_TIM8CLK_PLLCLK',
    'RCC_I2C1CLK_HSI', 'RCC_I2C1CLK_SYSCLK', 'RCC_I2C2CLK_HSI', 'RCC_I2C2CLK_SYSCLK',
    'RCC_USART1CLK_PCLK', 'RCC_USART1CLK_SYSCLK', 'RCC_USART1CLK_LSE',
    'RCC_USART1CLK_HSI', 'RCC_USART2CLK_PCLK', 'RCC_USART2CLK_SYSCLK',
    'RCC_USART2CLK_LSE', 'RCC_USART2CLK_HSI', 'RCC_USART3CLK_PCLK',
    'RCC_USART3CLK_SYSCLK', 'RCC_USART3CLK_LSE', 'RCC_USART3CLK_HSI',
    'RCC_UART4CLK_PCLK', 'RCC_UART4CLK_SYSCLK', 'RCC_UART4CLK_LSE', 'RCC_UART4CLK_HSI',
    'RCC_UART5CLK_PCLK', 'RCC_UART5CLK_SYSCLK', 'RCC_UART5CLK_LSE', 'RCC_UART5CLK_HSI',
    'RCC_IT_LSIRDY', 'RCC_IT_LSERDY', 'RCC_IT_HSIRDY', 'RCC_IT_HSERDY', 'RCC_IT_PLLRDY',
    'RCC_IT_CSS', 'RCC_LSE_OFF', 'RCC_LSE_ON', 'RCC_LSE_Bypass', 'RCC_RTCCLKSource_LSE',
    'RCC_RTCCLKSource_LSI', 'RCC_RTCCLKSource_HSE_Div32', 'RCC_I2S2CLKSource_SYSCLK',
    'RCC_I2S2CLKSource_Ext', 'RCC_LSEDrive_Low', 'RCC_LSEDrive_MediumLow',
    'RCC_LSEDrive_MediumHigh', 'RCC_LSEDrive_High', 'RCC_AHBPeriph_ADC34',
    'RCC_AHBPeriph_ADC12', 'RCC_AHBPeriph_GPIOA', 'RCC_AHBPeriph_GPIOB',
    'RCC_AHBPeriph_GPIOC', 'RCC_AHBPeriph_GPIOD', 'RCC_AHBPeriph_GPIOE',
    'RCC_AHBPeriph_GPIOF', 'RCC_AHBPeriph_TS', 'RCC_AHBPeriph_CRC',
    'RCC_AHBPeriph_FLITF', 'RCC_AHBPeriph_SRAM', 'RCC_AHBPeriph_DMA2',
    'RCC_AHBPeriph_DMA1', 'RCC_APB2Periph_SYSCFG', 'RCC_APB2Periph_TIM1',
    'RCC_APB2Periph_SPI1', 'RCC_APB2Periph_TIM8', 'RCC_APB2Periph_USART1',
    'RCC_APB2Periph_TIM15', 'RCC_APB2Periph_TIM16', 'RCC_APB2Periph_TIM17',
    'RCC_APB1Periph_TIM2', 'RCC_APB1Periph_TIM3', 'RCC_APB1Periph_TIM4',
    'RCC_APB1Periph_TIM6', 'RCC_APB1Periph_TIM7', 'RCC_APB1Periph_WWDG',
    'RCC_APB1Periph_SPI2', 'RCC_APB1Periph_SPI3', 'RCC_APB1Periph_USART2',
    'RCC_APB1Periph_USART3', 'RCC_APB1Periph_UART4', 'RCC_APB1Periph_UART5',
    'RCC_APB1Periph_I2C1', 'RCC_APB1Periph_I2C2', 'RCC_APB1Periph_USB',
    'RCC_APB1Periph_CAN1', 'RCC_APB1Periph_PWR', 'RCC_APB1Periph_DAC',
    'RCC_MCOSource_NoClock', 'RCC_MCOSource_LSI', 'RCC_MCOSource_LSE',
    'RCC_MCOSource_SYSCLK', 'RCC_MCOSource_HSI', 'RCC_MCOSource_HSE',
    'RCC_MCOSource_PLLCLK_Div2', 'RCC_USBCLKSource_PLLCLK_1Div5',
    'RCC_USBCLKSource_PLLCLK_Div1', 'RCC_FLAG_HSIRDY', 'RCC_FLAG_HSERDY',
    'RCC_FLAG_PLLRDY', 'RCC_FLAG_MCOF', 'RCC_FLAG_LSERDY', 'RCC_FLAG_LSIRDY',
    'RCC_FLAG_OBLRST', 'RCC_FLAG_PINRST', 'RCC_FLAG_PORRST', 'RCC_FLAG_SFTRST',
    'RCC_FLAG_IWDGRST', 'RCC_FLAG_WWDGRST', 'RCC_FLAG_LPWRRST', 'RCC_ClocksTypeDef',
    'IWDG_WriteAccess_Enable', 'IWDG_WriteAccess_Disable', 'IWDG_Prescaler_4',
    'IWDG_Prescaler_8', 'IWDG_Prescaler_16', 'IWDG_Prescaler_32', 'IWDG_Prescaler_64',
    'IWDG_Prescaler_128', 'IWDG_Prescaler_256', 'IWDG_FLAG_PVU', 'IWDG_FLAG_RVU',
    'IWDG_FLAG_WVU', 'EXTI_Mode_Interrupt', 'EXTI_Mode_Event', 'EXTI_Trigger_Rising',
    'EXTI_Trigger_Falling', 'EXTI_Trigger_Rising_Falling', 'EXTI_Line0', 'EXTI_Line1',
    'EXTI_Line2', 'EXTI_Line3', 'EXTI_Line4', 'EXTI_Line5', 'EXTI_Line6', 'EXTI_Line7',
    'EXTI_Line8', 'EXTI_Line9', 'EXTI_Line10', 'EXTI_Line11', 'EXTI_Line12',
    'EXTI_Line13', 'EXTI_Line14', 'EXTI_Line15', 'EXTI_Line16', 'EXTI_Line17',
    'EXTI_Line18', 'EXTI_Line19', 'EXTI_Line20', 'EXTI_Line21', 'EXTI_Line22',
    'EXTI_Line23', 'EXTI_Line24', 'EXTI_Line25', 'EXTI_Line26', 'EXTI_Line27',
    'EXTI_Line28', 'EXTI_Line29', 'EXTI_Line30', 'EXTI_Line31', 'EXTI_Line32',
    'EXTI_Line33', 'EXTI_Line34', 'EXTI_Line35', 'EXTI_InitTypeDef', 'DAC_CR_DMAUDRIE',
    'DAC_Trigger_None', 'DAC_Trigger_T2_TRGO', 'DAC_Trigger_T3_TRGO',
    'DAC_Trigger_T4_TRGO', 'DAC_Trigger_T6_TRGO', 'DAC_Trigger_T7_TRGO',
    'DAC_Trigger_T8_TRGO', 'DAC_Trigger_T15_TRGO', 'DAC_Trigger_Ext_IT9',
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
    'DAC_Align_8b_R', 'DAC_Wave_Noise', 'DAC_Wave_Triangle', 'DAC_IT_DMAUDR',
    'DAC_FLAG_DMAUDR', 'DAC_InitTypeDef', 'GPIO_Mode_IN', 'GPIO_Mode_OUT',
    'GPIO_Mode_AF', 'GPIO_Mode_AN', 'GPIO_OType_PP', 'GPIO_OType_OD', 'GPIO_Speed_2MHz',
    'GPIO_Speed_10MHz', 'GPIO_Speed_50MHz', 'GPIO_PuPd_NOPULL', 'GPIO_PuPd_UP',
    'GPIO_PuPd_DOWN', 'Bit_RESET', 'Bit_SET', 'GPIO_Pin_0', 'GPIO_Pin_1', 'GPIO_Pin_2',
    'GPIO_Pin_3', 'GPIO_Pin_4', 'GPIO_Pin_5', 'GPIO_Pin_6', 'GPIO_Pin_7', 'GPIO_Pin_8',
    'GPIO_Pin_9', 'GPIO_Pin_10', 'GPIO_Pin_11', 'GPIO_Pin_12', 'GPIO_Pin_13',
    'GPIO_Pin_14', 'GPIO_Pin_15', 'GPIO_Pin_All', 'GPIO_PinSource0', 'GPIO_PinSource1',
    'GPIO_PinSource2', 'GPIO_PinSource3', 'GPIO_PinSource4', 'GPIO_PinSource5',
    'GPIO_PinSource6', 'GPIO_PinSource7', 'GPIO_PinSource8', 'GPIO_PinSource9',
    'GPIO_PinSource10', 'GPIO_PinSource11', 'GPIO_PinSource12', 'GPIO_PinSource13',
    'GPIO_PinSource14', 'GPIO_PinSource15', 'GPIO_AF_0', 'GPIO_AF_1', 'GPIO_AF_2',
    'GPIO_AF_3', 'GPIO_AF_4', 'GPIO_AF_5', 'GPIO_AF_6', 'GPIO_AF_7', 'GPIO_AF_8',
    'GPIO_AF_9', 'GPIO_AF_10', 'GPIO_AF_11', 'GPIO_AF_12', 'GPIO_AF_14', 'GPIO_AF_15',
    'GPIO_InitTypeDef', 'TIM_OCMode_Timing', 'TIM_OCMode_Active', 'TIM_OCMode_Inactive',
    'TIM_OCMode_Toggle', 'TIM_OCMode_PWM1', 'TIM_OCMode_PWM2',
    'TIM_OCMode_Retrigerrable_OPM1', 'TIM_OCMode_Retrigerrable_OPM2',
    'TIM_OCMode_Combined_PWM1', 'TIM_OCMode_Combined_PWM2',
    'TIM_OCMode_Asymmetric_PWM1', 'TIM_OCMode_Asymmetric_PWM2', 'TIM_OPMode_Single',
    'TIM_OPMode_Repetitive', 'TIM_Channel_1', 'TIM_Channel_2', 'TIM_Channel_3',
    'TIM_Channel_4', 'TIM_Channel_5', 'TIM_Channel_6', 'TIM_CKD_DIV1', 'TIM_CKD_DIV2',
    'TIM_CKD_DIV4', 'TIM_CounterMode_Up', 'TIM_CounterMode_Down',
    'TIM_CounterMode_CenterAligned1', 'TIM_CounterMode_CenterAligned2',
    'TIM_CounterMode_CenterAligned3', 'TIM_OCPolarity_High', 'TIM_OCPolarity_Low',
    'TIM_OCNPolarity_High', 'TIM_OCNPolarity_Low', 'TIM_OutputState_Disable',
    'TIM_OutputState_Enable', 'TIM_OutputNState_Disable', 'TIM_OutputNState_Enable',
    'TIM_CCx_Enable', 'TIM_CCx_Disable', 'TIM_CCxN_Enable', 'TIM_CCxN_Disable',
    'TIM_Break_Enable', 'TIM_Break_Disable', 'TIM_Break1_Enable', 'TIM_Break1_Disable',
    'TIM_Break2_Enable', 'TIM_Break2_Disable', 'TIM_BreakPolarity_Low',
    'TIM_BreakPolarity_High', 'TIM_Break1Polarity_Low', 'TIM_Break1Polarity_High',
    'TIM_Break2Polarity_Low', 'TIM_Break2Polarity_High', 'TIM_AutomaticOutput_Enable',
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
    'TIM_DMABase_BDTR', 'TIM_DMABase_DCR', 'TIM_DMABase_OR', 'TIM_DMABase_CCMR3',
    'TIM_DMABase_CCR5', 'TIM_DMABase_CCR6', 'TIM_DMABurstLength_1Transfer',
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
    'TIM_EventSource_Break', 'TIM_EventSource_Break2', 'TIM_UpdateSource_Global',
    'TIM_UpdateSource_Regular', 'TIM_OCPreload_Enable', 'TIM_OCPreload_Disable',
    'TIM_OCFast_Enable', 'TIM_OCFast_Disable', 'TIM_OCClear_Enable',
    'TIM_OCClear_Disable', 'TIM_TRGOSource_Reset', 'TIM_TRGOSource_Enable',
    'TIM_TRGOSource_Update', 'TIM_TRGOSource_OC1', 'TIM_TRGOSource_OC1Ref',
    'TIM_TRGOSource_OC2Ref', 'TIM_TRGOSource_OC3Ref', 'TIM_TRGOSource_OC4Ref',
    'TIM_TRGO2Source_Reset', 'TIM_TRGO2Source_Enable', 'TIM_TRGO2Source_Update',
    'TIM_TRGO2Source_OC1', 'TIM_TRGO2Source_OC1Ref', 'TIM_TRGO2Source_OC2Ref',
    'TIM_TRGO2Source_OC3Ref', 'TIM_TRGO2Source_OC4Ref', 'TIM_TRGO2Source_OC5Ref',
    'TIM_TRGO2Source_OC6Ref', 'TIM_TRGO2Source_OC4Ref_RisingFalling',
    'TIM_TRGO2Source_OC6Ref_RisingFalling', 'TIM_TRGO2Source_OC4RefRising_OC6RefRising',
    'TIM_TRGO2Source_OC4RefRising_OC6RefFalling',
    'TIM_TRGO2Source_OC5RefRising_OC6RefRising',
    'TIM_TRGO2Source_OC5RefRising_OC6RefFalling', 'TIM_SlaveMode_Reset',
    'TIM_SlaveMode_Gated', 'TIM_SlaveMode_Trigger', 'TIM_SlaveMode_External1',
    'TIM_SlaveMode_Combined_ResetTrigger', 'TIM_MasterSlaveMode_Enable',
    'TIM_MasterSlaveMode_Disable', 'TIM16_GPIO', 'TIM16_RTC_CLK', 'TIM16_HSEDiv32',
    'TIM16_MCO', 'TIM1_ADC1_AWDG1', 'TIM1_ADC1_AWDG2', 'TIM1_ADC1_AWDG3',
    'TIM1_ADC4_AWDG1', 'TIM1_ADC4_AWDG2', 'TIM1_ADC4_AWDG3', 'TIM8_ADC2_AWDG1',
    'TIM8_ADC2_AWDG2', 'TIM8_ADC2_AWDG3', 'TIM8_ADC3_AWDG1', 'TIM8_ADC3_AWDG2',
    'TIM8_ADC3_AWDG3', 'TIM_FLAG_Update', 'TIM_FLAG_CC1', 'TIM_FLAG_CC2',
    'TIM_FLAG_CC3', 'TIM_FLAG_CC4', 'TIM_FLAG_COM', 'TIM_FLAG_Trigger',
    'TIM_FLAG_Break', 'TIM_FLAG_Break2', 'TIM_FLAG_CC1OF', 'TIM_FLAG_CC2OF',
    'TIM_FLAG_CC3OF', 'TIM_FLAG_CC4OF', 'TIM_FLAG_CC5', 'TIM_FLAG_CC6',
    'TIM_OCReferenceClear_ETRF', 'TIM_OCReferenceClear_OCREFCLR',
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
    'TIM_BDTRInitTypeDef', 'NVIC_VectTab_RAM', 'NVIC_VectTab_FLASH',
    'NVIC_LP_SEVONPEND', 'NVIC_LP_SLEEPDEEP', 'NVIC_LP_SLEEPONEXIT',
    'NVIC_PriorityGroup_0', 'NVIC_PriorityGroup_1', 'NVIC_PriorityGroup_2',
    'NVIC_PriorityGroup_3', 'NVIC_PriorityGroup_4', 'SysTick_CLKSource_HCLK_Div8',
    'SysTick_CLKSource_HCLK', 'NVIC_InitTypeDef', 'DBGMCU_SLEEP', 'DBGMCU_STOP',
    'DBGMCU_STANDBY', 'DBGMCU_TIM2_STOP', 'DBGMCU_TIM3_STOP', 'DBGMCU_TIM4_STOP',
    'DBGMCU_TIM6_STOP', 'DBGMCU_TIM7_STOP', 'DBGMCU_RTC_STOP', 'DBGMCU_WWDG_STOP',
    'DBGMCU_IWDG_STOP', 'DBGMCU_I2C1_SMBUS_TIMEOUT', 'DBGMCU_I2C2_SMBUS_TIMEOUT',
    'DBGMCU_CAN1_STOP', 'DBGMCU_TIM1_STOP', 'DBGMCU_TIM8_STOP', 'DBGMCU_TIM15_STOP',
    'DBGMCU_TIM16_STOP', 'DBGMCU_TIM17_STOP', 'I2C_AnalogFilter_Enable',
    'I2C_AnalogFilter_Disable', 'I2C_Mode_I2C', 'I2C_Mode_SMBusDevice',
    'I2C_Mode_SMBusHost', 'I2C_Ack_Enable', 'I2C_Ack_Disable',
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
    'I2C_Generate_Start_Write', 'I2C_InitTypeDef', 'DMA_DIR_PeripheralSRC',
    'DMA_DIR_PeripheralDST', 'DMA_PeripheralInc_Disable', 'DMA_PeripheralInc_Enable',
    'DMA_MemoryInc_Disable', 'DMA_MemoryInc_Enable', 'DMA_PeripheralDataSize_Byte',
    'DMA_PeripheralDataSize_HalfWord', 'DMA_PeripheralDataSize_Word',
    'DMA_MemoryDataSize_Byte', 'DMA_MemoryDataSize_HalfWord', 'DMA_MemoryDataSize_Word',
    'DMA_Mode_Normal', 'DMA_Mode_Circular', 'DMA_Priority_VeryHigh',
    'DMA_Priority_High', 'DMA_Priority_Medium', 'DMA_Priority_Low', 'DMA_M2M_Disable',
    'DMA_M2M_Enable', 'DMA_IT_TC', 'DMA_IT_HT', 'DMA_IT_TE', 'DMA1_IT_GL1',
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
    'DMA_InitTypeDef', 'ADC_ContinuousConvMode_Enable',
    'ADC_ContinuousConvMode_Disable', 'ADC_OverrunMode_Enable',
    'ADC_OverrunMode_Disable', 'ADC_AutoInjec_Enable', 'ADC_AutoInjec_Disable',
    'ADC_Resolution_12b', 'ADC_Resolution_10b', 'ADC_Resolution_8b',
    'ADC_Resolution_6b', 'ADC_ExternalTrigEventEdge_None',
    'ADC_ExternalTrigEventEdge_RisingEdge', 'ADC_ExternalTrigEventEdge_FallingEdge',
    'ADC_ExternalTrigEventEdge_BothEdge', 'ADC_ExternalTrigInjecEventEdge_None',
    'ADC_ExternalTrigInjecEventEdge_RisingEdge',
    'ADC_ExternalTrigInjecEventEdge_FallingEdge',
    'ADC_ExternalTrigInjecEventEdge_BothEdge', 'ADC_ExternalTrigConvEvent_0',
    'ADC_ExternalTrigConvEvent_1', 'ADC_ExternalTrigConvEvent_2',
    'ADC_ExternalTrigConvEvent_3', 'ADC_ExternalTrigConvEvent_4',
    'ADC_ExternalTrigConvEvent_5', 'ADC_ExternalTrigConvEvent_6',
    'ADC_ExternalTrigConvEvent_7', 'ADC_ExternalTrigConvEvent_8',
    'ADC_ExternalTrigConvEvent_9', 'ADC_ExternalTrigConvEvent_10',
    'ADC_ExternalTrigConvEvent_11', 'ADC_ExternalTrigConvEvent_12',
    'ADC_ExternalTrigConvEvent_13', 'ADC_ExternalTrigConvEvent_14',
    'ADC_ExternalTrigConvEvent_15', 'ADC_ExternalTrigInjecConvEvent_0',
    'ADC_ExternalTrigInjecConvEvent_1', 'ADC_ExternalTrigInjecConvEvent_2',
    'ADC_ExternalTrigInjecConvEvent_3', 'ADC_ExternalTrigInjecConvEvent_4',
    'ADC_ExternalTrigInjecConvEvent_5', 'ADC_ExternalTrigInjecConvEvent_6',
    'ADC_ExternalTrigInjecConvEvent_7', 'ADC_ExternalTrigInjecConvEvent_8',
    'ADC_ExternalTrigInjecConvEvent_9', 'ADC_ExternalTrigInjecConvEvent_10',
    'ADC_ExternalTrigInjecConvEvent_11', 'ADC_ExternalTrigInjecConvEvent_12',
    'ADC_ExternalTrigInjecConvEvent_13', 'ADC_ExternalTrigInjecConvEvent_14',
    'ADC_ExternalTrigInjecConvEvent_15', 'ADC_DataAlign_Right', 'ADC_DataAlign_Left',
    'ADC_Channel_1', 'ADC_Channel_2', 'ADC_Channel_3', 'ADC_Channel_4', 'ADC_Channel_5',
    'ADC_Channel_6', 'ADC_Channel_7', 'ADC_Channel_8', 'ADC_Channel_9',
    'ADC_Channel_10', 'ADC_Channel_11', 'ADC_Channel_12', 'ADC_Channel_13',
    'ADC_Channel_14', 'ADC_Channel_15', 'ADC_Channel_16', 'ADC_Channel_17',
    'ADC_Channel_18', 'ADC_Channel_TempSensor', 'ADC_Channel_Vrefint',
    'ADC_Channel_Vbat', 'ADC_Mode_Independent', 'ADC_Mode_CombRegSimulInjSimul',
    'ADC_Mode_CombRegSimulAltTrig', 'ADC_Mode_InjSimul', 'ADC_Mode_RegSimul',
    'ADC_Mode_Interleave', 'ADC_Mode_AltTrig', 'ADC_Clock_AsynClkMode',
    'ADC_Clock_SynClkModeDiv1', 'ADC_Clock_SynClkModeDiv2', 'ADC_Clock_SynClkModeDiv4',
    'ADC_DMAAccessMode_Disabled', 'ADC_DMAAccessMode_1', 'ADC_DMAAccessMode_2',
    'ADC_SampleTime_1Cycles5', 'ADC_SampleTime_2Cycles5', 'ADC_SampleTime_4Cycles5',
    'ADC_SampleTime_7Cycles5', 'ADC_SampleTime_19Cycles5', 'ADC_SampleTime_61Cycles5',
    'ADC_SampleTime_181Cycles5', 'ADC_SampleTime_601Cycles5', 'ADC_InjectedChannel_1',
    'ADC_InjectedChannel_2', 'ADC_InjectedChannel_3', 'ADC_InjectedChannel_4',
    'ADC_AnalogWatchdog_SingleRegEnable', 'ADC_AnalogWatchdog_SingleInjecEnable',
    'ADC_AnalogWatchdog_SingleRegOrInjecEnable', 'ADC_AnalogWatchdog_AllRegEnable',
    'ADC_AnalogWatchdog_AllInjecEnable', 'ADC_AnalogWatchdog_AllRegAllInjecEnable',
    'ADC_AnalogWatchdog_None', 'ADC_CalibrationMode_Single',
    'ADC_CalibrationMode_Differential', 'ADC_DMAMode_OneShot', 'ADC_DMAMode_Circular',
    'ADC_IT_RDY', 'ADC_IT_EOSMP', 'ADC_IT_EOC', 'ADC_IT_EOS', 'ADC_IT_OVR',
    'ADC_IT_JEOC', 'ADC_IT_JEOS', 'ADC_IT_AWD1', 'ADC_IT_AWD2', 'ADC_IT_AWD3',
    'ADC_IT_JQOVF', 'ADC_FLAG_RDY', 'ADC_FLAG_EOSMP', 'ADC_FLAG_EOC', 'ADC_FLAG_EOS',
    'ADC_FLAG_OVR', 'ADC_FLAG_JEOC', 'ADC_FLAG_JEOS', 'ADC_FLAG_AWD1', 'ADC_FLAG_AWD2',
    'ADC_FLAG_AWD3', 'ADC_FLAG_JQOVF', 'ADC_FLAG_MSTRDY', 'ADC_FLAG_MSTEOSMP',
    'ADC_FLAG_MSTEOC', 'ADC_FLAG_MSTEOS', 'ADC_FLAG_MSTOVR', 'ADC_FLAG_MSTJEOC',
    'ADC_FLAG_MSTJEOS', 'ADC_FLAG_MSTAWD1', 'ADC_FLAG_MSTAWD2', 'ADC_FLAG_MSTAWD3',
    'ADC_FLAG_MSTJQOVF', 'ADC_FLAG_SLVRDY', 'ADC_FLAG_SLVEOSMP', 'ADC_FLAG_SLVEOC',
    'ADC_FLAG_SLVEOS', 'ADC_FLAG_SLVOVR', 'ADC_FLAG_SLVJEOC', 'ADC_FLAG_SLVJEOS',
    'ADC_FLAG_SLVAWD1', 'ADC_FLAG_SLVAWD2', 'ADC_FLAG_SLVAWD3', 'ADC_FLAG_SLVJQOVF',
    'ADC_InitTypeDef', 'ADC_InjectedInitTypeDef', 'ADC_CommonInitTypeDef',
    'WWDG_Prescaler_1', 'WWDG_Prescaler_2', 'WWDG_Prescaler_4', 'WWDG_Prescaler_8',
    'OPAMP_Selection_OPAMP1', 'OPAMP_Selection_OPAMP2', 'OPAMP_Selection_OPAMP3',
    'OPAMP_Selection_OPAMP4', 'OPAMP_InvertingInput_IO1', 'OPAMP_InvertingInput_IO2',
    'OPAMP_InvertingInput_PGA', 'OPAMP_InvertingInput_Vout',
    'OPAMP_NonInvertingInput_IO1', 'OPAMP_NonInvertingInput_IO2',
    'OPAMP_NonInvertingInput_IO3', 'OPAMP_NonInvertingInput_IO4',
    'OPAMP_OPAMP_PGAGain_2', 'OPAMP_OPAMP_PGAGain_4', 'OPAMP_OPAMP_PGAGain_8',
    'OPAMP_OPAMP_PGAGain_16', 'OPAMP_PGAConnect_No', 'OPAMP_PGAConnect_IO1',
    'OPAMP_PGAConnect_IO2', 'OPAMP_Input_Inverting', 'OPAMP_Input_NonInverting',
    'OPAMP_Vref_3VDDA', 'OPAMP_Vref_10VDDA', 'OPAMP_Vref_50VDDA', 'OPAMP_Vref_90VDDA',
    'OPAMP_Trimming_Factory', 'OPAMP_Trimming_User', 'OPAMP_OutputLevel_High',
    'OPAMP_OutputLevel_Low', 'OPAMP_InitTypeDef', 'CAN_InitStatus_Failed',
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
    'CAN_FilterInitTypeDef', 'CanTxMsg', 'CanRxMsg', '__CM4_CMSIS_VERSION_MAIN',
    '__CM4_CMSIS_VERSION_SUB', '__CM4_CMSIS_VERSION', '__CORTEX_M', 'NVIC_Type',
    'SCB_Type', 'SCnSCB_Type', 'SysTick_Type', 'ITM_Type', 'DWT_Type', 'TPI_Type',
    'MPU_Type', 'FPU_Type', 'CoreDebug_Type', 'NonMaskableInt_IRQn',
    'MemoryManagement_IRQn', 'BusFault_IRQn', 'UsageFault_IRQn', 'SVCall_IRQn',
    'DebugMonitor_IRQn', 'PendSV_IRQn', 'SysTick_IRQn', 'WWDG_IRQn', 'PVD_IRQn',
    'TAMPER_STAMP_IRQn', 'RTC_WKUP_IRQn', 'FLASH_IRQn', 'RCC_IRQn', 'EXTI0_IRQn',
    'EXTI1_IRQn', 'EXTI2_TS_IRQn', 'EXTI3_IRQn', 'EXTI4_IRQn', 'DMA1_Channel1_IRQn',
    'DMA1_Channel2_IRQn', 'DMA1_Channel3_IRQn', 'DMA1_Channel4_IRQn',
    'DMA1_Channel5_IRQn', 'DMA1_Channel6_IRQn', 'DMA1_Channel7_IRQn', 'ADC1_2_IRQn',
    'USB_HP_CAN1_TX_IRQn', 'USB_LP_CAN1_RX0_IRQn', 'CAN1_RX1_IRQn', 'CAN1_SCE_IRQn',
    'EXTI9_5_IRQn', 'TIM1_BRK_TIM15_IRQn', 'TIM1_UP_TIM16_IRQn',
    'TIM1_TRG_COM_TIM17_IRQn', 'TIM1_CC_IRQn', 'TIM2_IRQn', 'TIM3_IRQn', 'TIM4_IRQn',
    'I2C1_EV_IRQn', 'I2C1_ER_IRQn', 'I2C2_EV_IRQn', 'I2C2_ER_IRQn', 'SPI1_IRQn',
    'SPI2_IRQn', 'USART1_IRQn', 'USART2_IRQn', 'USART3_IRQn', 'EXTI15_10_IRQn',
    'RTC_Alarm_IRQn', 'USBWakeUp_IRQn', 'TIM8_BRK_IRQn', 'TIM8_UP_IRQn',
    'TIM8_TRG_COM_IRQn', 'TIM8_CC_IRQn', 'ADC3_IRQn', 'SPI3_IRQn', 'UART4_IRQn',
    'UART5_IRQn', 'TIM6_DAC_IRQn', 'TIM7_IRQn', 'DMA2_Channel1_IRQn',
    'DMA2_Channel2_IRQn', 'DMA2_Channel3_IRQn', 'DMA2_Channel4_IRQn',
    'DMA2_Channel5_IRQn', 'ADC4_IRQn', 'COMP1_2_3_IRQn', 'COMP4_5_6_IRQn', 'COMP7_IRQn',
    'USB_HP_IRQn', 'USB_LP_IRQn', 'USBWakeUp_RMP_IRQn', 'FPU_IRQn', 'RESET', 'SET',
    'DISABLE', 'ENABLE', 'ERROR', 'SUCCESS', 'HSE_VALUE', 'HSE_STARTUP_TIMEOUT',
    'HSI_STARTUP_TIMEOUT', 'HSI_VALUE', 'LSI_VALUE', 'LSE_VALUE',
    '__STM32F30X_STDPERIPH_VERSION_MAIN', '__STM32F30X_STDPERIPH_VERSION_SUB1',
    '__STM32F30X_STDPERIPH_VERSION_SUB2', '__STM32F30X_STDPERIPH_VERSION_RC',
    '__STM32F30X_STDPERIPH_VERSION', '__CM4_REV', '__MPU_PRESENT', '__NVIC_PRIO_BITS',
    '__Vendor_SysTickConfig', '__FPU_PRESENT', 'FLASH_BASE', 'SRAM_BASE', 'PERIPH_BASE',
    'SRAM_BB_BASE', 'PERIPH_BB_BASE', 'APB1PERIPH_BASE', 'APB2PERIPH_BASE',
    'AHB1PERIPH_BASE', 'AHB2PERIPH_BASE', 'AHB3PERIPH_BASE', 'TIM2_BASE', 'TIM3_BASE',
    'TIM4_BASE', 'TIM6_BASE', 'TIM7_BASE', 'RTC_BASE', 'WWDG_BASE', 'IWDG_BASE',
    'I2S2ext_BASE', 'SPI2_BASE', 'SPI3_BASE', 'I2S3ext_BASE', 'USART2_BASE',
    'USART3_BASE', 'UART4_BASE', 'UART5_BASE', 'I2C1_BASE', 'I2C2_BASE', 'CAN1_BASE',
    'PWR_BASE', 'DAC_BASE', 'SYSCFG_BASE', 'COMP_BASE', 'COMP1_BASE', 'COMP2_BASE',
    'COMP3_BASE', 'COMP4_BASE', 'COMP5_BASE', 'COMP6_BASE', 'COMP7_BASE', 'OPAMP_BASE',
    'OPAMP1_BASE', 'OPAMP2_BASE', 'OPAMP3_BASE', 'OPAMP4_BASE', 'EXTI_BASE',
    'TIM1_BASE', 'SPI1_BASE', 'TIM8_BASE', 'USART1_BASE', 'TIM15_BASE', 'TIM16_BASE',
    'TIM17_BASE', 'DMA1_BASE', 'DMA1_Channel1_BASE', 'DMA1_Channel2_BASE',
    'DMA1_Channel3_BASE', 'DMA1_Channel4_BASE', 'DMA1_Channel5_BASE',
    'DMA1_Channel6_BASE', 'DMA1_Channel7_BASE', 'DMA2_BASE', 'DMA2_Channel1_BASE',
    'DMA2_Channel2_BASE', 'DMA2_Channel3_BASE', 'DMA2_Channel4_BASE',
    'DMA2_Channel5_BASE', 'RCC_BASE', 'FLASH_R_BASE', 'OB_BASE', 'CRC_BASE', 'TSC_BASE',
    'GPIOA_BASE', 'GPIOB_BASE', 'GPIOC_BASE', 'GPIOD_BASE', 'GPIOE_BASE', 'GPIOF_BASE',
    'ADC1_BASE', 'ADC2_BASE', 'ADC1_2_BASE', 'ADC3_BASE', 'ADC4_BASE', 'ADC3_4_BASE',
    'DBGMCU_BASE', 'TIM2', 'TIM3', 'TIM4', 'TIM6', 'TIM7', 'RTC', 'WWDG', 'IWDG',
    'I2S2ext', 'SPI2', 'SPI3', 'I2S3ext', 'USART2', 'USART3', 'UART4', 'UART5', 'I2C1',
    'I2C2', 'CAN1', 'PWR', 'DAC', 'SYSCFG', 'COMP', 'COMP1', 'COMP2', 'COMP3', 'COMP4',
    'COMP5', 'COMP6', 'COMP7', 'OPAMP', 'OPAMP1', 'OPAMP2', 'OPAMP3', 'OPAMP4', 'EXTI',
    'TIM1', 'SPI1', 'TIM8', 'USART1', 'TIM15', 'TIM16', 'TIM17', 'DBGMCU', 'DMA1',
    'DMA1_Channel1', 'DMA1_Channel2', 'DMA1_Channel3', 'DMA1_Channel4', 'DMA1_Channel5',
    'DMA1_Channel6', 'DMA1_Channel7', 'DMA2', 'DMA2_Channel1', 'DMA2_Channel2',
    'DMA2_Channel3', 'DMA2_Channel4', 'DMA2_Channel5', 'RCC', 'FLASH', 'OB', 'CRC',
    'TSC', 'GPIOA', 'GPIOB', 'GPIOC', 'GPIOD', 'GPIOE', 'GPIOF', 'ADC1', 'ADC2', 'ADC3',
    'ADC4', 'ADC1_2', 'ADC3_4', 'ADC_ISR_ADRD', 'ADC_ISR_EOSMP', 'ADC_ISR_EOC',
    'ADC_ISR_EOS', 'ADC_ISR_OVR', 'ADC_ISR_JEOC', 'ADC_ISR_JEOS', 'ADC_ISR_AWD1',
    'ADC_ISR_AWD2', 'ADC_ISR_AWD3', 'ADC_ISR_JQOVF', 'ADC_IER_RDY', 'ADC_IER_EOSMP',
    'ADC_IER_EOC', 'ADC_IER_EOS', 'ADC_IER_OVR', 'ADC_IER_JEOC', 'ADC_IER_JEOS',
    'ADC_IER_AWD1', 'ADC_IER_AWD2', 'ADC_IER_AWD3', 'ADC_IER_JQOVF', 'ADC_CR_ADEN',
    'ADC_CR_ADDIS', 'ADC_CR_ADSTART', 'ADC_CR_JADSTART', 'ADC_CR_ADSTP',
    'ADC_CR_JADSTP', 'ADC_CR_ADVREGEN', 'ADC_CR_ADVREGEN_0', 'ADC_CR_ADVREGEN_1',
    'ADC_CR_ADCALDIF', 'ADC_CR_ADCAL', 'ADC_CFGR_DMAEN', 'ADC_CFGR_DMACFG',
    'ADC_CFGR_RES', 'ADC_CFGR_RES_0', 'ADC_CFGR_RES_1', 'ADC_CFGR_ALIGN',
    'ADC_CFGR_EXTSEL', 'ADC_CFGR_EXTSEL_0', 'ADC_CFGR_EXTSEL_1', 'ADC_CFGR_EXTSEL_2',
    'ADC_CFGR_EXTSEL_3', 'ADC_CFGR_EXTEN', 'ADC_CFGR_EXTEN_0', 'ADC_CFGR_EXTEN_1',
    'ADC_CFGR_OVRMOD', 'ADC_CFGR_CONT', 'ADC_CFGR_AUTDLY', 'ADC_CFGR_AUTOFF',
    'ADC_CFGR_DISCEN', 'ADC_CFGR_DISCNUM', 'ADC_CFGR_DISCNUM_0', 'ADC_CFGR_DISCNUM_1',
    'ADC_CFGR_DISCNUM_2', 'ADC_CFGR_JDISCEN', 'ADC_CFGR_JQM', 'ADC_CFGR_AWD1SGL',
    'ADC_CFGR_AWD1EN', 'ADC_CFGR_JAWD1EN', 'ADC_CFGR_JAUTO', 'ADC_CFGR_AWD1CH',
    'ADC_CFGR_AWD1CH_0', 'ADC_CFGR_AWD1CH_1', 'ADC_CFGR_AWD1CH_2', 'ADC_CFGR_AWD1CH_3',
    'ADC_CFGR_AWD1CH_4', 'ADC_SMPR1_SMP0', 'ADC_SMPR1_SMP0_0', 'ADC_SMPR1_SMP0_1',
    'ADC_SMPR1_SMP0_2', 'ADC_SMPR1_SMP1', 'ADC_SMPR1_SMP1_0', 'ADC_SMPR1_SMP1_1',
    'ADC_SMPR1_SMP1_2', 'ADC_SMPR1_SMP2', 'ADC_SMPR1_SMP2_0', 'ADC_SMPR1_SMP2_1',
    'ADC_SMPR1_SMP2_2', 'ADC_SMPR1_SMP3', 'ADC_SMPR1_SMP3_0', 'ADC_SMPR1_SMP3_1',
    'ADC_SMPR1_SMP3_2', 'ADC_SMPR1_SMP4', 'ADC_SMPR1_SMP4_0', 'ADC_SMPR1_SMP4_1',
    'ADC_SMPR1_SMP4_2', 'ADC_SMPR1_SMP5', 'ADC_SMPR1_SMP5_0', 'ADC_SMPR1_SMP5_1',
    'ADC_SMPR1_SMP5_2', 'ADC_SMPR1_SMP6', 'ADC_SMPR1_SMP6_0', 'ADC_SMPR1_SMP6_1',
    'ADC_SMPR1_SMP6_2', 'ADC_SMPR1_SMP7', 'ADC_SMPR1_SMP7_0', 'ADC_SMPR1_SMP7_1',
    'ADC_SMPR1_SMP7_2', 'ADC_SMPR1_SMP8', 'ADC_SMPR1_SMP8_0', 'ADC_SMPR1_SMP8_1',
    'ADC_SMPR1_SMP8_2', 'ADC_SMPR1_SMP9', 'ADC_SMPR1_SMP9_0', 'ADC_SMPR1_SMP9_1',
    'ADC_SMPR1_SMP9_2', 'ADC_SMPR2_SMP10', 'ADC_SMPR2_SMP10_0', 'ADC_SMPR2_SMP10_1',
    'ADC_SMPR2_SMP10_2', 'ADC_SMPR2_SMP11', 'ADC_SMPR2_SMP11_0', 'ADC_SMPR2_SMP11_1',
    'ADC_SMPR2_SMP11_2', 'ADC_SMPR2_SMP12', 'ADC_SMPR2_SMP12_0', 'ADC_SMPR2_SMP12_1',
    'ADC_SMPR2_SMP12_2', 'ADC_SMPR2_SMP13', 'ADC_SMPR2_SMP13_0', 'ADC_SMPR2_SMP13_1',
    'ADC_SMPR2_SMP13_2', 'ADC_SMPR2_SMP14', 'ADC_SMPR2_SMP14_0', 'ADC_SMPR2_SMP14_1',
    'ADC_SMPR2_SMP14_2', 'ADC_SMPR2_SMP15', 'ADC_SMPR2_SMP15_0', 'ADC_SMPR2_SMP15_1',
    'ADC_SMPR2_SMP15_2', 'ADC_SMPR2_SMP16', 'ADC_SMPR2_SMP16_0', 'ADC_SMPR2_SMP16_1',
    'ADC_SMPR2_SMP16_2', 'ADC_SMPR2_SMP17', 'ADC_SMPR2_SMP17_0', 'ADC_SMPR2_SMP17_1',
    'ADC_SMPR2_SMP17_2', 'ADC_SMPR2_SMP18', 'ADC_SMPR2_SMP18_0', 'ADC_SMPR2_SMP18_1',
    'ADC_SMPR2_SMP18_2', 'ADC_TR1_LT1', 'ADC_TR1_LT1_0', 'ADC_TR1_LT1_1',
    'ADC_TR1_LT1_2', 'ADC_TR1_LT1_3', 'ADC_TR1_LT1_4', 'ADC_TR1_LT1_5', 'ADC_TR1_LT1_6',
    'ADC_TR1_LT1_7', 'ADC_TR1_LT1_8', 'ADC_TR1_LT1_9', 'ADC_TR1_LT1_10',
    'ADC_TR1_LT1_11', 'ADC_TR1_HT1', 'ADC_TR1_HT1_0', 'ADC_TR1_HT1_1', 'ADC_TR1_HT1_2',
    'ADC_TR1_HT1_3', 'ADC_TR1_HT1_4', 'ADC_TR1_HT1_5', 'ADC_TR1_HT1_6', 'ADC_TR1_HT1_7',
    'ADC_TR1_HT1_8', 'ADC_TR1_HT1_9', 'ADC_TR1_HT1_10', 'ADC_TR1_HT1_11', 'ADC_TR2_LT2',
    'ADC_TR2_LT2_0', 'ADC_TR2_LT2_1', 'ADC_TR2_LT2_2', 'ADC_TR2_LT2_3', 'ADC_TR2_LT2_4',
    'ADC_TR2_LT2_5', 'ADC_TR2_LT2_6', 'ADC_TR2_LT2_7', 'ADC_TR2_HT2', 'ADC_TR2_HT2_0',
    'ADC_TR2_HT2_1', 'ADC_TR2_HT2_2', 'ADC_TR2_HT2_3', 'ADC_TR2_HT2_4', 'ADC_TR2_HT2_5',
    'ADC_TR2_HT2_6', 'ADC_TR2_HT2_7', 'ADC_TR3_LT3', 'ADC_TR3_LT3_0', 'ADC_TR3_LT3_1',
    'ADC_TR3_LT3_2', 'ADC_TR3_LT3_3', 'ADC_TR3_LT3_4', 'ADC_TR3_LT3_5', 'ADC_TR3_LT3_6',
    'ADC_TR3_LT3_7', 'ADC_TR3_HT3', 'ADC_TR3_HT3_0', 'ADC_TR3_HT3_1', 'ADC_TR3_HT3_2',
    'ADC_TR3_HT3_3', 'ADC_TR3_HT3_4', 'ADC_TR3_HT3_5', 'ADC_TR3_HT3_6', 'ADC_TR3_HT3_7',
    'ADC_SQR1_L', 'ADC_SQR1_L_0', 'ADC_SQR1_L_1', 'ADC_SQR1_L_2', 'ADC_SQR1_L_3',
    'ADC_SQR1_SQ1', 'ADC_SQR1_SQ1_0', 'ADC_SQR1_SQ1_1', 'ADC_SQR1_SQ1_2',
    'ADC_SQR1_SQ1_3', 'ADC_SQR1_SQ1_4', 'ADC_SQR1_SQ2', 'ADC_SQR1_SQ2_0',
    'ADC_SQR1_SQ2_1', 'ADC_SQR1_SQ2_2', 'ADC_SQR1_SQ2_3', 'ADC_SQR1_SQ2_4',
    'ADC_SQR1_SQ3', 'ADC_SQR1_SQ3_0', 'ADC_SQR1_SQ3_1', 'ADC_SQR1_SQ3_2',
    'ADC_SQR1_SQ3_3', 'ADC_SQR1_SQ3_4', 'ADC_SQR1_SQ4', 'ADC_SQR1_SQ4_0',
    'ADC_SQR1_SQ4_1', 'ADC_SQR1_SQ4_2', 'ADC_SQR1_SQ4_3', 'ADC_SQR1_SQ4_4',
    'ADC_SQR2_SQ5', 'ADC_SQR2_SQ5_0', 'ADC_SQR2_SQ5_1', 'ADC_SQR2_SQ5_2',
    'ADC_SQR2_SQ5_3', 'ADC_SQR2_SQ5_4', 'ADC_SQR2_SQ6', 'ADC_SQR2_SQ6_0',
    'ADC_SQR2_SQ6_1', 'ADC_SQR2_SQ6_2', 'ADC_SQR2_SQ6_3', 'ADC_SQR2_SQ6_4',
    'ADC_SQR2_SQ7', 'ADC_SQR2_SQ7_0', 'ADC_SQR2_SQ7_1', 'ADC_SQR2_SQ7_2',
    'ADC_SQR2_SQ7_3', 'ADC_SQR2_SQ7_4', 'ADC_SQR2_SQ8', 'ADC_SQR2_SQ8_0',
    'ADC_SQR2_SQ8_1', 'ADC_SQR2_SQ8_2', 'ADC_SQR2_SQ8_3', 'ADC_SQR2_SQ8_4',
    'ADC_SQR2_SQ9', 'ADC_SQR2_SQ9_0', 'ADC_SQR2_SQ9_1', 'ADC_SQR2_SQ9_2',
    'ADC_SQR2_SQ9_3', 'ADC_SQR2_SQ9_4', 'ADC_SQR3_SQ10', 'ADC_SQR3_SQ10_0',
    'ADC_SQR3_SQ10_1', 'ADC_SQR3_SQ10_2', 'ADC_SQR3_SQ10_3', 'ADC_SQR3_SQ10_4',
    'ADC_SQR3_SQ11', 'ADC_SQR3_SQ11_0', 'ADC_SQR3_SQ11_1', 'ADC_SQR3_SQ11_2',
    'ADC_SQR3_SQ11_3', 'ADC_SQR3_SQ11_4', 'ADC_SQR3_SQ12', 'ADC_SQR3_SQ12_0',
    'ADC_SQR3_SQ12_1', 'ADC_SQR3_SQ12_2', 'ADC_SQR3_SQ12_3', 'ADC_SQR3_SQ12_4',
    'ADC_SQR3_SQ13', 'ADC_SQR3_SQ13_0', 'ADC_SQR3_SQ13_1', 'ADC_SQR3_SQ13_2',
    'ADC_SQR3_SQ13_3', 'ADC_SQR3_SQ13_4', 'ADC_SQR3_SQ14', 'ADC_SQR3_SQ14_0',
    'ADC_SQR3_SQ14_1', 'ADC_SQR3_SQ14_2', 'ADC_SQR3_SQ14_3', 'ADC_SQR3_SQ14_4',
    'ADC_SQR3_SQ15', 'ADC_SQR3_SQ15_0', 'ADC_SQR3_SQ15_1', 'ADC_SQR3_SQ15_2',
    'ADC_SQR3_SQ15_3', 'ADC_SQR3_SQ15_4', 'ADC_SQR3_SQ16', 'ADC_SQR3_SQ16_0',
    'ADC_SQR3_SQ16_1', 'ADC_SQR3_SQ16_2', 'ADC_SQR3_SQ16_3', 'ADC_SQR3_SQ16_4',
    'ADC_DR_RDATA', 'ADC_DR_RDATA_0', 'ADC_DR_RDATA_1', 'ADC_DR_RDATA_2',
    'ADC_DR_RDATA_3', 'ADC_DR_RDATA_4', 'ADC_DR_RDATA_5', 'ADC_DR_RDATA_6',
    'ADC_DR_RDATA_7', 'ADC_DR_RDATA_8', 'ADC_DR_RDATA_9', 'ADC_DR_RDATA_10',
    'ADC_DR_RDATA_11', 'ADC_DR_RDATA_12', 'ADC_DR_RDATA_13', 'ADC_DR_RDATA_14',
    'ADC_DR_RDATA_15', 'ADC_JSQR_JL', 'ADC_JSQR_JL_0', 'ADC_JSQR_JL_1',
    'ADC_JSQR_JEXTSEL', 'ADC_JSQR_JEXTSEL_0', 'ADC_JSQR_JEXTSEL_1',
    'ADC_JSQR_JEXTSEL_2', 'ADC_JSQR_JEXTSEL_3', 'ADC_JSQR_JEXTEN', 'ADC_JSQR_JEXTEN_0',
    'ADC_JSQR_JEXTEN_1', 'ADC_JSQR_JSQ1', 'ADC_JSQR_JSQ1_0', 'ADC_JSQR_JSQ1_1',
    'ADC_JSQR_JSQ1_2', 'ADC_JSQR_JSQ1_3', 'ADC_JSQR_JSQ1_4', 'ADC_JSQR_JSQ2',
    'ADC_JSQR_JSQ2_0', 'ADC_JSQR_JSQ2_1', 'ADC_JSQR_JSQ2_2', 'ADC_JSQR_JSQ2_3',
    'ADC_JSQR_JSQ2_4', 'ADC_JSQR_JSQ3', 'ADC_JSQR_JSQ3_0', 'ADC_JSQR_JSQ3_1',
    'ADC_JSQR_JSQ3_2', 'ADC_JSQR_JSQ3_3', 'ADC_JSQR_JSQ3_4', 'ADC_JSQR_JSQ4',
    'ADC_JSQR_JSQ4_0', 'ADC_JSQR_JSQ4_1', 'ADC_JSQR_JSQ4_2', 'ADC_JSQR_JSQ4_3',
    'ADC_JSQR_JSQ4_4', 'ADC_OFR1_OFFSET1', 'ADC_OFR1_OFFSET1_0', 'ADC_OFR1_OFFSET1_1',
    'ADC_OFR1_OFFSET1_2', 'ADC_OFR1_OFFSET1_3', 'ADC_OFR1_OFFSET1_4',
    'ADC_OFR1_OFFSET1_5', 'ADC_OFR1_OFFSET1_6', 'ADC_OFR1_OFFSET1_7',
    'ADC_OFR1_OFFSET1_8', 'ADC_OFR1_OFFSET1_9', 'ADC_OFR1_OFFSET1_10',
    'ADC_OFR1_OFFSET1_11', 'ADC_OFR1_OFFSET1_CH', 'ADC_OFR1_OFFSET1_CH_0',
    'ADC_OFR1_OFFSET1_CH_1', 'ADC_OFR1_OFFSET1_CH_2', 'ADC_OFR1_OFFSET1_CH_3',
    'ADC_OFR1_OFFSET1_CH_4', 'ADC_OFR1_OFFSET1_EN', 'ADC_OFR2_OFFSET2',
    'ADC_OFR2_OFFSET2_0', 'ADC_OFR2_OFFSET2_1', 'ADC_OFR2_OFFSET2_2',
    'ADC_OFR2_OFFSET2_3', 'ADC_OFR2_OFFSET2_4', 'ADC_OFR2_OFFSET2_5',
    'ADC_OFR2_OFFSET2_6', 'ADC_OFR2_OFFSET2_7', 'ADC_OFR2_OFFSET2_8',
    'ADC_OFR2_OFFSET2_9', 'ADC_OFR2_OFFSET2_10', 'ADC_OFR2_OFFSET2_11',
    'ADC_OFR2_OFFSET2_CH', 'ADC_OFR2_OFFSET2_CH_0', 'ADC_OFR2_OFFSET2_CH_1',
    'ADC_OFR2_OFFSET2_CH_2', 'ADC_OFR2_OFFSET2_CH_3', 'ADC_OFR2_OFFSET2_CH_4',
    'ADC_OFR2_OFFSET2_EN', 'ADC_OFR3_OFFSET3', 'ADC_OFR3_OFFSET3_0',
    'ADC_OFR3_OFFSET3_1', 'ADC_OFR3_OFFSET3_2', 'ADC_OFR3_OFFSET3_3',
    'ADC_OFR3_OFFSET3_4', 'ADC_OFR3_OFFSET3_5', 'ADC_OFR3_OFFSET3_6',
    'ADC_OFR3_OFFSET3_7', 'ADC_OFR3_OFFSET3_8', 'ADC_OFR3_OFFSET3_9',
    'ADC_OFR3_OFFSET3_10', 'ADC_OFR3_OFFSET3_11', 'ADC_OFR3_OFFSET3_CH',
    'ADC_OFR3_OFFSET3_CH_0', 'ADC_OFR3_OFFSET3_CH_1', 'ADC_OFR3_OFFSET3_CH_2',
    'ADC_OFR3_OFFSET3_CH_3', 'ADC_OFR3_OFFSET3_CH_4', 'ADC_OFR3_OFFSET3_EN',
    'ADC_OFR4_OFFSET4', 'ADC_OFR4_OFFSET4_0', 'ADC_OFR4_OFFSET4_1',
    'ADC_OFR4_OFFSET4_2', 'ADC_OFR4_OFFSET4_3', 'ADC_OFR4_OFFSET4_4',
    'ADC_OFR4_OFFSET4_5', 'ADC_OFR4_OFFSET4_6', 'ADC_OFR4_OFFSET4_7',
    'ADC_OFR4_OFFSET4_8', 'ADC_OFR4_OFFSET4_9', 'ADC_OFR4_OFFSET4_10',
    'ADC_OFR4_OFFSET4_11', 'ADC_OFR4_OFFSET4_CH', 'ADC_OFR4_OFFSET4_CH_0',
    'ADC_OFR4_OFFSET4_CH_1', 'ADC_OFR4_OFFSET4_CH_2', 'ADC_OFR4_OFFSET4_CH_3',
    'ADC_OFR4_OFFSET4_CH_4', 'ADC_OFR4_OFFSET4_EN', 'ADC_JDR1_JDATA',
    'ADC_JDR1_JDATA_0', 'ADC_JDR1_JDATA_1', 'ADC_JDR1_JDATA_2', 'ADC_JDR1_JDATA_3',
    'ADC_JDR1_JDATA_4', 'ADC_JDR1_JDATA_5', 'ADC_JDR1_JDATA_6', 'ADC_JDR1_JDATA_7',
    'ADC_JDR1_JDATA_8', 'ADC_JDR1_JDATA_9', 'ADC_JDR1_JDATA_10', 'ADC_JDR1_JDATA_11',
    'ADC_JDR1_JDATA_12', 'ADC_JDR1_JDATA_13', 'ADC_JDR1_JDATA_14', 'ADC_JDR1_JDATA_15',
    'ADC_JDR2_JDATA', 'ADC_JDR2_JDATA_0', 'ADC_JDR2_JDATA_1', 'ADC_JDR2_JDATA_2',
    'ADC_JDR2_JDATA_3', 'ADC_JDR2_JDATA_4', 'ADC_JDR2_JDATA_5', 'ADC_JDR2_JDATA_6',
    'ADC_JDR2_JDATA_7', 'ADC_JDR2_JDATA_8', 'ADC_JDR2_JDATA_9', 'ADC_JDR2_JDATA_10',
    'ADC_JDR2_JDATA_11', 'ADC_JDR2_JDATA_12', 'ADC_JDR2_JDATA_13', 'ADC_JDR2_JDATA_14',
    'ADC_JDR2_JDATA_15', 'ADC_JDR3_JDATA', 'ADC_JDR3_JDATA_0', 'ADC_JDR3_JDATA_1',
    'ADC_JDR3_JDATA_2', 'ADC_JDR3_JDATA_3', 'ADC_JDR3_JDATA_4', 'ADC_JDR3_JDATA_5',
    'ADC_JDR3_JDATA_6', 'ADC_JDR3_JDATA_7', 'ADC_JDR3_JDATA_8', 'ADC_JDR3_JDATA_9',
    'ADC_JDR3_JDATA_10', 'ADC_JDR3_JDATA_11', 'ADC_JDR3_JDATA_12', 'ADC_JDR3_JDATA_13',
    'ADC_JDR3_JDATA_14', 'ADC_JDR3_JDATA_15', 'ADC_JDR4_JDATA', 'ADC_JDR4_JDATA_0',
    'ADC_JDR4_JDATA_1', 'ADC_JDR4_JDATA_2', 'ADC_JDR4_JDATA_3', 'ADC_JDR4_JDATA_4',
    'ADC_JDR4_JDATA_5', 'ADC_JDR4_JDATA_6', 'ADC_JDR4_JDATA_7', 'ADC_JDR4_JDATA_8',
    'ADC_JDR4_JDATA_9', 'ADC_JDR4_JDATA_10', 'ADC_JDR4_JDATA_11', 'ADC_JDR4_JDATA_12',
    'ADC_JDR4_JDATA_13', 'ADC_JDR4_JDATA_14', 'ADC_JDR4_JDATA_15', 'ADC_AWD2CR_AWD2CH',
    'ADC_AWD2CR_AWD2CH_0', 'ADC_AWD2CR_AWD2CH_1', 'ADC_AWD2CR_AWD2CH_2',
    'ADC_AWD2CR_AWD2CH_3', 'ADC_AWD2CR_AWD2CH_4', 'ADC_AWD2CR_AWD2CH_5',
    'ADC_AWD2CR_AWD2CH_6', 'ADC_AWD2CR_AWD2CH_7', 'ADC_AWD2CR_AWD2CH_8',
    'ADC_AWD2CR_AWD2CH_9', 'ADC_AWD2CR_AWD2CH_10', 'ADC_AWD2CR_AWD2CH_11',
    'ADC_AWD2CR_AWD2CH_12', 'ADC_AWD2CR_AWD2CH_13', 'ADC_AWD2CR_AWD2CH_14',
    'ADC_AWD2CR_AWD2CH_15', 'ADC_AWD2CR_AWD2CH_16', 'ADC_AWD2CR_AWD2CH_17',
    'ADC_AWD3CR_AWD3CH', 'ADC_AWD3CR_AWD3CH_0', 'ADC_AWD3CR_AWD3CH_1',
    'ADC_AWD3CR_AWD3CH_2', 'ADC_AWD3CR_AWD3CH_3', 'ADC_AWD3CR_AWD3CH_4',
    'ADC_AWD3CR_AWD3CH_5', 'ADC_AWD3CR_AWD3CH_6', 'ADC_AWD3CR_AWD3CH_7',
    'ADC_AWD3CR_AWD3CH_8', 'ADC_AWD3CR_AWD3CH_9', 'ADC_AWD3CR_AWD3CH_10',
    'ADC_AWD3CR_AWD3CH_11', 'ADC_AWD3CR_AWD3CH_12', 'ADC_AWD3CR_AWD3CH_13',
    'ADC_AWD3CR_AWD3CH_14', 'ADC_AWD3CR_AWD3CH_15', 'ADC_AWD3CR_AWD3CH_16',
    'ADC_AWD3CR_AWD3CH_17', 'ADC_DIFSEL_DIFSEL', 'ADC_DIFSEL_DIFSEL_0',
    'ADC_DIFSEL_DIFSEL_1', 'ADC_DIFSEL_DIFSEL_2', 'ADC_DIFSEL_DIFSEL_3',
    'ADC_DIFSEL_DIFSEL_4', 'ADC_DIFSEL_DIFSEL_5', 'ADC_DIFSEL_DIFSEL_6',
    'ADC_DIFSEL_DIFSEL_7', 'ADC_DIFSEL_DIFSEL_8', 'ADC_DIFSEL_DIFSEL_9',
    'ADC_DIFSEL_DIFSEL_10', 'ADC_DIFSEL_DIFSEL_11', 'ADC_DIFSEL_DIFSEL_12',
    'ADC_DIFSEL_DIFSEL_13', 'ADC_DIFSEL_DIFSEL_14', 'ADC_DIFSEL_DIFSEL_15',
    'ADC_DIFSEL_DIFSEL_16', 'ADC_DIFSEL_DIFSEL_17', 'ADC_CALFACT_CALFACT_S',
    'ADC_CALFACT_CALFACT_S_0', 'ADC_CALFACT_CALFACT_S_1', 'ADC_CALFACT_CALFACT_S_2',
    'ADC_CALFACT_CALFACT_S_3', 'ADC_CALFACT_CALFACT_S_4', 'ADC_CALFACT_CALFACT_S_5',
    'ADC_CALFACT_CALFACT_S_6', 'ADC_CALFACT_CALFACT_D', 'ADC_CALFACT_CALFACT_D_0',
    'ADC_CALFACT_CALFACT_D_1', 'ADC_CALFACT_CALFACT_D_2', 'ADC_CALFACT_CALFACT_D_3',
    'ADC_CALFACT_CALFACT_D_4', 'ADC_CALFACT_CALFACT_D_5', 'ADC_CALFACT_CALFACT_D_6',
    'ADC12_CSR_ADRDY_MST', 'ADC12_CSR_ADRDY_EOSMP_MST', 'ADC12_CSR_ADRDY_EOC_MST',
    'ADC12_CSR_ADRDY_EOS_MST', 'ADC12_CSR_ADRDY_OVR_MST', 'ADC12_CSR_ADRDY_JEOC_MST',
    'ADC12_CSR_ADRDY_JEOS_MST', 'ADC12_CSR_AWD1_MST', 'ADC12_CSR_AWD2_MST',
    'ADC12_CSR_AWD3_MST', 'ADC12_CSR_JQOVF_MST', 'ADC12_CSR_ADRDY_SLV',
    'ADC12_CSR_ADRDY_EOSMP_SLV', 'ADC12_CSR_ADRDY_EOC_SLV', 'ADC12_CSR_ADRDY_EOS_SLV',
    'ADC12_CSR_ADRDY_OVR_SLV', 'ADC12_CSR_ADRDY_JEOC_SLV', 'ADC12_CSR_ADRDY_JEOS_SLV',
    'ADC12_CSR_AWD1_SLV', 'ADC12_CSR_AWD2_SLV', 'ADC12_CSR_AWD3_SLV',
    'ADC12_CSR_JQOVF_SLV', 'ADC34_CSR_ADRDY_MST', 'ADC34_CSR_ADRDY_EOSMP_MST',
    'ADC34_CSR_ADRDY_EOC_MST', 'ADC34_CSR_ADRDY_EOS_MST', 'ADC34_CSR_ADRDY_OVR_MST',
    'ADC34_CSR_ADRDY_JEOC_MST', 'ADC34_CSR_ADRDY_JEOS_MST', 'ADC34_CSR_AWD1_MST',
    'ADC34_CSR_AWD2_MST', 'ADC34_CSR_AWD3_MST', 'ADC34_CSR_JQOVF_MST',
    'ADC34_CSR_ADRDY_SLV', 'ADC34_CSR_ADRDY_EOSMP_SLV', 'ADC34_CSR_ADRDY_EOC_SLV',
    'ADC34_CSR_ADRDY_EOS_SLV', 'ADC12_CSR_ADRDY_OVR_SLV', 'ADC34_CSR_ADRDY_JEOC_SLV',
    'ADC34_CSR_ADRDY_JEOS_SLV', 'ADC34_CSR_AWD1_SLV', 'ADC34_CSR_AWD2_SLV',
    'ADC34_CSR_AWD3_SLV', 'ADC34_CSR_JQOVF_SLV', 'ADC12_CCR_MULTI', 'ADC12_CCR_MULTI_0',
    'ADC12_CCR_MULTI_1', 'ADC12_CCR_MULTI_2', 'ADC12_CCR_MULTI_3', 'ADC12_CCR_MULTI_4',
    'ADC12_CCR_DELAY', 'ADC12_CCR_DELAY_0', 'ADC12_CCR_DELAY_1', 'ADC12_CCR_DELAY_2',
    'ADC12_CCR_DELAY_3', 'ADC12_CCR_DMACFG', 'ADC12_CCR_MDMA', 'ADC12_CCR_MDMA_0',
    'ADC12_CCR_MDMA_1', 'ADC12_CCR_CKMODE', 'ADC12_CCR_CKMODE_0', 'ADC12_CCR_CKMODE_1',
    'ADC12_CCR_VREFEN', 'ADC12_CCR_TSEN', 'ADC12_CCR_VBATEN', 'ADC34_CCR_MULTI',
    'ADC34_CCR_MULTI_0', 'ADC34_CCR_MULTI_1', 'ADC34_CCR_MULTI_2', 'ADC34_CCR_MULTI_3',
    'ADC34_CCR_MULTI_4', 'ADC34_CCR_DELAY', 'ADC34_CCR_DELAY_0', 'ADC34_CCR_DELAY_1',
    'ADC34_CCR_DELAY_2', 'ADC34_CCR_DELAY_3', 'ADC34_CCR_DMACFG', 'ADC34_CCR_MDMA',
    'ADC34_CCR_MDMA_0', 'ADC34_CCR_MDMA_1', 'ADC34_CCR_CKMODE', 'ADC34_CCR_CKMODE_0',
    'ADC34_CCR_CKMODE_1', 'ADC34_CCR_VREFEN', 'ADC34_CCR_TSEN', 'ADC34_CCR_VBATEN',
    'ADC12_CDR_RDATA_MST', 'ADC12_CDR_RDATA_MST_0', 'ADC12_CDR_RDATA_MST_1',
    'ADC12_CDR_RDATA_MST_2', 'ADC12_CDR_RDATA_MST_3', 'ADC12_CDR_RDATA_MST_4',
    'ADC12_CDR_RDATA_MST_5', 'ADC12_CDR_RDATA_MST_6', 'ADC12_CDR_RDATA_MST_7',
    'ADC12_CDR_RDATA_MST_8', 'ADC12_CDR_RDATA_MST_9', 'ADC12_CDR_RDATA_MST_10',
    'ADC12_CDR_RDATA_MST_11', 'ADC12_CDR_RDATA_MST_12', 'ADC12_CDR_RDATA_MST_13',
    'ADC12_CDR_RDATA_MST_14', 'ADC12_CDR_RDATA_MST_15', 'ADC12_CDR_RDATA_SLV',
    'ADC12_CDR_RDATA_SLV_0', 'ADC12_CDR_RDATA_SLV_1', 'ADC12_CDR_RDATA_SLV_2',
    'ADC12_CDR_RDATA_SLV_3', 'ADC12_CDR_RDATA_SLV_4', 'ADC12_CDR_RDATA_SLV_5',
    'ADC12_CDR_RDATA_SLV_6', 'ADC12_CDR_RDATA_SLV_7', 'ADC12_CDR_RDATA_SLV_8',
    'ADC12_CDR_RDATA_SLV_9', 'ADC12_CDR_RDATA_SLV_10', 'ADC12_CDR_RDATA_SLV_11',
    'ADC12_CDR_RDATA_SLV_12', 'ADC12_CDR_RDATA_SLV_13', 'ADC12_CDR_RDATA_SLV_14',
    'ADC12_CDR_RDATA_SLV_15', 'ADC34_CDR_RDATA_MST', 'ADC34_CDR_RDATA_MST_0',
    'ADC34_CDR_RDATA_MST_1', 'ADC34_CDR_RDATA_MST_2', 'ADC34_CDR_RDATA_MST_3',
    'ADC34_CDR_RDATA_MST_4', 'ADC34_CDR_RDATA_MST_5', 'ADC34_CDR_RDATA_MST_6',
    'ADC34_CDR_RDATA_MST_7', 'ADC34_CDR_RDATA_MST_8', 'ADC34_CDR_RDATA_MST_9',
    'ADC34_CDR_RDATA_MST_10', 'ADC34_CDR_RDATA_MST_11', 'ADC34_CDR_RDATA_MST_12',
    'ADC34_CDR_RDATA_MST_13', 'ADC34_CDR_RDATA_MST_14', 'ADC34_CDR_RDATA_MST_15',
    'ADC34_CDR_RDATA_SLV', 'ADC34_CDR_RDATA_SLV_0', 'ADC34_CDR_RDATA_SLV_1',
    'ADC34_CDR_RDATA_SLV_2', 'ADC34_CDR_RDATA_SLV_3', 'ADC34_CDR_RDATA_SLV_4',
    'ADC34_CDR_RDATA_SLV_5', 'ADC34_CDR_RDATA_SLV_6', 'ADC34_CDR_RDATA_SLV_7',
    'ADC34_CDR_RDATA_SLV_8', 'ADC34_CDR_RDATA_SLV_9', 'ADC34_CDR_RDATA_SLV_10',
    'ADC34_CDR_RDATA_SLV_11', 'ADC34_CDR_RDATA_SLV_12', 'ADC34_CDR_RDATA_SLV_13',
    'ADC34_CDR_RDATA_SLV_14', 'ADC34_CDR_RDATA_SLV_15', 'COMP1_CSR_COMP1EN',
    'COMP1_CSR_COMP1SW1', 'COMP1_CSR_COMP1MODE', 'COMP1_CSR_COMP1MODE_0',
    'COMP1_CSR_COMP1MODE_1', 'COMP1_CSR_COMP1INSEL', 'COMP1_CSR_COMP1INSEL_0',
    'COMP1_CSR_COMP1INSEL_1', 'COMP1_CSR_COMP1INSEL_2', 'COMP1_CSR_COMP1NONINSEL',
    'COMP1_CSR_COMP1OUTSEL', 'COMP1_CSR_COMP1OUTSEL_0', 'COMP1_CSR_COMP1OUTSEL_1',
    'COMP1_CSR_COMP1OUTSEL_2', 'COMP1_CSR_COMP1OUTSEL_3', 'COMP1_CSR_COMP1POL',
    'COMP1_CSR_COMP1HYST', 'COMP1_CSR_COMP1HYST_0', 'COMP1_CSR_COMP1HYST_1',
    'COMP1_CSR_COMP1BLANKING', 'COMP1_CSR_COMP1BLANKING_0', 'COMP1_CSR_COMP1BLANKING_1',
    'COMP1_CSR_COMP1BLANKING_2', 'COMP1_CSR_COMP1OUT', 'COMP1_CSR_COMP1LOCK',
    'COMP2_CSR_COMP2EN', 'COMP2_CSR_COMP2MODE', 'COMP2_CSR_COMP2MODE_0',
    'COMP2_CSR_COMP2MODE_1', 'COMP2_CSR_COMP2INSEL', 'COMP2_CSR_COMP2INSEL_0',
    'COMP2_CSR_COMP2INSEL_1', 'COMP2_CSR_COMP2INSEL_2', 'COMP2_CSR_COMP2NONINSEL',
    'COMP2_CSR_COMP2WNDWEN', 'COMP2_CSR_COMP2OUTSEL', 'COMP2_CSR_COMP2OUTSEL_0',
    'COMP2_CSR_COMP2OUTSEL_1', 'COMP2_CSR_COMP2OUTSEL_2', 'COMP2_CSR_COMP2OUTSEL_3',
    'COMP2_CSR_COMP2POL', 'COMP2_CSR_COMP2HYST', 'COMP2_CSR_COMP2HYST_0',
    'COMP2_CSR_COMP2HYST_1', 'COMP2_CSR_COMP2BLANKING', 'COMP2_CSR_COMP2BLANKING_0',
    'COMP2_CSR_COMP2BLANKING_1', 'COMP2_CSR_COMP2BLANKING_2', 'COMP2_CSR_COMP2OUT',
    'COMP2_CSR_COMP2LOCK', 'COMP3_CSR_COMP3EN', 'COMP3_CSR_COMP3MODE',
    'COMP3_CSR_COMP3MODE_0', 'COMP3_CSR_COMP3MODE_1', 'COMP3_CSR_COMP3INSEL',
    'COMP3_CSR_COMP3INSEL_0', 'COMP3_CSR_COMP3INSEL_1', 'COMP3_CSR_COMP3INSEL_2',
    'COMP3_CSR_COMP3NONINSEL', 'COMP3_CSR_COMP3OUTSEL', 'COMP3_CSR_COMP3OUTSEL_0',
    'COMP3_CSR_COMP3OUTSEL_1', 'COMP3_CSR_COMP3OUTSEL_2', 'COMP3_CSR_COMP3OUTSEL_3',
    'COMP3_CSR_COMP3POL', 'COMP3_CSR_COMP3HYST', 'COMP3_CSR_COMP3HYST_0',
    'COMP3_CSR_COMP3HYST_1', 'COMP3_CSR_COMP3BLANKING', 'COMP3_CSR_COMP3BLANKING_0',
    'COMP3_CSR_COMP3BLANKING_1', 'COMP3_CSR_COMP3BLANKING_2', 'COMP3_CSR_COMP3OUT',
    'COMP3_CSR_COMP3LOCK', 'COMP4_CSR_COMP4EN', 'COMP4_CSR_COMP4MODE',
    'COMP4_CSR_COMP4MODE_0', 'COMP4_CSR_COMP4MODE_1', 'COMP4_CSR_COMP4INSEL',
    'COMP4_CSR_COMP4INSEL_0', 'COMP4_CSR_COMP4INSEL_1', 'COMP4_CSR_COMP4INSEL_2',
    'COMP4_CSR_COMP4NONINSEL', 'COMP4_CSR_COMP4WNDWEN', 'COMP4_CSR_COMP4OUTSEL',
    'COMP4_CSR_COMP4OUTSEL_0', 'COMP4_CSR_COMP4OUTSEL_1', 'COMP4_CSR_COMP4OUTSEL_2',
    'COMP4_CSR_COMP4OUTSEL_3', 'COMP4_CSR_COMP4POL', 'COMP4_CSR_COMP4HYST',
    'COMP4_CSR_COMP4HYST_0', 'COMP4_CSR_COMP4HYST_1', 'COMP4_CSR_COMP4BLANKING',
    'COMP4_CSR_COMP4BLANKING_0', 'COMP4_CSR_COMP4BLANKING_1',
    'COMP4_CSR_COMP4BLANKING_2', 'COMP4_CSR_COMP4OUT', 'COMP4_CSR_COMP4LOCK',
    'COMP5_CSR_COMP5EN', 'COMP5_CSR_COMP5MODE', 'COMP5_CSR_COMP5MODE_0',
    'COMP5_CSR_COMP5MODE_1', 'COMP5_CSR_COMP5INSEL', 'COMP5_CSR_COMP5INSEL_0',
    'COMP5_CSR_COMP5INSEL_1', 'COMP5_CSR_COMP5INSEL_2', 'COMP5_CSR_COMP5NONINSEL',
    'COMP5_CSR_COMP5OUTSEL', 'COMP5_CSR_COMP5OUTSEL_0', 'COMP5_CSR_COMP5OUTSEL_1',
    'COMP5_CSR_COMP5OUTSEL_2', 'COMP5_CSR_COMP5OUTSEL_3', 'COMP5_CSR_COMP5POL',
    'COMP5_CSR_COMP5HYST', 'COMP5_CSR_COMP5HYST_0', 'COMP5_CSR_COMP5HYST_1',
    'COMP5_CSR_COMP5BLANKING', 'COMP5_CSR_COMP5BLANKING_0', 'COMP5_CSR_COMP5BLANKING_1',
    'COMP5_CSR_COMP5BLANKING_2', 'COMP5_CSR_COMP5OUT', 'COMP5_CSR_COMP5LOCK',
    'COMP6_CSR_COMP6EN', 'COMP6_CSR_COMP6MODE', 'COMP6_CSR_COMP6MODE_0',
    'COMP6_CSR_COMP6MODE_1', 'COMP6_CSR_COMP6INSEL', 'COMP6_CSR_COMP6INSEL_0',
    'COMP6_CSR_COMP6INSEL_1', 'COMP6_CSR_COMP6INSEL_2', 'COMP6_CSR_COMP6NONINSEL',
    'COMP6_CSR_COMP6WNDWEN', 'COMP6_CSR_COMP6OUTSEL', 'COMP6_CSR_COMP6OUTSEL_0',
    'COMP6_CSR_COMP6OUTSEL_1', 'COMP6_CSR_COMP6OUTSEL_2', 'COMP6_CSR_COMP6OUTSEL_3',
    'COMP6_CSR_COMP6POL', 'COMP6_CSR_COMP6HYST', 'COMP6_CSR_COMP6HYST_0',
    'COMP6_CSR_COMP6HYST_1', 'COMP6_CSR_COMP6BLANKING', 'COMP6_CSR_COMP6BLANKING_0',
    'COMP6_CSR_COMP6BLANKING_1', 'COMP6_CSR_COMP6BLANKING_2', 'COMP6_CSR_COMP6OUT',
    'COMP6_CSR_COMP6LOCK', 'COMP7_CSR_COMP7EN', 'COMP7_CSR_COMP7MODE',
    'COMP7_CSR_COMP7MODE_0', 'COMP7_CSR_COMP7MODE_1', 'COMP7_CSR_COMP7INSEL',
    'COMP7_CSR_COMP7INSEL_0', 'COMP7_CSR_COMP7INSEL_1', 'COMP7_CSR_COMP7INSEL_2',
    'COMP7_CSR_COMP7NONINSEL', 'COMP7_CSR_COMP7OUTSEL', 'COMP7_CSR_COMP7OUTSEL_0',
    'COMP7_CSR_COMP7OUTSEL_1', 'COMP7_CSR_COMP7OUTSEL_2', 'COMP7_CSR_COMP7OUTSEL_3',
    'COMP7_CSR_COMP7POL', 'COMP7_CSR_COMP7HYST', 'COMP7_CSR_COMP7HYST_0',
    'COMP7_CSR_COMP7HYST_1', 'COMP7_CSR_COMP7BLANKING', 'COMP7_CSR_COMP7BLANKING_0',
    'COMP7_CSR_COMP7BLANKING_1', 'COMP7_CSR_COMP7BLANKING_2', 'COMP7_CSR_COMP7OUT',
    'COMP7_CSR_COMP7LOCK', 'COMP_CSR_COMPxEN', 'COMP_CSR_COMP1SW1',
    'COMP_CSR_COMPxMODE', 'COMP_CSR_COMPxMODE_0', 'COMP_CSR_COMPxMODE_1',
    'COMP_CSR_COMPxINSEL', 'COMP_CSR_COMPxINSEL_0', 'COMP_CSR_COMPxINSEL_1',
    'COMP_CSR_COMPxINSEL_2', 'COMP_CSR_COMPxNONINSEL', 'COMP_CSR_COMPxWNDWEN',
    'COMP_CSR_COMPxOUTSEL', 'COMP_CSR_COMPxOUTSEL_0', 'COMP_CSR_COMPxOUTSEL_1',
    'COMP_CSR_COMPxOUTSEL_2', 'COMP_CSR_COMPxOUTSEL_3', 'COMP_CSR_COMPxPOL',
    'COMP_CSR_COMPxHYST', 'COMP_CSR_COMPxHYST_0', 'COMP_CSR_COMPxHYST_1',
    'COMP_CSR_COMPxBLANKING', 'COMP_CSR_COMPxBLANKING_0', 'COMP_CSR_COMPxBLANKING_1',
    'COMP_CSR_COMPxBLANKING_2', 'COMP_CSR_COMPxOUT', 'COMP_CSR_COMPxLOCK',
    'OPAMP1_CSR_OPAMP1EN', 'OPAMP1_CSR_FORCEVP', 'OPAMP1_CSR_VPSEL',
    'OPAMP1_CSR_VPSEL_0', 'OPAMP1_CSR_VPSEL_1', 'OPAMP1_CSR_VMSEL',
    'OPAMP1_CSR_VMSEL_0', 'OPAMP1_CSR_VMSEL_1', 'OPAMP1_CSR_TCMEN', 'OPAMP1_CSR_VMSSEL',
    'OPAMP1_CSR_VPSSEL', 'OPAMP1_CSR_VPSSEL_0', 'OPAMP1_CSR_VPSSEL_1',
    'OPAMP1_CSR_CALON', 'OPAMP1_CSR_CALSEL', 'OPAMP1_CSR_CALSEL_0',
    'OPAMP1_CSR_CALSEL_1', 'OPAMP1_CSR_PGGAIN', 'OPAMP1_CSR_PGGAIN_0',
    'OPAMP1_CSR_PGGAIN_1', 'OPAMP1_CSR_PGGAIN_2', 'OPAMP1_CSR_PGGAIN_3',
    'OPAMP1_CSR_USERTRIM', 'OPAMP1_CSR_TRIMOFFSETP', 'OPAMP1_CSR_TRIMOFFSETN',
    'OPAMP1_CSR_TSTREF', 'OPAMP1_CSR_OUTCAL', 'OPAMP1_CSR_LOCK', 'OPAMP2_CSR_OPAMP2EN',
    'OPAMP2_CSR_FORCEVP', 'OPAMP2_CSR_VPSEL', 'OPAMP2_CSR_VPSEL_0',
    'OPAMP2_CSR_VPSEL_1', 'OPAMP2_CSR_VMSEL', 'OPAMP2_CSR_VMSEL_0',
    'OPAMP2_CSR_VMSEL_1', 'OPAMP2_CSR_TCMEN', 'OPAMP2_CSR_VMSSEL', 'OPAMP2_CSR_VPSSEL',
    'OPAMP2_CSR_VPSSEL_0', 'OPAMP2_CSR_VPSSEL_1', 'OPAMP2_CSR_CALON',
    'OPAMP2_CSR_CALSEL', 'OPAMP2_CSR_CALSEL_0', 'OPAMP2_CSR_CALSEL_1',
    'OPAMP2_CSR_PGGAIN', 'OPAMP2_CSR_PGGAIN_0', 'OPAMP2_CSR_PGGAIN_1',
    'OPAMP2_CSR_PGGAIN_2', 'OPAMP2_CSR_PGGAIN_3', 'OPAMP2_CSR_USERTRIM',
    'OPAMP2_CSR_TRIMOFFSETP', 'OPAMP2_CSR_TRIMOFFSETN', 'OPAMP2_CSR_TSTREF',
    'OPAMP2_CSR_OUTCAL', 'OPAMP2_CSR_LOCK', 'OPAMP3_CSR_OPAMP3EN', 'OPAMP3_CSR_FORCEVP',
    'OPAMP3_CSR_VPSEL', 'OPAMP3_CSR_VPSEL_0', 'OPAMP3_CSR_VPSEL_1', 'OPAMP3_CSR_VMSEL',
    'OPAMP3_CSR_VMSEL_0', 'OPAMP3_CSR_VMSEL_1', 'OPAMP3_CSR_TCMEN', 'OPAMP3_CSR_VMSSEL',
    'OPAMP3_CSR_VPSSEL', 'OPAMP3_CSR_VPSSEL_0', 'OPAMP3_CSR_VPSSEL_1',
    'OPAMP3_CSR_CALON', 'OPAMP3_CSR_CALSEL', 'OPAMP3_CSR_CALSEL_0',
    'OPAMP3_CSR_CALSEL_1', 'OPAMP3_CSR_PGGAIN', 'OPAMP3_CSR_PGGAIN_0',
    'OPAMP3_CSR_PGGAIN_1', 'OPAMP3_CSR_PGGAIN_2', 'OPAMP3_CSR_PGGAIN_3',
    'OPAMP3_CSR_USERTRIM', 'OPAMP3_CSR_TRIMOFFSETP', 'OPAMP3_CSR_TRIMOFFSETN',
    'OPAMP3_CSR_TSTREF', 'OPAMP3_CSR_OUTCAL', 'OPAMP3_CSR_LOCK', 'OPAMP4_CSR_OPAMP4EN',
    'OPAMP4_CSR_FORCEVP', 'OPAMP4_CSR_VPSEL', 'OPAMP4_CSR_VPSEL_0',
    'OPAMP4_CSR_VPSEL_1', 'OPAMP4_CSR_VMSEL', 'OPAMP4_CSR_VMSEL_0',
    'OPAMP4_CSR_VMSEL_1', 'OPAMP4_CSR_TCMEN', 'OPAMP4_CSR_VMSSEL', 'OPAMP4_CSR_VPSSEL',
    'OPAMP4_CSR_VPSSEL_0', 'OPAMP4_CSR_VPSSEL_1', 'OPAMP4_CSR_CALON',
    'OPAMP4_CSR_CALSEL', 'OPAMP4_CSR_CALSEL_0', 'OPAMP4_CSR_CALSEL_1',
    'OPAMP4_CSR_PGGAIN', 'OPAMP4_CSR_PGGAIN_0', 'OPAMP4_CSR_PGGAIN_1',
    'OPAMP4_CSR_PGGAIN_2', 'OPAMP4_CSR_PGGAIN_3', 'OPAMP4_CSR_USERTRIM',
    'OPAMP4_CSR_TRIMOFFSETP', 'OPAMP4_CSR_TRIMOFFSETN', 'OPAMP4_CSR_TSTREF',
    'OPAMP4_CSR_OUTCAL', 'OPAMP4_CSR_LOCK', 'OPAMP_CSR_OPAMPxEN', 'OPAMP_CSR_FORCEVP',
    'OPAMP_CSR_VPSEL', 'OPAMP_CSR_VPSEL_0', 'OPAMP_CSR_VPSEL_1', 'OPAMP_CSR_VMSEL',
    'OPAMP_CSR_VMSEL_0', 'OPAMP_CSR_VMSEL_1', 'OPAMP_CSR_TCMEN', 'OPAMP_CSR_VMSSEL',
    'OPAMP_CSR_VPSSEL', 'OPAMP_CSR_VPSSEL_0', 'OPAMP_CSR_VPSSEL_1', 'OPAMP_CSR_CALON',
    'OPAMP_CSR_CALSEL', 'OPAMP_CSR_CALSEL_0', 'OPAMP_CSR_CALSEL_1', 'OPAMP_CSR_PGGAIN',
    'OPAMP_CSR_PGGAIN_0', 'OPAMP_CSR_PGGAIN_1', 'OPAMP_CSR_PGGAIN_2',
    'OPAMP_CSR_PGGAIN_3', 'OPAMP_CSR_USERTRIM', 'OPAMP_CSR_TRIMOFFSETP',
    'OPAMP_CSR_TRIMOFFSETN', 'OPAMP_CSR_TSTREF', 'OPAMP_CSR_OUTCAL', 'OPAMP_CSR_LOCK',
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
    'CRC_IDR_IDR', 'CRC_CR_RESET', 'CRC_CR_POLSIZE', 'CRC_CR_POLSIZE_0',
    'CRC_CR_POLSIZE_1', 'CRC_CR_REV_IN', 'CRC_CR_REV_IN_0', 'CRC_CR_REV_IN_1',
    'CRC_CR_REV_OUT', 'CRC_INIT_INIT', 'CRC_POL_POL', 'DAC_CR_EN1', 'DAC_CR_BOFF1',
    'DAC_CR_TEN1', 'DAC_CR_TSEL1', 'DAC_CR_TSEL1_0', 'DAC_CR_TSEL1_1', 'DAC_CR_TSEL1_2',
    'DAC_CR_WAVE1', 'DAC_CR_WAVE1_0', 'DAC_CR_WAVE1_1', 'DAC_CR_MAMP1',
    'DAC_CR_MAMP1_0', 'DAC_CR_MAMP1_1', 'DAC_CR_MAMP1_2', 'DAC_CR_MAMP1_3',
    'DAC_CR_DMAEN1', 'DAC_CR_EN2', 'DAC_CR_BOFF2', 'DAC_CR_TEN2', 'DAC_CR_TSEL2',
    'DAC_CR_TSEL2_0', 'DAC_CR_TSEL2_1', 'DAC_CR_TSEL2_2', 'DAC_CR_WAVE2',
    'DAC_CR_WAVE2_0', 'DAC_CR_WAVE2_1', 'DAC_CR_MAMP2', 'DAC_CR_MAMP2_0',
    'DAC_CR_MAMP2_1', 'DAC_CR_MAMP2_2', 'DAC_CR_MAMP2_3', 'DAC_CR_DMAEN2',
    'DAC_SWTRIGR_SWTRIG1', 'DAC_SWTRIGR_SWTRIG2', 'DAC_DHR12R1_DACC1DHR',
    'DAC_DHR12L1_DACC1DHR', 'DAC_DHR8R1_DACC1DHR', 'DAC_DHR12R2_DACC2DHR',
    'DAC_DHR12L2_DACC2DHR', 'DAC_DHR8R2_DACC2DHR', 'DAC_DHR12RD_DACC1DHR',
    'DAC_DHR12RD_DACC2DHR', 'DAC_DHR12LD_DACC1DHR', 'DAC_DHR12LD_DACC2DHR',
    'DAC_DHR8RD_DACC1DHR', 'DAC_DHR8RD_DACC2DHR', 'DAC_DOR1_DACC1DOR',
    'DAC_DOR2_DACC2DOR', 'DAC_SR_DMAUDR1', 'DAC_SR_DMAUDR2', 'DBGMCU_IDCODE_DEV_ID',
    'DBGMCU_IDCODE_REV_ID', 'DBGMCU_CR_DBG_SLEEP', 'DBGMCU_CR_DBG_STOP',
    'DBGMCU_CR_DBG_STANDBY', 'DBGMCU_CR_TRACE_IOEN', 'DBGMCU_CR_TRACE_MODE',
    'DBGMCU_CR_TRACE_MODE_0', 'DBGMCU_CR_TRACE_MODE_1', 'DBGMCU_APB1_FZ_DBG_TIM2_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM3_STOP', 'DBGMCU_APB1_FZ_DBG_TIM4_STOP',
    'DBGMCU_APB1_FZ_DBG_TIM6_STOP', 'DBGMCU_APB1_FZ_DBG_TIM7_STOP',
    'DBGMCU_APB1_FZ_DBG_RTC_STOP', 'DBGMCU_APB1_FZ_DBG_WWDG_STOP',
    'DBGMCU_APB1_FZ_DBG_IWDG_STOP', 'DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT',
    'DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT', 'DBGMCU_APB1_FZ_DBG_CAN1_STOP',
    'DBGMCU_APB2_FZ_DBG_TIM1_STOP', 'DBGMCU_APB2_FZ_DBG_TIM8_STOP',
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
    'DMA_CPAR_PA', 'DMA_CMAR_MA', 'EXTI_IMR_MR0', 'EXTI_IMR_MR1', 'EXTI_IMR_MR2',
    'EXTI_IMR_MR3', 'EXTI_IMR_MR4', 'EXTI_IMR_MR5', 'EXTI_IMR_MR6', 'EXTI_IMR_MR7',
    'EXTI_IMR_MR8', 'EXTI_IMR_MR9', 'EXTI_IMR_MR10', 'EXTI_IMR_MR11', 'EXTI_IMR_MR12',
    'EXTI_IMR_MR13', 'EXTI_IMR_MR14', 'EXTI_IMR_MR15', 'EXTI_IMR_MR16', 'EXTI_IMR_MR17',
    'EXTI_IMR_MR18', 'EXTI_IMR_MR19', 'EXTI_IMR_MR20', 'EXTI_IMR_MR21', 'EXTI_IMR_MR22',
    'EXTI_IMR_MR23', 'EXTI_IMR_MR24', 'EXTI_IMR_MR25', 'EXTI_IMR_MR26', 'EXTI_IMR_MR27',
    'EXTI_IMR_MR28', 'EXTI_EMR_MR0', 'EXTI_EMR_MR1', 'EXTI_EMR_MR2', 'EXTI_EMR_MR3',
    'EXTI_EMR_MR4', 'EXTI_EMR_MR5', 'EXTI_EMR_MR6', 'EXTI_EMR_MR7', 'EXTI_EMR_MR8',
    'EXTI_EMR_MR9', 'EXTI_EMR_MR10', 'EXTI_EMR_MR11', 'EXTI_EMR_MR12', 'EXTI_EMR_MR13',
    'EXTI_EMR_MR14', 'EXTI_EMR_MR15', 'EXTI_EMR_MR16', 'EXTI_EMR_MR17', 'EXTI_EMR_MR18',
    'EXTI_EMR_MR19', 'EXTI_EMR_MR20', 'EXTI_EMR_MR21', 'EXTI_EMR_MR22', 'EXTI_EMR_MR23',
    'EXTI_EMR_MR24', 'EXTI_EMR_MR25', 'EXTI_EMR_MR26', 'EXTI_EMR_MR27', 'EXTI_EMR_MR28',
    'EXTI_RTSR_TR0', 'EXTI_RTSR_TR1', 'EXTI_RTSR_TR2', 'EXTI_RTSR_TR3', 'EXTI_RTSR_TR4',
    'EXTI_RTSR_TR5', 'EXTI_RTSR_TR6', 'EXTI_RTSR_TR7', 'EXTI_RTSR_TR8', 'EXTI_RTSR_TR9',
    'EXTI_RTSR_TR10', 'EXTI_RTSR_TR11', 'EXTI_RTSR_TR12', 'EXTI_RTSR_TR13',
    'EXTI_RTSR_TR14', 'EXTI_RTSR_TR15', 'EXTI_RTSR_TR16', 'EXTI_RTSR_TR17',
    'EXTI_RTSR_TR18', 'EXTI_RTSR_TR19', 'EXTI_RTSR_TR20', 'EXTI_RTSR_TR21',
    'EXTI_RTSR_TR22', 'EXTI_RTSR_TR23', 'EXTI_RTSR_TR24', 'EXTI_RTSR_TR25',
    'EXTI_RTSR_TR26', 'EXTI_RTSR_TR27', 'EXTI_RTSR_TR28', 'EXTI_FTSR_TR0',
    'EXTI_FTSR_TR1', 'EXTI_FTSR_TR2', 'EXTI_FTSR_TR3', 'EXTI_FTSR_TR4', 'EXTI_FTSR_TR5',
    'EXTI_FTSR_TR6', 'EXTI_FTSR_TR7', 'EXTI_FTSR_TR8', 'EXTI_FTSR_TR9',
    'EXTI_FTSR_TR10', 'EXTI_FTSR_TR11', 'EXTI_FTSR_TR12', 'EXTI_FTSR_TR13',
    'EXTI_FTSR_TR14', 'EXTI_FTSR_TR15', 'EXTI_FTSR_TR16', 'EXTI_FTSR_TR17',
    'EXTI_FTSR_TR18', 'EXTI_FTSR_TR19', 'EXTI_FTSR_TR20', 'EXTI_FTSR_TR21',
    'EXTI_FTSR_TR22', 'EXTI_FTSR_TR23', 'EXTI_FTSR_TR24', 'EXTI_FTSR_TR25',
    'EXTI_FTSR_TR26', 'EXTI_FTSR_TR27', 'EXTI_FTSR_TR28', 'EXTI_SWIER_SWIER0',
    'EXTI_SWIER_SWIER1', 'EXTI_SWIER_SWIER2', 'EXTI_SWIER_SWIER3', 'EXTI_SWIER_SWIER4',
    'EXTI_SWIER_SWIER5', 'EXTI_SWIER_SWIER6', 'EXTI_SWIER_SWIER7', 'EXTI_SWIER_SWIER8',
    'EXTI_SWIER_SWIER9', 'EXTI_SWIER_SWIER10', 'EXTI_SWIER_SWIER11',
    'EXTI_SWIER_SWIER12', 'EXTI_SWIER_SWIER13', 'EXTI_SWIER_SWIER14',
    'EXTI_SWIER_SWIER15', 'EXTI_SWIER_SWIER16', 'EXTI_SWIER_SWIER17',
    'EXTI_SWIER_SWIER18', 'EXTI_SWIER_SWIER19', 'EXTI_SWIER_SWIER20',
    'EXTI_SWIER_SWIER21', 'EXTI_SWIER_SWIER22', 'EXTI_SWIER_SWIER23',
    'EXTI_SWIER_SWIER24', 'EXTI_SWIER_SWIER25', 'EXTI_SWIER_SWIER26',
    'EXTI_SWIER_SWIER27', 'EXTI_SWIER_SWIER28', 'EXTI_PR_PR0', 'EXTI_PR_PR1',
    'EXTI_PR_PR2', 'EXTI_PR_PR3', 'EXTI_PR_PR4', 'EXTI_PR_PR5', 'EXTI_PR_PR6',
    'EXTI_PR_PR7', 'EXTI_PR_PR8', 'EXTI_PR_PR9', 'EXTI_PR_PR10', 'EXTI_PR_PR11',
    'EXTI_PR_PR12', 'EXTI_PR_PR13', 'EXTI_PR_PR14', 'EXTI_PR_PR15', 'EXTI_PR_PR16',
    'EXTI_PR_PR17', 'EXTI_PR_PR18', 'EXTI_PR_PR19', 'EXTI_PR_PR20', 'EXTI_PR_PR21',
    'EXTI_PR_PR22', 'EXTI_PR_PR23', 'EXTI_PR_PR24', 'EXTI_PR_PR25', 'EXTI_PR_PR26',
    'EXTI_PR_PR27', 'EXTI_PR_PR28', 'FLASH_ACR_LATENCY', 'FLASH_ACR_LATENCY_0',
    'FLASH_ACR_LATENCY_1', 'FLASH_ACR_HLFCYA', 'FLASH_ACR_PRFTBE', 'FLASH_ACR_PRFTBS',
    'FLASH_KEYR_FKEYR', 'RDP_KEY', 'FLASH_KEY1', 'FLASH_KEY2', 'FLASH_OPTKEYR_OPTKEYR',
    'FLASH_OPTKEY1', 'FLASH_OPTKEY2', 'FLASH_SR_BSY', 'FLASH_SR_PGERR',
    'FLASH_SR_WRPERR', 'FLASH_SR_EOP', 'FLASH_CR_PG', 'FLASH_CR_PER', 'FLASH_CR_MER',
    'FLASH_CR_OPTPG', 'FLASH_CR_OPTER', 'FLASH_CR_STRT', 'FLASH_CR_LOCK',
    'FLASH_CR_OPTWRE', 'FLASH_CR_ERRIE', 'FLASH_CR_EOPIE', 'FLASH_CR_OBL_LAUNCH',
    'FLASH_AR_FAR', 'FLASH_OBR_OPTERR', 'FLASH_OBR_RDPRT1', 'FLASH_OBR_RDPRT2',
    'FLASH_OBR_USER', 'FLASH_OBR_IWDG_SW', 'FLASH_OBR_nRST_STOP',
    'FLASH_OBR_nRST_STDBY', 'FLASH_WRPR_WRP', 'OB_RDP_RDP', 'OB_RDP_nRDP',
    'OB_USER_USER', 'OB_USER_nUSER', 'OB_WRP0_WRP0', 'OB_WRP0_nWRP0', 'OB_WRP1_WRP1',
    'OB_WRP1_nWRP1', 'OB_WRP2_WRP2', 'OB_WRP2_nWRP2', 'OB_WRP3_WRP3', 'OB_WRP3_nWRP3',
    'GPIO_MODER_MODER0', 'GPIO_MODER_MODER0_0', 'GPIO_MODER_MODER0_1',
    'GPIO_MODER_MODER1', 'GPIO_MODER_MODER1_0', 'GPIO_MODER_MODER1_1',
    'GPIO_MODER_MODER2', 'GPIO_MODER_MODER2_0', 'GPIO_MODER_MODER2_1',
    'GPIO_MODER_MODER3', 'GPIO_MODER_MODER3_0', 'GPIO_MODER_MODER3_1',
    'GPIO_MODER_MODER4', 'GPIO_MODER_MODER4_0', 'GPIO_MODER_MODER4_1',
    'GPIO_MODER_MODER5', 'GPIO_MODER_MODER5_0', 'GPIO_MODER_MODER5_1',
    'GPIO_MODER_MODER6', 'GPIO_MODER_MODER6_0', 'GPIO_MODER_MODER6_1',
    'GPIO_MODER_MODER7', 'GPIO_MODER_MODER7_0', 'GPIO_MODER_MODER7_1',
    'GPIO_MODER_MODER8', 'GPIO_MODER_MODER8_0', 'GPIO_MODER_MODER8_1',
    'GPIO_MODER_MODER9', 'GPIO_MODER_MODER9_0', 'GPIO_MODER_MODER9_1',
    'GPIO_MODER_MODER10', 'GPIO_MODER_MODER10_0', 'GPIO_MODER_MODER10_1',
    'GPIO_MODER_MODER11', 'GPIO_MODER_MODER11_0', 'GPIO_MODER_MODER11_1',
    'GPIO_MODER_MODER12', 'GPIO_MODER_MODER12_0', 'GPIO_MODER_MODER12_1',
    'GPIO_MODER_MODER13', 'GPIO_MODER_MODER13_0', 'GPIO_MODER_MODER13_1',
    'GPIO_MODER_MODER14', 'GPIO_MODER_MODER14_0', 'GPIO_MODER_MODER14_1',
    'GPIO_MODER_MODER15', 'GPIO_MODER_MODER15_0', 'GPIO_MODER_MODER15_1',
    'GPIO_OTYPER_OT_0', 'GPIO_OTYPER_OT_1', 'GPIO_OTYPER_OT_2', 'GPIO_OTYPER_OT_3',
    'GPIO_OTYPER_OT_4', 'GPIO_OTYPER_OT_5', 'GPIO_OTYPER_OT_6', 'GPIO_OTYPER_OT_7',
    'GPIO_OTYPER_OT_8', 'GPIO_OTYPER_OT_9', 'GPIO_OTYPER_OT_10', 'GPIO_OTYPER_OT_11',
    'GPIO_OTYPER_OT_12', 'GPIO_OTYPER_OT_13', 'GPIO_OTYPER_OT_14', 'GPIO_OTYPER_OT_15',
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
    'IWDG_WINR_WIN', 'PWR_CR_LPSDSR', 'PWR_CR_PDDS', 'PWR_CR_CWUF', 'PWR_CR_CSBF',
    'PWR_CR_PVDE', 'PWR_CR_PLS', 'PWR_CR_PLS_0', 'PWR_CR_PLS_1', 'PWR_CR_PLS_2',
    'PWR_CR_PLS_LEV0', 'PWR_CR_PLS_LEV1', 'PWR_CR_PLS_LEV2', 'PWR_CR_PLS_LEV3',
    'PWR_CR_PLS_LEV4', 'PWR_CR_PLS_LEV5', 'PWR_CR_PLS_LEV6', 'PWR_CR_PLS_LEV7',
    'PWR_CR_DBP', 'PWR_CSR_WUF', 'PWR_CSR_SBF', 'PWR_CSR_PVDO', 'PWR_CSR_VREFINTRDYF',
    'PWR_CSR_EWUP1', 'PWR_CSR_EWUP2', 'PWR_CSR_EWUP3', 'RCC_CR_HSION', 'RCC_CR_HSIRDY',
    'RCC_CR_HSITRIM', 'RCC_CR_HSITRIM_0', 'RCC_CR_HSITRIM_1', 'RCC_CR_HSITRIM_2',
    'RCC_CR_HSITRIM_3', 'RCC_CR_HSITRIM_4', 'RCC_CR_HSICAL', 'RCC_CR_HSICAL_0',
    'RCC_CR_HSICAL_1', 'RCC_CR_HSICAL_2', 'RCC_CR_HSICAL_3', 'RCC_CR_HSICAL_4',
    'RCC_CR_HSICAL_5', 'RCC_CR_HSICAL_6', 'RCC_CR_HSICAL_7', 'RCC_CR_HSEON',
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
    'RCC_CFGR_PPRE2_DIV16', 'RCC_CFGR_PLLSRC', 'RCC_CFGR_PLLXTPRE', 'RCC_CFGR_PLLMULL',
    'RCC_CFGR_PLLMULL_0', 'RCC_CFGR_PLLMULL_1', 'RCC_CFGR_PLLMULL_2',
    'RCC_CFGR_PLLMULL_3', 'RCC_CFGR_PLLSRC_HSI_Div2', 'RCC_CFGR_PLLSRC_PREDIV1',
    'RCC_CFGR_PLLXTPRE_PREDIV1', 'RCC_CFGR_PLLXTPRE_PREDIV1_Div2', 'RCC_CFGR_PLLMULL2',
    'RCC_CFGR_PLLMULL3', 'RCC_CFGR_PLLMULL4', 'RCC_CFGR_PLLMULL5', 'RCC_CFGR_PLLMULL6',
    'RCC_CFGR_PLLMULL7', 'RCC_CFGR_PLLMULL8', 'RCC_CFGR_PLLMULL9', 'RCC_CFGR_PLLMULL10',
    'RCC_CFGR_PLLMULL11', 'RCC_CFGR_PLLMULL12', 'RCC_CFGR_PLLMULL13',
    'RCC_CFGR_PLLMULL14', 'RCC_CFGR_PLLMULL15', 'RCC_CFGR_PLLMULL16', 'RCC_CFGR_USBPRE',
    'RCC_CFGR_I2SSRC', 'RCC_CFGR_MCO', 'RCC_CFGR_MCO_0', 'RCC_CFGR_MCO_1',
    'RCC_CFGR_MCO_2', 'RCC_CFGR_MCO_NOCLOCK', 'RCC_CFGR_MCO_LSI', 'RCC_CFGR_MCO_LSE',
    'RCC_CFGR_MCO_SYSCLK', 'RCC_CFGR_MCO_HSI', 'RCC_CFGR_MCO_HSE', 'RCC_CFGR_MCO_PLL',
    'RCC_CFGR_MCOF', 'RCC_CIR_LSIRDYF', 'RCC_CIR_LSERDYF', 'RCC_CIR_HSIRDYF',
    'RCC_CIR_HSERDYF', 'RCC_CIR_PLLRDYF', 'RCC_CIR_CSSF', 'RCC_CIR_LSIRDYIE',
    'RCC_CIR_LSERDYIE', 'RCC_CIR_HSIRDYIE', 'RCC_CIR_HSERDYIE', 'RCC_CIR_PLLRDYIE',
    'RCC_CIR_LSIRDYC', 'RCC_CIR_LSERDYC', 'RCC_CIR_HSIRDYC', 'RCC_CIR_HSERDYC',
    'RCC_CIR_PLLRDYC', 'RCC_CIR_CSSC', 'RCC_APB2RSTR_SYSCFGRST', 'RCC_APB2RSTR_TIM1RST',
    'RCC_APB2RSTR_SPI1RST', 'RCC_APB2RSTR_TIM8RST', 'RCC_APB2RSTR_USART1RST',
    'RCC_APB2RSTR_TIM15RST', 'RCC_APB2RSTR_TIM16RST', 'RCC_APB2RSTR_TIM17RST',
    'RCC_APB1RSTR_TIM2RST', 'RCC_APB1RSTR_TIM3RST', 'RCC_APB1RSTR_TIM4RST',
    'RCC_APB1RSTR_TIM6RST', 'RCC_APB1RSTR_TIM7RST', 'RCC_APB1RSTR_WWDGRST',
    'RCC_APB1RSTR_SPI2RST', 'RCC_APB1RSTR_SPI3RST', 'RCC_APB1RSTR_USART2RST',
    'RCC_APB1RSTR_USART3RST', 'RCC_APB1RSTR_UART4RST', 'RCC_APB1RSTR_UART5RST',
    'RCC_APB1RSTR_I2C1RST', 'RCC_APB1RSTR_I2C2RST', 'RCC_APB1RSTR_USBRST',
    'RCC_APB1RSTR_CAN1RST', 'RCC_APB1RSTR_PWRRST', 'RCC_APB1RSTR_DACRST',
    'RCC_AHBENR_DMA1EN', 'RCC_AHBENR_DMA2EN', 'RCC_AHBENR_SRAMEN', 'RCC_AHBENR_FLITFEN',
    'RCC_AHBENR_CRCEN', 'RCC_AHBENR_GPIOAEN', 'RCC_AHBENR_GPIOBEN',
    'RCC_AHBENR_GPIOCEN', 'RCC_AHBENR_GPIODEN', 'RCC_AHBENR_GPIOEEN',
    'RCC_AHBENR_GPIOFEN', 'RCC_AHBENR_TSEN', 'RCC_AHBENR_ADC12EN', 'RCC_AHBENR_ADC34EN',
    'RCC_APB2ENR_SYSCFGEN', 'RCC_APB2ENR_TIM1EN', 'RCC_APB2ENR_SPI1EN',
    'RCC_APB2ENR_TIM8EN', 'RCC_APB2ENR_USART1EN', 'RCC_APB2ENR_TIM15EN',
    'RCC_APB2ENR_TIM16EN', 'RCC_APB2ENR_TIM17EN', 'RCC_APB1ENR_TIM2EN',
    'RCC_APB1ENR_TIM3EN', 'RCC_APB1ENR_TIM4EN', 'RCC_APB1ENR_TIM6EN',
    'RCC_APB1ENR_TIM7EN', 'RCC_APB1ENR_WWDGEN', 'RCC_APB1ENR_SPI2EN',
    'RCC_APB1ENR_SPI3EN', 'RCC_APB1ENR_USART2EN', 'RCC_APB1ENR_USART3EN',
    'RCC_APB1ENR_UART3EN', 'RCC_APB1ENR_UART4EN', 'RCC_APB1ENR_I2C1EN',
    'RCC_APB1ENR_I2C2EN', 'RCC_APB1ENR_USBEN', 'RCC_APB1ENR_CAN1EN',
    'RCC_APB1ENR_PWREN', 'RCC_APB1ENR_DACEN', 'RCC_BDCR_LSEON', 'RCC_BDCR_LSERDY',
    'RCC_BDCR_LSEBYP', 'RCC_BDCR_LSEDRV', 'RCC_BDCR_LSEDRV_0', 'RCC_BDCR_LSEDRV_1',
    'RCC_BDCR_RTCSEL', 'RCC_BDCR_RTCSEL_0', 'RCC_BDCR_RTCSEL_1',
    'RCC_BDCR_RTCSEL_NOCLOCK', 'RCC_BDCR_RTCSEL_LSE', 'RCC_BDCR_RTCSEL_LSI',
    'RCC_BDCR_RTCSEL_HSE', 'RCC_BDCR_RTCEN', 'RCC_BDCR_BDRST', 'RCC_CSR_LSION',
    'RCC_CSR_LSIRDY', 'RCC_CSR_RMVF', 'RCC_CSR_OBLRSTF', 'RCC_CSR_PINRSTF',
    'RCC_CSR_PORRSTF', 'RCC_CSR_SFTRSTF', 'RCC_CSR_IWDGRSTF', 'RCC_CSR_WWDGRSTF',
    'RCC_CSR_LPWRRSTF', 'RCC_AHBRSTR_GPIOARST', 'RCC_AHBRSTR_GPIOBRST',
    'RCC_AHBRSTR_GPIOCRST', 'RCC_AHBRSTR_GPIODRST', 'RCC_AHBRSTR_GPIOFRST',
    'RCC_AHBRSTR_TSRST', 'RCC_AHBRSTR_ADC12RST', 'RCC_AHBRSTR_ADC34RST',
    'RCC_CFGR2_PREDIV1', 'RCC_CFGR2_PREDIV1_0', 'RCC_CFGR2_PREDIV1_1',
    'RCC_CFGR2_PREDIV1_2', 'RCC_CFGR2_PREDIV1_3', 'RCC_CFGR2_PREDIV1_DIV1',
    'RCC_CFGR2_PREDIV1_DIV2', 'RCC_CFGR2_PREDIV1_DIV3', 'RCC_CFGR2_PREDIV1_DIV4',
    'RCC_CFGR2_PREDIV1_DIV5', 'RCC_CFGR2_PREDIV1_DIV6', 'RCC_CFGR2_PREDIV1_DIV7',
    'RCC_CFGR2_PREDIV1_DIV8', 'RCC_CFGR2_PREDIV1_DIV9', 'RCC_CFGR2_PREDIV1_DIV10',
    'RCC_CFGR2_PREDIV1_DIV11', 'RCC_CFGR2_PREDIV1_DIV12', 'RCC_CFGR2_PREDIV1_DIV13',
    'RCC_CFGR2_PREDIV1_DIV14', 'RCC_CFGR2_PREDIV1_DIV15', 'RCC_CFGR2_PREDIV1_DIV16',
    'RCC_CFGR2_ADCPRE12', 'RCC_CFGR2_ADCPRE12_0', 'RCC_CFGR2_ADCPRE12_1',
    'RCC_CFGR2_ADCPRE12_2', 'RCC_CFGR2_ADCPRE12_3', 'RCC_CFGR2_ADCPRE12_4',
    'RCC_CFGR2_ADCPRE12_NO', 'RCC_CFGR2_ADCPRE12_DIV1', 'RCC_CFGR2_ADCPRE12_DIV2',
    'RCC_CFGR2_ADCPRE12_DIV4', 'RCC_CFGR2_ADCPRE12_DIV6', 'RCC_CFGR2_ADCPRE12_DIV8',
    'RCC_CFGR2_ADCPRE12_DIV10', 'RCC_CFGR2_ADCPRE12_DIV12', 'RCC_CFGR2_ADCPRE12_DIV16',
    'RCC_CFGR2_ADCPRE12_DIV32', 'RCC_CFGR2_ADCPRE12_DIV64', 'RCC_CFGR2_ADCPRE12_DIV128',
    'RCC_CFGR2_ADCPRE12_DIV256', 'RCC_CFGR2_ADCPRE34', 'RCC_CFGR2_ADCPRE34_0',
    'RCC_CFGR2_ADCPRE34_1', 'RCC_CFGR2_ADCPRE34_2', 'RCC_CFGR2_ADCPRE34_3',
    'RCC_CFGR2_ADCPRE34_4', 'RCC_CFGR2_ADCPRE34_NO', 'RCC_CFGR2_ADCPRE34_DIV1',
    'RCC_CFGR2_ADCPRE34_DIV2', 'RCC_CFGR2_ADCPRE34_DIV4', 'RCC_CFGR2_ADCPRE34_DIV6',
    'RCC_CFGR2_ADCPRE34_DIV8', 'RCC_CFGR2_ADCPRE34_DIV10', 'RCC_CFGR2_ADCPRE34_DIV12',
    'RCC_CFGR2_ADCPRE34_DIV16', 'RCC_CFGR2_ADCPRE34_DIV32', 'RCC_CFGR2_ADCPRE34_DIV64',
    'RCC_CFGR2_ADCPRE34_DIV128', 'RCC_CFGR2_ADCPRE34_DIV256', 'RCC_CFGR3_USART1SW',
    'RCC_CFGR3_USART1SW_0', 'RCC_CFGR3_USART1SW_1', 'RCC_CFGR3_I2CSW',
    'RCC_CFGR3_I2C1SW', 'RCC_CFGR3_I2C2SW', 'RCC_CFGR3_TIMSW', 'RCC_CFGR3_TIM1SW',
    'RCC_CFGR3_TIM8SW', 'RCC_CFGR3_USART2SW', 'RCC_CFGR3_USART2SW_0',
    'RCC_CFGR3_USART2SW_1', 'RCC_CFGR3_USART3SW', 'RCC_CFGR3_USART3SW_0',
    'RCC_CFGR3_USART3SW_1', 'RCC_CFGR3_UART4SW', 'RCC_CFGR3_UART4SW_0',
    'RCC_CFGR3_UART4SW_1', 'RCC_CFGR3_UART5SW', 'RCC_CFGR3_UART5SW_0',
    'RCC_CFGR3_UART5SW_1', 'RTC_TR_PM', 'RTC_TR_HT', 'RTC_TR_HT_0', 'RTC_TR_HT_1',
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
    'RTC_CR_POL', 'RTC_CR_COSEL', 'RTC_CR_BCK', 'RTC_CR_SUB1H', 'RTC_CR_ADD1H',
    'RTC_CR_TSIE', 'RTC_CR_WUTIE', 'RTC_CR_ALRBIE', 'RTC_CR_ALRAIE', 'RTC_CR_TSE',
    'RTC_CR_WUTE', 'RTC_CR_ALRBE', 'RTC_CR_ALRAE', 'RTC_CR_FMT', 'RTC_CR_BYPSHAD',
    'RTC_CR_REFCKON', 'RTC_CR_TSEDGE', 'RTC_CR_WUCKSEL', 'RTC_CR_WUCKSEL_0',
    'RTC_CR_WUCKSEL_1', 'RTC_CR_WUCKSEL_2', 'RTC_ISR_RECALPF', 'RTC_ISR_TAMP3F',
    'RTC_ISR_TAMP2F', 'RTC_ISR_TAMP1F', 'RTC_ISR_TSOVF', 'RTC_ISR_TSF', 'RTC_ISR_WUTF',
    'RTC_ISR_ALRBF', 'RTC_ISR_ALRAF', 'RTC_ISR_INIT', 'RTC_ISR_INITF', 'RTC_ISR_RSF',
    'RTC_ISR_INITS', 'RTC_ISR_SHPF', 'RTC_ISR_WUTWF', 'RTC_ISR_ALRBWF',
    'RTC_ISR_ALRAWF', 'RTC_PRER_PREDIV_A', 'RTC_PRER_PREDIV_S', 'RTC_WUTR_WUT',
    'RTC_ALRMAR_MSK4', 'RTC_ALRMAR_WDSEL', 'RTC_ALRMAR_DT', 'RTC_ALRMAR_DT_0',
    'RTC_ALRMAR_DT_1', 'RTC_ALRMAR_DU', 'RTC_ALRMAR_DU_0', 'RTC_ALRMAR_DU_1',
    'RTC_ALRMAR_DU_2', 'RTC_ALRMAR_DU_3', 'RTC_ALRMAR_MSK3', 'RTC_ALRMAR_PM',
    'RTC_ALRMAR_HT', 'RTC_ALRMAR_HT_0', 'RTC_ALRMAR_HT_1', 'RTC_ALRMAR_HU',
    'RTC_ALRMAR_HU_0', 'RTC_ALRMAR_HU_1', 'RTC_ALRMAR_HU_2', 'RTC_ALRMAR_HU_3',
    'RTC_ALRMAR_MSK2', 'RTC_ALRMAR_MNT', 'RTC_ALRMAR_MNT_0', 'RTC_ALRMAR_MNT_1',
    'RTC_ALRMAR_MNT_2', 'RTC_ALRMAR_MNU', 'RTC_ALRMAR_MNU_0', 'RTC_ALRMAR_MNU_1',
    'RTC_ALRMAR_MNU_2', 'RTC_ALRMAR_MNU_3', 'RTC_ALRMAR_MSK1', 'RTC_ALRMAR_ST',
    'RTC_ALRMAR_ST_0', 'RTC_ALRMAR_ST_1', 'RTC_ALRMAR_ST_2', 'RTC_ALRMAR_SU',
    'RTC_ALRMAR_SU_0', 'RTC_ALRMAR_SU_1', 'RTC_ALRMAR_SU_2', 'RTC_ALRMAR_SU_3',
    'RTC_ALRMBR_MSK4', 'RTC_ALRMBR_WDSEL', 'RTC_ALRMBR_DT', 'RTC_ALRMBR_DT_0',
    'RTC_ALRMBR_DT_1', 'RTC_ALRMBR_DU', 'RTC_ALRMBR_DU_0', 'RTC_ALRMBR_DU_1',
    'RTC_ALRMBR_DU_2', 'RTC_ALRMBR_DU_3', 'RTC_ALRMBR_MSK3', 'RTC_ALRMBR_PM',
    'RTC_ALRMBR_HT', 'RTC_ALRMBR_HT_0', 'RTC_ALRMBR_HT_1', 'RTC_ALRMBR_HU',
    'RTC_ALRMBR_HU_0', 'RTC_ALRMBR_HU_1', 'RTC_ALRMBR_HU_2', 'RTC_ALRMBR_HU_3',
    'RTC_ALRMBR_MSK2', 'RTC_ALRMBR_MNT', 'RTC_ALRMBR_MNT_0', 'RTC_ALRMBR_MNT_1',
    'RTC_ALRMBR_MNT_2', 'RTC_ALRMBR_MNU', 'RTC_ALRMBR_MNU_0', 'RTC_ALRMBR_MNU_1',
    'RTC_ALRMBR_MNU_2', 'RTC_ALRMBR_MNU_3', 'RTC_ALRMBR_MSK1', 'RTC_ALRMBR_ST',
    'RTC_ALRMBR_ST_0', 'RTC_ALRMBR_ST_1', 'RTC_ALRMBR_ST_2', 'RTC_ALRMBR_SU',
    'RTC_ALRMBR_SU_0', 'RTC_ALRMBR_SU_1', 'RTC_ALRMBR_SU_2', 'RTC_ALRMBR_SU_3',
    'RTC_WPR_KEY', 'RTC_SSR_SS', 'RTC_SHIFTR_SUBFS', 'RTC_SHIFTR_ADD1S', 'RTC_TSTR_PM',
    'RTC_TSTR_HT', 'RTC_TSTR_HT_0', 'RTC_TSTR_HT_1', 'RTC_TSTR_HU', 'RTC_TSTR_HU_0',
    'RTC_TSTR_HU_1', 'RTC_TSTR_HU_2', 'RTC_TSTR_HU_3', 'RTC_TSTR_MNT', 'RTC_TSTR_MNT_0',
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
    'RTC_CALR_CALM_6', 'RTC_CALR_CALM_7', 'RTC_CALR_CALM_8', 'RTC_TAFCR_ALARMOUTTYPE',
    'RTC_TAFCR_TAMPPUDIS', 'RTC_TAFCR_TAMPPRCH', 'RTC_TAFCR_TAMPPRCH_0',
    'RTC_TAFCR_TAMPPRCH_1', 'RTC_TAFCR_TAMPFLT', 'RTC_TAFCR_TAMPFLT_0',
    'RTC_TAFCR_TAMPFLT_1', 'RTC_TAFCR_TAMPFREQ', 'RTC_TAFCR_TAMPFREQ_0',
    'RTC_TAFCR_TAMPFREQ_1', 'RTC_TAFCR_TAMPFREQ_2', 'RTC_TAFCR_TAMPTS',
    'RTC_TAFCR_TAMP3TRG', 'RTC_TAFCR_TAMP3E', 'RTC_TAFCR_TAMP2TRG', 'RTC_TAFCR_TAMP2E',
    'RTC_TAFCR_TAMPIE', 'RTC_TAFCR_TAMP1TRG', 'RTC_TAFCR_TAMP1E', 'RTC_ALRMASSR_MASKSS',
    'RTC_ALRMASSR_MASKSS_0', 'RTC_ALRMASSR_MASKSS_1', 'RTC_ALRMASSR_MASKSS_2',
    'RTC_ALRMASSR_MASKSS_3', 'RTC_ALRMASSR_SS', 'RTC_ALRMBSSR_MASKSS',
    'RTC_ALRMBSSR_MASKSS_0', 'RTC_ALRMBSSR_MASKSS_1', 'RTC_ALRMBSSR_MASKSS_2',
    'RTC_ALRMBSSR_MASKSS_3', 'RTC_ALRMBSSR_SS', 'RTC_BKP0R', 'RTC_BKP1R', 'RTC_BKP2R',
    'RTC_BKP3R', 'RTC_BKP4R', 'RTC_BKP5R', 'RTC_BKP6R', 'RTC_BKP7R', 'RTC_BKP8R',
    'RTC_BKP9R', 'RTC_BKP10R', 'RTC_BKP11R', 'RTC_BKP12R', 'RTC_BKP13R', 'RTC_BKP14R',
    'RTC_BKP15R', 'SPI_CR1_CPHA', 'SPI_CR1_CPOL', 'SPI_CR1_MSTR', 'SPI_CR1_BR',
    'SPI_CR1_BR_0', 'SPI_CR1_BR_1', 'SPI_CR1_BR_2', 'SPI_CR1_SPE', 'SPI_CR1_LSBFIRST',
    'SPI_CR1_SSI', 'SPI_CR1_SSM', 'SPI_CR1_RXONLY', 'SPI_CR1_CRCL', 'SPI_CR1_CRCNEXT',
    'SPI_CR1_CRCEN', 'SPI_CR1_BIDIOE', 'SPI_CR1_BIDIMODE', 'SPI_CR2_RXDMAEN',
    'SPI_CR2_TXDMAEN', 'SPI_CR2_SSOE', 'SPI_CR2_NSSP', 'SPI_CR2_FRF', 'SPI_CR2_ERRIE',
    'SPI_CR2_RXNEIE', 'SPI_CR2_TXEIE', 'SPI_CR2_DS', 'SPI_CR2_DS_0', 'SPI_CR2_DS_1',
    'SPI_CR2_DS_2', 'SPI_CR2_DS_3', 'SPI_CR2_FRXTH', 'SPI_CR2_LDMARX', 'SPI_CR2_LDMATX',
    'SPI_SR_RXNE', 'SPI_SR_TXE', 'SPI_SR_CRCERR', 'SPI_SR_MODF', 'SPI_SR_OVR',
    'SPI_SR_BSY', 'SPI_SR_FRE', 'SPI_SR_FRLVL', 'SPI_SR_FRLVL_0', 'SPI_SR_FRLVL_1',
    'SPI_SR_FTLVL', 'SPI_SR_FTLVL_0', 'SPI_SR_FTLVL_1', 'SPI_DR_DR',
    'SPI_CRCPR_CRCPOLY', 'SPI_RXCRCR_RXCRC', 'SPI_TXCRCR_TXCRC', 'SPI_I2SCFGR_CHLEN',
    'SPI_I2SCFGR_DATLEN', 'SPI_I2SCFGR_DATLEN_0', 'SPI_I2SCFGR_DATLEN_1',
    'SPI_I2SCFGR_CKPOL', 'SPI_I2SCFGR_I2SSTD', 'SPI_I2SCFGR_I2SSTD_0',
    'SPI_I2SCFGR_I2SSTD_1', 'SPI_I2SCFGR_PCMSYNC', 'SPI_I2SCFGR_I2SCFG',
    'SPI_I2SCFGR_I2SCFG_0', 'SPI_I2SCFGR_I2SCFG_1', 'SPI_I2SCFGR_I2SE',
    'SPI_I2SCFGR_I2SMOD', 'SPI_I2SPR_I2SDIV', 'SPI_I2SPR_ODD', 'SPI_I2SPR_MCKOE',
    'SYSCFG_CFGR1_MEM_MODE', 'SYSCFG_CFGR1_MEM_MODE_0', 'SYSCFG_CFGR1_MEM_MODE_1',
    'SYSCFG_CFGR1_USB_IT_RMP', 'SYSCFG_CFGR1_TIM1_ITR3_RMP',
    'SYSCFG_CFGR1_DAC_TRIG_RMP', 'SYSCFG_CFGR1_ADC24_DMA_RMP',
    'SYSCFG_CFGR1_TIM16_DMA_RMP', 'SYSCFG_CFGR1_TIM17_DMA_RMP',
    'SYSCFG_CFGR1_TIM6DAC1_DMA_RMP', 'SYSCFG_CFGR1_TIM7DAC2_DMA_RMP',
    'SYSCFG_CFGR1_I2C_PB6_FMP', 'SYSCFG_CFGR1_I2C_PB7_FMP', 'SYSCFG_CFGR1_I2C_PB8_FMP',
    'SYSCFG_CFGR1_I2C_PB9_FMP', 'SYSCFG_CFGR1_I2C1_FMP', 'SYSCFG_CFGR1_I2C2_FMP',
    'SYSCFG_CFGR1_ENCODER_MODE', 'SYSCFG_CFGR1_ENCODER_MODE_0',
    'SYSCFG_CFGR1_ENCODER_MODE_1', 'SYSCFG_CFGR1_FPU_IE', 'SYSCFG_CFGR1_FPU_IE_0',
    'SYSCFG_CFGR1_FPU_IE_1', 'SYSCFG_CFGR1_FPU_IE_2', 'SYSCFG_CFGR1_FPU_IE_3',
    'SYSCFG_CFGR1_FPU_IE_4', 'SYSCFG_CFGR1_FPU_IE_5', 'SYSCFG_RCR_PAGE0',
    'SYSCFG_RCR_PAGE1', 'SYSCFG_RCR_PAGE2', 'SYSCFG_RCR_PAGE3', 'SYSCFG_RCR_PAGE4',
    'SYSCFG_RCR_PAGE5', 'SYSCFG_RCR_PAGE6', 'SYSCFG_RCR_PAGE7', 'SYSCFG_EXTICR1_EXTI0',
    'SYSCFG_EXTICR1_EXTI1', 'SYSCFG_EXTICR1_EXTI2', 'SYSCFG_EXTICR1_EXTI3',
    'SYSCFG_EXTICR1_EXTI0_PA', 'SYSCFG_EXTICR1_EXTI0_PB', 'SYSCFG_EXTICR1_EXTI0_PC',
    'SYSCFG_EXTICR1_EXTI0_PD', 'SYSCFG_EXTICR1_EXTI0_PE', 'SYSCFG_EXTICR1_EXTI0_PF',
    'SYSCFG_EXTICR1_EXTI1_PA', 'SYSCFG_EXTICR1_EXTI1_PB', 'SYSCFG_EXTICR1_EXTI1_PC',
    'SYSCFG_EXTICR1_EXTI1_PD', 'SYSCFG_EXTICR1_EXTI1_PE', 'SYSCFG_EXTICR1_EXTI1_PF',
    'SYSCFG_EXTICR1_EXTI2_PA', 'SYSCFG_EXTICR1_EXTI2_PB', 'SYSCFG_EXTICR1_EXTI2_PC',
    'SYSCFG_EXTICR1_EXTI2_PD', 'SYSCFG_EXTICR1_EXTI2_PE', 'SYSCFG_EXTICR1_EXTI2_PF',
    'SYSCFG_EXTICR1_EXTI3_PA', 'SYSCFG_EXTICR1_EXTI3_PB', 'SYSCFG_EXTICR1_EXTI3_PC',
    'SYSCFG_EXTICR1_EXTI3_PD', 'SYSCFG_EXTICR1_EXTI3_PE', 'SYSCFG_EXTIRCR_EXTI4',
    'SYSCFG_EXTIRCR_EXTI5', 'SYSCFG_EXTIRCR_EXTI6', 'SYSCFG_EXTIRCR_EXTI7',
    'SYSCFG_EXTIRCR_EXTI4_PA', 'SYSCFG_EXTIRCR_EXTI4_PB', 'SYSCFG_EXTIRCR_EXTI4_PC',
    'SYSCFG_EXTIRCR_EXTI4_PD', 'SYSCFG_EXTIRCR_EXTI4_PE', 'SYSCFG_EXTIRCR_EXTI4_PF',
    'SYSCFG_EXTIRCR_EXTI5_PA', 'SYSCFG_EXTIRCR_EXTI5_PB', 'SYSCFG_EXTIRCR_EXTI5_PC',
    'SYSCFG_EXTIRCR_EXTI5_PD', 'SYSCFG_EXTIRCR_EXTI5_PE', 'SYSCFG_EXTIRCR_EXTI5_PF',
    'SYSCFG_EXTIRCR_EXTI6_PA', 'SYSCFG_EXTIRCR_EXTI6_PB', 'SYSCFG_EXTIRCR_EXTI6_PC',
    'SYSCFG_EXTIRCR_EXTI6_PD', 'SYSCFG_EXTIRCR_EXTI6_PE', 'SYSCFG_EXTIRCR_EXTI6_PF',
    'SYSCFG_EXTIRCR_EXTI7_PA', 'SYSCFG_EXTIRCR_EXTI7_PB', 'SYSCFG_EXTIRCR_EXTI7_PC',
    'SYSCFG_EXTIRCR_EXTI7_PD', 'SYSCFG_EXTIRCR_EXTI7_PE', 'SYSCFG_EXTICR3_EXTI8',
    'SYSCFG_EXTICR3_EXTI9', 'SYSCFG_EXTICR3_EXTI10', 'SYSCFG_EXTICR3_EXTI11',
    'SYSCFG_EXTICR3_EXTI8_PA', 'SYSCFG_EXTICR3_EXTI8_PB', 'SYSCFG_EXTICR3_EXTI8_PC',
    'SYSCFG_EXTICR3_EXTI8_PD', 'SYSCFG_EXTICR3_EXTI8_PE', 'SYSCFG_EXTICR3_EXTI9_PA',
    'SYSCFG_EXTICR3_EXTI9_PB', 'SYSCFG_EXTICR3_EXTI9_PC', 'SYSCFG_EXTICR3_EXTI9_PD',
    'SYSCFG_EXTICR3_EXTI9_PE', 'SYSCFG_EXTICR3_EXTI9_PF', 'SYSCFG_EXTICR3_EXTI10_PA',
    'SYSCFG_EXTICR3_EXTI10_PB', 'SYSCFG_EXTICR3_EXTI10_PC', 'SYSCFG_EXTICR3_EXTI10_PD',
    'SYSCFG_EXTICR3_EXTI10_PE', 'SYSCFG_EXTICR3_EXTI10_PF', 'SYSCFG_EXTICR3_EXTI11_PA',
    'SYSCFG_EXTICR3_EXTI11_PB', 'SYSCFG_EXTICR3_EXTI11_PC', 'SYSCFG_EXTICR3_EXTI11_PD',
    'SYSCFG_EXTICR3_EXTI11_PE', 'SYSCFG_EXTICR4_EXTI12', 'SYSCFG_EXTICR4_EXTI13',
    'SYSCFG_EXTICR4_EXTI14', 'SYSCFG_EXTICR4_EXTI15', 'SYSCFG_EXTICR4_EXTI12_PA',
    'SYSCFG_EXTICR4_EXTI12_PB', 'SYSCFG_EXTICR4_EXTI12_PC', 'SYSCFG_EXTICR4_EXTI12_PD',
    'SYSCFG_EXTICR4_EXTI12_PE', 'SYSCFG_EXTICR4_EXTI13_PA', 'SYSCFG_EXTICR4_EXTI13_PB',
    'SYSCFG_EXTICR4_EXTI13_PC', 'SYSCFG_EXTICR4_EXTI13_PD', 'SYSCFG_EXTICR4_EXTI13_PE',
    'SYSCFG_EXTICR4_EXTI14_PA', 'SYSCFG_EXTICR4_EXTI14_PB', 'SYSCFG_EXTICR4_EXTI14_PC',
    'SYSCFG_EXTICR4_EXTI14_PD', 'SYSCFG_EXTICR4_EXTI14_PE', 'SYSCFG_EXTICR4_EXTI15_PA',
    'SYSCFG_EXTICR4_EXTI15_PB', 'SYSCFG_EXTICR4_EXTI15_PC', 'SYSCFG_EXTICR4_EXTI15_PD',
    'SYSCFG_EXTICR4_EXTI15_PE', 'SYSCFG_CFGR2_LOCKUP_LOCK',
    'SYSCFG_CFGR2_SRAM_PARITY_LOCK', 'SYSCFG_CFGR2_PVD_LOCK',
    'SYSCFG_CFGR2_BYP_ADDR_PAR', 'SYSCFG_CFGR2_SRAM_PE', 'TIM_CR1_CEN', 'TIM_CR1_UDIS',
    'TIM_CR1_URS', 'TIM_CR1_OPM', 'TIM_CR1_DIR', 'TIM_CR1_CMS', 'TIM_CR1_CMS_0',
    'TIM_CR1_CMS_1', 'TIM_CR1_ARPE', 'TIM_CR1_CKD', 'TIM_CR1_CKD_0', 'TIM_CR1_CKD_1',
    'TIM_CR1_UIFREMAP', 'TIM_CR2_CCPC', 'TIM_CR2_CCUS', 'TIM_CR2_CCDS', 'TIM_CR2_MMS',
    'TIM_CR2_MMS_0', 'TIM_CR2_MMS_1', 'TIM_CR2_MMS_2', 'TIM_CR2_TI1S', 'TIM_CR2_OIS1',
    'TIM_CR2_OIS1N', 'TIM_CR2_OIS2', 'TIM_CR2_OIS2N', 'TIM_CR2_OIS3', 'TIM_CR2_OIS3N',
    'TIM_CR2_OIS4', 'TIM_CR2_OIS5', 'TIM_CR2_OIS6', 'TIM_CR2_MMS2', 'TIM_CR2_MMS2_0',
    'TIM_CR2_MMS2_1', 'TIM_CR2_MMS2_2', 'TIM_CR2_MMS2_3', 'TIM_SMCR_SMS',
    'TIM_SMCR_SMS_0', 'TIM_SMCR_SMS_1', 'TIM_SMCR_SMS_2', 'TIM_SMCR_SMS_3',
    'TIM_SMCR_OCCS', 'TIM_SMCR_TS', 'TIM_SMCR_TS_0', 'TIM_SMCR_TS_1', 'TIM_SMCR_TS_2',
    'TIM_SMCR_MSM', 'TIM_SMCR_ETF', 'TIM_SMCR_ETF_0', 'TIM_SMCR_ETF_1',
    'TIM_SMCR_ETF_2', 'TIM_SMCR_ETF_3', 'TIM_SMCR_ETPS', 'TIM_SMCR_ETPS_0',
    'TIM_SMCR_ETPS_1', 'TIM_SMCR_ECE', 'TIM_SMCR_ETP', 'TIM_DIER_UIE', 'TIM_DIER_CC1IE',
    'TIM_DIER_CC2IE', 'TIM_DIER_CC3IE', 'TIM_DIER_CC4IE', 'TIM_DIER_COMIE',
    'TIM_DIER_TIE', 'TIM_DIER_BIE', 'TIM_DIER_UDE', 'TIM_DIER_CC1DE', 'TIM_DIER_CC2DE',
    'TIM_DIER_CC3DE', 'TIM_DIER_CC4DE', 'TIM_DIER_COMDE', 'TIM_DIER_TDE', 'TIM_SR_UIF',
    'TIM_SR_CC1IF', 'TIM_SR_CC2IF', 'TIM_SR_CC3IF', 'TIM_SR_CC4IF', 'TIM_SR_COMIF',
    'TIM_SR_TIF', 'TIM_SR_BIF', 'TIM_SR_B2IF', 'TIM_SR_CC1OF', 'TIM_SR_CC2OF',
    'TIM_SR_CC3OF', 'TIM_SR_CC4OF', 'TIM_SR_CC5IF', 'TIM_SR_CC6IF', 'TIM_EGR_UG',
    'TIM_EGR_CC1G', 'TIM_EGR_CC2G', 'TIM_EGR_CC3G', 'TIM_EGR_CC4G', 'TIM_EGR_COMG',
    'TIM_EGR_TG', 'TIM_EGR_BG', 'TIM_EGR_B2G', 'TIM_CCMR1_CC1S', 'TIM_CCMR1_CC1S_0',
    'TIM_CCMR1_CC1S_1', 'TIM_CCMR1_OC1FE', 'TIM_CCMR1_OC1PE', 'TIM_CCMR1_OC1M',
    'TIM_CCMR1_OC1M_0', 'TIM_CCMR1_OC1M_1', 'TIM_CCMR1_OC1M_2', 'TIM_CCMR1_OC1M_3',
    'TIM_CCMR1_OC1CE', 'TIM_CCMR1_CC2S', 'TIM_CCMR1_CC2S_0', 'TIM_CCMR1_CC2S_1',
    'TIM_CCMR1_OC2FE', 'TIM_CCMR1_OC2PE', 'TIM_CCMR1_OC2M', 'TIM_CCMR1_OC2M_0',
    'TIM_CCMR1_OC2M_1', 'TIM_CCMR1_OC2M_2', 'TIM_CCMR1_OC2M_3', 'TIM_CCMR1_OC2CE',
    'TIM_CCMR1_IC1PSC', 'TIM_CCMR1_IC1PSC_0', 'TIM_CCMR1_IC1PSC_1', 'TIM_CCMR1_IC1F',
    'TIM_CCMR1_IC1F_0', 'TIM_CCMR1_IC1F_1', 'TIM_CCMR1_IC1F_2', 'TIM_CCMR1_IC1F_3',
    'TIM_CCMR1_IC2PSC', 'TIM_CCMR1_IC2PSC_0', 'TIM_CCMR1_IC2PSC_1', 'TIM_CCMR1_IC2F',
    'TIM_CCMR1_IC2F_0', 'TIM_CCMR1_IC2F_1', 'TIM_CCMR1_IC2F_2', 'TIM_CCMR1_IC2F_3',
    'TIM_CCMR2_CC3S', 'TIM_CCMR2_CC3S_0', 'TIM_CCMR2_CC3S_1', 'TIM_CCMR2_OC3FE',
    'TIM_CCMR2_OC3PE', 'TIM_CCMR2_OC3M', 'TIM_CCMR2_OC3M_0', 'TIM_CCMR2_OC3M_1',
    'TIM_CCMR2_OC3M_2', 'TIM_CCMR2_OC3M_3', 'TIM_CCMR2_OC3CE', 'TIM_CCMR2_CC4S',
    'TIM_CCMR2_CC4S_0', 'TIM_CCMR2_CC4S_1', 'TIM_CCMR2_OC4FE', 'TIM_CCMR2_OC4PE',
    'TIM_CCMR2_OC4M', 'TIM_CCMR2_OC4M_0', 'TIM_CCMR2_OC4M_1', 'TIM_CCMR2_OC4M_2',
    'TIM_CCMR2_OC4M_3', 'TIM_CCMR2_OC4CE', 'TIM_CCMR2_IC3PSC', 'TIM_CCMR2_IC3PSC_0',
    'TIM_CCMR2_IC3PSC_1', 'TIM_CCMR2_IC3F', 'TIM_CCMR2_IC3F_0', 'TIM_CCMR2_IC3F_1',
    'TIM_CCMR2_IC3F_2', 'TIM_CCMR2_IC3F_3', 'TIM_CCMR2_IC4PSC', 'TIM_CCMR2_IC4PSC_0',
    'TIM_CCMR2_IC4PSC_1', 'TIM_CCMR2_IC4F', 'TIM_CCMR2_IC4F_0', 'TIM_CCMR2_IC4F_1',
    'TIM_CCMR2_IC4F_2', 'TIM_CCMR2_IC4F_3', 'TIM_CCER_CC1E', 'TIM_CCER_CC1P',
    'TIM_CCER_CC1NE', 'TIM_CCER_CC1NP', 'TIM_CCER_CC2E', 'TIM_CCER_CC2P',
    'TIM_CCER_CC2NE', 'TIM_CCER_CC2NP', 'TIM_CCER_CC3E', 'TIM_CCER_CC3P',
    'TIM_CCER_CC3NE', 'TIM_CCER_CC3NP', 'TIM_CCER_CC4E', 'TIM_CCER_CC4P',
    'TIM_CCER_CC4NP', 'TIM_CCER_CC5E', 'TIM_CCER_CC5P', 'TIM_CCER_CC6E',
    'TIM_CCER_CC6P', 'TIM_CNT_CNT', 'TIM_CNT_UIFCPY', 'TIM_PSC_PSC', 'TIM_ARR_ARR',
    'TIM_RCR_REP', 'TIM_CCR1_CCR1', 'TIM_CCR2_CCR2', 'TIM_CCR3_CCR3', 'TIM_CCR4_CCR4',
    'TIM_CCR5_CCR5', 'TIM_CCR5_GC5C1', 'TIM_CCR5_GC5C2', 'TIM_CCR5_GC5C3',
    'TIM_CCR6_CCR6', 'TIM_BDTR_DTG', 'TIM_BDTR_DTG_0', 'TIM_BDTR_DTG_1',
    'TIM_BDTR_DTG_2', 'TIM_BDTR_DTG_3', 'TIM_BDTR_DTG_4', 'TIM_BDTR_DTG_5',
    'TIM_BDTR_DTG_6', 'TIM_BDTR_DTG_7', 'TIM_BDTR_LOCK', 'TIM_BDTR_LOCK_0',
    'TIM_BDTR_LOCK_1', 'TIM_BDTR_OSSI', 'TIM_BDTR_OSSR', 'TIM_BDTR_BKE', 'TIM_BDTR_BKP',
    'TIM_BDTR_AOE', 'TIM_BDTR_MOE', 'TIM_BDTR_BKF', 'TIM_BDTR_BK2F', 'TIM_BDTR_BK2E',
    'TIM_BDTR_BK2P', 'TIM_DCR_DBA', 'TIM_DCR_DBA_0', 'TIM_DCR_DBA_1', 'TIM_DCR_DBA_2',
    'TIM_DCR_DBA_3', 'TIM_DCR_DBA_4', 'TIM_DCR_DBL', 'TIM_DCR_DBL_0', 'TIM_DCR_DBL_1',
    'TIM_DCR_DBL_2', 'TIM_DCR_DBL_3', 'TIM_DCR_DBL_4', 'TIM_DMAR_DMAB',
    'TIM16_OR_TI1_RMP', 'TIM16_OR_TI1_RMP_0', 'TIM16_OR_TI1_RMP_1', 'TIM1_OR_ETR_RMP',
    'TIM1_OR_ETR_RMP_0', 'TIM1_OR_ETR_RMP_1', 'TIM1_OR_ETR_RMP_2', 'TIM1_OR_ETR_RMP_3',
    'TIM8_OR_ETR_RMP', 'TIM8_OR_ETR_RMP_0', 'TIM8_OR_ETR_RMP_1', 'TIM8_OR_ETR_RMP_2',
    'TIM8_OR_ETR_RMP_3', 'TIM_CCMR3_OC5FE', 'TIM_CCMR3_OC5PE', 'TIM_CCMR3_OC5M',
    'TIM_CCMR3_OC5M_0', 'TIM_CCMR3_OC5M_1', 'TIM_CCMR3_OC5M_2', 'TIM_CCMR3_OC5M_3',
    'TIM_CCMR3_OC5CE', 'TIM_CCMR3_OC6FE', 'TIM_CCMR3_OC6PE', 'TIM_CCMR3_OC6M',
    'TIM_CCMR3_OC6M_0', 'TIM_CCMR3_OC6M_1', 'TIM_CCMR3_OC6M_2', 'TIM_CCMR3_OC6M_3',
    'TIM_CCMR3_OC6CE', 'USART_CR1_UE', 'USART_CR1_UESM', 'USART_CR1_RE', 'USART_CR1_TE',
    'USART_CR1_IDLEIE', 'USART_CR1_RXNEIE', 'USART_CR1_TCIE', 'USART_CR1_TXEIE',
    'USART_CR1_PEIE', 'USART_CR1_PS', 'USART_CR1_PCE', 'USART_CR1_WAKE', 'USART_CR1_M',
    'USART_CR1_MME', 'USART_CR1_CMIE', 'USART_CR1_OVER8', 'USART_CR1_DEDT',
    'USART_CR1_DEDT_0', 'USART_CR1_DEDT_1', 'USART_CR1_DEDT_2', 'USART_CR1_DEDT_3',
    'USART_CR1_DEDT_4', 'USART_CR1_DEAT', 'USART_CR1_DEAT_0', 'USART_CR1_DEAT_1',
    'USART_CR1_DEAT_2', 'USART_CR1_DEAT_3', 'USART_CR1_DEAT_4', 'USART_CR1_RTOIE',
    'USART_CR1_EOBIE', 'USART_CR2_ADDM7', 'USART_CR2_LBDL', 'USART_CR2_LBDIE',
    'USART_CR2_LBCL', 'USART_CR2_CPHA', 'USART_CR2_CPOL', 'USART_CR2_CLKEN',
    'USART_CR2_STOP', 'USART_CR2_STOP_0', 'USART_CR2_STOP_1', 'USART_CR2_LINEN',
    'USART_CR2_SWAP', 'USART_CR2_RXINV', 'USART_CR2_TXINV', 'USART_CR2_DATAINV',
    'USART_CR2_MSBFIRST', 'USART_CR2_ABREN', 'USART_CR2_ABRMODE', 'USART_CR2_ABRMODE_0',
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
    'WWDG_CFR_WDGTB0', 'WWDG_CFR_WDGTB1', 'WWDG_CFR_EWI', 'WWDG_SR_EWIF', 'ADC_TypeDef',
    'ADC_Common_TypeDef', 'CAN_TxMailBox_TypeDef', 'CAN_FIFOMailBox_TypeDef',
    'CAN_FilterRegister_TypeDef', 'COMP_TypeDef', 'CRC_TypeDef', 'DAC_TypeDef',
    'DBGMCU_TypeDef', 'DMA_Channel_TypeDef', 'DMA_TypeDef', 'EXTI_TypeDef',
    'FLASH_TypeDef', 'OB_TypeDef', 'GPIO_TypeDef', 'OPAMP_TypeDef', 'SYSCFG_TypeDef',
    'I2C_TypeDef', 'IWDG_TypeDef', 'PWR_TypeDef', 'RCC_TypeDef', 'RTC_TypeDef',
    'SPI_TypeDef', 'TIM_TypeDef', 'TSC_TypeDef', 'USART_TypeDef', 'WWDG_TypeDef']
