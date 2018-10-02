CC = gcc
LD = ld
CFLAGS = -c -o
LDFLAGS = -melf_x86_64 --oformat binary -e _start -o 

TARGET = boot.bin
objs = boot.bin boot.o

.PHONY : everything clean all

everything : $(TARGET)

install :
	dd if=boot.bin of=a.img bs=512 count=1 conv=notrunc
	dd if=kernel/kernel.bin of=a.img bs=512 seek=1 count=10

clean : 
	rm -rf $(objs)

all : clean everything

boot.bin : boot.o
	$(LD) $(LDFLAGS) $@ $^ -Ttext 0x7c00

boot.o : boot.S
	$(CC) $(CFLAGS) $@ $^

