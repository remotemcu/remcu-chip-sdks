project(qs_adc_basic C)

add_executable(qs_adc_basic
	qs_adc_basic.c
	board_init.c
	)
target_include_directories(qs_adc_basic PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(qs_adc_basic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(qs_adc_basic remcu)