/*
 * LazyPlantWatering.h
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTWATERING_H_
#define LAZYPLANTWATERING_H_


#include "LazyPlantSourceFiles.h"

#define wateringRelayPort P1
#define wateringRelayPin BIT5


#endif /* LAZYPLANTWATERING_H_ */

extern void wateringInit();
extern void wateringTurnON();
extern void wateringTurnOFF();
