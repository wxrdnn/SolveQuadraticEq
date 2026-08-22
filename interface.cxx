#include "h/interface.h"
#include "h/errorHandle.h"
#include "h/io.h"
#include "h/limits.h"
#include "h/solve.h"
#include <cstdio>
#include <cstring>

//! returned ExitCodes are
Error SolveSingle(const InputType inputType)
{
    Polynomial pol = {};
    Error error = Get2DegreePolynomial(inputType, &pol);
    if (error.exitCode != ecSucces)
    {
        return error;
    }
    DisplayPolynomial(pol);
    DisplayRoots(SolveQuadraticEquation(pol));
    return error;
}

Error SolveCycle()
{
    char fileName[cMaxLine] = {0};

    GetFileName(fileName);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return CreateError(ecCantOpenFile, fileName);
    }

    long fileLength = CountLinesOfFile(fp);

    if (FileIsEmpty(fp))
    {
        return CreateError(ecFileIsEmpty, fileName);
    }

    for (long i = fileLength; i > 0; --i)
    {
        Polynomial pol = {};
        Error error = GetNext2DegreePolynomialFromFile(fp, &pol, ';');
        if (error.exitCode != ecSucces)
        {
            return error;
        }
        printf("%s", "-------------------------\n");
        DisplayPolynomial(pol);
        DisplayRoots(SolveQuadraticEquation(pol));
    }

    printf("%s", "-------------------------\n");

    fclose(fp);
    return CreateError(ecSucces, "");
}
