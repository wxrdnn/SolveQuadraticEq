#define SLE_INFINITE_ROOTS -1

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

int SolveQuadraticEquation(const double a, const double b, const double c, double *x1, double *x2);

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

int SolveLinearEquation(const double a, const double b, double *x);
