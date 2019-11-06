#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20000
#define PLOT_DOWN '\\'
#define PLOT_FLAT '_'
#define PLOT_UP '/'

typedef enum plot {SEA, DOWN, FLAT, UP} plot_t;

typedef struct landform {
  plot_t *p;
  int v_size, h_size, offset;
} landform_t;

static void
read_landform(FILE *f, landform_t *lf) {
  char buf[MAX_SIZE];
  char *ret;
  int i, top, bottom, curr, tmp;
  char prev;

  ret = fgets(buf, MAX_SIZE, f);
  if (ret == NULL) return;
  while (buf[lf->h_size] != '\n' && buf[lf->h_size] != '\0') lf->h_size++;

  lf->p = malloc(sizeof(plot_t) * lf->h_size);
  if (lf->p == NULL) return;

  for (i = top = bottom = curr = 0, prev = '\0'; i < lf->h_size; prev = buf[i++]) {
    switch (buf[i]) {
      case PLOT_DOWN:
        lf->p[i] = DOWN;
        if (prev == PLOT_DOWN || prev == PLOT_FLAT) ++curr;
        break;
      case PLOT_FLAT:
        lf->p[i] = FLAT;
        if (prev == PLOT_UP) --curr;
        break;
      case PLOT_UP:
        lf->p[i] = UP;
        if (prev == PLOT_UP) --curr;
        break;
    }
    if (curr < top) top = curr;
    if (curr > bottom) bottom = curr;
  }

  tmp = top - bottom;
  lf->v_size = (tmp < 0 ? -tmp : tmp) + 1;
  tmp = top - 0;
  lf->offset = tmp < 0 ? -tmp : tmp;
}

static void
print_landform(FILE *f, landform_t *lf) {
  char **matrix;
  int i, j, y;
  plot_t prev;

  matrix = malloc(sizeof(char *) * lf->v_size);
  if (matrix == NULL) return;

  for (i = 0; i < lf->v_size; ++i) {
    matrix[i] = malloc(sizeof(char) * lf->h_size);
    if (matrix == NULL) break;
    for (j = 0; j < lf->h_size; ++j) matrix[i][j] = ' ';
  }

  for (i = 0, y = lf->offset, prev = SEA; i < lf->h_size; prev = lf->p[i++]) {
    switch (lf->p[i]) {
      case DOWN:
        if (prev == DOWN || prev == FLAT) ++y;
        matrix[y][i] = PLOT_DOWN;
        break;
      case FLAT:
        if (prev == UP) --y;
        matrix[y][i] = PLOT_FLAT;
        break;
      case UP:
        if (prev == UP) --y;
        matrix[y][i] = PLOT_UP;
        break;
      default:
        break;
    }
  }

  for (i = 0; i < lf->v_size; ++i) {
    for (j = 0; j < lf->h_size; ++j) fprintf(f, "%c", matrix[i][j]);
    fprintf(f, "\n");
    free(matrix[i]);
  }
  free(matrix);
}

int main(int argc, char **argv) {
  landform_t lf = {NULL, 0, 0};

  read_landform(stdin, &lf);
  print_landform(stdout, &lf);

  free(lf.p);
  exit(0);
}
