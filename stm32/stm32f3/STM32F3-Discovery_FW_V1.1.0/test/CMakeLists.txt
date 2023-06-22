project(test CXX)

add_executable(test_TIM6
	TIM6/main.cpp
	)

target_include_directories(test_TIM6 PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_TIM6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_TIM6 remcu)


add_executable(Gyro
	Gyro/main.c
	Gyro/stm32f3_discovery_l3gd20.c
	Gyro/stm32f3_discovery_lsm303dlhc.c
	)

target_include_directories(Gyro PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(Gyro PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Gyro remcu)

install(TARGETS Gyro DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS test_TIM6 DESTINATION ${FULL_ARCHIVE_NAME}/test)
