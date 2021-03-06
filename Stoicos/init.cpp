#include "init.h"


int sq120to64[amountSquares];
int sq64to120[relevantSquares];

Mask setMask[64];
Mask clearMask[64];

QWORD pieceKeys[pieceTypes][relevantSquares];
QWORD sideKey;
QWORD castleKeys[castleOptions];

std::random_device rd;

int squareFiles[amountSquares];
int squareRanks[amountSquares];

void initAll()
{
	init120to64();
	initMasks();
	initHashkeys();
	initSquareIdentifiers();
}

void init120to64()
{
	int square64 = 0;
	// sets all squares to -1;
	for(int i = 0; i < amountSquares; i++)
	{
		sq120to64[i] = -1;
	}
	// sets all but off-board squares to their representive value
	for(int r = RANK_1; r < OFF_RANK; r++)
	{
		for(int f = FILE_A; f < OFF_FILE; f++, square64++)
		{
			int square = from64to120(f, r);
			sq64to120[square64] = square;
			sq120to64[square] = square64;			
		}
	}
}

void initMasks()
{
	for(int i = 0; i < relevantSquares; i++)
	{
		setMask[i] = EMPTY_MASK;
	}
	for (int i = 0; i < relevantSquares; i++)
	{
		// this creates 64 setMasks each having exactly one bit set true
		// and 64 clearMasks each having one bit off
		setMask[i] |= 1ULL << i;
		clearMask[i] = ~setMask[i];
	}
}

void initHashkeys()
{
	for(int i = 0; i < pieceTypes; i++)
	{
		for(int j = 0; j < relevantSquares; j++)
		{
			pieceKeys[i][j] = RAND64;
		}
	}
	sideKey = RAND64;
	for(int i = 0; i < castleOptions; i++)
	{
		castleKeys[i] = RAND64;
	}
}

void initSquareIdentifiers()
{
	for(int i = 0; i < amountSquares; i++)
	{
		squareFiles[i] = OFF_BOARD;
		squareRanks[i] = OFF_BOARD;
	}
	for(int r = RANK_1; r <= RANK_8; r++)
	{
		for(int f = FILE_A; f <= FILE_H; f++)
		{
			int sq = from64to120(f, r);
			squareFiles[sq] = f;
			squareRanks[sq] = r;
		}
	}
}