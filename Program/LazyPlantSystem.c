
#include "LazyPlantSystem.h"


/*choose in LazyPlantSourceFiles.h
 *
 * #define WakeUpfromAlarm 0
 * #define WakeUpfromTimeEvent 1 // for project demo
 *
 */


double usedWater = 0;
int lightTimeHours = 0; // might be in min or hours depends


void overallinit() {
    configHFXT();
    configLFXT();
    bluetooth_init();
    wateringInit();
    analogSensorSetup();
    RTC_Init(0, 0, 0, 0, 0, 0, 0);
    lackWater_LED_init();
    LED1_init();
    WS2812init();
    timer32Init();
    NVIC_SetPriority(RTC_C_IRQn,0);
    NVIC_SetPriority(TA0_0_IRQn,1);
    NVIC_SetPriority(ADC14_IRQn,2);
    NVIC_SetPriority(T32_INT1_IRQn,3);
    __enable_irq();
}

void overallCheck(){
    LED1_toggle();
//    moistureCheck();
//    lightCheck();

}

void tempCheck(){


}

void moistureCheck() {
    int moistureDeficit = DESIRED_MOISTURE_LEVEL - getMoisture();
    int waterNeeded = moistureDeficit * WATER_INFLUENCE_RATIO;

    if (waterNeeded > 0) {
        usedWater += waterNeeded;
        int wateringTimeSec = waterNeeded / FLOW_RATE;
        uint32_t wateringTimeTicks = TIMER32_FREQ * wateringTimeSec;

        TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;
        TIMER32_1->LOAD = wateringTimeTicks;
        wateringTurnON();
    }

    if (usedWater > WATER_TANK_CAPACITY) {
        lackWater_LED_ON();
    } else {
        lackWater_LED_OFF();
    }
}

void lightCheck() {
    int lightNeeded = DESIRED_LIGHT_INTENSITY; // Placeholder for actual light measurement logic
    if (lightNeeded > 0) {
        uint8_t brightness = (uint8_t)(lightNeeded * LIGHT_ADJUSTMENT_FACTOR);
        fill(brightness, brightness, brightness);
    }
    lightTimeHours++;
}


void timer32Init() {
    TIMER32_1->CONTROL = TIMER32_CONTROL_MODE | TIMER32_CONTROL_PRESCALE_1 |
            TIMER32_CONTROL_IE | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_ONESHOT;
    TIMER32_1->INTCLR = 1;

    NVIC_EnableIRQ(T32_INT1_IRQn);
}

void T32_INT1_IRQHandler(void) {
    TIMER32_1->INTCLR = 0; // Clear the interrupt flag
    wateringTurnOFF();
}


void main(void) {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

    overallinit();
    overallCheck();
    while (1) {
        __sleep(); // Enter low power mode until the next RTC interrupt
    }
}



