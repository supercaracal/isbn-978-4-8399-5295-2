#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int
search(int *arr, int size, int e) {
  int lower, upper, i;

  for (lower = 0, upper = size - 1, i = (lower + upper) / 2; lower <= upper; i = (lower + upper) / 2) {
    if (e == arr[i]) return 1;
    if (e > arr[i]) {
      lower = i + 1;
    } else {
      upper = i - 1;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  int n, q, i, e, cnt, ret;
  int s[100001];

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
    if (search(s, n, e)) ++cnt;
  }

  printf("%d\n", cnt);
  exit(0);
}
