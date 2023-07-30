set(DESTINATION_DIR_NAME_PREFIX STM32/)

add_subdirectory(stm32f0)

add_subdirectory(stm32f10X)

add_subdirectory(stm32f2)

add_subdirectory(stm32f3)

add_subdirectory(stm32f4xx)

add_subdirectory(stm32l1)

if(NOT ${TARGET_REMCU_OS_NAME} STREQUAL "Raspbian_armv6")
	add_subdirectory(stm32l0)
endif()

add_subdirectory(stm32f7)

add_subdirectory(stm32h7)