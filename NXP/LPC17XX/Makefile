
include $(REMCU_PATH_MK)/remcu.mk

#DEVICE = EFM32TG840F32

BUILD_DIR = build

INCLUDEPATHS += \
 -I CMSIS/CMSIS/Include/  \
 -I lpc_core/lpc_chip/chip_17xx_40xx/ \
 -I lpc_core/lpc_chip/chip_common/ \

 #-I lpc_core/lpc_chip/chip_17xx_40xx/config_177x_8x/ \

C_CXX_SRC += \
lpc_core/lpc_chip/chip_17xx_40xx/i2s_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/rtc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/spi_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/dac_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/sdc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/gpdma_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/sysinit_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/gpio_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/eeprom_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/timer_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/cmp_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/stopwatch_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/i2c_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/gpioint_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/crc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/can_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/uart_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/wwdt_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/enet_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/ssp_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/clock_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/ritimer_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/adc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/sdmmc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/iocon_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/emc_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/chip_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/sysctl_17xx_40xx.c \
lpc_core/lpc_chip/chip_17xx_40xx/lcd_17xx_40xx.c

C_CXX_SRC += \
lpc_core/lpc_chip/chip_common/eeprom.c \
lpc_core/lpc_chip/chip_common/ring_buffer.c \
lpc_core/lpc_chip/chip_common/fpu_init.c \
lpc_core/lpc_chip/chip_common/iap.c

C_CXX_SRC_UNCESS +=  \
lpc_core/lpc_chip/chip_17xx_40xx/pmu_17xx_40xx.c \


C_SRC = $(filter %.c, $(C_CXX_SRC))
CXX_SRC = $(filter %.cpp, $(C_CXX_SRC))


IR_FILES += $(C_SRC:.c=.ll)

LOCAL_CFLAGS +=-DCORE_M3
LOCAL_CFLAGS +=-DCHIP_$(DEVICE)

#LOCAL_CXXFLAGS += -D$(DEVICE)

$(OUTPUT): $(IR_FILES)
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@

# Create objects from C SRC files
%.ll: %.c
	@echo "Building file: $<"
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) $(INCLUDEPATHS) -c  $< -o $(BUILD_DIR)/$(notdir $<).ll
	$(OPT) $(OPT_FLAGS)  $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll