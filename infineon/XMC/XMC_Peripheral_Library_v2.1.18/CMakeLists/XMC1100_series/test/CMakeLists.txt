project(test C)

add_executable(test_gpio
	gpio.c
	)

target_include_directories(test_gpio PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_gpio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_gpio remcu)

add_executable(test_uart
	uart.c
	)

target_include_directories(test_uart PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_uart PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_uart remcu)

install(TARGETS test_gpio DESTINATION ${DESTINATION_DIR_NAME}/test)
install(TARGETS test_uart DESTINATION ${DESTINATION_DIR_NAME}/test)