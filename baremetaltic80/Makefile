#
# Makefile
#

CIRCLEHOME = ../circle-stdlib/libs/circle
NEWLIBDIR = ../circle-stdlib/install/arm-none-circle
TIC80LIB = ../TIC-80/lib
OBJS	= main.o kernel.o customchargenerator.o customscreen.o

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../circle-stdlib/include -I ../TIC-80/include
LIBS := $(TIC80LIB)/libtic80core.a \
	$(TIC80LIB)/libgiflib.a \
	$(TIC80LIB)/liblpeg.a \
 	$(TIC80LIB)/liblua.a \
	$(TIC80LIB)/libsquirrel.a \
	$(TIC80LIB)/libwren.a \
	"$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/lib/fs/fat/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a \
	"$(NEWLIBDIR)/lib/libm.a"

