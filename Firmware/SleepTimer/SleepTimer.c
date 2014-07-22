/*
 * File:   SleepTimer.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay/Delay.h"
#include "Encoder/Encoder.h"
#include "GenericTypeDefs.h"
#include "Imu/Imu.h"
#include "Led/Led.h"
#include "Send/Send.h"
#include "SleepTimer.h"
#include "SystemClock.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define SLEEP_TIMER         300 // seconds
#define ENCODER_ENABLE_PIN  _LATA9
#define IMU_ENABLE_PIN      _LATB5
#define X_OSC_ENABLE_PIN    _LATB9

//------------------------------------------------------------------------------
// Functions

void SleepTimerInitialise() {
    T4CONbits.T32 = 1; // TMR4 and TMR4 form a 32-bit timer
    T4CONbits.TCKPS = 0b11; // 1:256 prescaler
    T4CONbits.TON = 1; // start timer
}

void SleepTimerDoTasks() {

    // Restart sleep timer if motion detected
    long newPosition = EncoderGetPostion();
    static long oldPosition = 0;
    if (newPosition != oldPosition) {
        SleepTimerRestart();
    }
    oldPosition = newPosition;

    // If sleep timer expired
    DWORD_VAL timer;
    timer.word.LW = TMR4;
    timer.word.HW = TMR5HLD;
    if (timer.Val > (SLEEP_TIMER * (FP >> 8))) {

        // Indicate sleep timer expired
        SendSleep();
        Delay(100); // wait for send to complete

        // Switch off modules
        LedOff();
        _RP40R = 0; // unmap RB8 (RP40) to prevent current flow to x-OSC input 1
        X_OSC_ENABLE_PIN = 0;
        ENCODER_ENABLE_PIN = 0;
        IMU_ENABLE_PIN = 0;

        // Enable watch dog timer
        _SWDTEN = 1;

        // Sleep cycle
        do {

            // Enter sleep mode (will wake up on button press or watch dog timeout)
            Sleep();

            // Switch on LED and encoder
            LedOn();
            ENCODER_ENABLE_PIN = 1;
            Delay(1); // wait for encoder to settle

            // Exit sleep cycle if position changes over next 50 ms period
            long position = EncoderGetPostion();
            Delay(50);
            if (position != EncoderGetPostion()) {
                SleepTimerRestart();
            }

            // Switch off LED and encoder
            LedOff();
            ENCODER_ENABLE_PIN = 0;
        } while (_SLEEP);

        // Reset on exiting sleep mode
        asm("reset");
    }
}

void SleepTimerRestart() {
    _SLEEP = 0; // clear SLEEP bit
    TMR5HLD = 0; // zero timer
    TMR4 = 0;
}

void SleepTimerDisable() {
    SleepTimerRestart();
    T4CONbits.TON = 0; // stop timer
}

//------------------------------------------------------------------------------
// End of file
