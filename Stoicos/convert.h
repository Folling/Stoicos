#ifndef STOICOS_CONVERT_H
#define STOICOS_CONVERT_H

#include "constants.h"

extern int sq120to64[amountSquares];
extern int sq64to120[relevantSquares];


int from64to120(int file, int rank);
std::string evaluateEnpassent(int input);

#endif