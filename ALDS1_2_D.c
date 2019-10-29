#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int *
read_arr(FILE *f, int size) {
  int *arr;
  int *tmp_arr;
  int n;

  arr = (int *) malloc(sizeof(int) * size);
  if (arr == NULL) return NULL;

  tmp_arr = arr;
  while (1) {
    n = fscanf(f, "%d", tmp_arr++);
    if (errno != 0) perror("fscanf");
    if (n == EOF) break;
  }

  return arr;
}

static int
count_g_arr(int max) {
  int cnt, val;

  for (cnt = 0, val = 1; val < max; ++cnt) {
    val = val * 3 + 1;
  }

  return cnt == 0 ? 1 : cnt;
}

static int *
build_g_arr(int size, int max) {
  int *arr;
  int i, j, tmp;

  arr = (int *) malloc(sizeof(int) * size);
  if (arr == NULL) return NULL;

  for (i = 0, tmp = 1; i < size; ++i) {
    arr[i] = tmp;
    tmp = tmp * 3 + 1;
  }

  for (i = 0, j = size - 1; i < size / 2; ++i, --j) {
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }

  return arr;
}

static void
print_horizontal(FILE *f, int *arr, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    if (i > 0) fprintf(f, " ");
    fprintf(f, "%d", arr[i]);
  }
  fprintf(f, "\n");
}

static void
print_vertical(FILE *f, int *arr, int size) {
  int i;

  for (i = 0; i < size; ++i) fprintf(f, "%d\n", arr[i]);
}

static int
insertion_sort(int *a, int n, int g) {
  int i, j, v, cnt;

  cnt = 0;
  for (i = g; i < n; ++i) {
    v = a[i];
    j = i - g;
    while (j >= 0 && a[j] > v) {
      a[j + g] = a[j];
      j = j - g;
      ++cnt;
    }
    a[j + g] = v;
  }

  return cnt;
}

static int
shell_sort(int *a, int n, int m, int g[]) {
  int cnt, i;

  cnt = 0;
  for (i = 0; i < m; ++i) {
    cnt += insertion_sort(a, n, g[i]);
  }

  return cnt;
}

int
main(int argc, char **argv) {
  int *arr;
  int *g;
  int m, n, ret, cnt;

  ret = fscanf(stdin, "%d", &n);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  arr = read_arr(stdin, n);
  if (arr == NULL) exit(1);

  m = count_g_arr(n);;
  g = build_g_arr(m, n);

  cnt = shell_sort(arr, n, m, g);
  fprintf(stdout, "%d\n", m);
  print_horizontal(stdout, g, m);
  fprintf(stdout, "%d\n", cnt);
  print_vertical(stdout, arr, n);

  free(arr);
  arr = NULL;
  free(g);
  g = NULL;
  exit(0);
}
