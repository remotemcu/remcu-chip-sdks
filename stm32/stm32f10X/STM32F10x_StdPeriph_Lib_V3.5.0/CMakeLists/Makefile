
# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
$(MCU_SDK_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c \
$(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/STM32F10x_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/CM3/CoreSupport/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/ \
       $(MCU_SDK_PATH)/Project/STM32F10x_StdPeriph_Template/ \


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)



include $(TARGET_MK)
