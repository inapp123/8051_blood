#include <stdint.h>


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
    _Bool is_rendering;
} sseg_display_t;

void sseg_set_string(sseg_display_t *sseg, char *str);
void sseg_set_display(sseg_display_t *display, uint8_t index, uint8_t c);
void sseg_display(sseg_display_t *display);
