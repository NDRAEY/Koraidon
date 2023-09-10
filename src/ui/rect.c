//
// Created by ndraey on 10.09.23.
//

#include "../../include/ui/rect.h"

void draw_fill_rect(set_pixel_func func, koraidon_backfb_t buffer, size_t x, size_t y, size_t w, size_t h, uint32_t color) {
	for(size_t i = y; i < y + h; i++) {
		for(size_t j = x; j < x + w; j++) {
			func(buffer, j, i, color);
		}
	}
}