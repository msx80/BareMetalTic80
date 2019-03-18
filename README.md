# BareMetalTic80
Port of TIC80 to bare metal Raspberry Pi

This is a port of fantasy console [TIC-80](https://github.com/nesbox/TIC-80) to Raspberry-PI 2 in baremetal, that is, without operating system. It boots almost instantly. It is built on top of [circle](https://github.com/rsta2/circle) and [circle-stdlib](https://github.com/smuehlst/circle-stdlib).

This is a preview proof of concept, only basic input is implemented (z, x and cursors), no audio, probably broken colors, etc. But shows it can be done!

It runs any "cart.tic" on SD card.

### TODO

* Fix input (mouse and keyboard)
* Run full TIC-80 studio (the editor etc)
* Implement audio

## Download

An already built version is available [here](https://drive.google.com/file/d/1kck1odAhhJPL2Zs7zP8cYOfv2Ap05nV4/view?usp=sharing).

Just unpack on the root of an appropriate SD card (fat32) and put it on a Raspberry PI 2 with a keyboard connected.
This is just the player, it can run any cart.tic but doesn't have the full editor. I'm still working on it.

## Want to help?

* If you tryed the program, let me know if and how it worked! Either here, on twitter @msx80 or on TIC-80 discord.
* Are you good with cmake and building script? Review the mess i put together!

## How to build

The build is rapidly evolving, feel free to ask if it doesn't work

The build works on a regular x86 linux. Following these steps should work. Feedback welcome :)

* Download [gcc arm toolkit](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) (i used version gcc-arm-none-eabi-8-2018-q4-major) and expand on your disk and add it to your path:
* `PATH=/home/xxxx/gcc-arm-none-eabi-8-2018-q4-major/bin/:$PATH`
* clone the repository and modules
* `git clone --recursive https://github.com/msx80/BareMetalTic80.git`
* `cd BareMetalTic80`
* Build circle-stdlib runtime:
* `cd circle-stdlib`
* `./configure --raspberrypi 2`
* `make`
* `cd ..`
* Build TIC-80 core:
* `cd TIC-80`
* `cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DBAREMETAL=1 -DCMAKE_TOOLCHAIN_FILE=../arm-gcc-toolchain.cmake .`
* `make tic80core`
* `cd ..`
* Now on to build the "kernel":
* `cd baremetaltic80player`
* `make`

You'll now have kernel7.img
