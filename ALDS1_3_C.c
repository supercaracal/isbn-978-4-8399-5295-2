#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef struct node {
  unsigned int key;
  struct node *prev;
  struct node *next;
} Node;

typedef struct meta {
  Node *first;
  Node *last;
} Meta;

static void
insert(Meta *m, unsigned int k) {
  Node *n;

  n = (struct node *) malloc(sizeof(struct node));
  if (n == NULL) return;

  n->key = k;
  n->prev = NULL;
  if (m->first != NULL) {
    n->next = m->first;
    m->first->prev = n;
  } else {
    m->last = n;
  }
  m->first = n;
}

static void
delete(Meta *m, unsigned int k) {
  Node *n;

  if (m->first == NULL) return;

  for (n = m->first; n != NULL; n = n->next) {
    if (n->key == k) {
      if (n->prev) {
        n->prev->next = n->next;
      } else {
        m->first = n->next;
      }
      if (n->next) {
        n->next->prev = n->prev;
      } else {
        m->last = n->prev;
      }
      free(n);
      break;
    }
  }
}

static void
delete_first(Meta *m) {
  Node *n;

  if (m->first == NULL) return;

  n = m->first;
  m->first = n->next;
  if (m->first) {
    m->first->prev = NULL;
  } else {
    m->last = NULL;
  }
  free(n);
}

static void
delete_last(Meta *m) {
  Node *n;

  if (m->last == NULL) return;

  n = m->last;
  m->last = n->prev;
  if (m->last) {
    m->last->next = NULL;
  } else {
    m->first = NULL;
  }
  free(n);
}

static void
free_list(Meta *m) {
  Node *n;
  Node *tmp;

  n = m->first;
  while (n) {
    tmp = n->next;
    free(n);
    n = tmp;
  }
}

int
main(int argc, char **argv) {
  char cmd[16];
  unsigned int key;
  int ret, n;
  Node *nd;

  Meta m = {NULL, NULL};

  ret = fscanf(stdin, "%d", &n);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  while(1) {
    ret = fscanf(stdin, "%s", cmd);
    if (errno != 0) perror("fscanf");
    if (ret == EOF) break;

    if (strcmp(cmd, "deleteFirst") == 0) {
      delete_first(&m);
      continue;
    }

    if (strcmp(cmd, "deleteLast") == 0) {
      delete_last(&m);
      continue;
    }

    ret = fscanf(stdin, "%u", &key);
    if (errno != 0) perror("fscanf");
    if (ret == EOF) break;

    if (strcmp(cmd, "delete") == 0) {
      delete(&m, key);
      continue;
    }

    insert(&m, key);
  }

  for (nd = m.first; nd; nd = nd->next) {
    if (nd != m.first) printf(" ");
    printf("%u", nd->key);
  }
  printf("\n");

  free_list(&m);
  exit(0);
}
