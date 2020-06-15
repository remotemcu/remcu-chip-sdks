
include $(TARGET_MK)

include $(MCU_UTIL_PATH)/python2.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_adc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_adc_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_comp.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_comp_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_crc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_crc_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cryp.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cryp_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dac.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dac_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_firewall.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2s.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_irda.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_iwdg.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_lcd.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_lptim.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_msp_template.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rng.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_smartcard.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_smartcard_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_smbus.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_spi.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tsc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_usart.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_wwdg.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_adc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_comp.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_crc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_crs.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dac.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rng.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rtc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_spi.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c \


SRC_IGNORE = \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usb.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pcd.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pcd_ex.c \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.c \


C_SRC += $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c

C_SRC += $(wildcard $(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/ \
       $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32L0xx/Include/ \
       $(MCU_SDK_PATH)/CMSIS/Include \
       $(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/Inc \
       ./

EXPORT_INC_PATH_NOT = \
	$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/ \
	$(MCU_SDK_PATH)/CMSIS/Include \
	./

DEVICE_HEADER = $(shell echo $(DEVICE) | tr '[:upper:]' '[:lower:]')


EXPORT_INC_FILE = \
$(MCU_SDK_PATH)/CMSIS/Device/ST/STM32L0xx/Include/stm32l0xx.h \
$(MCU_SDK_PATH)/CMSIS/Device/ST/STM32L0xx/Include/$(DEVICE_HEADER).h\
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_adc_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_adc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_comp_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_comp.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_crc_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_crc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_dac_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_dac.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_def.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_dma.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_firewall.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_flash_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_flash.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_flash_ramfunc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_gpio_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_gpio.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_i2c_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_i2c.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_i2s.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_irda_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_irda.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_iwdg.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_lcd.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_lptim_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_lptim.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_rcc_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_rcc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_rng.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_rtc_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_smartcard_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_smartcard.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_smbus.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_spi.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_tim_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_tim.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_tsc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_uart_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_uart.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_usart_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_usart.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_wwdg.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_adc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_bus.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_comp.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_crc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_crs.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_dac.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_dma.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_exti.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_gpio.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_i2c.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_iwdg.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_lptim.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_lpuart.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_rcc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_rng.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_rtc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_spi.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_system.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_tim.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_usart.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_utils.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_ll_wwdg.h \



INC_EXTRA = \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_rtc.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_cryp_ex.h \
$(MCU_SDK_PATH)/STM32L0xx_HAL_Driver/transformed_Inc/stm32l0xx_hal_cryp.h \

FIRST_RUNTIME_STRING = \#include "stm32l0xx_hal.h"

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------
DEFS = -DUSE_FULL_LL_DRIVER -DREMCU_LIB -D$(DEVICE) -DUSE_HAL_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)  -Werror=implicit-function-declaration -Wno-int-to-pointer-cast -Wno-constant-conversion

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES) python
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#gcc $(LOCAL_CFLAGS) -o app $(BUILD_DIR)/* test.c

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

