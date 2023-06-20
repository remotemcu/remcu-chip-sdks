
C_SRC +=  \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_wwdg.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_flash.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_comp.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_tim2.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_syscfg.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_clk.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_aes.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_lcd.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_gpio.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_tim3.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_tim5.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_adc.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_i2c.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_beep.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_spi.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_usart.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_dac.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_tim4.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_dma.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_tim1.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_rtc.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_exti.c

C_SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_itc.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_wfe.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_irtim.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_pwr.c \
$(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_rst.c \


INC_PATH = 	\
 $(MCU_SDK_PATH)/Libraries/STM8L15x_StdPeriph_Driver/inc/

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

#-DUSE_STDPERIPH_DRIVER

# IR_FILES += $(C_SRC:.c=.ll)

DEFS += -D$(DEVICE)
INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))


include $(TARGET_MK)
