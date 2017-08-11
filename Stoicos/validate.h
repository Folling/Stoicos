#ifndef STOICOS_VALIDATE_H
#define STOICOS_VALIDATE_H

#include "constants.h"

inline bool sqOnBoard(const int sq)
{
	return squareFiles[sq] != OFF_BOARD ? true : false;
}

inline bool validSide(const int side)
{
	return (side == WHITE || side == BLACK) ? true : false;
}

inline bool fileRankValid(const int fr)
{
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

inline bool pieceValid(const int piece)
{
	return (piece > EMPTY && piece <= k) ? true : false;
}

inline bool pieceValidEmpty(const int piece)
{
	return (piece >= EMPTY && piece <= k) ? true : false;
}

#endif