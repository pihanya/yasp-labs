#ifndef _BMP_IO_H_
#define _BMP_IO_H_

#include <stdio.h>

#include "../util/bmp_io_statuses.h"
#include "../data/image.h"

read_status_t read_header(FILE *const file, struct bmp_file_header *const header);

read_status_t read_info(FILE *const file, struct bmp_info *const info);

read_status_t read_pixels(FILE *const file, const uint32_t offset,
                          pixel_t *const data,
                          const uint32_t width,
                          const uint32_t height);

write_status_t write_image(FILE *const file, const image_t *const image);

#endif
