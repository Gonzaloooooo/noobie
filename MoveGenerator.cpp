#include "MoveGenerator.h"

std::vector<Move> MoveGenerator::generateMoves(const Board& board, int color) 
{
    std::vector<Move> moves;
    generatePawnMoves(board, moves, color);
    generateBishopMoves(board, moves, color, false);
    generateKnightMoves(board, moves, color);
    generateTowerMoves(board, moves, color, false);
    generateQueenMoves(board, moves, color);
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

bool MoveGenerator::isSameRank(int from, int to)
{
    int from_rank = from / 8;
    int to_rank = to / 8;
    return (from_rank == to_rank);
}

bool MoveGenerator::isSameColumn(int from, int to)
{
    int from_col = from % 8;
    int to_col = to % 8;
    return (from_col == to_col);
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
            
            Move fwd_1{ from, from + 8, PAWN, NULL_TYPE };
            moves.push_back(fwd_1);

            if (from_rank == 1) {
                Move fwd_2{ from, from + 16, PAWN, NULL_TYPE };
                moves.push_back(fwd_2);
            }
            if (from_col < 7) {
                Move right{ from, from + 9, PAWN, NULL_TYPE };
                moves.push_back(right);
            }
            if (from_col > 0) {
                Move left{ from, from + 7, PAWN, NULL_TYPE };
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

            Move fwd_1{ from, from - 8, PAWN, NULL_TYPE };
            moves.push_back(fwd_1);

            if (from_rank == 6) {
                Move fwd_2{ from, from - 16, PAWN, NULL_TYPE };
                moves.push_back(fwd_2);
            }

            if (from_col < 7) {
                Move right{ from, from - 7, PAWN, NULL_TYPE };
                moves.push_back(right);
            }

            if (from_col > 0) {
                Move left{ from, from - 9, PAWN, NULL_TYPE };
                moves.push_back(left);
            }
        }
    }
}

void MoveGenerator::generateBishopMoves(const Board& board, std::vector<Move>& moves, int color, bool forQueen) 
{
    uint64_t bishops;

    if (forQueen) {
        if (color == WHITE) {
            bishops = board.getBitboardFromType(Board::W_QUEEN);
        }
        else if (color == BLACK) {
            bishops = board.getBitboardFromType(Board::B_QUEEN);
        }
    } 
    else 
    {
        if (color == WHITE) {
            bishops = board.getBitboardFromType(Board::W_BISHOP);
        }
        else if (color == BLACK) {
            bishops = board.getBitboardFromType(Board::B_BISHOP);
        }
    }
    

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & bishops) {
            for (int to = from + 9; to < 64; to += 9) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, (forQueen ? QUEEN : BISHOP), NULL_TYPE };
                moves.push_back(m);
            }
            for (int to = from - 9; to >= 0; to -= 9) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, (forQueen ? QUEEN : BISHOP), NULL_TYPE };
                moves.push_back(m);
            }
            for (int to = from + 7; to < 64; to += 7) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, (forQueen ? QUEEN : BISHOP), NULL_TYPE };
                moves.push_back(m);
            }
            for (int to = from - 7; to >= 0; to -= 7) {
                if (!MoveGenerator::isSameDiagonal(from, to)) {
                    break;
                }
                Move m{ from, to, (forQueen ? QUEEN : BISHOP), NULL_TYPE };
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
                    Move m{ from, to, KNIGHT, NULL_TYPE };
                    moves.push_back(m);
                }
            }

        }
    }
}

void MoveGenerator::generateTowerMoves(const Board& board, std::vector<Move>& moves, int color, bool forQueen) 
{
    uint64_t tower;

    if (forQueen) {
        if (color == WHITE) {
            tower = board.getBitboardFromType(Board::W_QUEEN);
        }
        else if (color == BLACK) {
            tower = board.getBitboardFromType(Board::B_QUEEN);
        }
    } else {
        if (color == WHITE) {
            tower = board.getBitboardFromType(Board::W_TOWER);
        }
        else if (color == BLACK) {
            tower = board.getBitboardFromType(Board::B_TOWER);
        }
    }
    

    for (int from = 0; from < 64; from++) {
        uint64_t from_mask = 1ULL << from;
        if (from_mask & tower) {
            // Upward moves
            for (int to = from + 8; to < 64; to+=8) {
                Move m{from, to, (forQueen ? QUEEN : TOWER), NULL_TYPE};
                moves.push_back(m);
            }
            // Downward moves
            for (int to = from - 8; to >= 0; to-=8) {
                Move m{ from, to, (forQueen ? QUEEN : TOWER), NULL_TYPE };
                moves.push_back(m);
            }
            // Right moves
            for (int to = from + 1; to < 64; to++) {
                int from_rank = from / 8;
                int to_rank = to / 8;
                if (from_rank == to_rank) {
                    Move m{from, to, (forQueen ? QUEEN : TOWER), NULL_TYPE };
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
                    Move m{ from, to, (forQueen ? QUEEN : TOWER), NULL_TYPE };
                    moves.push_back(m);
                }
                else {
                    break;
                }
            }
        }
    }
}

