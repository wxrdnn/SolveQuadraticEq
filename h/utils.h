#ifndef UTILS_H

#define UTILS_H

#include <stdio.h>

const double cCompareEpsilon = 1e-4;

bool Equal(const double x, const double y);

bool EqualToZero(const double x);

void Swap(double *const a, double *const b);

long CountLinesOfFile(FILE *const fp);

void ReplaceNewLineCharWithNullTerminator(char *const s);

void ClearBuffer();

#endif
