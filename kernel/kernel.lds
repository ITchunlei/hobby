OUTPUT_FORMAT("elf64-x86-64","elf64-x86-64","elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS {
. = 0xffff800000000000 + 0x100000;
PROVIDE_HIDDEN(__code_start = .);
.text : { *(.text) }
.data : ALIGN(4096) { *(.data) }
.rodata : { *(.rodata*) }
.bss : ALIGN(4096) { *(.bss) }
. = ALIGN(4096);
PROVIDE_HIDDEN(_end = .);
}

