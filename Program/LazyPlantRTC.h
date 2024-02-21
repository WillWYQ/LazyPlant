/*
 * LazyPlantRTC.h
 *
 *  Created on: Feb 20, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTRTC_H_
#define LAZYPLANTRTC_H_

#include "LazyPlantSourceFiles.h"

void RTC_Init(unsigned int year, unsigned int month, unsigned int dayofMonth,
              unsigned int dayofWeek, unsigned int hour, unsigned int min,
              unsigned int second);
void RTC_CountDown(unsigned int hour, unsigned int min);
void RTC_GetCurrentTimeString(char* buffer, unsigned int bufferSize);
void RTC_C_IRQHandler(void);

#endif /* LAZYPLANTRTC_H_ */
