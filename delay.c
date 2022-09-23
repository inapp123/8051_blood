#include "delay.h"
#include <stdint.h>

void Delay50us()		//@11.0592MHz
{
	__data unsigned char i;
	_nop_();
	i = 20;
	while (--i);
}

void Delay_Force_Stack(){
	_nop_();
}

void Delay50ms()		//@11.0592MHz
{
	__data unsigned char i, j;

	i = 90;
	j = 163;
	do
	{
		while (--j);
	} while (--i);
}

void Delayms(uint8_t ms_count)		//@11.0592MHz
{
	__data unsigned char i, j;

    while(ms_count--){
        i = 90;
        j = 163;
        do
        {
            while (--j);
        } while (--i);
    }
}


void DelayInCalc(){
	__data unsigned char i,j;

	_nop_();
	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}