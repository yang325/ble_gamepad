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
    union {
        struct gpio_callback callback;
        int state;
    };
} button_t;

/* Button list with low latency */
static button_t btn_list_1[] = {
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
};
/* Button list with normal latency */
static button_t btn_list_2[] = {
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
        .name = DT_GPIO_LABEL(BUTTON_P_NODE, gpios),
        .pin = DT_GPIO_PIN(BUTTON_P_NODE, gpios),
        .flag = DT_GPIO_FLAGS(BUTTON_P_NODE, gpios),
    }
};

static void board_button_handler(const struct device *dev, struct gpio_callback *cb,
		                    uint32_t pins)
{
    int ret;

    switch (pins) {
        case BIT(DT_GPIO_PIN(BUTTON_A_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_A_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_A_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button A pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button A released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_B_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_B_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_B_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button B pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button B released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_C_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_C_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_C_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button C pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button C released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_D_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_D_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_D_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button D pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button D released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_E_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_E_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_E_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button E pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button E released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_F_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_F_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_F_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button F pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button F released at %u", k_cycle_get_32());
            }
            break;
        case BIT(DT_GPIO_PIN(BUTTON_P_NODE, gpios)):
            ret = gpio_pin_get(dev, DT_GPIO_PIN(BUTTON_P_NODE, gpios));
            if (ret < 0) {
                LOG_ERROR("Failed to get pin %d state (err %d)", DT_GPIO_PIN(BUTTON_P_NODE, gpios), ret);
            } else if (1 == ret) {
                LOG_INFO("Button P pressed at %u", k_cycle_get_32());
            } else {
                LOG_INFO("Button P released at %u", k_cycle_get_32());
            }
            break;
        default:
            LOG_WARNING("Unknown button %x", pins);
            break;
    }
}

static void board_button_init(button_t *p_button, bool low_latency)
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

    if (low_latency) {
        err = gpio_pin_interrupt_configure(button,
                                        p_button->pin,
                                        GPIO_INT_EDGE_BOTH);
        if (err) {
            LOG_ERROR("Failed to configure interrupt on %s pin %d (err %d)",
                    p_button->name, p_button->pin, err);
            return;
        }

        gpio_init_callback(&p_button->callback, board_button_handler, BIT(p_button->pin));
        err = gpio_add_callback(button, &p_button->callback);
        if (err) {
            LOG_ERROR("Failed to add callback on %s (err %d)",
                        p_button->name, err);
            return;
        }
    } else {
        err = gpio_pin_get(button, p_button->pin);
        if (err < 0) {
            LOG_ERROR("Failed to get pin %d state (err %d)", p_button->pin, err);
            return;
        }
        p_button->state = err;
    }

    LOG_INFO("Set up button at %s pin %d", p_button->name, p_button->pin);
}

void board_init(void)
{
    int index;

    /* Initialize all buttons */
    for (index = 0; index < ARRAY_SIZE(btn_list_1); ++index) {
        board_button_init(&btn_list_1[index], true);
    }
    for (index = 0; index < ARRAY_SIZE(btn_list_2); ++index) {
        board_button_init(&btn_list_2[index], false);
    }
}

void board_button_scan(void)
{
    int index, err;
    const struct device *button;

    for (index = 0; index < ARRAY_SIZE(btn_list_2); ++index) {
        button = device_get_binding(btn_list_2[index].name);
        if (button == NULL) {
            LOG_ERROR("Cannot find %s device", btn_list_2[index].name);
            continue;
        }
        err = gpio_pin_get(button, btn_list_2[index].pin);
        if (err < 0) {
            LOG_ERROR("Failed to get pin %d state (err %d)", btn_list_2[index].pin, err);
            continue;
        }
        if (err != btn_list_2[index].state) {
            btn_list_2[index].state = err;
            board_button_handler(button, NULL, BIT(btn_list_2[index].pin));
        }
    }
}
