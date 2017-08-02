#ifndef STOICOS_INIT_H
#define STOICOS_INIT_H

#include "bitboard.h"
#include "masks.h"
#include "constants.h"
#include "position.h"
#include "convert.h"

void initAll();
void init120to64();
void initMasks();
void initHashkeys();
void initSquareIdentifiers();

#endif