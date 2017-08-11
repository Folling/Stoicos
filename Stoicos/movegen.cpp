#include "movegen.h"

enum pawnDirection {
	left = 9,
	right = 11
};

void printMoveList( const moveList* list ) {
	std::cout << "MoveList: \n";
	std::cout << "Total moves: " << list->count << std::endl;

	for (int i = 0; i < list->count; i++) {
		move t = list->moves[i];
		int score = list->moves[i].score;

		std::cout << "Move " << i + 1 << ": ";
		t.printMove();
		std::cout << std::endl << "Score: " << score << std::endl;
	}
}

static void addQuietMove( int mInf, moveList* list ) {
	move t;
	t.information = mInf;
	t.score = 0;
	list->moves.push_back( t );
	list->count++;
} // TODO is this necessary?

static void addCaptureMove( int mInf, moveList* list ) {
	move t;
	t.information = mInf;
	t.score = 0;
	list->moves.push_back( t );
	list->count++;
}

static void addWhitePawnMove( const int from, const int to, const int cap, moveList* list ) {

	ASSERT(pieceValidEmpty(cap));
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if (squareRanks[from] == RANK_7) {
		addCaptureMove( MOVE(from, to, cap, Q, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, N, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, R, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, B, NOFLAG), list );
	} else {
		addCaptureMove( MOVE(from, to, cap, EMPTY, NOFLAG), list );
	}
}

static void addBlackPawnMove( const int from, const int to, const int cap, moveList* list ) {
	ASSERT(pieceValidEmpty(cap));
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if (squareRanks[from] == RANK_2) {
		addCaptureMove( MOVE(from, to, cap, q, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, n, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, r, NOFLAG), list );
		addCaptureMove( MOVE(from, to, cap, b, NOFLAG), list );
	} else {
		addCaptureMove( MOVE(from, to, cap, EMPTY, NOFLAG), list );
	}
}

