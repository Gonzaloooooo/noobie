#pragma once
#include <stdint.h>
#include <vector>
#include "Board.h"

class Board;

struct Move {
    int from;
    int to;
    char promotion;
};

class MoveGenerator {
public:
    std::vector<Move> generateMoves(const Board& board);
private:
    static void generatePawnMoves(const Board& board, std::vector<Move>& moves);
    static void generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves);
    static void getWhitePawnMoves(const Board& board, std::vector<Move>, int pawnIndx);
};

