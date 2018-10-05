CC = gcc
AS = as
LD = ld
CFLAGS := -mcmodel=large -m64 -c
ASFLAGS := --64
LDFLAGS := -b elf64-x86-64

TARGET = kernel.elf

objs = kernel.elf start.o main.o klib.o

.PHONY : everything clean all

all : clean everything

everything : $(TARGET)

clean :
	rm -rf $(objs)

start.o : start.S
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

klib.o : klib.S
	$(CC) $(CFLAGS) -o $@ $^

kernel.elf : start.o main.o klib.o
	$(LD) $(LDFLAGS) -o $@ $^ -T kernel.lds
