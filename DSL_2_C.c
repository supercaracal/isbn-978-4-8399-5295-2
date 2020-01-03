#include <stdio.h>
#include <stdlib.h>
#define SENTINEL (1 << 30)
#define DEFAULT_SUBSET_SIZE 16

typedef struct { int i, x, y; } point_t;
typedef struct { int sx, tx, sy, ty; } square_t;
typedef struct Node { point_t p; struct Node *l, *r; } node_t;
typedef struct { int i, size, *ids; } result_t;

static void merge_for_vertex(point_t *p, int left, int mid, int right, int is_x) {
  int n1, n2, i, j, k;
  point_t *l, *r;

  n1 = mid - left;
  l = (point_t *) malloc(sizeof(point_t) * (n1 + 1));
  for (i = 0; i < n1; ++i) l[i] = p[left + i];
  l[i].x = l[i].y = SENTINEL;

  n2 = right - mid;
  r = (point_t *) malloc(sizeof(point_t) * (n2 + 1));
  for (i = 0; i < n2; ++i) r[i] = p[mid + i];
  r[i].x = r[i].y = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (is_x ? l[i].x <= r[j].x : l[i].y <= r[j].y) {
      p[k] = l[i++];
    } else {
      p[k] = r[j++];
    }
  }
  free(l); free(r);
}

static void merge_sort_for_vertex(point_t *p, int left, int right, int is_x) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort_for_vertex(p, left, mid, is_x);
  merge_sort_for_vertex(p, mid, right, is_x);
  merge_for_vertex(p, left, mid, right, is_x);
}

static node_t *make_2d_tree(point_t *p, int left, int right, int depth) {
  node_t *nd;
  int mid;

  if (left >= right) return NULL;
  nd = (node_t *) malloc(sizeof(node_t));
  merge_sort_for_vertex(p, left, right, depth % 2);
  mid = (left + right) / 2;
  nd->p = p[mid];
  nd->l = make_2d_tree(p, left, mid, depth + 1);
  nd->r = make_2d_tree(p, mid + 1, right, depth + 1);
  return nd;
}

static void free_2d_tree(node_t *n) {
  if (n->l != NULL) free_2d_tree(n->l);
  if (n->r != NULL) free_2d_tree(n->r);
  free(n);
}

static result_t rectangle_search(point_t *p, node_t *nd, square_t a, int depth, result_t r) {
  int can_search_left, can_search_right;

  if (nd == NULL) return r;
  if (r.i == r.size) {
    r.size *= 2;
    r.ids = (int *) realloc(r.ids, sizeof(int) * r.size);
  }
  can_search_left = (((depth % 2) && (a.sx <= nd->p.x)) || (!(depth % 2) && (a.sy <= nd->p.y)));
  can_search_right = (((depth % 2) && (nd->p.x <= a.tx)) || (!(depth % 2) && (nd->p.y <= a.ty)));
  if (a.sx <= nd->p.x && nd->p.x <= a.tx && a.sy <= nd->p.y && nd->p.y <= a.ty) r.ids[r.i++] = nd->p.i;
  if (can_search_left) r = rectangle_search(p, nd->l, a, depth + 1, r);
  if (can_search_right) r = rectangle_search(p, nd->r, a, depth + 1, r);
  return r;
}

static void merge_for_id(int *p, int left, int mid, int right) {
  int n1, n2, i, j, k, *l, *r;

  n1 = mid - left;
  l = (int *) malloc(sizeof(int) * (n1 + 1));
  for (i = 0; i < n1; ++i) l[i] = p[left + i];
  l[i] = SENTINEL;

  n2 = right - mid;
  r = (int *) malloc(sizeof(int) * (n2 + 1));
  for (i = 0; i < n2; ++i) r[i] = p[mid + i];
  r[i] = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i] <= r[j]) {
      p[k] = l[i++];
    } else {
      p[k] = r[j++];
    }
  }
  free(l); free(r); // FIXME: double free or corruption
}

static void merge_sort_for_id(int *p, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort_for_id(p, left, mid);
  merge_sort_for_id(p, mid, right);
  merge_for_id(p, left, mid, right);
}

int main(int argc, char **argv) {
  int n, q, i, j;
  point_t *p; node_t *nd; square_t a; result_t r;

  scanf("%d", &n);
  p = (point_t *) malloc(sizeof(point_t) * n);
  for (i = 0; i < n; ++i) {
    p[i].i = i;
    scanf("%d %d", &p[i].x, &p[i].y);
  }
  nd = make_2d_tree(p, 0, n, 0);
  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%d %d %d %d", &a.sx, &a.tx, &a.sy, &a.ty);
    r.i = 0;
    r.size = DEFAULT_SUBSET_SIZE;
    r.ids = (int *) malloc(sizeof(int) * r.size);
    r = rectangle_search(p, nd, a, 0, r);
    merge_sort_for_id(r.ids, 0, r.i);
    for (j = 0; j < r.i; ++j) printf("%d\n", r.ids[j]);
    printf("\n"); free(r.ids);
  }
  free(p); free_2d_tree(nd);
}
