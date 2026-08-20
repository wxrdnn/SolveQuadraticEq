#ifndef __IO

#define __IO

#define __RED "\x1b[31m"
#define __GREEN "\x1b[32m"
#define __BLUE "\x1b[34m"
#define __MAGENTA "\x1b[35m"
#define __YELLOW "\x1b[33m"
#define __CYAN "\x1b[36m"
#define __RESET "\x1b[0m"

void DisplayGreeting();

void DisplayCat();

void DisplaySadCat();

void GetInput(double *a, double *b, double *c);

void DisplayOutput(int roots, const double *x1, const double *x2);

void DisplayInput(const double a, const double b, const double c);

#endif
