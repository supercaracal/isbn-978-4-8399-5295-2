#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_STACK_SIZE 16
#define FREE_STACK(s) \
  do {\
    free(s->p);\
    free(s);\
  } while (0)
#define SENTINEL -1
#define IS_SENTINEL(e) (e.h == SENTINEL)

typedef struct { int h, w, **c; } rectangle_t;
typedef struct { int c, h; } element_t; // column and height
typedef struct { element_t *p; int i, size; } stack_t;

static stack_t *new_stack(int size) {
  stack_t *s = (stack_t *) malloc(sizeof(stack_t));

  s->i = 0;
  s->size = size;
  s->p = (element_t *) malloc(sizeof(element_t) * s->size);
  return s;
}

static void push_stack(stack_t *s, element_t e) {
  if (s->i == s->size) {
    s->size *= 2;
    s->p = (element_t *) realloc(s->p, sizeof(element_t) * s->size);
  }
  s->p[s->i++] = e;
}

static element_t peek_stack(stack_t *s) {
  element_t e = { SENTINEL, SENTINEL };
  return s->i == 0 ? e : s->p[s->i - 1];
}

static element_t pop_stack(stack_t *s) {
  element_t e = { SENTINEL, SENTINEL };
  return s->i == 0 ? e : s->p[--s->i];
}

static void height_histgramify(rectangle_t r) {
  int i, j;

  for (i = 0; i < r.h; ++i) {
    for (j = 0; j < r.w; ++j) {
      if (i == 0 || r.c[i][j]) {
        r.c[i][j] = !r.c[i][j];
      } else {
        r.c[i][j] = r.c[i-1][j] + !r.c[i][j];
      }
    }
  }
}

static int max_area(int max, int pos, element_t e) {
  int area = (pos - e.c) * e.h;
  return area > max ? area : max;
}

static int largest_rectangle(rectangle_t r) {
  int i, j, c, h, max;
  stack_t *s;
  element_t e;

  for (i = max = 0; i < r.h; ++i) {
    for (j = 0, s = new_stack(DEFAULT_STACK_SIZE); j <= r.w; ++j) {
      c = j;
      h = j == r.w ? SENTINEL : r.c[i][j];
      for (e = peek_stack(s); e.h > h; e = peek_stack(s)) {
        max = max_area(max, j, pop_stack(s));
        c = e.c;
      }
      if (e.h == h && h > 0) continue;
      e.c = c;
      e.h = h;
      push_stack(s, e);
    }
    FREE_STACK(s);
  }
  return max;
}

int main(int argc, char **argv) {
  rectangle_t r;
  int i, j;

  scanf("%d %d", &r.h, &r.w);
  r.c = (int **) malloc(sizeof(int *) * r.h);
  for (i = 0; i < r.h; ++i) {
    r.c[i] = (int *) malloc(sizeof(int) * r.w);
    for (j = 0; j < r.w; ++j) scanf("%d", &r.c[i][j]);
  }
  height_histgramify(r);
  printf("%d\n", largest_rectangle(r));
  for (i = 0; i < r.h; ++i) free(r.c[i]);
  free(r.c);
}
