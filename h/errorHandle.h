#ifndef ERCODES_H

#define ERCODES_H

#include "limits.h"

enum ExitCode
{
    ecSuccess = 0,
    ecNoSuchFile = 1,
    ecFileIsEmpty = 2,
    ecIncorrectInput = 3,
    ecParsingFailed = 4,
    ecUnexpectedFailure = 5,
    ecCantReadFile = 6,
    ecTestFilesDiffer = 7,
    ecNoAccesToFile = 8,
    ecTooManyOpenFiles = 9,
    ecFileIsDirectory = 10,
    ecFileNameTooLong = 11,
    ecHardwareError = 12,
    ecFileIsBusy = 13,
    ecNoSpaceOnDevice = 14,
    ecReadOnly = 15,
    ecNotDirectory = 16,
    ecWrongUsage = 17,
};

typedef struct
{
    ExitCode exitCode;
    char context[cMaxLine];
} Error;

Error HandleError(Error error);

Error CreateError(const ExitCode exitCode, const char *const context);

ExitCode TranslateErrnoCode(const int errnoCode);

#endif
