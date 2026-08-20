#include "solve.h"
#include "assert.h"
#include <cmath>
#include <math.h>

#define ETZ_EPSILON 1e-10

int EqualToZero(const double x);
double GetDiscriminant(const double a, const double b, const double c);

int SolveQuadraticEquation(const double a, const double b, const double c,
                           double *x1, double *x2) {
  assert(std::isfinite(a));
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (EqualToZero(a))
    return SolveLinearEquation(b, c, x1);
  else {
    double discriminant = GetDiscriminant(a, b, c);
    if (discriminant < 0)
      return 0;
    else if (EqualToZero(discriminant)) {
      double root = -b / 2.0 / a;
      *x1 = EqualToZero(root) ? 0 : root;
      return 1;
    }
    double sqrtDiscriminant = sqrt(discriminant);
    double root1 = (-b + sqrtDiscriminant) / 2.0 / a;
    double root2 = (-b - sqrtDiscriminant) / 2.0 / a;
    *x1 = EqualToZero(root1) ? 0 : root1;
    *x2 = EqualToZero(root2) ? 0 : root2;
    return 2;
  }
}

int SolveLinearEquation(const double a, const double b,
                        double *x) { // ax + b = 0
  assert(x != NULL);
  assert(std::isfinite(a));
  assert(std::isfinite(b));

  if (EqualToZero(a)) {
    if (EqualToZero(b))
      return SLE_INFINITE_ROOTS;
    return 0;
  }
  double root = -b / a;
  *x = EqualToZero(root) ? 0 : root;
  return 1;
}

int EqualToZero(const double x) { return (fabs(x - 0) < ETZ_EPSILON); }

double GetDiscriminant(const double a, const double b, const double c) { return b * b - 4 * a * c; }
