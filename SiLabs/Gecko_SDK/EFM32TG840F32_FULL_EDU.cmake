
set(LICENSE_TYPE EDU)

set(MCU_TYPE EFM32TG840F32)

set(MCU_LIB_NAME EMLIB)

set(MCU_MAJOR_VERSION_LIB V1)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

FILE(GLOB COPY_SOURCE_FROM_LIB 
	"${CMAKE_CURRENT_LIST_DIR}/platform/emlib/inc/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/hardware/kit/common/bsp/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/platform/Device/SiliconLabs/EFM32TG/Include/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/hardware/kit/EFM32TG_STK3300/config/*.h"
	"${CMAKE_CURRENT_LIST_DIR}/hardware/kit/common/drivers/segmentlcd.h")
FILE(GLOB COPY_DESCRIPTION_FROM_LIB "${CMAKE_CURRENT_LIST_DIR}/README.txt")

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
