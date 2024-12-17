#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board) {
    std::vector<Move> moves;
    generatePawnMoves(board, moves);
    return moves;
}

void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves) {
    generateWhitePawnsMoves(board, moves);
}

void MoveGenerator::generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t w_pawns = board.getBitboardFromType(board.W_PAWN);
    uint64_t occupied = board.getOccupiedBitBoard();
    uint64_t white = board.getWhiteBitBoard();

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = Board::getBit(occupied, from);
        if (from_mask & w_pawns) {
            //std::cout << from << std::endl;
            uint64_t to_forward = from_mask << 8;
            uint64_t to_forward_2 = from_mask << 16;
            if (!(to_forward & occupied)) { //1 square forward
                if (!(to_forward_2 & occupied) && (from_mask & MoveGenerator::w_pawns_starting_pos)) { //2 squares forward
                    Move m = { from , from + 16, -1 };
                    moves.push_back(m);
                }
                Move m = {from, from+8, -1};
                moves.push_back(m);
            }
        }
    }
}