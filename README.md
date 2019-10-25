# feather-m4-slave
### DEPENDANCIES:
- bossac (version 1.9.1) (Atmel SAM chip programmer)
- arm-none-eabi-gcc (ARM cross compiler)

### To setup your environment:
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_EXE_LINKER_FLAGS=--specs=nosys.specs --debug-trycompile
```

### To build:<br />
**In the 'build' directory-** Run the command `make [name]` <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- The name will correspond to the folder within the 'app' directory containing the main.cpp you wish to build. <br />

### To flash the feather m4:<br />
**In the 'build' directory-** Run the command `make flash APP=[name] PORT=[usb_port]`<br />

**\***NOTE:** Right now we don't have a procedure for adding custom libraries to the directory so you will have to keep everything within the main.cpp. Support wil be added with later updates.
