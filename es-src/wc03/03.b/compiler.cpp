// 3.b compiler
//
// g++ -Wall -o compiler compiler.cpp parser.cpp
// ./compiler

#include <stdio.h>
#include <stdint.h>
#include "parser.hpp"

int main(int nArgc, char* aArgv[]) {

  Parser parser;

  // Initialiseren
  printf("03.b compiler\n\n");
  char varDec1[] = "led red 2";
  char varDec2[] = "button stop 22";
  char varDec3[] = "label fun";
  char varDec4[] = "led red 45";

  parser.parse(varDec1);
  parser.parse(varDec2);
  parser.parse(varDec3);
  parser.parse(varDec4);
  parser.printVars();

  // Afsluiten
  printf("\nAfgesloten :-)\n\n");
  return 0;
};