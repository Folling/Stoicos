#include "bitboard.h"

void printBitboard(Bitboard bb)
{
	QWORD toShift = 1ULL;
	int square = 0;
	int square64 = 0;

	std::cout << std::endl;

	// shift through all the squares of the boards once and prints "X"
	// if it contains a selected piece
	// and "-" if it doesn't.
	for(int r = RANK_8; r >= RANK_1; r--)
	{
		for(int f = FILE_A; f <= FILE_H; f++)
		{
			square = from64to120(f, r);
			square64 = sq120to64[square];
			if ((toShift << square64) & bb) std::cout << "X";
			else std::cout << "-";

		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

int popBit(Bitboard* bb)
{
	// sets the least signficant bit to 0 and returns the index of said bit
	Bitboard temp = *bb ^ (*bb - 1);
	unsigned int fold = static_cast<unsigned>((temp & 0xffffffff) ^ (temp >> 32));
	*bb &= (*bb - 1);
	return BitTable[(fold * 0x783a9b23) >> 26];
}

int countBits(Bitboard bb)
{
	int r;
	for (r = 0; bb; r++, bb &= bb - 1);
	return r;
}