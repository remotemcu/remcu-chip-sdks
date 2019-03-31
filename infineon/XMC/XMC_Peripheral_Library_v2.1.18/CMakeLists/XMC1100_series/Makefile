
include $(TARGET_MK)


# List of C source files.
C_SRC = \
$(XMC_ROOT)/CMSIS/Infineon/XMC1100_series/Source/system_XMC1100.c \
$(XMC_ROOT)/XMCLib/src/xmc1_eru.c \
$(XMC_ROOT)/XMCLib/src/xmc1_flash.c \
$(XMC_ROOT)/XMCLib/src/xmc1_gpio.c \
$(XMC_ROOT)/XMCLib/src/xmc1_rtc.c \
$(XMC_ROOT)/XMCLib/src/xmc1_scu.c \
$(XMC_ROOT)/XMCLib/src/xmc_acmp.c \
$(XMC_ROOT)/XMCLib/src/xmc_bccu.c \
$(XMC_ROOT)/XMCLib/src/xmc_ccu4.c \
$(XMC_ROOT)/XMCLib/src/xmc_ccu8.c \
$(XMC_ROOT)/XMCLib/src/xmc_common.c \
$(XMC_ROOT)/XMCLib/src/xmc_eru.c \
$(XMC_ROOT)/XMCLib/src/xmc_gpio.c \
$(XMC_ROOT)/XMCLib/src/xmc_i2c.c \
$(XMC_ROOT)/XMCLib/src/xmc_ledts.c \
$(XMC_ROOT)/XMCLib/src/xmc_math.c \
$(XMC_ROOT)/XMCLib/src/xmc_posif.c \
$(XMC_ROOT)/XMCLib/src/xmc_prng.c \
$(XMC_ROOT)/XMCLib/src/xmc_rtc.c \
$(XMC_ROOT)/XMCLib/src/xmc_spi.c \
$(XMC_ROOT)/XMCLib/src/xmc_uart.c \
$(XMC_ROOT)/XMCLib/src/xmc_usic.c \
$(XMC_ROOT)/XMCLib/src/xmc_vadc.c \
$(XMC_ROOT)/XMCLib/src/xmc_wdt.c


SRC_EXTRA = \



# List of include paths.
INC_PATH = \
$(XMC_ROOT)/CMSIS/Infineon/XMC1100_series/Include/ \
$(XMC_ROOT)/CMSIS/Include/ \
$(XMC_ROOT)/XMCLib/inc/ \

INC_EXTRA = \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -DREMCU_LIB -DXMC1100_Q024x0064

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

