#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_VARR_SIZE 8
#define UNKNOWN_ID -1
#define START_ID 0
#define SENTINEL (1 << 30)

typedef struct { int size, i, *arr; } varr_t;
typedef struct { int i, *arr; } carr_t;

static void merge(int *a, int left, int mid, int right) {
  int n1, n2, i, j, k, *l, *r;

  n1 = mid - left;
  l = (int *) malloc(sizeof(int) * (n1 + 1));
  if (l == NULL) return;
  for (i = 0; i < n1; ++i) l[i] = a[left + i];
  l[i] = SENTINEL;

  n2 = right - mid;
  r = (int *) malloc(sizeof(int) * (n2 + 1));
  if (r == NULL) return;
  for (i = 0; i < n2; ++i) r[i] = a[mid + i];
  r[i] = SENTINEL;

  for (i = j = 0, k = left; k < right; ++k) {
    if (l[i] <= r[j]) {
      a[k] = l[i++];
    } else {
      a[k] = r[j++];
    }
  }
  free(l); free(r);
}

static void merge_sort(int *a, int left, int right) {
  int mid;

  if (left >= right - 1) return;
  mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid, right);
  merge(a, left, mid, right);
}

static void dfs(int size, const varr_t *g, carr_t *pr, int *vf, int *pi, int *sr, int m, int prev) {
  int i, n;

  if (vf[m]) return;
  pr->arr[m] = sr[m] = pr->i;
  pr->i++;
  vf[m] = 1;
  for (i = 0; i < g[m].i; ++i) {
    n = g[m].arr[i];
    if (!vf[n]) {
      pi[n] = m;
      dfs(size, g, pr, vf, pi, sr, n, m);
      if (sr[n] < sr[m]) sr[m] = sr[n];
    } else if (n != prev) {
      if (pr->arr[n] < sr[m]) sr[m] = pr->arr[n];
    }
  }
}

static void print_articulation_points(int size, carr_t *pr, int *pi, int *sr) {
  int i, p, start_id_children_cnt;
  varr_t ap;

  start_id_children_cnt = 0;
  ap.size = DEFAULT_VARR_SIZE;
  ap.i = 0;
  ap.arr = (int *) malloc(sizeof(int) * ap.size);
  for (i = 0; i < size; ++i) {
    p = pi[i];
    if (p == UNKNOWN_ID) {
      continue;
    } else if (p == START_ID) {
      ++start_id_children_cnt;
    } else if (pr->arr[p] <= sr[i]) {
      if (ap.i == ap.size) {
        ap.size *= 2;
        ap.arr = (int *) realloc(ap.arr, sizeof(int) * ap.size);
      }
      ap.arr[ap.i++] = p;
    }
  }
  if (start_id_children_cnt > 1) {
    if (ap.i == ap.size) {
      ap.size *= 2;
      ap.arr = (int *) realloc(ap.arr, sizeof(int) * ap.size);
    }
    ap.arr[ap.i++] = START_ID;
  }
  merge_sort(ap.arr, 0, ap.i);
  for (i = 0; i < ap.i; ++i) {
    if (i == 0 || ap.arr[i - 1] != ap.arr[i]) printf("%d\n", ap.arr[i]);
  }
  free(ap.arr);
}

int main(int argc, char **argv) {
  int v, e, k, l, i, *vf, *pi, *sr; // visited flags, parent ids, sub-root ids
  carr_t pr;                        // pre-ordered numbers
  varr_t *g;                        // graph data

  scanf("%d %d", &v, &e);
  vf = (int *) malloc(sizeof(int) * v);
  pi = (int *) malloc(sizeof(int) * v);
  sr = (int *) malloc(sizeof(int) * v);
  pr.i = 0;
  pr.arr = (int *) malloc(sizeof(int) * v);
  g = (varr_t *) malloc(sizeof(varr_t) * v);
  for (i = 0; i < v; ++i) {
    vf[i] = 0;
    pi[i] = sr[i] = pr.arr[i] = UNKNOWN_ID;
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
    if (g[l].i == g[l].size) {
      g[l].size *= 2;
      g[l].arr = (int *) realloc(g[l].arr, sizeof(int) * g[l].size);
    }
    g[k].arr[g[k].i++] = l;
    g[l].arr[g[l].i++] = k;
  }
  dfs(v, g, &pr, vf, pi, sr, START_ID, UNKNOWN_ID);
  print_articulation_points(v, &pr, pi, sr);
  for (i = 0; i < v; ++i) free(g[i].arr);
  free(g); free(pr.arr); free(vf); free(pi); free(sr);
}
