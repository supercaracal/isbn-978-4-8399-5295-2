#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int
hash(char *str) {
  int hv = 1;

  while (*str != '\0') {
    switch (*str++) {
      case 'T':
        break;
      case 'G':
        break;
      case 'A':
        break;
      case 'C':
        break;
    }
  }

  return hv;
}

int main(int argc, char **argv) {
  int n, ret;
  char cmd[8];
  char str[16];
  int arr[2000000];

  ret = scanf("%d", &n);
  if (errno != 0) perror("scanf: n");
  if (ret < 1) exit(1);

  while (n--) {
    ret = scanf("%s %s", cmd, str);
    if (errno != 0) perror("scanf: cmd, str");
    if (ret < 1) break;

    switch (cmd[0]) {
      case 'i':
        arr[hash(str)] = 1;
        break;
      case 'f':
        if (arr[hash(str)]) {
          printf("yes\n");
        } else {
          printf("no\n");
        }
        break;
    }
  }

  exit(0);
}
