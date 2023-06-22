project(test C)

add_executable(test_TIM6
	TIM6/main.c
	)

target_include_directories(test_TIM6 PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_TIM6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_TIM6 remcu)

install(TARGETS test_TIM6 DESTINATION ${FULL_ARCHIVE_NAME}/test)