#pragma once
#include <stdint.h> // Para uint64_t
#include <iostream> // Para std::cout
#include "MoveGenerator.h"

class Board
{
private:
    // Almacena las posiciones de las piezas de ajedrez
    uint64_t pieces[12];
    uint64_t white;    // Posiciones de las piezas blancas
    uint64_t black;    // Posiciones de las piezas negras
    uint64_t occupied; // Posiciones ocupadas por cualquier pieza

    // Variables indican si el enroque es posible
    bool blackCastleLeft = true;
    bool blackCastleRight = true;
    bool whiteCastleLeft = true;
    bool whiteCastleRight = true;

    // Movimientos
    int moves = 0;

    // A quién le toca mover
    bool whiteToMove = true;

public:
    // Constantes para indexar las piezas en el array 'pieces'
    static const short W_PAWN = 0;
    static const short W_BISHOP = 1;
    static const short W_KNIGHT = 2;
    static const short W_TOWER = 3;
    static const short W_QUEEN = 4;
    static const short W_KING = 5;
    static const short B_PAWN = 6;
    static const short B_BISHOP = 7;
    static const short B_KNIGHT = 8;
    static const short B_TOWER = 9;
    static const short B_QUEEN = 10;
    static const short B_KING = 11;

    // Default constructor 
    Board();

    // Métodos públicos

    void printBitboard(uint64_t bitboard); // Imprime el bitboard en formato visual
    void make_move(int from, int to);      // Realiza un movimiento de una casilla a otra
    void print();

    bool getBlackCastle(); // Gets a boolean that indicates if castling is possible for black
    bool getWhiteCastle(); // Gets a boolean that indicates if castling is possible for white
    bool isWhiteToMove();  // Gets a boolean that indicates if white is making the next move

    int getMoves(); // Gets the number of moves that have happened in the match

    static uint64_t getBit(uint64_t board, int from);
    static uint64_t setBit(uint64_t board, int to);
    static uint64_t clearBit(uint64_t board, int to);

    // Gets the position of a type of piece using the color and pieces indexes defined in Board
    uint64_t getBitboardFromType(int pieceType);

    // Gets the position of all white pieces in a single bitboard
    uint64_t getWhiteBitBoard();

    // Gets the position of all black pieces in a single bitboard
    uint64_t getBlackBitBoard();

    // Gets the position of all pieces in a single bitboard
    uint64_t getOccupiedBitBoard();

private:
    bool validateMove(uint64_t from, uint64_t to);
};

