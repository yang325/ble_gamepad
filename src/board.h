#ifndef __BOARD_H_
#define __BOARD_H_

#include <inttypes.h>
#include <zephyr.h>

typedef enum {
    BOARD_ROCKER_AXIS_X,
    BOARD_ROCKER_AXIS_Y,
} axis_t;

typedef enum {
    BOARD_BUTTON_KEY_A,
    BOARD_BUTTON_KEY_B,
    BOARD_BUTTON_KEY_C,
    BOARD_BUTTON_KEY_D,
    BOARD_BUTTON_KEY_E,
    BOARD_BUTTON_KEY_F,
    BOARD_BUTTON_KEY_P,
} button_t;

typedef enum {
    BUTTON_ACTION_PREASSED,
    BUTTON_ACTION_RELEASED,
} action_t;

typedef void (*board_button_callback)(button_t button, action_t action);

void board_init(board_button_callback callback);
void board_button_scan(void);
int16_t board_rocker_read(axis_t axis);

#endif