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
void handleReceivedChar(unsigned char data)
{
	if (data == 'A')
	{
		PutsUART1("Prijal som znak A");
	}
	else if (data == 'T' || data == 't')
	{
		char buf[20];
		sprintf(buf, "t=%d\n",tick);
		PutsUART1(buf);
	}
}


int main(void)
{
	initUSART1();	//configures all necessary to use USART1

	RegisterCallbackUART1(&handleReceivedChar);	//register function to be called when interrupt occurs
	PutsUART1("Running USART1...\n");			//write something to usart to see some effect

    while(1)
    {
    	tick++;
    }

	return 0;
}

