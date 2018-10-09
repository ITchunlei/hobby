#ifndef _LOS_TYPES_H_
#define _LOS_TYPES_H_

typedef unsigned char      u8_t;
typedef unsigned short     u16_t;
typedef unsigned int       u32_t;
typedef unsigned long long u64_t;

#define DESC_ATTR()

inline void set_desc()
{
    
}

typedef struct {
    u32_t	reserved0;
    u64_t	rsp0;
    u64_t 	rsp1;
    u64_t	rsp2;
    u32_t	reserved1;
    u32_t	reserved2;
    u64_t	ist1;
    u64_t	ist2;
    u64_t	ist3;
    u64_t	ist4;
    u64_t	ist5;
    u64_t	ist6;
    u64_t	ist7;
    u32_t	reserved3;
    u32_t	reserved4;
    u16_t	reserved5;
    u16_t	io_map;
}__attribute__((packed)) tss_t;

typedef struct {
    u16_t offset_1;
    u16_t sel;
    u16_t attr;
    u16_t offset_2;
    u32_t offset_3;
    u32_t reserved;
}__attribute__((packed)) gate_t;

typedef struct {
    u16_t limit;
    u64_t base;
}__attribute__((packed)) idt_p_t;

typedef struct {
    u16_t limit_l;
    u16_t base_l;
    u8_t base_m;
    u16_t attr_limit;
    u8_t base_h;
}__attribute__((packed)) desc_t;


typedef struct {
    u32_t    back_link;
    u32_t    esp0;
    u32_t    ss0;
    u32_t    esp1;
    u32_t    ss1;
    u32_t    esp2;
    u32_t    ss2;
    u32_t    cr3;
    u32_t    eip;
    u32_t    eflags;
    u32_t    eax;
    u32_t    ecx;
    u32_t    edx;
    u32_t    ebx;
    u32_t    esp;
    u32_t    ebp;
    u32_t    esi;
    u32_t    edi;
    u32_t    es;
    u32_t    cs;
    u32_t    ss;
    u32_t    ds;
    u32_t    fs;
    u32_t    gs;
    u32_t    ldt;
    u16_t    trap;
    u16_t    io_base;
}__attribute__((packed)) tss32_t;


#endif /* _LOS_TYPES_H_ */
