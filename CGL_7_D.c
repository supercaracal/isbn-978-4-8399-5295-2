#include <stdio.h>
#include <math.h>
#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)
#define NORM(v) (v.x * v.x + v.y * v.y)
#define ABS(v) (sqrt(NORM(v)))

typedef struct { double x, y; } point_t;
typedef point_t vector_t;
typedef struct { point_t p0, p1; } segment_t;
typedef segment_t line_t;
typedef struct { point_t p; double r; } circle_t;

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

static vector_t divide(vector_t v, double s) {
  vector_t ret = { v.x / s, v.y / s };
  return ret;
}

static point_t projection(line_t l, point_t p) {
  vector_t base = minus(l.p1, l.p0);
  double r = DOT(minus(p, l.p0), base) / NORM(base);
  return plus(l.p0, multiple(base, r));
}

static segment_t cross_points(circle_t c, line_t l) {
  segment_t s;
  vector_t e, v, x, tmp;
  double base;

  x = projection(l, c.p);
  v = minus(l.p1, l.p0);
  e = divide(v, ABS(v));
  base = sqrt(c.r * c.r - NORM(minus(c.p, x)));
  v = multiple(e, base);
  s.p0 = plus(x, v);
  s.p1 = minus(x, v);
  if (s.p0.x > s.p1.x || (s.p0.x == s.p1.x && s.p0.y > s.p1.y)) {
    tmp = s.p0;
    s.p0 = s.p1;
    s.p1 = tmp;
  }
  return s;
}

int main(int argc, char **argv) {
  circle_t c;
  line_t l;
  segment_t s;
  int q, i;

  scanf("%lf %lf %lf %d", &c.p.x, &c.p.y, &c.r, &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf %lf %lf", &l.p0.x, &l.p0.y, &l.p1.x, &l.p1.y);
    s = cross_points(c, l);
    printf("%.8lf %.8lf %.8lf %.8lf\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);
  }
}
