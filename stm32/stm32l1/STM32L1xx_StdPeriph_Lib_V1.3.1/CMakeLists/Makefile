

# include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32L1xx/Source/Templates/system_stm32l1xx.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_wwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dma.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_i2c.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_exti.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rtc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_adc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_sdio.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_spi.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_gpio.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_comp.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_syscfg.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_crc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_tim.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_opamp.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rcc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_usart.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_lcd.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dac.c \

SRC_NOT_USED = \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_pwr.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/misc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes_util.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_fsmc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32L1xx/Include/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/Template/


INC_NOT_USED = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)




include $(TARGET_MK)

