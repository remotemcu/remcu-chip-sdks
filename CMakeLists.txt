cmake_minimum_required(VERSION 3.5)

set(REMCU_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/output)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	message("**************************************************\n\n\n")
	message("not defined toolchain file")
	message("set -DCMAKE_TOOLCHAIN_FILE argument")
	message("for example: cmake . -DCMAKE_TOOLCHAIN_FILE=REMCU/platform/windows_x64.cmake")
	message(FATAL_ERROR "\n\n\n**************************************************")
endif()

add_subdirectory(stm32)

add_subdirectory(stm8)

add_subdirectory(nordicsemi)

if(NOT WIN32)
	add_subdirectory(NXP)

	add_subdirectory(SiLabs)

	add_subdirectory(Atmel)

	add_subdirectory(freescale)
	
	add_subdirectory(infineon)
endif(NOT WIN32)
