#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 12

int
main(int argc, char **argv) {
  char *buf;
  int n, price, min, profit, lost;

  buf = (char *) malloc(LINE_SIZE);
  if (buf == NULL) exit(1);

  buf = fgets(buf, LINE_SIZE, stdin);
  if (buf == NULL) exit(1);

  n = atoi(buf);
  price = min = profit = lost = -1;

  while (1) {
    buf = fgets(buf, LINE_SIZE, stdin);
    if (buf == NULL || n < 1) break;

    --n;
    price = atoi(buf);

    if (min == -1) {
      min = price;
    } else if (price < min) {
      if (lost == -1 || lost > (min - price)) {
        lost = min - price;
      }
      min = price;
    } else if (profit < (price - min)) {
      profit = price - min;
    }
  }

  fprintf(stdout, "%d\n", profit > -1 ? profit : -lost);

  free(buf);
  buf = NULL;
  exit(0);
}
