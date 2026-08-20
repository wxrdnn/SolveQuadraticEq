#include "solve.h"
#include "myassert.h"
#include <math.h>

const double cEtzEpsilon = 1e-9;

bool EqualToZero(const double x);
RootsAmount SolveTrueQuadraticEquation(const double a, const double b,
                                       const double c, double *x1, double *x2);

RootsAmount SolveQuadraticEquation(const double a, const double b,
                                   const double c, double *x1, double *x2)
{
  ASSERT(std::isfinite(a));
  ASSERT(std::isfinite(b));
  ASSERT(std::isfinite(c));

  ASSERT(x1 != NULL);
  ASSERT(x2 != NULL);
  ASSERT(x1 != x2);

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
  ASSERT(x != NULL);
  ASSERT(std::isfinite(a));
  ASSERT(std::isfinite(b));

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
  ASSERT(std::isfinite(a));
  ASSERT(std::isfinite(b));
  ASSERT(std::isfinite(c));

  ASSERT(x1 != NULL);
  ASSERT(x2 != NULL);
  ASSERT(x1 != x2);

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
  ASSERT(std::isfinite(a));
  ASSERT(std::isfinite(b));
  ASSERT(std::isfinite(c));

  return b * b - 4 * a * c;
}
