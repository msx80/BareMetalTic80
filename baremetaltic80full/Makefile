#
# Makefile
#

CIRCLEHOME = ../circle-stdlib/libs/circle
NEWLIBDIR = ../circle-stdlib/install/arm-none-circle
TIC80LIB = ../TIC-80/lib
TIC80SRC = ../TIC-80/src
TIC803RD = ../TIC-80/3rd-party

OBJS	= \
	main.o kernel.o customchargenerator.o customscreen.o utils.o \
        ${TIC80SRC}/studio.o \
        ${TIC80SRC}/console.o \
        ${TIC80SRC}/run.o \
        ${TIC80SRC}/ext/md5.o \
        ${TIC80SRC}/ext/gif.o \
        ${TIC80SRC}/fs.o \
        ${TIC80SRC}/tools.o \
        ${TIC80SRC}/start.o \
        ${TIC80SRC}/sprite.o \
        ${TIC80SRC}/map.o \
        ${TIC80SRC}/sfx.o \
        ${TIC80SRC}/music.o \
        ${TIC80SRC}/history.o \
        ${TIC80SRC}/world.o \
        ${TIC80SRC}/config.o \
        ${TIC80SRC}/code.o \
        ${TIC80SRC}/dialog.o \
        ${TIC80SRC}/menu.o \
        ${TIC80SRC}/surf.o 

#../TIC-80/src/studio.o

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../circle-stdlib/include -I ../TIC-80/include -I ../TIC-80/src \
	  -I ${TIC803RD}/giflib-5.1.4/lib -I ${TIC803RD}/zlib-1.2.11 -I ${TIC803RD}/lua-5.3.1/src \
	  -D BAREMETAL


LIBS :=  \
	$(TIC80LIB)/libtic80core.a \
	$(TIC80LIB)/libgiflib.a \
	$(TIC80LIB)/liblpeg.a \
 	$(TIC80LIB)/liblua.a \
	$(TIC80LIB)/libwren.a \
	$(TIC80LIB)/libzlib.a \
	"$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
 	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/lib/fs/fat/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a \
	"$(NEWLIBDIR)/lib/libm.a"

