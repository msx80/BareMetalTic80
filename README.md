# BareMetalTic80
Port of TIC80 to bare metal Raspberry Pi

## How to build


* The build works on a regular x86 linux.
* Download [gcc arm toolkit](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) and expand on your disk and add it to your path:

* `PATH=/home/xxxx/gcc-arm-none-eabi-8-2018-q4-major/bin/:$PATH`

* clone the repository and modules
* `git clone --recursive https://github.com/msx80/BareMetalTic80.git`
* `cd BareMetalTic80`
* Build circle-stdlib runtime:
* `cd circle-stdlib`
* `./configure --raspberrypi 2`
* `make`
* `cd ..`
* Copy modified cmake file to Tic80
* `cp tic80editedCMakeLists.txt TIC-80/CMakeLists.txt`
* `cd TIC-80`
* Build TIC-80 core:
* `cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../arm-gcc-toolchain.cmake .`
* `make tic80core`
* `cd ..`
* Now on to build the "kernel":
* `cd baremetaltic80`
* now for some reason there's a type conflict on s32 and u32 (strangely not on other types whick are also defined, anyone has an idea?)
* edit `../TIC-80/include/tic80_types.h` comment out s32 and u32
* `make`

You'll now have kernel7.img
