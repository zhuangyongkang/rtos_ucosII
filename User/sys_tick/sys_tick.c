#define _SYS_TICK_C_
 #include "stm32f10x.h" 

void SysTick_Configuration(void)
{
  if (SysTick_Config(SystemCoreClock / 100))
  { 
      while (1);
  }	  
	
  NVIC_SetPriority(SysTick_IRQn, 0x6); 
}
