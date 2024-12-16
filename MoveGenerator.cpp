#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board) {
    return std::vector<Move>();
}

void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves) {
    generateWhitePawnsMoves(board, moves);
}

void MoveGenerator::generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t pawns = board.getBitboardFromType(board.W_PAWN);
    uint64_t occupied = board.getOccupiedBitBoard();
    for (int i = 0; i < 64; i++) {
        if (pawns = (Board::getBit(occupied, i) & pawns)) {
            std::cout << i << std::endl;
        }
    }
}