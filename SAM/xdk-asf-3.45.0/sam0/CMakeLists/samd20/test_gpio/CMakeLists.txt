project(Test C)

add_executable(test_gpio_samd20_xpro_board
	led_toggle.c
	board_init.c
	)
target_include_directories(test_gpio_samd20_xpro_board PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_gpio_samd20_xpro_board PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_gpio_samd20_xpro_board remcu)