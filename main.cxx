#include "solve.h"
#include <stdio.h>

void Greeting();
int GetInput(double *a, double *b, double *c); // Returns 0 if input is correct, otherwise 1
void DisplayOutput(int roots, const double *x1, const double *x2);

int main() {
  double a = 0, b = 0, c = 0;
  double x1 = 0, x2 = 0;

  Greeting();

  if (GetInput(&a, &b, &c) != 0)
      return 1;

  int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
  DisplayOutput(roots, &x1, &x2);

  return 0;
}

void Greeting(){
    printf("%s", "# Solve quadratic equation\n# Made by Chumakov Alexey (c) "
                 "2026\n# ^..^\n\n");
    return;
}


int GetInput(double *a, double *b, double *c){
    printf("%s", "Enter a, b, c separated by space:\n");
    if (scanf("%lg %lg %lg", a, b, c) != 3) {
      printf("%s", "Error: Incorrect input.\n");
      return 1;
    }
    return 0;
}

void DisplayOutput(int roots, const double *x1, const double *x2){
    switch (roots) {
    case 2:
      printf("There are two roots:\nx1: %lg\nx2: %lg\n", *x1, *x2);
      break;
    case 1:
      printf("There is one root:\nx: %lg\n", *x1);
      break;
    case 0:
      printf("%s", "There are no roots for this equation\n");
      break;
    case SLE_INFINITE_ROOTS:
      printf("%s", "There are infinite number of roots for this equation\n");
      break;
    default:
      printf("%s", "Invalid number of roots\n");
      break;
    }
    return;
}
