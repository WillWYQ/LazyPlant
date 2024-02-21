/*
 * LazyPlantSystem.h
 *
 *  Created on: Feb 20, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTSYSTEM_H_
#define LAZYPLANTSYSTEM_H_

#include "LazyPlantSourceFiles.h"


// Initializes all components of the LazyPlant system
void overallinit(void);

// Performs periodic checks for moisture and light
void overallCheck(void);

// Checks and manages the temperature (placeholder for future implementation)
void tempCheck(void);

// Evaluates and acts upon the plant's moisture needs
void moistureCheck(void);

// Controls the lighting based on plant needs
void lightCheck(void);

// Initializes the 32-bit timer for scheduling tasks
void timer32Init(void);

// Handles interrupts from the 32-bit timer
void T32_INT1_IRQHandler(void);

#endif // LAZYPLANTSYSTEM_H_
