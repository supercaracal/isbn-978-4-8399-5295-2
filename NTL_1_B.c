#include <stdio.h>
#define O 1000000007L
typedef unsigned long long int num_t;

static num_t power(num_t m, num_t n, num_t o) {
  num_t p;

  if (n == 0) return 1;
  p = power(m * m % o, n / 2, o);
  if (n % 2) p = p * m % o;
  return p;
}

int main(int argc, char **argv) {
  num_t m, n;

  scanf("%llu %llu", &m, &n);
  printf("%llu\n", power(m, n, O));
}
