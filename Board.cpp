#include "Board.h"

Board::Board() {
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
    printBitboard(occupied);
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

// Gets the value of a bit
uint64_t Board::getBit(uint64_t board, int from) {
    return board & (1ULL << from);
}

// Sets a bit to 1
uint64_t Board::setBit(uint64_t board, int to) {
    return board | (1ULL << to);
}

// Sets a bit to 0
uint64_t Board::clearBit(uint64_t board, int to) {
    return board & ~(1ULL << to);
}

// Gets the position of a type of piece
uint64_t Board::getBitboardFromType(int pieceType) {
    return pieces[pieceType];
}

//
uint64_t Board::getWhiteBitBoard() {
    return pieces[W_PAWN] | pieces[W_BISHOP] |
        pieces[W_KNIGHT] | pieces[W_TOWER] |
        pieces[W_QUEEN] | pieces[W_KING];
}

//
uint64_t Board::getBlackBitBoard() {
    return pieces[B_PAWN] | pieces[B_BISHOP] |
        pieces[B_KNIGHT] | pieces[B_TOWER] |
        pieces[B_QUEEN] | pieces[B_KING];
}

uint64_t Board::getOccupiedBitBoard() {
    return getBlackBitBoard() | getWhiteBitBoard();
}

void Board::make_move(int from, int to) {
    uint64_t from_mask = 1ULL << from;
    uint64_t delete_mask = ~from_mask;
    uint64_t to_mask = 1ULL << to;
    if (validateMove(from_mask, to_mask)) {
        occupied = occupied & delete_mask; // set to 0 the bit the piece was in
        occupied = occupied | to_mask;     // set to 1 the bit the piece is goin to
    }
}

bool Board::validateMove(uint64_t from, uint64_t to) {
    bool valid = false;
    if ((from == (from & occupied)) && (occupied != (to | occupied))) {
        valid = true;
    }
    return valid;
}
