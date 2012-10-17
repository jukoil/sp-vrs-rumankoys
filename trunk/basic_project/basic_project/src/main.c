/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32Lxx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/
/* Includes */
#include <stddef.h>
#include <stdio.h>
#include "mcu.h"
#include "usart.h"
#include "pwm_out.h"
#include "timer.h"


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

int tick = 0;


//this is a function handling received data
//it is not called automaticaly
void handleReceivedChar1(unsigned char data)
{
	if (data == 'A')
	{
		PutsUART1("Prijal som znak A");
	}
	else if (data == 'T' || data == 't')
	{
		char buf[20];
		sprintf(buf, "t=%d\r\n",tick);
		PutsUART1(buf);
	}
}

//this is a function handling received data
//it is not called automaticaly
void handleReceivedChar1pwm(unsigned char data)
{
	data = toupper(data);
	if (data == 'I')
	{
    	PutsUART1( "Increasing\r\n" );
    	if(TIM3->CCR2<=450)
    		TIM3->CCR2+=50;
	}
	else if (data == 'D')
	{
    	PutsUART1( "Decreasing\r\n" );
    	if(TIM3->CCR2>=50)
    		TIM3->CCR2-=50;
	}
}


void handleReceivedChar2(unsigned char data)
{
	if (data == 'A')
	{
		PutsUART2("Zapredal som znak A");
	}
	else if (data == 'T' || data == 't')
	{
		char buf[60];
		sprintf(buf, "t=%d nehehehe\r\n",tick);
		PutsUART2(buf);
	}
}

void handleReceivedChar3(unsigned char data)
{
	if (data == 'A')
	{
		PutsUART3("Som zabil znak A");
	}
	else if (data == 'T' || data == 't')
	{
		char buf[60];
		sprintf(buf, "t=%d muhehehe\r\n",tick);
		PutsUART3(buf);
	}
}


void handlerTimer(long long timeStamp){
	if( TIM3->CCR2 >= 100 )
		TIM3->CCR2-=100;
	else
		TIM3->CCR2=500;
}

void initUserButton(){

	GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  /*--------------------------------- GPIO Configuration -------------------------*/
	  /* GPIOC Configuration: Pin 6 */
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

	  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

char userButtonDown(){
	static char lastPressed = 0;
	char pressed = GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_0 );
	int result = !lastPressed && pressed;
	lastPressed = pressed;
	return result;
}

char userButtonUp(){
	static char lastPressed = 0;
	char pressed = GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_0 );
	int result = lastPressed && !pressed;
	lastPressed = pressed;
	return result;
}

int main(void)
{
	initUSART1();	//configures all necessary to use USART1

	RegisterCallbackUART1(&handleReceivedChar1pwm);	//register function to be called when interrupt occurs
	PutsUART1("Running USART1...\r\n");			//write something to usart to see some effect
/*
	initUSART2();	//configures all necessary to use USART2

	RegisterCallbackUART2(&handleReceivedChar2);	//register function to be called when interrupt occurs
	PutsUART2("Running USART2...\r\n");			//write something to usart to see some effect

	initUSART3();	//configures all necessary to use USART3

	RegisterCallbackUART3(&handleReceivedChar3);	//register function to be called when interrupt occurs
	PutsUART3("Running USART3...\r\n");			//write something to usart to see some effect
*/


/*
    while(1)
    {
    	char temp[128];
    	volatile int i;
    	sprintf( temp, "ADC pot: %i ADC term: %i Deg Celsius \r\n", ADC_read_potenciometer(), ADC_read_termistor());
    	PutsUART1( temp );
    	for( i=0; i<500000; i++ );
    	tick++;
    }
*/

	int horedole = 1;
	initBaseTimer();
	initPWM_Output();
//	registerBaseTimerHandler(&handlerTimer);

	volatile int i;

    while(1)
    {
    /*	if( horedole ){
    		TIM3->CCR2++;
    		if(TIM3->CCR2>500)
    			horedole=0;
    	}else{
    		TIM3->CCR2--;
    		if(TIM3->CCR2<2)
    			horedole=1;
    	}
    	for( i=0;i<500;i++);*/

    	if ( userButtonDown() )
    	{
        	PutsUART1( "Button Decreasing\r\n" );
        	if(TIM3->CCR2>=50)
        		TIM3->CCR2-=50;
    	}
    }


	return 0;
}

