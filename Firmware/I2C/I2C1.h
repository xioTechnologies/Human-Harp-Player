/*
 * File:   I2C.h
 * Author: Seb Madgwick
 */

#ifndef I2C1_H
#define I2C1_H

//------------------------------------------------------------------------------
// Includes

#include "GenericTypeDefs.h"

//------------------------------------------------------------------------------
// Function declarations

void I2C1Initialise(const long baud);

void I2C1Start(void);
void I2C1Stop(void);
void I2C1Restart(void);
void I2C1Send(char data);
char I2C1Receive(void);
void I2C1Ack(void);
void I2C1Nack(void);

void I2C1ScriptEdit(int lineNumber);
int I2C1ScriptWriteStart(void);
int I2C1ScriptWriteRestart(void);
int I2C1ScriptWriteStop(void);
int I2C1ScriptWriteSend(const char data);
int I2C1ScriptWriteReceive(void);
int I2C1ScriptWriteAck(char* const destination);
int I2C1ScriptWriteNack(char* const destination);
void I2C1ScriptRun(void);
BOOL I2C1ScriptIsRunning(void);
BOOL I2C1ScriptGetCompleteFlag(void);
void I2C1ScriptClearCompleteFlag(void);

//------------------------------------------------------------------------------
// Macros

#define I2C_WRITE(ADDRESS)  ((ADDRESS << 1) | 0)
#define I2C_READ(ADDRESS)   ((ADDRESS << 1) | 1)

#endif

//------------------------------------------------------------------------------
// End of file