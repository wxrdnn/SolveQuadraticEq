#include "h/displayCats.h"
#include "h/interface.h"
#include "h/io.h"
#include <stdlib.h>

int main()
{
    // TODO check for fclose before return
    // TODO File output
    // TODO check double for finite and NaN
    // TODO test solving square eq with nan and inf coefs
    // TODO solve cycle from keyboard

    DisplayGreeting();
    DisplayCat();

    InputType inputType = AskForInputType();
    bool cycleSolve = false;

    if (inputType == itFile)
    {
        cycleSolve = AskForCycleSolve();
    }

    return HandleError(cycleSolve ? SolveCycle()
                                  : SolveSingle(inputType)) // TODO expand
        .exitCode;
}
