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

#define IDT_TABLE_VECTOR_SIZE 256

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
    for (auto i = 0;i < IDT_TABLE_VECTOR_SIZE; ++i) {
        this->Setup(i, 0x8, 0x8E00, (u64_t)&IDT_Table::DefaultHandler);
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

IDT_Table idt_table;


class Kernel {
public:
    void Start();
    void Loop();
};

void Kernel::Start() {
    idt_table.Init();
    idt_table.Load();
}

void Kernel::Loop() {
    for (;;);
}

Kernel kernel;


void mm_init(void);


void kernel_main()
{
    kprintf("=============kernel_main============\n");
    kprintf("__code_start: %lx\n", __code_start);
    kprintf("_end: %lx\n", _end);

    kprintf("cr0: %lx, cr3:%lx, cr4: %lx\n", get_cr0(), get_cr3(), get_cr4());
    
    kprintf("initialize memery.\n");
    mm_init();
    

    kernel.Start();
    __asm__ __volatile__("int $0x0");
    kernel.Loop();
}


// memery init
#define PAGE_SIZE 0x1000
#define PDT_SIZE 512
uint64_t pml4e[PDT_SIZE] __ALIGNED(PAGE_SIZE);
uint64_t pdt[PDT_SIZE] __ALIGNED(PAGE_SIZE);
uint64_t pte[PDT_SIZE] __ALIGNED(PAGE_SIZE);

void mm_init() {

}

