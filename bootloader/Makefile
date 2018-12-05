# CC = gcc
# AS = as
# LD = ld

CC = x86_64-linux-gnu-gcc
LD = x86_64-linux-gnu-ld

CFLAGS := -fno-pic -fno-builtin -c

.PHONY : boot loader

objs := boot.o loader.o loader_.o lib.o main.o

boot : boot.o

boot.o : boot.S
	$(CC) $(CFLAGS) -o $@ $^

loader : loader_.o lib.o main.o
	$(LD) -r -o loader.o loader_.o lib.o main.o

loader_.o : loader.S
	$(CC) $(CFLAGS) -o $@ $^

lib.o : lib.S
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^	

clean :
	rm -rf $(objs)

