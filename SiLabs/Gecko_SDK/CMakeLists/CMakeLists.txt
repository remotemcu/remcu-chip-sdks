
include(${REMCU_VM_PATH}/cmake/MultiBuild.cmake)

ExternalProject_Add(EFM32TG840F32
      COMMENT           "Building EFM32TG840F32"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/EFM32TG840F32/"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )