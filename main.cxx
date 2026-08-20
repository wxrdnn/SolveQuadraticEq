#include "io.h"
#include "myassert.h"
#include "solve.h"

int main()
{
  // TODO assert
  assert(0);

  double a = 0, b = 0, c = 0;
  double x1 = 0, x2 = 0;

  DisplayGreeting();
  DisplayCat();

  GetInput(&a, &b, &c);

  int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
  DisplayOutput(roots, &x1, &x2);

  return 0;
}
