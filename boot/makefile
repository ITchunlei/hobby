##########################################################################
# makefile for boot
# author: wangchunlei
# date: 2013-12-22
##########################################################################

ASM	= as
CC	= gcc
LD	= ld
CCFLAGS = -std=gnu99 -m32 -fno-builtin -c -o
LDFLAGS = -melf_i386 --oformat binary -e _start -N -Ttext 0x100 -o

TARGET	= loader.bin
objs	= loader.bin boot.o lib.o boot_main.o
.PHONY : everything clean all

everything : $(TARGET)
clean : 
	rm  -rf $(objs)
all : clean everything
loader.bin : boot.o boot_main.o  lib.o
	$(LD) $(LDFLAGS) $@  $^
boot_main.o : boot/boot_main.c
	$(CC) $(CCFLAGS) $@  $^
boot.o : boot/asm/x86/boot.S
	$(CC) $(CCFLAGS) $@ $^
lib.o : boot/asm/x86/lib.S
	$(CC) $(CCFLAGS) $@ $^
