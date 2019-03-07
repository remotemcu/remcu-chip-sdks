
include $(REMCU_PATH_MK)/remcu.mk

#DEVICE = EFM32TG840F32

BUILD_DIR = build

INCLUDEPATHS += \
-I platform/emlib/inc \
-I platform/Device/SiliconLabs/EFM32TG/Include \

#-I hardware/kit/common/bsp \
#-I hardware/kit/EFM32TG_STK3300/config

#-I platform/CMSIS/Include \

C_CXX_SRC +=  \
 platform/emlib/src/em_assert.c \
 platform/emlib/src/em_cmu.c \
 platform/emlib/src/em_gpio.c \
 platform/emlib/src/em_system.c \
 platform/emlib/src/em_usart.c \
 platform/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c \

 #hardware/kit/common/bsp/bsp_bcc.c \
 #hardware/kit/common/bsp/bsp_stk.c \
 #hardware/kit/common/bsp/bsp_stk_leds.c \ 
 #platform/emlib/src/em_emu.c \


C_SRC = $(filter %.c, $(C_CXX_SRC))
CXX_SRC = $(filter %.cpp, $(C_CXX_SRC))


IR_FILES += $(C_SRC:.c=.ll)

LOCAL_CFLAGS += -D$(DEVICE)

LOCAL_CXXFLAGS += -D$(DEVICE)

$(OUTPUT): $(IR_FILES)
	$(LD) -v $(BUILD_DIR)/*.adin.ll -S -o $@.ll
	$(CLANG) $(COMPILE_FLAGS) -c $@.ll -o $@

# Create objects from C SRC files
%.ll: %.c
	@echo "Building file: $<"
	$(CLANG) $(IR_FLAGS) $(LOCAL_CFLAGS) $(INCLUDEPATHS) -c  $< -o $(BUILD_DIR)/$(notdir $<).ll
	$(OPT) $(OPT_FLAGS)  $(BUILD_DIR)/$(notdir $<).ll -o  $(BUILD_DIR)/$(notdir $<).adin.ll