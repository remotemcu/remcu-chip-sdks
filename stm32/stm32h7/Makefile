
# include $(MCU_UTIL_PATH)/python2.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_adc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_bdma.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_comp.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_crc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_crs.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_dac.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_dma2d.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_dma.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_exti.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_gpio.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_hrtim.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_i2c.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_lptim.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_lpuart.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_mdma.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_opamp.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_rcc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_rng.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_rtc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_spi.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_swpmi.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_tim.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usart.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \

SRC_IGNORE = \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_pwr.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_utils.c \


C_SRC += $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.c

C_SRC += $(wildcard $(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/ \
       $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32H7xx/Include/ \
       $(MCU_SDK_PATH)/CMSIS/Include \
       ./

EXPORT_INC_PATH_NOT = \
	$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/ \
	$(MCU_SDK_PATH)/CMSIS/Include \
	./

DEVICE_HEADER = $(shell echo $(DEVICE) | tr '[:upper:]' '[:lower:]')

EXPORT_INC_FILE_NOT_USED = \
$(MCU_SDK_PATH)/CMSIS/Device/ST/STM32H7xx/Include/stm32h7xx.h \
$(MCU_SDK_PATH)/CMSIS/Device/ST/STM32H7xx/Include/$(DEVICE_HEADER).h\
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_adc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_bdma.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_bus.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_comp.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_crc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_crs.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_dac.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_delayblock.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_dma2d.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_dma.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_dmamux.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_exti.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_fmc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_gpio.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_hrtim.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_hsem.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_i2c.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_iwdg.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_lptim.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_lpuart.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_mdma.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_opamp.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_rcc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_rng.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_rtc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_sdmmc.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_spi.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_swpmi.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_system.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_tim.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_usart.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_utils.h \
$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/stm32h7xx_ll_wwdg.h \



INC_NOT_USED = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------
#-DSTM32F767xx
DEFS = -DUSE_FULL_LL_DRIVER -DREMCU_LIB -D$(DEVICE) -DUSE_HAL_DRIVER



EXTRA_FLAGS = -Werror=implicit-function-declaration -Wno-int-to-pointer-cast -Wno-constant-conversion


include $(TARGET_MK)
