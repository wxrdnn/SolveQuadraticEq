#include "h/solve.h"
#include "h/debug.h"
#include <math.h>

const double cEtzEpsilon = 1e-9;

bool EqualToZero(const double x);
Roots SolveTrueQuadraticEquation(const Polynomial pol);

Roots SolveQuadraticEquation(const Polynomial pol)
{
    double c = pol.coefs[0];
    double b = pol.coefs[1];
    double a = pol.coefs[2];

    ASSERT(std::isfinite(a));
    ASSERT(std::isfinite(b));
    ASSERT(std::isfinite(c));

    if (EqualToZero(a))
    {
        return SolveLinearEquation(pol);
    }
    else
    {
        return SolveTrueQuadraticEquation(pol);
    }
}

Roots SolveLinearEquation(Polynomial pol)
{ // ax + b = 0
    double b = pol.coefs[0];
    double a = pol.coefs[1];

    ASSERT(std::isfinite(a));
    ASSERT(std::isfinite(b));

    Roots roots = {0};

    if (EqualToZero(a))
    {
        if (EqualToZero(b))
        {
            roots.rootsAmount = cInfiniteRootsAmount;
            return roots;
        }
        roots.rootsAmount = 0;
        return roots;
    }
    double root = -b / a;
    roots.rootsAmount = 1;
    roots.roots[0] = EqualToZero(root) ? 0 : root;
    return roots;
}

Roots SolveTrueQuadraticEquation(Polynomial pol)
{
    double c = pol.coefs[0];
    double b = pol.coefs[1];
    double a = pol.coefs[2];

    ASSERT(std::isfinite(a));
    ASSERT(std::isfinite(b));
    ASSERT(std::isfinite(c));

    Roots roots = {0};

    double discriminant = Get2DegreeDiscriminant(pol);
    if (discriminant < 0)
    {
        roots.rootsAmount = 0;
        return roots;
    }
    else if (EqualToZero(discriminant))
    {
        double root = -b / 2.0 / a;

        roots.rootsAmount = 1;
        roots.roots[0] = EqualToZero(root) ? 0 : root;
        return roots;
    }

    double sqrtDiscriminant = sqrt(discriminant);
    double root1 = (-b + sqrtDiscriminant) / 2.0 / a;
    double root2 = (-b - sqrtDiscriminant) / 2.0 / a;

    roots.rootsAmount = 2;
    roots.roots[0] = EqualToZero(root1) ? 0 : root1;
    roots.roots[1] = EqualToZero(root2) ? 0 : root2;
    return roots;
}

bool EqualToZero(const double x)
{
    return fabs(x) < cEtzEpsilon;
}

double Get2DegreeDiscriminant(Polynomial pol)
{
    double c = pol.coefs[0];
    double b = pol.coefs[1];
    double a = pol.coefs[2];

    ASSERT(std::isfinite(a));
    ASSERT(std::isfinite(b));
    ASSERT(std::isfinite(c));

    return b * b - 4 * a * c;
}
