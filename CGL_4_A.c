#include <stdio.h>
#include <stdlib.h>

#define EPS (1e-10)
#define DEFAULT_STACK_SIZE 16
#define SENTINEL (1 << 30)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)

typedef struct { double x, y; } point_t;
typedef point_t vector_t;
typedef struct { point_t p0, p1; } segment_t;
typedef segment_t line_t;
typedef struct { int size, i; point_t *p; } point_set_t;

static point_set_t new_stack(void) {
  point_set_t stk = { DEFAULT_STACK_SIZE, 0, NULL };
  stk.p = (point_t *) malloc(sizeof(point_t) * stk.size);
  return stk;
}

static void push_stack(point_set_t *stk, point_t p) {
  if (stk->size == stk->i) {
    stk->size *= 2;
    stk->p = (point_t *) realloc(stk->p, sizeof(point_t) * stk->size);
  }
  stk->p[stk->i++] = p;
}

static point_t pop_stack(point_set_t *stk) {
  point_t p = { 0.0, 0.0 };
  if (stk->i == 0) return p;
  return stk->p[--stk->i];
}

static void merge(point_t *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  point_t *l, *r;

  n1 = mid - left;
  l = (point_t *) malloc(sizeof(point_t) * (n1 + 1));
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i].x = SENTINEL;

  n2 = right - mid;
  r = (point_t *) malloc(sizeof(point_t) * (n2 + 1));
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i].x = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i].x < r[j].x || (l[i].x == r[j].x && l[i].y < r[j].y)) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }
  free(l); free(r);
}

static void merge_sort(point_t *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static void reverse_sort(point_t *a, int size) {
  int i, j;
  point_t tmp;

  for (i = 0, j = size - 1; j - i >= 1; ++i, --j) {
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
}

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

static int is_counter_clockwise(segment_t s, point_t p) {
  vector_t a = minus(s.p1, s.p0);
  vector_t b = minus(p, s.p0);
  return CROSS(a, b) > EPS;
}

static point_set_t convex_hull_by_andrew(point_set_t *ps) {
  point_set_t su, sl, ch;
  segment_t seg;
  point_t start;
  int i, j;
  
  su = new_stack();
  sl = new_stack();
  merge_sort(ps->p, 0, ps->size);

  // upper hull
  for (i = 0; i < ps->size; ++i) {
    while (su.i > 1) {
      seg.p1 = su.p[su.i - 1];
      seg.p0 = su.p[su.i - 2];
      if (!is_counter_clockwise(seg, ps->p[i])) break;
      pop_stack(&su);
    }
    push_stack(&su, ps->p[i]);
  }

  // lower hull
  for (i = ps->size - 1; i >= 0; --i) {
    while (sl.i > 1) {
      seg.p1 = sl.p[sl.i - 1];
      seg.p0 = sl.p[sl.i - 2];
      if (!is_counter_clockwise(seg, ps->p[i])) break;
      pop_stack(&sl);
    }
    push_stack(&sl, ps->p[i]);
  }

  // merge upper into reversed lower
  reverse_sort(sl.p, sl.i);
  for (i = su.i - 2; i >= 1; --i) push_stack(&sl, su.p[i]);
  free(su.p);

  // rotate
  ch = new_stack();
  start = sl.p[0];
  for (i = 0; i < sl.i; ++i) {
    if (sl.p[i].y < start.y || (sl.p[i].y == start.y && sl.p[i].x < start.x)) {
      start = sl.p[i];
      j = i;
    }
  }
  for (i = 0; i < sl.i; ++i) {
    push_stack(&ch, sl.p[j++]);
    if (j == sl.i) j = 0;
  }
  free(sl.p);

  return ch;
}

int main(int argc, char **argv) {
  point_set_t ps, ch;
  int i;

  scanf("%d", &ps.size);
  ps.p = (point_t *) malloc(sizeof(point_t) * ps.size);
  for (i = 0; i < ps.size; ++i) scanf("%lf %lf", &ps.p[i].x, &ps.p[i].y);

  ch = convex_hull_by_andrew(&ps);
  printf("%d\n", ch.i);
  for (i = 0; i < ch.i; ++i) printf("%.0lf %.0lf\n", ch.p[i].x, ch.p[i].y);

  free(ps.p);
  free(ch.p);
}
