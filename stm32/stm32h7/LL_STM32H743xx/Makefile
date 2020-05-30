
include $(TARGET_MK)

#include $(MCU_UTIL_PATH)/python.mk

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

C_SRC += $(wildcard $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/Inc \
       $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32H7xx/Include/ \
       $(MCU_SDK_PATH)/CMSIS/Include \
       ./
       
       #$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/
       #$(MCU_SDK_PATH)/STM32H7xx_HAL_Driver/transformed_Inc/ \



INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------
#-DSTM32F767xx
DEFS = -DUSE_FULL_LL_DRIVER -DREMCU_LIB -D$(DEVICE) -DUSE_HAL_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)  -Werror=implicit-function-declaration -Wno-int-to-pointer-cast -Wno-constant-conversion

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES) #python
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#$(AR) rcv $@.ar $(BUILD_DIR)/*.adin.o
	gcc $(LOCAL_CFLAGS) -o app $(BUILD_DIR)/* test.c

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

