#include "io.h"
#include "solve.h"
#include <stdio.h>
#include <stdlib.h>

void TestRandom(int testAmount);

int main()
{
  DisplayGreeting();
  printf("Enter random test amount:\n");
  int n = 0;
  scanf("%d", &n);
  TestRandom(n);
}

void TestRandom(int testAmount)
{
  for (int i = 0; i < testAmount; ++i)
  {
    double a = rand() % 2026;
    double b = rand() % 2026;
    double c = rand() % 2026;
    double x1 = 0, x2 = 0;

    DisplayInput(a, b, c);

    int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
    DisplayOutput(roots, &x1, &x2);

    printf("%s", "\n\n");
  }
}
