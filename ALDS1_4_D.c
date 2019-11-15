#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int
enough(int *arr, int n, int k, int p) {
  int i, j, s;

  for (i = j = s = 0; i < n && j < k; ++i) {
    if ((s + arr[i]) <= p) {
      s += arr[i];
    } else {
      ++j;
      s = arr[i];
    }
  }

  return j < k;
}

int main(int argc, char **argv) {
  int n, k, p, i, ret, sum, avg, max;
  int *arr;

  ret = scanf("%d %d", &n, &k);
  if (errno != 0) perror("scanf: n, k");
  if (ret < 1) exit(1);

  arr = (int *) malloc(sizeof(int) * n);
  if (arr == NULL) exit(1);

  for (i = sum = max = 0; i < n; ++i) {
    ret = scanf("%d", &arr[i]);
    if (errno != 0) perror("scanf: arr[i]");
    if (ret < 1) break;
    sum += arr[i];
    if (arr[i] > max) max = arr[i];
  }

  avg = (sum / k) + ((sum % k) ? 1 : 0);
  for (p = max > avg ? max : avg; !enough(arr, n, k, p); ++p) {}
  printf("%d\n", p);

  free(arr);
  exit(0);
}
