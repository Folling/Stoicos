#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <chrono>

#include "bitboard.h"
#include "position.h"
#include "movegen.h"
#include "move.h"
#include "attack.h"
#include "init.h"
#include "makemove.h"
#include "perft.h"

void printConvertArrays();
void printMove(int move);

int main()
{
	initAll();
	position blubb;
	moveList l;

	blubb.parseFEN(START_FEN);

	QWORD startingTime = _Query_perf_counter();
	std::cout << perft(4, &blubb) << std::endl;
	QWORD endingTime = _Query_perf_counter();


	std::cout << "Time needed was: " << (endingTime - startingTime)*1000.0 / _Query_perf_frequency()
		<< " milliseconds" << std::endl;
	_getch();
}

// redundant function for debugging
// simply prints the arrays which store convert information about the
// 120 to 64 board formats
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

// prints the information about a move
// 27 because there are 27 relevant bits in the moveinfo
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