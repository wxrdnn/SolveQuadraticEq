#ifndef IO

#define IO

void DisplayGreeting();

//! Returns 0 if input is correct, otherwise 1
int GetInput(double *a, double *b, double *c);

void DisplayOutput(int roots, const double *x1, const double *x2);

void DisplayInput(const double a, const double b, const double c);

#endif
