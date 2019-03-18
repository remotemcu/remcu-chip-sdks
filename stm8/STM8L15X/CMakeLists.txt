cmake_minimum_required (VERSION 3.5)

set(LICENSE_TYPE EDU)

set(MCU_TYPE STM8L15X_MD)

set(MCU_LIB_NAME STDPERIPH_DRIVER)

set(MCU_MAJOR_VERSION_LIB V1.4.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_LIST_DIR}/conf.cpp)

set(MCU_OBJECT_FILE ${CMAKE_CURRENT_LIST_DIR}/build/${MCU_TYPE}.adin.o)

set(LICENSE_TYPE EDU)


set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)

add_custom_target( MCU_LIB
                   COMMAND make all
                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
                   OUTPUT=${MCU_OBJECT_FILE}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
                   DEVICE=${MCU_TYPE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

include(shared)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/STM8L15x_StdPeriph_Driver/inc/"
      DESTINATION ${ALL_INCLUDE_DIR}
      FILES_MATCHING PATTERN "*.h"
      )