SDK_ROOT := $(MCU_SDK_PATH)

C_SRC +=  \
  $(SDK_ROOT)/components/boards/boards.c \
  $(SDK_ROOT)/components/drivers_nrf/hal/nrf_adc.c \
  $(SDK_ROOT)/components/drivers_nrf/adc/nrf_drv_adc.c \
  $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c \
  $(SDK_ROOT)/components/toolchain/system_nrf51.c \


# ../config -> $(SDK_ROOT)/examples/peripheral/adc/pca10028/blank/config

INC_PATH =  \
  $(SDK_ROOT)/components/libraries/util \
  $(SDK_ROOT)/examples/peripheral/adc/pca10028/blank/config \
  $(SDK_ROOT)/components/drivers_nrf/common \
  $(SDK_ROOT)/components/drivers_nrf/adc \
  $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd \
  $(SDK_ROOT)/components/toolchain \
  $(SDK_ROOT)/components/device \
  $(SDK_ROOT)/components/libraries/log \
  $(SDK_ROOT)/components/boards \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/components/drivers_nrf/hal \
  $(SDK_ROOT)/components/libraries/log/src \

# TOOLCHAIN OPTIONS
#-------------------------------------------------------------------------------

DEFS += -DNRF51 -DNRF51422 -DBOARD_PCA10028 -DBSP_DEFINES_ONLY

include $(TARGET_MK)
