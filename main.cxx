#include "io.h"
#include "solve.h"
#include <cstdio>

void SolveSingle(InputType inputType);
void SolveCycle();

int main()
{
    // TODO Input from file

    DisplayGreeting();
    DisplayCat();

    InputType inputType = GetInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    cycleSolve ? SolveCycle() : SolveSingle(inputType);

    return 0;
}

void SolveSingle(InputType inputType)
{
    Polynomial pol = Get2DegreePolynomial(inputType);
    DisplayPolynomial(pol);
    DisplayRoots(SolveQuadraticEquation(pol));
}

void SolveCycle()
{
    char fileName[cMaxLine] = {0};

    GetFileName(fileName);
    FILE *fp = fopen(fileName, "r");
    for (long i = CountLinesOfFile(fp); i > 0; --i)
    {
        printf("%s", "-------------------------\n");
        Polynomial pol = Get2DegreePolynomialFromFile(fp);
        DisplayPolynomial(pol);
        DisplayRoots(SolveQuadraticEquation(pol));
    }

    printf("%s", "-------------------------\n");

    fclose(fp);
    return;
}
