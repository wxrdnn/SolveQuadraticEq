#ifndef GRAPHING_H

#define GRAPHING_H

#include "errorHandle.h"
#include "solve.h"

struct Point
{
    double x;
    double y;
};

void InitGraph();

void KeepWindowOpen();

void DrawGraphAxis();

Error DrawFunction(const Polynomial *const pp);

void DrawLinear(const Polynomial *const pp);

void DrawParabola(const Polynomial *const pp);

double GetParabolaValY(const Polynomial *const pp, double x);

#endif
