#include "movegen.h"

enum direction
{
	left = 9,
	right = 11
};

void printMoveList(const moveList* list)
{
	std::cout << "MoveList: \n";
	std::cout << "Total moves: " << list->count << std::endl;
	for(int i = 0; i < list->count; i++)
	{
		move t = list->moves[i];
		int score = list->moves[i].score;

		std::cout << "Move " << i+1 << ": ";
		t.printMove();
		std::cout << std::endl << "Score: " << score << std::endl;
	}
}

void addQuietMove(const position* pos, int mInf, moveList* list)
{
	move t;
	t.information = mInf;
	t.score = 0;
	list->moves.push_back(t);
	list->count++;
}

void addCaptureMove(const position* pos, int mInf, moveList* list)
{
	move t;
	t.information = mInf;
	t.score = 0;
	list->moves.push_back(t);
	list->count++;
}

void addEnPassentMove(const position* pos, int mInf, moveList* list)
{
	move t;
	t.information = mInf;
	t.score = 0;
	list->moves.push_back(t);
	list->count++;
}


// slightly altered to only use one function and have cap be EMPTY otherwise. Not sure if it works
void addWhitePawnMove( const position* pos, const int from, const int to, const int cap, moveList* list)
{
	if(squareRanks[from] == RANK_7)
	{
		addCaptureMove(pos, MOVE(from, to, cap, Q, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, N, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, R, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, B, NOFLAG), list);
	} else
	{
		addCaptureMove(pos, MOVE(from, to, cap, EMPTY, NOFLAG), list);
	}
}

void addBlackPawnMove(const position* pos, const int from, const int to, const int cap, moveList* list)
{
	if (squareRanks[from] == RANK_2)
	{
		addCaptureMove(pos, MOVE(from, to, cap, q, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, n, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, r, NOFLAG), list);
		addCaptureMove(pos, MOVE(from, to, cap, b, NOFLAG), list);
	}
	else
	{
		addCaptureMove(pos, MOVE(from, to, cap, EMPTY, NOFLAG), list);
	}
}

void generateAllMoves(const position* pos, moveList* list)
{

	// TODO reduce pawn move generation to not use the "if" and maybe reduce it to one addPawnMove function

	ASSERT(pos->checkBoard());

	list->count = 0;
	int side = pos->side;

	if(side == WHITE)
	{
		for(int i = 0; i < pos->pieceNum[P]; i++)
		{
			int sq = pos->pList[P][i];
			ASSERT(sqOnBoard(sq));

			// nonCap moves
			if(pos->pieces[sq + pawnRange] == EMPTY)
			{
				// pawns move bitwise 10 forward as our board is 10 wide
				addWhitePawnMove(pos, sq, sq + pawnRange, EMPTY, list);
				if (squareRanks[sq] == RANK_2 && pos->pieces[sq + psRange] == EMPTY)
				{
					// pawns can move two squares if they're on the second rank
					addQuietMove(pos, MOVE(sq, sq + psRange, EMPTY, NOPROM, mFlagPS), list);
				}
			}
			
			// cap moves
			if(sqOnBoard(sq + left) && pieceColours[pos->pieces[sq + left]] == BLACK)
			{
				addWhitePawnMove(pos, sq, sq + left, pos->pieces[sq + left], list);
			}
			if (sqOnBoard(sq + right) && pieceColours[pos->pieces[sq + right]] == BLACK)
			{
				addWhitePawnMove(pos, sq, sq + right, pos->pieces[sq + right], list);
			}
			// enPassent moves
			if(sq + left == pos->enPassentSquare)
			{
				addCaptureMove(pos, MOVE(sq, sq + left, EMPTY, EMPTY, mFlagEP), list);
			}
			if(sq + right == pos->enPassentSquare)
			{
				addCaptureMove(pos, MOVE(sq, sq + right, EMPTY, EMPTY, mFlagEP), list);
			}
		}
	}
	else // black pawns
	{
		for (int i = 0; i < pos->pieceNum[p]; i++)
		{
			int sq = pos->pList[p][i];
			ASSERT(sqOnBoard(sq));

			// nonCap moves
			if (pos->pieces[sq - pawnRange] == EMPTY)
			{
				// pawns move bitwise 10 forward as our board is 10 wide
				addBlackPawnMove(pos, sq, sq - pawnRange, EMPTY, list);
				if (squareRanks[sq] == RANK_7 && pos->pieces[sq - psRange] == EMPTY)
				{
					// pawns can move two squares if they're on the second rank
					addQuietMove(pos, MOVE(sq, sq - psRange, EMPTY, NOPROM, mFlagPS), list);
				}
			}

			// cap moves
			if (sqOnBoard(sq - left) && pieceColours[pos->pieces[sq - left]] == WHITE)
			{
				addBlackPawnMove(pos, sq, sq - left, pos->pieces[sq - left], list);
			}
			if (sqOnBoard(sq - right) && pieceColours[pos->pieces[sq - right]] == WHITE)
			{
				addBlackPawnMove(pos, sq, sq - right, pos->pieces[sq - right], list);
			}
			// enPassent moves
			if (sq - left == pos->enPassentSquare)
			{
				addCaptureMove(pos, MOVE(sq, sq - left, EMPTY, EMPTY, mFlagEP), list);
			}
			if (sq - right == pos->enPassentSquare)
			{
				addCaptureMove(pos, MOVE(sq, sq - right, EMPTY, EMPTY, mFlagEP), list);
			}
		}
	}
}