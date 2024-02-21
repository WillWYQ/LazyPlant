/*!
 * \file
 * \brief rgbLED.c
 *
 * \author Yueqiao Wang
 * \date Dec 21, 2023
 *
 * \brief Description: LED driver for LEDs on MSP432P4111 Launchpad
 */


#include <LazyPlantrgbLED.h>


#define LED1PIN BIT0

void offAllLED(void);
void updateLED(bool onoff, bool RGB, short state);
void LED1_init(void);

/*!
 * \brief Turn off all LEDs
 */
void offAllLED(void) {
    P1->OUT &= ~LED1PIN;
    P2->OUT &= ~RGB_ALL_PINS;
}

/*!
 * \brief Update LED states based on parameters
 *
 * \param onoff Boolean indicating whether the LEDs should be turned on or off
 * \param RGB Boolean indicating whether RGB LEDs or LED1 should be controlled
 * \param state Integer representing the state of the LEDs (used for RGB)
 */
void updateLED(bool onoff, bool RGB, short state) {
    if (onoff) {
        offAllLED();
        if (RGB) {
            switch (state) {
                case 0:
                    REDON();
                    break;
                case 1:
                    GREENON();
                    break;
                case 2:
                    BLUEON();
                    break;
            };
        } else {
            LED1ON();
        }
    } else {
        offAllLED();
    }
}

/*!
 * \brief Initialize LED1
 */
void LED1_init(void) {
    P1->DIR |= LED1PIN;
    P1->SEL0 &= ~LED1PIN;
    P1->SEL1 &= ~LED1PIN;
    P1->OUT &= ~LED1PIN;
}

/*!
 * \brief Toggle LED1 state
 */
void LED1_toggle(void) {
    P1->OUT ^= LED1PIN;
}

/*!
 * \brief Turn on LED1
 */
void LED1ON() {
    P1->OUT |= LED1PIN;
}
void LED1OFF() {
    P1->OUT &= ~LED1PIN;
}

/*!
 * \brief Initialize RGB LEDs
 */
void RGBLED_init(void) {
    P2->DIR |= RGB_ALL_PINS;
    P2->SEL0 &= ~RGB_ALL_PINS;
    P2->SEL1 &= ~RGB_ALL_PINS;
    P2->OUT &= ~RGB_ALL_PINS;
}

/*!
 * \brief Toggle the red component of RGB LEDs
 */
void RGBLED_toggleRed(void) {
    P2->OUT ^= RGB_RED_PIN;
}

/*!
 * \brief Turn on the red component of RGB LEDs
 */
void REDON(void) {
    P2->OUT |= RGB_RED_PIN;
}

/*!
 * \brief Toggle the green component of RGB LEDs
 */
void RGBLED_toggleGreen(void) {
    P2->OUT ^= RGB_GREEN_PIN;
}

/*!
 * \brief Turn on the green component of RGB LEDs
 */
void GREENON(void) {
    P2->OUT |= RGB_GREEN_PIN;
}

/*!
 * \brief Toggle the blue component of RGB LEDs
 */
void RGBLED_toggleBlue(void) {
    P2->OUT ^= RGB_BLUE_PIN;
}

/*!
 * \brief Turn on the blue component of RGB LEDs
 */
void BLUEON(void) {
    P2->OUT |= RGB_BLUE_PIN;
}

/*!
 * \brief Turn off the red component of RGB LEDs
 */
void REDOFF(void) {
    P2->OUT &= ~RGB_RED_PIN;
}

/*!
 * \brief Turn off the green component of RGB LEDs
 */
void GREENOFF(void) {
    P2->OUT &= ~RGB_GREEN_PIN;
}

/*!
 * \brief Turn off the blue component of RGB LEDs
 */
void BLUEOFF(void) {
    P2->OUT &= ~RGB_BLUE_PIN;
}

/*!
 * \brief Turn off all components of  LEDs
 */
void ALLOFF(void) {
    LED1OFF();
    P2->OUT &= ~(RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN);
}



/*!
 * \brief Set the color of RGB LEDs
 *
 * \param color Enumeration representing the desired color
 */
void RGBLED_setColor(Colors color) {
    if (color <= WHITE) {
        P2->OUT = (P2->OUT & ~RGB_ALL_PINS) | color;
    }
}

/*!
 * \brief Initialize specified LED
 *
 * \param led Integer representing the LED to be initialized (1 for LED1, 2 for RGBLED)
 */
void LED_init(short led) {
    switch (led) {
        case 1:
            LED1ON();
            break;
        case 2:
            RGBLED_init();
            break;
        default:
            break;
    }
}
