CC = gcc
AS = as
LD = ld

CFLAGS := -c

.PHONY : boot loader

objs := boot.o loader.o

boot : boot.o

boot.o : boot.S
	$(CC) $(CFLAGS) -o $@ $^

loader : loader_.o lib.o
	$(LD) -r -o loader.o loader_.o lib.o

loader_.o : loader.S
	$(CC) $(CFLAGS) -o $@ $^

lib.o : lib.S
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf $(objs)

