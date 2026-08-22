#ifndef IO_H

#define IO_H

#include "errorHandle.h"
#include "solve.h"
#include <stdio.h>

enum InputType
{
    itKeyborad = 0,
    itFile = 1,
};

Error Get2DegreePolynomial(const InputType inputType, Polynomial *const pp);

Error GetFirst2DegreePolynomialFromFile(Polynomial *const pp);

Error GetNext2DegreePolynomialFromFile(FILE *const fp, Polynomial *const pp,
                                       const char separator);

InputType GetInputType();

void GetFileName(char *const fileName);

Error ParsePolynomial(const char *const s, const char separator,
                      Polynomial *pp);

bool AskForCycleSolve();

void DisplayGreeting();

void DisplayRoots(const Roots roots);

void DisplayPolynomial(const Polynomial pol);

long CountLinesOfFile(FILE *const fp);

void ReplaceNewLineCharWithNullTerminator(char *const s);

bool FileIsEmpty(FILE *fp);

#endif
