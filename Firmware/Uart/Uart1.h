/*
 * File:   Uart1.h
 * Author: Seb Madgwick
 */

#ifndef UART1_H
#define UART1_H

//------------------------------------------------------------------------------
// Includes

#include "GenericTypeDefs.h"

//------------------------------------------------------------------------------
// Function declarations

void Uart1Initialise(const long baudRate, const BOOL ctsRtsEnabled);
unsigned int Uart1IsGetReady();
char Uart1GetChar();
unsigned int Uart1IsPutReady();
void Uart1PutChar(const char c);
void Uart1PutString(const char* str);
void Uart1ClearRxBuffer();
void Uart1ClearTxBuffer();
int Uart1GetRxBufferOverrunFlag();
void Uart1ClearRxBufferOverrunFlag();
int Uart1TxIsIdle();

#endif

//------------------------------------------------------------------------------
// End of file
