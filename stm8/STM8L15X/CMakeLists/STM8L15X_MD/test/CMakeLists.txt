project(Test C)

add_executable(test_stm8l_discovery_lcd 
	main.c
	stm8l_discovery_lcd.c
	)
target_include_directories(test_stm8l_discovery_lcd PRIVATE ${ALL_INCLUDE_DIR})
target_link_libraries(test_stm8l_discovery_lcd remcu)

install(TARGETS test_stm8l_discovery_lcd DESTINATION ${DESTINATION_DIR_NAME}/test)