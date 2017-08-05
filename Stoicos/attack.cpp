#include "attack.h"

bool isBishopOrQueen(int piece) 
{
	if (piece != B && piece != b && piece != Q && piece != q) return false;
	return true;
}

bool isRookOrQueen(int piece)
{
	if (piece != R && piece != r && piece != Q && piece != q) return false;
	return true;
}

bool isKnight(int piece)
{
	if (piece != N && piece != n) return false;
	return true;
}

bool isKing(int piece)
{
	if (piece != K && piece != k) return false;
	return true;
}

bool isSquareAttacked(const int square, const int side, const position* pos)
{
	ASSERT(sqOnBoard(square));
	ASSERT(validSide(side));
	ASSERT(pos->checkBoard());

	// side is attacking side, not specifically current side

	// checks whether a pawn is attacking the square
	if(side == WHITE)
	{
		if (pos->pieces[square - 11] == P || pos->pieces[square - 9] == P) return true;		
	} else
	{
		if (pos->pieces[square + 11] == p || pos->pieces[square + 9] == p) return true;
	}
	for(int i = 0; i < knightDirs; i++)
	{
		int piece = pos->pieces[square + knightDir[i]];
		if (isN(piece) && pieceColours[piece] == side) return true;
	}
	for(int i = 0; i < bishopDirs; i++)
	{
		int dir = bishopDir[i];
		int t_square = square + dir;
		int piece = pos->pieces[t_square];

		// loops through all the diagonal squares until it either hits a piece or goes off board
		// if it hits a piece it checks whether the piece is a bishop
		while(piece != OFF_BOARD)
		{
			if(piece != EMPTY)
			{
				if (isBQ(piece) && pieceColours[piece] == side) return true;
				break;
			}
			t_square += dir;
			piece = pos->pieces[t_square];
		}
	}
	for (int i = 0; i < rookDirs; i++)
	{
		int dir = rookDir[i];
		int t_square = square + dir;
		int piece = pos->pieces[t_square];

		// loops through all the diagonal squares until it either hits a piece or goes off board
		// if it hits a piece it checks whether the piece is a bishop
		while (piece != OFF_BOARD)
		{
			if (piece != EMPTY)
			{
				if (isRQ(piece) && pieceColours[piece] == side) return true;
				break;
			}
			t_square += dir;
			piece = pos->pieces[t_square];
		}
	}
	for (int i = 0; i < kingDirs; i++)
	{
		int piece = pos->pieces[square + kingDir[i]];
		if (isK(piece) && pieceColours[piece] == side) return true;
	}
	return false;
}