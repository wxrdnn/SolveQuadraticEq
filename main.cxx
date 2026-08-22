#include "h/cats.h"
#include "h/colors.h"
#include "h/ercodes.h"
#include "h/interface.h"
#include "h/io.h"
#include "h/solve.h"
#include <stdlib.h>

int main()
{
    // TODO enum with error codes
    // TODO Errno
    // TODO move main.cxx funcs to interface.cxx
    // TODO point on first failed test
    // TODO File output
    // TODO check double for finite and NaN
    // TODO test solving square eq with nan and inf coefs

    DisplayGreeting();
    DisplayCat();

    InputType inputType = GetInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    // cycleSolve ? SolveCycle() : SolveSingle(inputType);

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
    if (fp == NULL)
    {
        printf(__RED "Error: Can\'t open file \"%s\".\n" __RESET, fileName);
        exit(ecCantOpenFile);
    }

    long fileLength = CountLinesOfFile(fp);

    if (fileLength <= 1)
    {
        printf(__RED "Error: File is \"%s\" empty.\n" __RESET, fileName);
        exit(EXIT_FAILURE);
    }

    for (long i = fileLength; i > 0; --i)
    {
        Polynomial pol = {};
        if (Get2DegreePolynomialFromFile(fp, &pol, ';') == ecParsingFailed)
        {
            printf(__RED "Error: incorrect file input.\n" __RESET);
            exit(EXIT_FAILURE);
        }
        printf("%s", "-------------------------\n");
        DisplayPolynomial(pol);
        DisplayRoots(SolveQuadraticEquation(pol));
    }

    printf("%s", "-------------------------\n");

    fclose(fp);
    return;
}
