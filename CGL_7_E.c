#include <stdio.h>
#include <math.h>

#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)
#define NORM(v) (v.x * v.x + v.y * v.y)
#define POW(v) (v * v)

typedef struct { double x, y; } point_t;
typedef point_t vector_t;
typedef struct { point_t p0, p1; } segment_t;
typedef segment_t line_t;
typedef struct { point_t p; double r; } circle_t;

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

static vector_t plus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x + v2.x, v1.y + v2.y };
  return ret;
}

static point_t polar(point_t o, double r, double a) {
  point_t p = { r * cos(a), r * sin(a) };
  return plus(o, p);
}

static segment_t cross_points(circle_t c1, circle_t c2) {
  segment_t s;

  double dd = NORM(minus(c1.p, c2.p));
  double d = sqrt(dd);
  double cosA = (POW(c1.r) + dd - POW(c2.r)) / (2 * c1.r * d);
  double a = acos(cosA);
  vector_t vd = minus(c2.p, c1.p);
  double t = atan2(vd.y, vd.x);

  s.p0 = polar(c1.p, c1.r, t + a);
  s.p1 = polar(c1.p, c1.r, t - a);
  point_t tmp = s.p1;
  if (s.p0.x > tmp.x || (s.p0.x == tmp.x && s.p0.y > tmp.y)) {
    s.p1 = s.p0;
    s.p0 = tmp;
  }
  return s;
}

int main(int argc, char **argv) {
  circle_t c1, c2;

  scanf("%lf %lf %lf", &c1.p.x, &c1.p.y, &c1.r);
  scanf("%lf %lf %lf", &c2.p.x, &c2.p.y, &c2.r);
  segment_t s = cross_points(c1, c2);
  printf("%.8lf %.8lf %.8lf %.8lf\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);
}
