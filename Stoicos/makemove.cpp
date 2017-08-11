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
	if (officers[piece] == true) {
		pos->officers[colour]--;
		if (majPieces[piece] == true) {
			pos->majors[colour]--;
		}
		else {
			pos->minors[colour]--;
		}
	}
	else {
		CLRBIT(pos->pawns[colour], sq120to64[sq]);
		CLRBIT(pos->pawns[BOTH], sq120to64[sq]);
	}
	for (int i = 0; i < pos->pieceNum[piece]; i++) {
		if (pos->pList[piece][i] == sq) {
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
	if (officers[piece] == true) {
		pos->officers[colour]++;
		if (majPieces[piece] == true) {
			pos->majors[colour]++;
		}
		else {
			pos->minors[colour]++;
		}
	}
	else {
		SETBIT(pos->pawns[colour], sq120to64[sq]);
		SETBIT(pos->pawns[BOTH], sq120to64[sq]);
	}
	pos->material[colour] += pieceValues[piece];
	// increases the pos->pieceNum by one, effectively making one more square 
	// accessable and immediately assigns the newborn piece to it
	pos->pList[piece][pos->pieceNum[piece]++] = sq;
}

static void movePiece(const int from, const int to, position* pos) {
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

	if (!officers[piece]) {
		CLRBIT(pos->pawns[colour], sq120to64[from]);
		CLRBIT(pos->pawns[BOTH], sq120to64[from]);
		SETBIT(pos->pawns[colour], sq120to64[to]);
		SETBIT(pos->pawns[BOTH], sq120to64[to]);
	}

	for (int i = 0; i < pos->pieceNum[piece]; i++) {
		if (pos->pList[piece][i] == from) {
			pos->pList[piece][i] = to;
#ifdef DEBUG
			t_pieceNum = true;
#endif
			break;
		}
	}
	ASSERT(t_pieceNum);
}

bool makeMove(const int move, position* pos) {

	ASSERT(pos->checkBoard());

	const int from = FROMSQ(move);
	const int to TOSQ(move);
	const int side = pos->side;
	const bool isWhite = side == WHITE;
	const int hPly = pos->historyPly;

	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));
	ASSERT(validSide(side));

	// does the move select a piece?
	ASSERT(pieceValid(pos->pieces[from]));

	pos->history[hPly].positionKey = pos->positionKey;

	// en passent captures don't capture the piece at which the enemy pawn is
	// but rather one square above (white moves) or below (black moves) is

	if (move & mFlagEP) {
		if (isWhite) {
			clearPiece(to - 10, pos);
		}
		else {
			clearPiece(to + 10, pos);
		}
	}
	else if (move & mFlagCstl) {
		// switches which rook has to move, as the king has obviously already moved
		switch (to) {
		case C1: movePiece(A1, D1, pos);
			break;
		case C8: movePiece(A8, D8, pos);
			break;
		case G1: movePiece(H1, F1, pos);
			break;
		case G8: movePiece(H8, F8, pos);
			break;
		default: ASSERT(false);
		}
	}
	// an en passent square only lasts for one move
	if (pos->enPassentSquare != OFF_BOARD) HASH_EP;

	// hashes out caslte perm
	HASH_CA;

	// stores position in history
	pos->history[hPly].move = move;
	pos->history[hPly].fiftyMove = pos->fiftyMoveCount;
	pos->history[hPly].enPas = pos->enPassentSquare;
	pos->history[hPly].castlePerm = pos->castlePermission;

	// updates castle permission
	pos->castlePermission &= castlePerm[from];
	pos->castlePermission &= castlePerm[to];

	// temporary clears en passent square
	pos->enPassentSquare = OFF_BOARD;

	// hashes in castle perm
	HASH_CA;

	// deals with the case that the move captured a piece
	int captured = CAPPIECE(move);
	pos->fiftyMoveCount++;
	if (captured != EMPTY) {
		ASSERT(pieceValid(captured));
		clearPiece(to, pos);
		pos->fiftyMoveCount = 0;
	}
	pos->historyPly++;
	pos->ply++;

	if (piecePawn[pos->pieces[from]]) {
		pos->fiftyMoveCount = 0;
		// en passent square will be set if it is a pawnstart
		if (move & mFlagPS) {
			if (isWhite) {
				// en passent squares are always the square the pawn skips 
				// in a pawnstart
				pos->enPassentSquare = to - 10;
				ASSERT(squareRanks[pos->enPassentSquare] == RANK_3);
			}
			else {
				pos->enPassentSquare = to + 10;
				ASSERT(squareRanks[pos->enPassentSquare] == RANK_6);
			}
			HASH_EP;
		}
	}

	movePiece(from, to, pos);

	//deals with promotion
	const int prom = PROMPIECE(move);
	if (prom != NOPROM) {
		ASSERT(pieceValid(prom));
		ASSERT(!piecePawn[prom]);
		clearPiece(to, pos);
		addPiece(to, pos, prom);
	}

	// moves kingSquare if you moved a king
	if (isKing(pos->pieces[to])) {
		pos->kingSquares[side] = to;
	}

	// changes side
	pos->side ^= 1;
	HASH_SIDE;

	ASSERT(pos->checkBoard());

	// needs to be down here due to pinned pieces and other moves involving a piece other than the
	// king that would still put him in check
	if (isSquareAttacked(pos->kingSquares[side], pos->side, pos)) {
		takeMove(pos);
		return false;
	}

	return true;
}

void takeMove(position* pos) {
	ASSERT(pos->checkBoard());

	pos->historyPly--;
	pos->ply--;

	const int hPly = pos->historyPly;

	int move = pos->history[hPly].move;
	int from = FROMSQ(move);
	int to = TOSQ(move);

	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	// de- and resets the en passent square as well as
	// the castling permision of the position 
	if (pos->enPassentSquare != OFF_BOARD) HASH_EP;
	HASH_CA;

	pos->castlePermission = pos->history[hPly].castlePerm;
	pos->fiftyMoveCount = pos->history[hPly].fiftyMove;
	pos->enPassentSquare = pos->history[hPly].enPas;

	if (pos->enPassentSquare != OFF_BOARD) HASH_EP;

	HASH_CA;
	pos->side ^= 1;
	HASH_SIDE;

	// readds pawn in case of en passent move
	if (move & mFlagEP) {
		if (pos->side == WHITE) {
			addPiece(to - 10, pos, p);
		}
		else {
			addPiece(to + 10, pos, P);
		}
	}
	else if (move & mFlagCstl) {
		switch (to) {
		case C1: movePiece(D1, A1, pos);
			break;
		case C8: movePiece(D8, A8, pos);
			break;
		case G1: movePiece(F1, H1, pos);
			break;
		case G8: movePiece(F8, H8, pos);
			break;
		default:
			ASSERT(false);
		}
	}
	movePiece(to, from, pos);
	if (isKing(pos->pieces[from])) {
		pos->kingSquares[pos->side] = from;
	}

	// redoes capture in case there was one
	int cap = CAPPIECE(move);
	if (cap != EMPTY) {
		ASSERT(pieceValid(cap));
		addPiece(to, pos, cap);
	}

	// redoes promotion, in case there was one
	int prom = PROMPIECE(move);
	if (prom != EMPTY) {
		ASSERT(pieceValid(prom));
		ASSERT(!piecePawn[prom]);
		clearPiece(from, pos);
		addPiece(from, pos, (pieceColours[prom] == WHITE ? P : p));
	}
	ASSERT(pos->checkBoard());
}