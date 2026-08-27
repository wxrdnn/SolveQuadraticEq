#include "h/io.h"
#include "h/colors.h"
#include "h/debug.h"
#include "h/errorHandle.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/utils.h"
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <string.h>

void Get2DegreePolynomialFromKeyboard(Polynomial *const pp);

void Get2DegreePolynomialFromKeyboard(
    Polynomial *const pp) // FIX error handling
{
    ASSERT(pp != NULL);

    *pp = {0};
    pp->coefsAmount = c2DegreeCoefsAmount;

    char inputLine[cMaxLine] = {};

    // ClearBuffer();
    // ASSERT(0);
    while (true)
    {
        printf(__GREEN "Enter a, b, c separated by \' \':\n" __RESET);
        fgets(inputLine, cMaxLine, stdin);
        // printf("[%s]", inputLine);
        if (inputLine[0] == '\n')
        {
            HandleError(CreateError(ecIncorrectInput, ""));
            continue;
        }
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

Error GetNext2DegreeRootsFromFile(FILE *const fp, Roots *const rp,
                                  const char separator)
{
    ASSERT(fp != NULL);
    ASSERT(rp != NULL);

    *rp = {};

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, fp);
    // printf("input line of roots: %s", inputLine);
    return Parse2DegreeRoots(inputLine, separator, rp);
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
        return CreateError(TranslateErrnoCode(errno), fileName);
    }

    Error error = GetNext2DegreePolynomialFromFile(fp, pp, ';');
    fclose(fp);
    return error;
}

InputType AskForInputType()
{
    printf(__GREEN "Select input type:\n0: from keyboard\n1: from "
                   "file\n\n(default=0)\n" __RESET);

    // char inputLine[cMaxLine] = {};
    // fgets(inputLine, cMaxLine, stdin);

    // printf("%d", input);
    // ASSERT(0);

    int input = GetNum();

    switch (input)
    {
    case 0:
    default:
        return itKeyborad;

    case 1:
        return itFile;
    }
}

void AskForFileName(char *const fileName)
{
    ASSERT(fileName != NULL);

    printf(__GREEN "Enter file name:\n" __RESET);

    // fgets(inputLine, cMaxLine, stdin);
    // sscanf(inputLine, "%s", fileName); // Remove \n
    scanf("%s", fileName); // Remove \n
    ClearBuffer();

    return;
}

Error ParsePolynomial(const char *const s, const char separator,
                      Polynomial *const pp)
{
    ASSERT(s != NULL);
    ASSERT(pp != NULL);

    double arr[cMaxCoefsAmount] = {};

    Error error = ParseNDoubles(s, pp->coefsAmount, arr, separator);
    if (error.exitCode != ecSuccess)
    {
        return error;
    }

    unsigned index = 0;
    while (index < pp->coefsAmount)
    {
        ASSERT(pp->coefsAmount > index)
        unsigned coefIndex = pp->coefsAmount - 1 - index;
        ASSERT(index < cMaxCoefsAmount)

        pp->coefs[coefIndex] = arr[index];
        index++;
    }

    return error;
}

Error Parse2DegreeRoots(const char *const s, const char separator,
                        Roots *const rp) // FIXME
{
    ASSERT(s != NULL);
    ASSERT(rp != NULL);

    *rp = {};
    int nRoots = 0;

    if (sscanf(s, "%d", &nRoots) != 1)
    {
        return CreateError(ecParsingFailed, s);
    }

    double arr[cMaxRootsAmount];
    Error error =
        ParseNDoubles(s, (unsigned)(nRoots > 0 ? nRoots : 0), arr, separator);
    if (error.exitCode != ecSuccess)
    {
        return error;
    }

    rp->rootsAmount = nRoots;
    rp->roots[0] = arr[1]; // because arr[0] is roots number
    rp->roots[1] = arr[2];
    ASSERT_ROOTS_FINITE(*rp);
    return error;
}

Error ParseNDoubles(const char *const s, const unsigned n, double *const arr,
                    const char separator)
{
    const char *pl = s;
    char *pr = NULL;
    double buf = 0;
    unsigned index = 0;

    while (index < n)
    {
        buf = strtod(pl, &pr);

        if (!std::isfinite(buf) || std::isnan(buf))
        {
            return CreateError(ecParsingFailed, s);
        }

        // fprintf(stderr, "index: %d, buf: %lg, pl: %s, *pr: \'%c\'\n", index,
        //         buf, pl, *pr);

        if (*pr == separator)
        {
            arr[index] = buf;
            ++index;
            pl = pr + 1;
        }
        else if (*pr == '\0' || *pr == '\n')
        {
            arr[index] = buf;
            break;
        }
        else
        {
            return CreateError(ecParsingFailed, s);
        }
    }

    return CreateError(ecSuccess, "");
}

bool AskForCycleSolve()
{
    printf(__GREEN "Solve all equations from file, or the first one "
                   "only:\n0: the first one\n1: all\n\n(default=0)\n" __RESET);

    // char inputLine[cMaxLine] = {};
    // fgets(inputLine, cMaxLine, stdin);
    // ClearBuffer();
    // ASSERT(0);
    // printf("%d\n", getchar());

    return GetNum();
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
    ASSERT_ROOTS_FINITE(roots);

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
    ASSERT_POLYNOMIAL_CORRECT(pol);
    printf(__MAGENTA "Solving ");

    for (unsigned i = pol.coefsAmount; i > 0; --i)
    {
        if (i > 2)
        {
            printf(pol.coefs[i - 1] > 0 || EqualToZero(pol.coefs[i - 1]) ? ""
                                                                         : "-");
            printf("%lg*x%u", fabs(pol.coefs[i - 1]), i - 1);
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

int GetNum()
{
    int c = 0;
    if ((c = getc(stdin)) == '\n')
    {
        // printf("got \\n\n");
        return 0;
    }
    ungetc(c, stdin);
    int input = 0; // default value
    scanf("%d", &input);
    ClearBuffer();
    return input;
}
