#include "h/debug.h"
#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/interface.h"
#include "h/io.h"
#include <math.h>
#include <stdlib.h>

int main()
{
    // TODO File output
    // TODO solve cycle from keyboard

    // ASSERT_DOUBLE_CORRECT(INFINITY);

    DisplayGreeting();
    DisplayCat();

    InputType inputType = AskForInputType();
    bool cycleSolve = false;
    Error error = {};

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
