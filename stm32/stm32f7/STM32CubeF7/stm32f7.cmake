
set(MCU_LIB_NAME LowLayer_HAL_drivers)

set(MCU_MAJOR_VERSION_LIB V1.16.0)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers)

set(CONF_SOURCE ${CMAKE_CURRENT_LIST_DIR}/conf.cpp)

set(MAKEFILE_DIR ${CMAKE_CURRENT_LIST_DIR})


include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)


configure_file(${CMAKE_CURRENT_LIST_DIR}/defines.h.in ${ALL_INCLUDE_DIR}/device_defines.h)

add_custom_command(     
      TARGET MCU_LIB 
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      ${ALL_INCLUDE_DIR})


FILE(GLOB COPY_HEADER_FROM_LIB 
      ${MCU_SDK_PATH}/CMSIS/Device/ST/STM32F7xx/Include/*.h        #system_stm32f7xx.h
      ${MCU_SDK_PATH}/STM32F7xx_HAL_Driver/transformed_Inc/*.h
      ${MCU_SDK_PATH}/STM32F7xx_HAL_Driver/${MCU_TYPE}/*
      ${MCU_SDK_PATH}/CMSIS/Include/*.h
      )

file(INSTALL ${MCU_SDK_PATH}/STM32F7xx_HAL_Driver/transformed_Inc/Legacy/
      DESTINATION ${ALL_INCLUDE_DIR}/Legacy/
      FILES_MATCHING PATTERN "*.h"
      )

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/test)
