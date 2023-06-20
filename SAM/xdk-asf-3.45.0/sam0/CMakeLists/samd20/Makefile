
ASF_ROOT = $(MCU_SDK_PATH)

# List of C source files.
C_SRC = \
       $(ASF_ROOT)/sam0/drivers/port/port.c                           \
       $(ASF_ROOT)/sam0/drivers/system/clock/clock_samd20/clock.c     \
       $(ASF_ROOT)/sam0/drivers/system/clock/clock_samd20/gclk.c      \
       $(ASF_ROOT)/sam0/drivers/adc/adc_sam_d_r_h/adc.c               \
       $(ASF_ROOT)/sam0/drivers/system/pinmux/pinmux.c                \
       $(ASF_ROOT)/sam0/drivers/system/system.c                       \
       $(ASF_ROOT)/sam0/utils/cmsis/samd20/source/system_samd20.c     \
       $(ASF_ROOT)/sam0/drivers/dac/dac_sam_d_c_h/dac.c               \
       $(ASF_ROOT)/sam0/drivers/sercom/sercom.c                       \
       $(ASF_ROOT)/sam0/drivers/sercom/spi/spi.c                      \

SRC_UNCESS = \
       $(ASF_ROOT)/sam0/applications/led_toggle/led_toggle.c          \
       $(ASF_ROOT)/sam0/drivers/system/interrupt/system_interrupt.c   \
       $(ASF_ROOT)/common/utils/interrupt/interrupt_sam_nvic.c        \
       $(ASF_ROOT)/sam0/boards/samd20_xplained_pro/board_init.c       \
	$(ASF_ROOT)/sam0/utils/syscalls/gcc/syscalls.c

# List of include paths.
INC_PATH = \
       $(ASF_ROOT)/common/utils                                       \
       $(ASF_ROOT)/sam0/boards                                        \
       $(ASF_ROOT)/sam0/boards/samd20_xplained_pro                    \
       $(ASF_ROOT)/sam0/boards/samd20_xplained_pro/board_config       \
       $(ASF_ROOT)/sam0/drivers/port                                  \
       $(ASF_ROOT)/sam0/drivers/system                                \
       $(ASF_ROOT)/sam0/drivers/system/clock                          \
       $(ASF_ROOT)/sam0/drivers/system/clock/clock_samd20             \
       $(ASF_ROOT)/sam0/drivers/system/pinmux                         \
       $(ASF_ROOT)/sam0/drivers/system/power                          \
       $(ASF_ROOT)/sam0/drivers/system/power/power_sam_d_r_h          \
       $(ASF_ROOT)/sam0/drivers/system/reset                          \
       $(ASF_ROOT)/sam0/drivers/system/reset/reset_sam_d_r_h          \
       $(ASF_ROOT)/sam0/utils                                         \
       $(ASF_ROOT)/sam0/utils/cmsis/samd20/include                    \
       $(ASF_ROOT)/sam0/utils/cmsis/samd20/source                     \
       $(ASF_ROOT)/sam0/utils/header_files                            \
       $(ASF_ROOT)/sam0/utils/preprocessor                            \
       $(ASF_ROOT)/thirdparty/CMSIS/Include                           \
       $(ASF_ROOT)/sam0/drivers/system/interrupt                      \
       $(ASF_ROOT)/sam0/drivers/adc                                   \
       $(ASF_ROOT)/sam0/drivers/adc/adc_sam_d_r_h                     \
       $(ASF_ROOT)/sam0/drivers/dac                                   \
       $(ASF_ROOT)/sam0/drivers/dac/dac_sam_d_c_h                     \
       $(ASF_ROOT)/sam0/drivers/sercom                                \
       $(ASF_ROOT)/sam0/drivers/sercom/spi                            \


INC_EXTRA = \
       $(ASF_ROOT)/common/boards                                      \
       $(ASF_ROOT)/sam0/drivers/system/interrupt/system_interrupt_samd20 \
       $(ASF_ROOT)/thirdparty/CMSIS/Lib/GCC 							\
       $(ASF_ROOT)/sam0/applications/led_toggle                       \
       $(ASF_ROOT)/sam0/applications/led_toggle/samd20_xplained_pro/gcc \
       $(ASF_ROOT)/sam0/applications/led_toggle/samd20_xplained_pro   \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS = -D__$(DEVICE)__ -DREMCU_LIB -DBOARD=SAMD20_XPLAINED_PRO -DADC_CALLBACK_MODE=false
DEFS += -DSPI_CALLBACK_MODE=false

INCLUDE_LOCAL  += $(foreach INC,$(addprefix $(PRJ_PATH),$(INC_PATH)),-I$(INC))

include $(TARGET_MK)
