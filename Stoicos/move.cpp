#include "move.h"

move::move()
{
}


move::~move()
{
}

void move::printMove()
{
	int mInf = this->information;

	std::cout << char('a' + squareFiles[FROMSQ(mInf)]);
	std::cout << squareRanks[FROMSQ(mInf)] + 1;

	std::cout << char('a' + squareFiles[TOSQ(mInf)]);
	std::cout << squareRanks[TOSQ(mInf)] + 1;

	int pPiece = PROMPIECE(mInf);

	if(pPiece)
	{
		std::cout << " = ";
		char pChar = 'q';
		if (isN(pPiece)) pChar = 'n';
		else if (isRQ(pPiece) && !isBQ(pPiece)) pChar = 'r';
		else if (isBQ(pPiece) && !isRQ(pPiece)) pChar = 'b';
		std::cout << pChar;
	}
}
