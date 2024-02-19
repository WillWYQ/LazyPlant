/*
 * sensorsetup.c
 *
 *  Created on: Feb 18, 2024
 *      Author: zhuy16
 */
#include <All_header.h>

static volatile uint16_t light;
static volatile uint16_t moisture;
static volatile uint16_t temp;
static volatile bool resultReady = false;

void setup(){
    volatile int i;
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;


    lightPin->DIR &= ~lightBit;
    lightPin->SEL0 |= lightBit;
    lightPin->SEL1 |= lightBit;

    moisturePin->DIR &= ~moistureBit;
    moisturePin->SEL0 |= moistureBit;
    moisturePin->SEL1 |= moistureBit;

    tempPin->DIR &= ~tempBit;
    tempPin->SEL0 |= tempBit;
    tempPin->SEL1 |= tempBit;

    /* Configure ADC (CTL0 and CTL1) registers for:
     *      clock source - default MODCLK, clock prescale 1:1,
     *      sample input signal (SHI) source - software controlled (ADC14SC),
     *      Pulse Sample mode with sampling period of 16 ADC14CLK cycles,
     *      Single-channel, single-conversion mode, 12-bit resolution,
     *      ADC14 conversion start address ADC14MEM1, and Low-power mode
     */
    ADC14->CTL0 = ADC14_CTL0_SHP        // Pulse Sample Mode
            | ADC14_CTL0_SHT0__16       // 16 cycle sample-and-hold time (for ADC14MEM1)
            | ADC14_CTL0_PDIV__1        // Predivide by 1
            | ADC14_CTL0_DIV__1         // /1 clock divider
            | ADC14_CTL0_SHS_0          // ADC14SC bit sample-and-hold source select
            | ADC14_CTL0_SSEL__MODCLK   // clock source select MODCLK
            | ADC14_CTL0_CONSEQ_1
            | ADC14_CTL0_ON;            // ADC14 on

    ADC14->CTL0 |= ADC14_CTL0_MSC;

    ADC14->CTL1 = ADC14_CTL1_RES__12BIT         // 12-bit conversion results
            | (0x1 << ADC14_CTL1_CSTARTADD_OFS) // ADC14MEM1 - conversion start address
            | ADC14_CTL1_PWRMD_2;               // Low-power mode

    //Single-ended mode with Vref+ = Vcc and Vref- = Vss,
    //Input channel - A1, and comparator window disabled
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_15;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_14;
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_1;

    //Enable ADC conversion complete interrupt for ADC14MEM1
    ADC14->IER0 = ADC14_IER0_IE1;
    ADC14->IER0 = ADC14_IER0_IE1;
    ADC14->IER0 = ADC14_IER0_IE1;


    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = (1 << ADC14_IRQn);

    // Enable global interrupt
    __enable_irq();

}

void oneSample(){
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
}


void ADC14_IRQHandler(void) {
    // Check if interrupt triggered by ADC14MEM1 conversion value loaded
    //  Not necessary for this example since only one ADC channel used
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1) {
           light = ADC14->MEM[1];
           printf("light %d\n", light);
    }
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1) {
        moisture = ADC14->MEM[2];
        printf("moisture %d\n", moisture);
    }
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1){
        temp = ADC14->MEM[3];
        printf("tempature %d\n",temp);
    }
    ADC14->CLRIFGR0 |= ADC14_IFGR0_IFG1;
}
