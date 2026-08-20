#include <cassert>
#include <cmath>
#include <cstdio>
#include "solve.h"

int main(int argc, char *argv[]){
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    printf("%s", "# Solve quadratic equation\n# Made by Chumakov Alexey (c) 2026\n^..^\n\n");
    printf("%s", "Enter a, b, c separated by space:\n");
    if (scanf("%lg %lg %lg", &a, &b, &c) != 3){
        printf("%s", "Error: Incorrect input.\n");
        return 1;
    }
    int roots = SolveQuadraticEquation(a, b, c, &x1, &x2);
    switch (roots) {
        case 2:
            printf("There are two roots:\nx1: %lg\nx2: %lg\n", x1, x2);
            break;
        case 1:
            printf("There is one root:\nx: %lg\n", x1);
            break;
        case 0:
            printf("%s", "There are no roots for this equation\n");
            break;
        case SLE_INFINITE_ROOTS:
            printf("%s", "There are infinite number of roots for this equation\n");
            break;
        default:
            printf("%s", "Invalid number of roots\n");
            break;
    }
    return 0;
}

int SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2){ // ax2 + bx + c = 0
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (a == 0)
        return SolveLinearEquation(b, c, x1);
    else {
        double discriminant = b*b - 4*a*c;
        if (discriminant < 0)
            return 0;
        else if (discriminant == 0) {
            *x1 = -b / 2.0 / a;
            return 1;
        }
        double sqrtDiscriminant = sqrt(discriminant);
        *x1 = (-b + sqrtDiscriminant) / 2.0 / a;
        *x2 = (-b - sqrtDiscriminant) / 2.0 / a;
        return 2;
    }
}

int SolveLinearEquation(double a, double b, double *x){ // ax + b = 0
    assert(x != NULL);
    assert(std::isfinite(a));
    assert(std::isfinite(b));

    if (a == 0){
        if (b == 0)
            return SLE_INFINITE_ROOTS;
        return 0;
    }
    *x = -b / a;
    return 1;
}
