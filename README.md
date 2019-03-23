# BareMetalTic80
Port of TIC80 to bare metal Raspberry Pi

This is a port of fantasy console [TIC-80](https://github.com/nesbox/TIC-80) to Raspberry-PI 2 in baremetal, that is, without operating system. It boots almost instantly. It is built on top of [circle](https://github.com/rsta2/circle) and [circle-stdlib](https://github.com/smuehlst/circle-stdlib).

This is an alpha release, things are pretty usable but there are limitations.

Store your carts in the "tic80" folder and boot up and voilà, you have the editor and everything :)

### TODO

* Fix input (keyboard glitches, gamepads)
* Fix file access code
* Use multicore mode for better performances

## Download

An already built version is available in [Releases](https://github.com/msx80/BareMetalTic80/releases).

Just unpack on the root of an appropriate SD card (fat32) and put it on a Raspberry PI 2 with a keyboard (optionally a mouse) connected.
This is the full TIC-80 release with the editor.

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
