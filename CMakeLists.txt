# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(peripheral)

target_sources(app PRIVATE
  src/main.c
  $ENV{ZEPHYR_BASE}/samples/bluetooth/gatt/hrs.c
  $ENV{ZEPHYR_BASE}/samples/bluetooth/gatt/bas.c
  $ENV{ZEPHYR_BASE}/samples/bluetooth/gatt/cts.c
)

zephyr_library_include_directories($ENV{ZEPHYR_BASE}/samples/bluetooth)
