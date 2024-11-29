/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "bme688Facade.h"

int main(void)
{	
	start_bme688();

	for (;;) {
		bme688_get_data();
		k_sleep(K_SECONDS(5));
	}
}
