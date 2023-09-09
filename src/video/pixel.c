#include <stdio.h>

#include "video/pixel.h"

// Pixel in ARGB format
void set_pixel(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color) {
	if(x >= buf.screen.real_info.width || y >= buf.screen.real_info.height)
		return;

	size_t bpp = buf.screen.real_info.bits_per_pixel >> 3;  // Bytes per pixel
	size_t width = buf.screen.real_info.width;  // Real width

	if(buf.screen.pixfmt == SCREEN_BGR) {
		color = BGR2RGB(color);
	}

	width *= bpp;
	x *= bpp;

	uint32_t coord = (y * width) + x;

	if(buf.screen.real_info.bits_per_pixel == 32) {
		*((uint32_t*)(buf.buffer + coord)) = color;
	} else {
		printf("Unsupported bpp: %d\n", buf.screen.real_info.bits_per_pixel);
	}
}

// Both background and foreground pixels are in ARGB pixel format.
uint32_t rgba_blend(uint32_t background, uint32_t foreground) {
	uint8_t components[4] = {0};

	uint8_t alpha = (foreground >> 24) & 0xff;
	uint8_t inv_alpha = 255 - alpha;

	components[0] = 0x00;
	components[1] = (alpha * ((foreground >> 16) & 0xFF) + inv_alpha * ((background >> 16) & 0xFF)) >> 8;
	components[2] = (alpha * ((foreground >> 8 ) & 0xFF) + inv_alpha * ((background >> 8 ) & 0xFF)) >> 8;
	components[3] = (alpha * ((foreground >> 0 ) & 0xFF) + inv_alpha * ((background >> 0 ) & 0xFF)) >> 8;

	return (components[0] << 24)
		|  (components[1] << 16)
		|  (components[2] << 8)
		|  (components[3] << 0);
}

// Pixel in ARGB format
void set_pixel_alpha(koraidon_backfb_t buf, size_t x, size_t y, uint32_t color) {
	if(x >= buf.screen.real_info.width || y >= buf.screen.real_info.height)
		return;

	size_t bpp = buf.screen.real_info.bits_per_pixel >> 3;  // Bytes per pixel
	size_t width = buf.screen.real_info.width;  // Real width

	if(buf.screen.pixfmt == SCREEN_BGR) {
		color = ABGR2ARGB(color);
	}

	width *= bpp;
	x *= bpp;

	uint32_t coord = (y * width) + x;

	if(buf.screen.real_info.bits_per_pixel == 32) {
		uint32_t curcolor = *((uint32_t*)(buf.buffer + coord));
		uint32_t res_color = rgba_blend(curcolor, color);

		*((uint32_t*)(buf.buffer + coord)) = res_color;
	} else {
		printf("Unsupported bpp: %d\n", buf.screen.real_info.bits_per_pixel);
	}
}

void fill_screen(koraidon_backfb_t buf, uint32_t color) {
	if(buf.screen.real_info.bits_per_pixel == 32) {
		for(int i = 0; i < buf.screen.real_info.height; i++) {
			for(int j = 0; j < buf.screen.real_info.width; j++) {
				uint32_t coord = (i * buf.screen.real_info.width) + j;

				*((uint32_t*)buf.buffer + coord) = color;
			}
		}
	} else {
		printf("Unsupported bpp: %d\n", buf.screen.real_info.bits_per_pixel);
	}
}