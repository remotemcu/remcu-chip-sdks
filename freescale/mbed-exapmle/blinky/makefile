# ----- Configuration ---------------------------------------------------------

TOOLCHAIN_PREFIX = arm-none-eabi-
PROJECT_NAME     = blinky

LIBS_DIR = ../libs
SDK_ROOT = $(LIBS_DIR)/SDK_2.2_FRDM-K64F

# ----- Sources ---------------------------------------------------------------

SYMBOLS += CPU_MK64FN1M0VLL12
SYMBOLS += SDK_DEBUGCONSOLE=1

INCLUDE_DIRS += $(LIBS_DIR)

# Startup/System
INCLUDE_DIRS += $(SDK_ROOT)/CMSIS/Include
INCLUDE_DIRS += $(SDK_ROOT)/CMSIS/Driver/Include
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/system_MK64F12.c
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/gcc/startup_MK64F12.S

# FreeRTOS
INCLUDE_DIRS += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/include
INCLUDE_DIRS += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/portable/GCC/ARM_CM4F
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/list.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/queue.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/tasks.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/timers.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/portable/GCC/ARM_CM4F/fsl_tickless_systick.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/portable/GCC/ARM_CM4F/port.c
SOURCE_FILES += $(SDK_ROOT)/rtos/freertos_9.0.0/Source/portable/MemMang/heap_3.c

# Driver
INCLUDE_DIRS += $(SDK_ROOT)/devices/MK64F12
INCLUDE_DIRS += $(SDK_ROOT)/devices/MK64F12/cmsis_drivers
INCLUDE_DIRS += $(SDK_ROOT)/devices/MK64F12/drivers
INCLUDE_DIRS += $(SDK_ROOT)/devices/MK64F12/utilities
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/drivers/fsl_clock.c
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/drivers/fsl_gpio.c
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/drivers/fsl_uart.c
SOURCE_FILES += $(SDK_ROOT)/devices/MK64F12/utilities/fsl_debug_console.c

# SEGGER RTT
INCLUDE_DIRS += $(LIBS_DIR)/SEGGER_RTT/RTT
SOURCE_FILES += $(LIBS_DIR)/SEGGER_RTT/RTT/SEGGER_RTT.c

INCLUDE_DIRS += src/config

SOURCE_FILES += $(shell find src -iregex ".*\.\(c\|cpp\)")

# ----- Flags -----------------------------------------------------------------

GCCFLAGS += -mcpu=cortex-m4
GCCFLAGS += -mthumb
GCCFLAGS += -mfloat-abi=hard
GCCFLAGS += -mfpu=fpv4-sp-d16

CFLAGS += -O3
CFLAGS += -flto
CFLAGS += -std=gnu11

CXXFLAGS += -O3
CXXFLAGS += -flto
CXXFLAGS += -std=gnu++14

# CPPFLAGS +=

LDFLAGS += -T$(SDK_ROOT)/devices/MK64F12/gcc/MK64FN1M0xxx12_flash.ld
LDFLAGS += --specs=nano.specs
LDFLAGS += --specs=nosys.specs

# ----- Rules -----------------------------------------------------------------

include $(LIBS_DIR)/xXx/utils/rules.mk

download: $(PROJECT_NAME).elf
	$(TOOLCHAIN_PREFIX)gdb -q -x download.gdb $<
