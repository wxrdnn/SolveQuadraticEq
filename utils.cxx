#include "h/utils.h"
#include "h/debug.h"
#include "h/limits.h"
#include "string.h"
#include <cmath>
#include <math.h>
#include <stdio.h>

void Swap(double *const a, double *const b)
{
    ASSERT(a != NULL);
    ASSERT(b != NULL);
    double t = *a;
    *a = *b;
    *b = t;
    return;
}

bool EqualToZero(const double x)
{
    AssertDoubleCorrect(x);
    return Equal(x, 0);
}

bool Equal(const double x, const double y)
{
    AssertDoubleCorrect(x);
    AssertDoubleCorrect(y);
    return fabs(x - y) < cCompareEpsilon;
}

long CountLinesOfFile(FILE *const fp)
{
    ASSERT(fp != NULL);
    long currentPos = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char buffer[cMaxLine] = {};
    long count = 0;
    while (fgets(buffer, cMaxLine, fp) != NULL)
    {
        ++count;
    }

    fseek(fp, currentPos, SEEK_SET);
    return count;
}

void ReplaceNewLineCharWithNullTerminator(char *const s)
{
    ASSERT(s != NULL);
    char *p = strchr(s, '\n');
    if (p)
    {
        *p = '\0';
    }
    return;
}

void ClearBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return;
}
