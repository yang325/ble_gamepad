/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "hid.h"

static void connected(struct bt_conn *conn, uint8_t err)
{
	int ret;
	char addr[BT_ADDR_LE_STR_LEN];
	struct bt_le_conn_param param = {
		.interval_min = 12,
		.interval_max = 16,
		.latency = 0,
		.timeout = 500,
	};

	if (err) {
		printk("[E] Connection failed (err %u)\n", err);
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	printk("[D] Connect index %u, address %s\n", bt_conn_index(conn), addr);

	ret = bt_conn_le_param_update(conn, &param);
	if (ret) {
		printk("[E] Update parameter failed (err %d)\n", ret);
		return;
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("[D] Disconnect index %u (reason %u)\n", bt_conn_index(conn), reason);
	hid_reset();
}

static void param_updated(struct bt_conn *conn, uint16_t interval,
						uint16_t latency, uint16_t timeout)
{
	printk("[D] LE conn %d param updated: interval %d, timeout %d, latency %d\n",
			bt_conn_index(conn), interval, timeout, latency);
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
	.le_param_updated = param_updated,
};

static void bt_ready(int err)
{
	struct bt_data ad[] = {
		BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
		BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0x12, 0x18)
	};
	/* Set Scan Response data */
	struct bt_data sd[] = {
		BT_DATA_BYTES(BT_DATA_TX_POWER, 0x00),
		BT_DATA_BYTES(BT_DATA_GAP_APPEARANCE, CONFIG_BT_DEVICE_APPEARANCE & 0xFF, (CONFIG_BT_DEVICE_APPEARANCE >> 8) & 0xFF)
	};
	struct bt_le_adv_param param = {
		.id = BT_ID_DEFAULT,
		.options = BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_NAME,
		.interval_min = BT_GAP_ADV_FAST_INT_MIN_2,
		.interval_max = BT_GAP_ADV_FAST_INT_MAX_2
	};

	if (err) {
		printk("[E] Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("[D] Bluetooth initialized\n");

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	/* Initilize services*/
	hid_init();

	err = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		printk("[E] Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("[D] Advertising successfully started\n");
}

void main(void)
{
	int err;

	err = bt_enable(bt_ready);
	if (err) {
		printk("[E] Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_conn_cb_register(&conn_callbacks);

	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_msleep(1000);
	}
}
