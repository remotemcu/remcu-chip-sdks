
include(${REMCU_VM_PATH}/cmake/MultiBuild.cmake)

ExternalProject_Add(XMC1100_series
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/XMC1100_series/"
      CMAKE_ARGS ${CMAKE_ARGS}
      )