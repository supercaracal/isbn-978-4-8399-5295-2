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

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

// @see http://www5d.biglobe.ne.jp/~tomoya03/shtml/algorithm/Intersection.htm
// (y - q) = slope * (x - p)
static int intersect(segment_t s1, segment_t s2) {
  double t1, t2, t3, t4;

  //    *******                                               *******
  t1 = (s1.p0.y - s2.p0.y) * (s2.p0.x - s2.p1.x) + (s2.p0.x - s1.p0.x) * (s2.p0.y - s2.p1.y);
  t2 = (s1.p1.y - s2.p0.y) * (s2.p0.x - s2.p1.x) + (s2.p0.x - s1.p1.x) * (s2.p0.y - s2.p1.y);
  t3 = (s2.p0.y - s1.p0.y) * (s1.p0.x - s1.p1.x) + (s1.p0.x - s2.p0.x) * (s1.p0.y - s1.p1.y);
  t4 = (s2.p1.y - s1.p0.y) * (s1.p0.x - s1.p1.x) + (s1.p0.x - s2.p1.x) * (s1.p0.y - s1.p1.y);
  return (t1 * t2 < 0.0) && (t3 * t4 < 0.0);
}

static double distance(segment_t s1, segment_t s2) {
  int i;
  double min, d;
  segment_t s;
  point_t p;

  if (intersect(s1, s2)) return 0.0;
  struct { segment_t s; point_t p; } list[4] = {{s1, s2.p0}, {s1, s2.p1}, {s2, s1.p0}, {s2, s1.p1}};
  for (i = 0, min = -1.0; i < 4; ++i) {
    s = list[i].s;
    p = list[i].p;
    if (DOT(minus(s.p0, s.p1), minus(p, s.p1)) < 0.0) {
      d = ABS(minus(p, s.p1));
    } else if (DOT(minus(s.p1, s.p0), minus(p, s.p0)) < 0.0) {
      d = ABS(minus(p, s.p0));
    } else {
      d = CROSS(minus(s.p0, s.p1), minus(p, s.p1)) / ABS(minus(s.p0, s.p1));
      if (d < 0.0) d = -d;
    }
    if (min < 0.0 || d < min) min = d;
  }
  return min;
}

int main(int argc, char **argv) {
  int q, i;
  segment_t s1, s2;

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
        &s1.p0.x, &s1.p0.y, &s1.p1.x, &s1.p1.y,
        &s2.p0.x, &s2.p0.y, &s2.p1.x, &s2.p1.y);
    printf("%.10lf\n", distance(s1, s2));
  }
}
