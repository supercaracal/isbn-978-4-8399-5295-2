#include <stdio.h>
#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
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

static point_t project(line_t l, point_t p) {
  vector_t base = minus(l.p1, l.p0);
  double r = DOT(minus(p, l.p0), base) / NORM(base);
  return plus(l.p0, multiple(base, r));
}

static point_t reflect(line_t l, point_t p) {
  return plus(p, multiple(minus(project(l, p), p), 2.0));
}

int main(int argc, char **argv) {
  line_t l;
  point_t p;
  int q, i;

  scanf("%lf %lf %lf %lf", &l.p0.x, &l.p0.y, &l.p1.x, &l.p1.y);
  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf", &p.x, &p.y);
    p = reflect(l, p);
    printf("%.10lf %.10lf\n", p.x, p.y);
  }
}
