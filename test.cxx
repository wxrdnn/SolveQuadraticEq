#include "h/test.h"
#include "h/colors.h"
#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/io.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/utils.h"
#include <cstdio>
#include <stdlib.h>

void TestRandom(int testAmount);

int main()
{
    DisplayGreeting();
    DisplayCat();

    return HandleError(RunTests()).exitCode;
}

bool RunSingleTest(const Polynomial pol, const Roots refRoots)
{
    Roots roots = SolveQuadraticEquation(pol);
    if (EqualRoots(roots, refRoots))
    {
        printf(__GREEN "TEST PASSED\n" __RESET);
        return true;
    }
    else
    {
        printf(__RED "TEST FAILED!\n" __RESET);
        DisplayPolynomial(pol);
        printf(__GREEN "EXPECTED:\n" __RESET);
        DisplayRoots(refRoots);
        printf(__RED "GOT:\n" __RESET);
        DisplayRoots(roots);
        return false;
    }
}

Error RunTests()
{
    char polynomialsFileName[cMaxLine] = {};
    char refRootsFileName[cMaxLine] = {};

    AskForFileName(polynomialsFileName);
    AskForFileName(refRootsFileName);

    FILE *fppols = fopen(polynomialsFileName, "r");
    if (fppols == NULL)
    {
        return CreateError(ecCantOpenFile, polynomialsFileName);
    }
    FILE *fprefroots = fopen(refRootsFileName, "r");
    if (fprefroots == NULL)
    {
        return CreateError(ecCantOpenFile, refRootsFileName);
    }
    Polynomial pol = {};
    Roots refRoots = {};
    Error error = CreateError(ecSuccess, "");
    long polynomialsFileLength = CountLinesOfFile(fppols);
    long refRootsFileLength = CountLinesOfFile(fprefroots);
    if (polynomialsFileLength != refRootsFileLength)
    {
        return CreateError(ecTestFilesDiffer, "");
    }

    for (long i = 0; i < polynomialsFileLength; ++i)
    {
        error = GetNext2DegreePolynomialFromFile(fppols, &pol, ';');
        if (error.exitCode != ecSuccess)
        {
            // printf("failed to parse pol");
            return error;
        }
        error = GetNext2DegreeRootsFromFile(fprefroots, &refRoots, ';');
        if (error.exitCode != ecSuccess)
        {
            // printf("failed to parse refroots");
            return error;
        }
        RunSingleTest(pol, refRoots);
    }
    return error;
}
