set(LINKER ${CMAKE_SOURCE_DIR}/samd-core/variants/feather_m4/linker_scripts/gcc/flash_with_bootloader.ld)

file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(child ${children})
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
	add_executable(${child} ${child}/main.cpp)

	set_target_properties(${child} PROPERTIES LINK_FLAGS "${MCU_FLAGS} -T${LINKER} -Wl,-Map,${child}.map -Os -Wl,--gc-sections -save-temps -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align")

	target_link_libraries(${child} PRIVATE
		custom_lib
		freeRTOS_lib
		arduino_core_lib
		)

	set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

	add_custom_command(TARGET ${child} POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -O binary ${child} ${child}.bin
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

	set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${child}.bin" APPEND)
	set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${child}.map" APPEND)

endif()
endforeach()


