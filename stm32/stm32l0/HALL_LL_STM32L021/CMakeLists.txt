cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32L021xx)

set(MCU_LIB_NAME LowLayer_HAL_drivers)

set(MCU_MAJOR_VERSION_LIB v1.11.2)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers)

include(McuCommon)

add_custom_target( MCU_LIB
                   COMMAND make all
                   ${MCU_MAKE_ARGUMENTS}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

include(shared)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/defines.h.in ${ALL_INCLUDE_DIR}/device_defines.h)

add_custom_command(     
      TARGET MCU_LIB 
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      ${ALL_INCLUDE_DIR})


FILE(GLOB COPY_HEADER_FROM_LIB 
      ${MCU_SDK_PATH}/CMSIS/Device/ST/STM32L0xx/Include/*.h        #system_stm32fl0xx.h
      ${MCU_SDK_PATH}/STM32L0xx_HAL_Driver/transformed_Inc/*.h
      ${MCU_SDK_PATH}/CMSIS/Include/*.h
      ${CMAKE_CURRENT_SOURCE_DIR}/*.h
      )

file(INSTALL ${MCU_SDK_PATH}/STM32L0xx_HAL_Driver/transformed_Inc/Legacy/
      DESTINATION ${ALL_INCLUDE_DIR}/Legacy/
      FILES_MATCHING PATTERN "*.h"
      )

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(test)
