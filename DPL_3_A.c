#include <stdio.h>
#include <stdlib.h>

typedef struct { int h, w, **c; } square_t;

static int largest_square(square_t s) {
  int i, j, max;

  for (i = max = 0; i < s.h; ++i) {
    for (j = 0; j < s.w; ++j) {
      if (s.c[i][j] > 0) {
        s.c[i][j] = 0;
      } else if (i == 0 || j == 0) {
        s.c[i][j] = !s.c[i][j];
      } else if (s.c[i-1][j-1] <= s.c[i-1][j] && s.c[i-1][j-1] <= s.c[i][j-1]) {
        s.c[i][j] = s.c[i-1][j-1] + 1;
      } else if (s.c[i-1][j] <= s.c[i-1][j-1] && s.c[i-1][j] <= s.c[i][j-1]) {
        s.c[i][j] = s.c[i-1][j] + 1;
      } else {
        s.c[i][j] = s.c[i][j-1] + 1;
      }
      if (max < s.c[i][j]) max = s.c[i][j];
    }
  }
  return max * max;
}

int main(int argc, char **argv) {
  square_t s;
  int i, j;

  scanf("%d %d", &s.h, &s.w);
  s.c = (int **) malloc(sizeof(int *) * s.h);
  for (i = 0; i < s.h; ++i) {
    s.c[i] = (int *) malloc(sizeof(int) * s.w);
    for (j = 0; j < s.w; ++j) scanf("%d", &s.c[i][j]);
  }
  printf("%d\n", largest_square(s));
  for (i = 0; i < s.h; ++i) free(s.c[i]);
  free(s.c);
}
