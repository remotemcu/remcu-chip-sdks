# peripherial driver
#-------------------------------------------------------------------------------
PERIPHDRIVERS += stm32f10x_adc
PERIPHDRIVERS += stm32f10x_bkp
PERIPHDRIVERS += stm32f10x_can
PERIPHDRIVERS += stm32f10x_cec
PERIPHDRIVERS += stm32f10x_crc
PERIPHDRIVERS += stm32f10x_dbgmcu
PERIPHDRIVERS += stm32f10x_exti
PERIPHDRIVERS += stm32f10x_flash
PERIPHDRIVERS += stm32f10x_fsmc
PERIPHDRIVERS += stm32f10x_gpio
PERIPHDRIVERS += stm32f10x_i2c
PERIPHDRIVERS += stm32f10x_iwdg
#PERIPHDRIVERS += stm32f10x_pwr	#problem: contains ARM assebler instructions
PERIPHDRIVERS += stm32f10x_rcc
PERIPHDRIVERS += stm32f10x_rtc
PERIPHDRIVERS += stm32f10x_sdio
PERIPHDRIVERS += stm32f10x_spi
PERIPHDRIVERS += stm32f10x_tim
PERIPHDRIVERS += stm32f10x_usart
PERIPHDRIVERS += stm32f10x_wwdg
PERIPHDRIVERS += stm32f10x_dma
#PERIPHDRIVERS += misc.c

# USE DEFINES
#-------------------------------------------------------------------------------
DEFINES += USE_STDPERIPH_DRIVER
DEFINES += $(TARGET)

# PATH to CMSIS and StdPeriph Lib
#-------------------------------------------------------------------------------
CMSIS_PATH         = cmsis
STDPERIPH_INC_PATH = stdperiph/inc
STDPERIPH_SRC_PATH = stdperiph/src


# PATH SOURCE
#-------------------------------------------------------------------------------
#SOURCEDIRS := src
SOURCEDIRS += $(CMSIS_PATH)

# PATH HEADERS
#-------------------------------------------------------------------------------
INCLUDES += .
INCLUDES += $(SOURCEDIRS) 
INCLUDES += $(CMSIS_PATH)
INCLUDES += $(STDPERIPH_INC_PATH)




CFLAGS += $(addprefix -I, $(INCLUDES))
CFLAGS += $(addprefix -D, $(DEFINES))

# OBJECT FILES
#-------------------------------------------------------------------------------
OBJS += $(patsubst %.c, %.ll, $(wildcard  $(addsuffix /*.c, $(SOURCEDIRS))))
OBJS += $(addprefix $(STDPERIPH_SRC_PATH)/, $(addsuffix .ll, $(PERIPHDRIVERS)))

# list of directories that make should search
#-------------------------------------------------------------------------------
VPATH := $(SOURCEDIRS)

# temp file
#-------------------------------------------------------------------------------
TOREMOVE += $(addsuffix /*.ll, $(SOURCEDIRS))
TOREMOVE += $(addsuffix /*.o, $(SOURCEDIRS))
TOREMOVE += $(addsuffix /*.d, $(SOURCEDIRS))
TOREMOVE += $(STDPERIPH_SRC_PATH)/*.ll


BUILD_DIR 	= build

ifdef ADIN_PATH
include $(ADIN_PATH)/adin.mk
endif

ifndef TARGET
$(warning "TARGET variable not set!")
endif


#-------------------------------------------------------------------------------
.PHONY: clean
clean:
	$(RM) -rf $(TOREMOVE) $(BUILD_DIR)

print-%  : ; @echo $* = $($*)


# compile
#------------------------------------------------------------------------------- 
%.ll: %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

