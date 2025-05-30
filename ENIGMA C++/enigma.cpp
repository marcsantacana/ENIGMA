#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include "enigma.h"
#include "rotor.h"
#include "utils.h"
#include "UI.h"

// Comprova si Missatge.txt existeix o demana un nou missatge.
void comprovarMissatge() {
    const std::string nomFitxer = "Missatge.txt";

    std::ifstream arxiu(nomFitxer);
    if (arxiu.is_open()) {
        std::cout << "\033[34m   [INFO]\033[0m S'ha detectat Missatge.txt existent. Si vols introduir un nou missatge hauras de borrar l'arxiu Missatge.txt.\n";
        std::cout << " " << std::endl;
        arxiu.close();
        return;
    }

    std::string missatge;
    std::cout << "    Introdueix el missatge que vols xifrar:\n >  ";
    std::getline(std::cin, missatge);

    std::ofstream out(nomFitxer);
    if (!out) {
        std::cout << "\033[31m   [ERROR]\033[0m No s'ha pogut crear Missatge.txt\n";
        esperat();
        return;
    }

    out << missatge;
    out.close();
    std::cout << " " << std::endl;
    std::cout << "\033[32m   [OK]\033[0m Missatge guardat a \"" << nomFitxer << "\"\n";
    esperat();
    return;
}

// Funció per xifrar el missatge amb els rotors carregats.
void xifrarMissatge() {
    // Mostra el menú específic per a l'opció de xifrat.
    menuXifrar();

    // Carrega els tres rotors des de fitxers de configuració.
    Rotor r1 = carregarRotor("Rotor1.txt");
    Rotor r2 = carregarRotor("Rotor2.txt");
    Rotor r3 = carregarRotor("Rotor3.txt");

    // Comprova si els rotors s'han carregat correctament.
    if (r1.cablejat.empty() || r2.cablejat.empty() || r3.cablejat.empty()) {
        std::cout << "\033[31m   [ERROR]\033[0m No s'han pogut carregar els rotors.\n";
        esperat();
        return;
    }

    // Demana a l'usuari la finestra inicial (posicions inicials A-Z de cada rotor).
    std::string finestra;
    std::cout << "   Finestra inicial (ex: ABC): ";
    std::cin >> finestra;
    if (finestra.size() != 3) {
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m Configuracio invalida.\n";
        esperat();
        return;
    }

    // Converteix les lletres de la finestra inicial a índexs numèrics per als rotors.
    r1.posicio = lletraAIndex(finestra[0]);
    r2.posicio = lletraAIndex(finestra[1]);
    r3.posicio = lletraAIndex(finestra[2]);

    // Obre i llegeix el contingut del fitxer d'entrada Missatge.txt.
    std::ifstream in("Missatge.txt");
    if (!in) {
        std::cout << "\033[31m   [ERROR]\033[0m No s'ha trobat Missatge.txt\n";
        esperat();
        return;
    }

    // Afegeix cada caràcter al string 'entrada'.
    std::string entrada;
    for (char c; in.get(c); ) {
        entrada += c;
    }

    // Neteja el text per deixar només lletres majúscules A-Z.
    std::string net = netejarText(entrada);
    std::string resultat;

    // Procesa cada lletra individualment a través dels rotors.
    for (char c : net) {
        // Gira el primer rotor i, si cal, el segon i tercer segons el notch.
        r1 = girarRotor(r1);
        if (indexALletra(r1.posicio) == r1.notch) r2 = girarRotor(r2);
        if (indexALletra(r2.posicio) == r2.notch) r3 = girarRotor(r3);

        // Passa la lletra a través dels rotors endavant (forward).
        char x = transformarEndavant(c, r1);
        x = transformarEndavant(x, r2);
        x = transformarEndavant(x, r3);

        // Passa la lletra a través dels rotors enrere (reverse).
        x = transformarEnrere(x, r3);
        x = transformarEnrere(x, r2);
        x = transformarEnrere(x, r1);

        // Afegeix el resultat xifrat al text final.
        resultat += x;
    }

    // Escriu el resultat xifrat en grups de 5 lletres al fitxer de sortida Xifrat.txt.
    std::ofstream out("Xifrat.txt");
    out << formatGrupsDe5(resultat);

    // Calcula i mostra informació estadística del resultat.
    int longitud = resultat.size();
    int grupsDe5 = longitud / 5 + (longitud % 5 != 0 ? 1 : 0);
    std::cout << " " << std::endl;
    std::cout << "\033[32m   [OK]\033[0m Missatge xifrat a \"Xifrat.txt\" (" << longitud << " lletres, " << grupsDe5 << " grups de 5)\n";
    
    // Pausa final abans de tornar al menú.
    esperat();
}

