#include "verticles.h"
#include "../io/bmp_io.h"

int main(int argc, char *argv[]) {
  FILE *f_verticles;
  FILE *f_edges;
  FILE *f_image;

  if(argc != 4) {
    usage();
    return 1;
  }

  f_verticles = fopen(argv[1], "r");
  f_edges = fopen(argv[2], "r");
  f_image = fopen(argv[3], "w");

  int n;
  int x, y, z;
  fscanf(f_verticles, "%d\n", &n);
  printf("%d\n", n);
  while( ! feof(f_verticles) ) {
    fscanf(f_verticles, "%d %d %d\n", &x, &y, &z);
    printf("%d %d %d\n", x, y, z);
  }

  image_t image;
  image.height = 1000;
  image.width = 1000;
}

void usage() {

}