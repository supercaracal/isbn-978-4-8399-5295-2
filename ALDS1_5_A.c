#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int
can_build(int *a, int n, int m) {
  if (m == 0) return 1;
  if (m < 0 || n <= 0) return 0;
  --n;
  return (can_build(a, n, m) || can_build(a, n, m - a[n]));
}

int main(int argc, char **argv) {
  int ret, n, i, q, m;
  int a[20];

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  for (i = 0; i < n; ++i) {
    ret = scanf("%d", &a[i]);
    if (errno != 0) perror("scanf: a[i]");
    if (ret < 1) break;
  }

  ret = scanf("%d", &q);
  if (errno != 0) perror("scanf: q");
  if (ret < 1) exit(1);

  for (i = 0; i < q; ++i) {
    ret = scanf("%d", &m);
    if (errno != 0) perror("scanf: m[i]");
    if (ret < 1) break;
    printf("%s\n", can_build(a, n, m) ? "yes" : "no");
  }

  exit(0);
}
