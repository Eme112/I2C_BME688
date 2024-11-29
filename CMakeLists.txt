# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(i2cCommBME688)

# Add the BME68x driver library
# Add the BME68x driver library directory to the include path
zephyr_include_directories(drivers/bme688/BME68x-Sensor-API)
# Add the BME68x driver source file
zephyr_library_sources(drivers/bme688/BME68x-Sensor-API/bme68x.c)
# Add the BME688 driver library directory to the include path
zephyr_include_directories(drivers/bme688/)
# Add the BME688 driver source file
zephyr_library_sources(drivers/bme688/bme688.c)

# Set target sources
# FILE(GLOB app_sources src/*.c src/*.cpp)
# target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE src/main.c src/bme688Facade.c)