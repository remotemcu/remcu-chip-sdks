project(Test C)

add_executable(test_build_nrf5_adc 
	main.c
	)
target_include_directories(test_build_nrf5_adc PRIVATE ${ALL_INCLUDE_DIR})
target_link_libraries(test_build_nrf5_adc remcu)

install(TARGETS test_build_nrf5_adc DESTINATION ${FULL_ARCHIVE_NAME}/test)