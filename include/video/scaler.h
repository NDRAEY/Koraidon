//
// Created by ndraey on 09.09.23.
//

#pragma once

#include <stdint.h>

void scaler_scale(const char* input_pixels,
				  uint8_t original_bpp, size_t original_width, size_t original_height,
				  size_t target_width, size_t target_height,
				  char** output_pixels_ptr
);