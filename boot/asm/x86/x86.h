#ifndef __X86_H__
#define __X86_H__
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;




typedef struct regs {
	union {
		struct {
			u32	edi;
			u32	esi;
			u32	ebp;
			u32	esp;
			u32	ebx;
			u32	edx;
			u32	ecx;
			u32	eax;
			u32	es_ds;
			u32	gs_fs;
			u32	eflags;
		};
		struct {
			u16	di, edi_h;
			u16	si, esi_h;
			u16	bp, ebp_h;
			u16	sp, esp_h;
			u16	bx, ebx_h;
			u16	dx, edx_h;
			u16	cx, ecx_h;
			u16	ax, eax_h;
			u16	ds, es;
			u16	fs, gs;
			u16	flags, eflags_h;
		};
		struct {
			u8	di_l, di_h, edi_h_l, edi_h_h;
			u8	si_l, si_h, esi_h_l, esi_h_h;
			u8	bp_l, bp_h, ebp_h_l, ebp_h_h;
			u8	sp_l, sp_h, esp_h_l, esp_h_h;
			u8	bl, bh, ebx_h_l, ebx_h_h;
			u8	dl, dh, edx_h_l, edx_h_h;
			u8	cl, ch, ecx_h_l, ecx_h_h;
			u8	al, ah, eax_h_l, eax_h_h;
		};
	};
} regs;
#endif
