project(test_display_ssd1306 C)

add_executable(test_display_ssd1306
	ssd1306.c
	ssd1306_example.c
	font.c
	)
target_include_directories(test_display_ssd1306 PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_display_ssd1306 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_display_ssd1306 remcu)

install(TARGETS test_display_ssd1306 DESTINATION ${DESTINATION_DIR_NAME}/test)