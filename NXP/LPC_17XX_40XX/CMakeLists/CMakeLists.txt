
include(${REMCU_VM_PATH}/cmake/MultiBuild.cmake)

ExternalProject_Add(LPC175X_6X
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/LPC175X_6X/"
      CMAKE_ARGS ${CMAKE_ARGS}
      )