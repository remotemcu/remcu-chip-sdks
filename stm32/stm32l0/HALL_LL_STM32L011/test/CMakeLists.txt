project(test CXX)

add_executable(test_clock
	gpio.cpp
	)


target_include_directories(test_clock PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_clock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_clock remcu)