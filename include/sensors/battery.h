#pragma once

#include <stdint.h>

typedef enum {
    BATTERY_DRAIN = 0,
    BATTERY_CHARGING = 1,
    BATTERY_FULL = 2,
} koraidon_battery_status_t;

typedef struct {
    char* path;

    uint32_t level;
    float temp;
    float voltage;

    koraidon_battery_status_t status;
} koraidon_battery_info_t;

koraidon_battery_info_t battery_get_info(const char* path);