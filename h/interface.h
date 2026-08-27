#ifndef INTERFACE_H

#define INTERFACE_H

#include "errorHandle.h"
#include "io.h"
#include "solve.h"

Error SolveSingle(const InputType inputType);
// TODO
// Error ProcessArgs(const int argc, const char *const argv[]);
Error SolveCycle();

#endif
