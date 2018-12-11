#ifndef __PROG_H__
#define __PROG_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../data/image.h"
#include "../io/bmp_io.h"
#include "../filters/image_rotator.h"
#include "../filters/acid.h"
#include "../filters/gaussian_blur.h"
#include "../util/bmp_io_statuses.h"

void calc(void **calc_chain, size_t len, image_t *const image);
void **parse_keys(size_t leys_len, const char *keys);

read_status_t image_parse(FILE *const f_image, image_t *const image);

int contains(const char *string, char c);

void rotation(image_t *const image);
void blur(image_t *const image);
void acid(image_t *const image);

void usage();
#endif
