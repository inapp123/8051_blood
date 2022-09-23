#include <8052.h>
#include <stdint.h>
#include "7seg.h"
#include "delay.h"
#include "key.h"
#include <stdio.h>
#include "blood.h"

#define led P2_7

typedef enum {
    STATUS_SPLASH = 0,
    STATUS_ADJUST_DELAY_TIME,
    STATUS_WAITING_FATHER_BLOOD_TYPE,
    STATUS_CONFIRMING_FATHER_BLOOD_TYPE,
    STATUS_WAITING_MOTHER_BLOOD_TYPE,
    STATUS_CONFIRMING_MOTHER_BLOOD_TYPE,
    STATUS_DELAYING,
    STATUS_RESULT,
} status_t;



__sfr __at (0xE7) IAP_CONTR ;

void serial_isr(void) __interrupt(4) {
    if (TI)
    {
        TI = 0;
    }
    if (RI)
    {
        RI = 0;
        IAP_CONTR = 0x60;
    }
    
}

int putchar (int c)
{
    while (!TI);  /* wait until transmitter ready */
    TI = 0;
    SBUF = c;      /* output character */
    return (c);
}

sseg_display_t disp;

void sseg_timer0_isr(void) __interrupt(1) {
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




keys_t keys;
// we dont have k and v in char
void main(void)
{
    init_serial();
    sseg_init_timer();
    EA = 1; // Enable Interrupts now!


    // sseg_set_string(&disp, "blood type calculator");

    uint8_t status = 0;
    uint8_t father_blood_type = 0;
    uint8_t mother_blood_type = 0;

    blood_result_t* result;
    char result_buf[SSEG_BUFFER_SIZE];

    uint8_t result_back_2_zero = 0;

    __data uint8_t delay_time = 0;
    __data uint8_t delay;
    
    while(1)
    {
        key_scan(&keys);
        if(keys.S10){
            disp.display_pos = 0;
            status = STATUS_WAITING_FATHER_BLOOD_TYPE;
            result_back_2_zero = 0;
        }

        else if(keys.S9 && status != STATUS_RESULT){
            disp.display_pos = 0;
            status = STATUS_ADJUST_DELAY_TIME;
        }

        switch (status)
        {
        case STATUS_SPLASH:
            sseg_set_string(&disp, "blood type calculator.");
            if(keys.S11){
                disp.display_pos = 0;
                status = STATUS_WAITING_FATHER_BLOOD_TYPE;
            }
            break;
        case STATUS_WAITING_FATHER_BLOOD_TYPE:
            sseg_set_string(&disp, "father blood type");
            if(keys.S5){
                father_blood_type = BLOODTYPE_A;
                status = STATUS_CONFIRMING_FATHER_BLOOD_TYPE;
            }
            else if(keys.S6){
                father_blood_type = BLOODTYPE_B;
                status = STATUS_CONFIRMING_FATHER_BLOOD_TYPE;
            }
            else if(keys.S7){
                father_blood_type = BLOODTYPE_AB;
                status = STATUS_CONFIRMING_FATHER_BLOOD_TYPE;
            }
            else if(keys.S8){
                father_blood_type = BLOODTYPE_O;
                status = STATUS_CONFIRMING_FATHER_BLOOD_TYPE;
            }
            break;
        case STATUS_CONFIRMING_FATHER_BLOOD_TYPE:
            switch (father_blood_type)
            {
            case BLOODTYPE_A:
                sseg_set_string(&disp, "A");
                break;
            case BLOODTYPE_B:
                sseg_set_string(&disp, "B");
                break;
            case BLOODTYPE_AB:
                sseg_set_string(&disp, "AB");
                break;
            case BLOODTYPE_O:
                sseg_set_string(&disp, "O");
                break;
            default:
                break;
            }
            if(keys.S5){
                father_blood_type = BLOODTYPE_A;
            }
            else if(keys.S6){
                father_blood_type = BLOODTYPE_B;
            }
            else if(keys.S7){
                father_blood_type = BLOODTYPE_AB;
            }
            else if(keys.S8){
                father_blood_type = BLOODTYPE_O;
            }
            else if(keys.S11){
                status = STATUS_WAITING_MOTHER_BLOOD_TYPE;
            }

            break;
        case STATUS_WAITING_MOTHER_BLOOD_TYPE:
            sseg_set_string(&disp, "mother blood type");
            if(keys.S5){
                mother_blood_type = BLOODTYPE_A;
                status = STATUS_CONFIRMING_MOTHER_BLOOD_TYPE;
            }
            else if(keys.S6){
                mother_blood_type = BLOODTYPE_B;
                status = STATUS_CONFIRMING_MOTHER_BLOOD_TYPE;
            }
            else if(keys.S7){
                mother_blood_type = BLOODTYPE_AB;
                status = STATUS_CONFIRMING_MOTHER_BLOOD_TYPE;
            }
            else if(keys.S8){
                mother_blood_type = BLOODTYPE_O;
                status = STATUS_CONFIRMING_MOTHER_BLOOD_TYPE;
            }
            break;
        case STATUS_CONFIRMING_MOTHER_BLOOD_TYPE:
            switch (mother_blood_type)
            {
            case BLOODTYPE_A:
                sseg_set_string(&disp, "A");
                break;
            case BLOODTYPE_B:
                sseg_set_string(&disp, "B");
                break;
            case BLOODTYPE_AB:
                sseg_set_string(&disp, "AB");
                break;
            case BLOODTYPE_O:
                sseg_set_string(&disp, "O");
                break;
            default:
                break;
            }
            if(keys.S5){
                father_blood_type = BLOODTYPE_A;
            }
            else if(keys.S6){
                father_blood_type = BLOODTYPE_B;
            }
            else if(keys.S7){
                father_blood_type = BLOODTYPE_AB;
            }
            else if(keys.S8){
                father_blood_type = BLOODTYPE_O;
            }
            else if(keys.S11){
                sseg_set_string(&disp, "Calculating....");
                status = STATUS_RESULT;
            }
            break;
        
        case STATUS_RESULT:
            if(result_back_2_zero == 0){
                result = calculate_blood(father_blood_type, mother_blood_type);
                blood_result_format(result, result_buf);

                delay = delay_time;
                while(delay--){
                    DelayInCalc();
                }

                sseg_set_string(&disp, result_buf);
                disp.display_pos = -1;
                result_back_2_zero = 1;
            }
            break;

        case STATUS_ADJUST_DELAY_TIME:
           
            switch (delay_time)
            {
            case 0:
                sseg_set_string(&disp,"DLY0");
                break;
            case 1:
                sseg_set_string(&disp,"DLY1");
                break;
            case 2:
                sseg_set_string(&disp,"DLY2");
                break;
            case 3:
                sseg_set_string(&disp,"DLY3");
                break;
            case 4:
                sseg_set_string(&disp,"DLY4");
                break;
            case 5:
                sseg_set_string(&disp,"DLY5");
                break;
            
            default:
                break;
            }

            if(keys.S1 && delay_time > 0){
                delay_time -- ;
            }
            else if(keys.S4 && delay_time < 5 ){
                delay_time ++ ;
            }

            if(keys.S11){
                status = STATUS_WAITING_FATHER_BLOOD_TYPE;
            }

            break;
        default:
            break;
        }


        // Delay50ms();

    }
}
 