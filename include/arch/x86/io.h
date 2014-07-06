#ifndef	__IO_H__
#define __IO_H__

#include <cinix/types.h>
static void io_delay() {
	asm volatile("jmp 1f;\t1:\tjmp 1f;\t1:\n\t");
}

static inline void outb(u8_t value, u16_t port) {
	asm volatile("outb %%al, %%dx"::"a" (value), "d" (port));
}

static inline u8_t inb(u16_t port) {
	u8_t value;
	asm volatile("inb %1, %0\n\t":"=a"(value):"d"(port));
	return value;	
}


#endif /* __IO_H__ */
