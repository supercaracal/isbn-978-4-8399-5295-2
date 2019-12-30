#include <stdio.h>
#include <stdlib.h>

static int find_representative(int *a, int i) {
  if (i != a[i]) a[i] = find_representative(a, a[i]);
  return a[i];
}

int main(int argc, char **argv) {
  int n, q, i, c, x, y;
  int *a;

  scanf("%d %d", &n, &q);
  a = (int *) malloc(sizeof(int) * n);
  for (i = 0; i < n; ++i) a[i] = i;
  for (i = 0; i < q; ++i) {
    scanf("%d %d %d", &c, &x, &y);
    switch (c) {
      case 0:
        a[find_representative(a, x)] = find_representative(a, y);
        break;
      case 1:
        printf("%d\n", find_representative(a, x) == find_representative(a, y));
        break;
    }
  }
  free(a);
}
