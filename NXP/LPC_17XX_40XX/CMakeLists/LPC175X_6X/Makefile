
INC_PATH += \
$(MCU_SDK_PATH)/CMSIS/CMSIS/Include/  \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/ \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_common/ \

 #-I $(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/config_177x_8x/ \

C_SRC += \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/i2s_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/rtc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/spi_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/dac_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/sdc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/gpdma_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/sysinit_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/gpio_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/eeprom_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/timer_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/cmp_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/stopwatch_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/i2c_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/gpioint_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/crc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/can_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/uart_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/wwdt_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/enet_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/ssp_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/clock_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/ritimer_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/adc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/sdmmc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/iocon_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/emc_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/chip_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/sysctl_17xx_40xx.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/lcd_17xx_40xx.c

C_SRC += \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_common/eeprom.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_common/ring_buffer.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_common/fpu_init.c \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_common/iap.c

C_SRC_UNCESS +=  \
$(MCU_SDK_PATH)/lpc_core/lpc_chip/chip_17xx_40xx/pmu_17xx_40xx.c \


IR_FILES += $(C_SRC:.c=.ll)

DEFS +=-DCORE_M3
DEFS +=-DCHIP_$(DEVICE)

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

include $(TARGET_MK)
