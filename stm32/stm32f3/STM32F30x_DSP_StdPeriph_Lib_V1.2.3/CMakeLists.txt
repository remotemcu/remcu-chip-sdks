cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32F334x8
      COMMENT           "Building STM32F334x8"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F334x8/"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )