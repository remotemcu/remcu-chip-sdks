KSDK_ROOT = $(MCU_SDK_PATH)

INC_PATH += \
 -I $(KSDK_ROOT)/platform/osa/inc  \
-I $(KSDK_ROOT)/platform/utilities/inc  \
-I $(KSDK_ROOT)/platform/CMSIS/Include  \
-I $(KSDK_ROOT)/platform/devices  \
-I $(KSDK_ROOT)/platform/devices/MK64F12/include  \
-I $(KSDK_ROOT)/platform/devices/MK64F12/startup  \
-I $(KSDK_ROOT)/platform/hal/inc  \
-I $(KSDK_ROOT)/platform/drivers/inc  \
-I $(KSDK_ROOT)/platform/system/inc \
-I board 

#-I $(KSDK_ROOT)/platform/CMSIS/Include \

C_SRC +=  \
$(KSDK_ROOT)/platform/system/src/clock/fsl_clock_manager.c \
$(KSDK_ROOT)/platform/system/src/clock/fsl_clock_manager_common.c \
$(KSDK_ROOT)/platform/system/src/clock/MK64F12/fsl_clock_MK64F12.c \
$(KSDK_ROOT)/platform/system/src/hwtimer/fsl_hwtimer.c \
$(KSDK_ROOT)/platform/system/src/hwtimer/fsl_hwtimer_pit.c \
$(KSDK_ROOT)/platform/hal/src/adc16/fsl_adc16_hal.c \
$(KSDK_ROOT)/platform/drivers/src/adc16/fsl_adc16_driver.c \
$(KSDK_ROOT)/platform/drivers/src/adc16/fsl_adc16_common.c \
$(KSDK_ROOT)/platform/hal/src/flexbus/fsl_flexbus_hal.c \
$(KSDK_ROOT)/platform/drivers/src/flexbus/fsl_flexbus_driver.c \
$(KSDK_ROOT)/platform/drivers/src/flexbus/fsl_flexbus_common.c \
$(KSDK_ROOT)/platform/hal/src/flexcan/fsl_flexcan_hal.c \
$(KSDK_ROOT)/platform/drivers/src/flexcan/fsl_flexcan_driver.c \
$(KSDK_ROOT)/platform/drivers/src/flexcan/fsl_flexcan_common.c \
$(KSDK_ROOT)/platform/hal/src/cmp/fsl_cmp_hal.c \
$(KSDK_ROOT)/platform/drivers/src/cmp/fsl_cmp_driver.c \
$(KSDK_ROOT)/platform/drivers/src/cmp/fsl_cmp_common.c \
$(KSDK_ROOT)/platform/hal/src/cmt/fsl_cmt_hal.c \
$(KSDK_ROOT)/platform/drivers/src/cmt/fsl_cmt_driver.c \
$(KSDK_ROOT)/platform/drivers/src/cmt/fsl_cmt_common.c \
$(KSDK_ROOT)/platform/hal/src/crc/fsl_crc_hal.c \
$(KSDK_ROOT)/platform/drivers/src/crc/fsl_crc_driver.c \
$(KSDK_ROOT)/platform/drivers/src/crc/fsl_crc_common.c \
$(KSDK_ROOT)/platform/hal/src/dac/fsl_dac_hal.c \
$(KSDK_ROOT)/platform/drivers/src/dac/fsl_dac_driver.c \
$(KSDK_ROOT)/platform/drivers/src/dac/fsl_dac_common.c \
$(KSDK_ROOT)/platform/hal/src/dmamux/fsl_dmamux_hal.c \
$(KSDK_ROOT)/platform/hal/src/edma/fsl_edma_hal.c \
$(KSDK_ROOT)/platform/drivers/src/edma/fsl_edma_driver.c \
$(KSDK_ROOT)/platform/drivers/src/edma/fsl_edma_common.c \
$(KSDK_ROOT)/platform/hal/src/dspi/fsl_dspi_hal.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_shared_function.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_common.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_master_driver.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_slave_driver.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_edma_master_driver.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_edma_slave_driver.c \
$(KSDK_ROOT)/platform/drivers/src/dspi/fsl_dspi_edma_shared_function.c \
$(KSDK_ROOT)/platform/hal/src/ftm/fsl_ftm_hal.c \
$(KSDK_ROOT)/platform/drivers/src/ftm/fsl_ftm_driver.c \
$(KSDK_ROOT)/platform/drivers/src/ftm/fsl_ftm_common.c \
$(KSDK_ROOT)/platform/hal/src/gpio/fsl_gpio_hal.c \
$(KSDK_ROOT)/platform/drivers/src/gpio/fsl_gpio_common.c \
$(KSDK_ROOT)/platform/drivers/src/gpio/fsl_gpio_driver.c \
$(KSDK_ROOT)/platform/hal/src/i2c/fsl_i2c_hal.c \
$(KSDK_ROOT)/platform/drivers/src/i2c/fsl_i2c_shared_function.c \
$(KSDK_ROOT)/platform/drivers/src/i2c/fsl_i2c_common.c \
$(KSDK_ROOT)/platform/drivers/src/i2c/fsl_i2c_master_driver.c \
$(KSDK_ROOT)/platform/drivers/src/i2c/fsl_i2c_slave_driver.c \
$(KSDK_ROOT)/platform/hal/src/llwu/fsl_llwu_hal.c \
$(KSDK_ROOT)/platform/hal/src/lptmr/fsl_lptmr_hal.c \
$(KSDK_ROOT)/platform/drivers/src/lptmr/fsl_lptmr_driver.c \
$(KSDK_ROOT)/platform/drivers/src/lptmr/fsl_lptmr_common.c \
$(KSDK_ROOT)/platform/hal/src/mpu/fsl_mpu_hal.c \
$(KSDK_ROOT)/platform/drivers/src/mpu/fsl_mpu_driver.c \
$(KSDK_ROOT)/platform/drivers/src/mpu/fsl_mpu_common.c \
$(KSDK_ROOT)/platform/hal/src/ewm/fsl_ewm_hal.c \
$(KSDK_ROOT)/platform/drivers/src/ewm/fsl_ewm_driver.c \
$(KSDK_ROOT)/platform/drivers/src/ewm/fsl_ewm_common.c \
$(KSDK_ROOT)/platform/hal/src/mcg/fsl_mcg_hal.c \
$(KSDK_ROOT)/platform/hal/src/mcg/fsl_mcg_hal_modes.c \
$(KSDK_ROOT)/platform/hal/src/osc/fsl_osc_hal.c \
$(KSDK_ROOT)/platform/hal/src/pdb/fsl_pdb_hal.c \
$(KSDK_ROOT)/platform/drivers/src/pdb/fsl_pdb_driver.c \
$(KSDK_ROOT)/platform/drivers/src/pdb/fsl_pdb_common.c \
$(KSDK_ROOT)/platform/hal/src/pit/fsl_pit_hal.c \
$(KSDK_ROOT)/platform/drivers/src/pit/fsl_pit_driver.c \
$(KSDK_ROOT)/platform/drivers/src/pit/fsl_pit_common.c \
$(KSDK_ROOT)/platform/hal/src/port/fsl_port_hal.c \
$(KSDK_ROOT)/platform/hal/src/rtc/fsl_rtc_hal.c \
$(KSDK_ROOT)/platform/drivers/src/rtc/fsl_rtc_driver.c \
$(KSDK_ROOT)/platform/drivers/src/rtc/fsl_rtc_common.c \
$(KSDK_ROOT)/platform/hal/src/rnga/fsl_rnga_hal.c \
$(KSDK_ROOT)/platform/drivers/src/rnga/fsl_rnga_driver.c \
$(KSDK_ROOT)/platform/drivers/src/rnga/fsl_rnga_common.c \
$(KSDK_ROOT)/platform/hal/src/sai/fsl_sai_hal.c \
$(KSDK_ROOT)/platform/drivers/src/sai/fsl_sai_driver.c \
$(KSDK_ROOT)/platform/drivers/src/sai/fsl_sai_common.c \
$(KSDK_ROOT)/platform/hal/src/sdhc/fsl_sdhc_hal.c \
$(KSDK_ROOT)/platform/drivers/src/sdhc/fsl_sdhc_driver.c \
$(KSDK_ROOT)/platform/drivers/src/sdhc/fsl_sdhc_common.c \
$(KSDK_ROOT)/platform/hal/src/sim/MK64F12/fsl_sim_hal_MK64F12.c \
$(KSDK_ROOT)/platform/hal/src/rcm/fsl_rcm_hal.c \
$(KSDK_ROOT)/platform/hal/src/uart/fsl_uart_hal.c \
$(KSDK_ROOT)/platform/drivers/src/uart/fsl_uart_common.c \
$(KSDK_ROOT)/platform/drivers/src/uart/fsl_uart_driver.c \
$(KSDK_ROOT)/platform/drivers/src/uart/fsl_uart_edma_driver.c \
$(KSDK_ROOT)/platform/hal/src/vref/fsl_vref_hal.c \
$(KSDK_ROOT)/platform/drivers/src/vref/fsl_vref_common.c \
$(KSDK_ROOT)/platform/drivers/src/vref/fsl_vref_driver.c \

