/*
 * LazyPlantBluetooth.c
 *
 *  Created on: Feb 19, 2024
 *      Author: willwyq
 */


#include "LazyPlantBluetooth.h"



void bluetooth_init(){
    // Configure UART pins for Bluetooth module
    bluetoothPort -> SEL0 |= bluetoothRXD | bluetoothTXD;
    bluetoothPort -> SEL1 &= ~(bluetoothRXD | bluetoothTXD);

    // Setup UART configuration: 9600 baud rate, 8N1 format, Asynchronous UART mode
    // based on  table 24-5 BRCLK = 12000000 Baud Rate = 9600 UCBR = 78=4E OS16 =1 BRF = 2 BRS = 0
    EUSCI_A2 -> MCTLW  = 0;
    EUSCI_A2 -> MCTLW |= EUSCI_A_MCTLW_OS16;
    EUSCI_A2 -> MCTLW |= (2 << 4);
    EUSCI_A2 -> BRW = 0;
    EUSCI_A2 -> BRW = 0x4E;

    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;    // Initialize eUSCI
    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;        // Clear eUSCI RX interrupt flag
    EUSCI_A2->IE |= EUSCI_A_IE_RXIE;            // Enable USCI_A2 RX interrupt

    NVIC_EnableIRQ(EUSCIA2_IRQn);
}

// Send a message over Bluetooth
void printMessage(const char* message, int msgLength) {
    int i;
    for (i = 0; i < msgLength; i++) {
        while (!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG)); // Wait for TX buffer to be ready
        EUSCI_A2->TXBUF = message[i]; // Transmit character
    }
}

// Test function to send a single character 'U'
void testBluetooth() {
    const char prompt[] = "U"; // Changed to a string to match printMessage's signature
    printMessage(prompt, 1); // Send a single character
}


// UART interrupt service routine
void EUSCIA2_IRQHandler(void) {
    // Check if the receive interrupt flag (RXIFG) is set
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG) {
        // Clear the receive interrupt flag
        EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;

        // Read the received data
        uint8_t receivedData = EUSCI_A2->RXBUF;

        // Process the received data
        processReceivedData(receivedData);

        // Optionally, you can echo the received data back for testing
        while (!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG)); // Wait for TX buffer to be ready
        EUSCI_A2->TXBUF = receivedData; // Echo received data
    }
}

// Function to process received data (to be implemented)
void processReceivedData(uint8_t data) {
}
