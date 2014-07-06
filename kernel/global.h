#ifndef	__GLOBAL_H__
#define __GLOBAL_H__
#include <cinix/param.h>
#include <arch/x86/protect.h>

extern struct boot_param_struct boot_param;
extern void restart(void);
extern void arch_init(void);
#endif /* __GLOBAL_H__ */
