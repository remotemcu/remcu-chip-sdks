
include $(REMCU_PATH_MK)/remcu.mk

#DEVICE = EFM32TG840F32

BUILD_DIR = build

INCLUDEPATHS += \
 -I platform/osa/inc  \
-I platform/utilities/inc  \
-I platform/CMSIS/Include  \
-I platform/devices  \
-I platform/devices/MK64F12/include  \
-I platform/devices/MK64F12/startup  \
-I platform/hal/inc  \
-I platform/drivers/inc  \
-I platform/system/inc \
-I board 

#-I platform/CMSIS/Include \

C_CXX_SRC +=  \
     board/gpio_pins.c \
     board/pin_mux.c \
     board/board.c \
 platform/devices/MK64F12/startup/system_MK64F12.c \

C_CXX_SRC_33 += platform/utilities/src/fsl_misc_utilities.c \
 platform/utilities/src/fsl_debug_console.c \
 platform/utilities/src/print_scan.c \
     hello_world/main.c \
     hello_world/fsl_lptmr_irq.c \
     hello_world/hardware_init.c \

C_CXX_SRC +=  \
platform/system/src/clock/fsl_clock_manager.c \
platform/system/src/clock/fsl_clock_manager_common.c \
platform/system/src/clock/MK64F12/fsl_clock_MK64F12.c \
platform/system/src/hwtimer/fsl_hwtimer.c \
platform/system/src/hwtimer/fsl_hwtimer_pit.c \
platform/hal/src/adc16/fsl_adc16_hal.c \
platform/drivers/src/adc16/fsl_adc16_driver.c \
platform/drivers/src/adc16/fsl_adc16_common.c \
platform/hal/src/flexbus/fsl_flexbus_hal.c \
platform/drivers/src/flexbus/fsl_flexbus_driver.c \
platform/drivers/src/flexbus/fsl_flexbus_common.c \
platform/hal/src/flexcan/fsl_flexcan_hal.c \
platform/drivers/src/flexcan/fsl_flexcan_driver.c \
platform/drivers/src/flexcan/fsl_flexcan_common.c \
platform/hal/src/cmp/fsl_cmp_hal.c \
platform/drivers/src/cmp/fsl_cmp_driver.c \
platform/drivers/src/cmp/fsl_cmp_common.c \
platform/hal/src/cmt/fsl_cmt_hal.c \
platform/drivers/src/cmt/fsl_cmt_driver.c \
platform/drivers/src/cmt/fsl_cmt_common.c \
platform/hal/src/crc/fsl_crc_hal.c \
platform/drivers/src/crc/fsl_crc_driver.c \
platform/drivers/src/crc/fsl_crc_common.c \
platform/hal/src/dac/fsl_dac_hal.c \
platform/drivers/src/dac/fsl_dac_driver.c \
platform/drivers/src/dac/fsl_dac_common.c \
platform/hal/src/dmamux/fsl_dmamux_hal.c \
platform/hal/src/edma/fsl_edma_hal.c \
platform/drivers/src/edma/fsl_edma_driver.c \
platform/drivers/src/edma/fsl_edma_common.c \
platform/hal/src/dspi/fsl_dspi_hal.c \
platform/drivers/src/dspi/fsl_dspi_shared_function.c \
platform/drivers/src/dspi/fsl_dspi_common.c \
platform/drivers/src/dspi/fsl_dspi_master_driver.c \
platform/drivers/src/dspi/fsl_dspi_slave_driver.c \
platform/drivers/src/dspi/fsl_dspi_edma_master_driver.c \
platform/drivers/src/dspi/fsl_dspi_edma_slave_driver.c \
platform/drivers/src/dspi/fsl_dspi_edma_shared_function.c \
platform/hal/src/ftm/fsl_ftm_hal.c \
platform/drivers/src/ftm/fsl_ftm_driver.c \
platform/drivers/src/ftm/fsl_ftm_common.c \
platform/hal/src/gpio/fsl_gpio_hal.c \
platform/drivers/src/gpio/fsl_gpio_common.c \
platform/drivers/src/gpio/fsl_gpio_driver.c \
platform/hal/src/i2c/fsl_i2c_hal.c \
platform/drivers/src/i2c/fsl_i2c_shared_function.c \
platform/drivers/src/i2c/fsl_i2c_common.c \
platform/drivers/src/i2c/fsl_i2c_master_driver.c \
platform/drivers/src/i2c/fsl_i2c_slave_driver.c \
platform/hal/src/llwu/fsl_llwu_hal.c \
platform/hal/src/lptmr/fsl_lptmr_hal.c \
platform/drivers/src/lptmr/fsl_lptmr_driver.c \
platform/drivers/src/lptmr/fsl_lptmr_common.c \
platform/hal/src/mpu/fsl_mpu_hal.c \
platform/drivers/src/mpu/fsl_mpu_driver.c \
platform/drivers/src/mpu/fsl_mpu_common.c \
platform/hal/src/ewm/fsl_ewm_hal.c \
platform/drivers/src/ewm/fsl_ewm_driver.c \
platform/drivers/src/ewm/fsl_ewm_common.c \
platform/hal/src/mcg/fsl_mcg_hal.c \
platform/hal/src/mcg/fsl_mcg_hal_modes.c \
platform/hal/src/osc/fsl_osc_hal.c \
platform/hal/src/pdb/fsl_pdb_hal.c \
platform/drivers/src/pdb/fsl_pdb_driver.c \
platform/drivers/src/pdb/fsl_pdb_common.c \
platform/hal/src/pit/fsl_pit_hal.c \
platform/drivers/src/pit/fsl_pit_driver.c \
platform/drivers/src/pit/fsl_pit_common.c \
platform/hal/src/port/fsl_port_hal.c \
platform/hal/src/rtc/fsl_rtc_hal.c \
platform/drivers/src/rtc/fsl_rtc_driver.c \
platform/drivers/src/rtc/fsl_rtc_common.c \
platform/hal/src/rnga/fsl_rnga_hal.c \
platform/drivers/src/rnga/fsl_rnga_driver.c \
platform/drivers/src/rnga/fsl_rnga_common.c \
platform/hal/src/sai/fsl_sai_hal.c \
platform/drivers/src/sai/fsl_sai_driver.c \
platform/drivers/src/sai/fsl_sai_common.c \
platform/hal/src/sdhc/fsl_sdhc_hal.c \
platform/drivers/src/sdhc/fsl_sdhc_driver.c \
platform/drivers/src/sdhc/fsl_sdhc_common.c \
platform/hal/src/sim/MK64F12/fsl_sim_hal_MK64F12.c \
platform/hal/src/rcm/fsl_rcm_hal.c \
platform/hal/src/uart/fsl_uart_hal.c \
platform/drivers/src/uart/fsl_uart_common.c \
platform/drivers/src/uart/fsl_uart_driver.c \
platform/drivers/src/uart/fsl_uart_edma_driver.c \
platform/hal/src/vref/fsl_vref_hal.c \
platform/drivers/src/vref/fsl_vref_common.c \
platform/drivers/src/vref/fsl_vref_driver.c \



