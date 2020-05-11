cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE STM32F429_439xx)

set(MCU_LIB_NAME StdPeriph_Lib)

set(MCU_MAJOR_VERSION_LIB V1.8.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

include(McuCommon)

message("MCU_SDK_PATH ${MCU_SDK_PATH}")

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
      ${MCU_SDK_PATH}/Libraries/CMSIS/Include/core_cm4.h
      ${MCU_SDK_PATH}/Libraries/CMSIS/Device/ST/STM32F4xx/Include/*.h
      ${MCU_SDK_PATH}/Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_conf.h 
      ${MCU_SDK_PATH}/Libraries/STM32F4xx_StdPeriph_Driver/inc/*.h
      )

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

add_subdirectory(test)
