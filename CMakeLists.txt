cmake_minimum_required(VERSION "3.10.2")

# change this to the project you're working on
project("blink")

set(VERBOSE)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(CMAKE_BUILD_FLAGS "-Os -w  -ffunction-sections -fdata-sections --param max-inline-insns-single=500 -MMD -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${MCU_FLAGS} ${CMAKE_BUILD_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} ${CMAKE_BUILD_FLAGS} -std=gnu++11 -fno-threadsafe-statics -fno-rtti -fno-exceptions")

add_definitions(-DF_CPU=120000000L -DARDUINO=10810 -DARDUINO_FEATHER_M4 -DARDUINO_ARCH_SAMD -D__SAMD51J19A__ -DADAFRUIT_FEATHER_M4_EXPRESS -D__SAMD51__ -DUSB_VID=0x239A -DUSB_PID=0x8022 -DUSBCON -DUSB_CONFIG_POWER=100 "-DUSB_MANUFACTURER=\"Adafruit LLC\"" "-DUSB_PRODUCT=\"Adafruit Feather M4\"" -D__FPU_PRESENT -DARM_MATH_CM4 -DENABLE_CACHE -DVARIANT_QSPI_BAUD_DEFAULT=50000000)

add_subdirectory(freeRTOS)
add_subdirectory(samd-core)
add_subdirectory(apps)

set(PROGRAMMER ${CMAKE_SOURCE_DIR}/tools/bossac/1.8.0-48-gb176eee/bossac)

add_custom_target(flash
    COMMAND ${PROGRAMMER} -i -d --port=\${PORT} --offset=0x4000 -e -w -v apps/${PROJECT_NAME}.bin -R
    DEPENDS build/apps/${PROJECT_NAME}.bin
)