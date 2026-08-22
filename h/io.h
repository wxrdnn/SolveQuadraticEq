#ifndef IO_H

#define IO_H

#include "ercodes.h"
#include "solve.h"
#include <stdio.h>

const int cMaxLine = 1024;

enum InputType
{
    itKeyborad = 0,
    itFile = 1,
};

Polynomial Get2DegreePolynomial(const InputType inputType);

InputType GetInputType();

ExitCode Get2DegreePolynomialFromFile(FILE *const fp, Polynomial *const pp,
                                      const char separator);

void GetFileName(char *const fileName);

ExitCode ParsePolynomial(const char *const s, const char separator,
                         Polynomial *pp);

bool AskForCycleSolve();

void DisplayGreeting();

void DisplayRoots(const Roots roots);

void DisplayPolynomial(const Polynomial pol);

long CountLinesOfFile(FILE *const fp);

#endif
