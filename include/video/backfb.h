#pragma once

// #include <stdint.h>
#include "screen.h"

typedef struct {
    koraidon_screen_t screen;

    size_t size;
    uint8_t* buffer;
} koraidon_backfb_t;

koraidon_backfb_t backfb_from_screen(koraidon_screen_t screen);
void screen_update(koraidon_screen_t screen);
void backfb_flush(koraidon_backfb_t framebuffer);
void backfb_deinit(koraidon_backfb_t framebuffer);