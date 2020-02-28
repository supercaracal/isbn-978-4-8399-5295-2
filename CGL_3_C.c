#include <stdio.h>
#include <math.h>

#define MAX_N 100
#define IN 2
#define ON 1
#define OUT 0
#define EPS (1e-10)

#define DOT(v1, v2) (v1.x * v2.x + v1.y * v2.y)
#define CROSS(v1, v2) (v1.x * v2.y - v1.y * v2.x)

typedef struct { double x, y; } point_t;
typedef point_t vector_t;

static vector_t minus(vector_t v1, vector_t v2) {
  vector_t ret = { v1.x - v2.x, v1.y - v2.y };
  return ret;
}

static int contains(point_t *g, int size, point_t q) {
  vector_t a, b, tmp;
  double c, d;
  int i, intersect;

  for (i = intersect = 0; i < size; ++i) {
    a = minus(g[i], q);
    b = minus(g[(i + 1) % size], q);
    c = CROSS(a, b);
    d = DOT(a, b);
    if (fabs(c) < EPS && d < EPS) return ON;
    if (a.y > b.y) {
      tmp = a;
      a = b;
      b = tmp;
    }
    c = CROSS(a, b);
    d = DOT(a, b);
    if (a.y < EPS && EPS < b.y && c > EPS) ++intersect;
  }

  return intersect % 2 ? IN : OUT;
}

int main(int argc, char **argv) {
  int n, m, i;
  point_t q, g[MAX_N];

  scanf("%d", &n);
  for (i = 0; i < n; ++i) scanf("%lf %lf", &g[i].x, &g[i].y);

  scanf("%d", &m);
  for (i = 0; i < m; ++i) {
    scanf("%lf %lf", &q.x, &q.y);
    printf("%d\n", contains(g, n, q));
  }
}
