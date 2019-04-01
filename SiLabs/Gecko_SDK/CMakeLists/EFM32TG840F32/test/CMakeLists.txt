project(test C)

add_executable(test_lcd
	lcd.c
	)

target_include_directories(test_lcd PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_lcd PRIVATE ${ALL_INCLUDE_DIR}/src)
target_include_directories(test_lcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/accel_i2c)

target_link_libraries(test_lcd remcu)


add_executable(test_gpio
	gpio.c
	)

target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR}/src)
target_include_directories(test_gpio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/accel_i2c)

target_link_libraries(test_gpio remcu)