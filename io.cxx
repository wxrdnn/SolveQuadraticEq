#include "h/io.h"
#include "h/colors.h"
#include "h/debug.h"
#include "h/errorHandle.h"
#include "h/limits.h"
#include "h/solve.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void Get2DegreePolynomialFromKeyboard(Polynomial *const pp);

void Get2DegreePolynomialFromKeyboard(Polynomial *const pp)
{
    ASSERT(pp != NULL);

    *pp = {0};
    pp->coefsAmount = c2DegreeCoefsAmount;

    char inputLine[cMaxLine] = {};

    while (true)
    {
        printf(__GREEN "Enter a, b, c separated by \' \':\n" __RESET);
        fgets(inputLine, cMaxLine, stdin);
        Error error = ParsePolynomial(inputLine, ' ', pp);
        if (error.exitCode == ecSuccess)
        {
            return;
        }
        HandleError(error);
    }
}
//! returned ExitCodes: ecSucces, ecParsingFailed
Error GetNext2DegreePolynomialFromFile(FILE *const fp, Polynomial *const pp,
                                       const char separator)
{
    ASSERT(fp != NULL);
    ASSERT(pp != NULL);

    *pp = {};
    pp->coefsAmount = c2DegreeCoefsAmount;

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, fp);
    return ParsePolynomial(inputLine, separator, pp);
}

//! returned ExitCodes: ecSucces, ecCantOpenFile, ecIncorrectInput
Error Get2DegreePolynomial(const InputType inputType, Polynomial *const pp)
{
    ASSERT(pp != NULL);

    switch (inputType)
    {
    case (itKeyborad):
        Get2DegreePolynomialFromKeyboard(pp);
        return CreateError(ecSuccess, "");

    case (itFile):
        return GetFirst2DegreePolynomialFromFile(pp);

    default:
        return CreateError(ecUnexpectedFailure, "");
    }
}

//! returned ExitCodes: ecSucces, ecCantOpenFile, ecIncorrectInput
Error GetFirst2DegreePolynomialFromFile(Polynomial *const pp)
{
    ASSERT(pp != NULL);

    char fileName[cMaxLine] = {0};

    AskForFileName(fileName);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return CreateError(ecCantOpenFile, fileName);
    }

    Error error = GetNext2DegreePolynomialFromFile(fp, pp, ';');
    fclose(fp);
    return error;
}

InputType AskForInputType()
{
    printf(__GREEN "Select input type:\n0: from keyboard\n1: from "
                   "file\n\n(default=0)\n" __RESET);

    int input = itKeyborad;

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, stdin);

    if (sscanf(inputLine, "%d", &input) != 1 ||
        (input != itKeyborad && input != itFile))
    {
        return itKeyborad;
    }

    return (InputType)input;
}

void AskForFileName(char *const fileName)
{
    ASSERT(fileName != NULL);

    printf(__GREEN "Enter file name:\n" __RESET);

    char inputLine[cMaxLine] = {};

    fgets(inputLine, cMaxLine, stdin);
    sscanf(inputLine, "%s", fileName); // Remove \n

    return;
}

Error ParsePolynomial(const char *const s, const char separator,
                      Polynomial *const pp)
{
    ASSERT(s != NULL);
    ASSERT(pp != NULL);

    int coefsAmount = pp->coefsAmount;
    char format[cMaxLine] = {0};

    for (int i = coefsAmount; i > 0; --i)
    {
        char prevFormat[cMaxLine - sizeof("%s%%lg%c")] = {};
        strcpy(prevFormat, format);
        sprintf(format, "%s%%lg%c", prevFormat, separator);
    }

    if (sscanf(s, format, pp->coefs + 2, pp->coefs + 1, pp->coefs) != 3)
    {
        char context[cMaxLine] = {};
        strcpy(context, s);
        ReplaceNewLineCharWithNullTerminator(context);
        return CreateError(ecParsingFailed, context);
    }

    return CreateError(ecSuccess, "");
}

bool AskForCycleSolve()
{
    printf(__GREEN "Solve all equations from file, or the first one "
                   "only:\n0: the first one\n1: all\n\n(default=0)\n" __RESET);

    int input = 0; // default value

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, stdin);

    if (sscanf(inputLine, "%d", &input) != 1 || (input != 1 && input != 0))
    {
        return false;
    }

    return (bool)input;
}

void DisplayGreeting()
{
    printf("%s",
           __GREEN "# Solve quadratic equation\n# Made by Chumakov Alexey (c) "
                   "2026\n\n" __RESET);
    return;
}

void DisplayRoots(Roots roots)
{
    ASSERT(roots.rootsAmount >= 0 || roots.rootsAmount == cInfiniteRootsAmount);
    AssertRootsFinite(roots);

    if (roots.rootsAmount > 1)
    {
        printf(__GREEN "There are %d roots:\n", roots.rootsAmount);

        for (int i = 0; i < roots.rootsAmount; ++i)
        {
            printf("x%d: %lg\n", i + 1, roots.roots[i]);
        }

        printf(__RESET); // Reset text color
    }
    else if (roots.rootsAmount == 1)
    {
        printf(__YELLOW "There is 1 root:\nx: %lg\n" __RESET, roots.roots[0]);
    }
    else if (roots.rootsAmount == 0)
    {
        printf(__BLUE "There are no roots for this equation\n" __RESET);
    }
    else
    {
        printf(__CYAN "There are infinite number of roots for this "
                      "equation\n" __RESET);
    }
    return;
}

void DisplayPolynomial(Polynomial pol)
{
    AssertPolynomialFinite(pol);
    printf(__MAGENTA "Solving ");

    for (int i = pol.coefsAmount; i > 0; --i)
    {
        if (i > 2)
        {
            printf(pol.coefs[i - 1] > 0 ? "" : "-");
            printf("%lg*x%d", fabs(pol.coefs[i - 1]), i - 1);
            printf(pol.coefs[i - 2] > 0 ? " + " : " - ");
        }
        else if (i == 2)
        {
            printf("%lg*x", fabs(pol.coefs[i - 1]));
            printf(pol.coefs[i - 2] > 0 ? " + " : " - ");
        }
        else
        {
            printf("%lg", fabs(pol.coefs[i - 1]));
        }
    }

    printf(" = 0\n" __RESET);

    return;
}

//! works with opened files only
bool FileIsEmpty(FILE *fp)
{
    ASSERT(fp != NULL);

    int c = 0; // default value
    if ((c = getc(fp)) == EOF)
    {
        return true;
    }

    ungetc(c, fp);
    return false;
}
