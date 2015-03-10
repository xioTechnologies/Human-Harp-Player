/*
 * @file Encoder.c
 * @author Seb Madgwick
 * @brief Quadrature encoder module to provide measurements of rotational
 * position and velocity.
 */

//------------------------------------------------------------------------------
// Includes

#include "Encoder.h"
#include "SystemDefinitions.h" // FCY
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Int32 union typedef.
 */
typedef union {
    int32_t value;

    struct {
        uint16_t word0;
        uint16_t word1;
    };
} Int32Union;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Initialises module.  This function should be called once on system
 * start up.
 */
void EncoderInitialise() {
    QEI1CONbits.QEIEN = 1; // Module counters are enabled
}

/**
 * @brief Gets current rotational position measurement.
 * @return Current rotational position measurement.
 */
int32_t EncoderGetPostion() {
    Int32Union position;
    position.word0 = POS1CNTL;
    position.word1 = POS1HLD;
    return position.value;
}

/**
 * @brief Gets current rotational velocity measurement.
 * @return Current rotational velocity measurement.
 */
int32_t EncoderGetVelocity() {

    // Read registers 'simultaneously'
    asm volatile("DISI #3"); // disable all interrupts (except level 7) for 3 instructions
    Int32Union interval;
    interval.word0 = INT1HLDL;
    interval.word1 = INT1HLDH;
    const int16_t velocityCoutner = VEL1CNT;

    // Store direction
    float direction;
    if (velocityCoutner > 0) {
        direction = 1.0f;
    } else if (velocityCoutner < 0) {
        direction = -1.0f;
    } else {
        return 0;
    }

    // Calculate velocity with rounding
    return (int32_t) ((direction * (float) (FCY << 1) / (float) interval.value) + 0.5f);
}

/**
 * @brief Zeros rotational position measurement.
 */
void EncoderZero() {
    POS1HLD = 0;
    POS1CNTL = 0;
}

//------------------------------------------------------------------------------
// End of file
