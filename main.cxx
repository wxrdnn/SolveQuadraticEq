#include "h/cats.h"
#include "h/interface.h"
#include "h/io.h"
#include <stdlib.h>

int main()
{
    // TODO File output
    // TODO check double for finite and NaN
    // TODO test solving square eq with nan and inf coefs

    DisplayGreeting();
    DisplayCat();

    InputType inputType = GetInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    return HandleError(cycleSolve ? SolveCycle() : SolveSingle(inputType))
        .exitCode;
}
