#include "perft.h"


QWORD perft(const int depth, position* pos) {
	ASSERT(pos->checkBoard())
	int leafNodes = 0;
	if (depth == 0) return 1;

	moveList l;
	generateAllMoves(pos, &l);
	for (int mNum = 0; mNum < l.count; mNum++) {

		if (!makeMove(l.moves[mNum].information, pos)) {
			continue;
		}		
		leafNodes += perft(depth - 1, pos);
		takeMove(pos);
	}
	return leafNodes;
}
