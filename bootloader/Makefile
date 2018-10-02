CC = gcc
AS = as
LD = ld

objs := boot.o loader.o

boot.o : boot.S
	$(CC) -c -o $@ $^

loader.o : loader.S
	$(CC) -E loader.S > loader.s
	$(AS) -o $@ $^

clean :
	rm -rf $(objs)

