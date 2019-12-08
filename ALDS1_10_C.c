#include <stdlib.h>
#include <stdio.h>
#define MAX_ARR_SIZE 1024

static int count_lcs(char *x, char *y) {
  int i, j, m, n, max, mn[MAX_ARR_SIZE][MAX_ARR_SIZE];

  for (i = m = 0; x[i] != '\0'; ++i) ++m;
  for (j = n = 0; y[j] != '\0'; ++j) ++n;
  for (i = 0; i < m; ++i) mn[i][0] = 0;
  for (j = 0; j < n; ++j) mn[0][j] = 0;
  max = 0;
  for (i = 1; i < m + 1; ++i) {
    for (j = 1; j < n + 1; ++j) {
      if (x[i - 1] == y[j - 1]) {
        mn[i][j] = mn[i - 1][j - 1] + 1;
      } else {
        if (mn[i][j - 1] > mn[i - 1][j]) {
          mn[i][j] = mn[i][j - 1];
        } else {
          mn[i][j] = mn[i - 1][j];
        }
      }
      max = mn[i][j] > max ? mn[i][j] : max;
    }
  }
  return max;
}

int main(int argc, char **argv) {
  int q, i;
  char x[MAX_ARR_SIZE], y[MAX_ARR_SIZE];

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%s", x);
    scanf("%s", y);
    printf("%d\n", count_lcs(x, y));
  }
  exit(0);
}
