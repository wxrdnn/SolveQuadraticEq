#ifndef ERCODES_H

#define ERCODES_H

#include "limits.h"

enum ExitCode
{
    ecSucces = 0,
    ecCantOpenFile = 1,
    ecFileIsEmpty = 2,
    ecIncorrectInput = 3,
    ecParsingFailed = 4,
    ecUnexpectedFailure = 5,
};

typedef struct
{
    ExitCode exitCode;
    char context[cMaxLine];
} Error;

Error HandleError(const Error error);

Error CreateError(const ExitCode exitCode, const char *const context);

#endif
