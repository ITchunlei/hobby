#CC = gcc
#AS = as
#LD = ld

#CC = x86_64-linux-gnu-g++
#CXX = x86_64-linux-gnu-g++
#LD = x86_64-linux-gnu-ld

CFLAGS := -mcmodel=large -fno-stack-protector -fno-builtin -m64 -c
ASFLAGS := --64
LDFLAGS := -b elf64-x86-64 -z muldefs

TARGET = kernel.elf

objs = kernel.elf start.o idt.o main.o mem.o lib.o vsprintf.o i8259a.o thread.o

.PHONY : everything clean all

all : clean everything

everything : $(TARGET)

clean :
	rm -rf $(objs)

start.o : start.S
	$(CC) $(CFLAGS) -o $@ $^

# kmain.o : main.cpp
# 	$(CXX) $(CFLAGS) -o $@ $^

#interrupt.o : interrupt.S
#	$(CC) $(CFLAGS) -o $@ $^

#exception.o : exception.c
#	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

mem.o : mem.c
	$(CC) $(CFLAGS) -o $@ $^

# klib.o : lib.S
# 	$(CC) $(CFLAGS) -o $@ $^

lib.o : lib.c
	$(CC) $(CFLAGS) -o $@ $^

vsprintf.o : vsprintf.c
	$(CC) $(CFLAGS) -o $@ $^

i8259a.o : i8259a.c
	$(CC) $(CFLAGS) -o $@ $^

thread.o : thread.cpp
	$(CXX) $(CFLAGS) -o $@ $^

# proc.o : proc.c
# 	$(CC) $(CFLAGS) -o $@ $^

idt.o : idt.S
	$(CC) $(CFLAGS) -o $@ $^

kernel.elf : start.o idt.o main.o mem.o lib.o vsprintf.o i8259a.o thread.o
	$(LD) $(LDFLAGS) -o $@ $^ -T kernel.lds
