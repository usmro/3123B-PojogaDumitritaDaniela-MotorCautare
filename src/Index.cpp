#include "Index.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <fstream>

Index::Index() {
    incarcaStopWords();
}

void Index::incarcaStopWords() {
    std::vector<std::string> words = { "si", "in", "la", "cu", "o", "un", "de", "pe", "ca", "the", "a", "is" };
    for (const auto& w : words) stopWords.insert(w);
}

std::string Index::proceseazaCuvant(std::string cuvant) {
    cuvant.erase(std::remove_if(cuvant.begin(), cuvant.end(), ispunct), cuvant.end());
    std::transform(cuvant.begin(), cuvant.end(), cuvant.begin(), ::tolower);
    return cuvant;
}

void Index::adaugaDocument(const Document& doc) {
    std::stringstream ss(doc.getContinut());
    std::string cuvant;
    int contorCuvinte = 0;

    while (ss >> cuvant) {
        cuvant = proceseazaCuvant(cuvant);
        if (!cuvant.empty() && stopWords.find(cuvant) == stopWords.end()) {
            indexInversat[cuvant][doc.getCaleFisier()]++;
            contorCuvinte++;
        }
    }
    dimensiuneDocumente[doc.getCaleFisier()] = contorCuvinte;
    numarTotalDocumente++;
}

std::set<std::string> Index::cautaCuvant(const std::string& cuvant) const {
    std::string c = cuvant;
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);

    std::set<std::string> rezultate;
    auto it = indexInversat.find(c);
    if (it != indexInversat.end()) {
        for (const auto& pereche : it->second) {
            rezultate.insert(pereche.first);
        }
    }
    return rezultate;
}

double Index::calculeazaTF(const std::string& cuvant, const std::string& caleFisier) const {
    auto itCuvant = indexInversat.find(cuvant);
    if (itCuvant != indexInversat.end()) {
        auto itDoc = itCuvant->second.find(caleFisier);
        if (itDoc != itCuvant->second.end()) {
            auto itDim = dimensiuneDocumente.find(caleFisier);
            if (itDim != dimensiuneDocumente.end() && itDim->second > 0) {
                return (double)itDoc->second / itDim->second;
            }
        }
    }
    return 0.0;
}

double Index::calculeazaIDF(const std::string& cuvant) const {
    auto it = indexInversat.find(cuvant);
    if (it != indexInversat.end() && numarTotalDocumente > 0) {
        int docCuCuvant = it->second.size();
        return std::log((double)numarTotalDocumente / (1 + docCuCuvant));
    }
    return 0.0;
}

double Index::getScorTFIDF(const std::string& cuvant, const std::string& caleFisier) const {
    std::string c = cuvant;
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);
    return calculeazaTF(c, caleFisier) * calculeazaIDF(c);
}
void Index::salveazaBazaDate(const std::string& caleFisier) const {
    std::ofstream f(caleFisier);
    if (!f.is_open()) return;

    // Salvăm numărul total de documente
    f << numarTotalDocumente << "\n";

    // Salvăm dimensiunile documentelor
    f << dimensiuneDocumente.size() << "\n";
    for (const auto& pereche : dimensiuneDocumente) {
        f << pereche.first << " " << pereche.second << "\n";
    }

    // Salvăm indexul inversat propriu-zis
    f << indexInversat.size() << "\n";
    for (const auto& cuvantPereche : indexInversat) {
        f << cuvantPereche.first << " " << cuvantPereche.second.size();
        for (const auto& docPereche : cuvantPereche.second) {
            f << " " << docPereche.first << ":" << docPereche.second;
        }
        f << "\n";
    }
    f.close();
}

void Index::incarcaBazaDate(const std::string& caleFisier) {
    std::ifstream f(caleFisier);
    if (!f.is_open()) throw std::runtime_error("Nu s-a putut deschide baza de date a indexului!");

    indexInversat.clear();
    dimensiuneDocumente.clear();

    f >> numarTotalDocumente;

    size_t nrDim;
    f >> nrDim;
    for (size_t i = 0; i < nrDim; ++i) {
        std::string cale;
        int dim;
        f >> cale >> dim;
        dimensiuneDocumente[cale] = dim;
    }

    size_t nrCuvinte;
    f >> nrCuvinte;
    for (size_t i = 0; i < nrCuvinte; ++i) {
        std::string cuvant;
        size_t nrDoc;
        f >> cuvant >> nrDoc;
        for (size_t j = 0; j < nrDoc; ++j) {
            std::string dateDoc;
            f >> dateDoc;
            size_t separator = dateDoc.find(':');
            std::string cale = dateDoc.substr(0, separator);
            int aparitii = std::stoi(dateDoc.substr(separator + 1));
            indexInversat[cuvant][cale] = aparitii;
        }
    }
    f.close();
}