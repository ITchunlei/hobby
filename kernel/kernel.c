#include "types.h"
#include "i8259a.h"


extern tss_t tss;

extern void *gdtr;
extern void lgdt(void* gdtr);
extern desc_t gdt[6];

extern void cli();
extern void sti();
extern gate_t idt[256];
extern void kprint(char*);
extern void exception();


void divide_err();
void single_stepexception();
void nmi();
void breakpointexception();
void overflow();
void bounds_check();
void invalid_op();
void coprocessor_not_available();
void double_fault();
void coprocessor_seg_overrun();
void invalid_tss();
void seg_not_present();
void stackexception();
void general_protection();
void page_fault();
void coprocessor_err();

void timer_interrupt();

void do_timer_interrupt();

void do_exception();

void set_desc(desc_t*, u32_t, u32_t, u16_t);

void set_trap_gate(gate_t*, void*);

char* itoa(char*, int);

void set_gate(gate_t* gate, u16_t sel, void* offset, u16_t attr) {
    u32_t addr = (u32_t)offset;
    gate->offset_l = addr & 0xffff;
    gate->offset_h = (addr >> 16) & 0xffff;
    gate->sel = sel;
    gate->attr = attr;
}


void kernel_main(void)
{
    char buf[10];
    kprint("kernel...\n");
    kprint("tss.ss0: ");
    kprint(itoa(buf, (int)tss.ss0));
    kprint(" tss.esp0: ");
    kprint(itoa(buf, (int)tss.esp0));
    kprint(" tss.io_base: ");
    kprint(itoa(buf, (int)&timer_interrupt));
    
    tss.ss0 = 0x10;
    //tss.io_base = 0x68;
    
    set_desc(&gdt[0], 0, 0, 0);
    set_desc(&gdt[1], 0, 0xfffff, 0xc09a);
    set_desc(&gdt[2], 0, 0xfffff, 0xc092);
    set_desc(&gdt[3], 0, 0xfffff, 0xc0fa);
    set_desc(&gdt[4], 0, 0xfffff, 0xc0f2);
    set_desc(&gdt[5], (u32_t)&tss, 0x67, 0xc089);
    
    //lgdt((void*)gdtr);
    
    
    set_trap_gate(&idt[0], &divide_err);
    set_trap_gate(&idt[1], &single_stepexception);
    set_trap_gate(&idt[2], &nmi);
    set_trap_gate(&idt[3], &breakpointexception);
    set_trap_gate(&idt[4], &overflow);
    set_trap_gate(&idt[5], &bounds_check);
    set_trap_gate(&idt[6], &invalid_op);
    set_trap_gate(&idt[7], &coprocessor_not_available);
    set_trap_gate(&idt[8], &double_fault);
    set_trap_gate(&idt[9], &coprocessor_seg_overrun);
    set_trap_gate(&idt[10], &invalid_tss);
    set_trap_gate(&idt[11], &seg_not_present);
    set_trap_gate(&idt[12], &stackexception);
    set_trap_gate(&idt[13], &general_protection);
    set_trap_gate(&idt[14], &page_fault);
    set_trap_gate(&idt[15], &coprocessor_err);
    
    int i;
    for (i = 16; i< 256 ; ++i) {
        set_trap_gate(&idt[i], &timer_interrupt);
    }
    
    init_i8259a();
    sti();
}

int num = 0;

void do_timer_interrupt() {
    char buf[10];
    kprint("irq: ");
    kprint(itoa(buf, num++));
}

void do_exception(int vec_no, int error_code) {
    kprint("ex_handle: vec_no = ");
    char buf[100];
    kprint(itoa(buf, vec_no));
    kprint(" , error_code = ");
    kprint(itoa(buf, error_code));
    kprint("\n");
}

void set_desc(desc_t* desc, u32_t base, u32_t limit, u16_t attr)
{
    desc->base_l = base & 0xffff;
    desc->base_m = base > 16 & 0xff;
    desc->base_h = base > 24 & 0xff;
    desc->limit_l = limit & 0xffff;
    desc->attr_limit = attr | ((limit > 16 & 0xf) < 8);
}

void set_trap_gate(gate_t* gate, void* addr)
{
    set_gate(gate, 0x8, addr, 0x8e00);
}

