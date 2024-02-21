/*! \file */
/*!
 * rgbLED.h
 *
 * Description: RGB driver for LED2 on MSP432P4111 Launchpad
 *
 *  Created on:
 *      Author:
 */

#ifndef LAZYPLANTRGBLED_H_
#define LAZYPLANTRGBLED_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "LazyPlantSourceFiles.h"

#define RGB_PORT                                            P2
#define RGB_RED_PIN                                         (0x0001)
#define RGB_GREEN_PIN                                       (0x0002)
#define RGB_BLUE_PIN                                        (0x0004)
#define RGB_ALL_PINS                                        (0x0007)

typedef enum _Colors {
    BLACK,          /* (0x0000) */
    RED,            /* (0x0001) */
    GREEN,          /* (0x0002) */
    YELLOW,         /* (0x0003) */
    BLUE,           /* (0x0004) */
    MAGENTA,        /* (0x0005) */
    CYAN,           /* (0x0006) */
    WHITE           /* (0x0007) */
} Colors;

/*!
 * \brief Turn off all LEDs
 */
extern void offAllLED(void);

/*!
 * \brief Update LED states based on parameters
 *
 * \param onoff Boolean indicating whether the LEDs should be turned on or off
 * \param RGB Boolean indicating whether RGB LEDs or LED1 should be controlled
 * \param state Integer representing the state of the LEDs (used for RGB)
 */
extern void updateLED(bool onoff, bool RGB, short state);

/*!
 * \brief Initialize LED1
 */
extern void LED1_init(void);

/*!
 * \brief Toggle LED1 state
 */
extern void LED1_toggle(void);

/*!
 * \brief Turn on LED1
 */
extern void LED1ON(void);

/*!
 * \brief Turn off LED1
 */
extern void LED1OFF(void);

/*!
 * \brief Initialize RGB LEDs
 */
extern void RGBLED_init(void);

/*!
 * \brief Toggle the red component of RGB LEDs
 */
extern void RGBLED_toggleRed(void);

/*!
 * \brief Turn on the red component of RGB LEDs
 */
extern void REDON(void);

/*!
 * \brief Toggle the green component of RGB LEDs
 */
extern void RGBLED_toggleGreen(void);

/*!
 * \brief Turn on the green component of RGB LEDs
 */
extern void GREENON(void);

/*!
 * \brief Toggle the blue component of RGB LEDs
 */
extern void RGBLED_toggleBlue(void);

/*!
 * \brief Turn on the blue component of RGB LEDs
 */
extern void BLUEON(void);

/*!
 * \brief Turn off the red component of RGB LEDs
 */
extern void REDOFF(void);

/*!
 * \brief Turn off the green component of RGB LEDs
 */
extern void GREENOFF(void);

/*!
 * \brief Turn off the blue component of RGB LEDs
 */
extern void BLUEOFF(void);

/*!
 * \brief Turn off all components of LEDs
 */
extern void ALLOFF(void);

/*!
 * \brief Set the color of RGB LEDs
 *
 * \param color Enumeration representing the desired color
 */
extern void RGBLED_setColor(Colors color);

/*!
 * \brief Initialize specified LED
 *
 * \param led Integer representing the LED to be initialized (1 for LED1, 2 for RGBLED)
 */
extern void LED_init(short led);



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* LAZYPLANTRGBLED_H_ */
