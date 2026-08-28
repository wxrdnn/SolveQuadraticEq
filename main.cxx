#include "h/displayCats.h"
#include "h/errorHandle.h"
#include "h/interface.h"
#include "h/io.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    LaunchOptions launchOptions = {};

    Error error = ProcessArgs((unsigned)argc, argv, &launchOptions);

    if (error.exitCode != ecSuccess)
    {
        HandleError(error);
        return error.exitCode;
    }

    if (!launchOptions.displayHelp)
    {
        DisplayGreeting();
        DisplayCat();
        DisplayMode(launchOptions.mode);
    }

    error = LaunchProgram(&launchOptions);

    HandleError(error);
    return error.exitCode;
}
