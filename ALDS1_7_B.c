#include <stdlib.h>
#include <stdio.h>

typedef struct { int id, parent, left, right; } node;

static int dig(node *nodes, int *depths, int *heights, int id, int depth) {
  int d, d1, d2;
  if (id != -1) {
    depths[id] = depth;
    d1 = dig(nodes, depths, heights, nodes[id].left, depth + 1);
    d2 = dig(nodes, depths, heights, nodes[id].right, depth + 1);
    d = d1 > d2 ? d1 : d2;
    heights[id] = d - depth;
  } else {
    d = depth - 1;
  }
  return d;
}

int main(int argc, char **argv) {
  int n, i, id, sibling, degree, root;
  node *nodes;
  int *depths;
  int *heights;
  char *type;

  scanf("%d", &n);
  nodes = (node *) malloc(sizeof(node) * n);
  for (i = 0; i < n; ++i) {
    nodes[i].id = nodes[i].parent = nodes[i].left = nodes[i].right = -1;
  }
  for (i = 0; i < n; ++i) {
    scanf("%d", &id);
    nodes[id].id = id;
    scanf("%d %d", &nodes[id].left, &nodes[id].right);
    nodes[nodes[id].left].parent = nodes[nodes[id].right].parent = id;
  }
  for (i = 0; i < n; ++i) {
    if (nodes[i].parent == -1) {
      root = i;
      break;
    }
  }
  depths = (int *) malloc(sizeof(int) * n);
  heights = (int *) malloc(sizeof(int) * n);
  dig(nodes, depths, heights, root, 0);
  for (i = 0; i < n; ++i) {
    if (nodes[i].parent == -1) {
      type = "root";
    } else if (nodes[i].left == -1 && nodes[i].right == -1) {
      type = "leaf";
    } else {
      type = "internal node";
    }
    sibling = -1;
    if (nodes[i].parent != -1) {
      if (nodes[nodes[i].parent].left == i) {
        sibling = nodes[nodes[i].parent].right;
      } else {
        sibling = nodes[nodes[i].parent].left;
      }
    }
    degree = (nodes[i].left != -1) + (nodes[i].right != -1);
    printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, %s\n",
      nodes[i].id, nodes[i].parent, sibling, degree, depths[i], heights[i], type);
  }
  free(nodes);
  free(depths);
  // free(heights); // WTF
  exit(0);
}
