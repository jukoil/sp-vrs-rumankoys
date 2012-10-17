#include "pwm_out.h"
#include "mcu.h"
#include "stm32l1xx_tim.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
uint16_t PrescalerValue = 0;

void initPWM_Output()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	  /* GPIOC clock enable */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	  /*--------------------------------- GPIO Configuration -------------------------*/
	  /* GPIOC Configuration: Pin 6 */
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);

	  /* -----------------------------------------------------------------------
	    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
	    The TIM3CLK frequency is set to SystemCoreClock (Hz), to get TIM3 counter
	    clock at 8 MHz the Prescaler is computed as following:
	     - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	    SystemCoreClock is set to 32 MHz for  Medium-density devices.

	    The TIM3 is running at 12 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
	                                                  = 8 MHz / 666 = 12 KHz
	    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
	    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
	    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
	  ----------------------------------------------------------------------- */
	  /* Compute the prescaler value */
	  PrescalerValue = (uint16_t) (SystemCoreClock / 100000) - 1;
	  /* Time base configuration */
	  TIM_TimeBaseStructure.TIM_Period = 500;
	  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  /* PWM1 Mode configuration: Channel1 */
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 500;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;



	  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  TIM_ARRPreloadConfig(TIM3, ENABLE);

	  /* TIM3 enable counter */
	  TIM_Cmd(TIM3, ENABLE);
}
