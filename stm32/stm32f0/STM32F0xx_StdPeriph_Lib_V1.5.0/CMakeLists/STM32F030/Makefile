
include $(TARGET_MK)

include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_wwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dma.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_exti.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_crs.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_adc.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_syscfg.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_usart.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rtc.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_cec.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_comp.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rcc.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_crc.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dac.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_i2c.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_spi.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_gpio.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_can.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_tim.c

SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_pwr.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_misc.c \
$(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_flash.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/STM32F0xx_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F0xx/Include/ \
       $(MCU_SDK_PATH)/Projects/STM32F0xx_StdPeriph_Templates/ \
       $(MCU_SDK_PATH)/Libraries/


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES) python
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#$(AR) rcv $@.ar $(BUILD_DIR)/*.adin.o

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $<).$(IR_SUFFIX)
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).adin.o

