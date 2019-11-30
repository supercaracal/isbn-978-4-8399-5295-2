#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 40
#define SENTINEL -1
typedef struct { int left, right; } node;

static int build(node *nodes, int *pre, int *in, int left, int right) {
  int i, m;

  if (right - left == 1) return in[left];
  if (left == right) return SENTINEL;
  for (i = m = left; i < right; ++i) {
    if (in[i] == *pre) {
      m = i; break;
    }
  }
  nodes[*pre].left = build(nodes, pre + 1, in, left, m);
  nodes[*pre].right = build(nodes, pre + (m - left + 1), in, m + 1, right);
  return *pre;
}

static int postorder(const node *nodes, int id, int is_first) {
  if (id < 1 || id > 40) return is_first; // FIXME: WTF
  is_first = postorder(nodes, nodes[id].left, is_first);
  is_first = postorder(nodes, nodes[id].right, is_first);
  if (!is_first) printf(" ");
  printf("%d", id);
  return 0;
}

int main(int argc, char **argv) {
  int n, i, root, pre[MAX_SIZE], in[MAX_SIZE];
  node nodes[MAX_SIZE];

  scanf("%d", &n);
  for (i = 0; i < MAX_SIZE; ++i) pre[i] = in[i] = nodes[i].left = nodes[i].right = SENTINEL;
  for (i = 0; i < n; ++i) scanf("%d", &pre[i]);
  for (i = 0; i < n; ++i) scanf("%d", &in[i]);
  root = build(nodes, pre, in, 0, n);
  postorder(nodes, root, 1); printf("\n");
  exit(0);
}
