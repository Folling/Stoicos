#ifndef STOICOS_ATTACK_H
#define STOICOS_ATTACK_H

#include "constants.h"
#include "position.h"

#define isBQ(pi) isBishopOrQueen(pi)
#define isRQ(pi) isRookOrQueen(pi)
#define isN(pi)  isKnight(pi)
#define isK(pi)  isKing(pi)

const int knightDirs = 8;
const int rookDirs = 4;
const int bishopDirs = 4;
const int kingDirs = 8;

const int knightDir[knightDirs] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int rookDir[rookDirs]   = { -1, -10, 1, 10 };
const int bishopDir[bishopDirs] = { -9, -11, 9, 11 };
const int kingDir[kingDirs]   = { -1, -9, -10, -11, 1, 9, 10, 11 };

bool isBishopOrQueen(int piece);
bool isRookOrQueen(int piece);
bool isKnight(int piece);
bool isKing(int piece);

bool isSquareAttacked(const int square, const int side, const position* pos);

#endif