//
//  proc.h
//  Hobby
//
//  Created by chunlei on 2018/10/9.
//  Copyright © 2018 los. All rights reserved.
//

#ifndef __PROC_H__
#define __PROC_H__

#include "thread.h"
#include "types.h"

#define NR_PROCS 10

#define PROC_NAME_LENGTH	20

struct proc {
    char name[PROC_NAME_LENGTH];
    void* entry;
    int pid;
    int state;
    u64_t regs[24];
};

struct proc proc_table[NR_PROCS];

#endif /* __PROC_H__ */
