#include "position.h"
#include "bitboard.h"
#include "hashkey.h"

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
	int count = 0;
	int sq64 = 0;
	int sq120 = 0;
	int i = 0;

	this->resetPosition();

	while (i < FEN.size())
	{
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
			// skips the parts which are not for the basic position setup
			FEN.erase(0, 1);
			continue;
		case ' ':
			i = FEN.size();
			continue;
		default:
			std::cout << "Critical Error parsing FEN \n"
				<< "Failed to parse: " << FEN.at(0);
			return;
		}
		FEN.erase(0, 1);

		// applies the result gathered in switch
		for (i = 0; i < count; i++)
		{
			sq64 = (rank-1) * 8 + file - 1;
			sq120 = sq64to120[sq64];
			if (piece != EMPTY)
			{
				ASSERT(piece >= P && piece <= k);
				this->pieces[sq120] = piece;
			}
			file++;
		}
	} // end of for loop

	FEN.erase(0, 1);
	this->side = FEN.at(0) == 'w'? WHITE : BLACK;
	FEN.erase(0, 2);

	ASSERT(FEN.size() >= 4);
	for(i = 0; i < 4; i++)
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
		default: std::cout << "Unable to parse FEN castle permission \n "
			<< "Attempted to parse : " << FEN.at(0);
		}
		FEN.erase(0, 1);
	}
	FEN.erase(0, 1);

	ASSERT(this->castlePermission >= 0 && this->castlePermission < 16);
	if(FEN.at(0) != '-')
	{
		// ASCII conversion
		file = FEN[0] - 'a';
		rank = FEN[1] - '1';

		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		this->enPassentSquare = from64to120(file, rank);
	}

	this->positionKey = generatePosKey(this);

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
		this->officiers[i] = 0;
		this->majors[i] = 0;
		this->minors[i] = 0;
		this->pawns[i] = 0ULL;
	}
	for(int i = 0; i < pieceTypes; i++)
	{
		this->amountPieces[i] = 0;
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