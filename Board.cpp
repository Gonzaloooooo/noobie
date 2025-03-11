#include "Board.h"

Board::Board(bool empty) {
    if (empty) {
        //White pieces
        pieces[W_PAWN] = 0ULL;
        pieces[W_BISHOP] = 0ULL;
        pieces[W_KNIGHT] = 0ULL;
        pieces[W_TOWER] = 0ULL;
        pieces[W_KING] = 0ULL;
        pieces[W_QUEEN] = 0ULL;

        //Black pieces
        pieces[B_PAWN] = 0ULL;
        pieces[B_BISHOP] = 0ULL;
        pieces[B_KNIGHT] = 0ULL;
        pieces[B_TOWER] = 0ULL;
        pieces[B_KING] = 0ULL;
        pieces[B_QUEEN] = 0ULL;
    } else {
        //White pieces
        pieces[W_PAWN] = 255ULL << 8;
        pieces[W_BISHOP] = 66ULL;
        pieces[W_KNIGHT] = 36ULL;
        pieces[W_TOWER] = 129ULL;
        pieces[W_KING] = 8ULL;
        pieces[W_QUEEN] = 16ULL;

        //Black pieces
        pieces[B_PAWN] = 255ULL << 48;
        pieces[B_BISHOP] = 66ULL << 56;
        pieces[B_KNIGHT] = 36ULL << 56;
        pieces[B_TOWER] = 129ULL << 56;
        pieces[B_KING] = 8ULL << 56;
        pieces[B_QUEEN] = 16ULL << 56;
    }
}

Board::Board(uint64_t w_pawn, uint64_t w_bishop, uint64_t w_knight, uint64_t w_tower, uint64_t w_king, uint64_t w_queen, 
             uint64_t b_pawn, uint64_t b_bishop, uint64_t b_knight, uint64_t b_tower, uint64_t b_king, uint64_t b_queen)
{
    pieces[W_PAWN] = w_pawn;
    pieces[W_KNIGHT] = w_knight;
    pieces[W_BISHOP] = w_bishop;
    pieces[W_TOWER] = w_tower;
    pieces[W_KING] = w_king;
    pieces[W_QUEEN] = w_queen;

    pieces[B_PAWN] = b_pawn;
    pieces[B_KNIGHT] = b_knight;
    pieces[B_BISHOP] = b_bishop;
    pieces[B_TOWER] = b_tower;
    pieces[B_KING] = b_king;
    pieces[B_QUEEN] = b_queen;
}

void Board::printBitboard(uint64_t bitboard) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            std::cout << ((bitboard & (1ULL << square)) ? "1 " : ". ");
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Board::print() {
    std::cout << "----------------\n";
    printBitboard(getOccupiedBitBoard());
}

bool Board::getBlackCastle() {
    return blackCastleLeft || blackCastleRight;
}

bool Board::getWhiteCastle() {
    return whiteCastleLeft || whiteCastleRight;
}

bool Board::isWhiteToMove() {
    return whiteToMove;
}

int Board::getMoves() {
    return moves;
}

uint64_t Board::getBit(uint64_t board, int from) {
    return board & (1ULL << from);
}

uint64_t Board::setBit(uint64_t board, int to) {
    return board | (1ULL << to);
}

// Sets a bit to 0
uint64_t Board::clearBit(uint64_t board, int to) {
    return board & ~(1ULL << to);
}

// Gets the position of all pieces of a certain type and color
uint64_t Board::getBitboardFromType(int pieceType) const{
    return pieces[pieceType];
}

//
uint64_t Board::getWhiteBitBoard() const{
    return pieces[W_PAWN] | pieces[W_BISHOP] |
        pieces[W_KNIGHT] | pieces[W_TOWER] |
        pieces[W_QUEEN] | pieces[W_KING];
}

//
uint64_t Board::getBlackBitBoard() const{
    return pieces[B_PAWN] | pieces[B_BISHOP] |
        pieces[B_KNIGHT] | pieces[B_TOWER] |
        pieces[B_QUEEN] | pieces[B_KING];
}

uint64_t Board::getOccupiedBitBoard() const{
    return getBlackBitBoard() | getWhiteBitBoard();
}

void Board::make_move(int from, int to) {
    uint64_t from_mask = 1ULL << from;
    uint64_t delete_mask = ~from_mask;
    uint64_t to_mask = 1ULL << to;
    uint64_t occupied = getOccupiedBitBoard();
    if (validateMove(from_mask, to_mask)) {
        occupied = occupied & delete_mask; // set to 0 the bit the piece was in
        occupied = occupied | to_mask;     // set to 1 the bit the piece is goin to
    }
}

bool Board::validateMove(uint64_t from, uint64_t to) {
    bool valid = false;
    uint64_t occupied = getOccupiedBitBoard();
    if ((from == (from & occupied)) && (occupied != (to | occupied))) {
        valid = true;
    }
    return valid;
}

int getBoardIndexFromMoveGenerator(int indexFromMoveGenerator) {
    int indexFromBoard;
    if (indexFromMoveGenerator == 0) {
        indexFromBoard = (whiteToMove ? W_PAWN : B_PAWN);
    }
    else if (indexFromMoveGenerator == 1) {
        indexFromBoard = (whiteToMove ? W_BISHOP : B_BISHOP);
    }
    else if (indexFromMoveGenerator == 2) {
        indexFromBoard = (whiteToMove ? W_KNIGHT : B_KNIGHT);
    }
    else if (indexFromMoveGenerator == 3) {
        indexFromBoard = (whiteToMove ? W_TOWER : B_TOWER);
    }
    else if (indexFromMoveGenerator == 4) {
        indexFromBoard = (whiteToMove ? W_QUEEN : B_QUEEN);
    }
    else if (indexFromMoveGenerator == 5) {
        indexFromBoard = (whiteToMove ? W_KING : B_KING);
    }
}
