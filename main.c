#include <8052.h>
#include <stdint.h>
#include "7seg.h"
#include "delay.h"
#include "key.h"

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
    PT0 = 0;
}

void init_timer0(void){
    TMOD = 0b00000010; // Mode 2
    TH0 = 0x00;
    TL0 = 0x00;
    ET0 = 1;
    TR0 = 1;
}

keys_t keys;
// we dont have k and v in char
void main(void)
{
    init_serial();
    init_timer0();
    EA = 1; // Enable Interrupts now!

    uint16_t i = 0;
    sseg_set_string(&disp, "Please input fathers blood type");
    char buf[15];

    while(1)
    {
        char *buf_ptr = buf;
        key_scan(&keys);
        if(keys.S1){
            *buf_ptr++ = '1';
        }
        if(keys.S2){
            *buf_ptr++ = '2';
        }
        if(keys.S3){
            *buf_ptr++ = '3';
        }
        if(keys.S4){
            *buf_ptr++ = '4';
        }
        if(keys.S5){
            *buf_ptr++ = '5';
        }
        if(keys.S6){
            *buf_ptr++ = '6';
        }
        if(keys.S7){
            *buf_ptr++ = '7';
        }
        if(keys.S8){
            *buf_ptr++ = '8';
        }
        if(keys.S9){
            *buf_ptr++ = '9';
        }
        if(keys.S10){
            *buf_ptr++ = 'A';
        }
        if(keys.S11){
            *buf_ptr++ = 'B';
        }

        if(buf_ptr != buf){
            *buf_ptr = '\0';
            sseg_set_string(&disp, buf);
        }
        else{
            sseg_set_string(&disp, "Nothing Pressed");
        }

    }
}
 