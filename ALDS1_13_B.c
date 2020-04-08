#include <stdio.h>
#include <stdlib.h>

#define PUZZLE_SIZE 3
#define DIRECTION_SIZE 4
#define RESOLVED_PUZZLE_KEY 123456780
#define DEFAULT_QUEUE_SIZE 16

typedef enum { UP, DOWN, RIGHT, LEFT } direction_t;
typedef struct { int row, col; } cell_t;
typedef struct { int cnt, size, key, **p; cell_t zero; } state_t;
typedef struct { int head, tail, size, max; state_t **arr; } queue_t;
typedef struct Node { int bf, x; struct Node *p, *l, *r; } node_t;

static queue_t *new_queue(int);
static void free_queue(queue_t *);
static void enqueue(queue_t *, state_t *);
static state_t *dequeue(queue_t *);

static node_t *new_node(int);
static void free_node(node_t *);
static void insert_node(node_t *, node_t *);
static node_t *find_node(node_t *, int);
static node_t *rotate_left(node_t *);
static node_t *rotate_right(node_t *);
static node_t *rebalance(node_t *);

static state_t *new_state(int);
static state_t *copy_state(const state_t *);
static void free_state(state_t *);
static int advance_state(state_t *, direction_t);
static void update_state_key(state_t *);

static queue_t *new_queue(int size) {
  queue_t *q;
  int i;

  q = (queue_t *) malloc(sizeof(queue_t));
  q->head = q->tail = q->size = 0;
  q->max = size;
  q->arr = (state_t **) malloc(sizeof(state_t *) * q->max);
  for (i = 0; i < q->max; ++i) q->arr[i] = NULL;
  return q;
}

static void free_queue(queue_t *q) {
  while (q->head < q->tail) {
    free_state(q->arr[q->head]);
    q->head = (q->head + 1) % q->max;
  }
  free(q->arr);
  free(q);
}

static void enqueue(queue_t *q, state_t *s) {
  int i, range, expanded;

  q->size++;
  if (q->size == q->max) {
    range = q->max - q->head;
    expanded = q->max;
    q->max *= 2;
    q->arr = (state_t **) realloc(q->arr, sizeof(state_t *) * q->max);
    if (q->head > q->tail) {
      for (i = q->max - 1; i >= q->tail; --i) q->arr[i] = (i >= q->max - range) ? q->arr[i - expanded] : NULL;
      q->head = q->max - range;
    }
  }
  q->arr[q->tail] = s;
  q->tail = (q->tail + 1) % q->max;
}

static state_t *dequeue(queue_t *q) {
  state_t *s;

  if (q->size == 0) return NULL;
  s = q->arr[q->head];
  q->arr[q->head] = NULL;
  q->head = (q->head + 1) % q->max;
  q->size--;
  return s;
}

static node_t *new_node(int x) {
  node_t *n;

  n = (node_t *) malloc(sizeof(node_t));
  n->p = n->l = n->r = NULL;
  n->x = x;
  n->bf = 1;
  return n;
}

static void free_node(node_t *n) {
  if (n == NULL) return;
  free_node(n->l);
  free_node(n->r);
  free(n);
}

static void insert_node(node_t *r, node_t *n) {
  if (n->x < r->x) {
    if (r->l == NULL) {
      r->l = n;
      n->p = r;
    } else {
      insert_node(r->l, n);
    }
  } else if (n->x > r->x) {
    if (r->r == NULL) {
      r->r = n;
      n->p = r;
    } else {
      insert_node(r->r, n);
    }
  }
}

static node_t *find_node(node_t *n, int x) {
  node_t *ret;

  if (n == NULL) {
    ret = NULL;
  } else if (x == n->x) {
    ret = n;
  } else if (x < n->x) {
    ret = find_node(n->l, x);
  } else if (x > n->x) {
    ret = find_node(n->r, x);
  } else {
    ret = NULL;
  }
  return ret;
}

static node_t *rotate_left(node_t *n) {
  node_t *p, *r;

  if (n == NULL) return n;

  p = n->p;
  r = n->r;

  if (p != NULL) {
    if (p->x > r->x) {
      p->l = r;
    } else {
      p->r = r;
    }
  }

  n->p = r;
  n->r = r->l;
  n->bf = r->bf - 1;

  r->p = p;
  r->l = n;

  return r;
}

static node_t *rotate_right(node_t *n) {
  node_t *p, *l;

  if (n == NULL) return n;

  p = n->p;
  l = n->l;

  if (p != NULL) {
    if (p->x > l->x) {
      p->l = l;
    } else {
      p->r = l;
    }
  }

  n->p = l;
  n->l = l->r;
  n->bf = l->bf - 1;

  l->p = p;
  l->r = n;

  return l;
}

