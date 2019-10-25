file(GLOB Library_SOURCES *.c)
file(GLOB Library_HEADER *.h) 

add_library(
	freeRTOS_lib
	${Library_SOURCES} ${Library_HEADERS}
	)

target_include_directories(freeRTOS_lib 
	PUBLIC ${CMAKE_SOURCE_DIR}/custom-lib
	PUBLIC ${CMAKE_SOURCE_DIR}/freeRTOS
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src 
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/variants/${TARGET_BOARD}
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS/4.5.0/CMSIS/Include
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL
	)