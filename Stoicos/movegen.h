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

static void addWhitePawnMove( const int from, const int to, const int cap, moveList* list);
static void addBlackPawnMove(const int from, const int to, const int cap, moveList* list);

static void addQuietMove(int mInf, moveList* list);
static void addCaptureMove(int mInf, moveList* list);
static void addEnPassentMove(int mInf, moveList* list);

void generateAllMoves(const position* pos, moveList* list);

#endif