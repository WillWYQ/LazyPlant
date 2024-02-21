/*
 * LazyPlantWatering.c
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */

#include "LazyPlantWatering.h"

// Initialize the GPIO pin connected to the watering relay
void wateringInit() {
    // Configure the relay pin as a general-purpose output
    wateringRelayPort->SEL0 &= ~wateringRelayPin; // Clear SEL0 to select GPIO function
    wateringRelayPort->SEL1 &= ~wateringRelayPin; // Clear SEL1 to select GPIO function
    wateringRelayPort->DIR |= wateringRelayPin;   // Set the relay pin as an output
}

// Turn the watering relay on
void wateringTurnON() {
    wateringRelayPort->OUT |= wateringRelayPin; // Set the relay pin high to turn the relay on
}

// Turn the watering relay off
void wateringTurnOFF() {
    wateringRelayPort->OUT &= ~wateringRelayPin; // Clear the relay pin to turn the relay off
}
