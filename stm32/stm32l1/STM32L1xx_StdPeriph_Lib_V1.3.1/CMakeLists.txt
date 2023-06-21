cmake_minimum_required(VERSION 3.5)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)
include(MultiBuild)

ExternalProject_Add(STM32L1XX_MD 
#      COMMENT           "Building STM32L1XX_MD"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32L1XX_MD"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )

ExternalProject_Add(STM32L1XX_MDP
#      COMMENT           "Building STM32L1XX_MDP"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists/STM32L1XX_MDP"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
       )
