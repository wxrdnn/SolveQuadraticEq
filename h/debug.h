#ifndef DEBUG_H

#define DEBUG_H

#include "cats.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(statement)                                                      \
    {                                                                          \
        if (!(statement))                                                      \
        {                                                                      \
            printf(__RED "Assertion \'" #statement "\' failed!" __RESET __BLUE \
                         "\nFile: " __RESET __YELLOW "%s" __RESET __BLUE       \
                         "\nLine: " __RESET __CYAN "%d\n" __RESET,             \
                   __FILE_NAME__, __LINE__);                                   \
            DisplaySadCat();                                                   \
            exit(1);                                                           \
        }                                                                      \
    }

#endif
