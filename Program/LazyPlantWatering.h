/*
 * LazyPlantWatering.h
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTWATERING_H_
#define LAZYPLANTWATERING_H_

#include "LazyPlantSourceFiles.h"

// Define the GPIO port and pin for the watering relay control
#define wateringRelayPort P1
#define wateringRelayPin BIT5

// Initializes the GPIO pin for the watering relay
void wateringInit();

// Turns the watering relay on
void wateringTurnON();

// Turns the watering relay off
void wateringTurnOFF();

#endif /* LAZYPLANTWATERING_H_ */
