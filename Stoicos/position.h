#ifndef STOICOS_POSITION_H
#define STOICOS_POSITION_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "constants.h"
#include "bitboard.h"


#define RAND64 	(QWORD)rd() | \
			    ((QWORD)rd() << 32)

extern Key pieceKeys[pieceTypes][relevantSquares];
extern Key sideKey;
extern Key castleKeys[castleOptions];

struct pastMoves
{
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	QWORD positionKey;
};

const int maxGameMoves = 2048;

class position
{
public:
	void resetPosition();
	void parseFEN(std::string FEN);
	void generateKey();
	void printPosition() const;
	void updatePieceList();

	// validates that the board was setup correctly
	bool checkBoard() const;
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

	// keeps track of the amount of pieces for each piece
	int pieceNum[pieceTypes];

	// necessary to be able to undo moves
	pastMoves history[maxGameMoves];

	// includes all non-pawns
	int officers[uniquePlayerTypes];

	// includes rooks and queens
	int majors[uniquePlayerTypes];

	// includes bishops and knights
	int minors[uniquePlayerTypes];

	int material[uniquePlayerTypes];
};

#endif