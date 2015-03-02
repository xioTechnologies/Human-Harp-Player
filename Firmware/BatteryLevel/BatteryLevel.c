/*
 * File:   BatteryLevel.c
 * Author: Seb Madgwick
 *
 *  Sample rate:
 *  = FCY / ( (ADCS + 1) * (14 + SAMC) * N)
 *  = 70 MHz / ( 256 * (14 + 31) * 16)
 *  = 379.77 Hz
 */

//------------------------------------------------------------------------------
// Includes

#include "BatteryLevel.h"
#include "Led/Led.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define MINIMUM_VOLTAGE 3.3

//------------------------------------------------------------------------------
// Variables

static float voltage;

//------------------------------------------------------------------------------
// Functions

void BatteryLevelInitialise(void) {
    AD1CON1bits.AD12B = 1; // 12-bit, 1-channel ADC operation
    AD1CON1bits.SSRC = 0b111; // internal counter ends sampling and starts conversion (auto-convert)
    AD1CON1bits.ASAM = 1; // sampling begins immediately after the last conversion completes; SAMP bit is auto-set
    AD1CON2bits.SMPI = 15; // interrupts at the completion of conversion for each 16th sample/convert sequence
    AD1CON3bits.SAMC = 31; // auto sample time = 31 * TAD
    AD1CON3bits.ADCS = 255; // TAD = 256 * TCY
    AD1CHS0bits.CH0SA = 0; // channel 0 positive input is AN0
    AD1CON1bits.ADON = 1; // enable ADC
}

void BatteryLevelDoTasks(void) {
    if (_AD1IF) { // if ADC conversion complete
        _AD1IF = 0; // clear interrupt flag
        unsigned int sum = ADC1BUF0;
        sum += ADC1BUF1;
        sum += ADC1BUF2;
        sum += ADC1BUF3;
        sum += ADC1BUF4;
        sum += ADC1BUF5;
        sum += ADC1BUF6;
        sum += ADC1BUF7;
        sum += ADC1BUF8;
        sum += ADC1BUF9;
        sum += ADC1BUFA;
        sum += ADC1BUFB;
        sum += ADC1BUFC;
        sum += ADC1BUFD;
        sum += ADC1BUFE;
        sum += ADC1BUFF;
        voltage = (float) sum * ((2.0f * 3.3f) / (16.0f * 4096.0f)); // Vref = 3.3 V, gain = 1/2, N = 16, resolution = 12-bit
        if (voltage < MINIMUM_VOLTAGE) {
            LedTriggerEvent(SLOW_FLASH_FOR_3_SECONDS); // flash LED if voltage too low
        }
    }
}

float BatteryLevelGetVoltage() {
    return voltage;
}

//------------------------------------------------------------------------------
// End of file
