#include "h/errorHandle.h"
#include "h/colors.h"
#include "h/debug.h"
#include "h/io.h"
#include "h/utils.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

Error HandleError(Error error)
{
    ASSERT(error.context != NULL);
    ReplaceNewLineCharWithNullTerminator(error.context);
    switch (error.exitCode)
    {
    case ecSuccess:
        break;

    case ecNoSuchFile:
        fprintf(stderr,
                __RED "Error: Failed to open file \"%s\" - no such file in "
                      "directory.\n" __RESET,
                error.context);
        break;

    case ecFileIsEmpty:
        fprintf(stderr, __RED "Error: File is \"%s\" empty.\n" __RESET,
                error.context);
        break;

    case ecIncorrectInput:
        fprintf(stderr, __RED "Error: Incorrect input.\n" __RESET);
        break;

    case ecParsingFailed:
        fprintf(stderr, __RED "Error: Failed parsing \"%s\".\n" __RESET,
                error.context);
        break;

    case ecCantReadFile:
        fprintf(stderr, __RED "Error: Failed to read file \"%s\".\n" __RESET,
                error.context);
        break;

    case ecTestFilesDiffer:
        fprintf(stderr, __RED "Error: Test files lengths differ.\n" __RESET);
        break;

    case ecFileIsBusy:
        fprintf(stderr, __RED "Error: File \"%s\" is busy.\n" __RESET,
                error.context);
        break;

    case ecFileIsDirectory:
        fprintf(stderr, __RED "Error: \"%s\" is a directory.\n" __RESET,
                error.context);
        break;

    case ecFileNameTooLong:
        fprintf(stderr, __RED "Error: File name \"%s\" is too long.\n" __RESET,
                error.context);
        break;

    case ecHardwareError:
        fprintf(stderr,
                __RED
                "Error: Failed to open file \"%s\" - hardware error.\n" __RESET,
                error.context);
        break;

    case ecNoAccesToFile:
        fprintf(
            stderr,
            __RED
            "Error: Failed to open file \"%s\" - permission denied.\n" __RESET,
            error.context);
        break;

    case ecTooManyOpenFiles:
        fprintf(stderr,
                __RED "Error: Failed to open file \"%s\" - too many files "
                      "opened.\n" __RESET,
                error.context);
        break;

    case ecNoSpaceOnDevice:
        fprintf(stderr,
                __RED "Error: Failed to write in file \"%s\" - no space left "
                      "on device.\n" __RESET,
                error.context);
        break;

    case ecReadOnly:
        fprintf(stderr,
                __RED "Error: Failed to write in file \"%s\" - file is "
                      "readonly.\n" __RESET,
                error.context);
        break;

    case ecNotDirectory:
        fprintf(stderr, __RED "Error: \"%s\" is not a directory.\n" __RESET,
                error.context);
        break;

    case ecWrongUsage:
        DisplayHelp();
        break;

    case ecUnexpectedFailure:
    default:
        fprintf(stderr, __RED "Error: Unexpected failure.\n" __RESET);
        break;
    }
    return error;
}

Error CreateError(const ExitCode exitCode, const char *const context)
{
    Error error = {};
    error.exitCode = exitCode;
    strcpy(error.context,
           context ? context : ""); // use empty string if context is null.
    return error;
}

ExitCode TranslateErrnoCode(const int errnoCode)
{
    switch (errnoCode)
    {
    case ENOENT:
        return ecNoSuchFile;

    case EACCES:
        return ecNoAccesToFile;

    case EMFILE:
        return ecTooManyOpenFiles;

    case EISDIR:
        return ecFileIsDirectory;

    case ENAMETOOLONG:
        return ecFileNameTooLong;

    case EBUSY:
        return ecFileIsBusy;

    case EIO:
        return ecHardwareError;

    case ENOSPC:
        return ecNoSpaceOnDevice;

    case EROFS:
        return ecReadOnly;

    case ENOTDIR:
        return ecNotDirectory;

    default:
        return ecUnexpectedFailure;
    }
}
