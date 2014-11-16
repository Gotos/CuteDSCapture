#pragma once
#include <stdint.h>
#include <stdbool.h>

bool dscapture_init();
void dscapture_deinit();
bool dscapture_grabFrame(uint16_t *frameBuf);

enum {
    FRAMEWIDTH   =256,
    FRAMEHEIGHT  =192
};
