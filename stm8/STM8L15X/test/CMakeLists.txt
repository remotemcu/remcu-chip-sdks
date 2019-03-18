project(Test C)

add_executable(test_stm8l_discovery 
	main.c
	delay.c
	icc_measure.c
	stm8l_discovery_lcd.c
	)
target_include_directories(test_stm8l_discovery PRIVATE ${ALL_INCLUDE_DIR})
target_link_libraries(test_stm8l_discovery remcu)