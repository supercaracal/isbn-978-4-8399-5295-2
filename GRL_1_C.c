#include <stdio.h>
#include <stdlib.h>
#define MAX_V 100
#define INF_COST (1LL << 62)

static void warshall_floyd(long long g[MAX_V][MAX_V], int size) {
  int i, j, k;
  long long cost;

  for (k = 0; k < size; ++k) {
    for (i = 0; i < size; ++i) {
      if (g[i][k] == INF_COST) continue;
      for (j = 0; j < size; ++j) {
        if (g[k][j] == INF_COST) continue;
        cost = g[i][k] + g[k][j];
        if (cost < g[i][j]) g[i][j] = cost;
      }
    }
  }
}

int main(int argc, char **argv) {
  int v, e, i, j, s, t, d;
  long long g[MAX_V][MAX_V];

  for (i = 0; i < MAX_V; ++i) {
    for (j = 0; j < MAX_V; ++j) g[i][j] = i == j ? 0LL : INF_COST;
  }
  scanf("%d %d", &v, &e);
  for(i = 0; i < e; ++i) {
    scanf("%d %d %d", &s, &t, &d);
    g[s][t] = d;
  }
  warshall_floyd(g, v);
  for (i = 0; i < v; ++i) {
    if (g[i][i] < 0) {
      printf("NEGATIVE CYCLE\n");
      exit(0);
    }
  }
  for (i = 0; i < v; ++i) {
    for (j = 0; j < v; ++j) {
      if (j > 0) printf(" ");
      if (g[i][j] == INF_COST) {
        printf("INF");
      } else {
        printf("%lld", g[i][j]);
      }
    }
    printf("\n");
  }
}
