/*
 * LazyPlantSourceFiles.h
 *
 * Created on: Feb 17, 2024
 * Author: willwyq
 */

#ifndef LAZYPLANTSOURCEFILES_H_
#define LAZYPLANTSOURCEFILES_H_

// Overall header
#include "msp.h"
#include <stdbool.h>
#include <stdio.h>  // For snprintf and printf

//RTC
#ifndef RTC_H_
#define RTC_H_

#endif

// Watering System
#ifndef LAZYPLANTWATERING_H_
#define LAZYPLANTWATERING_H_

#include "LazyPlantWatering.h"

#endif // LAZYPLANTWATERING_H_

// LED
#ifndef LAZYPLANTLED_H_
#define LAZYPLANTLED_H_

#include "rgbLED.h"

#endif // LAZYPLANTLED_H_

// Sensors
#ifndef SENSOR_H_
#define SENSOR_H_

#define lightPin P6
#define lightBit BIT0

#define moisturePin P6
#define moistureBit BIT1

#define tempPin P5
#define tempBit BIT4

#endif // SENSOR_H_

// Bluetooth
#ifndef LAZYPLANTBLUETOOTH_H_
#define LAZYPLANTBLUETOOTH_H_

#include "LazyPlantBluetooth.h"

#endif // LAZYPLANTBLUETOOTH_H_


#endif /* LAZYPLANTSOURCEFILES_H_ */
