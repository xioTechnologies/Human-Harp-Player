/*
 * File:   SystemClock.h
 * Author: Seb Madgwick
 */

#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

//------------------------------------------------------------------------------
// Definitions

#define FOSC    140000000ul
#define FP      (FOSC >> 1)
#define FCY     FP // valid only for DOZE = 0

#endif

//------------------------------------------------------------------------------
// End of file
