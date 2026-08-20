#include <stdlib.h>
#include "solve.h"
#include "io.h"

void Test(int testAmount);

int main(){
    DisplayGreeting();
    Test(3);
}

void Test(int testAmount){
    for (int i = 0; i < testAmount; ++i){
        double a = rand()%2026;
        double b = rand()%2026;
        double c = rand()%2026;
        double x1 = 0, x2 = 0;

        DisplayInput(a, b, c);

        int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
        DisplayOutput(roots, &x1, &x2);
    }
}
