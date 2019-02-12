TARGET = STM32F4XX
OS := $(shell uname)


CC = clang
LD = llvm-link
AR = llvm-ar
CP = objcopy
SZ = size
RM = rm


PERIPHDRIVERS = stm32f4xx_adc
PERIPHDRIVERS += stm32f4xx_can
PERIPHDRIVERS += stm32f4xx_crc
PERIPHDRIVERS += stm32f4xx_cryp_aes
PERIPHDRIVERS += stm32f4xx_cryp
PERIPHDRIVERS += stm32f4xx_cryp_des
PERIPHDRIVERS += stm32f4xx_cryp_tdes
PERIPHDRIVERS += stm32f4xx_dac
PERIPHDRIVERS += stm32f4xx_dbgmcu
PERIPHDRIVERS += stm32f4xx_dcmi
PERIPHDRIVERS += stm32f4xx_dma
PERIPHDRIVERS += stm32f4xx_exti
PERIPHDRIVERS += stm32f4xx_flash
PERIPHDRIVERS += stm32f4xx_fsmc
PERIPHDRIVERS += stm32f4xx_gpio
PERIPHDRIVERS += stm32f4xx_hash
PERIPHDRIVERS += stm32f4xx_hash_md5
PERIPHDRIVERS += stm32f4xx_hash_sha1
PERIPHDRIVERS += stm32f4xx_i2c
PERIPHDRIVERS += stm32f4xx_iwdg
PERIPHDRIVERS += stm32f4xx_pwr
PERIPHDRIVERS += stm32f4xx_rcc
PERIPHDRIVERS += stm32f4xx_rng
PERIPHDRIVERS += stm32f4xx_rtc
PERIPHDRIVERS += stm32f4xx_sdio
PERIPHDRIVERS += stm32f4xx_spi
PERIPHDRIVERS += stm32f4xx_syscfg
PERIPHDRIVERS += stm32f4xx_tim
PERIPHDRIVERS += stm32f4xx_usart
PERIPHDRIVERS += stm32f4xx_wwdg


STM32_INCLUDES = \
	-I./Libraries/CMSIS/ST/STM32F4xx/Include/ \
	-I./Libraries/CMSIS/Include/ \
	-I./Libraries/STM32F4xx_StdPeriph_Driver/inc/ \



# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

CFLAGS += -S -emit-llvm

DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DMANGUSTA_DISCOVERY -DUSE_USB_OTG_FS -DHSI_VALUE
#-DHSE_VALUE=8000000
CFLAGS +=$(DEFS) -I./ -I./ $(STM32_INCLUDES)

SRC = \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \


STDPERIPH_SRC_PATH = ./Libraries/STM32F4xx_StdPeriph_Driver/src


OBJS += $(addprefix $(STDPERIPH_SRC_PATH)/, $(addsuffix .ll, $(PERIPHDRIVERS)))


BUILD_DIR 	= build


all: $(BUILD_DIR) $(TARGET).ll

$(TARGET).ll: $(OBJS)
	$(LD) -v $(BUILD_DIR)/*.ll -S -o $(BUILD_DIR)/$@

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $^ -o $@

#-------------------------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) -rf $(TOREMOVE) $(BUILD_DIR)


$(BUILD_DIR):
	mkdir -p $@