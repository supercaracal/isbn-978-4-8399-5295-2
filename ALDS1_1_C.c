#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int
is_prime(int e) {
  int i;

  if (e < 2) return 0;
  if (e == 2) return 1;
  if (e % 2 == 0) return 0;

  for (i = 3; i * i <= e; i += 2) {
    if (e % i == 0) return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  int n, e, ret, cnt;

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  cnt = 0;
  while (1) {
    ret = scanf("%d", &e);
    if (errno != 0) perror("scanf: e");
    if (ret < 1) break;
    if (is_prime(e)) ++cnt;
  }

  printf("%d\n", cnt);
  exit(0);
}
