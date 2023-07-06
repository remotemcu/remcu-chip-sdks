
# include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_opamp.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dma.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_can.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_tim.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_hrtim.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_exti.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_comp.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_crc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_spi.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rcc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_fmc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rtc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_gpio.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dac.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_adc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_i2c.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_syscfg.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_wwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_usart.c \

SRC_NOT_USED = \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_flash.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_misc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_pwr.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F30x/Include/ \
       $(MCU_SDK_PATH)/Projects/STM32F30x_StdPeriph_Templates/



INC_NOT_USED = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)



include $(TARGET_MK)


