#ifndef STOICOS_MOVEGEN_H
#define STOICOS_MOVEGEN_H

#include "position.h"
#include "validate.h"
#include "move.h"

struct moveList
{
	std::vector<move> moves;
	int count;
};

void printMoveList(const moveList* list);

void addWhitePawnMove(const position* pos, const int from, const int to, const int cap, moveList* list);
void addBlackPawnMove(const position* pos, const int from, const int to, const int cap, moveList* list);

void addQuietMove(const position* pos, int mInf, moveList* list);
void addCaptureMove(const position* pos, int mInf, moveList* list);
void addEnPassentMove(const position* pos, int mInf, moveList* list);
void generateAllMoves(const position* pos, moveList* list);

#endif