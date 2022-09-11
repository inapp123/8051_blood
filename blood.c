#include <8052.h>
#include <stdint.h>
#include "7seg.h"
#include "delay.h"

#define led P2_7

__sfr __at (0xE7) IAP_CONTR ;

void serial_isr(void) __interrupt(4) {
    if (RI)
    {
        IAP_CONTR = 0x60;
    }
    
}

sseg_display_t disp;

void timer0_isr(void) __interrupt(1) {
    sseg_display(&disp);
}

void init_serial(void){
    // ; Serial init
    // ; init timer 1
    TMOD &= 0b00001111;
    TMOD |= 0b00100000; // ; SET timer 1 Reg
    TH1 = 0xFD; // ; auto reload value,9600 baudrate
    TR1 = 1; // ; start timer

    // ; Serial Config
    SCON = 0b01010000; //; make it 8-bit Serial
    ES = 1; // enable Serial
    PS = 1; // Serial Priority
}

void init_timer0(void){
    TMOD = 0b00000010; // Mode 2
    TH0 = 0x00;
    TL0 = 0x00;
    ET0 = 1;
    TR0 = 1;
}



void main(void)
{
    init_serial();
    init_timer0();
    EA = 1; // Enable Interrupts now!

    uint16_t i = 0;
    while(1)
    {
        sseg_set_string(&disp, "Please input fathers blood type");
        Delay50ms();
    }
}
 