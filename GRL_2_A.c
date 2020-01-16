#include <stdio.h>
#include <stdlib.h>
#define UNKNOWN_ID -1
#define SENTINEL (1 << 30)

typedef struct { int s, t, w; } edge_t;

static void merge(edge_t *a, int left, int mid, int right) {
  int n1, n2, i, j, k;
  edge_t *l, *r;

  n1 = mid - left;
  l = (edge_t *) malloc(sizeof(edge_t) * (n1 + 1));
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i].s = l[i].t = UNKNOWN_ID;
  l[i].w = SENTINEL;

  n2 = right - mid;
  r = (edge_t *) malloc(sizeof(edge_t) * (n2 + 1));
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i].s = r[i].t = UNKNOWN_ID;
  r[i].w = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i].w <= r[j].w) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }
  free(l); free(r);
}

static void merge_sort(edge_t *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static int find_representative(int *ds, int i) {
  if (i != ds[i]) ds[i] = find_representative(ds, ds[i]);
  return ds[i];
}

static int kruskal(edge_t *es, int e, int *ds, int v) {
  int mst_cost, i, r1, r2;

  for (i = mst_cost = 0; i < e; ++i) {
    r1 = find_representative(ds, es[i].s);
    r2 = find_representative(ds, es[i].t);
    if (r1 != r2) {
      mst_cost += es[i].w;
      ds[r1] = r2;
    }
  }
  return mst_cost;
}

int main(int argc, char **argv) {
  int v, e, i, *ds; // disjoint-set
  edge_t x, *es;    // edges

  scanf("%d %d", &v, &e);
  ds = (int *) malloc(sizeof(int) * v);
  es = (edge_t *) malloc(sizeof(edge_t) * e);
  for (i = 0; i < v; ++i) ds[i] = i;
  for (i = 0; i < e; ++i) {
    scanf("%d %d %d", &x.s, &x.t, &x.w);
    es[i] = x;
  }
  merge_sort(es, 0, e);
  printf("%d\n", kruskal(es, e, ds, v));
  free(es); free(ds);
}
