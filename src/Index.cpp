#include "Index.h"
#include <algorithm>
#include <sstream>
#include <cctype>

Index::Index() {
    incarcaStopWords();
}

void Index::incarcaStopWords() {
    // Facultativ: Eliminare stop-words
    std::vector<std::string> words = { "si", "in", "la", "cu", "o", "un", "de", "pe", "ca" };
    for (const auto& w : words) {
        stopWords.insert(w);
    }
}

std::string Index::proceseazaCuvant(std::string cuvant) {
    // Convertim la litere mici și eliminăm punctuația
    cuvant.erase(std::remove_if(cuvant.begin(), cuvant.end(), ispunct), cuvant.end());
    std::transform(cuvant.begin(), cuvant.end(), cuvant.begin(), ::tolower);
    return cuvant;
}

void Index::adaugaDocument(const Document& doc) {
    std::stringstream ss(doc.getContinut());
    std::string cuvant;

    while (ss >> cuvant) {
        cuvant = proceseazaCuvant(cuvant);
        if (!cuvant.empty() && stopWords.find(cuvant) == stopWords.end()) {
            indexInversat[cuvant].insert(doc.getCaleFisier());
        }
    }
}

std::set<std::string> Index::cautaCuvant(const std::string& cuvant) {
    std::string c = cuvant;
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);

    if (indexInversat.find(c) != indexInversat.end()) {
        return indexInversat[c];
    }
    return std::set<std::string>(); // Returnează gol dacă nu găsește
}