#ifndef INTERFACE_H

#define INTERFACE_H

#include "errorHandle.h"
#include "solve.h"

enum Mode
{
    mSolveSquare = 0,
    mTestSquare = 1,
    mGraphing = 2,
};

enum InputType
{
    itKeyborad = 0,
    itFile = 1,
};

struct LaunchOptions
{
    Mode mode;
    bool displayHelp;
};

Error SolveSingle(const InputType inputType);

//----------------------------------------------------------
//! Process launch arguments.
//!
//! @param [in] argc Argument count.
//! @param [in] argv Array of pointers on argument strings.
//!
//! @param [out] mode Program mode based on launch arguments.
//!
//! @return Error structure.
//----------------------------------------------------------
Error ProcessArgs(const unsigned argc, const char *const argv[],
                  LaunchOptions *const lp);

Error LaunchProgram(const LaunchOptions *const options);

Error LaunchSolveSquareMode();

Error LaunchTestMode();

Error SolveCycle();

#endif
