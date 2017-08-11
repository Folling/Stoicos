#ifndef STOICOS_MOVE_H
#define STOICOS_MOVE_H

/*
 * hex numbers are represented by 4 bits per symbol so e.g.
 *      0000 0011 0110 1111 0100 0111 1111 in hex is
 *  hex: 0    3    A    F    8    B    F
 *
 *		0000 0000 0000 0000 0000 0111 1111 -> From square [ 1 2 4 8 16 32 64 > 98 on 120 square board ]
 *		0000 0000 0000 0011 1111 1000 0000 -> To square 
 *		0000 0000 0011 1100 0000 0000 0000 -> captured piece [13 pieces _ king can't be captured _ can fit in 4 bits]
 *		0000 0000 0100 0000 0000 0000 0000 -> En passent capture?
 *		0000 0000 1000 0000 0000 0000 0000 -> Pawn start?
 *		0000 1111 0000 0000 0000 0000 0000 -> promoted piece, if so which piece
 *		0001 0000 0000 0000 0000 0000 0000 -> castled?
 *		
 *		fromSquare 0x3F
 *		toSquare >> 7, 0x3F
 *		Caputred >> 14,0xF
 *		EP 0x40000
 *		Pawn Start 0x80000
 *		Promoted Piece >> 20, 0xF
 *		Castle 0x1000000
 */

#include <iostream>

#include "constants.h"
#include "attack.h"

#define FROMSQ(m)     (m & 0x7F)
#define TOSQ(m)       (m >> 7 & 0x7F)
#define CAPPIECE(m)   (m>>14 & 0xF)
#define ENPAS(m)      (m & mFlagEP)
#define PAWNSTART(m)  (m & mFlagPS)
#define PROMPIECE(m)  ((m>>20) & 0xF)
#define CASTLING(m)   (m & mFlagCstl)

// specifies the specifics of a move in a macro, could do this in a "makeMove(f,t,ca,pro,fl)" function but meh
#define MOVE(f,t,cap,pro,flag) ( (f) | ((t) << 7) | ((cap) << 14) | ((pro) << 20) | (flag) )

#define NOPROM 0
#define NOFLAG 0

class move
{
public:
	move();	
	~move();
	void printMove();
public:
	int information;
	int score;
};

#endif