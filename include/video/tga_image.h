#pragma once

#include <stdint.h>

#include "image_formats/tga.h"

int tga_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, const char* filename);
int tga_scale_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, size_t width, size_t height, const char* filename);