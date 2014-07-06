#include "klib.h"
#include "global.h"
#include <arch/x86/protect.h>

char *itoa(char *str, int num) {
	char *p = str;
	char ch;
	int i;
	int flag = 0;
	*p++ = '0';
	*p++ = 'x';
	if (0 == num) {
		*p++ = '0';
	} else {
		for (i = 28;i >= 0;i -= 4) {
			ch = (num >> i) & 0xf;
			if (flag || (ch > 0)) {
				flag = 1;
				ch += '0';
				if (ch > '9') {
					ch += 7;
				}		
				*p++ = ch;
			}
		}
	}
	*p = 0;
	return str;
}
char tmp[256];
void display_tss(void) {
	display_str("tss.................................\n");
	display_str(itoa(tmp, _tss.esp0));
	display_str("\n");
	display_str(itoa(tmp, _tss.ss0));
	display_str("\n");
	display_str(itoa(tmp, _tss.esp1));
	display_str("\n");
	display_str(itoa(tmp, _tss.ss1));
	display_str("\n");
	display_str(itoa(tmp, _tss.esp2));
	display_str("\n");
	display_str(itoa(tmp, _tss.ss2));
	display_str("\n");
	display_str(itoa(tmp, _tss.es));
	display_str("\n");
	display_str(itoa(tmp, _tss.cs));
	display_str("\n");
	display_str(itoa(tmp, _tss.ss));
	display_str("\n");
}
void exception_handler(int vec_no, int err_code
	, int eip, int cs, int eflags) {
	display_str("error........\n");
	display_str("vec_no:");
	display_str(itoa(tmp, vec_no));
	display_str("\n");
	display_str("err_code:");
	display_str(itoa(tmp, err_code));
	display_str("\n");
	display_str("eip:");
	display_str(itoa(tmp, eip));
	display_str("\n");
	display_str("cs:");
	display_str(itoa(tmp, cs));
	display_str("\n");
	display_str("eflags:");
	display_str(itoa(tmp, eflags));
	display_str("\n");
			

}

