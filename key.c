#include "key.h"
#include "delay.h"

inline void key_set_indv_by_pack(_Bool *indv, uint8_t pack){
    pack = ~pack;
    for(int i = 0; i < 4; i++){
        indv[i] = (pack >> i) & 0x01;
    }
}

void key_scan(keys_t* keys) {
    uint8_t key;


    P1_4 = 0;
    Delay_Force_Stack();
    key = P1;
    P1_4 = 1;
    key_set_indv_by_pack(&(keys->S1), key);

    P1_5 = 0;
    Delay_Force_Stack();
    key = P1;
    P1_5 = 1;
    key_set_indv_by_pack(&(keys->S5), key);

    P1_6 = 0;
    Delay_Force_Stack();
    key = P1;
    P1_6 = 1;
    key_set_indv_by_pack(&(keys->S9), key);
}