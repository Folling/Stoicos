#ifndef STOICOS_MAKEMOVE_H
#define STOICOS_MAKEMOVE_H

#include "constants.h"
#include "position.h"
#include "validate.h"
#include "move.h"

// to change the posKey depending on what happens
// assumes that the position pointer will ALWAYS be called "pos"
#define HASH_PIECE(piece, sq) (pos->positionKey ^= (pieceKeys[piece][sq]))
#define HASH_CA (pos->positionKey ^= castleKeys[pos->castlePermission])
#define HASH_SIDE (pos->positionKey ^= sideKey)
#define HASH_EP (pos->positionKey ^= pieceKeys[EMPTY][pos->enPassentSquare])

// ca_perm &= castlePerm[from]
// for bits of castle permission equal 15 ( 1111 == 15 )
// moving one of the things will lose any of the permission when &= ing it.
// e.g. moving the king and then &= it will mean we &= with 3, which gives this:
// 1111 -> 0011 the most significant two bits were used for black castling and he has now
// lost both these options.

const int castlePerm[amountSquares] = {
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

static void clearPiece(const int sq, position* pos);
static void addPiece(const int sq, position* pos, const int piece);

static void movePiece(const int from, const int to, position* pos);

bool makeMove(const int move, position* pos);

void takeMove(position* pos);

#endif