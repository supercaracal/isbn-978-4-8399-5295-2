#include <stdio.h>
#define MAX_N 100
#define INF_COST 2001
#define NO_CONN -1
#define UNKNOWN_ID -1

typedef enum { UNEXPLORED, VISITED, COMPLETED } state_t;
typedef struct { int p, d; state_t s; } vertex_t;

static int prim(int a[MAX_N][MAX_N], int size) {
  vertex_t v[MAX_N];
  int i, u, min, sum;

  for (i = 0; i < size; ++i) {
    v[i].p = UNKNOWN_ID;
    v[i].d = INF_COST;
    v[i].s = UNEXPLORED;
  }

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
      if (v[i].s != COMPLETED && a[u][i] != NO_CONN && a[u][i] < v[i].d) {
        v[i].d = a[u][i];
        v[i].p = u;
        v[i].s = VISITED;
      }
    }
  }

  for (sum = i = 0; i < size; ++i) {
    if (v[i].p != UNKNOWN_ID) sum += v[i].d;
  }

  return sum;
}

int main(int argc, char **argv) {
  int n, i, j, a[MAX_N][MAX_N];

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) scanf("%d", &a[i][j]);
  }

  printf("%d\n", prim(a, n));
}
