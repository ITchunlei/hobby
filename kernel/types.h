#ifndef _LOS_TYPES_H_
#define _LOS_TYPES_H_

typedef unsigned char      u8_t;
typedef unsigned short     u16_t;
typedef unsigned long      u32_t;
typedef unsigned long long u64_t;


typedef struct {
    u16_t offset_l;
    u16_t sel;
    u16_t attr;
    u16_t offset_h;
}__attribute__((packed)) gate_t;

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
}__attribute__((packed)) tss_t;


#endif /* _LOS_TYPES_H_ */
