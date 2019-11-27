#include <stdlib.h>
#include <stdio.h>

#define NODE_TYPE(node, type)           \
  do {                                  \
    if (node.parent == -1) {            \
      type = "root";                    \
    } else if (node.children == NULL) { \
      type = "leaf";                    \
    } else {                            \
      type = "internal node";           \
    }                                   \
  } while (0)

typedef struct { int id, parent, *children, size; } node;

static int count_depth(node *nodes, int id) {
  int depth;

  for (depth = -1; id > -1; ++depth) id = nodes[id].parent;
  return depth;
}

int main(int argc, char **argv) {
  int n, i, j, id, k, depth;
  node *nodes;
  char *type;

  scanf("%d", &n);
  nodes = (node *) malloc(sizeof(node) * n);
  for (i = 0; i < n; ++i) {
    nodes[i].parent = -1;
    nodes[i].children = NULL;
  }
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &id, &k);
    nodes[id].id = id;
    nodes[id].size = k;
    if (k == 0) continue;
    nodes[id].children = (int *) malloc(sizeof(int) * k);
    for (j = 0; j < k; ++j) {
      scanf("%d", &nodes[id].children[j]);
      nodes[nodes[id].children[j]].parent = id;
    }
  }
  for (i = 0; i < n; ++i) {
    NODE_TYPE(nodes[i], type);
    depth = count_depth(nodes, i);
    printf("node %d: parent = %d, depth = %d, %s, [",
        nodes[i].id, nodes[i].parent, depth, type);
    for (j = 0; j < nodes[i].size; ++j) {
      if (j > 0) printf(", ");
      printf("%d", nodes[i].children[j]);
    }
    printf("]\n");
  }
  for (i = 0; i < n; ++i) free(nodes[i].children);
  free(nodes);
  exit(0);
}
