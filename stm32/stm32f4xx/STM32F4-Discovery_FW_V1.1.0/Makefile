
include $(TARGET_MK)


# List of C source files.
C_SRC = \
./Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c

SRC_EXTRA = \
./Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \

# List of include paths.
INC_PATH = \
       Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
       Libraries/CMSIS/Include/ \
       Libraries/CMSIS/ST/STM32F4xx/Include/ \
       Libraries/inc


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

LOCAL_CFLAGS = $(DEFS) $(INCLUDE_LOCAL)

IR_FILES += $(C_SRC:.c=.ll)


$(OUTPUT): $(IR_FILES)
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@
	#$(AR) rcv $@.ar $(BUILD_DIR)/*.adin.o

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $<).$(IR_SUFFIX)
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).adin.o

