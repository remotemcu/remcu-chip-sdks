
set(MCU_TYPE EFM32TG840F32)

set(MCU_LIB_NAME Gecko_SDK)

set(MCU_MAJOR_VERSION_LIB V1)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )


set(GECKO_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)

add_custom_target( MCU_LIB
	#OUTPUT ${MCU_OBJECT_FILE}
                   COMMAND make all
	                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
	                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
	                   OUTPUT=${MCU_OBJECT_FILE}
	                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
	                   DEVICE=${MCU_TYPE}
	                   GECKO_SDK_ROOT=${GECKO_SDK_ROOT}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

include(shared)

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
