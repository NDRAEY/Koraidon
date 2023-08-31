#pragma once

#include <stdint.h>

typedef size_t (*write_func_t)();

struct koraidon_tty {
    write_func_t write;
};
