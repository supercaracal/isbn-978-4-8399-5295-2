#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SENTINEL 2000000000

static unsigned long merge(int *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  int *l;
  int *r;
  unsigned long cnt;

  n1 = mid - left;
  l = (int *) malloc(sizeof(int) * (n1 + 1));
  if (l == NULL) return 0;
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i] = SENTINEL;

  n2 = right - mid;
  r = (int *) malloc(sizeof(int) * (n2 + 1));
  if (r == NULL) return 0;
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i] = SENTINEL;

  for (i = j = 0, cnt = 0L, k = left; k < right; ++k) {
    if (l[i] <= r[j]) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++]; cnt += n1 - i;
    }
  }

  free(l); free(r); return cnt;
}

static unsigned long merge_sort(int *a, int left, int right) {
  int mid;
  unsigned long cnt;

  cnt = 0L;
  if (left >= right - 1) return cnt;
  mid = (left + right) / 2;
  cnt += merge_sort(a, left, mid);
  cnt += merge_sort(a, mid, right);
  cnt += merge(a, left, mid, right);
  return cnt;
}

int main(int argc, char **argv) {
  int ret, n, i;
  int *a;

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  a = (int *) malloc(sizeof(int) * n);
  if (a == NULL) exit(0);

  for (i = 0; i < n; ++i) {
    ret = scanf("%d", &a[i]);
    if (errno != 0) perror("scanf: a[i]");
    if (ret < 1) break;
  }

  printf("%ld\n", merge_sort(a, 0, n));
  free(a); exit(0);
}
