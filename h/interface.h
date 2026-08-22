#ifndef INTERFACE_H

#define INTERFACE_H

#include "errorHandle.h"
#include "io.h"
#include "solve.h"

Error SolveSingle(const InputType inputType);
Error SolveCycle();

#endif
