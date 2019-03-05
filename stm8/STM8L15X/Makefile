
include $(REMCU_PATH_MK)/remcu.mk

PERIPHDRIVERS = stm8l15x_adc
PERIPHDRIVERS += stm8l15x_aes
PERIPHDRIVERS += stm8l15x_beep
PERIPHDRIVERS += stm8l15x_clk
PERIPHDRIVERS += stm8l15x_comp
PERIPHDRIVERS += stm8l15x_dac
PERIPHDRIVERS += stm8l15x_dma
PERIPHDRIVERS += stm8l15x_exti
PERIPHDRIVERS += stm8l15x_flash
PERIPHDRIVERS += stm8l15x_gpio
PERIPHDRIVERS += stm8l15x_i2c
PERIPHDRIVERS += stm8l15x_irtim
PERIPHDRIVERS += stm8l15x_itc
PERIPHDRIVERS += stm8l15x_iwdg
PERIPHDRIVERS += stm8l15x_lcd
PERIPHDRIVERS += stm8l15x_pwr
PERIPHDRIVERS += stm8l15x_rst
PERIPHDRIVERS += stm8l15x_rtc
PERIPHDRIVERS += stm8l15x_spi
PERIPHDRIVERS += stm8l15x_syscfg
PERIPHDRIVERS += stm8l15x_tim1
PERIPHDRIVERS += stm8l15x_tim2
PERIPHDRIVERS += stm8l15x_tim3
PERIPHDRIVERS += stm8l15x_tim4
PERIPHDRIVERS += stm8l15x_tim5
PERIPHDRIVERS += stm8l15x_usart
PERIPHDRIVERS += stm8l15x_wfe
PERIPHDRIVERS += stm8l15x_wwdg


STM8_INCLUDES = 	-I./Libraries/STM8L15x_StdPeriph_Driver/inc/

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DUSE_STDPERIPH_DRIVER -D$(TARGET)

LOCAL_CFLAGS = $(DEFS) -I./ -I./ $(STM8_INCLUDES)


STDPERIPH_SRC_PATH = ./Libraries/STM8L15x_StdPeriph_Driver/src


OBJS += $(addprefix $(STDPERIPH_SRC_PATH)/, $(addsuffix .ll, $(PERIPHDRIVERS)))


$(OUTPUT): $(OBJS)
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@

# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $<).ll
	$(OPT) $(OPT_FLAGS) $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll
	#$(CLANG) $(COMPILE_FLAGS) -c $(BUILD_DIR)/$(notdir $<).adin.ll -o $(BUILD_DIR)/$(notdir $<).o

