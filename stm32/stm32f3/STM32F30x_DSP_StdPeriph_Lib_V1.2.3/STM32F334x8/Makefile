
include $(TARGET_MK)

include $(MCU_UTIL_PATH)/python.mk

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

SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_flash.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_misc.c \
$(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_pwr.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/STM32F30x_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32F30x/Include/ \
       $(MCU_SDK_PATH)/Projects/STM32F30x_StdPeriph_Templates/



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

REMCU_C: $(IR_FILES)
	@echo done

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $<).$(IR_SUFFIX)
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll
	$(CBE) $(CBE_OPTIONS) $(BUILD_DIR)/$(notdir $<).adin.ll -o $(OUTPUT_DIR)/$(notdir $<).remcu.c
	$(CBE) $(CBE_OPTIONS) $(BUILD_DIR)/$(notdir $<).$(IR_SUFFIX) -o $(OUTPUT_MCU_DIR)/$(notdir $<).mcu.c
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).adin.

