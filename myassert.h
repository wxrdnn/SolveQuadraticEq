#ifndef __ASSERT
#define __ASSERT

#include <stdio.h>
#include <stdlib.h>

#define __RED "\x1b[31m"
#define __YELLOW "\x1b[33m"
#define __CYAN "\x1b[36m"
#define __RESET "\x1b[0m"

#define assert(statement)                                                      \
  {                                                                            \
    if (!statement)                                                            \
    {                                                                          \
      printf(__RED "Assertion \'" #statement "\' failed!" __RESET              \
                   "\nFile: " __YELLOW "%s" __RESET "\nLine: " __CYAN          \
                   "%d\n" __RESET,                                             \
             __FILE_NAME__, __LINE__);                                         \
      exit(1);                                                                 \
    }                                                                          \
  }

#endif
