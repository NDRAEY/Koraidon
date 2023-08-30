#include <stdlib.h>

#include "video/tga_image.h"
#include "video/pixel.h"

int tga_draw(koraidon_backfb_t framebuffer, size_t x, size_t y, const char* filename) {
    tga_header_t* tga_header = calloc(1, sizeof(tga_header_t));

    bool ok = tga_extract_info(filename, tga_header);

    if(ok) {        
        size_t buffer_size = tga_header->w * tga_header->h;
        uint32_t* image_data = calloc(buffer_size, 4);

        int errcode = tga_extract_pixels(filename, image_data);

        if(errcode < 0) {
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
