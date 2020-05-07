
include $(TARGET_MK)


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
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_fsmc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_comp.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_syscfg.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_crc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_tim.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_opamp.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rcc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_usart.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_iwdg.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dbgmcu.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_lcd.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dac.c \

SRC_EXTRA = \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_pwr.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash_ramfunc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/misc.c \
$(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_aes_util.c \


# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Device/ST/STM32L1xx/Include/ \
       $(MCU_SDK_PATH)/Libraries/CMSIS/Include/ \
       $(MCU_SDK_PATH)/Libraries/STM32L1xx_StdPeriph_Driver/inc/ \
       $(MCU_SDK_PATH)/Libraries/Template/


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -D$(DEVICE)

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES)
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#$(AR) rcv $@.ar $(BUILD_DIR)/*.adin.o

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $<).$(IR_SUFFIX)
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).adin.o

