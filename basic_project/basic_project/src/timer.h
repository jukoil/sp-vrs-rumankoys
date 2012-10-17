/**
  ******************************************************************************
  * @file    firmware/src/mcu/timer.h
  * @author  Jozef Rodina
  * @version V1.0.0
  * @date    20-January-2012
  * @brief   TIMER driver.
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2012 Jozef Rodina</center></h2>
  ******************************************************************************
  */
#ifndef __TIMER
#define __TIMER

#include "stm32l1xx.h"

void initBaseTimer(void);
void registerBaseTimerHandler(void (*handler)(long long timeStamp));

#endif
