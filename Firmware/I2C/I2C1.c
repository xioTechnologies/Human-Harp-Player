/*
 * File:   I2C.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "GenericTypeDefs.h"
#include "I2C1.h"
#include "SystemClock.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Definitions

#define SCRIPT_LENGTH       64
#define INTERRUPT_PRIORITY  6

#define CMD_START   0b1000000000000000
#define CMD_RESTART 0b0100000000000000
#define CMD_STOP    0b0010000000000000
#define CMD_SEND    0b0001000000000000
#define CMD_RECEIVE 0b0000100000000000
#define CMD_ACK     0b0000010000000000
#define CMD_NACK    0b0000001000000000

//------------------------------------------------------------------------------
// Variables

static int scripCmd[SCRIPT_LENGTH]; // script commands (MSB) and send data (LSB)
static char* scripDes[SCRIPT_LENGTH]; // script destinations for received data
static BOOL scriptIndex = FALSE; // script index
static BOOL scriptComplete = FALSE;

//------------------------------------------------------------------------------
// Functions

void I2C1Initialise(const long baud) {
    I2C1BRG = (int) (((float) FCY / (float) baud) - 1.0f - ((float) FCY * 0.000000130f));
    _DISSLW = 1; // slew rate control disabled
    _SMEN = 1; // use SMbus voltage levels
    _ACKDT = 0; // send ACK during Acknowledge
    _MI2C1IP = INTERRUPT_PRIORITY; // set interrupt priority
    _I2CEN = 1; // enable I2C1
}

void I2C1Start(void) {
    _SEN = 1;
    while (_SEN);
}

void I2C1Stop(void) {
    _PEN = 1;
    while (_PEN);
}

void I2C1Restart(void) {
    _RSEN = 1;
    while (_RSEN);
}

void I2C1Send(char data) {
    I2C1TRN = data;
    while (_TRSTAT);
}

char I2C1Receive(void) {
    _RCEN = 1;
    while (_RCEN);
    return I2C1RCV;
}

void I2C1Ack(void) {
    _ACKEN = 1;
    while (_ACKEN);
}

void I2C1Nack(void) {
    _ACKDT = 1;
    I2C1Ack();
    _ACKDT = 0;
}

void I2C1ScriptEdit(const int lineNumber) {
    scriptIndex = lineNumber;
}

int I2C1ScriptWriteStart(void) {
    scripCmd[scriptIndex] = CMD_START;
    return scriptIndex++;
}

int I2C1ScriptWriteRestart(void) {
    scripCmd[scriptIndex] = CMD_RESTART;
    return scriptIndex++;
}

int I2C1ScriptWriteStop(void) {
    scripCmd[scriptIndex] = CMD_STOP;
    return scriptIndex++;
}

int I2C1ScriptWriteSend(const char data) {
    scripCmd[scriptIndex] = CMD_SEND | ((int) data & 0xFF);
    return scriptIndex++;
}

int I2C1ScriptWriteReceive(void) {
    scripCmd[scriptIndex] = CMD_RECEIVE;
    return scriptIndex++;
}

int I2C1ScriptWriteAck(char* const destination) {
    scripDes[scriptIndex] = destination;
    scripCmd[scriptIndex] = CMD_ACK;
    return scriptIndex++;
}

int I2C1ScriptWriteNack(char* const destination) {
    scripDes[scriptIndex] = destination;
    scripCmd[scriptIndex] = CMD_NACK;
    return scriptIndex++;
}

void I2C1ScriptRun(void) {
    scriptComplete = FALSE;
    scriptIndex = 0;
    _MI2C1IF = 1;
    _MI2C1IE = 1;
}

BOOL I2C1ScriptIsRunning(void) {
    return _MI2C1IE;
}

BOOL I2C1ScriptGetCompleteFlag(void) {
    return scriptComplete;
}

void I2C1ScriptClearCompleteFlag(void) {
    scriptComplete = FALSE;
}

//------------------------------------------------------------------------------
// Functions - ISR

void __attribute__((interrupt, auto_psv))_MI2C1Interrupt(void) {
    _MI2C1IF = 0;
    int i = scriptIndex++;
    int cmd = scripCmd[i];
    if (cmd & CMD_RECEIVE) {
        _RCEN = 1;
    } else if (cmd & CMD_ACK) {
        *scripDes[i] = I2C1RCV;
        _ACKDT = 0;
        _ACKEN = 1;
    } else if (cmd & CMD_SEND) {
        I2C1TRN = cmd;
    } else if (cmd & CMD_RESTART) {
        _RSEN = 1;
    } else if (cmd & CMD_NACK) {
        *scripDes[i] = I2C1RCV;
        _ACKDT = 1;
        _ACKEN = 1;
    } else if (cmd & CMD_START) {
        _SEN = 1;
    } else {
        _MI2C1IE = 0; // script complete, prevent further interrupts
        _PEN = 1;
        scriptComplete = TRUE;
    }
}

//------------------------------------------------------------------------------
// End of file
