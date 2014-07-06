#ifndef __TYPES_H__
#define __TYPES_H__


#ifndef __SIZE_T__
#define __SIZE_T__
typedef unsigned int size_t;
#endif


#ifndef __SSIZE_T__
#define __SSIZE_T__
typedef int ssize_t;
#endif

#ifndef __TIME_T__
#define __TIME_T__
typedef long time_t;
#endif

typedef short 		dev_t;
typedef char 		gid_t;
typedef unsigned long	ino_t;
typedef unsigned short	mode_t;
typedef short		nlink_t;
typedef int		pid_t;
typedef short		uid_t;
typedef	unsigned long	zone_t;
typedef unsigned long	block_t;
typedef unsigned long	bit_t;


typedef	unsigned char	u8_t;
typedef unsigned short	u16_t;
typedef unsigned long	u32_t;

typedef char		i8_t;
typedef short		i16_t;
typedef long		i32_t;



#endif
