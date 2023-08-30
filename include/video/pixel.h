#pragma once

#include <stdint.h>

#include "video/backfb.h"

void set_pixel(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color);

