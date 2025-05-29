#include <fstream>
#include <algorithm>
#include "rotor.h"
#include "utils.h"

Rotor carregarRotor(const std::string nomFitxer) {
    Rotor rotor;
    std::ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) return rotor;

    std::getline(fitxer, rotor.cablejat);
    if (!validarPermutacio(rotor.cablejat)) return Rotor();

    std::string notchLine;
    if (std::getline(fitxer, notchLine) && !notchLine.empty())
        rotor.notch = notchLine[0];
    else
        rotor.notch = 'Z';

    rotor.posicio = 0;
    return rotor;
}

Rotor girarRotor(Rotor rotor) {
    rotor.posicio = (rotor.posicio + 1) % 26;
    return rotor;
}

char transformarEndavant(char input, Rotor rotor) {
    int index = (lletraAIndex(input) + rotor.posicio) % 26;
    return rotor.cablejat[index];
}

char transformarEnrere(char input, Rotor rotor) {
    int idx = rotor.cablejat.find(input);
    idx = (idx - rotor.posicio + 26) % 26;
    return indexALletra(idx);
}

bool validarPermutacio(std::string cablejat) {
    if (cablejat.size() != 26) return false;
    std::sort(cablejat.begin(), cablejat.end());
    return cablejat == "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

bool guardarPermutacio(std::string nomFitxer, std::string cablejat, char notch) {
    if (!validarPermutacio(cablejat)) return false;
    std::ofstream fitxer(nomFitxer);
    if (!fitxer.is_open()) return false;
    fitxer << cablejat << "\n" << notch;
    return true;
}