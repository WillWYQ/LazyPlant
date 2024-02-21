/*
 * sensorsetup.c
 *
 *  Created on: Feb 18, 2024
 *      Author: zhuy16
 */
#include "LazyPlantAnalogSensor.h"

static volatile uint16_t light;
static volatile uint16_t moisture;
static volatile bool lightReady = false, moistureReady = false;

void analogSensorSetup() {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stop watchdog timer

    // Configure sensor pins for ADC input
    lightPin->DIR &= ~lightBit;
    lightPin->SEL0 |= lightBit;
    lightPin->SEL1 |= lightBit;

    moisturePin->DIR &= ~moistureBit;
    moisturePin->SEL0 |= moistureBit;
    moisturePin->SEL1 |= moistureBit;

    // ADC14 configuration
    ADC14->CTL0 = ADC14_CTL0_SHP        // Pulse Sample Mode
                | ADC14_CTL0_SHT0__16   // 16 cycle sample-and-hold time
                | ADC14_CTL0_ON         // ADC14 on
                | ADC14_CTL0_MSC;       // Multiple sample and conversion

    ADC14->CTL1 = ADC14_CTL1_RES__12BIT; // 12-bit conversion results

    // Configure memory control registers for light and moisture channels
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15; // Light sensor on A15
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_EOS; // Moisture sensor on A14, mark as end of sequence

    // Enable ADC conversion complete interrupt for both sensors
    ADC14->IER0 = ADC14_IER0_IE1; // Only need to enable interrupt for the last conversion in a sequence

    NVIC_EnableIRQ(ADC14_IRQn); // Enable ADC interrupt in NVIC module
}

void oneSample() {
    // Start a single ADC sample-and-convert sequence
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
}

void startADC() {
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC | ADC14_CTL0_ON;
}

void stopADC() {
    ADC14->CTL0 &= ~ADC14_CTL0_ON;
}

uint16_t getLight() {
    lightReady = false;
    startADC();
    while (!lightReady); // Wait for light measurement to be ready
    stopADC();
    return light;
}

uint16_t getMoisture() {
    moistureReady = false;
    startADC();
    while (!moistureReady); // Wait for moisture measurement to be ready
    stopADC();
    return moisture;
}

void ADC14_IRQHandler(void) {
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG0) { // Light sensor interrupt
        light = ADC14->MEM[0];
        lightReady = true;
    }
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1) { // Moisture sensor interrupt
        moisture = ADC14->MEM[1];
        moistureReady = true;
    }

    // Clear interrupt flags
    ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0 | ADC14_CLRIFGR0_CLRIFG1;
}
