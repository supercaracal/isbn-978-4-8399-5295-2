#include <stdlib.h>
#include <stdio.h>

#define SENTINEL 2000000000

static void merge(int *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  int *l;
  int *r;

  n1 = mid - left;
  l = (int *) malloc(sizeof(int) * (n1 + 1));
  if (l == NULL) return;
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i] = SENTINEL;

  n2 = right - mid;
  r = (int *) malloc(sizeof(int) * (n2 + 1));
  if (r == NULL) return;
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i] = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i] <= r[j]) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }
  free(l); free(r);
}

static void merge_sort(int *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static int calc(int *a, int *b, int n) {
  return 0;
}

int main(int argc, char **argv) {
  int n, i, a[1000], b[1000];

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  merge_sort(b, 0, n);
  printf("%d\n", calc(a, b, n));
  exit(0);
}
