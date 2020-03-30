#include <stdio.h>
#define SIZE 8
#define CELL_SKIP -3
#define UNSAFE(cell) (cell > 0)
#define QUEEN(cell) (cell < 0)
#define SKIP(cell) (cell == CELL_SKIP)
#define PUT_FIXED_QUEEN(cb, r, c) \
  do {\
    cb[r][c] = -2;\
    dot_radially(cb, r, c, 1);\
  } while (0)
#define PUT_QUEEN(cb, r, c) \
  do {\
    cb[r][c] = -1;\
    dot_radially(cb, r, c, 1);\
  } while (0)
#define REMOVE_QUEEN(cb, r, c) \
  do {\
    cb[r][c] = 0;\
    dot_radially(cb, r, c, -1);\
  } while (0)

typedef struct { int r, c; } cell_t;

static void initialize(int cb[SIZE][SIZE]) {
  int i, j;

  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) cb[i][j] = 0;
  }
}

static void print_chess_board(int cb[SIZE][SIZE]) {
  int i, j;

  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      if (QUEEN(cb[i][j])) {
        printf("%s", "Q");
      } else if (UNSAFE(cb[i][j])) {
        printf("%s", ".");
      } else {
        printf("%s", "X");
      }
    }
    printf("\n");
  }
}

static void dot_radially(int cb[SIZE][SIZE], int r, int c, int d) {
  int i;

  for (i = 1; r-i >= 0 || r+i < SIZE || c-i >= 0 || c+i < SIZE; ++i) {
    if (r-i >= 0)                 cb[r-i][c+0] += d;
    if (r-i >= 0 && c+i < SIZE)   cb[r-i][c+i] += d;
    if (c+i < SIZE)               cb[r+0][c+i] += d;
    if (r+i < SIZE && c+i < SIZE) cb[r+i][c+i] += d;
    if (r+i < SIZE)               cb[r+i][c+0] += d;
    if (r+i < SIZE && c-i >= 0)   cb[r+i][c-i] += d;
    if (c-i >= 0)                 cb[r+0][c-i] += d;
    if (r-i >= 0 && c-i >= 0)     cb[r-i][c-i] += d;
  }
}

static void try_eight_queen(int cb[SIZE][SIZE]) {
  int i, j, k;
  cell_t stk[SIZE];

  for (i = k = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      if (UNSAFE(cb[i][j])) continue;
      if (SKIP(cb[i][j])) {
        cb[i][j] = 0;
        continue;
      }
      if (QUEEN(cb[i][j])) break;
      if (k < SIZE) {
        stk[k].r = i;
        stk[k].c = j;
        PUT_QUEEN(cb, stk[k].r, stk[k].c);
        ++k;
        break;
      }
    }
    if (j < SIZE) continue;
    if (k > 0) {
      --k;
      REMOVE_QUEEN(cb, stk[k].r, stk[k].c);
      cb[stk[k].r][stk[k].c] = CELL_SKIP;
      i = stk[k].r - 1;
    }
  }
}

int main(int argc, char **argv) {
  int i, k, r, c, cb[SIZE][SIZE];

  initialize(cb);
  scanf("%d", &k);
  for (i = 0; i < k; ++i) {
    scanf("%d %d", &r, &c);
    PUT_FIXED_QUEEN(cb, r, c);
  }
  try_eight_queen(cb);
  print_chess_board(cb);
}
