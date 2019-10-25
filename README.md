# arduino-mcu-slave
### DEPENDANCIES:
- bossac (version 1.9.1) (Atmel SAM chip programmer)
- arm-none-eabi-gcc (ARM cross compiler)
- cmake
- make

### To setup your environment:
First set your target board in the CMakeList.txt file in the root directory. Current supported boards are:
- Feather_m4_express
- Feather_m0
```
mkdir build
cd build
```
For UNIX/LINUX Systems:
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_EXE_LINKER_FLAGS=--specs=nosys.specs --debug-trycompile
```
For Windows Systems:
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\toolchain.cmake -DCMAKE_EXE_LINKER_FLAGS=--specs=nosys.specs --debug-trycompile -G "Unix Makefiles"
```

### To build:<br />
**In the 'build' directory-** Run the command `make [name]` 
- The name will correspond to the folder within the 'app' directory containing the main.cpp you wish to build. 

### To flash the feather m4:<br />
**In the 'build' directory-** Run the command `make flash APP=[name] PORT=[usb_port]`

**\***NOTE:** Right now we don't have a procedure for adding custom libraries to the directory so you will have to keep everything within the main.cpp. Support wil be added with later updates.
