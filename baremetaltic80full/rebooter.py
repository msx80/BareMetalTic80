import serial
import sys
import time

try:
    fileaddress = ' '.join(sys.argv[1:2])
    flashport = ' '.join(sys.argv[2:3])
    flashbaud = int(' '.join(sys.argv[3:]))
except Exception:
    print("Usage: python flasher.py FILENAME SERIALPORT BAUDRATE")
    exit()

try:
    ser = serial.Serial(flashport,flashbaud
        #parity=serial.PARITY_NONE,
        #stopbits=serial.STOPBITS_ONE,
        #bytesize=serial.EIGHTBITS
    )
except Exception:
    print("ERROR: Serial Port " + flashport + " busy or inexistent!")
    exit()
    
try:
    ser.write(b"REBOOT")
    print("Rebooted!")
    sys.stdout.flush()
    time.sleep(1)
except Exception as e:
    print("ERROR: Serial port disconnected. Check connections!")
    print(e)
    ser.close()
    exit()

ser.close()
