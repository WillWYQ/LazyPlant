/*
 * LazyPlantBluetooth.c
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */


#include "LazyPlantBluetooth.h"



void bluetooth_init(){
    bluetoothPort -> SEL0 |= bluetoothRXD | bluetoothTXD;                // set 2-UART pins as secondary function
    bluetoothPort -> SEL1 &= ~(bluetoothRXD | bluetoothTXD);

    EUSCI_A2 -> MCTLW  = 0;
    EUSCI_A2 -> MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A2 -> MCTLW |= (2 << 4);
    EUSCI_A2 -> BRW = 0;
    EUSCI_A2 -> BRW = 0x4E; // based on  table 24-5 BRCLK = 12000000 Baud Rate = 9600 UCBR = 78=4E OS16 =1 BRF = 2 BRS = 0

    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;    // Initialize eUSCI
    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;        // Clear eUSCI RX interrupt flag
    EUSCI_A2->IE |= EUSCI_A_IE_RXIE;            // Enable USCI_A2 RX interrupt

    NVIC_EnableIRQ(EUSCIA2_IRQn);
}
