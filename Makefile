ARCH := $(shell uname -r)
ifeq '${ARCH}' 'Linux'
CC = gcc
CXX = g++
LD = ld
OBJCOPY = objcopy
else
CC = x86_64-linux-gnu-gcc
CXX = x86_64-linux-gnu-g++
LD = x86_64-linux-gnu-ld
OBJCOPY = x86_64-linux-gnu-objcopy
endif

export CC
export CXX
export LD
export OBJCOPY

objs = boot.bin loader.bin kernel.bin

.PHONY : debug kernel

all : clean boot.bin loader.bin kernel.bin install-boot install-loader install-kernel

kernel : kernel.bin  install-kernel
	ls -al kernel.bin
	rm -rf kernel.bin

boot.bin : bootloader/boot.o
	$(LD) --oformat binary -e _start -o $@ $^ -Ttext 0x7c00

bootloader/boot.o :
	(cd bootloader; make boot)

loader.bin : bootloader/loader.o
	$(LD) --oformat binary -e _start -o $@ $^ -Ttext 0x9100

bootloader/loader.o :
	(cd bootloader; make loader)

kernel.bin :
	(cd kernel; make)
	$(OBJCOPY) -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel/kernel.elf kernel.bin

install-boot :
	dd if=boot.bin of=debug/a.img bs=512 count=1 conv=notrunc

install-loader :
	dd if=loader.bin of=debug/a.img bs=512 seek=1 count=2

install-kernel : 
	dd if=kernel.bin of=debug/a.img bs=512 seek=3 count=40

debug : 
	(cd debug; bochs -f bochsrc)

clean : 
	(cd bootloader; make clean)
	(cd kernel; make clean)
	rm -rf $(objs)
