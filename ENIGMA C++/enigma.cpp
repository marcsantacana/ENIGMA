#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include "enigma.h"
#include "rotor.h"
#include "utils.h"

void comprovarMissatge() {
    const std::string nomFitxer = "Missatge.txt";

    std::ifstream arxiu(nomFitxer);
    if (arxiu.is_open()) {
        std::cout << "   [INFO] S'ha detectat Missatge.txt existent. Si vols introduir un nou missatge hauras de borrar l'arxiu Missatge.txt.\n";
        std::cout << " " << std::endl;
        arxiu.close();
        return;
    }

    std::string missatge;
    std::cout << "    Introdueix el missatge que vols xifrar:\n >  ";
    std::getline(std::cin, missatge);

    std::ofstream out(nomFitxer);
    if (!out) {
        std::cout << "   [ERROR] No s'ha pogut crear Missatge.txt\n";
        return;
    }

    out << missatge;
    out.close();
    std::cout << " " << std::endl;
    std::cout << "   [OK] Missatge guardat a "" << nomFitxer << ""\n";
    return;
}


void xifrarMissatge() {

    Rotor r1 = carregarRotor("Rotor1.txt");
    Rotor r2 = carregarRotor("Rotor2.txt");
    Rotor r3 = carregarRotor("Rotor3.txt");

    if (r1.cablejat.empty() || r2.cablejat.empty() || r3.cablejat.empty()) {
        std::cout << "   [ERROR] No s'han pogut carregar els rotors.\n";
        return;
    }

    std::string finestra;
    std::cout << "   Finestra inicial (ex: ABC): ";
    std::cin >> finestra;
    if (finestra.size() != 3) {
        std::cout << " " << std::endl;
        std::cout << "   [ERROR] Configuracio invalida.\n";
        return;
    }
    r1.posicio = lletraAIndex(finestra[0]);
    r2.posicio = lletraAIndex(finestra[1]);
    r3.posicio = lletraAIndex(finestra[2]);

    std::ifstream in("Missatge.txt");
    if (!in) {
        std::cout << "   [ERROR] No s'ha trobat Missatge.txt\n";
        return;
    }

    std::string entrada;
    for (char c; in.get(c); ) {
        entrada += c;
    }

    std::string net = netejarText(entrada);
    std::string resultat;

    for (char c : net) {
        r1 = girarRotor(r1);
        if (indexALletra(r1.posicio) == r1.notch) r2 = girarRotor(r2);
        if (indexALletra(r2.posicio) == r2.notch) r3 = girarRotor(r3);

        char x = transformarEndavant(c, r1);
        x = transformarEndavant(x, r2);
        x = transformarEndavant(x, r3);
        x = transformarEnrere(x, r3);
        x = transformarEnrere(x, r2);
        x = transformarEnrere(x, r1);

        resultat += x;
    }

    std::ofstream out("Xifrat.txt");
    out << formatGrupsDe5(resultat);

    // Calcular grups de 5 lletres
    int longitud = resultat.size();
    int grupsDe5 = longitud / 5 + (longitud % 5 != 0 ? 1 : 0);
    std::cout << " " << std::endl;
    std::cout << "   [OK] Missatge xifrat a \"Xifrat.txt\" (" << longitud << " lletres, " << grupsDe5 << " grups de 5)\n";
}

void desxifrarMissatge() {

    Rotor r1 = carregarRotor("Rotor1.txt");
    Rotor r2 = carregarRotor("Rotor2.txt");
    Rotor r3 = carregarRotor("Rotor3.txt");

    if (r1.cablejat.empty()  r2.cablejat.empty()  r3.cablejat.empty()) {
        std::cout << "   [ERROR] No s'han pogut carregar els rotors.\n";
        return;
    }

    std::string finestra;
    std::cout << "   Finestra inicial (ex: ABC): ";
    std::cin >> finestra;
    if (finestra.size() != 3) {
        std::cout << " " << std::endl;
        std::cout << "   [ERROR] Configuracio invalida.\n";
        return;
    }
    r1.posicio = lletraAIndex(finestra[0]);
    r2.posicio = lletraAIndex(finestra[1]);
    r3.posicio = lletraAIndex(finestra[2]);

    std::ifstream in("Xifrat.txt");
    if (!in) {
        std::cout << " " << std::endl;
        std::cout << "   [ERROR] No s'ha trobat Xifrat.txt\n";
        return;
    }

    std::string entrada;
    for (char c; in.get(c); ) {
        entrada += c;
    }

    std::string net = netejarText(entrada);
    std::string resultat;

    for (char c : net) {
        r1 = girarRotor(r1);
        if (indexALletra(r1.posicio) == r1.notch) r2 = girarRotor(r2);
        if (indexALletra(r2.posicio) == r2.notch) r3 = girarRotor(r3);

        char x = transformarEndavant(c, r1);
        x = transformarEndavant(x, r2);
        x = transformarEndavant(x, r3);
        x = transformarEnrere(x, r3);
        x = transformarEnrere(x, r2);
        x = transformarEnrere(x, r1);

        resultat += x;
    }
    std::ofstream out("Desxifrat.txt");
    out << resultat;
    int longitud = resultat.size();
    int grupsDe5 = longitud / 5 + (longitud % 5 != 0 ? 1 : 0);
    std::cout << " " << std::endl;
    std::cout << "   [OK] Missatge desxifrat a "Dexifrat.txt" (" << resultat.size() << " lletres, " << grupsDe5 << " grups de 5)\n";
}

void editarRotor() {
    int id;
    std::string wiring;
    char notch;

    std::cout << "   Quin rotor vols editar (1, 2 o 3)? ";
    std::cin >> id;
    if (id < 1 || id > 3) {
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m ID de rotor invalid.\n";
        return;
    }
    std::cout << "   Introdueix nova permutacio (26 lletres uniques A-Z): ";
    std::cin >> wiring;
    std::cout << "   Lletra notch: ";
    std::cin >> notch;

    std::string nom = "Rotor" + std::to_string(id) + ".txt";
    if (guardarPermutacio(nom, wiring, notch))
        std::cout << "\033[32m   [OK]\033[0m Rotor" << id << " actualitzat.\n";
    else
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m Permutacio invalida.\n";
}