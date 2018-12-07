//
//  main.c
//  Hobby
//
//  Created by chunlei on 2018/10/3.
//  Copyright © 2018 los. All rights reserved.
//

#include "macros.h"
#include "lib.h"
#include "i8259a.h"
#include "exception.h"
#include "types.h"
#include "reg.h"
#include "mem.h"

// memery init

#define PML4E_SHIFT 39
#define PDE_SHIFT 30
#define PTE_SHIFT 21
#define PAGE_SHIFT 12

#define PAGE_SIZE (1UL << PAGE_SHIFT)

typedef uint64_t pml4e_t;
typedef uint64_t pde_t;
typedef uint64_t pte_t;

pml4e_t pml4e[512] __ALIGNED(PAGE_SIZE);
pde_t pde[512] __ALIGNED(PAGE_SIZE);
pte_t pte[512] __ALIGNED(PAGE_SIZE);






/* irq & trap */

#define IDT_SIZE 256

#define TR_SEL 0x48

#define UC_SEL 0x28 + 0x3
#define UD_SEL 0x30 + 0x3

typedef struct {
    uint32_t reserved0;
    uint64_t rsp0, rsp1, rsp2; 
    uint64_t reserved1;
    uint64_t ist0, ist1, ist2, ist3, ist4, ist5, ist6;
    uint64_t reserved2;
    uint32_t io_map;
} __PACKED tss_t;

typedef struct tss_desc {
    uint16_t limit;
    uint16_t base1;
    uint8_t base2;
    uint16_t attr;
    uint8_t base3;
    uint32_t base4;
    uint32_t reserved;
} __PACKED tss_desc_t;

static inline void load_tr(uint16_t sel) {
    __asm__ __volatile__("ltr %%ax"::"a"(sel));
}

void tss_desc_setup(tss_t* tss, uint16_t size);

void tss_init(tss_t* tss);

tss_t tss_table[1];

void tss_desc_setup(tss_t* tss, uint16_t size) {
    extern tss_desc_t tss_desc_table[];
    for (int i = 0;i < size; ++i) {
        tss_desc_t *t = &(tss_desc_table[i]);
        uint64_t base = (uint64_t)tss;
        kprintf("tss_desc_t: %lx, base: %lx", t, base);
        t->limit = sizeof(tss_t);
        t->base1 = base & 0xffff;
        t->base2 = base >> 16 & 0xff;
        //t->attr = 0x8089;
        t->base3 = base >> 24 & 0xff;
        t->base4 = base >> 32 & 0xffffffff;
        t->reserved = 0x0;
    }
}

void tss_init(tss_t* tss) {
    tss->rsp0 = 0x0;
    tss->ist0 = 0x0;
    tss->ist1 = 0x0;
    tss->ist2 = 0x0;
    tss->ist3 = 0x0;
    tss->ist4 = 0x0;
    tss->ist5 = 0x0;
    tss->ist6 = 0x0;
    tss->io_map = 0x0;
}

struct context {
    uint64_t gs, fs, es, ds;
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbx, rdx, rcx, rax;
    uint64_t vec_no, error_code;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
};

typedef struct context context_t;

struct idt_struct {
    uint16_t offset_1;
    uint16_t sel;
    uint16_t attr;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t reserved;
} __PACKED;

struct idtr {
    u16_t limit;
    u64_t base;
} __PACKED;

typedef struct idt_struct idt_t;

typedef struct idtr idtr_t;

void idt_init();

void idt_setup();

void idt_load();

void do_interrupt();

idt_t idt_table[IDT_SIZE];

void idt_init() {
    extern uintptr_t _interrupt_table[];
    int i;
    for (i = 0;i < IDT_SIZE; ++i) {
        if (i < 0x20) {
            idt_setup(&idt_table[i], 0x8, 0x8E00, _interrupt_table[i]);
        } else {
            idt_setup(&idt_table[i], 0x8, 0x8E00, _interrupt_table[i]);
        }
    }

    idt_load();
}

void idt_setup(idt_t* idt, uint32_t sel, uint32_t attr, uint64_t offset) {
    idt->sel = sel;
    idt->attr = attr;
    idt->offset_1 = offset & 0xFFFF;
    idt->offset_2 = offset >> 16 & 0xFFFF;
    idt->offset_3 = offset >> 32 & 0xFFFFFFFF;
    idt->reserved = 0x0;
}

void idt_load() {
    idtr_t table_ptr = {
        .limit = sizeof(idt_t) * IDT_SIZE - 1,
        .base = (u64_t)idt_table
    };
    __asm__ __volatile__("lidt %0" : : "m" (table_ptr));
}

void do_interrupt(context_t* ctx) {
    if (ctx->vec_no < 0x20) {
        kprintf("do_interrupt vec_no:%lx\n", ctx->vec_no);
        kprintf("do_interrupt error_code:%lx\n", ctx->error_code);
        kprintf("do_interrupt rip:%lx\n", ctx->rip);
        __asm__ __volatile__("hlt\n\t");
    }

    if (ctx->vec_no == 0x20) {
         kprintf("#T#");
         __asm__ __volatile__("mov $0x20, %al");
         __asm__ __volatile__("out %al, $0x20\n\t");
    }
}


/* thread */
typedef struct {
    context_t context;
    uintptr_t entry;
    char ustack[1024];
} thread_t;


void thread_create(thread_t* thread, uint64_t entry) {
    thread->entry = entry;

    context_t* ctx = &thread->context;

    ctx->gs = UD_SEL;
    ctx->fs = UD_SEL;
    ctx->es = 0;
    ctx->ds = 0;
    ctx->vec_no = 0x20;
    ctx->error_code = 0;
    ctx->rip = thread->entry;
    ctx->cs = UC_SEL;
    ctx->rflags = 0x1202;
    ctx->rsp = (uintptr_t)thread->ustack;
    ctx->ss = UD_SEL;
}

#define NR_THREAD 10

thread_t thread_table[NR_THREAD];

void restore_context(context_t *context);

void init();

void kmain()
{
    close_irq();
    
    idt_init();

    mem_init();

    init_i8259a();

    tss_desc_setup(tss_table, 1);

    tss_init(tss_table);

    load_tr(TR_SEL);

    thread_t *thread = &thread_table[0];

    thread_create(thread, (uintptr_t)&init);

    tss_t* tss = &(tss_table[0]);
    tss->rsp0 = (uintptr_t)(&thread->context) - sizeof(context_t);

    restore_context(&thread->context);
    for(;;);
}

void init() {
    kprintf("init.\n");
    for(;;);
}
