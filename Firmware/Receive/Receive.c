/**
 * @file Receive.c
 * @author Seb Madgwick
 * @brief Application tasks and functions for receiving messages.
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay/Delay.h"
#include "Encoder/Encoder.h"
#include "Send/Send.h"
#include "Uart/Uart1.h"

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Do tasks.  This function should be called repeatedly within the main
 * program loop.
 */
void ReceiveDoTasks() {
    while (Uart1IsGetReady() > 0) {
        switch (Uart1GetChar()) {
            case 'f':
            case 'F':
                SendFirmwareVersion();
                Delay(2000);
                break;
            case 'r':
            case 'R':
                asm("RESET");
                break;
            case 'z':
            case 'Z':
                EncoderZero();
                SendZero();
                break;
            default:
                break;
        }
    }
}

//------------------------------------------------------------------------------
// End of file
