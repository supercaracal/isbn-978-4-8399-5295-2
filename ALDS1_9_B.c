#include <stdlib.h>
#include <stdio.h>
#define P_KEY(i) (i / 2)
#define L_KEY(i) (i * 2)
#define R_KEY(i) (i * 2 + 1)

static void max_heapify(int *bh, int i, int n) {
  int l, r, m, tmp;

  l = L_KEY(i);
  r = R_KEY(i);
  m = i;
  if (l <= n && bh[l] > bh[i]) m = l;
  if (r <= n && bh[r] > bh[m]) m = r;
  if (m != i) {
    tmp = bh[i];
    bh[i] = bh[m];
    bh[m] = tmp;
    max_heapify(bh, m, n);
  }
}

int main(int argc, char **argv) {
  int n, i;
  int *bh;

  scanf("%d", &n);
  bh = (int *) malloc(sizeof(int) * (n + 1));
  for (i = 1; i <= n; ++i) scanf("%d", &bh[i]);
  for (i = n / 2; i > 0; --i) max_heapify(bh, i, n);
  for (i = 1; i <= n; ++i) printf(" %d", bh[i]);
  printf("\n"); free(bh); exit(0);
}
