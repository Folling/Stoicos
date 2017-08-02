#include <iostream>
#include <iomanip>
#include <conio.h>
#include <chrono>

#include "bitboard.h"
#include "position.h"
#include "attack.h"
#include "init.h"

void printConvertArrays();

int main()
{
	initAll();

	position blubb;

	QWORD startingTime = _Query_perf_counter();

	blubb.parseFEN("8/8/8/8/4K3/8/8/8 w - - 0 1");
	blubb.checkBoard();
	blubb.printPosition();


	QWORD endingTime = _Query_perf_counter();
	std::cout << "Time needed was : " << (endingTime - startingTime)*1000000.0 / _Query_perf_frequency()
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