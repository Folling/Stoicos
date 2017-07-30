#ifndef STOICOS_HASHKEY_H
#define STOICOS_HASHKEY_H

#include <cstdlib>

#include "position.h"
#include "constants.h"
#include "bitboard.h"

#define RAND64 	(QWORD)rd() + \
			    ((QWORD)rd() << 32)

extern Key pieceKeys[pieceTypes][relevantSquares];
extern Key sideKey;
extern Key castleKeys[castleOptions];

Key generatePosKey(const position* pos);

#endif
