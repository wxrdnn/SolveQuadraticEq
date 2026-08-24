#include "h/errorHandle.h"
#include "h/colors.h"
#include "string.h"
#include <stdio.h>

Error HandleError(const Error error)
{
    switch (error.exitCode)
    {
    case ecSuccess:
        break;

    case ecCantOpenFile:
        fprintf(stderr, __RED "Error: Failed to open file \"%s\".\n" __RESET,
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

    case ecUnexpectedFailure:
    default:
        fprintf(stderr, __RED "Error: Unexpected failure.\n");
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
