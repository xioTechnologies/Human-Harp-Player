/*
 * @file Encoder.h
 * @author Seb Madgwick
 * @brief Quadrature encoder module to provide measurements of rotational
 * position and velocity.
 */

#ifndef ENCODER_H
#define ENCODER_H

//------------------------------------------------------------------------------
// Includes

#include <stdint.h> // uint16_t, int16_t, int32_t

//------------------------------------------------------------------------------
// Function prototypes

void EncoderInitialise();
int32_t EncoderGetPostion();
int32_t EncoderGetVelocity();
void EncoderZero();

#endif

//------------------------------------------------------------------------------
// End of file
