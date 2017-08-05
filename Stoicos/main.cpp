#include <iostream>
#include <iomanip>
#include <conio.h>
#include <chrono>

#include "bitboard.h"
#include "position.h"
#include "movegen.h"
#include "move.h"
#include "attack.h"
#include "init.h"

void printConvertArrays();
void printMove(int move);

int main()
{
	QWORD startingTime = _Query_perf_counter();
	initAll();

	position blubb;
	moveList l;

	blubb.parseFEN("rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b - e3 0 1");
	blubb.checkBoard();
	blubb.printPosition();
	std::cout << std::endl;

	

	generateAllMoves(&blubb, &l);

	
	
	printMoveList(&l);
	QWORD endingTime = _Query_perf_counter();
	std::cout << "Time needed was: " << (endingTime - startingTime)*1000000.0 / _Query_perf_frequency()
		<< " microseconds" << std::endl;
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

void printMove(int move)
{
	for(int i = 27; i>=0; i--)
	{
		if (1 << i & move) std::cout << "1";
		else std::cout << "0";
		if (i % 4 == 0) std::cout << " ";
	}
	std::cout << std::endl;
}