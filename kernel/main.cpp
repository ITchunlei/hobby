//
//  main.cpp
//  Hobby
//
//  Created by chunlei on 2018/11/11.
//  Copyright © 2018 los. All rights reserved.
//

#include "types.h"
#include "lib.h"
#include "main.h"

extern char __code_start[];
extern char _end[];

#define IDT_VECTOR_SIZE 256

class IDT_Table {
public:
    void Init();
    void Init(int index, int selector);
    void Load();
private:
    struct {
        u16_t offset_1;
        u16_t sel;
        u16_t attr;
        u16_t offset_2;
        u32_t offset_3;
        u32_t reserved;
    } __PACKED vector[IDT_VECTOR_SIZE];
    
    struct Ptr {
        u16_t limit;
        u64_t base;
    } __PACKED;
};

void IDT_Table::Init() {
    this->vector[0].offset_1 = 0x1;
    this->vector[0].offset_2 = 0x2;
    this->vector[0].offset_3 = 0x3;
}

void IDT_Table::Init(int index, int selector) {
    
}

void IDT_Table::Load() {
    IDT_Table::Ptr table_ptr = {
        .limit = sizeof(*this->vector) * IDT_VECTOR_SIZE - 1,
        .base = (u64_t)this->vector
    };
    __asm__ __volatile__("lidt %0" : : "m" (table_ptr));
}

IDT_Table idt;

void kernel_main()
{
    
    kprintf("=============kernel_main============\n");
    kprintf("__code_start: %x\n", __code_start);
    kprintf("_end: %x", _end);
    
    idt.Init();
    idt.Load();
    for(;;);
}

