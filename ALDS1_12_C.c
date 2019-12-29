#include <stdio.h>
#include <stdlib.h>
#define INF_COST (1 << 30)
#define ROOT_IDX 1
#define DEFAULT_BH_SIZE 33
#define P_KEY(i) (i / 2)
#define L_KEY(i) (i * 2)
#define R_KEY(i) (i * 2 + 1)
#define EMPTY_PRIORITY_QUEUE(pq) (pq->i == ROOT_IDX)

typedef enum { UNEXPLORED, VISITED, COMPLETED } state_t;
typedef struct { int d; state_t s; } vertex_t;
typedef struct { int id, cost; } adjacency_t;
typedef struct { adjacency_t *adjs; int size; } adjacency_list_t;
typedef struct { adjacency_t *adjs; int size, i; } priority_queue_t;

static priority_queue_t *new_priority_queue(void) {
  priority_queue_t *pq;

  pq = (priority_queue_t *) malloc(sizeof(priority_queue_t));
  pq->i = ROOT_IDX;
  pq->size = DEFAULT_BH_SIZE;
  pq->adjs = (adjacency_t *) malloc(sizeof(adjacency_t) * pq->size);
  return pq;
}

static void free_priority_queue(priority_queue_t *pq) {
  free(pq->adjs);
  free(pq);
}

static void min_heapify(priority_queue_t *pq, int i) {
  int l, r, m;
  adjacency_t tmp;

  l = L_KEY(i);
  r = R_KEY(i);
  m = i;
  if (l < pq->i && pq->adjs[l].cost < pq->adjs[m].cost) m = l;
  if (r < pq->i && pq->adjs[r].cost < pq->adjs[m].cost) m = r;
  if (m != i) {
    tmp = pq->adjs[i];
    pq->adjs[i] = pq->adjs[m];
    pq->adjs[m] = tmp;
    min_heapify(pq, m);
  }
}

static void enqueue(priority_queue_t *pq, adjacency_t adj) {
  int j;
  adjacency_t tmp;

  if (pq->i == pq->size) {
    pq->size *= 2;
    pq->adjs = (adjacency_t *) realloc(pq->adjs, sizeof(adjacency_t) * pq->size);
  }
  pq->adjs[pq->i] = adj;
  for (j = pq->i; j >= ROOT_IDX; j = P_KEY(j)) {
    if (P_KEY(j) < ROOT_IDX || pq->adjs[j].cost > pq->adjs[P_KEY(j)].cost) break;
    tmp = pq->adjs[j];
    pq->adjs[j] = pq->adjs[P_KEY(j)];
    pq->adjs[P_KEY(j)] = tmp;
  }
  pq->i++;
}

static adjacency_t dequeue(priority_queue_t *pq) {
  adjacency_t root;

  if (EMPTY_PRIORITY_QUEUE(pq)) {
    root.id = root.cost = -1;
    return root;
  }
  pq->i--;
  root = pq->adjs[ROOT_IDX];
  pq->adjs[ROOT_IDX] = pq->adjs[pq->i];
  min_heapify(pq, ROOT_IDX);
  return root;
}

static void dijkstra(adjacency_list_t *a, vertex_t *v) {
  int i, tmp_cost;
  priority_queue_t *pq;
  adjacency_t adj1, adj2;

  v[0].d = adj1.id = adj1.cost = 0;
  pq = new_priority_queue();
  enqueue(pq, adj1);
  while (!EMPTY_PRIORITY_QUEUE(pq)) {
    adj1 = dequeue(pq);
    if (adj1.cost > v[adj1.id].d) continue;
    v[adj1.id].s = COMPLETED;
    for (i = 0; i < a[adj1.id].size; ++i) {
      adj2 = a[adj1.id].adjs[i];
      if (v[adj2.id].s == COMPLETED) continue;
      tmp_cost = v[adj1.id].d + adj2.cost;
      if (tmp_cost >= v[adj2.id].d) continue;
      v[adj2.id].d = tmp_cost;
      v[adj2.id].s = VISITED;
      adj2.cost = v[adj2.id].d;
      enqueue(pq, adj2);
    }
  }
  free_priority_queue(pq);
}

int main(int argc, char **argv) {
  int n, m, x, y, w, i, j;
  adjacency_list_t *a;
  vertex_t *v;

  scanf("%d", &n);
  a = (adjacency_list_t *) malloc(sizeof(adjacency_list_t) * n);
  v = (vertex_t *) malloc(sizeof(vertex_t) * n);
  for (i = 0; i < n; ++i) {
    v[i].d = INF_COST;
    v[i].s = UNEXPLORED;
  }
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &x, &m);
    a[x].size = m;
    a[x].adjs = (adjacency_t *) malloc(sizeof(adjacency_t) * m);
    for (j = 0; j < m; ++j) {
      scanf("%d %d", &y, &w);
      a[x].adjs[j].id = y;
      a[x].adjs[j].cost = w;
    }
  }
  dijkstra(a, v);
  for (i = 0; i < n; ++i) printf("%d %d\n", i, v[i].d);
  for (i = 0; i < n; ++i) free(a[i].adjs);
  free(a);
  free(v);
}
