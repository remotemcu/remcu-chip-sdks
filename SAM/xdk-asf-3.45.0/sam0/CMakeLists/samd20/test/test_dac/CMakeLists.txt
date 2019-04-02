project(qs_dac_basic C)

add_executable(qs_dac_basic
	qs_dac_basic.c
	board_init.c
	)
target_include_directories(qs_dac_basic PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(qs_dac_basic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(qs_dac_basic remcu)