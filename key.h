#include <8052.h>
#include <stdint.h>

#pragma once

typedef struct keys_t
{
    _Bool S1;
    _Bool S2;
    _Bool S3;
    _Bool S4;
    _Bool S5;
    _Bool S6;
    _Bool S7;
    _Bool S8;
    _Bool S9;
    _Bool S10;
    _Bool S11;
    _Bool PADDING;
}keys_t;

void key_scan(keys_t* keys);