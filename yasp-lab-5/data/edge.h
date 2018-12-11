//
// Created by Pihanya on 11.12.2018.
//

#ifndef YASP_LAB_5_EDGE_H
#define YASP_LAB_5_EDGE_H

#include "verticle.h"

struct _edge_t {
  verticle_t *first_verticle;
  verticle_t *second_verticle;
};

typedef struct _edge_t edge_t;

#endif //YASP_LAB_5_EDGE_H
