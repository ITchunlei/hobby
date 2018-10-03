OUTPUT_FORMAT("elf64-x86-64","elf64-x86-64","elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS {
. = 0x1100;
. = ALIGN(8);
.text : { *(.text) }
.data : { *(.data) }
.bss : { *(.bss) }
}

