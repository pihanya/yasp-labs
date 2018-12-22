#include "image_rotator.h"

void rotate_90_degrees_left(image_t *const image) {
    size_t x, y;
    size_t w = image->width;
    size_t h = image->height;
    pixel_t* rotated = malloc(sizeof(pixel_t)*w*h);
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            *(rotated + x*h + y) = *(image->data + (h - y - 1)*w + x);
        }
    }
    image->width  = h;
    image->height = w;
    free(image->data);
    image->data = rotated;
}
