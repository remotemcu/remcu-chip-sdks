cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE nRF51422)

set(MCU_LIB_NAME SDK)

set(MCU_MAJOR_VERSION_LIB V12.3.0)

set(MCU_MINOR_VERSION_LIB 01)

set(MCU_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

include(${REMCU_VM_PATH}/cmake/mcu_build_target.cmake)

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h" 
      DESTINATION ${ALL_INCLUDE_DIR}
      )


file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )


file(INSTALL 
      "${MCU_SDK_PATH}/components/libraries/util/"
      "${MCU_SDK_PATH}/components/drivers_nrf/common/"
      "${MCU_SDK_PATH}/components/drivers_nrf/adc/"
      "${MCU_SDK_PATH}/components/drivers_nrf/nrf_soc_nosd/"
      "${MCU_SDK_PATH}/components/toolchain/"
      "${MCU_SDK_PATH}/components/device/"
      "${MCU_SDK_PATH}/components/libraries/log/"
      "${MCU_SDK_PATH}/components/boards/"
      "${MCU_SDK_PATH}/components/toolchain/cmsis/include/"
      "${MCU_SDK_PATH}/components/drivers_nrf/hal/"
      "${MCU_SDK_PATH}/components/libraries/log/src/"
      "${MCU_SDK_PATH}/examples/peripheral/adc/pca10028/blank/config/"
      DESTINATION ${ALL_INCLUDE_DIR}
      FILES_MATCHING PATTERN "*.h"
      )

add_subdirectory(test)