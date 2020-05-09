cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32F30X)

set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V1.1.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)

add_custom_target( MCU_LIB
                   COMMAND make all
                   ${MCU_MAKE_ARGUMENTS}
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
      Libraries/CMSIS/Include/core_cm4.h
      Libraries/CMSIS/Device/ST/STM32F30x/Include/*.h
      Libraries/STM32F30x_StdPeriph_Driver/inc/*.h
      Libraries/stm32f30x_conf.h
      Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c
      )

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(test)