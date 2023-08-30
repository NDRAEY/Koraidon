#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "video/screen.h"
#include "video/backfb.h"
#include "video/tga_image.h"
#include "image_formats/tga.h"

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

int main(void) {
    srand(time(NULL));

    koraidon_screen_t screen = _init_screen("/dev/graphics/fb0");
    koraidon_backfb_t framebuffer = backfb_from_screen(screen);

    // CODE GOES HERE...



    // GRAPHICAL CODE ENDS HERE...

    backfb_flush(framebuffer);

    backfb_deinit(framebuffer);
    _deinit_screen(screen);

    return 0;
}