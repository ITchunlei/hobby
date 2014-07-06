#ifndef	__PARAM_H__
#define __PARAM_H__
#include <cinix/types.h>

struct memery_info_struct {
	u32_t	memery_size;
};
struct vedio_info_struct {
	u16_t	cursor_position;
	u16_t	current_page;	
};

struct hd_info_struct {
	
};

struct boot_param_struct {
	struct vedio_info_struct vedio_info;		
};

#endif
