CC = gcc
AS = as
LD = ld

objs = boot.bin loader.bin kernel.bin

.PHONY : debug

all : clean boot.bin loader.bin kernel.bin install-boot install-loader install-kernel

boot.bin : bootloader/boot.o
	$(LD) -melf_x86_64 --oformat binary -e _start -o $@ $^ -Ttext 0x7c00

bootloader/boot.o :
	(cd bootloader; make boot)

loader.bin : bootloader/loader.o
	$(LD) -melf_x86_64 --oformat binary -e _start -o $@ $^ -Ttext 0x9100

bootloader/loader.o :
	(cd bootloader; make loader)

kernel/kernel.elf :
	(cd kernel; make)

kernel.bin : kernel/kernel.elf
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary kernel/kernel.elf kernel.bin

install-boot :
	dd if=boot.bin of=debug/a.img bs=512 count=1 conv=notrunc

install-loader :
	dd if=loader.bin of=debug/a.img bs=512 seek=1 count=2

install-kernel : 
	dd if=kernel.bin of=debug/a.img bs=512 seek=3 count=6

debug : 
	(cd debug; bochs -f bochsrc)

clean : 
	(cd bootloader; make clean)
	(cd kernel; make clean)
	rm -rf $(objs)
