CC = gcc
AS = as
LD = ld
CFLAGS :=  -mcmodel=large -m64 -c -o
ASFLAGS := --64 -o
LDFLAGS := -b elf64-x86-64 -o

TARGET = kernel.bin

objs = kernel.bin kernel.elf ../loader/loader.o 

.PHONY : everything clean all

everything : $(TARGET)

clean :
	rm -rf $(objs)

all : clean everything

../loader/loader.o : ../loader/loader.S
	$(CC) -E ../loader/loader.S > ../loader/loader.s
	$(CC) $(CFLAGS) $@ ../loader/loader.s

start.o : start.S
	$(CC) -E $@ $^
	$(AS) $(CFLAGS) $@ $^

kernel.elf : ../loader/loader.o 
	$(LD) $(LDFLAGS) $@ $^ -d kernel.lds

kernel.bin : kernel.elf
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel.elf kernel.bin

