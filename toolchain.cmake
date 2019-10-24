set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Arm)
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++)
set(CMAKE_EXE_LINKER_FLAGS --specs=nosys.specs)

set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> rcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> rcs <TARGET> <LINK_FLAGS> <OBJECTS>")