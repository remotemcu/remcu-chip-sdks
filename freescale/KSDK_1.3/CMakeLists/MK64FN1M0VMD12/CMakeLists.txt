
set(LICENSE_TYPE EDU)

set(MCU_TYPE MK64FN1M0VMD12)

set(MCU_LIB_NAME KSDK)

set(MCU_MAJOR_VERSION_LIB 1.3.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(KSDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(LICENSE_TYPE EDU)

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
	                   KSDK_ROOT=${KSDK_ROOT}
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
"${KSDK_ROOT}/platform/drivers/inc/*.h"
"${KSDK_ROOT}/platform/devices/*.h"
"${KSDK_ROOT}/platform/devices/MK64F12/startup/*.h"
"${KSDK_ROOT}/platform/hal/inc/*.h"
"${KSDK_ROOT}/platform/system/inc/*.h"
"${KSDK_ROOT}/platform/osa/inc/*.h"
"${KSDK_ROOT}/platform/CMSIS/Include/core_cm4.h"
"${KSDK_ROOT}/board/*.h")
file(COPY ${COPY_SOURCE_FROM_LIB}
	DESTINATION  ${ALL_INCLUDE_DIR}
	)

message("ALL_INCLUDE_DIR ${ALL_INCLUDE_DIR} -")

file(INSTALL ${KSDK_ROOT}/platform/devices/MK64F12/include/
	DESTINATION ${ALL_INCLUDE_DIR}/MK64F12/include/
	FILES_MATCHING PATTERN "*.h"
	)
file(INSTALL ${KSDK_ROOT}/platform/hal/src/sim/MK64F12/
	DESTINATION ${ALL_INCLUDE_DIR}/src/sim/MK64F12/
	FILES_MATCHING PATTERN "*.h"
	)
file(INSTALL ${KSDK_ROOT}/platform/system/src/clock/MK64F12/
	DESTINATION ${ALL_INCLUDE_DIR}/src/clock/MK64F12/
	FILES_MATCHING PATTERN "*.h"
	)

add_subdirectory(test)