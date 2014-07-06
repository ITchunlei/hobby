####################################################################
# makefile for kernel
# author: wangchunlei
# date: 2014-1-31
####################################################################

CC	= gcc
LD	= ld
CCFLAGS = -I /home/chunlei/Desktop/cinix/include/ -std=gnu99 -m32 -fno-builtin -c -o
LDFLAGS = -melf_i386 --oformat binary -e _start -N -Ttext 0x10100 -o

TARGET	= kernel.bin
objs	= kernel.bin main.o arch.o klib.o i8259.o \
		protect.o arch_init.o proc.o int.o

.PHONY : everything clean all

everything : $(TARGET)
clean : 
	rm -rf $(objs)
all : clean everything
kernel.bin : arch.o main.o klib.o i8259.o protect.o arch_init.o proc.o int.o

	$(LD) $(LDFLAGS) $@ $^
main.o : kernel/main.c
	$(CC) $(CCFLAGS) $@ $^
arch.o : kernel/arch/x86/arch.S
	$(CC) $(CCFLAGS) $@ $^
klib.o : kernel/arch/x86/klib.S
	$(CC) $(CCFLAGS) $@ $^
i8259.o : kernel/arch/x86/i8259.c
	$(CC) $(CCFLAGS) $@ $^
protect.o : kernel/arch/x86/protect.c
	$(CC) $(CCFLAGS) $@ $^
arch_init.o : kernel/arch/x86/arch_init.c
	$(CC) $(CCFLAGS) $@ $^
proc.o : kernel/proc.c
	$(CC) $(CCFLAGS) $@ $^
int.o : kernel/arch/x86/int.c
	$(CC) $(CCFLAGS) $@ $^
