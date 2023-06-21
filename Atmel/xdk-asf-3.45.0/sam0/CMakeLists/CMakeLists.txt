
include(${REMCU_VM_PATH}/cmake/MultiBuild.cmake)

ExternalProject_Add(samd20
##      COMMENT           "Building samd20"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/samd20/"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )