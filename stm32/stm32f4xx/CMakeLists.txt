cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(DESTINATION_DIR_NAME_PREFIX ${DESTINATION_DIR_NAME_PREFIX}/STM32F4/)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32F4-Discovery_FW_V1.1.0 
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F4-Discovery_FW_V1.1.0/"
      CMAKE_ARGS ${CMAKE_ARGS}
      )


add_subdirectory(STM32F4xx_DSP_StdPeriph_Lib_V1.8.0)