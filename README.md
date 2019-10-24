# feather-m4-slave
To setup your environment:
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_EXE_LINKER_FLAGS=--specs=nosys.specs --debug-trycompile
```

### To build:<br />
**In the root directory-** Edit the project name CMakeLists.txt file to be the desired application <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- The name will correspond to the folder within the 'app' directory containing the main.cpp you wish to build. <br />
**In the 'build' directory-** Run the command `make` <br />

### To flash the feather m4:<br />
**In the 'build' directory-** Run the command `make flash PORT=[usb_port]`<br />

**\***NOTE:** Right now we don't have a procedure for adding custom libraries to the directory so you will have to keep everything within the main.cpp. Support wil be added with later updates.
