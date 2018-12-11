#include "draw_utils.h"

line_t line(int x0, int y0, int x1, int y1) {
  int c;
  size_t verticles_amount;

  if (x1 < x0) {
    c = x0;
    x0 = x1;
    x1 = c;
  }

  verticles_amount = (size_t) (x1 - x0 + 1);

  if (y1 < y0) {
    c = y0;
    y0 = y1;
    y1 = c;
  }

  size_t index = 0;

  int dx = x1 - x0;
  int dy = y1 - y0;

  float error = 0;
  float error_delta = ((float) dy) / dx;

  int y = y0;

  flat_decimal_verticle_t *verticles = calloc(verticles_amount, sizeof(flat_decimal_verticle_t));

  for (int x = x0; x <= x1; ++x) {
    (verticles + index++)->x = x;
    (verticles + index++)->y = y;

    error = error + error_delta;
    if (error >= 0.5) {
      y = y + 1;
      error -= 1.0;
    }
  }

  struct _line_t line;
  line.n = verticles_amount;
  line.verticles = verticles;

  return line;
}

flat_decimal_verticle_t project(verticle_t verticle) {
  flat_decimal_verticle_t flat_verticle;
  flat_verticle.x = verticle.x;
  flat_verticle.y = verticle.y;
  return flat_verticle;
}
