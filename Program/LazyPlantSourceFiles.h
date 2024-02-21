#ifndef LAZYPLANTSOURCEFILES_H_
#define LAZYPLANTSOURCEFILES_H_

// Include MSP432 specific headers and standard libraries
#include "msp.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

// System-wide definitions
#define SMCLK_FREQUENCY 12000000 // Use a more descriptive name for SMCLK

#define TIMER32_FREQ 3000000
#define WATER_TANK_CAPACITY 500 // in mL
#define DESIRED_MOISTURE_LEVEL 1000
#define WATER_INFLUENCE_RATIO 30
#define FLOW_RATE 20 // in mL/s
#define DESIRED_LIGHT_INTENSITY 3000
#define LIGHT_ADJUSTMENT_FACTOR (255.0 / DESIRED_LIGHT_INTENSITY)

// RTC definitions
#define WAKE_UP_FROM_ALARM 0
#define WAKE_UP_FROM_TIME_EVENT 1 // For project demonstration purposes

#include "LazyPlantRTC.h"
#include "LazyPlantWatering.h"
#include "LazyPlantBluetooth.h"
#include "LazyPlantSystem.h"
#include "LazyPlantWarning.h"
#include "LazyPlantLighting.h"
#include "LazyPlantAnalogSensor.h"
#include "LazyPlantcsHFXT.h"
#include "LazyPlantcsLFXT.h"
#include "LazyPlantrgbLED.h"



#endif // LAZYPLANTSOURCEFILES_H_
