#ifndef _SYS_TICK_H_
#define _SYS_TICK_H_

#ifdef _SYS_TICK_C_
#define SYS_TICK_C_EXT
#else
#define SYS_TICK_C_EXT extern
#endif
SYS_TICK_C_EXT int a = 3;

SYS_TICK_C_EXT void SysTick_Configuration(void);
#endif
