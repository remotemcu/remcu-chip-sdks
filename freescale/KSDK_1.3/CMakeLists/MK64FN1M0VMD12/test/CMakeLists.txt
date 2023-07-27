project(test C)

add_executable(test_accel_i2c
	accel_i2c/main.c
	accel_i2c/accel.c
	accel_i2c/fxos_api.c
	accel_i2c/hardware_init.c
	accel_i2c/mma8451_api.c
	accel_i2c/gpio_pins.c
	accel_i2c/pin_mux.c
	)

target_include_directories(test_accel_i2c PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_accel_i2c PRIVATE ${ALL_INCLUDE_DIR}/src)
target_include_directories(test_accel_i2c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/accel_i2c)

target_link_libraries(test_accel_i2c remcu)


add_executable(test_gpio
	gpio/gpio.c
	gpio/gpio_pins.c
	gpio/pin_mux.c
	#gpio/board.c
	)

target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR}/src)
target_include_directories(test_gpio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/accel_i2c)

target_link_libraries(test_gpio remcu)

install(TARGETS test_gpio DESTINATION ${DESTINATION_DIR_NAME}/test)
install(TARGETS test_accel_i2c DESTINATION ${DESTINATION_DIR_NAME}/test)