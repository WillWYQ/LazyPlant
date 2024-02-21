/*
 * LazyPlantWarning.c
 *
 *  Created on: Feb 20, 2024
 *      Author: willwyq
 */
#include "LazyPlantWarning.h"

// Initializes the GPIO pin connected to the lack-of-water LED
void lackWater_LED_init(void) {
    // Set the LED pin as output
    lackWaterPORT->DIR |= lackWaterPIN;
    // Ensure the LED pin functions as a GPIO
    lackWaterPORT->SEL0 &= ~lackWaterPIN;
    lackWaterPORT->SEL1 &= ~lackWaterPIN;
    // Initialize the LED to be off
    lackWaterPORT->OUT &= ~lackWaterPIN;
}

// Turns on the lack-of-water LED
void lackWater_LED_ON() {
    lackWaterPORT->OUT |= lackWaterPIN; // Set the LED pin high to turn on the LED
}

// Turns off the lack-of-water LED
void lackWater_LED_OFF() {
    lackWaterPORT->OUT &= ~lackWaterPIN; // Clear the LED pin to turn off the LED
}
