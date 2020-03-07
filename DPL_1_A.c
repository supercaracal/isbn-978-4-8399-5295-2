#include <stdio.h>

#define MAX_COINS 20
#define MAX_DENOMINATIONS 50000
#define INF (1 << 30)

int main(int argc, char **argv) {
  int n, m, i, j, c[MAX_COINS], d[MAX_DENOMINATIONS+1];

  scanf("%d %d", &n, &m);
  for (i = 0; i < m; ++i) scanf("%d", &c[i]);
  for (i = 0; i <= n; ++i) d[i] = i > 0 ? INF : 0;
  for (i = 0; i < m; ++i) {
    for (j = c[i]; j <= n; ++j) {
      if (d[j] < d[j-c[i]]+1) continue;
      d[j] = d[j-c[i]] + 1;
    }
  }
  printf("%d\n", d[n]);
}
