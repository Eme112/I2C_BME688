#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "bme68x.h"
#include "bme688.h"
#include "bme68x_defs.h"

// Initialize bme68x sensor
void start_bme688();

// Obtain data from sensor
void bme688_get_data();