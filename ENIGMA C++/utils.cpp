#include "utils.h"
#include <cctype>

int lletraAIndex(char c) {
    return std::toupper(c) - 'A';
}

char indexALletra(int i) {
    return 'A' + (i % 26);
}

std::string netejarText(const std::string& text) {
    std::string resultat;
    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c)))
            resultat += std::toupper(static_cast<unsigned char>(c));
    }
    return resultat;
}

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