void MoveGenerator::generateQueenMoves(const Board& board, std::vector<Move>& moves, int color)
{
    generateBishopMoves(board, moves, color, true);
    generateTowerMoves(board, moves, color, true);
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
            if (from_rank <= 6) {
                int to = from + 8;
                Move m{ from, to, KING, NULL_TYPE };
                moves.push_back(m);
            }
            // Downwards
            if (from_rank >= 1) {
                int to = from - 8;
                Move m{ from, to, KING, NULL_TYPE };
                moves.push_back(m);
            }
            // Right
            if (from_col <= 6) {
                int to = from + 1;
                Move m{ from, to, KING, NULL_TYPE };
                moves.push_back(m);
            }
            // Left
            if (from_col >= 1) {
                int to = from - 1;
                Move m{ from, to, KING, NULL_TYPE };
                moves.push_back(m);
            }
            // Right - Up
            if ( from_rank <= 6 && from_col <= 7) {
                int to = from + 9;
                if (isSameDiagonal(from, to)) {
                    Move m{ from, to, KING, NULL_TYPE };
                    moves.push_back(m);
                }
            }
            // Left - Up
            if (from_rank <= 6 && from_col >= 1) {
                int to = from + 7;
                if (isSameDiagonal(from, to)) {
                    Move m{ from, to, KING, NULL_TYPE };
                    moves.push_back(m);
                }
            }
            // Right - Down
            if (from_rank >= 1 && from_col <= 6) {
                int to = from - 7;
                if (isSameDiagonal(from, to)) {
                    Move m{ from, to, KING, NULL_TYPE };
                    moves.push_back(m);
                }
            }
            // Left - Down
            if (from_rank >= 1 && from_col >= 1) {
                int to = from - 9;
                if (isSameDiagonal(from, to)) {
                    Move m{ from, to, KING, NULL_TYPE };
                    moves.push_back(m);
                }
            }
        }
    }
}

bool MoveGenerator::isHorizontalPathClear(Move m, uint64_t occupied) {
    bool isClear = true;

    int fromRank = m.from / 8;
    int toRank = m.to / 8;

    if (m.from == m.to || fromRank != toRank) {
        throw std::invalid_argument("Movimiento no v�lido: debe ser vertical.");
    }

    if (m.from == m.to) {
        throw std::invalid_argument("La casilla de origen y destino no pueden ser la misma.");
    }

    if (m.from > m.to) {
        for (int i = m.from - 1; i > m.to; i--) {
            uint64_t i_mask = 1ULL << i;
            if (i_mask & occupied) {
                isClear = false;
                break;
            }
        }
    }
    else {
        for (int i = m.from + 1; i < m.to; i++) {
            uint64_t i_mask = 1ULL << i;
            if (i_mask & occupied) {
                isClear = false;
                break;
            }
        }
    }
    return isClear;
}

bool MoveGenerator::isVerticalPathClear(Move m, uint64_t occupied) {
    bool isClear = true;
    int fromRank = m.from / 8;
    int fromCol = m.from % 8;
    int toRank = m.to / 8;
    int toCol = m.to % 8;

    if (m.from == m.to || fromCol != toCol) {
        throw std::invalid_argument("Movimiento no v�lido: debe ser vertical.");
    }

    if (m.from == m.to) {
        throw std::invalid_argument("La casilla de origen y destino no pueden ser la misma.");
    }

    if (fromRank > toRank) {
        for (int rank = fromRank - 1; rank > toRank; rank--) {
            uint64_t mask = 1ULL << (rank * 8 + fromCol);
            if (mask & occupied) {
                isClear = false;
                break;
            }
        }
    }
    else {
        for (int rank = fromRank + 1; rank < toRank; rank++) {
            uint64_t mask = 1ULL << (rank * 8 + fromCol);
            if (mask & occupied) {
                isClear = false;
                break;
            }
        }
    }
    return isClear;
}

