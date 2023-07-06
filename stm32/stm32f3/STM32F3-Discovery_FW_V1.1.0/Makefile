

# include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_opamp.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dma.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_can.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_tim.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_exti.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_comp.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_crc.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_spi.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rcc.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rtc.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_iwdg.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_gpio.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dac.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_adc.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_i2c.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_syscfg.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_wwdg.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dbgmcu.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_usart.c \

SRC_NOT_USED = \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_flash.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_misc.c \
Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_pwr.c \


# List of include paths.
INC_PATH = \
       Libraries/STM32F30x_StdPeriph_Driver/inc/ \
       Libraries/CMSIS/Include/ \
       Libraries/CMSIS/Device/ST/STM32F30x/Include/ \
       Libraries/



INC_NOT_USED = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)




include $(TARGET_MK)
