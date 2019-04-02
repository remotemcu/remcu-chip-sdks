project(test C)

add_executable(test_gpio
	gpio.c
	)

target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR})

target_link_libraries(test_gpio remcu)

add_executable(test_adc
	adc.c
	)

target_include_directories(test_adc PRIVATE ${ALL_INCLUDE_DIR})

target_link_libraries(test_adc remcu)

add_executable(test_dac
	dac.c
	)

target_include_directories(test_dac PRIVATE ${ALL_INCLUDE_DIR})

target_link_libraries(test_dac remcu)