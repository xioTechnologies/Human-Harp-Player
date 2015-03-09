/**
 * @file SystemDefinitions.h
 * @author Seb Madgwick
 * @brief Global system definitions.  All I/O pin assignments and timing
 * calculations must be derived from this file.
 */

#ifndef SYSTEM_DEFINITIONS_H
#define SYSTEM_DEFINITIONS_H

//------------------------------------------------------------------------------
// Includes

#include <xc.h>

//------------------------------------------------------------------------------
// Definitions - System clock

#define FOSC    140000000ul
#define FP      (FOSC >> 1)
#define FCY     FP // valid only for DOZE = 0

//------------------------------------------------------------------------------
// Definitions - I/O assignments

// Encoder
#define ENCODER_A_MAP() _QEA1R = 24
#define ENCODER_B_MAP() _QEB1R = 36

// IMU
#define IMU_VDD_TRIS    _TRISB5
#define IMU_VDD_LAT     _LATB5
#define IMU_INT_MAP()   _INT1R = 51

// UART
#define UART_RX_MAP()   _U1RXR = 39
#define UART_TX_MAP()   _RP40R = 0b000001

// Test pin
#define TEST_TRIS       _TRISC0
#define TEST_LAT        _LATC0

//------------------------------------------------------------------------------
// Definitions - Firmware version

#define FIRMWARE_VERSION "v2.0" " (" __DATE__ " " __TIME__ ")"

#endif

//------------------------------------------------------------------------------
// End of file
