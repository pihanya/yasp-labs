#include "main.h"

int main(int argc, char *argv[]) {
  size_t len;
  image_t *image;
  FILE *f_image;
  void *calc_chain;
  read_status_t error;

  if (argc != 4) {
    usage();
    return 1;
  }

  len = strlen(argv[1]);
  if (len == 0) {
    puts("ERROR: no keys :: nothing to do");
    return 1;
  } else if (len > 42) {
    puts("ERROR: too much keys!");
    return 1;
  }

  calc_chain = parse_keys(len, argv[1]);
  if (calc_chain == NULL) {
    puts("ERROR: keys cannot be parsed");
    return 1;
  }

  f_image = fopen(argv[2], "r");
  if (f_image == NULL) {
    puts("ERROR: image cannot be open");
    return 2;
  }

  image = malloc(sizeof(image_t));
  if (image == NULL) {
    puts("OOPS: memory allocation problems :c");
  }

  error = image_parse(f_image, image);
  if (error != READ_OK) {
    puts("ERROR: image is corrupted");
    return error;
  }

  fclose(f_image);

  calc(calc_chain, len, image);

  f_image = fopen(argv[3], "w");

  if (write_image(f_image, image) != WRITE_OK) {
    puts("ERROR: image writing problems");
    return 3;
  }
  return 0;
}

void calc(void **calc_chain, size_t len, image_t *const image) {
  size_t i;
  for (i = 0; i < len; i++) {
    ((void (*)(image_t *)) *(calc_chain + i))(image);
  }
}

void **parse_keys(size_t keys_len, const char *keys) {
  size_t index = -1;
  void **chain = calloc(keys_len, sizeof(void *));
  if (chain == NULL || keys_len == 0) {
    return NULL;
  }

  while (++index < keys_len) {
    switch (keys[index]) {
      case 'a':chain[index] = &acid;
        break;
      case 'r':chain[index] = &rotation;
        break;
      case 'b':chain[index] = &blur;
        break;
      default:free(chain);
        return NULL;
    }
  }

  return chain;
}

read_status_t image_parse(FILE *const f_image, image_t *const image) {
  pixel_t *pixels;
  read_status_t error;

  struct bmp_file_header *header = malloc(sizeof(struct bmp_file_header));
  struct bmp_info *info = malloc(sizeof(struct bmp_info));

  error = read_header(f_image, header);
  if (error != READ_OK) {
    free(header);
    free(info);
    return error;
  }

  error = read_info(f_image, info);
  if (error != READ_OK) {
    free(header);
    free(info);
    return error;
  }
  image->width = info->bi_width;
  image->height = info->bi_height;

  pixels = malloc(sizeof(pixel_t) * image->width * image->height);
  error = read_pixels(f_image, header->bf_offb, pixels,
                      image->width,
                      image->height);
  if (error != READ_OK) {
    free(pixels);
    free(header);
    free(info);
    return error;
  }

  image->data = pixels;
  free(info);
  free(header);
  return READ_OK;
}

int contains(const char *string, char c) {
  return strchr(string, c) != NULL;
}

void usage() {
  puts("Usage: lab_05 [keys] file");
  puts("keys:");
  puts("\tr - rotation to 90 degree");
  puts("\tb - gaussian blur with radius 2");
  puts("\ta - some acid noise");
}

void rotation(image_t *const image) {
  rotate_90_degrees_left(image);
}

void blur(image_t *const image) {
  gaussian_blur(image);
}

void acid(image_t *const image) {
  image_acid(image);
}
