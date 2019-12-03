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

static node *find_node(node *n, int k) {
  node *ret;
  if (n == NULL) {
    ret = NULL;
  } else if (k == n->k) {
    ret = n;
  } else if (n->l != NULL && k < n->k) {
    ret = find_node(n->l, k);
  } else if (n->r != NULL && k > n->k) {
    ret = find_node(n->r, k);
  } else {
    ret = NULL;
  }
  return ret;
}

static node *find_successor(node *n) {
  node *p;

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

static node *delete_node(node *r, node *n) {
  node *dn;
  node *cn;
  node *rn;

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
  if (dn != n) n->k = dn->k;
  free(dn); dn = NULL;

  return rn;
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
    switch (cmd[0]) {
      case 'i':
        scanf("%d", &k);
        n = build_node(k);
        if (r == NULL) {
          r = n;
        } else {
          insert_node(r, n);
        }
        break;
      case 'f':
        scanf("%d", &k);
        n = find_node(r, k);
        printf("%s\n", n == NULL ? "no" : "yes");
        break;
      case 'd':
        scanf("%d", &k);
        n = find_node(r, k);
        r = delete_node(r, n);
        break;
      case 'p':
        print_inorder(r); printf("\n");
        print_preorder(r); printf("\n");
        break;
      default:
        break;
    }
  }
  free_node(r);
  exit(0);
}
