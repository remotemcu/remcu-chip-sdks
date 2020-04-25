
if(NOT DEFINED REMCU_VM_PATH)
	set(REMCU_VM_PATH /home/ser/MOCD/AddressInterceptor/AddressInterceptorLib)
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
	set(CMAKE_CXX_COMPILER clang++) 
	#maybe need : CACHE STRING "Linux x64 CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}"
endif()


set(MCU_INCLUDE_MK_FILE ${REMCU_VM_PATH}/mcu_utils/linux.mk)
set(STRIP_COMMAND strip)

include(${REMCU_VM_PATH}/cmake/common_linux_flags.cmake)

set(TARGET_REMCU_OS_NAME Linux_x64_r)

set(LICENSE_TYPE CMT)