//
// Created by ndraey on 10.09.23.
//

#pragma once

#include "screen.h"

void pixfmt_conv(char* pixels, size_t bpp, size_t width, size_t height, koraidon_screen_pixfmt_t input_format, koraidon_screen_pixfmt_t output_format);