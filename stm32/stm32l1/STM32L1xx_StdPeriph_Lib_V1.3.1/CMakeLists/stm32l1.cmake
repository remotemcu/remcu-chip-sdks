
set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V1.3.1)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CONF_SOURCE ${CMAKE_CURRENT_LIST_DIR}/conf.cpp)

set(MAKEFILE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )

add_custom_command(     
      TARGET MCU_LIB 
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      ${ALL_INCLUDE_DIR})

file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

FILE(GLOB COPY_HEADER_FROM_LIB 
      ${MCU_SDK_PATH}/Libraries/CMSIS/Include/core_cm3.h
      ${MCU_SDK_PATH}/Libraries/CMSIS/Device/ST/STM32L1xx/Include/*.h
      ${MCU_SDK_PATH}/Libraries/STM32L1xx_StdPeriph_Driver/inc/*.h
      ${MCU_SDK_PATH}/Libraries/Template/*_conf.h
      ${MCU_SDK_PATH}/Libraries/CMSIS/Device/ST/STM32L1xx/Include/system_stm32f10x.c
      )


file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/test)
