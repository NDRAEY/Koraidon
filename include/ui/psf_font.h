//
// Created by ndraey on 10.09.23.
//

#pragma once

#include "video/backfb.h"
#include "ui/rect.h"

typedef struct {
	uint8_t magic[2];
	uint8_t mode;
	uint8_t charHeight;
} __attribute__((packed)) psf_header_t;

void draw_char(set_pixel_func func, koraidon_backfb_t buffer, uint16_t character, size_t x, size_t y, uint32_t color);
void draw_string(set_pixel_func func, koraidon_backfb_t buffer, char* string, size_t x, size_t y, uint32_t color);