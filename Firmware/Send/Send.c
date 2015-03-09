/*
 * File:   Send.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Encoder/Encoder.h"
#include "Imu/Imu.h"
#include "Send.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemDefinitions.h"
#include "Timer/Timer.h"
#include "Uart/Uart1.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

//#define SEND_FREQUENCY  50 // messages per second

//------------------------------------------------------------------------------
// Function prototypes

//static void LongToAscii(char* const charArray, int* const index, long i);

//------------------------------------------------------------------------------
// Functions

void SendInitialise() {
    //    long ticksPeriod = (long) ((float) FP / (float) SEND_FREQUENCY + 0.5f);
    //    PR8 = (int) (ticksPeriod & 0xFFFF);
    //    PR9 = (int) (ticksPeriod >> 16);
    //    T8CONbits.T32 = 1; // TMR8 and TMR9 form a 32-bit timer
    //    T8CONbits.TON = 1; // start timer
}

void SendDoTasks() {
    const Ticks32 currentTicks = TimerGetTicks32();
    static Ticks32 previousTicks;
    if ((currentTicks.value - previousTicks.value) >= (TIMER_TICKS_PER_SECOND / 50)) {
        previousTicks = currentTicks;

        TEST_LAT = 1;

        char string[1024];
        DIRECTION direction;
        ImuGetDirection(&direction);
        sprintf(string, "%ld,%ld,%ld,%ld,%ld\r\n", EncoderGetPostion(), EncoderGetVelocity(), (long) (100.0f * direction.azimuth), (long) (100.0f * direction.elevation), (long) (100.0f * ImuGetAngularRate()));
        Uart1PutString(string);

        //        char string[1024];
        //        int stringIndex = 0;
        //        LongToAscii(string, &stringIndex, EncoderGetPostion());
        //        string[stringIndex++] = ',';
        //        LongToAscii(string, &stringIndex, EncoderGetVelocity());
        //        string[stringIndex++] = ',';
        //        DIRECTION direction;
        //        ImuGetDirection(&direction);
        //        LongToAscii(string, &stringIndex, 100.0f * direction.azimuth);
        //        string[stringIndex++] = ',';
        //        LongToAscii(string, &stringIndex, 100.0f * direction.elevation);
        //        string[stringIndex++] = ',';
        //        LongToAscii(string, &stringIndex, 100.0f * ImuGetAngularRate());
        //        string[stringIndex++] = '\r';
        //        string[stringIndex++] = '\n';
        //        string[stringIndex++] = '\0';
        //        Uart1PutString(string);

        TEST_LAT = 0;
    }
}

//static void LongToAscii(char* const charArray, int* const index, long i) {
//    static const char asciiDigits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',};
//    ldiv_t n;
//    if (i < 0) {
//        charArray[(*index)++] = '-';
//        i = -i;
//    }
//    if (i >= 1000000000l) {
//        n = ldiv(i, 1000000000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 100000000l) {
//        n = ldiv(i, 100000000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 10000000l) {
//        n = ldiv(i, 10000000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 1000000l) {
//        n = ldiv(i, 1000000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 100000l) {
//        n = ldiv(i, 100000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 10000l) {
//        n = ldiv(i, 10000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 1000l) {
//        n = ldiv(i, 1000l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 100l) {
//        n = ldiv(i, 100l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    if (i >= 10l) {
//        n = ldiv(i, 10l);
//        charArray[(*index)++] = asciiDigits[n.quot];
//        i = n.rem;
//    }
//    charArray[(*index)++] = asciiDigits[i];
//}

void SendZero() {

    Uart1PutString("Zero\r\n");
}

void SendReset() {

    Uart1PutString("Reset\r\n");
}

void SendFirmwareVersion() {
    char string[64];
    strcpy(string, "Firmware ");
    strcat(string, FIRMWARE_VERSION);
    strcat(string, "\r\n");
    Uart1PutString(string);
}

//------------------------------------------------------------------------------
// End of file
