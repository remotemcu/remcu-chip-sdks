
#include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/Libraries//CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c \

SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/misc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
$(MCU_SDK_PATH)/Libraries//STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Include/\
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Project/STM32F4xx_StdPeriph_Templates/


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

include $(TARGET_MK)