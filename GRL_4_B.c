#include <stdio.h>
#include <stdlib.h>
#define UNKNOWN_ID -1
#define DEFAULT_VARR_SIZE 8
#define EMPTY_QUEUE(q) (q->size == 0)
#define FULL_QUEUE(q) (q->size == q->max)

typedef struct { int head, tail, size, max, *arr; } queue_t;
typedef struct { int size, i, *arr; } varr_t;

static queue_t *new_queue(int size) {
  queue_t *q;
  int i;

  q = (queue_t *) malloc(sizeof(queue_t));
  q->head = q->tail = q->size = 0;
  q->max = size;
  q->arr = (int *) malloc(sizeof(int) * size);
  for (i = 0; i < size; ++i) q->arr[i] = UNKNOWN_ID;
  return q;
}

static void free_queue(queue_t *q) {
  free(q->arr);
  free(q);
}

static void enqueue(queue_t *q, int n) {
  if (FULL_QUEUE(q)) return;
  q->arr[q->tail] = n;
  q->tail = (q->tail + 1) % q->max;
  q->size--;
}

static int dequeue(queue_t *q) {
  int n;

  if (EMPTY_QUEUE(q)) return UNKNOWN_ID;
  n = q->arr[q->head];
  q->arr[q->head] = UNKNOWN_ID;
  q->head = (q->head + 1) % q->max;
  q->size++;
  return n;
}

static void topological_sort(int size, int *vt, int *ig, varr_t *ts, varr_t *g) {
  int i, j, m, n;
  queue_t *q;

  for (i = 0; i < size; ++i) {
    if (vt[i] == 0 && ig[i] == 0) {
      q = new_queue(size);
      enqueue(q, i);
      while (!EMPTY_QUEUE(q)) {
        m = dequeue(q);
        vt[m] = 1;
        ts->arr[ts->i++] = m;
        for (j = 0; j < g[m].i; ++j) {
          n = g[m].arr[j];
          if (vt[n] == 1) continue;
          if (--ig[n] == 0) enqueue(q, n);
        }
      }
      free_queue(q);
    }
  }
}

int main(int argc, char **argv) {
  int v, e, i, k, l, *vt, *ig; // visited, in-degree
  varr_t ts, *g; // topological sorted array, graph

  scanf("%d %d", &v, &e);
  vt = (int *) malloc(sizeof(int) * v);
  ig = (int *) malloc(sizeof(int) * v);
  ts.size = v;
  ts.i = 0;
  ts.arr = (int *) malloc(sizeof(int) * ts.size);
  g = (varr_t *) malloc(sizeof(varr_t) * v);
  for (i = 0; i < v; ++i) {
    vt[i] = ig[i] = 0;
    g[i].size = DEFAULT_VARR_SIZE;
    g[i].i = 0;
    g[i].arr = (int *) malloc(sizeof(int) * g[i].size);
  }
  for (i = 0; i < e; ++i) {
    scanf("%d %d", &k, &l);
    if (g[k].i == g[k].size) {
      g[k].size *= 2;
      g[k].arr = (int *) realloc(g[k].arr, sizeof(int) * g[k].size);
    }
    g[k].arr[g[k].i++] = l;
    ig[l]++;
  }
  topological_sort(v, vt, ig, &ts, g);
  for (i = 0; i < ts.i; ++i) printf("%d\n", ts.arr[i]);
  free(vt); free(ig); free(ts.arr);
  for (i = 0; i < v; ++i) free(g[i].arr);
}
