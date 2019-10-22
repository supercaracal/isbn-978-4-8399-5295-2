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

static void
print_arr(int *arr, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    if (i > 0) fprintf(stdout, " ");
    fprintf(stdout, "%d", arr[i]);
  }
  fprintf(stdout, "\n");
}

// Selection sort
static int
sort(int *a, int n) {
  int cnt, min, i, j, v;

  cnt = 0;
  for (i = 0; i < n; ++i) {
    min = i;
    for (j = i; j < n; ++j) {
      if (a[j] < a[min]) min = j;
    }
    if (i != min) {
      v = a[i];
      a[i] = a[min];
      a[min] = v;
      ++cnt;
    }
  }

  return cnt;
}

int
main(int argc, char **argv) {
  int *arr;
  int n, ret, cnt;

  ret = fscanf(stdin, "%d", &n);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  arr = read_arr(stdin, n);
  if (arr == NULL) exit(1);

  cnt = sort(arr, n);
  print_arr(arr, n);
  fprintf(stdout, "%d\n", cnt);

  free(arr);
  arr = NULL;
  exit(0);
}
