/*
 * File:   Uart1.c
 * Author: Seb Madgwick
 *
 * RX_BUFFER_SIZE and TX_BUFFER_SIZE must be a 2^n number, e.g. 256, 512, 1024.
 */

//------------------------------------------------------------------------------
// Includes

#include <xc.h>
#include "SystemDefinitions.h"
#include "Uart1.h"

//------------------------------------------------------------------------------
// Definitions

#define RX_BUFFER_SIZE          1024
#define TX_BUFFER_SIZE          1024
#define RX_INTERRUPT_PRIORITY   3
#define TX_INTERRUPT_PRIORITY   3

//------------------------------------------------------------------------------
// Variables

static volatile char rxBuffer[RX_BUFFER_SIZE];
static volatile unsigned int rxBufferIn = 0;
static volatile unsigned int rxBufferOut = 0;
static volatile int rxBufferOverrun = 0;
static volatile char txBuffer[TX_BUFFER_SIZE];
static volatile unsigned int txBufferIn = 0;
static volatile unsigned int txBufferOut = 0;

//------------------------------------------------------------------------------
// Functions

void Uart1Initialise(const long baudRate, const BOOL ctsRtsEnabled) {
    U1BRG = (unsigned int) (((float) FP / (4.0f * (float) baudRate) - 1.0f) + 0.5f); // calculate UxBRG for BRGH = 1 with rounding
    if (ctsRtsEnabled) {
        U1MODEbits.UEN = 0b10; // UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
    } else {
        U1MODEbits.UEN = 0b00; // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
    }
    U1MODEbits.UARTEN = 1; // UART1 enabled
    U1MODEbits.BRGH = 1; // high speed mode
    U1STAbits.UTXISEL1 = 0b01; // interrupt when TX FIFO is empty
    U1STAbits.UTXEN = 1; // transmit enabled
    _U1RXIP = RX_INTERRUPT_PRIORITY; // set RX interrupt priority
    _U1TXIP = TX_INTERRUPT_PRIORITY; // set TX interrupt priority
    _U1RXIF = 0; // clear RX interrupt flag
    _U1RXIE = 1; // RX interrupt enabled
}

unsigned int Uart1IsGetReady() {
    if (U1STAbits.URXDA) { // trigger interrupt if data available
        _U1RXIF = 1;
    }
    if (U1STAbits.OERR) {
        U1STAbits.OERR = 0; // clear flag and re-enable UART if hardware buffer overrun
    }
    return (rxBufferIn - rxBufferOut) & (RX_BUFFER_SIZE - 1);
}

char Uart1GetChar() {
    char c = rxBuffer[rxBufferOut++];
    rxBufferOut &= (RX_BUFFER_SIZE - 1); // overflow index at buffer size
    return c;
}

unsigned int Uart1IsPutReady() {
    return (TX_BUFFER_SIZE - 1) - ((txBufferIn - txBufferOut) & (TX_BUFFER_SIZE - 1));
}

void Uart1PutChar(const char c) {
    txBuffer[txBufferIn++] = c;
    txBufferIn &= (TX_BUFFER_SIZE - 1); // overflow index at buffer size
    if (!_U1TXIE) {
        _U1TXIF = 1;
        _U1TXIE = 1;
    }
}

void Uart1PutString(const char* str) {
    while (*str != '\0') {
        Uart1PutChar(*str++);
    }
}

void Uart1ClearRxBuffer() {
    rxBufferIn = rxBufferOut;
    rxBufferOverrun = 0;
}

void Uart1ClearTxBuffer() {
    txBufferOut = txBufferIn;
}

int Uart1GetRxBufferOverrunFlag() {
    return rxBufferOverrun;
}

void Uart1ClearRxBufferOverrunFlag() {
    rxBufferOverrun = 0;
}

int Uart1TxIsIdle() {
    return !_U1TXIE;
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __attribute__((interrupt, auto_psv))_U1RXInterrupt(void) {
    while (U1STAbits.URXDA) { // repeat while data available
        rxBuffer[rxBufferIn] = U1RXREG; // fetch data from buffer
        rxBufferIn++; // increment index with overflow
        rxBufferIn &= (RX_BUFFER_SIZE - 1);
    }
    _U1RXIF = 0; // data received immediately before clearing UxRXIF will be unhandled, URXDA should be polled to set UxRXIF
}

void __attribute__((interrupt, auto_psv))_U1TXInterrupt(void) {
    _U1TXIE = 0; // disable interrupt to avoid nested interrupt
    _U1TXIF = 0; // clear interrupt flag
    do {
        if (txBufferOut == txBufferIn) { // if FIFO empty
            return;
        }
        U1TXREG = txBuffer[txBufferOut]; // send data from FIFO
        txBufferOut++; // increment index with overflow
        txBufferOut &= (TX_BUFFER_SIZE - 1);
    } while (!U1STAbits.UTXBF); // repeat while buffer not full
    _U1TXIE = 1; // re-enable interrupt
}

//------------------------------------------------------------------------------
// End of file
