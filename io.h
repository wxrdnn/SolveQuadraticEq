#ifndef __IO

#define __IO

#include "solve.h"
#include <stdio.h>

#define __RED "\x1b[31m"
#define __GREEN "\x1b[32m"
#define __BLUE "\x1b[34m"
#define __MAGENTA "\x1b[35m"
#define __YELLOW "\x1b[33m"
#define __CYAN "\x1b[36m"
#define __RESET "\x1b[0m"

const int cMaxLine = 1024;

enum InputType
{
    itKeyborad = 0,
    itFile = 1,
};

enum ParseResult
{
    prSucces = 0,
    prFail = 1,
};

Polynomial Get2DegreePolynomial(InputType inputType);

InputType GetInputType();

Polynomial Get2DegreePolynomialFromFile(FILE *fp);

void GetFileName(char *fileName);

ParseResult ParsePolynomial(const char *s, char separator, Polynomial *pp);

bool AskForCycleSolve();

void DisplayGreeting();

void DisplayCat();

void DisplaySadCat();

void DisplayRoots(const Roots roots);

void DisplayPolynomial(const Polynomial pol);

long CountLinesOfFile(FILE *fp);

#endif
