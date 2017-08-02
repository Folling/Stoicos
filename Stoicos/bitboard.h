#ifndef STOICOS_BITBOARD_H
#define STOICOS_BITBOARD_H

#include <iostream>

#include "constants.h"
#include "convert.h"

typedef QWORD Bitboard;

void printBitboard(Bitboard bb);
int countBits(Bitboard bb);
int popBit(Bitboard* bb);

#endif