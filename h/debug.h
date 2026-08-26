#ifndef DEBUG_H

#define DEBUG_H

#include "colors.h"
#include "displayCats.h"
#include "solve.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG

#define ASSERT(statement) ((void)0)

#else

#define ASSERT(statement)                                                      \
    {                                                                          \
        if (!(statement))                                                      \
        {                                                                      \
            fprintf(stderr,                                                    \
                    __RED "Assertion \'" #statement                            \
                          "\' failed!" __RESET __BLUE                          \
                          "\nFile: " __RESET __YELLOW "%s" __RESET __BLUE      \
                          "\nLine: " __RESET __CYAN "%d\n" __RESET,            \
                    __FILE_NAME__, __LINE__);                                  \
            DisplaySadCat();                                                   \
            exit(1);                                                           \
        }                                                                      \
    }

#endif

#define ASSERT_DOUBLE_CORRECT(x) ASSERT(isfinite(x))

void AssertPolynomialCorrect(const Polynomial pol);
void AssertRootsFinite(const Roots roots);

#endif
