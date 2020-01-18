#include <stdio.h>

typedef struct { int x, y; } point_t;
typedef struct { point_t p0, p1; } segment_t;

static int get_type(segment_t s1, segment_t s2) {
  int k, l, m, n;

  k = s1.p0.x - s1.p1.x;
  l = s1.p0.y - s1.p1.y;
  m = s2.p0.x - s2.p1.x;
  n = s2.p0.y - s2.p1.y;
  if (k * n == l * m) return 2;
  if (-(k * m) == l * n) return 1;
  return 0;
}

int main(int argc, char **argv) {
  int q, i;
  segment_t s1, s2;

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%d %d %d %d %d %d %d %d",
        &s1.p0.x, &s1.p0.y, &s1.p1.x, &s1.p1.y,
        &s2.p0.x, &s2.p0.y, &s2.p1.x, &s2.p1.y);
    printf("%d\n", get_type(s1, s2));
  }
}
