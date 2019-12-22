#include <stdio.h>
#define MAX_SIZE 101
#define UNKNOWN_ID -1
#define UNREACHABLE -1

typedef enum { UNEXPLORED, VISITED, COMPLETED } state_t;
typedef struct { int first, last, arr[MAX_SIZE]; } queue_t;

static void enqueue(queue_t *q, int n) {
  if (q->first == q->last) return;
  q->arr[q->last - 1] = n;
  q->last++;
  if (q->last == MAX_SIZE) q->last = 0;
}

static int dequeue(queue_t *q) {
  int n;
  if (q->first == q->last - 1) return UNKNOWN_ID;
  n = q->arr[q->first];
  q->arr[q->first] = UNKNOWN_ID;
  q->first++;
  if (q->first == MAX_SIZE) q->first = 0;
  return n;
}

static void bfs(int g[MAX_SIZE][MAX_SIZE], int size, state_t *s, queue_t *q, int *d) {
  int n, j;

  n = dequeue(q);
  if (n == UNKNOWN_ID) return;
  s[n] = COMPLETED;
  for (j = 1; j <= size; ++j) {
    if (g[n][j] == 0) continue;
    if (s[j] != UNEXPLORED) continue;
    s[j] = VISITED;
    d[j] = d[n] + 1;
    enqueue(q, j);
  }
  bfs(g, size, s, q, d);
}

int main(int argc, char **argv) {
  int n, i, j, k, l, m, g[MAX_SIZE][MAX_SIZE], d[MAX_SIZE];
  state_t s[MAX_SIZE];
  queue_t q;

  q.first = 0;
  q.last = 1;
  for (i = 0; i < MAX_SIZE; ++i) {
    d[i] = 0;
    q.arr[i] = UNKNOWN_ID;
    s[i] = UNEXPLORED;
    for (j = 0; j < MAX_SIZE; ++j) g[i][j] = 0;
  }

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &k, &l);
    for (j = 0; j < l; ++j) {
      scanf("%d", &m);
      ++g[k][m];
    }
  }

  enqueue(&q, 1);
  bfs(g, n, s, &q, d);
  for (i = 1; i <= n; ++i) printf("%d %d\n", i, s[i] == UNEXPLORED ? UNREACHABLE : d[i]);
}
