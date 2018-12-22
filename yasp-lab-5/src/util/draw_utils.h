//
// Created by Pihanya on 11.12.2018.
//

#ifndef YASP_LAB_5_DRAW_UTILS_H
#define YASP_LAB_5_DRAW_UTILS_H

#include <math.h>
#include <stdlib.h>

#include "../data/verticle.h"
#include "../data/edge.h"
#include "../data/line.h"

line_t line(int x0, int y0, int x1, int y1);
flat_decimal_verticle_t project(verticle_t verticle);

#endif //YASP_LAB_5_DRAW_UTILS_H
