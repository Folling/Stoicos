#ifndef STOICOS_BITBOARD_H
#define STOICOS_BITBOARD_H

#include <vector>
#include "constants.h"

typedef unsigned long long QWORD;

struct pastMoves
{
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	QWORD positionKey;
};

class bitboard
{
public:
	bitboard();
	~bitboard();
private:
	short castePermission;

	// TODO what is this for?
	int pieces[amountSquares];

	// position of pawns
	QWORD pawns[playerTypes];

	// posiiton of kings
	int kingSquares[uniquePlayerTypes];	
	int side;

	// TODO what is this for?
	int enPassentSquare;
	int fiftyMoveCount;
	
	// current move in halfsteps
	int ply;

	// to undo moves
	int historyPly;

	// unique key to save the position and load it
	QWORD positionKey;
	int amountPieces[pieceTypes];

	// includes all non-pawns
	short amountOfficiers[playerTypes];

	// includes rooks and queens
	short amountMajors[playerTypes];

	// includes bishops and knights
	short amountMinors[playerTypes];

	// necessary to be able to undo moves
	std::vector<pastMoves> history;
};

#endif