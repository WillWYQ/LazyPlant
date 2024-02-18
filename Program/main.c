#include "LazyPlantSourceFiles.h"


void overallinit(){
    wateringInit();
    RTC_Init(0,0,0,11,0,1,0);
    RGBLED_init();
}





/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    overallinit();
    RTC_CountDown(0, 1);

    __enable_irq();

    char currentTime[20]; // Buffer to hold the current time string

    while(1){
        RTC_GetCurrentTimeString(currentTime, sizeof(currentTime));
        printf("Current Time: %s\n", currentTime);
    }

}
