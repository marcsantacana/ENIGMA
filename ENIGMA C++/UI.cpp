// ENIGMA C++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "enigma.h"

void titolInici() {
    const std::string blau = "\033[34m";
    const std::string reset = "\033[0m";

    std::cout << blau;
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
    // Tornar al color normal
    std::cout << reset;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    system("clear || cls");
}

void titolEnigma() {
    const std::string blau = "\033[34m";
    const std::string reset = "\033[0m";

    std::cout << blau;
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
    std::cout << reset;
}

void mostrarMenu() {
    std::cout << " " << std::endl;
    titolEnigma();
    comprovarMissatge();
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
}

void menuXifrar() {
    system("cls");

	titolEnigma();
    std::cout << R"(
   +----------------------------------+     .-""-.
   |        Xifrar el missatge        |    / .--. \
   +----------------------------------+   / /    \ \
                                          | |    | |
                                          | |    | |
                                          | |.-""-.|
                                         ///`.::::.`\
                                        ||| ::/  \:: ;
                                        ||; ::\__/:: ;
                                         \\\ '::::' /
                                          `=':-..-'`
             )" << std::endl;
}

void menuDesxifrar() {
    system("cls");

    titolEnigma();
    std::cout << R"(
   +-------------------------------------+     .-""-.
   |        Desxifrar el missatge        |    / .--. \
   +-------------------------------------+   / /    \ \
                                             | |    | |
                                             | |    | |.-""-.
                                                   ///`.::::.`\
                                                  ||| ::/  \:: ;
                                                  ||; ::\__/:: ;
                                                   \\\ '::::' /
                                                    `=':-..-'`
)" << std::endl;
}

void menuRotors() {
    system("cls");

    titolEnigma();
    std::cout << R"(
   +---------------------------------+                                               
   |        Editar els rotors        |                                                     
   +---------------------------------+                              
)" << std::endl;
}

void esperat() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("clear || cls");
}