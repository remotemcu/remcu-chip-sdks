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
#PERIPHDRIVERS += stm32f4xx_pwr
PERIPHDRIVERS += stm32f4xx_rcc
PERIPHDRIVERS += stm32f4xx_rng
PERIPHDRIVERS += stm32f4xx_rtc
PERIPHDRIVERS += stm32f4xx_sdio
PERIPHDRIVERS += stm32f4xx_spi
PERIPHDRIVERS += stm32f4xx_syscfg
PERIPHDRIVERS += stm32f4xx_tim
PERIPHDRIVERS += stm32f4xx_usart
PERIPHDRIVERS += stm32f4xx_wwdg
PERIPHDRIVERS += system_stm32f4xx


STM32_INCLUDES = \
	-I./Libraries/CMSIS/ST/STM32F4xx/Include/ \
	-I./Libraries/CMSIS/Include/ \
	-I./Libraries/STM32F4xx_StdPeriph_Driver/inc/ \



# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

OPT = ${LLVM_ADIN_PATH}/opt

ifndef LLVM_ADIN_PATH
$(error "LLVM_ADIN_PATH variable not set!")
endif

OPT_FLAGS = -S -adin

ADIN_SUFFIX = adin

CFLAGS += -S -emit-llvm

DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F4XX
# -DHSI_VALUE
#-DHSE_VALUE=8000000
CFLAGS +=$(DEFS) -I./ -I./ $(STM32_INCLUDES)


STDPERIPH_SRC_PATH = ./Libraries/STM32F4xx_StdPeriph_Driver/src

SUFFIX = ll

OBJS += $(addprefix $(STDPERIPH_SRC_PATH)/, $(addsuffix .$(SUFFIX), $(PERIPHDRIVERS)))


BUILD_DIR 	= build


all: $(BUILD_DIR) $(TARGET).$(SUFFIX)

$(TARGET).$(SUFFIX): $(OBJS)
	$(LD) -v $(BUILD_DIR)/*.$(SUFFIX) -S -o $(BUILD_DIR)/$@
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$@ -o  $(BUILD_DIR)/$(TARGET).${ADIN_SUFFIX}.$(SUFFIX)

# compile
#------------------------------------------------------------------------------- 
%.$(SUFFIX): %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

#-------------------------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) -rf $(TOREMOVE) $(BUILD_DIR)


$(BUILD_DIR):
	mkdir -p $@