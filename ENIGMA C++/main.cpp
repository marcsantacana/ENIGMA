// ENIGMA C++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "enigma.h"
#include "UI.h"

int main() {
    titolInici();
    int opcio;
    do {
        mostrarMenu();
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
            std::cout << "\033[31m   [ERROR]\033[0m Opcio invalida.\n";
			esperat();
        }
    } while (opcio != 4);

    return 0;
}
