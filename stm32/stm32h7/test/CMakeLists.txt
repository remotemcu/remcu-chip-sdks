project(test C)

add_executable(test_clock
	clock.c
	)


target_include_directories(test_clock PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_clock remcu)

install(TARGETS test_clock DESTINATION ${DESTINATION_DIR_NAME}/test)