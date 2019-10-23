#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct card {
  char c;
  int n;
};

static struct card *
read_arr(FILE *f, int size) {
  struct card *arr;
  struct card *tmp_arr;
  int n;
  char c;

  arr = (struct card *) malloc(sizeof(struct card) * size);
  if (arr == NULL) return NULL;

  tmp_arr = arr;
  while (1) {
    n = fgetc(f);
    if (n == EOF) break;
    c = (char) n;
    if (c == '\n') continue;
    if (c == ' ') continue;
    if ('A' <= c && c <= 'Z') {
      tmp_arr->c = c;
    } else if ('0' <= c && c <= '9') {
      tmp_arr->n = c - '0';
      ++tmp_arr;
    }
  }

  return arr;
}

static struct card *
copy_arr(struct card *src, int size) {
  struct card *dest;
  int i;

  dest = (struct card *) malloc(sizeof(struct card) * size);
  if (dest == NULL) return NULL;

  for (i = 0; i < size; ++i) {
    dest[i].c = src[i].c;
    dest[i].n = src[i].n;
  }

  return dest;
}

static void
print_arr(FILE *f, struct card *arr, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    if (i > 0) fprintf(f, " ");
    fprintf(f, "%c%d", arr[i].c, arr[i].n);
  }
  fprintf(f, "\n");
}

static int
equal(struct card a, struct card b) {
  return a.c == b.c && a.n == b.n;
}

static void
print_stability(FILE *f, struct card *o, struct card *s, int n) {
  int i, j, k, l;

  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      for (k = 0; k < n; ++k) {
        for (l = k + 1; l < n; ++l) {
          if (o[i].n == o[j].n && equal(o[i], s[l]) && equal(o[j], s[k])) {
            fprintf(f, "Not stable\n");
            return;
          }
        }
      }
    }
  }

  fprintf(f, "Stable\n");
}

static void
sort_bubbly(struct card *a, int n) {
  int flag, i;
  struct card v;

  flag = 1;
  while (flag) {
    flag = 0;
    for (i = n - 1; i > 0; --i) {
      if (a[i - 1].n > a[i].n) {
        v = a[i];
        a[i] = a[i - 1];
        a[i - 1] = v;
        flag = 1;
      }
    }
  }
}

static void
sort_selectively(struct card *a, int n) {
  int min, i, j;
  struct card v;

  for (i = 0; i < n; ++i) {
    min = i;
    for (j = i; j < n; ++j) {
      if (a[j].n < a[min].n) min = j;
    }
    if (i != min) {
      v = a[i];
      a[i] = a[min];
      a[min] = v;
    }
  }
}

int
main(int argc, char **argv) {
  struct card *orig;
  struct card *arr1;
  struct card *arr2;
  int n, ret;

  ret = fscanf(stdin, "%d", &n);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  orig = read_arr(stdin, n);
  if (orig == NULL) exit(1);

  arr1 = copy_arr(orig, n);
  if (arr1 == NULL) exit(1);

  arr2 = copy_arr(orig, n);
  if (arr2 == NULL) exit(1);

  sort_bubbly(arr1, n);
  print_arr(stdout, arr1, n);
  print_stability(stdout, orig, arr1, n);

  sort_selectively(arr2, n);
  print_arr(stdout, arr2, n);
  print_stability(stdout, orig, arr2, n);

  free(orig);
  orig = NULL;
  free(arr1);
  arr1 = NULL;
  free(arr2);
  arr2 = NULL;
  exit(0);
}
