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

#define ASSERT_POLYNOMIAL_CORRECT(pol__)                                       \
    {                                                                          \
        for (unsigned i = 0; i < (pol__).coefsAmount; ++i)                     \
        {                                                                      \
            ASSERT_DOUBLE_CORRECT((pol__).coefs[i]);                           \
        }                                                                      \
    }
#define ASSERT_ROOTS_FINITE(roots__)                                           \
    {                                                                          \
        for (int i = 0; i < (roots__).rootsAmount; ++i)                        \
        {                                                                      \
            ASSERT_DOUBLE_CORRECT((roots__).roots[i]);                         \
        }                                                                      \
    }

#endif
