//
// Created by Pihanya on 11.12.2018.
//

#ifndef YASP_LAB_5_LINE_H
#define YASP_LAB_5_LINE_H

#include "verticle.h"

struct _line_t {
  int n;
  flat_decimal_verticle_t *verticles;
};

typedef struct _line_t line_t;

#endif //YASP_LAB_5_LINE_H
