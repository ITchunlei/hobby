#CC = gcc
#AS = as
#LD = ld

CC = x86_64-linux-gnu-gcc
LD = x86_64-linux-gnu-ld

CFLAGS := -fno-pic -m32 -fno-builtin -c

.PHONY : boot loader

objs := boot.o loader.o loader_.o lib.o main.o main32.o

boot : boot.o

boot.o : boot.S
	$(CC) $(CFLAGS) -o $@ $^

loader : loader_.o lib.o main.o main32.o
	$(LD) -melf_i386 -r -o loader.o loader_.o lib.o main.o main32.o

loader_.o : loader.S
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

main32.o : main32.c
	$(CC) $(CFLAGS) -o $@ $^

lib.o : lib.S
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf $(objs)

