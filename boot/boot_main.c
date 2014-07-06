#ifndef __CODE16_H__
#define __CODE16_H__
asm(".code16gcc\n\t");
#endif
#include "asm/x86/x86.h"

char tmp[100];
extern void put_char(char ch);
extern void __attribute__((regparm(3)))bios_int(
	unsigned short int_num
	, regs* iregs
	, regs* oregs) {
	asm volatile ("mov	%al, 1f\n\t"
			"pushfl\n\t"
			"push	%fs\n\t"
			"push	%gs\n\t"
			"pushal\n\t"
			"subw	$44, %sp\n\t"
			"mov	%dx, %si\n\t"
			"mov	%sp, %di\n\t"
			"movw	$11, %cx\n\t"
			"rep;	movsd\n\t"
			"popal\n\t"
			"pop	%ds\n\t"
			"pop	%es\n\t"
			"pop	%fs\n\t"
			"pop	%gs\n\t"
			"popfl\n\t"
			".byte	0xcd\n\t"
			"1:	.byte	0\n\t"
			"pushfl\n\t"
			"push	%gs\n\t"
			"push	%fs\n\t"
			"push	%es\n\t"
			"push	%ds\n\t"
			"pushal\n\t"
			"cld\n\t"
			"movzwl	%sp, %esp\n\t"
			"mov	%cs, %ax\n\t"
			"mov	%ax, %ds\n\t"
			"mov	%ax, %es\n\t"
			"mov	68(%esp), %di\n\t"
			"and	%di, %di\n\t"
			"jz	2f\n\t"
			"mov	%sp, %si\n\t"
			"mov	$11, %cx\n\t"
			"rep; movsd\n\t"
			"2:\n\t"
			"add	$44, %sp\n\t"
			"popal\n\t"
			"pop	%gs\n\t"
			"pop	%fs\n\t"
			"popfl\n\t");
}

unsigned short inline get_ds() {
	asm("mov	%ds, %ax\n\t");
}
extern unsigned short inline get_es() {
	asm("mov	%es, %ax\n\t");
}
unsigned short inline get_fs() {
	asm("mov	%fs, %ax\n\t");
}
unsigned short inline get_gs() {
	asm("mov	%gs, %ax\n\t");
}



typedef struct {
	unsigned long addr_low;
	unsigned long addr_high;
	unsigned long length_low;
	unsigned long length_high;
	unsigned long	type;	
} s_e820;

int call_e820(s_e820* addr) {
	print("start to get memery info..\n");
	s_e820 buffer;
	regs iregs;
	regs oregs;
	iregs.eax = 0x0000e820;
	iregs.ebx = 0x0;
	iregs.es = get_es();
	iregs.di = (unsigned short)&buffer;
	iregs.ecx = sizeof(buffer);
	iregs.edx = 0x534d4150;
	int num = 0;
	do {
		bios_int(0x15, &iregs, &oregs);
		num ++;
		*addr ++ = buffer;
		iregs.ebx = oregs.ebx;
	} while(oregs.ebx);
	
	return num - 1;
}

void print(char *str) {

	regs iregs;
	regs oregs;
	while( 0 != *str ) {
		if ( '\n' == *str) {
			iregs.eax = 0x0e00 + '\r';
			bios_int(0x10, &iregs, &oregs);
		}
		iregs.eax = 0x0e00 + ( *str++ );
		bios_int(0x10, &iregs, &oregs);
	}
}

void print_num(unsigned long long num) {
	regs iregs;
	for (int i = 0;i < 16;i ++) {
		iregs.eax = 0x0e00 + (unsigned char)(num) + 0x30;
		bios_int(0x10, &iregs, 0);
		num = num >> 4;
	}
}
void print_num_32(unsigned long num) {
	regs iregs;
	for (int i = 8;i > 0;i --) {
		unsigned long tmp = num;
		iregs.eax = 0x0e00 + (unsigned char)(num >> ((i-1) * 4))
 + 0x30;
		bios_int(0x10, &iregs, 0);
	}
}

