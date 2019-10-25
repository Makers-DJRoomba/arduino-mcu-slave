file(GLOB_RECURSE Library_C_SOURCES *.c)
file(GLOB_RECURSE Library_CPP_SOURCES *.cpp)
file(GLOB_RECURSE Library_HEADER *.h) 

add_library(
	custom_lib
	${Library_C_SOURCES} ${Library_CPP_SOURCES} ${Library_HEADER}
	)

target_include_directories(custom_lib 
	PUBLIC ${CMAKE_SOURCE_DIR}/custom-lib
	PUBLIC ${CMAKE_SOURCE_DIR}/freeRTOS
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src 
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/variants/feather_m4
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS/4.5.0/CMSIS/Include
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL
	)