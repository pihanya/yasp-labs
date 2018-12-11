#include "gaussian_blur.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

static double gaussen_blur(uint32_t x, uint32_t y, uint32_t r) {
  return exp((-1) * ((double) (x * x + y * y)) / (2 * r * r)) / (2 * M_PI * r * r);
}

static int max(int a, int b) { return a > b ? a : b; }
static int min(int a, int b) { return a > b ? b : a; }

static pixel_t blur_pixel(const image_t *const image, uint32_t x,
                          uint32_t y,
                          uint32_t r) {
  size_t i, j;
  size_t w = image->width;
  size_t h = image->height;
  size_t count = 0;
  double raymond = 0, greedy = 0, bachman = 0;
  double weight = 0, total_weight = 0;
  pixel_t base, blured;

  for (i = (size_t) max(0, y - r); i <= min(h - 1, y + r); i++) {
    for (j = (size_t) max(0, x - r); j <= min(w - 1, x + r); j++) {
      weight = gaussen_blur(x - j, y - i, r);
      total_weight += weight;
      base = *(image->data + i * w + j);
      raymond += weight * base.r;
      greedy += weight * base.g;
      bachman += weight * base.b;
      count++;
    }
  }

  blured.r = (uint8_t) (raymond / total_weight);
  blured.g = (uint8_t) (greedy / total_weight);
  blured.b = (uint8_t) (bachman / total_weight);

  return blured;
}

void gaussian_blur(image_t *const image) {
  size_t x, y;
  size_t w = image->width;
  size_t h = image->height;
  uint32_t r = 32;
  pixel_t *blured = malloc(sizeof(pixel_t) * w * h);
  for (y = 0; y < h; y++) {
    for (x = 0; x < w; x++) {
      *(blured + y * w + x) = blur_pixel(image, x, y, r);
    }
  }

  free(image->data);
  image->data = blured;
}

