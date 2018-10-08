//
//  asm.h
//  Boot
//
//  Created by chunlei on 2018/10/5.
//  Copyright © 2018 los. All rights reserved.
//

#ifndef __ASM_H__
#define __ASM_H__

#define GLOBAL(L) .global L; L:
#define FUNC(N) GLOBAL(N)

#endif /* __ASM_H__ */
