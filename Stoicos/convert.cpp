#include "convert.h"

int from64to120(int file, int rank)
{
	// simple conversion formular
	return 21 + file + 10 * rank;
}

std::string evaluateEnpassent(int input)
{
	input = sq120to64[input];
	int rest = input % 8;
	input /= 8;
	std::string result;
	result.push_back(fileChars[rest]);
	result.push_back(rankChars[input]);

	return result;
}