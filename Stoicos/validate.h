#ifndef STOICOS_VALIDATE_H
#define STOICOS_VALIDATE_H

#include "constants.h"

inline bool sqOnBoard(const int sq)
{
	return squareFiles[sq] != OFF_BOARD ? 1 : 0;
}

inline bool validSide(const int side)
{
	return (side == WHITE || side == BLACK) ? 1 : 0;
}

inline bool fileRankValid(const int fr)
{
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

inline bool pieceValid(const int piece)
{
	return (piece > EMPTY && piece <= k) ? 1 : 0;
}

inline bool pieceValidEmpty(const int piece)
{
	return (piece >= EMPTY && piece <= k) ? 1 : 0;
}

#endif