char *itoa(long value,char *str,int radix){
	char* table = "0123456789ABCDEF";
	char* ptr = str;
	int i;
	int j; 
	int k=0;    
	if(value == 0)	{*ptr ++= '0'; *ptr = '\0';}
	while(value){
			*ptr++ = table[value%radix];
			 value /= radix;
			if(value < radix){
				*ptr++ = table[value];
				*ptr = '\0';
				break;
			}	
	}
	j =ptr -str -1;
	for(i =0;i < (ptr - str) / 2 ; i++){
		int temp = str[i];
		str[i] = str[j];
		str[j--] = temp;
	}
	return str;
}
void get_memery_info() {

}

struct s_seg_desc {
	unsigned short limit_low;
	unsigned short base_addr_low;
	unsigned char  base_addr_mid;
	unsigned char  attr_low;
	unsigned char  limit_high_attr_high;
	unsigned char  base_addr_high;
}__attribute__((packed));

struct s_gdtr {
	unsigned short limit;
	unsigned long  base_addr;
}__attribute__((packed));

void set_seg_desc(struct s_seg_desc *seg_desc
	, unsigned long base_addr
	, unsigned long limit
	, unsigned short attr) {
	seg_desc->limit_low		= limit & 0xffff;
	seg_desc->base_addr_low		= base_addr & 0xffff;
	seg_desc->base_addr_mid 	= (base_addr >> 16) & 0xff;
	seg_desc->attr_low		= attr & 0xff;
	seg_desc->limit_high_attr_high	= ((attr >> 8) & 0xf0) | ((limit >> 16) & 0xff);
	seg_desc->base_addr_high	= (base_addr >> 24) & 0xff;
}


#define set_seg_desc_attr(G, DB, P, DPL, S, TYPE) \
	TYPE | (S << 4) | (DPL << 5) | (P << 7) | (DB << 14) | (G << 15)


struct s_seg_desc gdt[3];
struct s_gdtr gdtr;
extern void inline sti() {
	asm volatile("sti\n\t");
}
extern void inline cli() {
	asm volatile("cli\n\t");
}

extern void inline lgdt(struct s_gdtr gdtr) {
	asm volatile("lgdt %0\n\t"::"m"(gdtr));
}

void init();

void goto_protected_mode() {
	set_seg_desc(&gdt[0], 0, 0, 0);
	set_seg_desc(&gdt[1], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, 0, 1, 0xa));	
	set_seg_desc(&gdt[2], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, 0, 1, 0x2));
	set_seg_desc(&gdt[3], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, 3, 1, 0x2));
	set_seg_desc(&gdt[4], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, 3, 1, 0x2));
	gdtr.limit 	= sizeof(struct s_seg_desc) * 5 - 1;
	gdtr.base_addr 	= (unsigned long)&gdt + 0x90000;
	lgdt(gdtr); 
	cli();
	print(itoa(gdtr.base_addr, tmp, 16));
	asm volatile("inb	$0x92, %al\n\t");
	asm volatile("or	$0x02, %al\n\t");
	asm volatile("outb	%al, $0x92\n\t");
	asm volatile("mov	%cr0, %eax\n\t");	
	asm volatile("or	$1, %eax\n\t");	
	asm volatile("mov	%eax, %cr0\n\t");
	asm volatile(".byte	0x66, 0xea\n\t");
	asm volatile(".long	0x10100\t");	
	asm volatile(".word	8\n\t");	
}

unsigned char	get_byte(unsigned short baseaddr, unsigned short offaddr){
	asm volatile("push	%%ds\n\t"
				"mov	%%dx, %%ds\n\t"
				"lodsb\n\t"
				"pop	%%ds\n\t"
				:
				:"d"(baseaddr),"S"(offaddr));
}

