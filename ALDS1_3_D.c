#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20000
#define PLOT_DOWN '\\'
#define PLOT_FLAT '_'
#define PLOT_UP '/'

int main(int argc, char **argv) {
  char buf[MAX_SIZE];
  char *ret;
  char prev;
  int i, j, depth, base;
  double cap, offset, total;
  double caps[MAX_SIZE / 2];

  ret = fgets(buf, MAX_SIZE, stdin);
  if (ret == NULL) exit(1);

  for (i = j = depth = base = 0, cap = offset = total = 0.0, prev = '\0'; buf[i] != '\0'; prev = buf[i++]) {
    if (prev != PLOT_DOWN && buf[i] == PLOT_DOWN && depth == 0) base = i;
    switch (buf[i]) {
      case PLOT_DOWN:
        if (prev != PLOT_UP) ++depth;
        offset = 0.5;
        break;
      case PLOT_UP:
        if (prev == PLOT_UP) --depth;
        offset = 0.5;
        break;
      case PLOT_FLAT:
        offset = 0.0;
        break;
    }
    if (depth > 0 && prev == PLOT_UP && buf[i] != PLOT_UP) {
    }
    if (depth > 0) cap += ((float) depth) * 1.0 - offset;
    if (buf[i] == PLOT_UP && depth == 1) {
      caps[j++] = cap;
      total += cap;
      cap = 0.0;
    }
  }

  printf("%d\n%d", (int) total, j);
  for (i = 0; i < j; ++i) printf(" %d", (int) caps[i]);
  printf("\n");
  exit(0);
}
