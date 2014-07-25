/*
 * File:   Button.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Button.h"
#include "Encoder/Encoder.h"
#include "GenericTypeDefs.h"
#include "Imu/Imu.h"
#include "Led/Led.h"
#include "Send/Send.h"
#include "SleepTimer/SleepTimer.h"
#include "Uart/Uart1.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define BUTTON_PIN (!_RC1)

//------------------------------------------------------------------------------
// Functions

void ButtonInitialise() {
    _INT2EP = 1; // interrupt on negative edge, i.e. when button pressed
    _INT2IP = 2; // set interrupt priority
    _INT2IF = 0; // clear interrupt flag
    _INT2IE = 1; // enable interrupt
}

void ButtonDoTasks() {

    // Disable sleep timer if button held when device switched on
    if (_POR && BUTTON_PIN) {
        SleepTimerDisable();
        LedTriggerEvent(FAST_FLASH_FOR_3_SECONDS);
        return;
    }
    _POR = 0;

    // Zero and reset sleep timer if button pressed or data received from host
    if (BUTTON_PIN || Uart1IsGetReady() > 0) {
        Uart1ClearRxBuffer();
        SleepTimerRestart();
        EncoderZero();
        ImuZero();
        LedTriggerEvent(BLINK_ONCE);
        SendZero();
    }
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __attribute__((interrupt, auto_psv))_INT2Interrupt(void) {
    SleepTimerRestart();
    _INT2IF = 0; // clear interrupt flag
}

//------------------------------------------------------------------------------
// End of file
