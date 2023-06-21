cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32F030 
#      COMMENT           "Building STM32F030"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F030"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

ExternalProject_Add(STM32F042
#      COMMENT           "Building STM32F042"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F042"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F051
#      COMMENT           "Building STM32F051"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F051"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F072
#      COMMENT           "Building STM32F072"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F072"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F091
#      COMMENT           "Building STM32F091"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F091"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

