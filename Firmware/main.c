/*
 * File:   main.c
 * Author: Seb Madgwick
 *
 * Device:
 * dsPIC33EP512GM604
 *
 * Compiler:
 * MPLAB XC16 v1.23
 *
 * Peripherals used:
 * INT1                 Imu.c
 * Timer 1              Delay.c
 * Timer 3              Imu.c
 * Timer 6,7            Imu.c
 * Timer 8,9            Send.c
 * QEI1                 Encoder.c
 * I2C1                 I2C1.c
 * UART1                Uart1.c
 *
 * Interrupt priorities (nesting enabled):
 * 7.
 * 6. I2C1 (I2C1.c)
 * 5. INT1 (Imu.c)
 * 4. TMR3 (Imu.c)
 * 3. UART1 (Uart1.c)
 * 2. INT2 (Button.c)
 * 1.
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay/Delay.h"
#include "Encoder/Encoder.h"
#include "GenericTypeDefs.h"
#include "Imu/Imu.h"
#include "Send/Send.h"
#include "Uart/Uart1.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Configuration Bits

_FICD(JTAGEN_OFF);
_FWDT(FWDTEN_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_HS);
_FOSCSEL(FNOSC_FRC & IESO_OFF);

//------------------------------------------------------------------------------
// Function declarations

static void Initialise(void);

//------------------------------------------------------------------------------
// Functions

int main(void) {

    // Initialise dsPIC33E
    Initialise();

    // Initialise modules
    Uart1Initialise(115200, FALSE);
    EncoderInitialise();
    ImuInitialise();
    SendInitialise();

    // Start up tasks
    SendReset();
    Delay(50);
    SendFirmwareVersion();
    Delay(50);

    // Main loop
    while (TRUE) {
        SendDoTasks();
    }
}

static void Initialise(void) {

    // Disable analogue inputs
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    ANSELC = 0x0000;

    // Set port latches
    _LATA9 = 1; // RA4 is encoder enable
    _LATB5 = 1; // RB5 is IMU enable
    _LATB8 = 1; // RB8 is is x-OSC input 1 (U1TX)
    _LATB9 = 1; // RB9 is x-OSC enable

    // Set port directions
    _TRISB7 = 1; // RB7 is is x-OSC output 1 (U1RX)
    _TRISB8 = 0; // RB8 is is x-OSC input 1 (U1TX)
    _TRISA9 = 0; // RA4 is encoder enable
    _TRISA8 = 1; // RA8 is encoder A (QEA1)
    _TRISB4 = 1; // RB4 is encoder B (QEB1)
    _TRISB5 = 0; // RB5 is IMU enable
    _TRISC4 = 1; // RC4 is IMU SDA (SDA1)
    _TRISC5 = 1; // RC5 is IMU SCL (SCL1)
    _TRISC3 = 1; // RC3 is IMU INT (INT1)
    _TRISC0 = 0; // RC0 is auxiliary pin

    // Map peripherals
    _U1RXR = 39; // RB7 (RP39) is x-OSC output 1 (U1RX)
    _RP40R = 0b000001; // RB8 (RP40) is is x-OSC input 1 (U1TX)
    _QEA1R = 24; // RA8 (RPI24) is encoder A (QEA1)
    _QEB1R = 36; // RB4 (RP47) is encoder B (QEB1)
    _INT1R = 51; // RC3 (RPI51) is BMX055 INT (INT1)

    // Setup oscillator for 70 MIPS with 16 MHz external crystal
    PLLFBD = 33; // M = 35
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    __builtin_write_OSCCONH(0x03); // initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(OSCCON | 0x01);
    while (OSCCONbits.COSC != 0b011); // wait for Clock switch to occur
    while (OSCCONbits.LOCK != 1); // wait for PLL to lock
}

//------------------------------------------------------------------------------
// End of file
