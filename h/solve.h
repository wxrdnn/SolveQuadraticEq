#ifndef __SOLVE

#define __SOLVE

const int cInfiniteRootsAmount = -1;
const int cMaxCoefsAmount = 8;
const int cMaxRootsAmount = 8;

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
//! @param [out] x1 Pointer to the 1st root
//! @param [out] x2 Pointer to the 2nd root
//!
//! @return Number of roots
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

#endif
