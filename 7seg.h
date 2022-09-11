#include <stdint.h>
#include <8052.h>
#include "delay.h"



#pragma once
#define SSEG_COUNT 4
#define SSEG_BUFFER_SIZE 100
#define ITER_TO_NEXT_DISPLAY 500

typedef enum {
    SSEG_NOTHING = 0,
    SSEG_0,
    SSEG_1,
    SSEG_2,
    SSEG_3,
    SSEG_4,
    SSEG_5,
    SSEG_6,
    SSEG_7,
    SSEG_8,
    SSEG_9,
    SSEG_A,
    SSEG_B,
    SSEG_C,
    SSEG_D,
    SSEG_E,
    SSEG_F,
    SSEG_G,
    SSEG_H,
    SSEG_I,
    SSEG_J,
    SSEG_L,
    SSEG_M_LEFT,
    SSEG_M_RIGHT,
    SSEG_N,
    SSEG_O,
    SSEG_P,
    SSEG_Q,
    SSEG_R,
    SSEG_S,
    SSEG_T,
    SSEG_U,
    SSEG_W_LEFT,
    SSEG_W_RIGHT,
    SSEG_X_LEFT,
    SSEG_X_RIGHT,
    SSEG_Y,
    SSEG_DOT,
    SSEG_SPLASH,
    SSEG_UNDERLINE,
    SSEG_MAX
}sseg_char_t;


typedef struct
{
    uint8_t chars[SSEG_BUFFER_SIZE];
    int8_t display_pos;
    uint16_t iter_count;
    uint8_t char_count;
} sseg_display_t;

uint8_t SSEG_TABLE[SSEG_MAX] = { \
    0b00000000 /* nothing */ , \
    0b00111111 /* 0 */ , \
    0b00000110 /* 1 */ , \
    0b01011011 /* 2 */ , \
    0b01001111 /* 3 */ , \
    0b01100110 /* 4 */ , \
    0b01101101 /* 5 */ , \
    0b01111101 /* 6 */ , \
    0b00000111 /* 7 */ , \
    0b01111111 /* 8 */ , \
    0b01100111 /* 9 */ , \
    0b01110111 /* a */ , \
    0b01111100 /* b */ , \
    0b01011000 /* c */ , \
    0b01011110 /* d */ , \
    0b01111001 /* e */ , \
    0b01110001 /* f */ , \
    0b01101111 /* 0x10,g */ , \
    0b01110110 /* 0x11,h */ , \
    0b00000100 /* 0x12,i */ , \
    0b00001110 /* 0x13,j */ , \
    0b00111000 /* 0x14,l */ , \
    0b00110011 /* 0x15,m - left */ , \
    0b00100111 /* 0x16,m - right */ , \
    0b01010100 /* 0x17,n */ , \
    0b01011100 /* 0x18,o */ , \
    0b01110011 /* 0x19,p */ , \
    0b11100111 /* 0x1A,q */ , \
    0b01010000 /* 0x1B,r */ , \
    0b01101101 /* 0x1C,s */ , \
    0b01111000 /* 0x1D,t */ , \
    0b00011100 /* 0x1F,u */ , \
    0b00111100 /* 0x20,w - left */ , \
    0b00011110 /* 0x21,w - right */ , \
    0b01001100 /* 0x22,x - left */ , \
    0b01011000 /* 0x23,x - right */ , \
    0b01101110 /* 0x24,y */ ,\
    0b10000000 /* 0x25,dot */, \
    0b01000000 /* 0x26,- */, \
    0b00001000 /* 0x27,_ */ \


};

void sseg_set_string(sseg_display_t *sseg, char *str){
    uint8_t* sseg_buf = sseg->chars;
    while (*str != '\0'){
        if(*str >= '0' && *str <= '9'){
            *sseg_buf = *str - '0' + SSEG_0;
        }
        else if(*str >= 'a' && *str <= 'j'){
            *sseg_buf = *str - 'a' + SSEG_A;
        }
        else if(*str >= 'A' && *str <= 'J'){
            *sseg_buf = *str - 'A' + SSEG_A;
        }
        else if(*str >= 'n' && *str <= 'u'){
            *sseg_buf = *str - 'n' + SSEG_N;
        }
        else if(*str >= 'N' && *str <= 'U'){
            *sseg_buf = *str - 'N' + SSEG_N;
        }
        // special care
        else if(*str == 'l' || *str == 'L'){
            *sseg_buf = SSEG_L;
        }
        else if(*str == 'y' || *str == 'Y'){
            *sseg_buf = SSEG_Y;
        }
        else if(*str == '.'){
            *sseg_buf = SSEG_DOT;
        }
        else if(*str == '-'){
            *sseg_buf = SSEG_SPLASH;
        }
        else if(*str == '_'){
            *sseg_buf = SSEG_UNDERLINE;
        }
        else if(*str == 'm' || *str == 'M'){
            *sseg_buf = SSEG_M_LEFT;
            sseg_buf ++;
            *sseg_buf = SSEG_M_RIGHT;
        }
        else if(*str == 'w' || *str == 'W'){
            *sseg_buf = SSEG_W_LEFT;
            sseg_buf ++;
            *sseg_buf = SSEG_W_RIGHT;
        }
        else if(*str == 'x' || *str == 'X'){
            *sseg_buf = SSEG_X_LEFT;
            sseg_buf ++;
            *sseg_buf = SSEG_X_RIGHT;
        }
        else{
            *sseg_buf = SSEG_NOTHING;
        }

        str ++;
        sseg_buf ++;
    }
    sseg->char_count = sseg_buf - sseg->chars;
}

void sseg_set_display(sseg_display_t *display, uint8_t index, uint8_t c){
    display->chars[index] = c;
    
}

void sseg_display(sseg_display_t *display){
    if(display->display_pos < SSEG_BUFFER_SIZE && display->display_pos >= 0){
        P0 = SSEG_TABLE[display->chars[display->display_pos]];
        P2_2 = 0;
        Delay50us();
        P2_2 = 1;
    }
    else{
        P0 = 0;
        P2_2 = 0;
        Delay50us();
        P2_2 = 1;
    }
    
    if(display->display_pos + 1 < SSEG_BUFFER_SIZE && display->display_pos + 1 >= 0){
        P0 = SSEG_TABLE[display->chars[display->display_pos + 1]];
        P2_3 = 0;
        Delay50us();
        P2_3 = 1;
    }
    else{
        P0 = 0;
        P2_3 = 0;
        Delay50us();
        P2_3 = 1;
    }
    
    if(display->display_pos + 2 < SSEG_BUFFER_SIZE && display->display_pos + 2 >= 0){
        P0 = SSEG_TABLE[display->chars[display->display_pos + 2]];
        P2_4 = 0;
        Delay50us();
        P2_4 = 1;
    }
    else{
        P0 = 0;
        P2_4 = 0;
        Delay50us();
        P2_4 = 1;
    }

    if(display->display_pos + 3 < SSEG_BUFFER_SIZE && display->display_pos + 3 >= 0){
        P0 = SSEG_TABLE[display->chars[display->display_pos + 3]];
        P2_5 = 0;
        Delay50us();
        P2_5 = 1;
    }
    else{
        P0 = 0;
        P2_5 = 0;
        Delay50us();
        P2_5 = 1;
    }


    if(display->char_count >= 4){
        display->iter_count ++;
        if(display->iter_count >= ITER_TO_NEXT_DISPLAY){
            display->iter_count = 0;
            display->display_pos ++;
            if((int)display->display_pos >= (int)display->char_count){
                display->display_pos = -4;
            }
        }
    }
    
}