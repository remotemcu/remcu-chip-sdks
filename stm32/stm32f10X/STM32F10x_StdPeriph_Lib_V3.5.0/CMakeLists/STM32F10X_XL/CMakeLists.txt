cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32F10X_XL)

set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V3.5.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_custom_target( MCU_LIB
                   COMMAND make all
                   DEVICE=${MCU_TYPE}
                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
                   CROSS_MK_FILE=${CROSS_MK_FILE}
                   OUTPUT=${MCU_OBJECT_FILE}
                   MCU_SDK_PATH=${MCU_SDK_PATH}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

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

FILE(GLOB COPY_HEADER_FROM_LIB 
      ${MCU_SDK_PATH}/Libraries/CMSIS/CM3/CoreSupport/core_cm3.h
      ${MCU_SDK_PATH}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/*.h
      ${MCU_SDK_PATH}/Libraries/STM32F10x_StdPeriph_Driver/inc/*.h
      ${MCU_SDK_PATH}/Project/STM32F10x_StdPeriph_Template/stm32f10x_conf.h
      ${MCU_SDK_PATH}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
      )

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

#add_subdirectory(test)
