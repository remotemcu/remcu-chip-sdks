cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM8L15X_MD)

set(MCU_LIB_NAME StdPeriph_Driver)

set(MCU_MAJOR_VERSION_LIB V1.4.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(McuCommon)

add_custom_target( MCU_LIB
                   COMMAND make all
                   ${MCU_MAKE_ARGUMENTS}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

#set(ARCHIVE_FILES ${CMAKE_CURRENT_BINARY_DIR}/${MCU_TYPE}.py)

include(shared)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h" 
      DESTINATION ${ALL_INCLUDE_DIR}
      )

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      DESTINATION ${ALL_INCLUDE_DIR}
      )

file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )


file(INSTALL "${MCU_SDK_PATH}/Libraries/STM8L15x_StdPeriph_Driver/inc/"
      DESTINATION ${ALL_INCLUDE_DIR}
      FILES_MATCHING PATTERN "*.h"
      )

add_subdirectory(test)