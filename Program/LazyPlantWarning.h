/*
 * LazyPlantWarning.h
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTWARNING_H_
#define LAZYPLANTWARNING_H_

#include "LazyPlantSourceFiles.h"

// Define the GPIO port and pin for the water deficiency indicator LED
#define lackWaterPORT P4
#define lackWaterPIN BIT6

void lackWater_LED_init(void);
void lackWater_LED_ON();
void lackWater_LED_OFF();

#endif /* LAZYPLANTWARNING_H_ */
