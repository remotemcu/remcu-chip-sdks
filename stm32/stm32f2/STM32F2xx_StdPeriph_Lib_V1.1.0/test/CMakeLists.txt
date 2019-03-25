project(test C)

add_executable(DAC_SignalsGeneration
	DAC_SignalsGeneration/main.c
	)

target_include_directories(DAC_SignalsGeneration PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(DAC_SignalsGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DAC_SignalsGeneration remcu)