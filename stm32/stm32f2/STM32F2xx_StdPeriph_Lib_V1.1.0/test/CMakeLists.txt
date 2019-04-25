project(test C)

add_executable(DAC_SignalsGeneration
	DAC_SignalsGeneration/main.c
	)

target_include_directories(DAC_SignalsGeneration PRIVATE ${ALL_INCLUDE_DIR})
target_include_directories(DAC_SignalsGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DAC_SignalsGeneration remcu)

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