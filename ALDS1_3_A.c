#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_STACK_SIZE 12
#define MAX_STR_SIZE 12

struct stack {
  char **arr;
  int i;
  int size;
};

static void
init_stack(struct stack *s) {
  s->arr = (char **) malloc(sizeof(char *) * DEFAULT_STACK_SIZE);
  s->size = s->arr == NULL ? 0 : DEFAULT_STACK_SIZE;
  s->i = 0;
}

static void
expand_stack_if_needed(struct stack *s) {
  char **tmp;

  if (s->i < s->size) return;

  tmp = (char **) realloc(s->arr, sizeof(char *) * s->size * 2);
  if (tmp == NULL) return;
  s->arr = tmp;
  s->size *= 2;
}

static void
push_stack(struct stack *s, char *v) {
  expand_stack_if_needed(s);
  s->arr[s->i] = v;
  s->i++;
}

static char *
pop_stack(struct stack *s) {
  char *v;

  if (s->i == 0) return NULL;

  v = s->arr[s->i - 1];
  s->i--;
  s->arr[s->i] = NULL;

  return v;
}

static void
destroy_stack(struct stack *s) {
  int i;

  for (i = 0; i < s->size; ++i) {
    free(s->arr[i]);
    s->arr[i] = NULL;
  }
  free(s->arr);
  s->arr = NULL;
}

static int
read_expr_and_calc(FILE *f, struct stack *s) {
  char *str;
  int m, n, ret;
  char *a;
  char *b;

  while (1) {
    str = (char *) malloc(sizeof(char) * MAX_STR_SIZE);
    if (str == NULL) break;

    n = fscanf(f, "%s", str);
    if (errno != 0) perror("fscanf");
    if (n == EOF) break;

    if (strcmp(str, "+") == 0) {
      b = pop_stack(s);
      a = pop_stack(s);
      m = atoi(a);
      n = atoi(b);
      free(a);
      free(b);
      a = b = NULL;
      snprintf(str, MAX_STR_SIZE, "%d", m + n);
      push_stack(s, str);
    } else if (strcmp(str, "-") == 0) {
      b = pop_stack(s);
      a = pop_stack(s);
      m = atoi(a);
      n = atoi(b);
      free(a);
      free(b);
      a = b = NULL;
      snprintf(str, MAX_STR_SIZE, "%d", m - n);
      push_stack(s, str);
    } else if (strcmp(str, "*") == 0) {
      b = pop_stack(s);
      a = pop_stack(s);
      m = atoi(a);
      n = atoi(b);
      free(a);
      free(b);
      a = b = NULL;
      snprintf(str, MAX_STR_SIZE, "%d", m * n);
      push_stack(s, str);
    } else if (strcmp(str, "/") == 0) {
      b = pop_stack(s);
      a = pop_stack(s);
      m = atoi(a);
      n = atoi(b);
      free(a);
      free(b);
      a = b = NULL;
      snprintf(str, MAX_STR_SIZE, "%d", m / n);
      push_stack(s, str);
    } else {
      push_stack(s, str);
    }
  }

  str = pop_stack(s);
  ret = atoi(str);
  free(str);
  str = NULL;
  return ret;
}

int
main(int argc, char **argv) {
  struct stack s;
  int n;

  init_stack(&s);
  n = read_expr_and_calc(stdin, &s);
  printf("%d\n", n);
  destroy_stack(&s);
  exit(0);
}
