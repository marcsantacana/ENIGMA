// ENIGMA C++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

int main() {

    std::cout << R"(
    ________    __    __    ______     ______     __       __     ______
   |        \  |  \  |  \  |      \   /      \   |  \     /  \   /      \ 
   | $$$$$$$$  | $$\ | $$   \$$$$$$  |  $$$$$$\  | $$\   /  $$  |  $$$$$$\
   | $$__      | $$$\| $$    | $$    | $$ __\$$  | $$$\ /  $$$  | $$__| $$
   | $$  \     | $$$$\ $$    | $$    | $$|    \  | $$$$\  $$$$  | $$    $$
   | $$$$$     | $$\$$ $$    | $$    | $$ \$$$$  | $$\$$ $$ $$  | $$$$$$$$
   | $$_____   | $$ \$$$$   _| $$_   | $$__| $$  | $$ \$$$| $$  | $$  | $$
   | $$     \  | $$  \$$$  |   $$ \   \$$    $$  | $$  \$ | $$  | $$  | $$
    \$$$$$$$$   \$$   \$$   \$$$$$$    \$$$$$$    \$$      \$$   \$$   \$$
)" << std::endl;

    std::cout << "   +----------------------------------------------------+" << std::endl;
    std::cout << "   |       Simulacio de la maquina ENIGMA en C++        |" << std::endl;
    std::cout << "   |      by Marc Santacana & Abderraman Ahiayouch      |" << std::endl;
    std::cout << "   +----------------------------------------------------+" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "   1. Xifrar missatge" << std::endl;
    std::cout << "   2. Desxifrar missatge" << std::endl;
    std::cout << "   3. Editar rotors" << std::endl;
    std::cout << "   4. Sortir" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "   ------------------------------------------------------" << std::endl;
    std::cout << "   Selecciona una opcio (1-4): ";

    int opcio;
    do {
        std::cin >> opcio;
        switch (opcio) {
        case 1:
            xifrarMissatge();
            break;
        case 2:
            desxifrarMissatge();
            break;
        case 3:
            editarRotor();
            break;
        case 4:
            std::cout << "   Sortint del programa...\n";
            break;
        default:
            std::cout << " " << std::endl;
            std::cout << "   [ERROR] Opcio invalida.\n";
        }
    } while (opcio != 4);

    return 0;
}