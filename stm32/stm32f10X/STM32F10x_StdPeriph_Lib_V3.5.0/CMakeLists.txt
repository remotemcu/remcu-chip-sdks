cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

include(parse_args.cmake)

set(CMAKE_C_COMPILER_FORCED TRUE)
    set(CMAKE_CXX_COMPILER_FORCED TRUE)

message("CMAKE_C_PLATFORM_ID :  ${CMAKE_C_PLATFORM_ID}")
message("CMAKE_COMPILER_IS_CYGWIN :  ${CMAKE_COMPILER_IS_CYGWIN}")
message("CMAKE_COMPILER_IS_CYGWIN :  ${CMAKE_C_COMPILER_ID}")

ExternalProject_Add(STM32F10X_HD 
      COMMENT           "Building STM32F10X_HD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_HD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

ExternalProject_Add(STM32F10X_MD
      COMMENT           "Building STM32F10X_MD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_MD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )
