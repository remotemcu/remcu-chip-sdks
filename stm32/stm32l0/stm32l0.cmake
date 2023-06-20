
set(MCU_LIB_NAME HAL_LL_drivers)

set(MCU_MAJOR_VERSION_LIB v1.11.2)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers)

set(CONF_SOURCE ${CMAKE_CURRENT_LIST_DIR}/conf.cpp)

set(MAKEFILE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

configure_file(${CMAKE_CURRENT_LIST_DIR}/defines.h.in ${ALL_INCLUDE_DIR}/device_defines.h)

add_custom_command(     
      TARGET MCU_LIB 
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      ${ALL_INCLUDE_DIR})


FILE(GLOB COPY_HEADER_FROM_LIB 
      ${MCU_SDK_PATH}/CMSIS/Device/ST/STM32L0xx/Include/*.h        #system_stm32fl0xx.h
      ${MCU_SDK_PATH}/STM32L0xx_HAL_Driver/transformed_Inc/*.h
      ${MCU_SDK_PATH}/CMSIS/Include/*.h
      ${CMAKE_CURRENT_LIST_DIR}/*.h
      )

file(INSTALL ${MCU_SDK_PATH}/STM32L0xx_HAL_Driver/transformed_Inc/Legacy/
      DESTINATION ${ALL_INCLUDE_DIR}/Legacy/
      FILES_MATCHING PATTERN "*.h"
      )

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/test)
