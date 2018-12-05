//
//  main.cpp
//  Hobby
//
//  Created by chunlei on 2018/11/11.
//  Copyright © 2018 los. All rights reserved.
//

#include "types.h"
#include "reg.h"
#include "lib.h"
#include "main.h"

extern char __code_start[];
extern char _end[];

// ======================= idt ====================
#define IDT_TABLE_VECTOR_SIZE 256

#define UC_SEL 0x28 + 0x3
#define UD_SEL 0x30 + 0x3

struct TSS {
    uint32_t reserved0;
    uint64_t rsp0, rsp1, rsp2; 
    uint64_t reserved1;
    uint64_t ist0, ist1, ist2, ist3, ist4, ist5, ist6;
    uint64_t reserved2;
    uint32_t io_map;
} __PACKED;

typedef TSS tss_t;

struct TSS_Desc {
    uint16_t limit;
    uint16_t base1;
    uint8_t base2;
    uint16_t attr;
    uint8_t base3;
    uint32_t base4;
    uint32_t reserved;
} __PACKED;

typedef TSS_Desc tss_desc_t;

static void ltr(uint16_t sel) {
    __asm__ __volatile__("ltr %%ax"::"a"(sel));
}


void setup_tss_desc(tss_t* tss, uint16_t size) {
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

tss_t tss_table[1];


struct Context {
    uint64_t gs, fs, es, ds;
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbx, rdx, rcx, rax;
    uint64_t vec_no, error_code;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
};

typedef Context context_t;

struct Thread {
    context_t context;
    uintptr_t entry;
    char ustack[1024];
};

typedef Thread thread_t;

void thread_create(thread_t* thread, uintptr_t entry) {
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

extern "C" {
    void do_interrupt(context_t* ctx);
    void restore_context(context_t *context);
}

class IDT_Table {
public:
    void Init();
    void Setup(int vector_idx, int sel, u16_t attr, u64_t offset);
    void Load();
private:
    struct {
        u16_t offset_1;
        u16_t sel;
        u16_t attr;
        u16_t offset_2;
        u32_t offset_3;
        u32_t reserved;
    } __PACKED vector[IDT_TABLE_VECTOR_SIZE];
    
    struct Ptr {
        u16_t limit;
        u64_t base;
    } __PACKED;

    static void DefaultHandler();
};

void IDT_Table::Init() {
    extern uintptr_t _interrupt_table[];
    for (auto i = 0;i < IDT_TABLE_VECTOR_SIZE; ++i) {
        //this->Setup(i, 0x8, 0x8E00, (u64_t)&IDT_Table::DefaultHandler);
        if (i < 0x20) {
            this->Setup(i, 0x8, 0x8F00, _interrupt_table[i]);
        } else {
            this->Setup(i, 0x8, 0x8E00, _interrupt_table[i]);
        }
    }
}

void IDT_Table::Setup(int index, int selector, u16_t attr, u64_t offset) {
    this->vector[index].sel = selector;
    this->vector[index].attr = attr;
    this->vector[index].offset_1 = offset & 0xFFFF;
    this->vector[index].offset_2 = offset >> 16 & 0xFFFF;
    this->vector[index].offset_3 = offset >> 32 & 0xFFFFFFFF;
    this->vector[index].reserved = 0x0;
}

void IDT_Table::Load() {
    IDT_Table::Ptr table_ptr = {
        .limit = sizeof(*this->vector) * IDT_TABLE_VECTOR_SIZE - 1,
        .base = (u64_t)this->vector
    };
    __asm__ __volatile__("lidt %0" : : "m" (table_ptr));
}

void IDT_Table::DefaultHandler() {
    kprintf("DefaultHandler\n");
}


void do_interrupt(context_t* ctx) {
    kprintf("do_interrupt vec_no:%lx\n", ctx->vec_no);
    kprintf("do_interrupt error_code:%lx\n", ctx->error_code);
    kprintf("do_interrupt rip:%lx\n", ctx->rip);

    if (ctx->vec_no < 0x20) {
        __asm__ __volatile__("hlt\n\t");
    }

    if (ctx->vec_no == 0x20) {

        // thread_t *current = &thread_table[0];

         kprintf("#T#");
         __asm__ __volatile__("mov $0x20, %al");
         __asm__ __volatile__("out %al, $0x20\n\t");
    }
}

IDT_Table idt_table;

// ========================= idt end ==========================

extern "C" {

void apic_test();

void test() {
    for (int i = 0;i < 10000;i ++) {
        for (int j = 0;j < 100000;j ++) {}
        kprintf("#u#");
    }
}
}

class Kernel {
public:
    void Start();
    void Loop();
};

void Kernel::Start() {


    idt_table.Init();
    idt_table.Load();

    setup_tss_desc(tss_table, 1);

    tss_init(tss_table);

    ltr(0x48);

    thread_t *thread = &thread_table[0];

    thread_create(thread, (uintptr_t)&test);

    kprintf("init rip: %lx\n", (uintptr_t)&test);
    kprintf("thread->context: %lx\n", &thread->context);

    tss_t* tss = &(tss_table[0]);
    tss->rsp0 = (uintptr_t)(&thread->context) - sizeof(context_t);

    //restore_context(&thread->context);

}

void Kernel::Loop() {
    for (;;);
}

Kernel kernel;


void kernel_main()
{
    kprintf("=============kernel_main============\n");
    kprintf("__code_start: %lx\n", __code_start);
    kprintf("_end: %lx\n", _end);

    kprintf("cr0: %lx, cr3:%lx, cr4: %lx\n", get_cr0(), get_cr3(), get_cr4());
    
    kernel.Start();


//apic_test();

    //kernel.Loop();
}


