#include <time.h>
#include "acid.h"

void acid(image_t *const image) {
  size_t x, y;
  size_t w = image->width;
  size_t h = image->height;
  srand(time(NULL));
  for (x = 0; x < h; x++) {
    for (y = 0; y < w; y++) {
      uint8_t r = (image->data + x * w + y)->r;
      uint8_t g = (image->data + x * w + y)->g;
      uint8_t b = (image->data + x * w + y)->b;
      (image->data + x * w + y)->r = (uint8_t) (3 * (((rand() & 125) & g + r) & 255));
      (image->data + x * w + y)->g = (uint8_t) (3 * (((rand() & 125) & b + g) & 255));
      (image->data + x * w + y)->b = (uint8_t) (3 * (((rand() & 125) & r + b) & 255));
    }
  }
}
