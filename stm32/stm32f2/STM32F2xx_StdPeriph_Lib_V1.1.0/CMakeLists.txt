cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32F2XX)

set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V1.1.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)


file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )
file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

add_custom_command(     
      TARGET MCU_LIB 
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${MCU_TYPE}_${MCU_LIB_NAME}.py"
      ${ALL_INCLUDE_DIR})

FILE(GLOB COPY_HEADER_FROM_LIB 
      Libraries/CMSIS/Include/core_cm3.h
      Libraries/CMSIS/Device/ST/STM32F2xx/Include/*.h
      Libraries/STM32F2xx_StdPeriph_Driver/inc/*.h
      Project/STM32F2xx_StdPeriph_Template/stm32f2xx_conf.h
      Libraries/CMSIS/Device/ST/STM32F2xx/Source/Templates/system_stm32f2xx.c
      )


file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(test)
