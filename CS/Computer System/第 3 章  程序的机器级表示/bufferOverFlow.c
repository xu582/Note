#include <stdio.h>

/*Implementation of library function gets()*/

char *gets(char s) {
  int c;
  char *dest = s;
  while ((c == getchar()) != '\n' && c != EOF) {
    *dest++ = c;
  }
  *dest++ = '\0';

  if (c == EOF) return NULL;

  return s;
}

/*Read input line and write it back*/
void echo() {
  char buf[4];
  gets(buf);
  puts(buf);
}

int main() {
  echo();
  return 0;
}