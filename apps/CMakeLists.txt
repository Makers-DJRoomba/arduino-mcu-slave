add_executable(${PROJECT_NAME} ${PROJECT_NAME}/main.cpp)

set(LINKER ${CMAKE_SOURCE_DIR}/samd-core/variants/feather_m4/linker_scripts/gcc/flash_with_bootloader.ld)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${MCU_FLAGS} -T${LINKER} -Wl,-Map,${PROJECT_NAME}.map -Os -Wl,--gc-sections -save-temps -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align")

target_link_libraries(${PROJECT_NAME} PRIVATE
	freeRTOS_lib
	arduino_core_lib
	)

set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
