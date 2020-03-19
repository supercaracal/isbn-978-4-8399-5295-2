#include <stdio.h>
#include <stdlib.h>
#define MIN_NUM -1
#define ABS_DIFF(a, b) (a - b < 0 ? (a - b) * -1 : a - b)
typedef struct Node { int x, bf; struct Node *p, *l, *r; } node_t;

static node_t *new_node(int x) {
  node_t *n;

  n = (node_t *) malloc(sizeof(node_t));
  n->p = n->l = n->r = NULL;
  n->x = x;
  n->bf = 1;
  return n;
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

// @see https://www.cs.usfca.edu/~galles/visualization/AVLtree.html AVLtree Visualization
static node_t *rebalance(node_t *n) {
  int l, r;

  if (n == NULL) return n;
  l = n->l == NULL ? 0 : n->l->bf;
  r = n->r == NULL ? 0 : n->r->bf;
  n->bf = (l > r ? l : r) + 1;
  if (ABS_DIFF(l, r) > 1) {
    if (l < r) {
      n = rotate_left(n);
    } else {
      n = rotate_right(n);
    }
  }
  return n->p ? rebalance(n->p) : n;
}

static node_t *find_lower_bound_node(node_t *n, int min) {
  if (n == NULL) return NULL;
  if (min == n->x || (min < n->x && n->l == NULL)) return n;
  if (min > n->x && n->r == NULL) return n->p;
  if (min < n->x && n->l != NULL) return find_lower_bound_node(n->l, min);
  if (min > n->x && n->r != NULL) return find_lower_bound_node(n->r, min);
  return NULL;
}

static int count_node(const node_t *n) {
  if (n == NULL) return 0;
  return 1 + count_node(n->l) + count_node(n->r);
}

static void free_node(node_t *n) {
  if (n == NULL) return;
  free_node(n->l);
  free_node(n->r);
  free(n);
}

#ifdef DEBUG
static void print_inorder(const node_t *n) {
  if (n == NULL) return;
  print_inorder(n->l);
  printf("%d ", n->x);
  print_inorder(n->r);
}
#endif

static int count_longest_increasing_subsequence(const int *a, int size) {
  node_t *root, *max, *node;
  int i, lis;

  max = new_node(MIN_NUM);
  for (i = 0, root = NULL; i < size; ++i) {
    if (max->x < a[i]) {
      max = node = new_node(a[i]);
      if (root == NULL) {
        root = node;
      } else {
        insert_node(root, node);
        root = rebalance(node);
      }
    } else {
      node = find_lower_bound_node(root, a[i]);
      node->x = a[i];
    }
#ifdef DEBUG
    print_inorder(root); printf("\n");
#endif
  }
  lis = count_node(root);
  free_node(root);
  return lis;
}

int main(int argc, char **argv) {
  int n, i, lis, *a;

  scanf("%d", &n);
  a = (int *) malloc(sizeof(int) * n);
  for (i = 0; i < n; ++i) scanf("%d", &a[i]);
  lis = count_longest_increasing_subsequence(a, n);
  printf("%d\n", lis);
  free(a);
}
