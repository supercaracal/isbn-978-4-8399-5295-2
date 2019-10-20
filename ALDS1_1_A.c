#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 512

static int *
split(char *line, int size) {
  char c;
  char elm[5];
  int *arr;
  int *tmp_arr;
  char *tmp_elm;

  arr = (int *) malloc(sizeof(int) * size);
  if (arr == NULL) return NULL;

  tmp_arr = arr;
  tmp_elm = elm;
  while (1) {
    c = *line++;
    if (c == '\0') break;
    if (c == ' ' || c == '\n') {
      *tmp_elm = '\0';
      *tmp_arr++ = atoi(elm);
      tmp_elm = elm;
      continue;
    }
    *tmp_elm++ = c;
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

// Insertion sort
static void
sort(int *a, int n) {
  int i, j, v;

  print_arr(a, n);
  for (i = 1; i < n; ++i) {
    v = a[i];
    j = i - 1;
    while (j >= 0 && a[j] > v) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = v;
    print_arr(a, n);
  }
}

int
main(int argc, char **argv) {
  char *buf;
  int n;
  int *arr;

  buf = (char *) malloc(LINE_SIZE);
  if (buf == NULL) exit(1);

  buf = fgets(buf, LINE_SIZE, stdin);
  if (buf == NULL) exit(1);
  n = atoi(buf);

  buf = fgets(buf, LINE_SIZE, stdin);
  if (buf == NULL) exit(1);
  arr = split(buf, n);
  if (arr == NULL) exit(1);

  sort(arr, n);

  free(buf);
  buf = NULL;
  free(arr);
  arr = NULL;
  exit(0);
}
