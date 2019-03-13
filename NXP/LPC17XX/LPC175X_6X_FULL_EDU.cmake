
set(LICENSE_TYPE EDU)

set(MCU_TYPE LPC175X_6X)

set(MCU_LIB_NAME lpc_open)

set(MCU_MAJOR_VERSION_LIB 2.10)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_LIST_DIR}/conf.cpp)

set(MCU_OBJECT_FILE ${CMAKE_CURRENT_LIST_DIR}/build/${MCU_TYPE}.adin.o)

add_custom_target( MCU_LIB
	#OUTPUT ${MCU_OBJECT_FILE}
                   COMMAND make all
	                   REMCU_PATH_MK=${REMCU_PATH_MK}
	                   OUTPUT=${MCU_OBJECT_FILE}
	                   DEVICE=${MCU_TYPE}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

set(TARGET_DIR_PATH ${CMAKE_CURRENT_LIST_DIR})

function(copy_target_files INCLUDE_DIR_PATH README_DIR_PATH UTIL_DIR_PATH)
	message(STATUS "Copy Header to: ${INCLUDE_DIR_PATH}")

	FILE(GLOB COPY_SOURCE_FROM_LIB 
	"${TARGET_DIR_PATH}/CMSIS/CMSIS/Include/core_cm3.h"
	"${TARGET_DIR_PATH}/lpc_core/lpc_chip/chip_17xx_40xx/*.h"
	"${TARGET_DIR_PATH}/lpc_core/lpc_chip/chip_common/*.h"
	)
	file(COPY ${COPY_SOURCE_FROM_LIB}
		DESTINATION  ${INCLUDE_DIR_PATH}
		)

    
    file(COPY "${TARGET_DIR_PATH}/README.txt"
		DESTINATION  ${README_DIR_PATH}
		)
endfunction()