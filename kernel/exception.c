//
//  exception.c
//  Hobby
//
//  Created by chunlei on 2018/10/5.
//  Copyright © 2018 los. All rights reserved.
//

#include "lib.h"
#include "types.h"
#include "exception.h"

void do_timer_interrup()
{
    print_str("\n\ndo_timer_interrupt!!!\n");
}

void divide_error();
void debug_exception();
void nmi_interrupt();
void breakpoint();
void overflow();
void bound_range_exceeded();
void invalid_opcode();
void device_not_available();
void double_fault();
void coprocessor_segment_overrun();
void invalid_tss();
void segment_not_present();
void stack_segment_fault();
void general_protection();
void page_fault();
void x87_fpu_floating_poing_error();
void alignment_check();
void machine_check();
void simd_floating_point_exception();
void virtualization_exception();


static void set_exception_gate(gate_t*, void*);

void exception_init(gate_t* idt)
{
    set_exception_gate(&idt[0], divide_error);
    set_exception_gate(&idt[1], debug_exception);
    set_exception_gate(&idt[2], nmi_interrupt);
    set_exception_gate(&idt[3], breakpoint);
    set_exception_gate(&idt[4], overflow);
    set_exception_gate(&idt[5], bound_range_exceeded);
    set_exception_gate(&idt[6], invalid_opcode);
    set_exception_gate(&idt[7], device_not_available);
    set_exception_gate(&idt[8], double_fault);
    set_exception_gate(&idt[9], coprocessor_segment_overrun);
    set_exception_gate(&idt[10], invalid_tss);
    set_exception_gate(&idt[11], segment_not_present);
    set_exception_gate(&idt[12], stack_segment_fault);
    set_exception_gate(&idt[13], general_protection);
    set_exception_gate(&idt[15], page_fault);
    set_exception_gate(&idt[15], x87_fpu_floating_poing_error);
    set_exception_gate(&idt[16], alignment_check);
    set_exception_gate(&idt[17], machine_check);
    set_exception_gate(&idt[18], simd_floating_point_exception);
    set_exception_gate(&idt[19], virtualization_exception);
}

void do_exception(int vec_no, int err_code, int rip, int cs, int rflags)
{
    char buf[20];
    print_str("vec_no:");
    print_str(itoa(buf, vec_no));
    print_str(" err_code:");
    print_str(itoa(buf, err_code));
    print_str(" rip:");
    print_str(itoa(buf, rip));
    print_str(" cs:");
    print_str(itoa(buf, cs));
    print_str(" rflags:");
    print_str(itoa(buf, rflags));
    print_str("\n");
}

void set_exception_gate(gate_t* idt, void* handler)
{
    u64_t addr = (u64_t)handler;
    idt->sel = 0x8;
    idt->attr = 0x8F00;
    idt->offset_1 = addr & 0xFFFF;
    idt->offset_2 = addr >> 16 & 0xFFFF;
    idt->offset_3 = addr >> 32 & 0xFFFFFFFF;
    idt->reserved = 0x0;
}
