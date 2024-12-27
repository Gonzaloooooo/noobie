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
    static const uint64_t w_pawns_starting_pos = 255ULL << 8;
    static const uint64_t b_pawns_starting_pos = 255ULL << 48;
    static const int WHITE = 0;
    static const int BLACK = 1;
public:
    std::vector<Move> generateMoves(const Board& board, int color);
private:
    static void generatePawnMoves(const Board& board, std::vector<Move>& moves);
    static void generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves);
    static void generateBlackPawnMoves(const Board& board, std::vector<Move>& moves);

    static void generateBishopMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateKnightMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateTowerMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateQueenMoves(const Board& board, std::vector<Move>& moves, int color);
};

