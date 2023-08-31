#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#include "video/backfb.h"

koraidon_backfb_t backfb_from_screen(koraidon_screen_t screen) {
    koraidon_backfb_t framebuffer = {0};

    framebuffer.screen = screen;
    framebuffer.size = screen.screen_size;
    framebuffer.buffer = calloc(screen.screen_size, 1);

    return framebuffer;
}

void screen_update(koraidon_screen_t screen) {
    ioctl(screen.fd, FBIOGET_VSCREENINFO, &screen.real_info);

    screen.real_info.sync = screen.real_info.sync;
    screen.real_info.yres_virtual = screen.real_info.sync;
    
    ioctl(screen.fd, FBIOPUT_VSCREENINFO, &screen.real_info);
}

void backfb_flush(koraidon_backfb_t framebuffer) {
    memcpy(framebuffer.screen.buffer, framebuffer.buffer, framebuffer.size);

    screen_update(framebuffer.screen);
}

void backfb_deinit(koraidon_backfb_t framebuffer) {
    free(framebuffer.buffer);
}