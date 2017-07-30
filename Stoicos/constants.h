#ifndef STOICOS_CONSTANTS_H
#define STOICOS_CONSTANTS_H

#include <random>
#include <conio.h>

#define DEBUG

// selfmade Assert funciton for debugging
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)){ \
printf("%s - Failed\n", #n); \
printf("In File %s \n", __FILE__); \
printf("At Line %d\n", __LINE__); \
_getch(); \
}

#endif

// to add a piece of any bitboard on a square (G2 e.g.):
// bitboard |= ADDPIECE(G2)
// multiple pieces can be added with bitboard |= ADDPIECE(G2) | ADDPIECE(G3) ...

#define ADDPIECE(n) (1ULL << sq120to64[n])

#define EMPTY_BITBOARD 0ULL
#define EMPTY_MASK 0ULL
#define EMPTY_KEY 0ULL

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TEST1_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1"
#define TEST2_FET "rnbqkbnr/pppppppp/8/8/8/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1"

// sets a bit true or a bit false
#define CLRBIT(bb, sq) ( bb &= clearMask[sq])
#define SETBIT(bb, sq) ( bb |= setMask[sq])

typedef unsigned long long QWORD;
typedef QWORD Bitboard;
typedef QWORD Mask;
typedef QWORD Key;

// GAME CONSTANTS
const short amountSquares = 120;
const short relevantSquares = 64;
const short playerTypes = 3;
const short uniquePlayerTypes = 2;
const short pieceTypes = 13;
const short maxOfOnePiece = 10;
const short castleOptions = 16;
extern std::random_device rd;

// table containing the indexes as resulted by popBit 
// in order to extract the popped bit's index
const int BitTable[64] = {
	63, 30,  3, 32, 25, 41, 22, 33,
	15, 50, 42, 13, 11, 53, 19, 34,
	61, 29,  2, 51, 21, 43, 45, 10,
	18, 47,  1, 54,  9, 57,  0, 35,
	62, 31, 40,  4, 49,  5, 52, 26,
	60,  6, 23, 44, 46, 27, 56, 16,
	 7, 39, 48, 24, 59, 14, 12, 55,
	38, 28, 58, 20, 37, 17, 36,  8
};

// GAME SPECIFICATIONS
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
	q,
	k
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

	WHITE_00  = 1,
	WHITE_000 = WHITE_00 << 1,
	BLACK_00  = WHITE_00 << 2,
	BLACK_000 = WHITE_00 << 3,
};

#endif