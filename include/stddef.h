#ifndef __STDDEF_H__
#define __STDDEF_H__

#ifndef __PTRDIFF_T__
#define __PTRDIFF_T__
typedef long ptrdiff_t;
#endif

#ifndef __SIZE_T__
#define __SIZE_T__
typedef unsigned long size_t;
#endif

#undef NULL
#define NULL ((void*)0)

#endif
