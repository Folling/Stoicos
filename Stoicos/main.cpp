#include <iostream>
#include <iomanip>
#include <conio.h>

#include "bitboard.h"
#include "position.h"
#include "init.h"

void printConvertArrays();

int main()
{
	initAll();
	position blubb;
	blubb.parseFEN(START_FEN);
	std::cout << blubb.positionKey << std::endl;
	position blobb;
	blubb.parseFEN(TEST1_FEN);
	std::cout << blubb.positionKey << std::endl;
	blubb.parseFEN(START_FEN);
	std::cout << blubb.positionKey << std::endl;
	_getch();
}

// redundant function for debugging
void printConvertArrays()
{
	for (int i = 0; i < amountSquares; i++)
	{
		if (i % 10 == 0) std::cout << std::endl;
		std::cout << std::setw(5) << sq120to64[i];
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < relevantSquares; i++)
	{
		if (i % 8 == 0) std::cout << std::endl;
		std::cout << std::setw(5) << sq64to120[i];
	}
}