#include "h/solve.h"
#include "h/debug.h"
#include "h/utils.h"
#include <math.h>

Roots SolveTrueQuadraticEquation(const Polynomial pol);

Roots SolveQuadraticEquation(const Polynomial pol)
{
    AssertPolynomialFinite(pol);

    if (EqualToZero(pol.coefs[2]))
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

    AssertPolynomialFinite(pol);

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
    AssertRootsFinite(roots);
    return roots;
}

Roots SolveTrueQuadraticEquation(Polynomial pol)
{
    double c = pol.coefs[0];
    double b = pol.coefs[1];
    double a = pol.coefs[2];

    AssertPolynomialFinite(pol);

    Roots roots = {0};

    double discriminant = Get2DegreeDiscriminant(pol);
    if (discriminant > 0)
    {
        double sqrtDiscriminant = sqrt(discriminant);
        double root1 = (-b + sqrtDiscriminant) / 2.0 / a;
        double root2 = (-b - sqrtDiscriminant) / 2.0 / a;

        if (root1 > root2)
        {
            Swap(&root1, &root2);
        }

        roots.rootsAmount = 2;
        roots.roots[0] = EqualToZero(root1) ? 0 : root1;
        roots.roots[1] = EqualToZero(root2) ? 0 : root2;
    }
    else if (EqualToZero(discriminant))
    {
        double root = -b / 2.0 / a;

        roots.rootsAmount = 1;
        roots.roots[0] = EqualToZero(root) ? 0 : root;
    }
    else
    {
        roots.rootsAmount = 0;
    }

    AssertRootsFinite(roots);
    return roots;
}

double Get2DegreeDiscriminant(const Polynomial pol)
{
    double c = pol.coefs[0];
    double b = pol.coefs[1];
    double a = pol.coefs[2];

    AssertPolynomialFinite(pol);

    return b * b - 4 * a * c;
}