int	searchfile(char *str,unsigned short baseaddr, unsigned short offaddr){
	int k,n=0;
	for(k =0;k<11;k++){
		if((*str != '\0')&&(*str == get_byte(baseaddr,offaddr+k))){ 
			*str++;
			n++;
		}
		else	break;
	}
	return n;
}
void readsec(unsigned int secn, unsigned short baseaddr, unsigned short offaddr){
	regs iregs, oregs;
	iregs.ch = (secn/18)>>1;
	iregs.cl = secn%18 +1;
	iregs.dh = (secn/18) & 1;
	iregs.dl = 0;
	iregs.es =baseaddr;
	iregs.bx = offaddr;
	iregs.ax = 0x0201;
	bios_int(0x13, &iregs, &oregs);
}

int	fixfile(char *str, unsigned short baseaddr, unsigned short offaddr){
	int i,j,k;	
	for(i = 0;i < 14; i ++){
		readsec(19+i,baseaddr, offaddr);
		for(j =0;j<16;j++){
			if(11>searchfile(str, baseaddr, offaddr + 32*j));
			else	return j;
		}
	}
	return 8;
}
void loadfat(unsigned short baseaddr, unsigned short offaddr){
	int i =0;
	for(;i < 9; i++)
		readsec(1+i, baseaddr, offaddr+512*i);
}
void readfat(unsigned short *a, unsigned short baseaddr ,unsigned short offaddr){
	int i;
		
	for(i =0;i < 1536;i++){
		unsigned short _offaddr = offaddr+3*i;
		unsigned short t1, t2;	
		asm volatile ("push	%%ds\n\t"
					"mov	%%dx, %%ds\n\t"
					"lodsl\n\t"
					"mov	%%eax, %%ebx\n\t"
					"and	$0x00000fff, %%eax\n\t"
					"shr		$12, %%ebx\n\t"
					"and	$0x00000fff, %%ebx\n\t"
					"pop	%%ds\n\t"
					:"=a"(t1),"=b"(t2)
					:"d"(baseaddr), "S"(_offaddr));
		a[2*i] = t1;
		a[2*i+1]=t2;
	}
}

int loadfile(char * fname, unsigned short *fat,unsigned short baseaddr, unsigned short offaddr){	
	loadfat(baseaddr, offaddr+0x200);
	readfat(fat, baseaddr, offaddr+0x200);
	int n = fixfile(fname,baseaddr, offaddr);
	int firstfatn =0;
	unsigned short _offaddr = offaddr + 32*n + 26;
	asm volatile( "push	%%ds\n\t"	
				"mov	%%dx, %%ds\n\t"
				"lodsw\n\t"
				"pop	%%ds\n\t"
				:"=a"(firstfatn)
				:"d"(baseaddr),"S"(_offaddr));
	readsec(31+firstfatn,baseaddr, offaddr);
	int i= 1;
	while(fat[firstfatn]<0xFF7){
		readsec(31+fat[firstfatn], baseaddr, offaddr+512*i);
		firstfatn = fat[firstfatn];
		i++;
	}
	return  firstfatn;
}
/********loader end*****/


void load_kernel() {}
unsigned short a[2046];
s_e820 e820[8];
void boot_main() {
	int num = call_e820(e820);
	for (int i = 0;i < num;i ++) {
		print(itoa(e820[i].addr_low, tmp, 16));
		print("\t");
		print(itoa(e820[i].addr_high, tmp, 16));
		print("\t");
		print(itoa(e820[i].length_low, tmp, 16));
		print("\t");
		print(itoa(e820[i].length_high, tmp, 16));
		print("\t");
		print(itoa(e820[i].type, tmp, 16));
		print("\n");
		
	}
	print(itoa((e820[4].length_low + e820[4].addr_low) / 0x100000, tmp, 10));
//
	loadfile("KERNEL  BIN", a, 0x1000, 0x100);	
	print("---------------goto_protected_mode-----------------");
	goto_protected_mode();
}

void init() {
	for (;;);
}
