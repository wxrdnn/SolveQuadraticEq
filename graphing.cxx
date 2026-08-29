#include "h/graphing.h"
#include "TXLin.h"
#include "h/limits.h"
#include "h/utils.h"
#include <stdio.h>

const unsigned cXWindowSize = 1600;
const unsigned cYWindowSize = 1600;
const unsigned cXDivisionsNumber = 10;
const unsigned cYDivisionsNumber = 10;
const unsigned cDivisionMarkLength = 20;
const unsigned cFontSize = 40;

const double cScale = 100;

void DrawXAxisDivisions();
void DrawYAxisDivisions();

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
    txLine(0, (int)(cYWindowSize / 2), cXWindowSize, (int)(cXWindowSize / 2));
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
        double yDivValue = (y - (double)cYWindowSize / 2) * cScale;

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
