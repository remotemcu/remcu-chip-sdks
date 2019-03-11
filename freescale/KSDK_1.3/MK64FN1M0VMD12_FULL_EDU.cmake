
set(LICENSE_TYPE EDU)

set(MCU_TYPE MK64FN1M0VMD12)

set(MCU_LIB_NAME KSDK)

set(MCU_MAJOR_VERSION_LIB 1.3.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

#[[
FILE(GLOB COPY_SOURCE_FROM_LIB 
	"${CMAKE_CURRENT_LIST_DIR}/platform/drivers/inc/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/devices/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/devices/MK64F12/startup/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/hal/inc/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/system/inc/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/osa/inc/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/CMSIS/Include/core_cm4.h"
	"${CMAKE_CURRENT_LIST_DIR}/board/*.h")
FILE(GLOB COPY_DESCRIPTION_FROM_LIB "${CMAKE_CURRENT_LIST_DIR}/README.txt")
]]
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
	"${TARGET_DIR_PATH}/platform/drivers/inc/*.h"
	"${TARGET_DIR_PATH}/platform/devices/*.h"
	"${TARGET_DIR_PATH}/platform/devices/MK64F12/startup/*.h"
	"${TARGET_DIR_PATH}/platform/hal/inc/*.h"
	"${TARGET_DIR_PATH}/platform/system/inc/*.h"
	"${TARGET_DIR_PATH}/platform/osa/inc/*.h"
	"${TARGET_DIR_PATH}/platform/CMSIS/Include/core_cm4.h"
	"${TARGET_DIR_PATH}/board/*.h")
	file(COPY ${COPY_SOURCE_FROM_LIB}
		DESTINATION  ${INCLUDE_DIR_PATH}
		)

    file(INSTALL ${TARGET_DIR_PATH}/platform/devices/MK64F12/include/
    	DESTINATION ${INCLUDE_DIR_PATH}/MK64F12/include/
    	FILES_MATCHING PATTERN "*.h"
    	)
    file(INSTALL ${TARGET_DIR_PATH}/platform/hal/src/sim/MK64F12/
    	DESTINATION ${INCLUDE_DIR_PATH}/src/sim/MK64F12/
    	FILES_MATCHING PATTERN "*.h"
    	)
    file(INSTALL ${TARGET_DIR_PATH}/platform/system/src/clock/MK64F12/
    	DESTINATION ${INCLUDE_DIR_PATH}/src/clock/MK64F12/
    	FILES_MATCHING PATTERN "*.h"
    	)
    file(COPY "${TARGET_DIR_PATH}/README.txt"
		DESTINATION  ${README_DIR_PATH}
		)
endfunction()