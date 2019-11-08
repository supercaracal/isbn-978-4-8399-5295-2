#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
  int n, q, i, e, cnt, ret;
  int s[10000];

  ret = fscanf(stdin, "%d", &n);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  for (i = 0; i < n; ++i) {
    ret = fscanf(stdin, "%d", &s[i]);
    if (errno != 0) perror("fscanf");
    if (ret < 1) break;
  }

  ret = fscanf(stdin, "%d", &q);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  for (cnt = 0; q > 0; --q) {
    ret = fscanf(stdin, "%d", &e);
    if (errno != 0) perror("fscanf");
    if (ret < 1) break;

    for (i = 0; i < n; ++i) {
      if (s[i] == e) {
        ++cnt;
        break;
      }
    }
  }

  printf("%d\n", cnt);
  exit(0);
}
