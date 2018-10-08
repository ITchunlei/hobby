//
//  i8259a.c
//  Hobby
//
//  Created by chunlei on 2018/9/19.
//  Copyright © 2018年 los. All rights reserved.
//

#include "lib.h"
#include "i8259a.h"

#define I8259A_M_CTL    0x20
#define I8259A_M_CTLM   0X21
#define I8259A_S_CTL    0xa0
#define I8259A_S_CTLM   0xa1

#define ICW1 0x11
#define ICW2 0x20

void init_i8259a()
{
    out_byte(I8259A_M_CTL, 0x11);
    out_byte(I8259A_S_CTL, 0x11);
    out_byte(I8259A_M_CTLM, 0x20);
    out_byte(I8259A_S_CTLM, 0x28);
    out_byte(I8259A_M_CTLM, 0x4);
    out_byte(I8259A_S_CTLM, 0x2);
    out_byte(I8259A_M_CTLM, 0x1);
    out_byte(I8259A_S_CTLM, 0x1);
    
    out_byte(I8259A_M_CTLM, 0xff);
    out_byte(I8259A_S_CTLM, 0xff);
}
