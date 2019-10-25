cmake_minimum_required(VERSION "3.10.2")

# change this to the project you're working on
project("DJRoomba")
set(TARGET_BOARD feather_m0)

set(VERBOSE)

if(${TARGET_BOARD} MATCHES feather_m4)
	set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
	add_definitions(-DF_CPU=120000000L -DARDUINO=10810 -DARDUINO_FEATHER_M4 -DARDUINO_ARCH_SAMD -D__SAMD51J19A__ -DADAFRUIT_FEATHER_M4_EXPRESS -D__SAMD51__ -DUSB_VID=0x239A -DUSB_PID=0x8022 -DUSBCON -DUSB_CONFIG_POWER=100 "-DUSB_MANUFACTURER=\"Adafruit LLC\"" "-DUSB_PRODUCT=\"Adafruit Feather M4\"" -D__FPU_PRESENT -DARM_MATH_CM4 -DENABLE_CACHE -DVARIANT_QSPI_BAUD_DEFAULT=50000000)
	set(FLASH_FLAG -i -d --offset=0x4000 -e -w -v -R)
elseif(${TARGET_BOARD} MATCHES feather_m0)
	set(MCU_FLAGS "-mcpu=cortex-m0plus -mthumb")
	add_definitions(-DF_CPU=48000000L -DARDUINO=10810 -DARDUINO_SAMD_ZERO -DARDUINO_ARCH_SAMD -D__SAMD21G18A__ -DADAFRUIT_FEATHER_M0 -D__SAMD21__ -DUSB_VID=0x239A -DUSB_PID=0x800B -DUSBCON -DUSB_CONFIG_POWER=100 "-DUSB_MANUFACTURER=\"Adafruit LLC\"" "-DUSB_PRODUCT=\"Feather M0\"" -DARM_MATH_CM0PLUS -DENABLE_CACHE -DVARIANT_QSPI_BAUD_DEFAULT=50000000)
	set(FLASH_FLAG -i -d --offset=0x2000 -e -w -v -R)
endif()

set(CMAKE_BUILD_FLAGS "-Os -w  -ffunction-sections -fdata-sections --param max-inline-insns-single=500 -MMD")
set(CMAKE_C_FLAGS "${MCU_FLAGS} ${CMAKE_BUILD_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} ${CMAKE_BUILD_FLAGS} -std=gnu++11 -fno-threadsafe-statics -fno-rtti -fno-exceptions")

add_subdirectory(custom-lib)
add_subdirectory(freeRTOS)
add_subdirectory(samd-core)
add_subdirectory(apps)

set(PROGRAMMER bossac)

add_custom_target(flash
    COMMAND ${PROGRAMMER} ${FLASH_FLAG} --port=\${PORT} apps/\${APP}.bin 
    DEPENDS build/apps/${APP}
)


