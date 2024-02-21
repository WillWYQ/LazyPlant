/*
 * LazyPlantAnalogSensor.h
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */

#ifndef LAZYPLANTANALOGSENSOR_H_
#define LAZYPLANTANALOGSENSOR_H_

#include "LazyPlantSourceFiles.h"

#define lightPin P6
#define lightBit BIT0

#define moisturePin P6
#define moistureBit BIT1

#define tempPin P5
#define tempBit BIT4


// Initializes ADC and configures pins for light, moisture, and temperature sensors
void analogSensorSetup(void);

// Starts a single ADC sample-and-convert sequence
void oneSample(void);

// Starts the ADC, enabling conversions
void startADC(void);

// Stops the ADC, disabling conversions
void stopADC(void);

// Retrieves the latest light sensor measurement
// Returns: 16-bit unsigned integer value representing light intensity
uint16_t getLight(void);

// Retrieves the latest moisture sensor measurement
// Returns: 16-bit unsigned integer value representing moisture level
uint16_t getMoisture(void);

// ADC14 interrupt service routine to handle conversion results
void ADC14_IRQHandler(void);


#endif /* LAZYPLANTANALOGSENSOR_H_ */
