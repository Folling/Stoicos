#ifndef STOICOS_PERFT_H
#define STOICOS_PERFT_H

#include "constants.h"
#include "makemove.h"
#include "movegen.h"

QWORD perft(const int depth, position* pos);

#endif