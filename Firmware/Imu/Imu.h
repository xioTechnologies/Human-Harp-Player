/*
 * File:   Imu.h
 * Author: Seb Madgwick
 */

#ifndef IMU_H
#define IMU_H

//------------------------------------------------------------------------------
// Definitions

typedef struct {
    float azimuth;
    float elevation;
} DIRECTION;

//------------------------------------------------------------------------------
// Function prototypes

void ImuInitialise();
void ImuGetDirection(DIRECTION * const direction);
float ImuGetAngularRate();
void ImuZero();
void ImuDisableHighPassFilter();

#endif

//------------------------------------------------------------------------------
// End of file
