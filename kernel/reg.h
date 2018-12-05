//
//  reg.h
//  Hobby
//
//  Created by chunlei on 2018/10/9.
//  Copyright © 2018 los. All rights reserved.
//

#ifndef __REG_H__
#define __REG_H__
#include "macros.h"
#include "types.h"


static inline uint64_t get_cr0() {
    uint64_t val;
    __asm__ __volatile__("mov %%cr0, %0 \n\t": "=r"(val));
    return val;
}

static inline void set_cr0(uint64_t val) {
    __asm__ __volatile__("mov %0, %%cr0 \n\t":: "r"(val));
}

static inline uint64_t get_cr3() {
    uint64_t val;
    __asm__ __volatile__("mov %%cr3, %0 \n\t": "=r"(val));
    return val;
}

static inline void set_cr3(uint64_t val) {
    __asm__ __volatile__("mov %0, %%cr3 \n\t":: "r"(val));
}

static inline uint64_t get_cr4() {
    uint64_t val;
    __asm__ __volatile__("mov %%cr4, %0 \n\t": "=r"(val));
    return val;
}

static inline void set_cr4(uint64_t val) {
    __asm__ __volatile__("mov %0, %%cr4 \n\t":: "r"(val));
}



#endif /* __SEG_H__ */
