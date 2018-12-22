#ifndef YASP_LAB_5_LINE_H
#define YASP_LAB_5_LINE_H

#include "verticle.h"

struct line_t {
  int n;
  flat_decimal_verticle_t *verticles;
};

typedef struct line_t line_t;

#endif
