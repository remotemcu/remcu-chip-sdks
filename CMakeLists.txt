
add_subdirectory(stm32)

add_subdirectory(stm8)

if(NOT WIN32)
	add_subdirectory(NXP)

	add_subdirectory(SiLabs)

	add_subdirectory(Atmel)

	add_subdirectory(freescale)
	
	add_subdirectory(infineon)
endif(NOT WIN32)
