#include <stdio.h>

int g = 15;

struct str {
  int t;
  char v;
};

union uni {
  int t;
  char v;
} u;

void fun(int *xp) {
  /*f is a function pointer*/
  void (*f)(int *) = fun;

  /*Allocate structure on stack*/
  struct str s = {1, 'a'};

  /*Allocate union from heap*/
  union uni *up = (union uni *)malloc(sizeof(union uni));

  /*Locally declared array*/
  int *ip[2] = {xp, &g};

  up->v = s.v + 1;

  printf("ip = %p, *ip = %p, **ip = %d\n", ip, *ip, **ip);
  printf("ip+1 = %p, ip[1] = %p, *ip[1] = %d\n", ip + 1, ip[1], *ip[1]);
}

int main() {
  int p = 3;
  fun(&p);

  return 0;
}