bool isDiagonalPathClear(Move m, uint64_t occupied) {
    bool isClear = true;
    int fromRank = m.from / 8;
    int fromCol = m.from % 8;
    int toRank = m.to / 8;
    int toCol = m.to % 8;

    if (m.from == m.to || abs(fromRank - toRank) != abs(fromCol - toCol)) {
        throw std::invalid_argument("Movimiento no v�lido: debe ser diagonal.");
    }

    if (m.from == m.to) {
        throw std::invalid_argument("La casilla de origen y destino no pueden ser la misma.");
    }

    int rankStep = (toRank > fromRank) ? 1 : -1;
    int colStep = (toCol > fromCol) ? 1 : -1;

    for (int rank = fromRank + rankStep, col = fromCol + colStep;
        rank != toRank;
        rank += rankStep, col += colStep) {
        uint64_t mask = 1ULL << (rank * 8 + col);
        if (mask & occupied) {
            isClear = false;
            break;
        }
    }
    return isClear;
}

bool MoveGenerator::isKingInCheck(const Board& board, int kingColor) {
    uint64_t kingBitboard = (kingColor == WHITE) ? board.getBitboardFromType(Board::W_KING)
                                                 : board.getBitboardFromType(Board::B_KING);
    
    // Buscamos la posici�n del rey
    int kingPosition = -1;
    for (int i = 0; i < 64; i++) {
        if (kingBitboard & (1ULL << i)) {
            kingPosition = i;
            break;
        }
    }

    // Generamos los movimientos del oponente
    int opponentColor = (kingColor == WHITE) ? BLACK : WHITE;
    MoveGenerator moveGen;
    std::vector<Move> opponentMoves = moveGen.generateMoves(board, opponentColor);

    for (const Move& move : opponentMoves) {
        if (move.to == kingPosition) {
            return true; // El rey est� en jaque
        }
    }

    return false;
}

bool MoveGenerator::isLegal(const Board& board, Move m) {
    bool isKingInCheck = false;
    int color = (board.isWhiteToMove() ? WHITE : BLACK);
    int pieceIndex = m.piece;
    uint64_t occupied = board.getOccupiedBitBoard();
    uint64_t position = (board.isWhiteToMove() ? board.getWhiteBitBoard() : board.getBlackBitBoard());
    uint64_t oppPosition = (board.isWhiteToMove() ? board.getBlackBitBoard() : board.getWhiteBitBoard());
    uint64_t toMask = 1ULL << m.to;
    Move lastMove = board.getLastMove();

    // Tabla auxiliar para comprobar el jaque
    Board auxBoard = board.clone();
    auxBoard.makeMove(m);

    // Verificar si la casilla de destino est� ocupada por una pieza del mismo color
    if (toMask & position) {
        return false;
    }

    // Comprobar si el camino est� despejado seg�n el tipo de movimiento
    if ((pieceIndex == TOWER || pieceIndex == QUEEN) & isSameRank(m.from, m.to)) {
        return isHorizontalPathClear(m, occupied);
    } 
    else if ((pieceIndex == TOWER || pieceIndex == QUEEN) & isSameColumn(m.from, m.to)) {
        return isVerticalPathClear(m, occupied);
    } 
    else if ((pieceIndex == BISHOP || pieceIndex == QUEEN) & isSameDiagonal(m.from, m.to)) {
        return isDiagonalPathClear(m, occupied);
    }
    else if (pieceIndex == KNIGHT) { // Comprobaci�n para los caballos
        return isKnigthMove(m.from, m.to);
    }
    else if (pieceIndex == PAWN) {
        int direction = (board.isWhiteToMove()) ? 8 : -8; // Blancas suben, negras bajan
        // int startRow = (board.isWhiteToMove()) ? 8 : 48;  // Filas iniciales para peones
        int startRow = m.from / 8;
        //int startRank = m.from % 8;

        // 1 casillas hacia delante
        if ((m.to == m.from + direction) && !(toMask & occupied)) {
            return true;
        }

        // 2 casillas hacia delante
        if ((color == WHITE && startRow == 1) || (color == BLACK && startRow == 6)) {
            if (m.to == m.from + 2 * direction && !(toMask & occupied)) {
                uint64_t intermediateSqu = 1ULL << (m.to + direction);
                if (!(intermediateSqu & occupied)) {
                    return true;
                }
            }
        }

        // Movimiento en diagonal
        if ((m.to == m.from + direction + 1) || (m.to == m.from + direction - 1)) {
            // Captura en diagonal
            if (toMask & oppPosition) {
                return true;
            }
            // En passant
            else if (lastMove.piece == PAWN && abs(lastMove.from - lastMove.to) == 16) { // Anterior movimiento es de pe�n, de dos casillas
                int passantSquare = lastMove.to; // Casilla donde se encuentra la pieza contraria
                if (passantSquare == m.from + 1 || passantSquare == m.from - 1) { // Casilla adyacente
                    return true;
                }
            }
        }
    }
    return false;
}