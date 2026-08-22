#include "h/errorHandle.h"
#include "h/colors.h"
#include "string.h"
#include <stdio.h>

Error HandleError(const Error error)
{
    switch (error.exitCode)
    {
    case ecSucces:
        break;

    case ecCantOpenFile:
        fprintf(stderr, __RED "Error: Can\'t open file \"%s\".\n" __RESET,
                error.context);
        break;

    case ecFileIsEmpty:
        fprintf(stderr, __RED "Error: File is \"%s\" empty.\n" __RESET,
                error.context);
        break;

    case ecIncorrectInput:
        fprintf(stderr, __RED "Error: Incorrect file input.\n" __RESET);
        break;

    case ecParsingFailed:
        fprintf(stderr, __RED "Error: Failed parsing \"%s\".\n" __RESET,
                error.context);
        break;
    }
    return error;
}

Error CreateError(const ExitCode exitCode, const char *const context)
{
    Error error = {};
    error.exitCode = exitCode;
    strcpy(error.context, context);
    return error;
}
