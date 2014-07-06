#!/bin/sh
echo 'test shell!'
sudo mount /home/chunlei/Desktop/a.img /mnt/floppy
sudo rm /mnt/floppy/loader.bin
sudo cp /home/chunlei/Desktop/cinix/boot/loader.bin /mnt/floppy
sudo umount -l /mnt/floppy
sudo bochs -f /home/chunlei/Desktop/bochsrc
