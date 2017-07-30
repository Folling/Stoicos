#include "hashkey.h"

Key generatePosKey(const position* pos)
{

	// take in all necessary parameters to turn a position into a key
	int piece = 0;
	Key finalKey = 0ULL;
	for(int sq = 0; sq < relevantSquares; sq++)
	{
		piece = pos->pieces[sq64to120[sq]];
		if(piece!=EMPTY)
		{
			// validates piece
			ASSERT(piece >= P && piece <= k)
			finalKey ^= pieceKeys[piece][sq];
		}
	}
	if(pos->side == WHITE)
	{
		finalKey ^= sideKey;
	}
	if(pos->enPassentSquare != OFF_BOARD)
	{
		// validates en-Passent square
		ASSERT(pos->enPassentSquare >= 0 && pos->enPassentSquare < amountSquares)

		finalKey ^= pieceKeys[EMPTY][pos->enPassentSquare];
	}

	// validates castle Permission
	ASSERT(pos->castlePermission >= 0 && pos->castlePermission < castleOptions);

	finalKey ^= castleKeys[pos->castlePermission];

	return finalKey;
}
