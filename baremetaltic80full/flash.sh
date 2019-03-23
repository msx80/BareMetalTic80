#!/bin/sh
objcopy kernel7.elf -O ihex kernel7.hex
python flasher.py kernel7.hex /dev/ttyUSB0 921600

