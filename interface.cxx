#include "h/interface.h"
#include "h/debug.h"
#include "h/errorHandle.h"
#include "h/io.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/utils.h"

//! returned ExitCodes are
Error SolveSingle(const InputType inputType)
{
    Polynomial pol = {};
    Error error = Get2DegreePolynomial(inputType, &pol);
    // ASSERT(0);
    if (error.exitCode != ecSuccess)
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

    AskForFileName(fileName);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return CreateError(ecCantOpenFile, fileName);
    }

    long fileLength = CountLinesOfFile(fp);

    if (FileIsEmpty(fp))
    {
        fclose(fp);
        return CreateError(ecFileIsEmpty, fileName);
    }

    for (long i = fileLength; i > 0; --i)
    {
        Polynomial pol = {};
        Error error = GetNext2DegreePolynomialFromFile(fp, &pol, ';');
        if (error.exitCode != ecSuccess)
        {
            fclose(fp);
            return error;
        }
        printf("%s", "-------------------------\n");
        DisplayPolynomial(pol);
        DisplayRoots(SolveQuadraticEquation(pol));
    }

    printf("%s", "-------------------------\n");

    fclose(fp);
    return CreateError(ecSuccess, "");
}
