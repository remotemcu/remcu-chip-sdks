project(test C)

add_executable(test_TIM6
	TIM6/main.c
	)

target_include_directories(test_TIM6 PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_TIM6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_TIM6 remcu)


add_executable(test_acc
	acc/main.c
	acc/stm32f4_discovery.c
	acc/stm32f4_discovery_lis302dl.c
	)

target_include_directories(test_acc PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_acc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_acc remcu)