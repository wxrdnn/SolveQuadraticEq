#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/interface.h"
#include "h/io.h"
#include <stdlib.h>

int main()
{
    // TODO Fix asking for input type
    // TODO use errno for crash reasons
    // TODO File output
    // TODO test solving square eq with nan and inf coefs
    // TODO solve cycle from keyboard

    DisplayGreeting();
    DisplayCat();

    // Roots roots = {};
    // ParseRoots("1;1;1;", ';', &roots);
    // DisplayRoots(roots);

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
