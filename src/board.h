#ifndef __BOARD_H_
#define __BOARD_H_

#include <inttypes.h>
#include <zephyr.h>

typedef struct {
    int16_t axis_x_raw;
    int16_t axis_y_raw;
} __attribute__((packed)) axis_val_t;

void board_init(void);
void board_button_scan(void);
void board_rocker_read(axis_val_t *axis_val);

#endif