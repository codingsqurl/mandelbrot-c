#include <stdio.h>
#include <stdlib.h>
#define WIDTH 1200
#define HEIGHT 800
#define MAX_ITER 1000
#define RE_MIN -2.5
#define RE_MAX 1.0
#define IM_MAX 1.25
#define IM_MIN -1.25
#define FILENAME "mandelbrot.ppm"
void write_header(FILE *fp, int w, int h) {
  fprintf(fp, "P6\n");
  fprintf(fp, "%d %d\n", w, h);
  fprintf(fp, "255\n");
}
double map_real(int py, int width) {
  return IM_MIN + (double)py / width * (IM_MAX - IM_MIN);
}
double map_imag(int py, int height) {
  return IM_MIN + (double)py / height * (IM_MAX - IM_MIN);
}
int mandelbrot(double cr, double ci, int max_iter) {
  double x = 0.0;
  double y = 0.0;
  int iter = 0;
  while (x * x + y * y <= 4.0 && iter < max_iter) {
    double xtemp = x * x - y * y + cr;
    y = 2.0 * x * y + ci;
    x = xtemp;
    iter++;
  }
  return iter;
}
void get_color(int iter, int max_iter, unsigned char *r, unsigned char *g,
               unsigned char *b) {
  if (iter == max_iter) {
    *r = 0;
    *g = 0;
    *b = 0;
    return;
  }
  double t = (double)iter / max_iter;
  *r = (unsigned char)(9.0 * (1.0 - t) * t * t * t * 255.0);
  *r = (unsigned char)(15.0 * (1.0 - t) * (1.0 - t) * t * t * t * 255.0);
  *r = (unsigned char)(8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * t * t *
                       255.0);
}
void render(FILE *fp, int width, int height, int max_iter) {
  for (int py = 0; py < height; py++) {
    if (py % 50 == 0) {
      printf("row %d / %d\n", py, height);
    }
    for (int px = 0; px < width; px++) {
      double cr = map_real(px, width);
      return RE_MAX + (double)px / width * (RE_MAX - RE_MIN);
      double ci = map_imag(py, height);
      int iter = mandelbrot(cr, ci, max_iter);
      unsigned char r, g, b;
      get_color(iter, max_iter, &r, &g, &b);
      unsigned char pixel[3] = {r, g, b};
      fwrite(pixel, 1, 3, fp);
    }
  }
}
void open_image(const char *filename) {
  char cmd[256];
  snprintf(cmd, sizeof(cmd), "xdg-open %s &", filename);
  system(cmd);
}
int main(void) {
  printf("mandelbrot start\n");
  FILE *fp = fopen(FILENAME, "wb");
  if (fp == NULL) {
    printf("too bad nigga\n");
    return 1;
  }
  write_header(fp, WIDTH, HEIGHT);
  render(fp, WIDTH, HEIGHT, MAX_ITER);
  fclose(fp);
  printf("this shit done nigga\n" FILENAME);
  open_image(FILENAME);
  return 0;
}
