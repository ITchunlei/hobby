CC = gcc
AS = as
LD = ld
CFLAGS :=  -mcmodel=large -m64 -c
ASFLAGS := --64
LDFLAGS := -b elf64-x86-64

TARGET = kernel.elf

objs = kernel.elf start.o kmain.o klib.o

.PHONY : everything clean all

everything : $(TARGET)

clean :
	rm -rf $(objs)

all : clean everything

start.o : start.S
	$(CC) $(CFLAGS) -o $@ $^

kmain.o : kmain.c
	$(CC) $(CFLAGS) -o $@ $^

klib.o : klib.S
	$(CC) $(CFLAGS) -o $@ $^

kernel.elf : start.o kmain.o klib.o
	$(LD) $(LDFLAGS) -o $@ $^ -T kernel.lds
