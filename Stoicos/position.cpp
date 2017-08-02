#include "position.h"

position::position()
{
	
}

position::~position()
{

}

void position::parseFEN(std::string FEN)
{
	ASSERT(FEN != "");
	ASSERT(this != nullptr);

	int rank = RANK_8;
	int file = FILE_A;
	int piece = 0;
	unsigned int count = 0;
	int sq64 = 0;
	int sq120 = 0;
	unsigned int i = 0;

	this->resetPosition();

	while (i < FEN.size())
	{
		count = 1;

		// switches current char and evaluates
		switch (FEN.at(0))
		{
		case 'p': piece = p;
			break;
		case 'P': piece = P;
			break;

		case 'b': piece = b;
			break;
		case 'B': piece = B;
			break;

		case 'n': piece = n;
			break;
		case 'N': piece = N;
			break;

		case 'r': piece = r;
			break;
		case 'R': piece = R;
			break;

		case 'q': piece = q;
			break;
		case 'Q': piece = Q;
			break;

		case 'k': piece = k;
			break;
		case 'K': piece = K;
			break;

		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			piece = EMPTY;

			// extracts value of string
			count = FEN.at(0) - '0';
			break;

		case '/':
			rank--;
			file = FILE_A;
			// skips the '/' and resets it to evaluate the next rank
			FEN.erase(0, 1);
			continue;
		case ' ':
			// the first space indicates that we're done with the position setup
			i = FEN.size();
			continue;
		default:
			std::cout << "Critical Error parsing FEN \n"
				<< "Failed to parse: " << FEN.at(0);
			return;
		}
		FEN.erase(0, 1);

		// applies the result gathered in switch
		for (i = 0; i < count; i++, file++)
		{
			sq64 = (rank) * 8 + file;
			sq120 = sq64to120[sq64];
			if (piece != EMPTY)
			{
				ASSERT(piece >= P && piece <= k);
				this->pieces[sq120] = piece;
			}
		}		
	} // end of for loop

	FEN.erase(0, 1);
	this->side = FEN.at(0) == 'w'? WHITE : BLACK;
	FEN.erase(0, 2);

	ASSERT(FEN.size() >= 4);
	while(FEN.at(0) != ' ')
	{
		switch(FEN.at(0))
		{
		case 'K': this->castlePermission |= WHITE_00;
			break;
		case 'Q': this->castlePermission |= WHITE_000;
			break;
		case 'k': this->castlePermission |= BLACK_00;
			break;
		case 'q': this->castlePermission |= BLACK_000;
			break;
		case '-': break;
		case ' ': break;
		default: std::cout << "Unable to parse FEN castle permission \n "
			<< "Attempted to parse : " << FEN.at(0);
		}
		FEN.erase(0, 1);
	}
	FEN.erase(0, 1);

	ASSERT(this->castlePermission >= 0 && this->castlePermission < 16);
	if(FEN.at(0) != '-' && FEN.at(0) != ' ')
	{
		// ASCII conversion
		file = FEN[0] - 'a';
		rank = FEN[1] - '1';

		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		this->enPassentSquare = from64to120(file, rank);
	}
	else this->enPassentSquare = OFF_BOARD;

	this->generateKey();

	this->updatePieceList();
}

void position::resetPosition()
{
	for(int i = 0; i < amountSquares; i++)
	{
		this->pieces[i] = OFF_BOARD;
	}
	for(int i = 0; i < relevantSquares; i++)
	{
		this->pieces[sq64to120[i]] = EMPTY;
	}
	for(int i = 0; i < playerTypes; i++)
	{
		this->officers[i] = 0;
		this->majors[i] = 0;
		this->minors[i] = 0;
		this->pawns[i] = 0ULL;
	}
	for(int i = 0; i < pieceTypes; i++)
	{
		this->pieceNum[i] = 0;
	}

	this->kingSquares[WHITE] = this->kingSquares[BLACK] = OFF_BOARD;

	this->side = BOTH;
	this->enPassentSquare = OFF_BOARD;
	this->fiftyMoveCount = 0;

	this->ply = 0;
	this->historyPly = 0;

	this->castlePermission = 0;
	this->positionKey = EMPTY_KEY;

	this->history.clear();
}

void position::generateKey()
{
	// take in all necessary parameters to turn a position into a key
	int piece = 0;
	Key finalKey = 0ULL;
	for (int sq = 0; sq < relevantSquares; sq++)
	{
		piece = this->pieces[sq64to120[sq]];
		if (piece != EMPTY)
		{
			// validates piece
			ASSERT(piece >= P && piece <= k)
				finalKey ^= pieceKeys[piece][sq];
		}
	}
	if (this->side == WHITE)
	{
		finalKey ^= sideKey;
	}
	if (this->enPassentSquare != OFF_BOARD)
	{
		// validates en-Passent square
		ASSERT(this->enPassentSquare >= 0 && this->enPassentSquare < amountSquares)

			finalKey ^= pieceKeys[EMPTY][this->enPassentSquare];
	}

	// validates castle Permission
	ASSERT(this->castlePermission >= 0 && this->castlePermission < castleOptions);

	finalKey ^= castleKeys[this->castlePermission];

	this->positionKey = finalKey;
}

