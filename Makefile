# Use `chcp 1251` to decode errors

NDK ?= android-ndk-r25c
NDK_PATH ?= $(HOME)/$(NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin

SRC = src/main.c \
	  src/image_formats/tga.c \
	  src/video/screen.c \
	  src/video/pixel.c \
	  src/video/backfb.c \
	  src/video/tga_image.c \

OBJS = $(SRC:.c=.o)
PROJECT = koraidon_firmware

RM ?= rm
CC = $(NDK_PATH)/armv7a-linux-androideabi26-clang
CFLAGS ?= -Iinclude -static -flto -O0 -Wall

PY ?= python3

# STATIC_C = $(NDK_PATH)/../sysroot/usr/lib/arm-linux-androideabi/libc.a

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) $(OBJS) -static -o $(PROJECT)
	$(PY) tools/fix_tls_alignment.py $(PROJECT)

$(OBJS): %.o : %.c
	$(CC) $? -c $(CFLAGS) -o $@

clean:
	-$(RM) $(PROJECT)
	-$(RM) $(OBJS)

setup_device:
	@echo "Now, turn your phone into recovery mode."
	@echo -n "Press any key to continue..."
	@bash -c read -sn1

	adb shell mount /dev/block/platform/*/by-name/system /system

push:
	@echo "Now, connect your phone in pseudo-recovery mode."
	@echo -n "Press any key to continue..."
	@bash -c read -sn1
	
	adb push $(PROJECT) /
	adb shell chmod +x /$(PROJECT)

run:
	adb shell /koraidon_firmware
