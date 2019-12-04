#include <stdlib.h>
#include <stdio.h>
#define P_KEY(i) (i / 2)
#define L_KEY(i) (i * 2)
#define R_KEY(i) (i * 2 + 1)

int main(int argc, char **argv) {
  int n, i;
  int *bh;

  scanf("%d", &n);
  bh = (int *) malloc(sizeof(int) * (n + 1));
  for (i = 1; i <= n; ++i) scanf("%d", &bh[i]);
  for (i = 1; i <= n; ++i) {
    printf("node %d: key = %d, ", i, bh[i]);
    if (P_KEY(i) >= 1) printf("parent key = %d, ", bh[P_KEY(i)]);
    if (L_KEY(i) <= n) printf("left key = %d, ", bh[L_KEY(i)]);
    if (R_KEY(i) <= n) printf("right key = %d, ", bh[R_KEY(i)]);
    printf("\n");
  }
  free(bh); exit(0);
}
