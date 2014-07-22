/*
 * File:   Led.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay/Delay.h"
#include "GenericTypeDefs.h"
#include "Led.h"
#include "SystemClock.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define LED_PIN _LATA4

//------------------------------------------------------------------------------
// Variables

LED_EVENT currentEvent;
static unsigned char eventCountdown;

//------------------------------------------------------------------------------
// Functions

void LedInitialise() {
    T2CONbits.TCKPS = 0b11; // 1:256 prescaler
    PR2 = (int) (FP / 256ul / 20ul); // 50 ms period
    T2CONbits.TON = 1; // start timer
}

void LedDoTasks() {
    if (_T2IF) {
        _T2IF = 0;
        if (eventCountdown > 0) {
            switch (currentEvent) {
                case BLINK_ONCE:
                    LED_PIN = (eventCountdown & 0x04) ? 1 : 0;
                    break;
                case FAST_FLASH_FOR_3_SECONDS:
                    LED_PIN = (eventCountdown & 0x01) ? 1 : 0;
                    break;
                case SLOW_FLASH_FOR_3_SECONDS:
                    LED_PIN = (eventCountdown & 0x08) ? 1 : 0;
                    break;
                default:
                    break;
            }
            eventCountdown--;
        } else {
            LED_PIN = 1;
        }
    }
}

void LedTriggerEvent(LED_EVENT newEvent) {
    if (eventCountdown > 0) {
        return; // discard if busy
    }
    switch (newEvent) {
        case BLINK_ONCE:
            eventCountdown = 7;
            break;
        case FAST_FLASH_FOR_3_SECONDS:
        case SLOW_FLASH_FOR_3_SECONDS:
            eventCountdown = 60;
            break;
        default:
            break;
    }
    currentEvent = newEvent;
}

void LedOn() {
    LED_PIN = 1;
    eventCountdown = 0;
}

void LedOff() {
    LED_PIN = 0;
    eventCountdown = 0;
}

//------------------------------------------------------------------------------
// End of file
