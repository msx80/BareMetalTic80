#!/bin/sh
objcopy kernel.elf -O ihex kernel.hex
python flasher.py kernel.hex /dev/ttyUSB0 921600

