#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
  int n, ret, i, j, x, tmp, k;
  int a[100000];

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  for (i = 0; i < n; ++i) {
    ret = scanf("%d", &a[i]);
    if (errno != 0) perror("scanf: a[i]");
    if (ret < 1) break;
  }
  x = a[n - 1];

  for (i = -1, j = 0; j < n - 1; ++j) {
    if (a[j] > x) continue;

    tmp = a[++i];
    a[i] = a[j];
    a[j] = tmp;
  }
  tmp = a[++i];
  a[i] = a[n - 1];
  a[n - 1] = tmp;
  k = i;

  for (i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    if (i == k) printf("[");
    printf("%d", a[i]);
    if (i == k) printf("]");
  }
  printf("\n");

  exit(0);
}
