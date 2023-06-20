cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32F4XX)

set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V1.1.0)

set(MCU_MINOR_VERSION_LIB 01)

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

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
      Libraries/CMSIS/Include/core_cm4.h
      Libraries/CMSIS/ST/STM32F4xx/Include/*.h
      Libraries/STM32F4xx_StdPeriph_Driver/inc/*.h
      Libraries/inc/*.h
      Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
      )

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(test)
