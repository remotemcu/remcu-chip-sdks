
include $(TARGET_MK)


# List of C source files.
C_SRC = \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \

C_SRC1 += STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_can.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cec.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma2d.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dsi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2s.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_irda.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_jpeg.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_lptim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nor.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rng.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sd.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sdram.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spdifrx.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sram.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_usart.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_wwdg.c \


IGNORE = STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hcd.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_msp_template.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_tim_template.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.c \


C_SRC += STM32F7xx_HAL_Driver/stm32f67x/system_stm32f7xx.c

C_SRC += $(wildcard STM32F7xx_HAL_Driver/fun_implementation/*.c)

# List of include paths.
INC_PATH = \
       STM32F7xx_HAL_Driver/transformed_Inc/ \
       CMSIS/Device/ST/STM32F7xx/Include \
       CMSIS/Include \
       STM32F7xx_HAL_Driver/stm32f67x

       #STM32F7xx_HAL_Driver



INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DUSE_FULL_LL_DRIVER -DSTM32F767xx -DREMCU_LIB -DUSE_HAL_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)  -Werror=implicit-function-declaration -Wno-int-to-pointer-cast -Wno-constant-conversion

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

