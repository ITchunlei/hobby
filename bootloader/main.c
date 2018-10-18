//
//  main.c
//  Hobby
//
//  Created by chunlei on 2018/10/16.
//  Copyright © 2018 los. All rights reserved.
//

__asm__(".code16gcc");

#include "lib.h"

void l_main()
{
    enable_A20();
    enable_PE();
}
