#pragma once


#define _nop_() __asm nop __endasm

void Delay50us()		//@11.0592MHz
{
	unsigned char i;
	_nop_();
	i = 20;
	while (--i);
}

void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 90;
	j = 163;
	do
	{
		while (--j);
	} while (--i);
}
