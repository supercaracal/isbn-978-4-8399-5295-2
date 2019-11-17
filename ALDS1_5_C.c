#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define COS60 (1.0 / 2.0)
#define SIN60 (1.73205080757 / 2.0)

typedef struct point { double x, y; } p_t;

static void koch(int d, p_t p1, p_t p2) {
  p_t s, t, u;

  if (d-- <= 0) return;

  /*
   *  m * x2 + n * x1
   * -----------------
   *       m + n
   */
  s.x = (1.0 * p2.x + 2.0 * p1.x) / (1.0 + 2.0);
  s.y = (1.0 * p2.y + 2.0 * p1.y) / (1.0 + 2.0);
  t.x = (2.0 * p2.x + 1.0 * p1.x) / (2.0 + 1.0);
  t.y = (2.0 * p2.y + 1.0 * p1.y) / (2.0 + 1.0);
  /*
   * (cosX, -sinX) (x)
   * (sinX,  cosX) (y)
   */ 
  u.x = COS60 * (t.x - s.x) - SIN60 * (t.y - s.y) + s.x;
  u.y = SIN60 * (t.x - s.x) + COS60 * (t.y - s.y) + s.y;

  koch(d, p1, s);
  printf("%f %f\n", s.x, s.y);
  koch(d, s, u);
  printf("%f %f\n", u.x, u.y);
  koch(d, u, t);
  printf("%f %f\n", t.x, t.y);
  koch(d, t, p2);
}

int main(int argc, char **argv) {
  int d, ret;
  p_t p1 = {0.0, 0.0};
  p_t p2 = {100.0, 0.0};

  ret = scanf("%d", &d);
  if (errno != 0) perror("scanf: d");
  if (ret < 1) exit(1);

  printf("%f %f\n", p1.x, p1.y);
  koch(d, p1, p2);
  printf("%f %f\n", p2.x, p2.y);

  exit(0);
}
