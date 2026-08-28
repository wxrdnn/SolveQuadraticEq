#ifndef IO_H

#define IO_H

#include "errorHandle.h"
#include "interface.h"
#include "solve.h"
#include <stdio.h>

Error Get2DegreePolynomial(const InputType inputType, Polynomial *const pp);

Error GetFirst2DegreePolynomialFromFile(Polynomial *const pp);

Error GetNext2DegreePolynomialFromFile(FILE *const fp, Polynomial *const pp,
                                       const char separator);

Error GetNext2DegreeRootsFromFile(FILE *const fp, Roots *const rp,
                                  const char separator);

//----------------------------------------------------------
//! Asks User for input type in terminal (stdin).
//!
//! @return InputType enum
//----------------------------------------------------------
InputType AskForInputType();

//----------------------------------------------------------
//! Asks User for file name in terminal (stdin).
//!
//! @param [out] fileName User's input.
//----------------------------------------------------------
void AskForFileName(char *const fileName);

Error ParsePolynomial(const char *const s, const char separator,
                      Polynomial *pp);

Error Parse2DegreeRoots(const char *const s, const char separator,
                        Roots *const rp);

Error ParseNDoubles(const char *const input, const unsigned nItems,
                    double *const arr, const char separator);

//----------------------------------------------------------
//! Asks User in terminal (stdin) for cycle solve all equations from file.
//!
//! @return True if User choosed cycle solve, otherwise false.
//----------------------------------------------------------
bool AskForCycleSolve();

//----------------------------------------------------------
//! Displays Author and program name (stdout).
//----------------------------------------------------------
void DisplayGreeting();

//----------------------------------------------------------
//! Display Roots structure in terminal (stdout).
//!
//! @param [in] roots Roots structure to display.
//----------------------------------------------------------
void DisplayRoots(const Roots roots);

//----------------------------------------------------------
//! Display Polynomial structure in terminal (stdout).
//!
//! @param [in] pol Polynomial structure to display.
//----------------------------------------------------------
void DisplayPolynomial(const Polynomial pol);

void DisplayMode(const Mode mode);

void DisplayHelp();

//----------------------------------------------------------
//! Reads a number from User's input (stdin). If input is incorrect, returns 0.
//!
//! @return Number from User's input or 0.
//----------------------------------------------------------
int GetNum();

#endif
