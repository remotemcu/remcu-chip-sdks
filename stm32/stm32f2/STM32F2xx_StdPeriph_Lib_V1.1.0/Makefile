# include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
       Libraries/CMSIS/Device/ST/STM32F2xx/Source/Templates/system_stm32f2xx.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_gpio.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_rcc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_dbgmcu.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_exti.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_crc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_rtc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_adc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_tim.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_dma.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_dac.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_can.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_spi.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_sdio.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_iwdg.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_usart.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_hash.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_wwdg.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_syscfg.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_cryp.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_i2c.c

SRC_EXTRA = \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_pwr.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/misc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_hash_sha1.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_hash_md5.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_cryp_tdes.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_cryp_des.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_cryp_aes.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_fsmc.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_flash.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_dcmi.c \
Libraries/STM32F2xx_StdPeriph_Driver/src/stm32f2xx_rng.c \

# List of include paths.
INC_PATH = \
       Libraries/STM32F2xx_StdPeriph_Driver/inc/ \
       Libraries/CMSIS/Include/ \
       Libraries/CMSIS/Device/ST/STM32F2xx/Include/ \
       Project/STM32F2xx_StdPeriph_Template/ \


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))


include $(TARGET_MK)
