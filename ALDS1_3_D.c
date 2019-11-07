#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20002
#define PLOT_DOWN '\\'
#define PLOT_FLAT '_'
#define PLOT_UP '/'

typedef struct section { int j, size; } sec_t;

int main(int argc, char **argv) {
  char buf[MAX_SIZE];
  char *ret;
  int i, j, m, n, total, sub;
  int s1[MAX_SIZE];
  sec_t tmp;
  sec_t s2[MAX_SIZE / 2];

  ret = fgets(buf, MAX_SIZE, stdin);
  if (ret == NULL) exit(1);

  for (i = m = n = total = 0; buf[i] != '\0'; ++i) {
    switch (buf[i]) {
      case PLOT_DOWN:
        s1[m++] = i;
        break;
      case PLOT_UP:
        if (m < 1) break;
        j = s1[--m];
        total += i - j;
        sub = i - j;
        while (n > 0) {
          tmp = s2[--n];
          if (j > tmp.j) {
            ++n;
            break;
          }
          sub += tmp.size;
        }
        s2[n].j = j;
        s2[n].size = sub;
        n++;
        break;
    }
  }

  printf("%d\n%d", (int) total, n);
  for (i = 0; i < n; ++i) printf(" %d", (int) s2[i].size);
  printf("\n");
  exit(0);
}
