//
// Created by ndraey on 10.09.23.
//

#pragma once

#include "../../include/video/backfb.h"
#include "../../include/video/pixel.h"

void draw_fill_rect(set_pixel_func func, koraidon_backfb_t buffer, size_t x, size_t y, size_t w, size_t h, uint32_t color);