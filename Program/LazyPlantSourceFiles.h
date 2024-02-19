/*
 * LazyPlantSourceFiles.h
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTSOURCEFILES_H_
#define LAZYPLANTSOURCEFILES_H_

//overall header
#include "msp.h"
#include <stdbool.h>

#ifndef LAZYPLANTWatering_H_
#define LAZYPLANTWatering_H_

#include "LazyPlantWatering.h"

//Watering System
#define wateringRelayPort P1
#define wateringRelayPin BIT5

#endif /* LAZYPLANTWatering_H_*/

#ifndef LAZYPLANTLED_H_
#define LAZYPLANTLED_H_

#include "rgbLED.h"

#endif /* LAZYPLANTLED_H_*/


#ifndef sensor_H_
#define sensor_H_

#define lightPin P6
#define lightBit BIT0

#define moisturePin P6
#define moistureBit BIT1

#define tempPin P5
#define tempBit BIT4
#endif


#endif /* LAZYPLANTSOURCEFILES_H_ */
