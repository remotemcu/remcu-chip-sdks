
set(MCU_TYPE EFM32TG840F32)

set(MCU_LIB_NAME Gecko_SDK)

set(MCU_MAJOR_VERSION_LIB V1)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

set(GECKO_SDK_ROOT ${MCU_SDK_PATH})

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )
file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

FILE(GLOB COPY_SOURCE_FROM_LIB 
	${GECKO_SDK_ROOT}/platform/CMSIS/Include/core_cm3.h
	"${GECKO_SDK_ROOT}/platform/emlib/inc/*.h"
	"${GECKO_SDK_ROOT}/hardware/kit/common/bsp/*.h"
	"${GECKO_SDK_ROOT}/platform/Device/SiliconLabs/EFM32TG/Include/*.h"
	"${GECKO_SDK_ROOT}/hardware/kit/EFM32TG_STK3300/config/*.h"
	"${GECKO_SDK_ROOT}/hardware/kit/common/drivers/segmentlcd.h"
	)


file(COPY ${COPY_SOURCE_FROM_LIB}
	DESTINATION  ${ALL_INCLUDE_DIR}
	)


add_subdirectory(test)
