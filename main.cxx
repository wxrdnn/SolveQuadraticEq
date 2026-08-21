#include "io.h"
#include "solve.h"

int main()
{
    // TODO Input from file

    DisplayGreeting();
    DisplayCat();

    InputType inputType = GetInputType();
    Polynomial pol = Get2DegreePolynomial(inputType);

    DisplayPolynomial(pol);

    DisplayRoots(SolveQuadraticEquation(pol));

    return 0;
}
