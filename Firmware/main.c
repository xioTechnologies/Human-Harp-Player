/*
 * @file Main.h
 * @author Seb Madgwick
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
 * 2.
 * 1.
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay/Delay.h"
#include "Encoder/Encoder.h"
#include "Imu/Imu.h"
#include "Send/Send.h"
#include <stdbool.h>
#include "SystemDefinitions.h"
#include "Uart/Uart1.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Configuration Bits

_FICD(JTAGEN_OFF); // JTAG is disabled
_FWDT(FWDTEN_OFF); // Watchdog timer enabled/disabled by user software
_FOSC(FCKSM_CSECMD & POSCMD_HS); // Clock switching is enabled,Fail-safe Clock Monitor is disabled; HS Crystal Oscillator Mode
_FOSCSEL(FNOSC_FRC & IESO_OFF); // Internal Fast RC (FRC); Start up with user-selected oscillator source

//------------------------------------------------------------------------------
// Function declarations

static void Initialise(void);

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Firmware entry point.
 * @return This function should never return.
 */
int main(void) {

    // Initialise oscillator and I/O
    Initialise();

    // Initialise drivers and middleware modules
    Uart1Initialise(115200, false);
    EncoderInitialise();
    ImuInitialise();

    // Initialise application modules
    SendInitialise();

    // Start up application tasks
    SendReset();
    Delay(50);
    SendFirmwareVersion();
    Delay(50);

    // Main loop
    while (true) {
        SendDoTasks();
    }
}

/**
 * @brief Initialise oscillator and I/O.
 */
static void Initialise(void) {

    // Configure oscillator for 70 MIPS with 16 MHz external crystal
    PLLFBD = 33; // M = 35
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    __builtin_write_OSCCONH(0x03); // initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(OSCCON | 0x01);
    while (OSCCONbits.COSC != 0b011); // wait for Clock switch to occur
    while (OSCCONbits.LOCK != 1); // wait for PLL to lock

    // Disable analogue inputs
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    ANSELC = 0x0000;

    // Configure encoder I/O
    ENCODER_A_MAP();
    ENCODER_B_MAP();

    // Configure IMU I/O
    IMU_VDD_LAT = 0;
    IMU_VDD_TRIS = 0;
    IMU_INT_MAP();

    // Configure UART I/O
    UART_RX_MAP();
    UART_TX_MAP();

    // Configure Test pin I/O
    TEST_TRIS = 0;
}

//------------------------------------------------------------------------------
// End of file
