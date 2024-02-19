/*
 * temp.c
 *
 *  Created on: Feb 18, 2024
 *      Author: zhuy16
 */
#include "msp.h"
#include "temp.h"

#include <stdlib.h>

int dht_data[DHT_DATA_SIZE] = {0, 0, 0, 0, 0};

/* DHT_init
 * sets up the DHT11 as simple IO and as an input. */
void DHT_init() {
    /* when power is supplied to the sensor, do not send any instruction to the
     * sensor in within one second in order to pass the unstable status. */

    /* set the data pin as an input with a pullup resistor */
    temp_Port -> SEL0 &= ~temp_Pin;
    temp_Port -> SEL1 &= ~temp_Pin;
    temp_Port -> DIR &= ~temp_Pin;
    temp_Port -> REN |= temp_Pin;
    temp_Port -> OUT |= temp_Pin;
}

void DHT_reset_data() {
    uint8_t i;
    for (i = 0; i < DHT_DATA_SIZE; i++) {
        dht_data[i] = 0;
    }
}

/* DHT_check_checksum
 * helper function for DHT_read_data. calculates what the checksum
 * should be and compares it to dht_data[4], which holds the checksum.
 * if they are the same, returns TRUE, else, returns FALSE. */
uint8_t DHT_check_checksum() {
    uint32_t dht_data_added = 0;
    uint8_t i;

    /* sum up the values to compare to our checksum */
    for (i = 0; i < DHT_DATA_SIZE-1; i++) {
        dht_data_added += dht_data[i];
    }
    dht_data_added &= 0xFF;

    /* check that all data was populated and checksum equals our sum */
    if (dht_data[DHT_CHECKSUM_INDEX] == dht_data_added) {
        return GOOD_DATA;
    }
    return BAD_DATA;
}

/* DHT_read_from_sensor
 * helper function for DHT_read_data */
void DHT_read_from_sensor() {
    uint8_t last_state = temp_Pin;
    uint8_t count = 0;
    uint8_t i = 0;
    uint8_t j = 0;

    /* detect change and read data */
    for (i=0; i < MAX_TIME; i++) {
        count = 0;

        /* count up while nothing has changed */
        while ((temp_Port -> IN & temp_Pin) == last_state) {
            count++;
            /* if we have delayed the max time, there was no change */
            if (count == MAX_COUNT) {
                break;
            }
        }

        /* read in the current input value */
        last_state = temp_Port -> IN & temp_Pin;

        if (count == MAX_COUNT) {
            break;
        }

        /* ignore the first 3 transitions, take in every other (when the DHT11
         * goes high, this is the data we care about) */
        if ((i >= 4) && (i % 2 == 0)) {
            /* shift everything so we are inputted the current bit being sent.
             * if the output was high for a certain amount of time, set this
             * bit high */
            dht_data[j / DHT_INDEX_SIZE] <<= 1;

            if (count > HIGH_BIT_COUNT)
                dht_data[j / DHT_INDEX_SIZE] |= 1;
            j++;
        }
    }
}

/* DHT_read_data
 * populates global array of size 5, or NULL on failure.
 * data will be as follows:
 * index 0 will hold integral humidity data
 * index 1 will hold decimal humidity data
 * index 2 will hold integral temperature data
 * index 3 will hold decimal temperature data
 * index 4 will be the checksum (already checked) */
void DHT_read_data() {
    DHT_reset_data();

    /* set the pin as an output and pull down pin for at least 18 ms */
    temp_Port -> DIR |= temp_Pin;
    temp_Port -> OUT &= ~temp_Pin;

    /* pull the pin up for 20-40us to wait for the sensor's response */
    temp_Port -> OUT |= temp_Pin;

    /* set the pin as an input to prepare for reading. */
    temp_Port -> DIR &= ~temp_Pin;

    /* read bits from the sensor, and populate dht_data */
    DHT_read_from_sensor();
}

