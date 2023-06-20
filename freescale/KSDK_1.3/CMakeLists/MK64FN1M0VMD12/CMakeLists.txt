
set(MCU_TYPE MK64FN1M0VMD12)

set(MCU_LIB_NAME KSDK)

set(MCU_MAJOR_VERSION_LIB 1.3.0)

set(MCU_MINOR_VERSION_LIB 01)

set(KSDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(MCU_SDK_PATH ${KSDK_ROOT})

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

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