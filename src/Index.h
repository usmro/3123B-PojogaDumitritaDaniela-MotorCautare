#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Document.h"

class Index {
private:
    // map: cuvant -> (caleFisier -> numar_aparitii)
    std::map<std::string, std::map<std::string, int>> indexInversat;
    // map: caleFisier -> numar_total_cuvinte_din_el
    std::map<std::string, int> dimensiuneDocumente;
    std::set<std::string> stopWords;
    int numarTotalDocumente = 0;

    std::string proceseazaCuvant(std::string cuvant);
    void incarcaStopWords();

public:
    // Salvează tot indexul din memorie într-un fișier pe disc (Baza de Date)
    void salveazaBazaDate(const std::string& caleFisier) const;

    // Încarcă indexul direct din fișier în memorie (fără să mai citească documentele brute)
    void incarcaBazaDate(const std::string& caleFisier);
    Index();
    void adaugaDocument(const Document& doc);
    std::set<std::string> cautaCuvant(const std::string& cuvant) const;

    // Functii pentru calculul TF-IDF
    double calculeazaTF(const std::string& cuvant, const std::string& caleFisier) const;
    double calculeazaIDF(const std::string& cuvant) const;
    double getScorTFIDF(const std::string& cuvant, const std::string& caleFisier) const;
};

#endif