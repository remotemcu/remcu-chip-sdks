
include $(TARGET_MK)


# List of C source files.
C_SRC = \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c \

C_SRC += $(wildcard STM32F7xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       STM32F7xx_HAL_Driver/transformed_Inc/ \
       CMSIS/Device/ST/STM32F7xx/Include \
       CMSIS/Include \
       STM32F7xx_HAL_Driver



INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DUSE_FULL_LL_DRIVER -DSTM32F767xx -DREMCU_LIB

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES)
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
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).adin.o

