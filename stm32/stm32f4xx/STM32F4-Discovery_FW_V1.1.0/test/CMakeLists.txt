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


add_executable(CAN_LOOP
	CAN_LOOP/main.c
	)

target_include_directories(CAN_LOOP PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(CAN_LOOP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CAN_LOOP remcu)


add_executable(CAN_Networking
	CAN_Networking/main.c
	)

target_include_directories(CAN_Networking PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(CAN_Networking PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CAN_Networking remcu)