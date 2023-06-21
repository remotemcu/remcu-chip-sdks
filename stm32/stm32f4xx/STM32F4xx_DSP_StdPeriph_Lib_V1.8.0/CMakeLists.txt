cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32F401xx 
#      COMMENT           "Building STM32F401xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F401xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

ExternalProject_Add(STM32F410xx
#      COMMENT           "Building STM32F410xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F410xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F411xE
#      COMMENT           "Building STM32F411xE"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F411xE"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F412xG
#      COMMENT           "Building STM32F412xG"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F412xG"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F413_423xx
#      COMMENT           "Building STM32F413_423xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F413_423xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F427_437xx
#      COMMENT           "Building STM32F427_437xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F427_437xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F429_439xx
#      COMMENT           "Building STM32F429_439xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F429_439xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F446xx
#      COMMENT           "Building STM32F446xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F446xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )

ExternalProject_Add(STM32F469_479xx
#      COMMENT           "Building STM32F469_479xx"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/STM32F469_479xx"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )
