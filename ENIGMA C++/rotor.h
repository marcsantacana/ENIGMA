#ifndef ROTOR_H
#define ROTOR_H

#include <string>

struct Rotor {
    std::string cablejat;
    char notch;
    int posicio; // 0 a 25
};

Rotor carregarRotor(const std::string nomFitxer);
Rotor girarRotor(Rotor rotor);
char transformarEndavant(char input, Rotor rotor);
char transformarEnrere(char input, Rotor rotor);
bool validarPermutacio(std::string wiring);
bool guardarPermutacio(std::string nomFitxer, std::string wiring, char notch);

#endif