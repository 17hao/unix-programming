// section 5.2
#include <ctype.h>

#define EOF '\0'

int getch(void);
void ungetch(int);  // section 4.3

// getint: get next integer from input into pn.
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch())) {
  }

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }

  sign = (c == '+') ? 1 : -1;
  if (c == '+' || c == '-') {
    c = getch();
  }
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn = *pn * sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}