static node_t *rebalance(node_t *n) {
  int l, r;

  if (n == NULL) return n;
  l = n->l == NULL ? 0 : n->l->bf;
  r = n->r == NULL ? 0 : n->r->bf;
  n->bf = (l > r ? l : r) + 1;
  if ((l - r < 0 ? (l - r) * -1 : l - r) > 1) {
    if (l < r) {
      n = rotate_left(n);
    } else {
      n = rotate_right(n);
    }
  }
  return n->p ? rebalance(n->p) : n;
}

static state_t *new_state(int size) {
  state_t *s;
  int i;

  s = (state_t *) malloc(sizeof(state_t));
  s->size = size;
  s->cnt = s->zero.row = s->zero.col = s->key = 0;
  s->p = (int **) malloc(sizeof(int *) * s->size);
  for (i = 0; i < s->size; ++i) s->p[i] = (int *) malloc(sizeof(int) * s->size);
  return s;
}

static state_t *copy_state(const state_t *src) {
  state_t *dest;
  int i, j;

  dest = new_state(src->size);
  dest->cnt = src->cnt;
  dest->zero = src->zero;
  dest->key = src->key;
  for (i = 0; i < dest->size; ++i) {
    for (j = 0; j < dest->size; ++j) dest->p[i][j] = src->p[i][j];
  }
  return dest;
}

static void free_state(state_t *s) {
  int i;

  for (i = 0; i < s->size; ++i) free(s->p[i]);
  free(s->p);
  free(s);
}

static int advance_state(state_t *s, direction_t d) {
  switch (d) {
    case UP:
      if (s->zero.row + 1 == s->size) return 1;
      s->p[s->zero.row][s->zero.col] = s->p[s->zero.row + 1][s->zero.col];
      s->zero.row++;
      break;
    case DOWN:
      if (s->zero.row - 1 < 0) return 1;
      s->p[s->zero.row][s->zero.col] = s->p[s->zero.row - 1][s->zero.col];
      s->zero.row--;
      break;
    case RIGHT:
      if (s->zero.col - 1 < 0) return 1;
      s->p[s->zero.row][s->zero.col] = s->p[s->zero.row][s->zero.col - 1];
      s->zero.col--;
      break;
    case LEFT:
      if (s->zero.col + 1 == s->size) return 1;
      s->p[s->zero.row][s->zero.col] = s->p[s->zero.row][s->zero.col + 1];
      s->zero.col++;
      break;
  }
  s->p[s->zero.row][s->zero.col] = 0;
  update_state_key(s);
  s->cnt++;
  return 0;
}

static void update_state_key(state_t *s) {
  int i, j, d;

  for (i = 0, d = 1; i < (s->size * s->size - 1); ++i, d *= 10) {}
  for (i = s->key = 0; i < s->size; ++i) {
    for (j = 0; j < s->size; ++j, d /= 10) {
      s->key += s->p[i][j] * d;
    }
  }
}

static int eight_puzzle(const state_t *s) {
  direction_t d[DIRECTION_SIZE] = {UP, DOWN, RIGHT, LEFT};
  state_t *s1, *s2;
  node_t *root, *node;
  queue_t *q;
  int cnt, fail, i;

  cnt = -1;
  q = new_queue(DEFAULT_QUEUE_SIZE);
  s1 = copy_state(s);
  enqueue(q, s1);
  root = new_node(s1->key);

  // BFS
  while (q->size > 0) {
    s1 = dequeue(q);
    if (s1 == NULL) break; // unsolvable or bug
    if (s1->key == RESOLVED_PUZZLE_KEY) {
      cnt = s1->cnt;
      free_state(s1);
      break;
    }
    for (i = 0; i < DIRECTION_SIZE; ++i) {
      s2 = copy_state(s1);
      fail = advance_state(s2, d[i]);
      node = find_node(root, s2->key);
      if (fail || node) {
        free_state(s2);
        continue;
      }
      enqueue(q, s2);
      node = new_node(s2->key);
      insert_node(root, node);
      root = rebalance(root);
    }
    free_state(s1);
  }

  free_queue(q);
  free_node(root);
  return cnt;
}

int main(int argc, char **argv) {
  state_t *s;
  int i, j;

  for (i = 0, s = new_state(PUZZLE_SIZE); i < s->size; ++i) {
    for (j = 0; j < s->size; ++j) {
      scanf("%d", &s->p[i][j]);
      if (s->p[i][j] == 0) {
        s->zero.row = i;
        s->zero.col = j;
      }
    }
  }
  update_state_key(s);
  printf("%d\n", eight_puzzle(s));
  free_state(s);
}
