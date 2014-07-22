/*
 * File:   Led.h
 * Author: Seb Madgwick
 */

#ifndef LED_H
#define LED_H

//------------------------------------------------------------------------------
// Definitions

typedef enum {
    BLINK_ONCE,
    FAST_FLASH_FOR_3_SECONDS,
    SLOW_FLASH_FOR_3_SECONDS,
} LED_EVENT;

//------------------------------------------------------------------------------
// Function declarations

void LedInitialise();
void LedDoTasks();
void LedTriggerEvent(LED_EVENT ledEvent);
void LedOn();
void LedOff();

#endif

//------------------------------------------------------------------------------
// End of file
