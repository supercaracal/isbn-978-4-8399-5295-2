#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int k;
  struct node *p;
  struct node *l;
  struct node *r;
} node;

static node *build_node(int k) {
  node *n;
  n = (node *) malloc(sizeof(node));
  n->p = n->l = n->r = NULL;
  n->k = k;
  return n;
}

static void insert_node(node *r, node *n) {
  if (n->k <= r->k) {
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

static void print_inorder(node *n) {
  if (n->l != NULL) print_inorder(n->l);
  printf(" %d", n->k);
  if (n->r != NULL) print_inorder(n->r);
}

static void print_preorder(node *n) {
  printf(" %d", n->k);
  if (n->l != NULL) print_preorder(n->l);
  if (n->r != NULL) print_preorder(n->r);
}

static void free_node(node *n) {
  if (n == NULL) return;
  free_node(n->l);
  free_node(n->r);
  free(n);
}

int main(int argc, char **argv) {
  int m, i, k;
  char cmd[8];
  node *r = NULL;
  node *n;

  scanf("%d", &m);
  for (i = 0; i < m; ++i) {
    scanf("%s", cmd);
    if (cmd[0] == 'i') {
      scanf("%d", &k);
      n = build_node(k);
      if (r == NULL) {
        r = n;
      } else {
        insert_node(r, n);
      }
    } else {
      print_inorder(r); printf("\n");
      print_preorder(r); printf("\n");
    }
  }
  free_node(r);
  exit(0);
}
