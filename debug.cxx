#include "h/debug.h"
#include "h/solve.h"
#include <math.h>

// void ASSERT_DOUBLE_CORRECT(const double x)
// {
//     ASSERT(isfinite(x));
// }

void AssertPolynomialCorrect(const Polynomial pol)
{
    for (unsigned i = 0; i < pol.coefsAmount; ++i)
    {
        ASSERT_DOUBLE_CORRECT(pol.coefs[i]);
    }
    return;
}

void AssertRootsFinite(const Roots roots)
{
    for (int i = 0; i < roots.rootsAmount; ++i)
    {
        ASSERT_DOUBLE_CORRECT(roots.roots[i]);
    }
    return;
}
