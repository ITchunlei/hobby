objs := boot.o loader.o

boot.o : boot.S
	$(CC) -c -o $@ $^

clean :
	rm -rf $(objs)

