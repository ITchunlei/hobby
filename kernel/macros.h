//
//  macros.h
//  Hobby
//
//  Created by chunlei on 2018/11/12.
//  Copyright © 2018 hobby. All rights reserved.
//

#ifndef __MACROS_H__
#define __MACROS_H__
#ifdef __cplusplus
#define __EXTERN_C_BEGIN extern "C" {
#define __EXTERN_C_END }
#else
#define __EXTERN_C_BEGIN
#define __EXTERN_C_END
#endif


#define __ALIGNED(x) __attribute__((aligned(x)))
#define __PACKED __attribute__((packed))

#define ALIGN(x, y)  (((x) + ((y) - 1)) & ~((y) - 1))

#endif /* __MACROS_H__ */
