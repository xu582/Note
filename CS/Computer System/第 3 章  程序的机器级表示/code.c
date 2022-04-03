#include <stdio.h>

int accum = 0;

int sum(int x, int y) {
  int t = x + y;
  accum += t;
  return t;
}

int simple(int *xp, int y) {
  int t = *xp + y;
  *xp = t;
  return t;
}

int main() {
  printf("sum = %d\n", sum(2, 3));
  return 0;
}
