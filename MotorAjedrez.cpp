// MotorAjedrez.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
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
    const int EXIT = -1;

    Board b = Board(false);
    MoveGenerator moveGen;

    bool exit = false;
    int option = 1;
    std::string input;

    while (!exit){
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
        case 0:
            std::cout << "MAKE_MOVE" << std::endl;
            break;
        case 1:
            std::cout << "GET_BEST_MOVE" << std::endl;
            break;
        case 2:
            std::cout << "GET_POSITION" << std::endl;
            break;
        case 3:
            std::cout << "GET_EVALUATION" << std::endl;
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
