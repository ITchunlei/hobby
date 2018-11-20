//
//  main.c
//  Hobby
//
//  Created by chunlei on 2018/10/3.
//  Copyright © 2018 los. All rights reserved.
//

#include "main.h"
#include "lib.h"
#include "i8259a.h"
#include "exception.h"
#include "types.h"

#define IDT_ATTR(P, DPL, TYPE, IST)

void timer_interrupt();

void user_mode();

void l3_mode() {
    for(;;) {
    	kprintf(".um");
        int i;
        for(i = 0;i < 1000000; ++i);
    }
}


void start_kernel()
{
    close_irq();
    
    kprintf("start_kernel\n");

    kernel_main();
    
/*
    gate_t* idt = (gate_t*)0x100000;
    
    
    kprintf("init exception handlers\n");
    exception_init(idt);
    
    
    kprintf("init interrupt handlers\n");
    int i;
    for (i = 32;i < 256; ++i) {
        u64_t addr = (u64_t)timer_interrupt;
        idt[i].sel = 0x8;
        idt[i].attr = 0x8E00;
        idt[i].offset_1 = addr & 0xFFFF;
        idt[i].offset_2 = addr >> 16 & 0xFFFF;
        idt[i].offset_3 = addr >> 32 & 0xFFFFFFFF;
        idt[i].reserved = 0x0;
    }
    
    idt_p_t idt_ptr;
    idt_ptr.limit = 16 * 256 - 1;
    idt_ptr.base = (u64_t)idt;
    
    load_idt(idt_ptr);
    */
    //kprintf("init i8259a\n");
    //init_i8259a();
    
    //open_irq();
    
    //__asm__ __volatile__("int $0");
    
    
    //user_mode();
        
    for(;;);
}
