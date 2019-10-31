#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_PROC_NAME_SIZE 16

struct proc {
  char name[MAX_PROC_NAME_SIZE];
  int time;
};

struct proc_list {
  struct proc *ps;
  int head;
  int tail;
  int size;
  int quantum;
};

static void
read_procs(FILE *f, struct proc_list *pl, int size) {
  int ret, i;

  for (i = 0; i < size; ++i) {
    ret = fscanf(f, "%s", pl->ps[i].name);
    if (errno != 0) perror("fscanf");
    if (ret == EOF) break;

    ret = fscanf(f, "%d", &pl->ps[i].time);
    if (errno != 0) perror("fscanf");
    if (ret == EOF) break;
  }
}

static void
enqueue(struct proc_list *pl, struct proc p) {
  pl->tail++;
  if (pl->tail == pl->size) pl->tail = 0;
  pl->ps[pl->tail] = p;
}

static struct proc
dequeue(struct proc_list *pl) {
  struct proc p;

  p = pl->ps[pl->head++];
  if (pl->head == pl->size) pl->head = 0;
  return p;
}

static void
do_process(FILE *f, struct proc_list *pl) {
  int elapsed;
  struct proc p;

  elapsed = 0;
  while (pl->head != pl->tail) {
    p = dequeue(pl);

    if (p.time <= pl->quantum) {
      fprintf(f, "%s %d\n", p.name, elapsed + p.time);
      elapsed += p.time;
      p.time = 0;
    } else {
      elapsed += pl->quantum;
      p.time -= pl->quantum;
      enqueue(pl, p);
    }
  }

  fprintf(f, "%s %d\n", pl->ps[pl->head].name, elapsed + pl->ps[pl->head].time);
}

int
main(int argc, char **argv) {
  int ret;
  struct proc_list pl;

  ret = fscanf(stdin, "%d", &pl.size);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  ret = fscanf(stdin, "%d", &pl.quantum);
  if (errno != 0) perror("fscanf");
  if (ret < 1) exit(1);

  pl.head = 0;
  pl.tail = pl.size - 1;
  pl.size++;
  pl.ps = (struct proc *) malloc(sizeof(struct proc) * pl.size);
  if (pl.ps == NULL) exit(1);

  read_procs(stdin, &pl, pl.size - 1);
  do_process(stdout, &pl);

  free(pl.ps);
  pl.ps = NULL;
  exit(0);
}
