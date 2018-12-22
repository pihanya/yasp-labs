#ifndef _IMAGE_BMP_H_
#define _IMAGE_BMP_H_

#include <stdint.h>

#pragma pack(push, 1)
struct pixel_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
#pragma pack(pop)
typedef struct pixel_t pixel_t;

struct image_t {
  uint32_t width;
  uint32_t height;
  pixel_t *data;
};

typedef struct image_t image_t;

/*----------------------------------BMP_FORMAT----------------------------------*/

#define BMP_HEADER_SIZE sizeof(struct bmp_file_header)
#pragma pack(push, 1)
struct bmp_file_header {
  uint16_t bf_type;        /* bmp magic-number 4D42                           */
  uint32_t bf_size;        /* file_size                                       */
  uint32_t bf_rsrv;        /* reserved must be NULL                           */
  uint32_t bf_offb;        /* pixel data offset                               */
};
#pragma pack(pop)

#define BMP_INFO_SIZE sizeof(struct bmp_info)
#pragma pack(push, 1)
struct bmp_info {
  uint32_t bi_size;        /* size of bit map info struct
                            * 12  -- CORE
                            * 40  -- BITMAPINFOHEADER
                            * 108 -- BITMAV4HEADER
                            * BITMAPV5HEADER                                   */
  uint32_t bi_width;       /* image width                                      */
  uint32_t bi_height;      /* image height                                     */
  uint16_t bi_planes;      /* must be 1                                        */
  uint16_t bi_bcount;      /* bits per pixel                                   */
  uint32_t bi_comprs;      /* compression method
                            * 0 -- BI_RGB [][] -> BitCount != 0
                            * 1 -- BI_RLE8 -- don't care
                            * 2 -- BI_RLE4 -- don't care
                            * 3 -- BI_BITFIELDS -- [][] color channel masks
                            * 4 -- BI_JPEG -- inlined jpeg-file
                            * 5 -- BI_PNG  -- inlined png-file
                            * 6 -- BI_ALPHABITFIELDS -- 3 + alpha channel mask  */
  uint32_t bi_imsize;      /* pixel data size                                   */
  uint32_t bi_xpxprm;      /* pixels per meter Ox                               */
  uint32_t bi_ypxprm;      /* pixels per meter Oy                               */
  uint32_t bi_coloru;      /* size of color tables                              */
  uint32_t bi_colori;      /* count of used cells(from st)                      */
};
#pragma pack(pop)

struct bmp_info_add {
  uint32_t red_mask;
  uint32_t green_mask;
  uint32_t blue_mask;
  uint32_t alpha_mask;
  uint32_t color_space_type;
};

#endif
