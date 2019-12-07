#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 45
static int fib(int n, int *m) {
  if (!m[n]) {
    m[n - 2] = fib(n - 2, m);
    m[n - 1] = fib(n - 1, m);
    m[n] = m[n - 2] + m[n - 1];
  }
  return m[n];
}

int main(int argc, char **argv) {
  int n, i;
  int m[MAX_SIZE];
  for (i = 0; i < MAX_SIZE; ++i) m[i] = 0;
  m[0] = m[1] = 1;
  scanf("%d", &n);
  printf("%d\n", fib(n, m));
  exit(0);
}
