#include "print.h" 
#include <stdio.h>
#include "sys_tick.h"
#include "ucos_ii.h"
#include "misc.h"

void task_func(void *p_arg)
{
	for(;;)
	{
       	printf("\njjj\n");	
  }
}

OS_STK stack_zyk[128];


//
int main(void)
{	 
	 print_init();
	 __set_BASEPRI(0x4<<4);
	
	 SysTick_Configuration();
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x40000);
	 OSInit();
	
	 OSTaskCreate(task_func,(void*)0,&stack_zyk[127],4);
	 OSStart();
	 
	 while(1)
	 {	       
		  printf("\n您发送的消息为:\n");	  
	 }	     	

	 
} 







