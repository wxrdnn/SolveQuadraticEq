#include "solve.h"
#include "io.h"

int main() {
  double a = 0, b = 0, c = 0;
  double x1 = 0, x2 = 0;

  DisplayGreeting();

  if (GetInput(&a, &b, &c) != 0)
      return 1;

  int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
  DisplayOutput(roots, &x1, &x2);

  return 0;
}
