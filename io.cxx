#include "io.h"
#include "assert.h"
#include "solve.h"
#include <cstdio>
#include <stdio.h>

const int cMaxLine = 1024;

void DisplayGreeting()
{
  printf("%s",
         __GREEN "# Solve quadratic equation\n# Made by Chumakov Alexey (c) "
                 "2026\n\n" __RESET);
  return;
}

void GetInput(double *a, double *b, double *c)
{
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);

  char inputLine[cMaxLine] = {};

  while (true)
  {
    printf(__GREEN "Enter a, b, c separated by space:\n" __RESET);
    fgets(inputLine, cMaxLine, stdin);
    if (sscanf(inputLine, "%lg %lg %lg", a, b, c) == 3)
    {
      return;
    }

    printf(__RED "Error: Incorrect input.\n\n" __RESET);
  }
}

void DisplayOutput(int roots, const double *x1, const double *x2)
{
  switch (roots)
  {
  case krTwo:
    printf(__GREEN "There are two roots:\nx1: %lg\nx2: %lg\n" __RESET, *x1,
           *x2);
    break;
  case krOne:
    printf(__YELLOW "There is one root:\nx: %lg\n" __RESET, *x1);
    break;
  case krZero:
    printf(__BLUE "There are no roots for this equation\n" __RESET);
    break;
  case krInfinite:
    printf(__CYAN
           "There are infinite number of roots for this equation\n" __RESET);
    break;
  default:
    printf("Invalid number of roots\n");
    break;
  }
  return;
}

void DisplayInput(const double a, const double b, const double c)
{
  printf("Solving (%lg) * x2 + (%lg) * x + (%lg)\n", a, b, c);
}

void DisplayCat()
{
  printf("%s", __YELLOW
         " /\\____/\\\n ( o   o )\n (  =^=  )\n (        )\n (         )\n ( "
         "         ))))))))))))\n\n" __RESET);
}

void DisplaySadCat()
{
  printf("%s", "          .__....._             _.....__,\n            .\": o "
               ":':         ;': o :\".\n            `. `-' .'.       .'. `-' "
               ".'\n              `---'             `---'\n\n    _...----...   "
               "   ...   ...      ...----..._\n .-'__..-\"\"'----    `.  `\"`  "
               ".'    ----'\"\"-..__`-.\n'.-'   _.--\"\"\"'       `-._.-'      "
               " '\"\"\"--._   `-.`\n'  .-\"'                  :               "
               "   `\"-.  `\n  '   `.              _.'\"'._              .'   "
               "`\n        `.       ,.-\"'       \"'-.       .'\n          `.  "
               "                         .'\n            `-._                  "
               " _.-'\n                `\"'--...___...--'\"`\n```\n");
}
