cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32F10X_HD 
#      COMMENT           "Building STM32F10X_HD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_HD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

ExternalProject_Add(STM32F10X_MD
#      COMMENT           "Building STM32F10X_MD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_MD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F10X_CL
#      COMMENT           "Building STM32F10X_CL"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_CL"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )