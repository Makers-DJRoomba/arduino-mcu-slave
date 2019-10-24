# feather-m4-slave
To setup your environment:
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_EXE_LINKER_FLAGS=--specs=nosys.specs --debug-trycompile
```

To build:
In the root directory- Edit the project name CMakeLists.txt file to be the desired application
- The name will correspond to the folder within the 'app' directory containing the main.cpp you wish to build. 
In the build directory- Run the command 'make'

To flash the feather m4:
In the build directory- run 'make flash PORT=[usb_port]'

NOTE: Right now we don't have a procedure for adding custom libraries to the directory so you will have to keep everything within the main.cpp. Support wil be added with later updates.
