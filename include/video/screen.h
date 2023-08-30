#pragma once

#include <stdint.h>
#include <linux/fb.h>

typedef enum {
    SCREEN_RGB = 0,
    SCREEN_BGR = 0,
} koraidon_screen_pixfmt_t;

typedef struct {
    uint8_t ok;
    int fd;
    koraidon_screen_pixfmt_t pixfmt;
    struct fb_var_screeninfo real_info;
    size_t screen_size;
    uint8_t* buffer;
} koraidon_screen_t;

static const koraidon_screen_t invalid_screen = {0};

#define BGR2RGB(color) ({ \
__typeof__ (color) _color = color;\
((_color & 0x000000FF) << 16) | (color & 0x0000FF00) | ((color & 0x00FF0000) >> 16);\
})

koraidon_screen_t _init_screen(const char* path);
void _deinit_screen(koraidon_screen_t screen);