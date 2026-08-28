#ifndef SOLVE_H

#define SOLVE_H

#include "limits.h"

const int cInfiniteRootsAmount = -1;
const int c2DegreeCoefsAmount = 3;
const int c1DegreeCoefsAmount = 2;

struct Polynomial
{
    double coefs[cMaxCoefsAmount];
    unsigned coefsAmount;
};

struct Roots
{
    double roots[cMaxRootsAmount];
    int rootsAmount;
};

//----------------------------------------------------------
//! Solves a quadratic equation ax2 + bx + c = 0.
//!
//! @param [in] pol Polynomial struct, contains amount of coefficients and their
//! values.
//!
//! @return Roots structure, contains amount of roots and their values by
//! ascending.
//!
//! @note In case of infinite number of roots, returns cInfiniteRootsAmount.
//----------------------------------------------------------
Roots SolveQuadraticEquation(const Polynomial pol);

//----------------------------------------------------------
//! Solves a linear equation ax + b = 0.
//!
//! @param [in] pol Polynomial struct, contains amount of coefficients and their
//! values.
//!
//! @return Roots structure, contains amount of roots and their values by
//! ascending.
//!
//! @note In case of infinite number of roots, returns cInfiniteRootsAmount.
//----------------------------------------------------------
Roots SolveLinearEquation(const Polynomial pol);

//----------------------------------------------------------
//! Calculates discriminant of 2-degree polynomial: D = b2 - 4*a*c.
//!
//! @param [in] pol Polynomial struct, contains amount of coefficients and their
//! values.
//!
//! @return Discriminant value.
//----------------------------------------------------------
double Get2DegreeDiscriminant(const Polynomial pol);

//----------------------------------------------------------
//! Compares two Roots structures.
//!
//! @param [in] r1 First Roots structure to compare.
//! @param [in] r2 Second Roots structure to compare.
//!
//! @return True if the Roots structures are equal, otherwise false.
//----------------------------------------------------------
bool EqualRoots(const Roots r1, const Roots r2);

#endif
