cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE XMC1100_series)

set(MCU_LIB_NAME XMC_Peripheral_Library)

set(MCU_MAJOR_VERSION_LIB v2.1.18)

set(MCU_MINOR_VERSION_LIB 01)

set(XMC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(MCU_SDK_PATH ${XMC_ROOT})

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )
file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

FILE(GLOB COPY_HEADER_FROM_LIB 
      ${XMC_ROOT}/CMSIS/Infineon/XMC1100_series/Include/*.h 
      ${XMC_ROOT}/CMSIS/Include/core_cm0.h
      ${XMC_ROOT}/CMSIS/Include/cmsis_compiler.h
      ${XMC_ROOT}/CMSIS/Include/cmsis_gcc.h
      ${XMC_ROOT}/XMCLib/inc/*.h
      )


file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )


add_subdirectory(test)
