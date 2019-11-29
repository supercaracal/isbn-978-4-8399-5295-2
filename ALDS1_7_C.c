#include <stdlib.h>
#include <stdio.h>
#define SENTINEL -1
typedef struct { int id, parent, left, right; } node;

static void preorder(const node *nodes, int id) {
  if (id == SENTINEL) return;
  printf(" %d", id);
  preorder(nodes, nodes[id].left);
  preorder(nodes, nodes[id].right);
}

static void inorder(const node *nodes, int id) {
  if (id == SENTINEL) return;
  inorder(nodes, nodes[id].left);
  printf(" %d", id);
  inorder(nodes, nodes[id].right);
}

static void postorder(const node *nodes, int id) {
  if (id == SENTINEL) return;
  postorder(nodes, nodes[id].left);
  postorder(nodes, nodes[id].right);
  printf(" %d", id);
}

int main(int argc, char **argv) {
  int n, i, id, root;
  node *nodes;

  scanf("%d", &n);
  nodes = (node *) malloc(sizeof(node) * n);
  for (i = 0; i < n; ++i) {
    nodes[i].id = nodes[i].parent = nodes[i].left = nodes[i].right = SENTINEL;
  }
  for (i = 0; i < n; ++i) {
    scanf("%d", &id);
    nodes[id].id = id;
    scanf("%d %d", &nodes[id].left, &nodes[id].right);
    nodes[nodes[id].left].parent = nodes[nodes[id].right].parent = id;
  }
  for (i = 0; i < n; ++i) {
    if (nodes[i].parent == SENTINEL) {
      root = i; break;
    }
  }
  printf("Preorder\n");  preorder(nodes, root);  printf("\n");
  printf("Inorder\n");   inorder(nodes, root);   printf("\n");
  printf("Postorder\n"); postorder(nodes, root); printf("\n");
  free(nodes);
  exit(0);
}
