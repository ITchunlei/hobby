CC = gcc
AS = as
LD = ld

objs = boot.bin

boot.bin : bootloader/boot.o
	(cd bootloader; make)
	$(LD) -melf_x86_64 --oformat binary -e _start -o $@ $^ -Ttext 0x7c00

install-boot :
	dd if=boot.bin of=debug/a.img bs=512 count=1 conv=notrunc

install-loader :
	dd if=loader.bin of=debug/a.img bs=512 seek=1 count=2

install-kernel : 
	dd if=kernel.bin of=debug/a.img bs=512 seek =3 count=10

clean : 
	(cd bootloader; make clean)
	rm -rf $(objs)
