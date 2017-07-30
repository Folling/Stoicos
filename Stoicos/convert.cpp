#include "convert.h"

int from64to120(int file, int rank)
{
	// simple conversion formular
	return 21 + file + 10 * rank;
}