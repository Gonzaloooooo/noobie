#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board, int color) {
    std::vector<Move> moves;
    generatePawnMoves(board, moves, color);
    generateBishopMoves(board, moves, color);
    return moves;
}

bool MoveGenerator::isSameDiagonal(int from, int to) {
    int from_rank = from / 8;
    int from_col = from % 8;

    int to_rank = to / 8;
    int to_col = to % 8;

    return std::abs(from_rank - to_rank) == std::abs(from_col - to_col);
}

void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves, int color) {
    if (color == WHITE) {
        generateWhitePawnsMoves(board, moves);
    } else {
        generateBlackPawnMoves(board, moves);
    }
}

void MoveGenerator::generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t w_pawns = board.getBitboardFromType(board.W_PAWN);

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = Board::getBit(w_pawns, from);
        if (from_mask & w_pawns) {
            int from_rank = from / 8;
            int from_col = from % 8;
            
            Move fwd_1{ from, from + 8, -1 };
            moves.push_back(fwd_1);

            if (from_rank == 1) {
                Move fwd_2{ from, from + 16, -1 };
                moves.push_back(fwd_2);
            }
            if (from_col < 7) {
                Move right{ from, from + 9, -1 };
                moves.push_back(right);
            }
            if (from_col > 0) {
                Move left{ from, from + 7, -1 };
                moves.push_back(left);
            }
        }
    }
}

void MoveGenerator::generateBlackPawnMoves(const Board& board, std::vector<Move>& moves){
    uint64_t b_pawns = board.getBitboardFromType(board.B_PAWN);

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = Board::getBit(b_pawns, from);
        if (from_mask & b_pawns) {
            int from_rank = from / 8;
            int from_col = from % 8;

            Move fwd_1{ from, from - 8, -1 };
            moves.push_back(fwd_1);

            if (from_rank == 6) {
                Move fwd_2{ from, from - 16, -1 };
                moves.push_back(fwd_2);
            }

            if (from_col < 7) {
                Move right{ from, from - 7, -1 };
                moves.push_back(right);
            }

            if (from_col > 0) {
                Move left{ from, from - 9, -1 };
                moves.push_back(left);
            }
        }
    }
}

void MoveGenerator::generateBishopMoves(const Board& board, std::vector<Move>& moves, int color) {
    uint64_t bishops;

    if (color == WHITE) {
        bishops = board.getBitboardFromType(Board::W_BISHOP);
    } else if (color == BLACK) {
        bishops = board.getBitboardFromType(Board::B_BISHOP);
    }

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & bishops) {
            for (int to = from + 9; to < 64; to += 9) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, -1 };
                moves.push_back(m);
            }
            for (int to = from - 9; to >= 0; to -= 9) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, -1 };
                moves.push_back(m);
            }
            for (int to = from + 7; to < 64; to += 7) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, -1 };
                moves.push_back(m);
            }
            for (int to = from - 7; to >= 0; to -= 7) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, -1 };
                moves.push_back(m);
            }
        }
    }
}
