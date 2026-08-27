#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/interface.h"
#include "h/io.h"
#include "h/test.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Error error = {};

    if (argc > 2)
    {
        error = CreateError(ecWrongUsage, "");
        return HandleError(error).exitCode;
    }

    if (argc > 1 && strcmp(argv[1], "-t") == 0)
    {
        error = RunTests();
        return HandleError(error).exitCode;
    }

    // ASSERT_DOUBLE_CORRECT(INFINITY);

    DisplayGreeting();
    DisplayCat();

    InputType inputType = AskForInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    if (cycleSolve)
    {
        error = HandleError(SolveCycle());
    }
    else
    {
        error = HandleError(SolveSingle(inputType));
    }
    return error.exitCode;
}
