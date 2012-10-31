/*
 * adc.c
 *
 *  Created on: Oct 10, 2012
 *      Author: student
 */
//ADC IN 10
#include "mcu.h"

void ADC_init(){
	  ADC_InitTypeDef ADC_InitStruct;
	  GPIO_InitTypeDef GPIO_InitStructure;

	  //GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_AN);

	  /* Configure USART Tx and Rx pins */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;			//alternating function
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;		//not very important, do not change
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//output is push pull type
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		//do not use pull ups or pull downs
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//choosing the pins
	  GPIO_Init(GPIOC, &GPIO_InitStructure);				//applying settings

	  /* Reset ADC init structure parameters values */
	  /* Initialize the ADC_Resolution member */
	  ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	  /* Initialize the ADC_ScanConvMode member */
	  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	  /* Initialize the ADC_ContinuousConvMode member */
	  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	  /* Initialize the ADC_ExternalTrigConvEdge member */
	  ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  /* Initialize the ADC_ExternalTrigConv member */
	  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
	  /* Initialize the ADC_DataAlign member */
	  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	  /* Initialize the ADC_NbrOfConversion member */
	  ADC_InitStruct.ADC_NbrOfConversion = 1;

	  ADC_Init( ADC1, &ADC_InitStruct );

	  ADC_Cmd( ADC1, ENABLE );
}

#define  IDD_MEASUREMENT_PIN       GPIO_Pin_0
#define  IDD_MEASUREMENT_GPIO_CLK  RCC_AHBPeriph_GPIOC
#define  IDD_MEASUREMENT_GPIO      GPIOC
#define  IDD_MEASUREMENT_ADC_CHANNELS  ADC_Channel_TempSensor | ADC_Channel_10
#define  IDD_MEASUREMENT_ADC_POTENCIOMETER ADC_Channel_10
#define  IDD_MEASUREMENT_ADC_TERMISTOR  ADC_Channel_TempSensor
//ADC_Channel_17
  #define  APOSTROPHE_OFF DOUBLEPOINT_OFF


void ADC_config(){
	  ADC_InitTypeDef ADC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable The HSI (16Mhz) */
	RCC_HSICmd(ENABLE);

	/* Enable the GPIOF or GPIOA Clock */
	RCC_AHBPeriphClockCmd(IDD_MEASUREMENT_GPIO_CLK, ENABLE);
	/* Configure PF.11 (ADC Channel11) or PA.05 (ADC Channe5) in analog mode */
	GPIO_InitStructure.GPIO_Pin =  IDD_MEASUREMENT_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(IDD_MEASUREMENT_GPIO, &GPIO_InitStructure);

	/* Check that HSI oscillator is ready */
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	/* ADC1 Configuration ------------------------------------------------------*/

	/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	#ifdef USE_STM32L152D_EVAL
	/* Select ADC Bank channel */
	ADC_BankSelection(ADC1, ADC_Bank_B);
	#endif

	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);


}

void neheheh()
{
	/* ADC1 regular channel5 or channel1 configuration */
	ADC_RegularChannelConfig(ADC1, IDD_MEASUREMENT_ADC_POTENCIOMETER, 1, ADC_SampleTime_192Cycles);

	/* Define delay between ADC1 conversions */
	ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

	/* Enable ADC1 Power Down during Delay */
	ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait until ADC1 ON status */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
	}

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConv(ADC1);

	/* Wait until ADC Channel 5 or 1 end of conversion */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
	{
	}
}




int ADC_read_potenciometer(){
	ADC_config();
	//ADC_SoftwareStartConv( ADC1 );
	/* ADC1 regular channel5 or channel1 configuration */
	ADC_RegularChannelConfig(ADC1, IDD_MEASUREMENT_ADC_POTENCIOMETER, 1, ADC_SampleTime_192Cycles);

	/* Define delay between ADC1 conversions */
	ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

	/* Enable ADC1 Power Down during Delay */
	ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait until ADC1 ON status */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
	}

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConv(ADC1);

	/* Wait until ADC Channel 5 or 1 end of conversion */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
	{
	}
	 return ADC_GetConversionValue( ADC1 );
}

int ADC_read_termistor(){
	ADC_config();
	//ADC_SoftwareStartConv( ADC1 );
	/* ADC1 regular channel5 or channel1 configuration */
	ADC_RegularChannelConfig(ADC1, IDD_MEASUREMENT_ADC_TERMISTOR, 1, ADC_SampleTime_192Cycles);

	/* Define delay between ADC1 conversions */
	ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

	/* Enable ADC1 Power Down during Delay */
	ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait until ADC1 ON status */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
	}

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConv(ADC1);

	/* Wait until ADC Channel 5 or 1 end of conversion */
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
	{
	}
	//ADC_SoftwareStartConv( ADC1 );
	 return ADC_GetConversionValue( ADC1 );
}
