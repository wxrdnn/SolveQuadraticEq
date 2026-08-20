#include "solve.h"
#include "assert.h"
#include <math.h>

const double cEtzEpsilon = 1e-9;

bool EqualToZero(const double x);
RootsAmount SolveTrueQuadraticEquation(const double a, const double b,
                                       const double c, double *x1, double *x2);

RootsAmount SolveQuadraticEquation(const double a, const double b,
                                   const double c, double *x1, double *x2)
{
  assert(std::isfinite(a));
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (EqualToZero(a))
  {
    return SolveLinearEquation(b, c, x1);
  }
  else
  {
    return SolveTrueQuadraticEquation(a, b, c, x1, x2);
  }
}

RootsAmount SolveLinearEquation(const double a, const double b, double *x)
{ // ax + b = 0
  assert(x != NULL);
  assert(std::isfinite(a));
  assert(std::isfinite(b));

  if (EqualToZero(a))
  {
    if (EqualToZero(b))
    {
      return krInfinite;
    }
    return krZero;
  }
  double root = -b / a;
  *x = EqualToZero(root) ? 0 : root;
  return krOne;
}

RootsAmount SolveTrueQuadraticEquation(const double a, const double b,
                                       const double c, double *x1, double *x2)
{
  assert(std::isfinite(a));
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  double discriminant = GetDiscriminant(a, b, c);
  if (discriminant < 0)
  {
    return krZero;
  }
  else if (EqualToZero(discriminant))
  {
    double root = -b / 2.0 / a;
    *x1 = EqualToZero(root) ? 0 : root;
    return krOne;
  }
  double sqrtDiscriminant = sqrt(discriminant);
  double root1 = (-b + sqrtDiscriminant) / 2.0 / a;
  double root2 = (-b - sqrtDiscriminant) / 2.0 / a;
  *x1 = EqualToZero(root1) ? 0 : root1;
  *x2 = EqualToZero(root2) ? 0 : root2;
  return krTwo;
}

bool EqualToZero(const double x)
{
  return fabs(x) < cEtzEpsilon;
}

double GetDiscriminant(const double a, const double b, const double c)
{
  assert(std::isfinite(a));
  assert(std::isfinite(b));
  assert(std::isfinite(c));

  return b * b - 4 * a * c;
}
