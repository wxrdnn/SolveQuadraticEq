#include "io.h"
#include "myassert.h"
#include "solve.h"
#include <cstring>
#include <math.h>
#include <stdio.h>

Polynomial Get2DegreePolynomialFromKeyboard();

Polynomial Get2DegreePolynomialFromKeyboard()
{
    Polynomial pol = {0};
    pol.coefsAmount = 3;

    char inputLine[cMaxLine] = {};

    while (true)
    {
        printf(__GREEN "Enter a, b, c separated by \' \':\n" __RESET);
        fgets(inputLine, cMaxLine, stdin);
        if (ParsePolynomial(inputLine, ' ', &pol) == prSucces)
        {
            return pol;
        }
        printf(__RED "Error: Incorrect input.\n\n" __RESET);
    }
}

Polynomial Get2DegreePolynomialFromFile(FILE *fp)
{
    ASSERT(fp != NULL);

    Polynomial pol = {};
    pol.coefsAmount = 3;

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, fp);
    ParsePolynomial(inputLine, ';', &pol); // TODO check for error
    return pol;
}

Polynomial Get2DegreePolynomial(InputType inputType)
{
    switch (inputType)
    {
    default:
        return {};
    case (itKeyborad):
        return Get2DegreePolynomialFromKeyboard();

    case (itFile):
        char fileName[cMaxLine] = {0};

        GetFileName(fileName);
        FILE *fp = fopen(fileName, "r");
        Polynomial pol = Get2DegreePolynomialFromFile(fp);

        fclose(fp);
        return pol;
    }
}

InputType GetInputType()
{
    printf(__GREEN "Select input type:\n0: from keyboard\n1: from "
                   "file\n\n(default=0)\n" __RESET);

    int input = -1;

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, stdin);

    if (sscanf(inputLine, "%d", &input) != 1 ||
        (input != itKeyborad && input != itFile))
    {
        return itKeyborad;
    }

    return (InputType)input;
}

void GetFileName(char *fileName)
{
    printf(__GREEN "Enter file name:\n" __RESET);

    char inputLine[cMaxLine] = {};

    fgets(inputLine, cMaxLine, stdin);
    sscanf(inputLine, "%s", fileName); // Remove \n

    return;
}

ParseResult ParsePolynomial(const char *s, char separator, Polynomial *pp)
{
    ASSERT(pp != NULL);
    ASSERT(s != NULL);

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
        return prFail;
    }

    return prSucces;
}

bool AskForCycleSolve()
{
    printf(__GREEN "Solve all equations from file, or the first one "
                   "only:\n0: the first one\n1: all\n\n(default=0)\n" __RESET);

    int input = -1;

    char inputLine[cMaxLine] = {};
    fgets(inputLine, cMaxLine, stdin);

    if (sscanf(inputLine, "%d", &input) != 1 || (input != 1 && input != 0))
    {
        return 0;
    }

    return input;
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
    ASSERT(roots.rootsAmount >= 0 || roots.rootsAmount == cInfiniteRootsAmount)

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
        printf(
            __CYAN
            "There are infinite number of roots for this equation\n" __RESET);
    }
    return;
}

void DisplayPolynomial(Polynomial pol)
{
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

void DisplayCat()
{
    printf("%s", __YELLOW
           "  /\\___/\\\n ( o   o )\n (  =^=  )\n (        )\n (         )\n ( "
           "         ))))))))))))\n\n" __RESET);
}

void DisplaySadCat()
{
    printf("%s",
           "          .__....._             _.....__,\n            .\": o "
           ":':         ;': o :\".\n            `. `-' .'.       .'. `-' "
           ".'\n              `---'             `---'\n\n    _...----...   "
           "   ...   ...      ...----..._\n .-'__..-\"\"'----    `.  `\"`  "
           ".'    ----'\"\"-..__`-.\n'.-'   _.--\"\"\"'       `-._.-'      "
           " '\"\"\"--._   `-.`\n'  .-\"'                  :               "
           "   `\"-.  `\n  '   `.              _.'\"'._              .'   "
           "`\n        `.       ,.-\"'       \"'-.       .'\n          `.  "
           "                         .'\n            `-._                  "
           " _.-'\n                `\"'--...___...--'\"`\n```\n");
}

long CountLinesOfFile(FILE *fp)
{
    long currentPos = SEEK_CUR;
    fseek(fp, SEEK_SET, 0);

    char buffer[cMaxLine] = {};
    long count = 0;
    while (fgets(buffer, cMaxLine, fp) != NULL)
    {
        ++count;
    }

    fseek(fp, currentPos, 0);
    return count;
}
