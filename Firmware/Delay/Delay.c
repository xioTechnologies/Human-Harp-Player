/*
 * File:   Delay.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "SystemClock.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Functions

void Delay(unsigned int milliseconds) {
    T1CON = 0x8000; // enable TMR1 with 1:1 prescalar
    while (milliseconds--) {
        TMR1 = 0;
        while (TMR1 < (FCY / 2000)); // wait 500 us
        TMR1 = 0;
        while (TMR1 < (FCY / 2000)); // wait 500 us
    }
}

//------------------------------------------------------------------------------
// End of file
