#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ARR_SIZE 1000003
#define STR_SIZE 16
#define CMD_SIZE 8
#define H1(k) (k % ARR_SIZE)
#define H2(k) (1 + k % (ARR_SIZE - 1))
#define HASH(k, i) ((H1(k) + i * H2(k)) % ARR_SIZE)

static long long int to_key(char *str) {
  long long int p, sum;

  for (p = 1, sum = 0; *str != '\0'; p *= 5) {
    switch (*str++) {
      case 'T': sum += 1L * p; break;
      case 'G': sum += 2L * p; break;
      case 'A': sum += 3L * p; break;
      case 'C': sum += 4L * p; break;
    }
  }
  return sum;
}

static void insert(char **arr, char *str) {
  long long int k;
  int idx, i;

  k = to_key(str);
  for (i = 0; i < ARR_SIZE; ++i) {
    idx = HASH(k, i);
    if (arr[idx] == NULL) {
      arr[idx] = str;
      break;
    }
    if (strcmp(arr[idx], str) == 0) break;
  }
}

static int find(char **arr, char *str) {
  long long int k;
  int idx, i;

  k = to_key(str);
  for (i = 0; i < ARR_SIZE; ++i) {
    idx = HASH(k, i);
    if (arr[idx] == NULL) return 0;
    if (strcmp(arr[idx], str) == 0) return 1;
  }
  return 0;
}

int main(int argc, char **argv) {
  int n, i, ret;
  char cmd[CMD_SIZE];
  char *str;
  char **arr;

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  arr = (char **) calloc(ARR_SIZE, sizeof(char *));
  if (arr == NULL) exit(1);

  while (n--) {
    str = (char *) calloc(STR_SIZE, sizeof(char));
    if (str == NULL) break;

    ret = scanf("%s %s", cmd, str);
    if (errno != 0) perror("scanf: cmd, str");
    if (ret < 1) break;

    switch (cmd[0]) {
      case 'i':
        insert(arr, str);
        break;
      case 'f':
        if (find(arr, str)) {
          printf("yes\n");
        } else {
          printf("no\n");
        }
        break;
    }
  }

  for (i = 0; i < ARR_SIZE; ++i) free(arr[i]);
  free(arr);
  exit(0);
}
