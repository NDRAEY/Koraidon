//
// Created by ndraey on 09.09.23.
//

#include "../../include/video/scaler.h"
#include <stdlib.h>

#define SIZE(width, height, bpp) ((width) * (height) * ((bpp) >> 3))

void scaler_scale(const char* input_pixels,
				  uint8_t original_bpp, size_t original_width, size_t original_height,
				  size_t target_width, size_t target_height,
				  char** output_pixels_ptr
) {
	size_t target_bufsize = SIZE(target_width, target_height, original_bpp);

	char* pixptr = malloc(target_bufsize);

	float xScale = (float)original_width / (float)target_width;
	float yScale = (float)original_height / (float)target_height;

	uint8_t byte_per_pixel = original_bpp >> 3;

	for(size_t y = 0; y < target_height; y++) {
		for(size_t x = 0; x < target_width; x++) {
			int sx = (int)((float)x * xScale);
			int sy = (int)((float)y * yScale);

			uint32_t coord_source = sy * (original_width * byte_per_pixel) + (sx * byte_per_pixel);
			uint32_t coord_target = y * (target_width * byte_per_pixel) + (x * byte_per_pixel);

			pixptr[coord_target + 0] = input_pixels[coord_source + 0];
			pixptr[coord_target + 1] = input_pixels[coord_source + 1];
			pixptr[coord_target + 2] = input_pixels[coord_source + 2];
			pixptr[coord_target + 3] = input_pixels[coord_source + 3];
//			((uint32_t*)pixptr)[coord_target] = ((uint32_t*)input_pixels)[coord_source];
		}
	}

	printf("[%d x %d @ %d] ", original_width, original_height, original_bpp);
	printf("===> [%d x %d @ %d]\n", target_width, target_height, original_bpp);

	*output_pixels_ptr = pixptr;
}