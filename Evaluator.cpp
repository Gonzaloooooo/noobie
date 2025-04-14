#include "Evaluator.h"

MoveGenerator moveGen;

int Evaluator::negamax(Board& board, int depth, int alpha, int beta) {
    if (depth == 0 || board.isStalemate() /* o board.isCheckmate() si lo tienes */) {
        return evaluate(board);
    }

    int mejorValor = -100000; // Simula -infinito
    std::vector<Move> movimientos = moveGen.generateMoves(board, (board.isWhiteToMove() ? Board::WHITE : Board::BLACK));;

    for (const Move& movimiento : movimientos) {
        // Guarda el estado previo, si es necesario
        board.makeMove(movimiento);

        int valor = -negamax(board, depth - 1, -beta, -alpha);

        board.unmakeMove(); // Requiere implementaci�n

        if (valor > mejorValor) {
            mejorValor = valor;
        }

        if (mejorValor > alpha) {
            alpha = mejorValor;
        }

        if (alpha >= beta) {
            break; // poda beta
        }
    }

    return mejorValor;
}

int Evaluator::evaluate(Board& board) {
    int score = 0;

    // Sumar piezas blancas
    score += __popcnt64(board.getBitboardFromType(Board::W_PAWN)) * PAWN_VALUE;
    score += __popcnt64(board.getBitboardFromType(Board::W_KNIGHT)) * KNIGHT_VALUE;
    score += __popcnt64(board.getBitboardFromType(Board::W_BISHOP)) * BISHOP_VALUE;
    score += __popcnt64(board.getBitboardFromType(Board::W_TOWER)) * ROOK_VALUE;
    score += __popcnt64(board.getBitboardFromType(Board::W_QUEEN)) * QUEEN_VALUE;

    // Restar piezas negras (perspectiva blanca positiva)
    score -= __popcnt64(board.getBitboardFromType(Board::B_PAWN)) * PAWN_VALUE;
    score -= __popcnt64(board.getBitboardFromType(Board::B_KNIGHT)) * KNIGHT_VALUE;
    score -= __popcnt64(board.getBitboardFromType(Board::B_BISHOP)) * BISHOP_VALUE;
    score -= __popcnt64(board.getBitboardFromType(Board::B_TOWER)) * ROOK_VALUE;
    score -= __popcnt64(board.getBitboardFromType(Board::B_QUEEN)) * QUEEN_VALUE;

    // Bonus por ocupaci�n del centro (simplificado)
    // const uint64_t center = 0x0000001818000000ULL; // d4, e4, d5, e5
    // score += __popcnt64(board.getWhiteBitBoard() & center) * 20;
    // score -= __popcnt64(board.getBlackBitBoard() & center) * 20;

    return score;
}

