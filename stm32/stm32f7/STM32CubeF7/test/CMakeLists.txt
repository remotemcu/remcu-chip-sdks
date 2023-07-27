project(test C)

add_executable(test_GPIO
	gpio.c
	)


target_include_directories(test_GPIO PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_GPIO PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_GPIO remcu)

install(TARGETS test_GPIO DESTINATION ${DESTINATION_DIR_NAME}/test)