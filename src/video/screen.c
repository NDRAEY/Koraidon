#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include "video/screen.h"

void screen_debug_info(struct fb_var_screeninfo inf) {
    printf("Width: %d\n", inf.width);
    printf("Height: %d\n", inf.height);
    printf("Sync: %X\n", inf.sync);
    printf("Colorspace: %d\n", inf.colorspace);
    printf("Grayscale: %d\n", inf.grayscale);
    printf("BPP: %d\n", inf.bits_per_pixel);
    printf("VMODE: %x\n", inf.vmode);
    printf("R: %d\n", inf.red.offset);
    printf("G: %d\n", inf.green.offset);
    printf("B: %d\n", inf.blue.offset);
    printf("Transp: %d\n", inf.transp.offset);
}

koraidon_screen_t init_screen(const char* path) {
    koraidon_screen_t screen = {0};
    
    struct fb_var_screeninfo* screen_info = &(screen.real_info);
    int fd = open(path, O_RDWR);

    screen.fd = fd;

    if(fd < 0) {
        printf("Could not open framebuffer: %s\n", path);
        return invalid_screen;
    }

    ioctl(fd, FBIOGET_VSCREENINFO, &(screen.real_info));

    size_t screen_size = screen_info->width * screen_info->height * (screen_info->bits_per_pixel >> 3);

	printf("Screen size: %d\n", screen_size);

    uint8_t* screendata = mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(!screendata) {
        printf("mmap() failed\n");

        return invalid_screen;
    }

    screen.ok = 1;
    screen.buffer = screendata;
    screen.screen_size = screen_size;

    if(screen.real_info.red.offset == 16) {
        screen.pixfmt = SCREEN_BGR;
    } else {
        screen.pixfmt = SCREEN_RGB;
    }

    // Double-Flip our screen to fully initialize it.

    screen.real_info.sync = !screen.real_info.sync;
    ioctl(fd, FBIOPUT_VSCREENINFO, &(screen.real_info));

    screen.real_info.sync = !screen.real_info.sync;
    ioctl(fd, FBIOPUT_VSCREENINFO, &(screen.real_info));

    screen_debug_info(screen.real_info);

    return screen;
}

void deinit_screen(koraidon_screen_t screen) {
    munmap(screen.buffer, screen.screen_size);
    close(screen.fd);
}