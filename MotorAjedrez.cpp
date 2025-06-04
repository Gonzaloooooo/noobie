// MotorAjedrez.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <sstream>
#include <string>
#include "Board.h"
#include "MoveGenerator.h"
#include "Evaluator.h"

int main()
{
    const int MAKE_MOVE = 0;
    const int GET_BEST_MOVE = 1;
    const int GET_POSITION = 2;
    const int GET_EVALUATION = 3;
    const int RESTART = 4;
    const int WHITE_TO_MOVE = 5;
    const int EXIT = -1;

    Board b = Board(false);
    MoveGenerator moveGen;
    int evaluation;

    bool exit = false;
    int option = 1;
    std::string input;

    while (!exit){
        evaluation = Evaluator::evaluate(b);
        const uint64_t(&pieces)[12] = b.getPieces();
        
        if (!std::getline(std::cin, input)) {
            break;  // Fin de entrada (EOF)
        }

        try {
            option = std::stoi(input);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            break;
        }

        if (std::cin.fail()) {
            std::cout << "OUTPUT:INPUT_ERROR" << std::endl;
            break;
        }

        switch (option) {
        case 0: // MAKE_MOVE
            {
                std::getline(std::cin, input);
                std::istringstream iss(input);
                int from, to, piece, promotion;
                if (!(iss >> from >> to >> piece >> promotion)) {
                    std::cerr << "OUTPUT:INPUT_ERROR" << std::endl;
                    break;
                }
                Move m{ from, to, piece, promotion };
                if (MoveGenerator::isLegal(b, m, (b.isWhiteToMove() ? Board::WHITE : Board::BLACK))) {
                    b.makeMove(m);
                    int alpha = -100000;
                    int beta = 100000;
                    int depth = 2;
                    Evaluator::negamax(b, depth-1, alpha, beta);
                    Move bestMove = Evaluator::getBestMove();
                    b.makeMove(bestMove);
                    std::cout << "Legal move carried out" << std::endl;
                }
                else {
                    std::cout << "Illegal move" << std::endl;
                }
            }
            break;
        case 1: 
            std::cout << "GET_BEST_MOVE" << std::endl;
            break;
        case 2: // GET_POSITION
            for (int i = 0; i<12; i++) {
                std::cout << static_cast<uint64_t>(pieces[i]);
                if (i < 11) {
                    std::cout << '/';
                }
            }
            std::cout << std::endl;
            break;
        case 3: // GET_EVALUATION
            std::cout << evaluation << std::endl;
            break;
        case 4:
            std::cout << "RESTART" << std::endl;
            break;
        case -1:
            std::cout << "EXIT" << std::endl;
            exit = true;
            break;
        default:
            std::cout << "DEFAULT" << std::endl;
            break;
        }
    }
}
