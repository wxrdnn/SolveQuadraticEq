#include "io.h"
#include "assert.h"
#include "solve.h"
#include <stdio.h>

void DisplayGreeting()
{
  printf("%s", "# Solve quadratic equation\n# Made by Chumakov Alexey (c) "
               "2026\n# ^..^\n\n");
  return;
}

bool GetInput(double *a, double *b, double *c)
{
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);

  printf("%s", "Enter a, b, c separated by space:\n");
  if (scanf("%lg %lg %lg", a, b, c) != 3) // TODO repeat input
  {
    printf("%s", "Error: Incorrect input.\n");
    return false;
  }
  return true;
}

void DisplayOutput(int roots, const double *x1, const double *x2)
{
  switch (roots)
  {
  case Two:
    printf("There are two roots:\nx1: %lg\nx2: %lg\n", *x1, *x2);
    break;
  case One:
    printf("There is one root:\nx: %lg\n", *x1);
    break;
  case Zero:
    printf("%s", "There are no roots for this equation\n");
    break;
  case Infinite:
    printf("%s", "There are infinite number of roots for this equation\n");
    break;
  default:
    printf("%s", "Invalid number of roots\n");
    break;
  }
  return;
}

void DisplayInput(const double a, const double b, const double c)
{
  printf("Solving (%lg) * x2 + (%lg) * x + (%lg)\n", a, b, c);
}