void position::printPosition() const
{
	int sq = 0;
	int piece = 0;

	std::cout << std::endl;

	// prints all rank numbers from top to bottom
	// prints the corresponding pieces after changing them from the 64 to 120 notation

	for(int r = RANK_8; r >= RANK_1; r--)
	{
		std::cout << std::setw(3) << rankChars[r];
		for(int f = FILE_A; f <= FILE_H; f++)
		{
			sq = from64to120(f, r);
			piece = this->pieces[sq];
			std::cout << std::setw(3) << pieceChars[piece];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::setw(3) << " ";
	for(int f = FILE_A; f <= FILE_H; f++)
	{
		std::cout << std::setw(3) << fileChars[f];
	}
	std::cout << std::endl << sideChars[this->side] << std::endl;
	if(this->enPassentSquare == 99)
	{
		std::cout << "No en-passent square possible\n";
	}
	else std::cout << evaluateEnpassent(this->enPassentSquare) << std::endl;
	std::cout << (this->castlePermission & WHITE_00  ? 'K' : '-');
	std::cout << (this->castlePermission & WHITE_000 ? 'Q' : '-');
	std::cout << (this->castlePermission & BLACK_00  ? 'k' : '-');
	std::cout << (this->castlePermission & BLACK_000 ? 'q' : '-')
			  << std::endl;
	std::cout << this->positionKey << std::endl;
}

void position::updatePieceList()
{
	for(int i = 0; i < amountSquares; i++)
	{
		int piece = this->pieces[i];
		if(piece != OFF_BOARD && piece != EMPTY)
		{
			int colour = pieceColours[piece];
			if (::officers[piece]  == true) this->officers[colour]++;
			if (minPieces[piece] == true) this->minors[colour]++;
			if (majPieces[piece] == true) this->majors[colour]++;

			this->material[colour] += pieceValues[piece];

			// piece list
			this->pList[piece][this->pieceNum[piece]] = i;
			this->pieceNum[piece]++;

			if(piece == P || piece == p)
			{
				int currSquare = sq120to64[i];
				SETBIT(this->pawns[piece == P? WHITE : BLACK], currSquare);
				SETBIT(this->pawns[BOTH], currSquare);
			}
			else if (piece == K) this->kingSquares[WHITE] = i;
			else if (piece == k) this->kingSquares[BLACK] = i;			
		}
	}
}

bool position::checkBoard()
{
	int t_pieceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0 };
	int t_officers[2] = { 0, 0 };
	int t_majors[2] = { 0, 0 };
	int t_minors[2] = { 0, 0 };
	int t_material[2] = { 0, 0 };

	QWORD t_pawns[3] = { 0ULL, 0ULL, 0ULL };

	t_pawns[WHITE] = this->pawns[WHITE];
	t_pawns[BLACK] = this->pawns[BLACK];
	t_pawns[BOTH] = this->pawns[BOTH];


	// validates piece list
	for(int t_piece = P; t_piece <= k; t_piece++)
	{
		for(int t_num = 0; t_num < this->pieceNum[t_piece]; t_num++)
		{
			int sq120 = this->pList[t_piece][t_num];
			ASSERT(this->pieces[sq120] == t_piece);
		}
	}

	// validate piece counter and other counters;
	for( int sq64 = 0; sq64 < relevantSquares; sq64++)
	{
		int sq120 = sq64to120[sq64];
		int t_piece = this->pieces[sq120];
		t_pieceNum[t_piece]++;
		int colour = pieceColours[t_piece];
		if (::officers[t_piece] == true) t_officers[colour]++;
		if (majPieces[t_piece] == true) t_majors[colour]++;
		if (minPieces[t_piece] == true) t_minors[colour]++;

		t_material[colour] += pieceValues[t_piece];
	}

	// validates the amount of pieces
	for(int t_piece = P; t_piece <= k; t_piece++)
	{
		ASSERT(t_pieceNum[t_piece] == this->pieceNum[t_piece]);
	}

	// validates amount of pawns
	int pcount = countBits(t_pawns[WHITE]);
	ASSERT(pcount == this->pieceNum[P]);
	pcount = countBits(t_pawns[BLACK]);
	ASSERT(pcount == this->pieceNum[p]);
	pcount = countBits(t_pawns[BOTH]);
	ASSERT(pcount == this->pieceNum[P] + this->pieceNum[p]);

	// check bitboards squares
	while(t_pawns[WHITE])
	{
		int sq64 = popBit(&t_pawns[WHITE]);
		ASSERT(this->pieces[sq64to120[sq64] == P]);
	}
	while (t_pawns[BLACK])
	{
		int sq64 = popBit(&t_pawns[BLACK]);
		ASSERT(this->pieces[sq64to120[sq64] == p]);
	}
	while (t_pawns[BOTH])
	{
		int sq64 = popBit(&t_pawns[BOTH]);
		ASSERT(this->pieces[sq64to120[sq64]] == P || this->pieces[sq64to120[sq64]] == p);
	}

	// asserts all the piece amounts are correct

	ASSERT(t_material[WHITE] == this->material[WHITE]);
	ASSERT(t_material[BLACK] == this->material[BLACK]);

	ASSERT(t_minors[WHITE] == this->minors[WHITE]);
	ASSERT(t_minors[BLACK] == this->minors[BLACK]);

	ASSERT(t_majors[WHITE] == this->majors[WHITE]);
	ASSERT(t_majors[BLACK] == this->majors[BLACK]);

	ASSERT(t_officers[WHITE] == this->officers[WHITE]);
	ASSERT(t_officers[BLACK] == this->officers[BLACK]);

	ASSERT(this->side == WHITE || this->side == BLACK);

	Key tempKey = this->positionKey;
	this->generateKey();

	ASSERT(tempKey == this->positionKey);

	// en passent squares can only exist on the 6th or the 3rd rank, if at all
	ASSERT(this->enPassentSquare == OFF_BOARD 
		|| squareRanks[this->enPassentSquare] == RANK_6 && this->side == WHITE
		|| squareRanks[this->enPassentSquare] == RANK_3 && this->side == BLACK
	);

	// validates king positions
	ASSERT(this->pieces[this->kingSquares[WHITE] == K]);
	ASSERT(this->pieces[this->kingSquares[BLACK] == k]);

	return true;
}