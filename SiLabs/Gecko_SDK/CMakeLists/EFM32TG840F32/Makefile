
GECKO_SDK_ROOT = $(MCU_SDK_PATH)

INC_PATH += \
$(GECKO_SDK_ROOT)/platform/CMSIS/Include \
$(GECKO_SDK_ROOT)/platform/emlib/inc \
$(GECKO_SDK_ROOT)/platform/Device/SiliconLabs/EFM32TG/Include \
$(GECKO_SDK_ROOT)/hardware/kit/common/bsp \
$(GECKO_SDK_ROOT)/hardware/kit/EFM32TG_STK3300/config \
$(GECKO_SDK_ROOT)/hardware/kit/common/drivers \
$(GECKO_SDK_ROOT)/platform/emdrv/common/inc \

#$(GECKO_SDK_ROOT)/platform/CMSIS/Include \

C_SRC +=  \
$(GECKO_SDK_ROOT)/platform/emlib/src/em_assert.c \
$(GECKO_SDK_ROOT)/platform/emlib/src/em_cmu.c \
$(GECKO_SDK_ROOT)/platform/emlib/src/em_gpio.c \
$(GECKO_SDK_ROOT)/platform/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c \
$(GECKO_SDK_ROOT)/hardware/kit/common/bsp/bsp_stk.c \
$(GECKO_SDK_ROOT)/hardware/kit/common/bsp/bsp_stk_leds.c \
$(GECKO_SDK_ROOT)/hardware/kit/common/bsp/bsp_bcc.c \
$(GECKO_SDK_ROOT)/platform/emlib/src/em_usart.c \
$(GECKO_SDK_ROOT)/hardware/kit/common/drivers/segmentlcd.c \
$(GECKO_SDK_ROOT)/platform/emlib/src/em_lcd.c \

 
IR_FILES += $(C_SRC:.c=.ll)

DEFS += -D$(DEVICE)
INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))


include $(TARGET_MK)
