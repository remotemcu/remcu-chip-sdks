project(test C)

add_executable(test_TIM6
	TIM6/main.cpp
	)

target_include_directories(test_TIM6 PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_TIM6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_TIM6 remcu)

add_executable(test_CAN_LOOP
	CAN_LOOP/main.c
	)

target_include_directories(test_CAN_LOOP PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_CAN_LOOP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_CAN_LOOP remcu)

add_executable(test_CAN_Networking
	CAN_Networking/main.c
	)

target_include_directories(test_CAN_Networking PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(test_CAN_Networking PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_CAN_Networking remcu)

add_executable(TriangleWave
	DAC/TriangleWave.c
	)

target_include_directories(TriangleWave PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(TriangleWave PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TriangleWave remcu)

add_executable(NoiseWave
	DAC/NoiseWave.c
	)

target_include_directories(NoiseWave PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(NoiseWave PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(NoiseWave remcu)

add_executable(DAC_DMA_Escalator
	DAC/DAC_DMA_Escalator.c
	)

target_include_directories(DAC_DMA_Escalator PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(DAC_DMA_Escalator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DAC_DMA_Escalator remcu)

install(TARGETS DAC_DMA_Escalator DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS NoiseWave DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS TriangleWave DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS test_CAN_Networking DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS test_CAN_LOOP DESTINATION ${FULL_ARCHIVE_NAME}/test)
install(TARGETS test_TIM6 DESTINATION ${FULL_ARCHIVE_NAME}/test)
