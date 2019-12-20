#include <stdio.h>
#define MAX_SIZE 101
int main(int argc, char **argv) {
  int n, i, j, k, l, m, g[MAX_SIZE][MAX_SIZE];

  for (i = 0; i < MAX_SIZE; ++i) {
    for (j = 0; j < MAX_SIZE; ++j) {
      g[i][j] = 0;
    }
  }

  scanf("%d", &n);

  for (i = 0; i < n; ++i) {
    scanf("%d %d", &k, &l);
    for (j = 0; j < l; ++j) {
      scanf("%d", &m);
      ++g[k][m];
    }
  }

  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= n; ++j) {
      if (j > 1) printf(" ");
      printf("%d", g[i][j]);
    }
    printf("\n");
  }
}
