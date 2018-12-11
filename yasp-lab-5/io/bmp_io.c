#include "bmp_io.h"

read_status_t read_header(FILE *const file,
                          struct bmp_file_header *const header) {
  rewind(file);
  if (fread(header, 1, BMP_HEADER_SIZE, file) != BMP_HEADER_SIZE)
    return READ_H_CORRUPTION;
  if (header->bf_type != 0x4D42)
    return READ_H_INVALID_SIGNATURE;
  if (header->bf_size <= BMP_HEADER_SIZE)
    return READ_H_INVALID_BMP_FILE_SIZE;
  if (header->bf_rsrv != 0)
    return READ_H_INVALID_RESERVED_BITS;
  if (header->bf_offb < 54)
    return READ_H_INVALID_BMP_OFFSET;
  return READ_OK;
}

read_status_t read_info(FILE *const file, struct bmp_info *const info) {
  fseek(file, 0x0E, SEEK_SET);
  if (fread(info, 1, BMP_INFO_SIZE, file) != BMP_INFO_SIZE)
    return READ_I_CORRUPTION;
  if (info->bi_planes != 1)
    return READ_I_INVALID_PLANES;
  if (info->bi_bcount != 24)
    return READ_I_UNSUPPORTED_BCOUNT;
  if (info->bi_comprs != 0)
    return READ_I_UNSUPPORTED_COMPRESSION;
  if (info->bi_width == 0)
    return READ_I_INVALID_WIDTH;
  if (info->bi_height == 0)
    return READ_I_INVALID_HEIGHT;
  return READ_OK;
}

read_status_t read_pixels(FILE *const file, const uint32_t offset,
                          pixel_t *const data,
                          const uint32_t width,
                          const uint32_t height) {
  size_t a, row;
  size_t trash_size = width * 3 % 4 == 0 ? 0 : 4 - (width * 3 % 4);
  fseek(file, (long) offset, SEEK_SET);
  for (row = 0; row < height; row++) {

    if ((a = fread(data + row * width, 3, width, file)) != width) {
      printf("%lu\n", a);
      return READ_P_CORRUPTED;
    }
    fseek(file, trash_size, SEEK_CUR);
  }
  return READ_OK;
}

write_status_t write_image(FILE *const file, const image_t *const image) {
  size_t row;
  const size_t w = image->width;
  const size_t h = image->height;
  const size_t padding = w % 4 == 0 ? 0 : 4 - (w * 3 % 4);
  const size_t img_size = (w * 3 + padding) * h;
  const size_t file_size = BMP_HEADER_SIZE + BMP_INFO_SIZE + img_size;
  const struct bmp_file_header header = {0x4D42, file_size, 0,
                                         (BMP_HEADER_SIZE + BMP_INFO_SIZE)};
  const struct bmp_info info = {40,              // bi_size
                                w,               // bi_width
                                h,               // bi_height
                                (uint16_t) 1,    // bi_planes
                                (uint16_t) 24,   // bi_bcount
                                0,               // bi_comprs
                                0,               // bi_imsize
                                0xb13, 0xb13,    // ppmOxy
                                0,               // bi_coloru
                                0};              // bi_colori
  const pixel_t *pixels = image->data;
  const uint8_t trash[padding];
  if (fwrite(&header, 1, sizeof(header), file) != sizeof(header))
    return WRITE_ERROR;
  if (fwrite(&info, 1, sizeof(info), file) != sizeof(info))
    return WRITE_ERROR;

  for (row = 0; row < h; row++) {
    if (fwrite(pixels + row * w, 1, 3 * w, file) != w * 3)
      return WRITE_ERROR;
    if (padding != 0) {
      fseek(file, padding, SEEK_CUR);
    }
  }

  if (fclose(file) == EOF) {
    return WRITE_CLOSE_ERROR;
  }
  return WRITE_OK;
}
