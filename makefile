#####################################################################
# makefile for cinix
# author: wangchunlei
# date: 2014-1-30
#####################################################################

.PHONY : everything clean all install
everything :
	make -f ./boot/makefile		
	make -f ./kernel/makefile
clean : 
	cd ./boot  \
	make clean \
	cd ..	   \
	cd ./kernel \
	make clean \
	cd .. 

all : clean everything


install : 
	sudo mount /home/chunlei/Desktop/a.img /mnt/floppy
#	sudo rm /mnt/floppy/loader.bin
#	souo rm /mnt/floppy/kernel.bin
	sudo cp ./loader.bin /mnt/floppy
	sudo cp ./kernel.bin /mnt/floppy
	sudo umount -l /mnt/floppy
	sudo bochs -f /home/chunlei/Desktop/bochsrc