C_CXX_SRC += platform/osa/src/fsl_os_abstraction_bm.c \

C_CXX_SRC1 +=  platform/hal/src/smc/fsl_smc_hal.c \
platform/system/src/hwtimer/fsl_hwtimer_systick.c \

#platform/system/src/power/fsl_power_manager.c \
#platform/hal/src/smc/fsl_smc_hal.c \
#platform/system/src/interrupt/fsl_interrupt_manager.c \

C_CXX_SRC2 +=  platform/hal/src/enet/fsl_enet_hal.c \
platform/drivers/src/enet/fsl_enet_driver.c \
platform/drivers/src/enet/fsl_enet_common.c \
platform/hal/src/wdog/fsl_wdog_hal.c \
platform/drivers/src/wdog/fsl_wdog_driver.c \
platform/drivers/src/wdog/fsl_wdog_common.c \

C_SRC = $(filter %.c, $(C_CXX_SRC))
CXX_SRC = $(filter %.cpp, $(C_CXX_SRC))


IR_FILES += $(C_SRC:.c=.ll)

#LOCAL_CFLAGS += -D$(DEVICE)

LOCAL_CFLAGS +=-DDEBUG
LOCAL_CFLAGS +=-DCPU_$(DEVICE)
#MK64FN1M0VMD12
#LOCAL_CFLAGS +=-DFRDM_K64F
#LOCAL_CFLAGS +=-DFREEDOM

LOCAL_CXXFLAGS += -D$(DEVICE)

$(OUTPUT): $(IR_FILES)
	#$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	$(CLANG) $(BUILD_DIR)/*.o -o $@

# Create objects from C SRC files
%.ll: %.c
	@echo "Building file: $<"
	$(CLANG) $(LOCAL_CFLAGS) $(INCLUDEPATHS) -c  $< -o $(BUILD_DIR)/$(notdir $<).o
	#$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) $(INCLUDEPATHS) -c  $< -o $(BUILD_DIR)/$(notdir $<).ll
	#$(OPT) $(OPT_FLAGS)  $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll