CC = gcc
AS = as
LD = ld

CFLAGS := -mcmodel=large -fno-stack-protector -fno-builtin -m64 -c
ASFLAGS := --64
LDFLAGS := -b elf64-x86-64

TARGET = kernel.elf

objs = kernel.elf startup.o interrupt.o exception.o main.o klib.o lib.o i8259a.o

.PHONY : everything clean all

all : clean everything

everything : $(TARGET)

clean :
	rm -rf $(objs)

startup.o : startup.S
	$(CC) $(CFLAGS) -o $@ $^

interrupt.o : interrupt.S
	$(CC) $(CFLAGS) -o $@ $^

exception.o : exception.c
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

klib.o : lib.S
	$(CC) $(CFLAGS) -o $@ $^

lib.o : lib.c
	$(CC) $(CFLAGS) -o $@ $^

i8259a.o : i8259a.c
	$(CC) $(CFLAGS) -o $@ $^

kernel.elf : startup.o interrupt.o exception.o main.o klib.o lib.o i8259a.o
	$(LD) $(LDFLAGS) -o $@ $^ -T kernel.lds
