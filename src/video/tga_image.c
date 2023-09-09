#include <stdlib.h>

#include "video/tga_image.h"
#include "video/pixel.h"
#include "video/scaler.h"

int tga_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, const char* filename) {
	tga_header_t* tga_header = calloc(1, sizeof(tga_header_t));

	if(!tga_header) {
		return -1;
	}

	bool ok = tga_extract_info(filename, tga_header);

	if(ok) {
		size_t buffer_size = tga_header->w * tga_header->h;
		uint32_t* image_data = calloc(buffer_size, 4);

		int errcode = tga_extract_pixels(filename, image_data);

		if(errcode < 0) {
			free(tga_header);

			return errcode;
		}

		for(size_t sy = 0; sy < tga_header->h; sy++) {
			for(size_t sx = 0; sx < tga_header->w; sx++) {
				set_pixel(framebuffer, x + sx, y + sy, image_data[(sy * tga_header->w + sx)]);
			}
		}

		free(image_data);

		return 0;
	}

	free(tga_header);
	return -1;
}

int tga_scale_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, size_t width, size_t height, const char* filename) {
	tga_header_t* tga_header = calloc(1, sizeof(tga_header_t));

	if(!tga_header) {
		return -1;
	}

	bool ok = tga_extract_info(filename, tga_header);

	if(ok) {
		size_t buffer_size = tga_header->w * tga_header->h;
		uint32_t* image_data = calloc(buffer_size, 4); // 4 byte is 32 bit (which ARGB pixel format)

		int errcode = tga_extract_pixels(filename, image_data);

		if(errcode < 0) {
			free(tga_header);

			return errcode;
		}

		uint32_t* out_data = 0;

		scaler_scale(
			(char*)image_data,
			32,
			tga_header->w, tga_header->h,
			width, height,
			(char**)&out_data
	 	);

		for(size_t sy = 0; sy < height; sy++) {
			for(size_t sx = 0; sx < width; sx++) {
				set_pixel(framebuffer, x + sx, y + sy, out_data[(sy * width) + sx]);
			}
		}

		free(image_data);
		free(out_data);

		return 0;
	}

	free(tga_header);

	return -1;
}