void generateAllMoves( const position* pos, moveList* list ) {

	ASSERT(pos->checkBoard());

	list->count = 0;

	int side = pos->side;
	bool isWhite = side == WHITE;

	// loop for all pawns
	if (isWhite) {
		for (int i = 0; i < pos->pieceNum[P]; i++) {
			int sq = pos->pList[P][i];
			ASSERT(sqOnBoard(sq));

			// nonCap moves
			if (pos->pieces[sq + pawnRange] == EMPTY) {
				// pawns move bitwise 10 forward as our board is 10 wide
				addWhitePawnMove( sq, sq + pawnRange, EMPTY, list );
				if (squareRanks[sq] == RANK_2 && pos->pieces[sq + psRange] == EMPTY) {
					// pawns can move two squares if they're on the second rank
					addQuietMove( MOVE(sq, sq + psRange, EMPTY, NOPROM, mFlagPS), list );
				}
			}

			// cap moves
			if (sqOnBoard( sq + left ) && pieceColours[pos->pieces[sq + left]] == BLACK) {
				addWhitePawnMove( sq, sq + left, pos->pieces[sq + left], list );
			}
			if (sqOnBoard( sq + right ) && pieceColours[pos->pieces[sq + right]] == BLACK) {
				addWhitePawnMove( sq, sq + right, pos->pieces[sq + right], list );
			}
			// enPassent moves
			if (pos->enPassentSquare != OFF_BOARD) {
				if (sq + left == pos->enPassentSquare) {
					addCaptureMove(MOVE(sq, sq + left, EMPTY, NOPROM, mFlagEP), list);
				}
				if (sq + right == pos->enPassentSquare) {
					addCaptureMove(MOVE(sq, sq + right, EMPTY, NOPROM, mFlagEP), list);
				}
			}
		}
	} else { // black pawns
		for (int i = 0; i < pos->pieceNum[p]; i++) {
			int sq = pos->pList[p][i];
			ASSERT(sqOnBoard(sq));

			// nonCap moves
			if (pos->pieces[sq - pawnRange] == EMPTY) {
				// pawns move bitwise 10 forward as our board is 10 wide
				addBlackPawnMove( sq, sq - pawnRange, EMPTY, list );
				if (squareRanks[sq] == RANK_7 && pos->pieces[sq - psRange] == EMPTY) {
					// pawns can move two squares if they're on the second rank
					addQuietMove( MOVE(sq, sq - psRange, EMPTY, NOPROM, mFlagPS), list );
				}
			}

			// cap moves
			if (sqOnBoard( sq - left ) && pieceColours[pos->pieces[sq - left]] == WHITE) {
				addBlackPawnMove( sq, sq - left, pos->pieces[sq - left], list );
			}
			if (sqOnBoard( sq - right ) && pieceColours[pos->pieces[sq - right]] == WHITE) {
				addBlackPawnMove( sq, sq - right, pos->pieces[sq - right], list );
			}
			// enPassent moves
			if (pos->enPassentSquare != OFF_BOARD) {
				if (sq - left == pos->enPassentSquare) {
					addCaptureMove(MOVE(sq, sq - left, EMPTY, EMPTY, mFlagEP), list);
				}
				if (sq - right == pos->enPassentSquare) {
					addCaptureMove(MOVE(sq, sq - right, EMPTY, EMPTY, mFlagEP), list);
				}
			}
		}
	} // pawns

	// loop for all sliders
	// starts at bishop and goes over rook and queen, but only for the given side
	int piece = (isWhite? B : b);
	for (; piece != (isWhite? K : k); piece++) {
		ASSERT(pieceValid(piece));
		for (int pieceNum = 0; pieceNum < pos->pieceNum[piece]; pieceNum++) {

			int sq = pos->pList[piece][pieceNum];
			ASSERT(sqOnBoard(sq));

			// loops through all possible directions for the respective piece	
			for (int i = 0; i < pieceDirections[piece]; i++) {
				int dir = directions[piece][i];
				int t_sq = sq + dir;

				while (t_sq != OFF_BOARD) {
					if (pos->pieces[t_sq] != EMPTY) {
						// (side ^ 1) == opposite side
						if (pieceColours[pos->pieces[t_sq]] == (side ^ 1)) {
							addCaptureMove( MOVE(sq, t_sq, pos->pieces[t_sq], NOPROM, NOFLAG), list );
						}
						// either the piece is of the same colour or its a capture which means
						// its not a normal move
						break;
					}
					addQuietMove( MOVE(sq, t_sq, EMPTY, NOPROM, NOFLAG), list );
					t_sq += dir;
				}
			}
		}
	}
	// loop for all non-sliders starting with the knight
	piece = (isWhite? N : n);
	for (int i = 0; i < amountNonSliders; i++) {
		ASSERT(pieceValid(piece));

		// loops through all the pieces specified
		for (int pieceNum = 0; pieceNum < pos->pieceNum[piece]; pieceNum++) {
			int sq = pos->pList[piece][pieceNum];
			ASSERT(sqOnBoard(sq));

			// loops through all possible directions for the respective piece	
			for (int j = 0; j < pieceDirections[piece]; j++) {
				int dir = directions[piece][j];
				int t_sq = sq + dir;

				if (t_sq == OFF_BOARD) continue;

				if (pos->pieces[t_sq] != EMPTY) {
					// (side ^ 1) == opposite side
					if (pieceColours[pos->pieces[t_sq]] == (side ^ 1)) {
						addCaptureMove( MOVE(sq, t_sq, pos->pieces[t_sq], NOPROM, NOFLAG), list );
					}
					// either the piece is of the same colour or its a capture which means
					// its not a normal move
					continue;
				}
				addQuietMove( MOVE(sq, t_sq, EMPTY, NOPROM, NOFLAG), list );
			}
		}
		// repeats the loop but this time with the king
		piece = (isWhite? K : k);
	} // non sliders

	// castling
	// we won't need to check whether the square the king moves to is being attacked
	// as that will be done in the makeMove function later
	if (isWhite) {
		// can't castle when in check
		if (!isSquareAttacked( E1, BLACK, pos )) {

			// kingside castling
			if (pos->castlePermission & WHITE_00) {
				// can't caslte if any of the squares are occupied
				if (pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY) {

					// can't castle if any of the squares you'd pass through 
					// are occupied
					if (!isSquareAttacked( F1, BLACK, pos )) {
						addQuietMove( MOVE(E1, G1, EMPTY, NOPROM, mFlagCstl), list );
					}
				}
			}

			//queen side castling
			if (pos->castlePermission & WHITE_000) {
				if (pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY) {
					if (!isSquareAttacked( D1, BLACK, pos )) {
						addQuietMove( MOVE(E1, C1, EMPTY, NOPROM, mFlagCstl), list );
					}
				}
			}
		}
	} else {
		// again, the being in check stuff
		if (!isSquareAttacked( E8, WHITE, pos )) {

			// kingside castling
			if (pos->castlePermission & BLACK_00) {
				// can't caslte if any of the squares are occupied
				if (pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY) {

					// can't castle if any of the squares you'd pass through 
					// are occupied
					if (!isSquareAttacked( F8, WHITE, pos )) {
						addQuietMove( MOVE(E8, G8, EMPTY, NOPROM, mFlagCstl), list );
					}
				}
			}

			//queen side castling
			if (pos->castlePermission & BLACK_000) {
				if (pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY) {
					if (!isSquareAttacked( D8, WHITE, pos )) {
						addQuietMove( MOVE(E8, C8, EMPTY, NOPROM, mFlagCstl), list );
					}
				}
			}
		}
	}
}
