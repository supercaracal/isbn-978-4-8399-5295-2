#include <stdio.h>
#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)
#define NORM(v) (v.x * v.x + v.y * v.y)

typedef struct { double x, y; } point_t;
typedef point_t vector_t;
typedef struct { point_t p0, p1; } segment_t;
typedef segment_t line_t;

static vector_t plus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x + v2.x, v1.y + v2.y };
  return ret;
}

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

static vector_t multiple(vector_t v, double s) {
  vector_t ret = { v.x * s, v.y * s };
  return ret;
}

/*
 *                   s2.p1
 *                  /|
 *              1-t/ |h2
 *                /  |
 * s1.p0 ------------------- s1.p1
 *            |  /
 *          h1| /t
 *            |/
 *            s2.p0
 */
static point_t cross_point(segment_t s1, segment_t s2) {
  vector_t v1, v2;
  double h1, h2, t;

  v1 = minus(s1.p1, s1.p0);
  v2 = minus(s2.p0, s1.p0);
  h1 = CROSS(v1, v2); // h1 * ABS(v1)
  if (h1 < 0.0) h1 = -h1;
  v2 = minus(s2.p1, s1.p0);
  h2 = CROSS(v1, v2); // h2 * ABS(v1)
  if (h2 < 0.0) h2 = -h2;
  t = h1 / (h1 + h2); // reduce ABS(v1)
  return plus(s2.p0, multiple(minus(s2.p1, s2.p0), t));
}

int main(int argc, char **argv) {
  int q, i;
  segment_t s1, s2;
  point_t p;

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
        &s1.p0.x, &s1.p0.y, &s1.p1.x, &s1.p1.y,
        &s2.p0.x, &s2.p0.y, &s2.p1.x, &s2.p1.y);
    p = cross_point(s1, s2);
    printf("%.10lf %.10lf\n", p.x, p.y);
  }
}
