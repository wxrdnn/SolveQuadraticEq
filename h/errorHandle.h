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

//----------------------------------------------------------
//! Prints error message based on the Error structure data.
//!
//! @param [in] error Error struct.
//!
//! @return Exact same Error struct, but context's '\\n' symbol replaced with
//! '\0'.
//----------------------------------------------------------
Error HandleError(Error error);

//----------------------------------------------------------
//! Creates an Error structure.
//!
//! @param [in] exitCode Exit code of the error.
//! @param [in] context Optional error context, such as name of crashed file.
//! Leave empty or NULL if not needed.
//!
//! @return Created Error structure.
//----------------------------------------------------------
Error CreateError(const ExitCode exitCode, const char *const context);

//----------------------------------------------------------
//! Translates standart library's errno code to ExitCode enum for error
//! handling.
//!
//! @param [in] errnoCode Standart library's errno code.
//!
//! @return Translated exit code to ExitCode enum.
//----------------------------------------------------------
ExitCode TranslateErrnoCode(const int errnoCode);

#endif
