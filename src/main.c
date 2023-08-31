#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include "video/screen.h"
#include "video/backfb.h"
#include "video/tga_image.h"
#include "image_formats/tga.h"
#include "sensors/battery.h"

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

#include <linux/input.h>
#include <linux/soundcard.h>


struct snd_xferi {
	int result;
	void *buf;
	unsigned int frames;
};

union snd_pcm_sync_id {
	unsigned char id[16];
	unsigned short id16[8];
	unsigned int id32[4];
};

struct snd_pcm_info {
	unsigned int device;		/* RO/WR (control): device number */
	unsigned int subdevice;		/* RO/WR (control): subdevice number */
	int stream;			/* RO/WR (control): stream direction */
	int card;			/* R: card number */
	unsigned char id[64];		/* ID (user selectable) */
	unsigned char name[80];		/* name of this device */
	unsigned char subname[32];	/* subdevice name */
	int dev_class;			/* SNDRV_PCM_CLASS_* */
	int dev_subclass;		/* SNDRV_PCM_SUBCLASS_* */
	unsigned int subdevices_count;
	unsigned int subdevices_avail;
	union snd_pcm_sync_id sync;	/* hardware synchronization ID */
	unsigned char reserved[64];	/* reserved for future... */
};

#define SNDRV_PCM_IOCTL_WRITEI_FRAMES _IOW('A', 0x50, struct snd_xferi);
#define SNDRV_PCM_IOCTL_PREPARE		_IO('A', 0x40)
#define SNDRV_PCM_IOCTL_INFO		_IOR('A', 0x01, struct snd_pcm_info)

int main(void) {
    srand(time(NULL));

    koraidon_screen_t screen = _init_screen("/dev/graphics/fb0");
    koraidon_backfb_t framebuffer = backfb_from_screen(screen);

    // CODE GOES HERE...

    // BATTERY

    int fd = open("/dev/snd/pcmC1D1p", O_RDWR | O_NONBLOCK);

    if(fd) {
        printf("Sound FD Ok\n");

        struct snd_pcm_info info;

        int result = ioctl(fd, SNDRV_PCM_IOCTL_INFO, &info);

        printf("%d\n", result);

        if(result >= 0) {
            printf("Card Ok!\n");
            printf("Card ID: %s\n", info.id);
            printf("Card Name: %s\n", info.name);
            printf("Card Subname: %s\n", info.subname);
            printf("Card Stream: %d\n", info.stream);
            printf("Card Class/Subclass: %d/%d\n", info.dev_class, info.dev_subclass);
        }

        close(fd);
    }

    // koraidon_battery_info_t battery;

    // battery = battery_get_info("/sys/class/power_supply/battery/");

    // printf("Level: %d%\nTemperature: %f *C\nVolatge: %f V\n", battery.level, battery.temp, battery.voltage);
    // printf("Is charging: %s\n", battery.status == BATTERY_CHARGING ? "yes" : "no");

    // BATTERY END

    // EVENTS

    // struct input_event event;

    // int fd = open("/dev/input/event1", O_RDONLY | O_NONBLOCK);

    // while(true) {
    //     ssize_t rdbytes = read(fd, &event, sizeof(event));
    
    //     if(rdbytes == sizeof(event)) {
    //         printf("Event: Type: %d -> %d = %d\n", event.type, event.code, event.value);
    //     }
    // }

    // close(fd);

    // EVENTS END

    // GRAPHICAL CODE ENDS HERE...

    backfb_flush(framebuffer);

    backfb_deinit(framebuffer);
    _deinit_screen(screen);

    return 0;
}
