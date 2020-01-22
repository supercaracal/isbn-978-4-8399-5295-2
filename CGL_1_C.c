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

static char *clockwise(segment_t s, point_t p) {
  vector_t a = minus(s.p1, s.p0);
  vector_t b = minus(p, s.p0);
  double c = CROSS(a, b);
  double d = DOT(a, b);
  double na = NORM(a);
  double nb = NORM(b);
  if (c > 0.0) return "COUNTER_CLOCKWISE";
  if (c < 0.0) return "CLOCKWISE";
  if (d < 0.0) return "ONLINE_BACK";
  if (nb > na) return "ONLINE_FRONT";
  return "ON_SEGMENT";
}

int main(int argc, char **argv) {
  int q, i;
  segment_t s;
  point_t p;

  scanf("%lf %lf %lf %lf", &s.p0.x, &s.p0.y, &s.p1.x, &s.p1.y);
  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%lf %lf", &p.x, &p.y);
    printf("%s\n", clockwise(s, p));
  }
}
