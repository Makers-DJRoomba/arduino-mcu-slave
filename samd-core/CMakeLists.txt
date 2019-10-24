file(GLOB 	arduino_core_c 		cores/arduino/*.c)
file(GLOB 	arduino_core_cpp	cores/arduino/*.cpp)
file(GLOB 	arduino_core_h 		cores/arduino/*.h) 
file(GLOB_RECURSE 	tinyusb_c 	cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src/*.c)
file(GLOB_RECURSE 	tinyusb_h 	cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src/*.h)
file(GLOB 	tinyusb_core_cpp 	cores/arduino/Adafruit_TinyUSB_Core/*.cpp) 
file(GLOB 	tinyusb_core_h 		cores/arduino/Adafruit_TinyUSB_Core/*.h) 
file(GLOB 	usb_core_c 			cores/arduino/USB/*.c) 
file(GLOB 	usb_core_cpp 		cores/arduino/USB/*.cpp) 
file(GLOB 	usb_core_h 			cores/arduino/USB/*.h) 
file(GLOB 	variant_core_cpp	variants/feather_m4/*.cpp) 
file(GLOB 	variant_core_h		variants/feather_m4/*.h) 

set_property(SOURCE cores/arduino/pulse_asm.S PROPERTY LANGUAGE C)

add_library(
	arduino_core_lib
	${arduino_core_c} ${arduino_core_cpp} ${arduino_core_h}
	cores/arduino/pulse_asm.S
	${tinyusb_c} ${tinyusb_h}
	${tinyusb_core_cpp} ${tinyusb_core_h}
	${usb_core_c} ${usb_core_cpp} ${usb_core_h}
	cores/arduino/avr/dtostrf.c
	cores/arduino/avr/dtostrf.h
	${variant_core_cpp} ${variant_core_h}
	)

target_include_directories(arduino_core_lib 
	PUBLIC ${CMAKE_SOURCE_DIR}/freeRTOS
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/cores/arduino/Adafruit_TinyUSB_Core/tinyusb/src 
	PUBLIC ${CMAKE_SOURCE_DIR}/samd-core/variants/feather_m4
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS/4.5.0/CMSIS/Include
	PUBLIC ${CMAKE_SOURCE_DIR}/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL
	)
