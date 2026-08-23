#include "h/test.h"
#include "h/colors.h"
#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/io.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/utils.h"
#include <stdlib.h>

void TestRandom(int testAmount);

bool EqualRoots(const Roots r1, const Roots r2);

int main()
{
    DisplayGreeting();
    DisplayCat();

    char fileName[cMaxLine] = {};
    AskForFileName(fileName);
    FILE *fp = fopen(fileName, "r");
    Polynomial pol = {};

    Error error = GetNext2DegreePolynomialFromFile(fp, &pol, ';');
    // RunSingleTest(&pol, Roots *const rp, const Roots *const refrp)
}

bool RunSingleTest(const Polynomial *const pp, Roots *const rp,
                   const Roots *const refrp)
{
    *rp = SolveQuadraticEquation(*pp);
    if (EqualRoots(*rp, *refrp))
    {
        printf(__GREEN "TEST PASSED\n" __RESET);
        return true;
    }
    else
    {
        printf(__RED "TEST FAILED!\n" __RESET);
        DisplayPolynomial(*pp);
        printf(__GREEN "EXPECTED:\n" __RESET);
        DisplayRoots(*refrp);
        printf(__RED "GOT:\n" __RESET);
        DisplayRoots(*rp);
        return false;
    }
}

bool EqualRoots(const Roots r1, const Roots r2)
{
    if (r1.rootsAmount != r2.rootsAmount)
    {
        return false;
    }
    for (int i = 0; i < r1.rootsAmount; ++i)
    {
        if (Equal(r1.roots[i], r2.roots[i]))
        {
            return false;
        }
    }
    return true;
}
