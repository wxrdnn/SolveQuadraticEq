#include "h/graphing.h"
#include "TXLin.h"
#include "h/debug.h"
#include "h/errorHandle.h"
#include "h/limits.h"
#include "h/solve.h"
#include "h/utils.h"
#include <cmath>
#include <stdio.h>
#include <sys/types.h>

const unsigned cXWindowSize = 1600;
const unsigned cYWindowSize = 1600;
const unsigned cXDivisionsNumber = 10;
const unsigned cYDivisionsNumber = 10;
const unsigned cDivisionMarkLength = 20;
const unsigned cFontSize = 40;
const unsigned cWindowBorderOffset = 5;

const double cScale = 0.00625; // FIXME

void DrawXAxisDivisions();
void DrawYAxisDivisions();
double ValueToScreenPosX(const double x);
double ValueToScreenPosY(const double y);
double ScreenPosToValueX(const double x);
double ScreenPosToValueY(const double y);
double GetLinearScreenY(const Polynomial *const pp, const double screenX);
double GetParabolaScreenY(const Polynomial *const pp, const double screenX);

void InitGraph()
{
    txCreateWindow(cXWindowSize, cYWindowSize);
    DrawGraphAxis();

    return;
}

void KeepWindowOpen()
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
    }
    return;
}

void DrawGraphAxis()
{
    txLine(0, (int)(cYWindowSize / 2), cXWindowSize, (int)(cYWindowSize / 2));
    txLine((int)(cXWindowSize / 2), 0, (int)(cXWindowSize / 2), cYWindowSize);
    DrawXAxisDivisions();
    DrawYAxisDivisions();
}

void DrawXAxisDivisions()
{
    txSelectFont("", cFontSize);
    double delta = (double)cXWindowSize / cXDivisionsNumber;

    for (double x = delta; x < cXWindowSize; x += delta)
    {
        double y1 = ((double)cYWindowSize + cDivisionMarkLength) / 2;
        double y2 = ((double)cYWindowSize - cDivisionMarkLength) / 2;
        txLine(x, y1, x, y2);

        char num[cMaxLine] = {};
        double xDivValue = (x - (double)cXWindowSize / 2) * cScale;
        snprintf(num, cMaxLine, "%lg", xDivValue);

        double xDivPos = x - (double)txGetTextExtentX(num) / 4; // why dividing by 4?
        double yDivPos = ((double)cYWindowSize - cDivisionMarkLength + cFontSize) / 2;

        if (EqualToZero(xDivValue))
        {
            xDivPos -= delta / 12;
        }

        txTextOut(xDivPos, yDivPos, num);
    }

    return;
}

void DrawYAxisDivisions()
{
    txSelectFont("", cFontSize);
    double delta = (double)cYWindowSize / cYDivisionsNumber;

    for (double y = delta; y < cYWindowSize; y += delta)
    {
        double x1 = ((double)cXWindowSize + cDivisionMarkLength) / 2;
        double x2 = ((double)cXWindowSize - cDivisionMarkLength) / 2;
        txLine(x1, y, x2, y);

        char num[cMaxLine] = {};
        double yDivValue = -(y - (double)cYWindowSize / 2) * cScale;

        if (!EqualToZero(yDivValue))
        {
            snprintf(num, cMaxLine, "%lg", yDivValue);

            double xDivPos = ((double)cXWindowSize - cDivisionMarkLength) / 2 - (double)txGetTextExtentX(num) / 1.5;
            double yDivPos = y - (double)cFontSize / 12;
            txTextOut(xDivPos, yDivPos, num);
        }
    }

    return;
}

Error DrawFunction(const Polynomial *const pp)
{
    ASSERT(pp);
    ASSERT_POLYNOMIAL_CORRECT(*pp);

    switch (pp->coefsAmount)
    {
    case 1:
    case 2:
        DrawLinear(pp);
        break;

    case 3:
        DrawParabola(pp);
        break;

    default:
        return CreateError(ecUnsupportedPolynomial, "");
        break;
    }

    return CreateError(ecSuccess, "`");
}

void DrawLinear(const Polynomial *const pp)
{
    ASSERT(pp);
    ASSERT_POLYNOMIAL_CORRECT(*pp);
    ASSERT(pp->coefsAmount < 3);

    double a = pp->coefs[1];
    double b = pp->coefs[0]; // y = ax + b

    double screenX1 = 0;
    double screenY1 = GetLinearScreenY(pp, screenX1);

    double screenX2 = cXWindowSize;
    double screenY2 = GetLinearScreenY(pp, screenX2);

    txLine(screenX1, screenY1, screenX2, screenY2);
    return;
}

void DrawParabola(const Polynomial *const pp)
{
    ASSERT(pp);
    ASSERT_POLYNOMIAL_CORRECT(*pp);
    ASSERT(pp->coefsAmount == 3);

    double a = pp->coefs[2];
    double b = pp->coefs[1];
    double c = pp->coefs[0];

    if (EqualToZero(a))
    {
        DrawLinear(pp);
        return;
    }

    double prevScreenX = 0;
    double prevScreenY = GetParabolaScreenY(pp, prevScreenX);

    for (double screenX = 1; screenX < cXWindowSize; ++screenX)
    {
        double screenY = GetParabolaScreenY(pp, screenX);
        // printf("screenX: %lg, valY: %lg, screenY: %lg\n", screenX, valY, screenY);

        if (screenY < cWindowBorderOffset || screenY > cYWindowSize - cWindowBorderOffset ||
            screenX < cWindowBorderOffset || screenX > cXWindowSize - cWindowBorderOffset)
        {
            prevScreenX = screenX;
            prevScreenY = screenY;
            continue;
        }

        txLine(screenX, screenY, prevScreenX, prevScreenY);

        prevScreenX = screenX;
        prevScreenY = screenY;
    }
}

double GetParabolaValY(const Polynomial *const pp, double valX)
{
    ASSERT_POLYNOMIAL_CORRECT(*pp);

    double a = pp->coefs[2];
    double b = pp->coefs[1];
    double c = pp->coefs[0];

    return a * valX * valX + b * valX + c;
}

double ValueToScreenPosX(const double x)
{
    return x / cScale + (double)cXWindowSize / 2;
}

double ValueToScreenPosY(const double y)
{
    return -y / cScale + (double)cXWindowSize / 2;
}

double ScreenPosToValueX(const double x)
{
    return x * cScale - cXWindowSize * cScale / 2;
}

double ScreenPosToValueY(const double y)
{
    return -y * cScale + cYWindowSize * cScale / 2;
}

double GetLinearScreenY(const Polynomial *const pp, const double screenX)
{
    ASSERT(pp);
    ASSERT_POLYNOMIAL_CORRECT(*pp);
    ASSERT(pp->coefsAmount >= 2);

    double a = pp->coefs[1];
    double b = pp->coefs[0];

    double valX = ScreenPosToValueX(screenX);
    double valY = a * valX + b;
    return ValueToScreenPosY(valY);
}

double GetParabolaScreenY(const Polynomial *const pp, const double screenX)
{
    ASSERT(pp);
    ASSERT_POLYNOMIAL_CORRECT(*pp);
    ASSERT(pp->coefsAmount >= 3);

    double valY = GetParabolaValY(pp, ScreenPosToValueX(screenX));
    return ValueToScreenPosY(valY);
}
