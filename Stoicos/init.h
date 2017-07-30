#ifndef STOICOS_INIT_H
#define STOICOS_INIT_H

#include "hashkey.h"
#include "bitboard.h"
#include "masks.h"
#include "constants.h"
#include "position.h"
#include "convert.h"

void initAll();
void init120to64();
void initMasks();
void initHashkeys();

#endif