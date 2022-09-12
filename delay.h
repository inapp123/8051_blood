#include "stdint.h"
#pragma once



#define _nop_() __asm nop __endasm

void Delayms(uint8_t ms_count);
void Delay50us();
void Delay50ms();
void Delay_Force_Stack();
