/*
 * Initialize i8259a
 * author: wangchunlei
 * date: 2014-1-31
 */
#include <cinix/types.h>
#include <arch/x86/io.h>

#define	I8259A_M_CTL	0x20
#define I8259A_M_CTLM	0X21
#define I8259A_S_CTL	0xa0
#define I8259A_S_CTLM	0xa1


#define IRQ0	0X20
#define IRQ1	0X21
#define IRQ2	0X22
#define IRQ3	0X23
#define IRQ4	0X24
#define IRQ5	0X25
#define IRQ6	0X26
#define IRQ7	0X27
#define IRQ8	0X28
#define IRQ9	0X29
#define IRQA	0X2a
#define IRQB	0X2b
#define IRQC	0X2c
#define IRQD	0X2d
#define IRQE	0X2e
#define IRQF	0X2f

/*
 * The function is used to initialize i8259a
 */
void init_i8259(void) {
	outb(0x11, I8259A_M_CTL);
	outb(0x11, I8259A_S_CTL);
	outb(0x20, I8259A_M_CTLM);				
	outb(0x28, I8259A_S_CTLM);				
	outb(0x4, I8259A_M_CTLM);				
	outb(0x2, I8259A_S_CTLM);				
	outb(0x1, I8259A_M_CTLM);				
	outb(0x1, I8259A_S_CTLM);				

	outb(0xfc, I8259A_M_CTLM); 
	outb(0xff, I8259A_S_CTLM);
}
