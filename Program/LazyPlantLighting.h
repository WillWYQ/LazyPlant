/*
 * LazyPlantLighting.h
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTLIGHTING_H_
#define LAZYPLANTLIGHTING_H_

#include "LazyPlantSourceFiles.h"

#define SMLCK 12000000
#define frameRESTTicks 3600 // Divide[1,12*Power[10,6]]*X = 300*Power[10,-6]

// Define GPIO pins and port for SPI communication
#define SPI_PORT    P2          // SPI port definition
#define STE_PIN     BIT0        // Slave Trigger Enable - not used in WS2812 but included for completeness
#define CLK_PIN     BIT1        // Clock pin for SPI
#define MOSI_PIN    BIT3        // Master Out Slave In pin for SPI

// Define codes for WS2812 bit representation
#define HIGH_CODE   (0b11111110)  // High bit representation for WS2812
#define LOW_CODE    (0b11100000)  // Low bit representation for WS2812

#define NUM_LEDS    241           // Number of WS2812 LEDs


// SPI and GPIO initialization for WS2812 control
void SPIGPIOinit(void);

// SPI module initialization for WS2812 control
void SPIinit(void);

// Send a byte via SPI
void SPISend(uint8_t WriteData);

// Timer initialization for controlling WS2812 timing
void timerInit(void);

// Initialization of WS2812 LEDs
void WS2812init(void);

// Process and prepare the bits for SPI transmission based on WS2812 protocol
uint8_t WS2812bitProcessing(bool in);

// Fill the LEDs with a specified color
void fill(uint8_t R, uint8_t G, uint8_t B);

// Timer A0 interrupt handler for WS2812 timing
void TA0_0_IRQHandler(void);

void delay_cycles(unsigned int count);

#endif /* LAZYPLANTLIGHTING_H_ */
