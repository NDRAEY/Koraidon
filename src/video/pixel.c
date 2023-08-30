#include <stdio.h>

#include "video/pixel.h"

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