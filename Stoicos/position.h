#ifndef STOICOS_POSITION_H
#define STOICOS_POSITION_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <assert.h>

#include "constants.h"

struct pastMoves
{
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	QWORD positionKey;
};

class position
{
public:
	void resetPosition();
	void parseFEN(std::string FEN);
	position();
	~position();
public:

	short castlePermission;

	// position of pieces
	int pieces[amountSquares];

	// all pieceTypes and their entities
	int pList[pieceTypes][maxOfOnePiece];

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

	// necessary to be able to undo moves
	std::vector<pastMoves> history;

	// includes all non-pawns
	short officiers[playerTypes];

	// includes rooks and queens
	short majors[playerTypes];

	// includes bishops and knights
	short minors[playerTypes];
};

extern position mainGame;

#endif