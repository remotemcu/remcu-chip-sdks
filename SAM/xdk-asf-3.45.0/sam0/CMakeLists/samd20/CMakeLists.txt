cmake_minimum_required (VERSION 3.5)

set(MCU_TYPE SAMD20J18)

set(MCU_LIB_NAME ASF)

set(MCU_MAJOR_VERSION_LIB v3.45.0)

set(MCU_MINOR_VERSION_LIB 01)

set(FULL_NAME_MCU_LIB ${MCU_TYPE}-${MCU_LIB_NAME}-${MCU_MAJOR_VERSION_LIB}-${MCU_MINOR_VERSION_LIB} )

set(CONF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.cpp)

set(CMAKE_MODULE_PATH ${REMCU_VM_PATH}/cmake)

include(McuCommon)


set(ASF_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../)

set(CMAKE_INSTALL_MESSAGE >>>>>>>>>>>>>>)


add_custom_target( MCU_LIB
                   COMMAND make all
                   MCU_UTIL_PATH=${MCU_UTIL_PATH}
                   TARGET_MK=${MCU_INCLUDE_MK_FILE}
                   OUTPUT=${MCU_OBJECT_FILE}
                   CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   BUILD_DIRECTORY=${BUILD_DIRECTORY}
                   DEVICE=${MCU_TYPE}
                   ASF_ROOT=${ASF_ROOT}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "---------------- Generating ADIN IR ----------------"
)

include(shared)
#[[
file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/STM8L15x_StdPeriph_Driver/inc/"
      DESTINATION ${ALL_INCLUDE_DIR}
      FILES_MATCHING PATTERN "*.h"
      )
]]
file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/defines_${MCU_TYPE}.h"
      DESTINATION ${ALL_INCLUDE_DIR}
      )
file(RENAME "${ALL_INCLUDE_DIR}/defines_${MCU_TYPE}.h"
            ${ALL_INCLUDE_DIR}/device_defines.h
      )

FILE(GLOB COPY_HEADER_FROM_LIB 
      "${ASF_ROOT}/common/utils/*.h"
      #"${ASF_ROOT}/sam0/applications/led_toggle/samd20_xplained_pro/*.h"
      "${ASF_ROOT}/sam0/boards/*.h"
      "${ASF_ROOT}/sam0/boards/samd20_xplained_pro/board_config/*.h"
      "${ASF_ROOT}/sam0/drivers/port/*.h"
      "${ASF_ROOT}/sam0/drivers/adc/adc.h"
      "${ASF_ROOT}/sam0/drivers/adc/adc_sam_d_r_h/adc_feature.h"
      "${ASF_ROOT}/sam0/drivers/dac/dac.h"
      "${ASF_ROOT}/sam0/drivers/dac/dac_sam_d_c_h/dac_feature.h"
      "${ASF_ROOT}/sam0/drivers/sercom/*.h"
      "${ASF_ROOT}/sam0/drivers/sercom/spi/*.h"
      "${ASF_ROOT}/sam0/drivers/system/*.h"
      "${ASF_ROOT}/sam0/drivers/system/clock/*.h"
      "${ASF_ROOT}/sam0/drivers/system/clock/clock_samd20/*.h"
      "${ASF_ROOT}/sam0/drivers/system/pinmux/*.h"
      "${ASF_ROOT}/sam0/drivers/system/power/*.h"
      "${ASF_ROOT}/sam0/drivers/system/power/power_sam_d_r_h/*.h"
      "${ASF_ROOT}/sam0/drivers/system/reset/*.h"
      "${ASF_ROOT}/sam0/drivers/system/reset/reset_sam_d_r_h/*.h"
      "${ASF_ROOT}/sam0/utils/*.h"
      "${ASF_ROOT}/sam0/utils/cmsis/samd20/include/*.h"
      "${ASF_ROOT}/sam0/utils/cmsis/samd20/source/*.h"
      "${ASF_ROOT}/sam0/utils/header_files/*.h"
      "${ASF_ROOT}/sam0/utils/preprocessor/*.h"
      "${ASF_ROOT}/thirdparty/CMSIS/Include/*.h"
      "${ASF_ROOT}/sam0/drivers/system/interrupt/*.h"
      )

#message(COPY_HEADER_FROM_LIB "******* $CONF_SOURCE is not defined! ********")

file(INSTALL ${COPY_HEADER_FROM_LIB}
            DESTINATION  ${ALL_INCLUDE_DIR}
            )

file(INSTALL 
      ${ASF_ROOT}/sam0/utils/cmsis/samd20/include/
      DESTINATION ${ALL_INCLUDE_DIR}
      FILES_MATCHING PATTERN "*.h"
      )

file(INSTALL 
      ${ASF_ROOT}/sam0/boards/samd20_xplained_pro/
      DESTINATION ${ALL_INCLUDE_DIR}/samd20_xplained_pro
      FILES_MATCHING PATTERN "*.h"
      )

#[[
      "${ASF_ROOT}/sam0/boards/samd20_xplained_pro/*.h"

       ${ASF_ROOT}/sam0/applications/led_toggle/samd20_xplained_pro
       ${ASF_ROOT}/sam0/boards                                        
       ${ASF_ROOT}/sam0/boards/samd20_xplained_pro                    
       ${ASF_ROOT}/sam0/drivers/port                                  
       ${ASF_ROOT}/sam0/drivers/system                                
       ${ASF_ROOT}/sam0/drivers/system/clock                          
       ${ASF_ROOT}/sam0/drivers/system/clock/clock_samd20             
       ${ASF_ROOT}/sam0/drivers/system/pinmux                         
       ${ASF_ROOT}/sam0/drivers/system/power                          
       ${ASF_ROOT}/sam0/drivers/system/power/power_sam_d_r_h          
       ${ASF_ROOT}/sam0/drivers/system/reset                          
       ${ASF_ROOT}/sam0/drivers/system/reset/reset_sam_d_r_h          
       ${ASF_ROOT}/sam0/utils                                         
       ${ASF_ROOT}/sam0/utils/cmsis/samd20/include                    
       ${ASF_ROOT}/sam0/utils/cmsis/samd20/source                     
       ${ASF_ROOT}/sam0/utils/header_files                            
       ${ASF_ROOT}/sam0/utils/preprocessor                            
       ${ASF_ROOT}/thirdparty/CMSIS/Include                           
       ${ASF_ROOT}/sam0/drivers/system/interrupt      

"${ASF_ROOT}/common/utils"
       ]]
add_subdirectory(test)