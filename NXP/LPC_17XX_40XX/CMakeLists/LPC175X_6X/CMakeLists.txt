
set(LICENSE_TYPE EDU)

set(MCU_TYPE LPC175X_6X)

set(MCU_LIB_NAME lpc_open)

set(MCU_MAJOR_VERSION_LIB 2.10)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_custom_target( MCU_LIB
                   COMMAND make all
                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
                   OUTPUT=${MCU_OBJECT_FILE}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
                   DEVICE=${MCU_TYPE}
                   MCU_SDK_PATH=${MCU_SDK_PATH}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
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
"${MCU_SDK_PATH}/CMSIS/CMSIS/Include/core_cm3.h"
"${MCU_SDK_PATH}/lpc_core/lpc_chip/chip_17xx_40xx/*.h"
"${MCU_SDK_PATH}/lpc_core/lpc_chip/chip_common/*.h"
)
file(COPY ${COPY_SOURCE_FROM_LIB}
	DESTINATION  ${ALL_INCLUDE_DIR}
	)


add_subdirectory(test)