// Funció per desxifrar el missatge amb els rotors carregats.
void desxifrarMissatge() {
    // Mostra el menú específic per a desxifrat.
	menuDesxifrar();

    // Carrega els tres rotors des dels fitxers.
    Rotor r1 = carregarRotor("Rotor1.txt");
    Rotor r2 = carregarRotor("Rotor2.txt");
    Rotor r3 = carregarRotor("Rotor3.txt");

    // Comprova si s'han carregat correctament.
    if (r1.cablejat.empty() || r2.cablejat.empty() || r3.cablejat.empty()) {
        std::cout << "\033[31m   [ERROR]\033[0m No s'han pogut carregar els rotors.\n";
        esperat();
        return;
    }

    // Demana a l'usuari la finestra inicial (posició inicial dels rotors).
    std::string finestra;
    std::cout << "   Finestra inicial (ex: ABC): ";
    std::cin >> finestra;
    if (finestra.size() != 3) {
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m Configuracio invalida.\n";
        esperat();
        return;
    }
    r1.posicio = lletraAIndex(finestra[0]);
    r2.posicio = lletraAIndex(finestra[1]);
    r3.posicio = lletraAIndex(finestra[2]);

    // Llegeix el text xifrat des del fitxer.
    std::ifstream in("Xifrat.txt");
    if (!in) {
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m No s'ha trobat Xifrat.txt\n";
        esperat();
        return;
    }

    std::string entrada;
    for (char c; in.get(c); ) {
        entrada += c;
    }

    // Neteja el text per assegurar-se que només conté lletres.
    std::string net = netejarText(entrada);
    std::string resultat;

    // Processa cada lletra del missatge.
    for (char c : net) {
        r1 = girarRotor(r1);
        if (indexALletra(r1.posicio) == r1.notch) r2 = girarRotor(r2);
        if (indexALletra(r2.posicio) == r2.notch) r3 = girarRotor(r3);

        // Passa pels rotors endavant i enrere per recuperar l'original.
        char x = transformarEndavant(c, r1);
        x = transformarEndavant(x, r2);
        x = transformarEndavant(x, r3);
        x = transformarEnrere(x, r3);
        x = transformarEnrere(x, r2);
        x = transformarEnrere(x, r1);

        resultat += x;
    }

    // Guarda el missatge desxifrat al fitxer de sortida.
    std::ofstream out("Desxifrat.txt");
    out << resultat;
    int longitud = resultat.size();
    int grupsDe5 = longitud / 5 + (longitud % 5 != 0 ? 1 : 0);
    std::cout << " " << std::endl;
    std::cout << "\033[32m   [OK]\033[0m Missatge desxifrat a \"Dexifrat.txt\" (" << resultat.size() << " lletres, " << grupsDe5 << " grups de 5)\n";
    esperat();
}

// Funció per editar un rotor manualment des de consola.
void editarRotor() {
    int id;
    std::string wiring;
    char notch;

    // Mostra el menú d'edició de rotors.
	menuRotors();

    // Demana quin rotor es vol editar.
    std::cout << "   Quin rotor vols editar (1, 2 o 3)? ";
    std::cin >> id;
    if (id < 1 || id > 3) {
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m ID de rotor invalid.\n";
        return;
    }

    // Demana el nou wiring (26 lletres úniques A-Z).
    std::cout << "   Introdueix nova permutacio (26 lletres uniques A-Z): ";
    std::cin >> wiring;

    // Demana la lletra notch.
    std::cout << "   Lletra notch: ";
    std::cin >> notch;

    // Guarda la nova configuració al fitxer corresponent.
    std::string nom = "Rotor" + std::to_string(id) + ".txt";
    if (guardarPermutacio(nom, wiring, notch))
        std::cout << "\033[32m   [OK]\033[0m Rotor" << id << " actualitzat.\n";
    else
        std::cout << " " << std::endl;
        std::cout << "\033[31m   [ERROR]\033[0m Permutacio invalida.\n";
        esperat();
}