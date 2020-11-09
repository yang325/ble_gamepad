/* board.c - Board Support Package */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/util.h>
#include <sys/printk.h>
#include <inttypes.h>

#include "main.h"

#define BUTTON_A_NODE           DT_ALIAS(sw0)
#define BUTTON_B_NODE           DT_ALIAS(sw1)
#define BUTTON_C_NODE           DT_ALIAS(sw2)
#define BUTTON_D_NODE           DT_ALIAS(sw3)
#define BUTTON_E_NODE           DT_ALIAS(sw4)
#define BUTTON_F_NODE           DT_ALIAS(sw5)
#define BUTTON_P_NODE           DT_ALIAS(sw6)

typedef struct {
    const char *name;
    gpio_pin_t pin;
    gpio_flags_t flag;
    struct gpio_callback callback;
} button_t;

static button_t btn_list[] = {
        {
            .name = DT_GPIO_LABEL(BUTTON_A_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_A_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_A_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_B_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_B_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_B_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_C_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_C_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_C_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_D_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_D_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_D_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_E_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_E_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_E_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_F_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_F_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_F_NODE, gpios),
        },
        {
            .name = DT_GPIO_LABEL(BUTTON_P_NODE, gpios),
            .pin = DT_GPIO_PIN(BUTTON_P_NODE, gpios),
            .flag = DT_GPIO_FLAGS(BUTTON_P_NODE, gpios),
        },
    };

static void button_pressed(const struct device *dev, struct gpio_callback *cb,
		                    uint32_t pins)
{
    LOG_INFO("Button %s pressed at %u", dev->name, k_cycle_get_32());
}

static void board_button_init(button_t *p_button)
{
    int err;
    const struct device *button;

    if (NULL == p_button) {
        LOG_ERROR("Invalid parameter");
        return;
    }

    button = device_get_binding(p_button->name);
    if (button == NULL) {
        LOG_ERROR("Cannot find %s device", p_button->name);
        return;
    }

    err = gpio_pin_configure(button,
                            p_button->pin,
                            p_button->flag | GPIO_INPUT);
    if (err) {
        LOG_ERROR("Failed to configure %s pin %d (err %d)",
                    p_button->name, p_button->pin, err);
        return;
    }

    err = gpio_pin_interrupt_configure(button,
                                        p_button->pin,
                                        GPIO_INT_EDGE_TO_ACTIVE);
    if (err) {
        LOG_ERROR("Failed to configure interrupt on %s pin %d (err %d)",
                    p_button->name, p_button->pin, err);
        return;
    }

    gpio_init_callback(&p_button->callback, button_pressed, BIT(p_button->pin));
    err = gpio_add_callback(button, &p_button->callback);
    if (err) {
        LOG_ERROR("Failed to add callback on %s (err %d)",
                    p_button->name, err);
        return;
    }

    LOG_INFO("Set up button at %s pin %d", p_button->name, p_button->pin);
}

void board_init(void)
{
    int index;

    for (index = 0; index < ARRAY_SIZE(btn_list); ++index) {
        board_button_init(&btn_list[index]);
    }
}
