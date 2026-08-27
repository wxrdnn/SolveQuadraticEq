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

Error GetNext2DegreeRootsFromFile(FILE *const fp, Roots *const rp,
                                  const char separator);

//----------------------------------------------------------
//! Asks User for input type in terminal.
//!
//! @return InputType enum
//----------------------------------------------------------
InputType AskForInputType();

//----------------------------------------------------------
//! Asks User for file name in terminal.
//!
//! @param [out] fileName User's input.
//----------------------------------------------------------
void AskForFileName(char *const fileName);

Error ParsePolynomial(const char *const s, const char separator,
                      Polynomial *pp);

Error Parse2DegreeRoots(const char *const s, const char separator,
                        Roots *const rp);

Error ParseNDoubles(const char *const s, const unsigned n, double *const arr,
                    const char separator);

//----------------------------------------------------------
//! Asks User for cycle solve all equations from file.
//!
//! @return True if User choosed cycle solve, otherwise false.
//----------------------------------------------------------
bool AskForCycleSolve();

//----------------------------------------------------------
//! Displays Author and programm name.
//----------------------------------------------------------
void DisplayGreeting();

void DisplayRoots(const Roots roots);

void DisplayPolynomial(const Polynomial pol);

bool FileIsEmpty(FILE *const fp);

//! returns correct input, otherwise 0
int GetNum();

#endif
