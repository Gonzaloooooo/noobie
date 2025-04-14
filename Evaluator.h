#pragma once
#include <intrin.h>
#include "MoveGenerator.h"

class Evaluator
{
public: 
    // Constante para evaluar una posici�n
    static const int PAWN_VALUE = 100;
    static const int KNIGHT_VALUE = 320;
    static const int BISHOP_VALUE = 330;
    static const int ROOK_VALUE = 500;
    static const int QUEEN_VALUE = 900;
    static const int KING_VALUE = 20000;

	static int negamax(Board& board, int depth, int alpha, int beta);
	static int evaluate(Board& board);
};

