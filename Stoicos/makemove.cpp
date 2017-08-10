#include "makemove.h"

static void clearPiece(const int sq, position* pos) {
	ASSERT(sqOnBoard(sq));

	int piece = pos->pieces[sq];
	ASSERT(pieceValid(piece));

	int colour = pieceColours[piece];
	HASH_PIECE(piece, sq);

	int t_pieceNum = -1;

	// removes information of the piece from the general matieral and piece array
	pos->pieces[sq] = EMPTY;
	pos->material[colour] -= pieceValues[piece];

	// removes information of the piece from the specific material arrays
	// if a piece is an officer but not a major it has to be a minor
	if(officers[piece] == true) {
		pos->officers[colour]--;
		if(majPieces[piece] == true) {
			pos->majors[colour]--;
		} else {
			pos->minors[colour]--;
		}
	} else {
		CLRBIT(pos->pawns[colour], sq120to64[sq]);
		CLRBIT(pos->pawns[BOTH], sq120to64[sq]);
	}
	for(int i = 0; i < pos->pieceNum[piece]; i++) {
		if(pos->pList[piece][i] == sq) {
			t_pieceNum = i;
			break;
		}
	}
	ASSERT(t_pieceNum != -1);
	pos->pieceNum[piece]--;
	// swaps last entry in piece list of some piece with the piece to be removed and decrements
	// the pList for that piece so the last part of the pList is unaccessable and will be overridden
	pos->pList[piece][t_pieceNum] = pos->pList[piece][pos->pieceNum[piece]];
}

static void addPiece(const int sq, position* pos, const int piece) {
	// this whole function basically does the opposite of what clearPiece did
	// so just check that commenting and apply the opposite
	
	ASSERT(pieceValid(piece));
	ASSERT(sqOnBoard(sq));

	int colour = pieceColours[piece];

	HASH_PIECE(piece, sq);
	pos->pieces[sq] = piece;
	if(officers[piece] == true) {
		pos->officers[colour]++;
		if(majPieces[piece] == true) {
			pos->majors[colour]++;
		} else {
			pos->minors[colour]++;
		}
	} else {
		SETBIT(pos->pawns[colour], sq120to64[sq]);
		SETBIT(pos->pawns[BOTH], sq120to64[sq]);
	}
	pos->material[colour] += pieceValues[piece];
	// increases the pos->pieceNum by one, effectively making one more square 
	// accessable and immediately assigns the newborn piece to it
	pos->pList[piece][pos->pieceNum[piece]++] = sq;
}

static void movePiece( const int from, const int to, position* pos) {
	ASSERT(sqOnBoard(from))
	ASSERT(sqOnBoard(to));
	int piece = pos->pieces[from];
	int colour = pieceColours[piece];

	// basic variable to check whether the move was executed successful
	#ifdef DEBUG 
		int t_pieceNum = false;
	#endif
	// switch the square the piece is on : this is the same as moving it
	HASH_PIECE(piece, from);
	pos->pieces[from] = EMPTY;

	HASH_PIECE(piece, to);
	pos->pieces[to] = piece;

	if(!officers[piece]) {
		CLRBIT(pos->pawns[colour], sq120to64[from]);
		CLRBIT(pos->pawns[BOTH], sq120to64[from]);
		SETBIT(pos->pawns[colour], sq120to64[to]);
		SETBIT(pos->pawns[BOTH], sq120to64[to]);
	}

	for(int i = 0; i < pos->pieceNum[piece]; i++) {
		if(pos->pList[piece][i] == from) {
			pos->pList[piece][i] = to;
		}
		#ifdef DEBUG
			t_pieceNum = true;
		#endif
		break;
	}
	ASSERT(t_pieceNum);
}