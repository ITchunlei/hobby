OUTPUT_FORMAT("elf64-x86-64","elf64-x86-64","elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS {
. = 0xffff800000000000 + 0x1100;
PROVIDE_HIDDEN(__code_start = .);
.text : { *(.text) }
. = ALIGN(8);
.data : { *(.data) }
.rodata : { *(.rodata) }
.bss : { *(.bss) }
PROVIDE_HIDDEN(_end = .);
}

