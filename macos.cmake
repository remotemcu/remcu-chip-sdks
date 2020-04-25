
if(NOT DEFINED REMCU_VM_PATH)
	set(REMCU_VM_PATH /Users/mk/Downloads/rmcu/test/remcu)
endif()

if(NOT DEFINED LLVM_ADIN_PATH)
    set(LLVM_ADIN_PATH /Users/mk/Downloads/rmcu/test/build-llvm-adin-jule/bin/)
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
	set(CMAKE_CXX_COMPILER clang++) 
	#maybe need : CACHE STRING "Linux x64 CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}"
endif()

#set(CLANG_PATH /Users/mk/Downloads/rmcu/anaconda2/bin/)
#set(CLANG_PATH /Users/mk/Downloads/rmcu/clang/clang+llvm-6.0.0-x86_64-apple-darwin/bin/)

set(MCU_INCLUDE_MK_FILE ${REMCU_VM_PATH}/mcu_utils/linux.mk)
set(STRIP_COMMAND strip)

include(${REMCU_VM_PATH}/cmake/common_linux_flags.cmake)
set(STRIP_ARGUMENT -NSXxT)
set(TARGET_REMCU_OS_NAME MacOS_Darwin_x64)

set(LICENSE_TYPE CMT)