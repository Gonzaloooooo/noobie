#pragma once
#include <stdint.h>
#include <vector>
#include "Board.h"

class MoveGenerator {
public:
    static const uint64_t w_pawns_starting_pos = 255ULL << 8;
    static const uint64_t b_pawns_starting_pos = 255ULL << 48;
    static const int WHITE = 0;
    static const int BLACK = 1;
    static const int NULL_TYPE = -1;
    static const int PAWN = 0;
    static const int BISHOP = 1;
    static const int KNIGHT = 2;
    static const int TOWER = 3;
    static const int QUEEN = 4;
    static const int KING = 5;
public:
    std::vector<Move> generateMoves(const Board& board, int color);
    void filterMoves(const Board& board, std::vector<Move>& moves);
private:
    static bool isSameDiagonal(int from, int to);
    static bool isKnigthMove(int from, int to);
    static bool isSameRank(int from, int to);
    static bool isSameColumn(int from, int to);
    static void generatePawnMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves);
    static void generateBlackPawnMoves(const Board& board, std::vector<Move>& moves);
    static void generateBishopMoves(const Board& board, std::vector<Move>& moves, int color, bool forQueen);
    static void generateKnightMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateTowerMoves(const Board& board, std::vector<Move>& moves, int color, bool forQueen);
    static void generateQueenMoves(const Board& board, std::vector<Move>& moves, int color);
    static void generateKingMoves(const Board& board, std::vector<Move>& moves, int color);
    // Métodos para la validación de movimientos
    static bool isKingInCheck(const Board& board, int color);
    static bool isPathClear(Move m, uint64_t occupied);
    static bool isHorizontalPathClear(Move m, uint64_t occupied);
    static bool isVerticalPathClear(Move m, uint64_t occupied);
    static bool isDiagonalClear(Move m, uint64_t occupied);
public:
    static bool isLegal(Move move, uint64_t white, uint64_t black, bool whiteToMove);
};

