/*
 * LazyPlantWatering.c
 *
 *  Created on: Feb 17, 2024
 *      Author: willwyq
 */

#include "LazyPlantWatering.h"


void wateringInit(){
    wateringRelayPort->SEL0 &= ~wateringRelayPin;
    wateringRelayPort->SEL1 &= ~wateringRelayPin;
    wateringRelayPort->DIR |= wateringRelayPin;
}

void wateringTurnON(){
    wateringRelayPort->OUT |= wateringRelayPin;
}

void wateringTurnOFF(){
    wateringRelayPort->OUT &= ~wateringRelayPin;
}


