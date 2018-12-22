#include <time.h>
#include "acid.h"

void image_acid(image_t *const image) {
    size_t i, j, x ,y;
    size_t w = image->width;
    size_t h = image->height;
    srand(time(NULL));
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            uint8_t r = (image->data + i*w + j)->r;
            uint8_t g = (image->data + i*w + j)->g;
            uint8_t b = (image->data + i*w + j)->b;
            (image->data + i*w + j)->r = 3*(((rand()&127)&g+r)&255);
            (image->data + i*w + j)->g = 3*(((rand()&127)&b+g)&255);
            (image->data + i*w + j)->b = 3*(((rand()&127)&r+b)&255);
        }
    }
}
