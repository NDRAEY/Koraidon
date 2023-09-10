//
// Created by ndraey on 10.09.23.
//

#pragma once
#include "video/backfb.h"

void buffer_blit(koraidon_backfb_t buffer, const char* input_image, size_t bpp, size_t x, size_t y, size_t w, size_t h);