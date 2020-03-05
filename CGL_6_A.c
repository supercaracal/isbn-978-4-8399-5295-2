#include <stdio.h>
#include <stdlib.h>

#define SENTINEL (1 << 30)

typedef enum { BOTTOM, LEFT, RIGHT, TOP, UNKNOWN } end_point_t;
typedef enum { VERTICAL, HORIZONTAL, DIAGONAL } slope_t;
typedef struct { int x, y, pair_x; end_point_t t; } point_t;
typedef struct { point_t p0, p1; } segment_t;
typedef struct Node { int x; struct Node *p, *l, *r; } node_t;

static segment_t swap_point(segment_t s) {
  point_t tmp;

  tmp = s.p0;
  s.p0 = s.p1;
  s.p1 = tmp;
  return s;
}

static segment_t normalize(segment_t s) {
  if (s.p0.x == s.p1.x) {
    if (s.p0.y > s.p1.y) s = swap_point(s);
    s.p0.t = BOTTOM;
    s.p1.t = TOP;
  } else if (s.p0.y == s.p1.y) {
    if (s.p0.x > s.p1.x) s = swap_point(s);
    s.p0.t = LEFT;
    s.p1.t = RIGHT;
  } else {
    s.p0.t = s.p1.t = UNKNOWN;
  }
  s.p0.pair_x = s.p1.x;
  s.p1.pair_x = s.p0.x;
  return s;
}

static void merge(point_t *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  point_t *l, *r;

  n1 = mid - left;
  l = (point_t *) malloc(sizeof(point_t) * (n1 + 1));
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i].x = l[i].y = SENTINEL;

  n2 = right - mid;
  r = (point_t *) malloc(sizeof(point_t) * (n2 + 1));
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i].x = r[i].y = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i].y < r[j].y || (l[i].y == r[j].y && l[i].t < r[j].t)) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }
  free(l);
  free(r);
}

static void merge_sort(point_t *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static node_t *new_node(int x) {
  node_t *n;

  n = (node_t *) malloc(sizeof(node_t));
  n->p = n->l = n->r = NULL;
  n->x = x;
  return n;
}

static void insert_node(node_t *r, node_t *n) {
  if (n->x <= r->x) {
    if (r->l == NULL) {
      r->l = n;
      n->p = r;
    } else {
      insert_node(r->l, n);
    }
  } else {
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
  } else if (n->l != NULL && x < n->x) {
    ret = find_node(n->l, x);
  } else if (n->r != NULL && x > n->x) {
    ret = find_node(n->r, x);
  } else {
    ret = NULL;
  }
  return ret;
}

static node_t *find_successor(node_t *n) {
  node_t *p;

  if (n->r != NULL) {
    n = n->r;
    while (n->l != NULL) n = n->l;
    return n;
  }

  p = n->p;
  while (p != NULL && n == p->r) {
    n = p;
    p = p->p;
  }
  return p;
}

static node_t *delete_node(node_t *r, node_t *n) {
  node_t *dn, *cn, *rn;

  if (n == NULL) return r;
  dn = (n->l == NULL || n->r == NULL) ? n : find_successor(n);
  cn = (dn->l != NULL) ? dn->l : dn->r;
  if (cn != NULL) cn->p = dn->p;
  rn = r;
  if (dn->p == NULL) {
    rn = cn;
  } else if (dn == dn->p->l) {
    dn->p->l = cn;
  } else {
    dn->p->r = cn;
  }
  if (dn != n) n->x = dn->x;
  free(dn);
  dn = NULL;
  return rn;
}

static int count_node(node_t *n, int first, int last) {
  if (n == NULL) return 0;
  return (n->x < first || n->x > last ? 0 : 1) + count_node(n->l, first, last) + count_node(n->r, first, last);
}

static void free_node(node_t *n) {
  if (n == NULL) return;
  free_node(n->l);
  free_node(n->r);
  free(n);
}

/*
static void print_inorder(const node_t *n) {
  if (n == NULL) return;
  print_inorder(n->l);
  printf("%d ", n->x);
  print_inorder(n->r);
}

static void print_points(const point_t *ps, int size) {
  int i;
  char *t;

  for (i = 0; i < size; ++i) {
    switch (ps[i].t) {
      case TOP:
        t = "TOP";
        break;
      case BOTTOM:
        t = "BOTTOM";
        break;
      case LEFT:
        t = "LEFT";
        break;
      default:
        break;
    }
    printf("x: %d, y: %d, pair-x: %d, type: %s\n", ps[i].x, ps[i].y, ps[i].pair_x, t);
  }
}
*/

static int sweep_as_manhattan_geometry(const point_t *ps, int size) {
  node_t *root, *node;
  int i, cnt;

  //print_points(ps, size);
  //printf("\n");

  for (i = cnt = 0, root = NULL; i < size; ++i) {
    switch (ps[i].t) {
      case TOP:
        if (root != NULL) {
          node = find_node(root, ps[i].x);
          if (node != NULL) root = delete_node(root, node);
        }
        break;
      case BOTTOM:
        node = new_node(ps[i].x);
        if (root == NULL) {
          root = node;
        } else {
          insert_node(root, node);
        }
        break;
      case LEFT:
        if (root != NULL) {
          //printf("From: %d, To: %d, B-Tree: ", ps[i].x, ps[i].pair_x);
          //print_inorder(root);
          //printf("\n");
          cnt += count_node(root, ps[i].x, ps[i].pair_x);
        }
        break;
      default:
        break;
    }
  }
  free_node(root);
  return cnt;
}

int main(int argc, char **argv) {
  segment_t s;
  point_t *ps;
  int n, i, j;

  scanf("%d", &n);
  ps = (point_t *) malloc(sizeof(point_t) * n * 2);
  for (i = j = 0; i < n; ++i) {
    scanf("%d %d %d %d", &s.p0.x, &s.p0.y, &s.p1.x, &s.p1.y);
    s = normalize(s);
    ps[j++] = s.p0;
    ps[j++] = s.p1;
  }
  merge_sort(ps, 0, j);
  printf("%d\n", sweep_as_manhattan_geometry(ps, j));
  free(ps);
}
