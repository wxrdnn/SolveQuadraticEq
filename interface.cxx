#include "h/interface.h"
#include "h/debug.h"
#include "h/errorHandle.h"
#include "h/graphing.h"
#include "h/io.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/test.h"
#include "h/utils.h"
#include <SDL2/SDL.h>
#include <TXLin.h>
#include <errno.h>
#include <string.h>

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
        return CreateError(TranslateErrnoCode(errno), fileName);
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

Error ProcessArgs(const unsigned argc, const char *const argv[],
                  LaunchOptions *const lp)
{
    lp->mode = mSolveSquare; // default value

    if (argc > 1)
    {
        for (unsigned index = 1; index < argc; index++)
        {
            ASSERT(index > 0 && index < argc);
            const char *arg = argv[index];

            if (arg[0] != '-')
            {
                return CreateError(ecWrongUsage, "");
            }

            if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
            {
                lp->displayHelp = true;
                lp->mode = mSolveSquare;
            }
            else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--solve") == 0)
            {
                lp->mode = mSolveSquare;
            }
            else if (strcmp(arg, "-t") == 0 || strcmp(arg, "--test") == 0)
            {
                lp->mode = mTestSquare;
            }
            else if (strcmp(arg, "-g") == 0 || strcmp(arg, "--graphing") == 0)
            {
                lp->mode = mGraphing;
            }
            else
            {
                return CreateError(ecWrongUsage, "");
            }
        }
    }
    return CreateError(ecSuccess, "");
}

Error LaunchProgram(const LaunchOptions *const lp)
{
    if (lp->displayHelp)
    {
        DisplayHelp();
        return CreateError(ecSuccess, "");
    }

    switch (lp->mode)
    {
    default:
    case mSolveSquare:
        return LaunchSolveSquareMode();

    case mTestSquare:
        return LaunchTestMode();

    case mGraphing:
        return LaunchGraphingMode();
    }

    // return CreateError(ecSuccess, "");
}

Error LaunchSolveSquareMode()
{
    Error error = {};

    InputType inputType = AskForInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    if (cycleSolve)
    {
        error = SolveCycle();
    }
    else
    {
        error = SolveSingle(inputType);
    }

    return error;
}

Error LaunchTestMode()
{
    char polynomialsFileName[cMaxLine] = {};
    char refRootsFileName[cMaxLine] = {};

    printf(__GREEN "Select coefficients file\n" __RESET);
    AskForFileName(polynomialsFileName);
    printf(__GREEN "Select ref roots file\n" __RESET);
    AskForFileName(refRootsFileName);

    FILE *fppols = fopen(polynomialsFileName, "r");
    if (fppols == NULL)
    {
        return CreateError(TranslateErrnoCode(errno), polynomialsFileName);
    }
    FILE *fprefroots = fopen(refRootsFileName, "r");
    if (fprefroots == NULL)
    {
        return CreateError(TranslateErrnoCode(errno), refRootsFileName);
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

Error LaunchGraphingMode()
{
    InitGraph();

    KeepWindowOpen();
    return CreateError(ecSuccess, "");
}
