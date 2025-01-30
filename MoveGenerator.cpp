#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board, int color) 
{
    std::vector<Move> moves;
    generatePawnMoves(board, moves, color);
    generateBishopMoves(board, moves, color);
    generateKnightMoves(board, moves, color);
    generateTowerMoves(board, moves, color);
    generateKingMoves(board, moves, color);
    return moves;
}

bool MoveGenerator::isSameDiagonal(int from, int to) 
{
    int from_rank = from / 8;
    int from_col = from % 8;

    int to_rank = to / 8;
    int to_col = to % 8;

    return std::abs(from_rank - to_rank) == std::abs(from_col - to_col);
}

bool MoveGenerator::isKnigthMove(int from, int to) 
{
    bool isKnightMove = false;
    if (!(to > 63 || to < 0)) {
        int from_rank = from / 8;
        int from_col = from % 8;

        int to_rank = to / 8;
        int to_col = to % 8;

        int rank_diff = std::abs(from_rank - to_rank);
        int col_diff = std::abs(from_col - to_col);

        if ((rank_diff == 1 && col_diff == 2) || rank_diff == 2 && col_diff == 1) {
            isKnightMove = true;
        }
    }
    return isKnightMove;
}

void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves, int color) 
{
    if (color == WHITE) {
        generateWhitePawnsMoves(board, moves);
    } else {
        generateBlackPawnMoves(board, moves);
    }
}

void MoveGenerator::generateWhitePawnsMoves(const Board& board, std::vector<Move>& moves) 
{
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

void MoveGenerator::generateBlackPawnMoves(const Board& board, std::vector<Move>& moves)
{
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

void MoveGenerator::generateBishopMoves(const Board& board, std::vector<Move>& moves, int color) 
{
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

void MoveGenerator::generateKnightMoves(const Board& board, std::vector<Move>& moves, int color) 
{
    uint64_t knight;
    if (color == WHITE) {
        knight = board.getBitboardFromType(Board::W_KNIGHT);
    }
    else if (color == BLACK) {
        knight = board.getBitboardFromType(Board::B_KNIGHT);
    }

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask= 1ULL << from;
        if (from_mask & knight) {
            int from_rank = from / 8;
            int from_col = from % 8;

            for (int move : {6, 10, 15, 17, -6, -10, -15, -17}) {
                int to = from + move;
                if (isKnigthMove(from, to)) {
                    Move m{ from, to, -1 };
                    moves.push_back(m);
                }
            }

        }
    }
}

void MoveGenerator::generateQueenMoves(const Board& board, std::vector<Move>& moves, int color) 
{
    uint64_t queen;
    Board b;
    MoveGenerator moveGen;

    if (color == WHITE) {
        queen = board.getBitboardFromType(Board::W_QUEEN);
        b = new Board(0, queen, 0, queen, queen, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (color == BLACK) {
        queen = board.getBitboardFromType(Board::B_QUEEN);
        b = new Board(0, 0, 0, 0, 0, 0, 0, queen, 0, queen, queen, 0);
    }
    std::vector<Move> m = moveGen.generateMoves(b, color);

    moves.insert(moves.end(), m.begin(), m.end());
}

void MoveGenerator::generateTowerMoves(const Board& board, std::vector<Move>& moves, int color) 
{
    uint64_t tower;
    if (color == WHITE) {
        tower = board.getBitboardFromType(Board::W_TOWER);
    } else if(color == BLACK) {
        tower = board.getBitboardFromType(Board::B_TOWER);
    }

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & tower) {
            // Upward moves
            for (int to = from + 8; to < 64; to+=8) {
                Move m{from, to, -1};
                moves.push_back(m);
            }
            // Downward moves
            for (int to = from - 8; to >= 0; to-=8) {
                Move m{ from, to, -1 };
                moves.push_back(m);
            }
            // Right moves
            for (int to = from + 1; to < 64; to++) {
                int from_rank = from / 8;
                int to_rank = to / 8;
                if (from_rank == to_rank) {
                    Move m{from, to, -1};
                    moves.push_back(m);
                } else {
                    break;
                }
            }
            // Left moves
            for (int to = from - 1; to >= 0; to--) {
                int from_rank = from / 8;
                int to_rank = to / 8;
                if (from_rank == to_rank) {
                    Move m{ from, to, -1 };
                    moves.push_back(m);
                }
                else {
                    break;
                }
            }
        }
    }
}

void MoveGenerator::generateKingMoves(const Board& board, std::vector<Move>& moves, int color)
{
    uint64_t king;
    if (color == WHITE) {
        king = board.getBitboardFromType(Board::W_KING);
    }
    else if (color == BLACK) {
        king = board.getBitboardFromType(Board::B_KING);
    }

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & king) {
            int from_rank = from / 8;
            int from_col = from % 8;
            // Upwards
            if (from_rank <= 7) {
                Move m{ from, from + 8, -1 };
                moves.push_back(m);
            }
            // Downwards
            if (from_rank >= 1) {
                Move m{ from, from - 8, -1 };
                moves.push_back(m);
            }
            // Right
            if (from_col <= 7) {
                Move m{ from, from + 1, -1 };
                moves.push_back(m);
            }
            // Left
            if (from_col >= 1) {
                Move m{ from, from - 1, -1 };
                moves.push_back(m);
            }
            // Right - Up
            if ( from_rank <= 7 && from_col <= 7) {
                Move m{ from, from + 7, -1 };
                moves.push_back(m);
            }
            // Left - Up
            if (from_rank <= 7 && from_col >= 1) {
                Move m{ from, from + 9, -1 };
                moves.push_back(m);
            }
            // Right - Down
            if (from_rank >= 1 && from_col <= 7) {
                Move m{ from, from - 7, -1 };
                moves.push_back(m);
            }
            // Left - Down
            if (from_rank >= 1 && from_col >= 1) {
                Move m{ from, from-9, -1};
                moves.push_back(m);
            }
        }
    }
}
