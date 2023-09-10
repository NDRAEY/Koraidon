#pragma once

#include <stdint.h>

#include "video/backfb.h"

typedef void (*set_pixel_func)(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color);

void set_pixel(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color);
void fill_screen(koraidon_backfb_t buf, uint32_t color);
void set_pixel_alpha(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color);