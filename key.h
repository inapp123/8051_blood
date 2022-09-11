#include <8052.h>
#include <stdint.h>

#pragma once

typedef struct keys_t
{
    uint8_t S1;
    uint8_t S2;
    uint8_t S3;
    uint8_t S4;
    uint8_t S5;
    uint8_t S6;
    uint8_t S7;
    uint8_t S8;
    uint8_t S9;
    uint8_t S10;
    uint8_t S11;
    uint8_t PADDING;
}keys_t;

void key_scan(keys_t* keys);