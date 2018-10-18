//
//  libs.h
//  Hobby
//
//  Created by chunlei on 2018/10/5.
//  Copyright © 2018 los. All rights reserved.
//

#include <stdarg.h>
#include "lib.h"

static int position = 0;

static char buf[1024] = {0};

char* itoa(char* str, int num)
{
    char *p = str;
    char ch;
    int i;
    int flag = 0;
    *p++ = '0';
    *p++ = 'x';
    if (num == 0) {
        *p++ = '0';
    } else {
        for (i = 28; i >= 0; i-=4) {
            ch = (num >> i) & 0xF;
            if (flag || (ch > 0)) {
                flag = 1;
                ch += '0';
                if (ch > '9') {
                    ch += 7;
                }
                *p++ = ch;
            }
        }
        
    }
    *p = 0;
    return str;
}

void kputc(char c)
{
    char *pvideo = (char*)0xB8000;
    pvideo = pvideo + 2 * position;
    if (c == '\n') {
        int m = 80 - position % 80;
        pvideo = pvideo + 2 * m;
        position = position + m;
    } else {
        *pvideo++ = c;
        *pvideo++ = 0x0f;
        position ++;
    }
}

__attribute__((regparm(0))) int kprintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int num = vsprintf(buf, format, args);
    va_end(args);
    
    int i;
    for (i = 0; i < num; ++i) {
        kputc(buf[i]);
    }
}
