#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void counting_sort(int *a, int *b, int *c, int n, int k) {
  int i;

  for (i = 0; i < k; ++i) c[i] = 0;
  for (i = 0; i < n; ++i) ++c[a[i]];
  for (i = 1; i < k; ++i) c[i] += c[i - 1];
  for (i = n - 1; i >= 0; --i) {
    b[c[a[i]] - 1] = a[i];
    --c[a[i]];
  }
}

int main(int argc, char **argv) {
  int n, ret, i, max;
  int *a;
  int *b;
  int *c;

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  a = (int *) malloc(sizeof(int) * n);
  if (a == NULL) exit(1);

  for (i = max = 0; i < n; ++i) {
    ret = scanf("%d", &a[i]);
    if (errno != 0) perror("scanf: a[i]");
    if (ret < 1) break;
    if (a[i] > max) max = a[i];
  }

  b = (int *) malloc(sizeof(int) * n);
  if (b == NULL) {
    free(a); exit(1);
  }

  c = (int *) malloc(sizeof(int) * (max + 1));
  if (c == NULL) {
    free(a); free(b); exit(1);
  }

  counting_sort(a, b, c, n, max + 1);

  for (i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    printf("%d", b[i]);
  }
  printf("\n");

  free(a); free(b); free(c); exit(0);
}
