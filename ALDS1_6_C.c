#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SENTINEL 2000000000
#define MAX_ARR_SIZE 100000

typedef struct card { char c; int n; } c_t;

static void merge(c_t *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  c_t *l;
  c_t *r;

  n1 = mid - left;
  l = (c_t *) malloc(sizeof(c_t) * (n1 + 1));
  if (l == NULL) return;
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i].n = SENTINEL;

  n2 = right - mid;
  r = (c_t *) malloc(sizeof(c_t) * (n2 + 1));
  if (r == NULL) return;
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i].n = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i].n <= r[j].n) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }

  free(l);
  free(r);
}

static int partition(c_t *a, int left, int right) {
  int i, j, x;
  c_t tmp;

  x = a[right - 1].n;
  for (i = left - 1, j = left; j < right - 1; ++j) {
    if (a[j].n > x) continue;
    tmp = a[++i];
    a[i] = a[j];
    a[j] = tmp;
  }
  tmp = a[++i];
  a[i] = a[right - 1];
  a[right - 1] = tmp;

  return i;
}

static void merge_sort(c_t *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;

  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static void quick_sort(c_t *a, int left, int right) {
  int x;

  if (left >= right - 1) return;

  x = partition(a, left, right);
  quick_sort(a, left, x);
  quick_sort(a, x + 1, right);
}

static void print_arr(c_t *a, int n) {
  int i;

  for (i = 0; i < n; ++i) printf("%c %d\n", a[i].c, a[i].n);
}

int main(int argc, char **argv) {
  int n, ret, i, is_stable;
  c_t a1[MAX_ARR_SIZE];
  c_t a2[MAX_ARR_SIZE];

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  for (i = 0; i < n; ++i) {
    ret = scanf("%s %d", &a1[i].c, &a1[i].n);
    if (errno != 0) perror("scanf: a1[i]");
    if (ret < 1) break;
    a2[i] = a1[i];
  }

  quick_sort(a1, 0, n);
  merge_sort(a2, 0, n);

  for (is_stable = 1, i = 0; i < n; ++i) {
    if (a1[i].c != a2[i].c || a1[i].n != a2[i].n) {
      is_stable = 0;
      break;
    }
  }
  printf("%s\n", is_stable ? "Stable" : "Not stable");
  print_arr(a1, n);

  exit(0);
}
