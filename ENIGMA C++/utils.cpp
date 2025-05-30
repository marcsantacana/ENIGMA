#include "utils.h"
#include <cctype>

// Converteix una lletra (A-Z) a un índex numèric (0-25).
int lletraAIndex(char c) {
    return std::toupper(c) - 'A';
}

// Converteix un índex numèric (0-25) a una lletra (A-Z).
char indexALletra(int i) {
    return 'A' + (i % 26);
}

// Neteja el text: elimina caràcters no alfabètics i converteix a majúscules.
std::string netejarText(const std::string& text) {
    std::string resultat;
    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c)))
            resultat += std::toupper(static_cast<unsigned char>(c));
    }
    return resultat;
}

// Dona format al text agrupant-lo en blocs de 5 lletres.
std::string formatGrupsDe5(const std::string& text) {
    std::string resultat;
    int count = 0;
    for (char c : text) {
        if (count > 0 && count % 5 == 0) resultat += ' ';
        resultat += c;
        ++count;
    }
    return resultat;
}
