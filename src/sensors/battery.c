#include "sensors/battery.h"
#include <stdlib.h>
#include <stdio.h>

koraidon_battery_info_t battery_get_info(const char* path) {
    koraidon_battery_info_t data = {0};

    char* level_path;
    asprintf(&level_path, "%s/capacity", path);

    char* voltage_path;
    asprintf(&voltage_path, "%s/voltage_now", path);

    char* temp_path;
    asprintf(&temp_path, "%s/temp", path);
    
    FILE* level_file = fopen(level_path, "rb");

    if(!level_file)
        goto end;

    FILE* voltage_file = fopen(voltage_path, "rb");

    if(!voltage_file) {
        fclose(level_file);
        goto end;
    }

    FILE* temp_file = fopen(temp_path, "rb");
    
    if(!temp_file) {
        fclose(level_file);
        fclose(voltage_file);
        goto end;
    }
    
    char* level_str = calloc(16, 1);
    fread(level_str, 1, 16, level_file);

    char* voltage_str = calloc(16, 1);
    fread(voltage_str, 1, 16, voltage_file);
    
    char* temp_str = calloc(16, 1);
    fread(temp_str, 1, 16, temp_file);
    
    int voltage = 0;
    int temp = 0;

    sscanf(level_str, "%d", &data.level);
    sscanf(voltage_str, "%7d", &voltage);

    data.voltage = voltage / 1000000.0;

    sscanf(temp_str, "%d", &temp);

    data.temp = temp / 10.0;

    free(level_str);
    free(voltage_str);
    free(temp_str);

    fclose(level_file);
    fclose(voltage_file);
    fclose(temp_file);

    end:

    free(level_path);
    free(voltage_path);
    free(temp_path);

    data.path = path;

    return data;
}