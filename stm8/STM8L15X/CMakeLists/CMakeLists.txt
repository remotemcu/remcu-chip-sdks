cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM8L15X_MD 
#      COMMENT           "Building STM8L15X_MD/"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM8L15X_MD/"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

