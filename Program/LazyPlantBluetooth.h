/*
 * LazyPlantBluetooth.h
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */
#ifndef LAZYPLANTBLUETOOTH_H_
#define LAZYPLANTBLUETOOTH_H_

#include "LazyPlantSourceFiles.h"

// Define constants for Bluetooth module
#define bluetoothPort P3
#define bluetoothRXD BIT2
#define bluetoothTXD BIT3

// Function prototypes
extern void bluetooth_init(void);
extern void printMessage(const char* message, int msgLength);
extern void processReceivedData(uint8_t data);
extern void testBluetooth(void);


#endif /* LAZYPLANTBLUETOOTH_H_ */
