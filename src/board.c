/* board.c - Board Support Package */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/adc.h>
#include <sys/util.h>
#include <sys/printk.h>

#include "main.h"
#include "board.h"

#define BUTTON_A_NODE           DT_ALIAS(sw0)
#define BUTTON_B_NODE           DT_ALIAS(sw1)
#define BUTTON_C_NODE           DT_ALIAS(sw2)
#define BUTTON_D_NODE           DT_ALIAS(sw3)
#define BUTTON_E_NODE           DT_ALIAS(sw4)
#define BUTTON_F_NODE           DT_ALIAS(sw5)
#define BUTTON_P_NODE           DT_ALIAS(sw6)

#define ROCKER_NODE             DT_PATH(rocker)

typedef struct {
    const char *name;
    gpio_pin_t pin;
    gpio_flags_t flag;
    union {
        struct gpio_callback callback;
        int state;
    };
} button_t;

typedef struct {
    const char *adc_name;
    uint8_t adc_channel;
    uint8_t adc_index;
    const char *pin_name;
    gpio_pin_t pin;
    gpio_flags_t pin_flag;
} rocker_axis_t;

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
/* Axis X of rocker */
static rocker_axis_t axis_x = {
    .adc_index = 0,
    .adc_name = DT_IO_CHANNELS_LABEL_BY_IDX(ROCKER_NODE, 0),
    .adc_channel = DT_IO_CHANNELS_INPUT_BY_IDX(ROCKER_NODE, 0),
    .pin_name = DT_GPIO_LABEL_BY_IDX(ROCKER_NODE, power_gpios, 0),
    .pin = DT_GPIO_PIN_BY_IDX(ROCKER_NODE, power_gpios, 0),
    .pin_flag = DT_GPIO_FLAGS_BY_IDX(ROCKER_NODE, power_gpios, 0),
};
/* Axis Y of rocker */
static rocker_axis_t axis_y = {
    .adc_index = 1,
    .adc_name = DT_IO_CHANNELS_LABEL_BY_IDX(ROCKER_NODE, 1),
    .adc_channel = DT_IO_CHANNELS_INPUT_BY_IDX(ROCKER_NODE, 1),
    .pin_name = DT_GPIO_LABEL_BY_IDX(ROCKER_NODE, power_gpios, 1),
    .pin = DT_GPIO_PIN_BY_IDX(ROCKER_NODE, power_gpios, 1),
    .pin_flag = DT_GPIO_FLAGS_BY_IDX(ROCKER_NODE, power_gpios, 1),
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

static void board_rocker_init(rocker_axis_t *p_axis)
{
    int err;
    const struct device *device;
    struct adc_channel_cfg adc_cfg = {0};

    device = device_get_binding(p_axis->pin_name);
    if (device == NULL) {
        LOG_ERROR("Cannot find %s GPIO device", p_axis->pin_name);
    }

    err = gpio_pin_configure(device, p_axis->pin, GPIO_OUTPUT_INACTIVE | p_axis->pin_flag);
    if (err) {
        LOG_ERROR("Failed to configure %s pin %d (err %d)",
                    p_axis->pin_name, p_axis->pin, err);
        return;
    }

    err = gpio_pin_set(device, p_axis->pin, true);
    if (err) {
        LOG_ERROR("Failed to set %s pin %d (err %d)",
                    p_axis->pin_name, p_axis->pin, err);
        return;
    }

    device = device_get_binding(p_axis->adc_name);
    if (device == NULL) {
        LOG_ERROR("Cannot find %s ADC device", p_axis->adc_name);
        return;
    }

    adc_cfg.gain = ADC_GAIN_1_3;
    adc_cfg.reference = ADC_REF_INTERNAL;
    adc_cfg.acquisition_time = ADC_ACQ_TIME_DEFAULT;
    adc_cfg.channel_id = p_axis->adc_index;
    adc_cfg.input_positive = BIT(p_axis->adc_channel);
    err = adc_channel_setup(device, &adc_cfg);
    if (err) {
        LOG_ERROR("Cannot setup %s ADC device (err %d)", p_axis->adc_name, err);
        return;
    }

    LOG_INFO("Set up Axis at %s pin %d", p_axis->adc_name, p_axis->adc_channel);
}

static void board_rocker_convert(int32_t ref_mv, enum adc_gain gain,
                                    uint8_t resolution, int16_t raw_value)
{
    int err;
    int32_t value;

    value = raw_value;
    err = adc_raw_to_millivolts(ref_mv, gain, resolution, &value);
    if (err) {
        LOG_ERROR("Cannot convert ADC value (err %d)", err);
        return;
    }

    LOG_INFO("ADC raw %d ~ %d mV", raw_value, value);
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
    /* Initialize the rocker */
    board_rocker_init(&axis_x);
    board_rocker_init(&axis_y);
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

void board_rocker_read(axis_val_t *axis_val)
{
    int err;
    const struct device *device;
    struct adc_sequence adc_seq = {0};

    device = device_get_binding(axis_x.adc_name);
    if (device == NULL) {
        LOG_ERROR("Cannot find %s ADC device", axis_x.adc_name);
        return;
    }

    adc_seq.channels = BIT(axis_y.adc_index) | BIT(axis_x.adc_index);
    adc_seq.buffer = &axis_val;
    adc_seq.buffer_size = sizeof(axis_val);
    adc_seq.resolution = 10;
    adc_seq.calibrate = true;
    err = adc_read(device, &adc_seq);
    if (err) {
        LOG_ERROR("Cannot read ADC device (err %d)", err);
        return;
    }

    //board_rocker_convert(adc_ref_internal(device), ADC_GAIN_1_3, adc_seq.resolution, axis_val->axis_x_raw);
    board_rocker_convert(adc_ref_internal(device), ADC_GAIN_1_3, adc_seq.resolution, axis_val->axis_y_raw);
}