C_SRC += $(KSDK_ROOT)/platform/osa/src/fsl_os_abstraction_bm.c \
 $(KSDK_ROOT)/platform/devices/MK64F12/startup/system_MK64F12.c \

SRC_EXTRA +=  \
     board/gpio_pins.c \
     board/pin_mux.c \
     board/board.c \

SRC_EXTRA += $(KSDK_ROOT)/platform/utilities/src/fsl_misc_utilities.c \
 $(KSDK_ROOT)/platform/utilities/src/fsl_debug_console.c \
 $(KSDK_ROOT)/platform/utilities/src/print_scan.c \
     hello_world/main.c \
     hello_world/fsl_lptmr_irq.c \
     hello_world/hardware_init.c \


SRC_EXTRA +=  \
 $(KSDK_ROOT)/platform/hal/src/smc/fsl_smc_hal.c \
$(KSDK_ROOT)/platform/system/src/hwtimer/fsl_hwtimer_systick.c \
$(KSDK_ROOT)/platform/system/src/power/fsl_power_manager.c \
$(KSDK_ROOT)/platform/hal/src/smc/fsl_smc_hal.c \
$(KSDK_ROOT)/platform/system/src/interrupt/fsl_interrupt_manager.c \

SRC_EXTRA +=  $(KSDK_ROOT)/platform/hal/src/enet/fsl_enet_hal.c \
$(KSDK_ROOT)/platform/drivers/src/enet/fsl_enet_driver.c \
$(KSDK_ROOT)/platform/drivers/src/enet/fsl_enet_common.c \
$(KSDK_ROOT)/platform/hal/src/wdog/fsl_wdog_hal.c \
$(KSDK_ROOT)/platform/drivers/src/wdog/fsl_wdog_driver.c \
$(KSDK_ROOT)/platform/drivers/src/wdog/fsl_wdog_common.c \


DEFS += -DDEBUG -DCPU_$(DEVICE)



include $(TARGET_MK)
