#include <stdio.h>

#include <libdragon.h>

int main(void) {
    debug_init_isviewer();

    console_init();

    debug_init_usblog();
    console_set_debug(true);

    printf("Hello world!\n");
    debugf("Test\n");

    while (1) {}
}