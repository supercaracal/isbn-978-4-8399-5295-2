#include <stdio.h>
#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)
#define NORM(v) (v.x * v.x + v.y * v.y)

typedef struct { double x, y; } point_t;
typedef point_t vector_t;
typedef struct { point_t p0, p1; } segment_t;
typedef segment_t line_t;

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

static int clockwise(segment_t s, point_t p) {
  vector_t a = minus(s.p1, s.p0);
  vector_t b = minus(p, s.p0);
  double c = CROSS(a, b);
  double d = DOT(a, b);
  double na = NORM(a);
  double nb = NORM(b);
  if (c > 0.0) return 1;
  if (c < 0.0) return -1;
  if (d < 0.0) return 1;
  if (nb > na) return -1;
  return 0;
}

int main(int argc, char **argv) {
  int q, i, k, l;
  segment_t s1, s2;

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
        &s1.p0.x, &s1.p0.y, &s1.p1.x, &s1.p1.y,
        &s2.p0.x, &s2.p0.y, &s2.p1.x, &s2.p1.y);
    k = clockwise(s1, s2.p0) * clockwise(s1, s2.p1);
    l = clockwise(s2, s1.p0) * clockwise(s2, s1.p1);
    printf("%d\n", k <= 0 && l <= 0);
  }
}
