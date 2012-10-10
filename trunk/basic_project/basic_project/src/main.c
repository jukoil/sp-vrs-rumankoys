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
**  Distribution: The file is distributed �as is,� without any warranty
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


int main(void)
{
	initUSART1();	//configures all necessary to use USART1

	RegisterCallbackUART1(&handleReceivedChar1);	//register function to be called when interrupt occurs
	PutsUART1("Running USART1...\r\n");			//write something to usart to see some effect
/*
	initUSART2();	//configures all necessary to use USART2

	RegisterCallbackUART2(&handleReceivedChar2);	//register function to be called when interrupt occurs
	PutsUART2("Running USART2...\r\n");			//write something to usart to see some effect

	initUSART3();	//configures all necessary to use USART3

	RegisterCallbackUART3(&handleReceivedChar3);	//register function to be called when interrupt occurs
	PutsUART3("Running USART3...\r\n");			//write something to usart to see some effect
*/



    while(1)
    {
    	char temp[128];
    	volatile int i;
    	sprintf( temp, "ADC pot: %i ADC term: %i Deg Celsius \r\n", ADC_read_potenciometer(), ADC_read_termistor()/*/4096.0*1353.0*//*/1.66-273.15*/ );
    	PutsUART1( temp );
    	for( i=0; i<500000; i++ );
    	tick++;
    }

	return 0;
}

