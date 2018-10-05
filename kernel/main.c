//
//  main.c
//  Hobby
//
//  Created by chunlei on 2018/10/3.
//  Copyright © 2018 los. All rights reserved.
//

#include "klib.h"

void myprint(char*);

void kernel_main()
{
    myprint("hello");
    for(;;);
}


void myprint(char* str) {
    char *pvideo = (char*)0xB8000;
    while(*str != '\0') {
        *pvideo++ = *str++;
        *pvideo++ = 0x04;
    }
}
