#include <stdio.h>

int main(void) {
  int width = 1200;
  int height = 800;
  int max_inter = 1000;

  FILE *fp = fopen("mandelbrot.ppm", "w");
  if (fp == NULL) {
    printf("yo shits fuckin up nigga took the (L)");
    return 1;
  }

  fprintf(fp, "P3\n");
  fprintf(fp, "%d %d\n", width, height);
  fprintf(fp, "255\n");

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      double c_re = -2.0 + (x * 3.0 / width);
      double c_im = -1.2 + (y * 2.4 / height);

      double x_val = 0.0;
      double y_val = 0.0;
      int inter = 0;

      while ((x_val * x_val + y_val * y_val <= 4.0) && (inter < max_inter)) {
        double x_new = x_val * x_val - y_val * y_val + c_re;
        y_val = 2.0 * x_val * y_val + c_im;
        x_val = x_new;
        inter++;
      }
      int r, g, b;

      if (inter == max_inter) {
        r = 0;
        g = 0;
        b = 0;
      } else {
        r = (inter * 7) % 255;
        g = (inter * 5) % 255;
        b = (inter * 11) % 255;
      }
      fprintf(fp, "%d %d %d\n", r, g, b);
    }
  }
  fclose(fp);
  printf("this shit work nigga");
  return 0;
}
