// MotorAjedrez.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "Board.h"
#include "MoveGenerator.h"

int main()
{
    const int WHITE = 0;
    const int BLACK = 1;

    Board b = Board(false);
    MoveGenerator moveGen;

    auto moves = moveGen.generateMoves(b, WHITE);

    for (auto& move : moves) {
        std::string from = "From: " + std::to_string(move.from);
        std::string to = " - To: " + std::to_string(move.to);
        std::cout << from+to << std::endl;
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
