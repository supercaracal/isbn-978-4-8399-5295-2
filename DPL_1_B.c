#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_W 10000
#define SELECTED 1
#define DISCARDED 0

typedef struct { int v, w; } item_t;

int main(int argc, char **argv) {
  int n, w, i, j, vs[MAX_N+1][MAX_W+1];
  item_t is[MAX_N+1];

  scanf("%d %d", &n, &w);
  for (i = 1; i <= n; ++i) scanf("%d %d", &is[i].v, &is[i].w);
  for (i = 0; i <= n; ++i) vs[i][0] = 0;
  for (i = 0; i <= w; ++i) vs[0][i] = 0;
  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= w; ++j) {
      if (is[i].w > j || vs[i-1][j] > vs[i-1][j-is[i].w] + is[i].v) {
        vs[i][j] = vs[i-1][j];
        continue;
      }
      vs[i][j] = vs[i-1][j-is[i].w] + is[i].v;
    }
  }
  printf("%d\n", vs[n][w]);
}
