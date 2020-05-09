
include $(TARGET_MK)

include $(MCU_UTIL_PATH)/python.mk

# List of C source files.
C_SRC = \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \

C_SRC1 += $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_can.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cec.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma2d.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dsi.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2s.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_irda.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_jpeg.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_lptim.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nor.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rng.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sd.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sdram.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spdifrx.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sram.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_usart.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_wwdg.c \


IGNORE = $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hcd.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_msp_template.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_tim_template.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
$(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.c \


C_SRC += $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/STM32F767xx/system_stm32f7xx.c

C_SRC += $(wildcard $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/transformed_Inc/ \
       $(MCU_SDK_PATH)/CMSIS/Device/ST/STM32F7xx/Include \
       $(MCU_SDK_PATH)/CMSIS/Include \
       $(MCU_SDK_PATH)/STM32F7xx_HAL_Driver/STM32F767xx



INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------
#-DSTM32F767xx
DEFS = -DUSE_FULL_LL_DRIVER -DREMCU_LIB -D$(DEVICE)
# -DUSE_HAL_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)  -Werror=implicit-function-declaration -Wno-int-to-pointer-cast -Wno-constant-conversion

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES) python
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#$(AR) rcv $@.ar $(BUILD_DIR)/*.adin.o
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

