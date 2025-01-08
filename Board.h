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

    //Límites del tablero
    static const uint64_t left = 9259542123273814144ULL;
    static const uint64_t right = 72340172838076673ULL;
    static const uint64_t top = 255ULL << 56;
    static const uint64_t bottom = 255ULL;

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

    /*
    * @brief
    * Recibe un entero de 64 bits y extrae un bit concreto que es 
    * devuelto en otro entero de 64 bits en la misma posición en la 
    * que se encontraba.
    * 
    * @params board
    * Entero del que se extraerá el valor del bit.
    * 
    * @params from 
    * Posición del bit que se va a extraer a partir 
    * del bit menos significativo.
    * 
    * @returns 
    * Devuelve un entero con el único bit indicado.
    */
    static uint64_t getBit(uint64_t board, int from);
    /*
    * @brief 
    * Pone el bit de un entero a 1 y lo devuelve.
    * 
    * @params board 
    * Es el entero de 64 bits que va a ser modificado.
    * 
    * @params to
    * Indica el bit que va a ser puesto a 1 a partir 
    * del bit menos significativo.
    * 
    * @returns
    * Devuelve el entero con el bit indicado puesto a 1.
    * 
    * @details
    * Si el bit indicado ya vale 1, se queda igual.
    */
    static uint64_t setBit(uint64_t board, int to);
    /*
    * @brief 
    * Recibe un entero de 64 bits, pone un bit en concreto a 0 y lo devuelve.
    * 
    * @params board
    * Entero de 64 bits que va a ser modificado.
    * 
    * @params to
    * Posición del bit que va a ser puesto a 0 a partir 
    * del bit menos significativo.
    * 
    * @returns
    */
    static uint64_t clearBit(uint64_t board, int to);

    // Gets the position of a type of piece using the color and pieces indexes defined in Board
    uint64_t getBitboardFromType(int pieceType) const;

    // Gets the position of all white pieces in a single bitboard
    uint64_t getWhiteBitBoard() const;

    // Gets the position of all black pieces in a single bitboard
    uint64_t getBlackBitBoard() const;

    // Gets the position of all pieces in a single bitboard
    uint64_t getOccupiedBitBoard() const;

private:
    bool validateMove(uint64_t from, uint64_t to);
};

