#ifndef SOLVE_H

#define SOLVE_H

#include "limits.h"

const int cInfiniteRootsAmount = -1;
const int c2DegreeCoefsAmount = 3;
const int c1DegreeCoefsAmount = 2;

typedef struct
{
    double coefs[cMaxCoefsAmount];
    int coefsAmount;
} Polynomial;

typedef struct
{
    double roots[cMaxRootsAmount];
    int rootsAmount;
} Roots;

//----------------------------------------------------------
//! Solves a quadratic equation ax2 + bx + c = 0
//!
//! @param [in] a a-coefficient
//! @param [in] b a-coefficient
//! @param [in] c a-coefficient
//!
//! @return Roots structure contains amount of roots and their values by
//! ascending.
//!
//! @note In case of infinite number of roots, returns SLE_INFINITE_ROOTS.
//----------------------------------------------------------

Roots SolveQuadraticEquation(const Polynomial pol);

//----------------------------------------------------------
//! Solves a linear equation ax + b = 0
//!
//! @param [in] a a-coefficient
//! @param [in] b a-coefficient
//! @param [out] x Pointer to the root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns SLE_INFINITE_ROOTS.
//----------------------------------------------------------

Roots SolveLinearEquation(const Polynomial pol);

double Get2DegreeDiscriminant(const Polynomial pol);

bool EqualRoots(const Roots r1, const Roots r2);

#endif
