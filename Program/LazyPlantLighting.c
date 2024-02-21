/*
 * LazyPlantLighting.c
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */
#include "LazyPlantLighting.h"

/*
 * use  MSB, 8bit, 3 Pin, Synchronous
 */

bool delayFlag = false;

//void main(void)
//{
//    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
//    configHFXT();
//    WS2812init();
//    __enable_irq();
//    fill(0xFF,0xFF,0xFF);
//    while(1){
//        fill(0xFF,0xFF,0xFF);
//    }
//
//}

// Initializes GPIO pins for SPI communication
void SPIGPIOinit() {
    // Set clock and MOSI pins as output
    SPI_PORT->DIR |= (CLK_PIN | MOSI_PIN); // Set as output
    SPI_PORT->SEL0 |= (CLK_PIN | MOSI_PIN); // Set function select to primary module function (SPI)
    SPI_PORT->SEL1 &= ~(CLK_PIN | MOSI_PIN); // Ensure SEL1 is cleared for SPI functionality
}

// Initializes the EUSCI module for SPI Communication
void SPIinit() {
    EUSCI_A1->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset state to configure
    // Configure for SPI: MSB first, 8-bit, master, synchronous, 3-pin mode, SMCLK
    EUSCI_A1->CTLW0 = EUSCI_A_CTLW0_MSB | EUSCI_A_CTLW0_SYNC | EUSCI_A_CTLW0_SSEL__SMCLK | EUSCI_A_CTLW0_UCSSEL_2 | EUSCI_A_CTLW0_MST;
    EUSCI_A1->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Release for operation
}

// Sends a byte via SPI
void SPISend(uint8_t WriteData) {
    while (!(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG)); // Wait for TX buffer to be ready
    EUSCI_A1->TXBUF = WriteData; // Send data
}

// Initializes timer for delays between LED updates
void timerInit() {
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__STOP; // Use SMCLK, stop mode
    TIMER_A0->CCR[0] = frameRESTTicks; // Set CCR0 for delay
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // Enable CCR0 interrupt
    NVIC_EnableIRQ(TA0_0_IRQn); // Enable Timer A0 interrupt in NVIC
}


//void DMAinit(){
//    DMA
//
//}

// Initializes the SPI, GPIO, and Timer for WS2812 LED control
void WS2812init() {
    SPIGPIOinit();
    SPIinit();
    timerInit();
}


// Processes each bit of color components to SPI format
uint8_t WS2812bitProcessing(bool in) {
    return in ? HIGH_CODE : LOW_CODE;
}

void prepareColor(uint8_t R, uint8_t G, uint8_t B, uint8_t *SPIcolor) {
    int i;
    for (i = 0; i < 8; i++) {
        SPIcolor[i] = WS2812bitProcessing((G >> i) & 1); // Get the i-th bit of G
        SPIcolor[i + 8] = WS2812bitProcessing((R >> i) & 1); // Get the i-th bit of R
        SPIcolor[i + 16] = WS2812bitProcessing((B >> i) & 1); // Get the i-th bit of B
    }
}


// Prepares and sends colors to a single WS2812 LED
void fill(uint8_t R, uint8_t G, uint8_t B) {
    uint8_t colors[3] = {G, R, B}; // GRB format for WS2812
    unsigned int i;
    for (i = 0; i < NUM_LEDS; i++) {
        __disable_irq(); // Disable interrupts to ensure timing
        unsigned int j;
        for (j = 0; j < 3; j++) { // For each color component
            uint8_t component = colors[j];
            int bit;
            for ( bit = 7; bit >= 0; bit--) { // MSB first
                while (EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG != EUSCI_A_IFG_TXIFG);
                EUSCI_A1->TXBUF = ((component & (1 << bit)) ? HIGH_CODE : LOW_CODE);
            }
        }
        __enable_irq(); // Re-enable interrupts

        // Delay to latch the color
        TIMER_A0->CTL |= TIMER_A_CTL_MC__UP; // Start timer in up mode
        delayFlag = true;
        while (delayFlag); // Wait for timer interrupt
    }
}


void delay_cycles(unsigned int count) {
    unsigned int index;
    for(index=0; index<count; index++) { }
}

// Timer A0 interrupt handler for timing between LEDs
void TA0_0_IRQHandler(void) {
    delayFlag = false; // Clear delay flag
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC__UP; // Stop timer
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // Clear interrupt flag
}

