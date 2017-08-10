#ifndef STOICOS_ATTACK_H
#define STOICOS_ATTACK_H

#include "constants.h"
#include "position.h"
#include "validate.h"

#define isBQ(pi) isBishopOrQueen(pi)
#define isRQ(pi) isRookOrQueen(pi)
#define isN(pi)  isKnight(pi)
#define isK(pi)  isKing(pi)

bool isBishopOrQueen(int piece);
bool isRookOrQueen(int piece);
bool isKnight(int piece);
bool isKing(int piece);

bool isSquareAttacked(const int square, const int side, const position* pos);

#endif