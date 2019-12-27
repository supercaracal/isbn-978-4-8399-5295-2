#include <stdio.h>
#define MAX_N 100
#define INF_COST (1 << 30)
#define NO_CONN -1
#define UNKNOWN_ID -1

typedef enum { UNEXPLORED, VISITED, COMPLETED } state_t;
typedef struct { int p, d; state_t s; } vertex_t;

static void dijkstra(int a[MAX_N][MAX_N], int size, vertex_t *v) {
  int i, u, min;

  u = 0;
  v[u].d = 0;

  while (1) {
    min = INF_COST;
    for (i = 0; i < size; ++i) {
      if (v[i].s != COMPLETED && v[i].d < min) {
        min = v[i].d;
        u = i;
      }
    }
    if (min == INF_COST) break;
    v[u].s = COMPLETED;
    for (i = 0; i < size; ++i) {
      if (v[i].s != COMPLETED && (v[u].d + a[u][i]) < v[i].d) {
        v[i].d = v[u].d + a[u][i];
        v[i].p = u;
        v[i].s = VISITED;
      }
    }
  }
}

int main(int argc, char **argv) {
  int n, m, x, y, w, i, j, a[MAX_N][MAX_N];
  vertex_t v[MAX_N];

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    v[i].p = UNKNOWN_ID;
    v[i].d = INF_COST;
    v[i].s = UNEXPLORED;
  }
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) a[i][j] = INF_COST;
  }
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &x, &m);
    for (j = 0; j < m; ++j) {
      scanf("%d %d", &y, &w);
      a[x][y] = w;
    }
  }
  dijkstra(a, n, v);
  for (i = 0; i < n; ++i) printf("%d %d\n", i, v[i].d);
}
