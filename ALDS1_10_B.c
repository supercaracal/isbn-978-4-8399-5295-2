#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
typedef struct { int r, c; } md_t;

static void matrix_chain_multiplication(md_t *md, int n, int m[MAX_N][MAX_N]) {
  int i, j, k, l, cost;

  for (l = 2; l < n + 1; ++l) {
    for (i = 0; i < n - l + 1; ++i) {
      j = i + l - 1;
      m[i][j] = -1;
      for (k = i; k < j; ++k) {
        cost = m[i][k] + m[k + 1][j] + md[i].r * md[k].c * md[j].c;
        if (m[i][j] == -1 || cost < m[i][j]) m[i][j] = cost;
      }
    }
  }
}

int main(int argc, char **argv) {
  int n, i, j, m[MAX_N][MAX_N];
  md_t md[MAX_N];

  scanf("%d", &n);
  for (i = 0; i < n; ++i) scanf("%d %d", &md[i].r, &md[i].c);
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) m[i][j] = 0;
  }
  matrix_chain_multiplication(md, n, m);
  printf("%d\n", m[0][n - 1]);
  exit(0);
}
