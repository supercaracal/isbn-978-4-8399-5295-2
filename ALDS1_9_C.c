#include <stdlib.h>
#include <stdio.h>
#define INIT_BH_SIZE 16
#define MAX_CMD_SIZE 8
#define ROOT_IDX 1
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

static void insert(int *bh, int i, int k) {
  int j, tmp;

  bh[i] = k;
  for (j = i; j > 0; j = P_KEY(j)) {
    if (P_KEY(j) < ROOT_IDX || bh[j] < bh[P_KEY(j)]) break;
    tmp = bh[j];
    bh[j] = bh[P_KEY(j)];
    bh[P_KEY(j)] = tmp;
  }
}

static int remove_root(int *bh, int i) {
  int root;

  root = bh[ROOT_IDX];
  bh[ROOT_IDX] = bh[i];
  max_heapify(bh, ROOT_IDX, i);
  return root;
}

int main(int argc, char **argv) {
  int n, i, k;
  int *bh;
  char cmd[MAX_CMD_SIZE];

  n = INIT_BH_SIZE;
  i = ROOT_IDX;
  bh = (int *) malloc(sizeof(int) * n);
  while (1) {
    scanf("%s", cmd);
    if (cmd[0] == 'i') {
      if (i == n) {
        bh = (int *) realloc(bh, sizeof(int) * n * 2);
        n *= 2;
      }
      scanf("%d", &k);
      insert(bh, i++, k);
    } else if (cmd[0] == 'e' && cmd[1] == 'x') {
      printf("%d\n", bh[ROOT_IDX]);
      remove_root(bh, --i);
    } else {
      break;
    }
  }
  free(bh); exit(0);
}
