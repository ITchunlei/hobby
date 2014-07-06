/*
 * file : proc.h
 * author : wangchunlei
 * date : 2014
 */

#ifndef	__PROC_H__
#define	__PROC_H__


#define NR_TASKS 10	/* the number of process */


/*
 * task struct
 */

struct task_struct {
	struct stack_frame_struct stack_frame;
	u32_t	pid;	/* process id */
};


#endif	/*__PROC_H__*/
