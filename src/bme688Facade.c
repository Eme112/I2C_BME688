#include "bme688Facade.h"

// Logging module for the sensor server
LOG_MODULE_REGISTER(sensor_server_logger, LOG_LEVEL_DBG);

// Struct to initialize bme68x sensor
const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bme688);

// Pointer to the BME688 sensor
const struct device *sensor_dev_bme688;

// Initialize bme68x sensor
void start_bme688() {
	LOG_INF("Starting BME688 sensor");

	if (!device_is_ready(dev)) {
		LOG_ERR("Device %s is not ready", dev->name);
		return;
	}

	LOG_INF("Device %s is ready", dev->name);

	if (bme688_init(dev) != 0) {
		LOG_ERR("Failed to initialize BME688 sensor");
		return;
	}

	bme688_mode_t mode = bme688_mode_forced; // BME688_MODE_FORCED, BME688_MODE_PARALLEL, BME688_MODE_SEQUENTIAL
	bme688_set_mode_default_conf(mode);
	LOG_INF("BME688 sensor started, MODE: %s", mode == bme688_mode_forced ? "FORCED" : mode == bme688_mode_parallel ? "PARALLEL" : mode == bme688_mode_sequencial ? "SEQUENTIAL" : "SLEEP");
}

// Obtain data from sensor
void bme688_get_data() {
	uint8_t last_index = 1;
	int measure_count = 0;
	struct bme68x_data data[3];
	
	bme688_sample_fetch(dev,SENSOR_CHAN_ALL);
	uint8_t n_fields = bme688_data_get(dev, data);

	if (n_fields != 0) {
		for (uint8_t i = 0; i < n_fields; i++) {
			if (data[i].gas_index < last_index) {
				LOG_DBG("---");
				measure_count++;
			}
			last_index = data[i].gas_index;
			if ((data[i].status & BME68X_NEW_DATA_MSK) &&
				(data[i].status & BME68X_GASM_VALID_MSK)
				) {

					LOG_DBG("sample:%d (%u/%d) : %.2f° , %.2f Pa , %.2f %% , %s %.2f ohm",
						measure_count,
						data[i].meas_index,
						data[i].gas_index,
						data[i].temperature,
						data[i].pressure,
						data[i].humidity,
						(data[i].status & BME68X_HEAT_STAB_MSK)?"":"(nhs)",
						data[i].gas_resistance);
			}
		}
	} else {
		LOG_INF("n_fields=%d;",n_fields);
	}
}