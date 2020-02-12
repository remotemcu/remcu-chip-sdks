cmake_minimum_required(VERSION 3.5)

project(External NONE)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

include(parse_args.cmake)

#[[
get_cmake_property(CACHE_VARS CACHE_VARIABLES)
foreach(CACHE_VAR ${CACHE_VARS})
  get_property(CACHE_VAR_HELPSTRING CACHE ${CACHE_VAR} PROPERTY HELPSTRING)
  if(CACHE_VAR_HELPSTRING STREQUAL "No help, variable specified on the command line.")
    get_property(CACHE_VAR_TYPE CACHE ${CACHE_VAR} PROPERTY TYPE)
    if(CACHE_VAR_TYPE STREQUAL "UNINITIALIZED")
      set(CACHE_VAR_TYPE)
    else()
      set(CACHE_VAR_TYPE :${CACHE_VAR_TYPE})
    endif()
    #set(CMAKE_ARGS "${CMAKE_ARGS} -D${CACHE_VAR}${CACHE_VAR_TYPE}=\"${${CACHE_VAR}}\"")
    list(APPEND CMAKE_ARGS "-D${CACHE_VAR}${CACHE_VAR_TYPE}=${${CACHE_VAR}}")
  endif()
endforeach()
]]

message("--------  ${CMAKE_ARGS}")

ExternalProject_Add(STM32F10X_HD 
      COMMENT           "Building STM32F10X_HD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_HD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND "11111111111111111111"
      )

ExternalProject_Add(STM32F10X_MD
      COMMENT           "Building STM32F10X_MD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32F10X_MD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ls -la
       )
