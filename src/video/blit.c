//
// Created by ndraey on 10.09.23.
//

#include "../../include/video/blit.h"

// ARGB or RGB supported
// TODO: Test with 24-bit surfaces
void buffer_blit(koraidon_backfb_t buffer, const char* input_image, size_t bpp, size_t x, size_t y, size_t w, size_t h) {
	size_t bytes_pp = bpp >> 3;

	if(!(bytes_pp == 4 || bytes_pp == 3)) {
		return;
	}

	for(size_t sy = y; sy < y + h; sy++) {
		for(size_t sx = x; sx < x + w; sx++) {
			uint32_t outcoords = sy * (w * bytes_pp) + (bytes_pp * sx);
			uint32_t srccoords = (sy - y) * (bytes_pp * w) + ((sx - x) * bytes_pp);

			buffer.buffer[outcoords + 0] = input_image[srccoords + 0];
			buffer.buffer[outcoords + 1] = input_image[srccoords + 1];
			buffer.buffer[outcoords + 2] = input_image[srccoords + 2];

			if(bytes_pp == 4)
				buffer.buffer[outcoords + 3] = input_image[srccoords + 3];
		}
	}
}