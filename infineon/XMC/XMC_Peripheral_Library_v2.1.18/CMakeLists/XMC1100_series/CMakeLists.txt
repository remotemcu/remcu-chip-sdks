cmake_minimum_required (VERSION 3.5)

set(LICENSE_TYPE EDU)

set(MCU_TYPE XMC1100_series)

set(MCU_LIB_NAME XMC_Peripheral_Library)

set(MCU_MAJOR_VERSION_LIB v2.1.18)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

#set(MCU_OBJECT_FILE ${BUILD_DIRECTORY}/${MCU_TYPE}.adin.o)

set(LICENSE_TYPE EDU)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)


set(XMC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../)

set(CMAKE_INSTALL_MESSAGE >>>>>>>>>>>>>>)


add_custom_target( MCU_LIB
                   COMMAND make all
                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
                   OUTPUT=${MCU_OBJECT_FILE}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
                   DEVICE=${MCU_TYPE}
                   XMC_ROOT=${XMC_ROOT}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

include(shared)


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

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )


#add_subdirectory(${XMC_ROOT}/test test)
add_subdirectory(test)
#add_subdirectory(test_adc_light)
#add_subdirectory(test_dac)