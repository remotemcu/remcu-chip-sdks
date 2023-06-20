
include(${REMCU_VM_PATH}/cmake/MultiBuild.cmake)

ExternalProject_Add(MK64FN1M0VMD12
      COMMENT           "Building MK64FN1M0VMD12"
      DOWNLOAD_COMMAND ""
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/MK64FN1M0VMD12/"
      CMAKE_ARGS ${CMAKE_ARGS}
      INSTALL_COMMAND ""
      )