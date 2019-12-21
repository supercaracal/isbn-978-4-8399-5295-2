#include <stdio.h>
#define MAX_SIZE 101
typedef struct { int seq, o[MAX_SIZE][2]; } dfs_t;

static dfs_t *dfs(int g[MAX_SIZE][MAX_SIZE], int size, int i, dfs_t *dt) {
  int j;

  if (dt->o[i][0] > 0) return dt;

  dt->o[i][0] = dt->seq++;
  for (j = 1; j <= size; ++j) {
    if (g[i][j] == 0) continue;
    if (i != j) dt = dfs(g, size, j, dt);
  }
  if (dt->o[i][1] == 0) dt->o[i][1] = dt->seq++;
  return dt;
}

int main(int argc, char **argv) {
  int n, i, j, k, l, m, g[MAX_SIZE][MAX_SIZE];
  dfs_t dt;

  dt.seq = 1;
  for (i = 0; i < MAX_SIZE; ++i) {
    dt.o[i][0] = dt.o[i][1] = 0;
    for (j = 0; j < MAX_SIZE; ++j) g[i][j] = 0;
  }

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &k, &l);
    for (j = 0; j < l; ++j) {
      scanf("%d", &m);
      ++g[k][m];
    }
  }

  for (i = 1; i <= n; ++i) dfs(g, n, i, &dt);
  for (i = 1; i <= n; ++i) printf("%d %d %d\n", i, dt.o[i][0], dt.o[i][1]);
}
