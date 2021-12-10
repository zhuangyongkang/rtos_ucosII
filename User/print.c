#include "stm32f10x.h" 
#include <stdio.h>

static void RCC_Configuration(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

//(2)GPIOPA9--TX, PA10--RX
static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef stGpioInitTypeDef;
	//TX
	stGpioInitTypeDef.GPIO_Pin = GPIO_Pin_9;
	stGpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	stGpioInitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &stGpioInitTypeDef);
	//RX
	stGpioInitTypeDef.GPIO_Pin = GPIO_Pin_10;
	stGpioInitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &stGpioInitTypeDef);
}

//(3)USART1printf
static void USART_Configuration(void)
{ // Set port, line and mode etc
	USART_InitTypeDef stUSART_InitTypeStruct;
	stUSART_InitTypeStruct.USART_BaudRate = 9600;
	stUSART_InitTypeStruct.USART_WordLength = USART_WordLength_8b;
	stUSART_InitTypeStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	stUSART_InitTypeStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	stUSART_InitTypeStruct.USART_StopBits = USART_StopBits_1;
	stUSART_InitTypeStruct.USART_Parity = USART_Parity_No;
	USART_Init(USART1, &stUSART_InitTypeStruct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

static void NVIC_Configuration(void)
{// Set Group and Priority
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_SetPriorityGrouping(4);
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
	//get receive it
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		USART_SendData(USART1, USART_ReceiveData(USART1) );
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
}

void print_init(void)
{
	 RCC_Configuration();
	 GPIO_Configuration();
	 USART_Configuration();
	 NVIC_Configuration();
}
int fputc(int ch, FILE *fp)
{
	USART_SendData(USART1, (u8)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET );
	return ch;
}
