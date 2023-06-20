
set(MCU_TYPE LPC175X_6X)

set(MCU_LIB_NAME lpc_open)

set(MCU_MAJOR_VERSION_LIB 2.10)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )
file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

FILE(GLOB COPY_SOURCE_FROM_LIB 
"${MCU_SDK_PATH}/CMSIS/CMSIS/Include/core_cm3.h"
"${MCU_SDK_PATH}/lpc_core/lpc_chip/chip_17xx_40xx/*.h"
"${MCU_SDK_PATH}/lpc_core/lpc_chip/chip_common/*.h"
)
file(COPY ${COPY_SOURCE_FROM_LIB}
	DESTINATION  ${ALL_INCLUDE_DIR}
	)


add_subdirectory(test)