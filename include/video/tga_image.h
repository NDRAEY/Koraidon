#pragma once

#include <stdint.h>

#include "image_formats/tga.h"

int tga_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, const char* filename);