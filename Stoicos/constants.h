#ifndef STOICOS_CONSTANTS_H
#define STOICOS_CONSTANTS_H

const short amountSquares = 120;
const short playerTypes = 3;
const short uniquePlayerTypes = 2;
const short pieceTypes = 13;

enum file
{
	FILE_A, 
	FILE_B,
	FILE_C,
	FILE_D,
	FILE_E,
	FILE_F,
	FILE_G,
	FILE_H,
	OFF_FILE
};

enum rank
{
	RANK_1,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	OFF_RANK
};

// different types a square can be, capitalised for white pieces
enum occupant
{
	EMPTY,
	P,
	N,	
	B,
	R,
	Q,
	K,
	p,
	n,
	b,
	r,
	q
};

enum activePlayer
{
	WHITE,
	BLACK,
	BOTH
};

enum square
{
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, OFF_BOARD
};

enum castlingPermission 
{
	// whether you can castle queen or kingside

	WHITE_KING_SIDE  = 1,
	WHITE_QUEEN_SIDE = 2,
	BLACK_KING_SIDE  = 4,
	BLACK_QUEEN_SIDE = 8,
};

#endif