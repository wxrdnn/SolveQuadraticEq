#include <cmath>
#include <math.h>
#include "solve.h"
#include "assert.h"

#define EPSILON 1e-10

int EqualToZero(const double x);


int SolveQuadraticEquation(const double a, const double b, const double c, double *x1,
                           double *x2) {
  assert(std::isfinite(a));
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (EqualToZero(a))
    return SolveLinearEquation(b, c, x1);
  else {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) // TODO compare to zero func
      return 0;
    else if (EqualToZero(discriminant)) {
      *x1 = -b / 2.0 / a;
      return 1;
    }
    double sqrtDiscriminant = sqrt(discriminant);
    *x1 = (-b + sqrtDiscriminant) / 2.0 / a;
    *x2 = (-b - sqrtDiscriminant) / 2.0 / a;
    return 2;
  }
}

int SolveLinearEquation(const double a, const double b, double *x) { // ax + b = 0
  assert(x != NULL);
  assert(std::isfinite(a));
  assert(std::isfinite(b));

  if (EqualToZero(a)) {
    if (EqualToZero(b))
      return SLE_INFINITE_ROOTS;
    return 0;
  }
  *x = -b / a;
  return 1;
}


int EqualToZero(const double x){
    return (fabs(x - 0) < EPSILON);
}
