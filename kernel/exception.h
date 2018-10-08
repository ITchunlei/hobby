//
//  exception.h
//  Hobby
//
//  Created by chunlei on 2018/10/5.
//  Copyright © 2018 los. All rights reserved.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "types.h"

void exception_init(gate_t*);

void do_exception(int vec_no, int err_code, int rip, int cs, int rflags);

#endif /* EXCEPTION_H */
