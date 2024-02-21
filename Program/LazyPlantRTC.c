/*
 * LazyPlantRTC.c
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */
#include "LazyPlantRTC.h"


void RTC_Init(unsigned int year, unsigned int month, unsigned int dayofMonth,
              unsigned int dayofWeek, unsigned int hour, unsigned int min,
              unsigned int second) {
    // Unlock RTC key protected registers
    RTC_C->CTL0 = RTC_C_KEY;
    RTC_C->CTL13 = 0; // Temporarily halt RTC for configuration

    // Set time and date
    RTC_C->TIM0 = (second << RTC_C_TIM0_SEC_OFS) | (min << RTC_C_TIM0_MIN_OFS);
    RTC_C->TIM1 = (hour << RTC_C_TIM1_HOUR_OFS) | (dayofWeek << RTC_C_TIM1_DOW_OFS);
    RTC_C->DATE = (dayofMonth << RTC_C_DATE_DAY_OFS) | (month << RTC_C_DATE_MON_OFS);
    RTC_C->YEAR = (year << RTC_C_YEAR_YEAR_OFS);

    // Enable RTC to run in calendar mode and start it
    RTC_C->CTL13 &= ~RTC_C_CTL13_HOLD;

    // Lock the RTC registers and enable RTC interrupt for time events
    RTC_C->CTL0 = RTC_C_KEY;
    RTC_C->CTL0 |= RTC_C_CTL0_TEVIE;
    RTC_C->CTL13 |= RTC_C_CTL13_TEV_0;
    RTC_C->CTL0 &= ~(RTC_C_CTL0_TEVIFG);

    // Lock the RTC registers
    RTC_C->CTL0 &= ~RTC_C_KEY;
    NVIC_EnableIRQ(RTC_C_IRQn);

//    NVIC->ISER[0] |= 1 << ((RTC_C_IRQn) & 31);

}

void RTC_enableAlarm() {
    // Unlock RTC key protected registers
    RTC_C -> CTL0 = RTC_C_KEY;
    // Ensure the alarm interrupt is enabled
    RTC_C->CTL0 |= RTC_C_CTL0_AIE; // Enable alarm interrupt
    RTC_C->CTL0 &= ~RTC_C_KEY; // Lock the RTC registers after configuration
}
void RTC_disableAlarm() {
    // Unlock RTC key protected registers
    RTC_C -> CTL0 = RTC_C_KEY;
    // Ensure the alarm interrupt is enabled
    RTC_C->CTL0 &= ~RTC_C_CTL0_AIE; // Enable alarm interrupt
    RTC_C->CTL0 &= ~RTC_C_KEY; // Lock the RTC registers after configuration
}

void RTC_SetAlarm(unsigned int hour, unsigned int min) {
    // Set alarm time
    RTC_C -> AMINHR = (hour << RTC_C_AMINHR_HOUR_OFS) | (min << RTC_C_AMINHR_MIN_OFS) | RTC_C_AMINHR_HOURAE | RTC_C_AMINHR_MINAE;

    RTC_C -> CTL0 |= RTC_C_CTL0_AIE;
    RTC_C->CTL0 |= RTC_C_CTL0_AIE; // Enable alarm interrupt
    RTC_C->CTL0 &= ~RTC_C_KEY; // Lock the RTC registers after configuration
}

void RTC_CountDown(unsigned int hour, unsigned int min) {
    unsigned int alarm_hour, alarm_minute;



    // Calculate time for 30 minutes from now
    alarm_minute = (RTC_C -> TIM0 & RTC_C_TIM0_MIN_MASK) >> RTC_C_TIM0_MIN_OFS;
    alarm_hour = (RTC_C -> TIM1 & RTC_C_TIM1_HOUR_MASK) >> RTC_C_TIM1_HOUR_OFS;

    alarm_minute += min;
    alarm_hour += hour;

    if (alarm_minute >= 60) {
        alarm_minute -= 60; // Adjust minute if overflows
        alarm_hour += 1; // Increment hour
    }

    if (alarm_hour >= 24) {
        alarm_hour -= 24; // Adjust hour if overflows
    }

    RTC_SetAlarm(alarm_hour,alarm_minute);
}


void RTC_GetCurrentTimeString(char* buffer, unsigned int bufferSize) {
    unsigned int year, month, day, hour, minute, second;
    // Assuming the RTC is already running, retrieve the current time
    year = (RTC_C->YEAR & RTC_C_YEAR_YEAR_MASK) >> RTC_C_YEAR_YEAR_OFS;
    month = (RTC_C->DATE & RTC_C_DATE_MON_MASK) >> RTC_C_DATE_MON_OFS;
    day = (RTC_C->DATE & RTC_C_DATE_DAY_MASK) >> RTC_C_DATE_DAY_OFS;
    hour = (RTC_C->TIM1 & RTC_C_TIM1_HOUR_MASK) >> RTC_C_TIM1_HOUR_OFS;
    minute = (RTC_C->TIM0 & RTC_C_TIM0_MIN_MASK) >> RTC_C_TIM0_MIN_OFS;
    second = (RTC_C->TIM0 & RTC_C_TIM0_SEC_MASK) >> RTC_C_TIM0_SEC_OFS;

    // Format the time into the provided buffer
    snprintf(buffer, bufferSize, "%02u/%02u/%02u %02u:%02u:%02u", year, month, day, hour, minute, second);
}

// RTC ISR
void RTC_C_IRQHandler(void) {
    // Check if this is a time event interrupt (e.g., every minute)
    if (RTC_C->CTL0 & RTC_C_CTL0_TEVIFG & WAKE_UP_FROM_TIME_EVENT) {
        overallCheck();
        RTC_C->CTL0 = RTC_C_KEY; // Unlock
        RTC_C->CTL0 &= ~RTC_C_CTL0_TEVIFG; // Clear flag
        RTC_C->CTL0 &= ~RTC_C_KEY; // Lock again
    }

    // Check if this is an alarm interrupt
    if (RTC_C->CTL0 & RTC_C_CTL0_AIFG & WAKE_UP_FROM_ALARM) {
        overallCheck();
        RTC_C->CTL0 = RTC_C_KEY; // Unlock
        RTC_C->CTL0 &= ~RTC_C_CTL0_AIFG; // Clear flag
        RTC_C->CTL0 &= ~RTC_C_KEY; // Lock again
    }
}
