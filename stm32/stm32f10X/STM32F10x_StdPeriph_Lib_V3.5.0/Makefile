
include $(TARGET_MK)


# List of C source files.
C_SRC = \
./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

SRC_EXTRA = \
./Libraries/STM32F10x_StdPeriph_Driver/src/misc.c \
./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \


# List of include paths.
INC_PATH = \
       Libraries/STM32F10x_StdPeriph_Driver/inc/ \
       Libraries/CMSIS/CM3/CoreSupport/ \
       Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/ \
       Project/STM32F10x_StdPeriph_Template/ \


INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD

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

