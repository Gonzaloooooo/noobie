#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board, int color) {
    std::vector<Move> moves;
    generatePawnMoves(board, moves);
    return moves;
}

void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves) {
    generateBlackPawnMoves(board, moves);
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

void MoveGenerator::generateBlackPawnMoves(const Board& board, std::vector<Move>& moves){
    uint64_t b_pawns = board.getBitboardFromType(board.B_PAWN);
    uint64_t occupied = board.getOccupiedBitBoard();
    uint64_t black = board.getBlackBitBoard();

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = Board::getBit(occupied, from);
        if (from_mask & b_pawns) {
            uint64_t to_forward = from_mask >> 8;
            uint64_t to_forward_2 = from_mask >> 16;
            if (!(to_forward_2 & occupied) && (from_mask & MoveGenerator::b_pawns_starting_pos)) { //2 squares forward
                Move m = { from , from - 16, -1 };
                moves.push_back(m);
            }
            Move m = { from, from - 8, -1 };
            moves.push_back(m);
        }
    }
}

void MoveGenerator::generateBishopMoves(const Board& board, std::vector<Move>& moves, int color) {
    uint64_t bishops;
    uint64_t opposite;
    uint64_t occupied = board.getOccupiedBitBoard();

    if (color == WHITE) {
        bishops = board.getBitboardFromType(Board::W_BISHOP);
        opposite = board.getBlackBitBoard();
    } else if (color == BLACK) {
        bishops = board.getBitboardFromType(Board::B_BISHOP);
        opposite = board.getWhiteBitBoard();
    }

    
    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & bishops) {
            for (int to = from + 9; to < 64; to += 9) {
                uint64_t to_mask = to;
                if ((to_mask | occupied) | ~opposite) {

                }
            }
        }
    }

}
