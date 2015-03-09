/*
 * File:   Encoder.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Encoder.h"
#include "SystemDefinitions.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Functions

void EncoderInitialise() {
    QEI1CONbits.QEIEN = 1; // Module counters are enabled
}

typedef union {
    long value;

    struct {
        int lsw;
        int msw;
    };
} LONG_UNION;

long EncoderGetPostion() {
    LONG_UNION position;
    position.lsw = POS1CNTL;
    position.msw = POS1HLD;
    return position.value;
}

long EncoderGetVelocity() {
    int velocityCoutner;
    LONG_UNION interval;
    static int direction;

    // Read registers
    asm volatile("DISI #3"); // disable all interrupts (except level 7) for 3 instructions
    velocityCoutner = VEL1CNT;
    interval.lsw = INT1HLDL;
    interval.msw = INT1HLDH;

    // Store direction
    if (velocityCoutner > 0) {
        direction = 1;
    } else if (velocityCoutner < 0) {
        direction = -1;
    } else {
        return 0;
    }

    // Calculate velocity with rounding
    return (long) (((float) direction * (float) (FCY << 1) / (float) interval.value) + 0.5f);
}

void EncoderZero() {
    POS1HLD = 0;
    POS1CNTL = 0;
}

//------------------------------------------------------------------------------
// End of file
