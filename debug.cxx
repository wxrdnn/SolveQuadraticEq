#include "h/debug.h"
#include "h/solve.h"
#include <math.h>

void AssertDoubleCorrect(const double x)
{
    ASSERT(std::isfinite(x));
    ASSERT(!std::isnan(x));
}

void AssertPolynomialFinite(const Polynomial pol)
{
    for (int i = 0; i < pol.coefsAmount; ++i)
    {
        AssertDoubleCorrect(pol.coefs[i]);
    }
    return;
}

void AssertRootsFinite(const Roots roots)
{
    for (int i = 0; i < roots.rootsAmount; ++i)
    {
        AssertDoubleCorrect(roots.roots[i]);
    }
    return;
}
