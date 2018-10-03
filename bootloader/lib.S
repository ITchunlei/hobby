#include "lib.h"
FUNCTION(read_bs)
    movw $0x0201, %ax
    /** 读一个扇区 **/
    movb $0x10, %al
    movb $0x0, %ch
    /** 0-5 起始扇区 6-7 磁道**/
    movb $0x02, %cl
    /** dl 驱动器号 dh 磁头号 **/
    movw $0x0, %dx
    /** es:bx 数据缓冲区地址 **/
    movw $0x1100, %bx
    int $0x13
    ret
